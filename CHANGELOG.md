# История изменений TgBot

## 0.5.0 — 2026-10-19

Локализация сообщений библиотеки: язык по умолчанию — английский, подключаемый переводчик `ITgTranslator`,
загрузчик переводов gettext (`.po`) — модуль `TgBot.Po`, каталоги `Locale\tgbot.pot` и `Locale\ru.po` и их
генератор `Tools\Locale\MakePot.ps1`. **Есть несовместимое изменение** — язык по умолчанию, см. «Миграция».

### Несовместимые изменения

- **Язык текстов библиотеки по умолчанию — английский (`TTgLanguage.En`).** Без вызова `TgSetLanguage` тексты
  исключений библиотеки (`ETgError` и наследники) и готовые тексты (`TgText`, `TgUpdatesText`, `TgRouterText`)
  теперь на английском, до 0.5.0 были на русском. **Миграция:** прежнее поведение —
  `TgSetLanguage(TTgLanguage.Ru)` в начале программы, до запуска ботов и рабочих потоков. Это касается и
  кода, который сравнивает или разбирает `E.Message`, и перевода ресурсными DLL (ITE) группы `SRu…`.
- В пакет `TgBotRT` добавлен модуль `TgBot.Po` — пакеты пересоберите.

### Новое

- **Подключаемый переводчик `ITgTranslator`** (`TgBot.Base`; псевдонимы в `TgBot.Intf` и фасаде `TgBot`),
  установка и чтение — `TgSetTranslator`/`TgGetTranslator` (есть и в фасаде). Ключ перевода (msgid в стиле
  gettext) — английский текст сообщения до подстановки аргументов `Format` (`LoadResString(SEn…)` из
  `TgBot.Consts`). Перевод применяется при любом языке `TgSetLanguage`; нет перевода (`False` или пустая
  строка) — встроенный текст на текущем языке, то есть встроенный язык служит запасным.
  - Перевод текста с форматированием, аргументы `Format` которого не совпадают с ключом (сравниваются
    множество индексов и тип каждого; порядок, повторы, ширина, точность и `%%` — нет, поэтому перестановка
    через `%1:s … %0:d` допустима), отбрасывается — используется встроенный текст. Перевод текста без
    форматирования отдаётся как есть, без `Format`.
  - Исключения `TryTranslate`, кроме `EOutOfMemory`, поглощаются библиотекой — встроенный текст.
  - `TgSetTranslator`/`TgGetTranslator` потокобезопасны (замок `TCriticalSection`), прежний переводчик
    освобождается вне замка; реализация `TryTranslate` тоже должна быть потокобезопасной.
  - `TgSetTranslator(nil)` вызывайте до завершения программы (в своём `finalization` или `OnDestroy`),
    особенно если переводчик живёт в BPL/DLL.
  - Ключ — английский текст `SEn…`, поэтому переводчик не сочетается с переводом ресурсными DLL (ITE): при
    ITE ключ уже переведён — используйте одно из двух.
- **`TgSameFormatSignature(A, B)`** (`TgBot.Base`) стала публичной: та же проверка аргументов `Format`, которой
  библиотека отбрасывает неподходящий перевод, — для своих загрузчиков переводов.
- **Модуль `TgBot.Po` — загрузчик переводов gettext.** `TgLoadPoTranslator(AFileName)` и
  `TgLoadPoTranslatorFromStream(AStream, ASourceName)` (поток с текущей позиции до конца — `TResourceStream`,
  asset на Android) возвращают `ITgPoTranslator` для `TgSetTranslator`: `Count` — число загруженных
  переводов, `Warnings` — предупреждения загрузки, `Language` — поле `Language:` заголовка. Фасад `TgBot`
  модуль не реэкспортирует — `uses TgBot.Po`. Разбор:
  - строго UTF-8 (BOM необязателен; недопустимые байты — ошибка), переводы строк CRLF, LF или CR; `charset`
    заголовка, кроме UTF-8 и ASCII, — ошибка;
  - неточные (`#, fuzzy`), непереведённые (пустой `msgstr`) и устаревшие (`#~`) записи пропускаются молча;
  - в `Warnings`: запись с `msgctxt` и непустым переводом (контекст не поддерживается — запись пропущена),
    перевод с несовпадающими спецификаторами `Format` (отброшен), повтор `msgid` (действует последняя запись);
  - строки `"…"` подряд склеиваются, escape-последовательности C (`\ooo` и `\x` — только символы ASCII);
    `msgid_plural`/`msgstr[n]` разбираются, перевод — `msgstr[0]`;
  - синтаксическая ошибка — `ETgPoError` (наследник `ETgError`) с именем источника (`FileName`) и номером
    строки (`LineNumber`).
  Тексты ошибок и предупреждений — на языке библиотеки (пары `SRuPo…`/`SEnPo…` в `TgBot.Consts`; всего в
  `TgBot.Consts` теперь 82 пары текстов).
- **Каталоги перевода `Locale\tgbot.pot` и `Locale\ru.po`** — шаблон для переводчиков (`msgid` — английский
  текст, 82 записи, из них 47 с флагом `object-pascal-format`) и готовый русский перевод; UTF-8 без BOM, LF.
- **`Tools\Locale\MakePot.ps1`** строит оба каталога из пар `SRu…`/`SEn…` `TgBot.Consts` (детерминированно:
  повторный запуск без изменений даёт те же байты); `-Check` — только сверка актуальности (код 1, если
  каталоги устарели). Ошибки исходника — с файлом и строкой (в том числе разные спецификаторы `Format` у
  `SRu…` и `SEn…`). `Tools\Dist\MakeDist.ps1` включает `Locale` и `Tools\Locale\MakePot.ps1` в дистрибутив.
- Демо `01_Smoke`: переменная `TGBOT_LANG=RU|EN` (не задана — английский). Демо 02–05 с русским интерфейсом
  вызывают `TgSetLanguage(TTgLanguage.Ru)` явно.

### Тесты

- Всего 125 тестов (4788 проверок; в 0.4.2 — 115 и 3823). Новые: `TestDefaultLanguage` (при запуске и до
  `TgSetLanguage` — En), `TestTranslatorBasic` (перевод при Ru и En, нет и пустой перевод,
  `TgSetTranslator(nil)`), `TestTranslatorFaults` (исключение переводчика и `EAbort` → встроенный текст,
  `EOutOfMemory` — наружу; перевод с меньшим числом аргументов, другим типом, неверными спецификаторами →
  встроенный; перестановка `%1:s %0:s` и `%%` → перевод), `TestTranslatorThreads` (4 потока x 2000 чтений
  при смене переводчика 500 раз), `TestPoBasic`, `TestPoSyntax` (в том числе `TgSameFormatSignature`),
  `TestPoSkipped`, `TestPoErrors` (`ETgPoError` с номером строки, RU/EN), `TestPoStream` (поток больше 64 КиБ,
  эмодзи на границе 64 КиБ, короткие `Read`, поток без `Size`), `TestPoRuLocale` (`Locale\ru.po` проекта
  загружается без предупреждений, `Count` — числу разных текстов `SEn…`, при En каждый текст переводится на
  русский). Тест ответа 409 проверяет текст на текущем языке и отдельно на русском.

### Миграция

| Было | Стало |
|---|---|
| тексты исключений библиотеки по умолчанию на русском | по умолчанию на английском; прежнее поведение — `TgSetLanguage(TTgLanguage.Ru)` в начале программы |
| сравнение или разбор `E.Message` с русским текстом | вызовите `TgSetLanguage(TTgLanguage.Ru)` или проверяйте тип исключения и свойства (`ETgApiError.ErrorCode` и т.п.) |
| перевод ресурсной DLL (ITE) группы `SRu…` без `TgSetLanguage` | добавьте `TgSetLanguage(TTgLanguage.Ru)` (или переводите группу `SEn…`) |
| перевод на свой язык только ресурсными DLL (ITE) | можно `.po`: `Locale\tgbot.pot` → Poedit → `xx.po`, `uses TgBot.Po` и `TgSetTranslator(TgLoadPoTranslator('xx.po'))`; ITE и переводчик не сочетайте |
| пакеты `TgBotRT` 0.4.x | пересоберите (новый модуль `TgBot.Po`) |

