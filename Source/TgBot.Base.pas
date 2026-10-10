unit TgBot.Base;

{
  TgBot — библиотека Telegram Bot API для Delphi.
  Базовые типы ядра: опциональные значения, идентификатор чата, входной файл,
  исключения, локализация сообщений (RU/EN) и токены отмены
  (ITgCancellation, TTgCancellationSource, TTgCancelScope).

  Модуль использует только RTL и компилируется под Win32, Win64, Linux64,
  Android/Android64. Минимальная версия Delphi — 10.4 Sydney.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.Classes,
  System.SyncObjs,
  System.JSON;

const
  /// <summary>Название библиотеки.</summary>
  TgBotLibName = 'TgBot';
  /// <summary>Старший номер версии библиотеки.</summary>
  TgBotVersionMajor = 0;
  /// <summary>Младший номер версии библиотеки.</summary>
  TgBotVersionMinor = 1;
  /// <summary>Номер выпуска библиотеки.</summary>
  TgBotVersionRelease = 0;
  /// <summary>Версия библиотеки строкой.</summary>
  TgBotVersion = '0.1.0';
  /// <summary>Значение заголовка User-Agent по умолчанию.</summary>
  TgBotUserAgent = TgBotLibName + '-Delphi/' + TgBotVersion;

type
  /// <summary>Язык сообщений библиотеки (текстов исключений).</summary>
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
    ClientClosed
  );

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
  ///   TTgCancellationSource; nil вместо токена означает «без отмены».
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
    ///   поглощаются. Освобождение возвращённой ссылки — отписка; колбэк,
    ///   уже начавший выполнение в другом потоке, при этом не прерывается.
    ///   Если отмена уже запрошена, колбэк вызывается сразу в текущем потоке
    ///   и возвращается nil.
    /// </summary>
    function Register(const ACallback: TProc): IInterface;
  end;

  /// <summary>
  ///   Источник отмены: владелец токена ITgCancellation (сам реализует его).
  ///   Связанный источник (AParent) отменяется вместе с родителем; подписка
  ///   на родителя снимается в деструкторе — циклов ссылок нет. Подписки
  ///   (Register) удерживают источник до своего освобождения.
  /// </summary>
  TTgCancellationSource = class(TInterfacedObject, ITgCancellation)
  private
    FLock: TCriticalSection;
    FCancelled: Integer;
    FEvent: TEvent;
    FRegistrations: TList;
    FLink: IInterface;
    FParentLinks: TArray<IInterface>;
    procedure LinkParent(const AParent: ITgCancellation);
    procedure Unregister(ARegistration: TObject);
  public
    /// <summary>
    ///   Создаёт источник; при заданном AParent — связанный: отмена родителя
    ///   отменяет и этот источник (если родитель уже отменён — сразу).
    /// </summary>
    constructor Create(const AParent: ITgCancellation = nil);
    destructor Destroy; override;
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
///   Устанавливает язык сообщений библиотеки (по умолчанию — русский).
///   Вызывайте до запуска рабочих потоков.
/// </summary>
procedure TgSetLanguage(ALanguage: TTgLanguage);
/// <summary>Текущий язык сообщений библиотеки.</summary>
function TgGetLanguage: TTgLanguage;
/// <summary>Локализованный текст на текущем языке.</summary>
function TgText(AText: TTgText): string;
/// <summary>Локализованный текст с форматированием (Format).</summary>
function TgTextFmt(AText: TTgText; const AArgs: array of const): string;

implementation

resourcestring
  SRuTokenRequired = 'Не задан токен бота';
  SEnTokenRequired = 'Bot token is not specified';
  SRuOptionalEmpty = 'Опциональное значение не задано';
  SEnOptionalEmpty = 'Optional value is not set';
  SRuChatIdEmpty = 'Идентификатор чата не задан';
  SEnChatIdEmpty = 'Chat identifier is not specified';
  SRuChatIdNotNumeric = 'Идентификатор чата "%s" не является числом';
  SEnChatIdNotNumeric = 'Chat identifier "%s" is not numeric';
  SRuInputFileEmpty = 'Файл не задан';
  SEnInputFileEmpty = 'Input file is not specified';
  SRuInputFileNotUpload = 'Файл требует загрузки и не может быть передан строкой';
  SEnInputFileNotUpload = 'Input file must be uploaded and cannot be passed as a string';
  SRuInputFileStreamNil = 'Поток для загрузки файла не задан (nil)';
  SEnInputFileStreamNil = 'Upload stream is not assigned (nil)';
  SRuLocalPathNotAbsolute = 'Путь "%s" должен быть абсолютным';
  SEnLocalPathNotAbsolute = 'Path "%s" must be absolute';
  SRuParamNameEmpty = 'Имя параметра не задано';
  SEnParamNameEmpty = 'Parameter name is not specified';
  SRuInvalidJson = 'Некорректный JSON в параметре "%s"';
  SEnInvalidJson = 'Invalid JSON in parameter "%s"';
  SRuApiError = 'Ошибка Telegram Bot API в методе %s (код %d): %s';
  SEnApiError = 'Telegram Bot API error in method %s (code %d): %s';
  SRuNetworkError = 'Сетевая ошибка при вызове %s: %s';
  SEnNetworkError = 'Network error while calling %s: %s';
  SRuInvalidResponse = 'Некорректный ответ сервера при вызове %s (HTTP %d)';
  SEnInvalidResponse = 'Invalid server response while calling %s (HTTP %d)';
  SRuUnexpectedResult = 'Неожиданный формат результата метода %s';
  SEnUnexpectedResult = 'Unexpected result format of method %s';
  SRuCancelled = 'Операция прервана';
  SEnCancelled = 'Operation cancelled';
  SRuFilePathEmpty = 'Не задан путь к файлу на сервере (file_path)';
  SEnFilePathEmpty = 'Server file path (file_path) is not specified';
  SRuFilePathInvalid = 'Недопустимый путь к файлу на сервере: "%s"';
  SEnFilePathInvalid = 'Invalid server file path: "%s"';
  SRuDownloadFailed = 'Не удалось скачать файл (HTTP %d)';
  SEnDownloadFailed = 'File download failed (HTTP %d)';
  SRuTransportRequired = 'Не задан транспорт Bot API';
  SEnTransportRequired = 'Bot API transport is not specified';
  SRuConflict = 'Конфликт в методе %s (код %d): %s. Вероятно, запущен другой ' +
    'экземпляр бота с этим токеном или для getUpdates установлен webhook';
  SEnConflict = 'Conflict in method %s (code %d): %s. Another bot instance with ' +
    'this token is probably running, or a webhook is set while using getUpdates';
  SRuClientClosed = 'Клиент Bot API уничтожается: асинхронный вызов отменён';
  SEnClientClosed = 'Bot API client is being destroyed: asynchronous call cancelled';

