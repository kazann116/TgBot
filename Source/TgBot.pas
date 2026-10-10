unit TgBot;

{
  TgBot 0.1.0 — библиотека Telegram Bot API 10.3 для Delphi (10.4 Sydney и новее;
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
  - сгенерированные типы и методы Bot API (Source\Generated\Gen.*.inc,
    TgBotGen по спецификации Bot API 10.3) — включаются относительно этого
    файла, дополнительный путь -I не нужен;
  - псевдонимы типов ядра (TgBot.Base, TgBot.Json, TgBot.Http, TgBot.Dto,
    TgBot.Core, TgBot.Updates, TgBot.State), чтобы пользователю не
    требовались другие модули в uses;
  - ручные удобства: построители клавиатур TTgKeyboard и TgRow;
  - TTgBot и контекст обработчика ITgContext.

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
  System.Classes,
  System.SyncObjs,
  System.JSON,
  System.Threading,
  TgBot.Base,
  TgBot.Json,
  TgBot.Http,
  TgBot.Dto,
  TgBot.Core,
  TgBot.Updates,
  TgBot.State;

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
  /// <summary>Наибольший размер тела webhook-запроса по умолчанию, байт (1 МБ).</summary>
  TgDefaultWebhookMaxBodySize = TgBot.Updates.TgDefaultWebhookMaxBodySize;
  /// <summary>Сколько HandleWebhook ждёт места в очереди по умолчанию, мс.</summary>
  TgDefaultWebhookPostTimeoutMs = TgBot.Updates.TgDefaultWebhookPostTimeoutMs;
  /// <summary>Окно дедупликации webhook по умолчанию (последних update_id).</summary>
  TgDefaultWebhookDedupWindow = TgBot.Updates.TgDefaultWebhookDedupWindow;
  /// <summary>Длина генерируемого секрета webhook.</summary>
  TgWebhookSecretLength = TgBot.Updates.TgWebhookSecretLength;
  /// <summary>Таймаут TTgBot.Stop по умолчанию, мс.</summary>
  TgDefaultBotStopTimeoutMs = 10000;

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
  /// <summary>Источник отмены: Cancel, связанные токены (Linked).</summary>
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
  /// <summary>Итог приёма webhook-запроса (Accepted, Forbidden, BadRequest, Unavailable).</summary>
  TTgWebhookResult = TgBot.Updates.TTgWebhookResult;
  /// <summary>Приём тела webhook-запроса из любого HTTP-сервера.</summary>
  ITgWebhookReceiver = TgBot.Updates.ITgWebhookReceiver;
  /// <summary>Webhook без собственного HTTP-сервера (setWebhook, Accept).</summary>
  TTgWebhookSource = TgBot.Updates.TTgWebhookSource;
  /// <summary>Диспетчер обновлений: порядок внутри чата, параллельность между чатами.</summary>
  TTgUpdateDispatcher = TgBot.Updates.TTgUpdateDispatcher;
  /// <summary>Сигнал завершения консольной программы (Ctrl+C, SIGTERM).</summary>
  TTgShutdownSignal = TgBot.Updates.TTgShutdownSignal;
  /// <summary>Хранилище состояния диалогов.</summary>
  ITgStateStorage = TgBot.State.ITgStateStorage;
  /// <summary>Хранилище состояния в памяти (по умолчанию).</summary>
  TTgMemoryStateStorage = TgBot.State.TTgMemoryStateStorage;

  { Сгенерированные типы Bot API }

{$I Generated\Gen.Forward.inc}
{$I Generated\Gen.Enums.inc}
{$I Generated\Gen.Unions.inc}
{$I Generated\Gen.Intf.inc}
{$I Generated\Gen.Factories.inc}
{$I Generated\Gen.Options.inc}

  { Построители клавиатур (ручной код) }

  /// <summary>
  ///   Построитель инлайн-клавиатуры: TTgKeyboard.Inline.Row.Button('Да', 'yes')
  ///   .Button('Нет', 'no').Row.Url('Сайт', 'https://…'). Запись-значение:
  ///   каждый вызов возвращает изменённую копию, исходная не меняется. Первая
  ///   кнопка без Row сама начинает строку; пустые строки не передаются.
  ///   Неявно приводится к ITgInlineKeyboardMarkup (edit-методы, поля ReplyMarkup
  ///   инлайн-типа) и к TTgReplyMarkup (send-методы); явно — Build и AsReplyMarkup.
  /// </summary>
  TTgInlineKeyboardBuilder = record
  private
    FRows: TArray<TArray<ITgInlineKeyboardButton>>;
  public
    /// <summary>Начинает новую строку кнопок.</summary>
    function Row: TTgInlineKeyboardBuilder;
    /// <summary>Добавляет готовую кнопку (стиль, иконка и т.п. — через With*) в текущую строку.</summary>
    function Add(const AButton: ITgInlineKeyboardButton): TTgInlineKeyboardBuilder;
    /// <summary>Кнопка с callback_data (1–64 байта): нажатие приходит как Update.CallbackQuery.</summary>
    function Button(const AText, ACallbackData: string): TTgInlineKeyboardBuilder;
    /// <summary>Кнопка-ссылка (http(s)://, tg://).</summary>
    function Url(const AText, AUrl: string): TTgInlineKeyboardBuilder;
    /// <summary>Кнопка Web App (только в личных чатах с ботом).</summary>
    function WebApp(const AText, AUrl: string): TTgInlineKeyboardBuilder;
    /// <summary>Кнопка авторизации на сайте (Telegram Login).</summary>
    function LoginUrl(const AText, AUrl: string): TTgInlineKeyboardBuilder;
    /// <summary>Выбор чата и inline-запрос к боту с текстом AQuery ('' — только имя бота).</summary>
    function SwitchInline(const AText: string; const AQuery: string = ''): TTgInlineKeyboardBuilder;
    /// <summary>Inline-запрос к боту в текущем чате.</summary>
    function SwitchInlineCurrentChat(const AText: string;
      const AQuery: string = ''): TTgInlineKeyboardBuilder;
    /// <summary>Кнопка копирования ACopyText в буфер обмена.</summary>
    function CopyText(const AText, ACopyText: string): TTgInlineKeyboardBuilder;
    /// <summary>Кнопка оплаты (первая кнопка первой строки для sendInvoice).</summary>
    function Pay(const AText: string): TTgInlineKeyboardBuilder;
    /// <summary>Кнопка запуска игры (первая кнопка первой строки для sendGame).</summary>
    function Game(const AText: string): TTgInlineKeyboardBuilder;
    /// <summary>Число непустых строк.</summary>
    function RowCount: Integer;
    /// <summary>Нет ни одной кнопки.</summary>
    function IsEmpty: Boolean;
    /// <summary>Новая разметка ITgInlineKeyboardMarkup из текущих кнопок.</summary>
    function Build: ITgInlineKeyboardMarkup;
    /// <summary>Разметка для параметра reply_markup send-методов.</summary>
    function AsReplyMarkup: TTgReplyMarkup;
    class operator Implicit(const ABuilder: TTgInlineKeyboardBuilder): ITgInlineKeyboardMarkup;
    class operator Implicit(const ABuilder: TTgInlineKeyboardBuilder): TTgReplyMarkup;
  end;

  /// <summary>
  ///   Построитель обычной клавиатуры: TTgKeyboard.Reply.Row.Text('Меню')
  ///   .RequestContact('Телефон').Resize.OneTime. Запись-значение, как
  ///   TTgInlineKeyboardBuilder. Неявно приводится к ITgReplyKeyboardMarkup
  ///   и TTgReplyMarkup.
  /// </summary>
  TTgReplyKeyboardBuilder = record
  private
    FRows: TArray<TArray<ITgKeyboardButton>>;
    FResize: Boolean;
    FOneTime: Boolean;
    FPersistent: Boolean;
    FSelective: Boolean;
    FPlaceholder: string;
  public
    /// <summary>Начинает новую строку кнопок.</summary>
    function Row: TTgReplyKeyboardBuilder;
    /// <summary>Добавляет готовую кнопку (RequestUsers, RequestChat и т.п.) в текущую строку.</summary>
    function Add(const AButton: ITgKeyboardButton): TTgReplyKeyboardBuilder;
    /// <summary>Текстовая кнопка: нажатие отправляет AText как сообщение.</summary>
    function Text(const AText: string): TTgReplyKeyboardBuilder;
    /// <summary>Кнопка отправки своего контакта (только в личных чатах).</summary>
    function RequestContact(const AText: string): TTgReplyKeyboardBuilder;
    /// <summary>Кнопка отправки своей геопозиции (только в личных чатах).</summary>
    function RequestLocation(const AText: string): TTgReplyKeyboardBuilder;
    /// <summary>Кнопка создания опроса; APollType — TTgPollType.Quiz/Regular или '' (любой).</summary>
    function RequestPoll(const AText: string; const APollType: string = ''): TTgReplyKeyboardBuilder;
    /// <summary>Кнопка Web App (только в личных чатах).</summary>
    function WebApp(const AText, AUrl: string): TTgReplyKeyboardBuilder;
    /// <summary>resize_keyboard: подогнать высоту клавиатуры под кнопки.</summary>
    function Resize(AValue: Boolean = True): TTgReplyKeyboardBuilder;
    /// <summary>one_time_keyboard: скрыть клавиатуру после нажатия.</summary>
    function OneTime(AValue: Boolean = True): TTgReplyKeyboardBuilder;
    /// <summary>is_persistent: не скрывать клавиатуру.</summary>
    function Persistent(AValue: Boolean = True): TTgReplyKeyboardBuilder;
    /// <summary>selective: только упомянутым пользователям или автору исходного сообщения.</summary>
    function Selective(AValue: Boolean = True): TTgReplyKeyboardBuilder;
    /// <summary>input_field_placeholder: подсказка в поле ввода (1–64 символа).</summary>
    function Placeholder(const AText: string): TTgReplyKeyboardBuilder;
    /// <summary>Число непустых строк.</summary>
    function RowCount: Integer;
    /// <summary>Нет ни одной кнопки.</summary>
    function IsEmpty: Boolean;
    /// <summary>Новая разметка ITgReplyKeyboardMarkup из текущих кнопок и флагов.</summary>
    function Build: ITgReplyKeyboardMarkup;
    /// <summary>Разметка для параметра reply_markup send-методов.</summary>
    function AsReplyMarkup: TTgReplyMarkup;
    class operator Implicit(const ABuilder: TTgReplyKeyboardBuilder): ITgReplyKeyboardMarkup;
    class operator Implicit(const ABuilder: TTgReplyKeyboardBuilder): TTgReplyMarkup;
  end;

  /// <summary>
  ///   Точка входа построителей клавиатур:
  ///   <code>
  ///     LApi.SendMessage(LChatId, 'Выберите:',
  ///       TTgKeyboard.Inline.Row.Button('Да', 'yes').Button('Нет', 'no'));
  ///     LApi.SendMessage(LChatId, 'Меню', TTgKeyboard.Reply.Row.Text('Помощь').Resize);
  ///     LApi.SendMessage(LChatId, 'Готово', TTgKeyboard.Remove);
  ///   </code>
  /// </summary>
  TTgKeyboard = record
  public
    /// <summary>Пустая инлайн-клавиатура (кнопки под сообщением).</summary>
    class function &Inline: TTgInlineKeyboardBuilder; static;
    /// <summary>Пустая обычная клавиатура (вместо клавиатуры устройства).</summary>
    class function Reply: TTgReplyKeyboardBuilder; static;
    /// <summary>Убрать обычную клавиатуру (ReplyKeyboardRemove).</summary>
    class function Remove(ASelective: Boolean = False): ITgReplyKeyboardRemove; static;
    /// <summary>Принудительный ответ на сообщение (ForceReply) с подсказкой APlaceholder.</summary>
    class function ForceReply(const APlaceholder: string = '';
      ASelective: Boolean = False): ITgForceReply; static;
  end;

  /// <summary>
  ///   Клиент Telegram Bot API. Для каждого метода: синхронный вызов
  ///   (исключение при ошибке), Try* (False и TTgErrorInfo), *Async (колбэки
  ///   в рабочем потоке). Потокобезопасен. Не уничтожайте объект из колбэка Async.
  /// </summary>
  TTgApi = class(TTgApiCore)
{$I Generated\Gen.Methods.inc}
  end;

  /// <summary>
  ///   Контекст обработки одного обновления (TTgBot.OnUpdate/OnMessage/
  ///   OnCallbackQuery). Используйте только внутри обработчика и в его потоке.
  ///
  ///   Сообщение обновления (Message) — message, edited_message, channel_post,
  ///   edited_channel_post, business_message, edited_business_message,
  ///   guest_message или message из callback_query (если доступно).
  ///   Text — текст (или подпись) этого сообщения; для callback_query —
  ///   callback data (то же, что Data); для inline_query и
  ///   chosen_inline_result — query; иначе ''. Data — только callback data.
  ///
  ///   Вызовы Api внутри обработчика прерываются при остановке бота (Cancel —
  ///   окружающий токен обработчика).
  /// </summary>
  ITgContext = interface
    ['{49678079-CCCC-45F5-A4ED-8064A44C34EA}']
    function GetUpdate: ITgUpdate;
    function GetRaw: ITgRawUpdate;
    function GetKind: string;
    function GetApi: TTgApi;
    function GetCancel: ITgCancellation;
    function GetChatId: TTgChatId;
    function GetFrom: ITgUser;
    function GetMessage: ITgMessage;
    function GetText: string;
    function GetData: string;
    function GetStateKey: string;
    function GetState(const AName: string): string;
    procedure SetState(const AName, AValue: string);
    /// <summary>
    ///   Отправляет сообщение в чат обновления (в той же теме форума и том же
    ///   бизнес-подключении). Нет чата — ETgError.
    /// </summary>
    function Reply(const AText: string): ITgMessage; overload;
    /// <summary>Reply с клавиатурой (TTgKeyboard.Inline/Reply/Remove/ForceReply).</summary>
    function Reply(const AText: string; const AKeyboard: TTgReplyMarkup): ITgMessage; overload;
    /// <summary>Reply с parse_mode = HTML.</summary>
    function ReplyHtml(const AText: string): ITgMessage; overload;
    /// <summary>ReplyHtml с клавиатурой.</summary>
    function ReplyHtml(const AText: string; const AKeyboard: TTgReplyMarkup): ITgMessage; overload;
    /// <summary>
    ///   answerCallbackQuery для callback_query (AText — уведомление, AShowAlert —
    ///   окном). Обновление другого вида — False без запроса.
    /// </summary>
    function Answer(const AText: string = ''; AShowAlert: Boolean = False): Boolean;
    /// <summary>
    ///   Меняет текст сообщения с нажатой кнопкой (callback_query): обычное
    ///   сообщение — editMessageText(chat_id, message_id), inline —
    ///   editMessageText(inline_message_id). Не callback_query или нет
    ///   сообщения — False без запроса; ответ 400 «message is not modified»
    ///   (текст и клавиатура не изменились, например повторное нажатие) —
    ///   False без исключения; другая ошибка Bot API — исключение.
    ///   Без AKeyboard инлайн-клавиатура сообщения убирается (так Bot API
    ///   обрабатывает отсутствие reply_markup).
    /// </summary>
    function Edit(const AText: string): Boolean; overload;
    /// <summary>Edit с новой инлайн-клавиатурой (nil — клавиатура убирается).</summary>
    function Edit(const AText: string; const AKeyboard: ITgInlineKeyboardMarkup): Boolean; overload;
    /// <summary>Удаляет все значения состояния StateKey.</summary>
    procedure ClearState;
    function GetCommand: string;
    function GetArgs: string;
    function GetHandled: Boolean;
    procedure SetHandled(AValue: Boolean);
    /// <summary>
    ///   Команда сообщения без '/' и '@бот', в нижнем регистре ('/Start@MyBot a'
    ///   → 'start'); '' — не команда или команда другому боту. Заполняется до
    ///   OnUpdate.
    /// </summary>
    property Command: string read GetCommand;
    /// <summary>
    ///   Аргументы сработавшего правила: текст после команды (без крайних
    ///   пробелов), первая группа TextMatch (нет групп — всё совпадение),
    ///   остаток callback data после префикса CallbackPrefix; иначе ''.
    /// </summary>
    property Args: string read GetArgs;
    /// <summary>
    ///   Обновление обработано: дальнейшие правила, OnMessage и OnCallbackQuery
    ///   не вызываются. OnUpdate может выставить True (перехват); правило
    ///   маршрутизатора выставляет True перед вызовом своего обработчика —
    ///   обработчик может сбросить в False, чтобы обработка шла дальше.
    /// </summary>
    property Handled: Boolean read GetHandled write SetHandled;
    /// <summary>Обновление (типизированное; разделяет JSON с Raw).</summary>
    property Update: ITgUpdate read GetUpdate;
    /// <summary>Обновление в сыром виде.</summary>
    property Raw: ITgRawUpdate read GetRaw;
    /// <summary>Вид обновления (TTgUpdateType.*).</summary>
    property Kind: string read GetKind;
    /// <summary>Клиент Bot API бота.</summary>
    property Api: TTgApi read GetApi;
    /// <summary>Токен отмены обработчика (отменяется при остановке бота).</summary>
    property Cancel: ITgCancellation read GetCancel;
    /// <summary>Чат обновления; пусто (IsEmpty), если чата нет (inline_query и т.п.).</summary>
    property ChatId: TTgChatId read GetChatId;
    /// <summary>Автор: from (или user) полезной нагрузки; nil, если нет (посты каналов).</summary>
    property From: ITgUser read GetFrom;
    /// <summary>Сообщение обновления или nil (см. описание интерфейса).</summary>
    property Message: ITgMessage read GetMessage;
    /// <summary>Текст (см. описание интерфейса).</summary>
    property Text: string read GetText;
    /// <summary>callback data (только callback_query), иначе ''.</summary>
    property Data: string read GetData;
    /// <summary>Ключ состояния 'чат:пользователь' (пустая часть, если её нет).</summary>
    property StateKey: string read GetStateKey;
    /// <summary>
    ///   Значение состояния диалога (ключ StateKey); '' — нет значения.
    ///   Присваивание '' удаляет значение.
    /// </summary>
    property State[const AName: string]: string read GetState write SetState;
  end;

  /// <summary>
  ///   Состояние бота (TTgBot.State).
  ///   Idle — не запущен (до Start, после Stop);
  ///   Running — приём и обработка идут;
  ///   Stopping — выполняется Stop (дренаж, итоговое подтверждение);
  ///   Faulted — приём остановлен неустранимой ошибкой (401, 404, 409
  ///   «webhook is active» без AutoDeleteWebhook…): уже принятые обновления
  ///   дорабатываются, ресурсы держатся до Stop, Start или Free.
  /// </summary>
  TTgBotState = (Idle, Running, Stopping, Faulted);

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
    // Внутреннее ядро (TTgBotCore) и ссылка, удерживающая его. Ядро владеет
    // клиентом, хранилищем и обработчиками; FApi — его клиент (не во владении).
    FCore: TObject;
    FCoreRef: IInterface;
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
    FAllowedUpdates: TTgOptionalStrings;
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
    property AllowedUpdates: TTgOptionalStrings read FAllowedUpdates write FAllowedUpdates;
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

/// <summary>
///   Общий пул потоков Async-вызовов библиотеки (см. TgBot.Core.TgBotThreadPool).
/// </summary>
function TgBotThreadPool: TThreadPool;
/// <summary>HTTP-код ответа на webhook-запрос по итогу HandleWebhook: 200, 403, 400 или 503.</summary>
function TgWebhookHttpStatus(AResult: TTgWebhookResult): Integer;
/// <summary>Максимум рабочих потоков общего пула библиотеки (не меньше 1).</summary>
procedure TgSetAsyncPoolSize(AMaxThreads: Integer);

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

uses
  System.RTLConsts,
  System.Diagnostics,
  System.Math,
  System.RegularExpressions;

resourcestring
  SRuRouteEmptyKey = 'Пустой ключ правила маршрутизатора (%s)';
  SEnRouteEmptyKey = 'Empty router rule key (%s)';
  SRuRouteBadCommand = 'Недопустимое имя команды "%s": пробелы и "@" не допускаются';
  SEnRouteBadCommand = 'Invalid command name "%s": spaces and "@" are not allowed';
  SRuWebhookNotHttps = 'Режим Webhook: WebhookUrl должен начинаться с https:// ' +
    '(Telegram принимает только HTTPS; http:// — только с Local Bot API server)';
  SEnWebhookNotHttps = 'Webhook mode: WebhookUrl must start with https:// ' +
    '(Telegram accepts HTTPS only; http:// is allowed only with a Local Bot API server)';

type
  TTgRouterText = (EmptyKey, BadCommand);
  /// <summary>Прочие тексты модуля.</summary>
  TTgBotText = (WebhookNotHttps);

const
  CRouterTexts: array[TTgRouterText, TTgLanguage] of PResStringRec = (
    (@SRuRouteEmptyKey, @SEnRouteEmptyKey),
    (@SRuRouteBadCommand, @SEnRouteBadCommand)
  );
  CBotTexts: array[TTgBotText, TTgLanguage] of PResStringRec = (
    (@SRuWebhookNotHttps, @SEnWebhookNotHttps)
  );

function TgRouterText(AText: TTgRouterText): string;
begin
  Result := LoadResString(CRouterTexts[AText, TgBot.Base.TgGetLanguage]);
end;

function TgBotText(AText: TTgBotText): string;
begin
  Result := LoadResString(CBotTexts[AText, TgBot.Base.TgGetLanguage]);
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

{$I Generated\Gen.ImplClasses.inc}
{$I Generated\Gen.ImplMake.inc}
{$I Generated\Gen.ImplTypes.inc}
{$I Generated\Gen.ImplMethods.inc}

{ Построители клавиатур }

function TgRow(const AButtons: array of ITgInlineKeyboardButton): TArray<ITgInlineKeyboardButton>;
begin
  Result := TTgDto.CopyArray<ITgInlineKeyboardButton>(AButtons);
end;

function TgRow(const AButtons: array of ITgKeyboardButton): TArray<ITgKeyboardButton>;
begin
  Result := TTgDto.CopyArray<ITgKeyboardButton>(AButtons);
end;

{ TTgInlineKeyboardBuilder }

function TTgInlineKeyboardBuilder.Row: TTgInlineKeyboardBuilder;
begin
  // Копия внешнего массива: изменения не видны прежним копиям записи.
  Result := Self;
  Result.FRows := Copy(FRows);
  SetLength(Result.FRows, Length(Result.FRows) + 1);
end;

function TTgInlineKeyboardBuilder.Add(const AButton: ITgInlineKeyboardButton): TTgInlineKeyboardBuilder;
var
  LLast: Integer;
begin
  if not Assigned(AButton) then
    raise EArgumentNilException.CreateRes(@SArgumentNil);
  Result := Self;
  Result.FRows := Copy(FRows);
  if Length(Result.FRows) = 0 then
    SetLength(Result.FRows, 1);
  LLast := High(Result.FRows);
  // «+» создаёт новый массив строки — прежняя строка не меняется.
  Result.FRows[LLast] := Result.FRows[LLast] + [AButton];
end;

function TTgInlineKeyboardBuilder.Button(const AText, ACallbackData: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText).WithCallbackData(ACallbackData));
end;

function TTgInlineKeyboardBuilder.Url(const AText, AUrl: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText).WithUrl(AUrl));
end;

