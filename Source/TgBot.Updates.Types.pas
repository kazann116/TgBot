unit TgBot.Updates.Types;

{
  TgBot — общие типы приёма обновлений (нижний слой, работает с сырым JSON
  и не зависит от сгенерированных типов TgBot.Types).

  - ITgRawUpdate / TTgRawUpdate — обновление: update_id, вид (ключ поля),
    ключ «полосы» ChatKey и JSON (обновление владеет своим объектом);
  - ITgUpdateSink / ITgTimedUpdateSink — приёмник обновлений (очередь
    диспетчера TTgUpdateDispatcher, модуль TgBot.Updates.Dispatcher);
  - ITgUpdateSource / ITgWebhookReceiver / ITgPollTimer — контракты
    источников TTgLongPollSource (TgBot.Updates.Polling) и
    TTgWebhookSource (TgBot.Updates.WebhookSource); контракты и
    перечисления объявлены в TgBot.Intf, здесь — псевдонимы;
  - перечисления, константы по умолчанию, тексты (TgUpdatesText),
    TgWebhookHttpStatus, TgWaitEventPumping;
  - служебное для источников: TgCallTransport, TgInvokeQuietly,
    TgFinalGraceMs, TgDestroyGraceMs;
  - TTgShutdownSignal — Ctrl+C / закрытие консоли (Windows),
    SIGINT/SIGTERM (Linux, macOS) для консольных ботов.

  Пользователю достаточно uses TgBot.Updates (или TgBot): публичные
  идентификаторы модуля реэкспортируются там псевдонимами.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.SyncObjs,
  System.Diagnostics,
  System.JSON,
  TgBot.Base,
  TgBot.Json,
  TgBot.Intf;

const
  /// <summary>Таймаут long polling (параметр timeout getUpdates) по умолчанию, с.</summary>
  TgDefaultPollTimeoutSec = 50;
  /// <summary>Максимум обновлений за один getUpdates по умолчанию (1–100).</summary>
  TgDefaultPollLimit = 100;
  /// <summary>Ёмкость очереди диспетчера по умолчанию (обновлений).</summary>
  TgDefaultQueueCapacity = 1000;
  /// <summary>Число потоков диспетчера по умолчанию.</summary>
  TgDefaultMaxParallel = 4;
  /// <summary>Сколько Stop ждёт обработки уже принятых обновлений по умолчанию, мс.</summary>
  TgDefaultDrainTimeoutMs = 5000;
  /// <summary>Минимальный интервал между событиями OnConflict «другой getUpdates», мс.</summary>
  TgDefaultConflictNotifyMs = 60000;
  /// <summary>Разброс пауз между повторами по умолчанию, ± процентов.</summary>
  TgDefaultBackoffJitterPercent = 20;
  /// <summary>Первая пауза после ошибки getUpdates, мс (далее — удвоение).</summary>
  TgBackoffMinMs = 1000;
  /// <summary>Максимальная пауза после ошибки getUpdates, мс.</summary>
  TgBackoffMaxMs = 60000;
  /// <summary>Минимальная пауза после 409 «другой getUpdates», мс.</summary>
  TgConflictRetryMs = 5000;
  /// <summary>Наибольший размер тела webhook-запроса по умолчанию, байт (1 МБ).</summary>
  TgDefaultWebhookMaxBodySize = 1024 * 1024;
  /// <summary>Сколько Accept ждёт места в очереди по умолчанию, мс (затем Unavailable).</summary>
  TgDefaultWebhookPostTimeoutMs = 250;
  /// <summary>Окно дедупликации webhook по умолчанию: сколько последних update_id помнить.</summary>
  TgDefaultWebhookDedupWindow = 1000;
  /// <summary>Длина секрета webhook, генерируемого библиотекой (символы [A-Za-z0-9_-]).</summary>
  TgWebhookSecretLength = 48;
  /// <summary>
  ///   Сколько деструктор диспетчера или источника ждёт свои потоки, если
  ///   остановку ещё не запрашивали, мс; дальше потоки отпускаются — своё
  ///   состояние они держат сами (служебное).
  /// </summary>
  TgDestroyGraceMs = 30;
  /// <summary>
  ///   Сколько Stop источника ждёт поток после отмены итогового запроса
  ///   (long polling) или setWebhook/deleteWebhook, мс (служебное).
  /// </summary>
  TgFinalGraceMs = 100;

type
  { Контракты приёма обновлений, их перечисления и типы обработчиков
    объявлены в TgBot.Intf (модуль без реализаций); здесь — псевдонимы для
    совместимости: те же типы и GUID. }

  /// <summary>Состояние источника обновлений (TgBot.Intf).</summary>
  TTgSourceState = TgBot.Intf.TTgSourceState;
  /// <summary>Когда подтверждать (offset) принятые обновления (TgBot.Intf).</summary>
  TTgAckPolicy = TgBot.Intf.TTgAckPolicy;
  /// <summary>Где выполняются обработчики обновлений (TgBot.Intf).</summary>
  TTgDelivery = TgBot.Intf.TTgDelivery;
  /// <summary>Итог приёма webhook-запроса; HTTP-код — TgWebhookHttpStatus (TgBot.Intf).</summary>
  TTgWebhookResult = TgBot.Intf.TTgWebhookResult;

  /// <summary>Тексты сообщений (служебное: источники, диспетчер, TgBot.Bot, TgBot.Context).</summary>
  TTgUpdatesText = (SourceRunning, DispatcherRunning, StopFromHandler, NoChat,
    RunNotMainThread, RunUnsupported, BotRunning, HandlerFiltered, WebhookUrlRequired,
    WebhookBadSecret, WebhookUnsupported);

  /// <summary>Обновление Bot API в сыром виде (описание — TgBot.Intf.ITgRawUpdate).</summary>
  ITgRawUpdate = TgBot.Intf.ITgRawUpdate;
  /// <summary>Приёмник обновлений (описание — TgBot.Intf.ITgUpdateSink).</summary>
  ITgUpdateSink = TgBot.Intf.ITgUpdateSink;
  /// <summary>Приёмник с ограниченным ожиданием места (описание — TgBot.Intf.ITgTimedUpdateSink).</summary>
  ITgTimedUpdateSink = TgBot.Intf.ITgTimedUpdateSink;
  /// <summary>Приём тела webhook-запроса (описание — TgBot.Intf.ITgWebhookReceiver).</summary>
  ITgWebhookReceiver = TgBot.Intf.ITgWebhookReceiver;
  /// <summary>Источник обновлений (описание — TgBot.Intf.ITgUpdateSource).</summary>
  ITgUpdateSource = TgBot.Intf.ITgUpdateSource;
  /// <summary>Часы и паузы источника (описание — TgBot.Intf.ITgPollTimer).</summary>
  ITgPollTimer = TgBot.Intf.ITgPollTimer;

  /// <summary>Обработчик обновления нижнего уровня (TgBot.Intf).</summary>
  TTgRawHandler = TgBot.Intf.TTgRawHandler;
  /// <summary>Обработчик исключения обработчика (TgBot.Intf).</summary>
  TTgRawErrorHandler = TgBot.Intf.TTgRawErrorHandler;
  /// <summary>Событие конфликта 409 (TgBot.Intf).</summary>
  TTgConflictHandler = TgBot.Intf.TTgConflictHandler;

  /// <summary>Реализация ITgRawUpdate.</summary>
  TTgRawUpdate = class(TInterfacedObject, ITgRawUpdate)
  private
    FJson: TJSONObject;
    FUpdateId: Int64;
    FKind: string;
    FChatKey: string;
  public
    /// <summary>
    ///   Владение AJson переходит к обновлению сразу (в т.ч. при исключении
    ///   конструктора). update_id не целое — ETgError.
    /// </summary>
    constructor Create(AJson: TJSONObject);
    destructor Destroy; override;
    /// <summary>Вид обновления: первое поле, кроме update_id; '' — нет.</summary>
    class function KindOf(AJson: TJSONObject): string; static;
    /// <summary>
    ///   Ключ порядка: chat.id полезной нагрузки (для callback_query —
    ///   message.chat.id); иначе 'u' + from.id (или user.id); poll,
    ///   poll_answer и обновления без чата и пользователя — ''.
    /// </summary>
    class function ChatKeyOf(AJson: TJSONObject): string; static;
    function GetUpdateId: Int64;
    function GetKind: string;
    function GetChatKey: string;
    function GetJson: TJSONObject;
  end;

  /// <summary>Часы и паузы по умолчанию (TStopwatch, WaitFor токена).</summary>
  TTgSystemPollTimer = class(TInterfacedObject, ITgPollTimer)
  private
    FWatch: TStopwatch;
  public
    constructor Create;
    function NowMs: Int64;
    function Sleep(AMs: Cardinal; const ACancel: ITgCancellation): Boolean;
  end;

  /// <summary>
  ///   Сигнал завершения консольной программы: Windows — Ctrl+C, Ctrl+Break,
  ///   закрытие окна, выход из системы, выключение (для трёх последних
  ///   обработчик ждёт NotifyStopped до 4,5 с — затем Windows завершает
  ///   процесс); Linux/macOS — SIGINT, SIGTERM (обработчик только атомарно
  ///   пишет флаг; прежние обработчики восстанавливаются в Uninstall);
  ///   Android — недоступно (Install = False).
  /// </summary>
  TTgShutdownSignal = class sealed
  public
    /// <summary>Устанавливает обработчики (вложенные вызовы считаются); False — недоступно.</summary>
    class function Install: Boolean; static;
    /// <summary>Снимает обработчики (парно Install).</summary>
    class procedure Uninstall; static;
    /// <summary>Сигнал получен (или вызван Request).</summary>
    class function Requested: Boolean; static;
    /// <summary>Программный запрос завершения (как сигнал).</summary>
    class procedure Request; static;
    /// <summary>Сбрасывает признак сигнала и «остановлен».</summary>
    class procedure Reset; static;
    /// <summary>Программа остановилась: обработчик закрытия консоли может вернуть управление.</summary>
    class procedure NotifyStopped; static;
    /// <summary>Сигналы поддерживаются на этой платформе.</summary>
    class function Supported: Boolean; static;
  end;

/// <summary>
///   Локализованный текст (служебное: источники, диспетчер, TgBot.Bot,
///   TgBot.Context);
///   язык — TgGetLanguage в момент вызова.
/// </summary>
function TgUpdatesText(AText: TTgUpdatesText): string;

/// <summary>
///   Ждёт AEvent не дольше AMs мс; в главном потоке при этом выполняет
///   CheckSynchronize (обработчики с Delivery = Main не блокируются).
/// </summary>
function TgWaitEventPumping(AEvent: TEvent; AMs: Cardinal): Boolean;

/// <summary>HTTP-код ответа на webhook-запрос: 200, 403, 400 или 503.</summary>
function TgWebhookHttpStatus(AResult: TTgWebhookResult): Integer;

{ Служебное (общее для источников TgBot.Updates.Polling и TgBot.Updates.WebhookSource),
  не часть публичного API. }

/// <summary>
///   Вызов метода Bot API через транспорт с токеном отмены (как
///   TTgApiCore.Call, но без клиента: потоки держат только счётчиковые ссылки).
///   Служебное.
/// </summary>
function TgCallTransport(const ATransport: ITgTransport; const AMethod: string;
  AParams: TTgParams; const AToken: ITgCancellation): TJSONValue;

/// <summary>Вызывает колбэк, поглощая его исключения (служебное).</summary>
procedure TgInvokeQuietly(const AProc: TProc);

implementation

uses
  System.Classes,
  System.Generics.Collections, // inline TJSONObject.GetPair, иначе H2443
{$IFDEF MSWINDOWS}
  Winapi.Windows,
{$ENDIF}
{$IF defined(POSIX) and not defined(ANDROID)}
  Posix.Signal,
{$IFEND}
  System.Math,
  TgBot.Consts;

const
  // Тексты TTgUpdatesText: пары ресурсных строк TgBot.Consts (SRuUpd…, SEnUpd…).
  CUpdatesTexts: array[TTgUpdatesText, TTgLanguage] of PResStringRec = (
    (@SRuUpdSourceRunning, @SEnUpdSourceRunning),
    (@SRuUpdDispatcherRunning, @SEnUpdDispatcherRunning),
    (@SRuUpdStopFromHandler, @SEnUpdStopFromHandler),
    (@SRuUpdNoChat, @SEnUpdNoChat),
    (@SRuUpdRunNotMainThread, @SEnUpdRunNotMainThread),
    (@SRuUpdRunUnsupported, @SEnUpdRunUnsupported),
    (@SRuUpdBotRunning, @SEnUpdBotRunning),
    (@SRuUpdHandlerFiltered, @SEnUpdHandlerFiltered),
    (@SRuUpdWebhookUrlRequired, @SEnUpdWebhookUrlRequired),
    (@SRuUpdWebhookBadSecret, @SEnUpdWebhookBadSecret),
    (@SRuUpdWebhookUnsupported, @SEnUpdWebhookUnsupported)
  );

function TgUpdatesText(AText: TTgUpdatesText): string;
begin
  Result := TgLangText(CUpdatesTexts[AText, TTgLanguage.Ru],
    CUpdatesTexts[AText, TTgLanguage.En]);
end;

function TgWebhookHttpStatus(AResult: TTgWebhookResult): Integer;
begin
  case AResult of
    TTgWebhookResult.Accepted:
      Result := 200;
    TTgWebhookResult.Forbidden:
      Result := 403;
    TTgWebhookResult.BadRequest:
      Result := 400;
  else
    Result := 503;
  end;
end;

function TgWaitEventPumping(AEvent: TEvent; AMs: Cardinal): Boolean;
var
  LWatch: TStopwatch;
  LLeft: Int64;
begin
  if TThread.CurrentThread.ThreadID <> MainThreadID then
    Exit(AEvent.WaitFor(AMs) = TWaitResult.wrSignaled);
  LWatch := TStopwatch.StartNew;
  while True do
  begin
    if AEvent.WaitFor(0) = TWaitResult.wrSignaled then
      Exit(True);
    LLeft := Int64(AMs) - LWatch.ElapsedMilliseconds;
    if LLeft <= 0 then
      Exit(False);
    try
      CheckSynchronize(Integer(Min(LLeft, 10)));
    except
      // Исключение чужой процедуры из очереди не должно прерывать остановку.
      if Assigned(ApplicationHandleException) then
        ApplicationHandleException(nil);
    end;
  end;
end;

function TgCallTransport(const ATransport: ITgTransport; const AMethod: string;
  AParams: TTgParams; const AToken: ITgCancellation): TJSONValue;
var
  LCancellable: ITgCancellableTransport;
  LScope: TTgCancelScope;
begin
  if Supports(ATransport, ITgCancellableTransport, LCancellable) then
    Exit(LCancellable.ExecuteEx(AMethod, AParams, AToken));
  // Транспорт без токенов: проверки до и после; токен доступен ему как окружающий.
  AToken.ThrowIfCancelled;
  LScope := TTgCancelScope.Enter(AToken);
  try
    Result := ATransport.Execute(AMethod, AParams);
  finally
    LScope.Leave;
  end;
  if AToken.IsCancelled then
  begin
    FreeAndNil(Result);
    raise ETgCancelledError.Create(TgText(TTgText.Cancelled));
  end;
end;

procedure TgInvokeQuietly(const AProc: TProc);
begin
  try
    AProc();
  except
    // Исключения пользовательских событий не прерывают работу потоков.
  end;
end;

{ TTgRawUpdate }

constructor TTgRawUpdate.Create(AJson: TJSONObject);
begin
  // Владение — сразу: при исключении деструктор освободит JSON.
  FJson := AJson;
  inherited Create;
  if not Assigned(FJson) then
    raise EArgumentNilException.Create(TgLangTextFmt(@SRuArgNil, @SEnArgNil, ['AJson']));
  FUpdateId := TTgJson.GetInt64(FJson, 'update_id');
  FKind := KindOf(FJson);
  try
    FChatKey := ChatKeyOf(FJson);
  except
    // Некорректный id чата не мешает обработке: обновление идёт без порядка.
    FChatKey := '';
  end;
end;

destructor TTgRawUpdate.Destroy;
begin
  FreeAndNil(FJson);
  inherited Destroy;
end;

class function TTgRawUpdate.KindOf(AJson: TJSONObject): string;
var
  I: Integer;
begin
  Result := '';
  if not Assigned(AJson) then
    Exit;
  for I := 0 to AJson.Count - 1 do
    if AJson.Pairs[I].JsonString.Value <> 'update_id' then
      Exit(AJson.Pairs[I].JsonString.Value);
end;

class function TTgRawUpdate.ChatKeyOf(AJson: TJSONObject): string;

  function ChatOf(AObj: TJSONObject): string;
  var
    LChat: TJSONObject;
  begin
    LChat := TTgJson.GetObj(AObj, 'chat');
    if TTgJson.Has(LChat, 'id') then
      Result := IntToStr(TTgJson.GetInt64(LChat, 'id'))
    else
      Result := '';
  end;

  function UserOf(AObj: TJSONObject): string;
  var
    LUser: TJSONObject;
  begin
    LUser := TTgJson.GetObj(AObj, 'from');
    if not Assigned(LUser) then
      LUser := TTgJson.GetObj(AObj, 'user');
    if TTgJson.Has(LUser, 'id') then
      Result := 'u' + IntToStr(TTgJson.GetInt64(LUser, 'id'))
    else
      Result := '';
  end;

var
  LKind: string;
  LPayload: TJSONObject;
begin
  Result := '';
  LKind := KindOf(AJson);
  LPayload := TTgJson.GetObj(AJson, LKind);
  if not Assigned(LPayload) then
    Exit;
  // Опросы не привязаны к диалогу: порядок не нужен.
  if (LKind = 'poll') or (LKind = 'poll_answer') then
    Exit;
  if LKind = 'callback_query' then
    Result := ChatOf(TTgJson.GetObj(LPayload, 'message'))
  else
    Result := ChatOf(LPayload);
  if Result = '' then
    Result := UserOf(LPayload);
end;

function TTgRawUpdate.GetUpdateId: Int64;
begin
  Result := FUpdateId;
end;

function TTgRawUpdate.GetKind: string;
begin
  Result := FKind;
end;

function TTgRawUpdate.GetChatKey: string;
begin
  Result := FChatKey;
end;

function TTgRawUpdate.GetJson: TJSONObject;
begin
  Result := FJson;
end;

{ TTgSystemPollTimer }

constructor TTgSystemPollTimer.Create;
begin
  inherited Create;
  FWatch := TStopwatch.StartNew;
end;

function TTgSystemPollTimer.NowMs: Int64;
begin
  Result := FWatch.ElapsedMilliseconds;
end;

function TTgSystemPollTimer.Sleep(AMs: Cardinal; const ACancel: ITgCancellation): Boolean;
begin
  if Assigned(ACancel) then
    Exit(ACancel.WaitFor(AMs));
  TThread.Sleep(AMs);
  Result := False;
end;

{ TTgShutdownSignal }

var
  // Признак сигнала: пишется атомарно (в т.ч. из обработчика сигнала POSIX).
  GTgSignalFlag: Integer = 0;
  // Число вложенных Install.
  GTgSignalInstalls: Integer = 0;

{$IFDEF MSWINDOWS}
var
  // Событие «программа остановилась» (живёт до завершения процесса).
  GTgStoppedEvent: THandle = 0;

function TgConsoleCtrlHandler(ACtrlType: DWORD): BOOL; stdcall;
begin
  case ACtrlType of
    CTRL_C_EVENT, CTRL_BREAK_EVENT:
      begin
        AtomicExchange(GTgSignalFlag, 1);
        Result := True;
      end;
    CTRL_CLOSE_EVENT, CTRL_LOGOFF_EVENT, CTRL_SHUTDOWN_EVENT:
      begin
        AtomicExchange(GTgSignalFlag, 1);
        // После возврата Windows завершает процесс: даём боту остановиться.
        if GTgStoppedEvent <> 0 then
          WaitForSingleObject(GTgStoppedEvent, 4500);
        Result := True;
      end;
  else
    Result := False;
  end;
end;
{$ENDIF}

{$IF defined(POSIX) and not defined(ANDROID)}
var
  GTgOldSigInt: sigaction_t;
  GTgOldSigTerm: sigaction_t;

procedure TgSignalHandler(ASignal: Integer); cdecl;
begin
  // Только запись выровненного Integer — допустимо в обработчике сигнала.
  GTgSignalFlag := 1;
end;
{$IFEND}

class function TTgShutdownSignal.Supported: Boolean;
begin
{$IF defined(MSWINDOWS) or (defined(POSIX) and not defined(ANDROID))}
  Result := True;
{$ELSE}
  Result := False;
{$IFEND}
end;

class function TTgShutdownSignal.Install: Boolean;
{$IF defined(POSIX) and not defined(ANDROID)}
var
  LAction: sigaction_t;
{$IFEND}
begin
  Result := Supported;
  if not Result then
    Exit;
  if AtomicIncrement(GTgSignalInstalls) > 1 then
    Exit;
{$IFDEF MSWINDOWS}
  if GTgStoppedEvent = 0 then
    GTgStoppedEvent := CreateEvent(nil, True, False, nil);
  Result := SetConsoleCtrlHandler(@TgConsoleCtrlHandler, True);
{$ENDIF}
{$IF defined(POSIX) and not defined(ANDROID)}
  FillChar(LAction, SizeOf(LAction), 0);
  // Поле обработчика — первое в sigaction_t (имя объединения различается
  // в Linux и macOS), поэтому пишем его по смещению 0.
  PPointer(@LAction)^ := @TgSignalHandler;
  sigemptyset(LAction.sa_mask);
  LAction.sa_flags := SA_RESTART;
  Result := (sigaction(SIGINT, @LAction, @GTgOldSigInt) = 0) and
    (sigaction(SIGTERM, @LAction, @GTgOldSigTerm) = 0);
{$IFEND}
  if not Result then
    AtomicDecrement(GTgSignalInstalls);
end;

class procedure TTgShutdownSignal.Uninstall;
begin
  if not Supported then
    Exit;
  if AtomicDecrement(GTgSignalInstalls) <> 0 then
  begin
    if GTgSignalInstalls < 0 then
      GTgSignalInstalls := 0;
    Exit;
  end;
{$IFDEF MSWINDOWS}
  SetConsoleCtrlHandler(@TgConsoleCtrlHandler, False);
{$ENDIF}
{$IF defined(POSIX) and not defined(ANDROID)}
  sigaction(SIGINT, @GTgOldSigInt, nil);
  sigaction(SIGTERM, @GTgOldSigTerm, nil);
{$IFEND}
end;

class function TTgShutdownSignal.Requested: Boolean;
begin
  Result := AtomicCmpExchange(GTgSignalFlag, 0, 0) <> 0;
end;

class procedure TTgShutdownSignal.Request;
begin
  AtomicExchange(GTgSignalFlag, 1);
end;

class procedure TTgShutdownSignal.Reset;
begin
  AtomicExchange(GTgSignalFlag, 0);
{$IFDEF MSWINDOWS}
  if GTgStoppedEvent <> 0 then
    ResetEvent(GTgStoppedEvent);
{$ENDIF}
end;

class procedure TTgShutdownSignal.NotifyStopped;
begin
{$IFDEF MSWINDOWS}
  if GTgStoppedEvent <> 0 then
    SetEvent(GTgStoppedEvent);
{$ENDIF}
end;

initialization

finalization
{$IFDEF MSWINDOWS}
  if GTgStoppedEvent <> 0 then
  begin
    CloseHandle(GTgStoppedEvent);
    GTgStoppedEvent := 0;
  end;
{$ENDIF}

end.
