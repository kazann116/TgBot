unit BotController;

{
  Логика VCL-демо: реакции бота на команды, сообщения и нажатия кнопок,
  запуск/остановка и отправка сообщения в последний активный чат.
  Без VCL: форма передаёт сюда события компонента TTelegramBot (Delivery =
  Main — все вызовы в главном потоке) и показывает журнал (OnLog) и
  состояние (OnChanged).
}

interface

uses
  System.SysUtils,
  System.Classes,
  TgBot,
  TgBot.Component;

type
  /// <summary>Строка журнала (главный поток).</summary>
  TBotLogEvent = procedure(Sender: TObject; const AText: string) of object;

  /// <summary>
  ///   Логика демо-бота поверх компонента TTelegramBot (компонент не
  ///   принадлежит контроллеру). Все методы — из главного потока.
  /// </summary>
  TBotController = class
  private type
    /// <summary>
    ///   Связь колбэков SendMessageAsync с контроллером: Owner = nil после
    ///   Destroy (колбэк может прийти после закрытия формы).
    /// </summary>
    TGuard = class(TInterfacedObject)
    private
      FOwner: TBotController;
    end;
  private
    FBot: TTelegramBot;
    FGuard: TGuard;
    FGuardRef: IInterface;
    FLastChatId: TTgChatId;
    FLastChatName: string;
    FMessageCount: Integer;
    FFaulted: Boolean;
    FOnLog: TBotLogEvent;
    FOnChanged: TNotifyEvent;
    procedure Log(const AText: string);
    procedure Changed;
    /// <summary>Запоминает чат входящего сообщения и считает сообщения.</summary>
    procedure RememberChat(const ACtx: ITgContext);
    function GetHasChat: Boolean;
  public
    constructor Create(ABot: TTelegramBot);
    destructor Destroy; override;
    /// <summary>
    ///   Запуск: AToken непустой — он, иначе переменная окружения TokenEnv
    ///   компонента. Нет токена или ошибка запуска — False и запись в журнал.
    /// </summary>
    function Start(const AToken: string): Boolean;
    procedure Stop;
    /// <summary>Асинхронная отправка в последний активный чат; результат — в журнал.</summary>
    function SendToLastChat(const AText: string): Boolean;
    /// <summary>Состояние для статуса: Idle, Running, Stopping, Faulted.</summary>
    function StateText: string;
    { Реакции на события компонента }
    procedure HandleStartCommand(const ACtx: ITgContext);
    procedure HandleHelpCommand(const ACtx: ITgContext);
    procedure HandleMessage(const ACtx: ITgContext);
    procedure HandleCallback(const ACtx: ITgContext);
    procedure HandleStarted;
    procedure HandleStopped(AReason: TTgStopReason);
    procedure HandleError(AError: Exception; const ACtx: ITgContext);
    procedure HandleFault(AError: Exception);
    /// <summary>Входящих сообщений (включая команды) с запуска программы.</summary>
    property MessageCount: Integer read FMessageCount;
    /// <summary>Известен чат для отправки (было входящее сообщение).</summary>
    property HasChat: Boolean read GetHasChat;
    /// <summary>Описание последнего активного чата ('' — нет).</summary>
    property LastChatName: string read FLastChatName;
    property OnLog: TBotLogEvent read FOnLog write FOnLog;
    property OnChanged: TNotifyEvent read FOnChanged write FOnChanged;
  end;

implementation

uses
  System.TypInfo;

const
  // U+1F44D и U+1F44E (суррогатные пары UTF-16).
  CThumbUp = #$D83D#$DC4D;
  CThumbDown = #$D83D#$DC4E;
  CVoteLike = 'vote:like';
  CVoteDislike = 'vote:dislike';

/// <summary>Имя пользователя для журнала и приветствия.</summary>
function DescribeUser(const AUser: ITgUser): string;
begin
  if not Assigned(AUser) then
    Exit('(неизвестно)');
  Result := Trim(AUser.FirstName + ' ' + AUser.LastName);
  if AUser.Username <> '' then
    Result := Result + ' (@' + AUser.Username + ')';
end;

{ TBotController }

constructor TBotController.Create(ABot: TTelegramBot);
begin
  inherited Create;
  FBot := ABot;
  FGuard := TGuard.Create;
  FGuardRef := FGuard;
  FGuard.FOwner := Self;
end;

destructor TBotController.Destroy;
begin
  // Колбэки, поставленные в очередь раньше, увидят Owner = nil.
  if Assigned(FGuard) then
    FGuard.FOwner := nil;
  FGuard := nil;
  FGuardRef := nil;
  inherited Destroy;
end;

procedure TBotController.Log(const AText: string);
begin
  if Assigned(FOnLog) then
    FOnLog(Self, AText);
end;

procedure TBotController.Changed;
begin
  if Assigned(FOnChanged) then
    FOnChanged(Self);
end;

function TBotController.GetHasChat: Boolean;
begin
  Result := not FLastChatId.IsEmpty;
end;

procedure TBotController.RememberChat(const ACtx: ITgContext);
begin
  if Assigned(ACtx.Message) then
    Inc(FMessageCount);
  if not ACtx.ChatId.IsEmpty then
  begin
    FLastChatId := ACtx.ChatId;
    FLastChatName := DescribeUser(ACtx.From) + ', чат ' + FLastChatId.ToString;
  end;
  Changed;
end;

function TBotController.StateText: string;
var
  LState: TTgBotState;
begin
  LState := FBot.State;
  // После отказа компонент освобождает бота (Idle) — показываем причину.
  if FFaulted and (LState = TTgBotState.Idle) then
    LState := TTgBotState.Faulted;
  Result := GetEnumName(TypeInfo(TTgBotState), Ord(LState));
