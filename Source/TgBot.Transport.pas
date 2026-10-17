unit TgBot.Transport;

{
  TgBot — протокол Bot API без привязки к HTTP-библиотеке.

  TTgTransportBase — база транспорта: реализует ITgTransport,
  ITgCancellableTransport и ITgHttpSettingsProvider (TgBot.Intf) целиком,
  кроме самой передачи байтов:
  - разбор ответа Bot API (ok/result/error_code/description/parameters),
    ETgApiError и ETgConflictError (409);
  - автоповтор 429 по retry_after, лимитёр (TTgRateLimiter), прерываемые
    ожидания (токен операции и глобальная отмена Cancel/ResetCancel);
  - подготовка запроса: JSON-тело или части формы multipart (поля, файлы
    с диска, байты, потоки пользователя), таймаут ответа с учётом long
    polling (getUpdates);
  - скачивание файлов (DownloadFile): проверки пути, LocalMode;
  - ошибки: токен бота маскируется, к сетевым ошибкам добавляется адрес
    прокси, отмена — ETgCancelledError.

  Наследник реализует два метода на своём HTTP-клиенте: Post (один POST
  метода Bot API) и Download (GET файла). Реализация на
  System.Net.HttpClient — TTgHttpTransport (TgBot.Http). Модуль не
  использует System.Net.*: uses TgBot.Transport не тянет THTTPClient.

  Реестр транспорта по умолчанию: клиент, созданный по токену или
  настройкам (TTgApi.Create(AToken/ASettings)), получает транспорт от
  TgCreateDefaultTransport. Фабрику регистрирует модуль реализации
  (TgBot.Http — в initialization, его подключает фасад TgBot) или
  пользователь (TgRegisterDefaultTransport). Встроенная фабрика —
  запасная (TgRegisterFallbackTransport, низ стека): фабрика пользователя
  действует при любом порядке initialization. Без зарегистрированной
  фабрики ядро не зависит от HTTP-библиотеки.

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
  TgBot.Base,
  TgBot.Json,
  TgBot.Intf;

const
  /// <summary>Запас к timeout getUpdates при расчёте таймаута ответа, с.</summary>
  TgLongPollReserveSec = 15;

type
  /// <summary>
  ///   Часть формы multipart/form-data. Поле (IsFile = False) — Name и Value;
  ///   файл (IsFile = True) — Name, Stream, FileName (без '"' и управляющих
  ///   символов, не пустое) и ContentType (пусто — по расширению FileName).
  /// </summary>
  TTgFormPart = record
    /// <summary>Имя поля формы.</summary>
    Name: string;
    /// <summary>Значение поля (для IsFile = False).</summary>
    Value: string;
    /// <summary>
    ///   Содержимое файла (для IsFile = True), позиция 0. Поток принадлежит
    ///   базе транспорта или пользователю: наследник его не освобождает и
    ///   не хранит после возврата из Post.
    /// </summary>
    Stream: TStream;
    /// <summary>Имя файла для заголовка части.</summary>
    FileName: string;
    /// <summary>MIME-тип файла; пусто — определить по расширению FileName.</summary>
    ContentType: string;
    /// <summary>Часть — файл (Stream задан).</summary>
    function IsFile: Boolean;
  end;

  /// <summary>
  ///   POST-запрос метода Bot API, подготовленный базой транспорта. Тело —
  ///   либо Body (ContentType задан, IsMultipart = False), либо форма
  ///   multipart/form-data из Parts в указанном порядке (IsMultipart = True;
  ///   ContentType пуст: заголовок с границей формирует наследник).
  /// </summary>
  TTgPostRequest = record
    /// <summary>Метод Bot API (для сообщений; URL уже готов).</summary>
    Method: string;
    /// <summary>Полный URL запроса (содержит токен бота).</summary>
    Url: string;
    /// <summary>Таймаут ответа, мс (> 0; для getUpdates увеличен на время long polling).</summary>
    ResponseTimeoutMs: Integer;
    /// <summary>Токен отмены операции или nil.</summary>
    Cancel: ITgCancellation;
    /// <summary>Content-Type тела Body ('' для multipart).</summary>
    ContentType: string;
    /// <summary>Тело запроса (для IsMultipart = False).</summary>
    Body: TBytes;
    /// <summary>Части формы (для IsMultipart = True).</summary>
    Parts: TArray<TTgFormPart>;
    /// <summary>Тело — форма multipart/form-data из Parts.</summary>
    function IsMultipart: Boolean;
  end;

  /// <summary>GET-запрос файла (DownloadFile), подготовленный базой транспорта.</summary>
  TTgDownloadRequest = record
    /// <summary>Полный URL файла (содержит токен бота).</summary>
    Url: string;
    /// <summary>Таймаут ответа, мс (> 0).</summary>
    ResponseTimeoutMs: Integer;
    /// <summary>Токен отмены операции или nil.</summary>
    Cancel: ITgCancellation;
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
  ///   База транспорта Bot API: протокол, повторы, лимиты, отмена и ошибки
  ///   без HTTP-клиента. Настройки неизменяемы после создания.
  ///
  ///   Контракт наследника (Post, Download):
  ///   - вызываются из любых потоков одновременно — реализация
  ///     потокобезопасна (например, клиент на запрос или пул клиентов);
  ///   - исключения HTTP-клиента можно не ловить: база превращает любое
  ///     исключение, кроме ETgError, в ETgNetworkError (токен в тексте
  ///     маскируется, добавляется адрес прокси) или в ETgCancelledError,
  ///     если операция отменена;
  ///   - это касается любого исключения изнутри Post/Download, не только
  ///     сетевого: ошибки сборки тела формы, чтения потоков частей (в том
  ///     числе потоков пользователя — TTgInputFile.FromStream) и записи в
  ///     ADest тоже становятся ETgNetworkError (класс исходного исключения
  ///     теряется, его текст — в сообщении). Файлы с диска база открывает
  ///     до Post: ошибка открытия — исходное исключение (например,
  ///     EFOpenError), не ETgNetworkError;
  ///   - после возврата база сама проверяет ARequest.Cancel.IsCancelled
  ///     (отмена — ETgCancelledError), поэтому ответ отменённого запроса
  ///     можно вернуть как есть;
  ///   - прерывать идущий запрос по отмене — по желанию:
  ///     ARequest.Cancel.Register(...) (Cancel может быть nil); без этого
  ///     запрос завершается по таймауту ответа, ожидания базы прерываются
  ///     сразу;
  ///   - потоки частей формы (TTgFormPart.Stream) действительны только до
  ///     возврата из Post: не освобождать и не хранить;
  ///   - настройки соединения (прокси, таймаут соединения, UserAgent) —
  ///     в Settings; прокси уже проверен (TTgProxySettings.Normalized).
  /// </summary>
  TTgTransportBase = class(TInterfacedObject, ITgTransport, ITgCancellableTransport,
    ITgHttpSettingsProvider)
  private
    FSettings: TTgHttpSettings;
    // Защищает замену FGlobalCancel.
    FCancelLock: TCriticalSection;
    // Глобальная отмена (устаревшие Cancel/ResetCancel); ResetCancel заменяет источник.
    FGlobalCancel: ITgCancellationSource;
    FLimiter: TTgRateLimiter;
    /// <summary>Текущий источник глобальной отмены (под FCancelLock).</summary>
    function GlobalCancelSource: ITgCancellationSource;
    function GlobalCancel: ITgCancellation;
    /// <summary>
    ///   Части формы для AParams: поля, затем файлы. Файлы с диска и байты
    ///   открываются потоками в AOwnedStreams (освобождает вызывающий).
    /// </summary>
    function FormPartsFor(AParams: TTgParams;
      AOwnedStreams: TObjectList<TStream>): TArray<TTgFormPart>;
    { ITgHttpSettingsProvider }
    function GetSettings: TTgHttpSettings;
  protected
    /// <summary>
    ///   Скрывает токен в тексте (для сообщений об ошибках) — как есть
    ///   и в URL-кодированном виде.
    /// </summary>
    function MaskToken(const AText: string): string;
    /// <summary>
    ///   Текст сетевой ошибки с адресом прокси (host:port, без учётных данных),
    ///   если прокси задан; иначе AMessage без изменений.
    /// </summary>
    function WithProxyInfo(const AMessage: string): string;
    /// <summary>
    ///   Сетевая ошибка по исключению транспорта; токен в тексте маскируется.
    /// </summary>
    function NetworkErrorFrom(const AMethod: string; AError: Exception): ETgNetworkError;
    /// <summary>
    ///   Ошибка вместо исключения HTTP-клиента: ETgCancelledError при
    ///   отменённом AToken, иначе сетевая ошибка (NetworkErrorFrom).
    /// </summary>
    function FailureFrom(const AMethod: string; AError: Exception;
      const AToken: ITgCancellation): Exception;
    /// <summary>URL метода Bot API.</summary>
    function MethodUrl(const AMethod: string): string;
    /// <summary>URL файла для скачивания (AFilePath — file_path из getFile).</summary>
    function FileUrl(const AFilePath: string): string;
    /// <summary>
    ///   Таймаут ответа метода, мс: Settings.ResponseTimeoutMs
    ///   (<= 0 — DefaultResponseTimeoutMs), для getUpdates — не меньше
    ///   timeout + TgLongPollReserveSec.
    /// </summary>
    function ResponseTimeoutFor(const AMethod: string; AParams: TTgParams): Integer;
    /// <summary>Ключ чата для лимита на чат ('' — только глобальный лимит).</summary>
    function ChatKeyFor(const AMethod: string; AParams: TTgParams): string;
    /// <summary>Токен ожиданий: операция (ACancel) или глобальная отмена.</summary>
    function WaitTokenFor(const ACancel: ITgCancellation): ITgCancellation;
    /// <summary>Ожидание AMs мс, прерываемое AToken (ETgCancelledError).</summary>
    procedure WaitInterruptible(AMs: Integer; const AToken: ITgCancellation);
    /// <summary>
    ///   Таймаут ответа, если Settings.ResponseTimeoutMs <= 0, мс.
    ///   База — TgDefaultResponseTimeoutMs.
    /// </summary>
    function DefaultResponseTimeoutMs: Integer; virtual;
    /// <summary>
    ///   Отправляет один HTTP-запрос метода (без повторов и разбора).
    ///   Виртуальный — для подмены в тестах. По умолчанию готовит
    ///   TTgPostRequest и вызывает Post; сетевые ошибки — ETgNetworkError.
    ///   Токен отмены операции — окружающий (TTgCancelScope.Current): ExecuteEx
    ///   устанавливает его на время вызова; отмена — ETgCancelledError.
    /// </summary>
    function SendRequest(const AMethod: string; AParams: TTgParams): TTgHttpResponse; virtual;
    /// <summary>
    ///   Выполняет один POST-запрос и возвращает статус и тело ответа
    ///   (любой статус — не ошибка: тело разбирает база). Контракт — в
    ///   описании класса.
    /// </summary>
    function Post(const ARequest: TTgPostRequest): TTgHttpResponse; virtual; abstract;
    /// <summary>
    ///   Выполняет GET-запрос файла, пишет тело ответа в ADest и возвращает
    ///   HTTP-статус (не 200 — ошибка скачивания, её формирует база).
    ///   Контракт — в описании класса.
    /// </summary>
    function Download(const ARequest: TTgDownloadRequest; ADest: TStream): Integer; virtual; abstract;
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

  /// <summary>
  ///   Фабрика транспорта по умолчанию: создаёт транспорт по настройкам
  ///   (токен, ApiUrl, прокси, таймауты, лимиты). Неверные настройки —
  ///   исключение (обычно ETgError). Вызывается из любых потоков.
  /// </summary>
  TTgTransportFactory = reference to function(const ASettings: TTgHttpSettings): ITgTransport;

/// <summary>
///   Регистрирует фабрику транспорта по умолчанию (TgCreateDefaultTransport).
///   Действует последняя зарегистрированная; повторная регистрация уже
///   зарегистрированной ссылки делает её текущей. Фабрики сравниваются по
///   ссылке: для снятия храните её в переменной (имя функции при каждом
///   присваивании ссылке на функцию даёт новую ссылку). nil —
///   EArgumentNilException. Потокобезопасно.
///   Встроенный HTTP-транспорт (TgBot.Http) регистрируется запасным
///   (TgRegisterFallbackTransport — в самый низ стека), поэтому
///   зарегистрированная здесь фабрика становится текущей независимо от
///   порядка initialization модулей: и до, и после TgBot.Http. Регистрируйте
///   свою фабрику в initialization своего модуля, снимайте в finalization.
///   После finalization модуля TgBot.Transport вызов ничего не делает.
/// </summary>
procedure TgRegisterDefaultTransport(const AFactory: TTgTransportFactory);
/// <summary>
///   Служебная (для модулей реализации транспорта, например TgBot.Http):
///   регистрирует запасную фабрику — в самый низ стека, под всеми уже
///   зарегистрированными. Она становится текущей, только если других фабрик
///   нет или все они сняты, поэтому любая регистрация пользователя
///   (TgRegisterDefaultTransport) её перекрывает, в каком бы порядке ни шли
///   initialization. Уже зарегистрированная ссылка переносится вниз.
///   Снятие — TgUnregisterDefaultTransport. nil — EArgumentNilException.
///   Потокобезопасно; после finalization модуля TgBot.Transport ничего не
///   делает.
/// </summary>
procedure TgRegisterFallbackTransport(const AFactory: TTgTransportFactory);
/// <summary>
///   Снимает фабрику, зарегистрированную TgRegisterDefaultTransport (или
///   TgRegisterFallbackTransport) с той же ссылкой. Снята текущая —
///   текущей становится зарегистрированная перед ней (если есть); снята
///   не текущая — текущая не меняется, ссылка просто
///   не хранится (модуль пакета можно выгрузить). Незарегистрированная
///   ссылка или nil — ничего не происходит. Потокобезопасно.
/// </summary>
procedure TgUnregisterDefaultTransport(const AFactory: TTgTransportFactory);
/// <summary>
///   Текущая фабрика транспорта по умолчанию или nil, если не
///   зарегистрирована (или модуль TgBot.Transport уже завершён —
///   finalization). Вызывайте со скобками — LFactory :=
///   TgDefaultTransportFactory(): без них компилятор берёт саму функцию.
/// </summary>
function TgDefaultTransportFactory: TTgTransportFactory;
/// <summary>
///   Транспорт по умолчанию по настройкам — текущей фабрикой (её
///   исключения, например ошибки прокси, — без изменений). Фабрики нет —
///   ETgError «транспорт по умолчанию не зарегистрирован» (подключите
///   TgBot.Http или фасад TgBot либо передайте клиенту свой транспорт;
///   то же после finalization модуля TgBot.Transport); фабрика вернула
///   nil — ETgError «не задан транспорт».
/// </summary>
function TgCreateDefaultTransport(const ASettings: TTgHttpSettings): ITgTransport;

implementation

uses
  System.Math,
  System.NetEncoding,
  TgBot.Consts;

var
  // Реестр фабрик транспорта по умолчанию: текущая — последняя.
  // Создаётся в initialization, освобождается в finalization.
  GFactoryLock: TCriticalSection;
  GFactories: TArray<TTgTransportFactory>;

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

{ TTgFormPart }

function TTgFormPart.IsFile: Boolean;
begin
  Result := Assigned(Stream);
end;

{ TTgPostRequest }

function TTgPostRequest.IsMultipart: Boolean;
begin
  Result := Length(Parts) > 0;
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

{ TTgTransportBase }

constructor TTgTransportBase.Create(const ASettings: TTgHttpSettings);
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
  FCancelLock := TCriticalSection.Create;
  FGlobalCancel := TTgCancellationSource.New;
  FLimiter := TTgRateLimiter.Create(FSettings.GlobalRatePerSec, FSettings.PerChatIntervalMs);
end;

destructor TTgTransportBase.Destroy;
begin
  FreeAndNil(FCancelLock);
  FGlobalCancel := nil;
  FreeAndNil(FLimiter);
  inherited Destroy;
end;

function TTgTransportBase.MaskToken(const AText: string): string;
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

function TTgTransportBase.NetworkErrorFrom(const AMethod: string;
  AError: Exception): ETgNetworkError;
begin
  Result := ETgNetworkError.Create(
    WithProxyInfo(TgTextFmt(TTgText.NetworkError, [AMethod, MaskToken(AError.Message)])),
    0, AMethod);
end;

function TTgTransportBase.WithProxyInfo(const AMessage: string): string;
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

function TTgTransportBase.FailureFrom(const AMethod: string; AError: Exception;
  const AToken: ITgCancellation): Exception;
begin
  // Отмена на уровне ОС проявляется ошибкой RTL — это не сетевая ошибка.
  if Assigned(AToken) and AToken.IsCancelled then
    Result := ETgCancelledError.Create(TgText(TTgText.Cancelled))
  else
    Result := NetworkErrorFrom(AMethod, AError);
end;

function TTgTransportBase.MethodUrl(const AMethod: string): string;
begin
  Result := FSettings.ApiUrl + '/bot' + FSettings.Token + '/' + AMethod;
end;

function TTgTransportBase.FileUrl(const AFilePath: string): string;
begin
  Result := FSettings.ApiUrl + '/file/bot' + FSettings.Token + '/' + AFilePath;
end;

function TTgTransportBase.DefaultResponseTimeoutMs: Integer;
begin
  Result := TgDefaultResponseTimeoutMs;
end;

function TTgTransportBase.ResponseTimeoutFor(const AMethod: string;
  AParams: TTgParams): Integer;
const
  CMaxPollSec = 86400;
var
  LPollSec: Integer;
begin
  // ResponseTimeoutMs <= 0 — значение транспорта по умолчанию.
  Result := FSettings.ResponseTimeoutMs;
  if Result <= 0 then
    Result := DefaultResponseTimeoutMs;
  // Long polling: сервер держит соединение до timeout секунд.
  if Assigned(AParams) and SameText(AMethod, 'getUpdates') then
  begin
    LPollSec := TTgJson.GetInt(AParams.Json, 'timeout', 0);
    if (LPollSec > 0) and (LPollSec <= CMaxPollSec) then
      Result := Max(Result, (LPollSec + TgLongPollReserveSec) * 1000);
  end;
end;

function TTgTransportBase.ChatKeyFor(const AMethod: string;
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

function TTgTransportBase.FormPartsFor(AParams: TTgParams;
  AOwnedStreams: TObjectList<TStream>): TArray<TTgFormPart>;
var
  I, LFieldCount: Integer;
  LPair: TJSONPair;
  LFile: TTgParamFile;
  LPart: TTgFormPart;
  LStream: TStream;
begin
  LFieldCount := AParams.Json.Count;
  SetLength(Result, LFieldCount + AParams.FileCount);
  for I := 0 to LFieldCount - 1 do
  begin
    LPair := AParams.Json.Pairs[I];
    LPart := Default(TTgFormPart);
    LPart.Name := LPair.JsonString.Value;
    LPart.Value := TTgJson.ToFormText(LPair.JsonValue);
    Result[I] := LPart;
  end;
  for I := 0 to AParams.FileCount - 1 do
  begin
    LFile := AParams.Files[I];
    LPart := Default(TTgFormPart);
    LPart.Name := LFile.Name;
    LStream := nil;
    case LFile.InputFile.Kind of
      TTgInputFileKind.UploadFile:
        // Файл открывается при каждой попытке; поток живёт в AOwnedStreams
        // до окончания отправки и освобождается вызывающим.
        LStream := TFileStream.Create(LFile.InputFile.Value, fmOpenRead or fmShareDenyWrite);
      TTgInputFileKind.UploadBytes:
        // Без копирования: поток ссылается на массив байт файла.
        LStream := TBytesStream.Create(LFile.InputFile.Bytes);
      TTgInputFileKind.UploadStream:
        // Поток пользователя отправляется целиком с позиции 0 (в т.ч. при повторе после 429).
        LPart.Stream := LFile.InputFile.Stream;
    else
      LPart.Value := LFile.InputFile.ToParamValue;
    end;
    if Assigned(LStream) then
    begin
      try
        AOwnedStreams.Add(LStream);
      except
        LStream.Free;
        raise;
      end;
      LPart.Stream := LStream;
    end;
    if LPart.IsFile then
    begin
      LPart.FileName := SanitizeFormFileName(LFile.InputFile.FileName);
      LPart.ContentType := LFile.InputFile.ContentType;
    end;
    Result[LFieldCount + I] := LPart;
  end;
end;

function TTgTransportBase.SendRequest(const AMethod: string;
  AParams: TTgParams): TTgHttpResponse;
var
  LRequest: TTgPostRequest;
  LOwnedStreams: TObjectList<TStream>;
  LJson: string;
  I: Integer;
begin
  Result := Default(TTgHttpResponse);
  LRequest := Default(TTgPostRequest);
  LRequest.Method := AMethod;
  LRequest.Url := MethodUrl(AMethod);
  LRequest.ResponseTimeoutMs := ResponseTimeoutFor(AMethod, AParams);
  // Токен операции — окружающий: ExecuteEx устанавливает его на время вызова.
  LRequest.Cancel := TTgCancelScope.Current;
  LOwnedStreams := nil;
  try
    // Тело готовится до сетевой части: ошибки открытия файлов не считаются сетевыми.
    if Assigned(AParams) and AParams.HasFiles then
    begin
      LOwnedStreams := TObjectList<TStream>.Create(True);
      LRequest.Parts := FormPartsFor(AParams, LOwnedStreams);
      // Каждая попытка (в т.ч. повтор после 429) отправляет файлы с начала.
      for I := 0 to High(LRequest.Parts) do
        if LRequest.Parts[I].IsFile then
          LRequest.Parts[I].Stream.Position := 0;
    end
    else
    begin
      if Assigned(AParams) then
        LJson := AParams.ToJsonText
      else
        LJson := '{}';
      LRequest.ContentType := 'application/json; charset=utf-8';
      LRequest.Body := TEncoding.UTF8.GetBytes(LJson);
    end;
    try
      Result := Post(LRequest);
    except
      on E: ETgError do
        raise;
      on E: Exception do
        raise FailureFrom(AMethod, E, LRequest.Cancel);
    end;
    // Отменённый запрос может завершиться без исключения (с неполным ответом).
    if Assigned(LRequest.Cancel) and LRequest.Cancel.IsCancelled then
      raise ETgCancelledError.Create(TgText(TTgText.Cancelled));
  finally
    // Потоки частей формы освобождаются после Post: наследник их не хранит.
    LOwnedStreams.Free;
  end;
end;

function TTgTransportBase.GlobalCancelSource: ITgCancellationSource;
begin
  FCancelLock.Enter;
  try
    Result := FGlobalCancel;
  finally
    FCancelLock.Leave;
  end;
end;

function TTgTransportBase.GlobalCancel: ITgCancellation;
begin
  Result := GlobalCancelSource;
end;

function TTgTransportBase.GetSettings: TTgHttpSettings;
begin
  Result := FSettings;
end;

function TTgTransportBase.WaitTokenFor(const ACancel: ITgCancellation): ITgCancellation;
begin
  Result := TTgCancellationSource.Linked(ACancel, GlobalCancel);
end;

procedure TTgTransportBase.WaitInterruptible(AMs: Integer; const AToken: ITgCancellation);
begin
  if AMs <= 0 then
    AToken.ThrowIfCancelled
  else if AToken.WaitFor(Cardinal(AMs)) then
    raise ETgCancelledError.Create(TgText(TTgText.Cancelled));
end;

function TTgTransportBase.Execute(const AMethod: string;
  AParams: TTgParams): TJSONValue;
begin
  Result := ExecuteEx(AMethod, AParams, TTgCancelScope.Current);
end;

function TTgTransportBase.ExecuteEx(const AMethod: string; AParams: TTgParams;
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

procedure TTgTransportBase.DownloadFile(const AFilePath: string; ADest: TStream);
begin
  DownloadFileEx(AFilePath, ADest, TTgCancelScope.Current);
end;

procedure TTgTransportBase.DownloadFileEx(const AFilePath: string; ADest: TStream;
  const ACancel: ITgCancellation);
const
  // Имя операции в сообщениях об ошибках (это не метод Bot API).
  CMethod = 'downloadFile';
var
  LWaitToken: ITgCancellation;
  LRequest: TTgDownloadRequest;
  LStatus: Integer;
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
  LRequest := Default(TTgDownloadRequest);
  LRequest.Url := FileUrl(AFilePath);
  // ResponseTimeoutMs <= 0 — значение транспорта по умолчанию.
  LRequest.ResponseTimeoutMs := FSettings.ResponseTimeoutMs;
  if LRequest.ResponseTimeoutMs <= 0 then
    LRequest.ResponseTimeoutMs := DefaultResponseTimeoutMs;
  LRequest.Cancel := ACancel;
  try
    LStatus := Download(LRequest, ADest);
  except
    on E: ETgError do
      raise;
    on E: Exception do
      raise FailureFrom(CMethod, E, ACancel);
  end;
  // Отменённый запрос может завершиться без исключения (с неполным ответом).
  if Assigned(ACancel) and ACancel.IsCancelled then
    raise ETgCancelledError.Create(TgText(TTgText.Cancelled));
  if LStatus <> 200 then
    raise ETgNetworkError.Create(
      WithProxyInfo(TgTextFmt(TTgText.DownloadFailed, [LStatus])),
      LStatus, CMethod);
end;

procedure TTgTransportBase.Cancel;
begin
  // Источник одноразовый: отменяем текущий, ResetCancel заменит его новым.
  // Отмена — вне FCancelLock: колбэки подписчиков не выполняются под блокировкой.
  GlobalCancelSource.Cancel;
end;

procedure TTgTransportBase.ResetCancel;
begin
  FCancelLock.Enter;
  try
    if FGlobalCancel.IsCancelled then
      FGlobalCancel := TTgCancellationSource.New;
  finally
    FCancelLock.Leave;
  end;
end;

function TTgTransportBase.IsCancelled: Boolean;
begin
  Result := GlobalCancel.IsCancelled;
end;

{ Реестр транспорта по умолчанию }

/// <summary>
///   Идентичность фабрики — указатель на объект ссылки на функцию (ссылка
///   на функцию — интерфейс). Нетипизированный параметр: берётся значение
///   переменной, а не результат вызова.
/// </summary>
function FactoryIdentity(const AFactory): Pointer;
begin
  Result := Pointer(AFactory);
end;

/// <summary>Индекс фабрики в GFactories или -1 (под GFactoryLock).</summary>
function IndexOfFactory(AIdentity: Pointer): Integer;
var
  I: Integer;
begin
  for I := High(GFactories) downto 0 do
    if FactoryIdentity(GFactories[I]) = AIdentity then
      Exit(I);
  Result := -1;
end;

/// <summary>
///   Добавляет фабрику в стек: наверх (текущая) или, при AFallback, в самый
///   низ (запасная). Уже зарегистрированная ссылка переносится.
/// </summary>
procedure AddFactory(const AFactory: TTgTransportFactory; AFallback: Boolean);
var
  LIndex, I: Integer;
begin
  if not Assigned(AFactory) then
    raise EArgumentNilException.Create(TgLangTextFmt(@SRuArgNil, @SEnArgNil, ['AFactory']));
  // После finalization модуля реестра (выгрузка) регистрировать некуда.
  if not Assigned(GFactoryLock) then
    Exit;
  GFactoryLock.Enter;
  try
    LIndex := IndexOfFactory(FactoryIdentity(AFactory));
    if LIndex >= 0 then
      Delete(GFactories, LIndex, 1);
    SetLength(GFactories, Length(GFactories) + 1);
    if AFallback then
    begin
      for I := High(GFactories) downto 1 do
        GFactories[I] := GFactories[I - 1];
      GFactories[0] := AFactory;
    end
    else
      GFactories[High(GFactories)] := AFactory;
  finally
    GFactoryLock.Leave;
  end;
end;

procedure TgRegisterDefaultTransport(const AFactory: TTgTransportFactory);
begin
  AddFactory(AFactory, False);
end;

procedure TgRegisterFallbackTransport(const AFactory: TTgTransportFactory);
begin
  AddFactory(AFactory, True);
end;

procedure TgUnregisterDefaultTransport(const AFactory: TTgTransportFactory);
var
  LIndex: Integer;
begin
  // После finalization модуля реестра (выгрузка) снимать уже нечего.
  if not Assigned(AFactory) or not Assigned(GFactoryLock) then
    Exit;
  GFactoryLock.Enter;
  try
    LIndex := IndexOfFactory(FactoryIdentity(AFactory));
    if LIndex >= 0 then
      Delete(GFactories, LIndex, 1);
  finally
    GFactoryLock.Leave;
  end;
end;

function TgDefaultTransportFactory: TTgTransportFactory;
begin
  // После finalization модуля реестра фабрик нет (TgCreateDefaultTransport —
  // ETgError «не зарегистрирован», а не нарушение доступа).
  if not Assigned(GFactoryLock) then
    Exit(nil);
  GFactoryLock.Enter;
  try
    if Length(GFactories) > 0 then
      Result := GFactories[High(GFactories)]
    else
      Result := nil;
  finally
    GFactoryLock.Leave;
  end;
end;

function TgCreateDefaultTransport(const ASettings: TTgHttpSettings): ITgTransport;
var
  LFactory: TTgTransportFactory;
begin
  // Фабрика вызывается вне замка: создание транспорта может быть долгим
  // или регистрировать/снимать фабрики.
  LFactory := TgDefaultTransportFactory();
  if not Assigned(LFactory) then
    raise ETgError.Create(TgLangText(@SRuDefaultTransportMissing, @SEnDefaultTransportMissing));
  Result := LFactory(ASettings);
  if not Assigned(Result) then
    raise ETgError.Create(TgText(TTgText.TransportRequired));
end;

initialization
  GFactoryLock := TCriticalSection.Create;

finalization
  GFactories := nil;
  FreeAndNil(GFactoryLock);

end.
