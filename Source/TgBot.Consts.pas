unit TgBot.Consts;

{
  TgBot — библиотека Telegram Bot API для Delphi.
  Ресурсные строки библиотеки: тексты исключений и сообщений (RU/EN),
  по образцу System.RTLConsts / System.SysConst.

  Служебный модуль: подключается только в разделах implementation модулей
  библиотеки. В прикладном коде его не подключайте — язык сообщений
  выбирается через TgSetLanguage, тексты возвращают TgText, TgTextFmt,
  TgUpdatesText, TgRouterText (фасад TgBot этот модуль не реэкспортирует).

  Устройство:
  - каждый текст — пара ресурсных строк рядом: SRu<Имя> (русский) и
    SEn<Имя> (английский); язык выбирает TgLangText из TgBot.Base;
  - секции по подсистемам с префиксами: ядро — без префикса (SRu<Имя>),
    JSON — SRuJson…, DTO — SRuDto…, обновления — SRuUpd…, маршрутизатор —
    SRuRoute…, TTgBot — SRuBot…, компонент — SRuComp…, webhook-сервер —
    SRuWhs…;
  - подстановки (%s, %d) сохраняйте в переводе в том же порядке и количестве.

  Перевод (Translation Manager / ITE): обе группы, SRu… и SEn…, —
  resourcestring и попадают в ресурсы пакета/программы. Чтобы получить
  третий язык, переведите в ресурсной DLL строки той группы, которая
  выбрана через TgSetLanguage (обычно SEn…). Имена модулей, методов
  и полей Telegram Bot API в тексты не переводятся.

  Модуль не использует другие модули и компилируется на всех платформах
  библиотеки (Win32, Win64, Linux64, Android/Android64).
}

interface

