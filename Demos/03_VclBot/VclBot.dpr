program VclBot;

{
  TgBot — VCL-демо: компонент TTelegramBot размещён на форме (MainForm.dfm).

  Токен — в поле ввода формы или в переменной окружения TGBOT_TOKEN.
  Команды: /start — приветствие с инлайн-кнопками, /help — справка; любое
  другое сообщение бот повторяет. Журнал формы показывает входящие
  сообщения, нажатия кнопок и ошибки; «Отправить» — сообщение в последний
  активный чат (асинхронно).

  Самопроверка без сети: VclBot.exe --selftest [файл-отчёт] — форма
  загружается из dfm, проверяются компонент и запуск без токена, в отчёт
  (по умолчанию VclBot.selftest.txt рядом с exe) пишется OK или FAIL,
  код выхода 0/1, форма закрывается сама.
}

uses
  System.SysUtils,
  System.Classes,
  Winapi.Windows,
  Vcl.Forms,
  Vcl.ExtCtrls,
  TgBot,
  TgBot.Component,
  MainForm in 'MainForm.pas' {FormMain},
  BotController in 'BotController.pas';

type
  /// <summary>Самопроверка (--selftest): после показа формы — проверки, отчёт, закрытие.</summary>
  TSelfTest = class
  private
    FTimer: TTimer;
    FReportPath: string;
    FErrors: TStringList;
    procedure Check(ACondition: Boolean; const AWhat: string);
    procedure RunChecks;
    procedure TimerTick(Sender: TObject);
  public
    constructor Create(const AReportPath: string);
    destructor Destroy; override;
  end;

constructor TSelfTest.Create(const AReportPath: string);
begin
  inherited Create;
  FReportPath := AReportPath;
  FErrors := TStringList.Create;
  FTimer := TTimer.Create(nil);
  FTimer.Interval := 1500;
  FTimer.OnTimer := TimerTick;
  FTimer.Enabled := True;
end;

destructor TSelfTest.Destroy;
begin
  FreeAndNil(FTimer);
  FreeAndNil(FErrors);
  inherited Destroy;
end;

procedure TSelfTest.Check(ACondition: Boolean; const AWhat: string);
begin
  if not ACondition then
    FErrors.Add(AWhat);
end;

procedure TSelfTest.RunChecks;
var
  LBot: TTelegramBot;
begin
  Check(Assigned(FormMain), 'FormMain не создана');
  if not Assigned(FormMain) then
    Exit;
  LBot := FormMain.TelegramBot1;
  Check(Assigned(LBot), 'TelegramBot1 не загружен из dfm');
  Check(Assigned(FormMain.Controller), 'контроллер не создан');
  if not Assigned(LBot) or not Assigned(FormMain.Controller) then
    Exit;
  // Свойства из dfm.
  Check(LBot.Delivery = TTgDelivery.Main, 'Delivery <> Main');
  Check(LBot.Token = '', 'Token не пуст');
  Check(LBot.Commands.Count = 2, 'Commands.Count <> 2');
  if LBot.Commands.Count = 2 then
  begin
    Check(LBot.Commands[0].Command = 'start', 'Commands[0] <> start');
    Check(LBot.Commands[0].Description = 'Начать', 'Commands[0].Description');
    Check(Assigned(LBot.Commands[0].OnExecute), 'Commands[0].OnExecute не назначен');
    Check(LBot.Commands[1].Command = 'help', 'Commands[1] <> help');
    Check(LBot.Commands[1].Description = 'Справка', 'Commands[1].Description');
    Check(Assigned(LBot.Commands[1].OnExecute), 'Commands[1].OnExecute не назначен');
  end;
  Check(Assigned(LBot.OnStart) and Assigned(LBot.OnStop) and Assigned(LBot.OnMessage) and
    Assigned(LBot.OnCallbackQuery) and Assigned(LBot.OnError) and Assigned(LBot.OnFault),
    'события компонента не назначены');
  Check(not LBot.Active and (LBot.State = TTgBotState.Idle), 'бот запущен после загрузки');
  // «Старт» без токена (переменная окружения процесса очищена): бот не запускается.
  FormMain.EditToken.Text := '';
  FormMain.ButtonStart.Click;
  Check(not LBot.Active and (LBot.State = TTgBotState.Idle), 'бот запустился без токена');
  Check(FormMain.Controller.StateText = 'Idle', 'StateText <> Idle');
  Check(FormMain.ButtonStart.Enabled and not FormMain.ButtonStop.Enabled and
    not FormMain.ButtonSend.Enabled, 'доступность кнопок');
  Check(FormMain.MemoLog.Lines.Count > 0, 'журнал пуст после «Старт» без токена');
end;

procedure TSelfTest.TimerTick(Sender: TObject);
var
  LReport: TStringList;
begin
  FTimer.Enabled := False;
  try
    RunChecks;
  except
    on E: Exception do
      FErrors.Add('исключение ' + E.ClassName + ': ' + E.Message);
  end;
  LReport := TStringList.Create;
  try
    if FErrors.Count = 0 then
      LReport.Add('OK')
    else
    begin
      LReport.Add('FAIL');
      LReport.AddStrings(FErrors);
    end;
    if Assigned(FormMain) then
    begin
      LReport.Add('--- журнал формы:');
      LReport.AddStrings(FormMain.MemoLog.Lines);
    end;
    LReport.SaveToFile(FReportPath, TEncoding.UTF8);
  finally
    LReport.Free;
  end;
  if FErrors.Count = 0 then
    ExitCode := 0
  else
    ExitCode := 1;
  if Assigned(FormMain) then
    FormMain.Close
  else
    Application.Terminate;
end;

/// <summary>
///   Ключ --selftest и путь отчёта (следующий параметр, иначе рядом с exe).
///   FindCmdLineSwitch не подходит: снимает только один префикс '-'.
/// </summary>
function FindSelfTestSwitch(out AReportPath: string): Boolean;
var
  I: Integer;
begin
  for I := 1 to ParamCount do
    if SameText(ParamStr(I), '--selftest') then
    begin
      if I < ParamCount then
        AReportPath := ParamStr(I + 1)
      else
        AReportPath := ChangeFileExt(ParamStr(0), '.selftest.txt');
      Exit(True);
    end;
  AReportPath := '';
  Result := False;
end;

var
  GSelfTest: TSelfTest;
  GReportPath: string;

begin
  // Демо с русским интерфейсом: тексты ошибок библиотеки — тоже по-русски (по умолчанию с 0.5.0 — английский).
  TgSetLanguage(TTgLanguage.Ru);
  ReportMemoryLeaksOnShutdown := True;
  GSelfTest := nil;
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.Title := 'TgBot VCL-демо';
  if FindSelfTestSwitch(GReportPath) then
  begin
    // Самопроверка не должна подключаться к Telegram даже при заданной переменной.
    SetEnvironmentVariable('TGBOT_TOKEN', nil);
    GSelfTest := TSelfTest.Create(GReportPath);
  end;
  try
    Application.CreateForm(TFormMain, FormMain);
    Application.Run;
  finally
    GSelfTest.Free;
  end;
end.