const
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
    (@SRuClientClosed, @SEnClientClosed)
  );

  // Внутренние метки вида TTgInputFile (см. FKindTag).
  CKindFileId = 'id';
  CKindUrl = 'url';
  CKindLocalUri = 'uri';
  CKindUploadFile = 'file';
  CKindUploadStream = 'stream';
  CKindUploadBytes = 'bytes';

var
  // Язык сообщений библиотеки; меняется только через TgSetLanguage.
  TgBotLanguage: TTgLanguage = TTgLanguage.Ru;

procedure TgSetLanguage(ALanguage: TTgLanguage);
begin
  TgBotLanguage := ALanguage;
end;

function TgGetLanguage: TTgLanguage;
begin
  Result := TgBotLanguage;
end;

function TgText(AText: TTgText): string;
begin
  Result := LoadResString(CTexts[AText, TgBotLanguage]);
end;

function TgTextFmt(AText: TTgText; const AArgs: array of const): string;
begin
  Result := Format(TgText(AText), AArgs);
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

  /// <summary>Реализация ITgCancelLink.</summary>
  TTgCancelLink = class(TInterfacedObject, ITgCancelLink)
  private
    FTarget: TTgCancellationSource;
  public
    constructor Create(ATarget: TTgCancellationSource);
    procedure Fire;
    procedure Detach;
  end;

  /// <summary>
  ///   Подписка на отмену. Удерживает источник; освобождение — отписка.
  /// </summary>
  TTgCancelRegistration = class(TInterfacedObject)
  private
    FSource: TTgCancellationSource;
    FSourceRef: IInterface;
    FCallback: TProc;
  public
    constructor Create(ASource: TTgCancellationSource; const ACallback: TProc);
    destructor Destroy; override;
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

constructor TTgCancelRegistration.Create(ASource: TTgCancellationSource;
  const ACallback: TProc);
begin
  inherited Create;
  FSource := ASource;
  FSourceRef := ASource;
  FCallback := ACallback;
end;

destructor TTgCancelRegistration.Destroy;
begin
  // Источник жив: его удерживает FSourceRef (освобождается после тела деструктора).
  if Assigned(FSource) then
    FSource.Unregister(Self);
  inherited Destroy;
end;

{ TTgCancellationSource }

constructor TTgCancellationSource.Create(const AParent: ITgCancellation);
begin
  inherited Create;
  FLock := TCriticalSection.Create;
  FRegistrations := TList.Create;
  if Assigned(AParent) then
    LinkParent(AParent);
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
  FreeAndNil(FRegistrations);
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
var
  LSource: TTgCancellationSource;
begin
  if not Assigned(A) then
    Exit(B);
  if not Assigned(B) or (A = B) then
    Exit(A);
  LSource := TTgCancellationSource.Create(A);
  Result := LSource;
  LSource.LinkParent(B);
end;

procedure TTgCancellationSource.Unregister(ARegistration: TObject);
var
  LIndex: Integer;
begin
  FLock.Enter;
  try
    // После Cancel список пуст — подписки там уже нет.
    LIndex := FRegistrations.IndexOf(ARegistration);
    if LIndex >= 0 then
      FRegistrations.Delete(LIndex);
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
    SetLength(LCallbacks, FRegistrations.Count);
    for I := 0 to FRegistrations.Count - 1 do
      LCallbacks[I] := TTgCancelRegistration(FRegistrations[I]).FCallback;
    FRegistrations.Clear;
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
  LRegistration: TTgCancelRegistration;
begin
  Result := nil;
  if not Assigned(ACallback) then
    Exit;
  FLock.Enter;
  try
    if FCancelled = 0 then
    begin
      LRegistration := TTgCancelRegistration.Create(Self, ACallback);
      Result := LRegistration;
      FRegistrations.Add(LRegistration);
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

end.