## 0.4.2 — 2026-10-18

Диспетчер обновлений ждёт на `TCriticalSection` и `TEvent` вместо `TMonitor.Wait`/`PulseAll`. Публичный API
не менялся.

### Улучшено

- **Диспетчер обновлений не использует `TMonitor.Wait`/`Pulse`/`PulseAll`.** Замок ядра — `TCriticalSection`,
  ожидания — на `TEvent` с автосбросом: рабочие потоки ждут общего события (будится один спящий, он
  передаёт сигнал дальше), `Post`/`TryPost` на полной очереди — личного события из пула ядра, задания
  главного потока (`Delivery = Main`) — события своего потока диспетчера; состояние задания меняется через
  `TInterlocked`. Условие всегда перепроверяется под замком, поэтому сигнал не теряется. API и поведение
  (порядок внутри чата, отмена, `Stop`, неблокирующий `Free`) не изменились.

### Тесты

- Всего 115 тестов (3823 проверки).
- Стресс-тесты диспетчера (выполняются в общем прогоне; отдельно — `TG_ONLY="Фаза 1"`):
  `TestDispatcherStress` — 8 производителей, 16 чатов, 9 конфигураций ёмкости очереди (1, 2, 4) x
  `MaxParallel` (1, 4, 8): ни одно обновление не потеряно и не обработано дважды, порядок внутри чата
  сохранён; `TestDispatcherBlockedPostCancel` — `Post` на полной очереди возвращается по отмене токена
  быстрее 200 мс; `TestDispatcherBlockedPostStop` — `Stop` из фонового потока разблокирует все ждущие `Post`;
  `TestDispatcherTryPostTimeout` — на полной очереди `TryPost(0)` отказывает сразу, `TryPost(250)` — в
  ожидаемом окне, а при освобождении места посреди ожидания возвращает `True` раньше срока;
  `TestDeliveryMainStress` — `Delivery = Main` под нагрузкой и `Stop` посреди накопленной очереди главного
  потока.
- `Tests\NoNet\check.ps1` перед сборкой проверяет исходники `Source` (рекурсивно, `*.pas`/`*.inc`): нет вызовов
  `TMonitor.Wait`/`Pulse`/`PulseAll` и `MonitorWait`/`MonitorPulse`/`MonitorPulseAll` и примитивов RTL на них
  (`TLightweightEvent`, `TLightweightSemaphore`, `TCountdownEvent`, `TConditionVariable*`); найдено — FAIL.
  `TMonitor.Enter`/`Exit` и `TLightweightMREW` разрешены.

## 0.4.1 — 2026-10-17

Источники обновлений `TTgBot` создаются по `Mode` при `Start`, `WebhookReceiver` больше не удерживает бота
после `Free`. Публичный API не менялся.

### Улучшено

- **Источник обновлений создаётся при `Start` только для выбранного `Mode`** (раньше `TTgBot` при создании
  строил оба — long polling и webhook). Следующие запуски в том же режиме используют тот же источник (память
  дедупликации webhook переживает `Stop`/`Start`), при смене `Mode` источник прежнего режима освобождается.
  До первого `Start` `SourceState` — `Idle`, а `HandleWebhook`/`WebhookReceiver` отвечают `Unavailable`, как
  и раньше.
- **`WebhookReceiver` — переходник, после `Free` бота не держит ядро.** Приёмник стал постоянным
  переходником к webhook-источнику бота (тот же объект на всю жизнь бота, можно взять до `Start`); при
  `Free` бот отцепляет его, поэтому сохранённая ссылка не держит ни источник, ни ядро бота с клиентом — они
  освобождаются при `Free`, а не с последней ссылкой на приёмник (ограничение 0.3.0). Из приёмника
  по-прежнему нельзя получить `ITgWebhookSource`.
- **Позиция long polling сохраняется при смене `Mode`.** Отпуская источник long polling (Polling →
  Webhook), бот запоминает, с какого `offset` продолжить, и новый источник (Webhook → Polling) начинает
  с него: уже обработанные обновления не приходят повторно, даже если итоговое подтверждение при `Stop` не
  прошло. Для своего кода — `TTgLongPollSource.New(ATransport, AParentCancel, AStartOffset)`.
- **`SourceState` потокобезопасен.** Чтение из любого потока (в т.ч. во время `Start` со сменой `Mode`)
  берёт ссылку на источник под блокировкой и не может получить освобождаемый источник.

### Совместимость

- Дедупликация webhook (`WebhookDedupWindow`) сбрасывается при смене `Mode`: память повторов живёт в
  webhook-источнике и освобождается вместе с ним. Повторная доставка `update_id`, принятого до перехода
  Webhook → Polling → Webhook, будет обработана заново.

### Тесты

- Всего 110 тестов (2519 проверок). Новые: `TestBotLazySources` (до `Start` источников нет; `Start` создаёт
  источник только для `Mode`, смена режима освобождает прежний; `WebhookReceiver` — тот же объект, после
  `Free` ядро освобождено при живом приёмнике; дедупликация переживает `Stop`/`Start`),
  `TestBotPollResumeAcrossMode` (Polling → Webhook (Faulted) → Polling: offset продолжается, с итоговым
  подтверждением и без), `TestBotFaultedModeSwitch` (Faulted → `Start` в другом `Mode`),
  `TestBotReceiverModeSwitchRace` (`Accept` и `SourceState` из других потоков во время смены `Mode` и `Free`).
  Тестовый хук `TgTestBotWebhookSource` (`TGBOT_TESTHOOKS`).

## 0.4.0 — 2026-10-17

Протокол Bot API отделён от HTTP-клиента. Контракты (интерфейсы и записи настроек) — в новом модуле
`TgBot.Intf`, протокол — в базе транспорта `TTgTransportBase` (`TgBot.Transport`), HTTP-транспорт на
`System.Net.HttpClient` (`TgBot.Http`) — её наследник и сам регистрируется транспортом по умолчанию. Свой
транспорт (Indy, Synapse, mORMot, тестовый) — два метода, `Post` и `Download`; программа с ним не тянет
`System.Net.*`. Настройки прокси проверяются при создании транспорта. **Есть несовместимые изменения** — см.
«Миграция».

### Несовместимые изменения

- **Транспорт по умолчанию регистрирует `TgBot.Http`.** Ядро клиента (`TgBot.Core`) больше не подключает
  `TgBot.Http`: `TTgApi.Create(AToken/ASettings)` и `TTgBot.Create(AToken/ASettings)` получают транспорт из
  реестра (`TgCreateDefaultTransport`), а фабрику `TTgHttpTransport` регистрирует `TgBot.Http` в
  `initialization`. С фасадом `TgBot` (его подключают и `TgBot.Component`, `TgBot.Webhook`) ничего не меняется.
  Программы, подключающие `TgBot.Core`, `TgBot.Bot` или `TgBot.Types` **без** фасада `TgBot` и без
  `TgBot.Http`, теперь при создании клиента или бота по токену или настройкам получают `ETgError`
  «Транспорт по умолчанию не зарегистрирован: подключите TgBot.Http (или TgBot) или передайте свой транспорт»
  (`DefaultTransportMissing`). **Миграция:** добавьте `TgBot.Http` в `uses` или передайте свой транспорт
  (`TTgApi.Create(ATransport)`, `TTgBot.Create(ATransport)`).
