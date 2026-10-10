# TgBot — Telegram Bot API для Delphi

Библиотека и невизуальный компонент для создания Telegram-ботов на Delphi.

## Содержание

1. [Что это](#1-что-это)
2. [Установка](#2-установка)
3. [Быстрый старт](#3-быстрый-старт)
4. [Основы: контекст, клавиатуры, маршрутизатор](#4-основы-контекст-клавиатуры-маршрутизатор)
5. [Прямой вызов API: TTgApi](#5-прямой-вызов-api-ttgapi)
6. [Потоки](#6-потоки)
7. [Жизненный цикл](#7-жизненный-цикл)
8. [Webhook](#8-webhook)
9. [Несколько ботов, прокси, Local Bot API](#9-несколько-ботов-прокси-local-bot-api)
10. [Частые вопросы](#10-частые-вопросы)
11. [Тесты и обновление API](#11-тесты-и-обновление-api)
12. [Демо-проекты](#12-демо-проекты)

---

## 1. Что это

- **Telegram Bot API 10.3, весь API.** Все типы и методы сгенерированы по официальной спецификации генератором
  `Tools\TgBotGen` (константа `TgBotApiVersion`). Версия библиотеки — `TgBotVersion` (сейчас 0.1.0).
- **Платформы:** Win32, Win64, Linux64, Android (32 и 64 бит). iOS не поддерживается.
- **Delphi 10.4 Sydney и новее.** Проверено на 10.4 и 12.
- **Зависимости.** Ядро использует только RTL (`System.Net.HttpClient`, `System.JSON`, `System.Threading`).
  Indy нужен только встроенному webhook-серверу `TTgWebhookServer` (модуль `TgBot.Webhook`, пакет
  `TgBotIndyRT`).
- **Что внутри:**
  - `TTgApi` — клиент Bot API: каждый метод в трёх вариантах (обычный, `Try*`, `*Async`);
  - `TTgBot` — бот в коде: приём обновлений (long polling или webhook), маршрутизатор команд и кнопок,
    состояние диалогов, многопоточная обработка;
  - `TTelegramBot` — компонент для формы (Object Inspector, коллекция команд, события `of object`);
  - `TTgWebhookServer` — HTTP-сервер для webhook (Indy).
- **Лицензия** — MIT (файл `LICENSE`): можно свободно использовать, в том числе в коммерческих проектах.

В `uses` обычно достаточно одного модуля `TgBot`: он реэкспортирует типы ядра. Для компонента добавьте
`TgBot.Component`, для webhook-сервера — `TgBot.Webhook`.

## 2. Установка

### Пакеты

Откройте `Packages\TgBot.groupproj` и соберите пакеты в таком порядке (зависимости в группе уже прописаны,
поэтому достаточно собрать всю группу):

| Пакет | Что содержит | Платформы |
|---|---|---|
| `TgBotRT` | runtime: всё ядро, `TgBot`, `TgBot.Component` | Win32, Win64, Linux64, Android, Android64 |
| `TgBotIndyRT` | runtime: `TgBot.Webhook` (`TTgWebhookServer`), требует Indy | Win32, Win64, Linux64 |
| `TgBotDT` | design-time: регистрация компонентов в палитре | только Win32 (IDE 32-битная) |

Затем правый щелчок по `TgBotDT` → **Install**. На палитре появится вкладка **Telegram** с компонентами
`TTelegramBot` и `TTgWebhookServer`.

Имена `.bpl` получают суффикс версии Delphi (`{$LIBSUFFIX AUTO}`): `TgBotRT270.bpl` (10.4), `TgBotRT280.bpl`
(11), `TgBotRT290.bpl` (12); аналогично `TgBotIndyRT*.bpl` и `TgBotDT*.bpl`. Файлы `.dcp` — без суффикса
(`TgBotRT.dcp`). Поэтому пакеты разных версий IDE не конфликтуют.

### Пути

В **Library Path** (Tools → Options → Language → Delphi → Library) или в **Search Path** проекта добавьте
**только папку `Source`**. Папку `Source\Generated` добавлять не нужно: `TgBot.pas` подключает
`Generated\*.inc` относительно своего расположения.

Без установки пакетов библиотеку можно использовать просто как исходники: укажите путь к `Source` и добавьте
`TgBot` в `uses`.

### Linux64

- Нужна редакция Delphi с поддержкой Linux, установленный на Linux PAServer и добавленный в IDE Linux SDK
  (Tools → Options → SDK Manager).
- `System.Net.HttpClient` на Linux работает через **libcurl**: на целевой машине должны быть установлены
  `libcurl` и корневые сертификаты, например на Debian/Ubuntu: `sudo apt install libcurl4 ca-certificates`.
- Ctrl+C и SIGTERM обрабатываются (`Run` корректно останавливает бота) — подходит для запуска как службы
  systemd.
- Идущий HTTP-запрос на Linux и Android прерывается только по таймауту ответа (отмена ожиданий и повторов
  работает сразу).

### Android

- Работает приём через long polling (компонент `TTelegramBot` или `TTgBot.Start`) и все методы `TTgApi`.
- Недоступны: `Mode = Webhook`, `Run` (блокирующий цикл консоли — `ETgError`), `TTgWebhookServer`,
  `TTgShutdownSignal`.
- Android приостанавливает приложения в фоне: бот на телефоне перестаёт получать обновления, когда приложение
  свёрнуто. Для круглосуточного бота используйте сервер (Windows или Linux).

## 3. Быстрый старт

Получите токен у [@BotFather](https://t.me/BotFather) и задайте его в переменной окружения `TGBOT_TOKEN` (так
токен не попадёт в исходники):

```
set TGBOT_TOKEN=123456:ABC...        (Windows)
export TGBOT_TOKEN=123456:ABC...     (Linux)
```

### Консольный бот на TTgBot

```pascal
program Ex01Console;

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

    if not LBot.Run then // блокирует до Ctrl+C / SIGTERM или отказа приёма
      ExitCode := 1;
  finally
    LBot.Free;
  end;
end.
```

`Run` запускает бота, ждёт Ctrl+C/SIGTERM (или `RequestStop`) и останавливает его. Результат `False` — бот
остановлен неустранимой ошибкой (например, неверный токен), подробности уже переданы в `OnError`/`OnFault`.

Команда с описанием (`'Начать'`) автоматически попадает в меню бота (`setMyCommands` при запуске).

### Форма с компонентом TTelegramBot

1. Положите `TTelegramBot` с вкладки **Telegram** на форму.
2. Токен: оставьте `Token` пустым — компонент возьмёт его из переменной окружения `TokenEnv` (по умолчанию
   `TGBOT_TOKEN`).
3. В свойстве **Commands** добавьте элементы: `Command = start`, `Description = Начать`; двойной щелчок по
   `OnExecute` создаст обработчик.
4. Назначьте `OnMessage`, `OnCallbackQuery`, `OnError`, `OnFault`.
5. Запуск — `TelegramBot1.Active := True` (или `Active = True` в Object Inspector: бот стартует после загрузки
   формы).

```pascal
procedure TFormMain.TelegramBot1Message(Sender: TObject; const Ctx: ITgContext);
begin
  MemoLog.Lines.Add(Ctx.Text);   // Delivery = Main: можно трогать VCL напрямую
  Ctx.Reply('Эхо: ' + Ctx.Text);
end;
```

У компонента `Delivery = Main` по умолчанию: события приходят в главном потоке, синхронизация не нужна (но см.
[раздел 6](#6-потоки)). Модуль `TgBot` добавляется в `uses` формы автоматически при сохранении.

Компонент можно использовать и без формы — в консоли или службе (`uses TgBot, TgBot.Component`):

```pascal
  LBot := TTelegramBot.Create(nil);
  try
    // Token пуст — токен берётся из переменной окружения TokenEnv (TGBOT_TOKEN).
    LBot.Command('start', 'Начать',
      procedure(ACtx: ITgContext)
      begin
        ACtx.Reply('Привет от компонента!');
      end);
    if not LBot.Run then // Delivery = Main: события разбирает сам Run
      ExitCode := 1;
  finally
    LBot.Free;
  end;
```

## 4. Основы: контекст, клавиатуры, маршрутизатор

### ITgContext

Каждый обработчик получает контекст обновления `ITgContext`:

| Член | Назначение |
|---|---|
| `Text` | текст или подпись сообщения; для кнопки — callback data; для inline-запроса — query |
| `Data` | callback data (только для нажатия кнопки) |
| `Message`, `Update`, `Raw` | типизированное сообщение, всё обновление, сырой JSON |
| `ChatId`, `From`, `Kind` | чат, автор, вид обновления (`TTgUpdateType.*`) |
| `Command`, `Args` | команда без `/` и `@бот`; аргументы сработавшего правила |
| `Reply`, `ReplyHtml` | ответ в тот же чат (и ту же тему форума) |
| `Answer(Text, ShowAlert)` | ответ на нажатие кнопки (`answerCallbackQuery`) |
| `Edit(Text[, Keyboard])` | правка сообщения с нажатой кнопкой |
| `State[Name]`, `ClearState` | состояние диалога по ключу «чат:пользователь» |
| `Handled` | `True` — остановить дальнейшую обработку |
| `Api`, `Cancel` | клиент Bot API; токен отмены обработчика |

Контекст действителен только внутри обработчика и в его потоке (не сохраняйте его и не передавайте в другие
потоки).

### Клавиатуры TTgKeyboard

`TTgKeyboard.Inline` (кнопки под сообщением), `TTgKeyboard.Reply` (вместо клавиатуры устройства),
`TTgKeyboard.Remove`, `TTgKeyboard.ForceReply`. Построители — записи-значения: каждый вызов возвращает новую
копию; первая кнопка без `Row` сама начинает строку.

```pascal
  ABot.Command('menu',
    procedure(ACtx: ITgContext)
    begin
      // Инлайн-кнопки под сообщением
      ACtx.Reply('Выберите:',
        TTgKeyboard.Inline
          .Row.Button('Да', 'yes').Button('Нет', 'no')
          .Row.Url('Сайт', 'https://example.com'));
      // Обычная клавиатура вместо клавиатуры устройства
      ACtx.Reply('Или нажмите кнопку внизу:',
        TTgKeyboard.Reply
          .Row.Text('Помощь').Text('Настройки')
          .Row.RequestContact('Отправить телефон')
          .Resize.OneTime);
    end);
  ABot.Text('Помощь',
    procedure(ACtx: ITgContext)
    begin
      ACtx.Reply('Клавиатура убрана.', TTgKeyboard.Remove);
    end);
```

Другие кнопки инлайн-клавиатуры: `WebApp`, `LoginUrl`, `SwitchInline`, `SwitchInlineCurrentChat`, `CopyText`,
`Pay`, `Game`, а также `Add` для готовой кнопки. Обычной: `RequestLocation`, `RequestPoll`, `WebApp`, `Add`;
флаги `Resize`, `OneTime`, `Persistent`, `Selective`, `Placeholder`. callback data — от 1 до 64 байт.

### Маршрутизатор

Регистрация возвращает `Self`, поэтому правила можно писать цепочкой:

```pascal
  ABot.Command(['help', 'h'], 'Справка',
    procedure(ACtx: ITgContext)
    begin
      ACtx.Reply('Команды: /help, /order <номер>');
    end)
  .Command('order',
    procedure(ACtx: ITgContext)
    begin
      ACtx.Reply('Заказ: ' + ACtx.Args); // '/order 42' → Args = '42'
    end)
  .Callback('yes',
    procedure(ACtx: ITgContext)
    begin
      ACtx.Answer('Принято');  // всплывающее уведомление
      ACtx.Edit('Вы ответили «Да»');
    end)
  .CallbackPrefix('page:',
    procedure(ACtx: ITgContext)
    begin
      ACtx.Answer;
      ACtx.Edit('Страница ' + ACtx.Args,  // 'page:2' → Args = '2'
        TTgKeyboard.Inline.Button('Дальше', 'page:' + IntToStr(StrToIntDef(ACtx.Args, 1) + 1)));
    end)
  .TextMatch('^заказ (\d+)$',
    procedure(ACtx: ITgContext)
    begin
      ACtx.Reply('Заказ №' + ACtx.Args);  // первая группа регулярного выражения
    end);

  ABot.OnUpdate :=
    procedure(ACtx: ITgContext)
    begin
      // Перехват до маршрутизатора: например, «бан-лист»
      if Assigned(ACtx.From) and (ACtx.From.Id = 123456789) then
        ACtx.Handled := True;
    end;
```

**Порядок обработки** (срабатывает первое подходящее правило):

1. `OnUpdate` — для каждого обновления; `ACtx.Handled := True` прекращает обработку.
2. Сообщение: `Command` (команда этому боту; нет правила — `OnUnknownCommand`) → `Text('точный текст')` (без
   учёта регистра) → `TextMatch` (в порядке регистрации) → `Text(любой текст)` → `OnMessage`.
3. Нажатие кнопки: `Callback('точные данные')` → `CallbackPrefix` (в порядке регистрации) → `OnCallbackQuery`.

`OnMessage`/`OnCallbackQuery` вызываются, только если ни одно правило не сработало (обработчик правила может
вернуть `ACtx.Handled := False`, чтобы обработка пошла дальше). Маршрутизируется только поле `text` (не
подпись к фото). Команда другому боту (`/start@OtherBot`) идёт дальше как обычный текст. Регистрировать
правила можно и во время работы; повторная регистрация того же ключа заменяет обработчик, `nil` — удаляет
правило.

Кнопку, на которую обработчик не ответил (`Answer`), бот подтверждает пустым ответом сам
(`AutoAnswerCallbacks = True`), чтобы у пользователя не висели «часики».

У компонента те же методы (`TelegramBot1.Command(...)`, `Callback`, `TextMatch`…) — регистрации сохраняются
между запусками; команды из коллекции `Commands` без `OnExecute` уходят в событие `OnCommand`.

### Меню команд

Команды с описанием (`Command('start', 'Начать', ...)`, элементы `Commands` с `Description`) при запуске
отправляются в `setMyCommands` — это меню «/» в клиенте Telegram. Отключить — `SetMyCommandsOnStart := False`.
Для другого языка или области видимости вызовите `Api.SetMyCommands` сами.

### Состояние диалога

`ACtx.State['step'] := 'wait_name'` в одном обработчике и `if ACtx.State['step'] = 'wait_name'` в следующем —
пошаговые диалоги без своих словарей; `ACtx.ClearState` сбрасывает всё. По умолчанию состояние хранится в
памяти процесса (`TTgMemoryStateStorage`); своё хранилище (БД, файл) — реализуйте `ITgStateStorage` и
присвойте `Bot.StateStorage`. Пример — команда `/counter` в демо EchoBot.

### Экранирование: TgHtmlEscape и TgMarkdownV2Escape

Любые данные пользователя (имена, текст) перед вставкой в размеченный текст экранируйте — иначе Telegram
вернёт ошибку 400 разбора разметки.

```pascal
  // HTML: ReplyHtml сам задаёт parse_mode = HTML
  ACtx.ReplyHtml('Привет, <b>' + TgHtmlEscape(AUserName) + '</b>!');

  // MarkdownV2: через опции метода
  LOptions.ParseMode := TTgParseMode.MarkdownV2;
  ACtx.Api.SendMessage(ACtx.ChatId, 'Привет, *' + TgMarkdownV2Escape(AUserName) + '*\!',
    LOptions);
```

## 5. Прямой вызов API: TTgApi

`TTgApi` можно использовать без бота — например, чтобы отправлять уведомления из приложения. Клиент
потокобезопасен. Внутри обработчика используйте `ACtx.Api`.

### Синхронный вызов, Try, Async

Синхронный вызов при ошибке выбрасывает исключение:

```pascal
var
  LApi: TTgApi;
  LMsg: ITgMessage;
begin
  LApi := TTgApi.Create(GetEnvironmentVariable('TGBOT_TOKEN'));
  try
    Writeln('Бот: @', LApi.GetMe.Username);
    LMsg := LApi.SendMessage(CChatId, 'Привет!');
    LApi.EditMessageText(CChatId, LMsg.MessageId, 'Привет! (изменено)');
  finally
    LApi.Free;
  end;
end;
```

`Try*` — без исключений, сведения об ошибке в `TTgErrorInfo`:

```pascal
var
  LMsg: ITgMessage;
  LError: TTgErrorInfo;
begin
  if not LApi.TrySendMessage(LChatId, 'Привет!', LMsg, LError) then
    Writeln('Не отправлено: ', LError.ErrorCode, ' ', LError.Description);
end;
```

`*Async` — в пуле потоков библиотеки; параметры проверяются в вызывающем потоке, колбэки приходят в
**рабочем** потоке:

```pascal
  LApi.SendMessageAsync(LChatId, 'Привет!',
    procedure(AMsg: ITgMessage)
    begin
      // рабочий поток пула; в UI — только через TThread.Queue
      TThread.Queue(nil, procedure begin Writeln('message_id = ', AMsg.MessageId); end);
    end,
    procedure(AError: Exception)
    begin
      Writeln('Ошибка: ', AError.Message); // AError живёт только внутри колбэка
    end);
```

Не уничтожайте `TTgApi` из его же Async-колбэка. Размер общего пула — `TgSetAsyncPoolSize`.

### Необязательные параметры (Options)

Необязательные параметры метода — запись `TTg<Метод>Options`; незаданные поля не передаются. Частые сочетания
есть в виде перегрузок (текст + клавиатура, фото + подпись и т.п.).

```pascal
var
  LOptions: TTgSendMessageOptions;
begin
  LOptions.ParseMode := TTgParseMode.Html;
  LOptions.DisableNotification := True;
  LOptions.ProtectContent := True;
  LApi.SendMessage(LChatId, '<i>Тихое</i> сообщение', LOptions);
end;
```

### Файлы и альбомы

```pascal
  LApi.SendPhoto(LChatId, TTgInputFile.FromFile('C:\Pictures\cat.jpg'), 'Кот');
  LApi.SendPhoto(LChatId, TTgInputFile.FromUrl('https://example.com/cat.jpg'));
  LApi.SendPhoto(LChatId, TTgInputFile.FromFileId('AgACAgIAAxkB...'));
  LApi.SendDocument(LChatId, TTgInputFile.FromStream(LStream, 'report.pdf'));
  LApi.SendDocument(LChatId, TTgInputFile.FromBytes(LBytes, 'data.csv', 'text/csv'));

  // Альбом (2–10 элементов)
  LApi.SendMediaGroup(LChatId, [
    TTgInputMediaPhoto.Create(TTgInputFile.FromFile('C:\Pictures\1.jpg')).WithCaption('Первое'),
    TTgInputMediaPhoto.Create(TTgInputFile.FromFile('C:\Pictures\2.jpg'))]);
```

`FromStream` не освобождает поток — он должен жить до конца вызова (для Async — до колбэка). Результаты
`SendMediaGroup` разделяют общий JSON ответа; для долгого хранения отдельного элемента используйте
`TTgDto.Detach`.

### Скачивание файла

```pascal
var
  LFile: ITgFile;
  LStream: TFileStream;
begin
  if (ACtx.Message = nil) or (ACtx.Message.Document = nil) then
    Exit;
  LFile := LApi.GetFile(ACtx.Message.Document.FileId);
  LStream := TFileStream.Create('C:\Downloads\' + ExtractFileName(LFile.FilePath), fmCreate);
  try
    LApi.DownloadFile(LFile.FilePath, LStream);
  finally
    LStream.Free;
  end;
end;
```

Облачный Bot API отдаёт файлы до 20 МБ; больше — через Local Bot API ([раздел
9](#9-несколько-ботов-прокси-local-bot-api)).

### Ошибки и 429

| Исключение | Когда |
|---|---|
| `ETgApiError` | Bot API вернул `ok = false`: `ErrorCode`, `Description`, `RetryAfter`, `MigrateToChatId`, `Method` |
| `ETgConflictError` | 409: второй экземпляр бота или активный webhook (наследник `ETgApiError`) |
| `ETgNetworkError` | нет соединения, таймаут, ответ не JSON: `StatusCode`, `Method` |
| `ETgCancelledError` | операция отменена (токен отмены, `Free` клиента, остановка бота) |
| `ETgError` | базовый класс; неверные аргументы |

```pascal
  try
    LApi.SendMessage(LChatId, 'Привет!');
  except
    on E: ETgApiError do      // ответ Bot API с ok = false
      if E.ErrorCode = 429 then
        Writeln('Слишком часто, повторить через ', E.RetryAfter, ' с')
      else if E.ErrorCode = 403 then
        Writeln('Пользователь заблокировал бота')
      else
        Writeln('Bot API: ', E.ErrorCode, ' ', E.Description);
    on E: ETgNetworkError do  // нет сети, таймаут, не JSON
      Writeln('Сеть: ', E.Message);
    on E: ETgCancelledError do
      Writeln('Отменено');
  end;
```

Ошибку 429 транспорт по умолчанию обрабатывает сам: ждёт `retry_after` и повторяет запрос. Кроме того, встроен
лимитёр (30 запросов/с на бота и 1 сообщение/с в один чат). Всё настраивается в `TTgHttpSettings`:

```pascal
  LSettings := TTgHttpSettings.Create(GetEnvironmentVariable('TGBOT_TOKEN'));
  LSettings.AutoRetry429 := True;      // повтор после retry_after (по умолчанию)
  LSettings.MaxRetries := 3;
  LSettings.MaxRetryAfterSec := 60;    // дольше ждать не будем — сразу ETgApiError
  LSettings.GlobalRatePerSec := 30;    // общий лимит запросов бота
  LSettings.PerChatIntervalMs := 1000; // интервал между сообщениями в один чат
  LSettings.ResponseTimeoutMs := 30000;
  LApi := TTgApi.Create(LSettings);    // или TTgBot.Create(LSettings)
```

Токен бота никогда не попадает в тексты исключений. Язык сообщений библиотеки —
`TgSetLanguage(TTgLanguage.En)` (по умолчанию русский).

### Отмена

Сгенерированные методы используют «окружающий» токен отмены потока (`TTgCancelScope`). Внутри обработчиков
бота он задан автоматически (`ACtx.Cancel`): при остановке бота вызовы `ACtx.Api` прерываются. Свой токен:

```pascal
var
  LSource: TTgCancellationSource;
  LToken: ITgCancellation;
  LScope: TTgCancelScope;
begin
  LSource := TTgCancellationSource.Create;
  LToken := LSource; // интерфейсная ссылка управляет временем жизни источника
  // LSource.Cancel из другого потока (кнопка «Отмена») прервёт вызовы ниже
  LScope := TTgCancelScope.Enter(LToken);
  try
    LApi.SendDocument(LChatId, TTgInputFile.FromFile('C:\big.zip'));
  finally
    LScope.Leave;
  end;
end;
```

Отмена прерывает ожидания (лимитёр, `retry_after`) сразу, а идущий HTTP-запрос — на Windows сразу, на Linux и
Android — по таймауту ответа. `Free` клиента отменяет его незавершённые вызовы. Для универсального `Call` есть
перегрузка с явным `ACancel`.

## 6. Потоки

### Delivery: Main или Worker

| | `TTgBot` | `TTelegramBot` |
|---|---|---|
| Значение по умолчанию | `Worker` | `Main` |

- **`Worker`** — обработчики выполняются в потоках диспетчера. UI не блокируется, но обращаться к VCL/FMX
  можно только через `TThread.Queue` или `TThread.Synchronize`; общие данные защищайте сами.
- **`Main`** — обработчики выполняются в главном потоке по очереди. Удобно для форм: синхронизация не нужна.
  **Но** `ACtx.Reply` и другие вызовы API синхронные: на время каждого HTTP-запроса (обычно 50–300 мс, при
  плохой сети — до таймаута) интерфейс «замирает». Для нагруженного бота с формой выбирайте `Worker` или
  отправляйте ответы через `*Async`. В консоли при `Main` главный поток должен вызывать `CheckSynchronize` —
  это делает `Run`.

```pascal
  LBot.Delivery := TTgDelivery.Worker;  // обработчики — в потоках диспетчера
  LBot.MaxParallel := 8;                // до 8 чатов обрабатываются одновременно
  LBot.OnMessage :=
    procedure(ACtx: ITgContext)
    var
      LText: string;
    begin
      ACtx.Reply('Принято');            // HTTP-запрос — в рабочем потоке, UI свободен
      LText := ACtx.Text;               // ACtx не передавайте в другой поток
      TThread.Queue(nil,
        procedure
        begin
          // здесь можно трогать VCL/FMX: Memo1.Lines.Add(LText)
        end);
    end;
```

### MaxParallel и порядок

- `MaxParallel` (по умолчанию 4) — число потоков обработчиков в режиме `Worker`.
- **Обновления одного чата обрабатываются строго по порядку**, по одному; разные чаты — параллельно. Поэтому в
  обработчике не нужно бояться, что два сообщения одного пользователя обгонят друг друга.
- `QueueCapacity` — ёмкость очереди (по умолчанию 1000), `AckPolicy` — когда подтверждать полученные
  обновления (`AfterReceive` — быстрее, `AfterBatch` — при сбое процесса пакет придёт повторно).
- События `OnError` (с `ACtx = nil`), `OnFault`, `OnConflict`, `OnWebhookRegistered` у `TTgBot` приходят в
  служебных потоках. У компонента при `Delivery = Main` они переносятся в главный поток.

## 7. Жизненный цикл

### Состояния

`State: TTgBotState`:

- `Idle` — не запущен (до `Start`, после `Stop`);
- `Running` — приём и обработка идут (`Active = True`);
- `Stopping` — выполняется `Stop`;
- `Faulted` — приём остановлен неустранимой ошибкой (401 — неверный токен, 404, 409 «webhook is active» без
  `AutoDeleteWebhook`, ошибка `setWebhook`). Уже принятые обновления дорабатываются.

При отказе вызываются `OnError(E, nil)`, затем `OnFault(E)` — один раз за запуск.

### TTgBot: Start/Stop, Run/RequestStop

```pascal
  LBot.OnFault :=
    procedure(AError: Exception)
    begin
      // поток источника; State уже Faulted. Stop/Start отсюда нельзя
      Writeln('Отказ приёма: ', AError.Message);
    end;

  LBot.Command('quit',
    procedure(ACtx: ITgContext)
    begin
      ACtx.Reply('Выключаюсь');
      LBot.RequestStop;                 // Run вернёт True
    end);

  LBot.Start;                           // Idle → Running, не блокирует
  // ... программа работает ...
  if LBot.State = TTgBotState.Faulted then
    Writeln('Бот остановлен ошибкой');
  LBot.Stop;                            // → Idle; можно снова Start
  LBot.Start;                           // перезапуск тем же объектом
  LBot.Stop;
```

- `Start` не ждёт сеть: бот сразу `Running`, `getMe`/`setMyCommands` идут в фоне. Из `Faulted` `Start` сам
  выполняет `Stop` и запускает заново.
- `Stop(AWaitMs)` дорабатывает принятое и ждёт обработчики (по умолчанию до 10 с); `False` — зависший
  обработчик не дождались. Из главного потока `Stop` продолжает обрабатывать очередь `TThread.Queue`, поэтому
  обработчики с `Delivery = Main` не взаимоблокируются.
- `Stop`/`Start` **нельзя** вызывать из обработчика обновления и из `OnFault` (`ETgError`): используйте
  `RequestStop` или `TThread.Queue`.
- `Run` (консоль): `Start` → ожидание → `Stop`. Завершается по `RequestStop`, Ctrl+C/SIGINT/SIGTERM, закрытию
  окна консоли или отказу. `True` — остановлен по запросу, `False` — из-за `Faulted`.
- `Free` вызывает `Stop`. Не обращайтесь к переменной бота из обработчика после `Free`.

### TTelegramBot

- `Active := True/False` (или `Start`/`Stop`). Свойства, влияющие на бота, при `Active` менять нельзя
  (`ETgError`); события — можно.
- `Active = True` в DFM: запуск откладывается до загрузки формы, поэтому `OnCreate` успевает задать `Token`.
- `OnStart` — бот запущен; `OnStop(Sender, Reason)` — остановлен (`Requested` или `Fault`).
- При отказе (`Delivery = Main`): `OnError` → `OnFault` → компонент освобождает внутреннего бота →
  `OnStop(Fault)`. Перезапуск — снова `Active := True`.
- `Run`/`RequestStop` — как у `TTgBot` (для консоли и служб).
- Внутренний бот доступен как `TelegramBot1.Bot` (только во время работы; тонкие настройки вроде
  `StateStorage`), клиент — `TelegramBot1.Api`.

## 8. Webhook

В режиме webhook Telegram сам присылает обновления POST-запросами на ваш HTTPS-адрес. Требования Telegram:
HTTPS с валидным сертификатом (или самоподписанным, переданным в `setWebhook`), порты 443, 80, 88 или 8443.
Long polling проще и не требует входящих соединений — webhook нужен на сервере с большим потоком обновлений
или когда polling невозможен.

### Встроенный сервер TTgWebhookServer

`TTgWebhookServer` (Indy) — только HTTP; HTTPS обеспечивает обратный прокси на той же машине. По умолчанию
сервер слушает `127.0.0.1:8080`. Один сервер обслуживает несколько ботов по разным путям.

```pascal
var
  LServer: TTgWebhookServer;
  LBot: TTelegramBot;
begin
  LServer := TTgWebhookServer.Create(nil);
  LBot := TTelegramBot.Create(nil);
  try
    LServer.Port := 8080;                 // слушает 127.0.0.1:8080 (BindAddress)
    LServer.PublicUrl := 'https://bots.example.com';
    LServer.Active := True;               // занятый порт — исключение здесь

    LBot.Mode := TTgReceiveMode.Webhook;
    LBot.Webhook.Server := LServer;
    LBot.Webhook.Path := '/tg/main';      // URL = PublicUrl + Path
    LBot.Webhook.DeleteOnStop := True;
    LBot.OnWebhookRegistered := AHandlers.BotRegistered;
    // ... команды и обработчики — как в режиме polling ...
    LBot.Run;                             // до Ctrl+C; затем deleteWebhook
  finally
    LBot.Free;                            // бот — раньше сервера
    LServer.Free;
  end;
end;
```

`OnWebhookRegistered` — `setWebhook` прошёл успешно (у компонента при `Delivery = Main` — в главном потоке,
после `OnStart`). Ошибка регистрации — `OnError` + `OnFault`. На форме то же самое настраивается в Object
Inspector: положите `TTgWebhookServer`, выберите его в `TelegramBot1.Webhook.Server`.

### HTTPS: обратный прокси

Caddy (сам получает сертификат Let's Encrypt):

```
bots.example.com {
  reverse_proxy 127.0.0.1:8080
}
```

nginx: `location /tg/ { proxy_pass http://127.0.0.1:8080; client_max_body_size 1m; }` внутри `server` с
`listen 443 ssl` и вашим сертификатом.

Быстрый тест без домена — временный туннель Cloudflare (адрес вида `https://xxxx.trycloudflare.com` печатается
при запуске, его и укажите в `PublicUrl`):

```
cloudflared tunnel --url http://localhost:8080
```

Прокси должен передавать путь без изменений (или срезать общий префикс, входящий в `PublicUrl`).

### Свой HTTP-сервер: HandleWebhook

Если в приложении уже есть HTTP-сервер (WebBroker, Horse, mORMot, Indy), передайте тело запроса в
`HandleWebhook` и ответьте кодом `TgWebhookHttpStatus`. Пример для `TTgBot` и WebBroker:

```pascal
procedure StartBot;
begin
  GBot := TTgBot.Create(GetEnvironmentVariable('TGBOT_TOKEN'));
  GBot.Mode := TTgReceiveMode.Webhook;
  GBot.WebhookUrl := 'https://bots.example.com/tg/hook';
  GBot.Delivery := TTgDelivery.Worker;
  GBot.OnMessage :=
    procedure(ACtx: ITgContext)
    begin
      ACtx.Reply('Эхо: ' + ACtx.Text);
    end;
  GBot.Start; // setWebhook — в фоне; ошибка — OnError + OnFault
end;
```

```pascal
// Действие WebBroker с PathInfo = '/tg/hook', MethodType = mtPost
procedure TWebModule1.WebModule1TgAction(Sender: TObject; Request: TWebRequest;
  Response: TWebResponse; var Handled: Boolean);
var
  LResult: TTgWebhookResult;
begin
  Request.ReadTotalContent; // тело целиком
  LResult := GBot.HandleWebhook(Request.RawContent,
    Request.GetFieldByName('X-Telegram-Bot-Api-Secret-Token'));
  Response.StatusCode := TgWebhookHttpStatus(LResult); // 200/400/403/503
  Response.Content := '';
  Handled := True;
end;
```

`HandleWebhook` потокобезопасен и не блокирует дольше `WebhookSource.PostTimeoutMs` (250 мс): обработка идёт в
потоках бота, а серверу сразу возвращается код. Результаты: `Accepted` (200), `Forbidden` (403, неверный
секрет), `BadRequest` (400), `Unavailable` (503 — бот не запущен или очередь переполнена; Telegram повторит
доставку). У компонента — `TelegramBot1.HandleWebhook` с тем же смыслом (при `Webhook.Server = nil`).

### Самоподписанный сертификат и IP-адрес

Если TLS завершает ваш собственный сервер с самоподписанным сертификатом, передайте Telegram его публичную
часть:

```pascal
  LBot.Webhook.Url := 'https://203.0.113.10:8443/tg/main';
  LBot.Webhook.Certificate := 'C:\certs\public.pem'; // публичный ключ самоподписанного сертификата
  LBot.Webhook.IpAddress := '203.0.113.10';          // необязательно: адрес вместо DNS
  LBot.Webhook.SecretToken := '';                    // пусто — случайный при каждом запуске
```

У `TTgBot` то же — `WebhookCertificate` (`TTgInputFile.FromFile(...)`) и `WebhookIpAddress`.

### Безопасность

- **Секрет.** `SecretToken` пустой — при каждом запуске генерируется случайный (48 символов) и передаётся в
  `setWebhook`; запросы без правильного заголовка `X-Telegram-Bot-Api-Secret-Token` получают 403. Не храните
  секрет в форме без необходимости.
- **Не включайте токен бота в путь** (`Path`) — для проверки отправителя служит секрет.
- Сервер по умолчанию слушает только `127.0.0.1` — наружу смотрит лишь прокси. `BindAddress = '0.0.0.0'` —
  только если понимаете зачем.
- Тело больше `MaxBodySize` (1 МБ) отклоняется (413/400); повторы одного `update_id` отбрасываются
  (`WebhookSource.DedupWindow`).
- URL webhook должен быть `https://`; `http://` допускается только с Local Bot API (у `TTgBot.WebhookUrl` и
  `Webhook.Url`; `PublicUrl` сервера — всегда `https://`).
- Переход webhook → polling: включите `Webhook.DeleteOnStop` (`DeleteWebhookOnStop` у `TTgBot`) или
  `AutoDeleteWebhook`, иначе `getUpdates` получит 409.

## 9. Несколько ботов, прокси, Local Bot API

### Несколько ботов в одном процессе

Каждый `TTgBot`/`TTelegramBot` независим (свой токен, поток приёма, потоки обработчиков). Общий у всех только
пул Async-вызовов.

```pascal
  LShop := TTgBot.Create(GetEnvironmentVariable('SHOP_TOKEN'));
  LSupport := TTgBot.Create(GetEnvironmentVariable('SUPPORT_TOKEN'));
  try
    SetupHandlers(LShop, LSupport); // обработчики — как у одного бота
    TTgShutdownSignal.Install;
    try
      LShop.Start;
      LSupport.Start;
      while not TTgShutdownSignal.Requested do // Ctrl+C / SIGTERM
        Sleep(200);
      LShop.Stop;
      LSupport.Stop;
    finally
      TTgShutdownSignal.NotifyStopped;
      TTgShutdownSignal.Uninstall;
    end;
  finally
    LSupport.Free;
    LShop.Free;
  end;
```

Один токен — один процесс: два экземпляра с одним токеном в режиме polling мешают друг другу (409). В режиме
webhook несколько ботов обслуживает один `TTgWebhookServer` по разным `Webhook.Path`.

### Прокси

```pascal
  LSettings := TTgHttpSettings.Create(GetEnvironmentVariable('TGBOT_TOKEN'));
  LSettings.Proxy := TTgProxySettings.Create('proxy.local', 3128, 'user', 'secret');
  LBot := TTgBot.Create(LSettings);
```

Компонент — свойство `Proxy` (пустой `Host` — без прокси):

```pascal
  TelegramBot1.Proxy.Host := 'proxy.local';
  TelegramBot1.Proxy.Port := 3128;
```

Поддерживаются HTTP(S)-прокси (средствами `System.Net.HttpClient`).

### Local Bot API server

[telegram-bot-api](https://github.com/tdlib/telegram-bot-api) на своём сервере снимает ограничения облака:
файлы до 2000 МБ, скачивание без ограничения размера, webhook по `http://`.

```pascal
  LSettings := TTgHttpSettings.Create(GetEnvironmentVariable('TGBOT_TOKEN'));
  LSettings.ApiUrl := 'http://127.0.0.1:8081'; // telegram-bot-api --local
  LSettings.LocalMode := True;                 // сервер на этой же машине
  LApi := TTgApi.Create(LSettings);
  try
    // Файл с диска сервера Bot API, без загрузки через HTTP
    LApi.SendDocument(123456789, TTgInputFile.FromLocalPath('/data/video.mp4'));
  finally
    LApi.Free;
  end;
```

- `LocalMode = True` (сервер запущен с `--local` на той же машине): `DownloadFile` читает файл прямо с диска
  по абсолютному `file_path`.
- У компонента — свойства `ApiUrl` и `LocalMode`.
- Перед переносом бота из облака на свой сервер Telegram требует вызвать `logOut` (`LApi.LogOut`) у облачного
  API.

## 10. Частые вопросы

**Бот не отвечает.** Чаще всего он просто не запущен: у компонента `Active = False`; в консоли не вызван `Run`
(или `Start` без цикла ожидания); у `TTgBot` с `Delivery = Main` в консоли никто не вызывает
`CheckSynchronize` (используйте `Run`). Проверьте также, что токен задан (`Token` или переменная `TokenEnv`),
и назначьте `OnError` — без него ошибки не видны.

**Кнопки не работают (нажатия не приходят).** Сервер Telegram **запоминает** последний переданный
`allowed_updates` (из `getUpdates` или `setWebhook`). Если список задан без `callback_query`, нажатия не
придут. Бот передаёт `allowed_updates` в каждом запросе: не задан — пустой список, то есть все типы, кроме
`chat_member` и реакций (заодно сбрасывается фильтр, оставленный другой программой с тем же токеном). Явный
список должен включать всё нужное:

```pascal
  LBot.AllowedUpdates := TArray<string>.Create(TTgUpdateType.Message,
    TTgUpdateType.CallbackQuery, TTgUpdateType.ChatMember);
  // компонент: строка через запятую
  TelegramBot1.AllowedUpdates := 'message,callback_query,chat_member';
```

Если назначен `OnCallbackQuery`, а в явном списке нет `callback_query`, при запуске придёт предупреждение в
`OnError`.

**Токен сохраняется в DFM.** Свойство `Token` хранится в форме открытым текстом и попадёт в систему контроля
версий. Оставьте `Token` пустым — компонент возьмёт токен из переменной окружения `TokenEnv` (по умолчанию
`TGBOT_TOKEN`), либо задавайте `Token` в коде из защищённого хранилища до `Active := True`.

**Русские строки превращаются в «кракозябры».** Сохраняйте `.pas`/`.dpr` в **UTF-8 с BOM** (в редакторе IDE:
правый щелчок → File Format → UTF8). Файл UTF-8 без BOM компилятор читает в ANSI-кодировке системы (если BOM
добавить нельзя — ключ компилятора `--codepage:65001`). Для консоли Windows вызовите
`SetConsoleOutputCP(CP_UTF8)` (см. демо EchoBot).

**409 Conflict.** `terminated by other getUpdates request` — запущен второй экземпляр бота с тем же токеном (в
том числе забытый в фоне процесс или отладочный запуск): оставьте один.
`can't use getUpdates method while webhook is active` — для токена установлен webhook:

```pascal
  LBot.AutoDeleteWebhook := True;  // 409 «webhook is active» → deleteWebhook и дальше polling
  LBot.OnConflict :=
    procedure(AError: ETgConflictError)
    begin
      Writeln('409: ', AError.Description);
    end;
```

**Android: бот перестаёт отвечать в фоне.** Это поведение ОС: приложение в фоне приостанавливается. Держите
бота на сервере, а на телефоне используйте только `TTgApi` для отправки.

**Ошибка «message is not modified».** Telegram возвращает её, если новый текст и клавиатура совпадают с
текущими (например, повторное нажатие кнопки). `ACtx.Edit` в этом случае возвращает `False` без исключения:

```pascal
  LBot.Callback('refresh',
    procedure(ACtx: ITgContext)
    begin
      if ACtx.Edit('Курс: 92,15') then
        ACtx.Answer('Обновлено')
      else
        ACtx.Answer('Без изменений'); // «message is not modified» — не исключение
    end);
```

Прямой `Api.EditMessageText` в той же ситуации выбрасывает `ETgApiError` (400). `ACtx.Edit` без клавиатуры
убирает инлайн-клавиатуру сообщения — передайте её вторым параметром, если она нужна.

**Бот в группе не видит сообщения.** По умолчанию бот в группе получает только команды и ответы на свои
сообщения (privacy mode). Отключается в @BotFather: `/setprivacy` → Disable (затем удалите и снова добавьте
бота в группу).

## 11. Тесты и обновление API

### Тесты

`Tests\TgBotTests.dpr` — офлайн-тесты без сети и без DUnitX (подменный транспорт). Сборка из папки `Tests`:

```
dcc64 -B -U..\Source TgBotTests.dpr
TgBotTests.exe
```

Итог печатается в конце (число тестов и проверок); код выхода 1, если хотя бы одна проверка не прошла; утечки
памяти выводятся отчётом менеджера памяти (Windows). Нужен Indy (тесты webhook-сервера).

- `TG_ONLY=<подстрока>` — выполнить только тесты, в имени которых есть подстрока (`set TG_ONLY=Webhook`).
- `TG_ONLY=STRESS` — долгое нагрузочное воспроизведение (только явно).

### Обновление Bot API (TgBotGen)

`Tools\TgBotGen\TgBotGen.dpr` — генератор `Source\Generated\Gen.*.inc` по HTML-странице документации (только
Windows). Соберите его так, чтобы exe оказался в `Tools\TgBotGen\Bin` (папка `Spec` по умолчанию ищется как
`..\Spec` относительно exe), и выполните из `Tools\TgBotGen`:

```
Bin\TgBotGen.exe --fetch
Bin\TgBotGen.exe --parse Spec\api-<версия>.html --strict
Bin\TgBotGen.exe --analyze Spec\api-<версия>.html --strict
Bin\TgBotGen.exe --gen Spec\api-<версия>.html --out ..\..\Source\Generated
```

- `--fetch` скачивает https://core.telegram.org/bots/api в `Spec\api-<версия>.html`; если файл этой версии уже
  есть и отличается, новый сохраняется как `api-<версия>-<ггггммдд>.html` (`--force` — перезаписать).
- `--parse`/`--dump` сверяют типы результатов с `returns-<версия>.json` (создаётся командой `--returns`);
  `--strict` — код 1 при предупреждениях.
- Ручные варианты методов и переименования — в `Spec\overrides.json`.
- После генерации обновите константу `TgBotApiVersion` в `Source\TgBot.pas`, соберите библиотеку и прогоните
  тесты.

Не редактируйте `Gen.*.inc` вручную — изменения пропадут при следующей генерации. Полный список команд:
`TgBotGen.exe` без параметров.

## 12. Демо-проекты

Папка `Demos`, группа `Demos\Demos.groupproj` (02–04). Токен — из `TGBOT_TOKEN` (в VCL-демо можно ввести в
форме); без него консольные демо печатают подсказку и завершаются.

| Демо | Что показывает |
|---|---|
| `01_Smoke\SmokeConsole.dpr` | дымовой тест: `getMe` (sync и Async), тестовое сообщение (`TGBOT_CHAT_ID`), несколько циклов `getUpdates`; `TGBOT_API_URL`, `TGBOT_LANG=EN` |
| `02_EchoBot` | консольный бот на `TTgBot`: команды и меню, инлайн-кнопки, `Callback`/`CallbackPrefix` (листание страниц), `TextMatch`, состояние диалога, `Delivery = Worker`, `Run` |
| `03_VclBot` | VCL-форма с компонентом `TTelegramBot` из DFM: коллекция `Commands`, события, журнал, отправка `SendMessageAsync` в последний чат; `--selftest` — самопроверка без сети |
| `04_WebhookBot` | консольный webhook-бот: `TTelegramBot` (`Mode = Webhook`) + `TTgWebhookServer`; `TGBOT_PUBLIC_URL` (https), `TGBOT_PORT`; Caddy/cloudflared |