function TTgInlineKeyboardBuilder.WebApp(const AText, AUrl: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText).WithWebApp(TTgWebAppInfo.Create(AUrl)));
end;

function TTgInlineKeyboardBuilder.LoginUrl(const AText, AUrl: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText).WithLoginUrl(TTgLoginUrl.Create(AUrl)));
end;

function TTgInlineKeyboardBuilder.SwitchInline(const AText, AQuery: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText).WithSwitchInlineQuery(AQuery));
end;

function TTgInlineKeyboardBuilder.SwitchInlineCurrentChat(const AText,
  AQuery: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText).WithSwitchInlineQueryCurrentChat(AQuery));
end;

function TTgInlineKeyboardBuilder.CopyText(const AText, ACopyText: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText)
    .WithCopyText(TTgCopyTextButton.Create(ACopyText)));
end;

function TTgInlineKeyboardBuilder.Pay(const AText: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText).WithPay(True));
end;

function TTgInlineKeyboardBuilder.Game(const AText: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText).WithCallbackGame(TTgCallbackGame.Create));
end;

function TTgInlineKeyboardBuilder.RowCount: Integer;
var
  LRow: TArray<ITgInlineKeyboardButton>;
begin
  Result := 0;
  for LRow in FRows do
    if Length(LRow) > 0 then
      Inc(Result);
end;

function TTgInlineKeyboardBuilder.IsEmpty: Boolean;
begin
  Result := RowCount = 0;
end;

function TTgInlineKeyboardBuilder.Build: ITgInlineKeyboardMarkup;
var
  LRows: TArray<TArray<ITgInlineKeyboardButton>>;
  LRow: TArray<ITgInlineKeyboardButton>;
begin
  LRows := nil;
  for LRow in FRows do
    if Length(LRow) > 0 then
      LRows := LRows + [LRow];
  Result := TTgInlineKeyboardMarkup.Create(LRows);
end;

function TTgInlineKeyboardBuilder.AsReplyMarkup: TTgReplyMarkup;
begin
  Result := Build;
end;

