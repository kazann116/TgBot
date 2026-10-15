unit TgBot.Bot;

{
  TgBot — бот TTgBot: приём обновлений (long polling или webhook),
  диспетчер обработчиков, запуск и остановка (Start, Stop, Run),
  регистрация правил маршрутизатора. Обработчики, правила, хранилище и
  состояние бота хранит внутреннее ядро — TTgBot обращается к нему только
  через интерфейс ITgBotCore (TgBot.Bot.Core).

  Указывать этот модуль в uses не нужно: TgBot реэкспортирует TTgBot,
  TTgBotState, TTgReceiveMode и TgDefaultBotStopTimeoutMs псевдонимами.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.SyncObjs,
  TgBot.Base,
  TgBot.Http,
  TgBot.Types,
  TgBot.Updates,
  TgBot.State,
  TgBot.Context,
  TgBot.Bot.Core;

const
  /// <summary>Таймаут TTgBot.Stop по умолчанию, мс.</summary>
  TgDefaultBotStopTimeoutMs = 10000;

type
  /// <summary>
  ///   Состояние бота (TTgBot.State): Idle, Running, Stopping, Faulted;
  ///   описание — TgBot.Bot.Core.TTgBotState.
  /// </summary>
  TTgBotState = TgBot.Bot.Core.TTgBotState;

  /// <summary>Способ получения обновлений (TTgBot.Mode).</summary>
  TTgReceiveMode = (
    /// <summary>Long polling (getUpdates) — по умолчанию, без входящих соединений.</summary>
    Polling,
    /// <summary>
    ///   Webhook: Telegram присылает обновления на WebhookUrl, HTTP-сервер
    ///   приложения передаёт тело запроса в TTgBot.HandleWebhook. Недоступно
    ///   на Android и iOS.
    /// </summary>
    Webhook);

  /// <summary>
  ///   Бот: приём (Mode: TTgLongPollSource или TTgWebhookSource +
  ///   HandleWebhook), раздача обработчикам
  ///   (TTgUpdateDispatcher: один чат — по порядку, разные — параллельно),
  ///   контекст ITgContext и состояние диалогов (StateStorage).
  ///   Обычный класс (компонент — в фазе 6). Свойства задаются до Start.
  ///
  ///   Порядок обработки (маршрутизатор):
  ///   1) OnUpdate — для каждого обновления; ACtx.Handled := True прекращает
  ///      дальнейшую обработку;
  ///   2) message: Command (команда этому боту; без обработчика —
  ///      OnUnknownCommand) → Text(точный текст) → TextMatch (по порядку
  ///      регистрации) → Text(любой текст) → OnMessage;
  ///   3) callback_query: Callback(точные данные) → CallbackPrefix (по порядку
  ///      регистрации) → OnCallbackQuery.
  ///   Срабатывает первое подходящее правило; OnMessage/OnCallbackQuery
  ///   вызываются, только если ни одно правило не сработало (или обработчик
  ///   правила сбросил ACtx.Handled := False) — эхо в OnMessage не дублирует
  ///   ответ на /start. Маршрутизируется только поле text сообщения (не
  ///   caption). Команда другому боту (/start@Other) правилам команд не
  ///   подходит и идёт дальше как обычный текст.
  ///   Регистрация (Command, Callback, Text…) потокобезопасна, возможна до и
  ///   во время работы; повторная регистрация того же ключа заменяет
  ///   обработчик, nil — удаляет правило.
  ///   При Start, если есть команды или OnUnknownCommand, один раз за жизнь
  ///   бота выполняется getMe (BotUserName для /cmd@бот), а при
  ///   SetMyCommandsOnStart и командах с описанием — setMyCommands. Оба
  ///   запроса идут в фоне (TgBotThreadPool), параллельно с приёмом: Start
  ///   не ждёт сеть и сразу переводит бота в Running; их ошибки —
  ///   OnError(E, nil) в потоке пула, запуск продолжается. Не сообщаются:
  ///   ошибки после отказа (Faulted — новых запросов задача тоже не шлёт),
  ///   после отмены Stop/Free и 401/404 —
  ///   неверный токен или адрес Bot API; о нём один раз сообщит отказ
  ///   приёма (OnError + OnFault), setMyCommands тогда не вызывается.
  ///   Команда '/cmd@бот'
  ///   маршрутизируется только после завершения этого getMe (обработчик
  ///   ждёт его; неудача — повторный getMe лениво). Stop дожидается фоновых
  ///   запросов (в пределах AWaitMs, затем отменяет их).
  ///   Исключение
  ///   обработчика — OnError(E, Context) в потоке обработчика; ошибки
  ///   приёма — OnError(E, nil) в потоке источника; исключения OnError
  ///   поглощаются. Неустранимая ошибка приёма переводит бота в Faulted
  ///   (State) и вызывает OnError(E, nil), затем OnFault(E) — один раз за
  ///   запуск. Нажатие кнопки, на которое обработчик не ответил,
  ///   подтверждается пустым answerCallbackQuery (AutoAnswerCallbacks).
  ///
  ///   Обработчики, StateStorage и AutoAnswerCallbacks можно менять на ходу
  ///   из любого потока: они хранятся во внутреннем ядре под блокировкой,
  ///   каждое обновление обрабатывается снимком, сделанным при его начале.
  ///
  ///   Free не ждёт зависший обработчик дольше Stop: ядро (клиент Api,
  ///   хранилище) живёт, пока на него ссылается обработчик или сохранённый
  ///   ITgContext. После Free обработчик, вернувшийся позже, не вызывает
  ///   OnError и автоответ, а вызовы ACtx.Api/ACtx.Reply и т.п. выбрасывают
  ///   ETgCancelledError. На пользователе остаётся: не обращаться после Free
  ///   к захваченной в обработчике переменной бота (LBot — уже освобождённый
  ///   объект) и не хранить указатель ACtx.Api дольше самого ITgContext.
  /// </summary>
  TTgBot = class
  private
    // Внутреннее ядро (TgBot.Bot.Core): владеет клиентом, хранилищем,
    // обработчиками, правилами и состоянием; бот держит его этой ссылкой и
    // обращается к нему только через интерфейс.
    FCore: ITgBotCore;
    // Кэш FCore.Api (не во владении): задаётся в Init и не меняется, пока
    // жива ссылка FCore; обнуляется в Destroy до её отпускания. Свойство Api
    // читает поле без вызова через интерфейс.
    FApi: TTgApi;
    FSource: TTgLongPollSource;
    FSourceRef: ITgUpdateSource;
    FWebhookSource: TTgWebhookSource;
    FWebhookSourceRef: ITgUpdateSource;
    // Источник текущего (последнего) запуска: FSourceRef или FWebhookSourceRef.
    FActiveSource: ITgUpdateSource;
    FMode: TTgReceiveMode;
    FWebhookUrl: string;
    FWebhookSecretToken: string;
    FWebhookMaxConnections: Integer;
    FWebhookDropPendingUpdates: Boolean;
    FWebhookIpAddress: string;
    FWebhookCertificate: TTgInputFile;
    FDeleteWebhookOnStop: Boolean;
    FDispatcher: TTgUpdateDispatcher;
    FDispatcherRef: ITgUpdateSink;
    FDelivery: TTgDelivery;
    FMaxParallel: Integer;
    FQueueCapacity: Integer;
    FAckPolicy: TTgAckPolicy;
    FAllowedUpdates: TTgOptional<TArray<string>>;
    FPollTimeout: Integer;
    FDropPendingUpdates: Boolean;
    FAutoDeleteWebhook: Boolean;
    FDrainTimeoutMs: Cardinal;
    // Ресурсы запуска (источник/диспетчер) запущены: Start без Stop. В отличие
    // от Active остаётся True в Faulted — Stop/Start/Free их освобождают.
    FStarted: Boolean;
    FRunStopFlag: Integer;
    FRunWake: TEvent;
    FSetMyCommandsOnStart: Boolean;
    procedure Init(AApi: TTgApi);
    /// <summary>Проверки и настройка webhook-источника перед запуском (Mode = Webhook).</summary>
    procedure PrepareWebhook;
    procedure WarnFilteredHandlers;
    procedure PrepareCommands;
    function GetOnUnknownCommand: TProc<ITgContext>;
    procedure SetOnUnknownCommand(const AValue: TProc<ITgContext>);
    function GetBotUserName: string;
    function GetStateStorage: ITgStateStorage;
    procedure SetStateStorage(const AValue: ITgStateStorage);
    function GetAutoAnswerCallbacks: Boolean;
    procedure SetAutoAnswerCallbacks(AValue: Boolean);
    function GetOnUpdate: TProc<ITgContext>;
    procedure SetOnUpdate(const AValue: TProc<ITgContext>);
    function GetOnMessage: TProc<ITgContext>;
    procedure SetOnMessage(const AValue: TProc<ITgContext>);
    function GetOnCallbackQuery: TProc<ITgContext>;
    procedure SetOnCallbackQuery(const AValue: TProc<ITgContext>);
    function GetOnError: TProc<Exception, ITgContext>;
    procedure SetOnError(const AValue: TProc<Exception, ITgContext>);
    function GetOnConflict: TProc<ETgConflictError>;
    procedure SetOnConflict(const AValue: TProc<ETgConflictError>);
    function GetOnFault: TProc<Exception>;
    procedure SetOnFault(const AValue: TProc<Exception>);
    function GetOnWebhookRegistered: TProc;
    procedure SetOnWebhookRegistered(const AValue: TProc);
    function GetSourceState: TTgSourceState;
    function GetState: TTgBotState;
    function GetActive: Boolean;
  public
    /// <summary>Бот облачного Bot API с настройками по умолчанию.</summary>
    constructor Create(const AToken: string); overload;
    /// <summary>Бот с настройками транспорта (прокси, Local Bot API server, таймауты…).</summary>
    constructor Create(const ASettings: TTgHttpSettings); overload;
    /// <summary>Бот с внешним транспортом (общим или тестовым).</summary>
    constructor Create(const ATransport: ITgTransport); overload;
    /// <summary>
    ///   Останавливает бота (Stop; результат может быть False), отсоединяет
    ///   ядро (обработчики сбрасываются, клиент закрывается Shutdown) и
    ///   отпускает его. Клиент освобождается вместе с ядром — сразу или,
    ///   если обработчик ещё выполняется, в его потоке после возврата.
    /// </summary>
    destructor Destroy; override;
    /// <summary>
    ///   Запускает приём и обработку (State: Idle → Running). Из Faulted
    ///   сначала выполняет Stop (освобождение ресурсов прежнего запуска),
    ///   затем запускает заново. Start в Running/Stopping — ETgError;
    ///   из обработчика обновления или из OnFault при Faulted — ETgError
    ///   (неявный Stop не может ждать сам себя).
    /// </summary>
    procedure Start;
    /// <summary>
    ///   Останавливает приём (дренаж принятого, итоговое подтверждение) и
    ///   обработчики не дольше ≈AWaitMs; State: Running/Faulted → Stopping →
    ///   Idle. False — поток, который не удалось прервать, отпущен. Из
    ///   Faulted дорабатывает принятое и освобождает ресурсы (обычно True).
    ///   Из главного потока ждёт с CheckSynchronize (Delivery = Main не
    ///   блокируется). Из обработчика обновления или из OnFault — ETgError
    ///   (используйте RequestStop или TThread.Queue).
    /// </summary>
    function Stop(AWaitMs: Cardinal = TgDefaultBotStopTimeoutMs): Boolean;
    /// <summary>
    ///   Блокирующий запуск для консоли: Start, цикл CheckSynchronize(100) до
    ///   RequestStop, Ctrl+C/закрытия консоли/SIGINT/SIGTERM или перехода в
    ///   Faulted (не позже ≈100 мс после него), затем Stop. Отказ приёма не
    ///   выбрасывается — он уже доставлен в OnError/OnFault; результат:
    ///   True — остановлен по запросу или сигналу, False — завершён из-за
    ///   Faulted (например, ExitCode := 1). Исключения Start и Stop (например,
    ///   повторный запуск) выбрасываются как обычно. Delivery = Main — только
    ///   из главного потока (иначе ETgError); на Android — ETgError.
    /// </summary>
    function Run: Boolean;
    /// <summary>Просит Run завершиться (из любого потока, в т.ч. из обработчика).</summary>
    procedure RequestStop;
    /// <summary>
    ///   Команда AName ('start' или '/start'; регистр не важен): сообщение
    ///   '/start', '/START', '/start@ЭтотБот аргументы' (ACtx.Command,
    ///   ACtx.Args). Результат — Self (цепочка вызовов).
    /// </summary>
    function Command(const AName: string; const AHandler: TProc<ITgContext>): TTgBot; overload;
    /// <summary>
    ///   Команда с описанием для меню бота (setMyCommands при Start, если
    ///   SetMyCommandsOnStart).
    /// </summary>
    function Command(const AName, ADescription: string;
      const AHandler: TProc<ITgContext>): TTgBot; overload;
    /// <summary>Несколько имён одной команды: Command(['help', 'h'], …).</summary>
    function Command(const ANames: array of string; const AHandler: TProc<ITgContext>): TTgBot; overload;
    /// <summary>Несколько имён; в меню попадает первое имя с описанием ADescription.</summary>
    function Command(const ANames: array of string; const ADescription: string;
      const AHandler: TProc<ITgContext>): TTgBot; overload;
    /// <summary>Нажатие кнопки с callback data, точно равной AData.</summary>
    function Callback(const AData: string; const AHandler: TProc<ITgContext>): TTgBot;
    /// <summary>
    ///   Нажатие кнопки, callback data которой начинается с APrefix
    ///   ('page:' → ACtx.Args = '2' для 'page:2'; ACtx.Data — полностью).
    /// </summary>
    function CallbackPrefix(const APrefix: string; const AHandler: TProc<ITgContext>): TTgBot;
    /// <summary>Любое текстовое сообщение, не обработанное предыдущими правилами.</summary>
    function Text(const AHandler: TProc<ITgContext>): TTgBot; overload;
    /// <summary>Сообщение с текстом AText (без учёта регистра, без обрезки пробелов).</summary>
    function Text(const AText: string; const AHandler: TProc<ITgContext>): TTgBot; overload;
    /// <summary>
    ///   Текст, в котором найдено регулярное выражение APattern
    ///   (System.RegularExpressions; '^…$' — весь текст, '(?i)' — без учёта
    ///   регистра); ACtx.Args — первая группа или всё совпадение. Неверный
    ///   шаблон — исключение здесь же. Повторный APattern заменяет обработчик.
    /// </summary>
    function TextMatch(const APattern: string; const AHandler: TProc<ITgContext>): TTgBot;
    /// <summary>
    ///   Тело webhook-запроса из HTTP-сервера приложения (WebBroker, Horse,
    ///   mORMot, Indy…): ABody — тело POST, ASecretHeader — заголовок
    ///   X-Telegram-Bot-Api-Secret-Token ('' — нет). Ответьте серверу Telegram
    ///   кодом TgWebhookHttpStatus(результат). Потокобезопасно, из любого
    ///   числа потоков; не блокирует дольше WebhookSource.PostTimeoutMs.
    ///   Не в Mode = Webhook, до Start, после Stop, в Faulted — Unavailable.
    ///   Не вызывайте во время и после Free бота (для компонента это
    ///   обеспечивает TTelegramBot.HandleWebhook).
    /// </summary>
    function HandleWebhook(const ABody, ASecretHeader: string): TTgWebhookResult; overload;
    /// <summary>То же для тела в байтах UTF-8.</summary>
    function HandleWebhook(const ABody: TBytes; const ASecretHeader: string): TTgWebhookResult; overload;
    /// <summary>Клиент Bot API (владеет бот).</summary>
    property Api: TTgApi read FApi;
    /// <summary>Источник long polling (тонкие настройки: Timer, JitterPercent, Offset…).</summary>
    property Source: TTgLongPollSource read FSource;
    /// <summary>
    ///   Webhook-источник (тонкие настройки: MaxBodySize, PostTimeoutMs,
    ///   DedupWindow, RegisterOnStart, AllowedUpdates — последнее задаёт Start).
    /// </summary>
    property WebhookSource: TTgWebhookSource read FWebhookSource;
    /// <summary>
    ///   Способ получения обновлений, по умолчанию Polling. Webhook: Start
    ///   вызывает setWebhook в фоне (ошибка — Faulted и OnFault), обновления
    ///   передаёт HandleWebhook. На Android/iOS Webhook — ETgError при Start.
    ///   Переход Webhook → Polling: getUpdates при активном webhook получает
    ///   409 — задайте AutoDeleteWebhook или DeleteWebhookOnStop.
    /// </summary>
    property Mode: TTgReceiveMode read FMode write FMode;
    /// <summary>
    ///   Внешний HTTPS-URL бота для setWebhook (Mode = Webhook; обязателен).
    ///   Не 'https://' — ETgError при Start (облачный Bot API принимает
    ///   только HTTPS); 'http://' допускается только с Local Bot API server
    ///   (адрес Bot API транспорта не облачный).
    /// </summary>
    property WebhookUrl: string read FWebhookUrl write FWebhookUrl;
    /// <summary>
    ///   secret_token (1–256 символов [A-Za-z0-9_-]); пусто — при каждом Start
    ///   генерируется случайный (48 символов, криптостойкий генератор ОС) и
    ///   передаётся в setWebhook; HandleWebhook сверяет его с заголовком.
    /// </summary>
    property WebhookSecretToken: string read FWebhookSecretToken write FWebhookSecretToken;
    /// <summary>max_connections (1–100); 0 — по умолчанию сервера (40).</summary>
    property WebhookMaxConnections: Integer read FWebhookMaxConnections write FWebhookMaxConnections;
    /// <summary>drop_pending_updates setWebhook: пропустить накопившиеся обновления.</summary>
    property WebhookDropPendingUpdates: Boolean read FWebhookDropPendingUpdates
      write FWebhookDropPendingUpdates;
    /// <summary>ip_address setWebhook (необязательно).</summary>
    property WebhookIpAddress: string read FWebhookIpAddress write FWebhookIpAddress;
    /// <summary>Публичный ключ самоподписанного сертификата (необязательно; FromFile/FromBytes).</summary>
    property WebhookCertificate: TTgInputFile read FWebhookCertificate write FWebhookCertificate;
    /// <summary>Вызывать deleteWebhook при Stop (по умолчанию False).</summary>
    property DeleteWebhookOnStop: Boolean read FDeleteWebhookOnStop write FDeleteWebhookOnStop;
    /// <summary>Диспетчер обработчиков.</summary>
    property Dispatcher: TTgUpdateDispatcher read FDispatcher;
    /// <summary>
    ///   Бот работает: State = Running. False в Idle, Stopping и Faulted
    ///   (в Faulted ресурсы ещё заняты — освободите их Stop или Start).
    ///   Чтение потокобезопасно.
    /// </summary>
    property Active: Boolean read GetActive;
    /// <summary>
    ///   Состояние бота (TTgBotState); хранится во внутреннем ядре, чтение
    ///   потокобезопасно из любого потока, в т.ч. из обработчиков и событий.
    ///   Переход в Faulted выполняет поток источника до вызова OnError/OnFault.
    /// </summary>
    property State: TTgBotState read GetState;
    /// <summary>
    ///   Состояние источника текущего режима (long polling или webhook);
    ///   Faulted — приём остановлен ошибкой.
    /// </summary>
    property SourceState: TTgSourceState read GetSourceState;
    /// <summary>Где выполнять обработчики, по умолчанию Worker.</summary>
    property Delivery: TTgDelivery read FDelivery write FDelivery;
    /// <summary>Число потоков обработчиков, по умолчанию TgDefaultMaxParallel.</summary>
    property MaxParallel: Integer read FMaxParallel write FMaxParallel;
    /// <summary>Ёмкость очереди обновлений, по умолчанию TgDefaultQueueCapacity.</summary>
    property QueueCapacity: Integer read FQueueCapacity write FQueueCapacity;
    /// <summary>Политика подтверждения, по умолчанию AfterReceive.</summary>
    property AckPolicy: TTgAckPolicy read FAckPolicy write FAckPolicy;
    /// <summary>
    ///   Типы обновлений allowed_updates (TTgUpdateType.*), передаются в каждом
    ///   getUpdates. Сервер запоминает последнее переданное значение (из
    ///   getUpdates или setWebhook), поэтому бот передаёт его всегда:
    ///   не задано — пустой массив [], то есть все типы, кроме chat_member,
    ///   message_reaction и message_reaction_count; фильтр, оставшийся от
    ///   другой программы с тем же токеном, при этом сбрасывается.
    ///   Чтобы получать chat_member или реакции, перечислите нужные типы
    ///   явно (вместе с остальными нужными, например message и
    ///   callback_query). Если назначен OnMessage/OnCallbackQuery, а явный
    ///   список не содержит его тип, при Start вызывается OnError(E, nil)
    ///   с предупреждением (запуск продолжается).
    /// </summary>
    property AllowedUpdates: TTgOptional<TArray<string>> read FAllowedUpdates write FAllowedUpdates;
    /// <summary>timeout getUpdates, с; по умолчанию TgDefaultPollTimeoutSec.</summary>
    property PollTimeout: Integer read FPollTimeout write FPollTimeout;
    /// <summary>Пропустить накопившиеся обновления при старте.</summary>
    property DropPendingUpdates: Boolean read FDropPendingUpdates write FDropPendingUpdates;
    /// <summary>При 409 «webhook is active» удалить webhook (по умолчанию False).</summary>
    property AutoDeleteWebhook: Boolean read FAutoDeleteWebhook write FAutoDeleteWebhook;
    /// <summary>Подтверждать неотвеченные callback_query пустым ответом (по умолчанию True).</summary>
    property AutoAnswerCallbacks: Boolean read GetAutoAnswerCallbacks write SetAutoAnswerCallbacks;
    /// <summary>Дренаж при Stop, мс; по умолчанию TgDefaultDrainTimeoutMs.</summary>
    property DrainTimeoutMs: Cardinal read FDrainTimeoutMs write FDrainTimeoutMs;
    /// <summary>Хранилище состояния диалогов (nil — новое в памяти).</summary>
    property StateStorage: ITgStateStorage read GetStateStorage write SetStateStorage;
    /// <summary>Каждое обновление (до специализированных обработчиков).</summary>
    property OnUpdate: TProc<ITgContext> read GetOnUpdate write SetOnUpdate;
    /// <summary>Новое сообщение (update.message).</summary>
    property OnMessage: TProc<ITgContext> read GetOnMessage write SetOnMessage;
    /// <summary>Нажатие инлайн-кнопки (update.callback_query).</summary>
    property OnCallbackQuery: TProc<ITgContext> read GetOnCallbackQuery write SetOnCallbackQuery;
    /// <summary>
    ///   Команда этому боту, для которой нет правила Command (ACtx.Command,
    ///   ACtx.Args заданы). Не назначен — команда идёт дальше как текст.
    /// </summary>
    property OnUnknownCommand: TProc<ITgContext> read GetOnUnknownCommand write SetOnUnknownCommand;
    /// <summary>
    ///   Вызывать setMyCommands при Start, если есть команды с описанием
    ///   (по умолчанию True). Меню — все команды с описанием в порядке
    ///   регистрации, область по умолчанию.
    /// </summary>
    property SetMyCommandsOnStart: Boolean read FSetMyCommandsOnStart write FSetMyCommandsOnStart;
    /// <summary>
    ///   username бота (getMe), '' — ещё не получен. Запрашивается один раз:
    ///   в фоне после Start, если есть команды, иначе при первой команде
    ///   '/cmd@бот'.
    /// </summary>
    property BotUserName: string read GetBotUserName;
    /// <summary>
    ///   Исключение обработчика (AContext задан) или ошибка приёма (AContext = nil),
    ///   в т.ч. неустранимая — тогда сразу после него вызывается OnFault.
    /// </summary>
    property OnError: TProc<Exception, ITgContext> read GetOnError write SetOnError;
    /// <summary>409: другой экземпляр бота или webhook (в потоке источника).</summary>
    property OnConflict: TProc<ETgConflictError> read GetOnConflict write SetOnConflict;
    /// <summary>
    ///   Неустранимая ошибка приёма (ETgApiError 401/404, 409 webhook…): бот
    ///   перешёл в Faulted. Вызывается один раз за запуск, в потоке источника,
    ///   после OnError(E, nil) (ошибка уже в журнале, OnFault — реакция на
    ///   смену состояния); State внутри уже Faulted. AError принадлежит
    ///   источнику — не освобождайте и не сохраняйте после возврата.
    ///   Исключения поглощаются. Stop/Start отсюда — ETgError: используйте
    ///   RequestStop (Run завершится сам) или TThread.Queue. После Free бота
    ///   не вызывается. Можно менять на ходу из любого потока.
    /// </summary>
    property OnFault: TProc<Exception> read GetOnFault write SetOnFault;
    /// <summary>
    ///   Webhook зарегистрирован: setWebhook при Start (Mode = Webhook,
    ///   WebhookSource.RegisterOnStart) выполнен успешно. Вызывается в фоне
    ///   (служебный поток webhook-источника; порядок относительно возврата
    ///   Start не гарантируется), только пока бот Running (не во время
    ///   Stop, не после Free и не в Faulted). Исключения
    ///   поглощаются. Можно менять на ходу из любого потока.
    /// </summary>
    property OnWebhookRegistered: TProc read GetOnWebhookRegistered write SetOnWebhookRegistered;
  end;

implementation

uses
  System.Classes,
  System.Diagnostics,
  System.Math,
  TgBot.Router;

resourcestring
  SRuWebhookNotHttps = 'Режим Webhook: WebhookUrl должен начинаться с https:// ' +
    '(Telegram принимает только HTTPS; http:// — только с Local Bot API server)';
  SEnWebhookNotHttps = 'Webhook mode: WebhookUrl must start with https:// ' +
    '(Telegram accepts HTTPS only; http:// is allowed only with a Local Bot API server)';

type
  /// <summary>Тексты модуля.</summary>
  TTgBotText = (WebhookNotHttps);

const
  CBotTexts: array[TTgBotText, TTgLanguage] of PResStringRec = (
    (@SRuWebhookNotHttps, @SEnWebhookNotHttps)
  );

function TgBotText(AText: TTgBotText): string;
begin
  Result := LoadResString(CBotTexts[AText, TgBot.Base.TgGetLanguage]);
end;

{ TTgBot }

/// <summary>
///   Подтверждение обработки для источника. Отдельная функция: замыкание
///   захватывает только источник (без кадра Init и Self).
/// </summary>
function NewProcessedHandler(const ASource: ITgUpdateSource): TProc<Int64>;
begin
  Result :=
    procedure(AUpdateId: Int64)
    begin
      ASource.Processed(AUpdateId);
    end;
end;

constructor TTgBot.Create(const AToken: string);
begin
  inherited Create;
  Init(TTgApi.Create(AToken));
end;

constructor TTgBot.Create(const ASettings: TTgHttpSettings);
begin
  inherited Create;
  Init(TTgApi.Create(ASettings));
end;

constructor TTgBot.Create(const ATransport: ITgTransport);
begin
  inherited Create;
  Init(TTgApi.Create(ATransport));
end;

procedure TTgBot.Init(AApi: TTgApi);
begin
  // Клиент переходит во владение ядра (если ядро не создано — освобождается).
  FCore := TgCreateBotCore(AApi);
  FApi := FCore.Api;
  FRunWake := TEvent.Create(nil, False, False, '');
  FDelivery := TTgDelivery.Worker;
  FMaxParallel := TgDefaultMaxParallel;
  FQueueCapacity := TgDefaultQueueCapacity;
  FAckPolicy := TTgAckPolicy.AfterReceive;
  FPollTimeout := TgDefaultPollTimeoutSec;
  FDrainTimeoutMs := TgDefaultDrainTimeoutMs;
  FSetMyCommandsOnStart := True;
  // Источник прерывается и отменой клиента (Api.Shutdown при Free бота).
  FSource := TTgLongPollSource.Create(FApi.Transport, FApi.CancelToken);
  FSourceRef := FSource;
  FDispatcher := TTgUpdateDispatcher.Create(TgNewRawHandler(FCore));
  FDispatcherRef := FDispatcher;
  FDispatcher.OnProcessed := NewProcessedHandler(FSourceRef);
  // События источника — в его потоке; захватывается только ядро.
  FSource.OnConflict := TgNewConflictHandler(FCore);
  FSource.OnError := TgNewSourceErrorHandler(FCore);
  // Webhook: setWebhook/deleteWebhook — через тот же транспорт, прерываются Free;
  // обёртка сообщает ядру об успешном setWebhook (OnWebhookRegistered).
  FWebhookSource := TTgWebhookSource.Create(TgNewWebhookTransport(FApi.Transport, FCore),
    FApi.CancelToken);
  FWebhookSourceRef := FWebhookSource;
  FWebhookSource.OnError := TgNewSourceErrorHandler(FCore);
  FActiveSource := FSourceRef;
  // OnFault источника (с номером запуска) назначает Start.
end;

destructor TTgBot.Destroy;
begin
  // В т.ч. в Faulted: ресурсы запуска заняты, пока не выполнен Stop.
  if FStarted then
    try
      Stop;
    except
      // Деструктор не выпускает исключений (например, вызов из обработчика).
    end;
  // Обработчик, вернувшийся позже, увидит отсоединённое ядро: без OnError и
  // автоответа, вызовы клиента — ETgCancelledError.
  if Assigned(FCore) then
    FCore.Detach;
  if Assigned(FDispatcher) then
    FDispatcher.OnProcessed := nil;
  FDispatcher := nil;
  FSource := nil;
  FWebhookSource := nil;
  // Деструкторы диспетчера и источника не ждут отпущенные (Stop = False)
  // потоки: те держат свои ядра сами и освобождают их по возврату.
  FDispatcherRef := nil;
  FActiveSource := nil;
  FSourceRef := nil;
  FWebhookSourceRef := nil;
  // Последняя ссылка на ядро (если обработчиков и контекстов нет) — клиент
  // освобождается здесь; иначе — с последним обработчиком/контекстом.
  FApi := nil;
  FCore := nil;
  FreeAndNil(FRunWake);
  inherited Destroy;
end;

function TTgBot.GetStateStorage: ITgStateStorage;
begin
  Result := FCore.GetStateStorage;
end;

procedure TTgBot.SetStateStorage(const AValue: ITgStateStorage);
begin
  FCore.SetStateStorage(AValue);
end;

function TTgBot.GetAutoAnswerCallbacks: Boolean;
begin
  Result := FCore.GetAutoAnswerCallbacks;
end;

procedure TTgBot.SetAutoAnswerCallbacks(AValue: Boolean);
begin
  FCore.SetAutoAnswerCallbacks(AValue);
end;

function TTgBot.GetOnUpdate: TProc<ITgContext>;
begin
  Result := FCore.GetOnUpdate();
end;

procedure TTgBot.SetOnUpdate(const AValue: TProc<ITgContext>);
begin
  FCore.SetOnUpdate(AValue);
end;

function TTgBot.GetOnMessage: TProc<ITgContext>;
begin
  Result := FCore.GetOnMessage();
end;

procedure TTgBot.SetOnMessage(const AValue: TProc<ITgContext>);
begin
  FCore.SetOnMessage(AValue);
end;

function TTgBot.GetOnCallbackQuery: TProc<ITgContext>;
begin
  Result := FCore.GetOnCallbackQuery();
end;

procedure TTgBot.SetOnCallbackQuery(const AValue: TProc<ITgContext>);
begin
  FCore.SetOnCallbackQuery(AValue);
end;

function TTgBot.GetOnError: TProc<Exception, ITgContext>;
begin
  Result := FCore.GetOnError();
end;

procedure TTgBot.SetOnError(const AValue: TProc<Exception, ITgContext>);
begin
  FCore.SetOnError(AValue);
end;

function TTgBot.GetOnConflict: TProc<ETgConflictError>;
begin
  Result := FCore.GetOnConflict();
end;

procedure TTgBot.SetOnConflict(const AValue: TProc<ETgConflictError>);
begin
  FCore.SetOnConflict(AValue);
end;

function TTgBot.GetOnFault: TProc<Exception>;
begin
  Result := FCore.GetOnFault();
end;

procedure TTgBot.SetOnFault(const AValue: TProc<Exception>);
begin
  FCore.SetOnFault(AValue);
end;

function TTgBot.GetOnWebhookRegistered: TProc;
begin
  Result := FCore.GetOnWebhookRegistered();
end;

procedure TTgBot.SetOnWebhookRegistered(const AValue: TProc);
begin
  FCore.SetOnWebhookRegistered(AValue);
end;

function TTgBot.GetSourceState: TTgSourceState;
begin
  Result := FActiveSource.State;
end;

function TTgBot.HandleWebhook(const ABody, ASecretHeader: string): TTgWebhookResult;
begin
  // Источник живёт столько же, сколько бот; вне Mode = Webhook он не запущен.
  Result := FWebhookSource.Accept(ABody, ASecretHeader);
end;

function TTgBot.HandleWebhook(const ABody: TBytes; const ASecretHeader: string): TTgWebhookResult;
begin
  Result := FWebhookSource.Accept(ABody, ASecretHeader);
end;

procedure TTgBot.PrepareWebhook;
{$IF not (defined(ANDROID) or defined(IOS))}
var
  LSecret: string;
{$ENDIF}
begin
{$IF defined(ANDROID) or defined(IOS)}
  // Мобильное приложение не принимает входящие HTTPS-запросы Telegram.
  raise ETgError.Create(TgUpdatesText(TTgUpdatesText.WebhookUnsupported));
{$ELSE}
  if Trim(FWebhookUrl) = '' then
    raise ETgError.Create(TgUpdatesText(TTgUpdatesText.WebhookUrlRequired));
  // Облачный Bot API принимает только HTTPS-адрес; Local Bot API server
  // (адрес Bot API транспорта задан и не облачный) — и HTTP.
  if not SameText(Copy(Trim(FWebhookUrl), 1, 8), 'https://') and
    ((FApi.Settings.ApiUrl = '') or SameText(FApi.Settings.ApiUrl, TgDefaultApiUrl) or
    not SameText(Copy(Trim(FWebhookUrl), 1, 7), 'http://')) then
    raise ETgError.Create(TgBotText(TTgBotText.WebhookNotHttps));
  // Текст ошибки не содержит самого секрета.
  if FWebhookSecretToken <> '' then
  begin
    if not TTgWebhookSource.IsValidSecretToken(FWebhookSecretToken) then
      raise ETgError.Create(TgUpdatesText(TTgUpdatesText.WebhookBadSecret));
    LSecret := FWebhookSecretToken;
  end
  else
    // Новый случайный секрет на каждый запуск: setWebhook сообщает его серверу.
    LSecret := TTgWebhookSource.GenerateSecretToken;
  FWebhookSource.Url := FWebhookUrl;
  FWebhookSource.SecretToken := LSecret;
  FWebhookSource.MaxConnections := FWebhookMaxConnections;
  FWebhookSource.DropPendingUpdates := FWebhookDropPendingUpdates;
  FWebhookSource.IpAddress := FWebhookIpAddress;
  FWebhookSource.Certificate := FWebhookCertificate;
  FWebhookSource.DeleteOnStop := FDeleteWebhookOnStop;
  // allowed_updates — как у long polling: без явного значения [] (сброс фильтра).
  if FAllowedUpdates.HasValue then
    FWebhookSource.AllowedUpdates := FAllowedUpdates
  else
    FWebhookSource.AllowedUpdates := TTgOptional<TArray<string>>.Create(nil);
{$ENDIF}
end;

function TTgBot.GetState: TTgBotState;
begin
  Result := FCore.GetState;
end;

function TTgBot.GetActive: Boolean;
begin
  Result := GetState = TTgBotState.Running;
end;

procedure TTgBot.WarnFilteredHandlers;

  procedure WarnIfFiltered(AAssigned: Boolean; const AHandler, AKind: string);
  var
    LKind: string;
    LWarning: ETgError;
  begin
    if not AAssigned then
      Exit;
    for LKind in FAllowedUpdates.Value do
      if LKind = AKind then
        Exit;
    LWarning := ETgError.Create(Format(TgUpdatesText(TTgUpdatesText.HandlerFiltered),
      [AHandler, AKind]));
    try
      FCore.NotifyError(LWarning, nil);
    finally
      LWarning.Free;
    end;
  end;

var
  LOnMessage, LOnCallbackQuery: TProc<ITgContext>;
  LRoutes: TTgRoutes;
begin
  // Предупреждение, не исключение: явный узкий фильтр мог быть задан намеренно.
  // Пустой массив означает «все типы, кроме chat_member и реакций».
  if not FAllowedUpdates.HasValue or (Length(FAllowedUpdates.Value) = 0) then
    Exit;
  LOnMessage := GetOnMessage();
  LOnCallbackQuery := GetOnCallbackQuery();
  WarnIfFiltered(Assigned(LOnMessage), 'OnMessage', TTgUpdateType.Message);
  WarnIfFiltered(Assigned(LOnCallbackQuery), 'OnCallbackQuery', TTgUpdateType.CallbackQuery);
  LRoutes := FCore.GetRoutes;
  WarnIfFiltered((Length(LRoutes.Lists[TTgRouteKind.Command]) > 0) or
    (Length(LRoutes.Lists[TTgRouteKind.Text]) > 0) or (Length(LRoutes.Matches) > 0) or
    Assigned(LRoutes.AnyText) or Assigned(LRoutes.UnknownCommand), 'Command/Text',
    TTgUpdateType.Message);
  WarnIfFiltered((Length(LRoutes.Lists[TTgRouteKind.Callback]) > 0) or
    (Length(LRoutes.Lists[TTgRouteKind.CallbackPrefix]) > 0), 'Callback', TTgUpdateType.CallbackQuery);
end;

procedure TTgBot.PrepareCommands;
begin
  // getMe и меню команд — в фоне: Start не ждёт сеть (см. описание TTgBot).
  FCore.BeginStartJob(FSetMyCommandsOnStart);
end;

function TTgBot.GetOnUnknownCommand: TProc<ITgContext>;
begin
  Result := FCore.GetOnUnknownCommand();
end;

procedure TTgBot.SetOnUnknownCommand(const AValue: TProc<ITgContext>);
begin
  FCore.SetOnUnknownCommand(AValue);
end;

function TTgBot.GetBotUserName: string;
begin
  Result := FCore.GetBotUserName;
end;

function TTgBot.Command(const AName: string; const AHandler: TProc<ITgContext>): TTgBot;
begin
  Result := Command([AName], '', AHandler);
end;

function TTgBot.Command(const AName, ADescription: string;
  const AHandler: TProc<ITgContext>): TTgBot;
begin
  Result := Command([AName], ADescription, AHandler);
end;

function TTgBot.Command(const ANames: array of string; const AHandler: TProc<ITgContext>): TTgBot;
begin
  Result := Command(ANames, '', AHandler);
end;

function TTgBot.Command(const ANames: array of string; const ADescription: string;
  const AHandler: TProc<ITgContext>): TTgBot;
var
  LKeys: TArray<string>;
  I: Integer;
begin
  if Length(ANames) = 0 then
    raise ETgError.Create(Format(TgRouterText(TTgRouterText.EmptyKey), ['Command']));
  // Сначала проверяются все имена: при ошибке не добавляется ни одно.
  SetLength(LKeys, Length(ANames));
  for I := 0 to High(ANames) do
    LKeys[I] := NormalizeCommandName(ANames[I]);
  // Описание (пункт меню) — только у первого имени, остальные — синонимы.
  for I := 0 to High(LKeys) do
    if I = 0 then
      FCore.SetRoute(TTgRouteKind.Command, LKeys[I], ADescription, AHandler)
    else
      FCore.SetRoute(TTgRouteKind.Command, LKeys[I], '', AHandler);
  Result := Self;
end;

function TTgBot.Callback(const AData: string; const AHandler: TProc<ITgContext>): TTgBot;
begin
  CheckRouteKey(AData, 'Callback');
  FCore.SetRoute(TTgRouteKind.Callback, AData, '', AHandler);
  Result := Self;
end;

function TTgBot.CallbackPrefix(const APrefix: string; const AHandler: TProc<ITgContext>): TTgBot;
begin
  CheckRouteKey(APrefix, 'CallbackPrefix');
  FCore.SetRoute(TTgRouteKind.CallbackPrefix, APrefix, '', AHandler);
  Result := Self;
end;

function TTgBot.Text(const AHandler: TProc<ITgContext>): TTgBot;
begin
  FCore.SetAnyText(AHandler);
  Result := Self;
end;

function TTgBot.Text(const AText: string; const AHandler: TProc<ITgContext>): TTgBot;
begin
  CheckRouteKey(AText, 'Text');
  FCore.SetRoute(TTgRouteKind.Text, AnsiLowerCase(AText), '', AHandler);
  Result := Self;
end;

function TTgBot.TextMatch(const APattern: string; const AHandler: TProc<ITgContext>): TTgBot;
var
  LMatcher: ITgTextMatcher;
begin
  CheckRouteKey(APattern, 'TextMatch');
  // Компиляция здесь: неверный шаблон — исключение в вызывающем потоке.
  LMatcher := TTgTextMatcher.Create(APattern);
  FCore.SetMatchRoute(LMatcher, AHandler);
  Result := Self;
end;

procedure TTgBot.Start;
var
  LGeneration: Integer;
begin
  // Из OnFault/OnError отказа: прежний запуск ещё не освобождён (его поток —
  // текущий), а FStarted мог быть ещё не выставлен вызвавшим Start потоком.
  if TgInFaultNotify then
    raise ETgError.Create(TgUpdatesText(TTgUpdatesText.StopFromHandler));
  if FStarted then
  begin
    if FCore.GetState <> TTgBotState.Faulted then
      raise ETgError.Create(TgUpdatesText(TTgUpdatesText.BotRunning));
    // Отказ приёма: освобождаем ресурсы прежнего запуска (дренаж принятого)
    // и запускаем заново. Из обработчика/OnFault Stop выбросит ETgError.
    Stop;
  end;
  // Webhook: проверки (URL, секрет, платформа) — до фоновых запросов и Running.
  if FMode = TTgReceiveMode.Webhook then
  begin
    PrepareWebhook;
    FActiveSource := FWebhookSourceRef;
  end
  else
    FActiveSource := FSourceRef;
  FSource.TimeoutSec := FPollTimeout;
  // allowed_updates сервер запоминает: без явного значения передаём [] (сброс
  // фильтра, оставленного прежним getUpdates/setWebhook с тем же токеном).
  if FAllowedUpdates.HasValue then
    FSource.AllowedUpdates := FAllowedUpdates
  else
    FSource.AllowedUpdates := TTgOptional<TArray<string>>.Create(nil);
  WarnFilteredHandlers;
  // getMe (username для /cmd@бот) и меню команд — в фоне, параллельно с
  // приёмом; '/cmd@бот' маршрутизируется после этого getMe.
  PrepareCommands;
  FSource.DropPendingUpdates := FDropPendingUpdates;
  FSource.AutoDeleteWebhook := FAutoDeleteWebhook;
  FSource.AckPolicy := FAckPolicy;
  FSource.DrainTimeoutMs := FDrainTimeoutMs;
  FDispatcher.MaxParallel := FMaxParallel;
  FDispatcher.QueueCapacity := FQueueCapacity;
  FDispatcher.Delivery := FDelivery;
  // Running — до запуска источника: отказ первого же getUpdates не потеряется.
  LGeneration := FCore.BeginRun;
  FSource.OnFault := TgNewFaultHandler(FCore, LGeneration);
  FWebhookSource.OnFault := TgNewFaultHandler(FCore, LGeneration);
  try
    FDispatcher.Start;
    try
      FActiveSource.Start(FDispatcherRef);
    except
      FDispatcher.Stop(TgDefaultDrainTimeoutMs);
      raise;
    end;
  except
    FCore.SetState(TTgBotState.Idle);
    // Фоновая подготовка не переживает неудачный запуск.
    FCore.FinishStartJob(0);
    raise;
  end;
  FStarted := True;
end;

function TTgBot.Stop(AWaitMs: Cardinal): Boolean;
var
  LWatch: TStopwatch;
  LLeft: Int64;
begin
  // Из обработчика ожидание остановки зависло бы на самом обработчике.
  // Из OnFault/OnError отказа — ожидание потока источника, который их вызвал.
  if TTgUpdateDispatcher.InHandler or TgInFaultNotify then
    raise ETgError.Create(TgUpdatesText(TTgUpdatesText.StopFromHandler));
  if not FStarted then
    Exit(True);
  FCore.SetState(TTgBotState.Stopping);
  LWatch := TStopwatch.StartNew;
  // Сначала источник: он дожидается обработки принятого (дренаж) и подтверждает offset.
  // В Faulted поток источника уже завершён — остаётся дренаж диспетчера.
  // Webhook: Accept сразу отвечает Unavailable, затем deleteWebhook (DeleteWebhookOnStop).
  Result := FActiveSource.Stop(AWaitMs);
  // Фоновые getMe/setMyCommands: дожидаемся (меню отправляется и при быстром
  // Stop), по истечении времени — отмена. Обработчики, ждущие getMe, к этому
  // моменту дождутся его завершения или отмены.
  LLeft := Max(Int64(AWaitMs) - LWatch.ElapsedMilliseconds, 100);
  if not FCore.FinishStartJob(Cardinal(LLeft)) then
    Result := False;
  LLeft := Max(Int64(AWaitMs) - LWatch.ElapsedMilliseconds, 100);
  if not FDispatcher.Stop(Cardinal(LLeft)) then
    Result := False;
  FStarted := False;
  FCore.SetState(TTgBotState.Idle);
end;

function TTgBot.Run: Boolean;
{$IFNDEF ANDROID}
var
  LMain: Boolean;
  LSignal: Boolean;
{$ENDIF}
begin
{$IFDEF ANDROID}
  raise ETgError.Create(TgUpdatesText(TTgUpdatesText.RunUnsupported));
{$ELSE}
  LMain := TThread.CurrentThread.ThreadID = MainThreadID;
  if (FDelivery = TTgDelivery.Main) and not LMain then
    raise ETgError.Create(TgUpdatesText(TTgUpdatesText.RunNotMainThread));
  AtomicExchange(FRunStopFlag, 0);
  TTgShutdownSignal.Reset;
  LSignal := TTgShutdownSignal.Install;
  try
    Start;
    try
      while (AtomicCmpExchange(FRunStopFlag, 0, 0) = 0) and
        not (LSignal and TTgShutdownSignal.Requested) and
        (GetState <> TTgBotState.Faulted) do
        if LMain then
          CheckSynchronize(100)
        else
          FRunWake.WaitFor(100);
      // До Stop: он переводит Faulted в Idle. Отказ уже доставлен в OnError/OnFault.
      Result := GetState <> TTgBotState.Faulted;
    finally
      Stop;
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

procedure TTgBot.RequestStop;
begin
  AtomicExchange(FRunStopFlag, 1);
  FRunWake.SetEvent;
end;

end.
