unit TgBot.Http;

{
  TgBot — HTTP-транспорт Bot API на System.Net.HttpClient.

  - ITgTransport — абстракция транспорта (подменяется в тестах);
  - ITgCancellableTransport — транспорт с токеном отмены на операцию;
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
  TgBot.Json;

const
  /// <summary>Адрес облачного Bot API по умолчанию.</summary>
  TgDefaultApiUrl = 'https://api.telegram.org';
  /// <summary>Таймаут соединения по умолчанию, мс.</summary>
  TgDefaultConnectionTimeoutMs = 15000;
  /// <summary>Таймаут ответа по умолчанию, мс (для long polling увеличивается автоматически).</summary>
  TgDefaultResponseTimeoutMs = 60000;
  /// <summary>Запас к timeout getUpdates при расчёте таймаута ответа, с.</summary>
  TgLongPollReserveSec = 15;
  /// <summary>Максимум попыток повтора при 429 по умолчанию.</summary>
  TgDefaultMaxRetries = 3;
  /// <summary>Максимальное ожидание retry_after по умолчанию, с (больше — ошибка сразу).</summary>
  TgDefaultMaxRetryAfterSec = 60;
  /// <summary>Глобальный лимит запросов в секунду на бота по умолчанию.</summary>
  TgDefaultGlobalRatePerSec = 30;
  /// <summary>Минимальный интервал между сообщениями в один чат по умолчанию, мс.</summary>
  TgDefaultPerChatIntervalMs = 1000;
  /// <summary>Максимум простаивающих HTTP-клиентов в пуле.</summary>
  TgMaxIdleClients = 8;

type
  /// <summary>Настройки HTTP(S)-прокси бота.</summary>
  TTgProxySettings = record
    /// <summary>Хост прокси; пусто — прокси не используется.</summary>
    Host: string;
    /// <summary>Порт прокси.</summary>
    Port: Integer;
    /// <summary>Имя пользователя (необязательно).</summary>
    UserName: string;
    /// <summary>Пароль (необязательно).</summary>
    Password: string;
    /// <summary>Схема прокси ('http' или 'https'); пусто — по умолчанию RTL.</summary>
    Scheme: string;
    /// <summary>Создаёт настройки прокси.</summary>
    class function Create(const AHost: string; APort: Integer;
      const AUserName: string = ''; const APassword: string = '';
      const AScheme: string = ''): TTgProxySettings; static;
    /// <summary>Прокси задан.</summary>
    function IsEnabled: Boolean;
  end;

  /// <summary>
  ///   Настройки транспорта. Создавайте через TTgHttpSettings.Create(Token) —
  ///   он заполняет значения по умолчанию, затем меняйте нужные поля.
  /// </summary>
  TTgHttpSettings = record
    /// <summary>Токен бота.</summary>
    Token: string;
    /// <summary>Адрес сервера Bot API (облачный или Local Bot API server), без '/' в конце.</summary>
    ApiUrl: string;
    /// <summary>Прокси бота.</summary>
    Proxy: TTgProxySettings;
    /// <summary>Таймаут соединения, мс.</summary>
    ConnectionTimeoutMs: Integer;
    /// <summary>Таймаут ответа, мс.</summary>
    ResponseTimeoutMs: Integer;
    /// <summary>Значение заголовка User-Agent.</summary>
    UserAgent: string;
    /// <summary>Автоматически повторять запрос при ошибке 429.</summary>
    AutoRetry429: Boolean;
    /// <summary>Максимум повторов при 429.</summary>
    MaxRetries: Integer;
    /// <summary>Если retry_after больше этого значения (с) — ошибка без ожидания.</summary>
    MaxRetryAfterSec: Integer;
    /// <summary>Глобальный лимит запросов в секунду; 0 — без ограничения.</summary>
    GlobalRatePerSec: Integer;
    /// <summary>Интервал между отправками в один чат, мс; 0 — без ограничения.</summary>
    PerChatIntervalMs: Integer;
    /// <summary>
    ///   Режим Local Bot API server (--local): DownloadFile читает абсолютный
    ///   file_path напрямую с локального диска. Включайте, только если бот
    ///   и сервер Bot API работают на одной машине. По умолчанию False.
    /// </summary>
    LocalMode: Boolean;
    /// <summary>Настройки по умолчанию для указанного токена.</summary>
    class function Create(const AToken: string): TTgHttpSettings; static;
  end;

  /// <summary>Сырой HTTP-ответ.</summary>
  TTgHttpResponse = record
    /// <summary>HTTP-статус.</summary>
    StatusCode: Integer;
    /// <summary>Тело ответа — исходные байты (ожидается JSON в UTF-8).</summary>
    Body: TBytes;
  end;

  /// <summary>
  ///   Транспорт Bot API. Реализации должны быть потокобезопасны.
  /// </summary>
  ITgTransport = interface
    ['{FCE9ECCD-6131-4258-B4BC-6C83CDDACBE8}']
    /// <summary>
    ///   Вызывает метод Bot API и возвращает поле result (объект принадлежит
    ///   вызывающему). AParams может быть nil.
    ///   Ошибки: ETgApiError, ETgNetworkError, ETgCancelledError.
    /// </summary>
    function Execute(const AMethod: string; AParams: TTgParams): TJSONValue;
    /// <summary>
    ///   Скачивает файл по file_path (из getFile) в поток ADest.
    ///   Пути UNC и с сегментом '..' отклоняются (ETgError).
    ///   При ошибке содержимое ADest не определено.
    /// </summary>
    procedure DownloadFile(const AFilePath: string; ADest: TStream);
    /// <summary>
    ///   УСТАРЕЛО: используйте токены отмены (ITgCancellableTransport,
    ///   TTgCancelScope). Глобально прерывает текущие и будущие ожидания
    ///   (лимитёр, retry_after) всех клиентов транспорта — они завершаются
    ///   ETgCancelledError. Уже идущий HTTP-запрос не прерывается.
    /// </summary>
    procedure Cancel;
    /// <summary>УСТАРЕЛО: снимает признак глобальной отмены (см. Cancel).</summary>
    procedure ResetCancel;
    /// <summary>УСТАРЕЛО: признак глобальной отмены установлен (см. Cancel).</summary>
    function IsCancelled: Boolean;
  end;

  /// <summary>
  ///   Транспорт с отменой отдельной операции. Execute/DownloadFile такого
  ///   транспорта используют окружающий токен (TTgCancelScope.Current).
  /// </summary>
  ITgCancellableTransport = interface(ITgTransport)
    ['{6FDF0494-1D1F-4832-B086-3B1E6043EE64}']
    /// <summary>
    ///   Как Execute, но с токеном отмены ACancel (nil — без отмены):
    ///   отмена прерывает ожидания и, где поддерживается, идущий HTTP-запрос
    ///   (ETgCancelledError).
    /// </summary>
    function ExecuteEx(const AMethod: string; AParams: TTgParams;
      const ACancel: ITgCancellation): TJSONValue;
    /// <summary>Как DownloadFile, но с токеном отмены ACancel (nil — без отмены).</summary>
    procedure DownloadFileEx(const AFilePath: string; ADest: TStream;
      const ACancel: ITgCancellation);
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
  ///   Служебный: транспорт с настройками TTgHttpSettings (реализует
  ///   TTgHttpTransport). Через него клиент получает настройки транспорта без
  ///   приведения к классу. В прикладном коде не нужен.
  /// </summary>
  ITgHttpSettingsProvider = interface
    ['{804B9679-6947-4414-8785-FE1C5499DF87}']
    /// <summary>Настройки транспорта (копия записи).</summary>
    function GetSettings: TTgHttpSettings;
  end;

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
    /// <summary>Создаёт транспорт; пустой токен — ETgError.</summary>
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
var
  LSelf: ITgRequestCanceller;
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
  LSelf := Self;
  StartRefire(LSelf);
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

{ TTgProxySettings }

class function TTgProxySettings.Create(const AHost: string; APort: Integer;
  const AUserName, APassword, AScheme: string): TTgProxySettings;
begin
  Result.Host := AHost;
  Result.Port := APort;
  Result.UserName := AUserName;
  Result.Password := APassword;
  Result.Scheme := AScheme;
end;

function TTgProxySettings.IsEnabled: Boolean;
begin
  Result := Host <> '';
end;

{ TTgHttpSettings }

class function TTgHttpSettings.Create(const AToken: string): TTgHttpSettings;
begin
  Result := Default(TTgHttpSettings);
  Result.Token := AToken;
  Result.ApiUrl := TgDefaultApiUrl;
  Result.ConnectionTimeoutMs := TgDefaultConnectionTimeoutMs;
  Result.ResponseTimeoutMs := TgDefaultResponseTimeoutMs;
  Result.UserAgent := TgBotUserAgent;
  Result.AutoRetry429 := True;
  Result.MaxRetries := TgDefaultMaxRetries;
  Result.MaxRetryAfterSec := TgDefaultMaxRetryAfterSec;
  Result.GlobalRatePerSec := TgDefaultGlobalRatePerSec;
  Result.PerChatIntervalMs := TgDefaultPerChatIntervalMs;
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
      Result.ProxySettings := TProxySettings.Create(FSettings.Proxy.Host,
        FSettings.Proxy.Port, FSettings.Proxy.UserName, FSettings.Proxy.Password,
        FSettings.Proxy.Scheme);
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
    TgTextFmt(TTgText.NetworkError, [AMethod, MaskToken(AError.Message)]), 0, AMethod);
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
        TgTextFmt(TTgText.InvalidResponse, [AMethod, LResponse.StatusCode]),
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
        TgTextFmt(TTgText.DownloadFailed, [LResponse.StatusCode]), LResponse.StatusCode,
        CMethod);
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
