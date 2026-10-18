unit TgBot.Updates.Dispatcher;

{
  TgBot — диспетчер обновлений TTgUpdateDispatcher: «полосы» по ChatKey
  (обновления одного чата — строго по порядку, разных — параллельно),
  MaxParallel собственных потоков, доставка в рабочем потоке или в главном
  (TThread.Queue, без Synchronize).

  Состояние одного запуска (ядро) скрыто за служебным интерфейсом
  ITgDispatchCore, реализация — в implementation. Диспетчер, его потоки и
  задания главного потока держат ядро только через этот интерфейс, поэтому
  поток с зависшим обработчиком может пережить сам диспетчер.

  Пользователю достаточно uses TgBot.Updates (или TgBot): TTgUpdateDispatcher
  и публичный ITgUpdateDispatcher (создание — TTgUpdateDispatcher.New)
  реэкспортируются там псевдонимами. ITgDispatchCore — служебный (не путать
  с ITgUpdateDispatcher), не используйте его напрямую. Контракт
  ITgUpdateDispatcher объявлен в TgBot.Intf, здесь — псевдоним.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.SyncObjs,
  TgBot.Base,
  TgBot.Intf,
  TgBot.Updates.Types;

type
  /// <summary>
  ///   Служебное, не часть публичного API (не используйте напрямую): ядро
  ///   одного запуска TTgUpdateDispatcher — полосы, очередь готовых полос,
  ///   учёт потоков, токен отмены. Держат его диспетчер (до следующего Start
  ///   или Free), каждый поток диспетчера и задания главного потока
  ///   (Delivery = Main); последний освободивший — уничтожает.
  /// </summary>
  ITgDispatchCore = interface
    ['{BD60FA50-F6EE-448D-850B-EAFDB700FB3C}']
    /// <summary>Цикл потока диспетчера: обрабатывает готовые полосы до BeginStop.</summary>
    procedure WorkerLoop;
    /// <summary>Поток создан (учёт до запуска; сбрасывает AllExited).</summary>
    procedure WorkerStarted;
    /// <summary>Поток вышел из цикла (последний — AllExited).</summary>
    procedure WorkerExited;
    /// <summary>Выполняет обработчик в текущем потоке (с областью отмены).</summary>
    procedure Execute(const AUpdate: ITgRawUpdate);
    /// <summary>Место в очереди ждёт не дольше ATimeoutMs (INFINITE — без предела).</summary>
    function Post(const AUpdate: ITgRawUpdate; const ACancel: ITgCancellation;
      ATimeoutMs: Cardinal): Boolean;
    /// <summary>Будит ждущих места в очереди (отмена их токена ACancel).</summary>
    procedure WakeWaiters;
    /// <summary>Остановка: необработанная очередь выбрасывается, токен отменяется.</summary>
    procedure BeginStop;
    /// <summary>BeginStop уже вызван.</summary>
    function Stopping: Boolean;
    function GetAllExited: TEvent;
    function GetIdle: TEvent;
    function GetCancel: ITgCancellation;
    /// <summary>Все потоки диспетчера вышли.</summary>
    property AllExited: TEvent read GetAllExited;
    /// <summary>Очередь пуста и обработчики не выполняются.</summary>
    property Idle: TEvent read GetIdle;
    /// <summary>Токен отмены запуска.</summary>
    property Cancel: ITgCancellation read GetCancel;
  end;

  /// <summary>
  ///   Диспетчер обновлений как интерфейс (описание —
  ///   TgBot.Intf.ITgUpdateDispatcher; псевдоним для совместимости: тот же
  ///   тип и GUID). Создание — TTgUpdateDispatcher.New. Не путать со
  ///   служебным ITgDispatchCore.
  /// </summary>
  ITgUpdateDispatcher = TgBot.Intf.ITgUpdateDispatcher;

  /// <summary>
  ///   Диспетчер обновлений: «полосы» по ChatKey (обновления одного чата —
  ///   строго по порядку, разных — параллельно), MaxParallel собственных
  ///   потоков, общая очередь готовых полос, ёмкость QueueCapacity.
  ///   Обработчик выполняется внутри TTgCancelScope с токеном диспетчера
  ///   (вызовы TTgApi без явного токена прерываются при Stop). Исключение
  ///   обработчика передаётся в OnError (исключения OnError поглощаются),
  ///   обновление считается обработанным (OnProcessed).
  ///
  ///   Создавайте через New и храните как ITgUpdateDispatcher; не храните
  ///   ссылку на класс (объект освобождается по счётчику ссылок).
  /// </summary>
  TTgUpdateDispatcher = class(TInterfacedObject, ITgUpdateSink, ITgTimedUpdateSink, ITgUpdateDispatcher)
  private
    FLock: TCriticalSection;
    // Ядро текущего (или последнего) запуска, под FLock; nil — Start не вызывался.
    FCore: ITgDispatchCore;
    FHandler: TTgRawHandler;
    FOnError: TTgRawErrorHandler;
    FOnProcessed: TProc<Int64>;
    FMaxParallel: Integer;
    FQueueCapacity: Integer;
    FDelivery: TTgDelivery;
    function CurrentCore: ITgDispatchCore;
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
  public
    /// <summary>Диспетчер с обработчиком AHandler. Предпочтительно создавать через New.</summary>
    constructor Create(const AHandler: TTgRawHandler);
    /// <summary>
    ///   Создаёт диспетчер (параметры — как у Create) и возвращает его как
    ///   ITgUpdateDispatcher. Создавайте через New и храните как интерфейс;
    ///   не храните ссылку на класс.
    /// </summary>
    class function New(const AHandler: TTgRawHandler): ITgUpdateDispatcher; static;
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

implementation

uses
  System.Classes,
  System.Generics.Collections,
  System.Diagnostics,
  System.Math,
  TgBot.Consts;

const
  // Предел потоков диспетчера.
  CMaxParallelLimit = 64;
  // Порция конечного ожидания места в Post (мс). Остаток срока считается по
  // монотонному TStopwatch, а TEvent.WaitFor на Linux/Android ждёт до
  // абсолютного момента по CLOCK_REALTIME (sem_timedwait) — поэтому ждём
  // порциями, каждая сверяется с TStopwatch заново. Скачок часов назад
  // посреди порции всё же затянет её на величину скачка (ограничение RTL).
  CPostWaitSliceMs = 200;

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

  {
    Ожидания ядра и заданий главного потока — без TMonitor.Wait/Pulse/PulseAll
    (из TMonitor допустимы только Enter/Exit, в т.ч. внутри TCriticalSection
    на POSIX). Схема везде одна: условие проверяется под замком; если ждать
    нужно — ждущий отмечается (счётчик спящих или список ожидающих), выходит
    из замка, ждёт TEvent с автосбросом, снова входит и перепроверяет
    условие. Выставленное событие хранит сигнал до пробуждения, поэтому
    SetEvent между выходом из замка и WaitFor не теряется; лишнее (позднее)
    пробуждение безопасно — условие перепроверяется. ResetEvent в циклах
    ожидания не используется.
  }

  /// <summary>
  ///   Сигнал пробуждения: TEvent с автосбросом с подсчётом ссылок. Поздний
  ///   Signal (после ухода ждущего) безопасен: объект жив, пока на него есть
  ///   ссылка, а ждущий перепроверяет условие.
  /// </summary>
  ITgWakeSignal = interface
    /// <summary>Будит одного ждущего (или следующий WaitFor).</summary>
    procedure Signal;
    /// <summary>Ждёт сигнала не дольше ATimeoutMs; причину пробуждения не сообщает.</summary>
    procedure WaitFor(ATimeoutMs: Cardinal);
  end;

  /// <summary>Реализация ITgWakeSignal.</summary>
  TTgWakeSignal = class(TInterfacedObject, ITgWakeSignal)
  private
    FEvent: TEvent;
  public
    constructor Create;
    destructor Destroy; override;
    procedure Signal;
    procedure WaitFor(ATimeoutMs: Cardinal);
  end;

  /// <summary>Внутреннее состояние одного запуска диспетчера (ITgDispatchCore).</summary>
  TTgDispatchCore = class(TInterfacedObject, ITgDispatchCore)
  private
    FLock: TCriticalSection;
    FLanes: TDictionary<string, TTgLane>;
    FReady: TQueue<TTgLane>;
    FCount: Integer;
    FBusy: Integer;
    FCapacity: Integer;
    FStopping: Boolean;
    FWorkers: Integer;
    // Потоки, ждущие готовых полос (под FLock), и их событие (см. WorkerLoop).
    FSleepingWorkers: Integer;
    FWorkReady: TEvent;
    // Производители, ждущие места в очереди, и пул их сигналов (под FLock, см. Post).
    FSpaceWaiters: TList<ITgWakeSignal>;
    FSignalPool: TStack<ITgWakeSignal>;
    FAllExited: TEvent;
    FIdle: TEvent;
    FCancel: ITgCancellationSource;
    FDelivery: TTgDelivery;
    FHandler: TTgRawHandler;
    FOnError: TTgRawErrorHandler;
    FOnProcessed: TProc<Int64>;
    procedure Deliver(const AUpdate: ITgRawUpdate; const ASignal: ITgWakeSignal);
    procedure DeliverMain(const AUpdate: ITgRawUpdate; const ASignal: ITgWakeSignal);
    procedure FinishLane(ALane: TTgLane; AFailed: Boolean);
    // Вызываются под FLock.
    procedure WakeWorker;
    procedure WakeSpaceWaiter;
    procedure WakeSpaceWaiters;
    function AcquireSignal: ITgWakeSignal;
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
    procedure WakeWaiters;
    procedure BeginStop;
    function Stopping: Boolean;
    function GetAllExited: TEvent;
    function GetIdle: TEvent;
    function GetCancel: ITgCancellation;
  end;

  /// <summary>Поток диспетчера (FreeOnTerminate).</summary>
  TTgDispatchThread = class(TThread)
  private
    FCore: ITgDispatchCore;
  protected
    procedure Execute; override;
  public
    constructor Create(const ACore: ITgDispatchCore);
  end;

  /// <summary>Задание для главного потока (Delivery = Main), см. TTgMainJob.</summary>
  ITgMainJob = interface
    function TryStart(const ACancel: ITgCancellation): Boolean;
    procedure Finish;
    procedure Wake;
    procedure WaitFor(const ACancel: ITgCancellation);
  end;

  /// <summary>
  ///   Задание для главного потока (Delivery = Main). Состояния:
  ///   0 — ждёт, 1 — выполняется, 2 — выполнено, 3 — брошено (процедура в
  ///   очереди ничего не сделает). Состояние меняется атомарно
  ///   (TInterlocked), ожидание — на сигнале потока диспетчера.
  /// </summary>
  TTgMainJob = class(TInterfacedObject, ITgMainJob)
  private
    FState: Integer;
    // Сигнал потока диспетчера (один на поток, общий для его заданий):
    // брошенное задание держит его живым, поздний Signal безопасен.
    FSignal: ITgWakeSignal;
  public
    constructor Create(const ASignal: ITgWakeSignal);
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

{ TTgWakeSignal }

constructor TTgWakeSignal.Create;
begin
  inherited Create;
  // Автосброс: сигнал забирает один ждущий, ResetEvent не нужен.
  FEvent := TEvent.Create(nil, False, False, '');
end;

destructor TTgWakeSignal.Destroy;
begin
  FreeAndNil(FEvent);
  inherited Destroy;
end;

procedure TTgWakeSignal.Signal;
begin
  FEvent.SetEvent;
end;

procedure TTgWakeSignal.WaitFor(ATimeoutMs: Cardinal);
begin
  // Результат не важен: ждущий всегда перепроверяет своё условие.
  FEvent.WaitFor(ATimeoutMs);
end;

{ TTgMainJob }

constructor TTgMainJob.Create(const ASignal: ITgWakeSignal);
begin
  inherited Create;
  FSignal := ASignal;
end;

function TTgMainJob.TryStart(const ACancel: ITgCancellation): Boolean;
begin
  // Диспетчер уже останавливается — не начинаем (не начатое — бросаем).
  if ACancel.IsCancelled then
  begin
    if TInterlocked.CompareExchange(FState, 3, 0) = 0 then
      FSignal.Signal;
    Exit(False);
  end;
  // Брошено потоком диспетчера (3) или уже выполнялось — отказ.
  Result := TInterlocked.CompareExchange(FState, 1, 0) = 0;
end;

procedure TTgMainJob.Finish;
begin
  TInterlocked.Exchange(FState, 2);
  FSignal.Signal;
end;

procedure TTgMainJob.Wake;
begin
  FSignal.Signal;
end;

procedure TTgMainJob.WaitFor(const ACancel: ITgCancellation);
var
  LState: Integer;
begin
  while True do
  begin
    LState := TInterlocked.CompareExchange(FState, 0, 0);
    if LState >= 2 then
      Exit;
    // Отмена: не начатое задание бросается. Главный поток мог успеть его
    // начать (CompareExchange не удался) — тогда ждём Finish.
    if (LState = 0) and ACancel.IsCancelled and
      (TInterlocked.CompareExchange(FState, 3, 0) = 0) then
      Exit;
    // Finish, отказ TryStart и отмена выставляют сигнал после смены
    // состояния; сигнал прежнего задания этого потока — лишний виток цикла.
    FSignal.WaitFor(INFINITE);
  end;
end;

// Замыкания — в отдельных функциях: захватывается только нужное.

function NewJobWakeCallback(const AJob: ITgMainJob): TProc;
begin
  Result :=
    procedure
    begin
      AJob.Wake;
    end;
end;

function NewMainJobProc(const ACore: ITgDispatchCore; const AJob: ITgMainJob;
  const AUpdate: ITgRawUpdate): TThreadProcedure;
begin
  Result :=
    procedure
    begin
      // «Осиротевшая» процедура (задание брошено) ничего не делает.
      if not AJob.TryStart(ACore.Cancel) then
        Exit;
      try
        ACore.Execute(AUpdate);
      finally
        AJob.Finish;
      end;
    end;
end;

function NewPulseCallback(const ACore: ITgDispatchCore): TProc;
begin
  Result :=
    procedure
    begin
      ACore.WakeWaiters;
    end;
end;

{ TTgDispatchThread }

constructor TTgDispatchThread.Create(const ACore: ITgDispatchCore);
begin
  inherited Create(True);
  FCore := ACore;
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
  end;
end;

{ TTgDispatchCore }

constructor TTgDispatchCore.Create(ADispatcher: TTgUpdateDispatcher);
begin
  inherited Create;
  FLock := TCriticalSection.Create;
  FLanes := TDictionary<string, TTgLane>.Create;
  FReady := TQueue<TTgLane>.Create;
  FWorkReady := TEvent.Create(nil, False, False, '');
  FSpaceWaiters := TList<ITgWakeSignal>.Create;
  FSignalPool := TStack<ITgWakeSignal>.Create;
  FAllExited := TEvent.Create(nil, True, True, '');
  FIdle := TEvent.Create(nil, True, True, '');
  FCancel := TTgCancellationSource.New;
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
  FreeAndNil(FSpaceWaiters);
  FreeAndNil(FSignalPool);
  FreeAndNil(FWorkReady);
  FreeAndNil(FAllExited);
  FreeAndNil(FIdle);
  FreeAndNil(FLock);
  FCancel := nil;
  inherited Destroy;
end;

procedure TTgDispatchCore.WorkerStarted;
begin
  FLock.Enter;
  try
    Inc(FWorkers);
    FAllExited.ResetEvent;
  finally
    FLock.Leave;
  end;
end;

procedure TTgDispatchCore.WorkerExited;
begin
  FLock.Enter;
  try
    Dec(FWorkers);
    if FWorkers = 0 then
      FAllExited.SetEvent;
  finally
    FLock.Leave;
  end;
end;

procedure TTgDispatchCore.WakeWorker;
begin
  // Событие с автосбросом: будит одного спящего, тот передаёт дальше.
  if FSleepingWorkers > 0 then
    FWorkReady.SetEvent;
end;

procedure TTgDispatchCore.WakeSpaceWaiter;
begin
  // Место есть — будим первого ждущего, не всех: толпа производителей на
  // одно место дала бы конвой на замке. Эстафета: каждый выходящий из Post
  // (занял место, срок, отмена) снова вызывает WakeSpaceWaiter, поэтому
  // оставшееся место не теряется. Разбуженный ещё в списке — повторный
  // Signal сольётся, он перепроверит место под замком сам.
  if (FSpaceWaiters.Count > 0) and (FCount < FCapacity) then
    FSpaceWaiters[0].Signal;
end;

procedure TTgDispatchCore.WakeSpaceWaiters;
var
  LSignal: ITgWakeSignal;
begin
  // Остановка или отмена: будим всех — каждый перепроверит свой токен.
  for LSignal in FSpaceWaiters do
    LSignal.Signal;
end;

function TTgDispatchCore.AcquireSignal: ITgWakeSignal;
begin
  // Сигналы переиспользуются: создаются, только когда ждущих больше, чем в пуле.
  if FSignalPool.Count > 0 then
    Result := FSignalPool.Pop
  else
    Result := TTgWakeSignal.Create;
end;

procedure TTgDispatchCore.WorkerLoop;
var
  LLane: TTgLane;
  LUpdate: ITgRawUpdate;
  LSignal: ITgWakeSignal;
  LFailed: Boolean;
begin
  // Ожидание заданий главного потока — на сигнале этого потока.
  if FDelivery = TTgDelivery.Main then
    LSignal := TTgWakeSignal.Create;
  while True do
  begin
    FLock.Enter;
    try
      while (FReady.Count = 0) and not FStopping do
      begin
        // Сон вне замка; SetEvent до WaitFor не теряется (см. WakeWorker).
        Inc(FSleepingWorkers);
        FLock.Leave;
        try
          FWorkReady.WaitFor(INFINITE);
        finally
          FLock.Enter;
          Dec(FSleepingWorkers);
        end;
      end;
      if FStopping then
      begin
        // Эстафета остановки: следующий спящий.
        WakeWorker;
        Exit;
      end;
      LLane := FReady.Dequeue;
      LLane.State := TTgLaneState.Running;
      LUpdate := LLane.Items.Dequeue;
      Dec(FCount);
      Inc(FBusy);
      // Сигналы события сливаются: остались готовые полосы — будим следующего.
      if FReady.Count > 0 then
        WakeWorker;
      // Ждущие Post: в очереди появилось место.
      WakeSpaceWaiter;
    finally
      FLock.Leave;
    end;
    // Сбой доставки (исключение мимо Execute) завершает поток: FinishLane
    // тогда передаёт готовые полосы спящему (см. FinishLane).
    LFailed := True;
    try
      Deliver(LUpdate, LSignal);
      LFailed := False;
    finally
      LUpdate := nil;
      FinishLane(LLane, LFailed);
    end;
  end;
end;

procedure TTgDispatchCore.FinishLane(ALane: TTgLane; AFailed: Boolean);
begin
  FLock.Enter;
  try
    Dec(FBusy);
    if ALane.Items.Count > 0 then
    begin
      // В конец общей очереди: другие чаты не голодают.
      ALane.State := TTgLaneState.Ready;
      FReady.Enqueue(ALane);
    end
    else
    begin
      if ALane.Keyed then
        FLanes.Remove(ALane.Key);
      ALane.Free;
    end;
    // Обычно не будим: этот поток сразу вернётся в WorkerLoop и сам возьмёт
    // голову FReady (остались ещё — разбудит следующего там же). Полосы,
    // поставленные в FReady, пока он был занят, будили спящих сами (Post),
    // а при отсутствии спящих их возьмёт любой вернувшийся поток. При сбое
    // доставки поток выходит и за FReady не вернётся — передаём спящему.
    if AFailed and (FReady.Count > 0) then
      WakeWorker;
    if (FCount = 0) and (FBusy = 0) then
      FIdle.SetEvent;
  finally
    FLock.Leave;
  end;
end;

procedure TTgDispatchCore.Deliver(const AUpdate: ITgRawUpdate; const ASignal: ITgWakeSignal);
begin
  if FDelivery = TTgDelivery.Main then
    DeliverMain(AUpdate, ASignal)
  else
    Execute(AUpdate);
end;

procedure TTgDispatchCore.DeliverMain(const AUpdate: ITgRawUpdate; const ASignal: ITgWakeSignal);
var
  LJob: ITgMainJob;
  LCore: ITgDispatchCore;
  LRegistration: IInterface;
begin
  LJob := TTgMainJob.Create(ASignal);
  LCore := Self;
  // Отмена диспетчера будит ожидание: не начатое задание бросается.
  LRegistration := FCancel.Register(NewJobWakeCallback(LJob));
  try
    // Процедура привязана к потоку диспетчера: TThread.Destroy вызывает
    // RemoveQueuedEvents(Self) — брошенное задание снимается из очереди
    // главного потока вместе с потоком (без CheckSynchronize замыкание с
    // ядром не висит до выхода). Выполнится раньше — TryStart откажет.
    TThread.Queue(TThread.CurrentThread, NewMainJobProc(LCore, LJob, AUpdate));
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
  LSignal: ITgWakeSignal;
  LLane: TTgLane;
  LKey: string;
  LWatch: TStopwatch;
  LLeft: Int64;
  LWaitMs: Cardinal;
  LRegistered: Boolean;
begin
  LRegistration := nil;
  LRegistered := False;
  LSignal := nil;
  LKey := AUpdate.ChatKey;
  LWatch := TStopwatch.StartNew;
  FLock.Enter;
  try
    while (FCount >= FCapacity) and not FStopping and
      not (Assigned(ACancel) and ACancel.IsCancelled) do
    begin
      // Срок — первым: TryPost с нулевым (истёкшим) сроком не подписывается
      // на отмену и не встаёт в список ждущих.
      if ATimeoutMs = INFINITE then
        LWaitMs := INFINITE
      else
      begin
        // Ограниченное ожидание (webhook): очередь так и не освободилась — отказ.
        LLeft := Int64(ATimeoutMs) - LWatch.ElapsedMilliseconds;
        if LLeft <= 0 then
          Exit(False);
        LWaitMs := Cardinal(Min(LLeft, CPostWaitSliceMs));
      end;
      // Личный сигнал из пула — один на весь Post: встаёт в конец списка
      // ждущих при первой блокировке и стоит там до выхода (очерёдность
      // сохраняется). Выставляют его под замком освобождение места
      // (первому, эстафетой), BeginStop и отмена ACancel (WakeWaiters).
      if not Assigned(LSignal) then
      begin
        LSignal := AcquireSignal;
        FSpaceWaiters.Add(LSignal);
      end;
      // Отмена ACancel будит ожидание места (подписка — один раз, только при
      // блокировке; флаг, а не проверка nil: сторонний токен мог вернуть nil
      // без отмены). Register — вне замка: у отменённого токена колбэк
      // (WakeWaiters) выполняется сразу, чужой код под замком ядра не вызываем.
      if Assigned(ACancel) and not LRegistered then
      begin
        LRegistered := True;
        FLock.Leave;
        try
          LRegistration := ACancel.Register(NewPulseCallback(Self));
        finally
          FLock.Enter;
        end;
        Continue;
      end;
      FLock.Leave;
      try
        LSignal.WaitFor(LWaitMs);
      finally
        FLock.Enter;
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
      WakeWorker;
    end;
    Result := True;
  finally
    try
      // Сначала — из списка ждущих: вне списка сигнал никто не выставит
      // (Signal — только под замком и только списку). Оставшийся
      // выставленным даст следующему владельцу из пула лишний виток.
      if Assigned(LSignal) then
      begin
        FSpaceWaiters.Remove(LSignal);
        FSignalPool.Push(LSignal);
        LSignal := nil;
      end;
      // Эстафета при любом выходе (место занято, срок, отмена): место ещё
      // есть — будим следующего ждущего.
      WakeSpaceWaiter;
    finally
      FLock.Leave;
    end;
  end;
end;

procedure TTgDispatchCore.BeginStop;
var
  LLane: TTgLane;
begin
  FLock.Enter;
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
    // Спящие потоки — эстафетой (см. WorkerLoop), ждущие Post — все.
    WakeWorker;
    WakeSpaceWaiters;
  finally
    FLock.Leave;
  end;
  FCancel.Cancel;
end;

function TTgDispatchCore.Stopping: Boolean;
begin
  FLock.Enter;
  try
    Result := FStopping;
  finally
    FLock.Leave;
  end;
end;

procedure TTgDispatchCore.WakeWaiters;
begin
  // Колбэк отмены держит ядро (интерфейс), не сигнал: поздний вызов после
  // снятия подписки безопасен — список ждущих уже без этого Post.
  // Отмена любого токена ACancel будит всех ждущих места в этом ядре, а не
  // только Post с этим токеном: прочие сделают лишний виток и снова уснут.
  // Допустимо — отмена редкая, а сигнал на токен не хранится.
  FLock.Enter;
  try
    WakeSpaceWaiters;
  finally
    FLock.Leave;
  end;
end;

function TTgDispatchCore.GetAllExited: TEvent;
begin
  Result := FAllExited;
end;

function TTgDispatchCore.GetIdle: TEvent;
begin
  Result := FIdle;
end;

function TTgDispatchCore.GetCancel: ITgCancellation;
begin
  Result := FCancel;
end;

{ TTgUpdateDispatcher }

constructor TTgUpdateDispatcher.Create(const AHandler: TTgRawHandler);
begin
  inherited Create;
  if not Assigned(AHandler) then
    raise EArgumentNilException.Create(TgLangTextFmt(@SRuArgNil, @SEnArgNil, ['AHandler']));
  FLock := TCriticalSection.Create;
  FHandler := AHandler;
  FMaxParallel := TgDefaultMaxParallel;
  FQueueCapacity := TgDefaultQueueCapacity;
  FDelivery := TTgDelivery.Worker;
end;

class function TTgUpdateDispatcher.New(const AHandler: TTgRawHandler): ITgUpdateDispatcher;
begin
  Result := TTgUpdateDispatcher.Create(AHandler);
end;

destructor TTgUpdateDispatcher.Destroy;
var
  LCore: ITgDispatchCore;
  LFirst: Boolean;
begin
  if Assigned(FLock) then
  begin
    LCore := CurrentCore;
    if Assigned(LCore) then
    begin
      // Потоки (FreeOnTerminate) держат ядро сами: зависший обработчик не ждём.
      // После Stop повторно не ждём; из обработчика ждать нечего (свой поток).
      LFirst := not LCore.Stopping;
      LCore.BeginStop;
      if LFirst and (GTgHandlerDepth = 0) then
        LCore.AllExited.WaitFor(TgDestroyGraceMs);
    end;
    LCore := nil;
  end;
  FCore := nil;
  FreeAndNil(FLock);
  inherited Destroy;
end;

function TTgUpdateDispatcher.CurrentCore: ITgDispatchCore;
begin
  FLock.Enter;
  try
    Result := FCore;
  finally
    FLock.Leave;
  end;
end;

procedure TTgUpdateDispatcher.Start;
var
  LCore: ITgDispatchCore;
  LThreads: TArray<TTgDispatchThread>;
  I: Integer;
begin
  FLock.Enter;
  try
    if Assigned(FCore) and not FCore.Stopping then
      raise ETgError.Create(TgUpdatesText(TTgUpdatesText.DispatcherRunning));
    LCore := TTgDispatchCore.Create(Self);
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
  finally
    FLock.Leave;
  end;
  for I := 0 to High(LThreads) do
    LThreads[I].Start;
end;

function TTgUpdateDispatcher.Stop(AWaitMs: Cardinal): Boolean;
var
  LCore: ITgDispatchCore;
begin
  LCore := CurrentCore;
  if not Assigned(LCore) then
    Exit(True);
  LCore.BeginStop;
  Result := TgWaitEventPumping(LCore.AllExited, AWaitMs);
end;

function TTgUpdateDispatcher.WaitIdle(AMs: Cardinal): Boolean;
var
  LCore: ITgDispatchCore;
begin
  LCore := CurrentCore;
  Result := not Assigned(LCore) or TgWaitEventPumping(LCore.Idle, AMs);
end;

function TTgUpdateDispatcher.Post(const AUpdate: ITgRawUpdate;
  const ACancel: ITgCancellation): Boolean;
var
  LCore: ITgDispatchCore;
begin
  LCore := CurrentCore;
  Result := Assigned(LCore) and Assigned(AUpdate) and
    LCore.Post(AUpdate, ACancel, INFINITE);
end;

function TTgUpdateDispatcher.TryPost(const AUpdate: ITgRawUpdate;
  const ACancel: ITgCancellation; ATimeoutMs: Cardinal): Boolean;
var
  LCore: ITgDispatchCore;
begin
  LCore := CurrentCore;
  Result := Assigned(LCore) and Assigned(AUpdate) and
    LCore.Post(AUpdate, ACancel, ATimeoutMs);
end;

class function TTgUpdateDispatcher.InHandler: Boolean;
begin
  Result := GTgHandlerDepth > 0;
end;

function TTgUpdateDispatcher.GetActive: Boolean;
var
  LCore: ITgDispatchCore;
begin
  LCore := CurrentCore;
  Result := Assigned(LCore) and not LCore.Stopping;
end;

function TTgUpdateDispatcher.GetCancel: ITgCancellation;
var
  LCore: ITgDispatchCore;
begin
  LCore := CurrentCore;
  if Assigned(LCore) then
    Result := LCore.Cancel
  else
    Result := nil;
end;

function TTgUpdateDispatcher.GetMaxParallel: Integer;
begin
  Result := FMaxParallel;
end;

procedure TTgUpdateDispatcher.SetMaxParallel(AValue: Integer);
begin
  FMaxParallel := AValue;
end;

function TTgUpdateDispatcher.GetQueueCapacity: Integer;
begin
  Result := FQueueCapacity;
end;

procedure TTgUpdateDispatcher.SetQueueCapacity(AValue: Integer);
begin
  FQueueCapacity := AValue;
end;

function TTgUpdateDispatcher.GetDelivery: TTgDelivery;
begin
  Result := FDelivery;
end;

procedure TTgUpdateDispatcher.SetDelivery(AValue: TTgDelivery);
begin
  FDelivery := AValue;
end;

function TTgUpdateDispatcher.GetOnError: TTgRawErrorHandler;
begin
  Result := FOnError;
end;

procedure TTgUpdateDispatcher.SetOnError(const AValue: TTgRawErrorHandler);
begin
  FOnError := AValue;
end;

function TTgUpdateDispatcher.GetOnProcessed: TProc<Int64>;
begin
  Result := FOnProcessed;
end;

procedure TTgUpdateDispatcher.SetOnProcessed(const AValue: TProc<Int64>);
begin
  FOnProcessed := AValue;
end;

end.
