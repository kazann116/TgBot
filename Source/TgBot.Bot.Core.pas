unit TgBot.Bot.Core;

{
  TgBot — внутреннее ядро бота TTgBot. Служебный модуль, не подключать
  напрямую: не часть публичного API библиотеки, пользователю достаточно
  uses TgBot (TTgBotState реэкспортируется псевдонимом).

  Содержит интерфейс ядра ITgBotCore и его реализацию (класс — в
  implementation, создаётся TgCreateBotCore), фоновую подготовку запуска
  (getMe, setMyCommands), транспорт-обёртку webhook-источника
  (OnWebhookRegistered) и фабрики обработчиков источника и диспетчера.
  Бот (TgBot.Bot) обращается к ядру только через ITgBotCore.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  TgBot.Base,
  TgBot.Http,
  TgBot.Types,
  TgBot.Updates,
  TgBot.State,
  TgBot.Context,
  TgBot.Router;

type
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

  /// <summary>
  ///   Ядро TTgBot со счётчиком ссылок (создаёт TgCreateBotCore): владеет
  ///   клиентом (TTgApi), хранилищем состояния, обработчиками, правилами
  ///   маршрутизатора, AutoAnswerCallbacks и состоянием бота (TTgBotState).
  ///   Держат его TTgBot, замыкания диспетчера/источника и каждый
  ///   TTgContext; само ядро ни на кого из них не ссылается (нет циклов).
  ///   Поля — под внутренней блокировкой; обработчики вызываются со снимка
  ///   вне блокировки. Сеттеры освобождают прежнее значение (замыкание,
  ///   хранилище, массив правил) вне блокировки.
  ///   После Detach (Free бота) обработчики сброшены, OnError, OnFault и
  ///   автоответ не вызываются, клиент закрыт (вызовы — ETgCancelledError);
  ///   клиент освобождается с последней ссылкой на ядро.
  /// </summary>
  ITgBotCore = interface
    ['{6B0C2E4A-3D51-4F8E-9A7B-2C1D5E8F9A30}']
    { Обновления и события источника }

    /// <summary>
    ///   Обработка обновления (поток диспетчера): контекст, OnUpdate,
    ///   маршрутизатор, OnMessage/OnCallbackQuery, автоответ на нажатие.
    /// </summary>
    procedure HandleRaw(const AUpdate: ITgRawUpdate);
    /// <summary>
    ///   OnError(AError, AContext); исключения OnError поглощаются. Отмена
    ///   обработчика при остановке бота и вызов после Detach — без OnError.
    /// </summary>
    procedure NotifyError(AError: Exception; const AContext: ITgContext);
    /// <summary>OnConflict (поток источника); после Detach не вызывается.</summary>
    procedure NotifyConflict(AError: ETgConflictError);
    /// <summary>
    ///   Отказ источника запуска AGeneration: Running → Faulted, затем
    ///   OnError(E, nil) и OnFault(E) (снимки под блокировкой). Не в Running,
    ///   чужой запуск или после Detach — ничего. Пока они выполняются,
    ///   TgInFaultNotify в этом потоке = True.
    /// </summary>
    procedure NotifyFault(AError: Exception; AGeneration: Integer);
    /// <summary>OnWebhookRegistered (снимок под блокировкой), только в Running и до Detach.</summary>
    procedure NotifyWebhookRegistered;

    { Жизненный цикл }

    /// <summary>
    ///   Отсоединение от бота (идемпотентно, не блокирует): Detached,
    ///   сброс обработчиков, Api.Shutdown.
    /// </summary>
    procedure Detach;
    function GetDetached: Boolean;
    /// <summary>Новый запуск: State := Running; результат — его номер.</summary>
    function BeginRun: Integer;
    function GetState: TTgBotState;
    procedure SetState(AValue: TTgBotState);
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
    function GetApi: TTgApi;

    { Настройки и обработчики }

    function GetStateStorage: ITgStateStorage;
    /// <summary>nil — новое хранилище в памяти.</summary>
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

    { Маршрутизатор }

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
    /// <summary>username бота (getMe); '' — ещё не получен.</summary>
    function GetBotUserName: string;

    /// <summary>Клиент Bot API (во владении ядра; не меняется за его жизнь).</summary>
    property Api: TTgApi read GetApi;
    /// <summary>Ядро отсоединено (бот уничтожен).</summary>
    property Detached: Boolean read GetDetached;
  end;

/// <summary>
///   Новое ядро. AApi переходит во владение ядра в любом случае: если ядро
///   не создано (исключение), клиент освобождается здесь.
/// </summary>
function TgCreateBotCore(AApi: TTgApi): ITgBotCore;

/// <summary>
///   Текущий поток выполняет OnError/OnFault отказа источника
///   (ITgBotCore.NotifyFault): Stop/Start отсюда ждали бы завершения этого
///   же потока. Выставляет только ядро.
/// </summary>
function TgInFaultNotify: Boolean;

{ Фабрики обработчиков. Отдельные функции: замыкание захватывает только
  интерфейс ядра (без кадра вызывающего метода и Self бота). }

/// <summary>Обработчик диспетчера: ACore.HandleRaw.</summary>
function TgNewRawHandler(const ACore: ITgBotCore): TTgRawHandler;
/// <summary>Устранимая ошибка приёма (OnError источника): ACore.NotifyError(E, nil).</summary>
function TgNewSourceErrorHandler(const ACore: ITgBotCore): TProc<Exception>;
/// <summary>409 от источника (OnConflict источника): ACore.NotifyConflict.</summary>
function TgNewConflictHandler(const ACore: ITgBotCore): TTgConflictHandler;
/// <summary>
///   Отказ источника (OnFault источника) запуска AGeneration. Назначается при
///   каждом Start: источник копирует обработчик в ядро опроса этого запуска.
/// </summary>
function TgNewFaultHandler(const ACore: ITgBotCore; AGeneration: Integer): TProc<Exception>;
/// <summary>
///   Транспорт webhook-источника поверх ATransport клиента: пропускает вызовы
///   и после успешного setWebhook вызывает ACore.NotifyWebhookRegistered.
///   Удерживает ядро; ядро его не удерживает.
/// </summary>
function TgNewWebhookTransport(const ATransport: ITgTransport; const ACore: ITgBotCore): ITgTransport;

implementation

uses
  System.Classes,
  System.SyncObjs,
  System.JSON,
  System.Threading,
  System.Diagnostics,
  System.Math,
  TgBot.Json,
  TgBot.Core;

type
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

  /// <summary>Реализация ITgBotCore (описание — у интерфейса). Поля под FLock.</summary>
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
    procedure SetBotUserName(const AValue: string);
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
  public
    /// <summary>
    ///   AApi переходит во владение ядра. Присваивается последним: если
    ///   конструктор упадёт раньше, клиент освобождает вызывающий
    ///   (TgCreateBotCore).
    /// </summary>
    constructor Create(AApi: TTgApi);
    destructor Destroy; override;
    { ITgBotCore }
    procedure HandleRaw(const AUpdate: ITgRawUpdate);
    procedure NotifyError(AError: Exception; const AContext: ITgContext);
    procedure NotifyConflict(AError: ETgConflictError);
    procedure NotifyFault(AError: Exception; AGeneration: Integer);
    procedure NotifyWebhookRegistered;
    procedure Detach;
    function GetDetached: Boolean;
    function BeginRun: Integer;
    function GetState: TTgBotState;
    procedure SetState(AValue: TTgBotState);
    procedure BeginStartJob(ASetMyCommands: Boolean);
    function FinishStartJob(AWaitMs: Cardinal): Boolean;
    function GetApi: TTgApi;
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
    procedure SetRoute(AKind: TTgRouteKind; const AKey, ADescription: string;
      const AHandler: TProc<ITgContext>);
    procedure SetMatchRoute(const AMatcher: ITgTextMatcher; const AHandler: TProc<ITgContext>);
    procedure SetAnyText(const AValue: TProc<ITgContext>);
    function GetOnUnknownCommand: TProc<ITgContext>;
    procedure SetOnUnknownCommand(const AValue: TProc<ITgContext>);
    function GetRoutes: TTgRoutes;
    function GetBotUserName: string;
    /// <summary>Ядро отсоединено (бот уничтожен).</summary>
    property Detached: Boolean read GetDetached;
  end;

threadvar
  // Поток выполняет OnError/OnFault отказа источника: Stop/Start отсюда
  // ждали бы завершения этого же потока.
  GTgInFaultNotify: Boolean;

function TgInFaultNotify: Boolean;
begin
  Result := GTgInFaultNotify;
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

function TgNewWebhookTransport(const ATransport: ITgTransport; const ACore: ITgBotCore): ITgTransport;
begin
  if Supports(ATransport, ITgCancellableTransport) then
    Result := TTgWebhookNotifyCancellableTransport.Create(ATransport, ACore)
  else
    Result := TTgWebhookNotifyTransport.Create(ATransport, ACore);
end;

{ Фабрики обработчиков }

function TgNewRawHandler(const ACore: ITgBotCore): TTgRawHandler;
begin
  Result :=
    procedure(const AUpdate: ITgRawUpdate)
    begin
      ACore.HandleRaw(AUpdate);
    end;
end;

function TgNewSourceErrorHandler(const ACore: ITgBotCore): TProc<Exception>;
begin
  Result :=
    procedure(AError: Exception)
    begin
      ACore.NotifyError(AError, nil);
    end;
end;

function TgNewConflictHandler(const ACore: ITgBotCore): TTgConflictHandler;
begin
  Result :=
    procedure(AError: ETgConflictError)
    begin
      ACore.NotifyConflict(AError);
    end;
end;

function TgNewFaultHandler(const ACore: ITgBotCore; AGeneration: Integer): TProc<Exception>;
begin
  Result :=
    procedure(AError: Exception)
    begin
      ACore.NotifyFault(AError, AGeneration);
    end;
end;

function TgCreateBotCore(AApi: TTgApi): ITgBotCore;
begin
  try
    Result := TTgBotCore.Create(AApi);
  except
    // Ядро не создано — клиент ему не передан.
    AApi.Free;
    raise;
  end;
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

function TTgBotCore.GetApi: TTgApi;
begin
  // Без блокировки: задаётся в конструкторе и не меняется до деструктора.
  Result := FApi;
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
    LIsCommand := (AUpdate.Kind = TTgUpdateType.Message) and
      TTgRouter.ParseCommand(LContext, ResolveBotUserName);
    if Assigned(LOnUpdate) then
      LOnUpdate(LRef);
    // OnUpdate может перехватить обновление (ACtx.Handled := True).
    if not LContext.GetHandled then
    begin
      if AUpdate.Kind = TTgUpdateType.Message then
      begin
        TTgRouter.RouteMessage(LContext, LRoutes, LIsCommand);
        // OnMessage — только если ни одно правило не обработало сообщение.
        if not LContext.GetHandled and Assigned(LOnMessage) then
          LOnMessage(LRef);
      end
      else if AUpdate.Kind = TTgUpdateType.CallbackQuery then
      begin
        TTgRouter.RouteCallback(LContext, LRoutes);
        if not LContext.GetHandled and Assigned(LOnCallbackQuery) then
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

end.