class operator TTgInlineKeyboardBuilder.Implicit(
  const ABuilder: TTgInlineKeyboardBuilder): ITgInlineKeyboardMarkup;
begin
  Result := ABuilder.Build;
end;

class operator TTgInlineKeyboardBuilder.Implicit(const ABuilder: TTgInlineKeyboardBuilder): TTgReplyMarkup;
begin
  Result := ABuilder.Build;
end;

{ TTgReplyKeyboardBuilder }

function TTgReplyKeyboardBuilder.Row: TTgReplyKeyboardBuilder;
begin
  Result := Self;
  Result.FRows := Copy(FRows);
  SetLength(Result.FRows, Length(Result.FRows) + 1);
end;

function TTgReplyKeyboardBuilder.Add(const AButton: ITgKeyboardButton): TTgReplyKeyboardBuilder;
var
  LLast: Integer;
begin
  if not Assigned(AButton) then
    raise EArgumentNilException.CreateRes(@SArgumentNil);
  Result := Self;
  Result.FRows := Copy(FRows);
  if Length(Result.FRows) = 0 then
    SetLength(Result.FRows, 1);
  LLast := High(Result.FRows);
  Result.FRows[LLast] := Result.FRows[LLast] + [AButton];
end;

function TTgReplyKeyboardBuilder.Text(const AText: string): TTgReplyKeyboardBuilder;
begin
  Result := Add(TTgKeyboardButton.Create(AText));
end;

function TTgReplyKeyboardBuilder.RequestContact(const AText: string): TTgReplyKeyboardBuilder;
begin
  Result := Add(TTgKeyboardButton.Create(AText).WithRequestContact(True));
end;

function TTgReplyKeyboardBuilder.RequestLocation(const AText: string): TTgReplyKeyboardBuilder;
begin
  Result := Add(TTgKeyboardButton.Create(AText).WithRequestLocation(True));
end;

function TTgReplyKeyboardBuilder.RequestPoll(const AText, APollType: string): TTgReplyKeyboardBuilder;
var
  LPollType: ITgKeyboardButtonPollType;
begin
  LPollType := TTgKeyboardButtonPollType.Create;
  if APollType <> '' then
    LPollType.WithKeyboardButtonPollTypeType(APollType);
  Result := Add(TTgKeyboardButton.Create(AText).WithRequestPoll(LPollType));
end;

function TTgReplyKeyboardBuilder.WebApp(const AText, AUrl: string): TTgReplyKeyboardBuilder;
begin
  Result := Add(TTgKeyboardButton.Create(AText).WithWebApp(TTgWebAppInfo.Create(AUrl)));
end;

function TTgReplyKeyboardBuilder.Resize(AValue: Boolean): TTgReplyKeyboardBuilder;
begin
  Result := Self;
  Result.FResize := AValue;
end;

function TTgReplyKeyboardBuilder.OneTime(AValue: Boolean): TTgReplyKeyboardBuilder;
begin
  Result := Self;
  Result.FOneTime := AValue;
end;

function TTgReplyKeyboardBuilder.Persistent(AValue: Boolean): TTgReplyKeyboardBuilder;
begin
  Result := Self;
  Result.FPersistent := AValue;
end;

function TTgReplyKeyboardBuilder.Selective(AValue: Boolean): TTgReplyKeyboardBuilder;
begin
  Result := Self;
  Result.FSelective := AValue;
end;

function TTgReplyKeyboardBuilder.Placeholder(const AText: string): TTgReplyKeyboardBuilder;
begin
  Result := Self;
  Result.FPlaceholder := AText;
end;

function TTgReplyKeyboardBuilder.RowCount: Integer;
var
  LRow: TArray<ITgKeyboardButton>;
begin
  Result := 0;
  for LRow in FRows do
    if Length(LRow) > 0 then
      Inc(Result);
end;

function TTgReplyKeyboardBuilder.IsEmpty: Boolean;
begin
  Result := RowCount = 0;
end;

function TTgReplyKeyboardBuilder.Build: ITgReplyKeyboardMarkup;
var
  LRows: TArray<TArray<ITgKeyboardButton>>;
  LRow: TArray<ITgKeyboardButton>;
begin
  LRows := nil;
  for LRow in FRows do
    if Length(LRow) > 0 then
      LRows := LRows + [LRow];
  Result := TTgReplyKeyboardMarkup.Create(LRows);
  // Флаги передаются, только если включены (false — значение Bot API по умолчанию).
  if FResize then
    Result.WithResizeKeyboard(True);
  if FOneTime then
    Result.WithOneTimeKeyboard(True);
  if FPersistent then
    Result.WithIsPersistent(True);
  if FSelective then
    Result.WithSelective(True);
  if FPlaceholder <> '' then
    Result.WithInputFieldPlaceholder(FPlaceholder);
end;

function TTgReplyKeyboardBuilder.AsReplyMarkup: TTgReplyMarkup;
begin
  Result := Build;
end;

class operator TTgReplyKeyboardBuilder.Implicit(const ABuilder: TTgReplyKeyboardBuilder): ITgReplyKeyboardMarkup;
begin
  Result := ABuilder.Build;
end;

class operator TTgReplyKeyboardBuilder.Implicit(const ABuilder: TTgReplyKeyboardBuilder): TTgReplyMarkup;
begin
  Result := ABuilder.Build;
end;

{ TTgKeyboard }

class function TTgKeyboard.&Inline: TTgInlineKeyboardBuilder;
begin
  Result := Default(TTgInlineKeyboardBuilder);
end;

class function TTgKeyboard.Reply: TTgReplyKeyboardBuilder;
begin
  Result := Default(TTgReplyKeyboardBuilder);
end;

class function TTgKeyboard.Remove(ASelective: Boolean): ITgReplyKeyboardRemove;
begin
  Result := TTgReplyKeyboardRemove.Create;
  if ASelective then
    Result.WithSelective(True);
end;

class function TTgKeyboard.ForceReply(const APlaceholder: string; ASelective: Boolean): ITgForceReply;
begin
  Result := TTgForceReply.Create;
  if APlaceholder <> '' then
    Result.WithInputFieldPlaceholder(APlaceholder);
  if ASelective then
    Result.WithSelective(True);
end;

{ Контекст обработчика }

