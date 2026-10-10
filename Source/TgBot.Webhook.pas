unit TgBot.Webhook;

(*
  TTgWebhookServer — встроенный HTTP-сервер webhook для TTelegramBot на Indy
  (TIdHTTPServer): TelegramBot1.Webhook.Server := TgWebhookServer1, и бот
  при запуске регистрирует у сервера свой путь Webhook.Path.

  Только HTTP: TLS завершает обратный прокси (Telegram требует HTTPS на
  портах 443, 80, 88 или 8443). Сервер по умолчанию слушает 127.0.0.1:8080,
  PublicUrl — внешний HTTPS-адрес прокси (https://bots.example.com), URL
  бота для setWebhook = PublicUrl + Path. Прокси должен передавать путь без
  изменений или срезать общий префикс, входящий в PublicUrl:

    Caddy:       bots.example.com {
                   reverse_proxy 127.0.0.1:8080
                 }
    nginx:       location /tg/ {
                   proxy_pass http://127.0.0.1:8080;
                   client_max_body_size 1m;
                 }
    cloudflared: ingress: - hostname: bots.example.com
                            service: http://127.0.0.1:8080

  Запрос: только POST (иначе 405); путь сравнивается с зарегистрированными
  точно (без query, с учётом регистра; неизвестный — 404 до чтения тела);
  Content-Length больше MaxBodySize — 413 до чтения тела, chunked-тело
  читается не дальше MaxBodySize (+ буфер сокета); затем тело и заголовок
  X-Telegram-Bot-Api-Secret-Token — в TTelegramBot.HandleWebhook, ответ —
  TgWebhookHttpStatus(результат) с пустым телом. Keep-alive поддерживается.

  Потоки: запросы обрабатываются в потоках Indy; OnRequest и OnError
  вызываются в них же (синхронизация — на пользователе; назначать до
  Active := True). Active, RegisterBot/UnregisterBot и Free — из потока,
  управляющего компонентами (обычно главного); из OnRequest/OnError
  останавливать сервер нельзя (взаимоблокировка с ожиданием потоков Indy).
  UnregisterBot ждёт завершения запросов, уже переданных этому боту.

  Безопасность: токен бота и секрет в тексты событий и исключений не
  попадают; не включайте токен в Path — для проверки отправителя служит
  Webhook.SecretToken (сравнение в боте за постоянное время).
*)

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.Classes,
  System.SyncObjs,
  System.Generics.Collections,
  IdContext,
  IdHeaderList,
  IdCustomHTTPServer,
  IdHTTPServer,
  TgBot,
  TgBot.Component;

const
  /// <summary>Порт TTgWebhookServer по умолчанию.</summary>
  TgWebhookDefaultPort = 8080;
  /// <summary>Адрес прослушивания по умолчанию: только локальный (за обратным прокси).</summary>
  TgWebhookDefaultBindAddress = '127.0.0.1';
  /// <summary>Предел тела запроса по умолчанию, байт (1 МБ).</summary>
  TgWebhookDefaultMaxBodySize = 1024 * 1024;

type
  /// <summary>
  ///   Запрос обработан (лог): AMethod — метод ('' — запрос отклонён до
  ///   разбора метода: 404/413/400), APath — путь без query, AStatus — код ответа.
  /// </summary>
  TTgWebhookRequestEvent = procedure(Sender: TObject; const AMethod, APath: string;
    AStatus: Integer) of object;
  /// <summary>Ошибка обработки запроса (ответ 500); E принадлежит вызывающему.</summary>
  TTgWebhookServerErrorEvent = procedure(Sender: TObject; E: Exception) of object;

  /// <summary>
  ///   HTTP-сервер webhook на Indy для одного или нескольких TTelegramBot
  ///   (по разным путям). Только HTTP: HTTPS — обратный прокси (Caddy, nginx,
  ///   cloudflared), см. шапку модуля.
  ///
  ///   Порядок запуска не важен: бот, запущенный раньше сервера, уже
  ///   зарегистрирован (setWebhook проходит, доставка Telegram начнётся с
  ///   запуском сервера). Active в дизайнере только запоминается; из формы —
  ///   отложенный запуск после загрузки (TThread.ForceQueue), его ошибка —
  ///   OnError, без OnError — исключение в обработчике очереди.
  ///   Занятый порт — ETgError при Active := True.
  ///
  ///   Destroy останавливает сервер (дожидаясь потоков запросов) и забывает
  ///   ботов; их Webhook.Server обнуляется (Notification), боты продолжают
  ///   работать.
  /// </summary>
  [ComponentPlatformsAttribute(pidWin32 or pidWin64 or pidLinux64)]
  TTgWebhookServer = class(TTgCustomWebhookServer)
  private type
    /// <summary>Связь отложенного запуска с компонентом (nil — уничтожен).</summary>
    TLink = class(TInterfacedObject)
    private
      FOwner: TTgWebhookServer;
    end;
  private
    FHttp: TIdHTTPServer;
    // Путь → бот; запись — под FLock.BeginWrite, запросы держат BeginRead
    // на время HandleWebhook (бот не освобождается посреди вызова).
    FLock: TLightweightMREW;
    FBots: TDictionary<string, TTelegramBot>;
    FLink: TLink;
    FLinkRef: IInterface;
    FPort: Integer;
    FBindAddress: string;
    FPublicUrl: string;
    FMaxBodySize: Integer;
    FMaxConnections: Integer;
    FDesignActive: Boolean;
    FStreamedActive: Boolean;
    FStartPending: Boolean;
    FOnError: TTgWebhookServerErrorEvent;
    FOnRequest: TTgWebhookRequestEvent;
    function GetActive: Boolean;
    procedure SetActive(AValue: Boolean);
    procedure SetPort(AValue: Integer);
    procedure SetBindAddress(const AValue: string);
    procedure SetMaxBodySize(AValue: Integer);
    procedure SetMaxConnections(AValue: Integer);
    function GetBoundPort: Integer;
    function GetBotCount: Integer;
    procedure CheckInactive;
    procedure StartServer;
    procedure StopServer;
    procedure StartDeferred;
    function HasPath(const APath: string): Boolean;
    procedure DoRequest(const AMethod, APath: string; AStatus: Integer);
    procedure DoError(E: Exception);
    // Обработчики TIdHTTPServer (потоки Indy).
    procedure HttpConnect(AContext: TIdContext);
    procedure HttpHeadersAvailable(AContext: TIdContext; const AUri: string;
      AHeaders: TIdHeaderList; var VContinueProcessing: Boolean);
    procedure HttpCreatePostStream(AContext: TIdContext; AHeaders: TIdHeaderList;
      var VPostStream: TStream);
    procedure HttpCommand(AContext: TIdContext; ARequestInfo: TIdHTTPRequestInfo;
      AResponseInfo: TIdHTTPResponseInfo);
    procedure HttpException(AContext: TIdContext; AException: Exception);
  protected
    procedure Loaded; override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
  public
    constructor Create(AOwner: TComponent); override;
    /// <summary>Останавливает сервер и забывает ботов (их Webhook.Server обнуляется).</summary>
    destructor Destroy; override;
    /// <summary>
    ///   Направлять POST по пути APath боту ABot ('/' добавляется в начало,
    ///   если его нет). Путь занят другим ботом — ETgError.
    /// </summary>
    procedure RegisterBot(const APath: string; ABot: TTelegramBot); override;
    /// <summary>
    ///   Снять регистрацию (неизвестная пара — ничего); ждёт запросы, уже
    ///   переданные боту (не дольше его PostTimeoutMs).
    /// </summary>
    procedure UnregisterBot(const APath: string; ABot: TTelegramBot); override;
    /// <summary>PublicUrl (без завершающего '/') + APath; PublicUrl пуст — ''.</summary>
    function GetWebhookUrl(const APath: string): string; override;
    /// <summary>Active := True.</summary>
    procedure Start;
    /// <summary>Active := False.</summary>
    procedure Stop;
    /// <summary>
    ///   Фактический порт работающего сервера (при Port = 0 — выбранный ОС);
    ///   0 — сервер не запущен.
    /// </summary>
    property BoundPort: Integer read GetBoundPort;
    /// <summary>Число зарегистрированных путей.</summary>
    property BotCount: Integer read GetBotCount;
  published
    /// <summary>
    ///   Сервер слушает порт. Ошибка запуска (порт занят) — ETgError;
    ///   из формы — OnError.
    /// </summary>
    property Active: Boolean read GetActive write SetActive default False;
    /// <summary>Порт (0 — любой свободный, см. BoundPort). Менять при работе нельзя.</summary>
    property Port: Integer read FPort write SetPort default TgWebhookDefaultPort;
    /// <summary>
    ///   Адрес прослушивания: '127.0.0.1' — только локально (за обратным
    ///   прокси, по умолчанию), '0.0.0.0' — все IPv4, '::1'/'::' — IPv6.
    /// </summary>
    property BindAddress: string read FBindAddress write SetBindAddress;
    /// <summary>
    ///   Внешний HTTPS-адрес (https://bots.example.com[/префикс]) для
    ///   GetWebhookUrl; пусто — Webhook.Url бота нужно задать явно.
    ///   Не пусто и не 'https://' — ETgError при Active := True (Telegram
    ///   принимает только HTTPS).
    /// </summary>
    property PublicUrl: string read FPublicUrl write FPublicUrl;
    /// <summary>Предел тела запроса, байт (по умолчанию 1 МБ); больше — 413.</summary>
    property MaxBodySize: Integer read FMaxBodySize write SetMaxBodySize
      default TgWebhookDefaultMaxBodySize;
    /// <summary>Предел одновременных соединений (0 — без предела). Менять при работе нельзя.</summary>
    property MaxConnections: Integer read FMaxConnections write SetMaxConnections default 0;
    /// <summary>Ошибка обработки запроса (поток Indy).</summary>
    property OnError: TTgWebhookServerErrorEvent read FOnError write FOnError;
    /// <summary>Каждый обработанный запрос (поток Indy): метод, путь, код.</summary>
    property OnRequest: TTgWebhookRequestEvent read FOnRequest write FOnRequest;
  end;

implementation

uses
  IdGlobal,
  IdException,
  IdExceptionCore,
  IdSocketHandle;

resourcestring
  SRuServerActive = 'Нельзя менять Port, BindAddress и MaxConnections, пока сервер работает';
  SEnServerActive = 'Cannot change Port, BindAddress and MaxConnections while the server is running';
  SRuBadPort = 'Недопустимый порт %d (0–65535)';
  SEnBadPort = 'Invalid port %d (0-65535)';
  SRuBadBodySize = 'Недопустимый MaxBodySize %d (нужно больше 0)';
  SEnBadBodySize = 'Invalid MaxBodySize %d (must be greater than 0)';
  SRuBadConnections = 'Недопустимый MaxConnections %d (нужно 0 и больше)';
  SEnBadConnections = 'Invalid MaxConnections %d (must be 0 or greater)';
  SRuStartFailed = 'Не удалось запустить webhook-сервер на %s:%d: %s';
  SEnStartFailed = 'Failed to start the webhook server on %s:%d: %s';
  SRuPathTaken = 'Путь webhook "%s" уже занят другим ботом (%s)';
  SEnPathTaken = 'Webhook path "%s" is already used by another bot (%s)';
  SRuBadPath = 'Недопустимый путь webhook "%s": пробелы, "?" и "#" не допускаются';
  SEnBadPath = 'Invalid webhook path "%s": spaces, "?" and "#" are not allowed';
  SRuPublicUrlNotHttps = 'PublicUrl webhook-сервера должен начинаться с https:// ' +
    '(Telegram принимает только HTTPS): %s';
  SEnPublicUrlNotHttps = 'The webhook server PublicUrl must start with https:// ' +
    '(Telegram accepts HTTPS only): %s';

const
  CSecretHeader = 'X-Telegram-Bot-Api-Secret-Token';
  // Сколько поток соединения ждёт данные (запрос или его продолжение), мс:
  // медленный клиент не держит поток бесконечно; простаивающее keep-alive
  // соединение закрывается.
  CReadTimeoutMs = 30000;

type
  /// <summary>
  ///   Прерывание соединения после ответа, записанного вручную (до чтения
  ///   тела). Наследник EIdClosedSocket: TIdCustomHTTPServer.DoExecute
  ///   перехватывает его и закрывает соединение без OnException.
  /// </summary>
  ETgWebhookAbort = class(EIdClosedSocket);

  /// <summary>
  ///   Поток тела chunked-запроса: запись дальше ALimit байт — ответ 413 и
  ///   разрыв соединения (остаток тела не читается).
  /// </summary>
  TTgLimitedStream = class(TMemoryStream)
  private
    FContext: TIdContext;
    FLimit: Int64;
  public
    constructor Create(AContext: TIdContext; ALimit: Int64);
    function Write(const Buffer; Count: Longint): Longint; override;
  end;

/// <summary>Текст на языке библиотеки (TgSetLanguage).</summary>
function LangText(const ARu, AEn: string): string;
begin
  if TgGetLanguage = TTgLanguage.En then
    Result := AEn
  else
    Result := ARu;
end;

/// <summary>Путь с ведущим '/' (пустой — '/').</summary>
function NormalizePath(const APath: string): string;
begin
  Result := Trim(APath);
  if (Result = '') or (Result[1] <> '/') then
    Result := '/' + Result;
end;

/// <summary>Путь допустим: без пробелов и управляющих символов, '?' и '#'.</summary>
function IsValidPath(const APath: string): Boolean;
var
  LChar: Char;
begin
  for LChar in APath do
    if (LChar <= ' ') or (LChar = '?') or (LChar = '#') then
      Exit(False);
  Result := True;
end;

function StatusText(AStatus: Integer): string;
begin
  case AStatus of
    400: Result := 'Bad Request';
    404: Result := 'Not Found';
    413: Result := 'Payload Too Large';
  else
    Result := 'Error';
  end;
end;

/// <summary>
///   Пишет ответ AStatus с пустым телом и закрытием соединения, затем
///   прерывает обработку (ETgWebhookAbort): тело запроса не читается.
/// </summary>
procedure AbortWithStatus(AContext: TIdContext; AStatus: Integer);
begin
  try
    AContext.Connection.IOHandler.Write('HTTP/1.1 ' + IntToStr(AStatus) + ' ' +
      StatusText(AStatus) + #13#10'Content-Length: 0'#13#10'Connection: close'#13#10#13#10);
  except
    // Клиент уже отключился — ответить некому.
  end;
  raise ETgWebhookAbort.Create('');
end;

{ TTgLimitedStream }

constructor TTgLimitedStream.Create(AContext: TIdContext; ALimit: Int64);
begin
  inherited Create;
  FContext := AContext;
  FLimit := ALimit;
end;

function TTgLimitedStream.Write(const Buffer; Count: Longint): Longint;
begin
  if Position + Count > FLimit then
    AbortWithStatus(FContext, 413);
  Result := inherited Write(Buffer, Count);
end;

{ TTgWebhookServer }

constructor TTgWebhookServer.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FLink := TLink.Create;
  FLinkRef := FLink;
  FLink.FOwner := Self;
  FBots := TDictionary<string, TTelegramBot>.Create;
  FPort := TgWebhookDefaultPort;
  FBindAddress := TgWebhookDefaultBindAddress;
  FMaxBodySize := TgWebhookDefaultMaxBodySize;
end;

destructor TTgWebhookServer.Destroy;
begin
  if Assigned(FLink) then
    FLink.FOwner := nil;
  FStartPending := False;
  // Сначала остановить приём: потоки запросов завершены, HandleWebhook не идёт.
  StopServer;
  if Assigned(FBots) then
  begin
    FLock.BeginWrite;
    try
      FBots.Clear;
    finally
      FLock.EndWrite;
    end;
  end;
  FLink := nil;
  FLinkRef := nil;
  // inherited Destroy рассылает Notification: боты обнуляют Webhook.Server.
  inherited Destroy;
  FreeAndNil(FBots);
end;

procedure TTgWebhookServer.Notification(AComponent: TComponent; Operation: TOperation);
var
  LPair: TPair<string, TTelegramBot>;
  LPaths: TList<string>;
  LPath: string;
begin
  inherited Notification(AComponent, Operation);
  if (Operation <> opRemove) or not (AComponent is TTelegramBot) or not Assigned(FBots) then
    Exit;
  // Страховка: бот сам снимает регистрацию в Destroy.
  LPaths := TList<string>.Create;
  try
    FLock.BeginWrite;
    try
      for LPair in FBots do
        if LPair.Value = AComponent then
          LPaths.Add(LPair.Key);
      for LPath in LPaths do
        FBots.Remove(LPath);
    finally
      FLock.EndWrite;
    end;
  finally
    LPaths.Free;
  end;
end;

procedure TTgWebhookServer.RegisterBot(const APath: string; ABot: TTelegramBot);
var
  LPath: string;
  LOther: TTelegramBot;
begin
  if not Assigned(ABot) then
    Exit;
  LPath := NormalizePath(APath);
  if not IsValidPath(LPath) then
    raise ETgError.CreateFmt(LangText(SRuBadPath, SEnBadPath), [LPath]);
  FLock.BeginWrite;
  try
    if FBots.TryGetValue(LPath, LOther) and (LOther <> ABot) then
      raise ETgError.CreateFmt(LangText(SRuPathTaken, SEnPathTaken), [LPath, LOther.Name]);
    FBots.AddOrSetValue(LPath, ABot);
  finally
    FLock.EndWrite;
  end;
  // Уничтожение бота, зарегистрированного вручную, снимает его пути (Notification).
  ABot.FreeNotification(Self);
end;

procedure TTgWebhookServer.UnregisterBot(const APath: string; ABot: TTelegramBot);
var
  LPath: string;
  LBot: TTelegramBot;
begin
  if not Assigned(FBots) then
    Exit;
  LPath := NormalizePath(APath);
  // Блокировка записи дожидается запросов, держащих BeginRead.
  FLock.BeginWrite;
  try
    if FBots.TryGetValue(LPath, LBot) and (LBot = ABot) then
      FBots.Remove(LPath);
  finally
    FLock.EndWrite;
  end;
end;

function TTgWebhookServer.GetWebhookUrl(const APath: string): string;
begin
  Result := Trim(FPublicUrl);
  if Result = '' then
    Exit;
  while (Result <> '') and (Result[Length(Result)] = '/') do
    SetLength(Result, Length(Result) - 1);
  Result := Result + NormalizePath(APath);
end;

function TTgWebhookServer.HasPath(const APath: string): Boolean;
begin
  FLock.BeginRead;
  try
    Result := FBots.ContainsKey(APath);
  finally
    FLock.EndRead;
  end;
end;

function TTgWebhookServer.GetBotCount: Integer;
begin
  FLock.BeginRead;
  try
    Result := FBots.Count;
  finally
    FLock.EndRead;
  end;
end;

procedure TTgWebhookServer.CheckInactive;
begin
  if (ComponentState * [csDesigning, csLoading] = []) and Assigned(FHttp) then
    raise ETgError.Create(LangText(SRuServerActive, SEnServerActive));
end;

procedure TTgWebhookServer.SetPort(AValue: Integer);
begin
  if (AValue < 0) or (AValue > 65535) then
    raise ETgError.CreateFmt(LangText(SRuBadPort, SEnBadPort), [AValue]);
  CheckInactive;
  FPort := AValue;
end;

procedure TTgWebhookServer.SetBindAddress(const AValue: string);
begin
  CheckInactive;
  FBindAddress := Trim(AValue);
end;

procedure TTgWebhookServer.SetMaxBodySize(AValue: Integer);
begin
  if AValue <= 0 then
    raise ETgError.CreateFmt(LangText(SRuBadBodySize, SEnBadBodySize), [AValue]);
  // Читается потоками запросов (выровненное Integer — атомарно); действует сразу.
  FMaxBodySize := AValue;
end;

procedure TTgWebhookServer.SetMaxConnections(AValue: Integer);
begin
  if AValue < 0 then
    raise ETgError.CreateFmt(LangText(SRuBadConnections, SEnBadConnections), [AValue]);
  CheckInactive;
  FMaxConnections := AValue;
end;

function TTgWebhookServer.GetBoundPort: Integer;
begin
  if Assigned(FHttp) and (FHttp.Bindings.Count > 0) then
    Result := FHttp.Bindings[0].Port
  else
    Result := 0;
end;

function TTgWebhookServer.GetActive: Boolean;
begin
  if csDesigning in ComponentState then
    Result := FDesignActive
  else if csLoading in ComponentState then
    Result := FStreamedActive
  else
    Result := Assigned(FHttp);
end;

procedure TTgWebhookServer.SetActive(AValue: Boolean);
begin
  if csDesigning in ComponentState then
  begin
    // В дизайнере сервер не запускается: значение только сохраняется в форме.
    FDesignActive := AValue;
    Exit;
  end;
  if csLoading in ComponentState then
  begin
    FStreamedActive := AValue;
    Exit;
  end;
  // Явная установка отменяет отложенный запуск из формы.
  FStartPending := False;
  if AValue then
    StartServer
  else
    StopServer;
end;

procedure TTgWebhookServer.Loaded;
var
  LLink: IInterface;
begin
  inherited Loaded;
  if FStreamedActive and not (csDesigning in ComponentState) then
  begin
    FStreamedActive := False;
    FStartPending := True;
    LLink := FLinkRef;
    // Как у TTelegramBot: OnCreate формы успевает задать Port/PublicUrl.
    TThread.ForceQueue(nil,
      procedure
      var
        LOwner: TTgWebhookServer;
      begin
        LOwner := TLink(LLink as TObject).FOwner;
        if Assigned(LOwner) then
          LOwner.StartDeferred;
      end);
  end;
end;

procedure TTgWebhookServer.StartDeferred;
begin
  if not FStartPending then
    Exit;
  FStartPending := False;
  try
    StartServer;
  except
    on E: Exception do
      if Assigned(FOnError) then
        FOnError(Self, E)
      else
        raise;
  end;
end;

procedure TTgWebhookServer.Start;
begin
  SetActive(True);
end;

procedure TTgWebhookServer.Stop;
begin
  SetActive(False);
end;

procedure TTgWebhookServer.StartServer;
var
  LHttp: TIdHTTPServer;
  LBinding: TIdSocketHandle;
begin
  if Assigned(FHttp) then
    Exit;
  // До открытия порта: URL бота строится из PublicUrl (setWebhook отклонил бы http).
  if (Trim(FPublicUrl) <> '') and not SameText(Copy(Trim(FPublicUrl), 1, 8), 'https://') then
    raise ETgError.CreateFmt(LangText(SRuPublicUrlNotHttps, SEnPublicUrlNotHttps), [Trim(FPublicUrl)]);
  LHttp := TIdHTTPServer.Create(nil);
  try
    LHttp.DefaultPort := FPort;
    LBinding := LHttp.Bindings.Add;
    if Pos(':', FBindAddress) > 0 then
      LBinding.IPVersion := Id_IPv6
    else
      LBinding.IPVersion := Id_IPv4;
    LBinding.IP := FBindAddress;
    LBinding.Port := FPort;
    LHttp.MaxConnections := FMaxConnections;
    LHttp.KeepAlive := True;
    LHttp.ParseParams := False;
    LHttp.SessionState := False;
    LHttp.AutoStartSession := False;
    LHttp.ServerSoftware := '';
    LHttp.OnConnect := HttpConnect;
    LHttp.OnHeadersAvailable := HttpHeadersAvailable;
    LHttp.OnCreatePostStream := HttpCreatePostStream;
    LHttp.OnCommandGet := HttpCommand;
    LHttp.OnCommandOther := HttpCommand;
    LHttp.OnException := HttpException;
    try
      LHttp.Active := True;
    except
      on E: Exception do
        raise ETgError.CreateFmt(LangText(SRuStartFailed, SEnStartFailed),
          [FBindAddress, FPort, E.Message]);
    end;
  except
    LHttp.Free;
    raise;
  end;
  FHttp := LHttp;
end;

procedure TTgWebhookServer.StopServer;
var
  LHttp: TIdHTTPServer;
begin
  LHttp := FHttp;
  if not Assigned(LHttp) then
    Exit;
  FHttp := nil;
  try
    // Закрывает соединения и ждёт потоки запросов.
    LHttp.Active := False;
  finally
    LHttp.Free;
  end;
end;

procedure TTgWebhookServer.DoRequest(const AMethod, APath: string; AStatus: Integer);
begin
  if Assigned(FOnRequest) then
  try
    FOnRequest(Self, AMethod, APath, AStatus);
  except
    // Ошибка журнала не должна ломать ответ Telegram.
  end;
end;

procedure TTgWebhookServer.DoError(E: Exception);
begin
  if Assigned(FOnError) then
  try
    FOnError(Self, E);
  except
    // Исключение из обработчика ошибок не выпускается в поток Indy.
  end;
end;

procedure TTgWebhookServer.HttpConnect(AContext: TIdContext);
begin
  AContext.Connection.IOHandler.ReadTimeout := CReadTimeoutMs;
end;

procedure TTgWebhookServer.HttpHeadersAvailable(AContext: TIdContext; const AUri: string;
  AHeaders: TIdHeaderList; var VContinueProcessing: Boolean);
var
  LLength: string;
  LSize: Int64;
  LStatus: Integer;
begin
  // До чтения тела: неизвестный путь и слишком большое тело не читаются.
  LStatus := 0;
  if not HasPath(AUri) then
    LStatus := 404
  else
  begin
    LLength := Trim(AHeaders.Values['Content-Length']);
    if LLength <> '' then
      if not TryStrToInt64(LLength, LSize) or (LSize < 0) then
        LStatus := 400
      else if LSize > FMaxBodySize then
        LStatus := 413;
  end;
  if LStatus <> 0 then
  begin
    DoRequest('', AUri, LStatus);
    AbortWithStatus(AContext, LStatus);
  end;
  VContinueProcessing := True;
end;

procedure TTgWebhookServer.HttpCreatePostStream(AContext: TIdContext; AHeaders: TIdHeaderList;
  var VPostStream: TStream);
begin
  // Content-Length уже проверен; chunked ограничивает поток.
  VPostStream := TTgLimitedStream.Create(AContext, FMaxBodySize);
end;

procedure TTgWebhookServer.HttpCommand(AContext: TIdContext; ARequestInfo: TIdHTTPRequestInfo;
  AResponseInfo: TIdHTTPResponseInfo);
var
  LPath: string;
  LBody: TBytes;
  LStream: TStream;
  LSecret: string;
  LBot: TTelegramBot;
  LStatus: Integer;
begin
  LPath := ARequestInfo.URI;
  // Пустое тело ответа (иначе Indy подставляет HTML-страницу кода).
  AResponseInfo.ContentText := '';
  AResponseInfo.ContentLength := 0;
  if ARequestInfo.CommandType <> hcPOST then
  begin
    AResponseInfo.ResponseNo := 405;
    AResponseInfo.CustomHeaders.Values['Allow'] := 'POST';
    DoRequest(ARequestInfo.Command, LPath, 405);
    Exit;
  end;
  try
    LStream := ARequestInfo.PostStream;
    if Assigned(LStream) and (LStream.Size > 0) then
    begin
      SetLength(LBody, LStream.Size);
      LStream.Position := 0;
      LStream.ReadBuffer(LBody[0], Length(LBody));
    end;
    LSecret := ARequestInfo.RawHeaders.Values[CSecretHeader];
    FLock.BeginRead;
    try
      if FBots.TryGetValue(LPath, LBot) then
        LStatus := TgWebhookHttpStatus(LBot.HandleWebhook(LBody, LSecret))
      else
        // Регистрацию сняли, пока читалось тело.
        LStatus := 404;
    finally
      FLock.EndRead;
    end;
  except
    on E: Exception do
    begin
      // Текст исключения клиенту не отдаётся.
      LStatus := 500;
      DoError(E);
    end;
  end;
  AResponseInfo.ResponseNo := LStatus;
  DoRequest(ARequestInfo.Command, LPath, LStatus);
end;

procedure TTgWebhookServer.HttpException(AContext: TIdContext; AException: Exception);
begin
  // Обрывы, тайм-ауты и мусорные запросы (EIdException) — штатный шум сети.
  if not (AException is EIdException) then
    DoError(AException);
end;

initialization
  // Загрузка формы/потока с компонентом без объявленного поля (FindClass).
  RegisterClasses([TTgWebhookServer]);

end.
