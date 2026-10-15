unit TgBot.Updates;

{
  TgBot — приём обновлений: фасад нижнего слоя (работает с сырым JSON и
  не зависит от сгенерированных типов TgBot.Types). Собственных
  объявлений нет, только реэкспорт:

  - общие типы (ITgRawUpdate, ITgUpdateSink, ITgUpdateSource, перечисления,
    константы, тексты, TTgShutdownSignal) — TgBot.Updates.Types;
  - диспетчер TTgUpdateDispatcher — TgBot.Updates.Dispatcher;
  - long polling TTgLongPollSource (getUpdates в собственном потоке:
    offset, политики подтверждения, паузы при ошибках, 401/404/409,
    остановка с дренажом и итоговым подтверждением) — TgBot.Updates.Polling;
  - webhook TTgWebhookSource без HTTP-сервера (setWebhook/deleteWebhook,
    приём тела запроса из любого сервера — Accept, проверка секрета,
    дедупликация update_id, ограниченное ожидание очереди) —
    TgBot.Updates.WebhookSource.

  Типы и константы реэкспортируются псевдонимами, функции — обёртками,
  поэтому достаточно uses TgBot.Updates.

  Время жизни: потоки источников и диспетчера держат только счётчиковые
  ссылки на внутреннее состояние, поэтому Stop может «отпустить» поток,
  который не удалось прервать (транспорт без отмены, Linux/Android, зависший
  обработчик), — поздний результат такого потока выбрасывается.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SyncObjs,
  TgBot.Updates.Types,
  TgBot.Updates.Dispatcher,
  TgBot.Updates.Polling,
  TgBot.Updates.WebhookSource;

const
  { Псевдонимы констант TgBot.Updates.Types }

  /// <summary>Таймаут long polling (параметр timeout getUpdates) по умолчанию, с.</summary>
  TgDefaultPollTimeoutSec = TgBot.Updates.Types.TgDefaultPollTimeoutSec;
  /// <summary>Максимум обновлений за один getUpdates по умолчанию (1–100).</summary>
  TgDefaultPollLimit = TgBot.Updates.Types.TgDefaultPollLimit;
  /// <summary>Ёмкость очереди диспетчера по умолчанию (обновлений).</summary>
  TgDefaultQueueCapacity = TgBot.Updates.Types.TgDefaultQueueCapacity;
  /// <summary>Число потоков диспетчера по умолчанию.</summary>
  TgDefaultMaxParallel = TgBot.Updates.Types.TgDefaultMaxParallel;
  /// <summary>Сколько Stop ждёт обработки уже принятых обновлений по умолчанию, мс.</summary>
  TgDefaultDrainTimeoutMs = TgBot.Updates.Types.TgDefaultDrainTimeoutMs;
  /// <summary>Минимальный интервал между событиями OnConflict «другой getUpdates», мс.</summary>
  TgDefaultConflictNotifyMs = TgBot.Updates.Types.TgDefaultConflictNotifyMs;
  /// <summary>Разброс пауз между повторами по умолчанию, ± процентов.</summary>
  TgDefaultBackoffJitterPercent = TgBot.Updates.Types.TgDefaultBackoffJitterPercent;
  /// <summary>Первая пауза после ошибки getUpdates, мс (далее — удвоение).</summary>
  TgBackoffMinMs = TgBot.Updates.Types.TgBackoffMinMs;
  /// <summary>Максимальная пауза после ошибки getUpdates, мс.</summary>
  TgBackoffMaxMs = TgBot.Updates.Types.TgBackoffMaxMs;
  /// <summary>Минимальная пауза после 409 «другой getUpdates», мс.</summary>
  TgConflictRetryMs = TgBot.Updates.Types.TgConflictRetryMs;
  /// <summary>Наибольший размер тела webhook-запроса по умолчанию, байт (1 МБ).</summary>
  TgDefaultWebhookMaxBodySize = TgBot.Updates.Types.TgDefaultWebhookMaxBodySize;
  /// <summary>Сколько Accept ждёт места в очереди по умолчанию, мс (затем Unavailable).</summary>
  TgDefaultWebhookPostTimeoutMs = TgBot.Updates.Types.TgDefaultWebhookPostTimeoutMs;
  /// <summary>Окно дедупликации webhook по умолчанию: сколько последних update_id помнить.</summary>
  TgDefaultWebhookDedupWindow = TgBot.Updates.Types.TgDefaultWebhookDedupWindow;
  /// <summary>Длина секрета webhook, генерируемого библиотекой (символы [A-Za-z0-9_-]).</summary>
  TgWebhookSecretLength = TgBot.Updates.Types.TgWebhookSecretLength;

type
  { Псевдонимы типов TgBot.Updates.Types }

  /// <summary>Состояние источника обновлений (Idle, Running, Stopping, Faulted).</summary>
  TTgSourceState = TgBot.Updates.Types.TTgSourceState;
  /// <summary>Когда подтверждать (offset) принятые обновления (AfterReceive, AfterBatch).</summary>
  TTgAckPolicy = TgBot.Updates.Types.TTgAckPolicy;
  /// <summary>Где выполняются обработчики обновлений (Worker, Main).</summary>
  TTgDelivery = TgBot.Updates.Types.TTgDelivery;
  /// <summary>Итог приёма webhook-запроса (Accepted, Forbidden, BadRequest, Unavailable).</summary>
  TTgWebhookResult = TgBot.Updates.Types.TTgWebhookResult;
  /// <summary>Тексты сообщений (служебное, для TgBot.Bot).</summary>
  TTgUpdatesText = TgBot.Updates.Types.TTgUpdatesText;
  /// <summary>Обновление Bot API в сыром виде (update_id, вид, ключ чата, JSON).</summary>
  ITgRawUpdate = TgBot.Updates.Types.ITgRawUpdate;
  /// <summary>Приёмник обновлений (очередь диспетчера).</summary>
  ITgUpdateSink = TgBot.Updates.Types.ITgUpdateSink;
  /// <summary>Приёмник с ограниченным ожиданием места в очереди.</summary>
  ITgTimedUpdateSink = TgBot.Updates.Types.ITgTimedUpdateSink;
  /// <summary>Приём тела webhook-запроса из любого HTTP-сервера.</summary>
  ITgWebhookReceiver = TgBot.Updates.Types.ITgWebhookReceiver;
  /// <summary>Источник обновлений (long polling или webhook).</summary>
  ITgUpdateSource = TgBot.Updates.Types.ITgUpdateSource;
  /// <summary>Часы и паузы источника (подменяются в тестах).</summary>
  ITgPollTimer = TgBot.Updates.Types.ITgPollTimer;
  /// <summary>Обработчик обновления нижнего уровня.</summary>
  TTgRawHandler = TgBot.Updates.Types.TTgRawHandler;
  /// <summary>Обработчик исключения обработчика (объект исключения действителен только внутри).</summary>
  TTgRawErrorHandler = TgBot.Updates.Types.TTgRawErrorHandler;
  /// <summary>Событие конфликта 409 (объект исключения действителен только внутри).</summary>
  TTgConflictHandler = TgBot.Updates.Types.TTgConflictHandler;
  /// <summary>Реализация ITgRawUpdate.</summary>
  TTgRawUpdate = TgBot.Updates.Types.TTgRawUpdate;
  /// <summary>Часы и паузы по умолчанию (TStopwatch, WaitFor токена).</summary>
  TTgSystemPollTimer = TgBot.Updates.Types.TTgSystemPollTimer;
  /// <summary>Сигнал завершения консольной программы (Ctrl+C, SIGINT/SIGTERM).</summary>
  TTgShutdownSignal = TgBot.Updates.Types.TTgShutdownSignal;

  { Псевдоним диспетчера TgBot.Updates.Dispatcher }

  /// <summary>Диспетчер обновлений: порядок внутри чата, параллельность между чатами.</summary>
  TTgUpdateDispatcher = TgBot.Updates.Dispatcher.TTgUpdateDispatcher;

  { Псевдоним источника long polling TgBot.Updates.Polling }

  /// <summary>Long polling (getUpdates) в собственном потоке: offset, паузы при ошибках, 401/404/409, остановка с дренажом.</summary>
  TTgLongPollSource = TgBot.Updates.Polling.TTgLongPollSource;

  { Псевдоним webhook-источника TgBot.Updates.WebhookSource }

  /// <summary>Webhook без HTTP-сервера: setWebhook/deleteWebhook, Accept из любого сервера, секрет, дедупликация update_id.</summary>
  TTgWebhookSource = TgBot.Updates.WebhookSource.TTgWebhookSource;

{ Обёртки функций TgBot.Updates.Types (не inline: inline-обёртка дала бы
  пользователю подсказку H2443 о модуле, не указанном в uses). }

/// <summary>Локализованный текст (служебное, для TgBot.Bot).</summary>
function TgUpdatesText(AText: TTgUpdatesText): string;

/// <summary>
///   Ждёт AEvent не дольше AMs мс; в главном потоке при этом выполняет
///   CheckSynchronize (обработчики с Delivery = Main не блокируются).
/// </summary>
function TgWaitEventPumping(AEvent: TEvent; AMs: Cardinal): Boolean;

/// <summary>HTTP-код ответа на webhook-запрос: 200, 403, 400 или 503.</summary>
function TgWebhookHttpStatus(AResult: TTgWebhookResult): Integer;

implementation

function TgUpdatesText(AText: TTgUpdatesText): string;
begin
  Result := TgBot.Updates.Types.TgUpdatesText(AText);
end;

function TgWaitEventPumping(AEvent: TEvent; AMs: Cardinal): Boolean;
begin
  Result := TgBot.Updates.Types.TgWaitEventPumping(AEvent, AMs);
end;

function TgWebhookHttpStatus(AResult: TTgWebhookResult): Integer;
begin
  Result := TgBot.Updates.Types.TgWebhookHttpStatus(AResult);
end;

end.
