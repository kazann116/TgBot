# История изменений TgBot

## Не выпущено

### Исправлено

- **Прокси: ошибка сети не показывала, что запрос шёл через прокси.** Неверный адрес или порт прокси, отказ
  прокси в туннеле `CONNECT` и ответ прокси с ошибкой выглядели как недоступность Telegram. Теперь текст
  `ETgNetworkError` (нет соединения, некорректный ответ, ошибка скачивания) при заданном `Proxy` заканчивается
  адресом прокси: «…; запрос шёл через прокси 192.168.1.1:3128» (без имени пользователя и пароля). Новый текст
  `TTgText.ViaProxy`. Само применение прокси не менялось: проверено, что `Proxy` (в том числе заданный через
  `with LSettings.Proxy do`) действует на все запросы — методы Bot API, long polling, скачивание файлов.
- Документация прокси (`TTgProxySettings`, README, раздел 9): нужен HTTP-прокси с поддержкой `CONNECT`
  (облачный Bot API — `https://`); `Scheme` `''` и `'http'` равнозначны; SOCKS на Windows не поддерживается;
  пустой `Host` — системные настройки; адреса `127.0.0.1`/`localhost` WinHTTP запрашивает мимо прокси.
  Прежнее описание «HTTP(S)-прокси, схема 'http' или 'https'» вводило в заблуждение.
- **Прокси: проверка и нормализация настроек.** `TTgHttpTransport.Create` (а значит, `TTgApi`, `TTgBot` и
  компонент при `Active := True`) проверяет `Proxy` через новый `TTgProxySettings.Normalized` и сразу
  сообщает об ошибке настройки `ETgError` с понятным текстом вместо сетевой ошибки при первом запросе.
  Принимаются `'хост:порт'` в `Host` (при `Port = 0`), префикс `http://`, IPv6 (`'[::1]:3128'` или `'::1'` с
  `Port`), пробелы по краям. В `THTTPClient` схема всегда передаётся пустой (`ToRtlSettings`) — единственный
  вариант HTTP-прокси, одинаковый на всех платформах. Пароль и имя пользователя в тексты ошибок не попадают.
  Новые тексты `TgBot.Consts`: `ProxyScheme`, `ProxyBadHost`, `ProxyPort`, `ProxyPortConflict`.

### Несовместимые изменения

- **Прокси: `ETgError` при создании транспорта** (у компонента — при `Active := True`) для настроек, которые
  раньше давали сетевую ошибку или зависели от платформы:
  - `Scheme`, кроме `''` и `'http'` (`'https'`, `'socks5'`…), и схема в `Host`, кроме `http://`
    (`socks5://…`, `https://…`). `Scheme = 'https'` на Windows означал TLS до самого прокси (WinHTTP начинает
    с прокси рукопожатие TLS; обычный HTTP-прокси отвечал ошибкой 12029), на Linux и Android схема
    игнорировалась. **Миграция:** `Scheme := ''` — для облачного Bot API (`https://`) этого достаточно;
  - порт не задан (`Port = 0` и нет `'хост:порт'` в `Host`) или вне 1–65535; порт в `Host` не совпадает с
    `Port`. **Миграция:** укажите порт явно;
  - путь, `логин:пароль@` или пробелы в `Host`. **Миграция:** учётные данные — в `UserName`/`Password`.

### Внутреннее

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

### Тесты

- Стресс-тест гонки отмены родителя и освобождения дочернего источника (`TestCancelLinkRace`; полный вариант —
  `TG_ONLY=STRESS`).
- Прокси (`Tests\TgBotTests.Proxy.pas`): локальный HTTP-прокси и фейковый Bot API на Indy. Код с
  `with LSettings.Proxy do`; getMe, sendMessage, getFile, DownloadFile и long polling через прокси (`Scheme`
  `''` и `'http'`); HTTPS — `CONNECT api.telegram.org:443`; адрес прокси в тексте ошибки; компонент
  `TTelegramBot.Proxy`. Фейковый Bot API адресуется именем `tgbot-api.invalid` — WinHTTP обходит прокси для
  loopback-адресов.
- Нормализация и проверка прокси (`TestProxyNormalize`, `TestProxyTransportSettings`): `'хост:порт'`,
  `http://`, IPv6, обязательный порт, противоречие портов, SOCKS/HTTPS в `Host` и `Scheme`, учётные данные в
  `Host` — `ETgError` без пароля в тексте; пустая схема в RTL; ошибки из конструктора транспорта и компонента.
- Тест завершения процесса больше не зависит от консоли родителя (`DETACHED_PROCESS`, маркер старта); отказ
  запуска дочернего процесса окружением — `[SKIP]`, а не ложный FAIL.

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
