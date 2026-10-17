# TgBot — Telegram Bot API для Delphi

![Bot API](https://img.shields.io/badge/Telegram%20Bot%20API-10.3-26A5E4?logo=telegram&logoColor=white)
![Delphi](https://img.shields.io/badge/Delphi-10.4%2B-EE1F35?logo=delphi&logoColor=white)
![Платформы](https://img.shields.io/badge/платформы-Win32%20%7C%20Win64%20%7C%20Linux64%20%7C%20Android-7A2E0E)
![Версия](https://img.shields.io/badge/версия-0.4.1-c2500f)
![Лицензия](https://img.shields.io/badge/лицензия-MIT-2ea44f)

Библиотека и невизуальный компонент для создания Telegram-ботов на Delphi. Весь Bot API, ничего лишнего в
зависимостях, подробная документация на русском.

**[Полная документация →](README.ru.md)** · [История изменений](CHANGELOG.md) · [Демо-проекты](Demos)

## Возможности

- **Весь Telegram Bot API 10.3.** Типы и методы сгенерированы по официальной спецификации генератором
  [`Tools/TgBotGen`](Tools/TgBotGen) — обновление API не требует ручной правки.
- **`TTgApi`** — клиент Bot API: каждый метод в трёх вариантах — обычный, `Try*` (без исключений) и `*Async`.
  Отправка файлов и альбомов, скачивание, обработка лимитов (429), отмена запросов.
- **`TTgBot`** — бот в коде: long polling или webhook, маршрутизатор команд и кнопок, клавиатуры, меню команд,
  состояние диалогов, многопоточная обработка.
- **`TTelegramBot`** — компонент для формы: Object Inspector, коллекция команд, обычные события.
- **`TTgWebhookServer`** — встроенный HTTP-сервер для webhook.
- **Только RTL.** Ядро использует `System.Net.HttpClient`, `System.JSON`, `System.Threading`. Indy нужен лишь
  встроенному webhook-серверу. HTTP-клиент заменяем: свой транспорт — наследник `TTgTransportBase` с двумя
  методами ([подробнее](README.ru.md#15-свой-транспорт)).

## Требования

- Delphi 10.4 Sydney и новее (проверено на 10.4 и 12).
- Win32, Win64, Linux64, Android (32 и 64 бит). Webhook — только Win32, Win64 и Linux64. iOS не поддерживается.

## Установка

**Без установки пакетов** — добавьте папку `Source` в Search Path проекта и напишите `uses TgBot;`.

**С компонентами на палитре** — запустите `Install\Install.cmd`: он соберёт пакеты, зарегистрирует их в IDE и
пропишет пути. Удаление — `Install\Uninstall.cmd`. Ручная установка описана в
[документации](README.ru.md#2-установка).

## Быстрый старт

Получите токен у [@BotFather](https://t.me/BotFather) и положите его в переменную окружения `TGBOT_TOKEN` —
так он не попадёт в исходники.

```pascal
program HelloBot;

{$APPTYPE CONSOLE}

uses
  System.SysUtils,
  TgBot;

var
  LBot: TTgBot;
begin
  LBot := TTgBot.Create(GetEnvironmentVariable('TGBOT_TOKEN'));
  try
    LBot.Command('start', 'Начать',
      procedure(ACtx: ITgContext)
      begin
        ACtx.Reply('Привет! Напишите что-нибудь.');
      end);

    LBot.OnMessage :=
      procedure(ACtx: ITgContext)
      begin
        if ACtx.Text <> '' then
          ACtx.Reply('Вы написали: ' + ACtx.Text);
      end;

    LBot.OnError :=
      procedure(AError: Exception; ACtx: ITgContext)
      begin
        Writeln('Ошибка: ', AError.Message);
      end;

    if not LBot.Run then // работает до Ctrl+C
      ExitCode := 1;
  finally
    LBot.Free;
  end;
end.
```

Бот на форме: положите `TTelegramBot` с вкладки **Telegram**, добавьте команды в свойстве `Commands`,
назначьте `OnMessage` и поставьте `Active := True`. События приходят в главном потоке — с VCL можно работать
напрямую.

## Демо-проекты

| Папка | Что показывает |
|---|---|
| [`Demos/01_Smoke`](Demos/01_Smoke) | минимальная консольная проверка |
| [`Demos/02_EchoBot`](Demos/02_EchoBot) | консольный бот: команды, инлайн-кнопки, листание страниц, состояние диалога |
| [`Demos/03_VclBot`](Demos/03_VclBot) | VCL-форма с компонентом `TTelegramBot` |
| [`Demos/04_WebhookBot`](Demos/04_WebhookBot) | приём обновлений через webhook |
| [`Demos/05_CustomTransport`](Demos/05_CustomTransport) | свой транспорт: наследник `TTgTransportBase` с журналом запросов, без `TgBot.Http` |

## Что в репозитории

| Папка | Содержимое |
|---|---|
| `Source` | исходники библиотеки; `Source/Generated` — сгенерированная часть API |
| `Packages` | пакеты `TgBotRT`, `TgBotIndyRT`, `TgBotDT` |
| `Install` | установка и удаление в IDE |
| `Demos` | примеры |
| `Tests` | 110 тестов, работают без сети и без токена |
| `Tools` | генератор API по спецификации и сборка дистрибутива |

## Известные ограничения

- Linux64 проверен компиляцией; запуск на Linux не проверялся.
- Android заявлен в пакете `TgBotRT`, на устройстве не проверялся.
- Webhook проверен локально, тестами и демо; с настоящим сервером Telegram не проверялся.

## Лицензия

[MIT](LICENSE) — берите и используйте, в том числе в коммерческих проектах. Нужно только сохранять строку об
авторе и текст лицензии.

## Связь

Вопросы и ошибки — в [Issues](../../issues). Telegram автора — [@Druidw](https://t.me/Druidw).
