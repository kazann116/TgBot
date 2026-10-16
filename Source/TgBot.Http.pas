unit TgBot.Http;

{
  TgBot — HTTP-транспорт Bot API на System.Net.HttpClient.

  - ITgTransport — абстракция транспорта (подменяется в тестах);
  - ITgCancellableTransport — транспорт с токеном отмены на операцию;
    оба контракта и записи настроек объявлены в TgBot.Intf (для своей
    реализации транспорта достаточно его), здесь — псевдонимы;
  - TTgHttpTransport — реализация на THTTPClient: наследник
    TTgTransportBase (TgBot.Transport — разбор ответа Bot API, автоповтор
    429, лимитёр, прерываемые ожидания, подготовка запросов, ошибки);
    здесь — только HTTP: POST JSON / multipart, GET для файлов, пул
    THTTPClient (THTTPClient не потокобезопасен — каждый запрос берёт
    клиент из пула в монопольное пользование), прерывание идущего запроса;
  - псевдонимы перенесённых в TgBot.Transport типов (TTgRateLimiter,
    TgLongPollReserveSec) — для совместимости.

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
  System.Net.URLClient,
  System.Net.HttpClient,
  System.Net.Mime,
  TgBot.Base,
  TgBot.Intf,
  TgBot.Transport;

const
  /// <summary>Адрес облачного Bot API по умолчанию (TgBot.Intf).</summary>
  TgDefaultApiUrl = TgBot.Intf.TgDefaultApiUrl;
  /// <summary>Таймаут соединения по умолчанию, мс (TgBot.Intf).</summary>
  TgDefaultConnectionTimeoutMs = TgBot.Intf.TgDefaultConnectionTimeoutMs;
  /// <summary>Таймаут ответа по умолчанию, мс (TgBot.Intf).</summary>
  TgDefaultResponseTimeoutMs = TgBot.Intf.TgDefaultResponseTimeoutMs;
  /// <summary>Запас к timeout getUpdates при расчёте таймаута ответа, с (TgBot.Transport).</summary>
  TgLongPollReserveSec = TgBot.Transport.TgLongPollReserveSec;
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
  ///   System.Net.URLClient. Действует там, где подключён TgBot.Http; в
  ///   фасаде TgBot — собственный помощник с тем же методом (в области
  ///   видимости действует один помощник на тип, псевдоним помощника его
  ///   не подключает). Оба вызывают TgProxyToRtlSettings.
  /// </summary>
  TTgProxySettingsHelper = record helper for TTgProxySettings
    /// <summary>
    ///   Настройки прокси для THTTPClient: Normalized, схема всегда пустая
    ///   (единственный вариант HTTP-прокси, корректный на всех платформах).
    /// </summary>
    function ToRtlSettings: TProxySettings;
  end;

  /// <summary>Лимитёр запросов (описание — TgBot.Transport.TTgRateLimiter).</summary>
  TTgRateLimiter = TgBot.Transport.TTgRateLimiter;

  /// <summary>
  ///   Служебный: транспорт с настройками TTgHttpSettings (описание —
  ///   TgBot.Intf.ITgHttpSettingsProvider). В прикладном коде не нужен.
  /// </summary>
  ITgHttpSettingsProvider = TgBot.Intf.ITgHttpSettingsProvider;

  /// <summary>
  ///   Транспорт на System.Net.HttpClient. Протокол Bot API, повторы,
  ///   лимиты, отмена ожиданий и ошибки — TTgTransportBase (TgBot.Transport);
  ///   здесь — HTTP-запросы через пул THTTPClient. Настройки неизменяемы
  ///   после создания.
  /// </summary>
  TTgHttpTransport = class(TTgTransportBase)
  private
    // Защищает пул клиентов.
    FPoolLock: TCriticalSection;
    FPool: TStack<THTTPClient>;
    function CreateClient: THTTPClient;
    function AcquireClient: THTTPClient;
    procedure ReleaseClient(AClient: THTTPClient; ADiscard: Boolean);
    /// <summary>
    ///   Выполняет подготовленный запрос с отменой по AToken (nil — без отмены).
    ///   Отмена до или во время выполнения — ETgCancelledError.
    /// </summary>
    function ExecuteRequest(AClient: THTTPClient; const ARequest: IHTTPRequest;
      AContent: TStream; const AHeaders: TNetHeaders;
      const AToken: ITgCancellation): IHTTPResponse;
  protected
    /// <summary>Таймаут ответа RTL по умолчанию (TURLClient.DefaultResponseTimeout).</summary>
    function DefaultResponseTimeoutMs: Integer; override;
    /// <summary>POST через клиент из пула; отмена прерывает идущий запрос.</summary>
    function Post(const ARequest: TTgPostRequest): TTgHttpResponse; override;
    /// <summary>GET файла через клиент из пула; отмена прерывает идущий запрос.</summary>
    function Download(const ARequest: TTgDownloadRequest; ADest: TStream): Integer; override;
  public
    /// <summary>
    ///   Создаёт транспорт; пустой токен или неверные настройки прокси
    ///   (TTgProxySettings.Normalized) — ETgError.
    /// </summary>
    constructor Create(const ASettings: TTgHttpSettings);
    destructor Destroy; override;
  end;

/// <summary>
///   Настройки прокси AProxy для THTTPClient (реализация
///   TTgProxySettings.ToRtlSettings): Normalized, схема всегда пустая.
///   Ошибка настройки — ETgError (см. TTgProxySettings.Normalized).
/// </summary>
function TgProxyToRtlSettings(const AProxy: TTgProxySettings): TProxySettings;

implementation

uses
  System.NetConsts;

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
begin
  Result := TgProxyToRtlSettings(Self);
end;

function TgProxyToRtlSettings(const AProxy: TTgProxySettings): TProxySettings;
var
  LProxy: TTgProxySettings;
begin
  LProxy := AProxy.Normalized;
  // Схема RTL — не схема прокси: на Windows это протокол связи с прокси
  // ('https://' — WinHTTP начинает с прокси TLS, обычный HTTP-прокси
  // отвечает ошибкой 12029; HTTPS-прокси не поддерживаем), на macOS — фильтр
  // целевых URL ('http' пустил бы https:// мимо прокси), curl её не
  // использует. Пустая схема — HTTP-прокси для всех запросов, везде.
  Result := TProxySettings.Create(LProxy.Host, LProxy.Port, LProxy.UserName,
    LProxy.Password, '');
end;

{ TTgHttpTransport }

constructor TTgHttpTransport.Create(const ASettings: TTgHttpSettings);
begin
  // Проверки токена и прокси, адрес API — в TTgTransportBase.
  inherited Create(ASettings);
  FPoolLock := TCriticalSection.Create;
  FPool := TStack<THTTPClient>.Create;
end;

destructor TTgHttpTransport.Destroy;
begin
  if Assigned(FPool) then
    while FPool.Count > 0 do
      FPool.Pop.Free;
  FreeAndNil(FPool);
  FreeAndNil(FPoolLock);
  inherited Destroy;
end;

function TTgHttpTransport.CreateClient: THTTPClient;
begin
  Result := THTTPClient.Create;
  try
    if Settings.ConnectionTimeoutMs > 0 then
      Result.ConnectionTimeout := Settings.ConnectionTimeoutMs;
    ApplyResponseTimeout(Result, Settings.ResponseTimeoutMs);
    if Settings.UserAgent <> '' then
      Result.UserAgent := Settings.UserAgent;
    Result.Accept := 'application/json';
    if Settings.Proxy.IsEnabled then
      Result.ProxySettings := Settings.Proxy.ToRtlSettings;
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

function TTgHttpTransport.DefaultResponseTimeoutMs: Integer;
begin
  // Как у нового THTTPClient (см. ApplyResponseTimeout).
  Result := TURLClient.DefaultResponseTimeout;
end;

function TTgHttpTransport.Post(const ARequest: TTgPostRequest): TTgHttpResponse;
var
  LClient: THTTPClient;
  LDiscard: Boolean;
  LRequest: IHTTPRequest;
  LResponse: IHTTPResponse;
  LHeaders: TNetHeaders;
  LForm: TMultipartFormData;
  LBody: TBytesStream;
  LPart: TTgFormPart;
begin
  // Сетевые ошибки и отмену в ETgError превращает база (SendRequest).
  Result := Default(TTgHttpResponse);
  LForm := nil;
  LBody := nil;
  try
    if ARequest.IsMultipart then
    begin
      LForm := TMultipartFormData.Create;
      for LPart in ARequest.Parts do
        if LPart.IsFile then
          AddFormStream(LForm, LPart.Name, LPart.Stream, LPart.FileName, LPart.ContentType)
        else
          LForm.AddField(LPart.Name, LPart.Value);
    end
    else
      LBody := TBytesStream.Create(ARequest.Body);
    LDiscard := True;
    LClient := AcquireClient;
    try
      ApplyResponseTimeout(LClient, ARequest.ResponseTimeoutMs);
      // Как THTTPClient.Post, но через GetRequest + Execute — ради отмены запроса.
      LRequest := LClient.GetRequest(sHTTPMethodPost, ARequest.Url);
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
        LHeaders := [TNetHeader.Create(sContentType, ARequest.ContentType)];
      end;
      LResponse := ExecuteRequest(LClient, LRequest, nil, LHeaders, ARequest.Cancel);
      Result.StatusCode := LResponse.StatusCode;
      // Тело — байтами: разбор UTF-8 выполняет база, без EEncodingError здесь.
      Result.Body := ReadAllBytes(LResponse.ContentStream);
      LDiscard := False;
    finally
      LResponse := nil;
      LRequest := nil;
      // После сетевой ошибки или отмены клиент не возвращается в пул.
      ReleaseClient(LClient, LDiscard);
    end;
  finally
    // Форма может читать потоки файлов при отправке — освобождается после неё
    // (потоки частей освобождает база после возврата).
    LForm.Free;
    LBody.Free;
  end;
end;

function TTgHttpTransport.Download(const ARequest: TTgDownloadRequest;
  ADest: TStream): Integer;
var
  LClient: THTTPClient;
  LDiscard: Boolean;
  LRequest: IHTTPRequest;
  LResponse: IHTTPResponse;
begin
  // Сетевые ошибки, отмену и статус, отличный от 200, обрабатывает база.
  LDiscard := True;
  LClient := AcquireClient;
  try
    ApplyResponseTimeout(LClient, ARequest.ResponseTimeoutMs);
    LRequest := LClient.GetRequest(sHTTPMethodGet, ARequest.Url);
    LResponse := ExecuteRequest(LClient, LRequest, ADest, nil, ARequest.Cancel);
    Result := LResponse.StatusCode;
    LDiscard := False;
  finally
    LResponse := nil;
    LRequest := nil;
    ReleaseClient(LClient, LDiscard);
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

end.
