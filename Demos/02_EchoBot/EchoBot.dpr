program EchoBot;

{
  TgBot — учебный консольный бот на TTgBot (long polling, Windows и Linux).

  Переменные окружения:
    TGBOT_TOKEN — токен бота от @BotFather (без него программа печатает
                  подсказку и выходит с кодом 0).

  Что показывает демо:
    /start   — приветствие (HTML) и инлайн-кнопки;
    /help    — список команд;
    /counter — счётчик нажатий в состоянии диалога (Ctx.State);
    кнопки «👍/👎» — Callback: всплывающий ответ (Answer) и правка сообщения (Edit);
    кнопки «◀ ▶» — CallbackPrefix('page:'): листание страниц 1..3;
    «заказ 42» — TextMatch: номер заказа берётся из первой группы (Ctx.Args);
    любой другой текст — OnMessage: эхо с общим счётчиком.

  Delivery = Worker: обработчики идут в потоках диспетчера (один чат — по
  порядку, разные — параллельно), поэтому вывод в консоль под блокировкой,
  а общий счётчик атомарный. Остановка — Ctrl+C или SIGINT/SIGTERM.
}

{$APPTYPE CONSOLE}

uses
{$IFDEF MSWINDOWS}
  Winapi.Windows,
{$ENDIF}
  System.SysUtils,
  TgBot;

const
  CPageCount = 3;

var
  GLogLock: TObject;
  GEchoCount: Integer = 0;

procedure Log(const AText: string);
begin
  // Writeln из нескольких потоков без блокировки может перемешать строки.
  TMonitor.Enter(GLogLock);
  try
    Writeln(FormatDateTime('hh:nn:ss', Now), '  ', AText);
  finally
    TMonitor.Exit(GLogLock);
  end;
end;

function PageText(APage: Integer): string;
begin
  Result := Format('Страница %d из %d', [APage, CPageCount]);
end;

function PageKeyboard(APage: Integer): TTgInlineKeyboardBuilder;
begin
  // Кнопки «◀» и «▶» — только там, где есть куда листать: правка сообщения
  // тем же текстом и клавиатурой вернула бы ошибку «message is not modified».
  Result := TTgKeyboard.Inline;
  if APage > 1 then
    Result := Result.Button('◀', 'page:' + IntToStr(APage - 1));
  if APage < CPageCount then
    Result := Result.Button('▶', 'page:' + IntToStr(APage + 1));
end;

