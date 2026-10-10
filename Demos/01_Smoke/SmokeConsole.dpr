program SmokeConsole;

{
  TgBot — дымовой тест библиотеки (модуль TgBot, сгенерированный Bot API).

  Переменные окружения:
    TGBOT_TOKEN            — токен бота (без него программа печатает подсказку и выходит с кодом 0);
    TGBOT_CHAT_ID          — (необязательно) чат для тестового сообщения: число или @username;
    TGBOT_POLL_ITERATIONS  — (необязательно) число циклов getUpdates (по умолчанию 3);
    TGBOT_API_URL          — (необязательно) адрес Local Bot API server;
    TGBOT_LANG             — (необязательно) EN — сообщения библиотеки на английском.

  Сценарий: getMe (синхронно и асинхронно) -> тестовое сообщение (если задан чат)
  -> эхо-цикл long polling (timeout 10 с) -> подтверждение обработанных обновлений.
  Ctrl+C (Windows) завершает цикл после текущего запроса getUpdates.
}

{$APPTYPE CONSOLE}

uses
  System.SysUtils,
  System.SyncObjs,
  System.Threading,
{$IFDEF MSWINDOWS}
  Winapi.Windows,
{$ENDIF}
  TgBot;

const
  CPollTimeoutSec = 10;
  CDefaultIterations = 3;

var
  GStopRequested: Integer = 0;

{$IFDEF MSWINDOWS}
function ConsoleCtrlHandler(ACtrlType: DWORD): BOOL; stdcall;
begin
  // Обработчик вызывается в отдельном потоке: только выставляем флаг,
  // сообщение печатает основной цикл.
  Result := (ACtrlType = CTRL_C_EVENT) or (ACtrlType = CTRL_BREAK_EVENT);
  if Result then
    TInterlocked.Exchange(GStopRequested, 1);
end;

procedure SetupConsole;
begin
  SetConsoleOutputCP(CP_UTF8);
  SetTextCodePage(Output, CP_UTF8);
  SetConsoleCtrlHandler(@ConsoleCtrlHandler, True);
end;
{$ELSE}
procedure SetupConsole;
begin
  // В POSIX консоль работает в UTF-8; Ctrl+C завершает процесс штатно.
end;
{$ENDIF}

function StopRequested: Boolean;
begin
  Result := TInterlocked.CompareExchange(GStopRequested, 0, 0) <> 0;
end;

function DescribeUser(const AUser: ITgUser): string;
begin
  if not Assigned(AUser) then
    Exit('(неизвестно)');
  Result := Trim(AUser.FirstName + ' ' + AUser.LastName);
  if AUser.Username <> '' then
    Result := Result + ' (@' + AUser.Username + ')';
end;

procedure PrintHint;
begin
  Writeln('TgBot SmokeConsole ', TgBotVersion);
  Writeln('Переменная окружения TGBOT_TOKEN не задана — тест пропущен.');
  Writeln('Пример (Windows):  set TGBOT_TOKEN=123456:ABC...');
  Writeln('Пример (Linux):    export TGBOT_TOKEN=123456:ABC...');
  Writeln('Необязательно: TGBOT_CHAT_ID, TGBOT_POLL_ITERATIONS, TGBOT_API_URL, TGBOT_LANG=EN');
end;

procedure TestGetMe(AApi: TTgApi);
var
  LMe: ITgUser;
  LTask: ITask;
begin
  LMe := AApi.GetMe;
  Writeln('getMe: ', DescribeUser(LMe), ', id = ', LMe.Id);

  LTask := AApi.GetMeAsync(
    procedure(AUser: ITgUser)
    begin
      Writeln('getMe (async): ', DescribeUser(AUser));
    end,
    procedure(AError: Exception)
    begin
      Writeln('getMe (async) ошибка: ', AError.Message);
    end);
  LTask.Wait;
end;

procedure TestSendMessage(AApi: TTgApi; const AChatId: TTgChatId);
var
  LMessage: ITgMessage;
  LError: TTgErrorInfo;
  LOptions: TTgSendMessageOptions;
begin
  LOptions := Default(TTgSendMessageOptions);
  LOptions.ParseMode := TTgParseMode.Html;
  LOptions.DisableNotification := True;
  if AApi.TrySendMessage(AChatId,
    '<b>TgBot ' + TgBotVersion + '</b>: тестовое сообщение SmokeConsole',
    LOptions, LMessage, LError) then
    Writeln('sendMessage: отправлено, message_id = ', LMessage.MessageId,
      ', чат = ', LMessage.Chat.Id)
  else
    Writeln('sendMessage: ошибка — ', LError.Message);