type
  /// <summary>
  ///   Реализация ITgContext. Поля читаются из сырого JSON обновления;
  ///   типизированные объекты (Update, From, Message) разделяют этот JSON и
  ///   удерживают обновление. Контекст удерживает ядро бота (FCoreRef):
  ///   клиент FApi действителен, пока жив контекст, даже после Free бота.
  /// </summary>
  TTgContext = class(TInterfacedObject, ITgContext)
  private
    FCoreRef: IInterface;
    FApi: TTgApi;
    FRaw: ITgRawUpdate;
    FCancel: ITgCancellation;
    FStorage: ITgStateStorage;
    FPayload: TJSONObject;
    FUpdate: ITgUpdate;
    FAnswered: Boolean;
    // Маршрутизатор (заполняет ядро в потоке обработчика).
    FCommand: string;
    FArgs: string;
    FHandled: Boolean;
    function IsCallback: Boolean;
    function MessageJson: TJSONObject;
    function ChatJson: TJSONObject;
    function UserJson: TJSONObject;
    function SendText(const AText, AParseMode: string; const AKeyboard: TTgReplyMarkup): ITgMessage;
    function EditText(const AText: string; const AKeyboard: ITgInlineKeyboardMarkup): Boolean;
  public
    /// <summary>ACore — ссылка на ядро, владеющее AApi (удерживается контекстом).</summary>
    constructor Create(const ACore: IInterface; AApi: TTgApi; const ARaw: ITgRawUpdate;
      const ACancel: ITgCancellation; const AStorage: ITgStateStorage);
    function GetUpdate: ITgUpdate;
    function GetRaw: ITgRawUpdate;
    function GetKind: string;
    function GetApi: TTgApi;
    function GetCancel: ITgCancellation;
    function GetChatId: TTgChatId;
    function GetFrom: ITgUser;
    function GetMessage: ITgMessage;
    function GetText: string;
    function GetData: string;
    function GetStateKey: string;
    function GetState(const AName: string): string;
    procedure SetState(const AName, AValue: string);
    function Reply(const AText: string): ITgMessage; overload;
    function Reply(const AText: string; const AKeyboard: TTgReplyMarkup): ITgMessage; overload;
    function ReplyHtml(const AText: string): ITgMessage; overload;
    function ReplyHtml(const AText: string; const AKeyboard: TTgReplyMarkup): ITgMessage; overload;
    function Answer(const AText: string = ''; AShowAlert: Boolean = False): Boolean;
    function Edit(const AText: string): Boolean; overload;
    function Edit(const AText: string; const AKeyboard: ITgInlineKeyboardMarkup): Boolean; overload;
    procedure ClearState;
    function GetCommand: string;
    function GetArgs: string;
    function GetHandled: Boolean;
    procedure SetHandled(AValue: Boolean);
    /// <summary>Поле text сообщения вида message ('' — нет текста или другой вид).</summary>
    function MessageText: string;
    /// <summary>Вызван Answer (для автоматического ответа на callback_query).</summary>
    property Answered: Boolean read FAnswered;
  end;

  /// <summary>Вид правила маршрутизатора с ключом.</summary>
  TTgRouteKind = (Command, Callback, CallbackPrefix, Text);

  /// <summary>
  ///   Правило: ключ (имя команды в нижнем регистре, callback data, префикс,
  ///   текст в нижнем регистре), описание (только команды, для меню) и
  ///   обработчик.
  /// </summary>
  TTgRoute = record
    Key: string;
    Description: string;
    Handler: TProc<ITgContext>;
  end;

  /// <summary>Регулярное выражение правила TextMatch (потокобезопасный поиск).</summary>
  ITgTextMatcher = interface
    ['{0E5C1B7A-8F42-4D6B-9C3E-7A1D2B4F6E58}']
    function GetPattern: string;
    /// <summary>Найдено совпадение; AArgs — первая группа или всё совпадение.</summary>
    function TryMatch(const AText: string; out AArgs: string): Boolean;
    property Pattern: string read GetPattern;
  end;

  /// <summary>
  ///   TRegEx не потокобезопасен (Match меняет Subject общего TPerlRegEx,
  ///   группы TMatch читаются лениво из него же): поиск — под блокировкой.
  ///   Шаблон компилируется один раз, в конструкторе (ошибка — исключение).
  /// </summary>
  TTgTextMatcher = class(TInterfacedObject, ITgTextMatcher)
  private
    FLock: TCriticalSection;
    FPattern: string;
    FRegEx: TRegEx;
    function DoMatch(const AText: string; out AArgs: string): Boolean;
  public
    constructor Create(const APattern: string);
    destructor Destroy; override;
    function GetPattern: string;
    function TryMatch(const AText: string; out AArgs: string): Boolean;
  end;

  /// <summary>Правило TextMatch.</summary>
  TTgMatchRoute = record
    Matcher: ITgTextMatcher;
    Handler: TProc<ITgContext>;
  end;

  /// <summary>
  ///   Таблица правил — снимок: массивы не меняются на месте (изменение
  ///   создаёт копию под блокировкой ядра), поэтому копия записи, сделанная
  ///   под блокировкой, безопасна для чтения в любом потоке.
  /// </summary>
  TTgRoutes = record
    Lists: array[TTgRouteKind] of TArray<TTgRoute>;
    Matches: TArray<TTgMatchRoute>;
    AnyText: TProc<ITgContext>;
    UnknownCommand: TProc<ITgContext>;
  end;

  /// <summary>
  ///   Служебное: точки входа ядра бота для замыканий диспетчера и
  ///   источника (они захватывают интерфейс ядра, а не TTgBot).
  /// </summary>
  /// <summary>
  ///   Фоновая подготовка запуска (getMe и setMyCommands в TgBotThreadPool):
  ///   Start не ждёт сеть. Done выставляется по завершении задачи; CancelSource
  ///   отменяет её запросы (Stop по истечении ожидания, Free бота — через
  ///   отмену клиента, с которой токен связан).
  /// </summary>
  TTgStartJob = class(TInterfacedObject)
  private
    FDone: TEvent;
    // getMe завершён (успешно или нет) — до вызова OnError задачи: обработчик
    // '/cmd@бот' в главном потоке не ждёт OnError с TThread.Synchronize.
    FNameDone: TEvent;
    FCancelSource: TTgCancellationSource;
    FCancel: ITgCancellation;
  public
    constructor Create(const AParent: ITgCancellation);
    destructor Destroy; override;
    /// <summary>
    ///   Ждёт завершения не дольше AMs; APump (только главный поток) —
    ///   ожидание с CheckSynchronize, чтобы TThread.Synchronize в OnError
    ///   задачи не зависал.
    /// </summary>
    function WaitDone(AMs: Cardinal; APump: Boolean): Boolean;
    property Done: TEvent read FDone;
    property NameDone: TEvent read FNameDone;
    property CancelSource: TTgCancellationSource read FCancelSource;
    property Cancel: ITgCancellation read FCancel;
  end;

  ITgBotCore = interface
    ['{6B0C2E4A-3D51-4F8E-9A7B-2C1D5E8F9A30}']
    procedure HandleRaw(const AUpdate: ITgRawUpdate);
    procedure NotifyError(AError: Exception; const AContext: ITgContext);
    procedure NotifyConflict(AError: ETgConflictError);
    procedure NotifyFault(AError: Exception; AGeneration: Integer);
    /// <summary>setWebhook выполнен успешно (поток webhook-источника).</summary>
    procedure NotifyWebhookRegistered;
  end;

  /// <summary>
  ///   Транспорт webhook-источника: пропускает вызовы во внутренний
  ///   транспорт клиента и после успешного setWebhook сообщает ядру
  ///   (OnWebhookRegistered). Удерживает ядро; ядро его не удерживает.
  /// </summary>
  TTgWebhookNotifyTransport = class(TInterfacedObject, ITgTransport)
  protected
    FInner: ITgTransport;
    FCore: ITgBotCore;
    /// <summary>После успешного вызова AMethod.</summary>
    procedure AfterCall(const AMethod: string);
  public
    constructor Create(const AInner: ITgTransport; const ACore: ITgBotCore);
    function Execute(const AMethod: string; AParams: TTgParams): TJSONValue;
    procedure DownloadFile(const AFilePath: string; ADest: TStream);
    procedure Cancel;
    procedure ResetCancel;
    function IsCancelled: Boolean;
  end;

  /// <summary>То же для транспорта с токенами отмены (ITgCancellableTransport).</summary>
  TTgWebhookNotifyCancellableTransport = class(TTgWebhookNotifyTransport, ITgCancellableTransport)
  public
    function ExecuteEx(const AMethod: string; AParams: TTgParams;
      const ACancel: ITgCancellation): TJSONValue;
    procedure DownloadFileEx(const AFilePath: string; ADest: TStream;
      const ACancel: ITgCancellation);
  end;

  /// <summary>
  ///   Ядро TTgBot со счётчиком ссылок: владеет клиентом (TTgApi),
  ///   хранилищем состояния, обработчиками и AutoAnswerCallbacks.
  ///   Держат его TTgBot, замыкания диспетчера/источника и каждый
  ///   TTgContext; само ядро ни на кого из них не ссылается (нет циклов).
  ///   Поля под FLock; обработчики вызываются со снимка вне блокировки.
  ///   После Detach (Free бота) обработчики сброшены, OnError, OnFault и
  ///   автоответ не вызываются, клиент закрыт (вызовы — ETgCancelledError);
  ///   клиент освобождается с последней ссылкой на ядро.
  /// </summary>
  TTgBotCore = class(TInterfacedObject, ITgBotCore)
  private
    FLock: TCriticalSection;
    FApi: TTgApi;
    FDetached: Boolean;
    FStateStorage: ITgStateStorage;
    FAutoAnswerCallbacks: Boolean;
    FOnUpdate: TProc<ITgContext>;
    FOnMessage: TProc<ITgContext>;
    FOnCallbackQuery: TProc<ITgContext>;
    FOnError: TProc<Exception, ITgContext>;
    FOnConflict: TProc<ETgConflictError>;
    FOnFault: TProc<Exception>;
    FOnWebhookRegistered: TProc;
    FState: TTgBotState;
    // Номер запуска: отказ от источника прежнего запуска игнорируется.
    FGeneration: Integer;
    FRoutes: TTgRoutes;
    FBotUserName: string;
    // Фоновая подготовка текущего запуска (nil — нет); FStartJobRef удерживает.
    FStartJob: TTgStartJob;
    FStartJobRef: IInterface;
    function GetDetached: Boolean;
    /// <summary>
    ///   username бота; '' — ждёт фоновую подготовку запуска (её getMe), затем
    ///   при необходимости запрашивает getMe (без исключений) и кэширует.
    ///   ACancel — токен обработчика: его отмена прерывает ожидание.
    /// </summary>
    function ResolveBotUserName(const ACancel: ITgCancellation): string;
    /// <summary>Снимок текущей задачи подготовки (AJobRef удерживает её).</summary>
    function CurrentStartJob(out AJobRef: IInterface): TTgStartJob;
    /// <summary>Тело задачи подготовки (поток пула): getMe, затем меню AMenu.</summary>
    procedure RunStartJob(AJob: TTgStartJob; const AMenu: TArray<ITgBotCommand>);
    /// <summary>
    ///   Задача подготовки ещё актуальна: не отменена, бот не отсоединён и
    ///   не Faulted. После отказа задача не шлёт новых запросов и не
    ///   сообщает ошибки.
    /// </summary>
    function StartJobActive(AJob: TTgStartJob): Boolean;
    /// <summary>
    ///   Разбор команды сообщения в AContext.FCommand/FArgs (только команда
    ///   этому боту: без '@' или '@' + BotUserName); результат — сообщение
    ///   является такой командой.
    /// </summary>
    function ParseCommand(AContext: TTgContext): Boolean;
    /// <summary>Правила message (итог — AContext.Handled).</summary>
    procedure RouteMessage(AContext: TTgContext; const ARoutes: TTgRoutes; AIsCommand: Boolean);
    /// <summary>Правила callback_query.</summary>
    procedure RouteCallback(AContext: TTgContext; const ARoutes: TTgRoutes);
  public
    /// <summary>AApi переходит во владение ядра (в т.ч. при исключении).</summary>
    constructor Create(AApi: TTgApi);
    destructor Destroy; override;
    procedure HandleRaw(const AUpdate: ITgRawUpdate);
    procedure NotifyError(AError: Exception; const AContext: ITgContext);
    procedure NotifyConflict(AError: ETgConflictError);
    /// <summary>
    ///   Отказ источника запуска AGeneration: Running → Faulted, затем
    ///   OnError(E, nil) и OnFault(E) (снимки под блокировкой). Не в Running,
    ///   чужой запуск или после Detach — ничего.
    /// </summary>
    procedure NotifyFault(AError: Exception; AGeneration: Integer);
    /// <summary>OnWebhookRegistered (снимок под блокировкой), только в Running и до Detach.</summary>
    procedure NotifyWebhookRegistered;
    function GetOnWebhookRegistered: TProc;
    procedure SetOnWebhookRegistered(const AValue: TProc);
    /// <summary>Новый запуск: State := Running; результат — его номер.</summary>
    function BeginRun: Integer;
    function GetState: TTgBotState;
    procedure SetState(AValue: TTgBotState);
    function GetOnFault: TProc<Exception>;
    procedure SetOnFault(const AValue: TProc<Exception>);
    /// <summary>
    ///   Отсоединение от бота (идемпотентно, не блокирует): FDetached,
    ///   сброс обработчиков, Api.Shutdown.
    /// </summary>
    procedure Detach;
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
    /// <summary>
    ///   Добавляет, заменяет (тот же ключ) или удаляет (AHandler = nil)
    ///   правило. Ключ уже нормализован вызывающим.
    /// </summary>
    procedure SetRoute(AKind: TTgRouteKind; const AKey, ADescription: string;
      const AHandler: TProc<ITgContext>);
    /// <summary>TextMatch: тот же шаблон заменяется, AHandler = nil — удаляется.</summary>
    procedure SetMatchRoute(const AMatcher: ITgTextMatcher; const AHandler: TProc<ITgContext>);
    procedure SetAnyText(const AValue: TProc<ITgContext>);
    function GetOnUnknownCommand: TProc<ITgContext>;
    procedure SetOnUnknownCommand(const AValue: TProc<ITgContext>);
    /// <summary>Снимок правил (под блокировкой).</summary>
    function GetRoutes: TTgRoutes;
    function GetBotUserName: string;
    procedure SetBotUserName(const AValue: string);
    /// <summary>
    ///   Запускает фоновую подготовку запуска, если есть команды или
    ///   OnUnknownCommand: getMe (если username ещё не получен) и при
    ///   ASetMyCommands — setMyCommands с командами, имеющими описание.
    /// </summary>
    procedure BeginStartJob(ASetMyCommands: Boolean);
    /// <summary>
    ///   Ждёт фоновую подготовку не дольше AWaitMs, затем отменяет её и ждёт
    ///   ещё ≈100 мс. False — задача не завершилась (отпущена).
    /// </summary>
    function FinishStartJob(AWaitMs: Cardinal): Boolean;
    /// <summary>Клиент Bot API (во владении ядра).</summary>
    property Api: TTgApi read FApi;
    /// <summary>Ядро отсоединено (бот уничтожен).</summary>
    property Detached: Boolean read GetDetached;
  end;

const
  // Виды обновлений, полезная нагрузка которых — сообщение.
  CMessageKinds: array[0..6] of string = (TTgUpdateType.Message, TTgUpdateType.EditedMessage,
    TTgUpdateType.ChannelPost, TTgUpdateType.EditedChannelPost, TTgUpdateType.BusinessMessage,
    TTgUpdateType.EditedBusinessMessage, TTgUpdateType.GuestMessage);

threadvar
  // Поток выполняет OnError/OnFault отказа источника: Stop/Start отсюда
  // ждали бы завершения этого же потока.
  GTgInFaultNotify: Boolean;

/// <summary>Id объекта (chat/user) строкой; '' — нет объекта или id.</summary>
function JsonIdText(AObj: TJSONObject): string;
begin
  if TTgJson.Has(AObj, 'id') then
    Result := IntToStr(TTgJson.GetInt64(AObj, 'id'))
  else
    Result := '';
end;

constructor TTgContext.Create(const ACore: IInterface; AApi: TTgApi; const ARaw: ITgRawUpdate;
  const ACancel: ITgCancellation; const AStorage: ITgStateStorage);
begin
  inherited Create;
  FCoreRef := ACore;
  FApi := AApi;
  FRaw := ARaw;
  FCancel := ACancel;
  FStorage := AStorage;
  FPayload := TTgJson.GetObj(ARaw.Json, ARaw.Kind);
end;

function TTgContext.IsCallback: Boolean;
begin
  Result := FRaw.Kind = TTgUpdateType.CallbackQuery;
end;

function TTgContext.MessageJson: TJSONObject;
var
  LKind: string;
begin
  if IsCallback then
    Exit(TTgJson.GetObj(FPayload, 'message'));
  for LKind in CMessageKinds do
    if FRaw.Kind = LKind then
      Exit(FPayload);
  Result := nil;
end;

function TTgContext.ChatJson: TJSONObject;
var
  LMessage: TJSONObject;
begin
  LMessage := MessageJson;
  if Assigned(LMessage) then
    Result := TTgJson.GetObj(LMessage, 'chat')
  else
    Result := TTgJson.GetObj(FPayload, 'chat');
end;

function TTgContext.UserJson: TJSONObject;
begin
  Result := TTgJson.GetObj(FPayload, 'from');
  if not Assigned(Result) then
    Result := TTgJson.GetObj(FPayload, 'user');
end;

function TTgContext.GetUpdate: ITgUpdate;
begin
  // Без копии JSON: DTO удерживает сырое обновление (владельца JSON).
  if not Assigned(FUpdate) then
    FUpdate := TgMakeUpdate(FRaw.Json, FRaw);
  Result := FUpdate;
end;

function TTgContext.GetRaw: ITgRawUpdate;
begin
  Result := FRaw;
end;

function TTgContext.GetKind: string;
begin
  Result := FRaw.Kind;
end;

function TTgContext.GetApi: TTgApi;
begin
  Result := FApi;
end;

function TTgContext.GetCancel: ITgCancellation;
begin
  Result := FCancel;
end;

function TTgContext.GetChatId: TTgChatId;
var
  LChat: TJSONObject;
begin
  LChat := ChatJson;
  if TTgJson.Has(LChat, 'id') then
    Result := TTgChatId.FromId(TTgJson.GetInt64(LChat, 'id'))
  else
    Result := Default(TTgChatId);
end;

function TTgContext.GetFrom: ITgUser;
var
  LUser: TJSONObject;
begin
  LUser := UserJson;
  if Assigned(LUser) then
    Result := TgMakeUser(LUser, FRaw)
  else
    Result := nil;
end;

function TTgContext.GetMessage: ITgMessage;
var
  LMessage: TJSONObject;
begin
  LMessage := MessageJson;
  // Недоступное сообщение callback_query (date = 0) — не Message.
  if not Assigned(LMessage) or (IsCallback and (TTgJson.GetInt64(LMessage, 'date') = 0)) then
    Exit(nil);
  Result := TgMakeMessage(LMessage, FRaw);
end;

function TTgContext.GetText: string;
var
  LMessage: TJSONObject;
