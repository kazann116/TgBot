unit TgBot.Intf;

{
  TgBot — контракты библиотеки: интерфейсы и записи настроек без реализаций.

  Модуль для тех, кто пишет свою реализацию (транспорт, хранилище состояния,
  источник или приёмник обновлений) или зависит только от абстракций:
  uses TgBot.Intf не тянет реализации — ни System.Net.*, ни Indy, ни
  TgBot.Http/TgBot.Core/TgBot.Updates.*. Зависимости: TgBot.Base (токены
  отмены, исключения), TgBot.Json (TTgParams).

  - транспорт Bot API: ITgTransport, ITgCancellableTransport,
    ITgHttpSettingsProvider; записи TTgProxySettings, TTgHttpSettings,
    TTgHttpResponse; константы транспорта по умолчанию (TgDefault…);
  - приём обновлений: ITgRawUpdate, ITgUpdateSink, ITgTimedUpdateSink,
    ITgWebhookReceiver, ITgUpdateSource, ITgPollTimer; перечисления
    TTgSourceState, TTgAckPolicy, TTgDelivery, TTgWebhookResult; типы
    обработчиков TTgRawHandler, TTgRawErrorHandler, TTgConflictHandler;
  - состояние диалогов: ITgStateStorage;
  - псевдонимы типов из сигнатур контрактов: ITgCancellation,
    ITgCancellationSource (TgBot.Base), TTgParams (TgBot.Json).

  Реализации — в прежних модулях (TTgHttpTransport — TgBot.Http,
  TTgMemoryStateStorage — TgBot.State, источники и диспетчер —
  TgBot.Updates.*). Там же остались псевдонимы перенесённых типов: код с
  uses TgBot.Http, TgBot.Updates.Types, TgBot.State или фасада TgBot
  компилируется без изменений, GUID интерфейсов прежние.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.Classes,
  System.JSON,
  TgBot.Base,
  TgBot.Json;

const
  /// <summary>Адрес облачного Bot API по умолчанию.</summary>
  TgDefaultApiUrl = 'https://api.telegram.org';
  /// <summary>Таймаут соединения по умолчанию, мс.</summary>
  TgDefaultConnectionTimeoutMs = 15000;
  /// <summary>Таймаут ответа по умолчанию, мс (для long polling увеличивается автоматически).</summary>
  TgDefaultResponseTimeoutMs = 60000;
  /// <summary>Максимум попыток повтора при 429 по умолчанию.</summary>
  TgDefaultMaxRetries = 3;
  /// <summary>Максимальное ожидание retry_after по умолчанию, с (больше — ошибка сразу).</summary>
  TgDefaultMaxRetryAfterSec = 60;
  /// <summary>Глобальный лимит запросов в секунду на бота по умолчанию.</summary>
  TgDefaultGlobalRatePerSec = 30;
  /// <summary>Минимальный интервал между сообщениями в один чат по умолчанию, мс.</summary>
  TgDefaultPerChatIntervalMs = 1000;

type
  { Типы из сигнатур контрактов (объявлены в TgBot.Base и TgBot.Json) }

  /// <summary>Токен отмены операции (TgBot.Base.ITgCancellation).</summary>
  ITgCancellation = TgBot.Base.ITgCancellation;
  /// <summary>Источник отмены (TgBot.Base.ITgCancellationSource).</summary>
  ITgCancellationSource = TgBot.Base.ITgCancellationSource;
  /// <summary>Параметры метода Bot API (TgBot.Json.TTgParams).</summary>
  TTgParams = TgBot.Json.TTgParams;

  { Транспорт Bot API }

  /// <summary>
  ///   Настройки HTTP-прокси бота (применяются ко всем запросам транспорта:
  ///   методы Bot API, long polling, скачивание файлов). Запросы к https://
  ///   (облачный Bot API) идут через прокси туннелем CONNECT — прокси должен
  ///   его поддерживать. Поддерживается только HTTP-прокси: SOCKS- и
  ///   HTTPS-прокси (TLS до самого прокси) библиотека не поддерживает. Настройки
  ///   проверяет и нормализует TTgHttpTransport.Create (см. Normalized),
  ///   ошибка настройки — ETgError. Преобразование в настройки RTL
  ///   (TProxySettings) — ToRtlSettings, помощник записи в TgBot.Http.
  ///   Поле записи меняется на месте, в том числе через with:
  ///   <code>
  ///   LSettings := TTgHttpSettings.Create(LToken);
  ///   with LSettings.Proxy do begin Host := '192.168.1.1'; Port := 3128; end;
  ///   LBot := TTgBot.Create(LSettings);
  ///   </code>
  ///   При сетевой ошибке текст ETgNetworkError содержит адрес прокси.
  /// </summary>
  TTgProxySettings = record
    /// <summary>
    ///   Хост прокси; пусто — прокси бота не задан (Windows: системные
    ///   настройки прокси WinHTTP/IE). Адреса 127.0.0.1/localhost в ApiUrl
    ///   WinHTTP запрашивает напрямую, минуя прокси. Допустимо 'хост:порт'
    ///   и префикс 'http://'; IPv6 — '[::1]' или без скобок.
    /// </summary>
    Host: string;
    /// <summary>Порт прокси 1..65535; 0 — порт берётся из Host ('хост:порт').</summary>
    Port: Integer;
    /// <summary>Имя пользователя (необязательно).</summary>
    UserName: string;
    /// <summary>Пароль (необязательно).</summary>
    Password: string;
    /// <summary>
    ///   Схема прокси — для совместимости: допустимы только пусто и 'http'
    ///   (равнозначно, HTTP-прокси). В RTL всегда передаётся пустая схема:
    ///   на Windows схема RTL — протокол связи с самим прокси ('https' —
    ///   TLS до прокси, обычный HTTP-прокси на это отвечает ошибкой 12029),
    ///   на Linux (curl) и Android RTL её не использует. Другие значения
    ///   ('https', 'socks5'…) — ETgError при создании транспорта.
    /// </summary>
    Scheme: string;
    /// <summary>Создаёт настройки прокси.</summary>
    class function Create(const AHost: string; APort: Integer;
      const AUserName: string = ''; const APassword: string = '';
      const AScheme: string = ''): TTgProxySettings; static;
    /// <summary>Прокси задан.</summary>
    function IsEnabled: Boolean;
    /// <summary>
    ///   Проверенная копия настроек: Host без пробелов и префикса 'http://',
    ///   порт из 'хост:порт' (при Port = 0), IPv6 без скобок — в '[…]'.
    ///   Host пустой или из пробелов — Host = '' без проверок (прокси не
    ///   задан). Учётные данные в тексты ошибок не попадают. Ошибки —
    ///   ETgError: схема, кроме '' и 'http' (в Scheme или 'схема://' в Host);
    ///   '/', '@' или пробел в Host; порт вне 1..65535; порт в Host
    ///   не совпадает с Port.
    /// </summary>
    function Normalized: TTgProxySettings;
  end;

  /// <summary>
  ///   Настройки транспорта. Создавайте через TTgHttpSettings.Create(Token) —
  ///   он заполняет значения по умолчанию, затем меняйте нужные поля.
  /// </summary>
  TTgHttpSettings = record
    /// <summary>Токен бота.</summary>
    Token: string;
    /// <summary>Адрес сервера Bot API (облачный или Local Bot API server), без '/' в конце.</summary>
    ApiUrl: string;
    /// <summary>Прокси бота.</summary>
    Proxy: TTgProxySettings;
    /// <summary>Таймаут соединения, мс.</summary>
    ConnectionTimeoutMs: Integer;
    /// <summary>Таймаут ответа, мс.</summary>
    ResponseTimeoutMs: Integer;
    /// <summary>Значение заголовка User-Agent.</summary>
    UserAgent: string;
    /// <summary>Автоматически повторять запрос при ошибке 429.</summary>
    AutoRetry429: Boolean;
    /// <summary>Максимум повторов при 429.</summary>
    MaxRetries: Integer;
    /// <summary>Если retry_after больше этого значения (с) — ошибка без ожидания.</summary>
    MaxRetryAfterSec: Integer;
    /// <summary>Глобальный лимит запросов в секунду; 0 — без ограничения.</summary>
    GlobalRatePerSec: Integer;
    /// <summary>Интервал между отправками в один чат, мс; 0 — без ограничения.</summary>
    PerChatIntervalMs: Integer;
    /// <summary>
    ///   Режим Local Bot API server (--local): DownloadFile читает абсолютный
    ///   file_path напрямую с локального диска. Включайте, только если бот
    ///   и сервер Bot API работают на одной машине. По умолчанию False.
    /// </summary>
    LocalMode: Boolean;
    /// <summary>Настройки по умолчанию для указанного токена.</summary>
    class function Create(const AToken: string): TTgHttpSettings; static;
  end;

  /// <summary>Сырой HTTP-ответ.</summary>
  TTgHttpResponse = record
    /// <summary>HTTP-статус.</summary>
    StatusCode: Integer;
    /// <summary>Тело ответа — исходные байты (ожидается JSON в UTF-8).</summary>
    Body: TBytes;
  end;

  /// <summary>
  ///   Транспорт Bot API. Реализации должны быть потокобезопасны.
  /// </summary>
  ITgTransport = interface
    ['{FCE9ECCD-6131-4258-B4BC-6C83CDDACBE8}']
    /// <summary>
    ///   Вызывает метод Bot API и возвращает поле result (объект принадлежит
    ///   вызывающему). AParams может быть nil.
    ///   Ошибки: ETgApiError, ETgNetworkError, ETgCancelledError.
    /// </summary>
    function Execute(const AMethod: string; AParams: TTgParams): TJSONValue;
    /// <summary>
    ///   Скачивает файл по file_path (из getFile) в поток ADest.
    ///   Пути UNC и с сегментом '..' отклоняются (ETgError).
    ///   При ошибке содержимое ADest не определено.
    /// </summary>
    procedure DownloadFile(const AFilePath: string; ADest: TStream);
    /// <summary>
    ///   УСТАРЕЛО: используйте токены отмены (ITgCancellableTransport,
    ///   TTgCancelScope). Глобально прерывает текущие и будущие ожидания
    ///   (лимитёр, retry_after) всех клиентов транспорта — они завершаются
    ///   ETgCancelledError. Уже идущий HTTP-запрос не прерывается.
    /// </summary>
    procedure Cancel;
    /// <summary>УСТАРЕЛО: снимает признак глобальной отмены (см. Cancel).</summary>
    procedure ResetCancel;
    /// <summary>УСТАРЕЛО: признак глобальной отмены установлен (см. Cancel).</summary>
    function IsCancelled: Boolean;
  end;

  /// <summary>
  ///   Транспорт с отменой отдельной операции. Execute/DownloadFile такого
  ///   транспорта используют окружающий токен (TTgCancelScope.Current).
  /// </summary>
  ITgCancellableTransport = interface(ITgTransport)
    ['{6FDF0494-1D1F-4832-B086-3B1E6043EE64}']
    /// <summary>
    ///   Как Execute, но с токеном отмены ACancel (nil — без отмены):
    ///   отмена прерывает ожидания и, где поддерживается, идущий HTTP-запрос
    ///   (ETgCancelledError).
    /// </summary>
    function ExecuteEx(const AMethod: string; AParams: TTgParams;
      const ACancel: ITgCancellation): TJSONValue;
    /// <summary>Как DownloadFile, но с токеном отмены ACancel (nil — без отмены).</summary>
    procedure DownloadFileEx(const AFilePath: string; ADest: TStream;
      const ACancel: ITgCancellation);
  end;

  /// <summary>
  ///   Служебный: транспорт с настройками TTgHttpSettings (реализует
  ///   TTgHttpTransport). Через него клиент получает настройки транспорта без
  ///   приведения к классу. В прикладном коде не нужен.
  /// </summary>
  ITgHttpSettingsProvider = interface
    ['{804B9679-6947-4414-8785-FE1C5499DF87}']
    /// <summary>Настройки транспорта (копия записи).</summary>
    function GetSettings: TTgHttpSettings;
  end;

  { Приём обновлений }

  /// <summary>Состояние источника обновлений.</summary>
  TTgSourceState = (
    /// <summary>Не запущен или остановлен.</summary>
    Idle,
    /// <summary>Принимает обновления.</summary>
    Running,
    /// <summary>Остановка запрошена (дренаж, итоговое подтверждение).</summary>
    Stopping,
    /// <summary>Остановлен из-за неустранимой ошибки (401, 404, webhook и т.п.).</summary>
    Faulted);

  /// <summary>Когда подтверждать (offset) принятые обновления.</summary>
  TTgAckPolicy = (
    /// <summary>
    ///   Сразу после приёма: следующий getUpdates отправляется, как только
    ///   пакет помещён в очередь (ограничение — ёмкость очереди). Быстро, но
    ///   при аварийном завершении процесса обновления из очереди теряются.
    /// </summary>
    AfterReceive,
    /// <summary>
    ///   После обработки: следующий getUpdates — только когда обработаны все
    ///   обновления пакета. Медленнее, зато при сбое пакет придёт повторно.
    /// </summary>
    AfterBatch);

  /// <summary>Где выполняются обработчики обновлений.</summary>
  TTgDelivery = (
    /// <summary>В потоках диспетчера (параллельно для разных чатов).</summary>
    Worker,
    /// <summary>
    ///   В главном потоке (TThread.Queue): для VCL/FMX — без ручной
    ///   синхронизации; в консоли главный поток должен вызывать
    ///   CheckSynchronize (это делает TTgBot.Run).
    /// </summary>
    Main);

  /// <summary>
  ///   Итог приёма webhook-запроса (TTgWebhookSource.Accept); HTTP-код
  ///   ответа — TgWebhookHttpStatus (TgBot.Updates).
  /// </summary>
  TTgWebhookResult = (
    /// <summary>Принято (или повтор уже принятого update_id) — 200.</summary>
    Accepted,
    /// <summary>Неверный X-Telegram-Bot-Api-Secret-Token — 403.</summary>
    Forbidden,
    /// <summary>Тело не JSON-объект обновления, нет update_id или больше лимита — 400.</summary>
    BadRequest,
    /// <summary>
    ///   Источник не запущен, останавливается, в Faulted или очередь
    ///   переполнена — 503 (Telegram повторит доставку позже).
    /// </summary>
    Unavailable);

  /// <summary>
  ///   Обновление Bot API в сыром виде. Владеет своим JSON-объектом (не
  ///   освобождайте Json); живёт, пока на него есть ссылки.
  /// </summary>
  ITgRawUpdate = interface
    ['{D51FD45E-3FE0-4240-9B70-5A58992E6674}']
    function GetUpdateId: Int64;
    function GetKind: string;
    function GetChatKey: string;
    function GetJson: TJSONObject;
    /// <summary>update_id.</summary>
    property UpdateId: Int64 read GetUpdateId;
    /// <summary>Вид обновления — имя поля ('message', 'callback_query', …; TTgUpdateType).</summary>
    property Kind: string read GetKind;
    /// <summary>
    ///   Ключ порядка: id чата ('-100123'), 'u' + id пользователя для
    ///   обновлений без чата ('u42'), '' — порядок не важен (poll, poll_answer).
    /// </summary>
    property ChatKey: string read GetChatKey;
    /// <summary>JSON обновления целиком (владелец — обновление).</summary>
    property Json: TJSONObject read GetJson;
  end;

  /// <summary>Приёмник обновлений (очередь диспетчера).</summary>
  ITgUpdateSink = interface
    ['{C83E716B-723A-43C2-8DE7-FCC6C6BAD5BF}']
    /// <summary>
    ///   Ставит обновление в очередь; при полной очереди ждёт места.
    ///   False — приёмник остановлен или ACancel отменён (обновление не принято).
    /// </summary>
    function Post(const AUpdate: ITgRawUpdate; const ACancel: ITgCancellation): Boolean;
  end;

  /// <summary>
  ///   Приёмник с ограниченным ожиданием места в очереди (webhook: поток
  ///   HTTP-сервера не должен висеть на полной очереди).
  /// </summary>
  ITgTimedUpdateSink = interface
    ['{8E4B1F0A-6C2D-4E73-9A5B-3D7F2C1E8B64}']
    /// <summary>
    ///   Как Post, но место в очереди ждёт не дольше ATimeoutMs мс (0 — не
    ///   ждёт). False — очередь полна, приёмник остановлен или ACancel отменён.
    /// </summary>
    function TryPost(const AUpdate: ITgRawUpdate; const ACancel: ITgCancellation;
      ATimeoutMs: Cardinal): Boolean;
  end;

  /// <summary>
  ///   Приём тела webhook-запроса из любого HTTP-сервера (потокобезопасно,
  ///   из любого числа потоков). ASecretHeader — значение заголовка
  ///   X-Telegram-Bot-Api-Secret-Token ('' — заголовка нет).
  /// </summary>
  ITgWebhookReceiver = interface
    ['{4F7A2C9E-1B3D-4A86-8E5F-6C0D9B2A7E31}']
    /// <summary>Тело — байты UTF-8 (как пришли по сети).</summary>
    function Accept(const ABody: TBytes; const ASecretHeader: string): TTgWebhookResult; overload;
    /// <summary>Тело — уже декодированная строка.</summary>
    function Accept(const ABody, ASecretHeader: string): TTgWebhookResult; overload;
  end;

  /// <summary>Источник обновлений (long polling или webhook).</summary>
  ITgUpdateSource = interface
    ['{2EB5AB98-37B8-4632-8BB9-B64429C8269B}']
    /// <summary>Запускает приём в ASink. Повторный Start работающего источника — ETgError.</summary>
    procedure Start(const ASink: ITgUpdateSink);
    /// <summary>
    ///   Останавливает приём не дольше ≈AWaitMs мс. False — поток не удалось
    ///   прервать и он отпущен (его поздний результат будет выброшен).
    /// </summary>
    function Stop(AWaitMs: Cardinal): Boolean;
    /// <summary>Обновление AUpdateId обработано (для подтверждения offset).</summary>
    procedure Processed(AUpdateId: Int64);
    function GetState: TTgSourceState;
    /// <summary>Состояние источника.</summary>
    property State: TTgSourceState read GetState;
  end;

  /// <summary>Часы и паузы источника (подменяются в тестах).</summary>
  ITgPollTimer = interface
    ['{CD72B2B4-FC57-46C4-958D-A76187CBB215}']
    /// <summary>Монотонное время, мс.</summary>
    function NowMs: Int64;
    /// <summary>Пауза AMs мс; True — прервана отменой ACancel.</summary>
    function Sleep(AMs: Cardinal; const ACancel: ITgCancellation): Boolean;
  end;

  /// <summary>Обработчик обновления нижнего уровня.</summary>
  TTgRawHandler = reference to procedure(const AUpdate: ITgRawUpdate);
  /// <summary>Обработчик исключения обработчика (объект исключения действителен только внутри).</summary>
  TTgRawErrorHandler = reference to procedure(AError: Exception; const AUpdate: ITgRawUpdate);
  /// <summary>Событие конфликта 409 (объект исключения действителен только внутри).</summary>
  TTgConflictHandler = reference to procedure(AError: ETgConflictError);

  { Состояние диалогов }

  /// <summary>
  ///   Хранилище состояния: строковые значения AName в пределах ключа AKey.
  ///   Реализации обязаны быть потокобезопасными.
  /// </summary>
  ITgStateStorage = interface
    ['{0C6A2F51-5A3B-4D7E-9B83-61A7C4E2D915}']
    /// <summary>Значение AName ключа AKey; False — значения нет.</summary>
    function TryGet(const AKey, AName: string; out AValue: string): Boolean;
    /// <summary>Записывает (заменяет) значение AName ключа AKey.</summary>
    procedure Put(const AKey, AName, AValue: string);
    /// <summary>Удаляет значение AName ключа AKey; AName = '' — все значения ключа.</summary>
    procedure Delete(const AKey: string; const AName: string = '');
  end;

implementation

uses
  TgBot.Consts;

{ TTgProxySettings }

class function TTgProxySettings.Create(const AHost: string; APort: Integer;
  const AUserName, APassword, AScheme: string): TTgProxySettings;
begin
  Result.Host := AHost;
  Result.Port := APort;
  Result.UserName := AUserName;
  Result.Password := APassword;
  Result.Scheme := AScheme;
end;

function TTgProxySettings.IsEnabled: Boolean;
begin
  Result := Host <> '';
end;

/// <summary>Порт в адресе прокси: 1–5 десятичных цифр (без знака и '$').</summary>
function IsProxyPortText(const AText: string): Boolean;
var
  I: Integer;
begin
  Result := (Length(AText) >= 1) and (Length(AText) <= 5);
  for I := 1 to Length(AText) do
    if not CharInSet(AText[I], ['0'..'9']) then
      Exit(False);
end;

/// <summary>Имя схемы URL (буквы, цифры, '+', '-', '.') — без учётных данных.</summary>
function IsSchemeName(const AText: string): Boolean;
var
  I: Integer;
begin
  Result := AText <> '';
  for I := 1 to Length(AText) do
    if not CharInSet(AText[I], ['A'..'Z', 'a'..'z', '0'..'9', '+', '-', '.']) then
      Exit(False);
end;

function TTgProxySettings.Normalized: TTgProxySettings;
const
  CHttpPrefix = 'http://';
  CSchemeMark = '://';

  procedure RaiseBadHost;
  begin
    raise ETgError.Create(TgLangText(@SRuProxyBadHost, @SEnProxyBadHost));
  end;

var
  LHost, LPortText, LScheme: string;
  LMark, LColons, LHostPort, I: Integer;
begin
  Result := Self;
  LHost := Trim(Host);
  Result.Host := LHost;
  if LHost = '' then
    Exit;
  // Схема RTL всё равно пустая (ToRtlSettings); иные значения — неподдерживаемый прокси.
  LScheme := Trim(Scheme);
  if (LScheme <> '') and not SameText(LScheme, 'http') then
    raise ETgError.Create(TgLangTextFmt(@SRuProxyScheme, @SEnProxyScheme, [LScheme]));
  if SameText(Copy(LHost, 1, Length(CHttpPrefix)), CHttpPrefix) then
    Delete(LHost, 1, Length(CHttpPrefix))
  else
  begin
    LMark := Pos(CSchemeMark, LHost);
    if LMark > 0 then
    begin
      // В текст — только имя схемы: после неё могут идти логин и пароль.
      LScheme := Copy(LHost, 1, LMark - 1);
      if not IsSchemeName(LScheme) then
        RaiseBadHost;
      raise ETgError.Create(TgLangTextFmt(@SRuProxyScheme, @SEnProxyScheme, [LScheme]));
    end;
  end;
  if LHost = '' then
    RaiseBadHost;
  for I := 1 to Length(LHost) do
    if CharInSet(LHost[I], ['/', '\', '@']) or (LHost[I] <= ' ') then
      RaiseBadHost;
  LPortText := '';
  if LHost[1] = '[' then
  begin
    // IPv6 в скобках: '[адрес]' или '[адрес]:порт'.
    LMark := Pos(']', LHost);
    if (LMark <= 2) or (Pos('[', Copy(LHost, 2, LMark - 2)) > 0) then
      RaiseBadHost;
    LPortText := Copy(LHost, LMark + 1, MaxInt);
    SetLength(LHost, LMark);
    if LPortText <> '' then
    begin
      if LPortText[1] <> ':' then
        RaiseBadHost;
      Delete(LPortText, 1, 1);
      if not IsProxyPortText(LPortText) then
        RaiseBadHost;
    end;
  end
  else
  begin
    if (Pos('[', LHost) > 0) or (Pos(']', LHost) > 0) then
      RaiseBadHost;
    LColons := 0;
    for I := 1 to Length(LHost) do
      if LHost[I] = ':' then
        Inc(LColons);
    if LColons = 1 then
    begin
      LMark := Pos(':', LHost);
      LPortText := Copy(LHost, LMark + 1, MaxInt);
      SetLength(LHost, LMark - 1);
      if (LHost = '') or not IsProxyPortText(LPortText) then
        RaiseBadHost;
    end
    else if LColons > 1 then
      // IPv6 без скобок: порт в такой записи неотделим — только из Port.
      LHost := '[' + LHost + ']';
  end;
  Result.Host := LHost;
  if LPortText <> '' then
  begin
    LHostPort := StrToInt(LPortText);
    if (Result.Port <> 0) and (Result.Port <> LHostPort) then
      raise ETgError.Create(TgLangTextFmt(@SRuProxyPortConflict, @SEnProxyPortConflict,
        [LHost, LHostPort, Result.Port]));
    Result.Port := LHostPort;
  end;
  if (Result.Port < 1) or (Result.Port > 65535) then
    raise ETgError.Create(TgLangTextFmt(@SRuProxyPort, @SEnProxyPort, [LHost, Result.Port]));
end;

{ TTgHttpSettings }

class function TTgHttpSettings.Create(const AToken: string): TTgHttpSettings;
begin
  Result := Default(TTgHttpSettings);
  Result.Token := AToken;
  Result.ApiUrl := TgDefaultApiUrl;
  Result.ConnectionTimeoutMs := TgDefaultConnectionTimeoutMs;
  Result.ResponseTimeoutMs := TgDefaultResponseTimeoutMs;
  Result.UserAgent := TgBotUserAgent;
  Result.AutoRetry429 := True;
  Result.MaxRetries := TgDefaultMaxRetries;
  Result.MaxRetryAfterSec := TgDefaultMaxRetryAfterSec;
  Result.GlobalRatePerSec := TgDefaultGlobalRatePerSec;
  Result.PerChatIntervalMs := TgDefaultPerChatIntervalMs;
end;

end.
