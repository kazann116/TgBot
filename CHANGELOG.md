# История изменений TgBot

## 0.2.2 — 2026-10-16

Правила владения: объекты библиотеки со счётчиком ссылок используются только через интерфейсы. Исправлена
путаница событий старого и нового запуска компонента. Публичный API не изменился.

### Улучшено

- **Правила владения.** Подсчитываемые объекты (`TInterfacedObject`) используются только через интерфейсы;
  убраны пары «класс + `IInterface`» и приведения интерфейсов к классам:
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

### Новое

- **`ITgCancellationSource`** (реэкспорт в `TgBot`) — источник отмены как интерфейс: `ITgCancellation` плюс
  `Cancel`.
- **`TTgCancellationSource.New`** / `New(AParent)` — рекомендуемый способ создать источник отмены (при
  `AParent` — связанный). Результат храните как `ITgCancellationSource` (README, разделы 5 «Отмена» и 14
  «Правила владения»).

### Исправлено

- `TTelegramBot`: события старого запуска — отложенный `OnWebhookRegistered`, решение об освобождении бота
  при отказе, `Stop`, отложенный из обработчика, — могли сработать для нового запуска, если новый `TTgBot`
  получил тот же адрес в памяти (ABA). Теперь они сверяются по номеру запуска, а не по указателю.

### Тесты

- Тесты времени жизни: `Free` бота во время висящего `getMe` (отменяемый и неотменяемый транспорт),
  перезапуск с поздними ответами старых задач, обработчик `/cmd@бот` при `Stop` и `Free`, 200 циклов
  `Start`/`Stop`/`Free`, поздние события старого запуска компонента (ABA), контекст после `Free` бота,
  источники отмены (в том числе 4 потока × 10000 подписок).
- Сборка тестов с `-DTGBOT_TESTHOOKS` включает счётчики живых ядер и задач подготовки (служебные хуки
  `TgBot.Bot.Core`); без символа эти проверки пропускаются. Тестов стало 88.

### Совместимость

- Публичный API не изменился.
- Класс `TTgContext` (модуль `TgBot.Context`) больше не виден снаружи — он был служебным; используйте
  `ITgContext`.
- `TTgCancellationSource.Create` сохранён, но рекомендуется `New`: ссылку на класс хранить нельзя (объект
  живёт по счётчику ссылок интерфейсов).
- `TgBot.Base` теперь в `uses` секции `interface` модулей `TgBot.Component` и `TgBot.Webhook` (для
  прикладного кода незаметно).

### Известные ограничения

- Публичные свойства `TTgBot.Source`, `TTgBot.WebhookSource` и `TTgBot.Dispatcher` по-прежнему отдают
  подсчитываемые классы (`TTgLongPollSource`, `TTgWebhookSource`, `TTgUpdateDispatcher`): не вызывайте для
  них `Free`. Перевод на интерфейсы запланирован в 0.3.0 (несовместимое изменение).

## 0.2.1 — 2026-10-15

Все тексты библиотеки собраны в одном модуле и стали переводимыми. Публичный API не изменился.

### Новое

- **Модуль `TgBot.Consts`** — все пользовательские тексты библиотеки (60 пар RU/EN, `resourcestring`) в одном
  месте по образцу `System.RTLConsts`. Каждый текст — пара `SRu…`/`SEn…`; секции по подсистемам (ядро, JSON,
  DTO, обновления, маршрутизатор, `TTgBot`, компонент, webhook-сервер). Модуль служебный: в прикладном коде
  его не подключают.
- Тексты ошибок `TgBot.Json` и `TgBot.Dto` стали переводимыми (раньше — обычные константы).
- Тексты всех исключений библиотеки переводимы, включая технические (параметр `nil`, значение вне
  диапазона).
- Единая служебная функция выбора языка `TgLangText` / `TgLangTextFmt` (`TgBot.Base`) вместо локальных
  таблиц и функций в модулях.
- Тест полноты текстов (`TestTextsComplete`): у каждого текста оба языка заданы и различаются, кириллица
  только в русском, подстановки формата совпадают. Тестов стало 79.

### Исправлено

- Сообщение «Значение не является JSON-объектом (поле %s)» (`SetValue`/`AppendRow` у DTO, построенного не
  над JSON-объектом) показывало имя класса вместо имени поля.

### Совместимость

- Публичный API не изменился: `TgText`/`TgTextFmt`, `TgUpdatesText`, `TgRouterText`, перечисления
  `TTgText`, `TTgUpdatesText`, `TTgRouterText`, `TgSetLanguage`/`TgGetLanguage`.
- Изменились имена ресурсов: все `resourcestring` теперь в модуле `TgBot.Consts`. Важно для существующих
  внешних переводов (ITE, `.drc`) — их нужно обновить.
- Технические исключения (`EArgumentNilException`, `EArgumentOutOfRangeException`) теперь содержат полную
  фразу на выбранном языке (например, «Параметр AHandler не может быть nil») вместо одного имени параметра
  или `AMaxThreads = %d`.
- Исключение при `nil`-кнопке в клавиатурах (`TTgKeyboard`) — текст библиотеки на её языке вместо RTL
  `SArgumentNil`.
- Строки webhook-сервера (`TgBot.Webhook`) теперь в пакете `TgBotRT`; `TgBotIndyRT` их импортирует.
  Пакеты пересоберите.

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