- **Контракты перенесены в `TgBot.Intf`.** Интерфейсы транспорта, приёма обновлений, источников, диспетчера и
  хранилища состояния, записи `TTgProxySettings`, `TTgHttpSettings`, `TTgHttpResponse`, перечисления и типы
  обработчиков приёма (список — в «Новое») объявлены теперь в `TgBot.Intf`. В прежних модулях (`TgBot.Http`,
  `TgBot.Updates.Types`, `TgBot.Updates.Polling`, `TgBot.Updates.WebhookSource`, `TgBot.Updates.Dispatcher`,
  `TgBot.State`) и в фасаде `TgBot` остались псевдонимы тех же типов, GUID прежние — исходный код
  компилируется без изменений. Меняется имя модуля в RTTI: `TTypeData.IntfUnit`,
  `TRttiInterfaceType.DeclaringUnitName` и `TRttiType.QualifiedName` перенесённых типов теперь указывают на
  `TgBot.Intf` (например, `TgBot.Intf.ITgTransport` вместо `TgBot.Http.ITgTransport`) — это касается кода,
  который ищет типы по полному имени (`TRttiContext.FindType`) или сохраняет его.
- **В `TgBot` и `TgBot.Http` объявлен `record helper for TTgProxySettings`** (`TTgProxySettingsHelper`,
  метод `ToRtlSettings` — см. «Новое»). Если у вас есть свой помощник для `TTgProxySettings`, подключайте свой
  модуль **после** `TgBot`/`TgBot.Http`: действует один помощник на тип — последний в области видимости, иначе
  ваш помощник скрыт помощником библиотеки. С вашим помощником скрыт `ToRtlSettings` — используйте функцию
  `TgProxyToRtlSettings` (`TgBot.Http`).
- **`TTgApi.Settings.Proxy` теперь нормализован.** Транспорт проверяет и нормализует прокси при создании
  (`TTgProxySettings.Normalized`), и клиент возвращает уже нормализованные настройки: `Host := 'h:3128'`
  (`Port = 0`) читается как `Host = 'h'`, `Port = 3128`; префикс `http://` и завершающий `/` убраны, IPv6 —
  в скобках (`'::1'` → `'[::1]'`). Учтите это в коде, который сравнивает `Settings.Proxy` с исходной записью.
  То же — `Settings` у `TTgTransportBase` и `TTgHttpTransport`.
- **Прокси: `ETgError` при создании транспорта** (у компонента — при `Active := True`) для настроек, которые
  раньше давали сетевую ошибку или зависели от платформы:
  - `Scheme`, кроме `''` и `'http'` (`'https'`, `'socks5'`…), и схема в `Host`, кроме `http://`
    (`socks5://…`, `https://…`). `Scheme = 'https'` на Windows означал TLS до самого прокси (WinHTTP начинает
    с прокси рукопожатие TLS; обычный HTTP-прокси отвечал ошибкой 12029). На Linux и Android такая настройка
    раньше работала (схема игнорировалась), теперь — `ETgError` при создании бота. **Миграция:**
    `Scheme := ''` — для облачного Bot API (`https://`) этого достаточно;
  - порт не задан (`Port = 0` и нет `'хост:порт'` в `Host`) или вне 1–65535; порт в `Host` не совпадает с
    `Port`. **Миграция:** укажите порт явно;
  - путь, `логин:пароль@` или пробелы в `Host` (один завершающий `/`, `'http://proxy:3128/'`, допустим).
    **Миграция:** учётные данные — в `UserName`/`Password`.
- В пакет `TgBotRT` добавлены модули `TgBot.Intf` и `TgBot.Transport` — пакеты пересоберите.

### Новое

- **Модуль контрактов `TgBot.Intf`** — интерфейсы и записи настроек без реализаций. Зависит только от
  `TgBot.Base`, `TgBot.Json` и RTL (`System.SysUtils`, `System.Classes`, `System.JSON`): ни `System.Net.*`, ни
  Indy, ни модулей реализации (`TgBot.Http`, `TgBot.Core`, `TgBot.Updates.*`). Состав:
  - транспорт: `ITgTransport`, `ITgCancellableTransport`, `ITgHttpSettingsProvider`, `TTgProxySettings`
    (`Create`, `IsEnabled`, `Normalized`), `TTgHttpSettings`, `TTgHttpResponse`, константы `TgDefault…`
    транспорта (`TgDefaultApiUrl`, таймауты, повторы, лимиты);
  - приём обновлений: `ITgRawUpdate`, `ITgUpdateSink`, `ITgTimedUpdateSink`, `ITgWebhookReceiver`,
    `ITgUpdateSource`, `ITgPollTimer`, `TTgSourceState`, `TTgAckPolicy`, `TTgDelivery`, `TTgWebhookResult`,
    `TTgRawHandler`, `TTgRawErrorHandler`, `TTgConflictHandler`;
  - источники и диспетчер: `ITgLongPollSource`, `ITgWebhookSource`, `ITgUpdateDispatcher` (классы и фабрики
    `New` — в прежних модулях `TgBot.Updates.*`);
  - состояние диалогов: `ITgStateStorage`;
  - псевдонимы типов из сигнатур контрактов: `ITgCancellation`, `ITgCancellationSource`, `TTgInputFile`,
    `TTgParams`.

  Подключайте его, когда пишете свою реализацию (транспорт, хранилище состояния, источник или приёмник
  обновлений) или код, зависящий только от абстракций (README, «Модуль контрактов TgBot.Intf»).
- **База транспорта `TTgTransportBase`** (новый модуль `TgBot.Transport` без `System.Net.*`; реэкспорт в
  `TgBot`) реализует `ITgTransport`, `ITgCancellableTransport` и `ITgHttpSettingsProvider` целиком, кроме
  передачи байтов: URL метода, JSON-тело или части формы multipart (поля, файлы с диска, байты, потоки),
  таймаут ответа с учётом long polling, разбор ответа (`ETgApiError`, `ETgConflictError`), автоповтор 429,
  лимитёр, отмена (токен операции и глобальная `Cancel`/`ResetCancel`), `DownloadFile` с проверками пути и
  `LocalMode`, маскировка токена в текстах ошибок, адрес прокси в сетевых ошибках. Наследник реализует два
  метода:
  - `Post(const ARequest: TTgPostRequest): TTgHttpResponse` — один POST метода Bot API; любой HTTP-статус —
    не ошибка (тело разбирает база);
  - `Download(const ARequest: TTgDownloadRequest; ADest: TStream): Integer` — GET файла, результат — статус.

  Записи запроса: `TTgPostRequest` (`Method`, `Url`, `ResponseTimeoutMs`, `Cancel`, `ContentType`, `Body` или
  `Parts`, `IsMultipart`), `TTgDownloadRequest`, `TTgFormPart` (поле или файл: `Name`, `Value`, `Stream`,
  `FileName`, `ContentType`, `IsFile`). Исключения HTTP-клиента ловить не нужно — база превращает их в
  `ETgNetworkError` или `ETgCancelledError`. Наследнику доступны `Settings`, `MaskToken`, `WithProxyInfo`,
  виртуальный `DefaultResponseTimeoutMs`. `TTgHttpTransport` стал наследником `TTgTransportBase` (пул
  `THTTPClient`, прерывание идущего запроса при отмене); его публичный интерфейс не изменился. В
  `TgBot.Transport` перенесены `TTgRateLimiter` и `TgLongPollReserveSec` (в `TgBot.Http` — псевдонимы).