begin
  if IsCallback then
    Exit(TTgJson.GetStr(FPayload, 'data'));
  if (FRaw.Kind = TTgUpdateType.InlineQuery) or (FRaw.Kind = TTgUpdateType.ChosenInlineResult) then
    Exit(TTgJson.GetStr(FPayload, 'query'));
  LMessage := MessageJson;
  Result := TTgJson.GetStr(LMessage, 'text');
  if Result = '' then
    Result := TTgJson.GetStr(LMessage, 'caption');
end;

function TTgContext.GetData: string;
begin
  if IsCallback then
    Result := TTgJson.GetStr(FPayload, 'data')
  else
    Result := '';
end;

function TTgContext.GetStateKey: string;
begin
  Result := JsonIdText(ChatJson) + ':' + JsonIdText(UserJson);
end;

function TTgContext.GetState(const AName: string): string;
begin
  if not FStorage.TryGet(GetStateKey, AName, Result) then
    Result := '';
end;

procedure TTgContext.SetState(const AName, AValue: string);
begin
  if AValue = '' then
    FStorage.Delete(GetStateKey, AName)
  else
    FStorage.Put(GetStateKey, AName, AValue);
end;

procedure TTgContext.ClearState;
begin
  FStorage.Delete(GetStateKey);
end;

function TTgContext.GetCommand: string;
begin
  Result := FCommand;
end;

function TTgContext.GetArgs: string;
begin
  Result := FArgs;
end;

function TTgContext.GetHandled: Boolean;
begin
  Result := FHandled;
end;

procedure TTgContext.SetHandled(AValue: Boolean);
begin
  FHandled := AValue;
end;

function TTgContext.MessageText: string;
begin
  if FRaw.Kind = TTgUpdateType.Message then
    Result := TTgJson.GetStr(FPayload, 'text')
  else
    Result := '';
end;

{ TTgTextMatcher }

constructor TTgTextMatcher.Create(const APattern: string);
begin
  inherited Create;
  // Сначала шаблон: при ошибке компиляции блокировка ещё не создана.
  // roCompiled — компиляция здесь (без него TRegEx компилирует при первом
  // поиске, и неверный шаблон проявился бы только в обработчике).
  FRegEx := TRegEx.Create(APattern, [roNotEmpty, roCompiled]);
  FPattern := APattern;
  FLock := TCriticalSection.Create;
end;

destructor TTgTextMatcher.Destroy;
begin
  FreeAndNil(FLock);
  inherited Destroy;
end;

function TTgTextMatcher.GetPattern: string;
begin
  Result := FPattern;
end;

function TTgTextMatcher.DoMatch(const AText: string; out AArgs: string): Boolean;
var
  LMatch: TMatch;
begin
  // Отдельный метод: TMatch (ссылается на общий TPerlRegEx) финализируется
  // до выхода из блокировки TryMatch.
  LMatch := FRegEx.Match(AText);
  Result := LMatch.Success;
  if not Result then
    AArgs := ''
  else if LMatch.Groups.Count > 1 then
    AArgs := LMatch.Groups[1].Value
  else
    AArgs := LMatch.Value;
end;

function TTgTextMatcher.TryMatch(const AText: string; out AArgs: string): Boolean;
begin
  FLock.Enter;
  try
    Result := DoMatch(AText, AArgs);
  finally
    FLock.Leave;
  end;
end;

function TTgContext.SendText(const AText, AParseMode: string;
  const AKeyboard: TTgReplyMarkup): ITgMessage;
var
  LChat: TTgChatId;
  LOptions: TTgSendMessageOptions;
  LMessage: TJSONObject;
  LBusiness: string;
begin
  LChat := GetChatId;
  if LChat.IsEmpty then
    raise ETgError.Create(TgUpdatesText(TTgUpdatesText.NoChat));
  LOptions := Default(TTgSendMessageOptions);
  LMessage := MessageJson;
  // Ответ — в то же бизнес-подключение и ту же тему форума.
  LBusiness := TTgJson.GetStr(LMessage, 'business_connection_id');
  if LBusiness <> '' then
    LOptions.BusinessConnectionId := LBusiness;
  if TTgJson.GetBool(LMessage, 'is_topic_message') and TTgJson.Has(LMessage, 'message_thread_id') then
    LOptions.MessageThreadId := TTgJson.GetInt64(LMessage, 'message_thread_id');
  if AParseMode <> '' then
    LOptions.ParseMode := AParseMode;
  if not AKeyboard.IsEmpty then
    LOptions.ReplyMarkup := AKeyboard;
  Result := FApi.SendMessage(LChat, AText, LOptions);
end;

function TTgContext.Reply(const AText: string): ITgMessage;
begin
  Result := SendText(AText, '', Default(TTgReplyMarkup));
end;

function TTgContext.Reply(const AText: string; const AKeyboard: TTgReplyMarkup): ITgMessage;
begin
  Result := SendText(AText, '', AKeyboard);
end;

function TTgContext.ReplyHtml(const AText: string): ITgMessage;
begin
  Result := SendText(AText, TTgParseMode.Html, Default(TTgReplyMarkup));
end;

function TTgContext.ReplyHtml(const AText: string; const AKeyboard: TTgReplyMarkup): ITgMessage;
begin
  Result := SendText(AText, TTgParseMode.Html, AKeyboard);
end;

function TTgContext.Answer(const AText: string; AShowAlert: Boolean): Boolean;
var
  LId: string;
begin
  if not IsCallback then
    Exit(False);
  LId := TTgJson.GetStr(FPayload, 'id');
  // До вызова: при ошибке автоматический ответ не повторяет запрос.
  FAnswered := True;
  if AShowAlert then
    Result := FApi.AnswerCallbackQuery(LId, AText, True)
  else if AText <> '' then
    Result := FApi.AnswerCallbackQuery(LId, AText)
  else
    Result := FApi.AnswerCallbackQuery(LId);
end;

/// <summary>400 «Bad Request: message is not modified…» от edit-метода.</summary>
function IsMessageNotModified(AError: ETgApiError): Boolean;
begin
  Result := (AError.ErrorCode = 400) and
    (Pos('message is not modified', LowerCase(AError.Description)) > 0);
end;

function TTgContext.EditText(const AText: string;
  const AKeyboard: ITgInlineKeyboardMarkup): Boolean;
var
  LOptions: TTgEditMessageTextOptions;
  LInlineId, LBusiness: string;
  LMessage, LChat: TJSONObject;
begin
  if not IsCallback then
    Exit(False);
  LOptions := Default(TTgEditMessageTextOptions);
  if Assigned(AKeyboard) then
    LOptions.ReplyMarkup := AKeyboard;
  try
    LInlineId := TTgJson.GetStr(FPayload, 'inline_message_id');
    if LInlineId <> '' then
      Exit(FApi.EditInlineMessageText(LInlineId, AText, LOptions));
    LMessage := TTgJson.GetObj(FPayload, 'message');
    LChat := TTgJson.GetObj(LMessage, 'chat');
    if not TTgJson.Has(LChat, 'id') or not TTgJson.Has(LMessage, 'message_id') then
      Exit(False);
    LBusiness := TTgJson.GetStr(LMessage, 'business_connection_id');
    if LBusiness <> '' then
      LOptions.BusinessConnectionId := LBusiness;
    FApi.EditMessageText(TTgChatId.FromId(TTgJson.GetInt64(LChat, 'id')),
      TTgJson.GetInt64(LMessage, 'message_id'), AText, LOptions);
    Result := True;
  except
    // Повторное нажатие той же кнопки: текст и клавиатура не изменились —
    // это не ошибка обработчика (только в хелпере, сырые методы Api — как есть).
    on E: ETgApiError do
      if IsMessageNotModified(E) then
        Result := False
      else
        raise;
  end;
end;

function TTgContext.Edit(const AText: string): Boolean;
begin
  Result := EditText(AText, nil);
end;

function TTgContext.Edit(const AText: string; const AKeyboard: ITgInlineKeyboardMarkup): Boolean;
begin
  Result := EditText(AText, AKeyboard);
end;

{ TTgWebhookNotifyTransport }

constructor TTgWebhookNotifyTransport.Create(const AInner: ITgTransport; const ACore: ITgBotCore);
begin
  inherited Create;
  FInner := AInner;
  FCore := ACore;
end;

procedure TTgWebhookNotifyTransport.AfterCall(const AMethod: string);
begin
  if SameText(AMethod, 'setWebhook') then
    FCore.NotifyWebhookRegistered;
end;

function TTgWebhookNotifyTransport.Execute(const AMethod: string; AParams: TTgParams): TJSONValue;
begin
  Result := FInner.Execute(AMethod, AParams);
  AfterCall(AMethod);
end;

procedure TTgWebhookNotifyTransport.DownloadFile(const AFilePath: string; ADest: TStream);
begin
  FInner.DownloadFile(AFilePath, ADest);
end;

procedure TTgWebhookNotifyTransport.Cancel;
begin
  FInner.Cancel;
end;

procedure TTgWebhookNotifyTransport.ResetCancel;
begin
  FInner.ResetCancel;
end;

function TTgWebhookNotifyTransport.IsCancelled: Boolean;
begin
  Result := FInner.IsCancelled;
end;

{ TTgWebhookNotifyCancellableTransport }

function TTgWebhookNotifyCancellableTransport.ExecuteEx(const AMethod: string; AParams: TTgParams;
  const ACancel: ITgCancellation): TJSONValue;
begin
  Result := (FInner as ITgCancellableTransport).ExecuteEx(AMethod, AParams, ACancel);
  AfterCall(AMethod);
end;

procedure TTgWebhookNotifyCancellableTransport.DownloadFileEx(const AFilePath: string; ADest: TStream;
  const ACancel: ITgCancellation);
begin
  (FInner as ITgCancellableTransport).DownloadFileEx(AFilePath, ADest, ACancel);
end;

/// <summary>Транспорт webhook-источника поверх ATransport клиента (см. TTgWebhookNotifyTransport).</summary>
function NewWebhookTransport(const ATransport: ITgTransport; const ACore: ITgBotCore): ITgTransport;
begin
  if Supports(ATransport, ITgCancellableTransport) then
    Result := TTgWebhookNotifyCancellableTransport.Create(ATransport, ACore)
  else
    Result := TTgWebhookNotifyTransport.Create(ATransport, ACore);
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

/// <summary>
///   Обработчик диспетчера. Отдельная функция: замыкание захватывает только
///   интерфейс ядра (без кадра Init и Self бота).
/// </summary>
function NewRawHandler(const ACore: ITgBotCore): TTgRawHandler;
begin
  Result :=
    procedure(const AUpdate: ITgRawUpdate)
    begin
      ACore.HandleRaw(AUpdate);
    end;
end;

/// <summary>Устранимая ошибка приёма (OnError источника).</summary>
function NewSourceErrorHandler(const ACore: ITgBotCore): TProc<Exception>;
begin
  Result :=
    procedure(AError: Exception)
    begin
      ACore.NotifyError(AError, nil);
    end;
end;

/// <summary>409 от источника (OnConflict источника).</summary>
function NewConflictHandler(const ACore: ITgBotCore): TTgConflictHandler;
begin
  Result :=
    procedure(AError: ETgConflictError)
    begin
      ACore.NotifyConflict(AError);
    end;
end;

/// <summary>
///   Отказ источника (OnFault источника) запуска AGeneration. Назначается при
///   каждом Start: источник копирует обработчик в ядро опроса этого запуска.
/// </summary>
function NewFaultHandler(const ACore: ITgBotCore; AGeneration: Integer): TProc<Exception>;
begin
  Result :=
    procedure(AError: Exception)
    begin
      ACore.NotifyFault(AError, AGeneration);
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
var
  LCore: TTgBotCore;
  LCoreIntf: ITgBotCore;
begin
  try
    LCore := TTgBotCore.Create(AApi);
  except
    // Ядро не создано — клиент ему не передан.
    AApi.Free;
    raise;
  end;
  FCore := LCore;
  FCoreRef := LCore;
  LCoreIntf := LCore;
  FApi := LCore.Api;
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
  FDispatcher := TTgUpdateDispatcher.Create(NewRawHandler(LCoreIntf));
  FDispatcherRef := FDispatcher;
  FDispatcher.OnProcessed := NewProcessedHandler(FSourceRef);
  // События источника — в его потоке; захватывается только ядро.
  FSource.OnConflict := NewConflictHandler(LCoreIntf);
  FSource.OnError := NewSourceErrorHandler(LCoreIntf);
  // Webhook: setWebhook/deleteWebhook — через тот же транспорт, прерываются Free;
  // обёртка сообщает ядру об успешном setWebhook (OnWebhookRegistered).
  FWebhookSource := TTgWebhookSource.Create(NewWebhookTransport(FApi.Transport, LCoreIntf),
    FApi.CancelToken);
  FWebhookSourceRef := FWebhookSource;
  FWebhookSource.OnError := NewSourceErrorHandler(LCoreIntf);
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
    TTgBotCore(FCore).Detach;
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
  FCoreRef := nil;
  FreeAndNil(FRunWake);
  inherited Destroy;
