# История изменений TgBot

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
