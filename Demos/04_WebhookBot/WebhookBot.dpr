program WebhookBot;

(*
  TgBot — учебный консольный бот в режиме webhook (Windows и Linux):
  компонент TTelegramBot (Mode = Webhook) + встроенный HTTP-сервер
  TTgWebhookServer (Indy). Компоненты создаются в коде, обработчики —
  методы класса THandlers (события of object, как в форме).

  Переменные окружения:
    TGBOT_TOKEN      — токен бота от @BotFather;
    TGBOT_PUBLIC_URL — внешний HTTPS-адрес обратного прокси, например
                       https://bots.example.com (без него — подсказка и выход 0);
    TGBOT_PORT       — локальный порт сервера (по умолчанию 8080).

  Сервер слушает только 127.0.0.1 и принимает обычный HTTP: HTTPS для
  Telegram обеспечивает обратный прокси на той же машине. Адрес бота для
  setWebhook = TGBOT_PUBLIC_URL + Webhook.Path (здесь '/tg/demo').

  Быстрый тест без домена — временный туннель Cloudflare (адрес вида
  https://xxxx.trycloudflare.com печатается при запуске):
    cloudflared tunnel --url http://localhost:8080

  Постоянный сервер — Caddy (сам получает сертификат Let's Encrypt), Caddyfile:
    bots.example.com {
      reverse_proxy 127.0.0.1:8080
    }

  Остановка — Ctrl+C (Windows) или SIGINT/SIGTERM (Linux); при остановке бот
  удаляет webhook (Webhook.DeleteOnStop), чтобы токен можно было снова
  использовать в режиме long polling (например, в демо EchoBot).
*)

{$APPTYPE CONSOLE}

uses
{$IFDEF MSWINDOWS}
  Winapi.Windows,
{$ENDIF}
  System.SysUtils,
  System.Classes,
  TgBot,
  TgBot.Component,
  TgBot.Webhook;

type
  /// <summary>Обработчики событий компонентов (вызываются в главном потоке, кроме сервера).</summary>
  THandlers = class
  private
    FFaulted: Boolean;
    FMessages: Integer;
  public
    procedure BotStart(Sender: TObject);
    procedure CmdStart(Sender: TObject; const Ctx: ITgContext);
    procedure CmdHelp(Sender: TObject; const Ctx: ITgContext);
    procedure BotMessage(Sender: TObject; const Ctx: ITgContext);
    procedure BotCallback(Sender: TObject; const Ctx: ITgContext);
    procedure BotError(Sender: TObject; E: Exception; const Ctx: ITgContext);
    procedure BotFault(Sender: TObject; E: Exception);
    procedure ServerRequest(Sender: TObject; const AMethod, APath: string; AStatus: Integer);
    procedure ServerError(Sender: TObject; E: Exception);
    /// <summary>Бот отказал (неверный токен, ошибка setWebhook…): пора выходить.</summary>
    property Faulted: Boolean read FFaulted;
  end;

procedure Log(const AText: string);
var
  LLine: string;
begin
  LLine := FormatDateTime('hh:nn:ss', Now) + '  ' + AText;
  // События сервера приходят в потоках Indy: печатаем через очередь
  // главного потока (её разбирает CheckSynchronize в цикле ожидания).
  if TThread.CurrentThread.ThreadID = MainThreadID then
    Writeln(LLine)
  else
    TThread.Queue(nil,
      procedure
      begin
        Writeln(LLine);
      end);
end;

{ THandlers }

procedure THandlers.BotStart(Sender: TObject);
begin
  Log('Бот запущен, webhook: ' + TTelegramBot(Sender).Webhook.EffectiveUrl);
end;

procedure THandlers.CmdStart(Sender: TObject; const Ctx: ITgContext);
begin
  Ctx.Reply('Привет! Я работаю через webhook. Напишите что-нибудь или нажмите кнопку:',
    TTgKeyboard.Inline.Button('👍', 'like').Button('👎', 'dislike'));
end;

procedure THandlers.CmdHelp(Sender: TObject; const Ctx: ITgContext);
begin
  Ctx.Reply('/start — приветствие и кнопки' + sLineBreak + '/help — эта справка');
end;

procedure THandlers.BotMessage(Sender: TObject; const Ctx: ITgContext);
begin
  if Ctx.Text = '' then
    Exit;
  // Delivery = Main (по умолчанию у компонента): все обработчики — в главном
  // потоке по очереди, поэтому поле меняется без блокировок.
  Inc(FMessages);
  Log(Format('Сообщение №%d, чат %s: %s', [FMessages, Ctx.ChatId.ToString, Ctx.Text]));
  Ctx.Reply(Format('Эхо №%d: %s', [FMessages, Ctx.Text]));
end;

procedure THandlers.BotCallback(Sender: TObject; const Ctx: ITgContext);
begin
  if Ctx.Data = 'like' then
  begin
    Ctx.Answer('Спасибо!');
    Ctx.Edit('Вам понравилось 👍');
  end
  else if Ctx.Data = 'dislike' then
  begin
    Ctx.Answer('Учтём');
    Ctx.Edit('Вам не понравилось 👎');
  end;
end;

procedure THandlers.BotError(Sender: TObject; E: Exception; const Ctx: ITgContext);
begin
  if Assigned(Ctx) then
    Log('Ошибка обработчика (' + Ctx.Kind + '): ' + E.ClassName + ': ' + E.Message)
  else
    Log('Ошибка бота: ' + E.ClassName + ': ' + E.Message);
end;

procedure THandlers.BotFault(Sender: TObject; E: Exception);
begin
  Log('Бот остановлен из-за ошибки: ' + E.Message);
  FFaulted := True;
end;

procedure THandlers.ServerRequest(Sender: TObject; const AMethod, APath: string;
  AStatus: Integer);
begin
  Log(Format('HTTP %s %s -> %d', [AMethod, APath, AStatus]));
end;

procedure THandlers.ServerError(Sender: TObject; E: Exception);
begin
  Log('Ошибка HTTP-сервера: ' + E.ClassName + ': ' + E.Message);
end;

procedure PrintHint(const AMissing: string);
begin
  Writeln('TgBot WebhookBot ', TgBotVersion);
  Writeln('Переменная окружения ', AMissing, ' не задана.');
  Writeln('Нужны: TGBOT_TOKEN, TGBOT_PUBLIC_URL (https://...), необязательно TGBOT_PORT (8080).');
  Writeln('Быстрый тест: cloudflared tunnel --url http://localhost:8080');
  Writeln('  и TGBOT_PUBLIC_URL = выданный адрес https://xxxx.trycloudflare.com');
  Writeln('Постоянно: Caddy с reverse_proxy 127.0.0.1:8080 (пример — в начале WebhookBot.dpr).');
end;

var
  LPublicUrl: string;
  LPort: Integer;
  LHandlers: THandlers;
  LServer: TTgWebhookServer;
  LBot: TTelegramBot;
  LCommand: TTgCommandItem;
begin
{$IFDEF MSWINDOWS}
  SetConsoleOutputCP(CP_UTF8);
  SetTextCodePage(Output, CP_UTF8);
{$ENDIF}
  // Компонент сам читает токен из TokenEnv (по умолчанию TGBOT_TOKEN);
  // здесь проверяем заранее только ради понятной подсказки.
  if Trim(GetEnvironmentVariable('TGBOT_TOKEN')) = '' then
  begin
    PrintHint('TGBOT_TOKEN');
    Exit; // ExitCode = 0
  end;
  LPublicUrl := Trim(GetEnvironmentVariable('TGBOT_PUBLIC_URL'));
  if LPublicUrl = '' then
  begin
    PrintHint('TGBOT_PUBLIC_URL');
    Exit;
  end;
  if not LPublicUrl.StartsWith('https://', True) then
  begin
    Writeln('TGBOT_PUBLIC_URL должен начинаться с https:// — Telegram не шлёт webhook по HTTP.');
    ExitCode := 1;
    Exit;
  end;
  LPort := StrToIntDef(GetEnvironmentVariable('TGBOT_PORT'), TgWebhookDefaultPort);

  TTgShutdownSignal.Install; // Ctrl+C / SIGTERM только выставляют флаг
  try
    LHandlers := THandlers.Create;
    LServer := nil;
    LBot := nil;
    try
      try
        LServer := TTgWebhookServer.Create(nil);
        LServer.Port := LPort;
        LServer.PublicUrl := LPublicUrl;
        LServer.OnRequest := LHandlers.ServerRequest;
        LServer.OnError := LHandlers.ServerError;
        LServer.Active := True; // занятый порт — исключение здесь

        LBot := TTelegramBot.Create(nil);
        LBot.Mode := TTgReceiveMode.Webhook;
        LBot.Webhook.Server := LServer;
        LBot.Webhook.Path := '/tg/demo';
        LBot.Webhook.DeleteOnStop := True;
        // SecretToken не задан: при каждом запуске генерируется случайный.
        // Команды — элементы коллекции, как в Object Inspector.
        LCommand := LBot.Commands.Add;
        LCommand.Command := 'start';
        LCommand.Description := 'Начать';
        LCommand.OnExecute := LHandlers.CmdStart;
        LCommand := LBot.Commands.Add;
        LCommand.Command := 'help';
        LCommand.Description := 'Список команд';
        LCommand.OnExecute := LHandlers.CmdHelp;
        LBot.OnStart := LHandlers.BotStart;
        LBot.OnMessage := LHandlers.BotMessage;
        LBot.OnCallbackQuery := LHandlers.BotCallback;
        LBot.OnError := LHandlers.BotError;
        LBot.OnFault := LHandlers.BotFault;
        LBot.Active := True; // setWebhook выполняется в фоне

        Writeln(Format('Сервер слушает 127.0.0.1:%d. Остановка — Ctrl+C.', [LServer.BoundPort]));
        // Delivery = Main: события бота приходят через очередь главного
        // потока — разбираем её, пока не придёт сигнал или отказ бота.
        while not TTgShutdownSignal.Requested and not LHandlers.Faulted do
          CheckSynchronize(100);
        if LHandlers.Faulted then
          ExitCode := 1;

        LBot.Active := False; // deleteWebhook (DeleteOnStop)
        LServer.Active := False;
        CheckSynchronize; // допечатать журнал из очереди
        Writeln('Бот остановлен.');
      except
        on E: Exception do
        begin
          Writeln('Ошибка: ', E.ClassName, ': ', E.Message);
          ExitCode := 1;
        end;
      end;
    finally
      LBot.Free;    // бот — раньше сервера: снимает регистрацию пути
      LServer.Free;
      LHandlers.Free;
    end;
  finally
    TTgShutdownSignal.NotifyStopped; // закрытие окна консоли ждёт этого
    TTgShutdownSignal.Uninstall;
  end;
end.