end;

function TTgBot.GetStateStorage: ITgStateStorage;
begin
  Result := TTgBotCore(FCore).GetStateStorage;
end;

procedure TTgBot.SetStateStorage(const AValue: ITgStateStorage);
begin
  TTgBotCore(FCore).SetStateStorage(AValue);
end;

function TTgBot.GetAutoAnswerCallbacks: Boolean;
begin
  Result := TTgBotCore(FCore).GetAutoAnswerCallbacks;
end;

procedure TTgBot.SetAutoAnswerCallbacks(AValue: Boolean);
begin
  TTgBotCore(FCore).SetAutoAnswerCallbacks(AValue);
end;

function TTgBot.GetOnUpdate: TProc<ITgContext>;
begin
  Result := TTgBotCore(FCore).GetOnUpdate();
end;

procedure TTgBot.SetOnUpdate(const AValue: TProc<ITgContext>);
begin
  TTgBotCore(FCore).SetOnUpdate(AValue);
end;

function TTgBot.GetOnMessage: TProc<ITgContext>;
begin
  Result := TTgBotCore(FCore).GetOnMessage();
end;

procedure TTgBot.SetOnMessage(const AValue: TProc<ITgContext>);
begin
  TTgBotCore(FCore).SetOnMessage(AValue);
end;

function TTgBot.GetOnCallbackQuery: TProc<ITgContext>;
begin
  Result := TTgBotCore(FCore).GetOnCallbackQuery();
end;

procedure TTgBot.SetOnCallbackQuery(const AValue: TProc<ITgContext>);
begin
  TTgBotCore(FCore).SetOnCallbackQuery(AValue);
end;

function TTgBot.GetOnError: TProc<Exception, ITgContext>;
begin
  Result := TTgBotCore(FCore).GetOnError();
end;

procedure TTgBot.SetOnError(const AValue: TProc<Exception, ITgContext>);
begin
  TTgBotCore(FCore).SetOnError(AValue);
end;

function TTgBot.GetOnConflict: TProc<ETgConflictError>;
begin
  Result := TTgBotCore(FCore).GetOnConflict();
end;

procedure TTgBot.SetOnConflict(const AValue: TProc<ETgConflictError>);
begin
  TTgBotCore(FCore).SetOnConflict(AValue);
end;

function TTgBot.GetOnFault: TProc<Exception>;
begin
  Result := TTgBotCore(FCore).GetOnFault();
end;

procedure TTgBot.SetOnFault(const AValue: TProc<Exception>);
begin
  TTgBotCore(FCore).SetOnFault(AValue);
end;

function TTgBot.GetOnWebhookRegistered: TProc;
begin
  Result := TTgBotCore(FCore).GetOnWebhookRegistered();
end;

procedure TTgBot.SetOnWebhookRegistered(const AValue: TProc);
begin
  TTgBotCore(FCore).SetOnWebhookRegistered(AValue);
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
    FWebhookSource.AllowedUpdates := TTgOptionalStrings.Create(nil);
{$ENDIF}
end;

function TTgBot.GetState: TTgBotState;
begin
  Result := TTgBotCore(FCore).GetState;
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
      TTgBotCore(FCore).NotifyError(LWarning, nil);
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
  LRoutes := TTgBotCore(FCore).GetRoutes;
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
  TTgBotCore(FCore).BeginStartJob(FSetMyCommandsOnStart);
end;

function TTgBot.GetOnUnknownCommand: TProc<ITgContext>;
begin
  Result := TTgBotCore(FCore).GetOnUnknownCommand();
end;

procedure TTgBot.SetOnUnknownCommand(const AValue: TProc<ITgContext>);
begin
  TTgBotCore(FCore).SetOnUnknownCommand(AValue);
end;

function TTgBot.GetBotUserName: string;
begin
  Result := TTgBotCore(FCore).GetBotUserName;
end;

/// <summary>Имя команды: без ведущего '/', в нижнем регистре; пустое или с пробелом/'@' — ETgError.</summary>
function NormalizeCommandName(const AName: string): string;
var
  C: Char;
begin
  Result := AName;
  if Copy(Result, 1, 1) = '/' then
    Delete(Result, 1, 1);
  if Result = '' then
    raise ETgError.Create(Format(TgRouterText(TTgRouterText.EmptyKey), ['Command']));
  for C in Result do
    if (C <= ' ') or (C = '@') then
      raise ETgError.Create(Format(TgRouterText(TTgRouterText.BadCommand), [AName]));
  Result := AnsiLowerCase(Result);
end;

/// <summary>Пустой ключ правила — ETgError (ARule — имя метода регистрации).</summary>
procedure CheckRouteKey(const AKey, ARule: string);
begin
  if AKey = '' then
    raise ETgError.Create(Format(TgRouterText(TTgRouterText.EmptyKey), [ARule]));
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
      TTgBotCore(FCore).SetRoute(TTgRouteKind.Command, LKeys[I], ADescription, AHandler)
    else
      TTgBotCore(FCore).SetRoute(TTgRouteKind.Command, LKeys[I], '', AHandler);
  Result := Self;
end;

function TTgBot.Callback(const AData: string; const AHandler: TProc<ITgContext>): TTgBot;
begin
  CheckRouteKey(AData, 'Callback');
  TTgBotCore(FCore).SetRoute(TTgRouteKind.Callback, AData, '', AHandler);
  Result := Self;
end;

function TTgBot.CallbackPrefix(const APrefix: string; const AHandler: TProc<ITgContext>): TTgBot;
begin
  CheckRouteKey(APrefix, 'CallbackPrefix');
  TTgBotCore(FCore).SetRoute(TTgRouteKind.CallbackPrefix, APrefix, '', AHandler);
  Result := Self;
end;

function TTgBot.Text(const AHandler: TProc<ITgContext>): TTgBot;
begin
  TTgBotCore(FCore).SetAnyText(AHandler);
  Result := Self;
end;

function TTgBot.Text(const AText: string; const AHandler: TProc<ITgContext>): TTgBot;
begin
  CheckRouteKey(AText, 'Text');
  TTgBotCore(FCore).SetRoute(TTgRouteKind.Text, AnsiLowerCase(AText), '', AHandler);
  Result := Self;
end;

function TTgBot.TextMatch(const APattern: string; const AHandler: TProc<ITgContext>): TTgBot;
var
  LMatcher: ITgTextMatcher;
begin
  CheckRouteKey(APattern, 'TextMatch');
  // Компиляция здесь: неверный шаблон — исключение в вызывающем потоке.
  LMatcher := TTgTextMatcher.Create(APattern);
  TTgBotCore(FCore).SetMatchRoute(LMatcher, AHandler);
  Result := Self;
end;

{ TTgStartJob }

constructor TTgStartJob.Create(const AParent: ITgCancellation);
begin
  inherited Create;
  // Ручной сброс: ждать могут Stop и несколько обработчиков сразу.
  FDone := TEvent.Create(nil, True, False, '');
  FNameDone := TEvent.Create(nil, True, False, '');
  FCancelSource := TTgCancellationSource.Create(AParent);
  FCancel := FCancelSource;
end;

destructor TTgStartJob.Destroy;
begin
  FCancelSource := nil;
  FCancel := nil;
  FreeAndNil(FNameDone);
  FreeAndNil(FDone);
  inherited Destroy;
end;

function TTgStartJob.WaitDone(AMs: Cardinal; APump: Boolean): Boolean;
var
  LWatch: TStopwatch;
  LLeft: Int64;
begin
  if not APump then
    Exit(FDone.WaitFor(AMs) = wrSignaled);
  LWatch := TStopwatch.StartNew;
  repeat
    if FDone.WaitFor(0) = wrSignaled then
      Exit(True);
    LLeft := Int64(AMs) - LWatch.ElapsedMilliseconds;
    if LLeft <= 0 then
      Exit(False);
    CheckSynchronize(Min(LLeft, 10));
  until False;
end;

{ TTgBotCore }

constructor TTgBotCore.Create(AApi: TTgApi);
begin
  inherited Create;
  FLock := TCriticalSection.Create;
  FStateStorage := TTgMemoryStateStorage.Create;
  FAutoAnswerCallbacks := True;
  // Последним: если конструктор упадёт раньше, клиент освобождает вызывающий.
  FApi := AApi;
end;

destructor TTgBotCore.Destroy;
begin
  FOnUpdate := nil;
  FOnMessage := nil;
  FOnCallbackQuery := nil;
  FOnError := nil;
  FOnConflict := nil;
  FOnFault := nil;
  FOnWebhookRegistered := nil;
  FRoutes := Default(TTgRoutes);
  FStateStorage := nil;
  // До клиента: токен задачи связан с токеном отмены клиента.
  FStartJob := nil;
  FStartJobRef := nil;
  // Последняя ссылка на ядро: никто больше не обращается к клиенту.
  FreeAndNil(FApi);
  FreeAndNil(FLock);
  inherited Destroy;
end;

function TTgBotCore.GetDetached: Boolean;
begin
  FLock.Enter;
  try
    Result := FDetached;
  finally
    FLock.Leave;
  end;
end;

procedure TTgBotCore.Detach;
var
  LOnUpdate, LOnMessage, LOnCallbackQuery: TProc<ITgContext>;
  LOnError: TProc<Exception, ITgContext>;
  LOnConflict: TProc<ETgConflictError>;
  LOnFault: TProc<Exception>;
  LOnWebhookRegistered: TProc;
  LRoutes: TTgRoutes;
begin
  FLock.Enter;
  try
    FDetached := True;
    LOnWebhookRegistered := FOnWebhookRegistered;
    FOnWebhookRegistered := nil;
    // Замыкания пользователя освобождаются при выходе — вне блокировки.
    LRoutes := FRoutes;
    FRoutes := Default(TTgRoutes);
    LOnUpdate := FOnUpdate;
    LOnMessage := FOnMessage;
    LOnCallbackQuery := FOnCallbackQuery;
    LOnError := FOnError;
    LOnConflict := FOnConflict;
    LOnFault := FOnFault;
    FOnUpdate := nil;
    FOnMessage := nil;
    FOnCallbackQuery := nil;
    FOnError := nil;
    FOnConflict := nil;
    FOnFault := nil;
  finally
    FLock.Leave;
  end;
  // Не ждёт: начатые вызовы прерываются, новые — ETgCancelledError.
  if Assigned(FApi) then
    FApi.Shutdown;
end;

function TTgBotCore.GetStateStorage: ITgStateStorage;
begin
  FLock.Enter;
  try
    Result := FStateStorage;
  finally
    FLock.Leave;
  end;
end;

procedure TTgBotCore.SetStateStorage(const AValue: ITgStateStorage);
var
  LNew, LOld: ITgStateStorage;
begin
  if Assigned(AValue) then
    LNew := AValue
  else
    LNew := TTgMemoryStateStorage.Create;
  FLock.Enter;
  try
    LOld := FStateStorage;
    FStateStorage := LNew;
  finally
    FLock.Leave;
  end;
end;

function TTgBotCore.GetAutoAnswerCallbacks: Boolean;
begin
  FLock.Enter;
  try
    Result := FAutoAnswerCallbacks;
  finally
    FLock.Leave;
  end;
end;

procedure TTgBotCore.SetAutoAnswerCallbacks(AValue: Boolean);
begin
  FLock.Enter;
  try
    FAutoAnswerCallbacks := AValue;
  finally
    FLock.Leave;
  end;
end;

// Сеттеры обработчиков: прежнее замыкание освобождается при выходе (LOld) —
// вне блокировки; его финализация может обращаться к чему угодно.

function TTgBotCore.GetOnUpdate: TProc<ITgContext>;
begin
  FLock.Enter;
  try
    Result := FOnUpdate;
  finally
    FLock.Leave;
  end;
end;

procedure TTgBotCore.SetOnUpdate(const AValue: TProc<ITgContext>);
var
  LOld: TProc<ITgContext>;
begin
  FLock.Enter;
  try
    LOld := FOnUpdate;
    FOnUpdate := AValue;
  finally
    FLock.Leave;
  end;
end;

function TTgBotCore.GetOnMessage: TProc<ITgContext>;
begin
  FLock.Enter;
  try
    Result := FOnMessage;
  finally
    FLock.Leave;
  end;
end;

procedure TTgBotCore.SetOnMessage(const AValue: TProc<ITgContext>);
var
  LOld: TProc<ITgContext>;
begin
  FLock.Enter;
  try
    LOld := FOnMessage;
    FOnMessage := AValue;
  finally
    FLock.Leave;
  end;
end;

function TTgBotCore.GetOnCallbackQuery: TProc<ITgContext>;
begin
  FLock.Enter;
  try
    Result := FOnCallbackQuery;
  finally
    FLock.Leave;
  end;
end;

