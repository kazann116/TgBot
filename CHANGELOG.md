# История изменений TgBot

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
