unit TgBot.Component;

{
  TTelegramBot — невизуальный компонент Telegram-бота поверх TTgBot
  (long polling или webhook — Mode): published-свойства для Object
  Inspector, коллекция команд и события of object. Без VCL/FMX (только
  System.Classes) — годится для VCL, FMX, служб и консоли на всех
  платформах библиотеки.

  Webhook (Mode = Webhook): HTTP-сервер приложения передаёт тело запроса
  в HandleWebhook (потокобезопасно) и отвечает кодом TgWebhookHttpStatus;
  либо Webhook.Server — компонент-сервер (TTgCustomWebhookServer), которому
  бот регистрирует свой путь Webhook.Path.

    TelegramBot1.TokenEnv := 'TGBOT_TOKEN';     // или Token
    TelegramBot1.Commands.Add.Command := 'start';
    TelegramBot1.Active := True;

  Жизненный цикл: внутренний TTgBot создаётся при запуске из свойств
  компонента и освобождается при остановке и в Destroy. Регистрации
  маршрутизатора из кода (Command, Callback, Text…) хранятся в компоненте и
  применяются при каждом запуске.

  Потоки: при Delivery = Main (по умолчанию) все события приходят в главном
  потоке — обработчики обновлений через очередь диспетчера, ошибки приёма
  (OnError с Ctx = nil), OnFault и OnStop(Fault) — через TThread.Queue с
  копией исключения. При Delivery = Worker события вызываются в потоках
  диспетчера, источника и пула (синхронизация — на пользователе), а
  отказавший бот (Faulted) освобождается при следующем Active := True/False
  или в Destroy.

  Регистрация в палитре компонентов — модуль пакета времени разработки.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.Classes,
  System.SyncObjs,
  System.Generics.Collections,
  TgBot,
  TgBot.Base;

type
  /// <summary>Причина остановки бота (OnStop).</summary>
  TTgStopReason = (
    /// <summary>Active := False или Stop (Destroy OnStop не вызывает: события уже отцеплены).</summary>
    Requested,
    /// <summary>Неустранимая ошибка приёма (401, 404, 409 webhook…).</summary>
    Fault);

  /// <summary>Событие с контекстом обновления.</summary>
  TTgContextEvent = procedure(Sender: TObject; const Ctx: ITgContext) of object;
  /// <summary>Обработчик команды (элемент Commands, OnCommand).</summary>
  TTgCommandEvent = procedure(Sender: TObject; const Ctx: ITgContext) of object;
  /// <summary>Каждое обновление; Handled := True прекращает дальнейшую обработку.</summary>
  TTgUpdateEvent = procedure(Sender: TObject; const Ctx: ITgContext; var Handled: Boolean) of object;
  /// <summary>Ошибка: обработчика (Ctx задан) или приёма/запуска (Ctx = nil).</summary>
  TTgErrorEvent = procedure(Sender: TObject; E: Exception; const Ctx: ITgContext) of object;
  /// <summary>Неустранимая ошибка приёма (бот перешёл в Faulted).</summary>
  TTgFaultEvent = procedure(Sender: TObject; E: Exception) of object;
  /// <summary>Бот остановлен.</summary>
  TTgStopEvent = procedure(Sender: TObject; Reason: TTgStopReason) of object;

  TTelegramBot = class;
  TTgCustomWebhookServer = class;

  /// <summary>
  ///   Настройки webhook компонента (Mode = Webhook). Менять при работе
  ///   бота нельзя — ETgError (в дизайнере — можно).
  /// </summary>
  TTgWebhookOptions = class(TPersistent)
  private
    FOwner: TTelegramBot;
    FUrl: string;
    FSecretToken: string;
    FMaxConnections: Integer;
    FDropPendingUpdates: Boolean;
    FDeleteOnStop: Boolean;
    FServer: TTgCustomWebhookServer;
    FPath: string;
    FIpAddress: string;
    FCertificate: string;
    FMaxBodySize: Integer;
    FPostTimeoutMs: Cardinal;
    FDedupWindow: Integer;
    FRegisterOnStart: Boolean;
    procedure SetUrl(const AValue: string);
    procedure SetIpAddress(const AValue: string);
    procedure SetCertificate(const AValue: string);
    procedure SetSecretToken(const AValue: string);
    procedure SetMaxConnections(AValue: Integer);
    procedure SetDropPendingUpdates(AValue: Boolean);
    procedure SetDeleteOnStop(AValue: Boolean);
    procedure SetMaxBodySize(AValue: Integer);
    procedure SetPostTimeoutMs(AValue: Cardinal);
    procedure SetDedupWindow(AValue: Integer);
    procedure SetRegisterOnStart(AValue: Boolean);
    procedure SetServer(AValue: TTgCustomWebhookServer);
    function GetPath: string;
    procedure SetPath(const AValue: string);
    function IsPathStored: Boolean;
  protected
    function GetOwner: TPersistent; override;
  public
    constructor Create(AOwner: TTelegramBot);
    procedure Assign(Source: TPersistent); override;
    /// <summary>URL для setWebhook: Url, а если он пуст — Server.GetWebhookUrl(Path).</summary>
    function EffectiveUrl: string;
  published
    /// <summary>Внешний HTTPS-URL бота (пусто — берётся у Server).</summary>
    property Url: string read FUrl write SetUrl;
    /// <summary>
    ///   secret_token (1–256 символов [A-Za-z0-9_-]); пусто — случайный при
    ///   каждом запуске (рекомендуется: в форме не хранится). При
    ///   RegisterOnStart = False случайный не генерируется: задайте тот же
    ///   secret_token, что передан в setWebhook при регистрации. Внимание:
    ///   пусто при RegisterOnStart = False — заголовок не проверяется, и
    ///   обновление может прислать любой, кто знает URL; это небезопасно,
    ///   при запуске вызывается OnError (Ctx = nil) с предупреждением.
    /// </summary>
    property SecretToken: string read FSecretToken write SetSecretToken;
    /// <summary>max_connections (1–100); 0 — по умолчанию сервера (40).</summary>
    property MaxConnections: Integer read FMaxConnections write SetMaxConnections default 0;
    /// <summary>Пропустить накопившиеся обновления при setWebhook.</summary>
    property DropPendingUpdates: Boolean read FDropPendingUpdates write SetDropPendingUpdates
      default False;
    /// <summary>deleteWebhook при остановке бота.</summary>
    property DeleteOnStop: Boolean read FDeleteOnStop write SetDeleteOnStop default False;
    /// <summary>
    ///   Компонент HTTP(S)-сервера: при запуске бот регистрирует у него Path,
    ///   при остановке — снимает регистрацию. nil — тело передаёт приложение
    ///   (TTelegramBot.HandleWebhook).
    /// </summary>
    property Server: TTgCustomWebhookServer read FServer write SetServer;
    /// <summary>
    ///   Путь бота на Server, по умолчанию '/tg/' + Name компонента. Server
    ///   задан, а Path и Name пусты — ETgError при запуске.
    /// </summary>
    property Path: string read GetPath write SetPath stored IsPathStored;
    /// <summary>ip_address setWebhook (вместо адреса из DNS); пусто — не передаётся.</summary>
    property IpAddress: string read FIpAddress write SetIpAddress;
    /// <summary>
    ///   Путь к файлу публичного сертификата (.pem) для самоподписанного
    ///   сертификата сервера: при запуске передаётся в setWebhook
    ///   (certificate, multipart). Пусто — не передаётся; файла нет — ETgError
    ///   при запуске. При RegisterOnStart = False не используется и не
    ///   проверяется.
    /// </summary>
    property Certificate: string read FCertificate write SetCertificate;
    /// <summary>
    ///   Наибольший размер тела HandleWebhook, байт UTF-8 (меньше 1 — как 1);
    ///   тело больше — BadRequest без разбора (TTgBot.WebhookMaxBodySize).
    ///   По умолчанию TgDefaultWebhookMaxBodySize (1 МБ).
    /// </summary>
    property MaxBodySize: Integer read FMaxBodySize write SetMaxBodySize
      default TgDefaultWebhookMaxBodySize;
    /// <summary>
    ///   Сколько HandleWebhook ждёт места в полной очереди, мс (0 — не ждёт),
    ///   затем отвечает Unavailable — Telegram повторит доставку
    ///   (TTgBot.WebhookPostTimeoutMs). По умолчанию TgDefaultWebhookPostTimeoutMs.
    /// </summary>
    property PostTimeoutMs: Cardinal read FPostTimeoutMs write SetPostTimeoutMs
      default TgDefaultWebhookPostTimeoutMs;
    /// <summary>
    ///   Сколько последних принятых update_id помнить: повторная доставка того
    ///   же update_id — Accepted без повторной обработки; 0 — без
    ///   дедупликации (TTgBot.WebhookDedupWindow). По умолчанию
    ///   TgDefaultWebhookDedupWindow. Разумный предел — до 10 000: большие
    ///   значения замедляют каждый запрос и расходуют память.
    /// </summary>
    property DedupWindow: Integer read FDedupWindow write SetDedupWindow
      default TgDefaultWebhookDedupWindow;
    /// <summary>
    ///   Вызывать setWebhook при запуске (по умолчанию True). False — webhook
    ///   зарегистрирован вне бота: setWebhook не выполняется,
    ///   OnWebhookRegistered не вызывается, Url и Certificate не используются,
    ///   пустой SecretToken не проверяется — небезопасно, см. SecretToken
    ///   (TTgBot.WebhookRegisterOnStart).
    ///   deleteWebhook при остановке — по-прежнему DeleteOnStop.
    /// </summary>
    property RegisterOnStart: Boolean read FRegisterOnStart write SetRegisterOnStart default True;
  end;

  /// <summary>
  ///   Тонкие настройки long polling компонента (Mode = Polling); timeout
  ///   getUpdates — TTelegramBot.PollingTimeout. Менять при работе бота
  ///   нельзя — ETgError (в дизайнере — можно).
  /// </summary>
  TTgPollingOptions = class(TPersistent)
  private
    FOwner: TTelegramBot;
    FLimit: Integer;
    FJitterPercent: Integer;
    FConflictNotifyIntervalMs: Cardinal;
    procedure SetLimit(AValue: Integer);
    procedure SetJitterPercent(AValue: Integer);
    procedure SetConflictNotifyIntervalMs(AValue: Cardinal);
  protected
    function GetOwner: TPersistent; override;
  public
    constructor Create(AOwner: TTelegramBot);
    procedure Assign(Source: TPersistent); override;
  published
    /// <summary>
    ///   limit getUpdates — сколько обновлений за один запрос (1–100; вне
    ///   диапазона — ближайшая граница; TTgBot.PollLimit). По умолчанию
    ///   TgDefaultPollLimit.
    /// </summary>
    property Limit: Integer read FLimit write SetLimit default TgDefaultPollLimit;
    /// <summary>
    ///   Разброс пауз между повторами getUpdates после ошибок, ± процентов
    ///   (0–50; вне диапазона — ближайшая граница; 0 — без разброса;
    ///   TTgBot.PollJitterPercent). По умолчанию TgDefaultBackoffJitterPercent.
    /// </summary>
    property JitterPercent: Integer read FJitterPercent write SetJitterPercent
      default TgDefaultBackoffJitterPercent;
    /// <summary>
    ///   Минимальный интервал повторных событий Bot.OnConflict (TTgBot) при
    ///   409 «другой getUpdates» — второй экземпляр бота с тем же токеном, мс
    ///   (TTgBot.PollConflictNotifyIntervalMs). По умолчанию
    ///   TgDefaultConflictNotifyMs.
    /// </summary>
    property ConflictNotifyIntervalMs: Cardinal read FConflictNotifyIntervalMs
      write SetConflictNotifyIntervalMs default TgDefaultConflictNotifyMs;
  end;

  /// <summary>
  ///   HTTP-прокси бота (TTgHttpSettings.Proxy, см. TTgProxySettings); пустой
  ///   Host — без прокси. Для https:// прокси должен поддерживать CONNECT.
  ///   Только HTTP-прокси: SOCKS не поддерживается. Порт обязателен — в Port
  ///   или в Host ('хост:порт'); неверные настройки — ETgError при Active.
  ///   Password хранится в DFM открытым текстом — задавайте его в коде.
  /// </summary>
  TTgProxyOptions = class(TPersistent)
  private
    FOwner: TTelegramBot;
    FHost: string;
    FPort: Integer;
    FUserName: string;
    FPassword: string;
    procedure SetHost(const AValue: string);
    procedure SetPort(AValue: Integer);
    procedure SetUserName(const AValue: string);
    procedure SetPassword(const AValue: string);
  protected
    function GetOwner: TPersistent; override;
  public
    constructor Create(AOwner: TTelegramBot);
    procedure Assign(Source: TPersistent); override;
    /// <summary>Настройки прокси транспорта.</summary>
    function ToSettings: TTgProxySettings;
  published
    property Host: string read FHost write SetHost;
    property Port: Integer read FPort write SetPort default 0;
    property UserName: string read FUserName write SetUserName;
    property Password: string read FPassword write SetPassword;
  end;

  /// <summary>
  ///   Команда бота: '/Command' и синонимы Aliases (через запятую). Description
  ///   непустое — пункт меню (setMyCommands при запуске). Без OnExecute
  ///   команда уходит в OnCommand компонента (нет и его — дальше как текст).
  /// </summary>
  TTgCommandItem = class(TCollectionItem)
  private
    FCommand: string;
    FDescription: string;
    FAliases: string;
    FOnExecute: TTgCommandEvent;
    procedure CheckInactive;
    procedure SetCommand(const AValue: string);
    procedure SetDescription(const AValue: string);
    procedure SetAliases(const AValue: string);
    procedure SetOnExecute(const AValue: TTgCommandEvent);
  protected
    function GetDisplayName: string; override;
  public
    procedure Assign(Source: TPersistent); override;
    /// <summary>Command и непустые Aliases (без крайних пробелов).</summary>
    function Names: TArray<string>;
  published
    property Command: string read FCommand write SetCommand;
    property Description: string read FDescription write SetDescription;
    property Aliases: string read FAliases write SetAliases;
    property OnExecute: TTgCommandEvent read FOnExecute write SetOnExecute;
  end;

  /// <summary>Коллекция команд TTelegramBot.Commands.</summary>
  TTgCommandItems = class(TOwnedCollection)
  private
    function GetItem(AIndex: Integer): TTgCommandItem;
    procedure SetItem(AIndex: Integer; AValue: TTgCommandItem);
  protected
    procedure Notify(Item: TCollectionItem; Action: TCollectionNotification); override;
  public
    constructor Create(AOwner: TTelegramBot);
    function Add: TTgCommandItem;
    property Items[AIndex: Integer]: TTgCommandItem read GetItem write SetItem; default;
  end;

  /// <summary>
  ///   Компонент Telegram-бота (long polling или webhook). Свойства, влияющие на бота,
  ///   при работе (Active) менять нельзя — ETgError (в дизайнере — можно);
  ///   события можно переназначать на ходу.
  ///
  ///   Active, сохранённый в форме, запускает бота после загрузки формы
  ///   отложенно (TThread.ForceQueue): OnCreate формы успевает задать Token;
  ///   ошибка такого запуска — OnError(E, nil), без OnError — исключение в
  ///   обработчике очереди (ApplicationHandleException), а не в загрузчике.
  ///
  ///   Destroy сначала отцепляет события (обработчик, вернувшийся после
  ///   освобождения формы, их не вызовет), затем освобождает бота.
  /// </summary>
{$IF Declared(pidAndroidArm32)}
  [ComponentPlatformsAttribute(pidWin32 or pidWin64 or pidLinux64 or pidAndroidArm32 or pidAndroidArm64)]
{$ELSE}
  [ComponentPlatformsAttribute(pidWin32 or pidWin64 or pidLinux64 or pidAndroid32Arm or pidAndroid64Arm)]
{$ENDIF}
  TTelegramBot = class(TComponent)
  private
    FBot: TTgBot;
    // Номер запуска: увеличивается при каждом создании бота (StartBot).
    // Отложенные события (очередь главного потока) сверяют номер, а не
    // указатель бота: новый TTgBot может занять адрес освобождённого.
    FBotGeneration: Integer;
    // Связь замыканий бота с компонентом: Owner = nil после Destroy.
    // Удерживается замыканиями и очередью главного потока.
    FLink: ITgOwnerLink;
    FTransport: ITgTransport;
    FToken: string;
    FTokenEnv: string;
    FDesignActive: Boolean;
    FStreamedActive: Boolean;
    FStartPending: Boolean;
    FStopping: Boolean;
    FDelivery: TTgDelivery;
    FMaxParallel: Integer;
    FAllowedUpdates: string;
    FPollingTimeout: Integer;
    FPolling: TTgPollingOptions;
    FDropPendingUpdates: Boolean;
    FAutoAnswerCallbacks: Boolean;
    FSetMyCommandsOnStart: Boolean;
    FApiUrl: string;
    FLocalMode: Boolean;
    FProxy: TTgProxyOptions;
    FCommands: TTgCommandItems;
    FMode: TTgReceiveMode;
    FWebhook: TTgWebhookOptions;
    // Приёмник webhook работающего бота: HandleWebhook из потоков сервера
    // берёт ссылку под блокировкой (бот может освобождаться в главном потоке).
    FReceiverLock: TCriticalSection;
    FReceiver: ITgWebhookReceiver;
    // Сервер и путь, у которых зарегистрирован работающий бот.
    FRegisteredServer: TTgCustomWebhookServer;
    FRegisteredPath: string;
    FRegistrations: TList<TProc<TTgBot>>;
    // Run: запрос завершения (RequestStop), пробуждение ожидания не в главном
    // потоке, число отказов (DispatchFault) — итог Run.
    FRunStopFlag: Integer;
    FRunWake: TEvent;
    FFaultCount: Integer;
    FOnStart: TNotifyEvent;
    FOnStop: TTgStopEvent;
    FOnWebhookRegistered: TNotifyEvent;
    FOnUpdate: TTgUpdateEvent;
    FOnMessage: TTgContextEvent;
    FOnCommand: TTgCommandEvent;
    FOnCallbackQuery: TTgContextEvent;
    FOnError: TTgErrorEvent;
    FOnFault: TTgFaultEvent;
    function GetActive: Boolean;
    procedure SetActive(AValue: Boolean);
    function GetApi: TTgApi;
    function GetState: TTgBotState;
    function IsApiUrlStored: Boolean;
    function IsTokenEnvStored: Boolean;
    procedure SetToken(const AValue: string);
    procedure SetTokenEnv(const AValue: string);
    procedure SetTransport(const AValue: ITgTransport);
    procedure SetDelivery(AValue: TTgDelivery);
    procedure SetMaxParallel(AValue: Integer);
    procedure SetAllowedUpdates(const AValue: string);
    procedure SetPollingTimeout(AValue: Integer);
    procedure SetPolling(AValue: TTgPollingOptions);
    procedure SetDropPendingUpdates(AValue: Boolean);
    procedure SetAutoAnswerCallbacks(AValue: Boolean);
    procedure SetSetMyCommandsOnStart(AValue: Boolean);
    procedure SetApiUrl(const AValue: string);
    procedure SetLocalMode(AValue: Boolean);
    procedure SetProxy(AValue: TTgProxyOptions);
    procedure SetCommands(AValue: TTgCommandItems);
    procedure SetMode(AValue: TTgReceiveMode);
    procedure SetWebhook(AValue: TTgWebhookOptions);
    function GetReceiver: ITgWebhookReceiver;
    procedure SetReceiver(const AValue: ITgWebhookReceiver);
    /// <summary>Регистрирует бота у Webhook.Server (если задан).</summary>
    procedure RegisterWithServer;
    /// <summary>Снимает регистрацию у сервера, если она была.</summary>
    procedure UnregisterFromServer;
    /// <summary>Отцепляет приёмник и сервер, освобождает ABot (уже остановленный).</summary>
    procedure ReleaseBot(ABot: TTgBot);
    procedure SetOnUpdate(const AValue: TTgUpdateEvent);
    procedure SetOnMessage(const AValue: TTgContextEvent);
    procedure SetOnCommand(const AValue: TTgCommandEvent);
    procedure SetOnCallbackQuery(const AValue: TTgContextEvent);
    /// <summary>Назначает обработчики бота по назначенным событиям компонента.</summary>
    procedure ApplyEvents(ABot: TTgBot);
    procedure StartBot;
    procedure StopBot(AReason: TTgStopReason);
    procedure StartDeferred;
    /// <summary>Применяет регистрацию к работающему боту и сохраняет для следующих запусков.</summary>
    procedure AddRegistration(const AProc: TProc<TTgBot>);
    procedure DispatchError(AError: Exception; const ACtx: ITgContext);
    /// <summary>AGeneration — номер запуска отказавшего бота (FBotGeneration).</summary>
    procedure DispatchFault(AGeneration: Integer; AError: Exception);
    procedure FaultInMainThread(AGeneration: Integer; AError: Exception);
    procedure DispatchWebhookRegistered(AGeneration: Integer);
    /// <summary>Webhook.Server задан, а Path и Name пусты — ETgError.</summary>
    procedure CheckWebhookPath;
    /// <summary>Run продолжает ждать: бот есть и (Main) не освобождён после отказа / (Worker) не Faulted.</summary>
    function RunAlive: Boolean;
  protected
    procedure Loaded; override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    /// <summary>
    ///   Создаёт внутреннего бота: с Transport (если задан) или с настройками
    ///   из Token/TokenEnv, ApiUrl, LocalMode, Proxy. Точка подмены для тестов.
    /// </summary>
    function CreateBot: TTgBot; virtual;
    /// <summary>Переносит свойства, команды, регистрации и события в ABot.</summary>
    procedure ConfigureBot(ABot: TTgBot); virtual;
    /// <summary>ETgError, если бот работает (вне дизайнера и загрузки).</summary>
    procedure CheckInactive;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    /// <summary>То же, что Active := True.</summary>
    procedure Start;
    /// <summary>То же, что Active := False.</summary>
    procedure Stop;
    /// <summary>
    ///   Блокирующий запуск для консоли и служб (как TTgBot.Run): Start
    ///   (если не Active), цикл CheckSynchronize(100) — события Delivery =
    ///   Main доставляются здесь — до RequestStop, Ctrl+C/закрытия
    ///   консоли/SIGINT/SIGTERM или отказа приёма (Faulted), затем
    ///   остановка. True — остановлен по запросу или сигналу (OnStop
    ///   (Requested)); False — завершён отказом (OnFault и OnStop(Fault)
    ///   уже вызваны). Ошибка запуска — исключение. Delivery = Main — только
    ///   из главного потока (иначе ETgError); на Android — ETgError.
    /// </summary>
    function Run: Boolean;
    /// <summary>Просит Run завершиться (из любого потока, в т.ч. из обработчика).</summary>
    procedure RequestStop;
    /// <summary>Команда (см. TTgBot.Command); регистрация сохраняется между запусками.</summary>
    function Command(const AName: string; const AHandler: TProc<ITgContext>): TTelegramBot; overload;
    /// <summary>Команда с описанием для меню.</summary>
    function Command(const AName, ADescription: string;
      const AHandler: TProc<ITgContext>): TTelegramBot; overload;
    /// <summary>Несколько имён одной команды; в меню — первое (если ADescription непусто).</summary>
    function Command(const ANames: array of string; const ADescription: string;
      const AHandler: TProc<ITgContext>): TTelegramBot; overload;
    /// <summary>Нажатие кнопки с callback data = AData.</summary>
    function Callback(const AData: string; const AHandler: TProc<ITgContext>): TTelegramBot;
    /// <summary>Нажатие кнопки с callback data, начинающимися с APrefix.</summary>
    function CallbackPrefix(const APrefix: string; const AHandler: TProc<ITgContext>): TTelegramBot;
    /// <summary>Любой текст, не обработанный предыдущими правилами.</summary>
    function Text(const AHandler: TProc<ITgContext>): TTelegramBot; overload;
    /// <summary>Текст AText (без учёта регистра).</summary>
    function Text(const AText: string; const AHandler: TProc<ITgContext>): TTelegramBot; overload;
    /// <summary>Регулярное выражение (неверный шаблон — исключение здесь же).</summary>
    function TextMatch(const APattern: string; const AHandler: TProc<ITgContext>): TTelegramBot;
    /// <summary>Удаляет все регистрации из кода (действует со следующего запуска).</summary>
    procedure ClearRegistrations;
    /// <summary>
    ///   Тело webhook-запроса (Mode = Webhook) из HTTP-сервера приложения:
    ///   ABody — тело POST, ASecretHeader — заголовок
    ///   X-Telegram-Bot-Api-Secret-Token. Ответ серверу Telegram —
    ///   TgWebhookHttpStatus(результат). Потокобезопасно из любых потоков, в
    ///   т.ч. во время Active := False; бот не запущен — Unavailable (503).
    /// </summary>
    function HandleWebhook(const ABody, ASecretHeader: string): TTgWebhookResult; overload;
    /// <summary>То же для тела в байтах UTF-8.</summary>
    function HandleWebhook(const ABody: TBytes; const ASecretHeader: string): TTgWebhookResult; overload;
    /// <summary>Внутренний бот (тонкие настройки, StateStorage…) или nil, если не запущен.</summary>
    property Bot: TTgBot read FBot;
    /// <summary>Клиент Bot API работающего бота или nil.</summary>
    property Api: TTgApi read GetApi;
    /// <summary>Состояние бота (Idle, если не запущен).</summary>
    property State: TTgBotState read GetState;
    /// <summary>
    ///   Внешний транспорт (общий или тестовый): если задан, Token, ApiUrl,
    ///   LocalMode и Proxy не используются.
    /// </summary>
    property Transport: ITgTransport read FTransport write SetTransport;
  published
    /// <summary>
    ///   Бот работает. В дизайнере только запоминается; при загрузке формы —
    ///   отложенный запуск. Чтение в работе — по состоянию бота (Faulted — False).
    /// </summary>
    property Active: Boolean read GetActive write SetActive default False;
    /// <summary>Токен бота; пустой — берётся из переменной окружения TokenEnv.</summary>
    property Token: string read FToken write SetToken;
    /// <summary>Переменная окружения с токеном (по умолчанию TGBOT_TOKEN).</summary>
    property TokenEnv: string read FTokenEnv write SetTokenEnv stored IsTokenEnvStored;
    /// <summary>Где вызываются обработчики (по умолчанию Main — главный поток).</summary>
    property Delivery: TTgDelivery read FDelivery write SetDelivery default TTgDelivery.Main;
    /// <summary>Число потоков обработчиков (Delivery = Worker).</summary>
    property MaxParallel: Integer read FMaxParallel write SetMaxParallel default TgDefaultMaxParallel;
    /// <summary>
    ///   allowed_updates через запятую ('message,callback_query'); пусто — все
    ///   типы, кроме chat_member и реакций.
    /// </summary>
    property AllowedUpdates: string read FAllowedUpdates write SetAllowedUpdates;
    /// <summary>timeout getUpdates, с.</summary>
    property PollingTimeout: Integer read FPollingTimeout write SetPollingTimeout
      default TgDefaultPollTimeoutSec;
    /// <summary>
    ///   Тонкие настройки long polling (Mode = Polling): Limit,
    ///   JitterPercent, ConflictNotifyIntervalMs.
    /// </summary>
    property Polling: TTgPollingOptions read FPolling write SetPolling;
    /// <summary>Пропустить накопившиеся обновления при запуске.</summary>
    property DropPendingUpdates: Boolean read FDropPendingUpdates write SetDropPendingUpdates
      default False;
    /// <summary>Подтверждать неотвеченные нажатия кнопок пустым ответом.</summary>
    property AutoAnswerCallbacks: Boolean read FAutoAnswerCallbacks write SetAutoAnswerCallbacks
      default True;
    /// <summary>setMyCommands при запуске (команды с описанием).</summary>
    property SetMyCommandsOnStart: Boolean read FSetMyCommandsOnStart write SetSetMyCommandsOnStart
      default True;
    /// <summary>Адрес Bot API (Local Bot API server); по умолчанию облачный.</summary>
    property ApiUrl: string read FApiUrl write SetApiUrl stored IsApiUrlStored;
    /// <summary>Local Bot API server на той же машине (DownloadFile с диска).</summary>
    property LocalMode: Boolean read FLocalMode write SetLocalMode default False;
    /// <summary>HTTP(S)-прокси.</summary>
    property Proxy: TTgProxyOptions read FProxy write SetProxy;
    /// <summary>Команды бота (регистрируются при каждом запуске).</summary>
    property Commands: TTgCommandItems read FCommands write SetCommands;
    /// <summary>Способ получения обновлений: Polling (по умолчанию) или Webhook.</summary>
    property Mode: TTgReceiveMode read FMode write SetMode default TTgReceiveMode.Polling;
    /// <summary>Настройки webhook (Mode = Webhook).</summary>
    property Webhook: TTgWebhookOptions read FWebhook write SetWebhook;
    /// <summary>
    ///   Бот запущен (в вызывающем потоке, после запуска). В Mode = Webhook
    ///   вызывается до регистрации webhook (setWebhook идёт в фоне) — её
    ///   итог: OnWebhookRegistered или OnError + OnFault.
    /// </summary>
    property OnStart: TNotifyEvent read FOnStart write FOnStart;
    /// <summary>
    ///   Webhook зарегистрирован (setWebhook при запуске выполнен успешно).
    ///   Delivery = Main — в главном потоке через очередь, всегда после
    ///   OnStart; Worker — в служебном потоке webhook-источника (может
    ///   прийти раньше OnStart). Не вызывается, если бот уже остановлен.
    /// </summary>
    property OnWebhookRegistered: TNotifyEvent read FOnWebhookRegistered write FOnWebhookRegistered;
    /// <summary>Бот остановлен: Requested — Active := False/Stop; Fault — отказ приёма.</summary>
    property OnStop: TTgStopEvent read FOnStop write FOnStop;
    /// <summary>Каждое обновление до маршрутизатора; Handled := True — перехват.</summary>
    property OnUpdate: TTgUpdateEvent read FOnUpdate write SetOnUpdate;
    /// <summary>Сообщение, не обработанное командами и правилами текста.</summary>
    property OnMessage: TTgContextEvent read FOnMessage write SetOnMessage;
    /// <summary>
    ///   Команда этому боту без своего обработчика (нет в Commands или у
    ///   элемента нет OnExecute): Ctx.Command, Ctx.Args.
    /// </summary>
    property OnCommand: TTgCommandEvent read FOnCommand write SetOnCommand;
    /// <summary>Нажатие кнопки, не обработанное правилами Callback.</summary>
    property OnCallbackQuery: TTgContextEvent read FOnCallbackQuery write SetOnCallbackQuery;
    /// <summary>
    ///   Ошибка обработчика (Ctx задан), приёма, getMe/setMyCommands или
    ///   отложенного запуска (Ctx = nil). Delivery = Main — в главном потоке
    ///   (ошибки фоновых потоков — копия исключения через TThread.Queue,
    ///   действительна только внутри обработчика).
    /// </summary>
    property OnError: TTgErrorEvent read FOnError write FOnError;
    /// <summary>
    ///   Неустранимая ошибка приёма (после OnError). Delivery = Main — в
    ///   главном потоке, затем бот освобождается и вызывается OnStop(Fault).
    /// </summary>
    property OnFault: TTgFaultEvent read FOnFault write FOnFault;
  end;

  /// <summary>
  ///   Базовый компонент HTTP(S)-сервера webhook для TTelegramBot.Webhook.Server
  ///   (реализация — в наследнике). Бот в Mode = Webhook при запуске вызывает
  ///   RegisterBot(Path, Self), при остановке и уничтожении — UnregisterBot.
  ///   Сервер на запрос POST по пути APath передаёт тело и заголовок
  ///   X-Telegram-Bot-Api-Secret-Token в ABot.HandleWebhook и отвечает кодом
  ///   TgWebhookHttpStatus(результат); неизвестный путь — 404.
  ///   Вызовы Register/Unregister — из потока, управляющего ботом (обычно
  ///   главного); HandleWebhook бота потокобезопасен.
  /// </summary>
  TTgCustomWebhookServer = class(TComponent)
  public
    /// <summary>Начать направлять запросы по пути APath боту ABot.</summary>
    procedure RegisterBot(const APath: string; ABot: TTelegramBot); virtual; abstract;
    /// <summary>Перестать направлять запросы по пути APath (неизвестная пара — ничего).</summary>
    procedure UnregisterBot(const APath: string; ABot: TTelegramBot); virtual; abstract;
    /// <summary>
    ///   Внешний HTTPS-URL для пути APath (для Webhook.Url по умолчанию);
    ///   '' — неизвестен (базовая реализация): Webhook.Url нужно задать явно.
    /// </summary>
    function GetWebhookUrl(const APath: string): string; virtual;
  end;

implementation

uses
  System.Diagnostics,
  System.RegularExpressions,
  TgBot.Consts;

const
  CDefaultTokenEnv = 'TGBOT_TOKEN';

/// <summary>
///   Компонент по связи замыкания (атомарное чтение); nil — компонент
///   уничтожен. Владелец связи — всегда TTelegramBot (TgNewOwnerLink(Self)).
/// </summary>
function LinkOwner(const ALink: ITgOwnerLink): TTelegramBot;
begin
  Result := TTelegramBot(ALink.Owner);
end;

/// <summary>
///   Копия исключения для доставки через очередь: оригинал принадлежит
///   потоку, который его выбросил, и освобождается сразу после возврата.
///   Класс сохраняется; ETgApiError/ETgConflictError — со всеми полями.
/// </summary>
function CloneException(AError: Exception): Exception;
var
  LApi: ETgApiError;
begin
  if AError is ETgApiError then
  begin
    LApi := ETgApiError(AError);
    if AError is ETgConflictError then
      Result := ETgConflictError.Create(LApi.Method, LApi.ErrorCode, LApi.Description,
        LApi.RetryAfter, LApi.MigrateToChatId)
    else
      Result := ETgApiError.Create(LApi.Method, LApi.ErrorCode, LApi.Description,
        LApi.RetryAfter, LApi.MigrateToChatId);
  end
  else
    Result := ExceptClass(AError.ClassType).Create(AError.Message);
  Result.Message := AError.Message;
end;

/// <summary>Разбивает строку через запятую: без крайних пробелов, без пустых.</summary>
function SplitList(const AValue: string): TArray<string>;
var
  LPart: string;
begin
  Result := nil;
  for LPart in AValue.Split([',']) do
    if Trim(LPart) <> '' then
      Result := Result + [Trim(LPart)];
end;

/// <summary>Проверка имени команды как у TTgBot.Command (до сохранения регистрации).</summary>
procedure CheckCommandName(const AName: string);
var
  LName: string;
  C: Char;
begin
  LName := AName;
  if Copy(LName, 1, 1) = '/' then
    Delete(LName, 1, 1);
  if LName = '' then
    raise ETgError.Create(TgLangTextFmt(@SRuRouteEmptyKey, @SEnRouteEmptyKey, ['Command']));
  for C in LName do
    if (C <= ' ') or (C = '@') then
      raise ETgError.Create(TgLangTextFmt(@SRuRouteBadCommand, @SEnRouteBadCommand, [AName]));
end;

procedure CheckRuleKey(const AKey, ARule: string);
begin
  if AKey = '' then
    raise ETgError.Create(TgLangTextFmt(@SRuRouteEmptyKey, @SEnRouteEmptyKey, [ARule]));
end;

{ Обработчики внутреннего бота: захватывают только связь с компонентом }

function NewUpdateHandler(const ALink: ITgOwnerLink): TProc<ITgContext>;
begin
  Result :=
    procedure(ACtx: ITgContext)
    var
      LOwner: TTelegramBot;
      LEvent: TTgUpdateEvent;
      LHandled: Boolean;
    begin
      LOwner := LinkOwner(ALink);
      if not Assigned(LOwner) then
        Exit;
      LEvent := LOwner.FOnUpdate;
      if not Assigned(LEvent) then
        Exit;
      LHandled := ACtx.Handled;
      LEvent(LOwner, ACtx, LHandled);
      ACtx.Handled := LHandled;
    end;
end;

/// <summary>AKind: 0 — OnMessage, 1 — OnCallbackQuery, 2 — OnCommand.</summary>
function NewContextHandler(const ALink: ITgOwnerLink; AKind: Integer): TProc<ITgContext>;
begin
  Result :=
    procedure(ACtx: ITgContext)
    var
      LOwner: TTelegramBot;
      LEvent: TTgContextEvent;
    begin
      LOwner := LinkOwner(ALink);
      if not Assigned(LOwner) then
        Exit;
      case AKind of
        0: LEvent := LOwner.FOnMessage;
        1: LEvent := LOwner.FOnCallbackQuery;
      else
        LEvent := TTgContextEvent(LOwner.FOnCommand);
      end;
      if Assigned(LEvent) then
        LEvent(LOwner, ACtx)
      else if AKind = 2 then
        // OnCommand снят на ходу — команда идёт дальше как текст.
        ACtx.Handled := False;
    end;
end;

/// <summary>Элемент Commands: AEvent (снимок при запуске) или OnCommand компонента.</summary>
function NewCommandHandler(const ALink: ITgOwnerLink; const AEvent: TTgCommandEvent): TProc<ITgContext>;
begin
  Result :=
    procedure(ACtx: ITgContext)
    var
      LOwner: TTelegramBot;
      LEvent: TTgCommandEvent;
    begin
      LOwner := LinkOwner(ALink);
      if not Assigned(LOwner) then
        Exit;
      LEvent := AEvent;
      if not Assigned(LEvent) then
        LEvent := LOwner.FOnCommand;
      if Assigned(LEvent) then
        LEvent(LOwner, ACtx)
      else
        ACtx.Handled := False;
    end;
end;

function NewErrorHandler(const ALink: ITgOwnerLink): TProc<Exception, ITgContext>;
begin
  Result :=
    procedure(AError: Exception; ACtx: ITgContext)
    var
      LOwner: TTelegramBot;
    begin
      LOwner := LinkOwner(ALink);
      if Assigned(LOwner) then
        LOwner.DispatchError(AError, ACtx);
    end;
end;

/// <summary>AGeneration — номер запуска бота, которому назначается обработчик.</summary>
function NewFaultHandler(const ALink: ITgOwnerLink; AGeneration: Integer): TProc<Exception>;
begin
  Result :=
    procedure(AError: Exception)
    var
      LOwner: TTelegramBot;
    begin
      LOwner := LinkOwner(ALink);
      if Assigned(LOwner) then
        LOwner.DispatchFault(AGeneration, AError);
    end;
end;

/// <summary>AGeneration — номер запуска бота, которому назначается обработчик.</summary>
function NewWebhookRegisteredHandler(const ALink: ITgOwnerLink; AGeneration: Integer): TProc;
begin
  Result :=
    procedure
    var
      LOwner: TTelegramBot;
    begin
      LOwner := LinkOwner(ALink);
      if Assigned(LOwner) then
        LOwner.DispatchWebhookRegistered(AGeneration);
    end;
end;

{ TTgProxyOptions }

constructor TTgProxyOptions.Create(AOwner: TTelegramBot);
begin
  inherited Create;
  FOwner := AOwner;
end;

function TTgProxyOptions.GetOwner: TPersistent;
begin
  Result := FOwner;
end;

procedure TTgProxyOptions.Assign(Source: TPersistent);
var
  LSource: TTgProxyOptions;
begin
  if Source is TTgProxyOptions then
  begin
    FOwner.CheckInactive;
    LSource := TTgProxyOptions(Source);
    FHost := LSource.FHost;
    FPort := LSource.FPort;
    FUserName := LSource.FUserName;
    FPassword := LSource.FPassword;
  end
  else
    inherited Assign(Source);
end;

function TTgProxyOptions.ToSettings: TTgProxySettings;
begin
  Result := TTgProxySettings.Create(Trim(FHost), FPort, FUserName, FPassword);
end;

procedure TTgProxyOptions.SetHost(const AValue: string);
begin
  FOwner.CheckInactive;
  FHost := AValue;
end;

procedure TTgProxyOptions.SetPort(AValue: Integer);
begin
  FOwner.CheckInactive;
  FPort := AValue;
end;

procedure TTgProxyOptions.SetUserName(const AValue: string);
begin
  FOwner.CheckInactive;
  FUserName := AValue;
end;

procedure TTgProxyOptions.SetPassword(const AValue: string);
begin
  FOwner.CheckInactive;
  FPassword := AValue;
end;

{ TTgWebhookOptions }

constructor TTgWebhookOptions.Create(AOwner: TTelegramBot);
begin
  inherited Create;
  FOwner := AOwner;
  FMaxBodySize := TgDefaultWebhookMaxBodySize;
  FPostTimeoutMs := TgDefaultWebhookPostTimeoutMs;
  FDedupWindow := TgDefaultWebhookDedupWindow;
  FRegisterOnStart := True;
end;

function TTgWebhookOptions.GetOwner: TPersistent;
begin
  Result := FOwner;
end;

procedure TTgWebhookOptions.Assign(Source: TPersistent);
var
  LSource: TTgWebhookOptions;
begin
  if Source is TTgWebhookOptions then
  begin
    FOwner.CheckInactive;
    LSource := TTgWebhookOptions(Source);
    FUrl := LSource.FUrl;
    FSecretToken := LSource.FSecretToken;
    FMaxConnections := LSource.FMaxConnections;
    FDropPendingUpdates := LSource.FDropPendingUpdates;
    FDeleteOnStop := LSource.FDeleteOnStop;
    FPath := LSource.FPath;
    FIpAddress := LSource.FIpAddress;
    FCertificate := LSource.FCertificate;
    FMaxBodySize := LSource.FMaxBodySize;
    FPostTimeoutMs := LSource.FPostTimeoutMs;
    FDedupWindow := LSource.FDedupWindow;
    FRegisterOnStart := LSource.FRegisterOnStart;
    SetServer(LSource.FServer);
  end
  else
    inherited Assign(Source);
end;

function TTgWebhookOptions.EffectiveUrl: string;
begin
  Result := Trim(FUrl);
  if (Result = '') and Assigned(FServer) then
    Result := Trim(FServer.GetWebhookUrl(GetPath));
end;

procedure TTgWebhookOptions.SetUrl(const AValue: string);
begin
  FOwner.CheckInactive;
  FUrl := AValue;
end;

procedure TTgWebhookOptions.SetIpAddress(const AValue: string);
begin
  FOwner.CheckInactive;
  FIpAddress := AValue;
end;

procedure TTgWebhookOptions.SetCertificate(const AValue: string);
begin
  FOwner.CheckInactive;
  FCertificate := AValue;
end;

procedure TTgWebhookOptions.SetSecretToken(const AValue: string);
begin
  FOwner.CheckInactive;
  FSecretToken := AValue;
end;

procedure TTgWebhookOptions.SetMaxConnections(AValue: Integer);
begin
  FOwner.CheckInactive;
  FMaxConnections := AValue;
end;

procedure TTgWebhookOptions.SetDropPendingUpdates(AValue: Boolean);
begin
  FOwner.CheckInactive;
  FDropPendingUpdates := AValue;
end;

procedure TTgWebhookOptions.SetDeleteOnStop(AValue: Boolean);
begin
  FOwner.CheckInactive;
  FDeleteOnStop := AValue;
end;

procedure TTgWebhookOptions.SetMaxBodySize(AValue: Integer);
begin
  FOwner.CheckInactive;
  FMaxBodySize := AValue;
end;

procedure TTgWebhookOptions.SetPostTimeoutMs(AValue: Cardinal);
begin
  FOwner.CheckInactive;
  FPostTimeoutMs := AValue;
end;

procedure TTgWebhookOptions.SetDedupWindow(AValue: Integer);
begin
  FOwner.CheckInactive;
  FDedupWindow := AValue;
end;

procedure TTgWebhookOptions.SetRegisterOnStart(AValue: Boolean);
begin
  FOwner.CheckInactive;
  FRegisterOnStart := AValue;
end;

procedure TTgWebhookOptions.SetServer(AValue: TTgCustomWebhookServer);
begin
  if AValue = FServer then
    Exit;
  FOwner.CheckInactive;
  // Отказавший (Faulted) бот ещё зарегистрирован у прежнего сервера.
  FOwner.UnregisterFromServer;
  if Assigned(FServer) then
    FServer.RemoveFreeNotification(FOwner);
  FServer := AValue;
  // Уничтожение сервера (в т.ч. на другой форме) обнуляет ссылку (Notification).
  if Assigned(FServer) then
    FServer.FreeNotification(FOwner);
end;

function TTgWebhookOptions.GetPath: string;
begin
  if FPath <> '' then
    Result := FPath
  else
    Result := '/tg/' + FOwner.Name;
end;

procedure TTgWebhookOptions.SetPath(const AValue: string);
begin
  FOwner.CheckInactive;
  // Значение по умолчанию не фиксируется: следует за переименованием компонента.
  if AValue = '/tg/' + FOwner.Name then
    FPath := ''
  else
    FPath := AValue;
end;

function TTgWebhookOptions.IsPathStored: Boolean;
begin
  Result := FPath <> '';
end;

{ TTgPollingOptions }

constructor TTgPollingOptions.Create(AOwner: TTelegramBot);
begin
  inherited Create;
  FOwner := AOwner;
  FLimit := TgDefaultPollLimit;
  FJitterPercent := TgDefaultBackoffJitterPercent;
  FConflictNotifyIntervalMs := TgDefaultConflictNotifyMs;
end;

function TTgPollingOptions.GetOwner: TPersistent;
begin
  Result := FOwner;
end;

procedure TTgPollingOptions.Assign(Source: TPersistent);
var
  LSource: TTgPollingOptions;
begin
  if Source is TTgPollingOptions then
  begin
    FOwner.CheckInactive;
    LSource := TTgPollingOptions(Source);
    FLimit := LSource.FLimit;
    FJitterPercent := LSource.FJitterPercent;
    FConflictNotifyIntervalMs := LSource.FConflictNotifyIntervalMs;
  end
  else
    inherited Assign(Source);
end;

procedure TTgPollingOptions.SetLimit(AValue: Integer);
begin
  FOwner.CheckInactive;
  FLimit := AValue;
end;

procedure TTgPollingOptions.SetJitterPercent(AValue: Integer);
begin
  FOwner.CheckInactive;
  FJitterPercent := AValue;
end;

procedure TTgPollingOptions.SetConflictNotifyIntervalMs(AValue: Cardinal);
begin
  FOwner.CheckInactive;
  FConflictNotifyIntervalMs := AValue;
end;

{ TTgCustomWebhookServer }

function TTgCustomWebhookServer.GetWebhookUrl(const APath: string): string;
begin
  Result := '';
end;

{ TTgCommandItem }

procedure TTgCommandItem.CheckInactive;
begin
  if Assigned(Collection) and (Collection.Owner is TTelegramBot) then
    TTelegramBot(Collection.Owner).CheckInactive;
end;

function TTgCommandItem.GetDisplayName: string;
begin
  if FCommand = '' then
    Result := inherited GetDisplayName
  else
    Result := '/' + FCommand;
end;

procedure TTgCommandItem.Assign(Source: TPersistent);
var
  LSource: TTgCommandItem;
begin
  if Source is TTgCommandItem then
  begin
    CheckInactive;
    LSource := TTgCommandItem(Source);
    FCommand := LSource.FCommand;
    FDescription := LSource.FDescription;
    FAliases := LSource.FAliases;
    FOnExecute := LSource.FOnExecute;
    Changed(False);
  end
  else
    inherited Assign(Source);
end;

function TTgCommandItem.Names: TArray<string>;
begin
  Result := [Trim(FCommand)] + SplitList(FAliases);
end;

procedure TTgCommandItem.SetCommand(const AValue: string);
begin
  CheckInactive;
  FCommand := AValue;
  Changed(False);
end;

procedure TTgCommandItem.SetDescription(const AValue: string);
begin
  CheckInactive;
  FDescription := AValue;
end;

procedure TTgCommandItem.SetAliases(const AValue: string);
begin
  CheckInactive;
  FAliases := AValue;
end;

procedure TTgCommandItem.SetOnExecute(const AValue: TTgCommandEvent);
begin
  CheckInactive;
  FOnExecute := AValue;
end;

{ TTgCommandItems }

constructor TTgCommandItems.Create(AOwner: TTelegramBot);
begin
  inherited Create(AOwner, TTgCommandItem);
end;

function TTgCommandItems.Add: TTgCommandItem;
begin
  Result := TTgCommandItem(inherited Add);
end;

function TTgCommandItems.GetItem(AIndex: Integer): TTgCommandItem;
begin
  Result := TTgCommandItem(inherited GetItem(AIndex));
end;

procedure TTgCommandItems.SetItem(AIndex: Integer; AValue: TTgCommandItem);
begin
  inherited SetItem(AIndex, AValue);
end;

procedure TTgCommandItems.Notify(Item: TCollectionItem; Action: TCollectionNotification);
begin
  // Добавление при работе — ETgError (элемент удаляется конструктором).
  // Удаление не проверяется: исключение из деструктора элемента недопустимо;
  // оно, как и любая правка коллекции, действует со следующего запуска.
  if (Action = cnAdded) and (Owner is TTelegramBot) then
    TTelegramBot(Owner).CheckInactive;
  inherited Notify(Item, Action);
end;

{ TTelegramBot }

constructor TTelegramBot.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FLink := TgNewOwnerLink(Self);
  FTokenEnv := CDefaultTokenEnv;
  FDelivery := TTgDelivery.Main;
  FMaxParallel := TgDefaultMaxParallel;
  FPollingTimeout := TgDefaultPollTimeoutSec;
  FPolling := TTgPollingOptions.Create(Self);
  FAutoAnswerCallbacks := True;
  FSetMyCommandsOnStart := True;
  FApiUrl := TgDefaultApiUrl;
  FProxy := TTgProxyOptions.Create(Self);
  FCommands := TTgCommandItems.Create(Self);
  FMode := TTgReceiveMode.Polling;
  FWebhook := TTgWebhookOptions.Create(Self);
  FReceiverLock := TCriticalSection.Create;
  FRegistrations := TList<TProc<TTgBot>>.Create;
  FRunWake := TEvent.Create(nil, False, False, '');
end;

destructor TTelegramBot.Destroy;
begin
  // Сначала отцепить события: обработчик, вернувшийся позже (зависший
  // дольше Stop), и элементы очереди главного потока видят Owner = nil.
  if Assigned(FLink) then
    FLink.Clear;
  FStartPending := False;
  // Webhook: сервер больше не направляет запросы, HandleWebhook — Unavailable.
  if Assigned(FReceiverLock) then
    SetReceiver(nil);
  UnregisterFromServer;
  // Free бота: Stop (не дольше таймаута), отсоединение ядра.
  FreeAndNil(FBot);
  FLink := nil;
  FreeAndNil(FRegistrations);
  FreeAndNil(FWebhook);
  FreeAndNil(FReceiverLock);
  FreeAndNil(FCommands);
  FreeAndNil(FProxy);
  FreeAndNil(FPolling);
  FreeAndNil(FRunWake);
  inherited Destroy;
end;

procedure TTelegramBot.Notification(AComponent: TComponent; Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);
  if Operation <> opRemove then
    Exit;
  if AComponent = FRegisteredServer then
    FRegisteredServer := nil;
  if Assigned(FWebhook) and (AComponent = FWebhook.FServer) then
    FWebhook.FServer := nil;
end;

function TTelegramBot.GetReceiver: ITgWebhookReceiver;
begin
  FReceiverLock.Enter;
  try
    Result := FReceiver;
  finally
    FReceiverLock.Leave;
  end;
end;

procedure TTelegramBot.SetReceiver(const AValue: ITgWebhookReceiver);
var
  LOld: ITgWebhookReceiver;
begin
  FReceiverLock.Enter;
  try
    LOld := FReceiver;
    FReceiver := AValue;
  finally
    FReceiverLock.Leave;
  end;
  // Прежняя ссылка (LOld) отпускается при выходе — вне блокировки.
end;

procedure TTelegramBot.RegisterWithServer;
var
  LServer: TTgCustomWebhookServer;
  LPath: string;
begin
  LServer := FWebhook.FServer;
  if not Assigned(LServer) then
    Exit;
  LPath := FWebhook.Path;
  LServer.RegisterBot(LPath, Self);
  FRegisteredServer := LServer;
  FRegisteredPath := LPath;
end;

procedure TTelegramBot.UnregisterFromServer;
var
  LServer: TTgCustomWebhookServer;
begin
  LServer := FRegisteredServer;
  if not Assigned(LServer) then
    Exit;
  FRegisteredServer := nil;
  LServer.UnregisterBot(FRegisteredPath, Self);
end;

procedure TTelegramBot.ReleaseBot(ABot: TTgBot);
begin
  SetReceiver(nil);
  UnregisterFromServer;
  if FBot = ABot then
    FBot := nil;
  ABot.Free;
end;

function TTelegramBot.HandleWebhook(const ABody, ASecretHeader: string): TTgWebhookResult;
var
  LReceiver: ITgWebhookReceiver;
begin
  // Ссылка удерживает источник, даже если бот освобождается параллельно.
  LReceiver := GetReceiver;
  if Assigned(LReceiver) then
    Result := LReceiver.Accept(ABody, ASecretHeader)
  else
    Result := TTgWebhookResult.Unavailable;
end;

function TTelegramBot.HandleWebhook(const ABody: TBytes; const ASecretHeader: string): TTgWebhookResult;
var
  LReceiver: ITgWebhookReceiver;
begin
  LReceiver := GetReceiver;
  if Assigned(LReceiver) then
    Result := LReceiver.Accept(ABody, ASecretHeader)
  else
    Result := TTgWebhookResult.Unavailable;
end;

procedure TTelegramBot.CheckInactive;
begin
  if (ComponentState * [csDesigning, csLoading] = []) and Assigned(FBot) and
    (FBot.State in [TTgBotState.Running, TTgBotState.Stopping]) then
    raise ETgError.Create(TgLangText(@SRuCompBotActive, @SEnCompBotActive));
end;

function TTelegramBot.GetActive: Boolean;
begin
  if csDesigning in ComponentState then
    Result := FDesignActive
  else if csLoading in ComponentState then
    Result := FStreamedActive
  else
    Result := Assigned(FBot) and FBot.Active;
end;

procedure TTelegramBot.SetActive(AValue: Boolean);
begin
  if csDesigning in ComponentState then
  begin
    // В дизайнере бот не запускается: значение только сохраняется в форме.
    FDesignActive := AValue;
    Exit;
  end;
  if csLoading in ComponentState then
  begin
    // Запуск — после загрузки (Loaded): Token может задать OnCreate формы.
    FStreamedActive := AValue;
    Exit;
  end;
  // Явная установка отменяет отложенный запуск из формы.
  FStartPending := False;
  if AValue then
  begin
    if not GetActive then
      StartBot;
  end
  else if Assigned(FBot) then
    StopBot(TTgStopReason.Requested);
end;

procedure TTelegramBot.Loaded;
var
  LLink: ITgOwnerLink;
begin
  inherited Loaded;
  if FStreamedActive and not (csDesigning in ComponentState) then
  begin
    FStreamedActive := False;
    FStartPending := True;
    LLink := FLink;
    // ForceQueue — и из главного потока ставит в очередь, а не вызывает сразу.
    TThread.ForceQueue(nil,
      procedure
      var
        LOwner: TTelegramBot;
      begin
        LOwner := LinkOwner(LLink);
        if Assigned(LOwner) then
          LOwner.StartDeferred;
      end);
  end;
end;

procedure TTelegramBot.StartDeferred;
begin
  // Active := True/False после загрузки уже решили судьбу запуска.
  if not FStartPending then
    Exit;
  FStartPending := False;
  try
    StartBot;
  except
    on E: Exception do
      if Assigned(FOnError) then
        FOnError(Self, E, nil)
      else
        raise;
  end;
end;

procedure TTelegramBot.Start;
begin
  SetActive(True);
end;

procedure TTelegramBot.Stop;
begin
  SetActive(False);
end;

function TTelegramBot.CreateBot: TTgBot;
var
  LToken: string;
  LSettings: TTgHttpSettings;
begin
  if Assigned(FTransport) then
    Exit(TTgBot.Create(FTransport));
  LToken := Trim(FToken);
  if (LToken = '') and (Trim(FTokenEnv) <> '') then
    LToken := Trim(GetEnvironmentVariable(Trim(FTokenEnv)));
  // Пустой токен — ETgError транспорта, как у TTgBot.Create.
  LSettings := TTgHttpSettings.Create(LToken);
  if Trim(FApiUrl) <> '' then
    LSettings.ApiUrl := Trim(FApiUrl);
  LSettings.LocalMode := FLocalMode;
  LSettings.Proxy := FProxy.ToSettings;
  Result := TTgBot.Create(LSettings);
end;

procedure TTelegramBot.ConfigureBot(ABot: TTgBot);
var
  LAllowed: TArray<string>;
  LItem: TCollectionItem;
  LCommand: TTgCommandItem;
  LRegistration: TProc<TTgBot>;
begin
  ABot.Delivery := FDelivery;
  ABot.MaxParallel := FMaxParallel;
  ABot.Mode := FMode;
  ABot.WebhookUrl := FWebhook.EffectiveUrl;
  ABot.WebhookSecretToken := FWebhook.SecretToken;
  ABot.WebhookMaxConnections := FWebhook.MaxConnections;
  ABot.WebhookDropPendingUpdates := FWebhook.DropPendingUpdates;
  ABot.WebhookIpAddress := Trim(FWebhook.IpAddress);
  // Публичный ключ самоподписанного сертификата — файлом (multipart). Нужен
  // только setWebhook: без регистрации при запуске файл не используется.
  if (FMode = TTgReceiveMode.Webhook) and FWebhook.RegisterOnStart and
    (Trim(FWebhook.Certificate) <> '') then
  begin
    if not FileExists(Trim(FWebhook.Certificate)) then
      raise ETgError.Create(TgLangTextFmt(@SRuCompNoCertificate, @SEnCompNoCertificate,
        [Trim(FWebhook.Certificate)]));
    ABot.WebhookCertificate := TTgInputFile.FromFile(Trim(FWebhook.Certificate));
  end;
  ABot.DeleteWebhookOnStop := FWebhook.DeleteOnStop;
  ABot.WebhookMaxBodySize := FWebhook.MaxBodySize;
  ABot.WebhookPostTimeoutMs := FWebhook.PostTimeoutMs;
  ABot.WebhookDedupWindow := FWebhook.DedupWindow;
  ABot.WebhookRegisterOnStart := FWebhook.RegisterOnStart;
  ABot.PollTimeout := FPollingTimeout;
  ABot.PollLimit := FPolling.Limit;
  ABot.PollJitterPercent := FPolling.JitterPercent;
  ABot.PollConflictNotifyIntervalMs := FPolling.ConflictNotifyIntervalMs;
  ABot.DropPendingUpdates := FDropPendingUpdates;
  ABot.AutoAnswerCallbacks := FAutoAnswerCallbacks;
  ABot.SetMyCommandsOnStart := FSetMyCommandsOnStart;
  LAllowed := SplitList(FAllowedUpdates);
  if Length(LAllowed) > 0 then
    ABot.AllowedUpdates := LAllowed;
  // Сначала коллекция, затем регистрации из кода (тот же ключ — заменяет).
  for LItem in FCommands do
  begin
    LCommand := TTgCommandItem(LItem);
    ABot.Command(LCommand.Names, Trim(LCommand.Description),
      NewCommandHandler(FLink, LCommand.OnExecute));
  end;
  for LRegistration in FRegistrations do
    LRegistration(ABot);
  ApplyEvents(ABot);
  // Всегда: доставка ошибок и отказа (освобождение бота, OnStop).
  // Отложенные события отказа и регистрации webhook сверяют номер запуска.
  ABot.OnError := NewErrorHandler(FLink);
  ABot.OnFault := NewFaultHandler(FLink, FBotGeneration);
  // Всегда: событие можно назначить и после запуска.
  ABot.OnWebhookRegistered := NewWebhookRegisteredHandler(FLink, FBotGeneration);
end;

procedure TTelegramBot.ApplyEvents(ABot: TTgBot);
begin
  // Только назначенные события: назначенный OnCommand/OnMessage меняет
  // маршрутизацию и предупреждения TTgBot (OnUnknownCommand, AllowedUpdates).
  if Assigned(FOnUpdate) then
    ABot.OnUpdate := NewUpdateHandler(FLink)
  else
    ABot.OnUpdate := nil;
  if Assigned(FOnMessage) then
    ABot.OnMessage := NewContextHandler(FLink, 0)
  else
    ABot.OnMessage := nil;
  if Assigned(FOnCallbackQuery) then
    ABot.OnCallbackQuery := NewContextHandler(FLink, 1)
  else
    ABot.OnCallbackQuery := nil;
  if Assigned(FOnCommand) then
    ABot.OnUnknownCommand := NewContextHandler(FLink, 2)
  else
    ABot.OnUnknownCommand := nil;
end;

procedure TTelegramBot.CheckWebhookPath;
begin
  // Путь нужен только серверу: без Server тело передаёт приложение (HandleWebhook).
  if (FMode = TTgReceiveMode.Webhook) and Assigned(FWebhook.FServer) and
    (Trim(FWebhook.FPath) = '') and (Name = '') then
    raise ETgError.Create(TgLangText(@SRuCompNoWebhookPath, @SEnCompNoWebhookPath));
end;

procedure TTelegramBot.StartBot;
var
  LBot: TTgBot;
begin
  // Проверка настроек — до освобождения прежнего бота.
  CheckWebhookPath;
  // Отказавший (Faulted) бот прежнего запуска освобождается без OnStop:
  // о его остановке уже сообщено (OnFault/OnStop(Fault)).
  if Assigned(FBot) then
  begin
    LBot := FBot;
    LBot.Stop;
    ReleaseBot(LBot);
  end;
  LBot := CreateBot;
  // Новый номер запуска — до ConfigureBot: его захватывают обработчики бота.
  Inc(FBotGeneration);
  try
    ConfigureBot(LBot);
    // Bot доступен событиям, вызванным уже во время Start (предупреждения).
    FBot := LBot;
    if FMode = TTgReceiveMode.Webhook then
    begin
      // До Start: запросы, пришедшие раньше, получат Unavailable, а не 404.
      SetReceiver(LBot.WebhookReceiver);
      RegisterWithServer;
    end;
    LBot.Start;
  except
    ReleaseBot(LBot);
    raise;
  end;
  if Assigned(FOnStart) then
    FOnStart(Self);
end;

procedure TTelegramBot.StopBot(AReason: TTgStopReason);
var
  LBot: TTgBot;
  LLink: ITgOwnerLink;
  LGeneration: Integer;
begin
  if not Assigned(FBot) or FStopping then
    Exit;
  // Из обработчика обновления остановка ждала бы сама себя: откладываем
  // в очередь главного потока (Active станет False после возврата).
  if TTgUpdateDispatcher.InHandler then
  begin
    LLink := FLink;
    LGeneration := FBotGeneration;
    TThread.ForceQueue(nil,
      procedure
      var
        LOwner: TTelegramBot;
      begin
        LOwner := LinkOwner(LLink);
        // Только тот же запуск: остановленный и перезапущенный за это время
        // бот — уже другой (его указатель может совпасть с прежним).
        if Assigned(LOwner) and (LOwner.FBotGeneration = LGeneration) then
          LOwner.StopBot(AReason);
      end);
    Exit;
  end;
  FStopping := True;
  try
    LBot := FBot;
    // Stop из OnFault (Delivery = Worker) — ETgError TTgBot; бот не трогаем.
    LBot.Stop;
    ReleaseBot(LBot);
  finally
    FStopping := False;
  end;
  if Assigned(FOnStop) then
    FOnStop(Self, AReason);
end;

procedure TTelegramBot.DispatchError(AError: Exception; const ACtx: ITgContext);
var
  LCopy: Exception;
  LLink: ITgOwnerLink;
begin
  if not Assigned(FOnError) then
    Exit;
  // Worker — в потоке ошибки; главный поток (обработчики при Main,
  // предупреждения Start) — сразу.
  if (FDelivery <> TTgDelivery.Main) or (TThread.CurrentThread.ThreadID = MainThreadID) then
  begin
    FOnError(Self, AError, ACtx);
    Exit;
  end;
  // Фоновый поток при Main: оригинал освободится после возврата — в очередь
  // уходит копия, она освобождается после обработчика.
  LCopy := CloneException(AError);
  LLink := FLink;
  TThread.Queue(nil,
    procedure
    var
      LOwner: TTelegramBot;
    begin
      try
        LOwner := LinkOwner(LLink);
        if Assigned(LOwner) and Assigned(LOwner.FOnError) then
          LOwner.FOnError(LOwner, LCopy, ACtx);
      finally
        LCopy.Free;
      end;
    end);
end;

procedure TTelegramBot.DispatchFault(AGeneration: Integer; AError: Exception);
var
  LCopy: Exception;
  LLink: ITgOwnerLink;
begin
  // Для Run: завершение отказом (итог False).
  AtomicIncrement(FFaultCount);
  if FDelivery <> TTgDelivery.Main then
  begin
    // В потоке источника: Stop отсюда невозможен — бот остаётся Faulted до
    // Active := True/False или Destroy.
    if Assigned(FOnFault) then
      FOnFault(Self, AError);
    if Assigned(FOnStop) then
      FOnStop(Self, TTgStopReason.Fault);
    Exit;
  end;
  LCopy := CloneException(AError);
  LLink := FLink;
  // Очередь FIFO: после OnError(E, nil), поставленного источником раньше.
  TThread.Queue(nil,
    procedure
    var
      LOwner: TTelegramBot;
    begin
      try
        LOwner := LinkOwner(LLink);
        if Assigned(LOwner) then
          LOwner.FaultInMainThread(AGeneration, LCopy);
      finally
        LCopy.Free;
      end;
    end);
end;

procedure TTelegramBot.FaultInMainThread(AGeneration: Integer; AError: Exception);
begin
  try
    if Assigned(FOnFault) then
      FOnFault(Self, AError);
  finally
    // Тот же запуск (номер, а не указатель бота: новый бот может занять
    // адрес прежнего) и не остановлен/перезапущен в OnFault: освобождаем ресурсы.
    if (FBotGeneration = AGeneration) and Assigned(FBot) and not FStopping and
      (FBot.State = TTgBotState.Faulted) then
      StopBot(TTgStopReason.Fault);
  end;
end;

procedure TTelegramBot.DispatchWebhookRegistered(AGeneration: Integer);
var
  LLink: ITgOwnerLink;
  LEvent: TNotifyEvent;
begin
  if FDelivery <> TTgDelivery.Main then
  begin
    // Worker — в служебном потоке webhook-источника.
    LEvent := FOnWebhookRegistered;
    if Assigned(LEvent) then
      LEvent(Self);
    Exit;
  end;
  LLink := FLink;
  // Очередь: после OnStart (он вызывается в главном потоке в конце запуска).
  TThread.Queue(nil,
    procedure
    var
      LOwner: TTelegramBot;
    begin
      LOwner := LinkOwner(LLink);
      // Тот же запуск, бот ещё работает: остановленный/перезапущенный — без
      // события (сверяется номер запуска, а не указатель бота).
      if Assigned(LOwner) and (LOwner.FBotGeneration = AGeneration) and
        Assigned(LOwner.FBot) and (LOwner.FBot.State = TTgBotState.Running) and
        Assigned(LOwner.FOnWebhookRegistered) then
        LOwner.FOnWebhookRegistered(LOwner);
    end);
end;

function TTelegramBot.RunAlive: Boolean;
begin
  if not Assigned(FBot) then
    Exit(False);
  // Main: отказавший бот освобождает очередь (OnFault, OnStop(Fault)) —
  // ждём её; Worker: события отказа уже вызваны в потоке источника.
  Result := (FDelivery = TTgDelivery.Main) or (FBot.State <> TTgBotState.Faulted);
end;

function TTelegramBot.Run: Boolean;
{$IFNDEF ANDROID}
const
  // Main: сколько ждать доставки отказа через очередь, мс (обычно — один цикл).
  CFaultGraceMs = 1000;
var
  LMain, LSignal: Boolean;
  LFaults: Integer;
  LBot: TTgBot;
  LFaultWatch: TStopwatch;
{$ENDIF}
begin
{$IFDEF ANDROID}
  raise ETgError.Create(TgLangText(@SRuCompRunUnsupported, @SEnCompRunUnsupported));
{$ELSE}
  LMain := TThread.CurrentThread.ThreadID = MainThreadID;
  if (FDelivery = TTgDelivery.Main) and not LMain then
    raise ETgError.Create(TgLangText(@SRuCompRunNotMain, @SEnCompRunNotMain));
  AtomicExchange(FRunStopFlag, 0);
  FRunWake.ResetEvent;
  LFaults := AtomicCmpExchange(FFaultCount, 0, 0);
  TTgShutdownSignal.Reset;
  LSignal := TTgShutdownSignal.Install;
  try
    if not GetActive then
      SetActive(True);
    try
      LFaultWatch := TStopwatch.Create;
      while (AtomicCmpExchange(FRunStopFlag, 0, 0) = 0) and
        not (LSignal and TTgShutdownSignal.Requested) and RunAlive do
      begin
        // Страховка Main: отказ не доставлен очередью за CFaultGraceMs.
        if FBot.State = TTgBotState.Faulted then
        begin
          if not LFaultWatch.IsRunning then
            LFaultWatch.Start
          else if LFaultWatch.ElapsedMilliseconds > CFaultGraceMs then
            Break;
        end
        else
          LFaultWatch.Reset;
        if LMain then
          CheckSynchronize(100)
        else
          FRunWake.WaitFor(100);
      end;
      // Отказ: бот освобождён очередью (Main) или ещё в Faulted (Worker).
      Result := not ((Assigned(FBot) and (FBot.State = TTgBotState.Faulted)) or
        (not Assigned(FBot) and (AtomicCmpExchange(FFaultCount, 0, 0) <> LFaults)));
    finally
      LBot := FBot;
      if Assigned(LBot) then
        if LBot.State = TTgBotState.Faulted then
        begin
          // О сбое уже сообщено (OnFault/OnStop(Fault)) — освобождение без OnStop.
          LBot.Stop;
          ReleaseBot(LBot);
        end
        else
          SetActive(False);
    end;
  finally
    if LSignal then
    begin
      TTgShutdownSignal.NotifyStopped;
      TTgShutdownSignal.Uninstall;
    end;
  end;
{$ENDIF}
end;

procedure TTelegramBot.RequestStop;
begin
  AtomicExchange(FRunStopFlag, 1);
  FRunWake.SetEvent;
end;

procedure TTelegramBot.AddRegistration(const AProc: TProc<TTgBot>);
begin
  // Работающему боту — сразу (ошибка — исключение, регистрация не сохраняется).
  if Assigned(FBot) then
    AProc(FBot);
  FRegistrations.Add(AProc);
end;

procedure TTelegramBot.ClearRegistrations;
begin
  FRegistrations.Clear;
end;

function TTelegramBot.Command(const AName: string; const AHandler: TProc<ITgContext>): TTelegramBot;
begin
  Result := Command([AName], '', AHandler);
end;

function TTelegramBot.Command(const AName, ADescription: string;
  const AHandler: TProc<ITgContext>): TTelegramBot;
begin
  Result := Command([AName], ADescription, AHandler);
end;

function TTelegramBot.Command(const ANames: array of string; const ADescription: string;
  const AHandler: TProc<ITgContext>): TTelegramBot;
var
  LNames: TArray<string>;
  I: Integer;
begin
  if Length(ANames) = 0 then
    raise ETgError.Create(TgLangTextFmt(@SRuRouteEmptyKey, @SEnRouteEmptyKey, ['Command']));
  // Открытый массив замыканием не захватывается — копия.
  SetLength(LNames, Length(ANames));
  for I := 0 to High(ANames) do
  begin
    CheckCommandName(ANames[I]);
    LNames[I] := ANames[I];
  end;
  AddRegistration(
    procedure(ABot: TTgBot)
    begin
      ABot.Command(LNames, ADescription, AHandler);
    end);
  Result := Self;
end;

function TTelegramBot.Callback(const AData: string; const AHandler: TProc<ITgContext>): TTelegramBot;
begin
  CheckRuleKey(AData, 'Callback');
  AddRegistration(
    procedure(ABot: TTgBot)
    begin
      ABot.Callback(AData, AHandler);
    end);
  Result := Self;
end;

function TTelegramBot.CallbackPrefix(const APrefix: string;
  const AHandler: TProc<ITgContext>): TTelegramBot;
begin
  CheckRuleKey(APrefix, 'CallbackPrefix');
  AddRegistration(
    procedure(ABot: TTgBot)
    begin
      ABot.CallbackPrefix(APrefix, AHandler);
    end);
  Result := Self;
end;

function TTelegramBot.Text(const AHandler: TProc<ITgContext>): TTelegramBot;
begin
  AddRegistration(
    procedure(ABot: TTgBot)
    begin
      ABot.Text(AHandler);
    end);
  Result := Self;
end;

function TTelegramBot.Text(const AText: string; const AHandler: TProc<ITgContext>): TTelegramBot;
begin
  CheckRuleKey(AText, 'Text');
  AddRegistration(
    procedure(ABot: TTgBot)
    begin
      ABot.Text(AText, AHandler);
    end);
  Result := Self;
end;

function TTelegramBot.TextMatch(const APattern: string;
  const AHandler: TProc<ITgContext>): TTelegramBot;
begin
  CheckRuleKey(APattern, 'TextMatch');
  // Проверка шаблона сразу (как TTgBot.TextMatch), а не при запуске.
  TRegEx.Create(APattern, [roCompiled]);
  AddRegistration(
    procedure(ABot: TTgBot)
    begin
      ABot.TextMatch(APattern, AHandler);
    end);
  Result := Self;
end;

function TTelegramBot.GetApi: TTgApi;
begin
  if Assigned(FBot) then
    Result := FBot.Api
  else
    Result := nil;
end;

function TTelegramBot.GetState: TTgBotState;
begin
  if Assigned(FBot) then
    Result := FBot.State
  else
    Result := TTgBotState.Idle;
end;

function TTelegramBot.IsApiUrlStored: Boolean;
begin
  Result := FApiUrl <> TgDefaultApiUrl;
end;

function TTelegramBot.IsTokenEnvStored: Boolean;
begin
  Result := FTokenEnv <> CDefaultTokenEnv;
end;

procedure TTelegramBot.SetToken(const AValue: string);
begin
  CheckInactive;
  FToken := AValue;
end;

procedure TTelegramBot.SetTokenEnv(const AValue: string);
begin
  CheckInactive;
  FTokenEnv := AValue;
end;

procedure TTelegramBot.SetTransport(const AValue: ITgTransport);
begin
  CheckInactive;
  FTransport := AValue;
end;

procedure TTelegramBot.SetDelivery(AValue: TTgDelivery);
begin
  CheckInactive;
  FDelivery := AValue;
end;

procedure TTelegramBot.SetMaxParallel(AValue: Integer);
begin
  CheckInactive;
  FMaxParallel := AValue;
end;

procedure TTelegramBot.SetAllowedUpdates(const AValue: string);
begin
  CheckInactive;
  FAllowedUpdates := AValue;
end;

procedure TTelegramBot.SetPollingTimeout(AValue: Integer);
begin
  CheckInactive;
  FPollingTimeout := AValue;
end;

procedure TTelegramBot.SetPolling(AValue: TTgPollingOptions);
begin
  FPolling.Assign(AValue);
end;

procedure TTelegramBot.SetDropPendingUpdates(AValue: Boolean);
begin
  CheckInactive;
  FDropPendingUpdates := AValue;
end;

procedure TTelegramBot.SetAutoAnswerCallbacks(AValue: Boolean);
begin
  CheckInactive;
  FAutoAnswerCallbacks := AValue;
end;

procedure TTelegramBot.SetSetMyCommandsOnStart(AValue: Boolean);
begin
  CheckInactive;
  FSetMyCommandsOnStart := AValue;
end;

procedure TTelegramBot.SetApiUrl(const AValue: string);
begin
  CheckInactive;
  FApiUrl := AValue;
end;

procedure TTelegramBot.SetLocalMode(AValue: Boolean);
begin
  CheckInactive;
  FLocalMode := AValue;
end;

procedure TTelegramBot.SetProxy(AValue: TTgProxyOptions);
begin
  FProxy.Assign(AValue);
end;

procedure TTelegramBot.SetCommands(AValue: TTgCommandItems);
begin
  CheckInactive;
  FCommands.Assign(AValue);
end;

procedure TTelegramBot.SetMode(AValue: TTgReceiveMode);
begin
  CheckInactive;
  FMode := AValue;
end;

procedure TTelegramBot.SetWebhook(AValue: TTgWebhookOptions);
begin
  FWebhook.Assign(AValue);
end;

procedure TTelegramBot.SetOnUpdate(const AValue: TTgUpdateEvent);
begin
  FOnUpdate := AValue;
  if Assigned(FBot) then
    ApplyEvents(FBot);
end;

procedure TTelegramBot.SetOnMessage(const AValue: TTgContextEvent);
begin
  FOnMessage := AValue;
  if Assigned(FBot) then
    ApplyEvents(FBot);
end;

procedure TTelegramBot.SetOnCommand(const AValue: TTgCommandEvent);
begin
  FOnCommand := AValue;
  if Assigned(FBot) then
    ApplyEvents(FBot);
end;

procedure TTelegramBot.SetOnCallbackQuery(const AValue: TTgContextEvent);
begin
  FOnCallbackQuery := AValue;
  if Assigned(FBot) then
    ApplyEvents(FBot);
end;

initialization
  // Загрузка формы/потока с компонентом без объявленного поля (FindClass).
  RegisterClasses([TTelegramBot]);

end.