procedure TTgBotCore.SetOnCallbackQuery(const AValue: TProc<ITgContext>);
var
  LOld: TProc<ITgContext>;
begin
  FLock.Enter;
  try
    LOld := FOnCallbackQuery;
    FOnCallbackQuery := AValue;
  finally
    FLock.Leave;
  end;
end;

function TTgBotCore.GetOnError: TProc<Exception, ITgContext>;
begin
  FLock.Enter;
  try
    Result := FOnError;
  finally
    FLock.Leave;
  end;
end;

procedure TTgBotCore.SetOnError(const AValue: TProc<Exception, ITgContext>);
var
  LOld: TProc<Exception, ITgContext>;
begin
  FLock.Enter;
  try
    LOld := FOnError;
    FOnError := AValue;
  finally
    FLock.Leave;
  end;
end;

function TTgBotCore.GetOnConflict: TProc<ETgConflictError>;
begin
  FLock.Enter;
  try
    Result := FOnConflict;
  finally
    FLock.Leave;
  end;
end;

procedure TTgBotCore.SetOnConflict(const AValue: TProc<ETgConflictError>);
var
  LOld: TProc<ETgConflictError>;
begin
  FLock.Enter;
  try
    LOld := FOnConflict;
    FOnConflict := AValue;
  finally
    FLock.Leave;
  end;
end;

procedure TTgBotCore.NotifyError(AError: Exception; const AContext: ITgContext);
var
  LOnError: TProc<Exception, ITgContext>;
begin
  // Отмена обработчика при остановке бота — не ошибка.
  if (AError is ETgCancelledError) and Assigned(AContext) and Assigned(AContext.Cancel) and
    AContext.Cancel.IsCancelled then
    Exit;
  // Снимок под блокировкой, вызов — вне её; после Detach не вызывается.
  FLock.Enter;
  try
    if FDetached then
      Exit;
    LOnError := FOnError;
  finally
    FLock.Leave;
  end;
  if Assigned(LOnError) then
    try
      LOnError(AError, AContext);
    except
      // Исключение OnError поглощается.
    end;
end;

procedure TTgBotCore.NotifyConflict(AError: ETgConflictError);
var
  LOnConflict: TProc<ETgConflictError>;
begin
  FLock.Enter;
  try
    if FDetached then
      Exit;
    LOnConflict := FOnConflict;
  finally
    FLock.Leave;
  end;
  if Assigned(LOnConflict) then
    LOnConflict(AError);
end;

procedure TTgBotCore.NotifyFault(AError: Exception; AGeneration: Integer);
var
  LOnError: TProc<Exception, ITgContext>;
  LOnFault: TProc<Exception>;
  LPrevious: Boolean;
begin
  FLock.Enter;
  try
    // Только из Running текущего запуска: отказ во время Stop или от
    // источника прежнего запуска — не смена состояния; после Free — тишина.
    if FDetached or (AGeneration <> FGeneration) or (FState <> TTgBotState.Running) then
      Exit;
    FState := TTgBotState.Faulted;
    LOnError := FOnError;
    LOnFault := FOnFault;
  finally
    FLock.Leave;
  end;
  LPrevious := GTgInFaultNotify;
  GTgInFaultNotify := True;
  try
    // Сначала OnError — общий журнал ошибок (как до появления OnFault),
    // затем OnFault — реакция на смену состояния, когда ошибка уже записана.
    if Assigned(LOnError) then
      try
        LOnError(AError, nil);
      except
        // Исключение OnError поглощается.
      end;
    if Assigned(LOnFault) then
      try
        LOnFault(AError);
      except
        // Исключение OnFault поглощается.
      end;
  finally
    GTgInFaultNotify := LPrevious;
  end;
end;

procedure TTgBotCore.NotifyWebhookRegistered;
var
  LHandler: TProc;
begin
  FLock.Enter;
  try
    // Регистрация, завершившаяся во время Stop или после отказа/Free, — тишина.
    if FDetached or (FState <> TTgBotState.Running) then
      Exit;
    LHandler := FOnWebhookRegistered;
  finally
    FLock.Leave;
  end;
  if Assigned(LHandler) then
    try
      LHandler();
    except
      // Исключение OnWebhookRegistered поглощается.
    end;
end;

function TTgBotCore.GetOnWebhookRegistered: TProc;
begin
  FLock.Enter;
  try
    Result := FOnWebhookRegistered;
  finally
    FLock.Leave;
  end;
end;

procedure TTgBotCore.SetOnWebhookRegistered(const AValue: TProc);
var
  LOld: TProc;
begin
  FLock.Enter;
  try
    // Прежнее замыкание освобождается при выходе — вне блокировки.
    LOld := FOnWebhookRegistered;
    FOnWebhookRegistered := AValue;
  finally
    FLock.Leave;
  end;
end;

function TTgBotCore.BeginRun: Integer;
begin
  FLock.Enter;
  try
    Inc(FGeneration);
    FState := TTgBotState.Running;
    Result := FGeneration;
  finally
    FLock.Leave;
  end;
end;

function TTgBotCore.GetState: TTgBotState;
begin
  FLock.Enter;
  try
    Result := FState;
  finally
    FLock.Leave;
  end;
end;

procedure TTgBotCore.SetState(AValue: TTgBotState);
begin
  FLock.Enter;
  try
    FState := AValue;
  finally
    FLock.Leave;
  end;
end;

function TTgBotCore.GetOnFault: TProc<Exception>;
begin
  FLock.Enter;
  try
    Result := FOnFault;
  finally
    FLock.Leave;
  end;
end;

procedure TTgBotCore.SetOnFault(const AValue: TProc<Exception>);
var
  LOld: TProc<Exception>;
begin
  FLock.Enter;
  try
    LOld := FOnFault;
    FOnFault := AValue;
  finally
    FLock.Leave;
  end;
end;

// Правила: массивы снимка не меняются на месте — изменение создаёт копию.
// Прежний массив (и замыкания удалённых/заменённых правил) освобождается при
// выходе (LOld) — вне блокировки.

procedure TTgBotCore.SetRoute(AKind: TTgRouteKind; const AKey, ADescription: string;
  const AHandler: TProc<ITgContext>);
var
  LOld, LNew: TArray<TTgRoute>;
  LIndex, I: Integer;
begin
  FLock.Enter;
  try
    LOld := FRoutes.Lists[AKind];
    LIndex := -1;
    for I := 0 to High(LOld) do
      if LOld[I].Key = AKey then
      begin
        LIndex := I;
        Break;
      end;
    if Assigned(AHandler) then
    begin
      LNew := Copy(LOld);
      if LIndex < 0 then
      begin
        LIndex := Length(LNew);
        SetLength(LNew, LIndex + 1);
        LNew[LIndex].Key := AKey;
      end;
      LNew[LIndex].Description := ADescription;
      LNew[LIndex].Handler := AHandler;
    end
    else if LIndex >= 0 then
    begin
      LNew := Copy(LOld);
      Delete(LNew, LIndex, 1);
    end
    else
      Exit;
    FRoutes.Lists[AKind] := LNew;
  finally
    FLock.Leave;
  end;
end;

procedure TTgBotCore.SetMatchRoute(const AMatcher: ITgTextMatcher; const AHandler: TProc<ITgContext>);
var
  LOld, LNew: TArray<TTgMatchRoute>;
  LIndex, I: Integer;
begin
  FLock.Enter;
  try
    LOld := FRoutes.Matches;
    LIndex := -1;
    for I := 0 to High(LOld) do
      if LOld[I].Matcher.Pattern = AMatcher.Pattern then
      begin
        LIndex := I;
        Break;
      end;
    if Assigned(AHandler) then
    begin
      LNew := Copy(LOld);
      if LIndex < 0 then
      begin
        LIndex := Length(LNew);
        SetLength(LNew, LIndex + 1);
      end;
      LNew[LIndex].Matcher := AMatcher;
      LNew[LIndex].Handler := AHandler;
    end
    else if LIndex >= 0 then
    begin
      LNew := Copy(LOld);
      Delete(LNew, LIndex, 1);
    end
    else
      Exit;
    FRoutes.Matches := LNew;
  finally
    FLock.Leave;
  end;
end;

procedure TTgBotCore.SetAnyText(const AValue: TProc<ITgContext>);
var
  LOld: TProc<ITgContext>;
begin
  FLock.Enter;
  try
    LOld := FRoutes.AnyText;
    FRoutes.AnyText := AValue;
  finally
    FLock.Leave;
  end;
end;

function TTgBotCore.GetOnUnknownCommand: TProc<ITgContext>;
begin
  FLock.Enter;
  try
    Result := FRoutes.UnknownCommand;
  finally
    FLock.Leave;
  end;
end;

procedure TTgBotCore.SetOnUnknownCommand(const AValue: TProc<ITgContext>);
var
  LOld: TProc<ITgContext>;
begin
  FLock.Enter;
  try
    LOld := FRoutes.UnknownCommand;
    FRoutes.UnknownCommand := AValue;
  finally
    FLock.Leave;
  end;
end;

function TTgBotCore.GetRoutes: TTgRoutes;
begin
  FLock.Enter;
  try
    Result := FRoutes;
  finally
    FLock.Leave;
  end;
end;

function TTgBotCore.GetBotUserName: string;
begin
  FLock.Enter;
  try
    Result := FBotUserName;
  finally
    FLock.Leave;
  end;
end;

procedure TTgBotCore.SetBotUserName(const AValue: string);
begin
  FLock.Enter;
  try
    FBotUserName := AValue;
  finally
    FLock.Leave;
  end;
end;

function TTgBotCore.CurrentStartJob(out AJobRef: IInterface): TTgStartJob;
begin
  FLock.Enter;
  try
    Result := FStartJob;
    AJobRef := FStartJobRef;
  finally
    FLock.Leave;
  end;
end;

function TTgBotCore.ResolveBotUserName(const ACancel: ITgCancellation): string;
var
  LUser: ITgUser;
  LError: TTgErrorInfo;
  LJob: TTgStartJob;
  LJobRef: IInterface;
begin
  Result := GetBotUserName;
  if Result <> '' then
    Exit;
  // getMe фоновой подготовки ещё идёт: ждём его, а не шлём второй запрос.
  // Без подкачки очереди: обработчик может выполняться в главном потоке
  // (Delivery = Main), вложенный CheckSynchronize нарушил бы порядок.
  // Ждём только getMe (NameDone), не OnError и не setMyCommands.
  LJob := CurrentStartJob(LJobRef);
  if Assigned(LJob) then
    while LJob.NameDone.WaitFor(50) <> wrSignaled do
      if Detached or (Assigned(ACancel) and ACancel.IsCancelled) then
        Exit;
  Result := GetBotUserName;
  // Не получен (нет команд при Start или ошибка): запрос здесь, без
  // исключений; неудача — команда считается адресованной другому боту.
  if (Result = '') and FApi.TryGetMe(LUser, LError) and Assigned(LUser) then
  begin
    Result := LUser.Username;
    SetBotUserName(Result);
  end;
end;

/// <summary>
///   401/404 от Bot API: неверный токен или адрес. О такой ошибке сообщает
///   отказ приёма (OnError + OnFault один раз), фоновая подготовка молчит.
/// </summary>
function IsTokenFailure(AError: Exception): Boolean;
begin
  Result := (AError is ETgApiError) and ((ETgApiError(AError).ErrorCode = 401) or
    (ETgApiError(AError).ErrorCode = 404));
end;

function TTgBotCore.StartJobActive(AJob: TTgStartJob): Boolean;
begin
  if AJob.Cancel.IsCancelled then
    Exit(False);
  FLock.Enter;
  try
    // Idle — Start ещё не выставил Running (задача запускается раньше);
    // Stopping — Stop дожидается задачи (меню уходит и при быстром Stop),
    // по истечении ожидания отменяет её (Cancel). Faulted — отказ приёма.
    Result := not FDetached and (FState <> TTgBotState.Faulted);
  finally
    FLock.Leave;
  end;
end;

procedure TTgBotCore.RunStartJob(AJob: TTgStartJob; const AMenu: TArray<ITgBotCommand>);
var
  LScope: TTgCancelScope;
  LError: Exception;
  LTokenFailed: Boolean;
begin
  LTokenFailed := False;
  // Токен задачи — окружающий: Stop/Free прерывают зависшие запросы.
  LScope := TTgCancelScope.Enter(AJob.Cancel);
  try
    // Один раз за жизнь бота: username не меняется (кэш переживает Stop/Start).
    if (GetBotUserName = '') and StartJobActive(AJob) then
    begin
      LError := nil;
      try
        SetBotUserName(FApi.GetMe.Username);
      except
        // Исключение забирается: OnError — после NameDone (см. TTgStartJob).
        on E: Exception do
          if IsTokenFailure(E) then
            LTokenFailed := True
          else if StartJobActive(AJob) then
            LError := Exception(AcquireExceptionObject);
      end;
      AJob.NameDone.SetEvent;
      if Assigned(LError) then
        try
          // Пока шёл перенос, бот мог перейти в Faulted или остановиться.
          if StartJobActive(AJob) then
            NotifyError(LError, nil);
        finally
          LError.Free;
        end;
    end;
    AJob.NameDone.SetEvent;
    // Неверный токен — меню бессмысленно; после отказа/Stop — тоже.
    if (Length(AMenu) > 0) and not LTokenFailed and StartJobActive(AJob) then
      try
        FApi.SetMyCommands(AMenu);
      except
        on E: Exception do
          if not IsTokenFailure(E) and StartJobActive(AJob) then
            NotifyError(E, nil);
      end;
  finally
    LScope.Leave;
  end;
