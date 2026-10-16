unit TgBot.Http;

{
  TgBot — HTTP-транспорт Bot API на System.Net.HttpClient.

  - ITgTransport — абстракция транспорта (подменяется в тестах);
  - ITgCancellableTransport — транспорт с токеном отмены на операцию;
    оба контракта и записи настроек объявлены в TgBot.Intf (для своей
    реализации транспорта достаточно его), здесь — псевдонимы;
  - TTgHttpTransport — реализация: POST JSON / multipart, GET для файлов,
    пул THTTPClient (THTTPClient не потокобезопасен — каждый запрос берёт
    клиент из пула в монопольное пользование), разбор ответа Bot API,
    автоповтор 429, простой лимитёр, прерываемые ожидания.

  Отмена операции (токен ITgCancellation):
  - ожидания лимитёра и retry_after прерываются сразу (WaitFor токена);
  - идущий HTTP-запрос на Windows и macOS прерывается IHTTPRequest.Cancel;
    на всех платформах приём/передача данных прерываются через
    Receive/SendDataCallback (AAbort). На Linux (libcurl) и Android
    «молчащее» соединение прерывается только по таймауту ответа: Cancel
    запроса из другого потока там небезопасен или не действует.

  Токен бота никогда не попадает в тексты исключений.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.Classes,
  System.SyncObjs,
  System.Generics.Collections,
  System.Diagnostics,
  System.JSON,
  System.Net.URLClient,
  System.Net.HttpClient,
  System.Net.Mime,
  TgBot.Base,
  TgBot.Json,
  TgBot.Intf;

const
  /// <summary>Адрес облачного Bot API по умолчанию (TgBot.Intf).</summary>
  TgDefaultApiUrl = TgBot.Intf.TgDefaultApiUrl;
  /// <summary>Таймаут соединения по умолчанию, мс (TgBot.Intf).</summary>
  TgDefaultConnectionTimeoutMs = TgBot.Intf.TgDefaultConnectionTimeoutMs;
  /// <summary>Таймаут ответа по умолчанию, мс (TgBot.Intf).</summary>
  TgDefaultResponseTimeoutMs = TgBot.Intf.TgDefaultResponseTimeoutMs;
  /// <summary>Запас к timeout getUpdates при расчёте таймаута ответа, с.</summary>
  TgLongPollReserveSec = 15;
  /// <summary>Максимум попыток повтора при 429 по умолчанию (TgBot.Intf).</summary>
  TgDefaultMaxRetries = TgBot.Intf.TgDefaultMaxRetries;
  /// <summary>Максимальное ожидание retry_after по умолчанию, с (TgBot.Intf).</summary>
  TgDefaultMaxRetryAfterSec = TgBot.Intf.TgDefaultMaxRetryAfterSec;
  /// <summary>Глобальный лимит запросов в секунду на бота по умолчанию (TgBot.Intf).</summary>
  TgDefaultGlobalRatePerSec = TgBot.Intf.TgDefaultGlobalRatePerSec;
  /// <summary>Минимальный интервал между сообщениями в один чат по умолчанию, мс (TgBot.Intf).</summary>
  TgDefaultPerChatIntervalMs = TgBot.Intf.TgDefaultPerChatIntervalMs;
  /// <summary>Максимум простаивающих HTTP-клиентов в пуле.</summary>
  TgMaxIdleClients = 8;

type
  { Контракты транспорта объявлены в TgBot.Intf (модуль без реализаций и без
    System.Net); здесь — псевдонимы для совместимости: те же типы и GUID. }

  /// <summary>Настройки HTTP-прокси бота (описание — TgBot.Intf.TTgProxySettings).</summary>
  TTgProxySettings = TgBot.Intf.TTgProxySettings;
  /// <summary>Настройки транспорта (описание — TgBot.Intf.TTgHttpSettings).</summary>
  TTgHttpSettings = TgBot.Intf.TTgHttpSettings;
  /// <summary>Сырой HTTP-ответ (TgBot.Intf).</summary>
  TTgHttpResponse = TgBot.Intf.TTgHttpResponse;
  /// <summary>Транспорт Bot API (описание — TgBot.Intf.ITgTransport).</summary>
  ITgTransport = TgBot.Intf.ITgTransport;
  /// <summary>Транспорт с отменой отдельной операции (описание — TgBot.Intf.ITgCancellableTransport).</summary>
  ITgCancellableTransport = TgBot.Intf.ITgCancellableTransport;

  /// <summary>
  ///   Преобразование настроек прокси в настройки RTL. Помощник записи
  ///   объявлен здесь, а не в TgBot.Intf: TProxySettings — тип
  ///   System.Net.URLClient. Действует там, где подключён TgBot.Http.
  /// </summary>
  TTgProxySettingsHelper = record helper for TTgProxySettings
    /// <summary>
    ///   Настройки прокси для THTTPClient: Normalized, схема всегда пустая
    ///   (единственный вариант HTTP-прокси, корректный на всех платформах).
    /// </summary>
    function ToRtlSettings: TProxySettings;
  end;

  /// <summary>
  ///   Простой потокобезопасный лимитёр: глобальное «ведро токенов»
  ///   (N запросов в секунду) и минимальный интервал между отправками в один чат.
  /// </summary>
  TTgRateLimiter = class
  private
    FLock: TCriticalSection;
    FClock: TStopwatch;
    FGlobalRatePerSec: Integer;
    FPerChatIntervalMs: Integer;
    FTokens: Double;
    FLastRefillMs: Int64;
    FChatNext: TDictionary<string, Int64>;
    procedure PurgeChats(ANowMs: Int64);
  public
    constructor Create(AGlobalRatePerSec, APerChatIntervalMs: Integer);
    destructor Destroy; override;
    /// <summary>
    ///   Резервирует слот отправки и возвращает время ожидания, мс.
    ///   AChatKey — ключ чата для лимита на чат ('' — только глобальный лимит).
    /// </summary>
    function Reserve(const AChatKey: string): Integer;
  end;

  /// <summary>
  ///   Служебный: транспорт с настройками TTgHttpSettings (описание —
  ///   TgBot.Intf.ITgHttpSettingsProvider). В прикладном коде не нужен.
  /// </summary>
  ITgHttpSettingsProvider = TgBot.Intf.ITgHttpSettingsProvider;

  /// <summary>Транспорт на System.Net.HttpClient. Настройки неизменяемы после создания.</summary>
  TTgHttpTransport = class(TInterfacedObject, ITgTransport, ITgCancellableTransport,
    ITgHttpSettingsProvider)
  private
    FSettings: TTgHttpSettings;
    // Защищает пул клиентов и замену FGlobalCancel.
    FPoolLock: TCriticalSection;
    FPool: TStack<THTTPClient>;
    // Глобальная отмена (устаревшие Cancel/ResetCancel); ResetCancel заменяет источник.
    FGlobalCancel: ITgCancellationSource;
    FLimiter: TTgRateLimiter;
    function CreateClient: THTTPClient;
    function AcquireClient: THTTPClient;
    procedure ReleaseClient(AClient: THTTPClient; ADiscard: Boolean);
    function ResponseTimeoutFor(const AMethod: string; AParams: TTgParams): Integer;
    function ChatKeyFor(const AMethod: string; AParams: TTgParams): string;
    procedure FillMultipart(AForm: TMultipartFormData; AParams: TTgParams;
      AOwnedStreams: TObjectList<TStream>);
    /// <summary>Текущий источник глобальной отмены (под FPoolLock).</summary>
    function GlobalCancelSource: ITgCancellationSource;
    function GlobalCancel: ITgCancellation;
    { ITgHttpSettingsProvider }
    function GetSettings: TTgHttpSettings;
    /// <summary>Токен ожиданий: операция (ACancel) или глобальная отмена.</summary>
    function WaitTokenFor(const ACancel: ITgCancellation): ITgCancellation;
    procedure WaitInterruptible(AMs: Integer; const AToken: ITgCancellation);
    /// <summary>
    ///   Выполняет подготовленный запрос с отменой по AToken (nil — без отмены).
    ///   Отмена до или во время выполнения — ETgCancelledError.
    /// </summary>
    function ExecuteRequest(AClient: THTTPClient; const ARequest: IHTTPRequest;
      AContent: TStream; const AHeaders: TNetHeaders;
      const AToken: ITgCancellation): IHTTPResponse;
    /// <summary>ETgCancelledError при отменённом AToken, иначе сетевая ошибка.</summary>
    function FailureFrom(const AMethod: string; AError: Exception;
      const AToken: ITgCancellation): Exception;
  protected
    /// <summary>
    ///   Скрывает токен в тексте (для сообщений об ошибках) — как есть
    ///   и в URL-кодированном виде.
    /// </summary>
    function MaskToken(const AText: string): string;
    /// <summary>
    ///   Сетевая ошибка по исключению транспорта; токен в тексте маскируется.
    /// </summary>
    function NetworkErrorFrom(const AMethod: string; AError: Exception): ETgNetworkError;
    /// <summary>
    ///   Текст сетевой ошибки с адресом прокси (host:port, без учётных данных),
    ///   если прокси задан; иначе AMessage без изменений.
    /// </summary>
    function WithProxyInfo(const AMessage: string): string;
    /// <summary>URL метода Bot API.</summary>
    function MethodUrl(const AMethod: string): string;
    /// <summary>
    ///   Отправляет один HTTP-запрос метода (без повторов и разбора).
    ///   Виртуальный — для подмены в тестах. Сетевые ошибки — ETgNetworkError.
    ///   Токен отмены операции — окружающий (TTgCancelScope.Current): ExecuteEx
    ///   устанавливает его на время вызова; отмена — ETgCancelledError.
    /// </summary>
    function SendRequest(const AMethod: string; AParams: TTgParams): TTgHttpResponse; virtual;
  public
    /// <summary>
    ///   Создаёт транспорт; пустой токен или неверные настройки прокси
    ///   (TTgProxySettings.Normalized) — ETgError.
    /// </summary>
    constructor Create(const ASettings: TTgHttpSettings);
    destructor Destroy; override;
    /// <summary>ExecuteEx с окружающим токеном (TTgCancelScope.Current).</summary>
    function Execute(const AMethod: string; AParams: TTgParams): TJSONValue;
    /// <summary>DownloadFileEx с окружающим токеном (TTgCancelScope.Current).</summary>
    procedure DownloadFile(const AFilePath: string; ADest: TStream);
    function ExecuteEx(const AMethod: string; AParams: TTgParams;
      const ACancel: ITgCancellation): TJSONValue;
    procedure DownloadFileEx(const AFilePath: string; ADest: TStream;
      const ACancel: ITgCancellation);
    procedure Cancel;
    procedure ResetCancel;
    function IsCancelled: Boolean;
    /// <summary>Настройки транспорта.</summary>
    property Settings: TTgHttpSettings read FSettings;
  end;

implementation

uses
  System.Math,
  System.NetConsts,
  System.NetEncoding;

/// <summary>
///   Таймаут ответа клиента: AMs <= 0 — значение RTL по умолчанию (как у нового
///   клиента). Присваивается всегда: клиент из пула мог сохранить увеличенный
///   таймаут long polling.
/// </summary>
procedure ApplyResponseTimeout(AClient: THTTPClient; AMs: Integer);
begin
  if AMs > 0 then
    AClient.ResponseTimeout := AMs
  else
    AClient.ResponseTimeout := TURLClient.DefaultResponseTimeout;
end;

/// <summary>Имя файла для multipart: без '"' и управляющих символов; пустое — 'file'.</summary>
function SanitizeFormFileName(const AFileName: string): string;
var
  I: Integer;
begin
  Result := AFileName;
  for I := Length(Result) downto 1 do
    if (Result[I] = '"') or (Result[I] < ' ') then
      Delete(Result, I, 1);
  if Trim(Result) = '' then
    Result := 'file';
end;

/// <summary>
///   Добавляет поток в форму без лишнего копирования. Форма не владеет потоком:
///   он должен жить до окончания отправки (Post). Отправляется с позиции 0.
/// </summary>
procedure AddFormStream(AForm: TMultipartFormData; const AField: string;
  AStream: TStream; const AFileName, AContentType: string);
begin
{$IF CompilerVersion >= 36}
  // Delphi 12+: поток читается при отправке, без копирования в память.
  AForm.AddStream(AField, AStream, False, AFileName, AContentType);
{$ELSE}
  // До Delphi 12: содержимое сразу копируется в форму (CopyFrom с позиции 0).
  AForm.AddStream(AField, AStream, AFileName, AContentType);
{$ENDIF}
end;

/// <summary>Путь UNC ('\\server', '//server' и смешанные разделители).</summary>
function IsUncPath(const APath: string): Boolean;
begin
  Result := (Length(APath) >= 2) and CharInSet(APath[1], ['\', '/']) and
    CharInSet(APath[2], ['\', '/']);
end;

/// <summary>
///   В пути есть сегмент из одних точек длиной от двух ('..', '...', '.. '):
///   Windows нормализует такие сегменты, поэтому отклоняются все.
/// </summary>
function HasParentSegment(const APath: string): Boolean;
var
  LSegment: string;
begin
  for LSegment in APath.Split(['\', '/']) do
    if (Length(Trim(LSegment)) >= 2) and (Trim(LSegment).Replace('.', '') = '') then
      Exit(True);
  Result := False;
end;

/// <summary>Абсолютный путь POSIX ('/dir/file') или Windows ('C:\dir\file').</summary>
function IsAbsoluteLocalPath(const APath: string): Boolean;
begin
  Result := (APath <> '') and ((APath[1] = '/') or
    ((Length(APath) >= 3) and (APath[2] = ':') and CharInSet(APath[3], ['\', '/'])));
end;

/// <summary>Содержимое потока целиком (с позиции 0); nil — пустой массив.</summary>
function ReadAllBytes(AStream: TStream): TBytes;
begin
  Result := nil;
  if not Assigned(AStream) then
    Exit;
  AStream.Position := 0;
  SetLength(Result, AStream.Size);
  if Length(Result) > 0 then
    AStream.ReadBuffer(Result[0], Length(Result));
end;

type
  /// <summary>
  ///   Связь токена отмены с идущим запросом: Fire вызывает Cancel запроса,
  ///   Detach (после Execute) гарантирует, что запрос больше не тронут —
  ///   Detach ждёт окончания идущего Fire.
  /// </summary>
  ITgRequestCanceller = interface
    procedure Fire;
    procedure Detach;
    /// <summary>
    ///   Повторная отмена (запрос ещё привязан): True — продолжать попытки,
    ///   False — запрос отвязан (Detach).
    /// </summary>
    function Refire: Boolean;
  end;

  /// <summary>
  ///   Реализация ITgRequestCanceller. THTTPClient.Execute сбрасывает
  ///   признак отмены запроса (DoResetCancel), если Cancel пришёл между
  ///   проверкой токена и входом в Execute. POST прерывается колбэком
  ///   передачи (он проверяет токен после сброса), а у GET без тела до
  ///   заголовков ответа колбэков нет — поэтому после Fire отмена
  ///   повторяется из короткоживущего потока, пока запрос не отвязан.
  /// </summary>
  TTgRequestCanceller = class(TInterfacedObject, ITgRequestCanceller)
  private
    FRequest: IHTTPRequest;
    FRefiring: Boolean;
  public
    constructor Create(const ARequest: IHTTPRequest);
    procedure Fire;
    procedure Detach;
    function Refire: Boolean;
  end;

const
  // Повторная отмена запроса после Fire: число попыток и интервал, мс.
  CRefireCount = 10;
  CRefireIntervalMs = 30;

/// <summary>Повторяет отмену запроса, пока он привязан (не дольше CRefireCount попыток).</summary>
procedure StartRefire(const ACanceller: ITgRequestCanceller);
begin
  TThread.CreateAnonymousThread(
    procedure
    var
      I: Integer;
    begin
      for I := 1 to CRefireCount do
      begin
        TThread.Sleep(CRefireIntervalMs);
        if not ACanceller.Refire then
          Break;
      end;
    end).Start;
end;

constructor TTgRequestCanceller.Create(const ARequest: IHTTPRequest);
begin
  inherited Create;
  FRequest := ARequest;
end;

procedure TTgRequestCanceller.Fire;
begin
  TMonitor.Enter(Self);
  try
    if not Assigned(FRequest) then
      Exit;
    FRequest.Cancel;
    if FRefiring then
      Exit;
    FRefiring := True;
  finally
    TMonitor.Exit(Self);
  end;
  // Отмена могла прийти до входа в Execute и быть сброшена им — повторяем.
  // Fire вызывается только через ITgRequestCanceller (счётчик ссылок > 0).
  StartRefire(Self);
end;

function TTgRequestCanceller.Refire: Boolean;
begin
  TMonitor.Enter(Self);
  try
    Result := Assigned(FRequest);
    // Cancel идемпотентен: повторный вызов действует, только если признак сброшен.
    if Result and not FRequest.IsCancelled then
      FRequest.Cancel;
  finally
    TMonitor.Exit(Self);
  end;
end;

procedure TTgRequestCanceller.Detach;
begin
  TMonitor.Enter(Self);
  try
    FRequest := nil;
  finally
    TMonitor.Exit(Self);
  end;
end;

// Замыкания создаются в отдельных функциях: захватывается только нужное
// (без запроса и Self), поэтому циклов ссылок «запрос → колбэк → запрос» нет.

/// <summary>Колбэк подписки на токен: отменяет запрос через связь.</summary>
function NewRequestCancelCallback(const ACanceller: ITgRequestCanceller): TProc;
begin
  Result :=
    procedure
    begin
      ACanceller.Fire;
    end;
end;

/// <summary>Колбэк приёма данных: прерывает приём при отменённом токене.</summary>
function NewReceiveAbortCallback(const AToken: ITgCancellation): TReceiveDataCallback;
begin
  Result :=
    procedure(const Sender: TObject; AContentLength, AReadCount: Int64; var AAbort: Boolean)
    begin
      if AToken.IsCancelled then
        AAbort := True;
    end;
end;

/// <summary>Колбэк передачи данных: прерывает отправку при отменённом токене.</summary>
function NewSendAbortCallback(const AToken: ITgCancellation): TSendDataCallback;
begin
  Result :=
    procedure(const Sender: TObject; AContentLength, AWriteCount: Int64; var AAbort: Boolean)
    begin
      if AToken.IsCancelled then
        AAbort := True;
    end;
end;

{ TTgProxySettingsHelper }

function TTgProxySettingsHelper.ToRtlSettings: TProxySettings;
var
  LProxy: TTgProxySettings;
begin
  LProxy := Normalized;
  // Схема RTL — не схема прокси: на Windows это протокол связи с прокси
  // ('https://' — WinHTTP начинает с прокси TLS, обычный HTTP-прокси
  // отвечает ошибкой 12029; HTTPS-прокси не поддерживаем), на macOS — фильтр
  // целевых URL ('http' пустил бы https:// мимо прокси), curl её не
  // использует. Пустая схема — HTTP-прокси для всех запросов, везде.
  Result := TProxySettings.Create(LProxy.Host, LProxy.Port, LProxy.UserName,
    LProxy.Password, '');
end;

{ TTgRateLimiter }

constructor TTgRateLimiter.Create(AGlobalRatePerSec, APerChatIntervalMs: Integer);
begin
  inherited Create;
  FLock := TCriticalSection.Create;
  FChatNext := TDictionary<string, Int64>.Create;
  FGlobalRatePerSec := Max(AGlobalRatePerSec, 0);
  FPerChatIntervalMs := Max(APerChatIntervalMs, 0);
  FTokens := FGlobalRatePerSec;
  FClock := TStopwatch.StartNew;
  FLastRefillMs := 0;
end;

destructor TTgRateLimiter.Destroy;
begin
  FreeAndNil(FChatNext);
  FreeAndNil(FLock);
  inherited Destroy;
end;

procedure TTgRateLimiter.PurgeChats(ANowMs: Int64);
var
  LExpired: TList<string>;
  LPair: TPair<string, Int64>;
  LKey: string;
begin
  LExpired := TList<string>.Create;
  try
    for LPair in FChatNext do
      if LPair.Value <= ANowMs then
        LExpired.Add(LPair.Key);
    for LKey in LExpired do
      FChatNext.Remove(LKey);
  finally
    LExpired.Free;
  end;
end;

function TTgRateLimiter.Reserve(const AChatKey: string): Integer;
const
  CMaxTrackedChats = 4096;
var
  LNow, LNext: Int64;
  LCapacity, LRefilled, LWaitMs: Double;
begin
  Result := 0;
  FLock.Enter;
  try
    LNow := FClock.ElapsedMilliseconds;
    if FGlobalRatePerSec > 0 then
    begin
      // Пополнение ведра; отрицательный остаток — очередь уже зарезервированных слотов.
      LCapacity := FGlobalRatePerSec;
      LRefilled := FTokens + (LNow - FLastRefillMs) * LCapacity / 1000;
      if LRefilled > LCapacity then
        LRefilled := LCapacity;
      FTokens := LRefilled - 1;
      FLastRefillMs := LNow;
      if FTokens < 0 then
      begin
        LWaitMs := -FTokens * 1000 / LCapacity;
        Result := Trunc(LWaitMs) + 1;
      end;
    end;
    if (FPerChatIntervalMs > 0) and (AChatKey <> '') then
    begin
      if not FChatNext.TryGetValue(AChatKey, LNext) or (LNext < LNow) then
        LNext := LNow;
      Result := Max(Result, Integer(LNext - LNow));
      FChatNext.AddOrSetValue(AChatKey, LNext + FPerChatIntervalMs);
      if FChatNext.Count > CMaxTrackedChats then
        PurgeChats(LNow);
    end;
  finally
    FLock.Leave;
  end;
end;

{ TTgHttpTransport }

constructor TTgHttpTransport.Create(const ASettings: TTgHttpSettings);
begin
  inherited Create;
  if Trim(ASettings.Token) = '' then
    raise ETgError.Create(TgText(TTgText.TokenRequired));
  FSettings := ASettings;
  FSettings.Token := Trim(FSettings.Token);
  // Неверный прокси — ошибка сразу, а не сетевая при первом запросе.
  FSettings.Proxy := FSettings.Proxy.Normalized;
  if FSettings.ApiUrl = '' then
    FSettings.ApiUrl := TgDefaultApiUrl;
  while (FSettings.ApiUrl <> '') and (FSettings.ApiUrl[Length(FSettings.ApiUrl)] = '/') do
    SetLength(FSettings.ApiUrl, Length(FSettings.ApiUrl) - 1);
  FPoolLock := TCriticalSection.Create;
  FPool := TStack<THTTPClient>.Create;
  FGlobalCancel := TTgCancellationSource.New;
  FLimiter := TTgRateLimiter.Create(FSettings.GlobalRatePerSec, FSettings.PerChatIntervalMs);
end;

destructor TTgHttpTransport.Destroy;
begin
  if Assigned(FPool) then
    while FPool.Count > 0 do
      FPool.Pop.Free;
  FreeAndNil(FPool);
  FreeAndNil(FPoolLock);
  FGlobalCancel := nil;
  FreeAndNil(FLimiter);
  inherited Destroy;
end;

function TTgHttpTransport.CreateClient: THTTPClient;
begin
  Result := THTTPClient.Create;
  try
    if FSettings.ConnectionTimeoutMs > 0 then
      Result.ConnectionTimeout := FSettings.ConnectionTimeoutMs;
    ApplyResponseTimeout(Result, FSettings.ResponseTimeoutMs);
    if FSettings.UserAgent <> '' then
      Result.UserAgent := FSettings.UserAgent;
    Result.Accept := 'application/json';
    if FSettings.Proxy.IsEnabled then
      Result.ProxySettings := FSettings.Proxy.ToRtlSettings;
  except
    Result.Free;
    raise;
  end;
end;

function TTgHttpTransport.AcquireClient: THTTPClient;
begin
  Result := nil;
  FPoolLock.Enter;
  try
    if FPool.Count > 0 then
      Result := FPool.Pop;
  finally
    FPoolLock.Leave;
  end;
  if not Assigned(Result) then
    Result := CreateClient;
end;

procedure TTgHttpTransport.ReleaseClient(AClient: THTTPClient; ADiscard: Boolean);
begin
  if not Assigned(AClient) then
    Exit;
  if not ADiscard then
  begin
    FPoolLock.Enter;
    try
      if FPool.Count < TgMaxIdleClients then
      begin
        FPool.Push(AClient);
        AClient := nil;
      end;
    finally
      FPoolLock.Leave;
    end;
  end;
  AClient.Free;
end;

function TTgHttpTransport.MaskToken(const AText: string): string;
const
  CMask = '***';
var
  LEncoded: string;
begin
  Result := AText;
  if FSettings.Token = '' then
    Exit;
  Result := StringReplace(Result, FSettings.Token, CMask, [rfReplaceAll]);
  // В URL токен может оказаться закодированным (':' -> '%3A', регистр hex — любой).
  LEncoded := TNetEncoding.URL.Encode(FSettings.Token);
  if LEncoded <> FSettings.Token then
    Result := StringReplace(Result, LEncoded, CMask, [rfReplaceAll, rfIgnoreCase]);
end;

function TTgHttpTransport.NetworkErrorFrom(const AMethod: string;
  AError: Exception): ETgNetworkError;
begin
  Result := ETgNetworkError.Create(
    WithProxyInfo(TgTextFmt(TTgText.NetworkError, [AMethod, MaskToken(AError.Message)])),
    0, AMethod);
end;

function TTgHttpTransport.WithProxyInfo(const AMessage: string): string;
var
  LAddress: string;
begin
  if not FSettings.Proxy.IsEnabled then
    Exit(AMessage);
  // Неверный адрес прокси иначе неотличим от недоступного сервера Bot API.
  LAddress := FSettings.Proxy.Host;
  if FSettings.Proxy.Port > 0 then
    LAddress := LAddress + ':' + IntToStr(FSettings.Proxy.Port);
  Result := TgTextFmt(TTgText.ViaProxy, [AMessage, LAddress]);
end;

function TTgHttpTransport.MethodUrl(const AMethod: string): string;
begin
  Result := FSettings.ApiUrl + '/bot' + FSettings.Token + '/' + AMethod;
end;

function TTgHttpTransport.ResponseTimeoutFor(const AMethod: string;
  AParams: TTgParams): Integer;
const
  CMaxPollSec = 86400;
var
  LPollSec: Integer;
begin
  // ResponseTimeoutMs <= 0 — значение RTL по умолчанию (см. ApplyResponseTimeout).
  Result := FSettings.ResponseTimeoutMs;
  if Result <= 0 then
    Result := TURLClient.DefaultResponseTimeout;
  // Long polling: сервер держит соединение до timeout секунд.
  if Assigned(AParams) and SameText(AMethod, 'getUpdates') then
  begin
    LPollSec := TTgJson.GetInt(AParams.Json, 'timeout', 0);
    if (LPollSec > 0) and (LPollSec <= CMaxPollSec) then
      Result := Max(Result, (LPollSec + TgLongPollReserveSec) * 1000);
  end;
end;

function TTgHttpTransport.ChatKeyFor(const AMethod: string;
  AParams: TTgParams): string;
var
  LMethod: string;
begin
  Result := '';
  if not Assigned(AParams) then
    Exit;
  LMethod := LowerCase(AMethod);
  // sendChatAction не создаёт сообщений — к нему лимит на чат не применяется.
  if LMethod = 'sendchataction' then
    Exit;
  // Лимит на чат применяется к методам, отправляющим сообщения.
  if (Copy(LMethod, 1, 4) = 'send') or (Copy(LMethod, 1, 7) = 'forward') or
    (Copy(LMethod, 1, 4) = 'copy') then
    Result := AParams.GetText('chat_id');
end;

procedure TTgHttpTransport.FillMultipart(AForm: TMultipartFormData;
  AParams: TTgParams; AOwnedStreams: TObjectList<TStream>);
var
  I: Integer;
  LPair: TJSONPair;
  LFile: TTgParamFile;
  LStream: TStream;
  LFileName: string;
begin
  for I := 0 to AParams.Json.Count - 1 do
  begin
    LPair := AParams.Json.Pairs[I];
    AForm.AddField(LPair.JsonString.Value, TTgJson.ToFormText(LPair.JsonValue));
  end;
  for I := 0 to AParams.FileCount - 1 do
  begin
    LFile := AParams.Files[I];
    LFileName := SanitizeFormFileName(LFile.InputFile.FileName);
    case LFile.InputFile.Kind of
      TTgInputFileKind.UploadFile:
        begin
          // Файл открывается при каждой попытке; поток живёт в AOwnedStreams
          // до окончания отправки и освобождается вызывающим.
          LStream := TFileStream.Create(LFile.InputFile.Value, fmOpenRead or fmShareDenyWrite);
          try
            AOwnedStreams.Add(LStream);
          except
            LStream.Free;
            raise;
          end;
          AddFormStream(AForm, LFile.Name, LStream, LFileName, LFile.InputFile.ContentType);
        end;
      TTgInputFileKind.UploadBytes:
        AForm.AddBytes(LFile.Name, LFile.InputFile.Bytes, LFileName,
          LFile.InputFile.ContentType);
      TTgInputFileKind.UploadStream:
        // Поток пользователя отправляется целиком с позиции 0 (в т.ч. при повторе после 429).
        AddFormStream(AForm, LFile.Name, LFile.InputFile.Stream, LFileName,
          LFile.InputFile.ContentType);
    else
      AForm.AddField(LFile.Name, LFile.InputFile.ToParamValue);
    end;
  end;
end;

function TTgHttpTransport.SendRequest(const AMethod: string;
  AParams: TTgParams): TTgHttpResponse;
var
  LToken: ITgCancellation;
  LClient: THTTPClient;
  LDiscard: Boolean;
  LRequest: IHTTPRequest;
  LResponse: IHTTPResponse;
  LHeaders: TNetHeaders;
  LForm: TMultipartFormData;
  LFormStreams: TObjectList<TStream>;
  LBody: TBytesStream;
  LJson: string;
begin
  Result := Default(TTgHttpResponse);
  // Токен операции — окружающий: ExecuteEx устанавливает его на время вызова.
  LToken := TTgCancelScope.Current;
  LForm := nil;
  LFormStreams := nil;
  LBody := nil;
  try
    // Тело готовится до сетевой части: ошибки открытия файлов не считаются сетевыми.
    if Assigned(AParams) and AParams.HasFiles then
    begin
      LFormStreams := TObjectList<TStream>.Create(True);
      LForm := TMultipartFormData.Create;
      FillMultipart(LForm, AParams, LFormStreams);
    end
    else
    begin
      if Assigned(AParams) then
        LJson := AParams.ToJsonText
      else
        LJson := '{}';
      LBody := TBytesStream.Create(TEncoding.UTF8.GetBytes(LJson));
    end;
    LDiscard := True;
    LClient := AcquireClient;
    try
      ApplyResponseTimeout(LClient, ResponseTimeoutFor(AMethod, AParams));
      try
        // Как THTTPClient.Post, но через GetRequest + Execute — ради отмены запроса.
        LRequest := LClient.GetRequest(sHTTPMethodPost, MethodUrl(AMethod));
        if Assigned(LForm) then
        begin
          LRequest.SourceStream := LForm.Stream;
          LRequest.SourceStream.Position := 0;
          LRequest.SetHeaderValue(sContentType, LForm.MimeTypeHeader);
          LHeaders := nil;
        end
        else
        begin
          LRequest.SourceStream := LBody;
          LHeaders := [TNetHeader.Create(sContentType, 'application/json; charset=utf-8')];
        end;
        LResponse := ExecuteRequest(LClient, LRequest, nil, LHeaders, LToken);
        Result.StatusCode := LResponse.StatusCode;
        // Тело — байтами: разбор UTF-8 выполняет Execute, без EEncodingError здесь.
        Result.Body := ReadAllBytes(LResponse.ContentStream);
        LDiscard := False;
      except
        on E: ETgError do
          raise;
        on E: Exception do
          raise FailureFrom(AMethod, E, LToken);
      end;
    finally
      LResponse := nil;
      LRequest := nil;
      // После сетевой ошибки или отмены клиент не возвращается в пул.
      ReleaseClient(LClient, LDiscard);
    end;
  finally
    // Форма может читать потоки файлов при отправке — освобождаем их после неё.
    LForm.Free;
    LFormStreams.Free;
    LBody.Free;
  end;
end;

function TTgHttpTransport.ExecuteRequest(AClient: THTTPClient;
  const ARequest: IHTTPRequest; AContent: TStream; const AHeaders: TNetHeaders;
  const AToken: ITgCancellation): IHTTPResponse;
var
  LCanceller: ITgRequestCanceller;
  LRegistration: IInterface;
begin
  if not Assigned(AToken) then
    Exit(AClient.Execute(ARequest, AContent, AHeaders));
  // Все платформы: приём и передача данных прерываются флагом AAbort.
  ARequest.ReceiveDataCallback := NewReceiveAbortCallback(AToken);
  ARequest.SendDataCallback := NewSendAbortCallback(AToken);
  LCanceller := nil;
  LRegistration := nil;
  try
{$IF defined(MSWINDOWS) or defined(MACOS)}
    // Windows/macOS: Cancel из другого потока закрывает запрос и прерывает
    // ожидание ответа. На Linux (curl_easy_cleanup из чужого потока) это
    // небезопасно, на Android — не прерывает ожидание.
    LCanceller := TTgRequestCanceller.Create(ARequest);
    LRegistration := AToken.Register(NewRequestCancelCallback(LCanceller));
{$ENDIF}
    // Проверка после подписки и до Execute: Execute сбрасывает отмену запроса.
    AToken.ThrowIfCancelled;
    Result := AClient.Execute(ARequest, AContent, AHeaders);
  finally
    // После Detach колбэк токена запрос уже не тронет.
    if Assigned(LCanceller) then
      LCanceller.Detach;
    LRegistration := nil;
  end;
  // Отменённый запрос RTL завершает без исключения (с неполным ответом).
  if AToken.IsCancelled or ARequest.IsCancelled then
    raise ETgCancelledError.Create(TgText(TTgText.Cancelled));
end;

function TTgHttpTransport.FailureFrom(const AMethod: string; AError: Exception;
  const AToken: ITgCancellation): Exception;
begin
  // Отмена на уровне ОС проявляется ошибкой RTL — это не сетевая ошибка.
  if Assigned(AToken) and AToken.IsCancelled then
    Result := ETgCancelledError.Create(TgText(TTgText.Cancelled))
  else
    Result := NetworkErrorFrom(AMethod, AError);
end;

function TTgHttpTransport.GlobalCancelSource: ITgCancellationSource;
begin
  FPoolLock.Enter;
  try
    Result := FGlobalCancel;
  finally
    FPoolLock.Leave;
  end;
end;

function TTgHttpTransport.GlobalCancel: ITgCancellation;
begin
  Result := GlobalCancelSource;
end;

function TTgHttpTransport.GetSettings: TTgHttpSettings;
begin
  Result := FSettings;
end;

function TTgHttpTransport.WaitTokenFor(const ACancel: ITgCancellation): ITgCancellation;
begin
  Result := TTgCancellationSource.Linked(ACancel, GlobalCancel);
end;

procedure TTgHttpTransport.WaitInterruptible(AMs: Integer; const AToken: ITgCancellation);
begin
  if AMs <= 0 then
    AToken.ThrowIfCancelled
  else if AToken.WaitFor(Cardinal(AMs)) then
    raise ETgCancelledError.Create(TgText(TTgText.Cancelled));
end;

function TTgHttpTransport.Execute(const AMethod: string;
  AParams: TTgParams): TJSONValue;
begin
  Result := ExecuteEx(AMethod, AParams, TTgCancelScope.Current);
end;

function TTgHttpTransport.ExecuteEx(const AMethod: string; AParams: TTgParams;
  const ACancel: ITgCancellation): TJSONValue;
var
  LWaitToken: ITgCancellation;
  LScope: TTgCancelScope;
  LAttempt: Integer;
  LChatKey: string;
  LResponse: TTgHttpResponse;
  LRoot, LParameters: TJSONObject;
  LResult: TJSONValue;
  LErrorCode, LRetryAfter: Integer;
  LDescription: string;
  LMigrateTo: Int64;
begin
  // Ожидания прерываются и токеном операции, и глобальной отменой (Cancel).
  LWaitToken := WaitTokenFor(ACancel);
  LChatKey := ChatKeyFor(AMethod, AParams);
  LAttempt := 0;
  while True do
  begin
    LWaitToken.ThrowIfCancelled;
    WaitInterruptible(FLimiter.Reserve(LChatKey), LWaitToken);
    // SendRequest (в т.ч. переопределённый) получает токен операции как окружающий.
    LScope := TTgCancelScope.Enter(ACancel);
    try
      LResponse := SendRequest(AMethod, AParams);
    finally
      LScope.Leave;
    end;
    // Пустое тело, не JSON или некорректный UTF-8 — nil (без исключения разбора).
    LRoot := TTgJson.ParseObjectUtf8(LResponse.Body);
    if not Assigned(LRoot) then
      raise ETgNetworkError.Create(
        WithProxyInfo(TgTextFmt(TTgText.InvalidResponse, [AMethod, LResponse.StatusCode])),
        LResponse.StatusCode, AMethod);
    try
      if TTgJson.GetBool(LRoot, 'ok') then
      begin
        LResult := TTgJson.GetValue(LRoot, 'result');
        if Assigned(LResult) then
          Result := LResult.Clone as TJSONValue
        else
          Result := TJSONNull.Create;
        Exit;
      end;
      LErrorCode := TTgJson.GetInt(LRoot, 'error_code', LResponse.StatusCode);
      LDescription := MaskToken(TTgJson.GetStr(LRoot, 'description'));
      LParameters := TTgJson.GetObj(LRoot, 'parameters');
      LRetryAfter := TTgJson.GetInt(LParameters, 'retry_after');
      LMigrateTo := TTgJson.GetInt64(LParameters, 'migrate_to_chat_id');
    finally
      LRoot.Free;
    end;
    if (LErrorCode = 429) and FSettings.AutoRetry429 and
      (LAttempt < FSettings.MaxRetries) and (LRetryAfter <= FSettings.MaxRetryAfterSec) then
    begin
      Inc(LAttempt);
      WaitInterruptible(Max(LRetryAfter, 1) * 1000, LWaitToken);
      Continue;
    end;
    if LErrorCode = 409 then
      raise ETgConflictError.Create(AMethod, LErrorCode, LDescription, LRetryAfter, LMigrateTo);
    raise ETgApiError.Create(AMethod, LErrorCode, LDescription, LRetryAfter, LMigrateTo);
  end;
end;

procedure TTgHttpTransport.DownloadFile(const AFilePath: string; ADest: TStream);
begin
  DownloadFileEx(AFilePath, ADest, TTgCancelScope.Current);
end;

procedure TTgHttpTransport.DownloadFileEx(const AFilePath: string; ADest: TStream;
  const ACancel: ITgCancellation);
const
  // Имя операции в сообщениях об ошибках (это не метод Bot API).
  CMethod = 'downloadFile';
var
  LWaitToken: ITgCancellation;
  LClient: THTTPClient;
  LDiscard: Boolean;
  LRequest: IHTTPRequest;
  LResponse: IHTTPResponse;
  LSource: TFileStream;
begin
  if AFilePath = '' then
    raise ETgError.Create(TgText(TTgText.FilePathEmpty));
  // UNC и выход за каталог ('..') недопустимы ни для диска, ни для URL.
  if IsUncPath(AFilePath) or HasParentSegment(AFilePath) then
    raise ETgError.Create(TgTextFmt(TTgText.FilePathInvalid, [AFilePath]));
  LWaitToken := WaitTokenFor(ACancel);
  LWaitToken.ThrowIfCancelled;
  // Local Bot API server (--local) возвращает абсолютный путь на своём диске:
  // только при явном LocalMode читаем его напрямую (бот и сервер на одной машине).
  if FSettings.LocalMode and IsAbsoluteLocalPath(AFilePath) and FileExists(AFilePath) then
  begin
    LSource := TFileStream.Create(AFilePath, fmOpenRead or fmShareDenyWrite);
    try
      ADest.CopyFrom(LSource, LSource.Size);
    finally
      LSource.Free;
    end;
    Exit;
  end;
  WaitInterruptible(FLimiter.Reserve(''), LWaitToken);
  LDiscard := True;
  LClient := AcquireClient;
  try
    ApplyResponseTimeout(LClient, FSettings.ResponseTimeoutMs);
    try
      LRequest := LClient.GetRequest(sHTTPMethodGet, FSettings.ApiUrl + '/file/bot' +
        FSettings.Token + '/' + AFilePath);
      LResponse := ExecuteRequest(LClient, LRequest, ADest, nil, ACancel);
      LDiscard := False;
    except
      on E: ETgError do
        raise;
      on E: Exception do
        raise FailureFrom(CMethod, E, ACancel);
    end;
    if LResponse.StatusCode <> 200 then
      raise ETgNetworkError.Create(
        WithProxyInfo(TgTextFmt(TTgText.DownloadFailed, [LResponse.StatusCode])),
        LResponse.StatusCode, CMethod);
  finally
    LResponse := nil;
    LRequest := nil;
    ReleaseClient(LClient, LDiscard);
  end;
end;

procedure TTgHttpTransport.Cancel;
begin
  // Источник одноразовый: отменяем текущий, ResetCancel заменит его новым.
  // Отмена — вне FPoolLock: колбэки подписчиков не выполняются под блокировкой.
  GlobalCancelSource.Cancel;
end;

procedure TTgHttpTransport.ResetCancel;
begin
  FPoolLock.Enter;
  try
    if FGlobalCancel.IsCancelled then
      FGlobalCancel := TTgCancellationSource.New;
  finally
    FPoolLock.Leave;
  end;
end;

function TTgHttpTransport.IsCancelled: Boolean;
begin
  Result := GlobalCancel.IsCancelled;
end;

end.
