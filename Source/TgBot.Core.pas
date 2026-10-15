unit TgBot.Core;

{
  TgBot — ядро клиента Bot API: TTgApiCore (база сгенерированного TTgApi).

  - транспорт: собственный (создаётся по токену/настройкам, владеет клиент)
    или переданный извне (общий, клиент им не управляет);
  - универсальный вызов Call/CallJson и скачивание файлов DownloadFile;
  - асинхронность: RunAsync (произвольная функция) и RunAsyncCall
    (метод над параметрами, построенными в вызывающем потоке) в общем пуле
    потоков библиотеки (TgBotThreadPool) или в пуле пользователя;
  - отмена: токен клиента (отменяется деструктором), окружающий токен
    потока (TTgCancelScope) и явный токен (Call(..., ACancel));
  - Shutdown (неблокирующий, идемпотентный) закрывает шлюз Async и
    отменяет токен клиента; деструктор вызывает его и ждёт завершения уже
    начатых вызовов не дольше ShutdownTimeoutMs.

  Create/Call/CallJson/DownloadFile/RunAsync — единственная реализация
  транспорта вызовов Bot API в библиотеке.
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
  TgBot.Http;

const
  /// <summary>Сколько деструктор клиента ждёт завершения начатых Async-вызовов, мс.</summary>
  TgDefaultShutdownTimeoutMs = 5000;
  /// <summary>
  ///   Максимум рабочих потоков общего пула библиотеки по умолчанию
  ///   (на машинах с более чем 16 ядрами — 2 потока на ядро).
  /// </summary>
  TgDefaultAsyncPoolSize = 32;

type
  /// <summary>
  ///   Выполнение метода Bot API над готовыми параметрами (AParams может
  ///   быть nil); параметры остаются во владении вызывающего.
  /// </summary>
  TTgExecFunc<T> = reference to function(AParams: TTgParams): T;

  /// <summary>
  ///   Служебное: шлюз Async-вызовов клиента. Задача захватывает шлюз, а не
  ///   клиент: после Close новые задачи не входят, WaitIdle ждёт выхода
  ///   уже вошедших.
  /// </summary>
  ITgAsyncGate = interface
    ['{EF13EE6E-9786-400B-97C4-F8E0EC3201AF}']
    /// <summary>Вход; False — шлюз закрыт.</summary>
    function TryEnter: Boolean;
    /// <summary>Выход (парный успешному TryEnter).</summary>
    procedure Leave;
    /// <summary>Закрывает шлюз для новых входов.</summary>
    procedure Close;
    /// <summary>Ждёт, пока внутри никого не останется; False — таймаут.</summary>
    function WaitIdle(ATimeoutMs: Cardinal): Boolean;
  end;

  /// <summary>
  ///   Служебное: владение параметрами асинхронного вызова. Параметры
  ///   освобождаются ровно один раз — рабочим потоком после выполнения либо
  ///   вместе с коробкой, если задача так и не запустилась.
  /// </summary>
  ITgParamsBox = interface
    ['{5C0B8E57-2F0E-4B8B-9E61-0D8F2F7E0A31}']
    /// <summary>Забирает параметры (дальнейшее владение — у вызывающего); повторно — nil.</summary>
    function Take: TTgParams;
  end;

  /// <summary>
  ///   База клиента Bot API: транспорт, универсальный вызов, асинхронность.
  ///   Потокобезопасен. Не уничтожайте объект из колбэка Async.
  ///
  ///   Async-задача захватывает шлюз и токен клиента, а не сам клиент.
  ///   ИНВАРИАНТ сгенерированного кода: Exec* (AExec в RunAsyncCall) после
  ///   возврата из Call не обращается к Self — только разбирает результат.
  ///   Call копирует транспорт и токены в локальные переменные до вызова
  ///   транспорта. Поэтому, если деструктор не дождался зависшего вызова
  ///   (ShutdownTimeoutMs), его завершение не обращается к освобождённому
  ///   клиенту. Собственные RunAsync-функции должны соблюдать то же правило.
  /// </summary>
  TTgApiCore = class
  private
    FTransport: ITgTransport;
    FOwnsTransport: Boolean;
    FSettings: TTgHttpSettings;
    FCancelSource: TTgCancellationSource;
    FCancelToken: ITgCancellation;
    FGate: ITgAsyncGate;
    FPool: TThreadPool;
    FShutdownTimeoutMs: Cardinal;
    function GetThreadPool: TThreadPool;
    /// <summary>Коробка владения параметрами; при ошибке создания AParams освобождается.</summary>
    class function NewParamsBox(AParams: TTgParams): ITgParamsBox; static;
    /// <summary>Новый открытый шлюз Async-вызовов.</summary>
    class function NewAsyncGate: ITgAsyncGate; static;
  protected
    /// <summary>
    ///   Асинхронный вызов над готовыми параметрами: AParams строятся и
    ///   проверяются в вызывающем потоке, владение ими переходит к функции
    ///   сразу (в т.ч. при исключении); в рабочем потоке выполняется только
    ///   AExec(AParams), затем параметры освобождаются. AParams = nil допустим.
    /// </summary>
    function RunAsyncCall<T>(AParams: TTgParams; const AExec: TTgExecFunc<T>;
      const AOnSuccess: TProc<T>; const AOnError: TProc<Exception>): ITask;
  public
    /// <summary>Клиент облачного Bot API с настройками по умолчанию.</summary>
    constructor Create(const AToken: string); overload;
    /// <summary>Клиент с настройками транспорта (прокси, ApiUrl, таймауты…).</summary>
    constructor Create(const ASettings: TTgHttpSettings); overload;
    /// <summary>
    ///   Клиент с настройками транспорта и пулом потоков пользователя для
    ///   Async (не во владении; nil — общий пул библиотеки). Пул должен жить
    ///   дольше клиента и всех его Async-задач.
    /// </summary>
    constructor Create(const ASettings: TTgHttpSettings; APool: TThreadPool); overload;
    /// <summary>
    ///   Клиент с внешним транспортом (общим для нескольких клиентов или
    ///   тестовым). Клиент не отменяет такой транспорт целиком: деструктор
    ///   прерывает только вызовы этого клиента (токен клиента).
    /// </summary>
    constructor Create(const ATransport: ITgTransport); overload;
    /// <summary>
    ///   Клиент с внешним транспортом и пулом потоков пользователя для Async
    ///   (не во владении; nil — общий пул библиотеки).
    /// </summary>
    constructor Create(const ATransport: ITgTransport; APool: TThreadPool); overload;
    /// <summary>
    ///   Закрывает шлюз Async (ещё не начатые задачи вызовут AOnError с
    ///   ETgCancelledError и не выполнятся), отменяет токен клиента (ожидания
    ///   и, где поддерживается, HTTP-запросы этого клиента прерываются;
    ///   общий транспорт и другие клиенты не затрагиваются) и ждёт выхода
    ///   начатых вызовов из шлюза не дольше ShutdownTimeoutMs. Колбэки
    ///   AOnSuccess/AOnError выполняются вне шлюза и не ожидаются.
    ///   Очередь Synchronize не обрабатывается: Async-функции не должны
    ///   ждать главный поток.
    /// </summary>
    destructor Destroy; override;
    /// <summary>
    ///   Неблокирующее закрытие клиента: закрывает шлюз Async и отменяет
    ///   токен клиента, не дожидаясь начатых вызовов (ожидание — в
    ///   деструкторе). Идемпотентно, потокобезопасно. После Shutdown любой
    ///   Call/CallJson/DownloadFile выбрасывает ETgCancelledError, новые
    ///   Async-вызовы завершаются AOnError(ETgCancelledError). Объект остаётся
    ///   действительным до Free.
    /// </summary>
    procedure Shutdown;
    /// <summary>
    ///   Универсальный вызов метода Bot API с окружающим токеном отмены
    ///   (TTgCancelScope.Current) и токеном клиента. Результат (поле result)
    ///   освобождает вызывающий. AParams остаётся во владении вызывающего.
    /// </summary>
    function Call(const AMethod: string; AParams: TTgParams = nil): TJSONValue; overload;
    /// <summary>
    ///   Универсальный вызов с явным токеном отмены ACancel (вместо
    ///   окружающего; nil — только токен клиента). Отмена — ETgCancelledError.
    /// </summary>
    function Call(const AMethod: string; AParams: TTgParams;
      const ACancel: ITgCancellation): TJSONValue; overload;
    /// <summary>Универсальный вызов; результат — JSON-текст поля result.</summary>
    function CallJson(const AMethod: string; AParams: TTgParams = nil): string;
    /// <summary>
    ///   Скачивает файл по file_path (из getFile) в поток; токены — как у Call.
    /// </summary>
    procedure DownloadFile(const AFilePath: string; ADest: TStream); overload;
    /// <summary>Скачивает файл с явным токеном отмены ACancel.</summary>
    procedure DownloadFile(const AFilePath: string; ADest: TStream;
      const ACancel: ITgCancellation); overload;
    /// <summary>
    ///   Выполняет AFunc в пуле потоков (ThreadPool) с окружающим токеном
    ///   клиента. При успехе вызывает AOnSuccess, при ошибке — AOnError
    ///   (объект исключения действителен только внутри колбэка). Если
    ///   AOnError не задан, исключение сохраняется в ITask (ITask.Wait
    ///   выбросит EAggregateException). Колбэки — в рабочем потоке, вне шлюза.
    ///   Если клиент уже уничтожается — AOnError(ETgCancelledError), AFunc
    ///   не вызывается.
    /// </summary>
    function RunAsync<T>(const AFunc: TFunc<T>; const AOnSuccess: TProc<T>;
      const AOnError: TProc<Exception>): ITask;
    /// <summary>Транспорт клиента.</summary>
    property Transport: ITgTransport read FTransport;
    /// <summary>Транспорт создан клиентом (по токену или настройкам).</summary>
    property OwnsTransport: Boolean read FOwnsTransport;
    /// <summary>
    ///   Настройки HTTP-транспорта (содержат токен). Для внешнего транспорта,
    ///   не являющегося TTgHttpTransport, — пустая запись.
    /// </summary>
    property Settings: TTgHttpSettings read FSettings;
    /// <summary>Токен клиента: отменяется в начале деструктора.</summary>
    property CancelToken: ITgCancellation read FCancelToken;
    /// <summary>Пул потоков Async: пул пользователя или общий пул библиотеки.</summary>
    property ThreadPool: TThreadPool read GetThreadPool;
    /// <summary>
    ///   Сколько деструктор ждёт начатые Async-вызовы, мс
    ///   (по умолчанию TgDefaultShutdownTimeoutMs).
    /// </summary>
    property ShutdownTimeoutMs: Cardinal read FShutdownTimeoutMs write FShutdownTimeoutMs;
  end;

/// <summary>
///   Общий пул потоков Async-вызовов библиотеки (создаётся при первом
///   обращении, потокобезопасно; уничтожается при завершении программы —
///   к этому моменту Async-задачи должны завершиться).
/// </summary>
function TgBotThreadPool: TThreadPool;
/// <summary>
///   Задаёт максимум рабочих потоков общего пула библиотеки (не меньше 1).
///   Каждый висящий long polling занимает поток пула. В Delphi 12 пул при
///   блокировке всех потоков может временно превысить максимум
///   (TThreadPool.UnlimitedWorkerThreadsWhenBlocked, по умолчанию True).
/// </summary>
procedure TgSetAsyncPoolSize(AMaxThreads: Integer);

implementation

uses
  System.Math,
  TgBot.Consts;

type
  /// <summary>Реализация ITgParamsBox.</summary>
  TTgParamsBox = class(TInterfacedObject, ITgParamsBox)
  private
    FParams: TTgParams;
  public
    constructor Create(AParams: TTgParams);
    destructor Destroy; override;
    function Take: TTgParams;
  end;

  /// <summary>Реализация ITgAsyncGate: счётчик входов и событие «пусто».</summary>
  TTgAsyncGate = class(TInterfacedObject, ITgAsyncGate)
  private
    FLock: TCriticalSection;
    FIdle: TEvent;
    FCount: Integer;
    FClosed: Boolean;
  public
    constructor Create;
    destructor Destroy; override;
    function TryEnter: Boolean;
    procedure Leave;
    procedure Close;
    function WaitIdle(ATimeoutMs: Cardinal): Boolean;
  end;

var
  // Общий пул библиотеки (TgBotThreadPool); создаётся лениво.
  GTgBotPool: TThreadPool = nil;

function TgBotThreadPool: TThreadPool;
var
  LPool: TThreadPool;
begin
  Result := TInterlocked.CompareExchange<TThreadPool>(GTgBotPool, nil, nil);
  if Assigned(Result) then
    Exit;
  LPool := TThreadPool.Create;
  try
    // Вызовы Bot API ждут сеть, а не процессор: не меньше TgDefaultAsyncPoolSize
    // потоков (на многоядерных машинах — 2 на ядро). Максимум задаётся явно:
    // умолчание TThreadPool зависит от версии (10.4 — 25 на ядро, 12 — 2).
    LPool.SetMaxWorkerThreads(Max(TgDefaultAsyncPoolSize, TThread.ProcessorCount * 2));
  except
    LPool.Free;
    raise;
  end;
  // Проигравший гонку создания освобождает свой экземпляр.
  if TInterlocked.CompareExchange<TThreadPool>(GTgBotPool, LPool, nil) <> nil then
    LPool.Free;
  Result := GTgBotPool;
end;

procedure TgSetAsyncPoolSize(AMaxThreads: Integer);
var
  LPool: TThreadPool;
begin
  if AMaxThreads < 1 then
    raise EArgumentOutOfRangeException.Create(
      TgLangTextFmt(@SRuArgOutOfRange, @SEnArgOutOfRange, ['AMaxThreads', AMaxThreads, 1]));
  LPool := TgBotThreadPool;
  // Минимум пула не может превышать максимум.
  if LPool.MinWorkerThreads > AMaxThreads then
    LPool.SetMinWorkerThreads(AMaxThreads);
  LPool.SetMaxWorkerThreads(AMaxThreads);
end;

{ TTgAsyncGate }

constructor TTgAsyncGate.Create;
begin
  inherited Create;
  FLock := TCriticalSection.Create;
  FIdle := TEvent.Create(nil, True, True, '');
end;

destructor TTgAsyncGate.Destroy;
begin
  FreeAndNil(FIdle);
  FreeAndNil(FLock);
  inherited Destroy;
end;

function TTgAsyncGate.TryEnter: Boolean;
begin
  FLock.Enter;
  try
    Result := not FClosed;
    if Result then
    begin
      Inc(FCount);
      if FCount = 1 then
        FIdle.ResetEvent;
    end;
  finally
    FLock.Leave;
  end;
end;

procedure TTgAsyncGate.Leave;
begin
  FLock.Enter;
  try
    Dec(FCount);
    if FCount = 0 then
      FIdle.SetEvent;
  finally
    FLock.Leave;
  end;
end;

procedure TTgAsyncGate.Close;
begin
  FLock.Enter;
  try
    FClosed := True;
  finally
    FLock.Leave;
  end;
end;

function TTgAsyncGate.WaitIdle(ATimeoutMs: Cardinal): Boolean;
begin
  // После Close новых входов нет: событие «пусто» больше не сбрасывается.
  Result := FIdle.WaitFor(ATimeoutMs) = TWaitResult.wrSignaled;
end;

{ TTgParamsBox }

constructor TTgParamsBox.Create(AParams: TTgParams);
begin
  inherited Create;
  FParams := AParams;
end;

destructor TTgParamsBox.Destroy;
begin
  // Задача не запустилась или не забрала параметры — освобождаем здесь.
  FreeAndNil(FParams);
  inherited Destroy;
end;

function TTgParamsBox.Take: TTgParams;
begin
  Result := FParams;
  FParams := nil;
end;

{ TTgApiCore }

constructor TTgApiCore.Create(const AToken: string);
begin
  Create(TTgHttpSettings.Create(AToken));
end;

constructor TTgApiCore.Create(const ASettings: TTgHttpSettings);
begin
  Create(ASettings, nil);
end;

constructor TTgApiCore.Create(const ASettings: TTgHttpSettings; APool: TThreadPool);
begin
  Create(TTgHttpTransport.Create(ASettings) as ITgTransport, APool);
  FOwnsTransport := True;
end;

constructor TTgApiCore.Create(const ATransport: ITgTransport);
begin
  Create(ATransport, nil);
end;

constructor TTgApiCore.Create(const ATransport: ITgTransport; APool: TThreadPool);
var
  LObject: TObject;
begin
  inherited Create;
  if not Assigned(ATransport) then
    raise ETgError.Create(TgText(TTgText.TransportRequired));
  FTransport := ATransport;
  FPool := APool;
  FShutdownTimeoutMs := TgDefaultShutdownTimeoutMs;
  FCancelSource := TTgCancellationSource.Create;
  FCancelToken := FCancelSource;
  FGate := NewAsyncGate;
  LObject := ATransport as TObject;
  if LObject is TTgHttpTransport then
    FSettings := TTgHttpTransport(LObject).Settings;
end;

procedure TTgApiCore.Shutdown;
begin
  // 1. Новые Async-задачи этого клиента больше не выполняются.
  if Assigned(FGate) then
    FGate.Close;
  // 2. Прерываем вызовы этого клиента. Транспорт (в т.ч. общий) не отменяем:
  //    другие клиенты на нём продолжают работать.
  if Assigned(FCancelSource) then
    FCancelSource.Cancel;
end;

destructor TTgApiCore.Destroy;
begin
  // 1–2. Закрыть шлюз и отменить токен клиента (повторный Shutdown безвреден).
  Shutdown;
  // 3. Ждём выхода начатых вызовов из шлюза — без обработки Synchronize.
  //    По таймауту продолжаем: зависший вызов не обращается к клиенту (см. инвариант).
  if Assigned(FGate) then
    FGate.WaitIdle(FShutdownTimeoutMs);
  FGate := nil;
  FTransport := nil;
  // Источник живёт, пока на токен ссылаются незавершённые задачи.
  FCancelSource := nil;
  FCancelToken := nil;
  inherited Destroy;
end;

class function TTgApiCore.NewAsyncGate: ITgAsyncGate;
begin
  Result := TTgAsyncGate.Create;
end;

function TTgApiCore.GetThreadPool: TThreadPool;
begin
  Result := FPool;
  if not Assigned(Result) then
    Result := TgBotThreadPool;
end;

function TTgApiCore.Call(const AMethod: string; AParams: TTgParams): TJSONValue;
begin
  Result := Call(AMethod, AParams, TTgCancelScope.Current);
end;

function TTgApiCore.Call(const AMethod: string; AParams: TTgParams;
  const ACancel: ITgCancellation): TJSONValue;
var
  LTransport: ITgTransport;
  LCancellable: ITgCancellableTransport;
  LToken: ITgCancellation;
  LScope: TTgCancelScope;
begin
  // Локальные копии: после вызова транспорта поля клиента не читаются.
  LTransport := FTransport;
  LToken := TTgCancellationSource.Linked(ACancel, FCancelToken);
  // Клиент закрыт (Shutdown) или токен уже отменён — транспорт не вызывается.
  LToken.ThrowIfCancelled;
  if Supports(LTransport, ITgCancellableTransport, LCancellable) then
    Exit(LCancellable.ExecuteEx(AMethod, AParams, LToken));
  // Транспорт без токенов: проверка после; токен доступен ему как окружающий.
  LScope := TTgCancelScope.Enter(LToken);
  try
    Result := LTransport.Execute(AMethod, AParams);
  finally
    LScope.Leave;
  end;
  if LToken.IsCancelled then
  begin
    FreeAndNil(Result);
    raise ETgCancelledError.Create(TgText(TTgText.Cancelled));
  end;
end;

function TTgApiCore.CallJson(const AMethod: string; AParams: TTgParams): string;
var
  LValue: TJSONValue;
begin
  LValue := Call(AMethod, AParams);
  try
    Result := TTgJson.ToText(LValue);
  finally
    LValue.Free;
  end;
end;

procedure TTgApiCore.DownloadFile(const AFilePath: string; ADest: TStream);
begin
  DownloadFile(AFilePath, ADest, TTgCancelScope.Current);
end;

procedure TTgApiCore.DownloadFile(const AFilePath: string; ADest: TStream;
  const ACancel: ITgCancellation);
var
  LTransport: ITgTransport;
  LCancellable: ITgCancellableTransport;
  LToken: ITgCancellation;
  LScope: TTgCancelScope;
begin
  LTransport := FTransport;
  LToken := TTgCancellationSource.Linked(ACancel, FCancelToken);
  LToken.ThrowIfCancelled;
  if Supports(LTransport, ITgCancellableTransport, LCancellable) then
  begin
    LCancellable.DownloadFileEx(AFilePath, ADest, LToken);
    Exit;
  end;
  LScope := TTgCancelScope.Enter(LToken);
  try
    LTransport.DownloadFile(AFilePath, ADest);
  finally
    LScope.Leave;
  end;
  LToken.ThrowIfCancelled;
end;

class function TTgApiCore.NewParamsBox(AParams: TTgParams): ITgParamsBox;
begin
  try
    Result := TTgParamsBox.Create(AParams);
  except
    AParams.Free;
    raise;
  end;
end;

function TTgApiCore.RunAsyncCall<T>(AParams: TTgParams; const AExec: TTgExecFunc<T>;
  const AOnSuccess: TProc<T>; const AOnError: TProc<Exception>): ITask;
var
  LBox: ITgParamsBox;
begin
  // С этого места параметрами владеет коробка: если задача не запустится,
  // замыкание и коробка будут освобождены вместе с параметрами.
  LBox := NewParamsBox(AParams);
  Result := RunAsync<T>(
    function: T
    var
      LParams: TTgParams;
    begin
      LParams := LBox.Take;
      try
        Result := AExec(LParams);
      finally
        LParams.Free;
      end;
    end,
    AOnSuccess, AOnError);
end;

function TTgApiCore.RunAsync<T>(const AFunc: TFunc<T>; const AOnSuccess: TProc<T>;
  const AOnError: TProc<Exception>): ITask;
var
  LGate: ITgAsyncGate;
  LToken: ITgCancellation;
begin
  // Задача захватывает шлюз и токен, но не Self: клиент может быть уже уничтожен.
  LGate := FGate;
  LToken := FCancelToken;
  Result := TTask.Run(
    procedure
    var
      LResult: T;
      LScope: TTgCancelScope;
    begin
      try
        if not LGate.TryEnter then
          raise ETgCancelledError.Create(TgText(TTgText.ClientClosed));
        try
          LScope := TTgCancelScope.Enter(LToken);
          try
            LResult := AFunc();
          finally
            LScope.Leave;
          end;
        finally
          // Выход из шлюза — до колбэков: деструктор их не ждёт.
          LGate.Leave;
        end;
      except
        on E: Exception do
        begin
          if not Assigned(AOnError) then
            raise;
          AOnError(E);
          Exit;
        end;
      end;
      // Исключение из AOnSuccess не перехватывается и сохраняется в ITask.
      if Assigned(AOnSuccess) then
        AOnSuccess(LResult);
    end,
    GetThreadPool);
end;

initialization

finalization
  // Пул уничтожается после всех модулей, использующих TgBot.Core; ждёт
  // завершения рабочих потоков.
  FreeAndNil(GTgBotPool);

end.
