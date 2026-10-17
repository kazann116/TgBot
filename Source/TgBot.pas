unit TgBot;

{
  TgBot 0.4.0 — библиотека Telegram Bot API 10.3 для Delphi (10.4 Sydney и новее;
  Win32, Win64, Linux64, Android).

  Подключение: добавьте папку Source в Search Path проекта (или в пути
  библиотеки IDE) и укажите в uses только этот модуль:

    uses
      TgBot;

    var
      LApi: TTgApi;
    begin
      LApi := TTgApi.Create('123456:ABC...');
      try
        LApi.SendMessage(123456789, 'Привет!');
      finally
        LApi.Free;
      end;
    end;

  Частые вызовы — позиционно (варианты методов, overrides methods.*.variants):

    LApi.SendMessage(LChatId, 'Выберите:',
      TTgKeyboard.Inline.Row.Button('Да', 'yes').Button('Нет', 'no'));
    LApi.AnswerCallbackQuery(LQuery.Id, 'Принято');
    LApi.EditMessageText(LChatId, LMessageId, 'Новый текст');
    LApi.EditInlineMessageText(LInlineMessageId, 'Новый текст'); // Boolean

  Клавиатуры: TTgKeyboard.Inline / Reply / Remove / ForceReply (неявно
  приводятся к ITgInlineKeyboardMarkup, ITgReplyKeyboardMarkup и
  TTgReplyMarkup); для фабрик с массивами строк — TgRow([A, B]).

  Бот (long polling, обработчики, состояние диалогов) — TTgBot:

    LBot := TTgBot.Create('123456:ABC...');
    try
      LBot.OnMessage :=
        procedure(ACtx: ITgContext)
        begin
          ACtx.Reply('Вы написали: ' + ACtx.Text);
        end;
      LBot.Run; // до Ctrl+C / SIGTERM
    finally
      LBot.Free;
    end;

  Маршрутизатор (команды, кнопки, текст; порядок — в описании TTgBot):

    LBot.Command('start', 'Начать',
      procedure(ACtx: ITgContext)
      begin
        ACtx.Reply('Выберите:', TTgKeyboard.Inline.Button('Да', 'yes'));
      end)
      .Callback('yes', procedure(ACtx: ITgContext) begin ACtx.Edit('Готово'); end)
      .TextMatch('^заказ (\d+)$',
        procedure(ACtx: ITgContext) begin ACtx.Reply('Заказ №' + ACtx.Args); end);

  Модуль собирает в одном месте:
  - псевдонимы сгенерированных типов и клиента TTgApi из TgBot.Types
    (Source\Generated\Gen.Aliases.inc, TgBotGen по спецификации Bot API
    10.3) — включается относительно этого файла, дополнительный путь -I
    не нужен;
  - псевдонимы типов ядра (TgBot.Base, TgBot.Json, TgBot.Http, TgBot.Dto,
    TgBot.Core, TgBot.Updates, TgBot.State), чтобы пользователю не
    требовались другие модули в uses; помощник TTgProxySettings.ToRtlSettings;
  - база своего транспорта TTgTransportBase и реестр транспорта по
    умолчанию (TgBot.Transport): uses TgBot подключает TgBot.Http, и клиент
    по токену получает TTgHttpTransport;
  - контракты (интерфейсы транспорта, источников, диспетчера, хранилища
    состояния и записи настроек) объявлены в модуле контрактов TgBot.Intf —
    для своей реализации без зависимости от реализаций библиотеки
    достаточно uses TgBot.Intf; псевдонимы здесь — те же типы и GUID;
  - псевдонимы построителей клавиатур TTgKeyboard (TgBot.Keyboards) и
    обёртки TgRow;
  - псевдоним контекста обработчика ITgContext (TgBot.Context);
  - псевдонимы бота TTgBot, TTgBotState, TTgReceiveMode (TgBot.Bot;
    внутреннее ядро бота — TgBot.Bot.Core);
  - функции TgHtmlEscape, TgMarkdownV2Escape и обёртки TgSetLanguage,
    TgBotThreadPool и т.п.

  Обобщённый TTgOptional<T> псевдонимом не реэкспортируется (ограничение
  языка): поля опций принимают значения неявно (LOptions.ParseMode :=
  TTgParseMode.Html), для объявления переменных — TTgOptionalString и т.п.
  или TgBot.Base в uses.

  Не редактируйте Gen.*.inc вручную — перегенерируйте TgBotGen --gen.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.Threading,
  System.Net.URLClient,
  TgBot.Base,
  TgBot.Json,
  TgBot.Transport,
  TgBot.Http,
  TgBot.Dto,
  TgBot.Core,
  TgBot.Types,
  TgBot.Updates,
  TgBot.State,
  TgBot.Keyboards,
  TgBot.Context,
  TgBot.Bot;

const
  /// <summary>Название библиотеки.</summary>
  TgBotLibName = TgBot.Base.TgBotLibName;
  /// <summary>Версия библиотеки строкой.</summary>
  TgBotVersion = TgBot.Base.TgBotVersion;
  /// <summary>Старший номер версии библиотеки.</summary>
  TgBotVersionMajor = TgBot.Base.TgBotVersionMajor;
  /// <summary>Младший номер версии библиотеки.</summary>
  TgBotVersionMinor = TgBot.Base.TgBotVersionMinor;
  /// <summary>Номер выпуска библиотеки.</summary>
  TgBotVersionRelease = TgBot.Base.TgBotVersionRelease;
  /// <summary>Значение заголовка User-Agent по умолчанию.</summary>
  TgBotUserAgent = TgBot.Base.TgBotUserAgent;
  /// <summary>Версия Telegram Bot API, по которой сгенерирован код.</summary>
  TgBotApiVersion = '10.3';

  /// <summary>Адрес облачного Bot API по умолчанию.</summary>
  TgDefaultApiUrl = TgBot.Http.TgDefaultApiUrl;
  /// <summary>Таймаут соединения по умолчанию, мс.</summary>
  TgDefaultConnectionTimeoutMs = TgBot.Http.TgDefaultConnectionTimeoutMs;
  /// <summary>Таймаут ответа по умолчанию, мс.</summary>
  TgDefaultResponseTimeoutMs = TgBot.Http.TgDefaultResponseTimeoutMs;
  /// <summary>Максимум попыток повтора при 429 по умолчанию.</summary>
  TgDefaultMaxRetries = TgBot.Http.TgDefaultMaxRetries;
  /// <summary>Максимальное ожидание retry_after по умолчанию, с.</summary>
  TgDefaultMaxRetryAfterSec = TgBot.Http.TgDefaultMaxRetryAfterSec;
  /// <summary>Глобальный лимит запросов в секунду по умолчанию.</summary>
  TgDefaultGlobalRatePerSec = TgBot.Http.TgDefaultGlobalRatePerSec;
  /// <summary>Минимальный интервал между сообщениями в один чат по умолчанию, мс.</summary>
  TgDefaultPerChatIntervalMs = TgBot.Http.TgDefaultPerChatIntervalMs;
  /// <summary>Сколько деструктор клиента ждёт начатые Async-вызовы по умолчанию, мс.</summary>
  TgDefaultShutdownTimeoutMs = TgBot.Core.TgDefaultShutdownTimeoutMs;
  /// <summary>Максимум потоков общего пула библиотеки по умолчанию.</summary>
  TgDefaultAsyncPoolSize = TgBot.Core.TgDefaultAsyncPoolSize;
  /// <summary>Таймаут long polling по умолчанию, с.</summary>
  TgDefaultPollTimeoutSec = TgBot.Updates.TgDefaultPollTimeoutSec;
  /// <summary>Максимум обновлений за один getUpdates по умолчанию.</summary>
  TgDefaultPollLimit = TgBot.Updates.TgDefaultPollLimit;
  /// <summary>Ёмкость очереди обновлений по умолчанию.</summary>
  TgDefaultQueueCapacity = TgBot.Updates.TgDefaultQueueCapacity;
  /// <summary>Число потоков обработчиков по умолчанию.</summary>
  TgDefaultMaxParallel = TgBot.Updates.TgDefaultMaxParallel;
  /// <summary>Дренаж очереди при остановке по умолчанию, мс.</summary>
  TgDefaultDrainTimeoutMs = TgBot.Updates.TgDefaultDrainTimeoutMs;
  /// <summary>Минимальный интервал между событиями OnConflict «другой getUpdates» по умолчанию, мс.</summary>
  TgDefaultConflictNotifyMs = TgBot.Updates.TgDefaultConflictNotifyMs;
  /// <summary>Разброс пауз между повторами getUpdates по умолчанию, ± процентов.</summary>
  TgDefaultBackoffJitterPercent = TgBot.Updates.TgDefaultBackoffJitterPercent;
  /// <summary>Наибольший размер тела webhook-запроса по умолчанию, байт (1 МБ).</summary>
  TgDefaultWebhookMaxBodySize = TgBot.Updates.TgDefaultWebhookMaxBodySize;
  /// <summary>Сколько HandleWebhook ждёт места в очереди по умолчанию, мс.</summary>
  TgDefaultWebhookPostTimeoutMs = TgBot.Updates.TgDefaultWebhookPostTimeoutMs;
  /// <summary>Окно дедупликации webhook по умолчанию (последних update_id).</summary>
  TgDefaultWebhookDedupWindow = TgBot.Updates.TgDefaultWebhookDedupWindow;
  /// <summary>Длина генерируемого секрета webhook.</summary>
  TgWebhookSecretLength = TgBot.Updates.TgWebhookSecretLength;
  /// <summary>Таймаут TTgBot.Stop по умолчанию, мс.</summary>
  TgDefaultBotStopTimeoutMs = TgBot.Bot.TgDefaultBotStopTimeoutMs;
  /// <summary>
  ///   Сколько Free бота ждёт фоновую подготовку (getMe/setMyCommands)
  ///   перед её отменой, мс; описание — TgBot.Bot.TgDefaultBotFreeStartJobWaitMs.
  /// </summary>
  TgDefaultBotFreeStartJobWaitMs = TgBot.Bot.TgDefaultBotFreeStartJobWaitMs;

type
  { Псевдонимы типов ядра (TgBot.Base) }

  /// <summary>Язык сообщений библиотеки (TgSetLanguage).</summary>
  TTgLanguage = TgBot.Base.TTgLanguage;
  /// <summary>Базовое исключение библиотеки.</summary>
  ETgError = TgBot.Base.ETgError;
  /// <summary>Ошибка, возвращённая Telegram Bot API (ok = false).</summary>
  ETgApiError = TgBot.Base.ETgApiError;
  /// <summary>Сетевая ошибка (нет соединения, таймаут, не JSON-ответ).</summary>
  ETgNetworkError = TgBot.Base.ETgNetworkError;
  /// <summary>Операция прервана отменой транспорта.</summary>
  ETgCancelledError = TgBot.Base.ETgCancelledError;
  /// <summary>Вид ошибки для Try-вариантов методов.</summary>
  TTgErrorKind = TgBot.Base.TTgErrorKind;
  /// <summary>Сведения об ошибке для Try-вариантов методов.</summary>
  TTgErrorInfo = TgBot.Base.TTgErrorInfo;
  /// <summary>Идентификатор чата: число или '@username'.</summary>
  TTgChatId = TgBot.Base.TTgChatId;
  /// <summary>Способ передачи файла.</summary>
  TTgInputFileKind = TgBot.Base.TTgInputFileKind;
  /// <summary>Входной файл (загрузка, file_id, URL, file://).</summary>
  TTgInputFile = TgBot.Base.TTgInputFile;
  /// <summary>Опциональная строка.</summary>
  TTgOptionalString = TgBot.Base.TTgOptional<string>;
  /// <summary>Опциональное целое.</summary>
  TTgOptionalInteger = TgBot.Base.TTgOptional<Integer>;
  /// <summary>Опциональное целое Int64.</summary>
  TTgOptionalInt64 = TgBot.Base.TTgOptional<Int64>;
  /// <summary>Опциональное логическое значение.</summary>
  TTgOptionalBoolean = TgBot.Base.TTgOptional<Boolean>;
  /// <summary>Опциональное вещественное.</summary>
  TTgOptionalDouble = TgBot.Base.TTgOptional<Double>;
  /// <summary>Опциональный массив строк (например, allowed_updates).</summary>
  TTgOptionalStrings = TgBot.Base.TTgOptional<TArray<string>>;

  { TgBot.Json }

  /// <summary>Безопасное чтение JSON (Raw-доступ к полям DTO).</summary>
  TTgJson = TgBot.Json.TTgJson;
  /// <summary>Файл, прикреплённый к запросу.</summary>
  TTgParamFile = TgBot.Json.TTgParamFile;
  /// <summary>Параметры вызова метода (для универсального Call/CallJson).</summary>
  TTgParams = TgBot.Json.TTgParams;

  { TgBot.Http }

  /// <summary>Настройки HTTP(S)-прокси.</summary>
  TTgProxySettings = TgBot.Http.TTgProxySettings;
  /// <summary>Настройки транспорта (токен, ApiUrl, прокси, таймауты, лимиты).</summary>
  TTgHttpSettings = TgBot.Http.TTgHttpSettings;
  /// <summary>Сырой HTTP-ответ (для собственных транспортов).</summary>
  TTgHttpResponse = TgBot.Http.TTgHttpResponse;
  /// <summary>Транспорт Bot API (подменяется в тестах).</summary>
  ITgTransport = TgBot.Http.ITgTransport;
  /// <summary>Транспорт на System.Net.HttpClient.</summary>
  TTgHttpTransport = TgBot.Http.TTgHttpTransport;
  /// <summary>
  ///   TTgProxySettings.ToRtlSettings при uses TgBot (без TgBot.Http).
  ///   Собственный помощник фасада: в области видимости действует один
  ///   помощник на тип, а псевдоним помощника TgBot.Http его не подключает.
  ///   При uses TgBot и TgBot.Http в любом порядке действует последний
  ///   подключённый помощник; оба вызывают TgBot.Http.TgProxyToRtlSettings,
  ///   результат одинаков.
  /// </summary>
  TTgProxySettingsHelper = record helper for TTgProxySettings
    /// <summary>
    ///   Настройки прокси для THTTPClient: Normalized, схема всегда пустая
    ///   (описание — TgBot.Http.TgProxyToRtlSettings).
    /// </summary>
    function ToRtlSettings: TProxySettings;
  end;

  { TgBot.Transport: база своего транспорта и фабрика транспорта по умолчанию }

  /// <summary>
  ///   База транспорта Bot API без HTTP-клиента: наследник реализует Post и
  ///   Download (описание и контракт — TgBot.Transport.TTgTransportBase).
  /// </summary>
  TTgTransportBase = TgBot.Transport.TTgTransportBase;
  /// <summary>POST-запрос метода Bot API для TTgTransportBase.Post.</summary>
  TTgPostRequest = TgBot.Transport.TTgPostRequest;
  /// <summary>GET-запрос файла для TTgTransportBase.Download.</summary>
  TTgDownloadRequest = TgBot.Transport.TTgDownloadRequest;
  /// <summary>Часть формы multipart/form-data (TTgPostRequest.Parts).</summary>
  TTgFormPart = TgBot.Transport.TTgFormPart;
  /// <summary>
  ///   Фабрика транспорта по умолчанию (TgRegisterDefaultTransport):
  ///   транспорт по настройкам для TTgApi.Create(AToken/ASettings).
  /// </summary>
  TTgTransportFactory = TgBot.Transport.TTgTransportFactory;

  { TgBot.Dto, TgBot.Core }

  /// <summary>Объект Bot API поверх JSON (входящий или двунаправленный).</summary>
  ITgJsonObject = TgBot.Dto.ITgJsonObject;
  /// <summary>Исходящий объект Bot API.</summary>
  ITgOutObject = TgBot.Dto.ITgOutObject;
  /// <summary>Хелперы DTO: Detach&lt;T&gt; (независимая копия) и др.</summary>
  TTgDto = TgBot.Dto.TTgDto;
  /// <summary>База клиента: транспорт, Call/CallJson, DownloadFile, RunAsync.</summary>
  TTgApiCore = TgBot.Core.TTgApiCore;

  { Отмена операций (TgBot.Base, TgBot.Http) }

  /// <summary>Токен отмены операции (nil — без отмены).</summary>
  ITgCancellation = TgBot.Base.ITgCancellation;
  /// <summary>
  ///   Источник отмены как интерфейс (токен + Cancel): создаётся через
  ///   TTgCancellationSource.New, хранить только как ITgCancellationSource.
  /// </summary>
  ITgCancellationSource = TgBot.Base.ITgCancellationSource;
  /// <summary>Источник отмены: New, Cancel, связанные токены (Linked).</summary>
  TTgCancellationSource = TgBot.Base.TTgCancellationSource;
  /// <summary>Окружающий токен отмены потока (Enter/Leave).</summary>
  TTgCancelScope = TgBot.Base.TTgCancelScope;
  /// <summary>Ошибка 409: другой экземпляр бота или установлен webhook.</summary>
  ETgConflictError = TgBot.Base.ETgConflictError;
  /// <summary>Транспорт с токеном отмены на операцию.</summary>
  ITgCancellableTransport = TgBot.Http.ITgCancellableTransport;

  { Приём обновлений (TgBot.Updates) и состояние диалогов (TgBot.State) }

  /// <summary>Состояние источника обновлений (Idle, Running, Stopping, Faulted).</summary>
  TTgSourceState = TgBot.Updates.TTgSourceState;
  /// <summary>Политика подтверждения обновлений (AfterReceive, AfterBatch).</summary>
  TTgAckPolicy = TgBot.Updates.TTgAckPolicy;
  /// <summary>Где выполняются обработчики (Worker, Main).</summary>
  TTgDelivery = TgBot.Updates.TTgDelivery;
  /// <summary>Обновление в сыром виде (update_id, вид, ключ чата, JSON).</summary>
  ITgRawUpdate = TgBot.Updates.ITgRawUpdate;
  /// <summary>Приёмник обновлений (очередь диспетчера).</summary>
  ITgUpdateSink = TgBot.Updates.ITgUpdateSink;
  /// <summary>
  ///   Приёмник с ограниченным ожиданием места в очереди (TryPost); диспетчер
  ///   поддерживает его — Supports(ITgUpdateDispatcher, ITgTimedUpdateSink).
  /// </summary>
  ITgTimedUpdateSink = TgBot.Updates.ITgTimedUpdateSink;
  /// <summary>Источник обновлений.</summary>
  ITgUpdateSource = TgBot.Updates.ITgUpdateSource;
  /// <summary>Часы и паузы источника (подменяются в тестах).</summary>
  ITgPollTimer = TgBot.Updates.ITgPollTimer;
  /// <summary>Обработчик сырого обновления.</summary>
  TTgRawHandler = TgBot.Updates.TTgRawHandler;
  /// <summary>Обработчик исключения обработчика сырого обновления.</summary>
  TTgRawErrorHandler = TgBot.Updates.TTgRawErrorHandler;
  /// <summary>Событие конфликта 409 источника.</summary>
  TTgConflictHandler = TgBot.Updates.TTgConflictHandler;
  /// <summary>Реализация ITgRawUpdate.</summary>
  TTgRawUpdate = TgBot.Updates.TTgRawUpdate;
  /// <summary>Long polling (getUpdates) в собственном потоке.</summary>
  TTgLongPollSource = TgBot.Updates.TTgLongPollSource;
  /// <summary>Источник long polling как интерфейс (создание — TTgLongPollSource.New; храните интерфейс, не класс).</summary>
  ITgLongPollSource = TgBot.Updates.ITgLongPollSource;
  /// <summary>Итог приёма webhook-запроса (Accepted, Forbidden, BadRequest, Unavailable).</summary>
  TTgWebhookResult = TgBot.Updates.TTgWebhookResult;
  /// <summary>Приём тела webhook-запроса из любого HTTP-сервера.</summary>
  ITgWebhookReceiver = TgBot.Updates.ITgWebhookReceiver;
  /// <summary>Webhook без собственного HTTP-сервера (setWebhook, Accept).</summary>
  TTgWebhookSource = TgBot.Updates.TTgWebhookSource;
  /// <summary>Webhook-источник как интерфейс (создание — TTgWebhookSource.New; храните интерфейс, не класс).</summary>
  ITgWebhookSource = TgBot.Updates.ITgWebhookSource;
  /// <summary>Диспетчер обновлений: порядок внутри чата, параллельность между чатами.</summary>
  TTgUpdateDispatcher = TgBot.Updates.TTgUpdateDispatcher;
  /// <summary>
  ///   Диспетчер как интерфейс (создание — TTgUpdateDispatcher.New; храните
  ///   интерфейс, не класс). Не путать со служебным ITgDispatchCore.
  /// </summary>
  ITgUpdateDispatcher = TgBot.Updates.ITgUpdateDispatcher;
  /// <summary>Сигнал завершения консольной программы (Ctrl+C, SIGTERM).</summary>
  TTgShutdownSignal = TgBot.Updates.TTgShutdownSignal;
  /// <summary>Хранилище состояния диалогов.</summary>
  ITgStateStorage = TgBot.State.ITgStateStorage;
  /// <summary>Хранилище состояния в памяти (по умолчанию).</summary>
  TTgMemoryStateStorage = TgBot.State.TTgMemoryStateStorage;

  { Сгенерированные типы Bot API и клиент TTgApi (TgBot.Types) }

{$I Generated\Gen.Aliases.inc}

  { Построители клавиатур (TgBot.Keyboards) и контекст обработчика (TgBot.Context) }
  /// <summary>
  ///   Построитель инлайн-клавиатуры (запись-значение); описание —
  ///   TgBot.Keyboards.TTgInlineKeyboardBuilder.
  /// </summary>
  TTgInlineKeyboardBuilder = TgBot.Keyboards.TTgInlineKeyboardBuilder;
  /// <summary>
  ///   Построитель обычной клавиатуры (запись-значение); описание —
  ///   TgBot.Keyboards.TTgReplyKeyboardBuilder.
  /// </summary>
  TTgReplyKeyboardBuilder = TgBot.Keyboards.TTgReplyKeyboardBuilder;
  /// <summary>
  ///   Фабрика клавиатур: Inline, Reply, Remove, ForceReply; описание и
  ///   примеры — TgBot.Keyboards.TTgKeyboard.
  /// </summary>
  TTgKeyboard = TgBot.Keyboards.TTgKeyboard;
  /// <summary>
  ///   Контекст обработчика TTgBot: обновление, Api, ответы, состояние
  ///   диалога; описание — TgBot.Context.ITgContext.
  /// </summary>
  ITgContext = TgBot.Context.ITgContext;

  { Бот (TgBot.Bot) }

  /// <summary>
  ///   Состояние бота (TTgBot.State): Idle, Running, Stopping, Faulted;
  ///   описание — TgBot.Bot.Core.TTgBotState.
  /// </summary>
  TTgBotState = TgBot.Bot.TTgBotState;
  /// <summary>Способ получения обновлений (TTgBot.Mode): Polling (по умолчанию) или Webhook.</summary>
  TTgReceiveMode = TgBot.Bot.TTgReceiveMode;
  /// <summary>
  ///   Бот: приём (long polling или webhook), раздача обработчикам,
  ///   маршрутизатор, контекст ITgContext и состояние диалогов
  ///   (подробное описание — TgBot.Bot.TTgBot).
  /// </summary>
  TTgBot = TgBot.Bot.TTgBot;

/// <summary>
///   Общий пул потоков Async-вызовов библиотеки (см. TgBot.Core.TgBotThreadPool).
/// </summary>
function TgBotThreadPool: TThreadPool;
/// <summary>HTTP-код ответа на webhook-запрос по итогу HandleWebhook: 200, 403, 400 или 503.</summary>
function TgWebhookHttpStatus(AResult: TTgWebhookResult): Integer;
/// <summary>Максимум рабочих потоков общего пула библиотеки (не меньше 1).</summary>
procedure TgSetAsyncPoolSize(AMaxThreads: Integer);

/// <summary>
///   Регистрирует фабрику транспорта по умолчанию; действует последняя
///   зарегистрированная (описание — TgBot.Transport.TgRegisterDefaultTransport).
///   При uses TgBot зарегистрирован TTgHttpTransport (TgBot.Http).
/// </summary>
procedure TgRegisterDefaultTransport(const AFactory: TTgTransportFactory);
/// <summary>
///   Снимает фабрику, зарегистрированную с той же ссылкой (описание —
///   TgBot.Transport.TgUnregisterDefaultTransport).
/// </summary>
procedure TgUnregisterDefaultTransport(const AFactory: TTgTransportFactory);
/// <summary>
///   Текущая фабрика транспорта по умолчанию или nil; вызывайте со скобками:
///   TgDefaultTransportFactory().
/// </summary>
function TgDefaultTransportFactory: TTgTransportFactory;
/// <summary>
///   Транспорт по умолчанию по настройкам; фабрики нет — ETgError
///   (описание — TgBot.Transport.TgCreateDefaultTransport).
/// </summary>
function TgCreateDefaultTransport(const ASettings: TTgHttpSettings): ITgTransport;

/// <summary>
///   Устанавливает язык сообщений библиотеки (по умолчанию — русский).
///   Вызывайте до запуска рабочих потоков.
/// </summary>
procedure TgSetLanguage(ALanguage: TTgLanguage);
/// <summary>Текущий язык сообщений библиотеки.</summary>
function TgGetLanguage: TTgLanguage;

/// <summary>
///   Строка инлайн-клавиатуры для фабрик с массивами массивов: вложенный
///   литерал [[A, B]] компилятор принимает за множество, поэтому
///   TTgInlineKeyboardMarkup.Create([TgRow([A, B]), TgRow([C])]).
/// </summary>
function TgRow(const AButtons: array of ITgInlineKeyboardButton): TArray<ITgInlineKeyboardButton>;
  overload;
/// <summary>Строка обычной клавиатуры: TTgReplyKeyboardMarkup.Create([TgRow([A, B])]).</summary>
function TgRow(const AButtons: array of ITgKeyboardButton): TArray<ITgKeyboardButton>; overload;

/// <summary>
///   Экранирует произвольный текст для вставки в сообщение с parse_mode =
///   HTML: '&amp;' → '&amp;amp;', '&lt;' → '&amp;lt;', '&gt;' → '&amp;gt;',
///   '"' → '&amp;quot;'. Пример: ACtx.ReplyHtml('&lt;b&gt;' +
///   TgHtmlEscape(LName) + '&lt;/b&gt;').
/// </summary>
function TgHtmlEscape(const S: string): string;
/// <summary>
///   Экранирует произвольный текст для parse_mode = MarkdownV2: перед
///   каждым из символов _ * [ ] ( ) ~ ` &gt; # + - = | { } . ! и '\'
///   ставится '\'.
/// </summary>
function TgMarkdownV2Escape(const S: string): string;

implementation

{ TTgProxySettingsHelper }

function TTgProxySettingsHelper.ToRtlSettings: TProxySettings;
begin
  Result := TgBot.Http.TgProxyToRtlSettings(Self);
end;

function TgHtmlEscape(const S: string): string;
var
  LBuilder: TStringBuilder;
  C: Char;
begin
  LBuilder := TStringBuilder.Create(Length(S) + 16);
  try
    for C in S do
      case C of
        '&': LBuilder.Append('&amp;');
        '<': LBuilder.Append('&lt;');
        '>': LBuilder.Append('&gt;');
        '"': LBuilder.Append('&quot;');
      else
        LBuilder.Append(C);
      end;
    Result := LBuilder.ToString;
  finally
    LBuilder.Free;
  end;
end;

function TgMarkdownV2Escape(const S: string): string;
var
  LBuilder: TStringBuilder;
  C: Char;
begin
  LBuilder := TStringBuilder.Create(Length(S) + 16);
  try
    for C in S do
    begin
      // Список символов — раздел «MarkdownV2 style» документации Bot API;
      // '\' экранируется, чтобы не стать экраном следующего символа.
      case C of
        '_', '*', '[', ']', '(', ')', '~', '`', '>', '#', '+', '-', '=', '|',
        '{', '}', '.', '!', '\':
          LBuilder.Append('\');
      end;
      LBuilder.Append(C);
    end;
    Result := LBuilder.ToString;
  finally
    LBuilder.Free;
  end;
end;

// Обёртки не inline: иначе при вызове из модуля без TgBot.Base в uses
// компилятор выдаёт подсказку H2443 и всё равно не разворачивает вызов.

procedure TgSetLanguage(ALanguage: TTgLanguage);
begin
  TgBot.Base.TgSetLanguage(ALanguage);
end;

function TgGetLanguage: TTgLanguage;
begin
  Result := TgBot.Base.TgGetLanguage;
end;

function TgBotThreadPool: TThreadPool;
begin
  Result := TgBot.Core.TgBotThreadPool;
end;

function TgWebhookHttpStatus(AResult: TTgWebhookResult): Integer;
begin
  Result := TgBot.Updates.TgWebhookHttpStatus(AResult);
end;

procedure TgSetAsyncPoolSize(AMaxThreads: Integer);
begin
  TgBot.Core.TgSetAsyncPoolSize(AMaxThreads);
end;

procedure TgRegisterDefaultTransport(const AFactory: TTgTransportFactory);
begin
  TgBot.Transport.TgRegisterDefaultTransport(AFactory);
end;

procedure TgUnregisterDefaultTransport(const AFactory: TTgTransportFactory);
begin
  TgBot.Transport.TgUnregisterDefaultTransport(AFactory);
end;

function TgDefaultTransportFactory: TTgTransportFactory;
begin
  Result := TgBot.Transport.TgDefaultTransportFactory();
end;

function TgCreateDefaultTransport(const ASettings: TTgHttpSettings): ITgTransport;
begin
  Result := TgBot.Transport.TgCreateDefaultTransport(ASettings);
end;

// TgRow — обычные обёртки: функцию с параметром «открытый массив» нельзя
// объявить inline (E2439).

function TgRow(const AButtons: array of ITgInlineKeyboardButton): TArray<ITgInlineKeyboardButton>;
begin
  Result := TgBot.Keyboards.TgRow(AButtons);
end;

function TgRow(const AButtons: array of ITgKeyboardButton): TArray<ITgKeyboardButton>;
begin
  Result := TgBot.Keyboards.TgRow(AButtons);
end;

end.