- **Реестр транспорта по умолчанию** (`TgBot.Transport`, обёртки в `TgBot`): тип `TTgTransportFactory`,
  `TgRegisterDefaultTransport`, `TgUnregisterDefaultTransport`, `TgDefaultTransportFactory`,
  `TgCreateDefaultTransport`. Реестр — стек под замком: действует последняя зарегистрированная фабрика,
  снятие текущей возвращает предыдущую, снятие не текущей её не меняет; фабрики сравниваются по ссылке
  (храните её в переменной до `TgUnregisterDefaultTransport`). `TgBot.Http` регистрирует фабрику
  `TTgHttpTransport` в `initialization` и снимает в `finalization` (в том числе при выгрузке пакета). Новый
  текст `TgBot.Consts`: `DefaultTransportMissing`.
- **Встроенный HTTP-транспорт — запасной.** `TgBot.Http` регистрирует свою фабрику служебной
  `TgRegisterFallbackTransport` (`TgBot.Transport`) в самый низ стека, поэтому любая регистрация пользователя
  (`TgRegisterDefaultTransport`) побеждает независимо от порядка `initialization` модулей — и до, и после
  `TgBot.Http`. Встроенная фабрика становится текущей, только если своих нет или все сняты. После
  `finalization` модуля `TgBot.Transport` реестр не вызывает нарушение доступа: `TgDefaultTransportFactory`
  возвращает `nil`, `TgCreateDefaultTransport` — `ETgError` `DefaultTransportMissing`, регистрация и снятие
  ничего не делают.
- **`TTgProxySettings.ToRtlSettings`** — помощник записи `TTgProxySettingsHelper` в `TgBot.Http` и `TgBot`
  (`TProxySettings` объявлен в `System.Net.URLClient`, поэтому не в `TgBot.Intf`): настройки прокси для
  `THTTPClient` (`Normalized`, схема всегда пустая). С одним `TgBot.Intf` — функция `TgProxyToRtlSettings`
  (`TgBot.Http`).
- **Прокси: проверка и нормализация настроек.** `TTgHttpTransport.Create` (а значит, `TTgApi`, `TTgBot` и
  компонент при `Active := True`) проверяет `Proxy` через новый `TTgProxySettings.Normalized` и сразу
  сообщает об ошибке настройки `ETgError` с понятным текстом вместо сетевой ошибки при первом запросе.
  Принимаются `'хост:порт'` в `Host` (при `Port = 0`), префикс `http://`, один завершающий `/`
  (`'http://proxy:3128/'`; путь после `/` — по-прежнему `ETgError`), IPv6 (`'[::1]:3128'` или `'::1'` с
  `Port`), пробелы по краям. В `THTTPClient` схема всегда передаётся пустой (`ToRtlSettings`) — единственный
  вариант HTTP-прокси, одинаковый на всех платформах. Пароль и имя пользователя в тексты ошибок не попадают.
  Новые тексты `TgBot.Consts`: `ProxyScheme`, `ProxyBadHost`, `ProxyPort`, `ProxyPortConflict`. Проверку
  выполняет конструктор базы `TTgTransportBase`, то есть любой транспорт-наследник; в `Post`/`Download`
  наследника `Settings.Proxy` уже нормализован.
- **Прокси: ошибка сети не показывала, что запрос шёл через прокси.** Неверный адрес или порт прокси, отказ
  прокси в туннеле `CONNECT` и ответ прокси с ошибкой выглядели как недоступность Telegram. Теперь текст
  `ETgNetworkError` (нет соединения, некорректный ответ, ошибка скачивания) при заданном `Proxy` заканчивается
  адресом прокси: «…; запрос шёл через прокси 192.168.1.1:3128» (без имени пользователя и пароля). Новый текст
  `TTgText.ViaProxy`. Само применение прокси не менялось: проверено, что `Proxy` (в том числе заданный через
  `with LSettings.Proxy do`) действует на все запросы — методы Bot API, long polling, скачивание файлов.
- **`TgProxyToRtlSettings`** (`TgBot.Http`) — настройки прокси для `THTTPClient` (`Normalized`, схема всегда
  пустая) для своего транспорта на `THTTPClient`; `ToRtlSettings` вызывает её.
- **Демо `Demos\05_CustomTransport`** — свой транспорт `TLoggingTransport` (наследник `TTgTransportBase` на
  `THTTPClient` без `TgBot.Http`) с журналом запросов: метод, HTTP-статус, время. Регистрируется транспортом по
  умолчанию; `getMe`, при заданном `TGBOT_CHAT_ID` — `sendMessage`, `sendDocument` (multipart), `getFile` и
  скачивание. Добавлено в `Demos\Demos.groupproj`.
- **`Tests\NoNet\check.ps1`** — проверка, что клиент со своим транспортом собирается без HTTP-стека RTL:
  собирает `Tests\NoNet\TgBotNoNetCheck.dpr` (только модули протокола и `System.*`) с картой `-GD`, ищет в
  `.map` `System.Net.HttpClient`, `System.Net.URLClient`, `System.Net.Mime` и `TgBot.Http`, затем запускает
  программу (фабрики по умолчанию нет, `GetMe` через свой транспорт). Код выхода: 0 — PASS, 1 — FAIL, 2 —
  компилятор не найден. Компилятор — `-Compiler`, `-BdsRoot`, переменная `BDS` или реестр (`-BdsVersion`);
  `-Platform Win64|Win32`.

### Улучшено

- **Ядро и бот зависят от контрактов, а не от HTTP-реализации.** `TgBot.Core`, `TgBot.Bot`, `TgBot.Bot.Core`,
  `TgBot.Updates.Types`, `TgBot.Updates.Polling` и `TgBot.Updates.WebhookSource` подключают `TgBot.Intf`
  вместо `TgBot.Http` (ядро клиента — `TgBot.Transport`); `TgBot.Http` в `uses` остался только у фасада
  `TgBot`. Программа со своим транспортом без фасада не содержит `TgBot.Http` и `System.Net.HttpClient`/
  `URLClient`/`Mime` (проверяет `Tests\NoNet\check.ps1`), программа с одними источниками обновлений
  (`TgBot.Updates.Polling`, `TgBot.Updates.WebhookSource`) — тоже.
- Документировано, почему связь родительского и дочернего источника отмены не использует `[weak]`: RTL обнуляет
  слабые ссылки после деструктора (`TObject.CleanupInstance`), а чтение `[weak]` не захватывает объект
  атомарно; окно гонки закрывает монитор связи и `Detach` в начале деструктора дочернего источника.
- Проверка правил владения (объекты со счётчиком ссылок — только через интерфейсы) расширена на `Demos` и
  `Tests`. Демо VclBot: вместо пары класс + интерфейс (`FGuard`/`FGuardRef` и приведение `as TObject`) —
  интерфейс `IBotLogTarget` (`Log`, `Detach`), колбэки отправки захватывают только его; поведение демо прежнее.
  Тесты: отмена через `ITgCancellationSource` вместо приведения к классу, сравнение объектов — `SameIntf`;
  оставшиеся ссылки на классы (проверка `RefCount` и внутреннего состояния) помечены как намеренные.
- Источники обновлений (long polling, webhook): замыкания вызова `OnError`/`OnFault`/`OnConflict` не
  захватывают ядро неявно (`Self`) — обработчик копируется в локальную переменную; вызов по-прежнему синхронный.

### Исправлено

- Документация прокси (`TTgProxySettings`, README, раздел 9): нужен HTTP-прокси с поддержкой `CONNECT`
  (облачный Bot API — `https://`); `Scheme` `''` и `'http'` равнозначны; SOCKS на Windows не поддерживается;
  пустой `Host` — системные настройки; адреса `127.0.0.1`/`localhost` WinHTTP запрашивает мимо прокси.
  Прежнее описание «HTTP(S)-прокси, схема 'http' или 'https'» вводило в заблуждение.
- Тест завершения процесса больше не зависит от консоли родителя (`DETACHED_PROCESS`, маркер старта); отказ
  запуска дочернего процесса окружением — `[SKIP]`, а не ложный FAIL.

### Тесты