end;

procedure TTgBotCore.BeginStartJob(ASetMyCommands: Boolean);
var
  LRoutes: TTgRoutes;
  LRoute: TTgRoute;
  LMenu: TArray<ITgBotCommand>;
  LJob: TTgStartJob;
  LJobRef, LOldRef, LCoreRef: IInterface;
  LSelf: TTgBotCore;
begin
  LRoutes := GetRoutes;
  // Без команд getMe не нужен; команды, добавленные на ходу, получат
  // username лениво (первая '/cmd@бот').
  if (Length(LRoutes.Lists[TTgRouteKind.Command]) = 0) and not Assigned(LRoutes.UnknownCommand) then
    Exit;
  LMenu := nil;
  if ASetMyCommands then
    for LRoute in LRoutes.Lists[TTgRouteKind.Command] do
      if LRoute.Description <> '' then
        LMenu := LMenu + [TTgBotCommand.Create(LRoute.Key, LRoute.Description)];
  if (GetBotUserName <> '') and (Length(LMenu) = 0) then
    Exit;
  LJob := TTgStartJob.Create(FApi.CancelToken);
  LJobRef := LJob;
  FLock.Enter;
  try
    LOldRef := FStartJobRef;
    FStartJob := LJob;
    FStartJobRef := LJobRef;
  finally
    FLock.Leave;
  end;
  // Задача удерживает ядро (клиент) и себя до завершения.
  LCoreRef := Self;
  LSelf := Self;
  try
    TTask.Run(
      procedure
      begin
        try
          if Assigned(LCoreRef) and Assigned(LJobRef) then
            LSelf.RunStartJob(LJob, LMenu);
        finally
          LJob.NameDone.SetEvent;
          LJob.Done.SetEvent;
        end;
      end, TgBotThreadPool);
  except
    LJob.NameDone.SetEvent;
    LJob.Done.SetEvent;
    raise;
  end;
end;

function TTgBotCore.FinishStartJob(AWaitMs: Cardinal): Boolean;
var
  LJob: TTgStartJob;
  LJobRef: IInterface;
  LPump: Boolean;
begin
  LJob := CurrentStartJob(LJobRef);
  if not Assigned(LJob) then
    Exit(True);
  LPump := TThread.CurrentThread.ThreadID = MainThreadID;
  Result := LJob.WaitDone(AWaitMs, LPump);
  if not Result then
  begin
    LJob.CancelSource.Cancel;
    Result := LJob.WaitDone(100, LPump);
  end;
  FLock.Enter;
  try
    if FStartJob = LJob then
    begin
      FStartJob := nil;
      FStartJobRef := nil;
    end;
  finally
    FLock.Leave;
  end;
end;

function TTgBotCore.ParseCommand(AContext: TTgContext): Boolean;
var
  LText, LToken, LName, LBot: string;
  LEnd, LAt: Integer;
begin
  Result := False;
  LText := AContext.MessageText;
  if (Length(LText) < 2) or (LText[1] <> '/') then
    Exit;
  // Команда — до первого пробельного символа: '/name[@bot] аргументы'.
  LEnd := 2;
  while (LEnd <= Length(LText)) and (LText[LEnd] > ' ') do
    Inc(LEnd);
  LToken := Copy(LText, 2, LEnd - 2);
  LAt := Pos('@', LToken);
  if LAt > 0 then
  begin
    LName := Copy(LToken, 1, LAt - 1);
    LBot := Copy(LToken, LAt + 1, MaxInt);
  end
  else
  begin
    LName := LToken;
    LBot := '';
  end;
  if LName = '' then
    Exit;
  // username в Telegram без учёта регистра (латиница, цифры, '_').
  if (LBot <> '') and not SameText(LBot, ResolveBotUserName(AContext.FCancel)) then
    Exit;
  AContext.FCommand := AnsiLowerCase(LName);
  AContext.FArgs := Trim(Copy(LText, LEnd, MaxInt));
  Result := True;
end;

procedure TTgBotCore.RouteMessage(AContext: TTgContext; const ARoutes: TTgRoutes;
  AIsCommand: Boolean);
var
  LRef: ITgContext;
  LText, LLower, LCommandArgs, LArgs: string;
  LRoute: TTgRoute;
  LMatch: TTgMatchRoute;
  LFound: Boolean;

  // Вызов обработчика правила; True — обработано (обработчик не сбросил Handled).
  function Fire(const AHandler: TProc<ITgContext>; const AArgs: string): Boolean;
  begin
    AContext.FArgs := AArgs;
    AContext.FHandled := True;
    AHandler(LRef);
    Result := AContext.FHandled;
  end;

begin
  LRef := AContext;
  LCommandArgs := AContext.FArgs;
  if AIsCommand then
  begin
    LFound := False;
    for LRoute in ARoutes.Lists[TTgRouteKind.Command] do
      if LRoute.Key = AContext.FCommand then
      begin
        LFound := True;
        if Fire(LRoute.Handler, LCommandArgs) then
          Exit;
        Break;
      end;
    if not LFound and Assigned(ARoutes.UnknownCommand) and
      Fire(ARoutes.UnknownCommand, LCommandArgs) then
      Exit;
  end;
  LText := AContext.MessageText;
  if LText = '' then
    Exit;
  LLower := AnsiLowerCase(LText);
  for LRoute in ARoutes.Lists[TTgRouteKind.Text] do
    if LRoute.Key = LLower then
    begin
      if Fire(LRoute.Handler, LCommandArgs) then
        Exit;
      Break;
    end;
  for LMatch in ARoutes.Matches do
    if LMatch.Matcher.TryMatch(LText, LArgs) and Fire(LMatch.Handler, LArgs) then
      Exit;
  if Assigned(ARoutes.AnyText) then
    Fire(ARoutes.AnyText, LCommandArgs);
end;

procedure TTgBotCore.RouteCallback(AContext: TTgContext; const ARoutes: TTgRoutes);
var
  LRef: ITgContext;
  LData: string;
  LRoute: TTgRoute;

  function Fire(const AHandler: TProc<ITgContext>; const AArgs: string): Boolean;
  begin
    AContext.FArgs := AArgs;
    AContext.FHandled := True;
    AHandler(LRef);
    Result := AContext.FHandled;
  end;

begin
  LRef := AContext;
  LData := AContext.GetData;
  if LData = '' then
    Exit;
  for LRoute in ARoutes.Lists[TTgRouteKind.Callback] do
    if LRoute.Key = LData then
    begin
      if Fire(LRoute.Handler, '') then
        Exit;
      Break;
    end;
  for LRoute in ARoutes.Lists[TTgRouteKind.CallbackPrefix] do
    if (Copy(LData, 1, Length(LRoute.Key)) = LRoute.Key) and
      Fire(LRoute.Handler, Copy(LData, Length(LRoute.Key) + 1, MaxInt)) then
      Exit;
end;

procedure TTgBotCore.HandleRaw(const AUpdate: ITgRawUpdate);
var
  LContext: TTgContext;
  LRef: ITgContext;
  LOnUpdate, LOnMessage, LOnCallbackQuery: TProc<ITgContext>;
  LStorage: ITgStateStorage;
  LAutoAnswer: Boolean;
  LRoutes: TTgRoutes;
  LIsCommand: Boolean;
begin
  // Снимок обработчиков и хранилища: их можно переназначать на ходу из
  // другого потока, а локальные ссылки удерживают замыкания до конца вызова.
  FLock.Enter;
  try
    if FDetached then
      Exit;
    LOnUpdate := FOnUpdate;
    LOnMessage := FOnMessage;
    LOnCallbackQuery := FOnCallbackQuery;
    LStorage := FStateStorage;
    LAutoAnswer := FAutoAnswerCallbacks;
    LRoutes := FRoutes;
  finally
    FLock.Leave;
  end;
  // Токен диспетчера — окружающий токен обработчика; контекст удерживает ядро.
  LContext := TTgContext.Create(Self, FApi, AUpdate, TTgCancelScope.Current, LStorage);
  LRef := LContext;
  try
    // Команда разбирается до OnUpdate: ACtx.Command доступен и в нём.
    LIsCommand := (AUpdate.Kind = TTgUpdateType.Message) and ParseCommand(LContext);
    if Assigned(LOnUpdate) then
      LOnUpdate(LRef);
    // OnUpdate может перехватить обновление (ACtx.Handled := True).
    if not LContext.FHandled then
    begin
      if AUpdate.Kind = TTgUpdateType.Message then
      begin
        RouteMessage(LContext, LRoutes, LIsCommand);
        // OnMessage — только если ни одно правило не обработало сообщение.
        if not LContext.FHandled and Assigned(LOnMessage) then
          LOnMessage(LRef);
      end
      else if AUpdate.Kind = TTgUpdateType.CallbackQuery then
      begin
        RouteCallback(LContext, LRoutes);
        if not LContext.FHandled and Assigned(LOnCallbackQuery) then
          LOnCallbackQuery(LRef);
      end;
    end;
  except
    on E: Exception do
      NotifyError(E, LRef);
  end;
  // Неотвеченное нажатие кнопки: иначе у пользователя «крутится» индикатор.
  // После Free бота (Detach) автоответ не отправляется.
  if LAutoAnswer and (AUpdate.Kind = TTgUpdateType.CallbackQuery) and
    not LContext.Answered and not (Assigned(LRef.Cancel) and LRef.Cancel.IsCancelled) and
    not Detached then
    try
      LRef.Answer;
    except
      on E: Exception do
        NotifyError(E, LRef);
    end;
end;

procedure TTgBot.Start;
var
  LCore: TTgBotCore;
  LCoreIntf: ITgBotCore;
  LGeneration: Integer;
begin
  // Из OnFault/OnError отказа: прежний запуск ещё не освобождён (его поток —
  // текущий), а FStarted мог быть ещё не выставлен вызвавшим Start потоком.
  if GTgInFaultNotify then
    raise ETgError.Create(TgUpdatesText(TTgUpdatesText.StopFromHandler));
  LCore := TTgBotCore(FCore);
  if FStarted then
  begin
    if LCore.GetState <> TTgBotState.Faulted then
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
    FSource.AllowedUpdates := TTgOptionalStrings.Create(nil);
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
  LGeneration := LCore.BeginRun;
  LCoreIntf := LCore;
  FSource.OnFault := NewFaultHandler(LCoreIntf, LGeneration);
  FWebhookSource.OnFault := NewFaultHandler(LCoreIntf, LGeneration);
  try
    FDispatcher.Start;
    try
      FActiveSource.Start(FDispatcherRef);
    except
      FDispatcher.Stop(TgDefaultDrainTimeoutMs);
      raise;
    end;
  except
    LCore.SetState(TTgBotState.Idle);
    // Фоновая подготовка не переживает неудачный запуск.
    LCore.FinishStartJob(0);
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
  if TTgUpdateDispatcher.InHandler or GTgInFaultNotify then
    raise ETgError.Create(TgUpdatesText(TTgUpdatesText.StopFromHandler));
  if not FStarted then
    Exit(True);
  TTgBotCore(FCore).SetState(TTgBotState.Stopping);
  LWatch := TStopwatch.StartNew;
  // Сначала источник: он дожидается обработки принятого (дренаж) и подтверждает offset.
  // В Faulted поток источника уже завершён — остаётся дренаж диспетчера.
  // Webhook: Accept сразу отвечает Unavailable, затем deleteWebhook (DeleteWebhookOnStop).
  Result := FActiveSource.Stop(AWaitMs);
  // Фоновые getMe/setMyCommands: дожидаемся (меню отправляется и при быстром
  // Stop), по истечении времени — отмена. Обработчики, ждущие getMe, к этому
  // моменту дождутся его завершения или отмены.
  LLeft := Max(Int64(AWaitMs) - LWatch.ElapsedMilliseconds, 100);
  if not TTgBotCore(FCore).FinishStartJob(Cardinal(LLeft)) then
    Result := False;
  LLeft := Max(Int64(AWaitMs) - LWatch.ElapsedMilliseconds, 100);
  if not FDispatcher.Stop(Cardinal(LLeft)) then
    Result := False;
  FStarted := False;
  TTgBotCore(FCore).SetState(TTgBotState.Idle);
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
