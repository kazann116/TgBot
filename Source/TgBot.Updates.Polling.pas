unit TgBot.Updates.Polling;

{
  TgBot — источник обновлений long polling TTgLongPollSource (getUpdates
  в собственном потоке): offset и политики подтверждения, паузы с
  разбросом при ошибках, обработка 401/404/409, остановка с дренажом и
  итоговым подтверждением offset.

  Состояние одного запуска (ядро) скрыто за служебным интерфейсом
  ITgPollCore, реализация — в implementation. Источник (до следующего
  Start или Free) и поток опроса держат ядро только через этот интерфейс,
  поэтому Stop может «отпустить» поток, который не удалось прервать
  (транспорт без отмены, Linux/Android), — его поздний результат
  выбрасывается.

  Пользователю достаточно uses TgBot.Updates (или TgBot): TTgLongPollSource
  реэкспортируется там псевдонимом. ITgPollCore — служебный, не
  используйте его напрямую.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.SyncObjs,
  TgBot.Base,
  TgBot.Http,
  TgBot.Updates.Types;

type
  /// <summary>
  ///   Служебное, не часть публичного API (не используйте напрямую): ядро
  ///   одного запуска TTgLongPollSource — настройки, offset, необработанные
  ///   update_id, токены отмены опроса и итогового запроса. Держат его
  ///   источник (до следующего Start или Free) и поток опроса; последний
  ///   освободивший — уничтожает.
  /// </summary>
  ITgPollCore = interface
    ['{EC805A84-1A5E-480D-886E-FD380224A9D4}']
    /// <summary>Тело потока опроса: getUpdates до остановки или Faulted, затем дренаж.</summary>
    procedure Run;
    /// <summary>Запрос остановки: отмена висящего getUpdates, бюджет дренажа — AWaitMs / 2.</summary>
    procedure RequestStop(AWaitMs: Cardinal);
    /// <summary>Прерывает дренаж и итоговый getUpdates.</summary>
    procedure CancelFinal;
    /// <summary>Поток отпущен: его поздний результат выбрасывается, состояние — Idle.</summary>
    procedure Abandon;
    /// <summary>Обновление AUpdateId обработано.</summary>
    procedure Processed(AUpdateId: Int64);
    /// <summary>Состояние запуска.</summary>
    function State: TTgSourceState;
    /// <summary>offset следующего getUpdates.</summary>
    function Offset: Int64;
    /// <summary>offset, подтверждённый серверу.</summary>
    function ConfirmedOffset: Int64;
    /// <summary>С какого offset продолжить при следующем Start.</summary>
    function ResumeOffset: Int64;
    /// <summary>RequestStop уже вызван.</summary>
    function IsStopRequested: Boolean;
    function GetDone: TEvent;
    /// <summary>Поток опроса завершил Run.</summary>
    property Done: TEvent read GetDone;
  end;

  /// <summary>
  ///   Long polling (getUpdates) в собственном потоке. Настройки задаются до
  ///   Start. События OnConflict/OnError/OnFault вызываются в потоке
  ///   источника, их исключения поглощаются.
  ///
  ///   Ошибки: сеть, 5xx, прочие — пауза 1, 2, 4 … 60 с (± JitterPercent),
  ///   прерываемая Stop, сброс после успешного ответа; 429 — не меньше
  ///   retry_after; 401/404 — Faulted без повторов; 409 «webhook is active» —
  ///   deleteWebhook и повтор (AutoDeleteWebhook) или OnConflict + Faulted;
  ///   409 «другой getUpdates» — OnConflict (не чаще ConflictNotifyIntervalMs)
  ///   и повтор не раньше чем через 5 с.
  ///
  ///   Остановка: отмена висящего запроса (Windows/macOS — прерывание HTTP;
  ///   Linux/Android и транспорт без отмены — поток отпускается), дренаж
  ///   принятых обновлений (Processed) не дольше DrainTimeoutMs (и половины
  ///   AWaitMs), итоговый getUpdates(offset = наименьший необработанный,
  ///   timeout = 0, limit = 1). Ответ, пришедший после Stop, выбрасывается
  ///   без сдвига offset.
  /// </summary>
  TTgLongPollSource = class(TInterfacedObject, ITgUpdateSource)
  private
    FLock: TCriticalSection;
    FTransport: ITgTransport;
    FParentCancel: ITgCancellation;
    // Ядро текущего (или последнего) запуска, под FLock; nil — Start не вызывался.
    FCore: ITgPollCore;
    FResumeOffset: Int64;
    FLimit: Integer;
    FTimeoutSec: Integer;
    FAllowedUpdates: TTgOptional<TArray<string>>;
    FDropPendingUpdates: Boolean;
    FAutoDeleteWebhook: Boolean;
    FAckPolicy: TTgAckPolicy;
    FDrainTimeoutMs: Cardinal;
    FConflictNotifyIntervalMs: Cardinal;
    FJitterPercent: Integer;
    FTimer: ITgPollTimer;
    FOnConflict: TTgConflictHandler;
    FOnError: TProc<Exception>;
    FOnFault: TProc<Exception>;
    function CurrentCore: ITgPollCore;
    function GetOffset: Int64;
    function GetConfirmedOffset: Int64;
  public
    /// <summary>
    ///   Источник поверх транспорта ATransport (тот же, что у TTgApi). Вызовы
    ///   прерываются и отменой AParentCancel (например, TTgApi.CancelToken).
    /// </summary>
    constructor Create(const ATransport: ITgTransport; const AParentCancel: ITgCancellation = nil);
    /// <summary>
    ///   Не блокирует: запрашивает остановку (отмена висящего getUpdates) и
    ///   ждёт поток не дольше 30 мс. Незавершившийся поток держит своё
    ///   состояние сам: дренаж (не дольше DrainTimeoutMs) и итоговое
    ///   подтверждение выполняются в фоне, затем поток освобождается. Для
    ///   гарантированного подтверждения до выхода из программы — Stop.
    /// </summary>
    destructor Destroy; override;
    procedure Start(const ASink: ITgUpdateSink);
    function Stop(AWaitMs: Cardinal): Boolean;
    procedure Processed(AUpdateId: Int64);
    function GetState: TTgSourceState;
    /// <summary>
    ///   Ждёт фактического завершения потока источника (в т.ч. отпущенного
    ///   при Stop = False). True — поток завершён или не запускался.
    /// </summary>
    function WaitForThread(AMs: Cardinal): Boolean;
    /// <summary>Состояние источника.</summary>
    property State: TTgSourceState read GetState;
    /// <summary>offset следующего запроса getUpdates (последний принятый update_id + 1; 0 — не было).</summary>
    property Offset: Int64 read GetOffset;
    /// <summary>offset, подтверждённый серверу (последний успешный getUpdates или итоговый).</summary>
    property ConfirmedOffset: Int64 read GetConfirmedOffset;
    /// <summary>limit getUpdates (1–100), по умолчанию TgDefaultPollLimit.</summary>
    property Limit: Integer read FLimit write FLimit;
    /// <summary>timeout getUpdates, с (0 — короткий опрос), по умолчанию TgDefaultPollTimeoutSec.</summary>
    property TimeoutSec: Integer read FTimeoutSec write FTimeoutSec;
    /// <summary>
    ///   allowed_updates (TTgUpdateType.*). Не задано — не передаётся (сервер
    ///   помнит прежнее значение); пустой массив — все, кроме chat_member,
    ///   message_reaction и message_reaction_count. TTgBot при Start всегда
    ///   задаёт значение (без явного TTgBot.AllowedUpdates — пустой массив).
    /// </summary>
    property AllowedUpdates: TTgOptional<TArray<string>> read FAllowedUpdates write FAllowedUpdates;
    /// <summary>При старте вызвать deleteWebhook(drop_pending_updates = true): пропустить накопившееся.</summary>
    property DropPendingUpdates: Boolean read FDropPendingUpdates write FDropPendingUpdates;
    /// <summary>При 409 «webhook is active» удалить webhook и продолжить (по умолчанию False).</summary>
    property AutoDeleteWebhook: Boolean read FAutoDeleteWebhook write FAutoDeleteWebhook;
    /// <summary>Политика подтверждения, по умолчанию AfterReceive.</summary>
    property AckPolicy: TTgAckPolicy read FAckPolicy write FAckPolicy;
    /// <summary>Дренаж при Stop, мс (по умолчанию TgDefaultDrainTimeoutMs).</summary>
    property DrainTimeoutMs: Cardinal read FDrainTimeoutMs write FDrainTimeoutMs;
    /// <summary>Минимальный интервал OnConflict для «другого getUpdates», мс.</summary>
    property ConflictNotifyIntervalMs: Cardinal read FConflictNotifyIntervalMs
      write FConflictNotifyIntervalMs;
    /// <summary>Разброс пауз, ± процентов (0–50), по умолчанию 20.</summary>
    property JitterPercent: Integer read FJitterPercent write FJitterPercent;
    /// <summary>Часы и паузы (nil — системные).</summary>
    property Timer: ITgPollTimer read FTimer write FTimer;
    /// <summary>409: другой экземпляр бота или установлен webhook.</summary>
    property OnConflict: TTgConflictHandler read FOnConflict write FOnConflict;
    /// <summary>Временная ошибка getUpdates (перед паузой и повтором).</summary>
    property OnError: TProc<Exception> read FOnError write FOnError;
    /// <summary>Неустранимая ошибка: источник перешёл в Faulted.</summary>
    property OnFault: TProc<Exception> read FOnFault write FOnFault;
  end;

implementation

uses
  System.Classes,
  System.Generics.Collections,
  System.Diagnostics,
  System.JSON,
  System.Math,
  System.StrUtils,
  TgBot.Json;

type
  /// <summary>
  ///   Внутреннее состояние одного запуска TTgLongPollSource (ITgPollCore).
  ///   Поток источника держит только ссылку на него, поэтому может пережить
  ///   сам источник.
  /// </summary>
  TTgPollCore = class(TInterfacedObject, ITgPollCore)
  private
    FLock: TCriticalSection;
    FWake: TEvent;
    FDone: TEvent;
    FTransport: ITgTransport;
    FPollSource: TTgCancellationSource;
    FPollToken: ITgCancellation;
    FFinalSource: TTgCancellationSource;
    FFinalToken: ITgCancellation;
    FSink: ITgUpdateSink;
    FTimer: ITgPollTimer;
    // Настройки (неизменны после создания).
    FLimit: Integer;
    FTimeoutSec: Integer;
    FAllowed: TTgOptional<TArray<string>>;
    FDropPending: Boolean;
    FAutoDeleteWebhook: Boolean;
    FAckPolicy: TTgAckPolicy;
    FDrainTimeoutMs: Cardinal;
    FConflictNotifyMs: Int64;
    FJitterPercent: Integer;
    FOnConflict: TTgConflictHandler;
    FOnError: TProc<Exception>;
    FOnFault: TProc<Exception>;
    // Состояние (под FLock).
    FState: TTgSourceState;
    FStopRequested: Boolean;
    FAbandoned: Boolean;
    FDrainLimitMs: Cardinal;
    FOffset: Int64;
    FConfirmedOffset: Int64;
    FPending: TList<Int64>;
    // Только поток источника.
    FBackoffStep: Integer;
    FWebhookRetries: Integer;
    FConflictNotified: Boolean;
    FLastConflictNotifyMs: Int64;
    FRandom: Cardinal;
    function NextRandom: Double;
    function NextBackoff: Cardinal;
    function Pause(AMs: Cardinal): Boolean;
    function Fetch(AOffset: Int64; ATimeoutSec, ALimit: Integer;
      const AToken: ITgCancellation): TJSONArray;
    procedure DeleteWebhook(ADropPending: Boolean);
    function Prepare: Boolean;
    function WaitBatchProcessed: Boolean;
    function PollOnce: Boolean;
    function AcceptBatch(AArray: TJSONArray; ARequestOffset: Int64): Boolean;
    function HandleFailure(AError: Exception): Boolean;
    function HandleConflict(AError: ETgConflictError): Boolean;
    procedure Fault(AError: Exception);
    procedure FinishGracefully;
    procedure NotifyError(AError: Exception);
    procedure NotifyConflict(AError: ETgConflictError);
  public
    constructor Create(const ATransport: ITgTransport; const AParentCancel: ITgCancellation;
      const ASink: ITgUpdateSink; ASource: TTgLongPollSource; AStartOffset: Int64);
    destructor Destroy; override;
    /// <summary>Тело потока.</summary>
    procedure Run;
    procedure RequestStop(AWaitMs: Cardinal);
    procedure CancelFinal;
    procedure Abandon;
    procedure Processed(AUpdateId: Int64);
    function State: TTgSourceState;
    function Offset: Int64;
    function ConfirmedOffset: Int64;
    /// <summary>С какого offset продолжить при следующем Start.</summary>
    function ResumeOffset: Int64;
    function IsStopRequested: Boolean;
    function GetDone: TEvent;
  end;

  /// <summary>Поток long polling (FreeOnTerminate).</summary>
  TTgPollThread = class(TThread)
  private
    FCore: ITgPollCore;
  protected
    procedure Execute; override;
  public
    constructor Create(const ACore: ITgPollCore);
  end;

{ TTgPollThread }

constructor TTgPollThread.Create(const ACore: ITgPollCore);
begin
  inherited Create(True);
  FCore := ACore;
  FreeOnTerminate := True;
end;

procedure TTgPollThread.Execute;
var
  LName: string;
begin
  LName := 'TgBot.LongPoll';
  NameThreadForDebugging(LName);
  try
    FCore.Run;
  finally
    FCore := nil;
  end;
end;

{ TTgPollCore }

constructor TTgPollCore.Create(const ATransport: ITgTransport;
  const AParentCancel: ITgCancellation; const ASink: ITgUpdateSink;
  ASource: TTgLongPollSource; AStartOffset: Int64);
begin
  inherited Create;
  FLock := TCriticalSection.Create;
  FWake := TEvent.Create(nil, False, False, '');
  FDone := TEvent.Create(nil, True, False, '');
  FPending := TList<Int64>.Create;
  FTransport := ATransport;
  FPollSource := TTgCancellationSource.Create(AParentCancel);
  FPollToken := FPollSource;
  FFinalSource := TTgCancellationSource.Create(AParentCancel);
  FFinalToken := FFinalSource;
  FSink := ASink;
  FTimer := ASource.FTimer;
  if not Assigned(FTimer) then
    FTimer := TTgSystemPollTimer.Create;
  FLimit := EnsureRange(ASource.FLimit, 1, 100);
  FTimeoutSec := Max(ASource.FTimeoutSec, 0);
  FAllowed := ASource.FAllowedUpdates;
  FDropPending := ASource.FDropPendingUpdates;
  FAutoDeleteWebhook := ASource.FAutoDeleteWebhook;
  FAckPolicy := ASource.FAckPolicy;
  FDrainTimeoutMs := ASource.FDrainTimeoutMs;
  FConflictNotifyMs := ASource.FConflictNotifyIntervalMs;
  FJitterPercent := EnsureRange(ASource.FJitterPercent, 0, 50);
  FOnConflict := ASource.FOnConflict;
  FOnError := ASource.FOnError;
  FOnFault := ASource.FOnFault;
  FState := TTgSourceState.Running;
  FOffset := AStartOffset;
  FConfirmedOffset := 0;
  FDrainLimitMs := FDrainTimeoutMs;
  // Затравка генератора разброса: время и адрес — разные экземпляры не синхронны.
  FRandom := Cardinal(TThread.GetTickCount) xor Cardinal(NativeUInt(Self) shr 4) or 1;
end;

destructor TTgPollCore.Destroy;
begin
  FreeAndNil(FPending);
  FreeAndNil(FDone);
  FreeAndNil(FWake);
  FreeAndNil(FLock);
  FPollToken := nil;
  FFinalToken := nil;
  inherited Destroy;
end;

function TTgPollCore.IsStopRequested: Boolean;
begin
  FLock.Enter;
  try
    Result := FStopRequested;
  finally
    FLock.Leave;
  end;
end;

function TTgPollCore.NextRandom: Double;
begin
  // xorshift32: только поток источника, без общего RandSeed.
  FRandom := FRandom xor (FRandom shl 13);
  FRandom := FRandom xor (FRandom shr 17);
  FRandom := FRandom xor (FRandom shl 5);
  Result := FRandom / 4294967296.0;
end;

function TTgPollCore.NextBackoff: Cardinal;
var
  LBase: Int64;
  LDelta: Int64;
begin
  LBase := Min(Int64(TgBackoffMinMs) shl Min(FBackoffStep, 6), TgBackoffMaxMs);
  Inc(FBackoffStep);
  if FJitterPercent > 0 then
  begin
    LDelta := Round(LBase * FJitterPercent / 100 * (2 * NextRandom - 1));
    LBase := Max(LBase + LDelta, 0);
  end;
  Result := Cardinal(LBase);
end;

function TTgPollCore.Pause(AMs: Cardinal): Boolean;
begin
  // True — продолжать; False — пауза прервана остановкой.
  Result := not FTimer.Sleep(AMs, FPollToken) and not IsStopRequested;
end;

function TTgPollCore.Fetch(AOffset: Int64; ATimeoutSec, ALimit: Integer;
  const AToken: ITgCancellation): TJSONArray;
var
  LParams: TTgParams;
  LResult: TJSONValue;
begin
  LParams := TTgParams.Create;
  try
    if AOffset <> 0 then
      LParams.Add('offset', AOffset);
    LParams.Add('limit', ALimit);
    LParams.Add('timeout', ATimeoutSec);
    if FAllowed.HasValue then
      LParams.AddStrings('allowed_updates', FAllowed.Value);
    LResult := TgCallTransport(FTransport, 'getUpdates', LParams, AToken);
  finally
    LParams.Free;
  end;
  if not (LResult is TJSONArray) then
  begin
    LResult.Free;
    raise ETgError.Create(TgTextFmt(TTgText.UnexpectedResult, ['getUpdates']));
  end;
  Result := TJSONArray(LResult);
end;

procedure TTgPollCore.DeleteWebhook(ADropPending: Boolean);
var
  LParams: TTgParams;
begin
  LParams := TTgParams.Create;
  try
    if ADropPending then
      LParams.Add('drop_pending_updates', True);
    TgCallTransport(FTransport, 'deleteWebhook', LParams, FPollToken).Free;
  finally
    LParams.Free;
  end;
end;

function TTgPollCore.Prepare: Boolean;
begin
  // deleteWebhook(drop_pending_updates) до первого getUpdates, с повторами.
  Result := True;
  if not FDropPending then
    Exit;
  while not IsStopRequested do
  begin
    try
      DeleteWebhook(True);
      FBackoffStep := 0;
      Exit(True);
    except
      on E: Exception do
        if not HandleFailure(E) then
          Exit(False);
    end;
  end;
  Result := False;
end;

function TTgPollCore.WaitBatchProcessed: Boolean;
var
  LEmpty, LStop: Boolean;
begin
  if FAckPolicy <> TTgAckPolicy.AfterBatch then
    Exit(not IsStopRequested);
  while True do
  begin
    FLock.Enter;
    try
      LEmpty := FPending.Count = 0;
      LStop := FStopRequested;
    finally
      FLock.Leave;
    end;
    if LStop then
      Exit(False);
    if LEmpty then
      Exit(True);
    // Будит Processed (очередь пуста) и RequestStop.
    FWake.WaitFor(INFINITE);
  end;
end;

function TTgPollCore.PollOnce: Boolean;
var
  LOffset: Int64;
  LArray: TJSONArray;
begin
  FLock.Enter;
  try
    LOffset := FOffset;
  finally
    FLock.Leave;
  end;
  try
    LArray := Fetch(LOffset, FTimeoutSec, FLimit, FPollToken);
  except
    on E: Exception do
      Exit(HandleFailure(E));
  end;
  try
    Result := AcceptBatch(LArray, LOffset);
  finally
    LArray.Free;
  end;
end;

function TTgPollCore.AcceptBatch(AArray: TJSONArray; ARequestOffset: Int64): Boolean;
var
  LUpdates: TList<ITgRawUpdate>;
  LValue: TJSONValue;
  LUpdate: ITgRawUpdate;
  I: Integer;
begin
  LUpdates := TList<ITgRawUpdate>.Create;
  try
    // Элементы вынимаются из массива без копирования: владение — у обновлений.
    while AArray.Count > 0 do
    begin
      LValue := AArray.Remove(0);
      if not (LValue is TJSONObject) then
      begin
        LValue.Free;
        Continue;
      end;
      try
        LUpdate := TTgRawUpdate.Create(TJSONObject(LValue));
      except
        // Конструктор уже освободил JSON; некорректный элемент пропускается.
        Continue;
      end;
      LUpdates.Add(LUpdate);
      LUpdate := nil;
    end;
    FLock.Enter;
    try
      // Ответ после Stop (отпущенный поток) выбрасывается без сдвига offset.
      if FStopRequested then
        Exit(False);
      FConfirmedOffset := Max(FConfirmedOffset, ARequestOffset);
      FBackoffStep := 0;
      FWebhookRetries := 0;
      for I := LUpdates.Count - 1 downto 0 do
        if (FOffset <> 0) and (LUpdates[I].UpdateId < FOffset) then
          LUpdates.Delete(I);
      for I := 0 to LUpdates.Count - 1 do
      begin
        FPending.Add(LUpdates[I].UpdateId);
        FOffset := Max(FOffset, LUpdates[I].UpdateId + 1);
      end;
    finally
      FLock.Leave;
    end;
    // Не принятые приёмником обновления остаются необработанными (итоговый offset).
    for I := 0 to LUpdates.Count - 1 do
      if not FSink.Post(LUpdates[I], FPollToken) then
        Exit(False);
    Result := True;
  finally
    LUpdates.Free;
  end;
end;

function TTgPollCore.HandleFailure(AError: Exception): Boolean;
var
  LDelay: Cardinal;
begin
  if IsStopRequested then
    Exit(False);
  // Отмена без Stop — отменён родительский токен (клиент уничтожается).
  if AError is ETgCancelledError then
  begin
    Fault(AError);
    Exit(False);
  end;
  if AError is ETgConflictError then
    Exit(HandleConflict(ETgConflictError(AError)));
  if (AError is ETgApiError) and ((ETgApiError(AError).ErrorCode = 401) or
    (ETgApiError(AError).ErrorCode = 404)) then
  begin
    // Неверный токен или адрес Bot API: повторы бессмысленны.
    Fault(AError);
    Exit(False);
  end;
  NotifyError(AError);
  LDelay := NextBackoff;
  if (AError is ETgApiError) and (ETgApiError(AError).RetryAfter > 0) then
    LDelay := Max(LDelay, Cardinal(ETgApiError(AError).RetryAfter) * 1000);
  Result := Pause(LDelay);
end;

function TTgPollCore.HandleConflict(AError: ETgConflictError): Boolean;
var
  LNow: Int64;
begin
  if ContainsText(AError.Description, 'webhook') then
  begin
    if not FAutoDeleteWebhook then
    begin
      NotifyConflict(AError);
      Fault(AError);
      Exit(False);
    end;
    Inc(FWebhookRetries);
    try
      DeleteWebhook(False);
    except
      on E: Exception do
      begin
        if IsStopRequested then
          Exit(False);
        NotifyError(E);
        Exit(Pause(NextBackoff));
      end;
    end;
    // Повтор сразу; если webhook снова установлен (другой процесс) — с паузой.
    if FWebhookRetries > 1 then
      Exit(Pause(NextBackoff));
    Exit(True);
  end;
  // Другой getUpdates с тем же токеном: сообщаем не чаще интервала и ждём.
  LNow := FTimer.NowMs;
  if not FConflictNotified or (LNow - FLastConflictNotifyMs >= FConflictNotifyMs) then
  begin
    FConflictNotified := True;
    FLastConflictNotifyMs := LNow;
    NotifyConflict(AError);
  end;
  Result := Pause(Max(NextBackoff, TgConflictRetryMs));
end;

procedure TTgPollCore.Fault(AError: Exception);
begin
  FLock.Enter;
  try
    // Ошибки после Stop (в т.ч. отпущенного потока) не переводят в Faulted.
    if FStopRequested or FAbandoned then
      Exit;
    FState := TTgSourceState.Faulted;
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

procedure TTgPollCore.NotifyError(AError: Exception);
begin
  if Assigned(FOnError) then
    TgInvokeQuietly(
      procedure
      begin
        FOnError(AError);
      end);
end;

procedure TTgPollCore.NotifyConflict(AError: ETgConflictError);
begin
  if Assigned(FOnConflict) then
    TgInvokeQuietly(
      procedure
      begin
        FOnConflict(AError);
      end);
end;

procedure TTgPollCore.FinishGracefully;
var
  LWatch: TStopwatch;
  LEmpty: Boolean;
  LLeft: Int64;
  LAck: Int64;
  LNeed: Boolean;
begin
  // Дренаж: ждём Processed уже принятых обновлений.
  LWatch := TStopwatch.StartNew;
  while True do
  begin
    FLock.Enter;
    try
      LEmpty := FPending.Count = 0;
      LLeft := Int64(FDrainLimitMs) - LWatch.ElapsedMilliseconds;
      if FAbandoned then
        Exit;
    finally
      FLock.Leave;
    end;
    if LEmpty or (LLeft <= 0) or FFinalToken.IsCancelled then
      Break;
    FWake.WaitFor(Cardinal(Min(LLeft, 100)));
  end;
  // Итоговое подтверждение: offset = наименьший необработанный.
  FLock.Enter;
  try
    if FPending.Count > 0 then
      LAck := FPending[0]
    else
      LAck := FOffset;
    LNeed := (LAck > 0) and (LAck > FConfirmedOffset) and not FAbandoned;
  finally
    FLock.Leave;
  end;
  if not LNeed or FFinalToken.IsCancelled then
    Exit;
  try
    Fetch(LAck, 0, 1, FFinalToken).Free;
    FLock.Enter;
    try
      FConfirmedOffset := Max(FConfirmedOffset, LAck);
    finally
      FLock.Leave;
    end;
  except
    on E: Exception do
      if not (E is ETgCancelledError) then
        NotifyError(E);
  end;
end;

procedure TTgPollCore.Run;
var
  LStopped: Boolean;
begin
  try
    try
      if Prepare then
        while WaitBatchProcessed and PollOnce do
          ;
      FLock.Enter;
      try
        LStopped := FStopRequested and not FAbandoned and
          (FState <> TTgSourceState.Faulted);
      finally
        FLock.Leave;
      end;
      if LStopped then
        FinishGracefully;
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

procedure TTgPollCore.RequestStop(AWaitMs: Cardinal);
begin
  FLock.Enter;
  try
    if not FStopRequested then
    begin
      FStopRequested := True;
      // Половина бюджета Stop — на дренаж, остальное — на итоговый запрос.
      FDrainLimitMs := Min(FDrainTimeoutMs, AWaitMs div 2);
      if FState = TTgSourceState.Running then
        FState := TTgSourceState.Stopping;
    end;
  finally
    FLock.Leave;
  end;
  FPollSource.Cancel;
  FWake.SetEvent;
end;

procedure TTgPollCore.CancelFinal;
begin
  FFinalSource.Cancel;
  FWake.SetEvent;
end;

procedure TTgPollCore.Abandon;
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

procedure TTgPollCore.Processed(AUpdateId: Int64);
var
  LIndex: Integer;
  LEmpty: Boolean;
begin
  FLock.Enter;
  try
    LIndex := FPending.IndexOf(AUpdateId);
    if LIndex < 0 then
      Exit;
    FPending.Delete(LIndex);
    LEmpty := FPending.Count = 0;
  finally
    FLock.Leave;
  end;
  if LEmpty then
    FWake.SetEvent;
end;

function TTgPollCore.State: TTgSourceState;
begin
  FLock.Enter;
  try
    Result := FState;
  finally
    FLock.Leave;
  end;
end;

function TTgPollCore.Offset: Int64;
begin
  FLock.Enter;
  try
    Result := FOffset;
  finally
    FLock.Leave;
  end;
end;

function TTgPollCore.ConfirmedOffset: Int64;
begin
  FLock.Enter;
  try
    Result := FConfirmedOffset;
  finally
    FLock.Leave;
  end;
end;

function TTgPollCore.ResumeOffset: Int64;
begin
  FLock.Enter;
  try
    if FPending.Count > 0 then
      Result := FPending[0]
    else
      Result := FOffset;
  finally
    FLock.Leave;
  end;
end;

function TTgPollCore.GetDone: TEvent;
begin
  Result := FDone;
end;

{ TTgLongPollSource }

constructor TTgLongPollSource.Create(const ATransport: ITgTransport;
  const AParentCancel: ITgCancellation);
begin
  inherited Create;
  if not Assigned(ATransport) then
    raise ETgError.Create(TgText(TTgText.TransportRequired));
  FLock := TCriticalSection.Create;
  FTransport := ATransport;
  FParentCancel := AParentCancel;
  FLimit := TgDefaultPollLimit;
  FTimeoutSec := TgDefaultPollTimeoutSec;
  FAckPolicy := TTgAckPolicy.AfterReceive;
  FDrainTimeoutMs := TgDefaultDrainTimeoutMs;
  FConflictNotifyIntervalMs := TgDefaultConflictNotifyMs;
  FJitterPercent := TgDefaultBackoffJitterPercent;
end;

destructor TTgLongPollSource.Destroy;
var
  LCore: ITgPollCore;
  LFirst: Boolean;
begin
  if Assigned(FLock) then
  begin
    LCore := CurrentCore;
    if Assigned(LCore) then
    begin
      // Поток (FreeOnTerminate) держит ядро сам: висящий запрос не ждём.
      // После Stop (в т.ч. вернувшего False) повторно не ждём.
      LFirst := not LCore.IsStopRequested;
      LCore.RequestStop(TgDefaultDrainTimeoutMs + 1000);
      if LFirst then
        LCore.Done.WaitFor(TgDestroyGraceMs);
    end;
    LCore := nil;
  end;
  FCore := nil;
  FreeAndNil(FLock);
  inherited Destroy;
end;

function TTgLongPollSource.CurrentCore: ITgPollCore;
begin
  FLock.Enter;
  try
    Result := FCore;
  finally
    FLock.Leave;
  end;
end;

procedure TTgLongPollSource.Start(const ASink: ITgUpdateSink);
var
  LOld: ITgPollCore;
  LCore: ITgPollCore;
  LThread: TTgPollThread;
begin
  if not Assigned(ASink) then
    raise EArgumentNilException.Create('ASink');
  FLock.Enter;
  try
    LOld := FCore;
    if Assigned(LOld) and (LOld.State in [TTgSourceState.Running, TTgSourceState.Stopping]) then
      raise ETgError.Create(TgUpdatesText(TTgUpdatesText.SourceRunning));
    if Assigned(LOld) then
      FResumeOffset := LOld.ResumeOffset;
    LCore := TTgPollCore.Create(FTransport, FParentCancel, ASink, Self, FResumeOffset);
    LThread := TTgPollThread.Create(LCore);
    FCore := LCore;
  finally
    FLock.Leave;
  end;
  LThread.Start;
end;

function TTgLongPollSource.Stop(AWaitMs: Cardinal): Boolean;
var
  LCore: ITgPollCore;
begin
  LCore := CurrentCore;
  if not Assigned(LCore) then
    Exit(True);
  LCore.RequestStop(AWaitMs);
  Result := TgWaitEventPumping(LCore.Done, AWaitMs);
  if not Result then
  begin
    // Бюджет исчерпан: прерываем дренаж и итоговый запрос, коротко ждём ещё.
    LCore.CancelFinal;
    Result := TgWaitEventPumping(LCore.Done, TgFinalGraceMs);
  end;
  if not Result then
    LCore.Abandon;
  FLock.Enter;
  try
    if FCore = LCore then
      FResumeOffset := LCore.ResumeOffset;
  finally
    FLock.Leave;
  end;
end;

procedure TTgLongPollSource.Processed(AUpdateId: Int64);
var
  LCore: ITgPollCore;
begin
  LCore := CurrentCore;
  if Assigned(LCore) then
    LCore.Processed(AUpdateId);
end;

function TTgLongPollSource.GetState: TTgSourceState;
var
  LCore: ITgPollCore;
begin
  LCore := CurrentCore;
  if Assigned(LCore) then
    Result := LCore.State
  else
    Result := TTgSourceState.Idle;
end;

function TTgLongPollSource.WaitForThread(AMs: Cardinal): Boolean;
var
  LCore: ITgPollCore;
begin
  LCore := CurrentCore;
  Result := not Assigned(LCore) or
    (LCore.Done.WaitFor(AMs) = TWaitResult.wrSignaled);
end;

function TTgLongPollSource.GetOffset: Int64;
var
  LCore: ITgPollCore;
begin
  LCore := CurrentCore;
  if Assigned(LCore) then
    Result := LCore.Offset
  else
    Result := FResumeOffset;
end;

function TTgLongPollSource.GetConfirmedOffset: Int64;
var
  LCore: ITgPollCore;
begin
  LCore := CurrentCore;
  if Assigned(LCore) then
    Result := LCore.ConfirmedOffset
  else
    Result := 0;
end;

end.