end;

procedure RunEchoLoop(AApi: TTgApi; AIterations: Integer);
var
  LIteration: Integer;
  LOffset: Int64;
  LUpdates: TArray<ITgUpdate>;
  LUpdate: ITgUpdate;
  LMessage, LSent: ITgMessage;
  LPoll: TTgGetUpdatesOptions;
  LOptions: TTgSendMessageOptions;
  LError: TTgErrorInfo;
begin
  LOffset := 0;
  for LIteration := 1 to AIterations do
  begin
    if StopRequested then
    begin
      Writeln('Получен Ctrl+C — завершение цикла.');
      Break;
    end;
    Writeln(Format('getUpdates: итерация %d из %d (timeout %d с)... напишите боту',
      [LIteration, AIterations, CPollTimeoutSec]));
    LPoll := Default(TTgGetUpdatesOptions);
    if LOffset <> 0 then
      LPoll.Offset := LOffset;
    LPoll.Limit := 100;
    LPoll.Timeout := CPollTimeoutSec;
    // allowed_updates сервер запоминает до следующего getUpdates/setWebhook,
    // в том числе для других программ с этим токеном. Узкий фильтр
    // (например, только message) отключил бы им нажатия кнопок, поэтому
    // передаём [] — все типы, кроме chat_member и реакций; лишние
    // обновления цикл ниже пропускает.
    LPoll.AllowedUpdates := [];
    LUpdates := AApi.GetUpdates(LPoll);
    for LUpdate in LUpdates do
    begin
      LOffset := LUpdate.UpdateId + 1;
      LMessage := LUpdate.Message;
      if not Assigned(LMessage) or (LMessage.Text = '') then
        Continue;
      Writeln('  <- ', DescribeUser(LMessage.From), ': ', LMessage.Text);
      LOptions := Default(TTgSendMessageOptions);
      LOptions.ReplyParameters := TTgReplyParameters.Create.WithMessageId(LMessage.MessageId);
      if AApi.TrySendMessage(LMessage.Chat.Id, 'Эхо: ' + LMessage.Text, LOptions,
        LSent, LError) then
        Writeln('  -> эхо отправлено, message_id = ', LSent.MessageId)
      else
        Writeln('  -> ошибка отправки: ', LError.Message);
    end;
  end;
  // Подтверждаем обработанные обновления, чтобы не получить их повторно.
  if LOffset <> 0 then
  begin
    LPoll := Default(TTgGetUpdatesOptions);
    LPoll.Offset := LOffset;
    LPoll.Limit := 1;
    AApi.GetUpdates(LPoll);
  end;
end;

procedure Run;
var
  LToken, LChat, LApiUrl: string;
  LIterations: Integer;
  LSettings: TTgHttpSettings;
  LApi: TTgApi;
begin
  LToken := Trim(GetEnvironmentVariable('TGBOT_TOKEN'));
  if LToken = '' then
  begin
    PrintHint;
    Exit;
  end;
  if SameText(GetEnvironmentVariable('TGBOT_LANG'), 'EN') then
    TgSetLanguage(TTgLanguage.En);
  LChat := Trim(GetEnvironmentVariable('TGBOT_CHAT_ID'));
  LIterations := StrToIntDef(GetEnvironmentVariable('TGBOT_POLL_ITERATIONS'),
    CDefaultIterations);

  LSettings := TTgHttpSettings.Create(LToken);
  LApiUrl := Trim(GetEnvironmentVariable('TGBOT_API_URL'));
  if LApiUrl <> '' then
    LSettings.ApiUrl := LApiUrl;

  Writeln('TgBot SmokeConsole ', TgBotVersion, ', сервер: ', LSettings.ApiUrl);
  LApi := TTgApi.Create(LSettings);
  try
    TestGetMe(LApi);
    if LChat <> '' then
      TestSendMessage(LApi, LChat);
    RunEchoLoop(LApi, LIterations);
    Writeln('Готово.');
  finally
    LApi.Free;
  end;
end;

begin
{$IFDEF MSWINDOWS}
  // Демо: отчёт об утечках памяти при завершении.
  ReportMemoryLeaksOnShutdown := True;
{$ENDIF}
  SetupConsole;
  try
    Run;
  except
    on E: Exception do
    begin
      Writeln(E.ClassName, ': ', E.Message);
      ExitCode := 1;
    end;
  end;
end.
