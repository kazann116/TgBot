unit TgBot.Base;

{
  TgBot — библиотека Telegram Bot API для Delphi.
  Базовые типы ядра: опциональные значения, идентификатор чата, входной файл,
  исключения, локализация сообщений (RU/EN) и токены отмены
  (ITgCancellation, ITgCancellationSource, TTgCancellationSource, TTgCancelScope).

  Модуль использует только RTL и компилируется под Win32, Win64, Linux64,
  Android/Android64. Минимальная версия Delphi — 10.4 Sydney.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.Classes,
  System.SyncObjs,
  System.Generics.Collections,
  System.JSON;

const
  /// <summary>Название библиотеки.</summary>
  TgBotLibName = 'TgBot';
  /// <summary>Старший номер версии библиотеки.</summary>
  TgBotVersionMajor = 0;
  /// <summary>Младший номер версии библиотеки.</summary>
  TgBotVersionMinor = 5;
  /// <summary>Номер выпуска библиотеки.</summary>
  TgBotVersionRelease = 0;
  /// <summary>Версия библиотеки строкой.</summary>
  TgBotVersion = '0.5.0';
  /// <summary>Значение заголовка User-Agent по умолчанию.</summary>
  TgBotUserAgent = TgBotLibName + '-Delphi/' + TgBotVersion;

type
  /// <summary>
  ///   Язык сообщений библиотеки (текстов исключений); по умолчанию — En
  ///   (TgSetLanguage).
  /// </summary>
  TTgLanguage = (Ru, En);

  /// <summary>Идентификаторы локализуемых текстов библиотеки.</summary>
  TTgText = (
    TokenRequired,
    OptionalEmpty,
    ChatIdEmpty,
    ChatIdNotNumeric,
    InputFileEmpty,
    InputFileNotUpload,
    InputFileStreamNil,
    LocalPathNotAbsolute,
    ParamNameEmpty,
    InvalidJson,
    ApiError,
    NetworkError,
    InvalidResponse,
    UnexpectedResult,
    Cancelled,
    FilePathEmpty,
    FilePathInvalid,
    DownloadFailed,
    TransportRequired,
    Conflict,
    ClientClosed,
    ViaProxy
  );

  /// <summary>
  ///   Подключаемый переводчик сообщений библиотеки (TgSetTranslator).
  ///   Ключ (msgid в стиле gettext) — английский текст сообщения до
  ///   подстановки аргументов Format, то есть LoadResString(SEn…) из
  ///   TgBot.Consts. Если приложение локализовано ресурсными DLL (ITE,
  ///   LoadResourceModule), строка SEn… уже переведена и ключ — не английский
  ///   текст: используйте либо ITE, либо переводчик.
  ///   Перевод текста с форматированием (TgTextFmt, TgLangTextFmt) должен
  ///   использовать те же аргументы Format, что и ключ: совпадают множество
  ///   индексов аргументов и тип каждого. Индекс — явный (%1:s; %:s — 0) или
  ///   следующий за предыдущим; '*' в ширине или точности тоже берёт
  ///   аргумент. Тип — буква спецификатора без учёта регистра (d, u и x —
  ///   разные типы), у '*' — свой тип '*'. Порядок, повторы индекса, ширина,
  ///   точность, '-' и '%%' не сравниваются: перестановка через явные индексы
  ///   (%1:s … %0:d) допустима. Иначе (аргументов меньше или больше, другой
  ///   тип, неизвестная буква, незавершённый спецификатор) — встроенный текст.
  ///   Перевод текста без форматирования (TgText, TgLangText) отдаётся как
  ///   есть, без Format: '%' в нём — литерал, '%%' не сокращается до '%'
  ///   (литерал '%%' нужен только в строках формата). Перевод применяется
  ///   при любом языке TgSetLanguage; нет перевода (False или пустая
  ///   строка) — встроенный текст на текущем языке.
  ///   Реализация должна быть потокобезопасной: TryTranslate вызывается из
  ///   любых потоков одновременно (лучше — неизменяемый словарь, заполненный
  ///   до TgSetTranslator). Исключения TryTranslate, кроме EOutOfMemory,
  ///   поглощаются библиотекой — используется встроенный текст (в сборке с
  ///   DEBUG на Windows исключение, кроме EAbort, пишется в
  ///   OutputDebugString); EOutOfMemory передаётся вызывающему.
  /// </summary>
  ITgTranslator = interface
    ['{607EC7D6-C799-4FFD-8AD4-F401F7EFDC0B}']
    /// <summary>
    ///   True и перевод в AText — перевод ключа AMsgId найден;
    ///   False — перевода нет.
    /// </summary>
    function TryTranslate(const AMsgId: string; out AText: string): Boolean;
  end;

  /// <summary>Базовое исключение библиотеки.</summary>
  ETgError = class(Exception);

  /// <summary>
  ///   Ошибка, возвращённая Telegram Bot API (ответ с ok = false).
  /// </summary>
  ETgApiError = class(ETgError)
  private
    FMethod: string;
    FErrorCode: Integer;
    FDescription: string;
    FRetryAfter: Integer;
    FMigrateToChatId: Int64;
  public
    /// <summary>Создаёт исключение с локализованным текстом.</summary>
    constructor Create(const AMethod: string; AErrorCode: Integer;
      const ADescription: string; ARetryAfter: Integer = 0;
      AMigrateToChatId: Int64 = 0);
    /// <summary>Имя метода Bot API, вызвавшего ошибку.</summary>
    property Method: string read FMethod;
    /// <summary>Код ошибки (error_code), обычно совпадает с HTTP-статусом.</summary>
    property ErrorCode: Integer read FErrorCode;
    /// <summary>Текст ошибки от Telegram (description), не переводится.</summary>
    property Description: string read FDescription;
    /// <summary>parameters.retry_after — сколько секунд ждать (для 429), иначе 0.</summary>
    property RetryAfter: Integer read FRetryAfter;
    /// <summary>parameters.migrate_to_chat_id — новый id супергруппы, иначе 0.</summary>
    property MigrateToChatId: Int64 read FMigrateToChatId;
  end;

  /// <summary>
  ///   Ошибка 409 (Conflict): обычно запущен второй экземпляр бота с тем же
  ///   токеном (параллельный getUpdates) или для getUpdates установлен webhook.
  /// </summary>
  ETgConflictError = class(ETgApiError)
  public
    /// <summary>Создаёт исключение с локализованным текстом-подсказкой.</summary>
    constructor Create(const AMethod: string; AErrorCode: Integer;
      const ADescription: string; ARetryAfter: Integer = 0;
      AMigrateToChatId: Int64 = 0);
  end;

  /// <summary>
  ///   Сетевая ошибка: нет соединения, таймаут, некорректный (не JSON) ответ.
  ///   Токен бота в текст сообщения не попадает.
  /// </summary>
  ETgNetworkError = class(ETgError)
  private
    FStatusCode: Integer;
    FMethod: string;
  public
    /// <summary>
    ///   Создаёт исключение; AStatusCode = 0, если HTTP-ответа не было.
    ///   AMethod — метод Bot API (или 'downloadFile'), при котором возникла ошибка.
    /// </summary>
    constructor Create(const AMessage: string; AStatusCode: Integer = 0;
      const AMethod: string = '');
    /// <summary>HTTP-статус ответа или 0, если ответ не получен.</summary>
    property StatusCode: Integer read FStatusCode;
    /// <summary>Метод Bot API (или 'downloadFile'); пусто, если не известен.</summary>
    property Method: string read FMethod;
  end;

  /// <summary>
  ///   Операция отменена: токен отмены (ITgCancellation), уничтожение клиента
  ///   или Cancel транспорта.
  /// </summary>
  ETgCancelledError = class(ETgError);

  /// <summary>Вид ошибки для Try-вариантов методов.</summary>
  TTgErrorKind = (None, Api, Network, Cancelled, Other);

  /// <summary>
  ///   Сведения об ошибке для Try-вариантов методов (без владения объектом исключения).
  /// </summary>
  TTgErrorInfo = record
    /// <summary>Вид ошибки.</summary>
    Kind: TTgErrorKind;
    /// <summary>Текст сообщения исключения.</summary>
    Message: string;
    /// <summary>Имя класса исключения.</summary>
    ExceptionClassName: string;
    /// <summary>Метод Bot API, вызвавший ошибку (для Kind = Api и Network), иначе пусто.</summary>
    Method: string;
    /// <summary>Исходный текст ошибки Telegram (description) для Kind = Api, иначе пусто.</summary>
    Description: string;
    /// <summary>Код ошибки Bot API (для Kind = Api) или HTTP-статус (для Network).</summary>
    ErrorCode: Integer;
    /// <summary>retry_after для ошибки 429, иначе 0.</summary>
    RetryAfter: Integer;
    /// <summary>migrate_to_chat_id, иначе 0.</summary>
    MigrateToChatId: Int64;
    /// <summary>Сведения об отсутствии ошибки.</summary>
    class function Empty: TTgErrorInfo; static;
    /// <summary>Заполняет сведения по объекту исключения.</summary>
    class function FromException(AError: Exception): TTgErrorInfo; static;
  end;

  /// <summary>
  ///   Токен отмены операции. Потокобезопасен. Создаётся через
  ///   TTgCancellationSource.New; nil вместо токена означает «без отмены».
  /// </summary>
  ITgCancellation = interface
    ['{8AF185BD-7206-4ACD-BCFE-7E817DF1B868}']
    /// <summary>Отмена запрошена.</summary>
    function IsCancelled: Boolean;
    /// <summary>Выбрасывает ETgCancelledError, если отмена запрошена.</summary>
    procedure ThrowIfCancelled;
    /// <summary>
    ///   Ждёт отмены не дольше AMs мс (INFINITE — без ограничения).
    ///   True — отмена запрошена, False — истёк таймаут.
    /// </summary>
    function WaitFor(AMs: Cardinal): Boolean;
    /// <summary>
    ///   Подписывает ACallback на отмену. Колбэк вызывается один раз в потоке,
    ///   вызвавшем Cancel (вне внутренней блокировки), исключения колбэка
    ///   поглощаются. Освобождение возвращённой ссылки снимает подписку, но
    ///   колбэк, уже скопированный идущим в другом потоке Cancel, может быть
    ///   вызван и после этого. Объекты, нужные колбэку, держите в самом
    ///   колбэке (интерфейсной ссылкой) или защищайте флагом. Колбэк не должен
    ///   ждать освобождения этого же источника или его родителя (возможна
    ///   взаимоблокировка). В частности, колбэк дочернего (связанного)
    ///   источника не должен ждать поток, который этот источник освобождает:
    ///   пока идёт отмена от родителя (вместе с колбэками ребёнка), деструктор
    ///   ребёнка ждёт её завершения. Если отмена уже запрошена, колбэк
    ///   вызывается сразу в текущем потоке и возвращается nil.
    /// </summary>
    function Register(const ACallback: TProc): IInterface;
  end;

  /// <summary>
  ///   Источник отмены: токен ITgCancellation с правом запросить отмену.
  ///   Создаётся через TTgCancellationSource.New; храните ссылку только как
  ///   ITgCancellationSource, а потребителям отдавайте как ITgCancellation.
  /// </summary>
  ITgCancellationSource = interface(ITgCancellation)
    ['{6E1AD13D-1A08-4B32-9C7B-2948B7FCBEB4}']
    /// <summary>
    ///   Запрашивает отмену. Идемпотентно: повторные вызовы ничего не делают.
    ///   Колбэки подписчиков вызываются в текущем потоке вне блокировки.
    /// </summary>
    procedure Cancel;
  end;

  /// <summary>
  ///   Служебный интерфейс подписок TTgCancellationSource: через него подписка
  ///   (результат Register) снимает свой колбэк при освобождении. В прикладном
  ///   коде не нужен.
  /// </summary>
  ITgCancelRegistry = interface
    ['{0D8864BB-2140-4DEC-88B8-A8A061EEF8F7}']
    /// <summary>Снимает колбэк с идентификатором AId (если он ещё не вызван).</summary>
    procedure Unregister(AId: Int64);
  end;

  /// <summary>
  ///   Источник отмены: владелец токена ITgCancellation (сам реализует его).
  ///   Создавайте через New и храните как ITgCancellationSource; не храните
  ///   ссылку на класс (объект живёт по счётчику ссылок интерфейсов).
  ///   Связанный источник (AParent) отменяется вместе с родителем; подписка
  ///   на родителя снимается в деструкторе — циклов ссылок нет. Подписки
  ///   (Register) удерживают источник до своего освобождения; источник
  ///   хранит только колбэки с идентификаторами, а не сами подписки.
  /// </summary>
  TTgCancellationSource = class(TInterfacedObject, ITgCancellation,
    ITgCancellationSource, ITgCancelRegistry)
  private type
    /// <summary>Колбэк подписчика и идентификатор его подписки.</summary>
    TCallbackEntry = record
      Id: Int64;
      Callback: TProc;
    end;
  private
    FLock: TCriticalSection;
    FCancelled: Integer;
    FEvent: TEvent;
    FCallbacks: TList<TCallbackEntry>;
    FLastId: Int64;
    FLink: IInterface;
    FParentLinks: TArray<IInterface>;
    procedure LinkParent(const AParent: ITgCancellation);
    { ITgCancelRegistry }
    procedure Unregister(AId: Int64);
    /// <summary>Источник, связанный с двумя родителями (любой может быть nil).</summary>
    constructor CreateLinked(const AParentA, AParentB: ITgCancellation);
  public
    /// <summary>
    ///   Создаёт источник; при заданном AParent — связанный: отмена родителя
    ///   отменяет и этот источник (если родитель уже отменён — сразу).
    ///   Предпочтительно создавать через New.
    /// </summary>
    constructor Create(const AParent: ITgCancellation = nil);
    destructor Destroy; override;
    /// <summary>
    ///   Создаёт источник (при заданном AParent — связанный, как Create)
    ///   и возвращает его как ITgCancellationSource. Колбэк Register не
    ///   должен ждать освобождения этого же источника или его родителя
    ///   (возможна взаимоблокировка). Для связанного источника это значит:
    ///   его колбэк не должен ждать поток, который источник освобождает, —
    ///   деструктор ждёт завершения идущей от родителя отмены, а та ждёт
    ///   колбэк.
    /// </summary>
    class function New(const AParent: ITgCancellation = nil): ITgCancellationSource; static;
    /// <summary>
    ///   Токен, отменяемый при отмене любого из A и B. Если один из них nil
    ///   (или A = B) — возвращается другой без создания источника; оба nil — nil.
    /// </summary>
    class function Linked(const A, B: ITgCancellation): ITgCancellation; static;
    /// <summary>
    ///   Запрашивает отмену. Идемпотентно: повторные вызовы ничего не делают.
    ///   Колбэки подписчиков вызываются в текущем потоке вне блокировки.
    /// </summary>
    procedure Cancel;
    function IsCancelled: Boolean;
    procedure ThrowIfCancelled;
    function WaitFor(AMs: Cardinal): Boolean;
    function Register(const ACallback: TProc): IInterface;
  end;

  /// <summary>
  ///   Служебная связь замыканий и очереди главного потока с компонентом
  ///   (TComponent — без счётчика ссылок): замыкания удерживают связь, а не
  ///   компонент. Owner читается атомарно из любого потока; компонент
  ///   вызывает Clear первым действием деструктора, после чего Owner = nil.
  ///   Приведение Owner к классу компонента безопасно, пока выполняется
  ///   код, уже получивший не-nil до Clear, и компонент ждёт его завершения
  ///   (или такой код работает в главном потоке). Создаётся TgNewOwnerLink.
  ///   В прикладном коде не нужна.
  /// </summary>
  ITgOwnerLink = interface
    ['{9C23CB35-37BE-4871-82D0-7E5A33750D8C}']
    /// <summary>Владелец связи; nil после Clear. Атомарное чтение.</summary>
    function Owner: TObject;
    /// <summary>Отцепляет владельца (атомарно); повторный вызов ничего не делает.</summary>
    procedure Clear;
  end;

  /// <summary>
  ///   Окружающий токен отмены текущего потока. Вызовы клиента Bot API без
  ///   явного токена используют TTgCancelScope.Current. Области вложенные:
  ///   Leave восстанавливает предыдущий токен. Используйте строго парами
  ///   в одном потоке:
  ///     LScope := TTgCancelScope.Enter(LToken);
  ///     try ... finally LScope.Leave; end;
  ///   Запись не копируйте; Enter(nil) отключает окружающую отмену в области.
  /// </summary>
  TTgCancelScope = record
  private
    FToken: ITgCancellation;
    FPrevious: Pointer;
    // Признак входа — управляемое поле: неинициализированная запись неактивна.
    FActive: string;
  public
    /// <summary>Делает AToken окружающим токеном текущего потока.</summary>
    class function Enter(const AToken: ITgCancellation): TTgCancelScope; static;
    /// <summary>Восстанавливает предыдущий токен; повторный вызов ничего не делает.</summary>
    procedure Leave;
    /// <summary>Окружающий токен текущего потока или nil.</summary>
    class function Current: ITgCancellation; static;
  end;

  /// <summary>
  ///   Опциональное значение. Неинициализированная переменная всегда пуста:
  ///   признак наличия хранится в управляемом поле (строке), которое
  ///   компилятор обнуляет автоматически.
  /// </summary>
  TTgOptional<T> = record
  private
    FValue: T;
    FHasValue: string;
    function GetHasValue: Boolean;
    function GetValue: T;
  public
    /// <summary>Создаёт значение, в котором задано AValue.</summary>
    constructor Create(const AValue: T);
    /// <summary>Пустое значение.</summary>
    class function Empty: TTgOptional<T>; static;
    /// <summary>Сбрасывает значение.</summary>
    procedure Clear;
    /// <summary>Значение или Default(T), если оно не задано.</summary>
    function ValueOrDefault: T; overload;
    /// <summary>Значение или ADefault, если оно не задано.</summary>
    function ValueOrDefault(const ADefault: T): T; overload;
    /// <summary>Неявное создание из значения: LOpt := 5;</summary>
    class operator Implicit(const AValue: T): TTgOptional<T>;
    /// <summary>Явное получение значения: T(LOpt). Пустое — ETgError.</summary>
    class operator Explicit(const AValue: TTgOptional<T>): T;
    /// <summary>Признак наличия значения.</summary>
    property HasValue: Boolean read GetHasValue;
    /// <summary>Значение; если не задано — ETgError.</summary>
    property Value: T read GetValue;
  end;

  /// <summary>
  ///   Идентификатор чата: число (Int64) или '@username' канала/супергруппы.
  ///   Неинициализированная переменная пуста (IsEmpty).
  /// </summary>
  TTgChatId = record
  private
    FValue: string;
  public
    /// <summary>Создаёт из числового идентификатора.</summary>
    class function FromId(AId: Int64): TTgChatId; static;
    /// <summary>Создаёт из имени; '@' добавляется при отсутствии.</summary>
    class function FromUsername(const AUsername: string): TTgChatId; static;
    /// <summary>LChat := 123456;</summary>
    class operator Implicit(AId: Int64): TTgChatId;
    /// <summary>
    ///   LChat := '@channel'; строка из цифр ('-100123') трактуется как число,
    ///   иначе как username ('@' добавляется при отсутствии).
    /// </summary>
    class operator Implicit(const AValue: string): TTgChatId;
    /// <summary>Идентификатор не задан.</summary>
    function IsEmpty: Boolean;
    /// <summary>Задан числовой идентификатор.</summary>
    function IsId: Boolean;
    /// <summary>Задан '@username'.</summary>
    function IsUsername: Boolean;
    /// <summary>Числовой идентификатор; для username — ETgError.</summary>
    function Id: Int64;
    /// <summary>'@username' или пустая строка для числового идентификатора.</summary>
    function Username: string;
    /// <summary>Текстовое представление: число или '@username'.</summary>
    function ToString: string;
    /// <summary>
    ///   JSON-значение (TJSONNumber или TJSONString). Объект принадлежит
    ///   вызывающему. Пустой идентификатор — ETgError.
    /// </summary>
    function ToJson: TJSONValue;
  end;

  /// <summary>Способ передачи файла в Bot API.</summary>
  TTgInputFileKind = (
    /// <summary>Файл не задан.</summary>
    None,
    /// <summary>file_id уже загруженного в Telegram файла.</summary>
    FileId,
    /// <summary>HTTP(S)-URL, который скачает сервер Telegram.</summary>
    Url,
    /// <summary>file:// URI на диске Local Bot API server.</summary>
    LocalUri,
    /// <summary>Загрузка локального файла (multipart).</summary>
    UploadFile,
    /// <summary>Загрузка из потока (multipart), поток не владеется.</summary>
    UploadStream,
    /// <summary>Загрузка из массива байт (multipart).</summary>
    UploadBytes
  );

  /// <summary>
  ///   Входной файл для методов Bot API (InputFile или строка file_id/URL).
  ///   Создавайте только через фабрики From*.
  /// </summary>
  TTgInputFile = record
  private
    // Вид хранится в строке, чтобы неинициализированная запись была пустой.
    FKindTag: string;
    FValue: string;
    FFileName: string;
    FContentType: string;
    FBytes: TBytes;
    FStream: TStream;
    function GetKind: TTgInputFileKind;
    function GetStream: TStream;
  public
    /// <summary>file_id уже загруженного файла.</summary>
    class function FromFileId(const AFileId: string): TTgInputFile; static;
    /// <summary>HTTP(S)-URL файла.</summary>
    class function FromUrl(const AUrl: string): TTgInputFile; static;
    /// <summary>
    ///   Загрузка локального файла. Файл открывается при каждой попытке отправки.
    ///   AFileName — имя для сервера (по умолчанию имя файла из пути).
    /// </summary>
    class function FromFile(const APath: string; const AFileName: string = '';
      const AContentType: string = ''): TTgInputFile; static;
    /// <summary>
    ///   Загрузка из потока. Поток НЕ освобождается библиотекой и должен жить
    ///   до завершения вызова (включая асинхронный). Отправляется целиком,
    ///   с позиции 0; при повторе Position сбрасывается в 0.
    /// </summary>
    class function FromStream(AStream: TStream; const AFileName: string;
      const AContentType: string = ''): TTgInputFile; static;
    /// <summary>Загрузка из массива байт.</summary>
    class function FromBytes(const ABytes: TBytes; const AFileName: string;
      const AContentType: string = ''): TTgInputFile; static;
    /// <summary>
    ///   Файл на диске Local Bot API server: абсолютный путь преобразуется
    ///   в URI file://. Работает только с локальным сервером Bot API.
    /// </summary>
    class function FromLocalPath(const APath: string): TTgInputFile; static;
    /// <summary>Файл не задан.</summary>
    function IsEmpty: Boolean;
    /// <summary>Требуется загрузка содержимого (multipart/form-data).</summary>
    function IsUpload: Boolean;
    /// <summary>
    ///   Строковое значение параметра для не-загрузок (file_id, URL, file://).
    ///   Для загрузок — ETgError.
    /// </summary>
    function ToParamValue: string;
    /// <summary>Вид файла.</summary>
    property Kind: TTgInputFileKind read GetKind;
    /// <summary>file_id, URL, file:// URI или путь к локальному файлу.</summary>
    property Value: string read FValue;
    /// <summary>Имя файла для multipart.</summary>
    property FileName: string read FFileName;
    /// <summary>MIME-тип для multipart; пусто — определить по расширению.</summary>
    property ContentType: string read FContentType;
    /// <summary>Байты для Kind = UploadBytes.</summary>
    property Bytes: TBytes read FBytes;
    /// <summary>Поток для Kind = UploadStream, иначе nil.</summary>
    property Stream: TStream read GetStream;
  end;

/// <summary>
///   Устанавливает язык сообщений библиотеки (по умолчанию — английский,
///   TTgLanguage.En; до 0.5.0 — русский: прежнее поведение —
///   TgSetLanguage(TTgLanguage.Ru)). Вызывайте до запуска рабочих потоков.
/// </summary>
procedure TgSetLanguage(ALanguage: TTgLanguage);
/// <summary>Текущий язык сообщений библиотеки.</summary>
function TgGetLanguage: TTgLanguage;
/// <summary>
///   Устанавливает переводчик сообщений библиотеки (nil — без переводчика,
///   только встроенные тексты). Потокобезопасно; прежний переводчик
///   освобождается вне внутренней блокировки. Контракт — ITgTranslator.
///   Вызовите TgSetTranslator(nil) до завершения программы (в своём
///   finalization или OnDestroy), особенно если переводчик живёт в BPL/DLL —
///   иначе последний _Release переводчика выполнится в finalization
///   TgBot.Base, когда его модуль может быть уже выгружен.
/// </summary>
procedure TgSetTranslator(const ATranslator: ITgTranslator);
/// <summary>Текущий переводчик сообщений библиотеки (nil — не установлен).</summary>
function TgGetTranslator: ITgTranslator;
/// <summary>
///   Локализованный текст: перевод ITgTranslator, если есть, иначе — на
///   текущем языке.
/// </summary>
function TgText(AText: TTgText): string;
/// <summary>Локализованный текст (как TgText) с форматированием (Format).</summary>
function TgTextFmt(AText: TTgText; const AArgs: array of const): string;
/// <summary>
///   Служебное (для модулей библиотеки): текст пары ресурсных строк
///   TgBot.Consts (SRu…/SEn…): перевод ITgTranslator по ключу
///   LoadResString(AEn), если есть, иначе — на текущем языке библиотеки.
/// </summary>
function TgLangText(ARu, AEn: PResStringRec): string;
/// <summary>
///   Служебное (для модулей библиотеки): TgLangText с форматированием (Format).
///   Перевод, аргументы которого не совпадают с аргументами ключа (правила —
///   ITgTranslator), или с неверными для AArgs спецификаторами
///   (EConvertError) — форматируется встроенный текст.
/// </summary>
function TgLangTextFmt(ARu, AEn: PResStringRec; const AArgs: array of const): string;
/// <summary>
///   Строки формата A и B берут одни и те же аргументы Format по правилам
///   ITgTranslator (множество индексов и тип каждого; порядок, повторы,
///   ширина, точность и '%%' не сравниваются) — той же проверкой
///   TgLangTextFmt отбрасывает неподходящий перевод. Строки без
///   спецификаторов совпадают. False — подписи разные или у одной из строк
///   не определены (незавершённый спецификатор, неизвестная буква, разные
///   типы одного индекса, в том числе одиночный '%' — литерал пишется '%%').
///   Для загрузчиков переводов (TgBot.Po): проверка пары msgid/msgstr.
///   Потокобезопасно.
/// </summary>
function TgSameFormatSignature(const A, B: string): Boolean;
/// <summary>
///   Служебное (для компонентов библиотеки): новая связь ITgOwnerLink с
///   владельцем AOwner.
/// </summary>
function TgNewOwnerLink(AOwner: TObject): ITgOwnerLink;

implementation

uses
{$IF DEFINED(DEBUG) and DEFINED(MSWINDOWS)}
  Winapi.Windows,
{$ENDIF}
  TgBot.Consts;

const
  // Наибольший индекс аргумента в подписи спецификаторов (TgFormatSignature):
  // у ключей библиотеки аргументов единицы, больший индекс перевода заведомо
  // не совпадёт с ключом.
  CTgFormatMaxArgIndex = 255;

  // Тексты TTgText: пары ресурсных строк TgBot.Consts (SRu…, SEn…).
  CTexts: array[TTgText, TTgLanguage] of PResStringRec = (
    (@SRuTokenRequired, @SEnTokenRequired),
    (@SRuOptionalEmpty, @SEnOptionalEmpty),
    (@SRuChatIdEmpty, @SEnChatIdEmpty),
    (@SRuChatIdNotNumeric, @SEnChatIdNotNumeric),
    (@SRuInputFileEmpty, @SEnInputFileEmpty),
    (@SRuInputFileNotUpload, @SEnInputFileNotUpload),
    (@SRuInputFileStreamNil, @SEnInputFileStreamNil),
    (@SRuLocalPathNotAbsolute, @SEnLocalPathNotAbsolute),
    (@SRuParamNameEmpty, @SEnParamNameEmpty),
    (@SRuInvalidJson, @SEnInvalidJson),
    (@SRuApiError, @SEnApiError),
    (@SRuNetworkError, @SEnNetworkError),
    (@SRuInvalidResponse, @SEnInvalidResponse),
    (@SRuUnexpectedResult, @SEnUnexpectedResult),
    (@SRuCancelled, @SEnCancelled),
    (@SRuFilePathEmpty, @SEnFilePathEmpty),
    (@SRuFilePathInvalid, @SEnFilePathInvalid),
    (@SRuDownloadFailed, @SEnDownloadFailed),
    (@SRuTransportRequired, @SEnTransportRequired),
    (@SRuConflict, @SEnConflict),
    (@SRuClientClosed, @SEnClientClosed),
    (@SRuViaProxy, @SEnViaProxy)
  );

  // Внутренние метки вида TTgInputFile (см. FKindTag).
  CKindFileId = 'id';
  CKindUrl = 'url';
  CKindLocalUri = 'uri';
  CKindUploadFile = 'file';
  CKindUploadStream = 'stream';
  CKindUploadBytes = 'bytes';

var
  // Язык сообщений библиотеки (по умолчанию — английский); меняется только
  // через TgSetLanguage.
  TgBotLanguage: TTgLanguage = TTgLanguage.En;
  // Переводчик сообщений (TgSetTranslator); читается и меняется только под
  // GTranslatorLock. Замок создаётся в initialization и освобождается в
  // finalization (после него — nil: тексты без переводчика).
  GTranslator: ITgTranslator;
  GTranslatorLock: TCriticalSection;

procedure TgSetLanguage(ALanguage: TTgLanguage);
begin
  TgBotLanguage := ALanguage;
end;

function TgGetLanguage: TTgLanguage;
begin
  Result := TgBotLanguage;
end;

procedure TgSetTranslator(const ATranslator: ITgTranslator);
var
  LLock: TCriticalSection;
  LOld: ITgTranslator;
begin
  LLock := GTranslatorLock;
  if LLock = nil then
    Exit; // модуль уже финализирован
  LLock.Enter;
  try
    LOld := GTranslator;
    GTranslator := ATranslator;
  finally
    LLock.Leave;
  end;
  // LOld отпускается при выходе — вне блокировки: деструктор прежнего
  // переводчика (чужой код) не выполняется под замком.
end;

function TgGetTranslator: ITgTranslator;
var
  LLock: TCriticalSection;
  LTranslator: ITgTranslator;
begin
  LLock := GTranslatorLock;
  if LLock = nil then
    Exit(nil); // модуль уже финализирован
  LLock.Enter;
  try
    LTranslator := GTranslator;
  finally
    LLock.Leave;
  end;
  // Присваивание Result — после Leave: прежнее значение переменной
  // вызывающего освобождается вне блокировки.
  Result := LTranslator;
end;

{$IFDEF DEBUG}
// Отладочная сборка: исключение переводчика — в отладочный вывод (Windows —
// OutputDebugString; на других платформах средства в RTL нет — пропуск).
procedure TgDebugTranslatorFault(E: Exception);
begin
{$IFDEF MSWINDOWS}
  OutputDebugString(PChar(TgBotLibName + ': ITgTranslator.TryTranslate — ' +
    E.ClassName + ': ' + E.Message));
{$ENDIF}
end;
{$ENDIF}

// Перевод ресурсной строки AEn установленным переводчиком. False — нет
// переводчика, нет перевода, пустой перевод или исключение переводчика
// (кроме EOutOfMemory — оно передаётся вызывающему).
function TgTryTranslate(AEn: PResStringRec; out AText: string): Boolean;
var
  LTranslator: ITgTranslator;
begin
  AText := '';
  LTranslator := TgGetTranslator;
  if LTranslator = nil then
    Exit(False);
  try
    Result := LTranslator.TryTranslate(LoadResString(AEn), AText) and (AText <> '');
  except
    // Ошибка переводчика не должна заменять собой ошибку, текст которой
    // строится, — используется встроенный текст. Нехватку памяти встроенный
    // текст не исправит — она передаётся дальше.
    on EOutOfMemory do
      raise;
    on EAbort do
      Result := False; // «тихое» исключение — без отладочного вывода
    on E: Exception do
    begin
{$IFDEF DEBUG}
      TgDebugTranslatorFault(E);
{$ENDIF}
      Result := False;
    end;
  else
    Result := False; // исключение — не потомок Exception
  end;
  if not Result then
    AText := '';
end;

// Встроенный текст пары ресурсных строк на текущем языке библиотеки.
function TgBuiltinLangText(ARu, AEn: PResStringRec): string;
begin
  if TgBotLanguage = TTgLanguage.En then
    Result := LoadResString(AEn)
  else
    Result := LoadResString(ARu);
end;

function TgLangText(ARu, AEn: PResStringRec): string;
begin
  if not TgTryTranslate(AEn, Result) then
    Result := TgBuiltinLangText(ARu, AEn);
end;

// Подпись спецификаторов строки формата Format: символ ASignature с
// позицией Low(string) + I — тип аргумента с индексом I (буква
// спецификатора в верхнем регистре или '*' для ширины/точности '*'), пробел —
// аргумент не используется; длина — наибольший индекс + 1. Разбор повторяет
// System.SysUtils.Format: %[index:][-][width][.prec]type; index — число
// (одно ':' — индекс 0), без него — следующий аргумент после предыдущего;
// число без ':' — ширина; '*' в width и prec берёт аргумент (до значения);
// '%%' — литерал. False — подпись не определена: незавершённый спецификатор
// или неизвестная буква (Format молча обрезал бы вывод или бросил
// EConvertError), разные типы одного индекса, индекс больше
// CTgFormatMaxArgIndex.
function TgFormatSignature(const AFormat: string; out ASignature: string): Boolean;
var
  P, LEnd: PChar;
  LArg, LNumber: Integer;
  LType: Char;

  // Отмечает аргумент LArg с типом AType; False — индекс вне диапазона или
  // тот же индекс уже отмечен другим типом.
  function UseArg(AType: Char): Boolean;
  begin
    if (LArg < 0) or (LArg > CTgFormatMaxArgIndex) then
      Exit(False);
    if Length(ASignature) <= LArg then
      ASignature := ASignature + StringOfChar(' ', LArg + 1 - Length(ASignature));
    if ASignature[Low(string) + LArg] = ' ' then
      ASignature[Low(string) + LArg] := AType
    else if ASignature[Low(string) + LArg] <> AType then
      Exit(False);
    Result := True;
  end;

  // Число из цифр ASCII с позиции P; больше CTgFormatMaxArgIndex — значение
  // CTgFormatMaxArgIndex + 1 (без переполнения).
  function ReadNumber: Integer;
  begin
    Result := 0;
    while (P < LEnd) and CharInSet(P^, ['0'..'9']) do
    begin
      if Result <= CTgFormatMaxArgIndex then
        Result := Result * 10 + (Ord(P^) - Ord('0'));
      Inc(P);
    end;
    if Result > CTgFormatMaxArgIndex then
      Result := CTgFormatMaxArgIndex + 1;
  end;

  // Ширина или точность: '*' берёт аргумент, иначе — пропуск цифр.
  function ReadWidth: Boolean;
  begin
    if (P < LEnd) and (P^ = '*') then
    begin
      Inc(P);
      if not UseArg('*') then
        Exit(False);
      Inc(LArg);
    end
    else
      ReadNumber;
    Result := True;
  end;

begin
  ASignature := '';
  P := PChar(AFormat);
  LEnd := P + Length(AFormat);
  LArg := -1;
  while P < LEnd do
  begin
    if P^ <> '%' then
    begin
      Inc(P);
      Continue;
    end;
    Inc(P);
    if P >= LEnd then
      Exit(False); // '%' в конце строки
    if P^ = '%' then
    begin
      Inc(P);
      Continue;
    end;
    Inc(LArg);
    // Индекс («число:» или «:») либо ширина (число без ':').
    if CharInSet(P^, ['0'..'9']) then
    begin
      LNumber := ReadNumber;
      if (P < LEnd) and (P^ = ':') then
      begin
        Inc(P);
        LArg := LNumber;
      end;
    end
    else if P^ = ':' then
    begin
      Inc(P);
      LArg := 0;
    end;
    if (P < LEnd) and (P^ = '-') then
      Inc(P);
    if not ReadWidth then
      Exit(False);
    if (P < LEnd) and (P^ = '.') then
    begin
      Inc(P);
      if P >= LEnd then
        Exit(False);
      if not ReadWidth then
        Exit(False);
    end;
    if P >= LEnd then
      Exit(False);
    LType := P^;
    if CharInSet(LType, ['a'..'z']) then
      LType := Char(Ord(LType) - (Ord('a') - Ord('A')));
    if not CharInSet(LType, ['D', 'U', 'X', 'E', 'F', 'G', 'N', 'M', 'P', 'S']) then
      Exit(False);
    if not UseArg(LType) then
      Exit(False);
    Inc(P);
  end;
  Result := True;
end;

// Подписи спецификаторов (TgFormatSignature) A и B определены и совпадают.
function TgSameFormatSignature(const A, B: string): Boolean;
var
  LSignatureA, LSignatureB: string;
begin
  Result := TgFormatSignature(A, LSignatureA) and TgFormatSignature(B, LSignatureB) and
    (LSignatureA = LSignatureB);
end;

function TgLangTextFmt(ARu, AEn: PResStringRec; const AArgs: array of const): string;
var
  LText: string;
begin
  // Аргументы перевода сверяются с ключом: Format не бросает при лишних
  // аргументах, и перевод с меньшим их числом молча потерял бы часть.
  if TgTryTranslate(AEn, LText) and TgSameFormatSignature(LText, LoadResString(AEn)) then
  begin
    try
      Exit(Format(LText, AArgs));
    except
      on EConvertError do
        ; // спецификаторы перевода не подходят к AArgs — встроенный текст
    end;
  end;
  Result := Format(TgBuiltinLangText(ARu, AEn), AArgs);
end;

function TgText(AText: TTgText): string;
begin
  Result := TgLangText(CTexts[AText, TTgLanguage.Ru], CTexts[AText, TTgLanguage.En]);
end;

function TgTextFmt(AText: TTgText; const AArgs: array of const): string;
begin
  Result := TgLangTextFmt(CTexts[AText, TTgLanguage.Ru], CTexts[AText, TTgLanguage.En],
    AArgs);
end;

type
  /// <summary>
  ///   Слабая связь «родитель → дочерний источник»: колбэк родителя держит
  ///   связь, а не сам источник, поэтому циклов ссылок нет. Деструктор
  ///   источника отвязывает его (Detach ждёт завершения идущего Fire).
  /// </summary>
  ITgCancelLink = interface
    ['{4FAA99C9-053B-412D-B14C-CA226E70F794}']
    procedure Fire;
    procedure Detach;
  end;

  /// <summary>
  ///   Реализация ITgCancelLink. FTarget — намеренно слабая ссылка на класс
  ///   (без счётчика): сильная ссылка дала бы цикл «родитель → колбэк →
  ///   ребёнок», а [Weak]-интерфейс нельзя безопасно разыменовать, пока
  ///   деструктор цели уже идёт. Жизнь FTarget гарантирует монитор: цель
  ///   вызывает Detach первым действием деструктора.
  ///   Почему не [weak] (сверено с System.pas Delphi 10.4 и 12): RTL обнуляет
  ///   слабые ссылки только при освобождении памяти объекта — цепочка
  ///   TObject.FreeInstance → TObject.CleanupInstance → _CleanupInstance →
  ///   TInstHashMap.Destroy → TInstItem.Destroy → TInstItem.ClearWeakRefs,
  ///   то есть ПОСЛЕ деструктора. Чтение [weak]-поля в сильную ссылку — это
  ///   загрузка указателя и _AddRef (_IntfCopy), а атомарного «захватить,
  ///   если жив» (аналога TryAddRef) в RTL нет. Поэтому параллельный Fire
  ///   увидел бы не-nil и вызвал Cancel у ребёнка, деструктор которого уже
  ///   идёт или закончился. Здесь окно закрыто явно: Fire и Detach работают
  ///   под TMonitor связи, деструктор ребёнка первым действием вызывает
  ///   Detach — после него Fire видит nil, а уже идущий Fire деструктор
  ///   дожидается. А [weak] на самом поле-объекте FTarget в Delphi 10.4 и 12
  ///   (Win32/Win64) не обнуляется вовсе (см. TTgOwnerLink).
  /// </summary>
  TTgCancelLink = class(TInterfacedObject, ITgCancelLink)
  private
    // Слабая ссылка без счётчика и не [weak] (см. описание класса): живость
    // цели — TMonitor связи + Detach первым действием деструктора цели.
    FTarget: TTgCancellationSource;
  public
    constructor Create(ATarget: TTgCancellationSource);
    procedure Fire;
    procedure Detach;
  end;

  /// <summary>
  ///   Подписка на отмену: идентификатор колбэка и реестр источника.
  ///   Удерживает источник (через ITgCancelRegistry); освобождение — отписка.
  ///   Источник подписку не хранит — циклов ссылок нет.
  /// </summary>
  TTgCancelRegistration = class(TInterfacedObject)
  private
    FRegistry: ITgCancelRegistry;
    FId: Int64;
  public
    constructor Create(const ARegistry: ITgCancelRegistry; AId: Int64);
    destructor Destroy; override;
  end;

  /// <summary>
  ///   Реализация ITgOwnerLink: владелец — указатель без счётчика ссылок,
  ///   запись и чтение атомарные (Clear — из главного потока, Owner — из
  ///   рабочих потоков обработчиков).
  ///   Почему не [weak] FOwner: на ссылке-объекте [weak] в Delphi 10.4 и 12
  ///   (Win32/Win64, без ARC) не обнуляется вовсе — _InstWeakCopy в System.pas
  ///   под WEAKINSTREF, который эти компиляторы не определяют (проверено:
  ///   после Free поле остаётся не-nil). А [weak]-интерфейс RTL обнулил бы
  ///   только в TObject.FreeInstance (… → TInstItem.ClearWeakRefs), то есть
  ///   после всего деструктора компонента (TTelegramBot.Destroy), а контракт —
  ///   Owner = nil с первого действия деструктора (Clear), пока компонент
  ///   останавливает приём и ждёт обработчики. Почему не FreeNotification:
  ///   получатель обязан быть TComponent, уведомления рассылает
  ///   TComponent.Destroy (RemoveFreeNotifications) — тоже в конце
  ///   разрушения, в потоке, освобождающем компонент (главном), без
  ///   синхронизации с рабочими потоками, которые читают Owner.
  /// </summary>
  TTgOwnerLink = class(TInterfacedObject, ITgOwnerLink)
  private
    FOwner: Pointer;
  public
    constructor Create(AOwner: TObject);
    function Owner: TObject;
    procedure Clear;
  end;

threadvar
  // Окружающий токен потока (TTgCancelScope): без счётчика ссылок —
  // ссылку удерживает активная запись TTgCancelScope.
  GTgAmbientCancel: Pointer;

/// <summary>Вызывает колбэк, поглощая его исключения.</summary>
procedure InvokeQuietly(const ACallback: TProc);
begin
  try
    ACallback();
  except
    // Исключения колбэков отмены не должны прерывать Cancel/Register.
  end;
end;

/// <summary>Колбэк для подписки на родителя: захватывает только связь.</summary>
function NewLinkCallback(const ALink: ITgCancelLink): TProc;
begin
  Result :=
    procedure
    begin
      ALink.Fire;
    end;
end;

{ ETgApiError }

constructor ETgApiError.Create(const AMethod: string; AErrorCode: Integer;
  const ADescription: string; ARetryAfter: Integer; AMigrateToChatId: Int64);
begin
  inherited Create(TgTextFmt(TTgText.ApiError, [AMethod, AErrorCode, ADescription]));
  FMethod := AMethod;
  FErrorCode := AErrorCode;
  FDescription := ADescription;
  FRetryAfter := ARetryAfter;
  FMigrateToChatId := AMigrateToChatId;
end;

{ ETgConflictError }

constructor ETgConflictError.Create(const AMethod: string; AErrorCode: Integer;
  const ADescription: string; ARetryAfter: Integer; AMigrateToChatId: Int64);
begin
  inherited Create(AMethod, AErrorCode, ADescription, ARetryAfter, AMigrateToChatId);
  Message := TgTextFmt(TTgText.Conflict, [AMethod, AErrorCode, ADescription]);
end;

{ ETgNetworkError }

constructor ETgNetworkError.Create(const AMessage: string; AStatusCode: Integer;
  const AMethod: string);
begin
  inherited Create(AMessage);
  FStatusCode := AStatusCode;
  FMethod := AMethod;
end;

{ TTgErrorInfo }

class function TTgErrorInfo.Empty: TTgErrorInfo;
begin
  Result.Kind := TTgErrorKind.None;
  Result.Message := '';
  Result.ExceptionClassName := '';
  Result.Method := '';
  Result.Description := '';
  Result.ErrorCode := 0;
  Result.RetryAfter := 0;
  Result.MigrateToChatId := 0;
end;

class function TTgErrorInfo.FromException(AError: Exception): TTgErrorInfo;
begin
  Result := Empty;
  if not Assigned(AError) then
    Exit;
  Result.Message := AError.Message;
  Result.ExceptionClassName := AError.ClassName;
  if AError is ETgApiError then
  begin
    Result.Kind := TTgErrorKind.Api;
    Result.Method := ETgApiError(AError).Method;
    Result.Description := ETgApiError(AError).Description;
    Result.ErrorCode := ETgApiError(AError).ErrorCode;
    Result.RetryAfter := ETgApiError(AError).RetryAfter;
    Result.MigrateToChatId := ETgApiError(AError).MigrateToChatId;
  end
  else if AError is ETgNetworkError then
  begin
    Result.Kind := TTgErrorKind.Network;
    Result.Method := ETgNetworkError(AError).Method;
    Result.ErrorCode := ETgNetworkError(AError).StatusCode;
  end
  else if AError is ETgCancelledError then
    Result.Kind := TTgErrorKind.Cancelled
  else
    Result.Kind := TTgErrorKind.Other;
end;

{ TTgCancelLink }

constructor TTgCancelLink.Create(ATarget: TTgCancellationSource);
begin
  inherited Create;
  FTarget := ATarget;
end;

procedure TTgCancelLink.Fire;
begin
  // Под блокировкой: деструктор цели (Detach) дождётся окончания Cancel.
  TMonitor.Enter(Self);
  try
    if Assigned(FTarget) then
      FTarget.Cancel;
  finally
    TMonitor.Exit(Self);
  end;
end;

procedure TTgCancelLink.Detach;
begin
  TMonitor.Enter(Self);
  try
    FTarget := nil;
  finally
    TMonitor.Exit(Self);
  end;
end;

{ TTgCancelRegistration }

constructor TTgCancelRegistration.Create(const ARegistry: ITgCancelRegistry;
  AId: Int64);
begin
  inherited Create;
  FRegistry := ARegistry;
  FId := AId;
end;

destructor TTgCancelRegistration.Destroy;
begin
  // Источник жив: его удерживает FRegistry (освобождается после тела деструктора).
  if Assigned(FRegistry) then
    FRegistry.Unregister(FId);
  inherited Destroy;
end;

{ TTgOwnerLink }

constructor TTgOwnerLink.Create(AOwner: TObject);
begin
  inherited Create;
  FOwner := Pointer(AOwner);
end;

function TTgOwnerLink.Owner: TObject;
begin
  Result := TObject(AtomicCmpExchange(FOwner, nil, nil));
end;

procedure TTgOwnerLink.Clear;
begin
  AtomicExchange(FOwner, nil);
end;

function TgNewOwnerLink(AOwner: TObject): ITgOwnerLink;
begin
  Result := TTgOwnerLink.Create(AOwner);
end;

{ TTgCancellationSource }

constructor TTgCancellationSource.Create(const AParent: ITgCancellation);
begin
  CreateLinked(AParent, nil);
end;

constructor TTgCancellationSource.CreateLinked(const AParentA,
  AParentB: ITgCancellation);
begin
  inherited Create;
  FLock := TCriticalSection.Create;
  FCallbacks := TList<TCallbackEntry>.Create;
  // Если родитель уже отменён, источник отменяется сразу (до возврата).
  LinkParent(AParentA);
  LinkParent(AParentB);
end;

class function TTgCancellationSource.New(
  const AParent: ITgCancellation): ITgCancellationSource;
begin
  Result := TTgCancellationSource.Create(AParent);
end;

destructor TTgCancellationSource.Destroy;
begin
  // Сначала отвязываемся: идущий от родителя Fire завершится до продолжения.
  if Assigned(FLink) then
    (FLink as ITgCancelLink).Detach;
  // Снимаем подписки на родителей (их освобождение — отписка).
  FParentLinks := nil;
  FLink := nil;
  FreeAndNil(FEvent);
  FreeAndNil(FCallbacks);
  FreeAndNil(FLock);
  inherited Destroy;
end;

procedure TTgCancellationSource.LinkParent(const AParent: ITgCancellation);
var
  LLink: ITgCancelLink;
  LRegistration: IInterface;
begin
  if not Assigned(AParent) then
    Exit;
  if not Assigned(FLink) then
    FLink := TTgCancelLink.Create(Self) as ITgCancelLink;
  LLink := FLink as ITgCancelLink;
  // Если родитель уже отменён, колбэк выполнится сразу (Cancel этого источника).
  LRegistration := AParent.Register(NewLinkCallback(LLink));
  if Assigned(LRegistration) then
    FParentLinks := FParentLinks + [LRegistration];
end;

class function TTgCancellationSource.Linked(const A,
  B: ITgCancellation): ITgCancellation;
begin
  if not Assigned(A) then
    Exit(B);
  if not Assigned(B) or (A = B) then
    Exit(A);
  Result := TTgCancellationSource.CreateLinked(A, B);
end;

procedure TTgCancellationSource.Unregister(AId: Int64);
var
  I: Integer;
begin
  FLock.Enter;
  try
    // После Cancel список пуст — колбэка там уже нет.
    for I := 0 to FCallbacks.Count - 1 do
      if FCallbacks[I].Id = AId then
      begin
        FCallbacks.Delete(I);
        Break;
      end;
  finally
    FLock.Leave;
  end;
end;

procedure TTgCancellationSource.Cancel;
var
  LCallbacks: TArray<TProc>;
  I: Integer;
begin
  FLock.Enter;
  try
    if FCancelled <> 0 then
      Exit;
    TInterlocked.Exchange(FCancelled, 1);
    if Assigned(FEvent) then
      FEvent.SetEvent;
    // Колбэки копируются: подписка может освобождаться параллельно.
    SetLength(LCallbacks, FCallbacks.Count);
    for I := 0 to FCallbacks.Count - 1 do
      LCallbacks[I] := FCallbacks[I].Callback;
    FCallbacks.Clear;
  finally
    FLock.Leave;
  end;
  for I := 0 to High(LCallbacks) do
    InvokeQuietly(LCallbacks[I]);
end;

function TTgCancellationSource.IsCancelled: Boolean;
begin
  Result := TInterlocked.CompareExchange(FCancelled, 0, 0) <> 0;
end;

procedure TTgCancellationSource.ThrowIfCancelled;
begin
  if IsCancelled then
    raise ETgCancelledError.Create(TgText(TTgText.Cancelled));
end;

function TTgCancellationSource.WaitFor(AMs: Cardinal): Boolean;
var
  LEvent: TEvent;
begin
  if IsCancelled then
    Exit(True);
  if AMs = 0 then
    Exit(False);
  // Событие создаётся лениво: большинству токенов ожидание не нужно.
  FLock.Enter;
  try
    if not Assigned(FEvent) then
      FEvent := TEvent.Create(nil, True, FCancelled <> 0, '');
    LEvent := FEvent;
  finally
    FLock.Leave;
  end;
  Result := LEvent.WaitFor(AMs) = TWaitResult.wrSignaled;
end;

function TTgCancellationSource.Register(const ACallback: TProc): IInterface;
var
  LEntry: TCallbackEntry;
begin
  Result := nil;
  if not Assigned(ACallback) then
    Exit;
  FLock.Enter;
  try
    if FCancelled = 0 then
    begin
      Inc(FLastId);
      LEntry.Id := FLastId;
      LEntry.Callback := ACallback;
      // Сначала подписка: если Add не удастся, её освобождение снимет
      // (несуществующую) запись без последствий.
      Result := TTgCancelRegistration.Create(Self, LEntry.Id);
      FCallbacks.Add(LEntry);
      Exit;
    end;
  finally
    FLock.Leave;
  end;
  // Отмена уже запрошена — вызываем сразу.
  InvokeQuietly(ACallback);
end;

{ TTgCancelScope }

class function TTgCancelScope.Enter(const AToken: ITgCancellation): TTgCancelScope;
begin
  Result.FToken := AToken;
  Result.FPrevious := GTgAmbientCancel;
  Result.FActive := '1';
  GTgAmbientCancel := Pointer(AToken);
end;

procedure TTgCancelScope.Leave;
begin
  if FActive = '' then
    Exit;
  GTgAmbientCancel := FPrevious;
  FPrevious := nil;
  FActive := '';
  FToken := nil;
end;

class function TTgCancelScope.Current: ITgCancellation;
begin
  Result := ITgCancellation(GTgAmbientCancel);
end;

{ TTgOptional<T> }

constructor TTgOptional<T>.Create(const AValue: T);
begin
  FValue := AValue;
  FHasValue := '1';
end;

class function TTgOptional<T>.Empty: TTgOptional<T>;
begin
  Result := Default(TTgOptional<T>);
end;

procedure TTgOptional<T>.Clear;
begin
  FValue := Default(T);
  FHasValue := '';
end;

function TTgOptional<T>.GetHasValue: Boolean;
begin
  Result := FHasValue <> '';
end;

function TTgOptional<T>.GetValue: T;
begin
  if FHasValue = '' then
    raise ETgError.Create(TgText(TTgText.OptionalEmpty));
  Result := FValue;
end;

function TTgOptional<T>.ValueOrDefault: T;
begin
  if FHasValue <> '' then
    Result := FValue
  else
    Result := Default(T);
end;

function TTgOptional<T>.ValueOrDefault(const ADefault: T): T;
begin
  if FHasValue <> '' then
    Result := FValue
  else
    Result := ADefault;
end;

class operator TTgOptional<T>.Implicit(const AValue: T): TTgOptional<T>;
begin
  Result := TTgOptional<T>.Create(AValue);
end;

class operator TTgOptional<T>.Explicit(const AValue: TTgOptional<T>): T;
begin
  Result := AValue.Value;
end;

{ TTgChatId }

class function TTgChatId.FromId(AId: Int64): TTgChatId;
begin
  Result.FValue := IntToStr(AId);
end;

class function TTgChatId.FromUsername(const AUsername: string): TTgChatId;
var
  LName: string;
begin
  LName := Trim(AUsername);
  if (LName <> '') and (LName[1] <> '@') then
    LName := '@' + LName;
  Result.FValue := LName;
end;

class operator TTgChatId.Implicit(AId: Int64): TTgChatId;
begin
  Result := TTgChatId.FromId(AId);
end;

class operator TTgChatId.Implicit(const AValue: string): TTgChatId;
var
  LText: string;
  LId: Int64;
begin
  LText := Trim(AValue);
  if TryStrToInt64(LText, LId) then
    Result := TTgChatId.FromId(LId)
  else
    Result := TTgChatId.FromUsername(LText);
end;

function TTgChatId.IsEmpty: Boolean;
begin
  Result := FValue = '';
end;

function TTgChatId.IsId: Boolean;
begin
  Result := (FValue <> '') and (FValue[1] <> '@');
end;

function TTgChatId.IsUsername: Boolean;
begin
  Result := (FValue <> '') and (FValue[1] = '@');
end;

function TTgChatId.Id: Int64;
begin
  if FValue = '' then
    raise ETgError.Create(TgText(TTgText.ChatIdEmpty));
  if not TryStrToInt64(FValue, Result) then
    raise ETgError.Create(TgTextFmt(TTgText.ChatIdNotNumeric, [FValue]));
end;

function TTgChatId.Username: string;
begin
  if IsUsername then
    Result := FValue
  else
    Result := '';
end;

function TTgChatId.ToString: string;
begin
  Result := FValue;
end;

function TTgChatId.ToJson: TJSONValue;
begin
  if FValue = '' then
    raise ETgError.Create(TgText(TTgText.ChatIdEmpty));
  if IsId then
    Result := TJSONNumber.Create(Id)
  else
    Result := TJSONString.Create(FValue);
end;

{ TTgInputFile }

class function TTgInputFile.FromFileId(const AFileId: string): TTgInputFile;
begin
  Result := Default(TTgInputFile);
  if AFileId = '' then
    raise ETgError.Create(TgText(TTgText.InputFileEmpty));
  Result.FKindTag := CKindFileId;
  Result.FValue := AFileId;
end;

class function TTgInputFile.FromUrl(const AUrl: string): TTgInputFile;
begin
  Result := Default(TTgInputFile);
  if AUrl = '' then
    raise ETgError.Create(TgText(TTgText.InputFileEmpty));
  Result.FKindTag := CKindUrl;
  Result.FValue := AUrl;
end;

class function TTgInputFile.FromFile(const APath, AFileName,
  AContentType: string): TTgInputFile;
begin
  Result := Default(TTgInputFile);
  if APath = '' then
    raise ETgError.Create(TgText(TTgText.InputFileEmpty));
  Result.FKindTag := CKindUploadFile;
  Result.FValue := APath;
  if AFileName <> '' then
    Result.FFileName := AFileName
  else
    Result.FFileName := ExtractFileName(APath);
  Result.FContentType := AContentType;
end;

class function TTgInputFile.FromStream(AStream: TStream; const AFileName,
  AContentType: string): TTgInputFile;
begin
  Result := Default(TTgInputFile);
  if not Assigned(AStream) then
    raise ETgError.Create(TgText(TTgText.InputFileStreamNil));
  Result.FKindTag := CKindUploadStream;
  Result.FStream := AStream;
  Result.FFileName := AFileName;
  Result.FContentType := AContentType;
end;

class function TTgInputFile.FromBytes(const ABytes: TBytes; const AFileName,
  AContentType: string): TTgInputFile;
begin
  Result := Default(TTgInputFile);
  Result.FKindTag := CKindUploadBytes;
  Result.FBytes := ABytes;
  Result.FFileName := AFileName;
  Result.FContentType := AContentType;
end;

class function TTgInputFile.FromLocalPath(const APath: string): TTgInputFile;
var
  LPath: string;
begin
  Result := Default(TTgInputFile);
  LPath := StringReplace(Trim(APath), '\', '/', [rfReplaceAll]);
  if LPath = '' then
    raise ETgError.Create(TgText(TTgText.InputFileEmpty));
  if SameText(Copy(LPath, 1, 7), 'file://') then
    Result.FValue := LPath
  else if (Length(LPath) >= 3) and (LPath[2] = ':') and (LPath[3] = '/') then
    Result.FValue := 'file:///' + LPath // диск Windows: file:///C:/dir/file
  else if LPath[1] = '/' then
    Result.FValue := 'file://' + LPath  // POSIX: file:///dir/file
  else
    raise ETgError.Create(TgTextFmt(TTgText.LocalPathNotAbsolute, [APath]));
  Result.FKindTag := CKindLocalUri;
end;

function TTgInputFile.GetKind: TTgInputFileKind;
begin
  if FKindTag = CKindFileId then
    Result := TTgInputFileKind.FileId
  else if FKindTag = CKindUrl then
    Result := TTgInputFileKind.Url
  else if FKindTag = CKindLocalUri then
    Result := TTgInputFileKind.LocalUri
  else if FKindTag = CKindUploadFile then
    Result := TTgInputFileKind.UploadFile
  else if FKindTag = CKindUploadStream then
    Result := TTgInputFileKind.UploadStream
  else if FKindTag = CKindUploadBytes then
    Result := TTgInputFileKind.UploadBytes
  else
    Result := TTgInputFileKind.None;
end;

function TTgInputFile.GetStream: TStream;
begin
  if FKindTag = CKindUploadStream then
    Result := FStream
  else
    Result := nil;
end;

function TTgInputFile.IsEmpty: Boolean;
begin
  Result := FKindTag = '';
end;

function TTgInputFile.IsUpload: Boolean;
begin
  Result := Kind in [TTgInputFileKind.UploadFile, TTgInputFileKind.UploadStream,
    TTgInputFileKind.UploadBytes];
end;

function TTgInputFile.ToParamValue: string;
begin
  if IsEmpty then
    raise ETgError.Create(TgText(TTgText.InputFileEmpty));
  if IsUpload then
    raise ETgError.Create(TgText(TTgText.InputFileNotUpload));
  Result := FValue;
end;

initialization
  GTranslatorLock := TCriticalSection.Create;

finalization
  // Сначала отпускаем переводчик (вне блокировки), затем — сам замок;
  // после этого тексты строятся без переводчика.
  TgSetTranslator(nil);
  FreeAndNil(GTranslatorLock);

end.
