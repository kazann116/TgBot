unit TgBot.Updates;

{
  TgBot — приём и раздача обновлений (нижний слой, работает с сырым JSON
  и не зависит от сгенерированных типов TgBot.pas).

  - ITgRawUpdate / TTgRawUpdate — обновление: update_id, вид (ключ поля),
    ключ «полосы» ChatKey и JSON (обновление владеет своим объектом);
  - ITgUpdateSource / TTgLongPollSource — long polling (getUpdates) в
    собственном потоке: offset, политики подтверждения, паузы при ошибках,
    обработка 401/404/409, корректная остановка с дренажом и итоговым
    подтверждением;
  - TTgWebhookSource / ITgWebhookReceiver — webhook без HTTP-сервера:
    setWebhook/deleteWebhook, приём тела запроса из любого сервера (Accept),
    проверка секрета, дедупликация update_id, ограниченное ожидание очереди;
  - ITgUpdateSink / TTgUpdateDispatcher — раздача обработчику: обновления
    одного чата строго по порядку, разных чатов — параллельно (MaxParallel
    собственных потоков); доставка в рабочем потоке или в главном
    (TThread.Queue, без Synchronize);
  - TTgShutdownSignal — Ctrl+C / закрытие консоли (Windows),
    SIGINT/SIGTERM (Linux, macOS) для консольных ботов.

  Время жизни: потоки источника и диспетчера держат только счётчиковые
  ссылки на внутреннее состояние, поэтому Stop может «отпустить» поток,
  который не удалось прервать (транспорт без отмены, Linux/Android, зависший
  обработчик), — поздний результат такого потока выбрасывается.
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
  TgBot.Http;

const
  /// <summary>Таймаут long polling (параметр timeout getUpdates) по умолчанию, с.</summary>
  TgDefaultPollTimeoutSec = 50;
  /// <summary>Максимум обновлений за один getUpdates по умолчанию (1–100).</summary>
  TgDefaultPollLimit = 100;
  /// <summary>Ёмкость очереди диспетчера по умолчанию (обновлений).</summary>
  TgDefaultQueueCapacity = 1000;
  /// <summary>Число потоков диспетчера по умолчанию.</summary>
  TgDefaultMaxParallel = 4;
  /// <summary>Сколько Stop ждёт обработки уже принятых обновлений по умолчанию, мс.</summary>
  TgDefaultDrainTimeoutMs = 5000;
  /// <summary>Минимальный интервал между событиями OnConflict «другой getUpdates», мс.</summary>
  TgDefaultConflictNotifyMs = 60000;
  /// <summary>Разброс пауз между повторами по умолчанию, ± процентов.</summary>
  TgDefaultBackoffJitterPercent = 20;
  /// <summary>Первая пауза после ошибки getUpdates, мс (далее — удвоение).</summary>
  TgBackoffMinMs = 1000;
  /// <summary>Максимальная пауза после ошибки getUpdates, мс.</summary>
  TgBackoffMaxMs = 60000;
  /// <summary>Минимальная пауза после 409 «другой getUpdates», мс.</summary>
  TgConflictRetryMs = 5000;
  /// <summary>Наибольший размер тела webhook-запроса по умолчанию, байт (1 МБ).</summary>
  TgDefaultWebhookMaxBodySize = 1024 * 1024;
  /// <summary>Сколько Accept ждёт места в очереди по умолчанию, мс (затем Unavailable).</summary>
  TgDefaultWebhookPostTimeoutMs = 250;
  /// <summary>Окно дедупликации webhook по умолчанию: сколько последних update_id помнить.</summary>
  TgDefaultWebhookDedupWindow = 1000;
  /// <summary>Длина секрета webhook, генерируемого библиотекой (символы [A-Za-z0-9_-]).</summary>
  TgWebhookSecretLength = 48;

type
  /// <summary>Состояние источника обновлений.</summary>
  TTgSourceState = (
    /// <summary>Не запущен или остановлен.</summary>
    Idle,
    /// <summary>Принимает обновления.</summary>
    Running,
    /// <summary>Остановка запрошена (дренаж, итоговое подтверждение).</summary>
    Stopping,
    /// <summary>Остановлен из-за неустранимой ошибки (401, 404, webhook и т.п.).</summary>
    Faulted);

  /// <summary>Когда подтверждать (offset) принятые обновления.</summary>
  TTgAckPolicy = (
    /// <summary>
    ///   Сразу после приёма: следующий getUpdates отправляется, как только
    ///   пакет помещён в очередь (ограничение — ёмкость очереди). Быстро, но
    ///   при аварийном завершении процесса обновления из очереди теряются.
    /// </summary>
    AfterReceive,
    /// <summary>
    ///   После обработки: следующий getUpdates — только когда обработаны все
    ///   обновления пакета. Медленнее, зато при сбое пакет придёт повторно.
    /// </summary>
    AfterBatch);

  /// <summary>Где выполняются обработчики обновлений.</summary>
  TTgDelivery = (
    /// <summary>В потоках диспетчера (параллельно для разных чатов).</summary>
    Worker,
    /// <summary>
    ///   В главном потоке (TThread.Queue): для VCL/FMX — без ручной
    ///   синхронизации; в консоли главный поток должен вызывать
    ///   CheckSynchronize (это делает TTgBot.Run).
    /// </summary>
    Main);

  /// <summary>
  ///   Итог приёма webhook-запроса (TTgWebhookSource.Accept); HTTP-код
  ///   ответа — TgWebhookHttpStatus.
  /// </summary>
  TTgWebhookResult = (
    /// <summary>Принято (или повтор уже принятого update_id) — 200.</summary>
    Accepted,
    /// <summary>Неверный X-Telegram-Bot-Api-Secret-Token — 403.</summary>
    Forbidden,
    /// <summary>Тело не JSON-объект обновления, нет update_id или больше лимита — 400.</summary>
    BadRequest,
    /// <summary>
    ///   Источник не запущен, останавливается, в Faulted или очередь
    ///   переполнена — 503 (Telegram повторит доставку позже).
    /// </summary>
    Unavailable);

  /// <summary>Тексты сообщений модуля (для TgBot.pas).</summary>
  TTgUpdatesText = (SourceRunning, DispatcherRunning, StopFromHandler, NoChat,
    RunNotMainThread, RunUnsupported, BotRunning, HandlerFiltered, WebhookUrlRequired,
    WebhookBadSecret, WebhookUnsupported);

  /// <summary>
  ///   Обновление Bot API в сыром виде. Владеет своим JSON-объектом (не
  ///   освобождайте Json); живёт, пока на него есть ссылки.
  /// </summary>
  ITgRawUpdate = interface
    ['{D51FD45E-3FE0-4240-9B70-5A58992E6674}']
    function GetUpdateId: Int64;
    function GetKind: string;
    function GetChatKey: string;
    function GetJson: TJSONObject;
    /// <summary>update_id.</summary>
    property UpdateId: Int64 read GetUpdateId;
    /// <summary>Вид обновления — имя поля ('message', 'callback_query', …; TTgUpdateType).</summary>
    property Kind: string read GetKind;
    /// <summary>
    ///   Ключ порядка: id чата ('-100123'), 'u' + id пользователя для
    ///   обновлений без чата ('u42'), '' — порядок не важен (poll, poll_answer).
    /// </summary>
    property ChatKey: string read GetChatKey;
    /// <summary>JSON обновления целиком (владелец — обновление).</summary>
    property Json: TJSONObject read GetJson;
  end;

  /// <summary>Приёмник обновлений (очередь диспетчера).</summary>
  ITgUpdateSink = interface
    ['{C83E716B-723A-43C2-8DE7-FCC6C6BAD5BF}']
    /// <summary>
    ///   Ставит обновление в очередь; при полной очереди ждёт места.
    ///   False — приёмник остановлен или ACancel отменён (обновление не принято).
    /// </summary>
    function Post(const AUpdate: ITgRawUpdate; const ACancel: ITgCancellation): Boolean;
  end;

  /// <summary>
  ///   Приёмник с ограниченным ожиданием места в очереди (webhook: поток
  ///   HTTP-сервера не должен висеть на полной очереди).
  /// </summary>
  ITgTimedUpdateSink = interface
    ['{8E4B1F0A-6C2D-4E73-9A5B-3D7F2C1E8B64}']
    /// <summary>
    ///   Как Post, но место в очереди ждёт не дольше ATimeoutMs мс (0 — не
    ///   ждёт). False — очередь полна, приёмник остановлен или ACancel отменён.
    /// </summary>
    function TryPost(const AUpdate: ITgRawUpdate; const ACancel: ITgCancellation;
      ATimeoutMs: Cardinal): Boolean;
  end;

  /// <summary>
  ///   Приём тела webhook-запроса из любого HTTP-сервера (потокобезопасно,
  ///   из любого числа потоков). ASecretHeader — значение заголовка
  ///   X-Telegram-Bot-Api-Secret-Token ('' — заголовка нет).
  /// </summary>
  ITgWebhookReceiver = interface
    ['{4F7A2C9E-1B3D-4A86-8E5F-6C0D9B2A7E31}']
    /// <summary>Тело — байты UTF-8 (как пришли по сети).</summary>
    function Accept(const ABody: TBytes; const ASecretHeader: string): TTgWebhookResult; overload;
    /// <summary>Тело — уже декодированная строка.</summary>
    function Accept(const ABody, ASecretHeader: string): TTgWebhookResult; overload;
  end;

  /// <summary>Источник обновлений (long polling или webhook).</summary>
  ITgUpdateSource = interface
    ['{2EB5AB98-37B8-4632-8BB9-B64429C8269B}']
    /// <summary>Запускает приём в ASink. Повторный Start работающего источника — ETgError.</summary>
    procedure Start(const ASink: ITgUpdateSink);
    /// <summary>
    ///   Останавливает приём не дольше ≈AWaitMs мс. False — поток не удалось
    ///   прервать и он отпущен (его поздний результат будет выброшен).
    /// </summary>
    function Stop(AWaitMs: Cardinal): Boolean;
    /// <summary>Обновление AUpdateId обработано (для подтверждения offset).</summary>
    procedure Processed(AUpdateId: Int64);
    function GetState: TTgSourceState;
    /// <summary>Состояние источника.</summary>
    property State: TTgSourceState read GetState;
  end;

  /// <summary>Часы и паузы источника (подменяются в тестах).</summary>
  ITgPollTimer = interface
    ['{CD72B2B4-FC57-46C4-958D-A76187CBB215}']
    /// <summary>Монотонное время, мс.</summary>
    function NowMs: Int64;
    /// <summary>Пауза AMs мс; True — прервана отменой ACancel.</summary>
    function Sleep(AMs: Cardinal; const ACancel: ITgCancellation): Boolean;
  end;

  /// <summary>Обработчик обновления нижнего уровня.</summary>
  TTgRawHandler = reference to procedure(const AUpdate: ITgRawUpdate);
  /// <summary>Обработчик исключения обработчика (объект исключения действителен только внутри).</summary>
  TTgRawErrorHandler = reference to procedure(AError: Exception; const AUpdate: ITgRawUpdate);
  /// <summary>Событие конфликта 409 (объект исключения действителен только внутри).</summary>
  TTgConflictHandler = reference to procedure(AError: ETgConflictError);

  /// <summary>Реализация ITgRawUpdate.</summary>
  TTgRawUpdate = class(TInterfacedObject, ITgRawUpdate)
  private
    FJson: TJSONObject;
    FUpdateId: Int64;
    FKind: string;
    FChatKey: string;
  public
    /// <summary>
    ///   Владение AJson переходит к обновлению сразу (в т.ч. при исключении
    ///   конструктора). update_id не целое — ETgError.
    /// </summary>
    constructor Create(AJson: TJSONObject);
    destructor Destroy; override;
    /// <summary>Вид обновления: первое поле, кроме update_id; '' — нет.</summary>
    class function KindOf(AJson: TJSONObject): string; static;
    /// <summary>
    ///   Ключ порядка: chat.id полезной нагрузки (для callback_query —
    ///   message.chat.id); иначе 'u' + from.id (или user.id); poll,
    ///   poll_answer и обновления без чата и пользователя — ''.
    /// </summary>
    class function ChatKeyOf(AJson: TJSONObject): string; static;
    function GetUpdateId: Int64;
    function GetKind: string;
    function GetChatKey: string;
    function GetJson: TJSONObject;
  end;

  /// <summary>Часы и паузы по умолчанию (TStopwatch, WaitFor токена).</summary>
  TTgSystemPollTimer = class(TInterfacedObject, ITgPollTimer)
  private
    FWatch: TStopwatch;
  public
    constructor Create;
    function NowMs: Int64;
    function Sleep(AMs: Cardinal; const ACancel: ITgCancellation): Boolean;
  end;

  /// <summary>
  ///   Long polling (getUpdates) в собственном потоке. Настройки задаются до
  ///   Start. События OnConflict/OnError/OnFault вызываются в потоке
  ///   источника, их исключения поглощаются.
  ///
  ///   Ошибки: сеть, 5xx, прочие — пауза 1, 2, 4 … 60 с (± JitterPercent),
  ///   прерываемая Stop, сброс после успешного ответа; 429 — не меньше
  ///   retry_after; 401/404 — Faulted без повторов; 409 «webhook is active» —
  ///   deleteWebhook и повтор (AutoDeleteWebhook) или OnConflict + Faulted;
  ///   409 «другой getUpdates» — OnConflict (не чаще ConflictNotifyIntervalMs)
  ///   и повтор не раньше чем через 5 с.
  ///
  ///   Остановка: отмена висящего запроса (Windows/macOS — прерывание HTTP;
  ///   Linux/Android и транспорт без отмены — поток отпускается), дренаж
  ///   принятых обновлений (Processed) не дольше DrainTimeoutMs (и половины
  ///   AWaitMs), итоговый getUpdates(offset = наименьший необработанный,
  ///   timeout = 0, limit = 1). Ответ, пришедший после Stop, выбрасывается
  ///   без сдвига offset.
  /// </summary>
  TTgLongPollSource = class(TInterfacedObject, ITgUpdateSource)
  private
    FLock: TCriticalSection;
    FTransport: ITgTransport;
    FParentCancel: ITgCancellation;
    // Текущее внутреннее состояние (TTgPollCore) и ссылка, удерживающая его.
    FCore: TObject;
    FCoreRef: IInterface;
    FResumeOffset: Int64;
    FLimit: Integer;
    FTimeoutSec: Integer;
    FAllowedUpdates: TTgOptional<TArray<string>>;
    FDropPendingUpdates: Boolean;
    FAutoDeleteWebhook: Boolean;
    FAckPolicy: TTgAckPolicy;
    FDrainTimeoutMs: Cardinal;
    FConflictNotifyIntervalMs: Cardinal;
    FJitterPercent: Integer;
    FTimer: ITgPollTimer;
    FOnConflict: TTgConflictHandler;
    FOnError: TProc<Exception>;
    FOnFault: TProc<Exception>;
    function CurrentCore(out ARef: IInterface): TObject;
    function GetOffset: Int64;
    function GetConfirmedOffset: Int64;
  public
    /// <summary>
    ///   Источник поверх транспорта ATransport (тот же, что у TTgApi). Вызовы
    ///   прерываются и отменой AParentCancel (например, TTgApi.CancelToken).
    /// </summary>
    constructor Create(const ATransport: ITgTransport; const AParentCancel: ITgCancellation = nil);
    /// <summary>
    ///   Не блокирует: запрашивает остановку (отмена висящего getUpdates) и
    ///   ждёт поток не дольше 30 мс. Незавершившийся поток держит своё
    ///   состояние сам: дренаж (не дольше DrainTimeoutMs) и итоговое
    ///   подтверждение выполняются в фоне, затем поток освобождается. Для
    ///   гарантированного подтверждения до выхода из программы — Stop.
    /// </summary>
    destructor Destroy; override;
    procedure Start(const ASink: ITgUpdateSink);
    function Stop(AWaitMs: Cardinal): Boolean;
    procedure Processed(AUpdateId: Int64);
    function GetState: TTgSourceState;
    /// <summary>
    ///   Ждёт фактического завершения потока источника (в т.ч. отпущенного
    ///   при Stop = False). True — поток завершён или не запускался.
    /// </summary>
    function WaitForThread(AMs: Cardinal): Boolean;
    /// <summary>Состояние источника.</summary>
    property State: TTgSourceState read GetState;
    /// <summary>offset следующего запроса getUpdates (последний принятый update_id + 1; 0 — не было).</summary>
    property Offset: Int64 read GetOffset;
    /// <summary>offset, подтверждённый серверу (последний успешный getUpdates или итоговый).</summary>
    property ConfirmedOffset: Int64 read GetConfirmedOffset;
    /// <summary>limit getUpdates (1–100), по умолчанию TgDefaultPollLimit.</summary>
    property Limit: Integer read FLimit write FLimit;
    /// <summary>timeout getUpdates, с (0 — короткий опрос), по умолчанию TgDefaultPollTimeoutSec.</summary>
    property TimeoutSec: Integer read FTimeoutSec write FTimeoutSec;
    /// <summary>
    ///   allowed_updates (TTgUpdateType.*). Не задано — не передаётся (сервер
    ///   помнит прежнее значение); пустой массив — все, кроме chat_member,
    ///   message_reaction и message_reaction_count. TTgBot при Start всегда
    ///   задаёт значение (без явного TTgBot.AllowedUpdates — пустой массив).
    /// </summary>
    property AllowedUpdates: TTgOptional<TArray<string>> read FAllowedUpdates write FAllowedUpdates;
    /// <summary>При старте вызвать deleteWebhook(drop_pending_updates = true): пропустить накопившееся.</summary>
    property DropPendingUpdates: Boolean read FDropPendingUpdates write FDropPendingUpdates;
    /// <summary>При 409 «webhook is active» удалить webhook и продолжить (по умолчанию False).</summary>
    property AutoDeleteWebhook: Boolean read FAutoDeleteWebhook write FAutoDeleteWebhook;
    /// <summary>Политика подтверждения, по умолчанию AfterReceive.</summary>
    property AckPolicy: TTgAckPolicy read FAckPolicy write FAckPolicy;
    /// <summary>Дренаж при Stop, мс (по умолчанию TgDefaultDrainTimeoutMs).</summary>
    property DrainTimeoutMs: Cardinal read FDrainTimeoutMs write FDrainTimeoutMs;
    /// <summary>Минимальный интервал OnConflict для «другого getUpdates», мс.</summary>
    property ConflictNotifyIntervalMs: Cardinal read FConflictNotifyIntervalMs
      write FConflictNotifyIntervalMs;
    /// <summary>Разброс пауз, ± процентов (0–50), по умолчанию 20.</summary>
    property JitterPercent: Integer read FJitterPercent write FJitterPercent;
    /// <summary>Часы и паузы (nil — системные).</summary>
    property Timer: ITgPollTimer read FTimer write FTimer;
    /// <summary>409: другой экземпляр бота или установлен webhook.</summary>
    property OnConflict: TTgConflictHandler read FOnConflict write FOnConflict;
    /// <summary>Временная ошибка getUpdates (перед паузой и повтором).</summary>
    property OnError: TProc<Exception> read FOnError write FOnError;
    /// <summary>Неустранимая ошибка: источник перешёл в Faulted.</summary>
    property OnFault: TProc<Exception> read FOnFault write FOnFault;
  end;

  /// <summary>
  ///   Webhook без собственного HTTP-сервера: тело запроса передаёт Accept
  ///   (из потока любого сервера — WebBroker, Horse, mORMot, Indy…), ответ
  ///   серверу Telegram — TgWebhookHttpStatus(результат). Настройки задаются
  ///   до Start.
  ///
  ///   Start: при RegisterOnStart (по умолчанию) в служебном потоке источника
  ///   вызывается setWebhook (url, secret_token, allowed_updates,
  ///   max_connections, drop_pending_updates, ip_address, certificate);
  ///   любая его ошибка неустранима — Faulted и OnFault (в этом потоке).
  ///   Accept работает сразу после Start, не дожидаясь setWebhook.
  ///
  ///   Accept: Running → секрет (сравнение за постоянное время; пустой
  ///   SecretToken — без проверки) → размер (MaxBodySize) → JSON с целым
  ///   update_id → дедупликация (последние DedupWindow принятых update_id:
  ///   повтор — Accepted без повторной обработки) → постановка в очередь с
  ///   ожиданием не дольше PostTimeoutMs (полная очередь — Unavailable,
  ///   update_id не запоминается: повтор Telegram будет принят).
  ///   Подтверждение — сам ответ 200, Processed ничего не делает.
  ///
  ///   Stop: Accept сразу отвечает Unavailable, висящие в ожидании места
  ///   освобождаются; незавершённый setWebhook дожидается (≈AWaitMs, затем
  ///   отмена); при DeleteOnStop — deleteWebhook в пределах того же бюджета.
  ///   Секрет и токен в тексты исключений и событий не попадают.
  /// </summary>
  TTgWebhookSource = class(TInterfacedObject, ITgUpdateSource, ITgWebhookReceiver)
  private
    FLock: TCriticalSection;
    FTransport: ITgTransport;
    FParentCancel: ITgCancellation;
    // Текущее внутреннее состояние (TTgWebhookCore) и ссылка, удерживающая его.
    FCore: TObject;
    FCoreRef: IInterface;
    FUrl: string;
    FSecretToken: string;
    FMaxConnections: Integer;
    FDropPendingUpdates: Boolean;
    FIpAddress: string;
    FCertificate: TTgInputFile;
    FAllowedUpdates: TTgOptional<TArray<string>>;
    FRegisterOnStart: Boolean;
    FDeleteOnStop: Boolean;
    FMaxBodySize: Integer;
    FPostTimeoutMs: Cardinal;
    FDedupWindow: Integer;
    FOnError: TProc<Exception>;
    FOnFault: TProc<Exception>;
    // Дедупликация (под FLock, переживает Stop/Start): множество и порядок.
    FSeen: TDictionary<Int64, Byte>;
    FSeenOrder: TList<Int64>;
    function CurrentCore(out ARef: IInterface): TObject;
    /// <summary>Разобранное тело AJson (во владении метода) — в очередь ядра ACore.</summary>
    function Deliver(ACore: TObject; AJson: TJSONObject): TTgWebhookResult;
    /// <summary>Проверки до разбора тела: состояние и секрет.</summary>
    function Admit(out ARef: IInterface; out ACore: TObject; const ASecretHeader: string): TTgWebhookResult;
  public
    /// <summary>
    ///   Источник поверх транспорта ATransport (тот же, что у TTgApi): через
    ///   него идут setWebhook и deleteWebhook. Вызовы прерываются и отменой
    ///   AParentCancel (например, TTgApi.CancelToken).
    /// </summary>
    constructor Create(const ATransport: ITgTransport; const AParentCancel: ITgCancellation = nil);
    /// <summary>
    ///   Не блокирует: запрашивает остановку и ждёт служебный поток не дольше
    ///   30 мс; незавершившийся поток (висящий setWebhook/deleteWebhook)
    ///   держит своё состояние сам. Для deleteWebhook при DeleteOnStop — Stop.
    /// </summary>
    destructor Destroy; override;
    procedure Start(const ASink: ITgUpdateSink);
    function Stop(AWaitMs: Cardinal): Boolean;
    /// <summary>Ничего не делает: подтверждение webhook — ответ 200.</summary>
    procedure Processed(AUpdateId: Int64);
    function GetState: TTgSourceState;
    function Accept(const ABody: TBytes; const ASecretHeader: string): TTgWebhookResult; overload;
    function Accept(const ABody, ASecretHeader: string): TTgWebhookResult; overload;
    /// <summary>
    ///   Ждёт завершения служебного потока (в т.ч. отпущенного при Stop =
    ///   False). True — завершён или не запускался.
    /// </summary>
    function WaitForThread(AMs: Cardinal): Boolean;
    /// <summary>
    ///   Случайный секрет длины ALength (1–256) из символов [A-Za-z0-9_-]
    ///   (криптостойкий генератор ОС). Недоступен генератор — ETgError.
    /// </summary>
    class function GenerateSecretToken(ALength: Integer = TgWebhookSecretLength): string; static;
    /// <summary>Секрет допустим для Bot API: 1–256 символов [A-Za-z0-9_-].</summary>
    class function IsValidSecretToken(const AValue: string): Boolean; static;
    /// <summary>Состояние источника.</summary>
    property State: TTgSourceState read GetState;
    /// <summary>Внешний HTTPS-URL webhook (параметр url setWebhook).</summary>
    property Url: string read FUrl write FUrl;
    /// <summary>
    ///   secret_token: Telegram присылает его в заголовке
    ///   X-Telegram-Bot-Api-Secret-Token, Accept сверяет. Пусто — не
    ///   передаётся и не проверяется (TTgBot всегда задаёт значение).
    /// </summary>
    property SecretToken: string read FSecretToken write FSecretToken;
    /// <summary>max_connections (1–100); 0 — не передаётся (значение сервера, 40).</summary>
    property MaxConnections: Integer read FMaxConnections write FMaxConnections;
    /// <summary>drop_pending_updates setWebhook: пропустить накопившиеся обновления.</summary>
    property DropPendingUpdates: Boolean read FDropPendingUpdates write FDropPendingUpdates;
    /// <summary>ip_address setWebhook (вместо адреса из DNS); пусто — не передаётся.</summary>
    property IpAddress: string read FIpAddress write FIpAddress;
    /// <summary>Публичный ключ самоподписанного сертификата (certificate); пусто — нет.</summary>
    property Certificate: TTgInputFile read FCertificate write FCertificate;
    /// <summary>allowed_updates; не задано — не передаётся (см. TTgLongPollSource.AllowedUpdates).</summary>
    property AllowedUpdates: TTgOptional<TArray<string>> read FAllowedUpdates write FAllowedUpdates;
    /// <summary>
    ///   Вызывать setWebhook при Start (по умолчанию True). False — webhook
    ///   зарегистрирован заранее (вручную или другим процессом).
    /// </summary>
    property RegisterOnStart: Boolean read FRegisterOnStart write FRegisterOnStart;
    /// <summary>Вызывать deleteWebhook при Stop (по умолчанию False).</summary>
    property DeleteOnStop: Boolean read FDeleteOnStop write FDeleteOnStop;
    /// <summary>Наибольший размер тела, байт UTF-8 (по умолчанию 1 МБ); больше — BadRequest.</summary>
    property MaxBodySize: Integer read FMaxBodySize write FMaxBodySize;
    /// <summary>Сколько Accept ждёт места в очереди, мс (по умолчанию 250).</summary>
    property PostTimeoutMs: Cardinal read FPostTimeoutMs write FPostTimeoutMs;
    /// <summary>Сколько последних update_id помнить для дедупликации (0 — без неё).</summary>
    property DedupWindow: Integer read FDedupWindow write FDedupWindow;
    /// <summary>Ошибка deleteWebhook при Stop (в служебном потоке; исключения поглощаются).</summary>
    property OnError: TProc<Exception> read FOnError write FOnError;
    /// <summary>Ошибка setWebhook: источник перешёл в Faulted (в служебном потоке).</summary>
    property OnFault: TProc<Exception> read FOnFault write FOnFault;
  end;

  /// <summary>
  ///   Диспетчер обновлений: «полосы» по ChatKey (обновления одного чата —
  ///   строго по порядку, разных — параллельно), MaxParallel собственных
  ///   потоков, общая очередь готовых полос, ёмкость QueueCapacity.
  ///   Обработчик выполняется внутри TTgCancelScope с токеном диспетчера
  ///   (вызовы TTgApi без явного токена прерываются при Stop). Исключение
  ///   обработчика передаётся в OnError (исключения OnError поглощаются),
  ///   обновление считается обработанным (OnProcessed).
  /// </summary>
  TTgUpdateDispatcher = class(TInterfacedObject, ITgUpdateSink, ITgTimedUpdateSink)
  private
    FLock: TCriticalSection;
    FCore: TObject;
    FCoreRef: IInterface;
    FHandler: TTgRawHandler;
    FOnError: TTgRawErrorHandler;
    FOnProcessed: TProc<Int64>;
    FMaxParallel: Integer;
    FQueueCapacity: Integer;
    FDelivery: TTgDelivery;
    function CurrentCore(out ARef: IInterface): TObject;
    function GetActive: Boolean;
    function GetCancel: ITgCancellation;
  public
    /// <summary>Диспетчер с обработчиком AHandler.</summary>
    constructor Create(const AHandler: TTgRawHandler);
    /// <summary>
    ///   Не блокирует: отменяет токен, выбрасывает очередь и ждёт потоки не
    ///   дольше 30 мс (без CheckSynchronize). Поток с зависшим обработчиком
    ///   отпускается: состояние диспетчера живёт, пока обработчик не вернётся.
    ///   Дождаться обработчиков — Stop(AWaitMs) до Free.
    /// </summary>
    destructor Destroy; override;
    /// <summary>Запускает потоки. Повторный Start работающего диспетчера — ETgError.</summary>
    procedure Start;
    /// <summary>
    ///   Отменяет токен диспетчера, выбрасывает необработанную очередь и ждёт
    ///   потоки не дольше AWaitMs (из главного потока — с CheckSynchronize).
    ///   False — потоки с зависшими обработчиками отпущены.
    /// </summary>
    function Stop(AWaitMs: Cardinal): Boolean;
    /// <summary>Ждёт, пока очередь опустеет и обработчики завершатся; True — дождались.</summary>
    function WaitIdle(AMs: Cardinal): Boolean;
    function Post(const AUpdate: ITgRawUpdate; const ACancel: ITgCancellation): Boolean;
    function TryPost(const AUpdate: ITgRawUpdate; const ACancel: ITgCancellation;
      ATimeoutMs: Cardinal): Boolean;
    /// <summary>Текущий поток выполняет обработчик диспетчера.</summary>
    class function InHandler: Boolean; static;
    /// <summary>Диспетчер запущен и не останавливается.</summary>
    property Active: Boolean read GetActive;
    /// <summary>Токен отмены текущего запуска (nil — не запущен).</summary>
    property Cancel: ITgCancellation read GetCancel;
    /// <summary>Число потоков (1–64), по умолчанию TgDefaultMaxParallel; задаётся до Start.</summary>
    property MaxParallel: Integer read FMaxParallel write FMaxParallel;
    /// <summary>Ёмкость очереди, по умолчанию TgDefaultQueueCapacity; задаётся до Start.</summary>
    property QueueCapacity: Integer read FQueueCapacity write FQueueCapacity;
    /// <summary>Где выполнять обработчик; задаётся до Start.</summary>
    property Delivery: TTgDelivery read FDelivery write FDelivery;
    /// <summary>Исключение обработчика (в потоке обработчика); задаётся до Start.</summary>
    property OnError: TTgRawErrorHandler read FOnError write FOnError;
    /// <summary>Обновление обработано (в т.ч. с исключением); задаётся до Start.</summary>
    property OnProcessed: TProc<Int64> read FOnProcessed write FOnProcessed;
  end;

  /// <summary>
  ///   Сигнал завершения консольной программы: Windows — Ctrl+C, Ctrl+Break,
  ///   закрытие окна, выход из системы, выключение (для трёх последних
  ///   обработчик ждёт NotifyStopped до 4,5 с — затем Windows завершает
  ///   процесс); Linux/macOS — SIGINT, SIGTERM (обработчик только атомарно
  ///   пишет флаг; прежние обработчики восстанавливаются в Uninstall);
  ///   Android — недоступно (Install = False).
  /// </summary>
  TTgShutdownSignal = class sealed
  public
    /// <summary>Устанавливает обработчики (вложенные вызовы считаются); False — недоступно.</summary>
    class function Install: Boolean; static;
    /// <summary>Снимает обработчики (парно Install).</summary>
    class procedure Uninstall; static;
    /// <summary>Сигнал получен (или вызван Request).</summary>
    class function Requested: Boolean; static;
    /// <summary>Программный запрос завершения (как сигнал).</summary>
    class procedure Request; static;
    /// <summary>Сбрасывает признак сигнала и «остановлен».</summary>
    class procedure Reset; static;
    /// <summary>Программа остановилась: обработчик закрытия консоли может вернуть управление.</summary>
    class procedure NotifyStopped; static;
    /// <summary>Сигналы поддерживаются на этой платформе.</summary>
    class function Supported: Boolean; static;
  end;

/// <summary>Локализованный текст модуля (служебное, для TgBot.pas).</summary>
function TgUpdatesText(AText: TTgUpdatesText): string;

/// <summary>
///   Ждёт AEvent не дольше AMs мс; в главном потоке при этом выполняет
///   CheckSynchronize (обработчики с Delivery = Main не блокируются).
/// </summary>
function TgWaitEventPumping(AEvent: TEvent; AMs: Cardinal): Boolean;

/// <summary>HTTP-код ответа на webhook-запрос: 200, 403, 400 или 503.</summary>
function TgWebhookHttpStatus(AResult: TTgWebhookResult): Integer;

implementation

uses
{$IFDEF MSWINDOWS}
  Winapi.Windows,
{$ENDIF}
{$IF defined(POSIX) and not defined(ANDROID)}
  Posix.Signal,
{$IFEND}
  System.Math,
  System.StrUtils;

resourcestring
  SRuSourceRunning = 'Источник обновлений уже запущен';
  SEnSourceRunning = 'Update source is already running';
  SRuDispatcherRunning = 'Диспетчер обновлений уже запущен';
  SEnDispatcherRunning = 'Update dispatcher is already running';
  SRuStopFromHandler = 'Нельзя ждать остановки бота из обработчика обновления: ' +
    'используйте RequestStop';
  SEnStopFromHandler = 'Cannot wait for the bot to stop from an update handler: ' +
    'use RequestStop';
  SRuNoChat = 'В обновлении нет чата для ответа';
  SEnNoChat = 'The update has no chat to reply to';
  SRuRunNotMainThread = 'Run с Delivery = Main можно вызывать только из главного потока';
  SEnRunNotMainThread = 'Run with Delivery = Main must be called from the main thread';
  SRuRunUnsupported = 'Run недоступен на этой платформе: используйте Start и Stop';
  SEnRunUnsupported = 'Run is not available on this platform: use Start and Stop';
  SRuBotRunning = 'Бот уже запущен';
  SEnBotRunning = 'The bot is already running';
  SRuHandlerFiltered = 'Назначен %s, но AllowedUpdates не содержит "%s": ' +
    'такие обновления сервер присылать не будет';
  SEnHandlerFiltered = '%s is assigned, but AllowedUpdates does not include "%s": ' +
    'the server will not send such updates';
  SRuWebhookUrlRequired = 'Режим Webhook: не задан WebhookUrl (внешний HTTPS-адрес бота)';
  SEnWebhookUrlRequired = 'Webhook mode: WebhookUrl (the public HTTPS address of the bot) is not set';
  SRuWebhookBadSecret = 'Недопустимый секрет webhook: нужно 1–256 символов A-Z, a-z, 0-9, "_" и "-"';
  SEnWebhookBadSecret = 'Invalid webhook secret: 1-256 characters A-Z, a-z, 0-9, "_" and "-" are required';
  SRuWebhookUnsupported = 'Режим Webhook недоступен на этой платформе: используйте Polling';
  SEnWebhookUnsupported = 'Webhook mode is not available on this platform: use Polling';
  SRuNoRandom = 'Криптостойкий генератор случайных чисел ОС недоступен';
  SEnNoRandom = 'The OS cryptographic random number generator is not available';

const
  CUpdatesTexts: array[TTgUpdatesText, TTgLanguage] of PResStringRec = (
    (@SRuSourceRunning, @SEnSourceRunning),
    (@SRuDispatcherRunning, @SEnDispatcherRunning),
    (@SRuStopFromHandler, @SEnStopFromHandler),
    (@SRuNoChat, @SEnNoChat),
    (@SRuRunNotMainThread, @SEnRunNotMainThread),
    (@SRuRunUnsupported, @SEnRunUnsupported),
    (@SRuBotRunning, @SEnBotRunning),
    (@SRuHandlerFiltered, @SEnHandlerFiltered),
    (@SRuWebhookUrlRequired, @SEnWebhookUrlRequired),
    (@SRuWebhookBadSecret, @SEnWebhookBadSecret),
    (@SRuWebhookUnsupported, @SEnWebhookUnsupported)
  );
  CNoRandomTexts: array[TTgLanguage] of PResStringRec = (@SRuNoRandom, @SEnNoRandom);
  // Алфавит секрета webhook: 64 символа — байт mod 64 распределён равномерно.
  CSecretAlphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-';
  // Сколько Stop источника ждёт поток после отмены итогового запроса, мс.
  CFinalGraceMs = 100;
  // Предел потоков диспетчера.
  CMaxParallelLimit = 64;
  // Сколько Destroy диспетчера/источника ждёт свои потоки (если остановку ещё
  // не запрашивали), мс; дальше потоки отпускаются — ядро держат они сами.
  CDestroyGraceMs = 30;

function TgUpdatesText(AText: TTgUpdatesText): string;
begin
  Result := LoadResString(CUpdatesTexts[AText, TgGetLanguage]);
end;

function TgWebhookHttpStatus(AResult: TTgWebhookResult): Integer;
begin
  case AResult of
    TTgWebhookResult.Accepted:
      Result := 200;
    TTgWebhookResult.Forbidden:
      Result := 403;
    TTgWebhookResult.BadRequest:
      Result := 400;
  else
    Result := 503;
  end;
end;

{$IFDEF MSWINDOWS}
// RtlGenRandom (экспорт SystemFunction036 advapi32): криптостойкий генератор ОС.
function TgRtlGenRandom(ABuffer: Pointer; ALength: ULONG): Boolean; stdcall;
  external advapi32 name 'SystemFunction036';
{$ENDIF}

/// <summary>Криптостойкие случайные байты ОС; недоступно — ETgError.</summary>
function TgRandomBytes(ACount: Integer): TBytes;
{$IFNDEF MSWINDOWS}
var
  LStream: TFileStream;
{$ENDIF}
begin
  SetLength(Result, ACount);
  if ACount <= 0 then
    Exit;
{$IFDEF MSWINDOWS}
  if not TgRtlGenRandom(@Result[0], ACount) then
    raise ETgError.Create(LoadResString(CNoRandomTexts[TgGetLanguage]));
{$ELSE}
  // Linux, Android, macOS, iOS: /dev/urandom (CreateGUID на POSIX — по времени).
  try
    LStream := TFileStream.Create('/dev/urandom', fmOpenRead or fmShareDenyNone);
    try
      LStream.ReadBuffer(Result[0], ACount);
    finally
      LStream.Free;
    end;
  except
    raise ETgError.Create(LoadResString(CNoRandomTexts[TgGetLanguage]));
  end;
{$ENDIF}
end;

/// <summary>
///   Сравнение секрета за время, зависящее только от длины AExpected (без
///   раннего выхода на первом несовпадении).
/// </summary>
function TgSecretEquals(const AExpected, AActual: string): Boolean;
var
  I, LActualLen: Integer;
  LDiff, LChar: Cardinal;
begin
  LActualLen := Length(AActual);
  LDiff := Cardinal(Length(AExpected) xor LActualLen);
  for I := 1 to Length(AExpected) do
  begin
    // Короткий AActual читается по кругу: объём работы не зависит от его длины.
    if LActualLen > 0 then
      LChar := Ord(AActual[((I - 1) mod LActualLen) + 1])
    else
      LChar := 0;
    LDiff := LDiff or (Cardinal(Ord(AExpected[I])) xor LChar);
  end;
  Result := LDiff = 0;
end;

function TgWaitEventPumping(AEvent: TEvent; AMs: Cardinal): Boolean;
var
  LWatch: TStopwatch;
  LLeft: Int64;
begin
  if TThread.CurrentThread.ThreadID <> MainThreadID then
    Exit(AEvent.WaitFor(AMs) = TWaitResult.wrSignaled);
  LWatch := TStopwatch.StartNew;
  while True do
  begin
    if AEvent.WaitFor(0) = TWaitResult.wrSignaled then
      Exit(True);
    LLeft := Int64(AMs) - LWatch.ElapsedMilliseconds;
    if LLeft <= 0 then
      Exit(False);
    try
      CheckSynchronize(Integer(Min(LLeft, 10)));
    except
      // Исключение чужой процедуры из очереди не должно прерывать остановку.
      if Assigned(ApplicationHandleException) then
        ApplicationHandleException(nil);
    end;
  end;
end;

/// <summary>
///   Вызов метода Bot API через транспорт с токеном отмены (как
///   TTgApiCore.Call, но без клиента: потоки держат только счётчиковые ссылки).
/// </summary>
function CallTransport(const ATransport: ITgTransport; const AMethod: string;
  AParams: TTgParams; const AToken: ITgCancellation): TJSONValue;
var
  LCancellable: ITgCancellableTransport;
  LScope: TTgCancelScope;
begin
  if Supports(ATransport, ITgCancellableTransport, LCancellable) then
    Exit(LCancellable.ExecuteEx(AMethod, AParams, AToken));
  // Транспорт без токенов: проверки до и после; токен доступен ему как окружающий.
  AToken.ThrowIfCancelled;
  LScope := TTgCancelScope.Enter(AToken);
  try
    Result := ATransport.Execute(AMethod, AParams);
  finally
    LScope.Leave;
  end;
  if AToken.IsCancelled then
  begin
    FreeAndNil(Result);
    raise ETgCancelledError.Create(TgText(TTgText.Cancelled));
  end;
end;

/// <summary>Вызывает колбэк, поглощая его исключения.</summary>
procedure InvokeQuietly(const AProc: TProc);
begin
  try
    AProc();
  except
    // Исключения пользовательских событий не прерывают работу потоков.
  end;
end;

{ TTgRawUpdate }

constructor TTgRawUpdate.Create(AJson: TJSONObject);
begin
  // Владение — сразу: при исключении деструктор освободит JSON.
  FJson := AJson;
  inherited Create;
  if not Assigned(FJson) then
    raise EArgumentNilException.Create('AJson');
  FUpdateId := TTgJson.GetInt64(FJson, 'update_id');
  FKind := KindOf(FJson);
  try
    FChatKey := ChatKeyOf(FJson);
  except
    // Некорректный id чата не мешает обработке: обновление идёт без порядка.
    FChatKey := '';
  end;
end;

destructor TTgRawUpdate.Destroy;
begin
  FreeAndNil(FJson);
  inherited Destroy;
end;

class function TTgRawUpdate.KindOf(AJson: TJSONObject): string;
var
  I: Integer;
begin
  Result := '';
  if not Assigned(AJson) then
    Exit;
  for I := 0 to AJson.Count - 1 do
    if AJson.Pairs[I].JsonString.Value <> 'update_id' then
      Exit(AJson.Pairs[I].JsonString.Value);
end;

class function TTgRawUpdate.ChatKeyOf(AJson: TJSONObject): string;

  function ChatOf(AObj: TJSONObject): string;
  var
    LChat: TJSONObject;
  begin
    LChat := TTgJson.GetObj(AObj, 'chat');
    if TTgJson.Has(LChat, 'id') then
      Result := IntToStr(TTgJson.GetInt64(LChat, 'id'))
    else
      Result := '';
  end;

  function UserOf(AObj: TJSONObject): string;
  var
    LUser: TJSONObject;
  begin
    LUser := TTgJson.GetObj(AObj, 'from');
    if not Assigned(LUser) then
      LUser := TTgJson.GetObj(AObj, 'user');
    if TTgJson.Has(LUser, 'id') then
      Result := 'u' + IntToStr(TTgJson.GetInt64(LUser, 'id'))
    else
      Result := '';
  end;

var
  LKind: string;
  LPayload: TJSONObject;
begin
  Result := '';
  LKind := KindOf(AJson);
  LPayload := TTgJson.GetObj(AJson, LKind);
  if not Assigned(LPayload) then
    Exit;
  // Опросы не привязаны к диалогу: порядок не нужен.
  if (LKind = 'poll') or (LKind = 'poll_answer') then
    Exit;
  if LKind = 'callback_query' then
    Result := ChatOf(TTgJson.GetObj(LPayload, 'message'))
  else
    Result := ChatOf(LPayload);
  if Result = '' then
    Result := UserOf(LPayload);
end;

function TTgRawUpdate.GetUpdateId: Int64;
begin
  Result := FUpdateId;
end;

function TTgRawUpdate.GetKind: string;
begin
  Result := FKind;
end;

function TTgRawUpdate.GetChatKey: string;
begin
  Result := FChatKey;
end;

function TTgRawUpdate.GetJson: TJSONObject;
begin
  Result := FJson;
end;

{ TTgSystemPollTimer }

constructor TTgSystemPollTimer.Create;
begin
  inherited Create;
  FWatch := TStopwatch.StartNew;
end;

function TTgSystemPollTimer.NowMs: Int64;
begin
  Result := FWatch.ElapsedMilliseconds;
end;

function TTgSystemPollTimer.Sleep(AMs: Cardinal; const ACancel: ITgCancellation): Boolean;
begin
  if Assigned(ACancel) then
    Exit(ACancel.WaitFor(AMs));
  TThread.Sleep(AMs);
  Result := False;
end;

type
  /// <summary>
  ///   Внутреннее состояние одного запуска TTgLongPollSource. Поток источника
  ///   держит только ссылку на него, поэтому может пережить сам источник.
  /// </summary>
  TTgPollCore = class(TInterfacedObject)
  private
    FLock: TCriticalSection;
    FWake: TEvent;
    FDone: TEvent;
    FTransport: ITgTransport;
    FPollSource: TTgCancellationSource;
    FPollToken: ITgCancellation;
    FFinalSource: TTgCancellationSource;
    FFinalToken: ITgCancellation;
    FSink: ITgUpdateSink;
    FTimer: ITgPollTimer;
    // Настройки (неизменны после создания).
    FLimit: Integer;
    FTimeoutSec: Integer;
    FAllowed: TTgOptional<TArray<string>>;
    FDropPending: Boolean;
    FAutoDeleteWebhook: Boolean;
    FAckPolicy: TTgAckPolicy;
    FDrainTimeoutMs: Cardinal;
    FConflictNotifyMs: Int64;
    FJitterPercent: Integer;
    FOnConflict: TTgConflictHandler;
    FOnError: TProc<Exception>;
    FOnFault: TProc<Exception>;
    // Состояние (под FLock).
    FState: TTgSourceState;
    FStopRequested: Boolean;
    FAbandoned: Boolean;
    FDrainLimitMs: Cardinal;
    FOffset: Int64;
    FConfirmedOffset: Int64;
    FPending: TList<Int64>;
    // Только поток источника.
    FBackoffStep: Integer;
    FWebhookRetries: Integer;
    FConflictNotified: Boolean;
    FLastConflictNotifyMs: Int64;
    FRandom: Cardinal;
    function IsStopRequested: Boolean;
    function NextRandom: Double;
    function NextBackoff: Cardinal;
    function Pause(AMs: Cardinal): Boolean;
    function Fetch(AOffset: Int64; ATimeoutSec, ALimit: Integer;
      const AToken: ITgCancellation): TJSONArray;
    procedure DeleteWebhook(ADropPending: Boolean);
    function Prepare: Boolean;
    function WaitBatchProcessed: Boolean;
    function PollOnce: Boolean;
    function AcceptBatch(AArray: TJSONArray; ARequestOffset: Int64): Boolean;
    function HandleFailure(AError: Exception): Boolean;
    function HandleConflict(AError: ETgConflictError): Boolean;
    procedure Fault(AError: Exception);
    procedure FinishGracefully;
    procedure NotifyError(AError: Exception);
    procedure NotifyConflict(AError: ETgConflictError);
  public
    constructor Create(const ATransport: ITgTransport; const AParentCancel: ITgCancellation;
      const ASink: ITgUpdateSink; ASource: TTgLongPollSource; AStartOffset: Int64);
    destructor Destroy; override;
    /// <summary>Тело потока.</summary>
    procedure Run;
    procedure RequestStop(AWaitMs: Cardinal);
    procedure CancelFinal;
    procedure Abandon;
    procedure Processed(AUpdateId: Int64);
    function State: TTgSourceState;
    function Offset: Int64;
    function ConfirmedOffset: Int64;
    /// <summary>С какого offset продолжить при следующем Start.</summary>
    function ResumeOffset: Int64;
    property Done: TEvent read FDone;
  end;

  /// <summary>Поток long polling (FreeOnTerminate).</summary>
  TTgPollThread = class(TThread)
  private
    FCore: TTgPollCore;
    FCoreRef: IInterface;
  protected
    procedure Execute; override;
  public
    constructor Create(ACore: TTgPollCore);
  end;

{ TTgPollThread }

constructor TTgPollThread.Create(ACore: TTgPollCore);
begin
  inherited Create(True);
  FCore := ACore;
  FCoreRef := ACore;
  FreeOnTerminate := True;
end;

procedure TTgPollThread.Execute;
var
  LName: string;
begin
  LName := 'TgBot.LongPoll';
  NameThreadForDebugging(LName);
  try
    FCore.Run;
  finally
    FCore := nil;
    FCoreRef := nil;
  end;
end;

{ TTgPollCore }

constructor TTgPollCore.Create(const ATransport: ITgTransport;
  const AParentCancel: ITgCancellation; const ASink: ITgUpdateSink;
  ASource: TTgLongPollSource; AStartOffset: Int64);
begin
  inherited Create;
  FLock := TCriticalSection.Create;
  FWake := TEvent.Create(nil, False, False, '');
  FDone := TEvent.Create(nil, True, False, '');
  FPending := TList<Int64>.Create;
  FTransport := ATransport;
  FPollSource := TTgCancellationSource.Create(AParentCancel);
  FPollToken := FPollSource;
  FFinalSource := TTgCancellationSource.Create(AParentCancel);
  FFinalToken := FFinalSource;
  FSink := ASink;
  FTimer := ASource.FTimer;
  if not Assigned(FTimer) then
    FTimer := TTgSystemPollTimer.Create;
  FLimit := EnsureRange(ASource.FLimit, 1, 100);
  FTimeoutSec := Max(ASource.FTimeoutSec, 0);
  FAllowed := ASource.FAllowedUpdates;
  FDropPending := ASource.FDropPendingUpdates;
  FAutoDeleteWebhook := ASource.FAutoDeleteWebhook;
  FAckPolicy := ASource.FAckPolicy;
  FDrainTimeoutMs := ASource.FDrainTimeoutMs;
  FConflictNotifyMs := ASource.FConflictNotifyIntervalMs;
  FJitterPercent := EnsureRange(ASource.FJitterPercent, 0, 50);
  FOnConflict := ASource.FOnConflict;
  FOnError := ASource.FOnError;
  FOnFault := ASource.FOnFault;
  FState := TTgSourceState.Running;
  FOffset := AStartOffset;
  FConfirmedOffset := 0;
  FDrainLimitMs := FDrainTimeoutMs;
  // Затравка генератора разброса: время и адрес — разные экземпляры не синхронны.
  FRandom := Cardinal(TThread.GetTickCount) xor Cardinal(NativeUInt(Self) shr 4) or 1;
end;

destructor TTgPollCore.Destroy;
begin
  FreeAndNil(FPending);
  FreeAndNil(FDone);
  FreeAndNil(FWake);
  FreeAndNil(FLock);
  FPollToken := nil;
  FFinalToken := nil;
  inherited Destroy;
end;

function TTgPollCore.IsStopRequested: Boolean;
begin
  FLock.Enter;
  try
    Result := FStopRequested;
  finally
    FLock.Leave;
  end;
end;

function TTgPollCore.NextRandom: Double;
begin
  // xorshift32: только поток источника, без общего RandSeed.
  FRandom := FRandom xor (FRandom shl 13);
  FRandom := FRandom xor (FRandom shr 17);
  FRandom := FRandom xor (FRandom shl 5);
  Result := FRandom / 4294967296.0;
end;

function TTgPollCore.NextBackoff: Cardinal;
var
  LBase: Int64;
  LDelta: Int64;
begin
  LBase := Min(Int64(TgBackoffMinMs) shl Min(FBackoffStep, 6), TgBackoffMaxMs);
  Inc(FBackoffStep);
  if FJitterPercent > 0 then
  begin
    LDelta := Round(LBase * FJitterPercent / 100 * (2 * NextRandom - 1));
    LBase := Max(LBase + LDelta, 0);
  end;
  Result := Cardinal(LBase);
end;

function TTgPollCore.Pause(AMs: Cardinal): Boolean;
begin
  // True — продолжать; False — пауза прервана остановкой.
  Result := not FTimer.Sleep(AMs, FPollToken) and not IsStopRequested;
end;

function TTgPollCore.Fetch(AOffset: Int64; ATimeoutSec, ALimit: Integer;
  const AToken: ITgCancellation): TJSONArray;
var
  LParams: TTgParams;
  LResult: TJSONValue;
begin
  LParams := TTgParams.Create;
  try
    if AOffset <> 0 then
      LParams.Add('offset', AOffset);
    LParams.Add('limit', ALimit);
    LParams.Add('timeout', ATimeoutSec);
    if FAllowed.HasValue then
      LParams.AddStrings('allowed_updates', FAllowed.Value);
    LResult := CallTransport(FTransport, 'getUpdates', LParams, AToken);
  finally
    LParams.Free;
  end;
  if not (LResult is TJSONArray) then
  begin
    LResult.Free;
    raise ETgError.Create(TgTextFmt(TTgText.UnexpectedResult, ['getUpdates']));
  end;
  Result := TJSONArray(LResult);
end;

procedure TTgPollCore.DeleteWebhook(ADropPending: Boolean);
var
  LParams: TTgParams;
begin
  LParams := TTgParams.Create;
  try
    if ADropPending then
      LParams.Add('drop_pending_updates', True);
    CallTransport(FTransport, 'deleteWebhook', LParams, FPollToken).Free;
  finally
    LParams.Free;
  end;
end;

function TTgPollCore.Prepare: Boolean;
begin
  // deleteWebhook(drop_pending_updates) до первого getUpdates, с повторами.
  Result := True;
  if not FDropPending then
    Exit;
  while not IsStopRequested do
  begin
    try
      DeleteWebhook(True);
      FBackoffStep := 0;
      Exit(True);
    except
      on E: Exception do
        if not HandleFailure(E) then
          Exit(False);
    end;
  end;
  Result := False;
end;

function TTgPollCore.WaitBatchProcessed: Boolean;
var
  LEmpty, LStop: Boolean;
begin
  if FAckPolicy <> TTgAckPolicy.AfterBatch then
    Exit(not IsStopRequested);
  while True do
  begin
    FLock.Enter;
    try
      LEmpty := FPending.Count = 0;
      LStop := FStopRequested;
    finally
      FLock.Leave;
    end;
    if LStop then
      Exit(False);
    if LEmpty then
      Exit(True);
    // Будит Processed (очередь пуста) и RequestStop.
    FWake.WaitFor(INFINITE);
  end;
end;

function TTgPollCore.PollOnce: Boolean;
var
  LOffset: Int64;
  LArray: TJSONArray;
begin
  FLock.Enter;
  try
    LOffset := FOffset;
  finally
    FLock.Leave;
  end;
  try
    LArray := Fetch(LOffset, FTimeoutSec, FLimit, FPollToken);
  except
    on E: Exception do
      Exit(HandleFailure(E));
  end;
  try
    Result := AcceptBatch(LArray, LOffset);
  finally
    LArray.Free;
  end;
end;

function TTgPollCore.AcceptBatch(AArray: TJSONArray; ARequestOffset: Int64): Boolean;
var
  LUpdates: TList<ITgRawUpdate>;
  LValue: TJSONValue;
  LUpdate: ITgRawUpdate;
  I: Integer;
begin
  LUpdates := TList<ITgRawUpdate>.Create;
  try
    // Элементы вынимаются из массива без копирования: владение — у обновлений.
    while AArray.Count > 0 do
    begin
      LValue := AArray.Remove(0);
      if not (LValue is TJSONObject) then
      begin
        LValue.Free;
        Continue;
      end;
      try
        LUpdate := TTgRawUpdate.Create(TJSONObject(LValue));
      except
        // Конструктор уже освободил JSON; некорректный элемент пропускается.
        Continue;
      end;
      LUpdates.Add(LUpdate);
      LUpdate := nil;
    end;
    FLock.Enter;
    try
      // Ответ после Stop (отпущенный поток) выбрасывается без сдвига offset.
      if FStopRequested then
        Exit(False);
      FConfirmedOffset := Max(FConfirmedOffset, ARequestOffset);
      FBackoffStep := 0;
      FWebhookRetries := 0;
      for I := LUpdates.Count - 1 downto 0 do
        if (FOffset <> 0) and (LUpdates[I].UpdateId < FOffset) then
          LUpdates.Delete(I);
      for I := 0 to LUpdates.Count - 1 do
      begin
        FPending.Add(LUpdates[I].UpdateId);
        FOffset := Max(FOffset, LUpdates[I].UpdateId + 1);
      end;
    finally
      FLock.Leave;
    end;
    // Не принятые приёмником обновления остаются необработанными (итоговый offset).
    for I := 0 to LUpdates.Count - 1 do
      if not FSink.Post(LUpdates[I], FPollToken) then
        Exit(False);
    Result := True;
  finally
    LUpdates.Free;
  end;
end;

function TTgPollCore.HandleFailure(AError: Exception): Boolean;
var
  LDelay: Cardinal;
begin
  if IsStopRequested then
    Exit(False);
  // Отмена без Stop — отменён родительский токен (клиент уничтожается).
  if AError is ETgCancelledError then
  begin
    Fault(AError);
    Exit(False);
  end;
  if AError is ETgConflictError then
    Exit(HandleConflict(ETgConflictError(AError)));
  if (AError is ETgApiError) and ((ETgApiError(AError).ErrorCode = 401) or
    (ETgApiError(AError).ErrorCode = 404)) then
  begin
    // Неверный токен или адрес Bot API: повторы бессмысленны.
    Fault(AError);
    Exit(False);
  end;
  NotifyError(AError);
  LDelay := NextBackoff;
  if (AError is ETgApiError) and (ETgApiError(AError).RetryAfter > 0) then
    LDelay := Max(LDelay, Cardinal(ETgApiError(AError).RetryAfter) * 1000);
  Result := Pause(LDelay);
end;

function TTgPollCore.HandleConflict(AError: ETgConflictError): Boolean;
var
  LNow: Int64;
begin
  if ContainsText(AError.Description, 'webhook') then
  begin
    if not FAutoDeleteWebhook then
    begin
      NotifyConflict(AError);
      Fault(AError);
      Exit(False);
    end;
    Inc(FWebhookRetries);
    try
      DeleteWebhook(False);
    except
      on E: Exception do
      begin
        if IsStopRequested then
          Exit(False);
        NotifyError(E);
        Exit(Pause(NextBackoff));
      end;
    end;
    // Повтор сразу; если webhook снова установлен (другой процесс) — с паузой.
    if FWebhookRetries > 1 then
      Exit(Pause(NextBackoff));
    Exit(True);
  end;
  // Другой getUpdates с тем же токеном: сообщаем не чаще интервала и ждём.
  LNow := FTimer.NowMs;
  if not FConflictNotified or (LNow - FLastConflictNotifyMs >= FConflictNotifyMs) then
  begin
    FConflictNotified := True;
    FLastConflictNotifyMs := LNow;
    NotifyConflict(AError);
  end;
  Result := Pause(Max(NextBackoff, TgConflictRetryMs));
end;

procedure TTgPollCore.Fault(AError: Exception);
begin
  FLock.Enter;
  try
    // Ошибки после Stop (в т.ч. отпущенного потока) не переводят в Faulted.
    if FStopRequested or FAbandoned then
      Exit;
    FState := TTgSourceState.Faulted;
  finally
    FLock.Leave;
  end;
  if Assigned(FOnFault) then
    InvokeQuietly(
      procedure
      begin
        FOnFault(AError);
      end);
end;

procedure TTgPollCore.NotifyError(AError: Exception);
begin
  if Assigned(FOnError) then
    InvokeQuietly(
      procedure
      begin
        FOnError(AError);
      end);
end;

procedure TTgPollCore.NotifyConflict(AError: ETgConflictError);
begin
  if Assigned(FOnConflict) then
    InvokeQuietly(
      procedure
      begin
        FOnConflict(AError);
      end);
end;

procedure TTgPollCore.FinishGracefully;
var
  LWatch: TStopwatch;
  LEmpty: Boolean;
  LLeft: Int64;
  LAck: Int64;
  LNeed: Boolean;
begin
  // Дренаж: ждём Processed уже принятых обновлений.
  LWatch := TStopwatch.StartNew;
  while True do
  begin
    FLock.Enter;
    try
      LEmpty := FPending.Count = 0;
      LLeft := Int64(FDrainLimitMs) - LWatch.ElapsedMilliseconds;
      if FAbandoned then
        Exit;
    finally
      FLock.Leave;
    end;
    if LEmpty or (LLeft <= 0) or FFinalToken.IsCancelled then
      Break;
    FWake.WaitFor(Cardinal(Min(LLeft, 100)));
  end;
  // Итоговое подтверждение: offset = наименьший необработанный.
  FLock.Enter;
  try
    if FPending.Count > 0 then
      LAck := FPending[0]
    else
      LAck := FOffset;
    LNeed := (LAck > 0) and (LAck > FConfirmedOffset) and not FAbandoned;
  finally
    FLock.Leave;
  end;
  if not LNeed or FFinalToken.IsCancelled then
    Exit;
  try
    Fetch(LAck, 0, 1, FFinalToken).Free;
    FLock.Enter;
    try
      FConfirmedOffset := Max(FConfirmedOffset, LAck);
    finally
      FLock.Leave;
    end;
  except
    on E: Exception do
      if not (E is ETgCancelledError) then
        NotifyError(E);
  end;
end;

procedure TTgPollCore.Run;
var
  LStopped: Boolean;
begin
  try
    try
      if Prepare then
        while WaitBatchProcessed and PollOnce do
          ;
      FLock.Enter;
      try
        LStopped := FStopRequested and not FAbandoned and
          (FState <> TTgSourceState.Faulted);
      finally
        FLock.Leave;
      end;
      if LStopped then
        FinishGracefully;
    except
      on E: Exception do
        Fault(E);
    end;
  finally
    FLock.Enter;
    try
      FSink := nil;
      if FState <> TTgSourceState.Faulted then
        FState := TTgSourceState.Idle;
    finally
      FLock.Leave;
    end;
    FDone.SetEvent;
  end;
end;

procedure TTgPollCore.RequestStop(AWaitMs: Cardinal);
begin
  FLock.Enter;
  try
    if not FStopRequested then
    begin
      FStopRequested := True;
      // Половина бюджета Stop — на дренаж, остальное — на итоговый запрос.
      FDrainLimitMs := Min(FDrainTimeoutMs, AWaitMs div 2);
      if FState = TTgSourceState.Running then
        FState := TTgSourceState.Stopping;
    end;
  finally
    FLock.Leave;
  end;
  FPollSource.Cancel;
  FWake.SetEvent;
end;

procedure TTgPollCore.CancelFinal;
begin
  FFinalSource.Cancel;
  FWake.SetEvent;
end;

procedure TTgPollCore.Abandon;
begin
  FLock.Enter;
  try
    FAbandoned := True;
    if FState <> TTgSourceState.Faulted then
      FState := TTgSourceState.Idle;
  finally
    FLock.Leave;
  end;
end;

procedure TTgPollCore.Processed(AUpdateId: Int64);
var
  LIndex: Integer;
  LEmpty: Boolean;
begin
  FLock.Enter;
  try
    LIndex := FPending.IndexOf(AUpdateId);
    if LIndex < 0 then
      Exit;
    FPending.Delete(LIndex);
    LEmpty := FPending.Count = 0;
  finally
    FLock.Leave;
  end;
  if LEmpty then
    FWake.SetEvent;
end;

function TTgPollCore.State: TTgSourceState;
begin
  FLock.Enter;
  try
    Result := FState;
  finally
    FLock.Leave;
  end;
end;

function TTgPollCore.Offset: Int64;
begin
  FLock.Enter;
  try
    Result := FOffset;
  finally
    FLock.Leave;
  end;
end;

function TTgPollCore.ConfirmedOffset: Int64;
begin
  FLock.Enter;
  try
    Result := FConfirmedOffset;
  finally
    FLock.Leave;
  end;
end;

function TTgPollCore.ResumeOffset: Int64;
begin
  FLock.Enter;
  try
    if FPending.Count > 0 then
      Result := FPending[0]
    else
      Result := FOffset;
  finally
    FLock.Leave;
  end;
end;

{ TTgLongPollSource }

constructor TTgLongPollSource.Create(const ATransport: ITgTransport;
  const AParentCancel: ITgCancellation);
begin
  inherited Create;
  if not Assigned(ATransport) then
    raise ETgError.Create(TgText(TTgText.TransportRequired));
  FLock := TCriticalSection.Create;
  FTransport := ATransport;
  FParentCancel := AParentCancel;
  FLimit := TgDefaultPollLimit;
  FTimeoutSec := TgDefaultPollTimeoutSec;
  FAckPolicy := TTgAckPolicy.AfterReceive;
  FDrainTimeoutMs := TgDefaultDrainTimeoutMs;
  FConflictNotifyIntervalMs := TgDefaultConflictNotifyMs;
  FJitterPercent := TgDefaultBackoffJitterPercent;
end;

destructor TTgLongPollSource.Destroy;
var
  LRef: IInterface;
  LCore: TTgPollCore;
  LFirst: Boolean;
begin
  if Assigned(FLock) then
  begin
    LCore := TTgPollCore(CurrentCore(LRef));
    if Assigned(LCore) then
    begin
      // Поток (FreeOnTerminate) держит ядро сам: висящий запрос не ждём.
      // После Stop (в т.ч. вернувшего False) повторно не ждём.
      LFirst := not LCore.IsStopRequested;
      LCore.RequestStop(TgDefaultDrainTimeoutMs + 1000);
      if LFirst then
        LCore.Done.WaitFor(CDestroyGraceMs);
    end;
    LRef := nil;
  end;
  FCore := nil;
  FCoreRef := nil;
  FreeAndNil(FLock);
  inherited Destroy;
end;

function TTgLongPollSource.CurrentCore(out ARef: IInterface): TObject;
begin
  FLock.Enter;
  try
    Result := FCore;
    ARef := FCoreRef;
  finally
    FLock.Leave;
  end;
end;

procedure TTgLongPollSource.Start(const ASink: ITgUpdateSink);
var
  LRef: IInterface;
  LOld: TTgPollCore;
  LCore: TTgPollCore;
  LThread: TTgPollThread;
begin
  if not Assigned(ASink) then
    raise EArgumentNilException.Create('ASink');
  FLock.Enter;
  try
    LOld := TTgPollCore(FCore);
    if Assigned(LOld) and (LOld.State in [TTgSourceState.Running, TTgSourceState.Stopping]) then
      raise ETgError.Create(TgUpdatesText(TTgUpdatesText.SourceRunning));
    if Assigned(LOld) then
      FResumeOffset := LOld.ResumeOffset;
    LCore := TTgPollCore.Create(FTransport, FParentCancel, ASink, Self, FResumeOffset);
    LRef := LCore;
    LThread := TTgPollThread.Create(LCore);
    FCore := LCore;
    FCoreRef := LRef;
  finally
    FLock.Leave;
  end;
  LThread.Start;
end;

function TTgLongPollSource.Stop(AWaitMs: Cardinal): Boolean;
var
  LRef: IInterface;
  LCore: TTgPollCore;
begin
  LCore := TTgPollCore(CurrentCore(LRef));
  if not Assigned(LCore) then
    Exit(True);
  LCore.RequestStop(AWaitMs);
  Result := TgWaitEventPumping(LCore.Done, AWaitMs);
  if not Result then
  begin
    // Бюджет исчерпан: прерываем дренаж и итоговый запрос, коротко ждём ещё.
    LCore.CancelFinal;
    Result := TgWaitEventPumping(LCore.Done, CFinalGraceMs);
  end;
  if not Result then
    LCore.Abandon;
  FLock.Enter;
  try
    if FCore = LCore then
      FResumeOffset := LCore.ResumeOffset;
  finally
    FLock.Leave;
  end;
end;

procedure TTgLongPollSource.Processed(AUpdateId: Int64);
var
  LRef: IInterface;
  LCore: TObject;
begin
  LCore := CurrentCore(LRef);
  if Assigned(LCore) then
    TTgPollCore(LCore).Processed(AUpdateId);
end;

function TTgLongPollSource.GetState: TTgSourceState;
var
  LRef: IInterface;
  LCore: TObject;
begin
  LCore := CurrentCore(LRef);
  if Assigned(LCore) then
    Result := TTgPollCore(LCore).State
  else
    Result := TTgSourceState.Idle;
end;

function TTgLongPollSource.WaitForThread(AMs: Cardinal): Boolean;
var
  LRef: IInterface;
  LCore: TObject;
begin
  LCore := CurrentCore(LRef);
  Result := not Assigned(LCore) or
    (TTgPollCore(LCore).Done.WaitFor(AMs) = TWaitResult.wrSignaled);
end;

function TTgLongPollSource.GetOffset: Int64;
var
  LRef: IInterface;
  LCore: TObject;
begin
  LCore := CurrentCore(LRef);
  if Assigned(LCore) then
    Result := TTgPollCore(LCore).Offset
  else
    Result := FResumeOffset;
end;

function TTgLongPollSource.GetConfirmedOffset: Int64;
var
  LRef: IInterface;
  LCore: TObject;
begin
  LCore := CurrentCore(LRef);
  if Assigned(LCore) then
    Result := TTgPollCore(LCore).ConfirmedOffset
  else
    Result := 0;
end;

type
  /// <summary>
  ///   Внутреннее состояние одного запуска TTgWebhookSource. Служебный поток
  ///   (setWebhook, ожидание остановки, deleteWebhook) держит только ссылку
  ///   на него, поэтому может пережить сам источник.
  /// </summary>
  TTgWebhookCore = class(TInterfacedObject)
  private
    FLock: TCriticalSection;
    FWake: TEvent;
    FDone: TEvent;
    FTransport: ITgTransport;
    // Отмена setWebhook/deleteWebhook (по истечении бюджета Stop, Free клиента).
    FCallSource: TTgCancellationSource;
    FCallToken: ITgCancellation;
    // Отмена ожидания места в очереди (сразу при Stop).
    FPostSource: TTgCancellationSource;
    FPostToken: ITgCancellation;
    FSink: ITgUpdateSink;
    // Настройки (неизменны после создания).
    FUrl: string;
    FSecret: string;
    FIpAddress: string;
    FMaxConnections: Integer;
    FDropPending: Boolean;
    FCertificate: TTgInputFile;
    FAllowed: TTgOptional<TArray<string>>;
    FRegisterOnStart: Boolean;
    FDeleteOnStop: Boolean;
    FMaxBodySize: Integer;
    FPostTimeoutMs: Cardinal;
    FOnError: TProc<Exception>;
    FOnFault: TProc<Exception>;
    // Состояние (под FLock).
    FState: TTgSourceState;
    FStopRequested: Boolean;
    FAbandoned: Boolean;
    procedure SetWebhook;
    procedure DeleteWebhook;
    procedure Fault(AError: Exception);
    procedure NotifyError(AError: Exception);
  public
    constructor Create(ASource: TTgWebhookSource; const ASink: ITgUpdateSink);
    destructor Destroy; override;
    /// <summary>Тело служебного потока.</summary>
    procedure Run;
    function IsStopRequested: Boolean;
    procedure RequestStop;
    /// <summary>Отменяет висящие setWebhook/deleteWebhook.</summary>
    procedure CancelCalls;
    procedure Abandon;
    function State: TTgSourceState;
    /// <summary>Секрет совпал (сравнение за постоянное время) или не задан.</summary>
    function CheckSecret(const AHeader: string): Boolean;
    /// <summary>В очередь (только в Running); False — не принято.</summary>
    function Post(const AUpdate: ITgRawUpdate): Boolean;
    property MaxBodySize: Integer read FMaxBodySize;
    property Done: TEvent read FDone;
  end;

  /// <summary>Служебный поток webhook (FreeOnTerminate).</summary>
  TTgWebhookThread = class(TThread)
  private
    FCore: TTgWebhookCore;
    FCoreRef: IInterface;
  protected
    procedure Execute; override;
  public
    constructor Create(ACore: TTgWebhookCore);
  end;

{ TTgWebhookThread }

constructor TTgWebhookThread.Create(ACore: TTgWebhookCore);
begin
  inherited Create(True);
  FCore := ACore;
  FCoreRef := ACore;
  FreeOnTerminate := True;
end;

procedure TTgWebhookThread.Execute;
var
  LName: string;
begin
  LName := 'TgBot.Webhook';
  NameThreadForDebugging(LName);
  try
    FCore.Run;
  finally
    FCore := nil;
    FCoreRef := nil;
  end;
end;

{ TTgWebhookCore }

constructor TTgWebhookCore.Create(ASource: TTgWebhookSource; const ASink: ITgUpdateSink);
begin
  inherited Create;
  FLock := TCriticalSection.Create;
  FWake := TEvent.Create(nil, False, False, '');
  FDone := TEvent.Create(nil, True, False, '');
  FTransport := ASource.FTransport;
  FCallSource := TTgCancellationSource.Create(ASource.FParentCancel);
  FCallToken := FCallSource;
  FPostSource := TTgCancellationSource.Create(ASource.FParentCancel);
  FPostToken := FPostSource;
  FSink := ASink;
  FUrl := Trim(ASource.FUrl);
  FSecret := ASource.FSecretToken;
  FIpAddress := Trim(ASource.FIpAddress);
  FMaxConnections := ASource.FMaxConnections;
  FDropPending := ASource.FDropPendingUpdates;
  FCertificate := ASource.FCertificate;
  FAllowed := ASource.FAllowedUpdates;
  FRegisterOnStart := ASource.FRegisterOnStart;
  FDeleteOnStop := ASource.FDeleteOnStop;
  FMaxBodySize := Max(ASource.FMaxBodySize, 1);
  FPostTimeoutMs := ASource.FPostTimeoutMs;
  FOnError := ASource.FOnError;
  FOnFault := ASource.FOnFault;
  FState := TTgSourceState.Running;
end;

destructor TTgWebhookCore.Destroy;
begin
  FreeAndNil(FDone);
  FreeAndNil(FWake);
  FreeAndNil(FLock);
  FCallToken := nil;
  FPostToken := nil;
  inherited Destroy;
end;

function TTgWebhookCore.IsStopRequested: Boolean;
begin
  FLock.Enter;
  try
    Result := FStopRequested;
  finally
    FLock.Leave;
  end;
end;

procedure TTgWebhookCore.SetWebhook;
var
  LParams: TTgParams;
begin
  LParams := TTgParams.Create;
  try
    LParams.Add('url', FUrl);
    if not FCertificate.IsEmpty then
      LParams.AddFile('certificate', FCertificate);
    if FIpAddress <> '' then
      LParams.Add('ip_address', FIpAddress);
    if FMaxConnections > 0 then
      LParams.Add('max_connections', FMaxConnections);
    if FAllowed.HasValue then
      LParams.AddStrings('allowed_updates', FAllowed.Value);
    if FDropPending then
      LParams.Add('drop_pending_updates', True);
    if FSecret <> '' then
      LParams.Add('secret_token', FSecret);
    CallTransport(FTransport, 'setWebhook', LParams, FCallToken).Free;
  finally
    LParams.Free;
  end;
end;

procedure TTgWebhookCore.DeleteWebhook;
var
  LParams: TTgParams;
begin
  LParams := TTgParams.Create;
  try
    CallTransport(FTransport, 'deleteWebhook', LParams, FCallToken).Free;
  finally
    LParams.Free;
  end;
end;

procedure TTgWebhookCore.Fault(AError: Exception);
begin
  FLock.Enter;
  try
    // Ошибки после Stop (в т.ч. отмена висящего setWebhook) не переводят в Faulted.
    if FStopRequested or FAbandoned then
      Exit;
    FState := TTgSourceState.Faulted;
    FSink := nil;
  finally
    FLock.Leave;
  end;
  if Assigned(FOnFault) then
    InvokeQuietly(
      procedure
      begin
        FOnFault(AError);
      end);
end;

procedure TTgWebhookCore.NotifyError(AError: Exception);
begin
  if Assigned(FOnError) then
    InvokeQuietly(
      procedure
      begin
        FOnError(AError);
      end);
end;

procedure TTgWebhookCore.Run;
var
  LDelete: Boolean;
begin
  try
    try
      // Регистрация: любая ошибка неустранима (без webhook обновлений не будет).
      // Выполняется и при Stop сразу после Start (как меню команд TTgBot):
      // Stop дожидается её в пределах бюджета, затем отменяет.
      if FRegisterOnStart then
        SetWebhook;
      while not IsStopRequested do
        FWake.WaitFor(INFINITE);
      FLock.Enter;
      try
        LDelete := FDeleteOnStop and not FAbandoned;
      finally
        FLock.Leave;
      end;
      if LDelete and not FCallToken.IsCancelled then
        try
          DeleteWebhook;
        except
          on E: Exception do
            if not (E is ETgCancelledError) then
              NotifyError(E);
        end;
    except
      on E: Exception do
        Fault(E);
    end;
  finally
    FLock.Enter;
    try
      FSink := nil;
      if FState <> TTgSourceState.Faulted then
        FState := TTgSourceState.Idle;
    finally
      FLock.Leave;
    end;
    FDone.SetEvent;
  end;
end;

procedure TTgWebhookCore.RequestStop;
begin
  FLock.Enter;
  try
    if not FStopRequested then
    begin
      FStopRequested := True;
      if FState = TTgSourceState.Running then
        FState := TTgSourceState.Stopping;
    end;
  finally
    FLock.Leave;
  end;
  // Accept, ждущие места в очереди, освобождаются сразу.
  FPostSource.Cancel;
  FWake.SetEvent;
end;

procedure TTgWebhookCore.CancelCalls;
begin
  FCallSource.Cancel;
  FWake.SetEvent;
end;

procedure TTgWebhookCore.Abandon;
begin
  FLock.Enter;
  try
    FAbandoned := True;
    if FState <> TTgSourceState.Faulted then
      FState := TTgSourceState.Idle;
  finally
    FLock.Leave;
  end;
end;

function TTgWebhookCore.State: TTgSourceState;
begin
  FLock.Enter;
  try
    Result := FState;
  finally
    FLock.Leave;
  end;
end;

function TTgWebhookCore.CheckSecret(const AHeader: string): Boolean;
begin
  Result := (FSecret = '') or TgSecretEquals(FSecret, AHeader);
end;

function TTgWebhookCore.Post(const AUpdate: ITgRawUpdate): Boolean;
var
  LSink: ITgUpdateSink;
  LTimed: ITgTimedUpdateSink;
begin
  FLock.Enter;
  try
    if FState = TTgSourceState.Running then
      LSink := FSink
    else
      LSink := nil;
  finally
    FLock.Leave;
  end;
  if not Assigned(LSink) then
    Exit(False);
  // Поток HTTP-сервера не висит на полной очереди: ждём не дольше PostTimeoutMs.
  if Supports(LSink, ITgTimedUpdateSink, LTimed) then
    Result := LTimed.TryPost(AUpdate, FPostToken, FPostTimeoutMs)
  else
    Result := LSink.Post(AUpdate, FPostToken);
end;

{ TTgWebhookSource }

constructor TTgWebhookSource.Create(const ATransport: ITgTransport;
  const AParentCancel: ITgCancellation);
begin
  inherited Create;
  if not Assigned(ATransport) then
    raise ETgError.Create(TgText(TTgText.TransportRequired));
  FLock := TCriticalSection.Create;
  FSeen := TDictionary<Int64, Byte>.Create;
  FSeenOrder := TList<Int64>.Create;
  FTransport := ATransport;
  FParentCancel := AParentCancel;
  FRegisterOnStart := True;
  FMaxBodySize := TgDefaultWebhookMaxBodySize;
  FPostTimeoutMs := TgDefaultWebhookPostTimeoutMs;
  FDedupWindow := TgDefaultWebhookDedupWindow;
end;

destructor TTgWebhookSource.Destroy;
var
  LRef: IInterface;
  LCore: TTgWebhookCore;
  LFirst: Boolean;
begin
  if Assigned(FLock) then
  begin
    LCore := TTgWebhookCore(CurrentCore(LRef));
    if Assigned(LCore) then
    begin
      // Поток (FreeOnTerminate) держит ядро сам: висящий запрос не ждём.
      LFirst := not LCore.IsStopRequested;
      LCore.RequestStop;
      if LFirst then
        LCore.Done.WaitFor(CDestroyGraceMs);
    end;
    LRef := nil;
  end;
  FCore := nil;
  FCoreRef := nil;
  FreeAndNil(FSeenOrder);
  FreeAndNil(FSeen);
  FreeAndNil(FLock);
  inherited Destroy;
end;

function TTgWebhookSource.CurrentCore(out ARef: IInterface): TObject;
begin
  FLock.Enter;
  try
    Result := FCore;
    ARef := FCoreRef;
  finally
    FLock.Leave;
  end;
end;

procedure TTgWebhookSource.Start(const ASink: ITgUpdateSink);
var
  LRef: IInterface;
  LOld: TTgWebhookCore;
  LCore: TTgWebhookCore;
  LThread: TTgWebhookThread;
begin
  if not Assigned(ASink) then
    raise EArgumentNilException.Create('ASink');
  // Пустой url в setWebhook означал бы удаление webhook.
  if FRegisterOnStart and (Trim(FUrl) = '') then
    raise ETgError.Create(TgUpdatesText(TTgUpdatesText.WebhookUrlRequired));
  if (FSecretToken <> '') and not IsValidSecretToken(FSecretToken) then
    raise ETgError.Create(TgUpdatesText(TTgUpdatesText.WebhookBadSecret));
  FLock.Enter;
  try
    LOld := TTgWebhookCore(FCore);
    if Assigned(LOld) and (LOld.State in [TTgSourceState.Running, TTgSourceState.Stopping]) then
      raise ETgError.Create(TgUpdatesText(TTgUpdatesText.SourceRunning));
    LCore := TTgWebhookCore.Create(Self, ASink);
    LRef := LCore;
    LThread := TTgWebhookThread.Create(LCore);
    FCore := LCore;
    FCoreRef := LRef;
  finally
    FLock.Leave;
  end;
  LThread.Start;
end;

function TTgWebhookSource.Stop(AWaitMs: Cardinal): Boolean;
var
  LRef: IInterface;
  LCore: TTgWebhookCore;
begin
  LCore := TTgWebhookCore(CurrentCore(LRef));
  if not Assigned(LCore) then
    Exit(True);
  LCore.RequestStop;
  // Незавершённый setWebhook и deleteWebhook (DeleteOnStop) — в пределах бюджета.
  Result := TgWaitEventPumping(LCore.Done, AWaitMs);
  if not Result then
  begin
    LCore.CancelCalls;
    Result := TgWaitEventPumping(LCore.Done, CFinalGraceMs);
  end;
  if not Result then
    LCore.Abandon;
end;

procedure TTgWebhookSource.Processed(AUpdateId: Int64);
begin
  // Подтверждение webhook — ответ 200 на запрос; offset не используется.
end;

function TTgWebhookSource.GetState: TTgSourceState;
var
  LRef: IInterface;
  LCore: TObject;
begin
  LCore := CurrentCore(LRef);
  if Assigned(LCore) then
    Result := TTgWebhookCore(LCore).State
  else
    Result := TTgSourceState.Idle;
end;

function TTgWebhookSource.WaitForThread(AMs: Cardinal): Boolean;
var
  LRef: IInterface;
  LCore: TObject;
begin
  LCore := CurrentCore(LRef);
  Result := not Assigned(LCore) or
    (TTgWebhookCore(LCore).Done.WaitFor(AMs) = TWaitResult.wrSignaled);
end;

function TTgWebhookSource.Admit(out ARef: IInterface; out ACore: TObject;
  const ASecretHeader: string): TTgWebhookResult;
begin
  ACore := CurrentCore(ARef);
  if not Assigned(ACore) or (TTgWebhookCore(ACore).State <> TTgSourceState.Running) then
    Exit(TTgWebhookResult.Unavailable);
  // Секрет — до разбора тела: чужой запрос не тратит память и процессор.
  if not TTgWebhookCore(ACore).CheckSecret(ASecretHeader) then
    Exit(TTgWebhookResult.Forbidden);
  Result := TTgWebhookResult.Accepted;
end;

function TTgWebhookSource.Accept(const ABody: TBytes;
  const ASecretHeader: string): TTgWebhookResult;
var
  LRef: IInterface;
  LCore: TObject;
begin
  Result := Admit(LRef, LCore, ASecretHeader);
  if Result <> TTgWebhookResult.Accepted then
    Exit;
  if (Length(ABody) = 0) or (Length(ABody) > TTgWebhookCore(LCore).MaxBodySize) then
    Exit(TTgWebhookResult.BadRequest);
  Result := Deliver(LCore, TTgJson.ParseObjectUtf8(ABody));
end;

function TTgWebhookSource.Accept(const ABody, ASecretHeader: string): TTgWebhookResult;
var
  LRef: IInterface;
  LCore: TObject;
  LMax: Integer;
begin
  Result := Admit(LRef, LCore, ASecretHeader);
  if Result <> TTgWebhookResult.Accepted then
    Exit;
  // Лимит — в байтах UTF-8 (как у перегрузки TBytes); длина в символах — быстрый отсев.
  LMax := TTgWebhookCore(LCore).MaxBodySize;
  if (ABody = '') or (Length(ABody) > LMax) or (TEncoding.UTF8.GetByteCount(ABody) > LMax) then
    Exit(TTgWebhookResult.BadRequest);
  Result := Deliver(LCore, TTgJson.ParseObject(ABody));
end;

function TTgWebhookSource.Deliver(ACore: TObject; AJson: TJSONObject): TTgWebhookResult;
var
  LUpdate: ITgRawUpdate;
  LId: Int64;
  LDedup: Boolean;
begin
  if not Assigned(AJson) then
    Exit(TTgWebhookResult.BadRequest);
  if not (TTgJson.GetValue(AJson, 'update_id') is TJSONNumber) then
  begin
    AJson.Free;
    Exit(TTgWebhookResult.BadRequest);
  end;
  try
    // Владение AJson переходит к обновлению сразу (в т.ч. при исключении).
    LUpdate := TTgRawUpdate.Create(AJson);
  except
    // update_id не целое число.
    on Exception do
      Exit(TTgWebhookResult.BadRequest);
  end;
  LId := LUpdate.UpdateId;
  // Повтор доставки (Telegram не получил ответ 200 вовремя) — без повторной обработки.
  FLock.Enter;
  try
    LDedup := FDedupWindow > 0;
    if LDedup then
    begin
      if FSeen.ContainsKey(LId) then
        Exit(TTgWebhookResult.Accepted);
      FSeen.Add(LId, 0);
      FSeenOrder.Add(LId);
      while FSeenOrder.Count > FDedupWindow do
      begin
        FSeen.Remove(FSeenOrder[0]);
        FSeenOrder.Delete(0);
      end;
    end;
  finally
    FLock.Leave;
  end;
  if TTgWebhookCore(ACore).Post(LUpdate) then
    Exit(TTgWebhookResult.Accepted);
  // Не принято (очередь полна, остановка): забываем id — повтор Telegram будет принят.
  if LDedup then
  begin
    FLock.Enter;
    try
      if FSeen.ContainsKey(LId) then
      begin
        FSeen.Remove(LId);
        FSeenOrder.Remove(LId);
      end;
    finally
      FLock.Leave;
    end;
  end;
  Result := TTgWebhookResult.Unavailable;
end;

class function TTgWebhookSource.GenerateSecretToken(ALength: Integer): string;
var
  LBytes: TBytes;
  LCount, I: Integer;
begin
  LCount := EnsureRange(ALength, 1, 256);
  LBytes := TgRandomBytes(LCount);
  SetLength(Result, LCount);
  for I := 0 to LCount - 1 do
    Result[I + 1] := CSecretAlphabet[(LBytes[I] and 63) + 1];
  // Случайные байты секрета не остаются в освобождённой памяти.
  FillChar(LBytes[0], LCount, 0);
end;

class function TTgWebhookSource.IsValidSecretToken(const AValue: string): Boolean;
var
  C: Char;
begin
  Result := (Length(AValue) >= 1) and (Length(AValue) <= 256);
  if Result then
    for C in AValue do
      if not CharInSet(C, ['A'..'Z', 'a'..'z', '0'..'9', '_', '-']) then
        Exit(False);
end;

type
  /// <summary>Состояние полосы диспетчера.</summary>
  TTgLaneState = (Idle, Ready, Running);

  /// <summary>Полоса: очередь обновлений одного ChatKey.</summary>
  TTgLane = class
  public
    Key: string;
    Keyed: Boolean;
    State: TTgLaneState;
    Items: TQueue<ITgRawUpdate>;
    constructor Create(const AKey: string; AKeyed: Boolean);
    destructor Destroy; override;
  end;

  /// <summary>Внутреннее состояние одного запуска диспетчера.</summary>
  TTgDispatchCore = class(TInterfacedObject)
  private
    FLock: TObject;
    FLanes: TDictionary<string, TTgLane>;
    FReady: TQueue<TTgLane>;
    FCount: Integer;
    FBusy: Integer;
    FCapacity: Integer;
    FStopping: Boolean;
    FWorkers: Integer;
    FAllExited: TEvent;
    FIdle: TEvent;
    FCancelSource: TTgCancellationSource;
    FCancel: ITgCancellation;
    FDelivery: TTgDelivery;
    FHandler: TTgRawHandler;
    FOnError: TTgRawErrorHandler;
    FOnProcessed: TProc<Int64>;
    procedure Deliver(const AUpdate: ITgRawUpdate);
    procedure DeliverMain(const AUpdate: ITgRawUpdate);
    procedure FinishLane(ALane: TTgLane);
  public
    constructor Create(ADispatcher: TTgUpdateDispatcher);
    destructor Destroy; override;
    procedure WorkerLoop;
    procedure WorkerStarted;
    procedure WorkerExited;
    /// <summary>Выполняет обработчик в текущем потоке (с областью отмены).</summary>
    procedure Execute(const AUpdate: ITgRawUpdate);
    /// <summary>Место в очереди ждёт не дольше ATimeoutMs (INFINITE — без предела).</summary>
    function Post(const AUpdate: ITgRawUpdate; const ACancel: ITgCancellation;
      ATimeoutMs: Cardinal): Boolean;
    procedure BeginStop;
    function Stopping: Boolean;
    property AllExited: TEvent read FAllExited;
    property Idle: TEvent read FIdle;
    property Cancel: ITgCancellation read FCancel;
  end;

  /// <summary>Поток диспетчера (FreeOnTerminate).</summary>
  TTgDispatchThread = class(TThread)
  private
    FCore: TTgDispatchCore;
    FCoreRef: IInterface;
  protected
    procedure Execute; override;
  public
    constructor Create(ACore: TTgDispatchCore);
  end;

  /// <summary>
  ///   Задание для главного потока (Delivery = Main). Состояния:
  ///   0 — ждёт, 1 — выполняется, 2 — выполнено, 3 — брошено (процедура в
  ///   очереди ничего не сделает).
  /// </summary>
  TTgMainJob = class(TInterfacedObject)
  private
    FState: Integer;
  public
    function TryStart(const ACancel: ITgCancellation): Boolean;
    procedure Finish;
    procedure Wake;
    /// <summary>Ждёт выполнения; при отмене не начатое задание бросается.</summary>
    procedure WaitFor(const ACancel: ITgCancellation);
  end;

threadvar
  // Глубина вложенности обработчиков диспетчера в текущем потоке.
  GTgHandlerDepth: Integer;

{ TTgLane }

constructor TTgLane.Create(const AKey: string; AKeyed: Boolean);
begin
  inherited Create;
  Key := AKey;
  Keyed := AKeyed;
  Items := TQueue<ITgRawUpdate>.Create;
end;

destructor TTgLane.Destroy;
begin
  FreeAndNil(Items);
  inherited Destroy;
end;

{ TTgMainJob }

function TTgMainJob.TryStart(const ACancel: ITgCancellation): Boolean;
begin
  TMonitor.Enter(Self);
  try
    Result := FState = 0;
    if not Result then
      Exit;
    // Диспетчер уже останавливается — не начинаем.
    if ACancel.IsCancelled then
    begin
      FState := 3;
      TMonitor.PulseAll(Self);
      Exit(False);
    end;
    FState := 1;
  finally
    TMonitor.Exit(Self);
  end;
end;

procedure TTgMainJob.Finish;
begin
  TMonitor.Enter(Self);
  try
    FState := 2;
    TMonitor.PulseAll(Self);
  finally
    TMonitor.Exit(Self);
  end;
end;

procedure TTgMainJob.Wake;
begin
  TMonitor.Enter(Self);
  try
    TMonitor.PulseAll(Self);
  finally
    TMonitor.Exit(Self);
  end;
end;

procedure TTgMainJob.WaitFor(const ACancel: ITgCancellation);
begin
  TMonitor.Enter(Self);
  try
    while True do
    begin
      if FState in [2, 3] then
        Exit;
      if (FState = 0) and ACancel.IsCancelled then
      begin
        FState := 3;
        Exit;
      end;
      TMonitor.Wait(Self, INFINITE);
    end;
  finally
    TMonitor.Exit(Self);
  end;
end;

// Замыкания — в отдельных функциях: захватывается только нужное.

function NewJobWakeCallback(const AJobRef: IInterface): TProc;
begin
  Result :=
    procedure
    begin
      TTgMainJob(AJobRef as TObject).Wake;
    end;
end;

function NewMainJobProc(const ACoreRef, AJobRef: IInterface;
  const AUpdate: ITgRawUpdate): TThreadProcedure;
begin
  Result :=
    procedure
    var
      LCore: TTgDispatchCore;
      LJob: TTgMainJob;
    begin
      LCore := TTgDispatchCore(ACoreRef as TObject);
      LJob := TTgMainJob(AJobRef as TObject);
      // «Осиротевшая» процедура (задание брошено) ничего не делает.
      if not LJob.TryStart(LCore.Cancel) then
        Exit;
      try
        LCore.Execute(AUpdate);
      finally
        LJob.Finish;
      end;
    end;
end;

function NewPulseCallback(const ACoreRef: IInterface): TProc;
begin
  Result :=
    procedure
    var
      LLock: TObject;
    begin
      LLock := TTgDispatchCore(ACoreRef as TObject).FLock;
      TMonitor.Enter(LLock);
      try
        TMonitor.PulseAll(LLock);
      finally
        TMonitor.Exit(LLock);
      end;
    end;
end;

{ TTgDispatchThread }

constructor TTgDispatchThread.Create(ACore: TTgDispatchCore);
begin
  inherited Create(True);
  FCore := ACore;
  FCoreRef := ACore;
  FreeOnTerminate := True;
end;

procedure TTgDispatchThread.Execute;
var
  LName: string;
begin
  LName := 'TgBot.Dispatcher';
  NameThreadForDebugging(LName);
  try
    try
      FCore.WorkerLoop;
    except
      // Цикл не выпускает исключений обработчиков; защита от сбоев самого цикла.
    end;
  finally
    FCore.WorkerExited;
    FCore := nil;
    FCoreRef := nil;
  end;
end;

{ TTgDispatchCore }

constructor TTgDispatchCore.Create(ADispatcher: TTgUpdateDispatcher);
begin
  inherited Create;
  FLock := TObject.Create;
  FLanes := TDictionary<string, TTgLane>.Create;
  FReady := TQueue<TTgLane>.Create;
  FAllExited := TEvent.Create(nil, True, True, '');
  FIdle := TEvent.Create(nil, True, True, '');
  FCancelSource := TTgCancellationSource.Create;
  FCancel := FCancelSource;
  FCapacity := Max(ADispatcher.FQueueCapacity, 1);
  FDelivery := ADispatcher.FDelivery;
  FHandler := ADispatcher.FHandler;
  FOnError := ADispatcher.FOnError;
  FOnProcessed := ADispatcher.FOnProcessed;
end;

destructor TTgDispatchCore.Destroy;
var
  LLane: TTgLane;
begin
  // Потоков уже нет: оставшиеся полосы принадлежат только ядру.
  if Assigned(FReady) then
    while FReady.Count > 0 do
    begin
      LLane := FReady.Dequeue;
      if LLane.Keyed then
        FLanes.Remove(LLane.Key);
      LLane.Free;
    end;
  if Assigned(FLanes) then
    for LLane in FLanes.Values do
      LLane.Free;
  FreeAndNil(FLanes);
  FreeAndNil(FReady);
  FreeAndNil(FAllExited);
  FreeAndNil(FIdle);
  FreeAndNil(FLock);
  FCancel := nil;
  inherited Destroy;
end;

procedure TTgDispatchCore.WorkerStarted;
begin
  TMonitor.Enter(FLock);
  try
    Inc(FWorkers);
    FAllExited.ResetEvent;
  finally
    TMonitor.Exit(FLock);
  end;
end;

procedure TTgDispatchCore.WorkerExited;
begin
  TMonitor.Enter(FLock);
  try
    Dec(FWorkers);
    if FWorkers = 0 then
      FAllExited.SetEvent;
  finally
    TMonitor.Exit(FLock);
  end;
end;

procedure TTgDispatchCore.WorkerLoop;
var
  LLane: TTgLane;
  LUpdate: ITgRawUpdate;
begin
  while True do
  begin
    TMonitor.Enter(FLock);
    try
      while (FReady.Count = 0) and not FStopping do
        TMonitor.Wait(FLock, INFINITE);
      if FStopping then
        Exit;
      LLane := FReady.Dequeue;
      LLane.State := TTgLaneState.Running;
      LUpdate := LLane.Items.Dequeue;
      Dec(FCount);
      Inc(FBusy);
      // Ждущие Post: в очереди появилось место.
      TMonitor.PulseAll(FLock);
    finally
      TMonitor.Exit(FLock);
    end;
    try
      Deliver(LUpdate);
    finally
      LUpdate := nil;
      FinishLane(LLane);
    end;
  end;
end;

procedure TTgDispatchCore.FinishLane(ALane: TTgLane);
begin
  TMonitor.Enter(FLock);
  try
    Dec(FBusy);
    if ALane.Items.Count > 0 then
    begin
      // В конец общей очереди: другие чаты не голодают.
      ALane.State := TTgLaneState.Ready;
      FReady.Enqueue(ALane);
      TMonitor.PulseAll(FLock);
    end
    else
    begin
      if ALane.Keyed then
        FLanes.Remove(ALane.Key);
      ALane.Free;
    end;
    if (FCount = 0) and (FBusy = 0) then
      FIdle.SetEvent;
  finally
    TMonitor.Exit(FLock);
  end;
end;

procedure TTgDispatchCore.Deliver(const AUpdate: ITgRawUpdate);
begin
  if FDelivery = TTgDelivery.Main then
    DeliverMain(AUpdate)
  else
    Execute(AUpdate);
end;

procedure TTgDispatchCore.DeliverMain(const AUpdate: ITgRawUpdate);
var
  LJob: TTgMainJob;
  LJobRef, LCoreRef, LRegistration: IInterface;
begin
  LJob := TTgMainJob.Create;
  LJobRef := LJob;
  LCoreRef := Self;
  // Отмена диспетчера будит ожидание: не начатое задание бросается.
  LRegistration := FCancel.Register(NewJobWakeCallback(LJobRef));
  try
    // Процедура привязана к потоку диспетчера: TThread.Destroy вызывает
    // RemoveQueuedEvents(Self) — брошенное задание снимается из очереди
    // главного потока вместе с потоком (без CheckSynchronize замыкание с
    // ядром не висит до выхода). Выполнится раньше — TryStart откажет.
    TThread.Queue(TThread.CurrentThread, NewMainJobProc(LCoreRef, LJobRef, AUpdate));
    LJob.WaitFor(FCancel);
  finally
    LRegistration := nil;
  end;
end;

procedure TTgDispatchCore.Execute(const AUpdate: ITgRawUpdate);
var
  LScope: TTgCancelScope;
begin
  LScope := TTgCancelScope.Enter(FCancel);
  Inc(GTgHandlerDepth);
  try
    try
      FHandler(AUpdate);
    except
      on E: Exception do
        if Assigned(FOnError) then
          try
            FOnError(E, AUpdate);
          except
            // Исключение OnError поглощается: цикл обработки продолжается.
          end;
    end;
  finally
    Dec(GTgHandlerDepth);
    LScope.Leave;
  end;
  // Обработано — в т.ч. с исключением (иначе offset навсегда застрянет).
  if Assigned(FOnProcessed) then
    try
      FOnProcessed(AUpdate.UpdateId);
    except
      // Подтверждение не должно ронять поток диспетчера.
    end;
end;

function TTgDispatchCore.Post(const AUpdate: ITgRawUpdate;
  const ACancel: ITgCancellation; ATimeoutMs: Cardinal): Boolean;
var
  LRegistration: IInterface;
  LLane: TTgLane;
  LKey: string;
  LWatch: TStopwatch;
  LLeft: Int64;
begin
  LRegistration := nil;
  LKey := AUpdate.ChatKey;
  LWatch := TStopwatch.StartNew;
  TMonitor.Enter(FLock);
  try
    while (FCount >= FCapacity) and not FStopping and
      not (Assigned(ACancel) and ACancel.IsCancelled) do
    begin
      // Отмена ACancel будит ожидание места (подписка — только при блокировке).
      if Assigned(ACancel) and not Assigned(LRegistration) then
      begin
        LRegistration := ACancel.Register(NewPulseCallback(Self));
        Continue;
      end;
      if ATimeoutMs = INFINITE then
        TMonitor.Wait(FLock, INFINITE)
      else
      begin
        // Ограниченное ожидание (webhook): очередь так и не освободилась — отказ.
        LLeft := Int64(ATimeoutMs) - LWatch.ElapsedMilliseconds;
        if LLeft <= 0 then
          Exit(False);
        TMonitor.Wait(FLock, Cardinal(LLeft));
      end;
    end;
    if FStopping or (Assigned(ACancel) and ACancel.IsCancelled) then
      Exit(False);
    if (LKey = '') or not FLanes.TryGetValue(LKey, LLane) then
    begin
      LLane := TTgLane.Create(LKey, LKey <> '');
      if LLane.Keyed then
        try
          FLanes.Add(LKey, LLane);
        except
          LLane.Free;
          raise;
        end;
    end;
    LLane.Items.Enqueue(AUpdate);
    Inc(FCount);
    FIdle.ResetEvent;
    if LLane.State = TTgLaneState.Idle then
    begin
      LLane.State := TTgLaneState.Ready;
      FReady.Enqueue(LLane);
      TMonitor.PulseAll(FLock);
    end;
    Result := True;
  finally
    TMonitor.Exit(FLock);
  end;
end;

procedure TTgDispatchCore.BeginStop;
var
  LLane: TTgLane;
begin
  TMonitor.Enter(FLock);
  try
    FStopping := True;
    // Необработанная очередь выбрасывается; выполняющиеся полосы освободят потоки.
    while FReady.Count > 0 do
    begin
      LLane := FReady.Dequeue;
      if LLane.Keyed then
        FLanes.Remove(LLane.Key);
      LLane.Free;
    end;
    for LLane in FLanes.Values do
      LLane.Items.Clear;
    FCount := 0;
    if FBusy = 0 then
      FIdle.SetEvent;
    TMonitor.PulseAll(FLock);
  finally
    TMonitor.Exit(FLock);
  end;
  FCancelSource.Cancel;
end;

function TTgDispatchCore.Stopping: Boolean;
begin
  TMonitor.Enter(FLock);
  try
    Result := FStopping;
  finally
    TMonitor.Exit(FLock);
  end;
end;

{ TTgUpdateDispatcher }

constructor TTgUpdateDispatcher.Create(const AHandler: TTgRawHandler);
begin
  inherited Create;
  if not Assigned(AHandler) then
    raise EArgumentNilException.Create('AHandler');
  FLock := TCriticalSection.Create;
  FHandler := AHandler;
  FMaxParallel := TgDefaultMaxParallel;
  FQueueCapacity := TgDefaultQueueCapacity;
  FDelivery := TTgDelivery.Worker;
end;

destructor TTgUpdateDispatcher.Destroy;
var
  LRef: IInterface;
  LCore: TTgDispatchCore;
  LFirst: Boolean;
begin
  if Assigned(FLock) then
  begin
    LCore := TTgDispatchCore(CurrentCore(LRef));
    if Assigned(LCore) then
    begin
      // Потоки (FreeOnTerminate) держат ядро сами: зависший обработчик не ждём.
      // После Stop повторно не ждём; из обработчика ждать нечего (свой поток).
      LFirst := not LCore.Stopping;
      LCore.BeginStop;
      if LFirst and (GTgHandlerDepth = 0) then
        LCore.AllExited.WaitFor(CDestroyGraceMs);
    end;
    LRef := nil;
  end;
  FCore := nil;
  FCoreRef := nil;
  FreeAndNil(FLock);
  inherited Destroy;
end;

function TTgUpdateDispatcher.CurrentCore(out ARef: IInterface): TObject;
begin
  FLock.Enter;
  try
    Result := FCore;
    ARef := FCoreRef;
  finally
    FLock.Leave;
  end;
end;

procedure TTgUpdateDispatcher.Start;
var
  LCore: TTgDispatchCore;
  LRef: IInterface;
  LThreads: TArray<TTgDispatchThread>;
  I: Integer;
begin
  FLock.Enter;
  try
    if Assigned(FCore) and not TTgDispatchCore(FCore).Stopping then
      raise ETgError.Create(TgUpdatesText(TTgUpdatesText.DispatcherRunning));
    LCore := TTgDispatchCore.Create(Self);
    LRef := LCore;
    SetLength(LThreads, EnsureRange(FMaxParallel, 1, CMaxParallelLimit));
    try
      for I := 0 to High(LThreads) do
      begin
        LThreads[I] := TTgDispatchThread.Create(LCore);
        LCore.WorkerStarted;
      end;
    except
      // Созданные, но не запущенные потоки освобождаются сами (FreeOnTerminate) —
      // запускаем их уже остановленными.
      LCore.BeginStop;
      for I := 0 to High(LThreads) do
        if Assigned(LThreads[I]) then
          LThreads[I].Start;
      raise;
    end;
    FCore := LCore;
    FCoreRef := LRef;
  finally
    FLock.Leave;
  end;
  for I := 0 to High(LThreads) do
    LThreads[I].Start;
end;

function TTgUpdateDispatcher.Stop(AWaitMs: Cardinal): Boolean;
var
  LRef: IInterface;
  LCore: TTgDispatchCore;
begin
  LCore := TTgDispatchCore(CurrentCore(LRef));
  if not Assigned(LCore) then
    Exit(True);
  LCore.BeginStop;
  Result := TgWaitEventPumping(LCore.AllExited, AWaitMs);
end;

function TTgUpdateDispatcher.WaitIdle(AMs: Cardinal): Boolean;
var
  LRef: IInterface;
  LCore: TObject;
begin
  LCore := CurrentCore(LRef);
  Result := not Assigned(LCore) or TgWaitEventPumping(TTgDispatchCore(LCore).Idle, AMs);
end;

function TTgUpdateDispatcher.Post(const AUpdate: ITgRawUpdate;
  const ACancel: ITgCancellation): Boolean;
var
  LRef: IInterface;
  LCore: TObject;
begin
  LCore := CurrentCore(LRef);
  Result := Assigned(LCore) and Assigned(AUpdate) and
    TTgDispatchCore(LCore).Post(AUpdate, ACancel, INFINITE);
end;

function TTgUpdateDispatcher.TryPost(const AUpdate: ITgRawUpdate;
  const ACancel: ITgCancellation; ATimeoutMs: Cardinal): Boolean;
var
  LRef: IInterface;
  LCore: TObject;
begin
  LCore := CurrentCore(LRef);
  Result := Assigned(LCore) and Assigned(AUpdate) and
    TTgDispatchCore(LCore).Post(AUpdate, ACancel, ATimeoutMs);
end;

class function TTgUpdateDispatcher.InHandler: Boolean;
begin
  Result := GTgHandlerDepth > 0;
end;

function TTgUpdateDispatcher.GetActive: Boolean;
var
  LRef: IInterface;
  LCore: TObject;
begin
  LCore := CurrentCore(LRef);
  Result := Assigned(LCore) and not TTgDispatchCore(LCore).Stopping;
end;

function TTgUpdateDispatcher.GetCancel: ITgCancellation;
var
  LRef: IInterface;
  LCore: TObject;
begin
  LCore := CurrentCore(LRef);
  if Assigned(LCore) then
    Result := TTgDispatchCore(LCore).Cancel
  else
    Result := nil;
end;

{ TTgShutdownSignal }

var
  // Признак сигнала: пишется атомарно (в т.ч. из обработчика сигнала POSIX).
  GTgSignalFlag: Integer = 0;
  // Число вложенных Install.
  GTgSignalInstalls: Integer = 0;

{$IFDEF MSWINDOWS}
var
  // Событие «программа остановилась» (живёт до завершения процесса).
  GTgStoppedEvent: THandle = 0;

function TgConsoleCtrlHandler(ACtrlType: DWORD): BOOL; stdcall;
begin
  case ACtrlType of
    CTRL_C_EVENT, CTRL_BREAK_EVENT:
      begin
        AtomicExchange(GTgSignalFlag, 1);
        Result := True;
      end;
    CTRL_CLOSE_EVENT, CTRL_LOGOFF_EVENT, CTRL_SHUTDOWN_EVENT:
      begin
        AtomicExchange(GTgSignalFlag, 1);
        // После возврата Windows завершает процесс: даём боту остановиться.
        if GTgStoppedEvent <> 0 then
          WaitForSingleObject(GTgStoppedEvent, 4500);
        Result := True;
      end;
  else
    Result := False;
  end;
end;
{$ENDIF}

{$IF defined(POSIX) and not defined(ANDROID)}
var
  GTgOldSigInt: sigaction_t;
  GTgOldSigTerm: sigaction_t;

procedure TgSignalHandler(ASignal: Integer); cdecl;
begin
  // Только запись выровненного Integer — допустимо в обработчике сигнала.
  GTgSignalFlag := 1;
end;
{$IFEND}

class function TTgShutdownSignal.Supported: Boolean;
begin
{$IF defined(MSWINDOWS) or (defined(POSIX) and not defined(ANDROID))}
  Result := True;
{$ELSE}
  Result := False;
{$IFEND}
end;

class function TTgShutdownSignal.Install: Boolean;
{$IF defined(POSIX) and not defined(ANDROID)}
var
  LAction: sigaction_t;
{$IFEND}
begin
  Result := Supported;
  if not Result then
    Exit;
  if AtomicIncrement(GTgSignalInstalls) > 1 then
    Exit;
{$IFDEF MSWINDOWS}
  if GTgStoppedEvent = 0 then
    GTgStoppedEvent := CreateEvent(nil, True, False, nil);
  Result := SetConsoleCtrlHandler(@TgConsoleCtrlHandler, True);
{$ENDIF}
{$IF defined(POSIX) and not defined(ANDROID)}
  FillChar(LAction, SizeOf(LAction), 0);
  // Поле обработчика — первое в sigaction_t (имя объединения различается
  // в Linux и macOS), поэтому пишем его по смещению 0.
  PPointer(@LAction)^ := @TgSignalHandler;
  sigemptyset(LAction.sa_mask);
  LAction.sa_flags := SA_RESTART;
  Result := (sigaction(SIGINT, @LAction, @GTgOldSigInt) = 0) and
    (sigaction(SIGTERM, @LAction, @GTgOldSigTerm) = 0);
{$IFEND}
  if not Result then
    AtomicDecrement(GTgSignalInstalls);
end;

class procedure TTgShutdownSignal.Uninstall;
begin
  if not Supported then
    Exit;
  if AtomicDecrement(GTgSignalInstalls) <> 0 then
  begin
    if GTgSignalInstalls < 0 then
      GTgSignalInstalls := 0;
    Exit;
  end;
{$IFDEF MSWINDOWS}
  SetConsoleCtrlHandler(@TgConsoleCtrlHandler, False);
{$ENDIF}
{$IF defined(POSIX) and not defined(ANDROID)}
  sigaction(SIGINT, @GTgOldSigInt, nil);
  sigaction(SIGTERM, @GTgOldSigTerm, nil);
{$IFEND}
end;

class function TTgShutdownSignal.Requested: Boolean;
begin
  Result := AtomicCmpExchange(GTgSignalFlag, 0, 0) <> 0;
end;

class procedure TTgShutdownSignal.Request;
begin
  AtomicExchange(GTgSignalFlag, 1);
end;

class procedure TTgShutdownSignal.Reset;
begin
  AtomicExchange(GTgSignalFlag, 0);
{$IFDEF MSWINDOWS}
  if GTgStoppedEvent <> 0 then
    ResetEvent(GTgStoppedEvent);
{$ENDIF}
end;

class procedure TTgShutdownSignal.NotifyStopped;
begin
{$IFDEF MSWINDOWS}
  if GTgStoppedEvent <> 0 then
    SetEvent(GTgStoppedEvent);
{$ENDIF}
end;

initialization

finalization
{$IFDEF MSWINDOWS}
  if GTgStoppedEvent <> 0 then
  begin
    CloseHandle(GTgStoppedEvent);
    GTgStoppedEvent := 0;
  end;
{$ENDIF}

end.