- Всего 106 тестов (2411 проверок; в 0.3.0 — 96 и 2049).
- Стресс-тест гонки отмены родителя и освобождения дочернего источника (`TestCancelLinkRace`; полный вариант —
  `TG_ONLY=STRESS`).
- Прокси (`Tests\TgBotTests.Proxy.pas`): локальный HTTP-прокси и фейковый Bot API на Indy. Код с
  `with LSettings.Proxy do`; getMe, sendMessage, getFile, DownloadFile и long polling через прокси (`Scheme`
  `''` и `'http'`); HTTPS — `CONNECT api.telegram.org:443`; адрес прокси в тексте ошибки; компонент
  `TTelegramBot.Proxy`. Фейковый Bot API адресуется именем `tgbot-api.invalid` — WinHTTP обходит прокси для
  loopback-адресов.
- Нормализация и проверка прокси (`TestProxyNormalize`, `TestProxyTransportSettings`): `'хост:порт'`,
  `http://`, завершающий `/` (путь — ошибка), IPv6, обязательный порт, противоречие портов, SOCKS/HTTPS в
  `Host` и `Scheme`, учётные данные в `Host` — `ETgError` без пароля в тексте; пустая схема в RTL; ошибки из
  конструктора транспорта и компонента.
- Реестр транспорта по умолчанию (`TestDefaultTransportRegistry`): `TTgHttpTransport` при `uses TgBot`, без
  фабрики — `ETgError` `DefaultTransportMissing`, своя фабрика, стек регистраций, снятие не текущей фабрики не
  меняет текущую; запасная фабрика (`TgRegisterFallbackTransport`): своя, зарегистрированная до запасной
  (порядок `initialization`), остаётся текущей, после её снятия — запасная.
- Свой транспорт (`TestCustomTransportBase`, 108 проверок): наследник `TTgTransportBase` без сети через
  `TTgApi.Create(ATransport)` — URL метода, JSON-тело, части формы (очищенное имя файла, `ContentType`),
  позиция потоков 0 на каждой попытке после 429, маскировка токена (в том числе URL-кодированного), обёртка
  исключений `Post`, `ETgApiError`/`ETgConflictError`, ответ не JSON, пути скачивания (`..`, UNC) и
  `LocalMode`, статус скачивания, отмена во время `Post`/`Download`.
