unit TgBot.Updates.WebhookSource;

{
  TgBot — источник обновлений webhook TTgWebhookSource без собственного
  HTTP-сервера: setWebhook/deleteWebhook в служебном потоке, приём тела
  запроса из любого сервера (Accept), проверка секрета за постоянное
  время, лимит размера тела, дедупликация update_id, ограниченное ожидание
  места в очереди (полная очередь — Unavailable), генерация секрета
  криптостойким генератором ОС.

  Состояние одного запуска (ядро) скрыто за служебным интерфейсом
  ITgWebhookCore, реализация — в implementation. Источник (до следующего
  Start или Free) и служебный поток держат ядро только через этот
  интерфейс, поэтому неблокирующий деструктор может «отпустить» поток с
  висящим setWebhook/deleteWebhook.

  Пользователю достаточно uses TgBot.Updates (или TgBot): TTgWebhookSource
  и ITgWebhookSource (создание — TTgWebhookSource.New) реэкспортируются там
  псевдонимами. ITgWebhookCore — служебный, не используйте его напрямую.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.SyncObjs,
  System.Generics.Collections,
  System.JSON,
  TgBot.Base,
  TgBot.Http,
  TgBot.Updates.Types;

type
  /// <summary>
  ///   Служебное, не часть публичного API (не используйте напрямую): ядро
  ///   одного запуска TTgWebhookSource — настройки, секрет, приёмник
  ///   обновлений, токены отмены setWebhook/deleteWebhook и ожидания места
  ///   в очереди. Держат его источник (до следующего Start или Free) и
  ///   служебный поток; последний освободивший — уничтожает.
  /// </summary>
  ITgWebhookCore = interface
    ['{151DEEDB-476F-4FF3-813B-6198C8676BF1}']
    /// <summary>Тело служебного потока: setWebhook, ожидание остановки, deleteWebhook.</summary>
    procedure Run;
    /// <summary>Запрос остановки: Accept отвечает Unavailable, ждущие места в очереди освобождаются.</summary>
    procedure RequestStop;
    /// <summary>Отменяет висящие setWebhook/deleteWebhook.</summary>
    procedure CancelCalls;
    /// <summary>Поток отпущен: deleteWebhook не выполняется, состояние — Idle.</summary>
    procedure Abandon;
    /// <summary>Состояние запуска.</summary>
    function State: TTgSourceState;
    /// <summary>Секрет совпал (сравнение за постоянное время) или не задан.</summary>
    function CheckSecret(const AHeader: string): Boolean;
    /// <summary>В очередь (только в Running) с ожиданием не дольше PostTimeoutMs; False — не принято.</summary>
    function Post(const AUpdate: ITgRawUpdate): Boolean;
    /// <summary>RequestStop уже вызван.</summary>
    function IsStopRequested: Boolean;
    function GetMaxBodySize: Integer;
    function GetDone: TEvent;
    /// <summary>Наибольший размер тела, байт UTF-8 (не меньше 1).</summary>
    property MaxBodySize: Integer read GetMaxBodySize;
    /// <summary>Служебный поток завершил Run.</summary>
    property Done: TEvent read GetDone;
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
    ///   Этот же источник как приёмник тела webhook-запроса (для HTTP-сервера
    ///   приложения). Держит источник, как и сам интерфейс.
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
  ///
  ///   Создавайте через New и храните как ITgWebhookSource; не храните
  ///   ссылку на класс (объект освобождается по счётчику ссылок).
  /// </summary>
  TTgWebhookSource = class(TInterfacedObject, ITgUpdateSource, ITgWebhookReceiver, ITgWebhookSource)
  private
    FLock: TCriticalSection;
    FTransport: ITgTransport;
    FParentCancel: ITgCancellation;
    // Ядро текущего (или последнего) запуска, под FLock; nil — Start не вызывался.
    FCore: ITgWebhookCore;
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
    function CurrentCore: ITgWebhookCore;
    /// <summary>Разобранное тело AJson (во владении метода) — в очередь ядра ACore.</summary>
    function Deliver(const ACore: ITgWebhookCore; AJson: TJSONObject): TTgWebhookResult;
    /// <summary>Проверки до разбора тела: состояние и секрет.</summary>
    function Admit(out ACore: ITgWebhookCore; const ASecretHeader: string): TTgWebhookResult;
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
  public
    /// <summary>
    ///   Источник поверх транспорта ATransport (тот же, что у TTgApi): через
    ///   него идут setWebhook и deleteWebhook. Вызовы прерываются и отменой
    ///   AParentCancel (например, TTgApi.CancelToken). Предпочтительно
    ///   создавать через New.
    /// </summary>
    constructor Create(const ATransport: ITgTransport; const AParentCancel: ITgCancellation = nil);
    /// <summary>
    ///   Создаёт источник (параметры — как у Create) и возвращает его как
    ///   ITgWebhookSource. Создавайте через New и храните как интерфейс;
    ///   не храните ссылку на класс.
    /// </summary>
    class function New(const ATransport: ITgTransport;
      const AParentCancel: ITgCancellation = nil): ITgWebhookSource; static;
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
    /// <summary>Этот же источник как приёмник тела webhook-запроса (ITgWebhookReceiver).</summary>
    function Receiver: ITgWebhookReceiver;
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
    property Url: string read GetUrl write SetUrl;
    /// <summary>
    ///   secret_token: Telegram присылает его в заголовке
    ///   X-Telegram-Bot-Api-Secret-Token, Accept сверяет. Пусто — не
    ///   передаётся и не проверяется (TTgBot всегда задаёт значение).
    /// </summary>
    property SecretToken: string read GetSecretToken write SetSecretToken;
    /// <summary>max_connections (1–100); 0 — не передаётся (значение сервера, 40).</summary>
    property MaxConnections: Integer read GetMaxConnections write SetMaxConnections;
    /// <summary>drop_pending_updates setWebhook: пропустить накопившиеся обновления.</summary>
    property DropPendingUpdates: Boolean read GetDropPendingUpdates write SetDropPendingUpdates;
    /// <summary>ip_address setWebhook (вместо адреса из DNS); пусто — не передаётся.</summary>
    property IpAddress: string read GetIpAddress write SetIpAddress;
    /// <summary>Публичный ключ самоподписанного сертификата (certificate); пусто — нет.</summary>
    property Certificate: TTgInputFile read GetCertificate write SetCertificate;
    /// <summary>allowed_updates; не задано — не передаётся (см. TTgLongPollSource.AllowedUpdates).</summary>
    property AllowedUpdates: TTgOptional<TArray<string>> read GetAllowedUpdates write SetAllowedUpdates;
    /// <summary>
    ///   Вызывать setWebhook при Start (по умолчанию True). False — webhook
    ///   зарегистрирован заранее (вручную или другим процессом).
    /// </summary>
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

implementation

uses
{$IFDEF MSWINDOWS}
  Winapi.Windows,
{$ENDIF}
  System.Classes,
  System.Math,
  TgBot.Consts,
  TgBot.Json;

const
  // Алфавит секрета webhook: 64 символа — байт mod 64 распределён равномерно.
  CSecretAlphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-';

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
    raise ETgError.Create(TgLangText(@SRuUpdNoRandom, @SEnUpdNoRandom));
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
    raise ETgError.Create(TgLangText(@SRuUpdNoRandom, @SEnUpdNoRandom));
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

type
  /// <summary>
  ///   Внутреннее состояние одного запуска TTgWebhookSource (ITgWebhookCore).
  ///   Служебный поток (setWebhook, ожидание остановки, deleteWebhook)
  ///   держит только ссылку на него, поэтому может пережить сам источник.
  /// </summary>
  TTgWebhookCore = class(TInterfacedObject, ITgWebhookCore)
  private
    FLock: TCriticalSection;
    FWake: TEvent;
    FDone: TEvent;
    FTransport: ITgTransport;
    // Отмена setWebhook/deleteWebhook (по истечении бюджета Stop, Free клиента).
    FCallCancel: ITgCancellationSource;
    // Отмена ожидания места в очереди (сразу при Stop).
    FPostCancel: ITgCancellationSource;
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
    function GetMaxBodySize: Integer;
    function GetDone: TEvent;
  end;

  /// <summary>Служебный поток webhook (FreeOnTerminate).</summary>
  TTgWebhookThread = class(TThread)
  private
    FCore: ITgWebhookCore;
  protected
    procedure Execute; override;
  public
    constructor Create(const ACore: ITgWebhookCore);
  end;

{ TTgWebhookThread }

constructor TTgWebhookThread.Create(const ACore: ITgWebhookCore);
begin
  inherited Create(True);
  FCore := ACore;
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
  FCallCancel := TTgCancellationSource.New(ASource.FParentCancel);
  FPostCancel := TTgCancellationSource.New(ASource.FParentCancel);
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
  FCallCancel := nil;
  FPostCancel := nil;
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
    TgCallTransport(FTransport, 'setWebhook', LParams, FCallCancel).Free;
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
    TgCallTransport(FTransport, 'deleteWebhook', LParams, FCallCancel).Free;
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
    TgInvokeQuietly(
      procedure
      begin
        FOnFault(AError);
      end);
end;

procedure TTgWebhookCore.NotifyError(AError: Exception);
begin
  if Assigned(FOnError) then
    TgInvokeQuietly(
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
      if LDelete and not FCallCancel.IsCancelled then
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
  FPostCancel.Cancel;
  FWake.SetEvent;
end;

procedure TTgWebhookCore.CancelCalls;
begin
  FCallCancel.Cancel;
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
    Result := LTimed.TryPost(AUpdate, FPostCancel, FPostTimeoutMs)
  else
    Result := LSink.Post(AUpdate, FPostCancel);
end;

function TTgWebhookCore.GetMaxBodySize: Integer;
begin
  Result := FMaxBodySize;
end;

function TTgWebhookCore.GetDone: TEvent;
begin
  Result := FDone;
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

class function TTgWebhookSource.New(const ATransport: ITgTransport;
  const AParentCancel: ITgCancellation): ITgWebhookSource;
begin
  Result := TTgWebhookSource.Create(ATransport, AParentCancel);
end;

destructor TTgWebhookSource.Destroy;
var
  LCore: ITgWebhookCore;
  LFirst: Boolean;
begin
  if Assigned(FLock) then
  begin
    LCore := CurrentCore;
    if Assigned(LCore) then
    begin
      // Поток (FreeOnTerminate) держит ядро сам: висящий запрос не ждём.
      LFirst := not LCore.IsStopRequested;
      LCore.RequestStop;
      if LFirst then
        LCore.Done.WaitFor(TgDestroyGraceMs);
    end;
    LCore := nil;
  end;
  FCore := nil;
  FreeAndNil(FSeenOrder);
  FreeAndNil(FSeen);
  FreeAndNil(FLock);
  inherited Destroy;
end;

function TTgWebhookSource.CurrentCore: ITgWebhookCore;
begin
  FLock.Enter;
  try
    Result := FCore;
  finally
    FLock.Leave;
  end;
end;

procedure TTgWebhookSource.Start(const ASink: ITgUpdateSink);
var
  LOld: ITgWebhookCore;
  LCore: ITgWebhookCore;
  LThread: TTgWebhookThread;
begin
  if not Assigned(ASink) then
    raise EArgumentNilException.Create(TgLangTextFmt(@SRuArgNil, @SEnArgNil, ['ASink']));
  // Пустой url в setWebhook означал бы удаление webhook.
  if FRegisterOnStart and (Trim(FUrl) = '') then
    raise ETgError.Create(TgUpdatesText(TTgUpdatesText.WebhookUrlRequired));
  if (FSecretToken <> '') and not IsValidSecretToken(FSecretToken) then
    raise ETgError.Create(TgUpdatesText(TTgUpdatesText.WebhookBadSecret));
  FLock.Enter;
  try
    LOld := FCore;
    if Assigned(LOld) and (LOld.State in [TTgSourceState.Running, TTgSourceState.Stopping]) then
      raise ETgError.Create(TgUpdatesText(TTgUpdatesText.SourceRunning));
    LCore := TTgWebhookCore.Create(Self, ASink);
    LThread := TTgWebhookThread.Create(LCore);
    FCore := LCore;
  finally
    FLock.Leave;
  end;
  LThread.Start;
end;

function TTgWebhookSource.Stop(AWaitMs: Cardinal): Boolean;
var
  LCore: ITgWebhookCore;
begin
  LCore := CurrentCore;
  if not Assigned(LCore) then
    Exit(True);
  LCore.RequestStop;
  // Незавершённый setWebhook и deleteWebhook (DeleteOnStop) — в пределах бюджета.
  Result := TgWaitEventPumping(LCore.Done, AWaitMs);
  if not Result then
  begin
    LCore.CancelCalls;
    Result := TgWaitEventPumping(LCore.Done, TgFinalGraceMs);
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
  LCore: ITgWebhookCore;
begin
  LCore := CurrentCore;
  if Assigned(LCore) then
    Result := LCore.State
  else
    Result := TTgSourceState.Idle;
end;

function TTgWebhookSource.WaitForThread(AMs: Cardinal): Boolean;
var
  LCore: ITgWebhookCore;
begin
  LCore := CurrentCore;
  Result := not Assigned(LCore) or
    (LCore.Done.WaitFor(AMs) = TWaitResult.wrSignaled);
end;

function TTgWebhookSource.Admit(out ACore: ITgWebhookCore;
  const ASecretHeader: string): TTgWebhookResult;
begin
  ACore := CurrentCore;
  if not Assigned(ACore) or (ACore.State <> TTgSourceState.Running) then
    Exit(TTgWebhookResult.Unavailable);
  // Секрет — до разбора тела: чужой запрос не тратит память и процессор.
  if not ACore.CheckSecret(ASecretHeader) then
    Exit(TTgWebhookResult.Forbidden);
  Result := TTgWebhookResult.Accepted;
end;

function TTgWebhookSource.Accept(const ABody: TBytes;
  const ASecretHeader: string): TTgWebhookResult;
var
  LCore: ITgWebhookCore;
begin
  Result := Admit(LCore, ASecretHeader);
  if Result <> TTgWebhookResult.Accepted then
    Exit;
  if (Length(ABody) = 0) or (Length(ABody) > LCore.MaxBodySize) then
    Exit(TTgWebhookResult.BadRequest);
  Result := Deliver(LCore, TTgJson.ParseObjectUtf8(ABody));
end;

function TTgWebhookSource.Accept(const ABody, ASecretHeader: string): TTgWebhookResult;
var
  LCore: ITgWebhookCore;
  LMax: Integer;
begin
  Result := Admit(LCore, ASecretHeader);
  if Result <> TTgWebhookResult.Accepted then
    Exit;
  // Лимит — в байтах UTF-8 (как у перегрузки TBytes); длина в символах — быстрый отсев.
  LMax := LCore.MaxBodySize;
  if (ABody = '') or (Length(ABody) > LMax) or (TEncoding.UTF8.GetByteCount(ABody) > LMax) then
    Exit(TTgWebhookResult.BadRequest);
  Result := Deliver(LCore, TTgJson.ParseObject(ABody));
end;

function TTgWebhookSource.Deliver(const ACore: ITgWebhookCore; AJson: TJSONObject): TTgWebhookResult;
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
  if ACore.Post(LUpdate) then
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

function TTgWebhookSource.Receiver: ITgWebhookReceiver;
begin
  // Неявное приведение: класс реализует ITgWebhookReceiver (без as и QueryInterface).
  Result := Self;
end;

function TTgWebhookSource.GetUrl: string;
begin
  Result := FUrl;
end;

procedure TTgWebhookSource.SetUrl(const AValue: string);
begin
  FUrl := AValue;
end;

function TTgWebhookSource.GetSecretToken: string;
begin
  Result := FSecretToken;
end;

procedure TTgWebhookSource.SetSecretToken(const AValue: string);
begin
  FSecretToken := AValue;
end;

function TTgWebhookSource.GetMaxConnections: Integer;
begin
  Result := FMaxConnections;
end;

procedure TTgWebhookSource.SetMaxConnections(AValue: Integer);
begin
  FMaxConnections := AValue;
end;

function TTgWebhookSource.GetDropPendingUpdates: Boolean;
begin
  Result := FDropPendingUpdates;
end;

procedure TTgWebhookSource.SetDropPendingUpdates(AValue: Boolean);
begin
  FDropPendingUpdates := AValue;
end;

function TTgWebhookSource.GetIpAddress: string;
begin
  Result := FIpAddress;
end;

procedure TTgWebhookSource.SetIpAddress(const AValue: string);
begin
  FIpAddress := AValue;
end;

function TTgWebhookSource.GetCertificate: TTgInputFile;
begin
  Result := FCertificate;
end;

procedure TTgWebhookSource.SetCertificate(const AValue: TTgInputFile);
begin
  FCertificate := AValue;
end;

function TTgWebhookSource.GetAllowedUpdates: TTgOptional<TArray<string>>;
begin
  Result := FAllowedUpdates;
end;

procedure TTgWebhookSource.SetAllowedUpdates(const AValue: TTgOptional<TArray<string>>);
begin
  FAllowedUpdates := AValue;
end;

function TTgWebhookSource.GetRegisterOnStart: Boolean;
begin
  Result := FRegisterOnStart;
end;

procedure TTgWebhookSource.SetRegisterOnStart(AValue: Boolean);
begin
  FRegisterOnStart := AValue;
end;

function TTgWebhookSource.GetDeleteOnStop: Boolean;
begin
  Result := FDeleteOnStop;
end;

procedure TTgWebhookSource.SetDeleteOnStop(AValue: Boolean);
begin
  FDeleteOnStop := AValue;
end;

function TTgWebhookSource.GetMaxBodySize: Integer;
begin
  Result := FMaxBodySize;
end;

procedure TTgWebhookSource.SetMaxBodySize(AValue: Integer);
begin
  FMaxBodySize := AValue;
end;

function TTgWebhookSource.GetPostTimeoutMs: Cardinal;
begin
  Result := FPostTimeoutMs;
end;

procedure TTgWebhookSource.SetPostTimeoutMs(AValue: Cardinal);
begin
  FPostTimeoutMs := AValue;
end;

function TTgWebhookSource.GetDedupWindow: Integer;
begin
  Result := FDedupWindow;
end;

procedure TTgWebhookSource.SetDedupWindow(AValue: Integer);
begin
  FDedupWindow := AValue;
end;

function TTgWebhookSource.GetOnError: TProc<Exception>;
begin
  Result := FOnError;
end;

procedure TTgWebhookSource.SetOnError(const AValue: TProc<Exception>);
begin
  FOnError := AValue;
end;

function TTgWebhookSource.GetOnFault: TProc<Exception>;
begin
  Result := FOnFault;
end;

procedure TTgWebhookSource.SetOnFault(const AValue: TProc<Exception>);
begin
  FOnFault := AValue;
end;

end.
