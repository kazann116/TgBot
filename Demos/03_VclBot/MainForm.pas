unit MainForm;

{
  Главная форма VCL-демо: компонент TelegramBot1 (TTelegramBot) размещён в
  dfm — команды /start и /help (Commands, OnExecute), события OnStart,
  OnStop, OnMessage, OnCallbackQuery, OnError, OnFault; Delivery = Main —
  обработчики вызываются в главном потоке.

  Обработчики формы только передают события в TBotController (логика) и
  обновляют интерфейс.
}

interface

uses
  System.SysUtils,
  System.Classes,
  Vcl.Controls,
  Vcl.Forms,
  Vcl.StdCtrls,
  Vcl.ExtCtrls,
  TgBot,
  TgBot.Component,
  BotController;

type
  TFormMain = class(TForm)
    PanelTop: TPanel;
    LabelToken: TLabel;
    EditToken: TEdit;
    ButtonStart: TButton;
    ButtonStop: TButton;
    LabelState: TLabel;
    LabelCount: TLabel;
    PanelBottom: TPanel;
    LabelChat: TLabel;
    EditSend: TEdit;
    ButtonSend: TButton;
    MemoLog: TMemo;
    TelegramBot1: TTelegramBot;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure ButtonStartClick(Sender: TObject);
    procedure ButtonStopClick(Sender: TObject);
    procedure ButtonSendClick(Sender: TObject);
    procedure BotCommandStartExecute(Sender: TObject; const Ctx: ITgContext);
    procedure BotCommandHelpExecute(Sender: TObject; const Ctx: ITgContext);
    procedure TelegramBot1Start(Sender: TObject);
    procedure TelegramBot1Stop(Sender: TObject; Reason: TTgStopReason);
    procedure TelegramBot1Message(Sender: TObject; const Ctx: ITgContext);
    procedure TelegramBot1CallbackQuery(Sender: TObject; const Ctx: ITgContext);
    procedure TelegramBot1Error(Sender: TObject; E: Exception; const Ctx: ITgContext);
    procedure TelegramBot1Fault(Sender: TObject; E: Exception);
  private
    FController: TBotController;
    procedure ControllerLog(Sender: TObject; const AText: string);
    procedure ControllerChanged(Sender: TObject);
    /// <summary>Статус, счётчик, чат и доступность кнопок по состоянию бота.</summary>
    procedure UpdateStatus;
  public
    property Controller: TBotController read FController;
  end;

var
  FormMain: TFormMain;

implementation

{$R *.dfm}

const
  // Журнал не растёт бесконечно: старые строки удаляются.
  CMaxLogLines = 1000;

procedure TFormMain.FormCreate(Sender: TObject);
begin
  FController := TBotController.Create(TelegramBot1);
  FController.OnLog := ControllerLog;
  FController.OnChanged := ControllerChanged;
  UpdateStatus;
end;

procedure TFormMain.FormDestroy(Sender: TObject);
begin
  // Остановка до освобождения контроллера: OnStop ещё дойдёт до него.
  TelegramBot1.Active := False;
  FreeAndNil(FController);
end;

procedure TFormMain.ControllerLog(Sender: TObject; const AText: string);
begin
  MemoLog.Lines.BeginUpdate;
  try
    while MemoLog.Lines.Count >= CMaxLogLines do
      MemoLog.Lines.Delete(0);
    MemoLog.Lines.Add(FormatDateTime('hh:nn:ss', Now) + '  ' + AText);
  finally
    MemoLog.Lines.EndUpdate;
  end;
end;

procedure TFormMain.ControllerChanged(Sender: TObject);
begin
  UpdateStatus;
end;

procedure TFormMain.UpdateStatus;
var
  LActive: Boolean;
begin
  if not Assigned(FController) then
    Exit;
  LActive := TelegramBot1.Active;
  LabelState.Caption := 'Состояние: ' + FController.StateText;
  LabelCount.Caption := 'Сообщений: ' + IntToStr(FController.MessageCount);
  if FController.HasChat then
    LabelChat.Caption := 'Последний чат: ' + FController.LastChatName
  else
    LabelChat.Caption := 'Последний чат: нет (напишите боту)';
  ButtonStart.Enabled := not LActive;
  ButtonStop.Enabled := LActive;
  EditToken.Enabled := not LActive;
  ButtonSend.Enabled := LActive and FController.HasChat;
end;

procedure TFormMain.ButtonStartClick(Sender: TObject);
begin
  FController.Start(EditToken.Text);
end;

procedure TFormMain.ButtonStopClick(Sender: TObject);
begin
  FController.Stop;
end;

procedure TFormMain.ButtonSendClick(Sender: TObject);
begin
  if FController.SendToLastChat(EditSend.Text) then
    EditSend.Clear;
end;

procedure TFormMain.BotCommandStartExecute(Sender: TObject; const Ctx: ITgContext);
begin
  if Assigned(FController) then
    FController.HandleStartCommand(Ctx);
end;

procedure TFormMain.BotCommandHelpExecute(Sender: TObject; const Ctx: ITgContext);
begin
  if Assigned(FController) then
    FController.HandleHelpCommand(Ctx);
end;

procedure TFormMain.TelegramBot1Start(Sender: TObject);
begin
  if Assigned(FController) then
    FController.HandleStarted;
end;

procedure TFormMain.TelegramBot1Stop(Sender: TObject; Reason: TTgStopReason);
begin
  if Assigned(FController) then
    FController.HandleStopped(Reason);
end;

procedure TFormMain.TelegramBot1Message(Sender: TObject; const Ctx: ITgContext);
begin
  if Assigned(FController) then
    FController.HandleMessage(Ctx);
end;

procedure TFormMain.TelegramBot1CallbackQuery(Sender: TObject; const Ctx: ITgContext);
begin
  if Assigned(FController) then
    FController.HandleCallback(Ctx);
end;

procedure TFormMain.TelegramBot1Error(Sender: TObject; E: Exception; const Ctx: ITgContext);
begin
  if Assigned(FController) then
    FController.HandleError(E, Ctx);
end;

procedure TFormMain.TelegramBot1Fault(Sender: TObject; E: Exception);
begin
  if Assigned(FController) then
    FController.HandleFault(E);
end;

end.