procedure SetupBot(ABot: TTgBot);
begin
  ABot.Delivery := TTgDelivery.Worker;

  // Команды с описанием попадают в меню бота (setMyCommands при запуске).
  ABot.Command('start', 'Начать',
    procedure(ACtx: ITgContext)
    begin
      // В HTML-текст не вставляйте данные пользователя без экранирования.
      ACtx.ReplyHtml('<b>Привет!</b> Я эхо-бот на TgBot.' + sLineBreak +
        'Напишите что-нибудь или нажмите кнопку:',
        TTgKeyboard.Inline
          .Row.Button('👍', 'like').Button('👎', 'dislike')
          .Row.Button('Листать страницы', 'page:1'));
    end)
  .Command('help', 'Список команд',
    procedure(ACtx: ITgContext)
    begin
      ACtx.Reply('/start — приветствие и кнопки' + sLineBreak +
        '/help — эта справка' + sLineBreak +
        '/counter — счётчик (хранится в состоянии диалога)' + sLineBreak +
        '«заказ 42» — пример разбора текста регулярным выражением');
    end)
  .Command('counter', 'Счётчик',
    procedure(ACtx: ITgContext)
    var
      LValue: Integer;
    begin
      // Состояние — строки по ключу «чат:пользователь» (в памяти процесса).
      LValue := StrToIntDef(ACtx.State['counter'], 0) + 1;
      ACtx.State['counter'] := IntToStr(LValue);
      ACtx.Reply(Format('Счётчик: %d', [LValue]));
    end)
  // Точное совпадение callback data.
  .Callback('like',
    procedure(ACtx: ITgContext)
    begin
      ACtx.Answer('Спасибо!');
      ACtx.Edit('Вам понравилось 👍');
    end)
  .Callback('dislike',
    procedure(ACtx: ITgContext)
    begin
      ACtx.Answer('Учтём', True); // True — окно вместо всплывающей подсказки
      ACtx.Edit('Вам не понравилось 👎');
    end)
  // Префикс: для 'page:2' Ctx.Args = '2'.
  .CallbackPrefix('page:',
    procedure(ACtx: ITgContext)
    var
      LPage: Integer;
    begin
      LPage := StrToIntDef(ACtx.Args, 1);
      if (LPage < 1) or (LPage > CPageCount) then
        LPage := 1;
      ACtx.Answer;
      ACtx.Edit(PageText(LPage), PageKeyboard(LPage));
    end)
  // Регулярное выражение: Ctx.Args — первая группа.
  .TextMatch('^заказ (\d+)$',
    procedure(ACtx: ITgContext)
    begin
      ACtx.Reply('Заказ №' + ACtx.Args + ' принят в обработку.');
    end);

  // Всё, что не подошло правилам выше.
  ABot.OnMessage :=
    procedure(ACtx: ITgContext)
    var
      LNumber: Integer;
    begin
      if ACtx.Text = '' then
        Exit; // стикер, фото без подписи и т.п.
      LNumber := AtomicIncrement(GEchoCount);
      Log(Format('Эхо №%d, чат %s: %s', [LNumber, ACtx.ChatId.ToString, ACtx.Text]));
      ACtx.Reply(Format('Эхо №%d: %s', [LNumber, ACtx.Text]));
    end;

  // Ошибки обработчиков (ACtx задан) и приёма (ACtx = nil). Токен в тексты
  // исключений библиотеки не попадает.
  ABot.OnError :=
    procedure(AError: Exception; ACtx: ITgContext)
    begin
      if Assigned(ACtx) then
        Log('Ошибка обработчика (' + ACtx.Kind + '): ' + AError.ClassName + ': ' + AError.Message)
      else
        Log('Ошибка приёма: ' + AError.ClassName + ': ' + AError.Message);
    end;

  // Неустранимая ошибка (неверный токен, webhook активен…): Run вернёт False.
  ABot.OnFault :=
    procedure(AError: Exception)
    begin
      Log('Бот остановлен из-за ошибки: ' + AError.Message);
    end;
end;

var
  LToken: string;
  LBot: TTgBot;
begin
  // Демо с русским интерфейсом: тексты ошибок библиотеки — тоже по-русски (по умолчанию с 0.5.0 — английский).
  TgSetLanguage(TTgLanguage.Ru);
{$IFDEF MSWINDOWS}
  SetConsoleOutputCP(CP_UTF8);
  SetTextCodePage(Output, CP_UTF8);
{$ENDIF}
  LToken := Trim(GetEnvironmentVariable('TGBOT_TOKEN'));
  if LToken = '' then
  begin
    Writeln('TgBot EchoBot ', TgBotVersion);
    Writeln('Переменная окружения TGBOT_TOKEN не задана.');
    Writeln('Пример (Windows):  set TGBOT_TOKEN=123456:ABC...');
    Writeln('Пример (Linux):    export TGBOT_TOKEN=123456:ABC...');
    Exit; // ExitCode = 0
  end;

  GLogLock := TObject.Create;
  try
    try
      LBot := TTgBot.Create(LToken);
      try
        SetupBot(LBot);
        Log('Бот запущен. Остановка — Ctrl+C.');
        // Run блокирует до Ctrl+C/SIGTERM или неустранимой ошибки.
        if not LBot.Run then
          ExitCode := 1;
        Log('Бот остановлен.');
      finally
        LBot.Free;
      end;
    except
      on E: Exception do
      begin
        Log('Ошибка: ' + E.ClassName + ': ' + E.Message);
        ExitCode := 1;
      end;
    end;
  finally
    GLogLock.Free;
  end;
end.
