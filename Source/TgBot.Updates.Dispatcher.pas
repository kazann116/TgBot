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
  реэкспортируется там псевдонимом. ITgDispatchCore — служебный, не
  используйте его напрямую.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.SyncObjs,
  TgBot.Base,
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

  /// <summary>Внутреннее состояние одного запуска диспетчера (ITgDispatchCore).</summary>
  TTgDispatchCore = class(TInterfacedObject, ITgDispatchCore)
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
    FCancel: ITgCancellationSource;
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
  ///   очереди ничего не сделает).
  /// </summary>
  TTgMainJob = class(TInterfacedObject, ITgMainJob)
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
  FLock := TObject.Create;
  FLanes := TDictionary<string, TTgLane>.Create;
  FReady := TQueue<TTgLane>.Create;
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
  LJob: ITgMainJob;
  LCore: ITgDispatchCore;
  LRegistration: IInterface;
begin
  LJob := TTgMainJob.Create;
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
  FCancel.Cancel;
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

procedure TTgDispatchCore.WakeWaiters;
begin
  TMonitor.Enter(FLock);
  try
    TMonitor.PulseAll(FLock);
  finally
    TMonitor.Exit(FLock);
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

end.