- `Tests\NoNet\check.ps1` — сборка и запуск клиента со своим транспортом без `System.Net.*` (см. «Новое»).
- Дистрибутив (`Tools\Dist\MakeDist.ps1`) включает `Tests\TgBotTests.Proxy.pas` и `Tests\NoNet\` (обязательные
  файлы): тесты и `check.ps1` собираются и запускаются из архива исходников.

### Миграция

| Было | Стало |
|---|---|
| `uses TgBot.Core` (`TgBot.Bot`, `TgBot.Types`) без фасада `TgBot`, клиент или бот по токену | добавьте `TgBot.Http` в `uses` (иначе `ETgError` «транспорт по умолчанию не зарегистрирован») или передайте свой транспорт в `TTgApi.Create(ATransport)` / `TTgBot.Create(ATransport)` |
| `ITgTransport`, `TTgHttpSettings`, `TTgProxySettings` и др. из `TgBot.Http` (`ITgUpdateSource` и др. — из `TgBot.Updates.*`, `ITgStateStorage` — из `TgBot.State`) | работает без изменений (псевдонимы, те же GUID); для своих реализаций рекомендуется `uses TgBot.Intf` |
| поиск типов по полному имени в RTTI (`TgBot.Http.ITgTransport`) | `TgBot.Intf.ITgTransport` |
| свой транспорт, реализующий `ITgTransport`/`ITgCancellableTransport` целиком | наследуйте `TTgTransportBase` (`TgBot.Transport`) и реализуйте только `Post` и `Download`; старая реализация интерфейса продолжает работать |
| `Proxy.Scheme := 'socks5'` / `'https'`, `Host := 'socks5://…'` | `ETgError`; используйте HTTP-прокси с `CONNECT` (`Scheme := ''`), для SOCKS — локальный HTTP-порт VPN-клиента или конвертер SOCKS → HTTP |
| `Proxy.Host := 'user:pass@host'` (или с путём) | `ETgError`; `Host := 'host'`, учётные данные — в `UserName`/`Password` |
| `Proxy.Port := 0` без `'хост:порт'` в `Host` | `ETgError`; укажите `Port` (1–65535) или `Host := 'хост:порт'` |
| свой `record helper for TTgProxySettings` | подключайте свой модуль после `TgBot`/`TgBot.Http` (действует последний помощник в области видимости); `ToRtlSettings` тогда скрыт — `TgProxyToRtlSettings(AProxy)` (`TgBot.Http`) |
| сравнение `TTgApi.Settings.Proxy` с исходными настройками | `Proxy` нормализован (`Host 'h:3128'` → `Host 'h'`, `Port 3128`); сравнивайте с `AProxy.Normalized` |

## 0.3.0 — 2026-10-16

Выпуск включает неопубликованные 0.2.1 и 0.2.2. Тексты библиотеки собраны в модуле `TgBot.Consts` и стали
переводимыми; объекты со счётчиком ссылок используются только через интерфейсы; источники обновлений и
диспетчер получили интерфейсы, а `TTgBot` — свойства для их настройки вместо доступа к самим объектам.
**Есть несовместимые изменения** — см. «Миграция».

### Несовместимые изменения

- **Удалены свойства `TTgBot.Source`, `TTgBot.WebhookSource` и `TTgBot.Dispatcher`.** Они отдавали
  подсчитываемые классы (`TTgLongPollSource`, `TTgWebhookSource`, `TTgUpdateDispatcher`), которые нельзя было
  ни хранить, ни освобождать. Бот хранит источники и диспетчер только как интерфейсы; их настройки — свойства
  самого бота (`PollLimit`, `PollJitterPercent`, `PollConflictNotifyIntervalMs`, `WebhookMaxBodySize`,
  `WebhookPostTimeoutMs`, `WebhookDedupWindow`, `WebhookRegisterOnStart`), приёмник webhook —
  `WebhookReceiver`. Замены — в таблице «Миграция».
- **Класс `TTgContext`** (модуль `TgBot.Context`) скрыт в `implementation` — он был служебным; используйте
  `ITgContext`.
- **Имена ресурсов перенесены в `TgBot.Consts`.** Все `resourcestring` библиотеки теперь в этом модуле, имена
  ресурсов изменились. Существующие внешние переводы (ITE, `.drc`) нужно обновить.
- Технические исключения (`EArgumentNilException`, `EArgumentOutOfRangeException`) содержат полную фразу на
  выбранном языке (например, «Параметр AHandler не может быть nil») вместо одного имени параметра или
  `AMaxThreads = %d`.
- Исключение при `nil`-кнопке в клавиатурах (`TTgKeyboard`) — текст библиотеки на её языке вместо RTL
  `SArgumentNil`.
- Строки webhook-сервера (`TgBot.Webhook`) теперь в пакете `TgBotRT`; `TgBotIndyRT` их импортирует. Пакеты
  пересоберите.

### Новое

- **Модуль `TgBot.Consts`** — все пользовательские тексты библиотеки (61 пара RU/EN, `resourcestring`) в одном
  месте по образцу `System.RTLConsts`. Каждый текст — пара `SRu…`/`SEn…`; секции по подсистемам (ядро, JSON,
  DTO, обновления, маршрутизатор, `TTgBot`, компонент, webhook-сервер). Модуль служебный: в прикладном коде
  его не подключают.
- **Переводимые исключения.** Тексты ошибок `TgBot.Json` и `TgBot.Dto` стали переводимыми (раньше — обычные
  константы); переводимы тексты всех исключений библиотеки, включая технические (параметр `nil`, значение вне
  диапазона). Единая служебная функция выбора языка `TgLangText` / `TgLangTextFmt` (`TgBot.Base`) вместо
  локальных таблиц и функций в модулях.
- **`ITgCancellationSource`** (реэкспорт в `TgBot`) — источник отмены как интерфейс: `ITgCancellation` плюс
  `Cancel`. **`TTgCancellationSource.New`** / `New(AParent)` — рекомендуемый способ создать источник отмены
  (при `AParent` — связанный). Результат храните как `ITgCancellationSource` (README, разделы 5 «Отмена» и 14
  «Правила владения»).
- **`ITgLongPollSource`, `ITgWebhookSource`, `ITgUpdateDispatcher`** (реэкспорт в `TgBot.Updates` и `TgBot`) —
  интерфейсы нижнего слоя со всеми настройками и событиями соответствующих классов. Фабрики
  `TTgLongPollSource.New(ATransport, AParentCancel)`, `TTgWebhookSource.New(ATransport, AParentCancel)`,
  `TTgUpdateDispatcher.New(AHandler)` возвращают интерфейс. `ITgWebhookSource.Receiver` — тонкий приёмник,
  реализующий только `ITgWebhookReceiver` (через `Supports` из него не получить `ITgWebhookSource`, то есть
  нельзя остановить источник или поменять настройки). `TryPost` диспетчера — по-прежнему через
  `Supports(…, ITgTimedUpdateSink)` (`ITgTimedUpdateSink` теперь реэкспортируется в `TgBot`).
- **Настройки `TTgBot`** (применяются при `Start`):
  - `PollLimit` — `limit` getUpdates (по умолчанию `TgDefaultPollLimit`, 100);
  - `PollJitterPercent` — разброс пауз между повторами после ошибок, ±% (`TgDefaultBackoffJitterPercent`, 20);
  - `PollConflictNotifyIntervalMs` — минимальный интервал повторных `OnConflict` (`TgDefaultConflictNotifyMs`,
    60000);
  - `WebhookMaxBodySize` — наибольший размер тела (`TgDefaultWebhookMaxBodySize`, 1 МБ);
  - `WebhookPostTimeoutMs` — сколько `HandleWebhook` ждёт места в полной очереди
    (`TgDefaultWebhookPostTimeoutMs`, 250);
  - `WebhookDedupWindow` — сколько последних `update_id` помнить для отбрасывания повторов
    (`TgDefaultWebhookDedupWindow`, 1000; 0 — без дедупликации);
  - `WebhookRegisterOnStart` (по умолчанию `True`) — `False`: webhook зарегистрирован вне бота, `setWebhook`
    и `OnWebhookRegistered` нет; `WebhookUrl`, `WebhookMaxConnections`, `WebhookDropPendingUpdates`,
    `WebhookIpAddress`, `WebhookCertificate` не используются, `AllowedUpdates` на сервер не передаётся.
    Пустой `WebhookSecretToken` в этом режиме не заменяется случайным (его некому сообщить серверу) —
    заголовок секрета не проверяется; это небезопасно, при `Start` выдаётся предупреждение (см. ниже).
    Задайте тот же секрет, что передан в `setWebhook`.
- **Предупреждение о webhook без секрета.** `Mode = Webhook`, `WebhookRegisterOnStart = False` и пустой
  `WebhookSecretToken` (у компонента — `Webhook.RegisterOnStart` и `Webhook.SecretToken`): при `Start`
  вызывается `OnError(ETgError, nil)` с текстом `SRuBotWebhookNoSecret`/`SEnBotWebhookNoSecret` — обновление
  может прислать любой, кто знает URL. Запуск продолжается.
- **`TTgBot.WebhookReceiver`** (`ITgWebhookReceiver`, только чтение) — приёмник тела webhook для своего
  HTTP-сервера; `Accept` равносилен `HandleWebhook`. Один объект на всю жизнь бота; реализует только
  `ITgWebhookReceiver`. Ссылка может пережить `Free` бота: после `Stop` и `Free` `Accept` отвечает
  `Unavailable`; до отпускания она удерживает webhook-источник и через его транспорт — закрытое ядро бота с
  клиентом (`StateStorage` освобождается при `Free` бота). Компонент `TTelegramBot` хранит приёмник сам и
  отпускает его до `Free` бота; `TTgWebhookServer` с приёмником не работает — он вызывает
  `TTelegramBot.HandleWebhook`, а компонент передаёт тело приёмнику.
- **Компонент `TTelegramBot`:** новая группа `Polling` (`TTgPollingOptions`: `Limit`, `JitterPercent`,
  `ConflictNotifyIntervalMs`; `PollingTimeout` остаётся на верхнем уровне для совместимости DFM) и новые
  `Webhook.MaxBodySize`, `Webhook.PostTimeoutMs`, `Webhook.DedupWindow`, `Webhook.RegisterOnStart`. Значения
  по умолчанию в DFM не пишутся; `Assign` копирует их; смена у работающего бота — `ETgError`. `TgBot`
  реэкспортирует `TgDefaultConflictNotifyMs` и `TgDefaultBackoffJitterPercent`.
- **`TgDefaultBotFreeStartJobWaitMs`** (500 мс; `TgBot.Bot`, реэкспорт в `TgBot`) — сколько `Free` бота ждёт
  фоновую подготовку запуска перед её отменой.

### Улучшено

- **Правила владения.** Подсчитываемые объекты (`TInterfacedObject`) используются только через интерфейсы;
  убраны пары «класс + `IInterface`» и приведения интерфейсов к классам:
  - `TTgBot` хранит long polling-источник, webhook-источник и диспетчер как `ITgLongPollSource`,
    `ITgWebhookSource`, `ITgUpdateDispatcher` и создаёт их через `New`;
  - фоновая подготовка запуска бота (`getMe`, `setMyCommands`) — служебный `ITgStartJob`; замыкание пула не
    захватывает `Self` ядра, задача не держит ядро (циклов ссылок нет);
  - источники отмены — одно поле `ITgCancellationSource` во всех модулях (клиент, HTTP-транспорт, long
    polling, webhook-источник, диспетчер, ядро бота);
  - контекст и маршрутизатор — служебные `ITgApiOwner` и `ITgRoutableContext`; класс `TTgContext` скрыт в
    `implementation`;
  - `TTgBot` больше не кэширует клиент (поле `FApi`): `TTgBot.Api` читает его из ядра;
  - DTO — держатель JSON через служебный `ITgJsonHolder`;
  - связь компонента `TTelegramBot` и webhook-сервера с замыканиями и очередью главного потока — служебный
    `ITgOwnerLink`;
  - настройки HTTP-транспорта ядро клиента получает через служебный `ITgHttpSettingsProvider` (`Supports`)
    вместо приведения к `TTgHttpTransport`.
- Подписки на отмену (`ITgCancellation.Register`) без сырых указателей: источник хранит колбэки с
  идентификаторами, подписка — идентификатор и интерфейсную ссылку на источник.
- **`Free` бота не замирает на висящем `getMe`.** `Free` (и `Free` формы с `TTelegramBot`) ждёт фоновую
  подготовку запуска не дольше 0,5 с (`TgDefaultBotFreeStartJobWaitMs`) и отменяет её — раньше ждал до 10 с
  (таймаут `Stop` по умолчанию). Меню команд при `Free` сразу после `Start` может не уйти — оно отправится
  при следующем `Start`. Явный `Stop(AWaitMs)` и `Active := False` ждут подготовку как раньше.
- **`Free` бота освобождает `StateStorage` сразу,** даже если внутреннее ядро удерживается дольше (обработчик,
  сохранённый `ITgContext`, `WebhookReceiver`): выполняющиеся обработчики и контексты держат свой снимок.
  `Free` также снимает события источников, чтобы удержанный webhook-источник не держал их замыкания.
- `TTgBot`: подтверждение обработки (`OnProcessed` диспетчера) назначается при `Start` источнику текущего
  запуска — long polling сдвигает offset как раньше, у webhook подтверждение — ответ 200.
- Компонент: при `Webhook.RegisterOnStart = False` файл `Webhook.Certificate` не проверяется и не
  передаётся (сертификат нужен только `setWebhook`).
- XML-doc: разумный предел `WebhookDedupWindow` / `Webhook.DedupWindow` — до 10 000 (большие значения
  замедляют каждый запрос).
- API, которые по-прежнему работают без изменений: `TgText`/`TgTextFmt`, `TgUpdatesText`, `TgRouterText`,
  перечисления `TTgText`, `TTgUpdatesText`, `TTgRouterText`, `TgSetLanguage`/`TgGetLanguage`;
  `TTgCancellationSource.Create` сохранён (но рекомендуется `New`); конструкторы `Create` источников и
  диспетчера сохранены (рекомендуется `New`).
- `TgBot.Base` теперь в `uses` секции `interface` модулей `TgBot.Component` и `TgBot.Webhook` (для
  прикладного кода незаметно).
- Документация: пример отмены в README (раздел 5) больше не захватывает форму в фоновой задаче; уточнено,
  что колбэк `Register` может быть вызван и после освобождения подписки и не должен ждать освобождения
  своего источника или его родителя (XML-doc `ITgCancellation.Register`, README, раздел 14).

### Исправлено

- `TTelegramBot`: события старого запуска — отложенный `OnWebhookRegistered`, решение об освобождении бота
  при отказе, `Stop`, отложенный из обработчика, — могли сработать для нового запуска, если новый `TTgBot`
  получил тот же адрес в памяти (ABA). Теперь они сверяются по номеру запуска, а не по указателю.
- Сообщение «Значение не является JSON-объектом (поле %s)» (`SetValue`/`AppendRow` у DTO, построенного не
  над JSON-объектом, `DtoNotObject`) показывало имя класса вместо имени поля.
- DTO: ошибка «объект не поддерживается» (и «не DTO над JSON») для интерфейса, реализованного не на Delphi,
  выбрасывалась как `EIntfCastError` при подстановке имени класса; теперь — `ETgError` с именем `?`.
- Тесты: проверки отсутствия `OnError` (и `OnStop`, `OnCommand`) в тестах компонента и webhook-сервера
  сравнивали запись журнала целиком и потому не могли сработать; теперь сравнивается префикс
  (`TTextLog.HasPrefix`). Исправленные проверки проходят — реальных вызовов `OnError` в этих сценариях нет.

### Тесты

- Тест полноты текстов (`TestTextsComplete`): у каждого текста оба языка заданы и различаются, кириллица
  только в русском, подстановки формата совпадают.
- Тесты времени жизни: `Free` бота во время висящего `getMe` (отменяемый и неотменяемый транспорт),
  перезапуск с поздними ответами старых задач, обработчик `/cmd@бот` при `Stop` и `Free`, 200 циклов
  `Start`/`Stop`/`Free`, поздние события старого запуска компонента (ABA), контекст после `Free` бота,
  источники отмены (в том числе 4 потока × 10000 подписок).
- `Free` бота и `TTelegramBot` при висящем `getMe` — не дольше 1,5 с; явный `Stop(300)` при висящем `getMe`
  ждёт подготовку ≈300 мс.
- Настройки бота: `PollLimit` (`limit` в getUpdates), `PollJitterPercent`, `PollConflictNotifyIntervalMs`,
  `WebhookRegisterOnStart = False` (без `setWebhook` и `OnWebhookRegistered`), `WebhookMaxBodySize`,
  `WebhookDedupWindow = 0`, `WebhookPostTimeoutMs`; `WebhookReceiver` после `Stop`/`Free` и без утечек;
  предупреждение о webhook без секрета.
- `WebhookReceiver` и `ITgWebhookSource.Receiver`: `Supports(…, ITgWebhookSource) = False`; после `Free` бота
  при живом приёмнике пользовательский `StateStorage` освобождён, `Accept` → `Unavailable`; ядро освобождается
  после отпускания приёмника.
- Компонент: `Webhook.RegisterOnStart = False` с несуществующим файлом `Webhook.Certificate` запускается без
  ошибки и без `setWebhook`.
- Компонент: значения по умолчанию групп `Polling` и `Webhook`, `Assign`, DFM (значение по умолчанию не
  пишется, иное сохраняется и загружается), передача в `TTgBot`, `ETgError` при смене у работающего бота.
- Тесты нижнего слоя держат источники и диспетчер только как интерфейсы, созданные через `New`.
- Сборка тестов с `-DTGBOT_TESTHOOKS` включает счётчики живых ядер и задач подготовки и доступ к источнику
  бота (служебные хуки `TgBot.Bot.Core` и `TgBot.Bot`); без символа эти проверки пропускаются. Всего 96 тестов
  (2049 проверок).

### Миграция

Удалённые свойства `TTgBot` и прочие замены:

| Было | Стало |
|---|---|
| `Bot.Source.Limit` | `Bot.PollLimit` (компонент: `Polling.Limit`) |
| `Bot.Source.JitterPercent` | `Bot.PollJitterPercent` (компонент: `Polling.JitterPercent`) |
| `Bot.Source.ConflictNotifyIntervalMs` | `Bot.PollConflictNotifyIntervalMs` (компонент: `Polling.ConflictNotifyIntervalMs`) |
| `Bot.Source.TimeoutSec`, `AllowedUpdates`, `DropPendingUpdates`, `AutoDeleteWebhook`, `AckPolicy`, `DrainTimeoutMs` | `Bot.PollTimeout`, `Bot.AllowedUpdates`, `Bot.DropPendingUpdates`, `Bot.AutoDeleteWebhook`, `Bot.AckPolicy`, `Bot.DrainTimeoutMs` (их значения и раньше переписывали настройки источника при `Start`) |
| `Bot.Source.OnConflict` | `Bot.OnConflict` |
| `Bot.Source.State`, `Bot.WebhookSource.State` | `Bot.SourceState` (источник текущего режима) |
| `Bot.Source.OnError`, `Bot.Source.OnFault`, `Bot.WebhookSource.OnError`, `Bot.WebhookSource.OnFault` | `Bot.OnError` (ошибка приёма — `AContext = nil`), `Bot.OnFault` |
| `Bot.Source.Offset`, `ConfirmedOffset`, `Timer` | у `TTgBot` нет; нужен такой контроль — свой источник `TTgLongPollSource.New` (`ITgLongPollSource`) |
| `Bot.Source.WaitForThread`, `Bot.WebhookSource.WaitForThread` | у `TTgBot` нет; состояние — `Bot.State`, остановка с ожиданием — `Bot.Stop(AWaitMs)` |
| `Bot.WebhookSource.Url`, `SecretToken`, `MaxConnections`, `DropPendingUpdates`, `IpAddress`, `Certificate`, `DeleteOnStop`, `AllowedUpdates` | `Bot.WebhookUrl`, `Bot.WebhookSecretToken`, `Bot.WebhookMaxConnections`, `Bot.WebhookDropPendingUpdates`, `Bot.WebhookIpAddress`, `Bot.WebhookCertificate`, `Bot.DeleteWebhookOnStop`, `Bot.AllowedUpdates` (их значения и раньше переписывали настройки источника при `Start`) |
| `Bot.WebhookSource.MaxBodySize` | `Bot.WebhookMaxBodySize` (компонент: `Webhook.MaxBodySize`) |
| `Bot.WebhookSource.PostTimeoutMs` | `Bot.WebhookPostTimeoutMs` (компонент: `Webhook.PostTimeoutMs`) |
| `Bot.WebhookSource.DedupWindow` | `Bot.WebhookDedupWindow` (компонент: `Webhook.DedupWindow`) |
| `Bot.WebhookSource.RegisterOnStart` | `Bot.WebhookRegisterOnStart` (компонент: `Webhook.RegisterOnStart`) |
| `Bot.WebhookSource` как приёмник (`Accept`) | `Bot.WebhookReceiver.Accept(…)` или `Bot.HandleWebhook(…)` |
| `Bot.Dispatcher.MaxParallel`, `QueueCapacity`, `Delivery` | `Bot.MaxParallel`, `Bot.QueueCapacity`, `Bot.Delivery` (их значения и раньше переписывали настройки диспетчера при `Start`) |
| `Bot.Dispatcher.WaitIdle` | у `TTgBot` нет; дождаться обработчиков — `Bot.Stop(AWaitMs)` |
| `Bot.Dispatcher.Active` | у `TTgBot` нет; `Bot.State` (`Bot.Active`) |
| `Bot.Dispatcher.Cancel` | у `TTgBot` нет; токен отмены обработчика — `ACtx.Cancel` |
| `Bot.Dispatcher.OnError` | у `TTgBot` нет; `Bot.OnError` (исключение обработчика — с `AContext`) |
| `Bot.Dispatcher.OnProcessed` | у `TTgBot` нет; подтверждение — `Bot.AckPolicy` |
| `LSource: TTgCancellationSource := TTgCancellationSource.Create` | `LSource: ITgCancellationSource := TTgCancellationSource.New` (связанный — `New(AParent)`) |
| `TTgContext` | `ITgContext` |
| `TTgLongPollSource.Create`, `TTgWebhookSource.Create`, `TTgUpdateDispatcher.Create` в переменную класса | `.New(…)` в переменную `ITgLongPollSource` / `ITgWebhookSource` / `ITgUpdateDispatcher`; `Free` не вызывать |
| Внешний перевод (ITE, `.drc`) со старыми именами ресурсов | перевести строки `SRu…`/`SEn…` модуля `TgBot.Consts` заново |
| Пакеты 0.2.0 | пересобрать `TgBotRT`, `TgBotIndyRT`, `TgBotDT` |

## 0.2.0 — 2026-10-15

Внутренняя реструктуризация исходников. Публичный API не изменился: по-прежнему достаточно `uses TgBot`
(плюс `TgBot.Component` / `TgBot.Webhook` для компонентов).

### Изменения

- **`TgBot.pas` разбит на модули** `TgBot.Types` (сгенерированный слой и `TTgApi`), `TgBot.Keyboards`
  (`TTgKeyboard`, `TgRow`), `TgBot.Context` (`ITgContext`), `TgBot.Router` (маршрутизатор), `TgBot.Bot.Core`
  (внутреннее ядро бота) и `TgBot.Bot` (`TTgBot`). `TgBot` стал фасадом: только реэкспорт псевдонимами
  (псевдонимы сгенерированных типов — `Source\Generated\Gen.Aliases.inc`, создаёт `TgBotGen --gen`).
- **`TgBot.Updates.pas` разбит на модули** `TgBot.Updates.Types` (общие типы), `TgBot.Updates.Dispatcher`
  (`TTgUpdateDispatcher`), `TgBot.Updates.Polling` (`TTgLongPollSource`) и `TgBot.Updates.WebhookSource`
  (`TTgWebhookSource`). `TgBot.Updates` стал фасадом.
- **Ядра за интерфейсами.** У бота, диспетчера и источников обновлений одно поле ядра через служебный
  интерфейс (`ITgBotCore`, `ITgDispatchCore`, `ITgPollCore`, `ITgWebhookCore`) вместо пары «объект + ссылка
  на интерфейс» и приведений типов.
- Удалён неиспользуемый код (подготовка к разбиению).
- Удалён устаревший ручной клиент `Source\TgBot.Api.pas` (фаза 1; не входил в пакеты и дистрибутив).

### Совместимость

- Исходный код, использующий `uses TgBot`, менять не нужно.
- Изменились `UnitName` и полные имена типов в RTTI: `TgBot.TTgBot` → `TgBot.Bot.TTgBot`, `TgBot.TTgApi` →
  `TgBot.Types.TTgApi`, `TgBot.TTgBotState` → `TgBot.Bot.Core.TTgBotState`, `TgBot.ITgContext` →
  `TgBot.Context.ITgContext`, `TgBot.TTgKeyboard` → `TgBot.Keyboards.TTgKeyboard`,
  `TgBot.Updates.TTgLongPollSource` → `TgBot.Updates.Polling.TTgLongPollSource` и др. Важно, только если
  код сравнивает или сохраняет эти имена.
- Изменились имена ресурсов `resourcestring` перенесённых текстов (теперь с префиксом нового модуля).
  Важно только для внешних переводов (ITE, `.drc`) — их нужно обновить.
- Пакеты пересоберите: в `TgBotRT` добавлены новые модули (`.dcp`/`.bpl` 0.1.0 несовместимы).

## 0.1.0 — 2026-10-09

Первый публичный выпуск.

### Возможности

- **Полный Telegram Bot API 10.3.** Все типы и методы сгенерированы по официальной спецификации
  генератором `Tools\TgBotGen` (спецификация и модель лежат в `Tools\TgBotGen\Spec`).
- **`TTgApi`** — клиент Bot API: каждый метод в трёх вариантах (обычный, `Try*`, `*Async`), необязательные
  параметры (Options), отправка файлов и альбомов, скачивание файлов, обработка 429 (`retry_after`), отмена.
- **`TTgBot`** — бот в коде: long polling или webhook, маршрутизатор команд и кнопок, клавиатуры, меню
  команд, состояние диалогов, многопоточная обработка (Delivery Main/Worker, MaxParallel), жизненный цикл
  Start/Stop и Run/RequestStop, экранирование `TgHtmlEscape` / `TgMarkdownV2Escape`.
- **`TTelegramBot`** — компонент для формы (Object Inspector, коллекция команд, события `of object`).
- **`TTgWebhookServer`** — встроенный HTTP-сервер для webhook на Indy (пакет `TgBotIndyRT`); для своего
  HTTP-сервера — `HandleWebhook`.
- **Пакеты:** `TgBotRT` (runtime), `TgBotIndyRT` (runtime, webhook), `TgBotDT` (design-time, вкладка
  Telegram в палитре). Имена `.bpl` с суффиксом версии Delphi (`{$LIBSUFFIX AUTO}`).
- **Установщик** `Install\Install.cmd` (`Install.ps1`): сборка пакетов, регистрация в IDE, пути
  Library/Browsing; удаление — `Install\Uninstall.cmd`.
- **Демо:** `01_Smoke` (консоль), `02_EchoBot` (эхо-бот на `TTgBot`), `03_VclBot` (VCL-форма с
  `TTelegramBot`), `04_WebhookBot` (webhook на `TTgWebhookServer`).
- **Тесты:** `Tests\TgBotTests.dpr` — 77 тестов, работают без сети и без токена.

### Требования

- Delphi 10.4 Sydney и новее (проверено на 10.4 и 12).
- Платформы: Win32, Win64, Linux64, Android (32 и 64 бит).
- Ядро использует только RTL (`System.Net.HttpClient`, `System.JSON`, `System.Threading`); Indy нужен только
  для `TTgWebhookServer`.
- Linux64: `libcurl` и корневые сертификаты на целевой машине.

### Известные ограничения

- Linux64 проверен только компиляцией (запуск на Linux не проверялся).
- Android заявлен в пакете `TgBotRT`, на устройстве не проверялся.
- Webhook с настоящим сервером Telegram не проверялся (проверено локально, тестами и демо).
- iOS не поддерживается.
- Пакет `TgBotDT` — только Win32 (32-битная IDE).