resourcestring

  { Ядро: тексты TTgText (TgText/TgTextFmt из TgBot.Base) }

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
  // Дополнение сетевой ошибки: текст ошибки, затем адрес прокси (host:port).
  SRuViaProxy = '%s; запрос шёл через прокси %s';
  SEnViaProxy = '%s; the request was sent via proxy %s';

  { Ядро: проверка настроек прокси (TTgProxySettings.Normalized, TgLangText).
    Учётные данные не подставляются. Подстановки: схема (ProxyScheme); хост
    и порт (ProxyPort); хост, порт из Host и Port (ProxyPortConflict). }

  SRuProxyScheme = 'Схема прокси "%s" не поддерживается: поддерживается только HTTP-прокси ' +
    '(CONNECT), SOCKS/HTTPS-прокси — нет. Оставьте Scheme пустым, Host — без схемы или с http://';
  SEnProxyScheme = 'Proxy scheme "%s" is not supported: only an HTTP proxy (CONNECT) is ' +
    'supported, SOCKS/HTTPS proxies are not. Leave Scheme empty and Host without a scheme or with http://';
  SRuProxyBadHost = 'Недопустимый адрес прокси (Host): укажите хост или хост:порт без пути ' +
    'и учётных данных — логин и пароль задаются в UserName/Password';
  SEnProxyBadHost = 'Invalid proxy address (Host): specify host or host:port without a path ' +
    'or credentials — set the login and password in UserName/Password';
  SRuProxyPort = 'Прокси %s: укажите порт прокси 1–65535 (Port или "хост:порт" в Host), задано %d';
  SEnProxyPort = 'Proxy %s: specify the proxy port 1-65535 (Port or "host:port" in Host), got %d';
  SRuProxyPortConflict = 'Прокси %s: порт в Host (%d) не совпадает с Port (%d)';
  SEnProxyPortConflict = 'Proxy %s: the port in Host (%d) does not match Port (%d)';

  { Ядро: проверка аргументов (EArgumentNilException, EArgumentOutOfRangeException).
    Первая подстановка — имя параметра (не переводится). }

  SRuArgNil = 'Параметр %s не может быть nil';
  SEnArgNil = 'Parameter %s must not be nil';
  SRuArgOutOfRange = 'Параметр %s = %d вне допустимого диапазона (минимум %d)';
  SEnArgOutOfRange = 'Parameter %s = %d is out of range (minimum %d)';

  { JSON: чтение чисел и запись параметров (TTgJson, TgBot.Json).
    Подстановки: имя поля/параметра, затем JSON-текст значения. }

  SRuJsonNotInteger = 'Поле «%s»: значение %s не является целым числом в диапазоне Int64';
  SEnJsonNotInteger = 'Field "%s": value %s is not an integer within the Int64 range';
  SRuJsonIntegerRange = 'Поле «%s»: значение %s вне диапазона Integer';
  SEnJsonIntegerRange = 'Field "%s": value %s is out of the Integer range';
  SRuJsonNotFloat = 'Поле «%s»: значение %s не представимо вещественным числом';
  SEnJsonNotFloat = 'Field "%s": value %s cannot be represented as a floating-point number';
  SRuJsonFloatInvalid = 'Параметр «%s»: недопустимое вещественное значение (NaN или бесконечность)';
  SEnJsonFloatInvalid = 'Parameter "%s": invalid floating-point value (NaN or infinity)';

  { DTO: объекты поверх JSON и сериализация (TgBot.Dto) }

  SRuDtoNotObject = 'Значение не является JSON-объектом (поле %s)';
  SEnDtoNotObject = 'The value is not a JSON object (field %s)';
  SRuDtoFileUpload = 'Поле %s: загрузка файла невозможна вне параметров метода';
  SEnDtoFileUpload = 'Field %s: file upload is not possible outside method parameters';
  SRuDtoUnsupported = 'Объект типа %s не поддерживает сериализацию';
  SEnDtoUnsupported = 'Object of type %s does not support serialization';
  SRuDtoEmptyItem = 'Элемент %d массива «%s» не задан (nil или пустое объединение)';
  SEnDtoEmptyItem = 'Item %d of array "%s" is not set (nil or empty union)';
  SRuDtoNotJsonDto = 'Объект типа %s не является DTO поверх JSON (ITgJsonObject)';
  SEnDtoNotJsonDto = 'Object of type %s is not a JSON-based DTO (ITgJsonObject)';

  { Обновления: источники, диспетчер, TTgBot, контекст (TTgUpdatesText,
    TgUpdatesText из TgBot.Updates.Types; webhook-источник). }

  SRuUpdSourceRunning = 'Источник обновлений уже запущен';
  SEnUpdSourceRunning = 'Update source is already running';
  SRuUpdDispatcherRunning = 'Диспетчер обновлений уже запущен';
  SEnUpdDispatcherRunning = 'Update dispatcher is already running';
  SRuUpdStopFromHandler = 'Нельзя ждать остановки бота из обработчика обновления: ' +
    'используйте RequestStop';
  SEnUpdStopFromHandler = 'Cannot wait for the bot to stop from an update handler: ' +
    'use RequestStop';
  SRuUpdNoChat = 'В обновлении нет чата для ответа';
  SEnUpdNoChat = 'The update has no chat to reply to';
  SRuUpdRunNotMainThread = 'Run с Delivery = Main можно вызывать только из главного потока';
  SEnUpdRunNotMainThread = 'Run with Delivery = Main must be called from the main thread';
  SRuUpdRunUnsupported = 'Run недоступен на этой платформе: используйте Start и Stop';
  SEnUpdRunUnsupported = 'Run is not available on this platform: use Start and Stop';
  SRuUpdBotRunning = 'Бот уже запущен';
  SEnUpdBotRunning = 'The bot is already running';
  SRuUpdHandlerFiltered = 'Назначен %s, но AllowedUpdates не содержит "%s": ' +
    'такие обновления сервер присылать не будет';
  SEnUpdHandlerFiltered = '%s is assigned, but AllowedUpdates does not include "%s": ' +
    'the server will not send such updates';
  SRuUpdWebhookUrlRequired = 'Режим Webhook: не задан WebhookUrl (внешний HTTPS-адрес бота)';
  SEnUpdWebhookUrlRequired = 'Webhook mode: WebhookUrl (the public HTTPS address of the bot) is not set';
  SRuUpdWebhookBadSecret = 'Недопустимый секрет webhook: нужно 1–256 символов A-Z, a-z, 0-9, "_" и "-"';
  SEnUpdWebhookBadSecret = 'Invalid webhook secret: 1-256 characters A-Z, a-z, 0-9, "_" and "-" are required';
  SRuUpdWebhookUnsupported = 'Режим Webhook недоступен на этой платформе: используйте Polling';
  SEnUpdWebhookUnsupported = 'Webhook mode is not available on this platform: use Polling';
  SRuUpdNoRandom = 'Криптостойкий генератор случайных чисел ОС недоступен';
  SEnUpdNoRandom = 'The OS cryptographic random number generator is not available';

  { Маршрутизатор: регистрация правил (TTgRouterText, TgRouterText из
    TgBot.Router; те же тексты — у TTelegramBot). Подстановки: имя метода
    регистрации (пустой ключ), имя команды как задано (недопустимая команда). }

  SRuRouteEmptyKey = 'Пустой ключ правила маршрутизатора (%s)';
  SEnRouteEmptyKey = 'Empty router rule key (%s)';
  SRuRouteBadCommand = 'Недопустимое имя команды "%s": пробелы и "@" не допускаются';
  SEnRouteBadCommand = 'Invalid command name "%s": spaces and "@" are not allowed';

  { TTgBot: проверка параметров запуска (TgBot.Bot) }

  SRuBotWebhookNotHttps = 'Режим Webhook: WebhookUrl должен начинаться с https:// ' +
    '(Telegram принимает только HTTPS; http:// — только с Local Bot API server)';
  SEnBotWebhookNotHttps = 'Webhook mode: WebhookUrl must start with https:// ' +
    '(Telegram accepts HTTPS only; http:// is allowed only with a Local Bot API server)';
  SRuBotWebhookNoSecret = 'Webhook без секрета: при регистрации вне бота передайте secret_token ' +
    'и задайте WebhookSecretToken — иначе обновление может прислать любой, кто знает URL';
  SEnBotWebhookNoSecret = 'Webhook without a secret: when registering outside the bot, pass secret_token ' +
    'and set WebhookSecretToken — otherwise anyone who knows the URL can send updates';

  { Компонент TTelegramBot (TgBot.Component). Ключи правил и имена команд
    проверяются текстами маршрутизатора (SRuRoute…). }

  SRuCompBotActive = 'Нельзя менять свойства TTelegramBot, пока бот работает (Active = True)';
  SEnCompBotActive = 'Cannot change TTelegramBot properties while the bot is running (Active = True)';
  SRuCompNoWebhookPath = 'TTelegramBot: не задан путь webhook для Webhook.Server — ' +
    'задайте Name компонента или Webhook.Path';
  SEnCompNoWebhookPath = 'TTelegramBot: the webhook path for Webhook.Server is not set — ' +
    'set the component Name or Webhook.Path';
  SRuCompNoCertificate = 'TTelegramBot: файл сертификата Webhook.Certificate не найден: %s';
  SEnCompNoCertificate = 'TTelegramBot: Webhook.Certificate file not found: %s';
  SRuCompRunNotMain = 'TTelegramBot.Run с Delivery = Main можно вызывать только из главного потока';
  SEnCompRunNotMain = 'TTelegramBot.Run with Delivery = Main must be called from the main thread';
  SRuCompRunUnsupported = 'TTelegramBot.Run недоступен на этой платформе: используйте Active';
  SEnCompRunUnsupported = 'TTelegramBot.Run is not available on this platform: use Active';

  { Webhook-сервер TTgWebhookServer (TgBot.Webhook, пакет TgBotIndyRT).
    Подстановки: путь webhook и имя бота-владельца (PathTaken); адрес,
    порт и текст ошибки Indy (StartFailed). Стандартные фразы HTTP
    (Bad Request, Not Found…) — не тексты библиотеки и не переводятся. }

  SRuWhsServerActive = 'Нельзя менять Port, BindAddress и MaxConnections, пока сервер работает';
  SEnWhsServerActive = 'Cannot change Port, BindAddress and MaxConnections while the server is running';
  SRuWhsBadPort = 'Недопустимый порт %d (0–65535)';
  SEnWhsBadPort = 'Invalid port %d (0-65535)';
  SRuWhsBadBodySize = 'Недопустимый MaxBodySize %d (нужно больше 0)';
  SEnWhsBadBodySize = 'Invalid MaxBodySize %d (must be greater than 0)';
  SRuWhsBadConnections = 'Недопустимый MaxConnections %d (нужно 0 и больше)';
  SEnWhsBadConnections = 'Invalid MaxConnections %d (must be 0 or greater)';
  SRuWhsStartFailed = 'Не удалось запустить webhook-сервер на %s:%d: %s';
  SEnWhsStartFailed = 'Failed to start the webhook server on %s:%d: %s';
  SRuWhsPathTaken = 'Путь webhook "%s" уже занят другим ботом (%s)';
  SEnWhsPathTaken = 'Webhook path "%s" is already used by another bot (%s)';
  SRuWhsBadPath = 'Недопустимый путь webhook "%s": пробелы, "?" и "#" не допускаются';
  SEnWhsBadPath = 'Invalid webhook path "%s": spaces, "?" and "#" are not allowed';
  SRuWhsPublicUrlNotHttps = 'PublicUrl webhook-сервера должен начинаться с https:// ' +
    '(Telegram принимает только HTTPS): %s';
  SEnWhsPublicUrlNotHttps = 'The webhook server PublicUrl must start with https:// ' +
    '(Telegram accepts HTTPS only): %s';

implementation

end.
