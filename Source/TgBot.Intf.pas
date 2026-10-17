unit TgBot.Intf;

{
  TgBot — контракты библиотеки: интерфейсы и записи настроек без реализаций.

  Модуль для тех, кто пишет свою реализацию (транспорт, хранилище состояния,
  источник или приёмник обновлений) или зависит только от абстракций:
  uses TgBot.Intf не тянет реализации — ни System.Net.*, ни Indy, ни
  TgBot.Http/TgBot.Core/TgBot.Updates.*. Зависимости: TgBot.Base (токены
  отмены, исключения), TgBot.Json (TTgParams); в implementation —
  TgBot.Consts (тексты ошибок проверки прокси).

  - транспорт Bot API: ITgTransport, ITgCancellableTransport,
    ITgHttpSettingsProvider; записи TTgProxySettings, TTgHttpSettings,
    TTgHttpResponse; константы транспорта по умолчанию (TgDefault…);
  - приём обновлений: ITgRawUpdate, ITgUpdateSink, ITgTimedUpdateSink,
    ITgWebhookReceiver, ITgUpdateSource, ITgPollTimer; перечисления
    TTgSourceState, TTgAckPolicy, TTgDelivery, TTgWebhookResult; типы
    обработчиков TTgRawHandler, TTgRawErrorHandler, TTgConflictHandler;
  - источники обновлений и диспетчер как интерфейсы: ITgLongPollSource,
    ITgWebhookSource, ITgUpdateDispatcher;
  - состояние диалогов: ITgStateStorage;
  - псевдонимы типов из сигнатур контрактов: ITgCancellation,
    ITgCancellationSource, TTgInputFile (TgBot.Base), TTgParams
    (TgBot.Json). Обобщённый TTgOptional<T> (AllowedUpdates источников)
    псевдонимом не реэкспортируется (ограничение языка) — для объявления
    переменных этого типа нужен TgBot.Base в uses.

  Реализации — в прежних модулях (TTgHttpTransport — TgBot.Http,
  TTgMemoryStateStorage — TgBot.State, источники и диспетчер с фабриками
  New — TgBot.Updates.Polling, TgBot.Updates.WebhookSource,
  TgBot.Updates.Dispatcher). Там же остались псевдонимы перенесённых типов:
  код с uses TgBot.Http, TgBot.Updates.*, TgBot.State или фасада TgBot
  компилируется без изменений, GUID интерфейсов прежние.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.Classes,
  System.JSON,
  TgBot.Base,
  TgBot.Json;

const
  /// <summary>Адрес облачного Bot API по умолчанию.</summary>
  TgDefaultApiUrl = 'https://api.telegram.org';
  /// <summary>Таймаут соединения по умолчанию, мс.</summary>
  TgDefaultConnectionTimeoutMs = 15000;
  /// <summary>Таймаут ответа по умолчанию, мс (для long polling увеличивается автоматически).</summary>
  TgDefaultResponseTimeoutMs = 60000;
  /// <summary>Максимум попыток повтора при 429 по умолчанию.</summary>
  TgDefaultMaxRetries = 3;
  /// <summary>Максимальное ожидание retry_after по умолчанию, с (больше — ошибка сразу).</summary>
  TgDefaultMaxRetryAfterSec = 60;
  /// <summary>Глобальный лимит запросов в секунду на бота по умолчанию.</summary>
  TgDefaultGlobalRatePerSec = 30;
  /// <summary>Минимальный интервал между сообщениями в один чат по умолчанию, мс.</summary>
  TgDefaultPerChatIntervalMs = 1000;

type
  { Типы из сигнатур контрактов (объявлены в TgBot.Base и TgBot.Json) }

  /// <summary>Токен отмены операции (TgBot.Base.ITgCancellation).</summary>
  ITgCancellation = TgBot.Base.ITgCancellation;
  /// <summary>Источник отмены (TgBot.Base.ITgCancellationSource).</summary>
  ITgCancellationSource = TgBot.Base.ITgCancellationSource;
  /// <summary>Входной файл (TgBot.Base.TTgInputFile; сертификат ITgWebhookSource).</summary>
  TTgInputFile = TgBot.Base.TTgInputFile;
  /// <summary>Параметры метода Bot API (TgBot.Json.TTgParams).</summary>
  TTgParams = TgBot.Json.TTgParams;

  { Транспорт Bot API }

  /// <summary>
  ///   Настройки HTTP-прокси бота (применяются ко всем запросам транспорта:
  ///   методы Bot API, long polling, скачивание файлов). Запросы к https://
  ///   (облачный Bot API) идут через прокси туннелем CONNECT — прокси должен
  ///   его поддерживать. Поддерживается только HTTP-прокси: SOCKS- и
  ///   HTTPS-прокси (TLS до самого прокси) библиотека не поддерживает. Настройки
  ///   проверяет и нормализует TTgTransportBase.Create (TgBot.Transport; см.
  ///   Normalized), ошибка настройки — ETgError. Преобразование в настройки RTL
  ///   (TProxySettings) — ToRtlSettings, помощник записи в TgBot.Http и
  ///   фасаде TgBot.
  ///   Поле записи меняется на месте, в том числе через with:
  ///   <code>
  ///   LSettings := TTgHttpSettings.Create(LToken);
  ///   with LSettings.Proxy do begin Host := '192.168.1.1'; Port := 3128; end;
  ///   LBot := TTgBot.Create(LSettings);
  ///   </code>
  ///   При сетевой ошибке текст ETgNetworkError содержит адрес прокси.
  /// </summary>
  TTgProxySettings = record
    /// <summary>
    ///   Хост прокси; пусто — прокси бота не задан (Windows: системные
    ///   настройки прокси WinHTTP/IE). Адреса 127.0.0.1/localhost в ApiUrl
    ///   WinHTTP запрашивает напрямую, минуя прокси. Допустимо 'хост:порт',
    ///   префикс 'http://' и завершающий '/' ('http://proxy:3128/'); IPv6 —
    ///   '[::1]' или без скобок.
    /// </summary>
    Host: string;
    /// <summary>Порт прокси 1..65535; 0 — порт берётся из Host ('хост:порт').</summary>
    Port: Integer;
    /// <summary>Имя пользователя (необязательно).</summary>
    UserName: string;
    /// <summary>Пароль (необязательно).</summary>
    Password: string;
    /// <summary>
    ///   Схема прокси — для совместимости: допустимы только пусто и 'http'
    ///   (равнозначно, HTTP-прокси). В RTL всегда передаётся пустая схема:
    ///   на Windows схема RTL — протокол связи с самим прокси ('https' —
    ///   TLS до прокси, обычный HTTP-прокси на это отвечает ошибкой 12029),
    ///   на Linux (curl) и Android RTL её не использует. Другие значения
    ///   ('https', 'socks5'…) — ETgError при создании транспорта.
    /// </summary>
    Scheme: string;
    /// <summary>Создаёт настройки прокси.</summary>
    class function Create(const AHost: string; APort: Integer;
      const AUserName: string = ''; const APassword: string = '';
      const AScheme: string = ''): TTgProxySettings; static;
    /// <summary>Прокси задан.</summary>
    function IsEnabled: Boolean;
    /// <summary>
    ///   Проверенная копия настроек: Host без пробелов, префикса 'http://' и
    ///   одного завершающего '/', порт из 'хост:порт' (при Port = 0), IPv6
    ///   без скобок — в '[…]'.
    ///   Host пустой или из пробелов — Host = '' без проверок (прокси не
    ///   задан). Учётные данные в тексты ошибок не попадают. Ошибки —
    ///   ETgError: схема, кроме '' и 'http' (в Scheme или 'схема://' в Host);
    ///   путь ('/' не последним символом), '@' или пробел в Host; порт вне
    ///   1..65535; порт в Host не совпадает с Port.
    /// </summary>
    function Normalized: TTgProxySettings;
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
  ///   Служебный: транспорт с настройками TTgHttpSettings (реализует
  ///   TTgTransportBase, TgBot.Transport). Через него клиент получает
  ///   настройки транспорта без приведения к классу. В прикладном коде не
  ///   нужен.
  /// </summary>
  ITgHttpSettingsProvider = interface
    ['{804B9679-6947-4414-8785-FE1C5499DF87}']
    /// <summary>Настройки транспорта (копия записи).</summary>
    function GetSettings: TTgHttpSettings;
  end;

  { Приём обновлений }

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
  ///   ответа — TgWebhookHttpStatus (TgBot.Updates).
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

  { Источники обновлений и диспетчер (реализации — TTgLongPollSource,
    TTgWebhookSource, TTgUpdateDispatcher в TgBot.Updates.*) }

  /// <summary>
  ///   Источник long polling как интерфейс: все настройки и события
  ///   TTgLongPollSource (описание — у класса), Offset, ConfirmedOffset и
  ///   WaitForThread. Создавайте через TTgLongPollSource.New и храните как
  ///   интерфейс; не храните ссылку на класс — объект освобождается по
  ///   счётчику ссылок. Настройки задаются до Start.
  /// </summary>
  ITgLongPollSource = interface(ITgUpdateSource)
    ['{5CD90BA7-B869-4CA5-AD10-8388B5EB380D}']
    function GetOffset: Int64;
    function GetConfirmedOffset: Int64;
    function GetLimit: Integer;
    procedure SetLimit(AValue: Integer);
    function GetTimeoutSec: Integer;
    procedure SetTimeoutSec(AValue: Integer);
    function GetAllowedUpdates: TTgOptional<TArray<string>>;
    procedure SetAllowedUpdates(const AValue: TTgOptional<TArray<string>>);
    function GetDropPendingUpdates: Boolean;
    procedure SetDropPendingUpdates(AValue: Boolean);
    function GetAutoDeleteWebhook: Boolean;
    procedure SetAutoDeleteWebhook(AValue: Boolean);
    function GetAckPolicy: TTgAckPolicy;
    procedure SetAckPolicy(AValue: TTgAckPolicy);
    function GetDrainTimeoutMs: Cardinal;
    procedure SetDrainTimeoutMs(AValue: Cardinal);
    function GetConflictNotifyIntervalMs: Cardinal;
    procedure SetConflictNotifyIntervalMs(AValue: Cardinal);
    function GetJitterPercent: Integer;
    procedure SetJitterPercent(AValue: Integer);
    function GetTimer: ITgPollTimer;
    procedure SetTimer(const AValue: ITgPollTimer);
    function GetOnConflict: TTgConflictHandler;
    procedure SetOnConflict(const AValue: TTgConflictHandler);
    function GetOnError: TProc<Exception>;
    procedure SetOnError(const AValue: TProc<Exception>);
    function GetOnFault: TProc<Exception>;
    procedure SetOnFault(const AValue: TProc<Exception>);
    /// <summary>
    ///   Ждёт фактического завершения потока источника (в т.ч. отпущенного
    ///   при Stop = False). True — поток завершён или не запускался.
    /// </summary>
    function WaitForThread(AMs: Cardinal): Boolean;
    /// <summary>offset следующего запроса getUpdates (последний принятый update_id + 1; 0 — не было).</summary>
    property Offset: Int64 read GetOffset;
    /// <summary>offset, подтверждённый серверу (последний успешный getUpdates или итоговый).</summary>
    property ConfirmedOffset: Int64 read GetConfirmedOffset;
    /// <summary>limit getUpdates (1–100), по умолчанию TgDefaultPollLimit.</summary>
    property Limit: Integer read GetLimit write SetLimit;
    /// <summary>timeout getUpdates, с (0 — короткий опрос), по умолчанию TgDefaultPollTimeoutSec.</summary>
    property TimeoutSec: Integer read GetTimeoutSec write SetTimeoutSec;
    /// <summary>allowed_updates (TTgUpdateType.*); не задано — не передаётся.</summary>
    property AllowedUpdates: TTgOptional<TArray<string>> read GetAllowedUpdates write SetAllowedUpdates;
    /// <summary>При старте вызвать deleteWebhook(drop_pending_updates = true): пропустить накопившееся.</summary>
    property DropPendingUpdates: Boolean read GetDropPendingUpdates write SetDropPendingUpdates;
    /// <summary>При 409 «webhook is active» удалить webhook и продолжить (по умолчанию False).</summary>
    property AutoDeleteWebhook: Boolean read GetAutoDeleteWebhook write SetAutoDeleteWebhook;
    /// <summary>Политика подтверждения, по умолчанию AfterReceive.</summary>
    property AckPolicy: TTgAckPolicy read GetAckPolicy write SetAckPolicy;
    /// <summary>Дренаж при Stop, мс (по умолчанию TgDefaultDrainTimeoutMs).</summary>
    property DrainTimeoutMs: Cardinal read GetDrainTimeoutMs write SetDrainTimeoutMs;
    /// <summary>Минимальный интервал OnConflict для «другого getUpdates», мс.</summary>
    property ConflictNotifyIntervalMs: Cardinal read GetConflictNotifyIntervalMs
      write SetConflictNotifyIntervalMs;
    /// <summary>Разброс пауз, ± процентов (0–50), по умолчанию 20.</summary>
    property JitterPercent: Integer read GetJitterPercent write SetJitterPercent;
    /// <summary>Часы и паузы (nil — системные).</summary>
    property Timer: ITgPollTimer read GetTimer write SetTimer;
    /// <summary>409: другой экземпляр бота или установлен webhook.</summary>
    property OnConflict: TTgConflictHandler read GetOnConflict write SetOnConflict;
    /// <summary>Временная ошибка getUpdates (перед паузой и повтором).</summary>
    property OnError: TProc<Exception> read GetOnError write SetOnError;
    /// <summary>Неустранимая ошибка: источник перешёл в Faulted.</summary>
    property OnFault: TProc<Exception> read GetOnFault write SetOnFault;
  end;

  /// <summary>
  ///   Webhook-источник как интерфейс: все настройки и события
  ///   TTgWebhookSource (описание — у класса), Accept, WaitForThread и
  ///   Receiver. Создавайте через TTgWebhookSource.New и храните как
  ///   интерфейс; не храните ссылку на класс — объект освобождается по
  ///   счётчику ссылок. Настройки задаются до Start.
  /// </summary>
  ITgWebhookSource = interface(ITgUpdateSource)
    ['{7E49F47D-6569-4AF4-8FA1-1D51B7817E7D}']
    function GetUrl: string;
    procedure SetUrl(const AValue: string);
    function GetSecretToken: string;
    procedure SetSecretToken(const AValue: string);
    function GetMaxConnections: Integer;
    procedure SetMaxConnections(AValue: Integer);
    function GetDropPendingUpdates: Boolean;
    procedure SetDropPendingUpdates(AValue: Boolean);
    function GetIpAddress: string;
    procedure SetIpAddress(const AValue: string);
    function GetCertificate: TTgInputFile;
    procedure SetCertificate(const AValue: TTgInputFile);
    function GetAllowedUpdates: TTgOptional<TArray<string>>;
    procedure SetAllowedUpdates(const AValue: TTgOptional<TArray<string>>);
    function GetRegisterOnStart: Boolean;
    procedure SetRegisterOnStart(AValue: Boolean);
    function GetDeleteOnStop: Boolean;
    procedure SetDeleteOnStop(AValue: Boolean);
    function GetMaxBodySize: Integer;
    procedure SetMaxBodySize(AValue: Integer);
    function GetPostTimeoutMs: Cardinal;
    procedure SetPostTimeoutMs(AValue: Cardinal);
    function GetDedupWindow: Integer;
    procedure SetDedupWindow(AValue: Integer);
    function GetOnError: TProc<Exception>;
    procedure SetOnError(const AValue: TProc<Exception>);
    function GetOnFault: TProc<Exception>;
    procedure SetOnFault(const AValue: TProc<Exception>);
    /// <summary>Тело — байты UTF-8 (как пришли по сети); см. ITgWebhookReceiver.</summary>
    function Accept(const ABody: TBytes; const ASecretHeader: string): TTgWebhookResult; overload;
    /// <summary>Тело — уже декодированная строка; см. ITgWebhookReceiver.</summary>
    function Accept(const ABody, ASecretHeader: string): TTgWebhookResult; overload;
    /// <summary>
    ///   Ждёт завершения служебного потока (в т.ч. отпущенного при Stop =
    ///   False). True — завершён или не запускался.
    /// </summary>
    function WaitForThread(AMs: Cardinal): Boolean;
    /// <summary>
    ///   Приёмник тела webhook-запроса для HTTP-сервера приложения: новая
    ///   тонкая обёртка, которая реализует только ITgWebhookReceiver и
    ///   передаёт Accept источнику (получить из неё ITgWebhookSource и
    ///   остановить источник нельзя). Держит источник, как и сам интерфейс.
    /// </summary>
    function Receiver: ITgWebhookReceiver;
    /// <summary>Внешний HTTPS-URL webhook (параметр url setWebhook).</summary>
    property Url: string read GetUrl write SetUrl;
    /// <summary>secret_token: Accept сверяет его с заголовком; пусто — не передаётся и не проверяется.</summary>
    property SecretToken: string read GetSecretToken write SetSecretToken;
    /// <summary>max_connections (1–100); 0 — не передаётся (значение сервера, 40).</summary>
    property MaxConnections: Integer read GetMaxConnections write SetMaxConnections;
    /// <summary>drop_pending_updates setWebhook: пропустить накопившиеся обновления.</summary>
    property DropPendingUpdates: Boolean read GetDropPendingUpdates write SetDropPendingUpdates;
    /// <summary>ip_address setWebhook (вместо адреса из DNS); пусто — не передаётся.</summary>
    property IpAddress: string read GetIpAddress write SetIpAddress;
    /// <summary>Публичный ключ самоподписанного сертификата (certificate); пусто — нет.</summary>
    property Certificate: TTgInputFile read GetCertificate write SetCertificate;
    /// <summary>allowed_updates; не задано — не передаётся.</summary>
    property AllowedUpdates: TTgOptional<TArray<string>> read GetAllowedUpdates write SetAllowedUpdates;
    /// <summary>Вызывать setWebhook при Start (по умолчанию True).</summary>
    property RegisterOnStart: Boolean read GetRegisterOnStart write SetRegisterOnStart;
    /// <summary>Вызывать deleteWebhook при Stop (по умолчанию False).</summary>
    property DeleteOnStop: Boolean read GetDeleteOnStop write SetDeleteOnStop;
    /// <summary>Наибольший размер тела, байт UTF-8 (по умолчанию 1 МБ); больше — BadRequest.</summary>
    property MaxBodySize: Integer read GetMaxBodySize write SetMaxBodySize;
    /// <summary>Сколько Accept ждёт места в очереди, мс (по умолчанию 250).</summary>
    property PostTimeoutMs: Cardinal read GetPostTimeoutMs write SetPostTimeoutMs;
    /// <summary>Сколько последних update_id помнить для дедупликации (0 — без неё).</summary>
    property DedupWindow: Integer read GetDedupWindow write SetDedupWindow;
    /// <summary>Ошибка deleteWebhook при Stop (в служебном потоке; исключения поглощаются).</summary>
    property OnError: TProc<Exception> read GetOnError write SetOnError;
    /// <summary>Ошибка setWebhook: источник перешёл в Faulted (в служебном потоке).</summary>
    property OnFault: TProc<Exception> read GetOnFault write SetOnFault;
  end;

  /// <summary>
  ///   Диспетчер обновлений как интерфейс (публичный): запуск, остановка,
  ///   ожидание и все настройки и события TTgUpdateDispatcher (описание —
  ///   у класса). Не путать со служебным ITgDispatchCore (ядро одного
  ///   запуска, не часть публичного API). Ограниченное ожидание места в
  ///   очереди (TryPost) — по-прежнему через Supports(…, ITgTimedUpdateSink).
  ///   Создавайте через TTgUpdateDispatcher.New и храните как интерфейс; не
  ///   храните ссылку на класс — объект освобождается по счётчику ссылок.
  /// </summary>
  ITgUpdateDispatcher = interface(ITgUpdateSink)
    ['{49ACBBD3-EBE0-41BB-B4BE-62EDDE0946FE}']
    function GetActive: Boolean;
    function GetCancel: ITgCancellation;
    function GetMaxParallel: Integer;
    procedure SetMaxParallel(AValue: Integer);
    function GetQueueCapacity: Integer;
    procedure SetQueueCapacity(AValue: Integer);
    function GetDelivery: TTgDelivery;
    procedure SetDelivery(AValue: TTgDelivery);
    function GetOnError: TTgRawErrorHandler;
    procedure SetOnError(const AValue: TTgRawErrorHandler);
    function GetOnProcessed: TProc<Int64>;
    procedure SetOnProcessed(const AValue: TProc<Int64>);
    /// <summary>Запускает потоки. Повторный Start работающего диспетчера — ETgError.</summary>
    procedure Start;
    /// <summary>
    ///   Отменяет токен диспетчера, выбрасывает необработанную очередь и ждёт
    ///   потоки не дольше AWaitMs. False — потоки с зависшими обработчиками отпущены.
    /// </summary>
    function Stop(AWaitMs: Cardinal): Boolean;
    /// <summary>Ждёт, пока очередь опустеет и обработчики завершатся; True — дождались.</summary>
    function WaitIdle(AMs: Cardinal): Boolean;
    /// <summary>Диспетчер запущен и не останавливается.</summary>
    property Active: Boolean read GetActive;
    /// <summary>Токен отмены текущего запуска (nil — не запущен).</summary>
    property Cancel: ITgCancellation read GetCancel;
    /// <summary>Число потоков (1–64), по умолчанию TgDefaultMaxParallel; задаётся до Start.</summary>
    property MaxParallel: Integer read GetMaxParallel write SetMaxParallel;
    /// <summary>Ёмкость очереди, по умолчанию TgDefaultQueueCapacity; задаётся до Start.</summary>
    property QueueCapacity: Integer read GetQueueCapacity write SetQueueCapacity;
    /// <summary>Где выполнять обработчик; задаётся до Start.</summary>
    property Delivery: TTgDelivery read GetDelivery write SetDelivery;
    /// <summary>Исключение обработчика (в потоке обработчика); задаётся до Start.</summary>
    property OnError: TTgRawErrorHandler read GetOnError write SetOnError;
    /// <summary>Обновление обработано (в т.ч. с исключением); задаётся до Start.</summary>
    property OnProcessed: TProc<Int64> read GetOnProcessed write SetOnProcessed;
  end;

  { Состояние диалогов }

  /// <summary>
  ///   Хранилище состояния: строковые значения AName в пределах ключа AKey.
  ///   Реализации обязаны быть потокобезопасными.
  /// </summary>
  ITgStateStorage = interface
    ['{0C6A2F51-5A3B-4D7E-9B83-61A7C4E2D915}']
    /// <summary>Значение AName ключа AKey; False — значения нет.</summary>
    function TryGet(const AKey, AName: string; out AValue: string): Boolean;
    /// <summary>Записывает (заменяет) значение AName ключа AKey.</summary>
    procedure Put(const AKey, AName, AValue: string);
    /// <summary>Удаляет значение AName ключа AKey; AName = '' — все значения ключа.</summary>
    procedure Delete(const AKey: string; const AName: string = '');
  end;

implementation

uses
  TgBot.Consts;

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

/// <summary>Порт в адресе прокси: 1–5 десятичных цифр (без знака и '$').</summary>
function IsProxyPortText(const AText: string): Boolean;
var
  I: Integer;
begin
  Result := (Length(AText) >= 1) and (Length(AText) <= 5);
  for I := 1 to Length(AText) do
    if not CharInSet(AText[I], ['0'..'9']) then
      Exit(False);
end;

/// <summary>Имя схемы URL (буквы, цифры, '+', '-', '.') — без учётных данных.</summary>
function IsSchemeName(const AText: string): Boolean;
var
  I: Integer;
begin
  Result := AText <> '';
  for I := 1 to Length(AText) do
    if not CharInSet(AText[I], ['A'..'Z', 'a'..'z', '0'..'9', '+', '-', '.']) then
      Exit(False);
end;

function TTgProxySettings.Normalized: TTgProxySettings;
const
  CHttpPrefix = 'http://';
  CSchemeMark = '://';

  procedure RaiseBadHost;
  begin
    raise ETgError.Create(TgLangText(@SRuProxyBadHost, @SEnProxyBadHost));
  end;

var
  LHost, LPortText, LScheme: string;
  LMark, LColons, LHostPort, I: Integer;
begin
  Result := Self;
  LHost := Trim(Host);
  Result.Host := LHost;
  if LHost = '' then
    Exit;
  // Схема RTL всё равно пустая (ToRtlSettings); иные значения — неподдерживаемый прокси.
  LScheme := Trim(Scheme);
  if (LScheme <> '') and not SameText(LScheme, 'http') then
    raise ETgError.Create(TgLangTextFmt(@SRuProxyScheme, @SEnProxyScheme, [LScheme]));
  if SameText(Copy(LHost, 1, Length(CHttpPrefix)), CHttpPrefix) then
    Delete(LHost, 1, Length(CHttpPrefix))
  else
  begin
    LMark := Pos(CSchemeMark, LHost);
    if LMark > 0 then
    begin
      // В текст — только имя схемы: после неё могут идти логин и пароль.
      LScheme := Copy(LHost, 1, LMark - 1);
      if not IsSchemeName(LScheme) then
        RaiseBadHost;
      raise ETgError.Create(TgLangTextFmt(@SRuProxyScheme, @SEnProxyScheme, [LScheme]));
    end;
  end;
  // Один завершающий '/' ('http://proxy:3128/') допустим; путь — нет.
  if (LHost <> '') and (LHost[Length(LHost)] = '/') then
    SetLength(LHost, Length(LHost) - 1);
  if LHost = '' then
    RaiseBadHost;
  for I := 1 to Length(LHost) do
    if CharInSet(LHost[I], ['/', '\', '@']) or (LHost[I] <= ' ') then
      RaiseBadHost;
  LPortText := '';
  if LHost[1] = '[' then
  begin
    // IPv6 в скобках: '[адрес]' или '[адрес]:порт'.
    LMark := Pos(']', LHost);
    if (LMark <= 2) or (Pos('[', Copy(LHost, 2, LMark - 2)) > 0) then
      RaiseBadHost;
    LPortText := Copy(LHost, LMark + 1, MaxInt);
    SetLength(LHost, LMark);
    if LPortText <> '' then
    begin
      if LPortText[1] <> ':' then
        RaiseBadHost;
      Delete(LPortText, 1, 1);
      if not IsProxyPortText(LPortText) then
        RaiseBadHost;
    end;
  end
  else
  begin
    if (Pos('[', LHost) > 0) or (Pos(']', LHost) > 0) then
      RaiseBadHost;
    LColons := 0;
    for I := 1 to Length(LHost) do
      if LHost[I] = ':' then
        Inc(LColons);
    if LColons = 1 then
    begin
      LMark := Pos(':', LHost);
      LPortText := Copy(LHost, LMark + 1, MaxInt);
      SetLength(LHost, LMark - 1);
      if (LHost = '') or not IsProxyPortText(LPortText) then
        RaiseBadHost;
    end
    else if LColons > 1 then
      // IPv6 без скобок: порт в такой записи неотделим — только из Port.
      LHost := '[' + LHost + ']';
  end;
  Result.Host := LHost;
  if LPortText <> '' then
  begin
    LHostPort := StrToInt(LPortText);
    if (Result.Port <> 0) and (Result.Port <> LHostPort) then
      raise ETgError.Create(TgLangTextFmt(@SRuProxyPortConflict, @SEnProxyPortConflict,
        [LHost, LHostPort, Result.Port]));
    Result.Port := LHostPort;
  end;
  if (Result.Port < 1) or (Result.Port > 65535) then
    raise ETgError.Create(TgLangTextFmt(@SRuProxyPort, @SEnProxyPort, [LHost, Result.Port]));
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

end.