end;

function TBotController.Start(const AToken: string): Boolean;
var
  LToken: string;
begin
  Result := FBot.Active;
  if Result then
    Exit;
  LToken := Trim(AToken);
  if (LToken = '') and ((FBot.TokenEnv = '') or
    (Trim(GetEnvironmentVariable(FBot.TokenEnv)) = '')) then
  begin
    Log('Токен не задан: введите его в поле или задайте переменную окружения ' +
      FBot.TokenEnv + '. Бот не запущен.');
    Changed;
    Exit;
  end;
  FFaulted := False;
  try
    // Пустой Token — компонент берёт токен из TokenEnv.
    FBot.Token := LToken;
    FBot.Active := True;
    Result := True;
  except
    // Граница UI: ошибка запуска (неверный формат токена и т.п.) — в журнал.
    on E: Exception do
      Log('Ошибка запуска: ' + E.Message);
  end;
  Changed;
end;

procedure TBotController.Stop;
begin
  FBot.Active := False;
  Changed;
end;

function TBotController.SendToLastChat(const AText: string): Boolean;
var
  LApi: TTgApi;
  LChat: TTgChatId;
  LGuard: IInterface;
begin
  Result := False;
  if Trim(AText) = '' then
  begin
    Log('Введите текст сообщения.');
    Exit;
  end;
  LApi := FBot.Api;
  if not Assigned(LApi) then
  begin
    Log('Бот не запущен.');
    Exit;
  end;
  if FLastChatId.IsEmpty then
  begin
    Log('Нет активного чата: сначала напишите боту в Telegram.');
    Exit;
  end;
  LChat := FLastChatId;
  LGuard := FGuardRef;
  Log('-> ' + LChat.ToString + ': ' + AText);
  // Колбэки — в потоке пула: в главный поток только через очередь, исключение
  // действительно лишь внутри колбэка — передаём текст.
  LApi.SendMessageAsync(LChat, AText,
    procedure(AMessage: ITgMessage)
    var
      LText: string;
    begin
      if Assigned(AMessage) then
        LText := Format('Отправлено (message_id %d)', [AMessage.MessageId])
      else
        LText := 'Отправлено';
      TThread.Queue(nil,
        procedure
        var
          LOwner: TBotController;
        begin
          LOwner := TGuard(LGuard as TObject).FOwner;
          if Assigned(LOwner) then
            LOwner.Log(LText);
        end);
    end,
    procedure(AError: Exception)
    var
      LText: string;
    begin
      LText := 'Ошибка отправки: ' + AError.ClassName + ': ' + AError.Message;
      TThread.Queue(nil,
        procedure
        var
          LOwner: TBotController;
        begin
          LOwner := TGuard(LGuard as TObject).FOwner;
          if Assigned(LOwner) then
            LOwner.Log(LText);
        end);
    end);
  Result := True;
end;

procedure TBotController.HandleStartCommand(const ACtx: ITgContext);
begin
  RememberChat(ACtx);
  Log('/start от ' + DescribeUser(ACtx.From));
  ACtx.Reply('Привет, ' + DescribeUser(ACtx.From) + '! Как вам демо?',
    TTgKeyboard.Inline.Row.Button(CThumbUp, CVoteLike).Button(CThumbDown, CVoteDislike));
end;

procedure TBotController.HandleHelpCommand(const ACtx: ITgContext);
begin
  RememberChat(ACtx);
  Log('/help от ' + DescribeUser(ACtx.From));
  ACtx.Reply('Команды: /start — приветствие с кнопками, /help — справка. ' +
    'Любое другое сообщение бот повторит.');
end;

procedure TBotController.HandleMessage(const ACtx: ITgContext);
begin
  RememberChat(ACtx);
  Log('<- ' + DescribeUser(ACtx.From) + ': ' + ACtx.Text);
  if ACtx.Text <> '' then
    ACtx.Reply('Эхо: ' + ACtx.Text)
  else
    ACtx.Reply('Получено сообщение без текста.');
end;

procedure TBotController.HandleCallback(const ACtx: ITgContext);
var
  LChoice: string;
begin
  if ACtx.Data = CVoteLike then
    LChoice := CThumbUp
  else if ACtx.Data = CVoteDislike then
    LChoice := CThumbDown
  else
  begin
    Log('Неизвестная кнопка: ' + ACtx.Data);
    ACtx.Answer('Неизвестная кнопка');
    Exit;
  end;
  Log('Кнопка ' + LChoice + ' от ' + DescribeUser(ACtx.From));
  // Сначала ответ (убирает «часики» на кнопке), затем правка сообщения.
  ACtx.Answer('Спасибо!');
  ACtx.Edit('Ваша оценка: ' + LChoice);
end;

procedure TBotController.HandleStarted;
begin
  Log('Бот запущен.');
  Changed;
end;

procedure TBotController.HandleStopped(AReason: TTgStopReason);
begin
  if AReason = TTgStopReason.Fault then
    Log('Бот остановлен из-за отказа приёма.')
  else
    Log('Бот остановлен.');
  Changed;
end;

procedure TBotController.HandleError(AError: Exception; const ACtx: ITgContext);
var
  LWhere: string;
begin
  if Assigned(ACtx) then
    LWhere := ' (обновление ' + ACtx.Kind + ')'
  else
    LWhere := '';
  Log('Ошибка' + LWhere + ': ' + AError.ClassName + ': ' + AError.Message);
  Changed;
end;

procedure TBotController.HandleFault(AError: Exception);
begin
  FFaulted := True;
  Log('Отказ приёма: ' + AError.ClassName + ': ' + AError.Message);
  Changed;
end;

end.
