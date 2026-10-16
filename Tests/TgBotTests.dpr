program TgBotTests;

{
  TgBot — офлайн-тесты библиотеки (без сети и без DUnitX).

  Подменный транспорт (TFakeTransport) возвращает заготовленные ответы и
  запоминает параметры последнего вызова. Итог — число тестов/проверок;
  код выхода 1, если хотя бы одна проверка не прошла. Утечки памяти
  выводятся отчётом менеджера памяти при завершении (Windows).

  Сборка (из папки Tests): dcc64 -B -U..\Source TgBotTests.dpr
  С -DTGBOT_TESTHOOKS тесты владения дополнительно проверяют счётчики живых
  ядер и задач подготовки (хуки TgBot.Bot.Core); без символа эти проверки
  пропускаются, остаются косвенные (транспорт отпущен) и отчёт об утечках.
}

{$APPTYPE CONSOLE}

uses
  System.SysUtils,
  System.Classes,
  System.IOUtils,
  System.Math,
  System.SyncObjs,
  System.Generics.Collections,
  System.Diagnostics,
  System.JSON,
  System.Threading,
  System.TypInfo,
{$IFDEF MSWINDOWS}
  Winapi.Windows,
  Winapi.Winsock2,
{$ENDIF}
  System.Net.URLClient,
  System.Net.HttpClient,
  // Клиент для сырых HTTP-запросов к TTgWebhookServer (тесты 6D2).
  IdTCPClient,
  // Токены отмены, пул и транспорт — напрямую из модулей ядра (в фасаде их пока нет).
  TgBot.Base,
  TgBot.Http,
  TgBot.Core,
  // Тест текстов (5b-1): TTgJsonDto, TgUpdatesText, TgRouterText и пары
  // TgBot.Consts — служебные модули; до фасада, чтобы не перекрывать его имена.
  TgBot.Dto,
  TgBot.Updates,
  TgBot.Router,
  TgBot.Consts,
  // Владение, фаза 3: служебные ITgApiOwner/ITgRoutableContext (проверки Supports).
  TgBot.Context,
{$IFDEF TGBOT_TESTHOOKS}
  // Счётчики живых ядер и задач подготовки (TgTestLiveBotCores/TgTestLiveStartJobs).
  TgBot.Bot.Core,
{$ENDIF}
  TgBot,
  TgBot.Component,
  TgBot.Webhook;

type
  /// <summary>
  ///   Строка клавиатуры. Вложенный литерал [[A, B]] компилятор трактует как
  ///   множество, поэтому строки создаются через TArray&lt;T&gt;.Create.
  /// </summary>
  TButtonRow = TArray<ITgInlineKeyboardButton>;

  /// <summary>Обработчик вызова подменного транспорта.</summary>
  TFakeHandler = reference to function(const AMethod: string; AParams: TTgParams): TJSONValue;

  /// <summary>
  ///   Подменный транспорт: ответы — из обработчика, параметры запоминаются.
  ///   ExecuteEx делает токен операции окружающим (TTgCancelScope.Current)
  ///   на время вызова обработчика.
  ///   Вызовы идут из нескольких потоков (Async, поток приёма, обработчики):
  ///   поля последнего вызова — под FLock (чтение и запись), счётчики —
  ///   TInterlocked. Неатомарное присваивание строки/массива из двух потоков
  ///   теряет одно значение без освобождения — утечка (фаза 6A1).
  /// </summary>
  TFakeTransport = class(TInterfacedObject, ITgTransport, ITgCancellableTransport)
  private
    FLock: TCriticalSection;
    FHandler: TFakeHandler;
    FCalls: Integer;
    FExCalls: Integer;
    FCancelCalls: Integer;
    FCancelled: Boolean;
    FLastMethod: string;
    FLastJson: string;
    FLastFileNames: TArray<string>;
    FLastFilePaths: TArray<string>;
    FLastThreadId: TThreadID;
    function GetLastMethod: string;
    function GetLastJson: string;
    function GetLastFileNames: TArray<string>;
    function GetLastFilePaths: TArray<string>;
    function GetLastThreadId: TThreadID;
  public
    constructor Create(const AHandler: TFakeHandler);
    destructor Destroy; override;
    function Execute(const AMethod: string; AParams: TTgParams): TJSONValue;
    procedure DownloadFile(const AFilePath: string; ADest: TStream);
    function ExecuteEx(const AMethod: string; AParams: TTgParams;
      const ACancel: ITgCancellation): TJSONValue;
    procedure DownloadFileEx(const AFilePath: string; ADest: TStream;
      const ACancel: ITgCancellation);
    procedure Cancel;
    procedure ResetCancel;
    function IsCancelled: Boolean;
    property Calls: Integer read FCalls;
    property ExCalls: Integer read FExCalls;
    property CancelCalls: Integer read FCancelCalls;
    property LastMethod: string read GetLastMethod;
    property LastJson: string read GetLastJson;
    property LastFileNames: TArray<string> read GetLastFileNames;
    property LastFilePaths: TArray<string> read GetLastFilePaths;
    property LastThreadId: TThreadID read GetLastThreadId;
  end;

  /// <summary>Транспорт без поддержки токенов (только ITgTransport).</summary>
  TPlainTransport = class(TInterfacedObject, ITgTransport)
  private
    FHandler: TFakeHandler;
    FCalls: Integer;
  public
    constructor Create(const AHandler: TFakeHandler);
    function Execute(const AMethod: string; AParams: TTgParams): TJSONValue;
    procedure DownloadFile(const AFilePath: string; ADest: TStream);
    procedure Cancel;
    procedure ResetCancel;
    function IsCancelled: Boolean;
    property Calls: Integer read FCalls;
  end;

  /// <summary>Заготовленный HTTP-ответ для TStubHttpTransport.</summary>
  TStubResponder = reference to function(const AMethod: string): TTgHttpResponse;

  /// <summary>
  ///   Настоящий TTgHttpTransport (лимитёр, retry_after, разбор ответа) без
  ///   сети: SendRequest подменён и возвращает заготовку.
  /// </summary>
  TStubHttpTransport = class(TTgHttpTransport)
  private
    FResponder: TStubResponder;
    FSends: Integer;
    FSawToken: Boolean;
  protected
    function SendRequest(const AMethod: string; AParams: TTgParams): TTgHttpResponse; override;
  public
    constructor Create(const ASettings: TTgHttpSettings; const AResponder: TStubResponder);
    property Sends: Integer read FSends;
    property SawToken: Boolean read FSawToken;
  end;

const
  CMessageJson =
    '{"message_id":42,"date":1760000000,' +
    '"from":{"id":9007199254740993,"is_bot":false,"first_name":"Иван","username":"ivan"},' +
    '"chat":{"id":-1001234567890123,"type":"supergroup","title":"Тестовая группа"},' +
    '"text":"Привет, мир! 👋",' +
    '"entities":[{"type":"bold","offset":0,"length":6},' +
    '{"type":"text_mention","offset":8,"length":3,' +
    '"user":{"id":5,"is_bot":false,"first_name":"Пётр"}}],' +
    '"reply_to_message":{"message_id":41,"date":1759999999,' +
    '"chat":{"id":-1001234567890123,"type":"supergroup"},' +
    '"from":{"id":7,"is_bot":true,"first_name":"Бот"},"text":"Исходное"}}';
  CUpdateJson = '{"update_id":900000001,"message":' + CMessageJson + '}';
  CShortMessageJson = '{"message_id":7,"date":1,"chat":{"id":1,"type":"private"},"text":"ок"}';

var
  GPassed: Integer;
  GFailed: Integer;
  GTests: Integer;
  GTestsFailed: Integer;
  GCurrent: string;

{ TFakeTransport }

constructor TFakeTransport.Create(const AHandler: TFakeHandler);
begin
  inherited Create;
  FLock := TCriticalSection.Create;
  FHandler := AHandler;
end;

destructor TFakeTransport.Destroy;
begin
  FreeAndNil(FLock);
  inherited Destroy;
end;

function TFakeTransport.Execute(const AMethod: string; AParams: TTgParams): TJSONValue;
var
  I: Integer;
  LJson: string;
  LNames, LPaths: TArray<string>;
begin
  TInterlocked.Increment(FCalls);
  // Параметры собираются в локальные переменные вне блокировки, в поля —
  // одним шагом под FLock. Обработчик вызывается без блокировки: он может
  // висеть (HangingHandler) или повторно входить в транспорт.
  if Assigned(AParams) then
  begin
    LJson := AParams.ToJsonText;
    SetLength(LNames, AParams.FileCount);
    SetLength(LPaths, AParams.FileCount);
    for I := 0 to AParams.FileCount - 1 do
    begin
      LNames[I] := AParams.Files[I].Name;
      LPaths[I] := AParams.Files[I].InputFile.Value;
    end;
  end;
  FLock.Enter;
  try
    FLastMethod := AMethod;
    FLastThreadId := TThread.CurrentThread.ThreadID;
    FLastJson := LJson;
    FLastFileNames := LNames;
    FLastFilePaths := LPaths;
  finally
    FLock.Leave;
  end;
  if Assigned(FHandler) then
    Result := FHandler(AMethod, AParams)
  else
    Result := TJSONTrue.Create;
end;

procedure TFakeTransport.DownloadFile(const AFilePath: string; ADest: TStream);
var
  LBytes: TBytes;
begin
  FLock.Enter;
  try
    FLastMethod := 'downloadFile';
  finally
    FLock.Leave;
  end;
  LBytes := TEncoding.UTF8.GetBytes(AFilePath);
  ADest.WriteBuffer(LBytes, Length(LBytes));
end;

function TFakeTransport.GetLastMethod: string;
begin
  FLock.Enter;
  try
    Result := FLastMethod;
  finally
    FLock.Leave;
  end;
end;

function TFakeTransport.GetLastJson: string;
begin
  FLock.Enter;
  try
    Result := FLastJson;
  finally
    FLock.Leave;
  end;
end;

function TFakeTransport.GetLastFileNames: TArray<string>;
begin
  FLock.Enter;
  try
    Result := FLastFileNames;
  finally
    FLock.Leave;
  end;
end;

function TFakeTransport.GetLastFilePaths: TArray<string>;
begin
  FLock.Enter;
  try
    Result := FLastFilePaths;
  finally
    FLock.Leave;
  end;
end;

function TFakeTransport.GetLastThreadId: TThreadID;
begin
  FLock.Enter;
  try
    Result := FLastThreadId;
  finally
    FLock.Leave;
  end;
end;

procedure TFakeTransport.Cancel;
begin
  TInterlocked.Increment(FCancelCalls);
  FCancelled := True;
end;

procedure TFakeTransport.ResetCancel;
begin
  FCancelled := False;
end;

function TFakeTransport.IsCancelled: Boolean;
begin
  Result := FCancelled;
end;

function TFakeTransport.ExecuteEx(const AMethod: string; AParams: TTgParams;
  const ACancel: ITgCancellation): TJSONValue;
var
  LScope: TTgCancelScope;
begin
  TInterlocked.Increment(FExCalls);
  LScope := TTgCancelScope.Enter(ACancel);
  try
    Result := Execute(AMethod, AParams);
  finally
    LScope.Leave;
  end;
end;

procedure TFakeTransport.DownloadFileEx(const AFilePath: string; ADest: TStream;
  const ACancel: ITgCancellation);
var
  LScope: TTgCancelScope;
begin
  LScope := TTgCancelScope.Enter(ACancel);
  try
    DownloadFile(AFilePath, ADest);
  finally
    LScope.Leave;
  end;
end;

{ TPlainTransport }

constructor TPlainTransport.Create(const AHandler: TFakeHandler);
begin
  inherited Create;
  FHandler := AHandler;
end;

function TPlainTransport.Execute(const AMethod: string; AParams: TTgParams): TJSONValue;
begin
  TInterlocked.Increment(FCalls);
  Result := FHandler(AMethod, AParams);
end;

procedure TPlainTransport.DownloadFile(const AFilePath: string; ADest: TStream);
begin
  TInterlocked.Increment(FCalls);
end;

procedure TPlainTransport.Cancel;
begin
end;

procedure TPlainTransport.ResetCancel;
begin
end;

function TPlainTransport.IsCancelled: Boolean;
begin
  Result := False;
end;

{ TStubHttpTransport }

constructor TStubHttpTransport.Create(const ASettings: TTgHttpSettings;
  const AResponder: TStubResponder);
begin
  inherited Create(ASettings);
  FResponder := AResponder;
end;

function TStubHttpTransport.SendRequest(const AMethod: string;
  AParams: TTgParams): TTgHttpResponse;
begin
  TInterlocked.Increment(FSends);
  // ExecuteEx передаёт токен операции через окружающую область.
  FSawToken := (TTgCancelScope.Current <> nil);
  Result := FResponder(AMethod);
end;

/// <summary>HTTP-ответ с JSON-телом.</summary>
function StubResponse(AStatus: Integer; const AJson: string): TTgHttpResponse;
begin
  Result.StatusCode := AStatus;
  Result.Body := TEncoding.UTF8.GetBytes(AJson);
end;

/// <summary>Ждёт выполнения условия не дольше ATimeoutMs мс.</summary>
function WaitUntil(const ACondition: TFunc<Boolean>; ATimeoutMs: Integer): Boolean;
var
  LWatch: TStopwatch;
begin
  LWatch := TStopwatch.StartNew;
  while not ACondition() do
  begin
    if LWatch.ElapsedMilliseconds > ATimeoutMs then
      Exit(False);
    TThread.Sleep(5);
  end;
  Result := True;
end;

/// <summary>Отменяет источник через ADelayMs мс в отдельном потоке.</summary>
procedure CancelLater(const ASource: ITgCancellation; ADelayMs: Integer);
begin
  TThread.CreateAnonymousThread(
    procedure
    begin
      TThread.Sleep(ADelayMs);
      (ASource as TTgCancellationSource).Cancel;
    end).Start;
end;

{ Мини-раннер }

procedure Check(ACondition: Boolean; const AWhat: string);
begin
  if ACondition then
    Inc(GPassed)
  else
  begin
    Inc(GFailed);
    Writeln('    FAIL: ', AWhat);
  end;
end;

procedure CheckEquals(const AExpected, AActual, AWhat: string); overload;
begin
  Check(AExpected = AActual, AWhat + ': ожидалось "' + AExpected + '", получено "' + AActual + '"');
end;

procedure CheckEquals(AExpected, AActual: Int64; const AWhat: string); overload;
begin
  Check(AExpected = AActual, AWhat + ': ожидалось ' + IntToStr(AExpected) + ', получено ' +
    IntToStr(AActual));
end;

/// <summary>AProc выбрасывает исключение класса AClass (или потомка).</summary>
function Raises(const AProc: TProc; AClass: ExceptClass): Boolean;
begin
  try
    AProc();
    Result := False;
  except
    on E: Exception do
      Result := E is AClass;
  end;
end;

function Contains(const ASub, AText: string): Boolean;
begin
  Result := Pos(ASub, AText) > 0;
end;

function JsonOf(const AText: string): TJSONValue;
begin
  Result := TTgJson.Parse(AText);
  if not Assigned(Result) then
    raise Exception.Create('Тест: некорректный JSON заготовки');
end;

/// <summary>Поле media элемента AIndex массива media из JSON параметров ('' — нет).</summary>
function MediaField(const AParamsJson: string; AIndex: Integer): string;
var
  LParams: TJSONObject;
  LMedia: TJSONArray;
begin
  Result := '';
  LParams := TTgJson.ParseObject(AParamsJson);
  try
    LMedia := TTgJson.GetArr(LParams, 'media');
    if Assigned(LMedia) and (AIndex < LMedia.Count) and (LMedia.Items[AIndex] is TJSONObject) then
      Result := TTgJson.GetStr(TJSONObject(LMedia.Items[AIndex]), 'media');
  finally
    LParams.Free;
  end;
end;

/// <summary>Клиент с подменным транспортом; транспорт — в ATransport.</summary>
function NewApi(const AHandler: TFakeHandler; out ATransport: TFakeTransport): TTgApi;
begin
  ATransport := TFakeTransport.Create(AHandler);
  Result := TTgApi.Create(ATransport as ITgTransport);
end;

procedure RunTest(const AName: string; const AProc: TProc);
var
  LFailedBefore: Integer;
  LOnly: string;
begin
  // TG_ONLY=<подстрока имени> — выполнить только тесты, в имени которых она есть.
  LOnly := GetEnvironmentVariable('TG_ONLY');
  if (LOnly <> '') and (Pos(LOnly, AName) = 0) then
    Exit;
  GCurrent := AName;
  Inc(GTests);
  LFailedBefore := GFailed;
  try
    AProc();
  except
    on E: Exception do
    begin
      Inc(GFailed);
      Writeln('    EXCEPTION: ', E.ClassName, ': ', E.Message);
    end;
  end;
  if GFailed = LFailedBefore then
    Writeln('[ OK ] ', AName)
  else
  begin
    Inc(GTestsFailed);
    Writeln('[FAIL] ', AName);
  end;
end;

{ Тесты }

procedure TestUpdateParsing;
var
  LUpdate: ITgUpdate;
  LMessage: ITgMessage;
  LEntities: TArray<ITgMessageEntity>;
  LMention: ITgMessageEntity;
begin
  LUpdate := TTgUpdate.FromJson(CUpdateJson);
  Check(Assigned(LUpdate), 'Update разобран');
  CheckEquals(900000001, LUpdate.UpdateId, 'update_id');
  LMessage := LUpdate.Message;
  Check(Assigned(LMessage), 'Update.Message');
  CheckEquals('Привет, мир! 👋', LMessage.Text, 'кириллица и эмодзи в text');
  CheckEquals(42, LMessage.MessageId, 'message_id');
  CheckEquals(9007199254740993, LMessage.From.Id, 'Int64 from.id > 2^53');
  CheckEquals(-1001234567890123, LMessage.Chat.Id, 'Int64 chat.id');
  CheckEquals('Тестовая группа', LMessage.Chat.Title, 'chat.title');
  CheckEquals('supergroup', LMessage.Chat.ChatType, 'chat.type');
  LEntities := LMessage.Entities;
  CheckEquals(2, Length(LEntities), 'число entities');
  CheckEquals('bold', LEntities[0].MessageEntityType, 'entities[0].type');
  CheckEquals(6, LEntities[0].Length, 'entities[0].length');
  CheckEquals('Пётр', LEntities[1].User.FirstName, 'entities[1].user');
  Check(Assigned(LMessage.ReplyToMessage), 'reply_to_message');
  CheckEquals(41, LMessage.ReplyToMessage.MessageId, 'reply_to_message.message_id');
  Check(LMessage.ReplyToMessage.From.IsBot, 'reply_to_message.from.is_bot');
  CheckEquals('Исходное', LMessage.ReplyToMessage.Text, 'reply_to_message.text');
  Check(not Assigned(LUpdate.EditedMessage), 'отсутствующее поле — nil');
  // Вложенный объект удерживает JSON всего Update после освобождения корня.
  LMention := LEntities[1];
  LEntities := nil;
  LMessage := nil;
  LUpdate := nil;
  CheckEquals('Пётр', LMention.User.FirstName, 'вложенный DTO живёт без корня');
  Check(not Assigned(TTgUpdate.FromJson('не json')), 'ошибка разбора — nil');
end;

procedure TestChatMember;
var
  LMember: ITgChatMember;
  LOwner: ITgChatMemberOwner;
begin
  LMember := TTgChatMember.FromJson('{"status":"creator","user":{"id":1,"is_bot":false,' +
    '"first_name":"A"},"is_anonymous":false,"custom_title":"Босс"}');
  Check(LMember.Kind = TTgChatMemberKind.Owner, 'creator → Kind = Owner');
  CheckEquals('creator', LMember.KindText, 'KindText');
  Check(Assigned(LMember.AsOwner), 'AsOwner');
  CheckEquals('Босс', LMember.AsOwner.CustomTitle, 'AsOwner.CustomTitle');
  Check(not Assigned(LMember.AsAdministrator), 'AsAdministrator = nil');
  Check(Supports(LMember, ITgChatMemberOwner, LOwner), 'Supports ITgChatMemberOwner');
  Check(not Supports(LMember, ITgChatMemberBanned), 'not Supports ITgChatMemberBanned');
  CheckEquals('A', LOwner.User.FirstName, 'общее поле user у варианта');

  LMember := TTgChatMember.FromJson('{"status":"administrator","user":{"id":2,"is_bot":false,' +
    '"first_name":"B"},"can_be_edited":true}');
  Check(LMember.Kind = TTgChatMemberKind.Administrator, 'administrator → Kind');
  Check(LMember.AsAdministrator.CanBeEdited, 'AsAdministrator.CanBeEdited');

  LMember := TTgChatMember.FromJson('{"status":"superuser","user":{"id":3,"is_bot":false,' +
    '"first_name":"C"}}');
  Check(Assigned(LMember), 'неизвестный status разобран');
  Check(LMember.Kind = TTgChatMemberKind.Unknown, 'неизвестный status → Unknown');
  CheckEquals('superuser', LMember.KindText, 'KindText неизвестного');
  CheckEquals('superuser', LMember.Status, 'Status неизвестного');
  Check(not Assigned(LMember.AsOwner), 'Unknown: AsOwner = nil');
  CheckEquals('C', LMember.User.FirstName, 'Unknown: общее поле user');
end;

procedure TestMaybeInaccessibleMessage;
var
  LValue: ITgMaybeInaccessibleMessage;
begin
  LValue := TTgMaybeInaccessibleMessage.FromJson(
    '{"chat":{"id":1,"type":"private"},"message_id":5,"date":0}');
  Check(LValue.Kind = TTgMaybeInaccessibleMessageKind.InaccessibleMessage,
    'date = 0 → InaccessibleMessage');
  Check(Assigned(LValue.AsInaccessibleMessage), 'AsInaccessibleMessage');
  Check(not Assigned(LValue.AsMessage), 'AsMessage = nil');
  CheckEquals(5, LValue.MessageId, 'message_id');
  CheckEquals(0, LValue.Date, 'date');

  LValue := TTgMaybeInaccessibleMessage.FromJson(CShortMessageJson);
  Check(LValue.Kind = TTgMaybeInaccessibleMessageKind.Message, 'date <> 0 → Message');
  CheckEquals('ок', LValue.AsMessage.Text, 'AsMessage.Text');
end;

procedure TestRichText;
var
  LText: ITgRichText;
  LItems: TArray<ITgRichText>;
begin
  LText := TTgRichText.FromJson('"простой текст"');
  Check(Assigned(LText), 'RichText-строка разобрана');
  Check(LText.Kind = TTgRichTextKind.Plain, 'строка → Plain');
  CheckEquals('простой текст', LText.AsPlain.Text, 'Plain.Text');
  CheckEquals('', LText.KindText, 'KindText строки пуст');

  LText := TTgRichText.FromJson('["a",{"type":"bold","text":"жирный"}]');
  Check(LText.Kind = TTgRichTextKind.List, 'массив → List');
  LItems := LText.AsList.Items;
  CheckEquals(2, Length(LItems), 'число элементов List');
  Check(LItems[0].Kind = TTgRichTextKind.Plain, 'List[0] — Plain');
  Check(LItems[1].Kind = TTgRichTextKind.Bold, 'List[1] — Bold');
  CheckEquals('жирный', LItems[1].AsBold.Text.AsPlain.Text, 'Bold.Text — Plain');

  LText := TTgRichText.FromJson('{"type":"future_kind"}');
  Check(LText.Kind = TTgRichTextKind.Unknown, 'неизвестный type → Unknown');
  CheckEquals('future_kind', LText.KindText, 'KindText неизвестного');
end;

/// <summary>Затирает освобождённую память: use-after-free проявится мусором или AV.</summary>
procedure ChurnHeap;
var
  LList: TStringList;
  I: Integer;
begin
  LList := TStringList.Create;
  try
    for I := 1 to 2000 do
      LList.Add(StringOfChar('#', 1 + I mod 64));
  finally
    LList.Free;
  end;
end;

procedure TestWithUseAfterFree;
var
  LKeyboard: ITgInlineKeyboardMarkup;
  LOld: ITgInlineKeyboardButton;
  LOldRow: TArray<ITgInlineKeyboardButton>;
  LEntity: ITgMessageEntity;
  LOldUser: ITgUser;
  I: Integer;
begin
  LKeyboard := TTgInlineKeyboardMarkup.Create([TButtonRow.Create(
    TTgInlineKeyboardButton.Create('Да'),
    TTgInlineKeyboardButton.Create('Нет'))]);
  LOldRow := LKeyboard.InlineKeyboard[0];
  LOld := LOldRow[0];
  for I := 1 to 50 do
    LKeyboard.WithInlineKeyboard([TButtonRow.Create(
      TTgInlineKeyboardButton.Create('Кнопка ' + IntToStr(I)))]);
  ChurnHeap;
  CheckEquals('Да', LOld.Text, 'старая кнопка после WithInlineKeyboard');
  CheckEquals('Нет', LOldRow[1].Text, 'старая строка после WithInlineKeyboard');
  CheckEquals('Кнопка 50', LKeyboard.InlineKeyboard[0][0].Text, 'новая клавиатура');

  LEntity := TTgMessageEntity.Create('text_mention', 0, 4)
    .WithUser(TTgUser.Create(1, False, 'Иван'));
  LOldUser := LEntity.User;
  for I := 1 to 50 do
    LEntity.WithUser(TTgUser.Create(I + 1, False, 'Пётр ' + IntToStr(I)));
  ChurnHeap;
  CheckEquals('Иван', LOldUser.FirstName, 'старый User после WithUser');
  CheckEquals('Пётр 50', LEntity.User.FirstName, 'новый User');
  CheckEquals(51, LEntity.User.Id, 'новый User.Id');
end;

procedure TestInlineKeyboardRoundTrip;
var
  LKeyboard, LParsed: ITgInlineKeyboardMarkup;
  LJson: string;
  LRows: TArray<TArray<ITgInlineKeyboardButton>>;
begin
  LKeyboard := TTgInlineKeyboardMarkup.Create([TButtonRow.Create(
    TTgInlineKeyboardButton.Create('Да').WithCallbackData('yes'),
    TTgInlineKeyboardButton.Create('Нет').WithCallbackData('no'))])
    .WithInlineKeyboardRow([TTgInlineKeyboardButton.Create('Сайт').WithUrl('https://example.com')]);
  LJson := LKeyboard.AsJson;
  Check(Contains('"inline_keyboard":[[', LJson), 'JSON содержит inline_keyboard');
  LParsed := TTgInlineKeyboardMarkup.FromJson(LJson);
  Check(Assigned(LParsed), 'FromJson');
  LRows := LParsed.InlineKeyboard;
  CheckEquals(2, Length(LRows), 'число строк');
  CheckEquals(2, Length(LRows[0]), 'кнопок в строке 1');
  CheckEquals('no', LRows[0][1].CallbackData, 'callback_data');
  CheckEquals('Сайт', LRows[1][0].Text, 'кнопка строки 2');
  CheckEquals('https://example.com', LRows[1][0].Url, 'url');
  CheckEquals(LJson, LParsed.AsJson, 'JSON → FromJson → JSON без изменений');
end;

procedure TestSendMediaGroup;
var
  LApi: TTgApi;
  LTransport: TFakeTransport;
  LFile1, LFile2: string;
  LPhoto1, LPhoto2: ITgInputMediaPhoto;
  LResult: TArray<ITgMessage>;
begin
  LFile1 := TPath.Combine(TPath.GetTempPath, 'tgbottests_' + TGUID.NewGuid.ToString + '.jpg');
  LFile2 := TPath.Combine(TPath.GetTempPath, 'tgbottests_' + TGUID.NewGuid.ToString + '.jpg');
  try
    TFile.WriteAllBytes(LFile1, TBytes.Create($FF, $D8, $FF, $E0));
    TFile.WriteAllBytes(LFile2, TBytes.Create($FF, $D8, $FF, $E1));
    LApi := NewApi(
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      begin
        Result := JsonOf('[' + CShortMessageJson + ',' + CShortMessageJson + ']');
      end, LTransport);
    try
      LPhoto1 := TTgInputMediaPhoto.Create(TTgInputFile.FromFile(LFile1)).WithCaption('Первая');
      LPhoto2 := TTgInputMediaPhoto.Create(TTgInputFile.FromFile(LFile2));
      LResult := LApi.SendMediaGroup(-100500, [LPhoto1, LPhoto2]);
      CheckEquals('sendMediaGroup', LTransport.LastMethod, 'метод');
      CheckEquals(2, Length(LResult), 'результат — 2 сообщения');
      CheckEquals(2, Length(LTransport.LastFileNames), 'загружаемых файлов 2');
      if Length(LTransport.LastFileNames) = 2 then
      begin
        // В JSON-тексте '/' экранируется ('attach:\/\/…'), поэтому сверяем разобранные значения.
        CheckEquals('attach://' + LTransport.LastFileNames[0], MediaField(LTransport.LastJson, 0),
          'media первого — attach://');
        CheckEquals('attach://' + LTransport.LastFileNames[1], MediaField(LTransport.LastJson, 1),
          'media второго — attach://');
        CheckEquals(LFile1, LTransport.LastFilePaths[0], 'файл 1');
        CheckEquals(LFile2, LTransport.LastFilePaths[1], 'файл 2');
      end;
      Check(Contains('"caption":"Первая"', LTransport.LastJson), 'caption');
      Check(Contains('"chat_id":-100500', LTransport.LastJson), 'chat_id');
    finally
      LApi.Free;
    end;
  finally
    if TFile.Exists(LFile1) then
      TFile.Delete(LFile1);
    if TFile.Exists(LFile2) then
      TFile.Delete(LFile2);
  end;
end;

procedure TestOptionsArrays;
var
  LApi: TTgApi;
  LTransport: TFakeTransport;
  LOptions: TTgGetUpdatesOptions;
begin
  LApi := NewApi(
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      Result := TJSONArray.Create;
    end, LTransport);
  try
    LOptions := Default(TTgGetUpdatesOptions);
    LOptions.AllowedUpdates := [];
    CheckEquals(0, Length(LApi.GetUpdates(LOptions)), 'пустой результат');
    Check(Contains('"allowed_updates":[]', LTransport.LastJson), 'AllowedUpdates := [] → []');

    LOptions := Default(TTgGetUpdatesOptions);
    LOptions.Timeout := 0;
    LApi.GetUpdates(LOptions);
    Check(not Contains('allowed_updates', LTransport.LastJson), 'незаданный массив не отправляется');
    Check(Contains('"timeout":0', LTransport.LastJson), 'заданный 0 отправляется');

    LOptions := Default(TTgGetUpdatesOptions);
    LOptions.AllowedUpdates := [TTgUpdateType.Message, TTgUpdateType.CallbackQuery];
    LApi.GetUpdates(LOptions);
    Check(Contains('"allowed_updates":["message","callback_query"]', LTransport.LastJson),
      'массив значений');

    LApi.GetUpdates;
    CheckEquals('{}', LTransport.LastJson, 'без опций — пустые параметры');
  finally
    LApi.Free;
  end;
end;

procedure TestAsync;
var
  LApi: TTgApi;
  LTransport: TFakeTransport;
  LGate: TEvent;
  LTask: ITask;
  LOptions: TTgSendMessageOptions;
  LKeyboard: ITgInlineKeyboardMarkup;
  LReceived: ITgMessage;
  LErrorText: string;
  LErrorCode: Integer;
  LCallbackThread: TThreadID;
  LSent: TJSONObject;
  LMarkup: TJSONObject;
  LRows: TJSONArray;
  LCallsBefore: Integer;
begin
  LGate := TEvent.Create(nil, True, False, '');
  try
    LApi := NewApi(
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      begin
        LGate.WaitFor(10000);
        if AParams.GetText('text') = 'ошибка' then
          raise ETgApiError.Create(AMethod, 403, 'Forbidden: bot was blocked by the user');
        Result := JsonOf(CShortMessageJson);
      end, LTransport);
    try
      // Ошибка проверки параметров — исключением сразу, в вызывающем потоке.
      LCallsBefore := LTransport.Calls;
      Check(Raises(
        procedure
        begin
          LApi.SendMessageAsync(Default(TTgChatId), 'x', nil);
        end, ETgError), 'пустой chat_id — ETgError синхронно');
      CheckEquals(LCallsBefore, LTransport.Calls, 'транспорт не вызывался');

      // Параметры строятся до запуска задачи: изменения после вызова не влияют.
      LKeyboard := TTgInlineKeyboardMarkup.Create(
        [TButtonRow.Create(TTgInlineKeyboardButton.Create('1'))]);
      LOptions := Default(TTgSendMessageOptions);
      LOptions.ReplyMarkup := LKeyboard;
      LOptions.ReplyParameters := TTgReplyParameters.Create.WithMessageId(41);
      LCallbackThread := MainThreadID;
      LTask := LApi.SendMessageAsync(1, 'асинхронно', LOptions,
        procedure(AMessage: ITgMessage)
        begin
          LReceived := AMessage;
          LCallbackThread := TThread.CurrentThread.ThreadID;
        end);
      LKeyboard.WithInlineKeyboardRow([TTgInlineKeyboardButton.Create('2')]);
      LGate.SetEvent;
      Check(LTask.Wait(10000), 'задача завершилась');
      Check(Assigned(LReceived), 'AOnSuccess получил сообщение');
      if Assigned(LReceived) then
        CheckEquals(7, LReceived.MessageId, 'message_id из ответа');
      Check(LCallbackThread <> MainThreadID, 'колбэк — в рабочем потоке');
      Check(LTransport.LastThreadId <> MainThreadID, 'запрос — в рабочем потоке');
      LSent := TTgJson.ParseObject(LTransport.LastJson);
      try
        LMarkup := TTgJson.GetObj(LSent, 'reply_markup');
        LRows := TTgJson.GetArr(LMarkup, 'inline_keyboard');
        Check(Assigned(LRows) and (LRows.Count = 1), 'reply_markup зафиксирован в момент вызова');
        CheckEquals(41, TTgJson.GetInt64(TTgJson.GetObj(LSent, 'reply_parameters'), 'message_id'),
          'reply_parameters.message_id');
      finally
        LSent.Free;
      end;

      // Ошибка API — в AOnError.
      LErrorText := '';
      LErrorCode := 0;
      LTask := LApi.SendMessageAsync(1, 'ошибка',
        procedure(AMessage: ITgMessage)
        begin
          LErrorText := 'неожиданный успех';
        end,
        procedure(AError: Exception)
        begin
          LErrorText := AError.ClassName;
          if AError is ETgApiError then
            LErrorCode := ETgApiError(AError).ErrorCode;
        end);
      Check(LTask.Wait(10000), 'задача с ошибкой завершилась');
      CheckEquals('ETgApiError', LErrorText, 'AOnError получил ETgApiError');
      CheckEquals(403, LErrorCode, 'код ошибки');
    finally
      LApi.Free;
    end;
  finally
    LGate.Free;
  end;
end;

procedure TestDestructorWaitsAsync;
var
  LApi: TTgApi;
  LTransport: TFakeTransport;
  LTransportRef: ITgTransport;
  LStarted, LExecDone, LDone: Integer;
begin
  LStarted := 0;
  LExecDone := 0;
  LDone := 0;
  // Обработчик не реагирует на отмену: деструктор должен дождаться его.
  LApi := NewApi(
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      TInterlocked.Exchange(LStarted, 1);
      TThread.Sleep(300);
      Result := JsonOf(CShortMessageJson);
      TInterlocked.Exchange(LExecDone, 1);
    end, LTransport);
  LTransportRef := LTransport;
  try
    Check(not LApi.OwnsTransport, 'внешний транспорт не принадлежит клиенту');
    LApi.GetMeAsync(
      procedure(AUser: ITgUser)
      begin
        TInterlocked.Exchange(LDone, 1);
      end);
    // Вызов должен начаться до деструктора (иначе он будет отменён шлюзом).
    Check(WaitUntil(
      function: Boolean
      begin
        Result := TInterlocked.CompareExchange(LStarted, 0, 0) = 1;
      end, 5000), 'Async-вызов начался');
  finally
    LApi.Free;
  end;
  CheckEquals(1, TInterlocked.CompareExchange(LExecDone, 0, 0),
    'деструктор дождался выполнения начатого Async-вызова');
  // Колбэк выполняется вне шлюза — деструктор его не ждёт.
  Check(WaitUntil(
    function: Boolean
    begin
      Result := TInterlocked.CompareExchange(LDone, 0, 0) = 1;
    end, 5000), 'деструктор дождался Async-вызова (колбэк успеха вызван)');
  CheckEquals(0, LTransport.CancelCalls, 'внешний транспорт не отменялся');
  Check(not LTransportRef.IsCancelled, 'внешний транспорт не в состоянии отмены');

  LApi := TTgApi.Create('123456:TEST');
  try
    Check(LApi.OwnsTransport, 'транспорт по токену принадлежит клиенту');
    CheckEquals('123456:TEST', LApi.Settings.Token, 'Settings.Token');
    CheckEquals(TgDefaultApiUrl, LApi.Settings.ApiUrl, 'Settings.ApiUrl');
  finally
    LApi.Free;
  end;
end;

procedure TestTrySendMessageApiError;
var
  LApi: TTgApi;
  LTransport: TFakeTransport;
  LMessage: ITgMessage;
  LError: TTgErrorInfo;
begin
  LApi := NewApi(
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      raise ETgApiError.Create(AMethod, 400, 'Bad Request: chat not found');
    end, LTransport);
  try
    Check(not LApi.TrySendMessage(1, 'текст', LMessage, LError), 'TrySendMessage = False');
    Check(not Assigned(LMessage), 'AResult = nil');
    Check(LError.Kind = TTgErrorKind.Api, 'Kind = Api');
    CheckEquals(400, LError.ErrorCode, 'ErrorCode');
    CheckEquals('sendMessage', LError.Method, 'Method');
    CheckEquals('Bad Request: chat not found', LError.Description, 'Description');
    CheckEquals('ETgApiError', LError.ExceptionClassName, 'ExceptionClassName');
    Check(Raises(
      procedure
      begin
        LApi.SendMessage(1, 'текст');
      end, ETgApiError), 'синхронный вариант — ETgApiError');
  finally
    LApi.Free;
  end;
end;

procedure TestEditReturnsTrue;
var
  LApi: TTgApi;
  LTransport: TFakeTransport;
  LReturnObject: Boolean;
  LOptions: TTgEditMessageTextOptions;
  LResult: ITgMessage;
  LError: TTgErrorInfo;
begin
  LReturnObject := False;
  LApi := NewApi(
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      if LReturnObject then
        Result := JsonOf(CShortMessageJson)
      else
        Result := TJSONTrue.Create;
    end, LTransport);
  try
    LOptions := Default(TTgEditMessageTextOptions);
    LOptions.InlineMessageId := 'inl-1';
    LOptions.Text := 'новый текст';
    LResult := LApi.EditMessageText(LOptions);
    Check(not Assigned(LResult), 'ответ true → nil');
    Check(Contains('"inline_message_id":"inl-1"', LTransport.LastJson), 'inline_message_id');
    Check(not Contains('chat_id', LTransport.LastJson), 'пустой ChatId не отправляется');
    Check(LApi.TryEditMessageText(LOptions, LResult, LError), 'Try-вариант при true');
    Check(not Assigned(LResult), 'Try-вариант: AResult = nil');

    LReturnObject := True;
    LOptions := Default(TTgEditMessageTextOptions);
    LOptions.ChatId := 1;
    LOptions.MessageId := 7;
    LOptions.Text := 'новый текст';
    LResult := LApi.EditMessageText(LOptions);
    Check(Assigned(LResult), 'ответ-объект → сообщение');
  finally
    LApi.Free;
  end;
end;

procedure TestLocaleAndNaN;
var
  LApi: TTgApi;
  LTransport: TFakeTransport;
  LSaved: TFormatSettings;
  LLocation: ITgLocation;
  LCalls: Integer;
begin
  LSaved := FormatSettings;
  FormatSettings.DecimalSeparator := ',';
  FormatSettings.ThousandSeparator := ' ';
  try
    LApi := NewApi(
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      begin
        Result := JsonOf(CShortMessageJson);
      end, LTransport);
    try
      LApi.SendLocation(1, 55.75, 37.625);
      Check(Contains('"latitude":55.75', LTransport.LastJson), 'latitude с точкой при запятой в локали');
      Check(Contains('"longitude":37.625', LTransport.LastJson), 'longitude с точкой');
      LCalls := LTransport.Calls;
      Check(Raises(
        procedure
        begin
          LApi.SendLocation(1, NaN, 0);
        end, ETgError), 'NaN → ETgError');
      Check(Raises(
        procedure
        begin
          LApi.SendLocation(1, 0, Infinity);
        end, ETgError), 'Infinity → ETgError');
      CheckEquals(LCalls, LTransport.Calls, 'при NaN запрос не отправлялся');
    finally
      LApi.Free;
    end;
    LLocation := TTgLocation.FromJson('{"latitude":55.75,"longitude":-37.625}');
    Check(SameValue(LLocation.Latitude, 55.75), 'разбор вещественного при запятой в локали');
    Check(SameValue(LLocation.Longitude, -37.625), 'отрицательное вещественное');
    Check(Contains('"latitude":1.5', TTgLocation.Create(1.5, 2.25).AsJson), 'With/Create: точка');
    Check(Raises(
      procedure
      begin
        TTgLocation.Create(0, 0).WithLatitude(NaN);
      end, ETgError), 'WithLatitude(NaN) → ETgError');
  finally
    FormatSettings := LSaved;
  end;
end;

procedure TestCloneDetach;
var
  LUpdate: ITgUpdate;
  LMessage, LDetached, LCloneMsg: ITgMessage;
  LClone: ITgJsonObject;
  LLocation, LLocationCopy: ITgLocation;
begin
  LUpdate := TTgUpdate.FromJson(CUpdateJson);
  LDetached := TTgDto.Detach<ITgMessage>(LUpdate.Message);
  LMessage := LUpdate.Message;
  Check((LDetached as TObject) <> (LMessage as TObject), 'Detach — новый объект');
  LMessage := nil;
  LUpdate := nil;
  CheckEquals('Привет, мир! 👋', LDetached.Text, 'Detach: текст');
  CheckEquals('Иван', LDetached.From.FirstName, 'Detach: вложенный объект');

  LClone := LDetached.Clone;
  Check(Supports(LClone, ITgMessage, LCloneMsg), 'Clone реализует тот же интерфейс');
  CheckEquals(LDetached.AsJson, LClone.AsJson, 'Clone: тот же JSON');

  LLocation := TTgLocation.Create(1, 2);
  LLocationCopy := TTgDto.Detach<ITgLocation>(LLocation);
  LLocation.WithLatitude(10);
  Check(SameValue(LLocationCopy.Latitude, 1), 'копия не зависит от изменений оригинала');
  Check(SameValue(LLocation.Latitude, 10), 'оригинал изменён');

  Check(not Assigned(TTgDto.Detach<ITgMessage>(nil)), 'Detach(nil) = nil');
  Check(Raises(
    procedure
    begin
      TTgDto.Detach<ITgInputMediaPhoto>(TTgInputMediaPhoto.Create(TTgInputFile.FromFileId('abc')));
    end, ETgError), 'Detach исходящего объекта → ETgError');
end;

procedure TestCoreMisc;
var
  LApi: TTgApi;
  LTransport: TFakeTransport;
  LStream: TBytesStream;
begin
  LApi := NewApi(
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      Result := JsonOf('{"id":1,"is_bot":true,"first_name":"Бот"}');
    end, LTransport);
  try
    CheckEquals('Бот', LApi.GetMe.FirstName, 'GetMe');
    CheckEquals('getMe', LTransport.LastMethod, 'имя метода');
    Check(Contains('"first_name":"Бот"', LApi.CallJson('getMe')), 'CallJson');
    LStream := TBytesStream.Create;
    try
      LApi.DownloadFile('photos/file_1.jpg', LStream);
      CheckEquals('downloadFile', LTransport.LastMethod, 'DownloadFile через транспорт');
      CheckEquals(Length('photos/file_1.jpg'), LStream.Size, 'данные записаны в поток');
    finally
      LStream.Free;
    end;
  finally
    LApi.Free;
  end;
  Check(Raises(
    procedure
    begin
      TTgApi.Create(ITgTransport(nil)).Free;
    end, ETgError), 'nil-транспорт → ETgError');

  TgSetLanguage(TTgLanguage.En);
  try
    Check(TgGetLanguage = TTgLanguage.En, 'TgGetLanguage');
    Check(Raises(
      procedure
      begin
        TTgChatId(Default(TTgChatId)).ToJson.Free;
      end, ETgError), 'пустой ChatId → ETgError');
  finally
    TgSetLanguage(TTgLanguage.Ru);
  end;
  CheckEquals('10.3', TgBotApiVersion, 'TgBotApiVersion');
  Check(TgBotVersion <> '', 'TgBotVersion');
  CheckEquals(Format('%d.%d.%d', [TgBotVersionMajor, TgBotVersionMinor, TgBotVersionRelease]),
    TgBotVersion, 'TgBotVersion = Major.Minor.Release');
end;

{ Фаза 4b: варианты методов и построители клавиатур }

/// <summary>Значение по пути (TJSONValue.FindValue) текстом: строка/bool — Value, иначе JSON; '' — нет.</summary>
function JsonAt(const AJson, APath: string): string;
var
  LRoot, LValue: TJSONValue;
begin
  Result := '';
  LRoot := TJSONObject.ParseJSONValue(AJson);
  try
    if not Assigned(LRoot) then
      Exit;
    LValue := LRoot.FindValue(APath);
    // Число — исходным текстом: TJSONNumber.Value в 10.4 форматирует по локали.
    if (LValue is TJSONObject) or (LValue is TJSONArray) or (LValue is TJSONNumber) then
      Result := LValue.ToJSON
    else if Assigned(LValue) then
      Result := LValue.Value;
  finally
    LRoot.Free;
  end;
end;

/// <summary>JSON исходящего объекта (ITgOutObject.Serialize) текстом.</summary>
function OutJson(const AValue: IInterface): string;
var
  LParams: TTgParams;
  LJson: TJSONValue;
begin
  LParams := TTgParams.Create;
  try
    LJson := TTgDto.Serialize(AValue, LParams);
    try
      Result := LJson.ToJSON;
    finally
      LJson.Free;
    end;
  finally
    LParams.Free;
  end;
end;

/// <summary>
///   Ответы как у Bot API: inline_message_id → true, getGameHighScores → массив,
///   answerCallbackQuery → true, остальное — сообщение.
/// </summary>
function VariantHandler: TFakeHandler;
begin
  Result :=
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      // inline_message_id = 'object' — имитация ответа-объекта для inline-варианта.
      if (AMethod = 'answerCallbackQuery') or (AParams.Contains('inline_message_id') and
        (AParams.GetText('inline_message_id') <> 'object')) then
      begin
        if AMethod = 'getGameHighScores' then
          Result := JsonOf('[{"position":1,"user":{"id":5,"is_bot":false,"first_name":"Игрок"},' +
            '"score":100}]')
        else
          Result := TJSONTrue.Create;
      end
      else if AMethod = 'getGameHighScores' then
        Result := JsonOf('[{"position":2,"user":{"id":5,"is_bot":false,"first_name":"Игрок"},' +
          '"score":50}]')
      else
        Result := JsonOf(CShortMessageJson);
    end;
end;

procedure TestEditVariants;
var
  LApi: TTgApi;
  LTransport: TFakeTransport;
  LChatId: TTgChatId;
  LId: Int64;
  LName: string;
  LOptions: TTgEditMessageTextOptions;
  LMessage: ITgMessage;
  LScores: TArray<ITgGameHighScore>;
begin
  LApi := NewApi(VariantHandler(), LTransport);
  try
    // chat_id: Int64-переменная, литерал, '@username', TTgChatId — без неоднозначности перегрузок.
    LId := -1001234567890123;
    LMessage := LApi.EditMessageText(LId, 7, 'новый текст');
    Check(Assigned(LMessage), 'EditMessageText(Int64, …) → сообщение');
    CheckEquals('editMessageText', LTransport.LastMethod, 'метод editMessageText');
    CheckEquals('-1001234567890123', JsonAt(LTransport.LastJson, 'chat_id'), 'chat_id из Int64');
    CheckEquals('7', JsonAt(LTransport.LastJson, 'message_id'), 'message_id');
    CheckEquals('новый текст', JsonAt(LTransport.LastJson, 'text'), 'text');
    Check(not Contains('inline_message_id', LTransport.LastJson), 'без inline_message_id');
    LApi.EditMessageText(42, 7, 'литерал');
    CheckEquals('42', JsonAt(LTransport.LastJson, 'chat_id'), 'chat_id из литерала');
    LName := '@channel';
    LApi.EditMessageText(LName, 7, 'строка');
    CheckEquals('@channel', JsonAt(LTransport.LastJson, 'chat_id'), 'chat_id из string');
    LApi.EditMessageText('@literal', 7, 'строка-литерал');
    CheckEquals('@literal', JsonAt(LTransport.LastJson, 'chat_id'), 'chat_id из литерала-строки');
    LChatId := TTgChatId.FromId(5);
    LApi.EditMessageText(LChatId, 7, 'TTgChatId');
    CheckEquals('5', JsonAt(LTransport.LastJson, 'chat_id'), 'chat_id из TTgChatId');

    // Опции дополняют позиционные; одноимённые поля опций заменяются параметрами.
    LOptions := Default(TTgEditMessageTextOptions);
    LOptions.ChatId := 999;
    LOptions.Text := 'из опций';
    LOptions.ParseMode := TTgParseMode.Html;
    LOptions.ReplyMarkup := TTgKeyboard.Inline.Button('Ок', 'ok');
    LApi.EditMessageText(1, 2, '<b>жирный</b>', LOptions);
    CheckEquals('1', JsonAt(LTransport.LastJson, 'chat_id'), 'позиционный chat_id важнее опций');
    CheckEquals('<b>жирный</b>', JsonAt(LTransport.LastJson, 'text'), 'позиционный text важнее опций');
    CheckEquals('HTML', JsonAt(LTransport.LastJson, 'parse_mode'), 'parse_mode из опций');
    CheckEquals('ok', JsonAt(LTransport.LastJson, 'reply_markup.inline_keyboard[0][0].callback_data'),
      'reply_markup из построителя в опциях');
    CheckEquals('из опций', LOptions.Text.Value, 'запись опций вызывающего не изменена');

    // Inline-вариант: Boolean, только inline_message_id.
    Check(LApi.EditInlineMessageText('inl-1', 'inline-текст'), 'EditInlineMessageText = True');
    CheckEquals('editMessageText', LTransport.LastMethod, 'inline: тот же метод Bot API');
    CheckEquals('inl-1', JsonAt(LTransport.LastJson, 'inline_message_id'), 'inline_message_id');
    CheckEquals('inline-текст', JsonAt(LTransport.LastJson, 'text'), 'inline: text');
    Check(not Contains('chat_id', LTransport.LastJson), 'inline: без chat_id');
    Check(LApi.EditInlineMessageText('inl-2', 'с опциями', LOptions), 'inline с опциями');
    CheckEquals('HTML', JsonAt(LTransport.LastJson, 'parse_mode'), 'inline: parse_mode из опций');
    // Опции с ChatId передаются как есть — это ответственность вызывающего (документировано).
    CheckEquals('999', JsonAt(LTransport.LastJson, 'chat_id'), 'inline: прочие поля опций передаются');

    // Остальные edit-варианты.
    LApi.EditMessageCaption(1, 2, 'подпись');
    CheckEquals('editMessageCaption', LTransport.LastMethod, 'editMessageCaption');
    CheckEquals('подпись', JsonAt(LTransport.LastJson, 'caption'), 'caption');
    Check(LApi.EditInlineMessageCaption('inl', 'подпись'), 'EditInlineMessageCaption = True');
    LApi.EditMessageReplyMarkup(1, 2, TTgKeyboard.Inline.Url('Сайт', 'https://example.com'));
    CheckEquals('https://example.com',
      JsonAt(LTransport.LastJson, 'reply_markup.inline_keyboard[0][0].url'), 'reply_markup.url');
    LApi.EditMessageReplyMarkup(1, 2, nil);
    Check(not Contains('reply_markup', LTransport.LastJson), 'nil — клавиатура убирается (без reply_markup)');
    Check(LApi.EditInlineMessageReplyMarkup('inl', TTgKeyboard.Inline.Button('A', 'a')),
      'EditInlineMessageReplyMarkup = True');
    LApi.EditMessageMedia(1, 2, TTgInputMediaPhoto.Create(TTgInputFile.FromFileId('file-1')));
    CheckEquals('file-1', JsonAt(LTransport.LastJson, 'media.media'), 'editMessageMedia: media');
    Check(LApi.EditInlineMessageMedia('inl', TTgInputMediaPhoto.Create(TTgInputFile.FromFileId('f'))),
      'EditInlineMessageMedia = True');
    LApi.EditMessageLiveLocation(1, 2, 55.75, 37.5);
    CheckEquals('55.75', JsonAt(LTransport.LastJson, 'latitude'), 'editMessageLiveLocation: latitude');
    CheckEquals('2', JsonAt(LTransport.LastJson, 'message_id'), 'editMessageLiveLocation: message_id');
    Check(LApi.EditInlineMessageLiveLocation('inl', 1.5, 2.5), 'EditInlineMessageLiveLocation = True');
    LApi.StopMessageLiveLocation(1, 2);
    CheckEquals('stopMessageLiveLocation', LTransport.LastMethod, 'stopMessageLiveLocation');
    Check(LApi.StopInlineMessageLiveLocation('inl'), 'StopInlineMessageLiveLocation = True');
    LApi.SetGameScore(5, 100, 1, 2);
    CheckEquals('100', JsonAt(LTransport.LastJson, 'score'), 'setGameScore: score');
    CheckEquals('1', JsonAt(LTransport.LastJson, 'chat_id'), 'setGameScore: chat_id');
    Check(LApi.SetInlineGameScore(5, 100, 'inl'), 'SetInlineGameScore = True');
    LScores := LApi.GetGameHighScores(5, 1, 2);
    CheckEquals(50, LScores[0].Score, 'GetGameHighScores(chat_id, message_id)');
    LScores := LApi.GetInlineGameHighScores(5, 'inl');
    CheckEquals(100, LScores[0].Score, 'GetInlineGameHighScores');

    // Inline-вариант ждёт true: объект в ответе — ошибка разбора, а не молчаливый успех.
    Check(Raises(
      procedure
      begin
        LApi.EditInlineMessageText('object', 'ответ-сообщение вместо true');
      end, ETgError), 'inline-вариант: ответ-объект → ETgError');
  finally
    LApi.Free;
  end;
end;

procedure TestSendAndAnswerVariants;
var
  LApi: TTgApi;
  LTransport: TFakeTransport;
  LOptions: TTgSendMessageOptions;
begin
  LApi := NewApi(VariantHandler(), LTransport);
  try
    Check(LApi.AnswerCallbackQuery('cb-1', 'Принято'), 'AnswerCallbackQuery(Id, Text)');
    CheckEquals('cb-1', JsonAt(LTransport.LastJson, 'callback_query_id'), 'callback_query_id');
    CheckEquals('Принято', JsonAt(LTransport.LastJson, 'text'), 'text');
    Check(not Contains('show_alert', LTransport.LastJson), 'show_alert не передан');
    Check(LApi.AnswerCallbackQuery('cb-2', 'Внимание', True), 'AnswerCallbackQuery(Id, Text, True)');
    CheckEquals('true', JsonAt(LTransport.LastJson, 'show_alert'), 'show_alert');
    LApi.AnswerCallbackQuery('cb-3');
    CheckEquals('{"callback_query_id":"cb-3"}', LTransport.LastJson, 'базовая перегрузка без текста');

    LApi.SendMessage(1, 'инлайн', TTgKeyboard.Inline.Row.Button('Да', 'yes').Button('Нет', 'no'));
    CheckEquals('no', JsonAt(LTransport.LastJson, 'reply_markup.inline_keyboard[0][1].callback_data'),
      'SendMessage(…, Inline)');
    LApi.SendMessage('@chan', 'обычная', TTgKeyboard.Reply.Text('Меню').Resize);
    CheckEquals('Меню', JsonAt(LTransport.LastJson, 'reply_markup.keyboard[0][0].text'),
      'SendMessage(…, Reply)');
    CheckEquals('@chan', JsonAt(LTransport.LastJson, 'chat_id'), 'chat_id @username');
    LApi.SendMessage(1, 'убрать', TTgKeyboard.Remove);
    CheckEquals('true', JsonAt(LTransport.LastJson, 'reply_markup.remove_keyboard'), 'SendMessage(…, Remove)');
    LApi.SendMessage(1, 'ответ', TTgKeyboard.ForceReply('Ваш ответ'));
    CheckEquals('true', JsonAt(LTransport.LastJson, 'reply_markup.force_reply'), 'SendMessage(…, ForceReply)');
    LApi.SendMessage(1, 'интерфейс', TTgInlineKeyboardMarkup.Create([TgRow([
      TTgInlineKeyboardButton.Create('X').WithCallbackData('x')])]));
    CheckEquals('x', JsonAt(LTransport.LastJson, 'reply_markup.inline_keyboard[0][0].callback_data'),
      'SendMessage(…, ITgInlineKeyboardMarkup)');
    LOptions := Default(TTgSendMessageOptions);
    LOptions.DisableNotification := True;
    LApi.SendMessage(1, 'с опциями', TTgKeyboard.Inline.Button('A', 'a'), LOptions);
    CheckEquals('true', JsonAt(LTransport.LastJson, 'disable_notification'), 'вариант + опции');
    CheckEquals('a', JsonAt(LTransport.LastJson, 'reply_markup.inline_keyboard[0][0].callback_data'),
      'вариант + опции: reply_markup');
    LApi.SendMessage(1, 'без клавиатуры');
    Check(not Contains('reply_markup', LTransport.LastJson), 'базовая перегрузка SendMessage');

    LApi.SendPhoto(1, TTgInputFile.FromFileId('photo-1'), 'подпись фото');
    CheckEquals('photo-1', JsonAt(LTransport.LastJson, 'photo'), 'sendPhoto: photo');
    CheckEquals('подпись фото', JsonAt(LTransport.LastJson, 'caption'), 'sendPhoto: caption');
    LApi.SendDocument(1, TTgInputFile.FromFileId('doc-1'), 'подпись документа');
    CheckEquals('подпись документа', JsonAt(LTransport.LastJson, 'caption'), 'sendDocument: caption');
  finally
    LApi.Free;
  end;
end;

procedure TestVariantsAsyncAndTry;
var
  LApi, LFailApi: TTgApi;
  LTransport, LFailTransport: TFakeTransport;
  LTask: ITask;
  LMessage: ITgMessage;
  LOk, LAnswered: Boolean;
  LError: TTgErrorInfo;
  LThreadOk: Boolean;
begin
  LApi := NewApi(VariantHandler(), LTransport);
  try
    LMessage := nil;
    LTask := LApi.EditMessageTextAsync(1, 2, 'async',
      procedure(AMessage: ITgMessage)
      begin
        LMessage := AMessage;
      end);
    Check(LTask.Wait(10000), 'EditMessageTextAsync завершился');
    Check(Assigned(LMessage), 'EditMessageTextAsync: сообщение');
    CheckEquals('async', JsonAt(LTransport.LastJson, 'text'), 'EditMessageTextAsync: text');

    LOk := False;
    LThreadOk := False;
    LTask := LApi.EditInlineMessageTextAsync('inl', 'async-inline',
      procedure(AResult: Boolean)
      begin
        LOk := AResult;
        LThreadOk := TThread.CurrentThread.ThreadID <> MainThreadID;
      end);
    Check(LTask.Wait(10000), 'EditInlineMessageTextAsync завершился');
    Check(LOk, 'EditInlineMessageTextAsync: True');
    Check(LThreadOk, 'колбэк варианта — в рабочем потоке');

    LAnswered := False;
    LTask := LApi.AnswerCallbackQueryAsync('cb', 'async-ответ',
      procedure(AResult: Boolean)
      begin
        LAnswered := AResult;
      end);
    Check(LTask.Wait(10000), 'AnswerCallbackQueryAsync завершился');
    Check(LAnswered, 'AnswerCallbackQueryAsync(Id, Text)');
    CheckEquals('async-ответ', JsonAt(LTransport.LastJson, 'text'), 'AnswerCallbackQueryAsync: text');

    LMessage := nil;
    LTask := LApi.SendMessageAsync(1, 'async-клавиатура', TTgKeyboard.Inline.Button('A', 'a'),
      procedure(AMessage: ITgMessage)
      begin
        LMessage := AMessage;
      end);
    Check(LTask.Wait(10000), 'SendMessageAsync(…, клавиатура) завершился');
    Check(Assigned(LMessage), 'SendMessageAsync(…, клавиатура): сообщение');

    Check(LApi.TryEditMessageText(1, 2, 'try', LMessage, LError), 'TryEditMessageText(chat, id, text)');
    Check(Assigned(LMessage), 'TryEditMessageText: AResult');
    Check(LApi.TryEditInlineMessageText('inl', 'try', LError), 'TryEditInlineMessageText = True');
    Check(LApi.TryAnswerCallbackQuery('cb', 'try', True, LError), 'TryAnswerCallbackQuery(Id, Text, True)');
    Check(LApi.TryStopInlineMessageLiveLocation('inl', LError), 'TryStopInlineMessageLiveLocation');
  finally
    LApi.Free;
  end;

  LFailApi := NewApi(
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      raise ETgApiError.Create(AMethod, 400, 'Bad Request: message is not modified');
    end, LFailTransport);
  try
    Check(not LFailApi.TryEditInlineMessageText('inl', 'x', LError), 'Try inline при ошибке = False');
    CheckEquals('editMessageText', LError.Method, 'Try inline: Method');
    CheckEquals(400, LError.ErrorCode, 'Try inline: ErrorCode');
    Check(not LFailApi.TryEditMessageText(1, 2, 'x', LMessage, LError), 'Try при ошибке = False');
    Check(not Assigned(LMessage), 'Try при ошибке: AResult = nil');
    LAnswered := True;
    LTask := LFailApi.EditInlineMessageTextAsync('inl', 'x',
      procedure(AResult: Boolean)
      begin
        LAnswered := False;
      end,
      procedure(AError: Exception)
      begin
        LAnswered := AError is ETgApiError;
      end);
    Check(LTask.Wait(10000), 'Async inline с ошибкой завершился');
    Check(LAnswered, 'Async inline: AOnError получил ETgApiError');
  finally
    LFailApi.Free;
  end;
end;

procedure TestKeyboardBuilders;
var
  LBase, LMore: TTgInlineKeyboardBuilder;
  LInline: ITgInlineKeyboardMarkup;
  LMarkup: TTgReplyMarkup;
  LReplyKb: ITgReplyKeyboardMarkup;
  LJson: string;
  LSendOptions: TTgSendMessageOptions;
begin
  LInline := TTgKeyboard.Inline
    .Row.Button('Да', 'yes').Button('Нет', 'no')
    .Row.Url('Сайт', 'https://example.com').WebApp('App', 'https://app.example.com')
    .Row
    .Row.LoginUrl('Вход', 'https://login.example.com').SwitchInline('Поиск', 'q')
    .Row.SwitchInlineCurrentChat('Здесь').CopyText('Копировать', 'секрет')
    .Row.Pay('Оплатить').Game('Играть');
  LJson := LInline.AsJson;
  CheckEquals(5, Length(LInline.InlineKeyboard), 'пустая строка пропущена: 5 строк');
  CheckEquals('yes', JsonAt(LJson, 'inline_keyboard[0][0].callback_data'), 'Button: callback_data');
  CheckEquals('Нет', JsonAt(LJson, 'inline_keyboard[0][1].text'), 'Button: text');
  CheckEquals('https://example.com', JsonAt(LJson, 'inline_keyboard[1][0].url'), 'Url');
  CheckEquals('https://app.example.com', JsonAt(LJson, 'inline_keyboard[1][1].web_app.url'), 'WebApp');
  CheckEquals('https://login.example.com', JsonAt(LJson, 'inline_keyboard[2][0].login_url.url'), 'LoginUrl');
  CheckEquals('q', JsonAt(LJson, 'inline_keyboard[2][1].switch_inline_query'), 'SwitchInline');
  CheckEquals('', JsonAt(LJson, 'inline_keyboard[3][0].switch_inline_query_current_chat'),
    'SwitchInlineCurrentChat: пустой запрос');
  Check(Contains('"switch_inline_query_current_chat":""', LJson), 'SwitchInlineCurrentChat передаётся');
  CheckEquals('секрет', JsonAt(LJson, 'inline_keyboard[3][1].copy_text.text'), 'CopyText');
  CheckEquals('true', JsonAt(LJson, 'inline_keyboard[4][0].pay'), 'Pay');
  CheckEquals('{}', JsonAt(LJson, 'inline_keyboard[4][1].callback_game'), 'Game: callback_game');

  // Запись-значение: продолжение цепочки не меняет исходную копию.
  LBase := TTgKeyboard.Inline.Button('1', 'one');
  LMore := LBase.Button('2', 'two').Row.Button('3', 'three');
  CheckEquals(1, LBase.RowCount, 'исходная копия: 1 строка');
  CheckEquals(1, Length(LBase.Build.InlineKeyboard[0]), 'исходная копия: 1 кнопка');
  CheckEquals(2, LMore.RowCount, 'продолжение: 2 строки');
  CheckEquals(2, Length(LMore.Build.InlineKeyboard[0]), 'продолжение: 2 кнопки в строке 1');
  Check(TTgKeyboard.Inline.IsEmpty, 'пустой построитель');
  Check(TTgKeyboard.Inline.Row.Row.IsEmpty, 'пустые строки — пусто');
  CheckEquals('{"inline_keyboard":[]}', TTgKeyboard.Inline.Build.AsJson, 'пустая клавиатура');

  // Неявные приведения.
  LMarkup := TTgKeyboard.Inline.Button('A', 'a');
  Check(Supports(LMarkup.Value, ITgInlineKeyboardMarkup), 'Implicit → TTgReplyMarkup (инлайн)');
  LMarkup := TTgKeyboard.Reply.Text('B');
  Check(Supports(LMarkup.Value, ITgReplyKeyboardMarkup), 'Implicit → TTgReplyMarkup (обычная)');
  LMarkup := TTgKeyboard.Inline.Button('C', 'c').AsReplyMarkup;
  Check(not LMarkup.IsEmpty, 'AsReplyMarkup');
  LSendOptions := Default(TTgSendMessageOptions);
  LSendOptions.ReplyMarkup := TTgKeyboard.Reply.Text('D');
  Check(Supports(LSendOptions.ReplyMarkup.Value, ITgReplyKeyboardMarkup), 'опции send: ReplyMarkup := Reply');

  // Обычная клавиатура и флаги.
  LReplyKb := TTgKeyboard.Reply
    .Row.Text('Меню').RequestContact('Телефон')
    .Row.RequestLocation('Где я').RequestPoll('Викторина', TTgPollType.Quiz)
    .Row.WebApp('App', 'https://app.example.com')
    .Resize.OneTime.Persistent.Selective.Placeholder('Выберите');
  LJson := OutJson(LReplyKb);
  CheckEquals('Меню', JsonAt(LJson, 'keyboard[0][0].text'), 'Reply: Text');
  CheckEquals('true', JsonAt(LJson, 'keyboard[0][1].request_contact'), 'RequestContact');
  CheckEquals('true', JsonAt(LJson, 'keyboard[1][0].request_location'), 'RequestLocation');
  CheckEquals('quiz', JsonAt(LJson, 'keyboard[1][1].request_poll.type'), 'RequestPoll(Quiz)');
  CheckEquals('https://app.example.com', JsonAt(LJson, 'keyboard[2][0].web_app.url'), 'Reply: WebApp');
  CheckEquals('true', JsonAt(LJson, 'resize_keyboard'), 'Resize');
  CheckEquals('true', JsonAt(LJson, 'one_time_keyboard'), 'OneTime');
  CheckEquals('true', JsonAt(LJson, 'is_persistent'), 'Persistent');
  CheckEquals('true', JsonAt(LJson, 'selective'), 'Selective');
  CheckEquals('Выберите', JsonAt(LJson, 'input_field_placeholder'), 'Placeholder');
  LJson := OutJson(TTgKeyboard.Reply.Text('X').Build);
  CheckEquals('{"keyboard":[[{"text":"X"}]]}', LJson, 'без флагов — только keyboard');
  CheckEquals('{}', JsonAt(OutJson(TTgKeyboard.Reply.RequestPoll('Опрос').Build),
    'keyboard[0][0].request_poll'),
    'RequestPoll без типа — {}');
  Check(not Contains('resize', OutJson(TTgKeyboard.Reply.Resize(False).Text('Y').Build)),
    'Resize(False) — не передаётся');

  // Remove и ForceReply.
  CheckEquals('{"remove_keyboard":true}', OutJson(TTgKeyboard.Remove), 'Remove');
  CheckEquals('true', JsonAt(OutJson(TTgKeyboard.Remove(True)), 'selective'), 'Remove(True): selective');
  CheckEquals('{"force_reply":true}', OutJson(TTgKeyboard.ForceReply), 'ForceReply');
  LJson := OutJson(TTgKeyboard.ForceReply('Ваш ответ', True));
  CheckEquals('Ваш ответ', JsonAt(LJson, 'input_field_placeholder'), 'ForceReply: placeholder');
  CheckEquals('true', JsonAt(LJson, 'selective'), 'ForceReply: selective');

  // TgRow для фабрик с массивами строк.
  LJson := TTgInlineKeyboardMarkup.Create([
    TgRow([TTgInlineKeyboardButton.Create('A').WithCallbackData('a'),
      TTgInlineKeyboardButton.Create('B').WithCallbackData('b')]),
    TgRow([TTgInlineKeyboardButton.Create('C').WithUrl('https://c.example')])]).AsJson;
  CheckEquals('b', JsonAt(LJson, 'inline_keyboard[0][1].callback_data'), 'TgRow (инлайн): строка 1');
  CheckEquals('C', JsonAt(LJson, 'inline_keyboard[1][0].text'), 'TgRow (инлайн): строка 2');
  LJson := OutJson(TTgReplyKeyboardMarkup.Create([TgRow([TTgKeyboardButton.Create('K1'),
    TTgKeyboardButton.Create('K2')])]));
  CheckEquals('K2', JsonAt(LJson, 'keyboard[0][1].text'), 'TgRow (обычная)');

  Check(Raises(
    procedure
    begin
      TTgKeyboard.Inline.Add(nil);
    end, EArgumentNilException), 'Add(nil) → EArgumentNilException');
  Check(Raises(
    procedure
    begin
      TTgKeyboard.Reply.Add(nil);
    end, EArgumentNilException), 'Reply.Add(nil) → EArgumentNilException');
end;

{ Фаза 5a: отмена, шлюз Async, пул библиотеки }

var
  // Замеры для итогового отчёта.
  GWaitWakeMs: Int64 = -1;
  GDestroyHangingMs: Int64 = -1;
  GDestroyUserPoolMs: Int64 = -1;
  GRealHttpCancelMs: Int64 = -1;
  GRealHttpDestroyMs: Int64 = -1;

/// <summary>Источник отмены как объект (Cancel не входит в ITgCancellation).</summary>
function SourceOf(const AToken: ITgCancellation): TTgCancellationSource;
begin
  Result := AToken as TTgCancellationSource;
end;

type
  /// <summary>Зонд колбэка отмены: число вызовов; живые зонды считаются в GCancelProbeLive.</summary>
  ICancelProbe = interface
    procedure Hit;
    function Calls: Integer;
  end;

  TCancelProbe = class(TInterfacedObject, ICancelProbe)
  private
    FCalls: Integer;
  public
    constructor Create;
    destructor Destroy; override;
    procedure Hit;
    function Calls: Integer;
  end;

  /// <summary>
  ///   Сценарий «кнопка Cancel»: обычный объект (ручной Free) хранит источник
  ///   только как ITgCancellationSource и отменяет его из другого метода.
  /// </summary>
  TCancelButtonOwner = class
  private
    FSource: ITgCancellationSource;
    FRegistration: IInterface;
    FWorker: TThread;
    FWorkerSawCancel: ICancelProbe;
    FCallbackProbe: ICancelProbe;
  public
    destructor Destroy; override;
    /// <summary>Создаёт источник и поток, ждущий отмены токена.</summary>
    procedure StartWork;
    /// <summary>«Нажатие кнопки»: отмена через поле-интерфейс.</summary>
    procedure CancelClick;
    /// <summary>Дожидается завершения рабочего потока.</summary>
    procedure WaitWorker;
    property WorkerSawCancel: ICancelProbe read FWorkerSawCancel;
    property CallbackProbe: ICancelProbe read FCallbackProbe;
  end;

var
  GCancelProbeLive: Integer = 0;

constructor TCancelProbe.Create;
begin
  inherited Create;
  TInterlocked.Increment(GCancelProbeLive);
end;

destructor TCancelProbe.Destroy;
begin
  TInterlocked.Decrement(GCancelProbeLive);
  inherited Destroy;
end;

procedure TCancelProbe.Hit;
begin
  TInterlocked.Increment(FCalls);
end;

function TCancelProbe.Calls: Integer;
begin
  Result := TInterlocked.CompareExchange(FCalls, 0, 0);
end;

/// <summary>Колбэк отмены, захватывающий только зонд.</summary>
function ProbeCallback(const AProbe: ICancelProbe): TProc;
begin
  Result :=
    procedure
    begin
      AProbe.Hit;
    end;
end;

/// <summary>
///   Подписывает зонд на отмену. Отдельная функция: временный TProc
///   освобождается при выходе из неё, а не в конце вызывающего теста.
/// </summary>
function RegisterProbe(const AToken: ITgCancellation; const AProbe: ICancelProbe): IInterface;
begin
  Result := AToken.Register(ProbeCallback(AProbe));
end;

{ TCancelButtonOwner }

destructor TCancelButtonOwner.Destroy;
begin
  CancelClick;
  WaitWorker;
  FRegistration := nil;
  FSource := nil;
  inherited Destroy;
end;

procedure TCancelButtonOwner.StartWork;
var
  LToken: ITgCancellation;
  LSaw: ICancelProbe;
begin
  FSource := TTgCancellationSource.New;
  FWorkerSawCancel := TCancelProbe.Create;
  FCallbackProbe := TCancelProbe.Create;
  FRegistration := RegisterProbe(FSource, FCallbackProbe);
  // Потоку — только токен (без права отмены) и зонд; Self не захватывается.
  LToken := FSource;
  LSaw := FWorkerSawCancel;
  FWorker := TThread.CreateAnonymousThread(
    procedure
    begin
      if LToken.WaitFor(10000) then
        LSaw.Hit;
    end);
  FWorker.FreeOnTerminate := False;
  FWorker.Start;
end;

procedure TCancelButtonOwner.CancelClick;
begin
  if Assigned(FSource) then
    FSource.Cancel;
end;

procedure TCancelButtonOwner.WaitWorker;
begin
  if Assigned(FWorker) then
  begin
    FWorker.WaitFor;
    FreeAndNil(FWorker);
  end;
end;

/// <summary>Обработчик подменного транспорта: висит до отмены окружающего токена.</summary>
function HangingHandler(const AHang: PInteger; const AEntered: PInteger): TFakeHandler;
begin
  Result :=
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    var
      LToken: ITgCancellation;
    begin
      if TInterlocked.CompareExchange(AHang^, 0, 0) = 1 then
      begin
        TInterlocked.Increment(AEntered^);
        LToken := TTgCancelScope.Current;
        if Assigned(LToken) then
        begin
          LToken.WaitFor(50000);
          LToken.ThrowIfCancelled;
        end;
      end;
      Result := JsonOf('{"id":1,"is_bot":true,"first_name":"Бот"}');
    end;
end;

procedure TestCancellationTokens;
var
  LSource, LParent, LChild, A, B, LLinked: ITgCancellation;
  LReg, LReg2: IInterface;
  LCount: Integer;
  LWatch: TStopwatch;
  I: Integer;
begin
  LCount := 0;
  LSource := TTgCancellationSource.Create;
  LReg := LSource.Register(
    procedure
    begin
      Inc(LCount);
    end);
  Check(Assigned(LReg), 'Register до отмены возвращает подписку');
  Check(not LSource.IsCancelled, 'новый токен не отменён');
  Check(not LSource.WaitFor(0), 'WaitFor(0) до отмены = False');
  SourceOf(LSource).Cancel;
  SourceOf(LSource).Cancel;
  CheckEquals(1, LCount, 'Cancel идемпотентен: колбэк вызван один раз');
  Check(LSource.IsCancelled, 'IsCancelled после Cancel');
  Check(LSource.WaitFor(0), 'WaitFor(0) после отмены = True');
  Check(Raises(
    procedure
    begin
      LSource.ThrowIfCancelled;
    end, ETgCancelledError), 'ThrowIfCancelled → ETgCancelledError');
  LReg := nil;

  // Подписка на уже отменённый токен — колбэк сразу.
  LCount := 0;
  LReg := LSource.Register(
    procedure
    begin
      Inc(LCount);
    end);
  CheckEquals(1, LCount, 'Register после отмены вызывает колбэк сразу');
  Check(not Assigned(LReg), 'Register после отмены возвращает nil');

  // Отписка освобождением ссылки.
  LSource := TTgCancellationSource.Create;
  LCount := 0;
  LReg := LSource.Register(
    procedure
    begin
      Inc(LCount);
    end);
  LReg := nil;
  SourceOf(LSource).Cancel;
  CheckEquals(0, LCount, 'после отписки колбэк не вызывается');

  // Исключение колбэка поглощается, остальные колбэки вызываются.
  LSource := TTgCancellationSource.Create;
  LCount := 0;
  LReg := LSource.Register(
    procedure
    begin
      raise Exception.Create('сбой колбэка');
    end);
  LReg2 := LSource.Register(
    procedure
    begin
      Inc(LCount);
    end);
  Check(not Raises(
    procedure
    begin
      SourceOf(LSource).Cancel;
    end, Exception), 'исключение колбэка не выходит из Cancel');
  CheckEquals(1, LCount, 'остальные колбэки вызваны');
  LReg := nil;
  LReg2 := nil;

  // Связанные токены.
  LParent := TTgCancellationSource.Create;
  LChild := TTgCancellationSource.Create(LParent);
  SourceOf(LChild).Cancel;
  Check(not LParent.IsCancelled, 'отмена ребёнка не отменяет родителя');
  LChild := TTgCancellationSource.Create(LParent);
  SourceOf(LParent).Cancel;
  Check(LChild.IsCancelled, 'отмена родителя отменяет ребёнка');
  LChild := TTgCancellationSource.Create(LParent);
  Check(LChild.IsCancelled, 'ребёнок отменённого родителя отменён сразу');

  // Освобождённые дети отписываются от родителя (иначе — use-after-free при Cancel).
  LParent := TTgCancellationSource.Create;
  LCount := 0;
  for I := 1 to 1000 do
  begin
    LChild := TTgCancellationSource.Create(LParent);
    LReg := LChild.Register(
      procedure
      begin
        Inc(LCount);
      end);
    LReg := nil;
  end;
  LChild := TTgCancellationSource.Create(LParent);
  LReg := LChild.Register(
    procedure
    begin
      Inc(LCount);
    end);
  ChurnHeap;
  SourceOf(LParent).Cancel;
  CheckEquals(1, LCount, '1000 освобождённых детей отписаны, живой ребёнок отменён');
  LReg := nil;
  LChild := nil;
  // Ребёнок переживает родителя (родителя держит подписка ребёнка).
  LParent := TTgCancellationSource.Create;
  LChild := TTgCancellationSource.Create(LParent);
  LParent := nil;
  Check(not LChild.IsCancelled, 'ребёнок после освобождения ссылки на родителя');
  LChild := nil;

  // Linked(A, B).
  A := TTgCancellationSource.Create;
  B := TTgCancellationSource.Create;
  Check(TTgCancellationSource.Linked(nil, B) = B, 'Linked(nil, B) = B');
  Check(TTgCancellationSource.Linked(A, nil) = A, 'Linked(A, nil) = A');
  Check(TTgCancellationSource.Linked(A, A) = A, 'Linked(A, A) = A');
  Check(not Assigned(TTgCancellationSource.Linked(nil, nil)), 'Linked(nil, nil) = nil');
  LLinked := TTgCancellationSource.Linked(A, B);
  Check((LLinked <> A) and (LLinked <> B), 'Linked(A, B) — новый токен');
  SourceOf(B).Cancel;
  Check(LLinked.IsCancelled, 'Linked(A, B) отменён вместе с B');
  Check(not A.IsCancelled, 'A не затронут');

  // WaitFor: таймаут и прерывание отменой.
  LSource := TTgCancellationSource.Create;
  Check(not LSource.WaitFor(30), 'WaitFor по таймауту = False');
  CancelLater(LSource, 50);
  LWatch := TStopwatch.StartNew;
  Check(LSource.WaitFor(10000), 'WaitFor прерван отменой');
  GWaitWakeMs := LWatch.ElapsedMilliseconds;
  Check(GWaitWakeMs < 150, Format('WaitFor проснулся < 100 мс после Cancel (всего %d мс, Cancel через 50 мс)',
    [GWaitWakeMs]));
end;

procedure TestCancellationSourceOwnership;
const
  CStressThreads = 4;
  CStressIterations = 10000;
var
  LSource, LParent, LChild, A, B, LNext, LOld: ITgCancellationSource;
  LToken, LLinked: ITgCancellation;
  LReg, LReg2: IInterface;
  LProbe, LProbe2: ICancelProbe;
  LLiveBefore: Integer;
  LLock: TCriticalSection;
  LCurrent: ITgCancellationSource;
  LThreads: array[0..CStressThreads - 1] of TThread;
  LDone, LErrors, LNilWithoutCall, LCancels: Integer;
  LFirstError: string;
  LOwner: TCancelButtonOwner;
  LWatch: TStopwatch;
  I: Integer;
begin
  LLiveBefore := TInterlocked.CompareExchange(GCancelProbeLive, 0, 0);

  // New + Cancel через интерфейс.
  LSource := TTgCancellationSource.New;
  LToken := LSource;
  Check(Supports(LToken, ITgCancellationSource), 'New: токен поддерживает ITgCancellationSource');
  LProbe := TCancelProbe.Create;
  LReg := RegisterProbe(LSource, LProbe);
  Check(Assigned(LReg), 'New: Register до отмены возвращает подписку');
  Check(not LToken.IsCancelled, 'New: новый источник не отменён');
  LSource.Cancel;
  LSource.Cancel;
  CheckEquals(1, LProbe.Calls, 'ITgCancellationSource.Cancel идемпотентен: колбэк вызван один раз');
  Check(LToken.IsCancelled and LToken.WaitFor(0), 'ITgCancellationSource.Cancel: токен отменён');
  LReg := nil;

  // Register после отмены — колбэк сразу, подписки нет.
  LProbe := TCancelProbe.Create;
  LReg := RegisterProbe(LSource, LProbe);
  CheckEquals(1, LProbe.Calls, 'New: Register после отмены вызывает колбэк сразу');
  Check(not Assigned(LReg), 'New: Register после отмены возвращает nil');

  // Отписка: освобождение подписки снимает только её колбэк.
  LSource := TTgCancellationSource.New;
  LProbe := TCancelProbe.Create;
  LProbe2 := TCancelProbe.Create;
  LReg := RegisterProbe(LSource, LProbe);
  LReg2 := RegisterProbe(LSource, LProbe2);
  LReg := nil;
  LSource.Cancel;
  CheckEquals(0, LProbe.Calls, 'отписанный колбэк не вызывается');
  CheckEquals(1, LProbe2.Calls, 'оставшийся колбэк вызван');
  // Отписка после отмены — без последствий.
  LReg2 := nil;

  // Связанный источник: отмена родителя отменяет ребёнка и его подписчиков.
  LParent := TTgCancellationSource.New;
  LChild := TTgCancellationSource.New(LParent);
  LProbe := TCancelProbe.Create;
  LReg := RegisterProbe(LChild, LProbe);
  LParent.Cancel;
  Check(LChild.IsCancelled, 'New(AParent): отмена родителя отменяет ребёнка');
  CheckEquals(1, LProbe.Calls, 'New(AParent): подписчик ребёнка вызван');
  LReg := nil;
  LChild := TTgCancellationSource.New(LParent);
  Check(LChild.IsCancelled, 'New(AParent): ребёнок отменённого родителя отменён сразу');
  LParent := TTgCancellationSource.New;
  LChild := TTgCancellationSource.New(LParent);
  LChild.Cancel;
  Check(not LParent.IsCancelled, 'New(AParent): отмена ребёнка не отменяет родителя');
  // Ребёнок переживает ссылку на родителя (родителя держит подписка ребёнка).
  LParent := TTgCancellationSource.New;
  LChild := TTgCancellationSource.New(LParent);
  LParent := nil;
  Check(not LChild.IsCancelled, 'New(AParent): ребёнок после освобождения ссылки на родителя');
  LChild.Cancel;
  Check(LChild.IsCancelled, 'New(AParent): ребёнок без ссылки на родителя отменяется сам');
  LToken := nil;

  // Linked с источниками-интерфейсами.
  A := TTgCancellationSource.New;
  B := TTgCancellationSource.New;
  LLinked := TTgCancellationSource.Linked(A, B);
  Check(Supports(LLinked, ITgCancellationSource), 'Linked(A, B) — новый источник');
  A.Cancel;
  Check(LLinked.IsCancelled, 'Linked(A, B) отменён вместе с A');
  Check(not B.IsCancelled, 'Linked(A, B): B не затронут');
  LLinked := nil;
  A := nil;
  B := nil;
  LParent := nil;
  LChild := nil;
  LSource := nil;
  LProbe := nil;
  LProbe2 := nil;

  // Без циклов ссылок: подписка переживает ссылку на источник, затем всё освобождается.
  LSource := TTgCancellationSource.New;
  LProbe := TCancelProbe.Create;
  LReg := RegisterProbe(LSource, LProbe);
  LSource := nil;
  LProbe := nil;
  LReg := nil;
  CheckEquals(LLiveBefore, TInterlocked.CompareExchange(GCancelProbeLive, 0, 0),
    'источник, подписка и колбэк освобождены (нет циклов ссылок)');

  // Стресс: Register/отписка из 4 потоков параллельно с Cancel.
  for I := 0 to High(LThreads) do
    LThreads[I] := nil;
  LDone := 0;
  LErrors := 0;
  LNilWithoutCall := 0;
  LCancels := 0;
  LFirstError := '';
  LLock := TCriticalSection.Create;
  try
    LCurrent := TTgCancellationSource.New;
    try
      for I := 0 to High(LThreads) do
      begin
        LThreads[I] := TThread.CreateAnonymousThread(
          procedure
          var
            N: Integer;
            LSrc: ITgCancellationSource;
            LP: ICancelProbe;
            LR: IInterface;
            LKept: TArray<IInterface>;
          begin
            try
              for N := 1 to CStressIterations do
              begin
                LLock.Enter;
                try
                  LSrc := LCurrent;
                finally
                  LLock.Leave;
                end;
                LP := TCancelProbe.Create;
                LR := RegisterProbe(LSrc, LP);
                // nil — только если отмена уже была: колбэк обязан быть вызван.
                if not Assigned(LR) and (LP.Calls <> 1) then
                  TInterlocked.Increment(LNilWithoutCall);
                // Часть подписок отпускается позже — возможно, после Cancel.
                if N mod 4 = 0 then
                  LKept := LKept + [LR];
                LR := nil;
                if Length(LKept) >= 64 then
                  LKept := nil;
              end;
              LKept := nil;
              LP := nil;
              LSrc := nil;
            except
              on E: Exception do
                if TInterlocked.Increment(LErrors) = 1 then
                  LFirstError := E.ClassName + ': ' + E.Message;
            end;
            TInterlocked.Increment(LDone);
          end);
        LThreads[I].FreeOnTerminate := False;
      end;
      for I := 0 to High(LThreads) do
        LThreads[I].Start;
      while TInterlocked.CompareExchange(LDone, 0, 0) < CStressThreads do
      begin
        LNext := TTgCancellationSource.New;
        LLock.Enter;
        try
          LOld := LCurrent;
          LCurrent := LNext;
        finally
          LLock.Leave;
        end;
        LNext := nil;
        LOld.Cancel;
        LOld := nil;
        Inc(LCancels);
        TThread.Yield;
      end;
    finally
      for I := 0 to High(LThreads) do
        LThreads[I].Free;
    end;
    LCurrent.Cancel;
    LCurrent := nil;
  finally
    LLock.Free;
  end;
  CheckEquals(0, LErrors, 'стресс: исключений в потоках нет (' + LFirstError + ')');
  CheckEquals(0, LNilWithoutCall, 'стресс: Register вернул nil только с уже вызванным колбэком');
  Check(LCancels > 0, 'стресс: Cancel выполнялся параллельно с подписками');
  CheckEquals(LLiveBefore, TInterlocked.CompareExchange(GCancelProbeLive, 0, 0),
    Format('стресс: %d x %d подписок и %d отмен — все колбэки освобождены',
    [CStressThreads, CStressIterations, LCancels]));

  // Сценарий «кнопка Cancel»: источник только в поле-интерфейсе, отмена из другого метода.
  LOwner := TCancelButtonOwner.Create;
  try
    LOwner.StartWork;
    TThread.Sleep(30);
    CheckEquals(0, LOwner.WorkerSawCancel.Calls, 'кнопка Cancel: до нажатия работа идёт');
    LWatch := TStopwatch.StartNew;
    LOwner.CancelClick;
    LOwner.WaitWorker;
    Check(LWatch.ElapsedMilliseconds < 5000,
      Format('кнопка Cancel: поток завершён после отмены (%d мс)', [LWatch.ElapsedMilliseconds]));
    CheckEquals(1, LOwner.WorkerSawCancel.Calls, 'кнопка Cancel: рабочий поток увидел отмену');
    CheckEquals(1, LOwner.CallbackProbe.Calls, 'кнопка Cancel: подписчик вызван');
    LOwner.CancelClick;
    CheckEquals(1, LOwner.CallbackProbe.Calls, 'кнопка Cancel: повторное нажатие ничего не делает');
  finally
    LOwner.Free;
  end;
  CheckEquals(LLiveBefore, TInterlocked.CompareExchange(GCancelProbeLive, 0, 0),
    'кнопка Cancel: после Free владельца всё освобождено');
end;

procedure TestCancelScope;
var
  A, B, C: ITgCancellation;
  LScopeA, LScopeB, LScopeNil: TTgCancelScope;
  LThread: TThread;
  LThreadSawNil, LThreadSawC, LThreadRestored: Boolean;
begin
  A := TTgCancellationSource.Create;
  B := TTgCancellationSource.Create;
  C := TTgCancellationSource.Create;
  Check(not (TTgCancelScope.Current <> nil), 'вне области токена нет');
  LScopeA := TTgCancelScope.Enter(A);
  Check(TTgCancelScope.Current = A, 'Enter(A)');
  LScopeB := TTgCancelScope.Enter(B);
  Check(TTgCancelScope.Current = B, 'вложенная Enter(B)');
  LScopeNil := TTgCancelScope.Enter(nil);
  Check(not (TTgCancelScope.Current <> nil), 'Enter(nil) отключает окружающий токен');
  LScopeNil.Leave;
  Check(TTgCancelScope.Current = B, 'Leave восстанавливает B');

  LThreadSawNil := False;
  LThreadSawC := False;
  LThreadRestored := False;
  LThread := TThread.CreateAnonymousThread(
    procedure
    var
      LScope: TTgCancelScope;
    begin
      LThreadSawNil := not (TTgCancelScope.Current <> nil);
      LScope := TTgCancelScope.Enter(C);
      try
        LThreadSawC := TTgCancelScope.Current = C;
      finally
        LScope.Leave;
      end;
      LThreadRestored := not (TTgCancelScope.Current <> nil);
    end);
  LThread.FreeOnTerminate := False;
  LThread.Start;
  LThread.WaitFor;
  LThread.Free;
  Check(LThreadSawNil, 'в другом потоке своя (пустая) область');
  Check(LThreadSawC, 'Enter в другом потоке');
  Check(LThreadRestored, 'Leave в другом потоке');
  Check(TTgCancelScope.Current = B, 'другой поток не затронул текущий');

  LScopeB.Leave;
  Check(TTgCancelScope.Current = A, 'Leave(B) → A');
  LScopeB.Leave;
  Check(TTgCancelScope.Current = A, 'повторный Leave ничего не делает');
  LScopeA.Leave;
  Check(not (TTgCancelScope.Current <> nil), 'все области закрыты');
end;

procedure TestCallCancellation;
var
  LApi, LPlainApi: TTgApi;
  LTransport: TFakeTransport;
  LPlain: TPlainTransport;
  LPlainRef: ITgTransport;
  LSource, LFresh, LDuring: ITgCancellation;
  LScope: TTgCancelScope;
  LWatch: TStopwatch;
  LRaised: Boolean;
  LElapsed: Int64;
begin
  LApi := NewApi(
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    var
      LToken: ITgCancellation;
    begin
      LToken := TTgCancelScope.Current;
      if (AMethod = 'getMe') and Assigned(LToken) then
      begin
        LToken.WaitFor(50000);
        LToken.ThrowIfCancelled;
      end;
      Result := JsonOf('{"id":1,"is_bot":true,"first_name":"Бот"}');
    end, LTransport);
  try
    // Окружающий токен: подменный ExecuteEx ждёт ACancel.WaitFor(50000).
    LSource := TTgCancellationSource.Create;
    CancelLater(LSource, 100);
    LWatch := TStopwatch.StartNew;
    LScope := TTgCancelScope.Enter(LSource);
    try
      LRaised := Raises(
        procedure
        begin
          LApi.GetMe;
        end, ETgCancelledError);
    finally
      LScope.Leave;
    end;
    LElapsed := LWatch.ElapsedMilliseconds;
    Check(LRaised, 'отмена окружающего токена → ETgCancelledError');
    Check(LElapsed < 1000, Format('вызов завершён < 1 с (%d мс)', [LElapsed]));
    Check(LTransport.ExCalls > 0, 'вызов шёл через ExecuteEx');

    // Явный токен (перегрузка Call) важнее окружающего.
    LFresh := TTgCancellationSource.Create;
    LScope := TTgCancelScope.Enter(LSource);
    try
      Check(not Raises(
        procedure
        begin
          LApi.Call('quick', nil, LFresh).Free;
        end, Exception), 'Call(..., ACancel): явный токен заменяет окружающий');
    finally
      LScope.Leave;
    end;
    Check(Raises(
      procedure
      begin
        LApi.Call('getMe', nil, LSource).Free;
      end, ETgCancelledError), 'Call(..., ACancel) с отменённым токеном');
  finally
    LApi.Free;
  end;

  // Транспорт без токенов: проверка до и после вызова.
  LDuring := TTgCancellationSource.Create;
  LPlain := TPlainTransport.Create(
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      Result := TJSONTrue.Create;
      if AMethod = 'cancelDuring' then
        SourceOf(LDuring).Cancel;
    end);
  LPlainRef := LPlain;
  LPlainApi := TTgApi.Create(LPlainRef);
  try
    LScope := TTgCancelScope.Enter(LSource);
    try
      Check(Raises(
        procedure
        begin
          LPlainApi.Call('x').Free;
        end, ETgCancelledError), 'простой транспорт: отменённый токен → ETgCancelledError');
    finally
      LScope.Leave;
    end;
    CheckEquals(0, LPlain.Calls, 'простой транспорт не вызывался при отменённом токене');
    Check(Raises(
      procedure
      begin
        LPlainApi.Call('cancelDuring', nil, LDuring).Free;
      end, ETgCancelledError), 'простой транспорт: отмена во время вызова — результат отброшен');
    CheckEquals(1, LPlain.Calls, 'простой транспорт вызван один раз');
    Check(not Raises(
      procedure
      begin
        LPlainApi.Call('ok').Free;
      end, Exception), 'простой транспорт: обычный вызов');
  finally
    LPlainApi.Free;
  end;
end;

/// <summary>Транспорт-заглушка с ответами: retry → 429, getUpdates → 409, иначе — сообщение.</summary>
function NewStubTransport(const ASettings: TTgHttpSettings): TStubHttpTransport;
begin
  Result := TStubHttpTransport.Create(ASettings,
    function(const AMethod: string): TTgHttpResponse
    begin
      if AMethod = 'retry' then
        Result := StubResponse(429, '{"ok":false,"error_code":429,' +
          '"description":"Too Many Requests: retry after 30","parameters":{"retry_after":30}}')
      else if AMethod = 'getUpdates' then
        Result := StubResponse(409, '{"ok":false,"error_code":409,' +
          '"description":"Conflict: terminated by other getUpdates request"}')
      else
        Result := StubResponse(200, '{"ok":true,"result":' + CShortMessageJson + '}');
    end);
end;

procedure TestTransportWaitsCancel;
var
  LSettings: TTgHttpSettings;
  LStub: TStubHttpTransport;
  LRef: ITgCancellableTransport;
  LSource: ITgCancellation;
  LParams: TTgParams;
  LWatch: TStopwatch;
  LElapsed: Int64;
  LSends: Integer;
begin
  LSettings := TTgHttpSettings.Create('123456:TEST');
  LSettings.GlobalRatePerSec := 0;
  LSettings.PerChatIntervalMs := 60000;
  LSettings.MaxRetryAfterSec := 120;
  LStub := NewStubTransport(LSettings);
  LRef := LStub;

  // retry_after = 30 с прерывается токеном операции.
  LSource := TTgCancellationSource.Create;
  CancelLater(LSource, 100);
  LWatch := TStopwatch.StartNew;
  Check(Raises(
    procedure
    begin
      LRef.ExecuteEx('retry', nil, LSource).Free;
    end, ETgCancelledError), 'ожидание retry_after прервано токеном');
  LElapsed := LWatch.ElapsedMilliseconds;
  Check(LElapsed < 1000, Format('retry_after: прервано < 1 с (%d мс)', [LElapsed]));
  CheckEquals(1, LStub.Sends, 'запрос до ожидания отправлен один раз');
  Check(LStub.SawToken, 'SendRequest видит токен операции (TTgCancelScope.Current)');

  // Лимит на чат (60 с) прерывается токеном операции.
  LParams := TTgParams.Create;
  try
    LParams.Add('chat_id', Int64(42)).Add('text', 'лимит');
    LRef.ExecuteEx('sendMessage', LParams, nil).Free;
    LSends := LStub.Sends;
    LSource := TTgCancellationSource.Create;
    CancelLater(LSource, 100);
    LWatch := TStopwatch.StartNew;
    Check(Raises(
      procedure
      begin
        LRef.ExecuteEx('sendMessage', LParams, LSource).Free;
      end, ETgCancelledError), 'ожидание лимитёра прервано токеном');
    LElapsed := LWatch.ElapsedMilliseconds;
    Check(LElapsed < 1000, Format('лимитёр: прервано < 1 с (%d мс)', [LElapsed]));
    CheckEquals(LSends, LStub.Sends, 'прерванный по лимиту запрос не отправлялся');
  finally
    LParams.Free;
  end;

  // Устаревшая глобальная отмена транспорта и её сброс.
  LRef.Cancel;
  Check(LRef.IsCancelled, 'Cancel транспорта: IsCancelled');
  Check(Raises(
    procedure
    begin
      LRef.ExecuteEx('getMe', nil, nil).Free;
    end, ETgCancelledError), 'Cancel транспорта прерывает вызовы');
  LRef.ResetCancel;
  Check(not LRef.IsCancelled, 'ResetCancel снимает отмену');
  Check(not Raises(
    procedure
    begin
      LRef.Execute('getMe', nil).Free;
    end, Exception), 'после ResetCancel транспорт работает');
end;

procedure TestConflict409;
var
  LStub: TStubHttpTransport;
  LRef: ITgTransport;
  LApi: TTgApi;
  LUpdates: TArray<ITgUpdate>;
  LError: TTgErrorInfo;
  LClass: string;
  LCode: Integer;
  LMessage: string;
begin
  LStub := NewStubTransport(TTgHttpSettings.Create('123456:TEST'));
  LRef := LStub;
  LApi := TTgApi.Create(LRef);
  try
    LClass := '';
    LCode := 0;
    try
      LApi.GetUpdates;
    except
      on E: ETgApiError do
      begin
        LClass := E.ClassName;
        LCode := E.ErrorCode;
        LMessage := E.Message;
      end;
    end;
    CheckEquals('ETgConflictError', LClass, '409 → ETgConflictError (наследник ETgApiError)');
    CheckEquals(409, LCode, 'ErrorCode = 409');
    Check(Contains('другой экземпляр', LMessage), 'текст-подсказка (RU)');
    Check(not LApi.TryGetUpdates(LUpdates, LError), 'TryGetUpdates = False');
    Check(LError.Kind = TTgErrorKind.Api, 'TTgErrorInfo.Kind = Api');
    CheckEquals('ETgConflictError', LError.ExceptionClassName, 'TTgErrorInfo.ExceptionClassName');
    CheckEquals('Conflict: terminated by other getUpdates request', LError.Description,
      'Description от Telegram');
  finally
    LApi.Free;
  end;
end;

procedure TestDestroyWithHangingAsync;
var
  LShared: TFakeTransport;
  LSharedRef: ITgTransport;
  LApi, LApi2: TTgApi;
  LHang, LEntered, LSuccess, LCancelled, LOther: Integer;
  LWatch: TStopwatch;
  I: Integer;
  LUser, LUser2: ITgUser;
  LTask: ITask;
begin
  LHang := 1;
  LEntered := 0;
  LSuccess := 0;
  LCancelled := 0;
  LOther := 0;
  LShared := TFakeTransport.Create(HangingHandler(@LHang, @LEntered));
  LSharedRef := LShared;
  LApi := TTgApi.Create(LSharedRef);
  try
    for I := 1 to 10 do
      LApi.GetMeAsync(
        procedure(AUser: ITgUser)
        begin
          TInterlocked.Increment(LSuccess);
        end,
        procedure(AError: Exception)
        begin
          if AError is ETgCancelledError then
            TInterlocked.Increment(LCancelled)
          else
            TInterlocked.Increment(LOther);
        end);
    Check(WaitUntil(
      function: Boolean
      begin
        Result := TInterlocked.CompareExchange(LEntered, 0, 0) = 10;
      end, 5000), '10 Async-вызовов висят в транспорте');
  finally
    LWatch := TStopwatch.StartNew;
    LApi.Free;
    GDestroyHangingMs := LWatch.ElapsedMilliseconds;
  end;
  Check(GDestroyHangingMs < 1000, Format('деструктор < 1 с (%d мс)', [GDestroyHangingMs]));
  Check(WaitUntil(
    function: Boolean
    begin
      Result := TInterlocked.CompareExchange(LSuccess, 0, 0) +
        TInterlocked.CompareExchange(LCancelled, 0, 0) +
        TInterlocked.CompareExchange(LOther, 0, 0) = 10;
    end, 5000), 'все 10 колбэков вызваны');
  CheckEquals(10, LCancelled + LSuccess, 'колбэки: ETgCancelledError или успех');
  CheckEquals(0, LOther, 'других ошибок нет');
  CheckEquals(0, LShared.CancelCalls, 'общий транспорт не отменялся');
  Check(not LSharedRef.IsCancelled, 'общий транспорт не в состоянии отмены');

  // Тот же транспорт с новым клиентом — без «отравления».
  TInterlocked.Exchange(LHang, 0);
  LApi2 := TTgApi.Create(LSharedRef);
  try
    LUser := LApi2.GetMe;
    Check(Assigned(LUser) and (LUser.FirstName = 'Бот'), 'новый клиент: синхронный вызов');
    LUser2 := nil;
    LTask := LApi2.GetMeAsync(
      procedure(AUser: ITgUser)
      begin
        LUser2 := AUser;
      end);
    Check(LTask.Wait(5000) and Assigned(LUser2), 'новый клиент: Async-вызов');
  finally
    LApi2.Free;
  end;
end;

procedure TestGateWithUserPool;
var
  LPool, LSeen: TThreadPool;
  LTransport: TFakeTransport;
  LApi: TTgApi;
  LHang, LEntered, LSuccess, LCancelled, I: Integer;
  LToken: ITgCancellation;
  LScopeOk: Boolean;
  LWatch: TStopwatch;
begin
  LPool := TThreadPool.Create;
  try
    // Один рабочий поток: первая задача висит, остальные стоят в очереди.
    LPool.SetMinWorkerThreads(1);
    LPool.SetMaxWorkerThreads(1);
{$IF CompilerVersion >= 36}
    // Delphi 12: иначе при блокировке всех потоков пул превышает максимум.
    LPool.UnlimitedWorkerThreadsWhenBlocked := False;
{$IFEND}
    LHang := 0;
    LEntered := 0;
    LSuccess := 0;
    LCancelled := 0;
    LTransport := TFakeTransport.Create(HangingHandler(@LHang, @LEntered));
    LApi := TTgApi.Create(LTransport as ITgTransport, LPool);
    try
      Check(LApi.ThreadPool = LPool, 'ThreadPool — пул пользователя');
      LToken := LApi.CancelToken;
      LSeen := nil;
      LScopeOk := False;
      Check(LApi.RunAsync<Boolean>(
        function: Boolean
        begin
          LSeen := TThreadPool.Current;
          LScopeOk := TTgCancelScope.Current = LToken;
          Result := True;
        end, nil, nil).Wait(5000), 'RunAsync в пуле пользователя');
      Check(LSeen = LPool, 'задача выполнялась в пуле пользователя');
      Check(LScopeOk, 'окружающий токен задачи — токен клиента');
      LToken := nil;

      LHang := 1;
      for I := 1 to 4 do
        LApi.GetMeAsync(
          procedure(AUser: ITgUser)
          begin
            TInterlocked.Increment(LSuccess);
          end,
          procedure(AError: Exception)
          begin
            if AError is ETgCancelledError then
              TInterlocked.Increment(LCancelled);
          end);
      Check(WaitUntil(
        function: Boolean
        begin
          Result := TInterlocked.CompareExchange(LEntered, 0, 0) = 1;
        end, 5000), 'первый вызов висит, остальные в очереди');
    finally
      LWatch := TStopwatch.StartNew;
      LApi.Free;
      GDestroyUserPoolMs := LWatch.ElapsedMilliseconds;
    end;
    Check(GDestroyUserPoolMs < 1000, Format('деструктор < 1 с (%d мс)', [GDestroyUserPoolMs]));
    Check(WaitUntil(
      function: Boolean
      begin
        Result := TInterlocked.CompareExchange(LCancelled, 0, 0) +
          TInterlocked.CompareExchange(LSuccess, 0, 0) = 4;
      end, 5000), 'все 4 колбэка вызваны');
    CheckEquals(4, LCancelled, 'все 4 получили ETgCancelledError');
    CheckEquals(1, LEntered, 'задачи после закрытия шлюза не выполняли вызов');
  finally
    LPool.Free;
  end;
end;

procedure TestLibraryPool;
var
  LApi: TTgApi;
  LTransport: TFakeTransport;
  LSeen, LHandlerPool: TThreadPool;
  LOldMax: Integer;
  LUser: ITgUser;
begin
  LHandlerPool := nil;
  LApi := NewApi(
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      LHandlerPool := TThreadPool.Current;
      Result := JsonOf('{"id":1,"is_bot":true,"first_name":"Бот"}');
    end, LTransport);
  try
    Check(LApi.ThreadPool = TgBotThreadPool, 'ThreadPool по умолчанию — пул библиотеки');
    Check(TgBotThreadPool <> TThreadPool.Default, 'пул библиотеки ≠ TThreadPool.Default');
    LSeen := nil;
    Check(LApi.RunAsync<Boolean>(
      function: Boolean
      begin
        LSeen := TThreadPool.Current;
        Result := True;
      end, nil, nil).Wait(5000), 'RunAsync завершился');
    Check(LSeen = TgBotThreadPool, 'RunAsync — в пуле библиотеки');
    LUser := nil;
    Check(LApi.GetMeAsync(
      procedure(AUser: ITgUser)
      begin
        LUser := AUser;
      end).Wait(5000) and Assigned(LUser), 'GetMeAsync завершился');
    Check(LHandlerPool = TgBotThreadPool, 'сгенерированный Async — в пуле библиотеки');
  finally
    LApi.Free;
  end;
  LOldMax := TgBotThreadPool.MaxWorkerThreads;
  CheckEquals(Max(TgDefaultAsyncPoolSize, TThread.ProcessorCount * 2), LOldMax,
    'максимум потоков пула по умолчанию');
  TgSetAsyncPoolSize(48);
  CheckEquals(48, TgBotThreadPool.MaxWorkerThreads, 'TgSetAsyncPoolSize');
  TgSetAsyncPoolSize(LOldMax);
  Check(Raises(
    procedure
    begin
      TgSetAsyncPoolSize(0);
    end, EArgumentOutOfRangeException), 'TgSetAsyncPoolSize(0) → EArgumentOutOfRangeException');
end;

{$IFDEF MSWINDOWS}
procedure TestRealHttpCancel;
var
  LData: TWSAData;
  LSocket: TSocket;
  LAddr: TSockAddrIn;
  LLen: Integer;
  LSettings: TTgHttpSettings;
  LApi: TTgApi;
  LSource: ITgCancellation;
  LWatch: TStopwatch;
  LRaised: Boolean;
  LError: string;
  LAsyncCancelled, LAsyncOther: Integer;
begin
  Check(WSAStartup($0202, LData) = 0, 'WSAStartup');
  // «Молчащий» сервер: слушающий сокет без accept — ядро принимает соединение
  // и запрос, но ответа нет; запрос висит до таймаута ответа (30 с).
  LSocket := socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  try
    Check(LSocket <> INVALID_SOCKET, 'socket');
    FillChar(LAddr, SizeOf(LAddr), 0);
    LAddr.sin_family := AF_INET;
    LAddr.sin_addr.S_addr := htonl(INADDR_LOOPBACK);
    Check(bind(LSocket, TSockAddr(LAddr), SizeOf(LAddr)) = 0, 'bind');
    Check(listen(LSocket, 16) = 0, 'listen');
    LLen := SizeOf(LAddr);
    Check(getsockname(LSocket, TSockAddr(LAddr), LLen) = 0, 'getsockname');
    LSettings := TTgHttpSettings.Create('123456:TEST');
    LSettings.ApiUrl := 'http://127.0.0.1:' + IntToStr(ntohs(LAddr.sin_port));
    LSettings.ResponseTimeoutMs := 30000;
    LSettings.GlobalRatePerSec := 0;
    LAsyncCancelled := 0;
    LAsyncOther := 0;
    LApi := TTgApi.Create(LSettings);
    try
      // Синхронный вызов с явным токеном: Cancel через 300 мс.
      LSource := TTgCancellationSource.Create;
      CancelLater(LSource, 300);
      LWatch := TStopwatch.StartNew;
      LRaised := False;
      LError := '';
      try
        LApi.Call('getMe', nil, LSource).Free;
      except
        on E: ETgCancelledError do
          LRaised := True;
        on E: Exception do
          LError := E.ClassName + ': ' + E.Message;
      end;
      GRealHttpCancelMs := LWatch.ElapsedMilliseconds;
      Check(LRaised, 'реальный HTTP-запрос прерван отменой ' + LError);
      Check(GRealHttpCancelMs < 1300, Format('прерван < 1 с после Cancel (всего %d мс, Cancel через 300 мс)',
        [GRealHttpCancelMs]));

      // Async-вызов висит в реальном запросе — деструктор прерывает его.
      LApi.GetMeAsync(
        procedure(AUser: ITgUser)
        begin
          TInterlocked.Increment(LAsyncOther);
        end,
        procedure(AError: Exception)
        begin
          if AError is ETgCancelledError then
            TInterlocked.Increment(LAsyncCancelled)
          else
            TInterlocked.Increment(LAsyncOther);
        end);
      TThread.Sleep(300);
    finally
      LWatch := TStopwatch.StartNew;
      LApi.Free;
      GRealHttpDestroyMs := LWatch.ElapsedMilliseconds;
    end;
    Check(GRealHttpDestroyMs < 1000, Format('деструктор с висящим реальным запросом < 1 с (%d мс)',
      [GRealHttpDestroyMs]));
    Check(WaitUntil(
      function: Boolean
      begin
        Result := TInterlocked.CompareExchange(LAsyncCancelled, 0, 0) +
          TInterlocked.CompareExchange(LAsyncOther, 0, 0) = 1;
      end, 5000), 'колбэк Async вызван');
    CheckEquals(1, LAsyncCancelled, 'Async получил ETgCancelledError');
  finally
    closesocket(LSocket);
    WSACleanup;
  end;
end;
{$ENDIF}

{ Фаза 5b: приём обновлений, диспетчер, контекст, TTgBot }

type
  /// <summary>
  ///   Потокобезопасный подменный транспорт: журнал вызовов (метод и JSON
  ///   параметров) под блокировкой, ответы — из обработчика (его вызывают
  ///   потоки источника и диспетчера одновременно). Только ITgTransport —
  ///   «неотменяемый» транспорт.
  /// </summary>
  TScriptTransport = class(TInterfacedObject, ITgTransport)
  private
    FLock: TCriticalSection;
    FMethods: TList<string>;
    FParams: TList<string>;
    FHandler: TFakeHandler;
  public
    constructor Create(const AHandler: TFakeHandler);
    destructor Destroy; override;
    function Execute(const AMethod: string; AParams: TTgParams): TJSONValue;
    procedure DownloadFile(const AFilePath: string; ADest: TStream);
    procedure Cancel;
    procedure ResetCancel;
    function IsCancelled: Boolean;
    /// <summary>Число вызовов метода AMethod.</summary>
    function Count(const AMethod: string): Integer;
    /// <summary>JSON параметров вызовов AMethod по порядку.</summary>
    function Calls(const AMethod: string): TArray<string>;
    /// <summary>Методы всех вызовов по порядку.</summary>
    function Methods: TArray<string>;
  end;

  /// <summary>Как TScriptTransport, но с токеном операции (окружающий токен в обработчике).</summary>
  TScriptCancellableTransport = class(TScriptTransport, ITgCancellableTransport)
  public
    function ExecuteEx(const AMethod: string; AParams: TTgParams;
      const ACancel: ITgCancellation): TJSONValue;
    procedure DownloadFileEx(const AFilePath: string; ADest: TStream;
      const ACancel: ITgCancellation);
  end;

  /// <summary>Потокобезопасный журнал чисел.</summary>
  TIdLog = class
  private
    FLock: TCriticalSection;
    FItems: TList<Int64>;
  public
    constructor Create;
    destructor Destroy; override;
    procedure Add(AValue: Int64);
    procedure Clear;
    function Count: Integer;
    function ToArray: TArray<Int64>;
  end;

  /// <summary>Потокобезопасный журнал строк.</summary>
  TTextLog = class
  private
    FLock: TCriticalSection;
    FItems: TStringList;
  public
    constructor Create;
    destructor Destroy; override;
    procedure Add(const AText: string);
    procedure Clear;
    function Has(const AText: string): Boolean;
    /// <summary>Сколько раз записан AText.</summary>
    function CountOf(const AText: string): Integer;
    /// <summary>Число записей.</summary>
    function Count: Integer;
    function Text: string;
  end;

  /// <summary>Подменные часы: паузы не ждут, время сдвигается на длительность паузы.</summary>
  TFakeTimer = class(TInterfacedObject, ITgPollTimer)
  private
    FLock: TCriticalSection;
    FNow: Int64;
    FSleeps: TList<Cardinal>;
  public
    constructor Create;
    destructor Destroy; override;
    function NowMs: Int64;
    function Sleep(AMs: Cardinal; const ACancel: ITgCancellation): Boolean;
    function Sleeps: TArray<Cardinal>;
  end;

const
  CWebhookConflict = 'Conflict: can''t use getUpdates method while webhook is active; ' +
    'use deleteWebhook to delete the webhook first';
  COtherConflict = 'Conflict: terminated by other getUpdates request; make sure that only ' +
    'one bot instance is running';

var
  GStopHangingMs: Int64 = -1;
  GStopAbandonMs: Int64 = -1;
  GDispatcherMainStopMs: Int64 = -1;
  GBotStopMs: Int64 = -1;
  GBotRunMs: Int64 = -1;
  GDownloadCancelMs: Int64 = -1;
  GDownloadRaceMaxMs: Int64 = -1;
  GMaxConcurrency: Integer = -1;
  // Замеры 6A2.
  GBotFreeHangingMs: Int64 = -1;
  GHandlerSwapGrowth: Int64 = -1;

{ TScriptTransport }

constructor TScriptTransport.Create(const AHandler: TFakeHandler);
begin
  inherited Create;
  FLock := TCriticalSection.Create;
  FMethods := TList<string>.Create;
  FParams := TList<string>.Create;
  FHandler := AHandler;
end;

destructor TScriptTransport.Destroy;
begin
  FreeAndNil(FParams);
  FreeAndNil(FMethods);
  FreeAndNil(FLock);
  inherited Destroy;
end;

function TScriptTransport.Execute(const AMethod: string; AParams: TTgParams): TJSONValue;
var
  LJson: string;
begin
  if Assigned(AParams) then
    LJson := AParams.ToJsonText
  else
    LJson := '{}';
  FLock.Enter;
  try
    FMethods.Add(AMethod);
    FParams.Add(LJson);
  finally
    FLock.Leave;
  end;
  Result := FHandler(AMethod, AParams);
end;

procedure TScriptTransport.DownloadFile(const AFilePath: string; ADest: TStream);
begin
end;

procedure TScriptTransport.Cancel;
begin
end;

procedure TScriptTransport.ResetCancel;
begin
end;

function TScriptTransport.IsCancelled: Boolean;
begin
  Result := False;
end;

function TScriptTransport.Count(const AMethod: string): Integer;
var
  LMethod: string;
begin
  Result := 0;
  FLock.Enter;
  try
    for LMethod in FMethods do
      if LMethod = AMethod then
        Inc(Result);
  finally
    FLock.Leave;
  end;
end;

function TScriptTransport.Calls(const AMethod: string): TArray<string>;
var
  I: Integer;
begin
  Result := nil;
  FLock.Enter;
  try
    for I := 0 to FMethods.Count - 1 do
      if FMethods[I] = AMethod then
        Result := Result + [FParams[I]];
  finally
    FLock.Leave;
  end;
end;

function TScriptTransport.Methods: TArray<string>;
begin
  FLock.Enter;
  try
    Result := FMethods.ToArray;
  finally
    FLock.Leave;
  end;
end;

{ TScriptCancellableTransport }

function TScriptCancellableTransport.ExecuteEx(const AMethod: string; AParams: TTgParams;
  const ACancel: ITgCancellation): TJSONValue;
var
  LScope: TTgCancelScope;
begin
  LScope := TTgCancelScope.Enter(ACancel);
  try
    Result := Execute(AMethod, AParams);
  finally
    LScope.Leave;
  end;
end;

procedure TScriptCancellableTransport.DownloadFileEx(const AFilePath: string; ADest: TStream;
  const ACancel: ITgCancellation);
begin
end;

{ TIdLog }

constructor TIdLog.Create;
begin
  inherited Create;
  FLock := TCriticalSection.Create;
  FItems := TList<Int64>.Create;
end;

destructor TIdLog.Destroy;
begin
  FreeAndNil(FItems);
  FreeAndNil(FLock);
  inherited Destroy;
end;

procedure TIdLog.Add(AValue: Int64);
begin
  FLock.Enter;
  try
    FItems.Add(AValue);
  finally
    FLock.Leave;
  end;
end;

procedure TIdLog.Clear;
begin
  FLock.Enter;
  try
    FItems.Clear;
  finally
    FLock.Leave;
  end;
end;

function TIdLog.Count: Integer;
begin
  FLock.Enter;
  try
    Result := FItems.Count;
  finally
    FLock.Leave;
  end;
end;

function TIdLog.ToArray: TArray<Int64>;
begin
  FLock.Enter;
  try
    Result := FItems.ToArray;
  finally
    FLock.Leave;
  end;
end;

{ TTextLog }

constructor TTextLog.Create;
begin
  inherited Create;
  FLock := TCriticalSection.Create;
  FItems := TStringList.Create;
end;

destructor TTextLog.Destroy;
begin
  FreeAndNil(FItems);
  FreeAndNil(FLock);
  inherited Destroy;
end;

procedure TTextLog.Add(const AText: string);
begin
  FLock.Enter;
  try
    FItems.Add(AText);
  finally
    FLock.Leave;
  end;
end;

procedure TTextLog.Clear;
begin
  FLock.Enter;
  try
    FItems.Clear;
  finally
    FLock.Leave;
  end;
end;

function TTextLog.CountOf(const AText: string): Integer;
var
  LItem: string;
begin
  Result := 0;
  FLock.Enter;
  try
    for LItem in FItems do
      if LItem = AText then
        Inc(Result);
  finally
    FLock.Leave;
  end;
end;

function TTextLog.Count: Integer;
begin
  FLock.Enter;
  try
    Result := FItems.Count;
  finally
    FLock.Leave;
  end;
end;

function TTextLog.Has(const AText: string): Boolean;
begin
  FLock.Enter;
  try
    Result := FItems.IndexOf(AText) >= 0;
  finally
    FLock.Leave;
  end;
end;

function TTextLog.Text: string;
begin
  FLock.Enter;
  try
    Result := FItems.CommaText;
  finally
    FLock.Leave;
  end;
end;

{ TFakeTimer }

constructor TFakeTimer.Create;
begin
  inherited Create;
  FLock := TCriticalSection.Create;
  FSleeps := TList<Cardinal>.Create;
end;

destructor TFakeTimer.Destroy;
begin
  FreeAndNil(FSleeps);
  FreeAndNil(FLock);
  inherited Destroy;
end;

function TFakeTimer.NowMs: Int64;
begin
  FLock.Enter;
  try
    Result := FNow;
  finally
    FLock.Leave;
  end;
end;

function TFakeTimer.Sleep(AMs: Cardinal; const ACancel: ITgCancellation): Boolean;
begin
  FLock.Enter;
  try
    FSleeps.Add(AMs);
    Inc(FNow, AMs);
  finally
    FLock.Leave;
  end;
  Result := Assigned(ACancel) and ACancel.IsCancelled;
end;

function TFakeTimer.Sleeps: TArray<Cardinal>;
begin
  FLock.Enter;
  try
    Result := FSleeps.ToArray;
  finally
    FLock.Leave;
  end;
end;

{ Хелперы 5b }

/// <summary>JSON обновления с текстовым сообщением.</summary>
function MsgUpdate(AId, AChat, AFrom: Int64; const AText: string): string;
begin
  Result := Format('{"update_id":%d,"message":{"message_id":%d,"date":1,' +
    '"chat":{"id":%d,"type":"private"},"from":{"id":%d,"is_bot":false,"first_name":"U"},' +
    '"text":"%s"}}', [AId, AId, AChat, AFrom, AText]);
end;

/// <summary>Массив обновлений (результат getUpdates).</summary>
function Batch(const AItems: array of string): TJSONValue;
var
  LText: string;
  I: Integer;
begin
  LText := '';
  for I := 0 to High(AItems) do
  begin
    if I > 0 then
      LText := LText + ',';
    LText := LText + AItems[I];
  end;
  Result := JsonOf('[' + LText + ']');
end;

/// <summary>Пакет сообщений с update_id из AIds в чат AChat.</summary>
function MsgBatch(const AIds: array of Int64; AChat: Int64): TJSONValue;
var
  LItems: TArray<string>;
  I: Integer;
begin
  SetLength(LItems, Length(AIds));
  for I := 0 to High(AIds) do
    LItems[I] := MsgUpdate(AIds[I], AChat, AChat, 'm' + IntToStr(AIds[I]));
  Result := Batch(LItems);
end;

/// <summary>Висит до отмены окружающего токена (как long polling); затем ETgCancelledError.</summary>
function HangUntilCancelled: TJSONValue;
var
  LToken: ITgCancellation;
begin
  LToken := TTgCancelScope.Current;
  if Assigned(LToken) then
  begin
    LToken.WaitFor(50000);
    LToken.ThrowIfCancelled;
  end;
  Result := TJSONArray.Create;
end;

/// <summary>Целое поле JSON параметров; -1 — нет поля.</summary>
function ParamInt(const AJson, AName: string): Int64;
var
  LObj: TJSONObject;
begin
  LObj := TTgJson.ParseObject(AJson);
  try
    if TTgJson.Has(LObj, AName) then
      Result := TTgJson.GetInt64(LObj, AName)
    else
      Result := -1;
  finally
    LObj.Free;
  end;
end;

/// <summary>Подтверждение обработки для источника (замыкание без кадра теста).</summary>
function AckTo(const ASource: ITgUpdateSource): TProc<Int64>;
begin
  Result :=
    procedure(AUpdateId: Int64)
    begin
      ASource.Processed(AUpdateId);
    end;
end;

/// <summary>Обработчик диспетчера: записывает update_id.</summary>
function RecordTo(ALog: TIdLog): TTgRawHandler;
begin
  Result :=
    procedure(const AUpdate: ITgRawUpdate)
    begin
      ALog.Add(AUpdate.UpdateId);
    end;
end;

/// <summary>Сырое обновление из JSON-текста.</summary>
function RawOf(const AJson: string): ITgRawUpdate;
begin
  Result := TTgRawUpdate.Create(TTgJson.ParseObject(AJson));
end;

procedure TestRawUpdateKeys;
var
  LRaw: ITgRawUpdate;
begin
  LRaw := RawOf(MsgUpdate(5, -100123, 7, 'x'));
  CheckEquals(5, LRaw.UpdateId, 'UpdateId');
  CheckEquals('message', LRaw.Kind, 'Kind = message');
  CheckEquals('-100123', LRaw.ChatKey, 'message → chat.id');
  CheckEquals('-100123', TTgRawUpdate.ChatKeyOf(LRaw.Json), 'ChatKeyOf');
  CheckEquals('55', RawOf('{"update_id":1,"callback_query":{"id":"c","from":{"id":7},' +
    '"message":{"message_id":1,"date":1,"chat":{"id":55}},"data":"d"}}').ChatKey,
    'callback_query → message.chat.id');
  CheckEquals('u7', RawOf('{"update_id":1,"callback_query":{"id":"c","from":{"id":7},' +
    '"inline_message_id":"im","data":"d"}}').ChatKey, 'inline callback_query → u + from.id');
  CheckEquals('u8', RawOf('{"update_id":1,"inline_query":{"id":"q","from":{"id":8},' +
    '"query":"x","offset":""}}').ChatKey, 'inline_query → u + from.id');
  CheckEquals('u9', RawOf('{"update_id":1,"pre_checkout_query":{"id":"p","from":{"id":9}}}').ChatKey,
    'pre_checkout_query → u + from.id');
  CheckEquals('', RawOf('{"update_id":1,"poll":{"id":"p","question":"?"}}').ChatKey, 'poll → ""');
  CheckEquals('', RawOf('{"update_id":1,"poll_answer":{"poll_id":"p","user":{"id":3}}}').ChatKey,
    'poll_answer → ""');
  CheckEquals('-5', RawOf('{"update_id":1,"chat_member":{"chat":{"id":-5},"from":{"id":3}}}').ChatKey,
    'chat_member → chat.id');
  CheckEquals('-6', RawOf('{"update_id":1,"business_message":{"message_id":1,"date":1,' +
    '"chat":{"id":-6},"business_connection_id":"b"}}').ChatKey, 'business_message → chat.id');
end;

procedure TestPollStopHanging;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LSource: TTgLongPollSource;
  LSourceRef: ITgUpdateSource;
  LDispatcher: TTgUpdateDispatcher;
  LSinkRef: ITgUpdateSink;
  LLog: TIdLog;
  LWatch: TStopwatch;
  LCalls: TArray<string>;
begin
  LLog := TIdLog.Create;
  try
    LTransport := TScriptCancellableTransport.Create(
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      begin
        Result := HangUntilCancelled;
      end);
    LTransportRef := LTransport;
    LDispatcher := TTgUpdateDispatcher.Create(RecordTo(LLog));
    LSinkRef := LDispatcher;
    LDispatcher.Start;
    LSource := TTgLongPollSource.Create(LTransportRef);
    LSourceRef := LSource;
    LSource.Start(LSinkRef);
    Check(WaitUntil(
      function: Boolean
      begin
        Result := LTransport.Count('getUpdates') = 1;
      end, 5000), 'getUpdates висит');
    Check(LSource.State = TTgSourceState.Running, 'State = Running');
    Check(Raises(
      procedure
      begin
        LSource.Start(LDispatcher);
      end, ETgError), 'повторный Start → ETgError');
    LCalls := LTransport.Calls('getUpdates');
    CheckEquals(50, ParamInt(LCalls[0], 'timeout'), 'timeout по умолчанию = 50');
    CheckEquals(100, ParamInt(LCalls[0], 'limit'), 'limit по умолчанию = 100');
    CheckEquals(-1, ParamInt(LCalls[0], 'offset'), 'первый запрос без offset');
    LWatch := TStopwatch.StartNew;
    Check(LSource.Stop(5000), 'Stop = True (запрос прерван токеном)');
    GStopHangingMs := LWatch.ElapsedMilliseconds;
    Check(GStopHangingMs < 1000, Format('Stop при висящем getUpdates < 1 с (%d мс)', [GStopHangingMs]));
    Check(LSource.State = TTgSourceState.Idle, 'State = Idle после Stop');
    CheckEquals(1, LTransport.Count('getUpdates'), 'ничего не принято — итогового запроса нет');
    Check(LDispatcher.Stop(2000), 'диспетчер остановлен');
  finally
    LSourceRef := nil;
    LSinkRef := nil;
    LLog.Free;
  end;
end;

procedure TestPollAbandon;
var
  LRelease: TEvent;
  LTransport: TScriptTransport;
  LTransportRef: ITgTransport;
  LSource: TTgLongPollSource;
  LSourceRef: ITgUpdateSource;
  LDispatcher: TTgUpdateDispatcher;
  LSinkRef: ITgUpdateSink;
  LLog: TIdLog;
  LWatch: TStopwatch;
  LStopped: Boolean;
begin
  LRelease := TEvent.Create(nil, True, False, '');
  LLog := TIdLog.Create;
  try
    // Транспорт без отмены: второй getUpdates игнорирует токен и ждёт LRelease.
    LTransport := TScriptTransport.Create(
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      begin
        if not TTgJson.Has(AParams.Json, 'offset') then
          Exit(MsgBatch([10], 1));
        LRelease.WaitFor(10000);
        Result := MsgBatch([11, 12], 1);
      end);
    LTransportRef := LTransport;
    LDispatcher := TTgUpdateDispatcher.Create(RecordTo(LLog));
    LSinkRef := LDispatcher;
    LSource := TTgLongPollSource.Create(LTransportRef);
    LSourceRef := LSource;
    LDispatcher.OnProcessed := AckTo(LSourceRef);
    LDispatcher.Start;
    LSource.Start(LSinkRef);
    Check(WaitUntil(
      function: Boolean
      begin
        Result := (LLog.Count = 1) and (LTransport.Count('getUpdates') = 2);
      end, 5000), 'первый пакет обработан, второй запрос висит');
    CheckEquals(11, LSource.Offset, 'offset = 11 после первого пакета');
    CheckEquals(11, ParamInt(LTransport.Calls('getUpdates')[1], 'offset'), 'второй запрос с offset = 11');
    LWatch := TStopwatch.StartNew;
    LStopped := LSource.Stop(300);
    GStopAbandonMs := LWatch.ElapsedMilliseconds;
    Check(not LStopped, 'Stop = False: неотменяемый запрос, поток отпущен');
    Check(GStopAbandonMs < 1000, Format('Stop с отпусканием потока < 1 с (%d мс)', [GStopAbandonMs]));
    Check(LSource.State = TTgSourceState.Idle, 'State = Idle после отпускания');
    LRelease.SetEvent;
    Check(LSource.WaitForThread(5000), 'отпущенный поток завершился');
    CheckEquals(1, LLog.Count, 'поздний пакет выброшен');
    CheckEquals(11, LSource.Offset, 'offset не сдвинут поздним пакетом');
    CheckEquals(2, LTransport.Count('getUpdates'), 'отпущенный поток не подтверждал offset');
    Check(LDispatcher.Stop(2000), 'диспетчер остановлен');
  finally
    LSourceRef := nil;
    LSinkRef := nil;
    LLog.Free;
    LRelease.Free;
  end;
end;

/// <summary>Сценарий подтверждения: пакет [1, 2, 3] в чат 1, затем висящий long polling.</summary>
function AckScript: TFakeHandler;
begin
  Result :=
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      if not TTgJson.Has(AParams.Json, 'offset') then
        Result := MsgBatch([1, 2, 3], 1)
      else if TTgJson.GetInt(AParams.Json, 'timeout') = 0 then
        Result := TJSONArray.Create
      else
        Result := HangUntilCancelled;
    end;
end;

procedure TestPollAckPolicies;
var
  LGate: TEvent;
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LSource: TTgLongPollSource;
  LSourceRef: ITgUpdateSource;
  LDispatcher: TTgUpdateDispatcher;
  LSinkRef: ITgUpdateSink;
  LLog: TIdLog;
  LCalls: TArray<string>;
  LPolicy: TTgAckPolicy;
begin
  LGate := TEvent.Create(nil, True, False, '');
  LLog := TIdLog.Create;
  try
    for LPolicy := Low(TTgAckPolicy) to High(TTgAckPolicy) do
    begin
      LGate.ResetEvent;
      LTransport := TScriptCancellableTransport.Create(AckScript());
      LTransportRef := LTransport;
      LDispatcher := TTgUpdateDispatcher.Create(
        procedure(const AUpdate: ITgRawUpdate)
        begin
          LGate.WaitFor(10000);
          LLog.Add(AUpdate.UpdateId);
        end);
      LSinkRef := LDispatcher;
      LSource := TTgLongPollSource.Create(LTransportRef);
      LSourceRef := LSource;
      LSource.AckPolicy := LPolicy;
      LDispatcher.OnProcessed := AckTo(LSourceRef);
      LDispatcher.Start;
      LSource.Start(LSinkRef);
      if LPolicy = TTgAckPolicy.AfterReceive then
      begin
        Check(WaitUntil(
          function: Boolean
          begin
            Result := LTransport.Count('getUpdates') >= 2;
          end, 5000), 'AfterReceive: следующий getUpdates сразу, до обработки');
        CheckEquals(0, LLog.Count, 'AfterReceive: обработчики ещё ждут');
      end
      else
      begin
        TThread.Sleep(300);
        CheckEquals(1, LTransport.Count('getUpdates'),
          'AfterBatch: следующий getUpdates не отправлен до обработки пакета');
      end;
      LGate.SetEvent;
      Check(WaitUntil(
        function: Boolean
        begin
          Result := (LLog.Count = 3) and (LTransport.Count('getUpdates') >= 2);
        end, 5000), 'пакет обработан, второй запрос отправлен');
      CheckEquals(4, ParamInt(LTransport.Calls('getUpdates')[1], 'offset'), 'второй запрос: offset = 4');
      Check(not Contains('allowed_updates', LTransport.Calls('getUpdates')[0]),
        'источник: незаданный AllowedUpdates не передаётся');
      Check(LSource.Stop(5000), 'Stop');
      LCalls := LTransport.Calls('getUpdates');
      CheckEquals(3, Length(LCalls), 'итоговый getUpdates отправлен');
      if Length(LCalls) = 3 then
      begin
        CheckEquals(4, ParamInt(LCalls[2], 'offset'), 'итоговый: offset = 4');
        CheckEquals(0, ParamInt(LCalls[2], 'timeout'), 'итоговый: timeout = 0');
        CheckEquals(1, ParamInt(LCalls[2], 'limit'), 'итоговый: limit = 1');
      end;
      CheckEquals(4, LSource.ConfirmedOffset, 'ConfirmedOffset = 4');
      Check(LDispatcher.Stop(2000), 'диспетчер остановлен');
      LSourceRef := nil;
      LSinkRef := nil;
      LTransportRef := nil;
      LLog.Free;
      LLog := TIdLog.Create;
    end;

    // Дренаж с таймаутом: обновление 2 не обработано — итоговый offset = 2.
    LTransport := TScriptCancellableTransport.Create(AckScript());
    LTransportRef := LTransport;
    LDispatcher := TTgUpdateDispatcher.Create(
      procedure(const AUpdate: ITgRawUpdate)
      begin
        if AUpdate.UpdateId = 2 then
          TTgCancelScope.Current.WaitFor(10000);
        LLog.Add(AUpdate.UpdateId);
      end);
    LSinkRef := LDispatcher;
    LSource := TTgLongPollSource.Create(LTransportRef);
    LSourceRef := LSource;
    LSource.AckPolicy := TTgAckPolicy.AfterBatch;
    LSource.DrainTimeoutMs := 300;
    LDispatcher.OnProcessed := AckTo(LSourceRef);
    LDispatcher.Start;
    LSource.Start(LSinkRef);
    Check(WaitUntil(
      function: Boolean
      begin
        Result := LLog.Count = 1;
      end, 5000), 'обновление 1 обработано, 2 висит');
    Check(LSource.Stop(5000), 'Stop после дренажа по таймауту');
    LCalls := LTransport.Calls('getUpdates');
    CheckEquals(2, Length(LCalls), 'запрос пакета и итоговый');
    if Length(LCalls) = 2 then
      CheckEquals(2, ParamInt(LCalls[1], 'offset'), 'итоговый offset = наименьший необработанный (2)');
    Check(LDispatcher.Stop(2000), 'диспетчер прервал висящий обработчик токеном');
  finally
    LSourceRef := nil;
    LSinkRef := nil;
    LLog.Free;
    LGate.Free;
  end;
end;

/// <summary>
///   Источник с подменными часами и сценарием AScript; события — в журнал
///   ('conflict', 'error', 'fault'), обновления — в ALog.
/// </summary>
procedure RunPollScenario(const AScript: TFakeHandler; ATimer: TFakeTimer;
  AAutoDeleteWebhook, ADropPending: Boolean; AJitter: Integer;
  const AUntil: TFunc<TScriptTransport, TTgLongPollSource, Boolean>;
  ALog: TIdLog; AEvents: TTextLog; out ATransportCalls: TArray<string>;
  out AState: TTgSourceState; out AReached: Boolean; out AGetUpdatesCalls: TArray<string>;
  out ADeleteCalls: TArray<string>);
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LTimerRef: ITgPollTimer;
  LSource: TTgLongPollSource;
  LSourceRef: ITgUpdateSource;
  LDispatcher: TTgUpdateDispatcher;
  LSinkRef: ITgUpdateSink;
begin
  LTransport := TScriptCancellableTransport.Create(AScript);
  LTransportRef := LTransport;
  LTimerRef := ATimer;
  LDispatcher := TTgUpdateDispatcher.Create(RecordTo(ALog));
  LSinkRef := LDispatcher;
  LSource := TTgLongPollSource.Create(LTransportRef);
  LSourceRef := LSource;
  LSource.Timer := LTimerRef;
  LSource.JitterPercent := AJitter;
  LSource.AutoDeleteWebhook := AAutoDeleteWebhook;
  LSource.DropPendingUpdates := ADropPending;
  LSource.OnConflict :=
    procedure(AError: ETgConflictError)
    begin
      AEvents.Add('conflict');
    end;
  LSource.OnError :=
    procedure(AError: Exception)
    begin
      AEvents.Add('error');
    end;
  LSource.OnFault :=
    procedure(AError: Exception)
    begin
      AEvents.Add('fault');
    end;
  LDispatcher.OnProcessed := AckTo(LSourceRef);
  LDispatcher.Start;
  LSource.Start(LSinkRef);
  AReached := WaitUntil(
    function: Boolean
    begin
      Result := AUntil(LTransport, LSource);
    end, 5000);
  AState := LSource.State;
  LSource.Stop(5000);
  LDispatcher.Stop(2000);
  ATransportCalls := LTransport.Methods;
  AGetUpdatesCalls := LTransport.Calls('getUpdates');
  ADeleteCalls := LTransport.Calls('deleteWebhook');
end;

procedure TestPollErrors;
var
  LTimer: TFakeTimer;
  LTimerRef: ITgPollTimer;
  LLog: TIdLog;
  LEvents: TTextLog;
  LStep: Integer;
  LMethods, LGets, LDeletes: TArray<string>;
  LState: TTgSourceState;
  LReached: Boolean;
  LSleeps: TArray<Cardinal>;
  LBase: Cardinal;
  I, LErrors, LConflicts: Integer;
  LEventsText: string;

  procedure Reset;
  begin
    LTimer := TFakeTimer.Create;
    LTimerRef := LTimer;
    LLog.Free;
    LLog := TIdLog.Create;
    LEvents.Free;
    LEvents := TTextLog.Create;
    LStep := 0;
  end;

  function CountEvents(const AName: string): Integer;
  var
    LItem: string;
    LList: TStringList;
  begin
    Result := 0;
    LList := TStringList.Create;
    try
      LList.CommaText := LEvents.Text;
      for LItem in LList do
        if LItem = AName then
          Inc(Result);
    finally
      LList.Free;
    end;
  end;

begin
  LLog := nil;
  LEvents := nil;
  try
    // Сеть: паузы 1 → 2 → 4 с, после успешного ответа — снова 1 с.
    Reset;
    RunPollScenario(
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      begin
        case TInterlocked.Increment(LStep) of
          1, 2, 3:
            raise ETgNetworkError.Create('сеть недоступна');
          4:
            Result := MsgBatch([1], 1);
          5:
            raise ETgApiError.Create('getUpdates', 502, 'Bad Gateway');
        else
          Result := HangUntilCancelled;
        end;
      end, LTimer, False, False, 0,
      function(ATransport: TScriptTransport; ASource: TTgLongPollSource): Boolean
      begin
        Result := ATransport.Count('getUpdates') >= 6;
      end, LLog, LEvents, LMethods, LState, LReached, LGets, LDeletes);
    Check(LReached, 'сценарий сети выполнен');
    LSleeps := LTimer.Sleeps;
    CheckEquals(4, Length(LSleeps), 'четыре паузы');
    if Length(LSleeps) = 4 then
    begin
      CheckEquals(1000, LSleeps[0], 'пауза 1 = 1 с');
      CheckEquals(2000, LSleeps[1], 'пауза 2 = 2 с');
      CheckEquals(4000, LSleeps[2], 'пауза 3 = 4 с');
      CheckEquals(1000, LSleeps[3], 'после успеха пауза снова 1 с (5xx)');
    end;
    CheckEquals(1, LLog.Count, 'пакет между ошибками доставлен');
    CheckEquals(4, CountEvents('error'), 'OnError на каждую временную ошибку');
    Check(LState = TTgSourceState.Running, 'источник жив после ошибок');

    // Разброс ±20%: 1, 2, 4 … 32, 60 (потолок) с.
    Reset;
    RunPollScenario(
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      begin
        if TInterlocked.Increment(LStep) <= 8 then
          raise ETgNetworkError.Create('сеть недоступна');
        Result := HangUntilCancelled;
      end, LTimer, False, False, 20,
      function(ATransport: TScriptTransport; ASource: TTgLongPollSource): Boolean
      begin
        Result := ATransport.Count('getUpdates') >= 9;
      end, LLog, LEvents, LMethods, LState, LReached, LGets, LDeletes);
    LSleeps := LTimer.Sleeps;
    CheckEquals(8, Length(LSleeps), 'восемь пауз с разбросом');
    for I := 0 to High(LSleeps) do
    begin
      if I < 6 then
        LBase := Cardinal(1000) shl I
      else
        LBase := 60000;
      Check((LSleeps[I] >= LBase * 8 div 10) and (LSleeps[I] <= LBase * 12 div 10),
        Format('пауза %d = %d мс в пределах ±20%% от %d', [I + 1, LSleeps[I], LBase]));
    end;

    // 409 webhook + AutoDeleteWebhook: deleteWebhook и повтор; DropPendingUpdates — при старте.
    Reset;
    RunPollScenario(
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      begin
        if AMethod = 'deleteWebhook' then
          Exit(TJSONTrue.Create);
        case TInterlocked.Increment(LStep) of
          1:
            raise ETgConflictError.Create('getUpdates', 409, CWebhookConflict);
          2:
            Result := MsgBatch([5], 1);
        else
          Result := HangUntilCancelled;
        end;
      end, LTimer, True, True, 0,
      function(ATransport: TScriptTransport; ASource: TTgLongPollSource): Boolean
      begin
        Result := LLog.Count = 1;
      end, LLog, LEvents, LMethods, LState, LReached, LGets, LDeletes);
    Check(LReached, '409 webhook: обновление доставлено после deleteWebhook');
    CheckEquals(2, Length(LDeletes), 'deleteWebhook: при старте и после 409');
    if Length(LDeletes) = 2 then
    begin
      CheckEquals('true', JsonAt(LDeletes[0], 'drop_pending_updates'), 'старт: drop_pending_updates = true');
      CheckEquals('', JsonAt(LDeletes[1], 'drop_pending_updates'), 'после 409: без drop_pending_updates');
    end;
    Check((Length(LMethods) > 0) and (LMethods[0] = 'deleteWebhook'), 'deleteWebhook — до первого getUpdates');
    CheckEquals(0, CountEvents('conflict'), 'AutoDeleteWebhook: без OnConflict');
    Check(LState = TTgSourceState.Running, 'источник работает');

    // 409 webhook без AutoDeleteWebhook: OnConflict + Faulted без повторов.
    Reset;
    RunPollScenario(
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      begin
        raise ETgConflictError.Create('getUpdates', 409, CWebhookConflict);
      end, LTimer, False, False, 0,
      function(ATransport: TScriptTransport; ASource: TTgLongPollSource): Boolean
      begin
        Result := ASource.State = TTgSourceState.Faulted;
      end, LLog, LEvents, LMethods, LState, LReached, LGets, LDeletes);
    Check(LState = TTgSourceState.Faulted, '409 webhook → Faulted');
    CheckEquals(1, CountEvents('conflict'), 'OnConflict один раз');
    CheckEquals(1, CountEvents('fault'), 'OnFault один раз');
    CheckEquals(1, Length(LGets), 'без повторов getUpdates');
    CheckEquals(0, Length(LDeletes), 'webhook не удалялся');

    // 409 «другой getUpdates»: OnConflict не чаще интервала, повтор через ≥ 5 с.
    Reset;
    RunPollScenario(
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      begin
        case TInterlocked.Increment(LStep) of
          1, 2, 3:
            raise ETgConflictError.Create('getUpdates', 409, COtherConflict);
          4:
            Result := MsgBatch([7], 1);
        else
          Result := HangUntilCancelled;
        end;
      end, LTimer, False, False, 0,
      function(ATransport: TScriptTransport; ASource: TTgLongPollSource): Boolean
      begin
        Result := LLog.Count = 1;
      end, LLog, LEvents, LMethods, LState, LReached, LGets, LDeletes);
    Check(LReached, '409 other: после повторов обновление доставлено');
    LSleeps := LTimer.Sleeps;
    CheckEquals(3, Length(LSleeps), 'три паузы');
    for I := 0 to High(LSleeps) do
      Check(LSleeps[I] >= 5000, Format('пауза после 409 other ≥ 5 с (%d мс)', [LSleeps[I]]));
    LConflicts := CountEvents('conflict');
    CheckEquals(1, LConflicts, 'OnConflict не чаще интервала (один раз)');
    Check(LState = TTgSourceState.Running, 'источник работает');

    // 401 и 404 → Faulted без повторов.
    for LErrors in [401, 404] do
    begin
      Reset;
      RunPollScenario(
        function(const AMethod: string; AParams: TTgParams): TJSONValue
        begin
          raise ETgApiError.Create('getUpdates', LErrors, 'Unauthorized');
        end, LTimer, False, False, 0,
        function(ATransport: TScriptTransport; ASource: TTgLongPollSource): Boolean
        begin
          Result := ASource.State = TTgSourceState.Faulted;
        end, LLog, LEvents, LMethods, LState, LReached, LGets, LDeletes);
      Check(LState = TTgSourceState.Faulted, Format('%d → Faulted', [LErrors]));
      CheckEquals(1, Length(LGets), Format('%d: без повторов', [LErrors]));
      CheckEquals(0, Length(LTimer.Sleeps), Format('%d: без пауз', [LErrors]));
      LEventsText := LEvents.Text;
      CheckEquals('fault', LEventsText, Format('%d: только OnFault', [LErrors]));
    end;
  finally
    LLog.Free;
    LEvents.Free;
  end;
end;

procedure TestDispatcherOrder;
var
  LDispatcher: TTgUpdateDispatcher;
  LSinkRef: ITgUpdateSink;
  LLock: TCriticalSection;
  LLast: TDictionary<string, Int64>;
  LProcessed: TIdLog;
  LViolations, LActive, LMax, LDone: Integer;
  I: Integer;
  LAllPosted: Boolean;
begin
  LLock := TCriticalSection.Create;
  LLast := TDictionary<string, Int64>.Create;
  LProcessed := TIdLog.Create;
  try
    LViolations := 0;
    LActive := 0;
    LMax := 0;
    LDone := 0;
    LDispatcher := TTgUpdateDispatcher.Create(
      procedure(const AUpdate: ITgRawUpdate)
      var
        LPrev: Int64;
      begin
        LLock.Enter;
        try
          Inc(LActive);
          if LActive > LMax then
            LMax := LActive;
          // Внутри чата update_id должны идти строго по возрастанию.
          if LLast.TryGetValue(AUpdate.ChatKey, LPrev) and (LPrev >= AUpdate.UpdateId) then
            Inc(LViolations);
          LLast.AddOrSetValue(AUpdate.ChatKey, AUpdate.UpdateId);
        finally
          LLock.Leave;
        end;
        TThread.Sleep(2 + AUpdate.UpdateId mod 3);
        LLock.Enter;
        try
          Dec(LActive);
          Inc(LDone);
        finally
          LLock.Leave;
        end;
      end);
    LSinkRef := LDispatcher;
    LDispatcher.MaxParallel := 4;
    LDispatcher.QueueCapacity := 16;
    LDispatcher.OnProcessed :=
      procedure(AUpdateId: Int64)
      begin
        LProcessed.Add(AUpdateId);
      end;
    Check(not LDispatcher.Post(RawOf(MsgUpdate(1, 1, 1, 'x')), nil), 'Post до Start → False');
    LDispatcher.Start;
    Check(LDispatcher.Active, 'Active после Start');
    LAllPosted := True;
    // Ёмкость 16 < 100: Post ждёт места — очередь ограничена.
    for I := 1 to 100 do
      if not LDispatcher.Post(RawOf(MsgUpdate(I, 1000 + I mod 5, 1, 'x')), nil) then
        LAllPosted := False;
    Check(LAllPosted, '100 обновлений приняты');
    Check(LDispatcher.WaitIdle(10000), 'очередь обработана');
    CheckEquals(100, LDone, 'обработаны все 100');
    CheckEquals(0, LViolations, 'порядок внутри каждого чата сохранён');
    GMaxConcurrency := LMax;
    Check((LMax >= 2) and (LMax <= 4), Format('параллельно 2–4 обработчика (было %d)', [LMax]));
    CheckEquals(100, LProcessed.Count, 'OnProcessed для каждого');
    Check(LDispatcher.Stop(2000), 'Stop');
    Check(not LDispatcher.Active, 'Active = False после Stop');
    Check(not LDispatcher.Post(RawOf(MsgUpdate(1, 1, 1, 'x')), nil), 'Post после Stop → False');
  finally
    LSinkRef := nil;
    LProcessed.Free;
    LLast.Free;
    LLock.Free;
  end;
end;

procedure TestDispatcherErrors;
var
  LDispatcher: TTgUpdateDispatcher;
  LSinkRef: ITgUpdateSink;
  LDone, LErrors, LProcessed: TIdLog;
  I: Integer;
begin
  LDone := TIdLog.Create;
  LErrors := TIdLog.Create;
  LProcessed := TIdLog.Create;
  try
    LDispatcher := TTgUpdateDispatcher.Create(
      procedure(const AUpdate: ITgRawUpdate)
      begin
        if AUpdate.UpdateId mod 3 = 0 then
          raise Exception.Create('сбой обработчика');
        LDone.Add(AUpdate.UpdateId);
      end);
    LSinkRef := LDispatcher;
    LDispatcher.MaxParallel := 2;
    LDispatcher.OnError :=
      procedure(AError: Exception; const AUpdate: ITgRawUpdate)
      begin
        LErrors.Add(AUpdate.UpdateId);
        if AUpdate.UpdateId = 3 then
          raise Exception.Create('сбой OnError');
      end;
    LDispatcher.OnProcessed :=
      procedure(AUpdateId: Int64)
      begin
        LProcessed.Add(AUpdateId);
      end;
    LDispatcher.Start;
    for I := 1 to 10 do
      LDispatcher.Post(RawOf(MsgUpdate(I, I mod 2, 1, 'x')), nil);
    Check(LDispatcher.WaitIdle(5000), 'очередь обработана');
    CheckEquals(3, LErrors.Count, 'OnError для 3, 6, 9');
    CheckEquals(7, LDone.Count, 'остальные обработаны');
    CheckEquals(10, LProcessed.Count, 'обновление с исключением считается обработанным');
    LDispatcher.Post(RawOf(MsgUpdate(11, 1, 1, 'x')), nil);
    Check(LDispatcher.WaitIdle(5000) and (LDone.Count = 8), 'цикл жив после исключения в OnError');
    Check(LDispatcher.Stop(2000), 'Stop');
  finally
    LSinkRef := nil;
    LProcessed.Free;
    LErrors.Free;
    LDone.Free;
  end;
end;

procedure TestDeliveryMain;
var
  LDispatcher: TTgUpdateDispatcher;
  LSinkRef: ITgUpdateSink;
  LThreads: TIdLog;
  LIds: TArray<Int64>;
  I: Integer;
  LAllMain: Boolean;
  LWatch: TStopwatch;
begin
  LThreads := TIdLog.Create;
  try
    LDispatcher := TTgUpdateDispatcher.Create(
      procedure(const AUpdate: ITgRawUpdate)
      begin
        LThreads.Add(Int64(TThread.CurrentThread.ThreadID));
      end);
    LSinkRef := LDispatcher;
    LDispatcher.Delivery := TTgDelivery.Main;
    LDispatcher.Start;
    for I := 1 to 5 do
      LDispatcher.Post(RawOf(MsgUpdate(I, I mod 2, 1, 'x')), nil);
    // WaitIdle из главного потока прокачивает очередь (CheckSynchronize).
    Check(LDispatcher.WaitIdle(5000), 'обработаны в главном потоке');
    LIds := LThreads.ToArray;
    CheckEquals(5, Length(LIds), 'пять обработчиков');
    LAllMain := True;
    for I := 0 to High(LIds) do
      if LIds[I] <> Int64(MainThreadID) then
        LAllMain := False;
    Check(LAllMain, 'Delivery = Main: обработчик в главном потоке');

    // Главный поток не прокачивает очередь: задания ждут в TThread.Queue.
    for I := 6 to 8 do
      LDispatcher.Post(RawOf(MsgUpdate(I, I mod 2, 1, 'x')), nil);
    TThread.Sleep(200);
    LWatch := TStopwatch.StartNew;
    Check(LDispatcher.Stop(3000), 'Stop из главного потока не блокируется');
    GDispatcherMainStopMs := LWatch.ElapsedMilliseconds;
    Check(GDispatcherMainStopMs < 1000, Format('Stop < 1 с (%d мс)', [GDispatcherMainStopMs]));
    // «Осиротевшие» процедуры в очереди ничего не делают.
    for I := 1 to 5 do
      CheckSynchronize(10);
    CheckEquals(5, LThreads.Count, 'брошенные задания не выполнялись');
  finally
    LSinkRef := nil;
    LThreads.Free;
  end;
end;

/// <summary>Поток нагрузки хранилища: свой ключ, чтение после записи, общий ключ.</summary>
function NewStorageWorker(const AStorage: ITgStateStorage; AIndex: Integer;
  AMismatches: PInteger): TThread;
begin
  Result := TThread.CreateAnonymousThread(
    procedure
    var
      I: Integer;
      LKey, LName, LValue: string;
    begin
      LKey := 'k' + IntToStr(AIndex);
      for I := 0 to 1999 do
      begin
        LName := 'n' + IntToStr(I mod 20);
        AStorage.Put(LKey, LName, IntToStr(I));
        if not AStorage.TryGet(LKey, LName, LValue) or (LValue <> IntToStr(I)) then
          TInterlocked.Increment(AMismatches^);
        AStorage.Put('shared', 't' + IntToStr(AIndex), IntToStr(I));
        AStorage.TryGet('k' + IntToStr((AIndex + 1) mod 8), LName, LValue);
        if I mod 50 = 0 then
          AStorage.Delete('tmp' + IntToStr(AIndex));
      end;
    end);
  Result.FreeOnTerminate := False;
end;

procedure TestStateStorage;
var
  LStorage: TTgMemoryStateStorage;
  LRef: ITgStateStorage;
  LValue: string;
  LThreads: array[0..7] of TThread;
  LMismatches: Integer;
  I: Integer;
begin
  LStorage := TTgMemoryStateStorage.Create;
  LRef := LStorage;
  Check(not LRef.TryGet('1:2', 'step', LValue) and (LValue = ''), 'нет значения → False и ''''');
  LRef.Put('1:2', 'step', 'a');
  LRef.Put('1:2', 'name', 'b');
  Check(LRef.TryGet('1:2', 'step', LValue) and (LValue = 'a'), 'Put/TryGet');
  LRef.Delete('1:2', 'step');
  Check(not LRef.TryGet('1:2', 'step', LValue), 'Delete(имя)');
  CheckEquals(1, LStorage.KeyCount, 'ключ с оставшимся значением жив');
  LRef.Delete('1:2', 'name');
  CheckEquals(0, LStorage.KeyCount, 'ключ без значений удалён');
  LRef.Put('3:4', 'a', '1');
  LRef.Put('3:4', 'b', '2');
  LRef.Delete('3:4');
  CheckEquals(0, LStorage.KeyCount, 'Delete(ключ) удаляет все значения');

  LMismatches := 0;
  for I := 0 to 7 do
    LThreads[I] := NewStorageWorker(LRef, I, @LMismatches);
  for I := 0 to 7 do
    LThreads[I].Start;
  for I := 0 to 7 do
  begin
    LThreads[I].WaitFor;
    LThreads[I].Free;
  end;
  CheckEquals(0, LMismatches, '8 потоков: чтение после записи согласовано');
  CheckEquals(9, LStorage.KeyCount, '8 своих ключей и общий');
  for I := 0 to 7 do
    Check(LRef.TryGet('k' + IntToStr(I), 'n19', LValue) and (LValue = '1999'),
      Format('поток %d: последнее значение', [I]));
end;

/// <summary>Ответы для сквозного теста TTgBot.</summary>
function BotScript: TFakeHandler;
begin
  Result :=
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      if AMethod = 'getUpdates' then
      begin
        if not TTgJson.Has(AParams.Json, 'offset') then
          Exit(Batch([
            MsgUpdate(1, 100, 7, '/start'),
            '{"update_id":2,"callback_query":{"id":"cb1","from":{"id":7,"is_bot":false,' +
              '"first_name":"U"},"chat_instance":"ci","data":"yes","message":{"message_id":55,' +
              '"date":1,"chat":{"id":100,"type":"private"},"text":"Привет"}}}',
            '{"update_id":3,"callback_query":{"id":"cb2","from":{"id":8,"is_bot":false,' +
              '"first_name":"V"},"chat_instance":"ci","data":"x","inline_message_id":"im1"}}']));
        if TTgJson.GetInt(AParams.Json, 'timeout') = 0 then
          Exit(TJSONArray.Create);
        Exit(HangUntilCancelled);
      end;
      if AMethod = 'sendMessage' then
        Exit(JsonOf(CShortMessageJson));
      Result := TJSONTrue.Create;
    end;
end;

procedure TestBotEndToEnd;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LLog: TTextLog;
  LErrors: TIdLog;
  LWatch: TStopwatch;
  LSent, LAnswers, LEdits, LGets: TArray<string>;
  LCb1, LCb2, LEditChat, LEditInline: string;
  I: Integer;
begin
  LLog := TTextLog.Create;
  LErrors := TIdLog.Create;
  try
    LTransport := TScriptCancellableTransport.Create(BotScript());
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      Check(not LBot.Active, 'не запущен');
      Check(Assigned(LBot.StateStorage), 'StateStorage по умолчанию — в памяти');
      LBot.OnMessage :=
        procedure(ACtx: ITgContext)
        begin
          LLog.Add('msg text=' + ACtx.Text + ' chat=' + ACtx.ChatId.ToString + ' from=' +
            IntToStr(ACtx.From.Id) + ' key=' + ACtx.StateKey + ' kind=' + ACtx.Kind);
          ACtx.Reply('Привет', TTgKeyboard.Inline.Button('Да', 'yes'));
          ACtx.State['step'] := '1';
        end;
      LBot.OnCallbackQuery :=
        procedure(ACtx: ITgContext)
        begin
          if ACtx.Data = 'yes' then
          begin
            LLog.Add('cb state=' + ACtx.State['step'] + ' text=' + ACtx.Text + ' msg=' +
              BoolToStr(Assigned(ACtx.Message), True) + ' upd=' + IntToStr(ACtx.Update.UpdateId));
            ACtx.Answer('Ок');
            ACtx.Edit('Готово');
            ACtx.ClearState;
            LLog.Add('cleared=' + ACtx.State['step']);
          end
          else
          begin
            LLog.Add('inline nochat=' + BoolToStr(ACtx.ChatId.IsEmpty, True) + ' key=' + ACtx.StateKey);
            try
              ACtx.Reply('x');
            except
              on E: ETgError do
                LLog.Add('reply-nochat');
            end;
            ACtx.Edit('inl', TTgKeyboard.Inline.Button('Ещё', 'more'));
            try
              LBot.Stop;
            except
              on E: ETgError do
                LLog.Add('stop-in-handler');
            end;
          end;
        end;
      LBot.OnError :=
        procedure(AError: Exception; ACtx: ITgContext)
        begin
          LErrors.Add(1);
          LLog.Add('error ' + AError.ClassName + ': ' + AError.Message);
        end;
      LBot.Start;
      Check(LBot.Active, 'Active после Start');
      Check(Raises(
        procedure
        begin
          LBot.Start;
        end, ETgError), 'повторный Start → ETgError');
      Check(WaitUntil(
        function: Boolean
        begin
          Result := (LTransport.Count('answerCallbackQuery') = 2) and
            (LTransport.Count('editMessageText') = 2) and (LTransport.Count('getUpdates') >= 2);
        end, 5000), 'обработчики выполнены, ответы отправлены');
      LWatch := TStopwatch.StartNew;
      Check(LBot.Stop, 'Stop = True');
      GBotStopMs := LWatch.ElapsedMilliseconds;
      Check(GBotStopMs < 1000, Format('TTgBot.Stop < 1 с (%d мс)', [GBotStopMs]));
      Check(not LBot.Active, 'Active = False после Stop');
      Check(LBot.Stop, 'повторный Stop = True');
    finally
      LBot.Free;
    end;
    // Обработчики.
    Check(LLog.Has('msg text=/start chat=100 from=7 key=100:7 kind=message'), 'OnMessage: Text/ChatId/From/StateKey');
    Check(LLog.Has('cb state=1 text=yes msg=True upd=2'), 'OnCallbackQuery: State того же chat:user, Text = data');
    Check(LLog.Has('cleared='), 'ClearState');
    Check(LLog.Has('inline nochat=True key=:8'), 'inline callback: без чата, ключ :user');
    Check(LLog.Has('reply-nochat'), 'Reply без чата → ETgError');
    Check(LLog.Has('stop-in-handler'), 'Stop из обработчика → ETgError');
    CheckEquals(0, LErrors.Count, 'OnError не вызывался: ' + LLog.Text);
    // Запросы.
    LSent := LTransport.Calls('sendMessage');
    CheckEquals(1, Length(LSent), 'один sendMessage');
    if Length(LSent) = 1 then
    begin
      CheckEquals('100', JsonAt(LSent[0], 'chat_id'), 'Reply: chat_id');
      CheckEquals('Привет', JsonAt(LSent[0], 'text'), 'Reply: text');
      CheckEquals('yes', JsonAt(LSent[0], 'reply_markup.inline_keyboard[0][0].callback_data'),
        'Reply: клавиатура');
    end;
    LAnswers := LTransport.Calls('answerCallbackQuery');
    LCb1 := '';
    LCb2 := '';
    for I := 0 to High(LAnswers) do
      if JsonAt(LAnswers[I], 'callback_query_id') = 'cb1' then
        LCb1 := LAnswers[I]
      else
        LCb2 := LAnswers[I];
    CheckEquals('Ок', JsonAt(LCb1, 'text'), 'Answer: text');
    CheckEquals('cb2', JsonAt(LCb2, 'callback_query_id'), 'AutoAnswerCallbacks: неотвеченный callback');
    CheckEquals('', JsonAt(LCb2, 'text'), 'автоответ без текста');
    LEdits := LTransport.Calls('editMessageText');
    LEditChat := '';
    LEditInline := '';
    for I := 0 to High(LEdits) do
      if JsonAt(LEdits[I], 'inline_message_id') <> '' then
        LEditInline := LEdits[I]
      else
        LEditChat := LEdits[I];
    CheckEquals('100', JsonAt(LEditChat, 'chat_id'), 'Edit: chat_id');
    CheckEquals('55', JsonAt(LEditChat, 'message_id'), 'Edit: message_id');
    CheckEquals('Готово', JsonAt(LEditChat, 'text'), 'Edit: text');
    Check(not Contains('reply_markup', LEditChat), 'Edit без клавиатуры');
    CheckEquals('im1', JsonAt(LEditInline, 'inline_message_id'), 'Edit inline: inline_message_id');
    CheckEquals('more', JsonAt(LEditInline, 'reply_markup.inline_keyboard[0][0].callback_data'),
      'Edit inline: клавиатура');
    LGets := LTransport.Calls('getUpdates');
    Check((Length(LGets) >= 3) and (ParamInt(LGets[High(LGets)], 'offset') = 4) and
      (ParamInt(LGets[High(LGets)], 'timeout') = 0), 'итоговое подтверждение offset = 4');
    for I := 0 to High(LGets) do
      Check(Contains('"allowed_updates":[]', LGets[I]),
        Format('AllowedUpdates не задан: getUpdates #%d передаёт []', [I]));
  finally
    LErrors.Free;
    LLog.Free;
  end;
end;

procedure TestBotRunMain;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LMainThread: Integer;
  LWatch: TStopwatch;
begin
  Check(TTgShutdownSignal.Supported, 'TTgShutdownSignal поддерживается (Windows/POSIX)');
  Check(TTgShutdownSignal.Install, 'Install');
  TTgShutdownSignal.Reset;
  Check(not TTgShutdownSignal.Requested, 'после Reset сигнала нет');
  TTgShutdownSignal.Request;
  Check(TTgShutdownSignal.Requested, 'Request → Requested');
  TTgShutdownSignal.Reset;
  TTgShutdownSignal.Uninstall;

  LMainThread := -1;
  LTransport := TScriptCancellableTransport.Create(
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      if AMethod = 'getUpdates' then
      begin
        if not TTgJson.Has(AParams.Json, 'offset') then
          Exit(Batch([MsgUpdate(1, 100, 7, 'stop')]));
        if TTgJson.GetInt(AParams.Json, 'timeout') = 0 then
          Exit(TJSONArray.Create);
        Exit(HangUntilCancelled);
      end;
      Result := JsonOf(CShortMessageJson);
    end);
  LTransportRef := LTransport;
  LBot := TTgBot.Create(LTransportRef);
  try
    LBot.Delivery := TTgDelivery.Main;
    LBot.OnMessage :=
      procedure(ACtx: ITgContext)
      begin
        if TThread.CurrentThread.ThreadID = MainThreadID then
          LMainThread := 1
        else
          LMainThread := 0;
        ACtx.Reply('Пока');
        LBot.RequestStop;
      end;
    LWatch := TStopwatch.StartNew;
    Check(LBot.Run, 'Run = True: остановлен по RequestStop');
    GBotRunMs := LWatch.ElapsedMilliseconds;
    CheckEquals(1, LMainThread, 'Run + Delivery = Main: обработчик в главном потоке');
    Check(GBotRunMs < 3000, Format('Run завершился по RequestStop (%d мс)', [GBotRunMs]));
    CheckEquals(1, LTransport.Count('sendMessage'), 'ответ отправлен');
    Check(not LBot.Active, 'после Run бот остановлен');
  finally
    LBot.Free;
  end;
end;

/// <summary>
///   Запускает TTgBot (OnMessage и OnCallbackQuery назначены) с AAllowed
///   (пустое — не задавать), ждёт getUpdates, останавливает. OnError пишется
///   в ALog. Результат — параметры всех getUpdates.
/// </summary>
function RunIdleBot(const AAllowed: TTgOptionalStrings; ALog: TTextLog): TArray<string>;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
begin
  LTransport := TScriptCancellableTransport.Create(
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      if (AMethod = 'getUpdates') and (TTgJson.GetInt(AParams.Json, 'timeout') <> 0) then
        Exit(HangUntilCancelled);
      Result := TJSONArray.Create;
    end);
  LTransportRef := LTransport;
  LBot := TTgBot.Create(LTransportRef);
  try
    if AAllowed.HasValue then
      LBot.AllowedUpdates := AAllowed;
    LBot.OnMessage :=
      procedure(ACtx: ITgContext)
      begin
      end;
    LBot.OnCallbackQuery :=
      procedure(ACtx: ITgContext)
      begin
      end;
    LBot.OnError :=
      procedure(AError: Exception; ACtx: ITgContext)
      begin
        ALog.Add(AError.ClassName + ' ctx=' + BoolToStr(Assigned(ACtx), True) + ': ' +
          AError.Message);
      end;
    LBot.Start;
    Check(WaitUntil(
      function: Boolean
      begin
        Result := LTransport.Count('getUpdates') >= 1;
      end, 5000), 'getUpdates отправлен');
    Check(AAllowed.HasValue = LBot.AllowedUpdates.HasValue, 'Start не меняет AllowedUpdates бота');
    Check(LBot.Source.AllowedUpdates.HasValue, 'источнику всегда задан allowed_updates');
    Check(LBot.Stop, 'Stop = True');
  finally
    LBot.Free;
  end;
  Result := LTransport.Calls('getUpdates');
end;

procedure TestBotAllowedUpdates;
var
  LLog: TTextLog;
  LGets: TArray<string>;
  I: Integer;
begin
  LLog := TTextLog.Create;
  try
    // Не задано: [] в каждом getUpdates (сброс фильтра, запомненного сервером).
    LGets := RunIdleBot(TTgOptionalStrings.Empty, LLog);
    Check(Length(LGets) >= 1, 'не задано: есть getUpdates');
    for I := 0 to High(LGets) do
      Check(Contains('"allowed_updates":[]', LGets[I]),
        Format('не задано: getUpdates #%d передаёт allowed_updates = [] (%s)', [I, LGets[I]]));
    CheckEquals('', LLog.Text, 'не задано: без предупреждений');
    // Явный []: так же, без предупреждений.
    LLog.Clear;
    LGets := RunIdleBot(TTgOptionalStrings.Create(nil), LLog);
    Check((Length(LGets) >= 1) and Contains('"allowed_updates":[]', LGets[0]), 'явный [] → []');
    CheckEquals('', LLog.Text, 'явный []: без предупреждений');
    // Узкий фильтр без callback_query при назначенном OnCallbackQuery: список
    // передаётся как есть, OnError(E, nil) предупреждает, запуск не прерван.
    LLog.Clear;
    LGets := RunIdleBot(TTgOptionalStrings.Create([TTgUpdateType.Message]), LLog);
    Check(Length(LGets) >= 1, 'только message: есть getUpdates');
    for I := 0 to High(LGets) do
      Check(Contains('"allowed_updates":["message"]', LGets[I]),
        Format('только message: getUpdates #%d передаёт список (%s)', [I, LGets[I]]));
    Check(Contains('ETgError ctx=False', LLog.Text) and Contains('OnCallbackQuery', LLog.Text) and
      Contains('"callback_query"', LLog.Text), 'только message: предупреждение про OnCallbackQuery');
    Check(not Contains('OnMessage', LLog.Text), 'только message: OnMessage не предупреждается');
    // Полный нужный список: без предупреждений.
    LLog.Clear;
    LGets := RunIdleBot(TTgOptionalStrings.Create([TTgUpdateType.Message,
      TTgUpdateType.CallbackQuery]), LLog);
    Check((Length(LGets) >= 1) and
      Contains('"allowed_updates":["message","callback_query"]', LGets[0]),
      'message + callback_query: список передан');
    CheckEquals('', LLog.Text, 'message + callback_query: без предупреждений');
  finally
    LLog.Free;
  end;
end;

{$IFDEF MSWINDOWS}
/// <summary>Отменяет источник через AMicros мкс (активное ожидание в отдельном потоке).</summary>
procedure CancelAfterMicros(const ASource: ITgCancellation; AMicros: Int64);
begin
  TThread.CreateAnonymousThread(
    procedure
    var
      LWatch: TStopwatch;
    begin
      LWatch := TStopwatch.StartNew;
      while LWatch.ElapsedTicks * 1000000 div TStopwatch.Frequency < AMicros do
        ;
      (ASource as TTgCancellationSource).Cancel;
    end).Start;
end;

procedure TestDownloadCancelRace;
var
  LData: TWSAData;
  LSocket: TSocket;
  LAddr: TSockAddrIn;
  LLen: Integer;
  LSettings: TTgHttpSettings;
  LTransport: ITgCancellableTransport;
  LStream: TMemoryStream;
  LSource: ITgCancellation;
  LWatch: TStopwatch;
  LElapsed: Int64;
  LCancelled, LOther, I: Integer;
  LError: string;
begin
  Check(WSAStartup($0202, LData) = 0, 'WSAStartup');
  // «Молчащий» сервер с большой очередью: соединения принимаются ядром, ответа нет.
  LSocket := socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  LStream := TMemoryStream.Create;
  try
    FillChar(LAddr, SizeOf(LAddr), 0);
    LAddr.sin_family := AF_INET;
    LAddr.sin_addr.S_addr := htonl(INADDR_LOOPBACK);
    Check(bind(LSocket, TSockAddr(LAddr), SizeOf(LAddr)) = 0, 'bind');
    Check(listen(LSocket, SOMAXCONN) = 0, 'listen');
    LLen := SizeOf(LAddr);
    Check(getsockname(LSocket, TSockAddr(LAddr), LLen) = 0, 'getsockname');
    LSettings := TTgHttpSettings.Create('123456:TEST');
    LSettings.ApiUrl := 'http://127.0.0.1:' + IntToStr(ntohs(LAddr.sin_port));
    LSettings.ResponseTimeoutMs := 15000;
    LSettings.GlobalRatePerSec := 0;
    LTransport := TTgHttpTransport.Create(LSettings);

    // GET висит до заголовков ответа: отмена через 300 мс прерывает его.
    LSource := TTgCancellationSource.Create;
    CancelLater(LSource, 300);
    LWatch := TStopwatch.StartNew;
    LError := '';
    try
      LTransport.DownloadFileEx('documents/file.bin', LStream, LSource);
      LError := 'без исключения';
    except
      on E: ETgCancelledError do
        ;
      on E: Exception do
        LError := E.ClassName + ': ' + E.Message;
    end;
    GDownloadCancelMs := LWatch.ElapsedMilliseconds;
    CheckEquals('', LError, 'DownloadFile прерван отменой (ETgCancelledError)');
    Check(GDownloadCancelMs < 1300, Format('DownloadFile прерван < 1 с после Cancel (всего %d мс)',
      [GDownloadCancelMs]));

    // Гонка: отмена в первые микросекунды (в т.ч. между проверкой токена и
    // Execute, который сбрасывает отмену запроса) — ни один запрос не висит.
    LCancelled := 0;
    LOther := 0;
    GDownloadRaceMaxMs := 0;
    for I := 0 to 59 do
    begin
      LSource := TTgCancellationSource.Create;
      CancelAfterMicros(LSource, I * 25);
      LWatch := TStopwatch.StartNew;
      try
        LTransport.DownloadFileEx('documents/file.bin', LStream, LSource);
        Inc(LOther);
      except
        on E: ETgCancelledError do
          Inc(LCancelled);
        on E: Exception do
          Inc(LOther);
      end;
      LElapsed := LWatch.ElapsedMilliseconds;
      if LElapsed > GDownloadRaceMaxMs then
        GDownloadRaceMaxMs := LElapsed;
    end;
    CheckEquals(60, LCancelled, Format('гонка: все 60 скачиваний отменены (иначе %d)', [LOther]));
    Check(GDownloadRaceMaxMs < 2000, Format('гонка: самое долгое < 2 с (%d мс)', [GDownloadRaceMaxMs]));
    LTransport := nil;
    // Потоки повторной отмены завершаются после отвязки запроса.
    TThread.Sleep(200);
  finally
    LStream.Free;
    closesocket(LSocket);
    WSACleanup;
  end;
end;
{$ENDIF}

{ Фаза 6A1: конкурентные вызовы подменного транспорта и память }

/// <summary>
///   Число занятых блоков и байт менеджера памяти (small + medium + large).
///   Вне Windows менеджер памяти системный и состояния не даёт — нули.
/// </summary>
procedure MemoryInUse(out ABlocks, ABytes: Int64);
{$IFDEF MSWINDOWS}
var
  LState: TMemoryManagerState;
  I: Integer;
begin
{$WARN SYMBOL_PLATFORM OFF}
  GetMemoryManagerState(LState);
{$WARN SYMBOL_PLATFORM DEFAULT}
  ABlocks := Int64(LState.AllocatedMediumBlockCount) + Int64(LState.AllocatedLargeBlockCount);
  ABytes := Int64(LState.TotalAllocatedMediumBlockSize) +
    Int64(LState.TotalAllocatedLargeBlockSize);
  for I := Low(LState.SmallBlockTypeStates) to High(LState.SmallBlockTypeStates) do
  begin
    Inc(ABlocks, Int64(LState.SmallBlockTypeStates[I].AllocatedBlockCount));
    Inc(ABytes, Int64(LState.SmallBlockTypeStates[I].AllocatedBlockCount) *
      LState.SmallBlockTypeStates[I].UseableBlockSize);
  end;
end;
{$ELSE}
begin
  ABlocks := 0;
  ABytes := 0;
end;
{$ENDIF}

/// <summary>
///   AThreads потоков ждут общий старт (TEvent-барьер), затем каждый
///   AIterations раз вызывает ATransport.Execute('getMe', nil).
///   Возвращает время от старта до завершения всех потоков, мс.
/// </summary>
function HammerFakeTransport(const ATransport: TFakeTransport;
  AThreads, AIterations: Integer): Int64;
var
  LStart: TEvent;
  LReady: Integer;
  LThreads: TArray<TThread>;
  LWatch: TStopwatch;
  I: Integer;
begin
  LReady := 0;
  LStart := TEvent.Create(nil, True, False, '');
  try
    SetLength(LThreads, AThreads);
    try
      for I := 0 to AThreads - 1 do
      begin
        LThreads[I] := TThread.CreateAnonymousThread(
          procedure
          var
            J: Integer;
          begin
            TInterlocked.Increment(LReady);
            LStart.WaitFor(INFINITE);
            for J := 1 to AIterations do
              ATransport.Execute('getMe', nil).Free;
          end);
        LThreads[I].FreeOnTerminate := False;
        LThreads[I].Start;
      end;
      // Все потоки дошли до барьера — отпускаем одновременно.
      WaitUntil(
        function: Boolean
        begin
          Result := TInterlocked.CompareExchange(LReady, 0, 0) = AThreads;
        end, 5000);
      LWatch := TStopwatch.StartNew;
      LStart.SetEvent;
      for I := 0 to AThreads - 1 do
        LThreads[I].WaitFor;
      Result := LWatch.ElapsedMilliseconds;
    finally
      // При исключении потоки не должны остаться висеть на барьере.
      LStart.SetEvent;
      for I := 0 to AThreads - 1 do
        LThreads[I].Free;
    end;
  finally
    LStart.Free;
  end;
end;

/// <summary>
///   Прирост памяти (блоки и байты) за один прогон HammerFakeTransport.
///   Прогрев перед замером: потоки, TEvent, ленивые структуры RTL и строка
///   FLastMethod уже созданы, поэтому без утечки прирост ровно 0.
/// </summary>
function FakeTransportGrowth(const ATransport: TFakeTransport; AThreads, AIterations: Integer;
  out ABytes, AMs: Int64): Int64;
var
  LBlocks0, LBytes0, LBlocks1, LBytes1: Int64;
begin
  HammerFakeTransport(ATransport, AThreads, 100);
  MemoryInUse(LBlocks0, LBytes0);
  AMs := HammerFakeTransport(ATransport, AThreads, AIterations);
  MemoryInUse(LBlocks1, LBytes1);
  Result := LBlocks1 - LBlocks0;
  ABytes := LBytes1 - LBytes0;
end;

/// <summary>
///   Регрессия гонки в TFakeTransport: 8 потоков одновременно пишут
///   FLastMethod. Без блокировки два одновременных присваивания строки теряют
///   одно значение без освобождения (утечка UnicodeString 25–40 байт).
/// </summary>
procedure TestFakeTransportConcurrency;
const
  CThreads = 8;
  CIterations = 50000;
var
  LTransport: TFakeTransport;
  LRef: ITgTransport;
  LAttempt: Integer;
  LBlocks, LBytes, LMs: Int64;
begin
  LTransport := TFakeTransport.Create(nil);
  LRef := LTransport;
  // Посторонние потоки дают случайный прирост в одном замере, утечка из-за
  // гонки — в каждом: провал, только если прирост есть во всех трёх попытках.
  LAttempt := 1;
  LBlocks := FakeTransportGrowth(LTransport, CThreads, CIterations, LBytes, LMs);
  while (LBlocks <> 0) and (LAttempt < 3) do
  begin
    Writeln(Format('    попытка %d: прирост блоков = %d, байт = %d (%d мс)',
      [LAttempt, LBlocks, LBytes, LMs]));
    Inc(LAttempt);
    LBlocks := FakeTransportGrowth(LTransport, CThreads, CIterations, LBytes, LMs);
  end;
  CheckEquals(0, LBlocks, 'конкурентный Execute: память не растёт (блоки)');
  CheckEquals('getMe', LTransport.LastMethod, 'LastMethod после конкурентных вызовов');
  // Прогрев (100) + замер (CIterations) в каждой попытке.
  CheckEquals(LAttempt * CThreads * (CIterations + 100), LTransport.Calls,
    'счётчик вызовов не теряет инкременты');
end;

/// <summary>
///   Нагрузочное воспроизведение (только по TG_ONLY=STRESS): 8 потоков по
///   100 000 вызовов, печать прироста памяти.
/// </summary>
procedure TestFakeTransportStress;
var
  LTransport: TFakeTransport;
  LRef: ITgTransport;
  LBlocks, LBytes, LMs: Int64;
begin
  LTransport := TFakeTransport.Create(nil);
  LRef := LTransport;
  LBlocks := FakeTransportGrowth(LTransport, 8, 100000, LBytes, LMs);
  Writeln(Format('    8 x 100000 Execute: %d мс, прирост блоков = %d, байт = %d',
    [LMs, LBlocks, LBytes]));
  CheckEquals(0, LBlocks, 'нагрузка: память не растёт (блоки)');
end;

{ 6A2: ядро TTgBot со счётчиком ссылок }

/// <summary>
///   Сценарий бота: первый getUpdates — одно сообщение AText в чат 100,
///   итоговое подтверждение (timeout = 0) — пусто, далее висит до отмены.
/// </summary>
function SingleMessageScript(const AText: string): TFakeHandler;
begin
  Result :=
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      if AMethod = 'getUpdates' then
      begin
        if not TTgJson.Has(AParams.Json, 'offset') then
          Exit(Batch([MsgUpdate(1, 100, 7, AText)]));
        if TTgJson.GetInt(AParams.Json, 'timeout') = 0 then
          Exit(TJSONArray.Create);
        Exit(HangUntilCancelled);
      end;
      if AMethod = 'sendMessage' then
        Exit(JsonOf(CShortMessageJson));
      Result := TJSONTrue.Create;
    end;
end;

/// <summary>Ждёт, пока на транспорт ссылается только тест (бот и ядро освобождены).</summary>
function WaitTransportReleased(ATransport: TInterfacedObject; ATimeoutMs: Integer): Boolean;
begin
  Result := WaitUntil(
    function: Boolean
    begin
      Result := ATransport.RefCount = 1;
    end, ATimeoutMs);
end;

procedure TestApiShutdown;
var
  LTransport: TScriptCancellableTransport;
  LPlain: TScriptTransport;
  LTransportRef, LPlainRef: ITgTransport;
  LApi, LPlainApi: TTgApi;
  LSuccess, LCancelled, LOther: Integer;
  LStream: TMemoryStream;
  LWatch: TStopwatch;
begin
  LTransport := TScriptCancellableTransport.Create(SingleMessageScript(''));
  LTransportRef := LTransport;
  LPlain := TScriptTransport.Create(SingleMessageScript(''));
  LPlainRef := LPlain;
  LSuccess := 0;
  LCancelled := 0;
  LOther := 0;
  LStream := TMemoryStream.Create;
  LApi := TTgApi.Create(LTransportRef);
  LPlainApi := TTgApi.Create(LPlainRef);
  try
    Check(not LApi.CancelToken.IsCancelled, 'до Shutdown токен не отменён');
    LApi.Shutdown;
    LApi.Shutdown;
    LPlainApi.Shutdown;
    Check(LApi.CancelToken.IsCancelled, 'Shutdown отменяет токен клиента');
    Check(Raises(
      procedure
      begin
        LApi.GetMe;
      end, ETgCancelledError), 'GetMe после Shutdown → ETgCancelledError');
    Check(Raises(
      procedure
      begin
        LApi.CallJson('getMe');
      end, ETgCancelledError), 'CallJson после Shutdown → ETgCancelledError');
    Check(Raises(
      procedure
      begin
        LApi.DownloadFile('a/b.txt', LStream);
      end, ETgCancelledError), 'DownloadFile после Shutdown → ETgCancelledError');
    Check(Raises(
      procedure
      begin
        LPlainApi.GetMe;
      end, ETgCancelledError), 'транспорт без токенов: GetMe после Shutdown → ETgCancelledError');
    LApi.GetMeAsync(
      procedure(AUser: ITgUser)
      begin
        TInterlocked.Increment(LSuccess);
      end,
      procedure(AError: Exception)
      begin
        if AError is ETgCancelledError then
          TInterlocked.Increment(LCancelled)
        else
          TInterlocked.Increment(LOther);
      end);
    Check(WaitUntil(
      function: Boolean
      begin
        Result := TInterlocked.CompareExchange(LCancelled, 0, 0) = 1;
      end, 5000), 'GetMeAsync после Shutdown → AOnError(ETgCancelledError)');
    CheckEquals(0, TInterlocked.CompareExchange(LSuccess, 0, 0), 'AOnSuccess не вызван');
    CheckEquals(0, TInterlocked.CompareExchange(LOther, 0, 0), 'других ошибок нет');
    CheckEquals(0, Length(LTransport.Methods), 'после Shutdown транспорт не вызывался');
    CheckEquals(0, Length(LPlain.Methods), 'транспорт без токенов не вызывался');
  finally
    LWatch := TStopwatch.StartNew;
    LApi.Free;
    LPlainApi.Free;
    LStream.Free;
  end;
  Check(LWatch.ElapsedMilliseconds < 1000,
    Format('Free после Shutdown быстрый (%d мс)', [LWatch.ElapsedMilliseconds]));
  // Задача GetMeAsync могла ещё не отпустить свои ссылки — ждём, а не проверяем мгновенно.
  WaitTransportReleased(LTransport, 2000);
  CheckEquals(1, LTransport.RefCount, 'клиент отпустил транспорт');
end;

procedure TestBotFreeWithHangingHandler;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LEntered, LRelease, LDone: TEvent;
  LLog: TTextLog;
  LFreed: Integer;
  LWatch: TStopwatch;
  LReleased: Boolean;
begin
  LLog := TTextLog.Create;
  LEntered := TEvent.Create(nil, True, False, '');
  LRelease := TEvent.Create(nil, True, False, '');
  LDone := TEvent.Create(nil, True, False, '');
  LReleased := False;
  LFreed := 0;
  try
    LTransport := TScriptCancellableTransport.Create(SingleMessageScript('hang'));
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      LBot.DrainTimeoutMs := 100;
      LBot.OnMessage :=
        procedure(ACtx: ITgContext)
        begin
          LEntered.SetEvent;
          // Неотменяемое ожидание: Stop не может прервать обработчик.
          LRelease.WaitFor(10000);
          try
            ACtx.Reply('после Free');
            LLog.Add('reply-ok');
          except
            on E: ETgCancelledError do
              LLog.Add('reply-cancelled');
            on E: Exception do
              LLog.Add('reply-' + E.ClassName);
          end;
          try
            ACtx.Api.GetMe;
            LLog.Add('getme-ok');
          except
            on E: ETgCancelledError do
              LLog.Add('getme-cancelled');
            on E: Exception do
              LLog.Add('getme-' + E.ClassName);
          end;
          LLog.Add('text=' + ACtx.Text);
          LDone.SetEvent;
          // Исключение после Free: OnError не вызывается (ядро отсоединено).
          raise ETgError.Create('ошибка после Free');
        end;
      LBot.OnError :=
        procedure(AError: Exception; ACtx: ITgContext)
        begin
          if TInterlocked.CompareExchange(LFreed, 0, 0) = 1 then
            LLog.Add('onerror-after-free')
          else
            LLog.Add('onerror ' + AError.Message);
        end;
      LBot.Start;
      Check(LEntered.WaitFor(5000) = TWaitResult.wrSignaled, 'обработчик вошёл');
      Check(not LBot.Stop(200), 'Stop(200) = False при зависшем обработчике');
    finally
      TInterlocked.Exchange(LFreed, 1);
      LWatch := TStopwatch.StartNew;
      LBot.Free;
      GBotFreeHangingMs := LWatch.ElapsedMilliseconds;
      LRelease.SetEvent;
    end;
    Check(GBotFreeHangingMs < 1000,
      Format('Free при зависшем обработчике < 1 с (%d мс)', [GBotFreeHangingMs]));
    Check(LDone.WaitFor(5000) = TWaitResult.wrSignaled, 'обработчик завершился после Free');
    LReleased := WaitTransportReleased(LTransport, 15000);
    Check(LReleased, 'ядро, клиент, источник и диспетчер освобождены после возврата обработчика');
    Check(LLog.Has('reply-cancelled'), 'ACtx.Reply после Free → ETgCancelledError: ' + LLog.Text);
    Check(LLog.Has('getme-cancelled'), 'ACtx.Api.GetMe после Free → ETgCancelledError: ' + LLog.Text);
    Check(LLog.Has('text=hang'), 'ACtx.Text после Free');
    Check(not LLog.Has('onerror-after-free'), 'OnError не вызван после Free: ' + LLog.Text);
    CheckEquals(0, LTransport.Count('sendMessage'), 'sendMessage после Free не отправлялся');
  finally
    // Не дождались освобождения — события могут быть ещё нужны обработчику.
    if LReleased then
    begin
      LDone.Free;
      LRelease.Free;
      LEntered.Free;
      LLog.Free;
    end;
  end;
end;

procedure TestBotContextOutlivesBot;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LSaved: ITgContext;
  LGot: TEvent;
  LApi, LBotApi: TTgApi;
{$IFDEF TGBOT_TESTHOOKS}
  LCores0: Integer;
{$ENDIF}
begin
{$IFDEF TGBOT_TESTHOOKS}
  // Ядра прежних тестов, отпущенные в чужих потоках, успевают освободиться.
  WaitUntil(
    function: Boolean
    begin
      Result := TgTestLiveBotCores = 0;
    end, 2000);
  LCores0 := TgTestLiveBotCores;
{$ENDIF}
  LGot := TEvent.Create(nil, True, False, '');
  try
    LTransport := TScriptCancellableTransport.Create(SingleMessageScript('сохранить'));
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      LBotApi := LBot.Api;
      Check(Assigned(LBotApi), 'TTgBot.Api — клиент ядра');
      LBot.OnMessage :=
        procedure(ACtx: ITgContext)
        begin
          ACtx.State['k'] := 'v';
          LSaved := ACtx;
          LGot.SetEvent;
        end;
      LBot.Start;
      Check(LGot.WaitFor(5000) = TWaitResult.wrSignaled, 'обработчик сохранил контекст');
      Check(LBot.Stop, 'Stop = True');
    finally
      LBot.Free;
    end;
    Check(Assigned(LSaved), 'контекст сохранён');
    if not Assigned(LSaved) then
      Exit;
    CheckEquals('сохранить', LSaved.Text, 'ACtx.Text после Free бота');
    CheckEquals('100:7', LSaved.StateKey, 'ACtx.StateKey после Free бота');
    CheckEquals('v', LSaved.State['k'], 'хранилище состояния живо вместе с контекстом');
{$IFDEF TGBOT_TESTHOOKS}
    CheckEquals(LCores0 + 1, TgTestLiveBotCores, 'после Free бота ядро удерживает только контекст');
{$ENDIF}
    // Контекст держит ядро как владельца клиента (ITgApiOwner) и не выдаёт его;
    // ITgRoutableContext — служебная сторона контекста (ядро и маршрутизатор).
    Check(not Supports(LSaved, ITgApiOwner), 'контекст не выдаёт владельца клиента (ITgApiOwner)');
    Check(Supports(LSaved, ITgRoutableContext), 'контекст поддерживает служебный ITgRoutableContext');
    LApi := LSaved.Api;
    Check(Assigned(LApi), 'ACtx.Api после Free бота');
    Check(LApi = LBotApi, 'ACtx.Api — тот же клиент, что TTgBot.Api (через ITgApiOwner ядра)');
    Check(LApi.CancelToken.IsCancelled, 'клиент закрыт (Shutdown)');
    Check(Raises(
      procedure
      begin
        LSaved.Reply('x');
      end, ETgCancelledError), 'ACtx.Reply после Free бота → ETgCancelledError');
    Check(Raises(
      procedure
      begin
        LSaved.Api.GetMe;
      end, ETgCancelledError), 'ACtx.Api.GetMe после Free бота → ETgCancelledError');
    Check(LTransport.RefCount > 1, 'контекст удерживает клиент (транспорт)');
    LSaved := nil;
    // Последнюю ссылку на ядро мог отпустить поток обработчика — ждём, а не проверяем мгновенно.
    WaitTransportReleased(LTransport, 2000);
    CheckEquals(1, LTransport.RefCount, 'последний контекст освободил ядро и клиент');
{$IFDEF TGBOT_TESTHOOKS}
    WaitUntil(
      function: Boolean
      begin
        Result := TgTestLiveBotCores <= LCores0;
      end, 2000);
    CheckEquals(LCores0, TgTestLiveBotCores, 'ядро освобождено вместе с последним контекстом');
{$ENDIF}
    CheckEquals(0, LTransport.Count('sendMessage'), 'sendMessage не отправлялся');
  finally
    LGot.Free;
  end;
end;

{ Владение, фаза 3: снимок хранилища состояния в контексте }

procedure TestContextStateStorageSnapshot;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LStorageA, LStorageB: ITgStateStorage;
  LSecondDone: TEvent;
  LFirstSeen, LSecondSeen, LValue: string;
begin
  LStorageA := TTgMemoryStateStorage.Create;
  LStorageB := TTgMemoryStateStorage.Create;
  LFirstSeen := '?';
  LSecondSeen := '?';
  LSecondDone := TEvent.Create(nil, True, False, '');
  try
    // Два сообщения одного чата в одном пакете: диспетчер обрабатывает их
    // строго по порядку — второе начинается после возврата первого
    // обработчика (который сменил хранилище); далее — итоговое
    // подтверждение и ожидание отмены.
    LTransport := TScriptCancellableTransport.Create(
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      begin
        if AMethod = 'getUpdates' then
        begin
          if not TTgJson.Has(AParams.Json, 'offset') then
            Exit(Batch([MsgUpdate(1, 100, 7, 'первое'), MsgUpdate(2, 100, 7, 'второе')]));
          if TTgJson.GetInt(AParams.Json, 'timeout') = 0 then
            Exit(TJSONArray.Create);
          Exit(HangUntilCancelled);
        end;
        Result := TJSONTrue.Create;
      end);
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      LBot.StateStorage := LStorageA;
      LBot.OnMessage :=
        procedure(ACtx: ITgContext)
        begin
          if ACtx.Text = 'первое' then
          begin
            ACtx.State['k'] := 'a';
            // Смена на ходу: текущий контекст продолжает работать со снимком A.
            LBot.StateStorage := LStorageB;
            LFirstSeen := ACtx.State['k'];
            ACtx.State['k2'] := 'x';
          end
          else
          begin
            LSecondSeen := ACtx.State['k'];
            ACtx.State['k3'] := 'y';
            LSecondDone.SetEvent;
          end;
        end;
      LBot.Start;
      Check(LSecondDone.WaitFor(5000) = TWaitResult.wrSignaled, 'оба сообщения обработаны');
      Check(LBot.Stop, 'Stop = True');
      Check(LBot.StateStorage = LStorageB, 'StateStorage бота — новое хранилище');
    finally
      LBot.Free;
    end;
    CheckEquals('a', LFirstSeen, 'после смены StateStorage контекст читает свой снимок (A)');
    Check(LStorageA.TryGet('100:7', 'k2', LValue) and (LValue = 'x'),
      'запись после смены StateStorage — в снимок контекста (A)');
    Check(not LStorageB.TryGet('100:7', 'k2', LValue), 'новое хранилище (B) не получило запись старого контекста');
    CheckEquals('', LSecondSeen, 'следующее обновление — с новым хранилищем (B)');
    Check(LStorageB.TryGet('100:7', 'k3', LValue) and (LValue = 'y'), 'следующее обновление пишет в B');
    Check(not LStorageA.TryGet('100:7', 'k3', LValue), 'A не получило запись следующего обновления');
    // Ядро могло освободиться в потоке обработчика — ждём, а не проверяем мгновенно.
    WaitTransportReleased(LTransport, 2000);
    CheckEquals(1, LTransport.RefCount, 'бот отпустил транспорт');
  finally
    LSecondDone.Free;
  end;
end;

/// <summary>Новое замыкание-счётчик при каждом вызове (свой кадр).</summary>
function NewCountingHandler(ACounter: PInteger): TProc<ITgContext>;
begin
  Result :=
    procedure(ACtx: ITgContext)
    begin
      if ACtx.Text <> '' then
        TInterlocked.Increment(ACounter^);
    end;
end;

/// <summary>
///   Бот с непрерывным потоком обновлений (по 4 сообщения на getUpdates в
///   4 чата); другой поток AIterations раз переназначает OnMessage (и
///   читает его). Возвращает число обработанных сообщений.
/// </summary>
function RunHandlerSwap(AIterations: Integer; out ADuring: Integer): Integer;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LCount: Integer;
  LBefore: Integer;
  LReads: Integer;
  LThread: TThread;
begin
  LCount := 0;
  LReads := 0;
  LTransport := TScriptCancellableTransport.Create(
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    var
      LOffset: Int64;
    begin
      if AMethod = 'getUpdates' then
      begin
        if TTgJson.GetInt(AParams.Json, 'timeout') = 0 then
          Exit(TJSONArray.Create);
        if TTgJson.Has(AParams.Json, 'offset') then
          LOffset := TTgJson.GetInt64(AParams.Json, 'offset')
        else
          LOffset := 1;
        Exit(MsgBatch([LOffset, LOffset + 1, LOffset + 2, LOffset + 3], 100 + (LOffset div 4) mod 4));
      end;
      Result := TJSONTrue.Create;
    end);
  LTransportRef := LTransport;
  LBot := TTgBot.Create(LTransportRef);
  try
    LBot.MaxParallel := 4;
    LBot.OnMessage := NewCountingHandler(@LCount);
    LBot.Start;
    Check(WaitUntil(
      function: Boolean
      begin
        Result := TInterlocked.CompareExchange(LCount, 0, 0) > 0;
      end, 5000), 'поток обновлений идёт');
    LBefore := TInterlocked.CompareExchange(LCount, 0, 0);
    LThread := TThread.CreateAnonymousThread(
      procedure
      var
        I: Integer;
        LHandler: TProc<ITgContext>;
      begin
        for I := 1 to AIterations do
        begin
          // Каждый раз новое замыкание: прежнее освобождается на ходу.
          LBot.OnMessage := NewCountingHandler(@LCount);
          if I mod 16 = 0 then
          begin
            LHandler := LBot.OnMessage;
            if Assigned(LHandler) then
              TInterlocked.Increment(LReads);
          end;
          if I mod 1000 = 0 then
            LBot.StateStorage := nil;
        end;
      end);
    LThread.FreeOnTerminate := False;
    try
      LThread.Start;
      LThread.WaitFor;
    finally
      LThread.Free;
    end;
    ADuring := TInterlocked.CompareExchange(LCount, 0, 0) - LBefore;
    CheckEquals(AIterations div 16, LReads, 'чтение OnMessage на ходу');
    Check(LBot.Stop, 'Stop = True после переназначений');
  finally
    LBot.Free;
  end;
  // Ядро могло освободиться в потоке обработчика — ждём, а не проверяем мгновенно.
  WaitTransportReleased(LTransport, 2000);
  CheckEquals(1, LTransport.RefCount, 'бот отпустил транспорт');
  Result := TInterlocked.CompareExchange(LCount, 0, 0);
end;

procedure TestBotHandlerSwap;
const
  CIterations = 10000;
var
  LBlocks0, LBytes0, LBlocks1, LBytes1: Int64;
  LHandled, LDuring: Integer;
begin
  // Прогрев: пулы потоков, ленивые синглтоны.
  RunHandlerSwap(1000, LDuring);
  MemoryInUse(LBlocks0, LBytes0);
  LHandled := RunHandlerSwap(CIterations, LDuring);
  MemoryInUse(LBlocks1, LBytes1);
  GHandlerSwapGrowth := LBlocks1 - LBlocks0;
  Writeln(Format('    %d переназначений: обработано %d (во время цикла %d), прирост блоков = %d, байт = %d',
    [CIterations, LHandled, LDuring, LBlocks1 - LBlocks0, LBytes1 - LBytes0]));
  Check(LHandled > 0, 'обновления обработаны');
  // Утечка при переназначении дала бы ≥ CIterations блоков; допуск — фоновые потоки.
  Check(LBlocks1 - LBlocks0 < 200,
    Format('память не растёт после %d переназначений (%d блоков)', [CIterations, LBlocks1 - LBlocks0]));
end;

{ Фаза 6A3: неблокирующие деструкторы диспетчера и источника }

var
  // Замеры 6A3, мс.
  GDispatcherFreeHangingMs: Int64 = -1;
  GDispatcherFreeAfterStopMs: Int64 = -1;
  GSourceFreeHangingMs: Int64 = -1;
  GSourceFreeAfterStopMs: Int64 = -1;
  GMainOrphanFreeMs: Int64 = -1;
  GExitHangMs: Int64 = -1;

const
  // Ключ командной строки: дочерний процесс теста завершения с висящими обработчиками.
  CExitHangSwitch = '--exit-hang';

/// <summary>
///   Обработчик диспетчера: сигнал входа, затем ожидание ARelease (для
///   диспетчера неотменяемое — Stop и Free его не прерывают). Замыкание
///   держит ARelease: его RefCount показывает, освобождены ли ядра.
/// </summary>
function NewHangingRawHandler(AEntered: TEvent; const ARelease: ITgCancellation;
  AHangMs: Cardinal): TTgRawHandler;
begin
  Result :=
    procedure(const AUpdate: ITgRawUpdate)
    begin
      AEntered.SetEvent;
      ARelease.WaitFor(AHangMs);
    end;
end;

/// <summary>Обработчик-счётчик (пока AMarker не отменён); замыкание держит AMarker.</summary>
function NewMarkedCountingHandler(const AMarker: ITgCancellation; ACounter: PInteger): TTgRawHandler;
begin
  Result :=
    procedure(const AUpdate: ITgRawUpdate)
    begin
      if not AMarker.IsCancelled then
        TInterlocked.Increment(ACounter^);
    end;
end;

/// <summary>
///   Диспетчер с NewHangingRawHandler. Отдельная функция: временная ссылка
///   на замыкание-аргумент освобождается при выходе из неё, а не в конце теста.
/// </summary>
function NewHangingDispatcher(AEntered: TEvent; const ARelease: ITgCancellation): TTgUpdateDispatcher;
begin
  Result := TTgUpdateDispatcher.Create(NewHangingRawHandler(AEntered, ARelease, 10000));
end;

/// <summary>Диспетчер Delivery = Main (4 потока) с NewMarkedCountingHandler.</summary>
function NewMarkedMainDispatcher(const AMarker: ITgCancellation; ACounter: PInteger): TTgUpdateDispatcher;
begin
  Result := TTgUpdateDispatcher.Create(NewMarkedCountingHandler(AMarker, ACounter));
  Result.Delivery := TTgDelivery.Main;
  Result.MaxParallel := 4;
end;

/// <summary>getUpdates, не реагирующий на токен: ждёт ARelease, затем пустой ответ.</summary>
function BlockingPollScript(ARelease: TEvent): TFakeHandler;
begin
  Result :=
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      ARelease.WaitFor(10000);
      Result := TJSONArray.Create;
    end;
end;

/// <summary>Ждёт, пока на интерфейсный объект ссылается только тест.</summary>
function WaitRefCountOne(AObject: TInterfacedObject; ATimeoutMs: Integer): Boolean;
begin
  Result := WaitUntil(
    function: Boolean
    begin
      Result := AObject.RefCount = 1;
    end, ATimeoutMs);
end;

procedure TestDispatcherFreeNonBlocking;
var
  LReleaseSource: TTgCancellationSource;
  LRelease: ITgCancellation;
  LEntered: TEvent;
  LDispatcher: TTgUpdateDispatcher;
  LSinkRef: ITgUpdateSink;
  LWatch: TStopwatch;
  LReleased: Boolean;
begin
  LReleaseSource := TTgCancellationSource.Create;
  LRelease := LReleaseSource;
  LEntered := TEvent.Create(nil, True, False, '');
  LReleased := False;
  try
    // 1) Free без Stop при зависшем обработчике.
    LDispatcher := NewHangingDispatcher(LEntered, LRelease);
    LSinkRef := LDispatcher;
    LDispatcher.Start;
    LDispatcher.Post(RawOf(MsgUpdate(1, 1, 1, 'x')), nil);
    Check(LEntered.WaitFor(5000) = TWaitResult.wrSignaled, 'обработчик вошёл (Free без Stop)');
    LWatch := TStopwatch.StartNew;
    LSinkRef := nil;
    GDispatcherFreeHangingMs := LWatch.ElapsedMilliseconds;
    Check(GDispatcherFreeHangingMs < 100,
      Format('Free диспетчера без Stop при зависшем обработчике < 100 мс (%d мс)', [GDispatcherFreeHangingMs]));

    // 2) Stop = False, затем Free.
    LEntered.ResetEvent;
    LDispatcher := NewHangingDispatcher(LEntered, LRelease);
    LSinkRef := LDispatcher;
    LDispatcher.Start;
    LDispatcher.Post(RawOf(MsgUpdate(2, 2, 1, 'x')), nil);
    Check(LEntered.WaitFor(5000) = TWaitResult.wrSignaled, 'обработчик вошёл (Stop, затем Free)');
    Check(not LDispatcher.Stop(100), 'Stop(100) = False при зависшем обработчике');
    LWatch := TStopwatch.StartNew;
    LSinkRef := nil;
    GDispatcherFreeAfterStopMs := LWatch.ElapsedMilliseconds;
    Check(GDispatcherFreeAfterStopMs < 100,
      Format('Free диспетчера после Stop = False < 100 мс (%d мс)', [GDispatcherFreeAfterStopMs]));
    Check(LReleaseSource.RefCount > 1, 'ядра живы, пока обработчики висят');

    LReleaseSource.Cancel;
    LReleased := WaitRefCountOne(LReleaseSource, 5000);
    Check(LReleased, 'после возврата обработчиков ядра и обработчики освобождены');
  finally
    LSinkRef := nil;
    // Не дождались освобождения — событие может быть ещё нужно обработчику.
    if LReleased then
      LEntered.Free;
    LRelease := nil;
  end;
end;

procedure TestSourceFreeNonBlocking;
var
  LRelease: TEvent;
  LTransport: TScriptTransport;
  LTransportRef: ITgTransport;
  LSource: TTgLongPollSource;
  LSourceRef: ITgUpdateSource;
  LDispatcher: TTgUpdateDispatcher;
  LSinkRef: ITgUpdateSink;
  LLog: TIdLog;
  LWatch: TStopwatch;
  LReleased: Boolean;
begin
  LRelease := TEvent.Create(nil, True, False, '');
  LLog := TIdLog.Create;
  LReleased := False;
  try
    LTransport := TScriptTransport.Create(BlockingPollScript(LRelease));
    LTransportRef := LTransport;
    LDispatcher := TTgUpdateDispatcher.Create(RecordTo(LLog));
    LSinkRef := LDispatcher;
    LDispatcher.Start;

    // 1) Free без Stop при висящем (неотменяемом) getUpdates.
    LSource := TTgLongPollSource.Create(LTransportRef);
    LSourceRef := LSource;
    LSource.Start(LSinkRef);
    Check(WaitUntil(
      function: Boolean
      begin
        Result := LTransport.Count('getUpdates') = 1;
      end, 5000), 'getUpdates висит (Free без Stop)');
    LWatch := TStopwatch.StartNew;
    LSourceRef := nil;
    GSourceFreeHangingMs := LWatch.ElapsedMilliseconds;
    Check(GSourceFreeHangingMs < 100,
      Format('Free источника без Stop при висящем запросе < 100 мс (%d мс)', [GSourceFreeHangingMs]));

    // 2) Stop = False, затем Free.
    LSource := TTgLongPollSource.Create(LTransportRef);
    LSourceRef := LSource;
    LSource.Start(LSinkRef);
    Check(WaitUntil(
      function: Boolean
      begin
        Result := LTransport.Count('getUpdates') = 2;
      end, 5000), 'getUpdates висит (Stop, затем Free)');
    Check(not LSource.Stop(200), 'Stop(200) = False: неотменяемый запрос');
    LWatch := TStopwatch.StartNew;
    LSourceRef := nil;
    GSourceFreeAfterStopMs := LWatch.ElapsedMilliseconds;
    Check(GSourceFreeAfterStopMs < 100,
      Format('Free источника после Stop = False < 100 мс (%d мс)', [GSourceFreeAfterStopMs]));
    Check(LTransport.RefCount > 1, 'отпущенные потоки держат транспорт, пока запрос висит');

    LRelease.SetEvent;
    LReleased := WaitTransportReleased(LTransport, 5000);
    Check(LReleased, 'после ответа потоки завершились, ядра освобождены');
    CheckEquals(2, LTransport.Count('getUpdates'), 'после остановки новых запросов нет');
    CheckEquals(0, LLog.Count, 'ответы после остановки выброшены');
    Check(LDispatcher.Stop(2000), 'диспетчер остановлен');
  finally
    LSourceRef := nil;
    LSinkRef := nil;
    if LReleased then
    begin
      LLog.Free;
      LRelease.Free;
    end;
  end;
end;

procedure TestDeliveryMainOrphans;
var
  LMarkerSource: TTgCancellationSource;
  LMarker: ITgCancellation;
  LCount: Integer;
  LDispatcher: TTgUpdateDispatcher;
  LSinkRef: ITgUpdateSink;
  LStopDone: TEvent;
  LStopped: Boolean;
  LWatch: TStopwatch;
  I: Integer;
begin
  LMarkerSource := TTgCancellationSource.Create;
  LMarker := LMarkerSource;
  LCount := 0;
  LStopDone := TEvent.Create(nil, True, False, '');
  try
    // 1) Free без Stop: задания ждут в очереди главного потока, CheckSynchronize не вызывается.
    LDispatcher := NewMarkedMainDispatcher(LMarker, @LCount);
    LSinkRef := LDispatcher;
    LDispatcher.Start;
    for I := 1 to 3 do
      LDispatcher.Post(RawOf(MsgUpdate(I, I, 1, 'x')), nil);
    TThread.Sleep(200);
    LWatch := TStopwatch.StartNew;
    LSinkRef := nil;
    GMainOrphanFreeMs := LWatch.ElapsedMilliseconds;
    Check(GMainOrphanFreeMs < 100,
      Format('Free диспетчера (Main, задания в очереди) < 100 мс (%d мс)', [GMainOrphanFreeMs]));
    // Без CheckSynchronize: процедуры сняты из очереди вместе с потоками (RemoveQueuedEvents).
    Check(WaitRefCountOne(LMarkerSource, 5000),
      'Free: брошенные задания сняты из очереди без CheckSynchronize, ядро освобождено');

    // 2) Stop из фонового потока (без прокачки очереди), затем Free.
    LDispatcher := NewMarkedMainDispatcher(LMarker, @LCount);
    LSinkRef := LDispatcher;
    LDispatcher.Start;
    for I := 1 to 3 do
      LDispatcher.Post(RawOf(MsgUpdate(10 + I, I, 1, 'x')), nil);
    TThread.Sleep(200);
    LStopped := False;
    // Ожидание — на событии, не TThread.WaitFor (тот в главном потоке прокачивает очередь).
    TThread.CreateAnonymousThread(
      procedure
      begin
        LStopped := LDispatcher.Stop(2000);
        LStopDone.SetEvent;
      end).Start;
    Check(LStopDone.WaitFor(5000) = TWaitResult.wrSignaled, 'Stop из фонового потока вернулся');
    Check(LStopped, 'Stop = True: брошенные задания не держат потоки диспетчера');
    LSinkRef := nil;
    Check(WaitRefCountOne(LMarkerSource, 5000),
      'Stop + Free: брошенные задания сняты из очереди без CheckSynchronize, ядро освобождено');

    for I := 1 to 5 do
      CheckSynchronize(10);
    CheckEquals(0, TInterlocked.CompareExchange(LCount, 0, 0), 'осиротевшие процедуры не выполнялись');
  finally
    LSinkRef := nil;
    LMarker := nil;
    LStopDone.Free;
  end;
end;

{$IFDEF MSWINDOWS}
/// <summary>
///   Дочерний процесс (ключ --exit-hang): бот и отдельный диспетчер с
///   обработчиками, висящими 60 с; диспетчер — Free без Stop, бот — Stop(200)
///   = False и Free; затем выход из программы. Объекты, нужные висящим
///   обработчикам, намеренно не освобождаются (отчёт об утечках выключен).
///   Код: 0 — сценарий выполнен; 3–5 — сбой сценария.
/// </summary>
function RunExitHangChild: Integer;
var
  LNeverSource: TTgCancellationSource;
  LNever: ITgCancellation;
  LEntered, LBotEntered: TEvent;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LDispatcher: TTgUpdateDispatcher;
  LSinkRef: ITgUpdateSink;
  LWatch: TStopwatch;
begin
  LNeverSource := TTgCancellationSource.Create;
  LNever := LNeverSource;
  LEntered := TEvent.Create(nil, True, False, '');
  LBotEntered := TEvent.Create(nil, True, False, '');
  LTransportRef := TScriptCancellableTransport.Create(SingleMessageScript('hang'));
  LBot := TTgBot.Create(LTransportRef);
  LBot.DrainTimeoutMs := 100;
  LBot.OnMessage :=
    procedure(ACtx: ITgContext)
    begin
      LBotEntered.SetEvent;
      LNever.WaitFor(60000);
    end;
  LBot.Start;
  LDispatcher := TTgUpdateDispatcher.Create(NewHangingRawHandler(LEntered, LNever, 60000));
  LSinkRef := LDispatcher;
  LDispatcher.Start;
  LDispatcher.Post(RawOf(MsgUpdate(1, 1, 1, 'x')), nil);
  if (LEntered.WaitFor(5000) <> TWaitResult.wrSignaled) or
    (LBotEntered.WaitFor(5000) <> TWaitResult.wrSignaled) then
    Exit(3);
  LWatch := TStopwatch.StartNew;
  LSinkRef := nil;
  if LBot.Stop(200) then
    Exit(4);
  LBot.Free;
  if LWatch.ElapsedMilliseconds > 1000 then
    Exit(5);
  Result := 0;
end;

procedure TestProcessExitWithHangingHandlers;
var
  LStartup: TStartupInfo;
  LProcess: TProcessInformation;
  LCommand: string;
  LWatch: TStopwatch;
  LWait, LCode: DWORD;
begin
  FillChar(LStartup, SizeOf(LStartup), 0);
  LStartup.cb := SizeOf(LStartup);
  LCommand := '"' + ParamStr(0) + '" ' + CExitHangSwitch;
  UniqueString(LCommand);
  LWatch := TStopwatch.StartNew;
  if not CreateProcess(nil, PChar(LCommand), nil, nil, False, 0, nil, nil, LStartup, LProcess) then
  begin
    Check(False, 'дочерний процесс запущен: ' + SysErrorMessage(GetLastError));
    Exit;
  end;
  try
    LWait := WaitForSingleObject(LProcess.hProcess, 15000);
    GExitHangMs := LWatch.ElapsedMilliseconds;
    if LWait <> WAIT_OBJECT_0 then
      TerminateProcess(LProcess.hProcess, 99);
    LCode := 99;
    GetExitCodeProcess(LProcess.hProcess, LCode);
  finally
    CloseHandle(LProcess.hThread);
    CloseHandle(LProcess.hProcess);
  end;
  Check(LWait = WAIT_OBJECT_0, 'процесс с висящими обработчиками завершился');
  CheckEquals(0, LCode, 'код выхода 0: сценарий выполнен, без AV при завершении');
  Check(GExitHangMs < 2000,
    Format('процесс завершился < 2 с (%d мс, включая запуск)', [GExitHangMs]));
end;
{$ENDIF}

{ 6A4: состояние бота, OnFault }

type
  /// <summary>
  ///   Управление сценарием FaultScript (поля меняет тест, читает поток
  ///   источника): Mode 0 — getUpdates → 401, 1 — исправный (висит до
  ///   отмены); Pending = 1 — ближайший getUpdates отдаёт сообщение NextId.
  /// </summary>
  TFaultScriptState = class
  public
    Mode: Integer;
    Pending: Integer;
    NextId: Integer;
    /// <summary>Следующий запуск: режим AMode, при AId > 0 — одно сообщение mAId.</summary>
    procedure Arm(AMode, AId: Integer);
  end;

var
  // Замеры 6A4.
  GRunFaultedMs: Int64 = -1;
  GStopFaultedMs: Int64 = -1;
  GFreeFaultedMs: Int64 = -1;

procedure TFaultScriptState.Arm(AMode, AId: Integer);
begin
  NextId := AId;
  AtomicExchange(Mode, AMode);
  if AId > 0 then
    AtomicExchange(Pending, 1)
  else
    AtomicExchange(Pending, 0);
end;

/// <summary>Транспорт бота по TFaultScriptState; прочие методы — сообщение.</summary>
function FaultScript(AState: TFaultScriptState): TFakeHandler;
begin
  Result :=
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      if AMethod <> 'getUpdates' then
        Exit(JsonOf(CShortMessageJson));
      // Итоговое подтверждение offset при Stop.
      if TTgJson.GetInt(AParams.Json, 'timeout') = 0 then
        Exit(TJSONArray.Create);
      if AtomicExchange(AState.Pending, 0) = 1 then
        Exit(Batch([MsgUpdate(AState.NextId, 100, 7, 'm' + IntToStr(AState.NextId))]));
      if AtomicCmpExchange(AState.Mode, 0, 0) = 0 then
        raise ETgApiError.Create('getUpdates', 401, 'Unauthorized');
      Result := HangUntilCancelled;
    end;
end;

function BotStateName(AState: TTgBotState): string;
begin
  case AState of
    TTgBotState.Idle: Result := 'Idle';
    TTgBotState.Running: Result := 'Running';
    TTgBotState.Stopping: Result := 'Stopping';
    TTgBotState.Faulted: Result := 'Faulted';
  else
    Result := '?';
  end;
end;

/// <summary>Код ETgApiError; -1 — другое исключение.</summary>
function ApiCode(AError: Exception): Int64;
begin
  if AError is ETgApiError then
    Result := ETgApiError(AError).ErrorCode
  else
    Result := -1;
end;

procedure TestBotFaultState;
var
  LScript: TFaultScriptState;
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LLog: TTextLog;
  LFaults, LErrors: TIdLog;
  LText: string;
begin
  LScript := TFaultScriptState.Create;
  LLog := TTextLog.Create;
  LFaults := TIdLog.Create;
  LErrors := TIdLog.Create;
  try
    // Первый getUpdates отдаёт m1, второй — 401.
    LScript.Arm(0, 1);
    LTransport := TScriptCancellableTransport.Create(FaultScript(LScript));
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      Check(LBot.State = TTgBotState.Idle, 'до Start: Idle');
      LBot.OnMessage :=
        procedure(ACtx: ITgContext)
        begin
          // m1 принят до отказа: диспетчер дорабатывает его уже в Faulted.
          if ACtx.Text = 'm1' then
            WaitUntil(
              function: Boolean
              begin
                Result := LBot.State = TTgBotState.Faulted;
              end, 5000);
          ACtx.Reply('ok');
          LLog.Add('handled ' + ACtx.Text + ' state=' + BotStateName(LBot.State));
        end;
      LBot.OnError :=
        procedure(AError: Exception; ACtx: ITgContext)
        begin
          LErrors.Add(ApiCode(AError));
          LLog.Add(Format('error %d ctx=%s', [ApiCode(AError), BoolToStr(Assigned(ACtx), True)]));
        end;
      LBot.OnFault :=
        procedure(AError: Exception)
        begin
          LLog.Add(Format('fault %d state=%s active=%s', [ApiCode(AError),
            BotStateName(LBot.State), BoolToStr(LBot.Active, True)]));
          if Raises(
            procedure
            begin
              LBot.Stop;
            end, ETgError) then
            LLog.Add('stop-in-fault');
          if Raises(
            procedure
            begin
              LBot.Start;
            end, ETgError) then
            LLog.Add('start-in-fault');
          LFaults.Add(ApiCode(AError));
        end;
      LBot.Start;
      Check(WaitUntil(
        function: Boolean
        begin
          Result := LFaults.Count > 0;
        end, 5000), '401 → OnFault');
      Check(LBot.State = TTgBotState.Faulted, 'State = Faulted');
      Check(not LBot.Active, 'Active = False в Faulted');
      Check(LBot.SourceState = TTgSourceState.Faulted, 'SourceState = Faulted');
      Check(WaitUntil(
        function: Boolean
        begin
          Result := LLog.Has('handled m1 state=Faulted');
        end, 5000), 'принятое до отказа дообработано в Faulted (диспетчер жив)');
      TThread.Sleep(200);
      CheckEquals(1, LFaults.Count, 'OnFault ровно один раз');
      if LFaults.Count > 0 then
        CheckEquals(401, LFaults.ToArray[0], 'OnFault: ETgApiError 401');
      CheckEquals(1, LErrors.Count, 'OnError ровно один раз');
      LText := LLog.Text;
      Check(LLog.Has('error 401 ctx=False'), 'OnError(E, nil) с 401');
      Check(LLog.Has('fault 401 state=Faulted active=False'), 'в OnFault State = Faulted');
      Check((Pos('error 401', LText) > 0) and (Pos('error 401', LText) < Pos('fault 401', LText)),
        'порядок: OnError, затем OnFault: ' + LText);
      Check(LLog.Has('stop-in-fault'), 'Stop из OnFault → ETgError');
      Check(LLog.Has('start-in-fault'), 'Start из OnFault → ETgError');
      CheckEquals(2, LTransport.Count('getUpdates'), '401 без повторов');
    finally
      LBot.Free;
    end;
  finally
    LErrors.Free;
    LFaults.Free;
    LLog.Free;
    LScript.Free;
  end;
end;

/// <summary>Ждёт ACount вызовов OnFault и State = Faulted (≤ 5 с).</summary>
function WaitBotFaults(ABot: TTgBot; AFaults: TIdLog; ACount: Integer): Boolean;
begin
  Result := WaitUntil(
    function: Boolean
    begin
      Result := (AFaults.Count >= ACount) and (ABot.State = TTgBotState.Faulted);
    end, 5000);
end;

/// <summary>Ждёт строку AText в журнале (≤ 5 с).</summary>
function WaitLogHas(ALog: TTextLog; const AText: string): Boolean;
begin
  Result := WaitUntil(
    function: Boolean
    begin
      Result := ALog.Has(AText);
    end, 5000);
end;

{ Повторный запуск после Faulted: явный Stop и неявный (Start из Faulted). }
procedure TestBotFaultRestart;
var
  LScript: TFaultScriptState;
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LLog: TTextLog;
  LFaults: TIdLog;
  LWatch: TStopwatch;
begin
  LScript := TFaultScriptState.Create;
  LLog := TTextLog.Create;
  LFaults := TIdLog.Create;
  try
    LScript.Arm(0, 0);
    LTransport := TScriptCancellableTransport.Create(FaultScript(LScript));
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      LBot.OnMessage :=
        procedure(ACtx: ITgContext)
        begin
          LLog.Add('handled ' + ACtx.Text + ' state=' + BotStateName(LBot.State));
        end;
      LBot.OnFault :=
        procedure(AError: Exception)
        begin
          LFaults.Add(ApiCode(AError));
        end;
      // 1. Отказ → явный Stop → Idle → Start с исправным транспортом.
      LBot.Start;
      Check(WaitBotFaults(LBot, LFaults, 1), 'запуск 1: Faulted');
      LWatch := TStopwatch.StartNew;
      Check(LBot.Stop, 'Stop из Faulted = True');
      GStopFaultedMs := LWatch.ElapsedMilliseconds;
      Check(GStopFaultedMs < 1000, Format('Stop из Faulted < 1 с (%d мс)', [GStopFaultedMs]));
      Check(LBot.State = TTgBotState.Idle, 'после Stop: Idle');
      Check(not LBot.Active, 'после Stop: Active = False');
      Check(LBot.Stop, 'повторный Stop = True');
      LScript.Arm(1, 2);
      LBot.Start;
      Check(LBot.State = TTgBotState.Running, 'запуск 2: Running');
      Check(LBot.Active, 'запуск 2: Active');
      Check(WaitLogHas(LLog, 'handled m2 state=Running'), 'запуск 2: обновление обработано');
      Check(LBot.Stop, 'запуск 2: Stop = True');
      Check(LBot.State = TTgBotState.Idle, 'запуск 2: Idle');
      // 2. Отказ → Start без Stop (неявный Stop) → работает.
      LScript.Arm(0, 0);
      LBot.Start;
      Check(WaitBotFaults(LBot, LFaults, 2), 'запуск 3: Faulted, OnFault второй раз (по разу за запуск)');
      LScript.Arm(1, 3);
      Check(not Raises(
        procedure
        begin
          LBot.Start;
        end, Exception), 'Start из Faulted без Stop — без исключения');
      Check(LBot.State = TTgBotState.Running, 'запуск 4: Running');
      Check(WaitLogHas(LLog, 'handled m3 state=Running'), 'запуск 4: обновление обработано');
      Check(Raises(
        procedure
        begin
          LBot.Start;
        end, ETgError), 'Start в Running → ETgError');
      CheckEquals(2, LFaults.Count, 'OnFault — по одному на каждый отказ');
      // 3. Отказ и Free без Stop: ресурсы освобождаются, OnFault больше не вызывается.
      LBot.Stop;
      LScript.Arm(0, 0);
      LBot.Start;
      Check(WaitBotFaults(LBot, LFaults, 3), 'запуск 5: Faulted');
    finally
      LWatch := TStopwatch.StartNew;
      LBot.Free;
      GFreeFaultedMs := LWatch.ElapsedMilliseconds;
    end;
    Check(GFreeFaultedMs < 1000, Format('Free в Faulted < 1 с (%d мс)', [GFreeFaultedMs]));
    TThread.Sleep(100);
    CheckEquals(3, LFaults.Count, 'после Free OnFault не вызывается');
  finally
    LFaults.Free;
    LLog.Free;
    LScript.Free;
  end;
end;

{ Run при отказе: завершается сам, без исключения, результат False. }
procedure TestBotRunFaulted;
var
  LScript: TFaultScriptState;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LFaults, LErrors: TIdLog;
  LWatch: TStopwatch;
  LResult: Boolean;
begin
  LScript := TFaultScriptState.Create;
  LFaults := TIdLog.Create;
  LErrors := TIdLog.Create;
  try
    LScript.Arm(0, 0);
    LTransportRef := TScriptCancellableTransport.Create(FaultScript(LScript));
    LBot := TTgBot.Create(LTransportRef);
    try
      LBot.OnError :=
        procedure(AError: Exception; ACtx: ITgContext)
        begin
          LErrors.Add(ApiCode(AError));
        end;
      LBot.OnFault :=
        procedure(AError: Exception)
        begin
          LFaults.Add(ApiCode(AError));
        end;
      LResult := True;
      LWatch := TStopwatch.StartNew;
      Check(not Raises(
        procedure
        begin
          LResult := LBot.Run;
        end, Exception), 'Run при Faulted не выбрасывает исключение');
      GRunFaultedMs := LWatch.ElapsedMilliseconds;
      Check(GRunFaultedMs < 1000, Format('Run при Faulted завершился < 1 с (%d мс)', [GRunFaultedMs]));
      Check(not LResult, 'Run = False при Faulted');
      CheckEquals(1, LFaults.Count, 'OnFault один раз');
      CheckEquals(1, LErrors.Count, 'OnError один раз');
      Check(LBot.State = TTgBotState.Idle, 'после Run: Idle (Stop выполнен)');
    finally
      LBot.Free;
    end;
  finally
    LErrors.Free;
    LFaults.Free;
    LScript.Free;
  end;
end;

{ Переходы в обычном цикле: Idle → Running → Stopping (виден из обработчика при дренаже) → Idle. }
procedure TestBotStateTransitions;
var
  LScript: TFaultScriptState;
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LLog: TTextLog;
  LEntered: TEvent;
begin
  LScript := TFaultScriptState.Create;
  LLog := TTextLog.Create;
  LEntered := TEvent.Create(nil, True, False, '');
  try
    LScript.Arm(1, 1);
    LTransport := TScriptCancellableTransport.Create(FaultScript(LScript));
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      LLog.Add('before=' + BotStateName(LBot.State) + ' active=' + BoolToStr(LBot.Active, True));
      LBot.OnMessage :=
        procedure(ACtx: ITgContext)
        begin
          LLog.Add('handler=' + BotStateName(LBot.State));
          LEntered.SetEvent;
          // Ждём, пока главный поток войдёт в Stop (дренаж принятого).
          WaitUntil(
            function: Boolean
            begin
              Result := LBot.State <> TTgBotState.Running;
            end, 5000);
          LLog.Add('drain=' + BotStateName(LBot.State) + ' active=' + BoolToStr(LBot.Active, True));
        end;
      LBot.Start;
      LLog.Add('started=' + BotStateName(LBot.State) + ' active=' + BoolToStr(LBot.Active, True));
      Check(LEntered.WaitFor(5000) = TWaitResult.wrSignaled, 'обработчик запущен');
      Check(LBot.Stop, 'Stop = True');
      LLog.Add('stopped=' + BotStateName(LBot.State) + ' active=' + BoolToStr(LBot.Active, True));
    finally
      LBot.Free;
    end;
    Check(LLog.Has('before=Idle active=False'), 'до Start: Idle');
    Check(LLog.Has('started=Running active=True'), 'после Start: Running, Active');
    Check(LLog.Has('handler=Running'), 'в обработчике: Running');
    Check(LLog.Has('drain=Stopping active=False'), 'во время Stop (дренаж): Stopping, Active = False');
    Check(LLog.Has('stopped=Idle active=False'), 'после Stop: Idle: ' + LLog.Text);
  finally
    LEntered.Free;
    LLog.Free;
    LScript.Free;
  end;
end;

{ Фаза 6B1: маршрутизатор TTgBot }

var
  // Замеры 6B1.
  GRouteSwapGrowth: Int64 = -1;

/// <summary>JSON обновления callback_query с данными AData (чат 100, пользователь 7).</summary>
function CbUpdate(AId: Int64; const AData: string): string;
begin
  Result := Format('{"update_id":%d,"callback_query":{"id":"cb%d","from":{"id":7,"is_bot":false,' +
    '"first_name":"U"},"chat_instance":"ci","data":"%s","message":{"message_id":55,"date":1,' +
    '"chat":{"id":100,"type":"private"},"text":"t"}}}', [AId, AId, AData]);
end;

/// <summary>
///   Транспорт маршрутизатора: первый getUpdates (без offset) отдаёт
///   AUpdates, следующие висят до отмены; getMe — @ThisBot (AFailGetMe —
///   ошибка 502), setMyCommands — True (AFailSetMyCommands — ошибка 400).
/// </summary>
function RouterScript(const AUpdates: TArray<string>; AFailGetMe, AFailSetMyCommands: Boolean): TFakeHandler;
begin
  Result :=
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      if AMethod = 'getUpdates' then
      begin
        if TTgJson.GetInt(AParams.Json, 'timeout') = 0 then
          Exit(TJSONArray.Create);
        if not TTgJson.Has(AParams.Json, 'offset') then
          Exit(Batch(AUpdates));
        Exit(HangUntilCancelled);
      end;
      if AMethod = 'getMe' then
      begin
        if AFailGetMe then
          raise ETgApiError.Create('getMe', 502, 'Bad Gateway');
        Exit(JsonOf('{"id":42,"is_bot":true,"first_name":"B","username":"ThisBot"}'));
      end;
      if AMethod = 'setMyCommands' then
      begin
        if AFailSetMyCommands then
          raise ETgApiError.Create('setMyCommands', 400, 'Bad Request: invalid command');
        Exit(TJSONTrue.Create);
      end;
      if AMethod = 'sendMessage' then
        Exit(JsonOf(CShortMessageJson));
      Result := TJSONTrue.Create;
    end;
end;

/// <summary>Start, ожидание приёма пакета (второй getUpdates), Stop с дренажом обработчиков.</summary>
procedure RunRouterBot(ABot: TTgBot; ATransport: TScriptTransport);
begin
  ABot.Start;
  Check(WaitUntil(
    function: Boolean
    begin
      Result := ATransport.Count('getUpdates') >= 2;
    end, 5000), 'пакет обновлений принят');
  Check(ABot.Stop, 'Stop = True');
end;

/// <summary>Индекс первого вызова AMethod в AMethods; -1 — нет.</summary>
function FirstCall(const AMethods: TArray<string>; const AMethod: string): Integer;
var
  I: Integer;
begin
  for I := 0 to High(AMethods) do
    if AMethods[I] = AMethod then
      Exit(I);
  Result := -1;
end;

procedure TestRouterMessages;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LLog, LErrors: TTextLog;
  LMenu: TArray<string>;
  LMethods: TArray<string>;
begin
  LLog := TTextLog.Create;
  LErrors := TTextLog.Create;
  try
    LTransport := TScriptCancellableTransport.Create(RouterScript(TArray<string>.Create(
      MsgUpdate(1, 100, 7, '/start'),
      MsgUpdate(2, 100, 7, '/START'),
      MsgUpdate(3, 100, 7, '/start@ThisBot'),
      MsgUpdate(4, 100, 7, '/start@thisbot x'),
      MsgUpdate(5, 100, 7, '/start@OtherBot'),
      MsgUpdate(6, 100, 7, '/start  arg1 arg2 '),
      MsgUpdate(7, 100, 7, '/help'),
      MsgUpdate(8, 100, 7, '/H@ThisBot'),
      MsgUpdate(9, 100, 7, '/foo bar'),
      MsgUpdate(10, 100, 7, 'привет'),
      MsgUpdate(11, 100, 7, 'ПРИВЕТ'),
      MsgUpdate(12, 100, 7, 'приветик'),
      MsgUpdate(13, 100, 7, 'order 123'),
      MsgUpdate(14, 100, 7, 'Hello world'),
      MsgUpdate(15, 100, 7, 'just text'),
      MsgUpdate(16, 100, 7, '/pass 5'),
      MsgUpdate(17, 100, 7, '/skip'),
      '{"update_id":18,"message":{"message_id":18,"date":1,"chat":{"id":100,"type":"private"},' +
        '"from":{"id":7,"is_bot":false,"first_name":"U"},"photo":[]}}'), False, False));
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      Check(LBot.SetMyCommandsOnStart, 'SetMyCommandsOnStart по умолчанию True');
      CheckEquals('', LBot.BotUserName, 'BotUserName до Start');
      LBot.OnUpdate :=
        procedure(ACtx: ITgContext)
        begin
          if ACtx.Command <> '' then
            LLog.Add('upd ' + ACtx.Command);
          // Перехват в OnUpdate: правила и OnMessage не вызываются.
          if ACtx.Command = 'skip' then
            ACtx.Handled := True;
        end;
      LBot.OnMessage :=
        procedure(ACtx: ITgContext)
        begin
          LLog.Add('msg [' + ACtx.Text + ']');
        end;
      LBot.OnUnknownCommand :=
        procedure(ACtx: ITgContext)
        begin
          LLog.Add('unknown ' + ACtx.Command + ' [' + ACtx.Args + ']');
        end;
      LBot.OnError :=
        procedure(AError: Exception; ACtx: ITgContext)
        begin
          LErrors.Add(AError.ClassName + ': ' + AError.Message);
        end;
      LBot
        .Command('start', 'Запуск',
          procedure(ACtx: ITgContext)
          begin
            LLog.Add('start [' + ACtx.Args + '] ' + ACtx.Text);
          end)
        .Command(['help', '/H'], 'Справка',
          procedure(ACtx: ITgContext)
          begin
            LLog.Add('help ' + ACtx.Command);
          end)
        .Command('pass',
          procedure(ACtx: ITgContext)
          begin
            LLog.Add('pass [' + ACtx.Args + ']');
            // Пропустить дальше по правилам.
            ACtx.Handled := False;
          end)
        .Command('skip',
          procedure(ACtx: ITgContext)
          begin
            LLog.Add('skip-called');
          end)
        .Text('Привет',
          procedure(ACtx: ITgContext)
          begin
            LLog.Add('exact ' + ACtx.Text);
          end)
        .TextMatch('^прив(.+)$',
          procedure(ACtx: ITgContext)
          begin
            LLog.Add('match-priv [' + ACtx.Args + ']');
          end)
        .TextMatch('^order (\d+)$',
          procedure(ACtx: ITgContext)
          begin
            LLog.Add('order [' + ACtx.Args + ']');
          end)
        .TextMatch('(?i)^hello',
          procedure(ACtx: ITgContext)
          begin
            LLog.Add('hello [' + ACtx.Args + ']');
          end)
        .Text(
          procedure(ACtx: ITgContext)
          begin
            LLog.Add('any [' + ACtx.Text + '] cmd=' + ACtx.Command + ' args=' + ACtx.Args);
          end);
      RunRouterBot(LBot, LTransport);
      CheckEquals('ThisBot', LBot.BotUserName, 'BotUserName из getMe');
      // Повторный запуск: getMe не повторяется (кэш), меню отправляется снова.
      LBot.Start;
      Check(LBot.Stop, 'второй Stop = True');
    finally
      LBot.Free;
    end;
    // Команды.
    CheckEquals(5, LLog.CountOf('upd start'), 'ACtx.Command в OnUpdate (5 команд start этому боту)');
    CheckEquals(1, LLog.CountOf('start [] /start'), '/start');
    CheckEquals(1, LLog.CountOf('start [] /START'), '/START: регистр команды не важен');
    CheckEquals(1, LLog.CountOf('start [] /start@ThisBot'), '/start@ThisBot');
    CheckEquals(1, LLog.CountOf('start [x] /start@thisbot x'), '/start@thisbot: username без учёта регистра');
    CheckEquals(0, LLog.CountOf('start [] /start@OtherBot'), '/start@OtherBot — не срабатывает');
    CheckEquals(1, LLog.CountOf('any [/start@OtherBot] cmd= args='),
      'команда другому боту идёт дальше как текст, Command пуст');
    CheckEquals(1, LLog.CountOf('start [arg1 arg2] /start  arg1 arg2 '), 'Args без крайних пробелов');
    CheckEquals(1, LLog.CountOf('help help'), 'несколько имён: help');
    CheckEquals(1, LLog.CountOf('help h'), 'несколько имён: /H@ThisBot → h');
    CheckEquals(1, LLog.CountOf('unknown foo [bar]'), 'OnUnknownCommand: Command и Args');
    // Текст: точный → regex → любой.
    CheckEquals(1, LLog.CountOf('exact привет'), 'Text точный');
    CheckEquals(1, LLog.CountOf('exact ПРИВЕТ'), 'Text точный без учёта регистра');
    CheckEquals(0, LLog.CountOf('match-priv [ет]'), 'точный Text раньше TextMatch');
    CheckEquals(1, LLog.CountOf('match-priv [етик]'), 'TextMatch: первая группа');
    CheckEquals(1, LLog.CountOf('order [123]'), 'TextMatch: группа (\d+)');
    CheckEquals(1, LLog.CountOf('hello [Hello]'), 'TextMatch без групп: всё совпадение, (?i)');
    CheckEquals(1, LLog.CountOf('any [just text] cmd= args='), 'Text любой');
    // Handled.
    CheckEquals(1, LLog.CountOf('pass [5]'), 'обработчик команды со сброшенным Handled');
    CheckEquals(1, LLog.CountOf('any [/pass 5] cmd=pass args=5'), 'Handled := False — дальше по правилам');
    CheckEquals(1, LLog.CountOf('upd skip'), 'OnUpdate видит /skip');
    CheckEquals(0, LLog.CountOf('skip-called'), 'OnUpdate Handled := True — правила не вызываются');
    Check(not Contains('[/skip]', LLog.Text), 'OnUpdate Handled := True — ни Text, ни OnMessage');
    // OnMessage — только не обработанное маршрутизатором.
    CheckEquals(1, LLog.CountOf('msg []'), 'OnMessage для сообщения без текста');
    Check(not Contains('msg [/', LLog.Text) and not Contains('msg [п', LLog.Text) and
      not Contains('msg [j', LLog.Text), 'OnMessage не вызывается для обработанных: ' + LLog.Text);
    CheckEquals(0, Length(LErrors.Text), 'OnError не вызывался: ' + LErrors.Text);
    // getMe и setMyCommands.
    // 6B2: getMe идёт в фоне параллельно с getUpdates (порядок не гарантирован);
    // гарантия — '/cmd@бот' маршрутизируется после getMe (проверено выше:
    // /start@ThisBot и /H@ThisBot сработали) без второго getMe.
    CheckEquals(1, LTransport.Count('getMe'), 'getMe один раз за два запуска');
    LMethods := LTransport.Methods;
    Check(FirstCall(LMethods, 'getMe') >= 0, 'getMe при Start (в фоне)');
    LMenu := LTransport.Calls('setMyCommands');
    CheckEquals(2, Length(LMenu), 'setMyCommands при каждом Start');
    if Length(LMenu) > 0 then
    begin
      CheckEquals('start', JsonAt(LMenu[0], 'commands[0].command'), 'меню: start');
      CheckEquals('Запуск', JsonAt(LMenu[0], 'commands[0].description'), 'меню: описание start');
      CheckEquals('help', JsonAt(LMenu[0], 'commands[1].command'), 'меню: help (первое имя)');
      CheckEquals('Справка', JsonAt(LMenu[0], 'commands[1].description'), 'меню: описание help');
      CheckEquals('', JsonAt(LMenu[0], 'commands[2].command'), 'меню: без синонимов и команд без описания');
    end;
  finally
    LErrors.Free;
    LLog.Free;
  end;
end;

procedure TestRouterCallbacks;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LLog: TTextLog;
  LAnswers, LMethods: TArray<string>;
  LAnswer: string;
  LYes, LAuto: Integer;
begin
  LLog := TTextLog.Create;
  try
    LTransport := TScriptCancellableTransport.Create(RouterScript(TArray<string>.Create(
      CbUpdate(1, 'yes'),
      CbUpdate(2, 'page:2'),
      CbUpdate(3, 'pagex'),
      CbUpdate(4, 'page:'),
      CbUpdate(5, 'zzz'),
      MsgUpdate(6, 100, 7, 'random'),
      MsgUpdate(7, 100, 7, '/x@ThisBot q')), False, False));
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      LBot.OnUpdate :=
        procedure(ACtx: ITgContext)
        begin
          if ACtx.Command <> '' then
            LLog.Add('upd ' + ACtx.Command + ' [' + ACtx.Args + ']');
        end;
      LBot.OnCallbackQuery :=
        procedure(ACtx: ITgContext)
        begin
          LLog.Add('cbq ' + ACtx.Data);
        end;
      LBot.OnMessage :=
        procedure(ACtx: ITgContext)
        begin
          LLog.Add('msg ' + ACtx.Text);
        end;
      LBot
        .Callback('yes',
          procedure(ACtx: ITgContext)
          begin
            LLog.Add('yes [' + ACtx.Args + '] ' + ACtx.Data);
            ACtx.Answer('ok');
          end)
        .CallbackPrefix('page:',
          procedure(ACtx: ITgContext)
          begin
            LLog.Add('page [' + ACtx.Args + '] ' + ACtx.Data);
          end)
        .CallbackPrefix('pa',
          procedure(ACtx: ITgContext)
          begin
            LLog.Add('pa [' + ACtx.Args + '] ' + ACtx.Data);
          end);
      RunRouterBot(LBot, LTransport);
    finally
      LBot.Free;
    end;
    CheckEquals(1, LLog.CountOf('yes [] yes'), 'Callback точный');
    CheckEquals(1, LLog.CountOf('page [2] page:2'), 'CallbackPrefix: Args = остаток, Data полностью');
    CheckEquals(0, LLog.CountOf('pa [ge:2] page:2'), 'первое подходящее правило по порядку регистрации');
    CheckEquals(1, LLog.CountOf('pa [gex] pagex'), 'второй префикс');
    CheckEquals(1, LLog.CountOf('page [] page:'), 'префикс без остатка: Args пуст');
    CheckEquals(1, LLog.CountOf('cbq zzz'), 'не сработавший callback → OnCallbackQuery');
    Check(not Contains('cbq yes', LLog.Text) and not Contains('cbq page', LLog.Text),
      'OnCallbackQuery не вызывается для обработанных');
    CheckEquals(1, LLog.CountOf('msg random'), 'сообщение без правил → OnMessage');
    CheckEquals(1, LLog.CountOf('upd x [q]'), 'команда без правил: Command/Args в OnUpdate');
    CheckEquals(1, LLog.CountOf('msg /x@ThisBot q'), 'команда без правил и OnUnknownCommand → OnMessage');
    // Без команд при Start getMe не нужен: username — лениво, на /x@ThisBot.
    CheckEquals(1, LTransport.Count('getMe'), 'getMe один раз (лениво)');
    LMethods := LTransport.Methods;
    Check(FirstCall(LMethods, 'getMe') > FirstCall(LMethods, 'getUpdates'),
      'без команд getMe при Start не вызывается');
    CheckEquals(0, LTransport.Count('setMyCommands'), 'без команд setMyCommands не вызывается');
    // AutoAnswerCallbacks: на 'yes' ответил обработчик, остальные — автоответ.
    LAnswers := LTransport.Calls('answerCallbackQuery');
    CheckEquals(5, Length(LAnswers), 'answerCallbackQuery на каждый callback ровно один раз');
    LYes := 0;
    LAuto := 0;
    for LAnswer in LAnswers do
      if JsonAt(LAnswer, 'callback_query_id') = 'cb1' then
      begin
        Inc(LYes);
        CheckEquals('ok', JsonAt(LAnswer, 'text'), 'ответ обработчика');
      end
      else if JsonAt(LAnswer, 'text') = '' then
        Inc(LAuto);
    CheckEquals(1, LYes, 'отвеченный обработчиком — без автоответа');
    CheckEquals(4, LAuto, 'автоответ на неотвеченные (в т.ч. обработанные правилом)');
  finally
    LLog.Free;
  end;
end;

/// <summary>Бот с одной командой 'a' (описание ADescription): число setMyCommands за Start/Stop.</summary>
function RouterMenuCalls(ASetOnStart: Boolean; const ADescription: string): Integer;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
begin
  LTransport := TScriptCancellableTransport.Create(RouterScript(nil, False, False));
  LTransportRef := LTransport;
  LBot := TTgBot.Create(LTransportRef);
  try
    LBot.SetMyCommandsOnStart := ASetOnStart;
    LBot.Command('a', ADescription,
      procedure(ACtx: ITgContext)
      begin
      end);
    RunRouterBot(LBot, LTransport);
  finally
    LBot.Free;
  end;
  CheckEquals(1, LTransport.Count('getMe'), 'getMe при Start (есть команда)');
  Result := LTransport.Count('setMyCommands');
end;

procedure TestRouterStartErrors;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LLog, LErrors: TTextLog;
begin
  LLog := TTextLog.Create;
  LErrors := TTextLog.Create;
  try
    LTransport := TScriptCancellableTransport.Create(RouterScript(TArray<string>.Create(
      MsgUpdate(1, 100, 7, '/start'),
      MsgUpdate(2, 100, 7, '/start@ThisBot')), True, True));
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      LBot.OnError :=
        procedure(AError: Exception; ACtx: ITgContext)
        begin
          LErrors.Add(Format('err %d ctx=%s', [ApiCode(AError), BoolToStr(Assigned(ACtx), True)]));
        end;
      LBot.OnMessage :=
        procedure(ACtx: ITgContext)
        begin
          LLog.Add('msg ' + ACtx.Text);
        end;
      LBot.Command('start', 'Запуск',
        procedure(ACtx: ITgContext)
        begin
          LLog.Add('start ' + ACtx.Text);
        end);
      LBot.Start;
      CheckEquals('Running', BotStateName(LBot.State), 'ошибки getMe/setMyCommands не прерывают Start');
      Check(WaitUntil(
        function: Boolean
        begin
          Result := LTransport.Count('getUpdates') >= 2;
        end, 5000), 'пакет обновлений принят');
      Check(LBot.Stop, 'Stop = True');
      CheckEquals('', LBot.BotUserName, 'BotUserName пуст после ошибки getMe');
    finally
      LBot.Free;
    end;
    CheckEquals(1, LErrors.CountOf('err 502 ctx=False'), 'ошибка getMe → OnError(E, nil)');
    CheckEquals(1, LErrors.CountOf('err 400 ctx=False'), 'ошибка setMyCommands → OnError(E, nil)');
    CheckEquals(2, LErrors.CountOf('err 502 ctx=False') + LErrors.CountOf('err 400 ctx=False'),
      'других ошибок нет: ' + LErrors.Text);
    CheckEquals(1, LLog.CountOf('start /start'), 'бот работает: /start обработан');
    CheckEquals(1, LLog.CountOf('msg /start@ThisBot'),
      'username неизвестен (ленивый getMe тоже неудачен) — /start@бот не считается своей');
    CheckEquals(2, LTransport.Count('getMe'), 'getMe: при Start и лениво (без OnError)');
    CheckEquals(1, LTransport.Count('setMyCommands'), 'setMyCommands при Start');
  finally
    LErrors.Free;
    LLog.Free;
  end;
  // Меню: SetMyCommandsOnStart и наличие описаний.
  CheckEquals(1, RouterMenuCalls(True, 'Описание'), 'команда с описанием → setMyCommands');
  CheckEquals(0, RouterMenuCalls(False, 'Описание'), 'SetMyCommandsOnStart = False → без setMyCommands');
  CheckEquals(0, RouterMenuCalls(True, ''), 'команды без описания → без setMyCommands');
end;

procedure TestRouterValidation;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LEmpty: TProc<ITgContext>;
begin
  LTransport := TScriptCancellableTransport.Create(RouterScript(nil, False, False));
  LTransportRef := LTransport;
  LBot := TTgBot.Create(LTransportRef);
  try
    LEmpty :=
      procedure(ACtx: ITgContext)
      begin
      end;
    Check(Raises(procedure begin LBot.Command('', LEmpty); end, ETgError), 'Command('''') → ETgError');
    Check(Raises(procedure begin LBot.Command('/', LEmpty); end, ETgError), 'Command(''/'') → ETgError');
    Check(Raises(procedure begin LBot.Command('a b', LEmpty); end, ETgError), 'пробел в имени → ETgError');
    Check(Raises(procedure begin LBot.Command('a@b', LEmpty); end, ETgError), '@ в имени → ETgError');
    Check(Raises(procedure begin LBot.Command(['ok', ''], LEmpty); end, ETgError),
      'пустое имя в списке → ETgError');
    Check(Raises(procedure begin LBot.Callback('', LEmpty); end, ETgError), 'Callback('''') → ETgError');
    Check(Raises(procedure begin LBot.CallbackPrefix('', LEmpty); end, ETgError),
      'CallbackPrefix('''') → ETgError');
    Check(Raises(procedure begin LBot.Text('', LEmpty); end, ETgError), 'Text('''') → ETgError');
    Check(Raises(procedure begin LBot.TextMatch('(', LEmpty); end, Exception),
      'неверный шаблон TextMatch → исключение при регистрации');
    Check(LBot.Command('a', LEmpty) = LBot, 'Command возвращает Self');
    Check(LBot.Command('a', nil) = LBot, 'Command(…, nil) удаляет правило');
    Check(LBot.TextMatch('^x$', nil) = LBot, 'удаление незарегистрированного — без ошибки');
  finally
    LBot.Free;
    // LEmpty — замыкание этого же кадра: без сброса кадр ссылается сам на себя.
    LEmpty := nil;
  end;
end;

/// <summary>
///   Бот с непрерывным потоком (команда, текст, callback, неизвестная команда
///   в 4 чата); другой поток AIterations раз регистрирует и удаляет правила.
///   Возвращает число обработанных правилами обновлений.
/// </summary>
function RunRouteSwap(AIterations: Integer; out AErrors: Integer; out AFirstError: string): Integer;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LCount, LErrorCount: Integer;
  LFirstError: string;
  LThread: TThread;
begin
  LCount := 0;
  LErrorCount := 0;
  LTransport := TScriptCancellableTransport.Create(
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    var
      LOffset, LId: Int64;
      LItems: TArray<string>;
      I: Integer;
    begin
      if AMethod = 'getUpdates' then
      begin
        if TTgJson.GetInt(AParams.Json, 'timeout') = 0 then
          Exit(TJSONArray.Create);
        if TTgJson.Has(AParams.Json, 'offset') then
          LOffset := TTgJson.GetInt64(AParams.Json, 'offset')
        else
          LOffset := 1;
        SetLength(LItems, 4);
        for I := 0 to 3 do
        begin
          LId := LOffset + I;
          case Integer(LId mod 4) of
            0: LItems[I] := MsgUpdate(LId, 100 + LId mod 4, 7, '/c ' + IntToStr(LId));
            1: LItems[I] := MsgUpdate(LId, 100 + LId mod 4, 7, 'm' + IntToStr(LId));
            2: LItems[I] := CbUpdate(LId, 'p:' + IntToStr(LId));
          else
            LItems[I] := MsgUpdate(LId, 100 + LId mod 4, 7, '/u' + IntToStr(LId));
          end;
        end;
        Exit(Batch(LItems));
      end;
      // Команда зарегистрирована до Start — getMe при Start.
      if AMethod = 'getMe' then
        Exit(JsonOf('{"id":42,"is_bot":true,"first_name":"B","username":"ThisBot"}'));
      Result := TJSONTrue.Create;
    end);
  LTransportRef := LTransport;
  LBot := TTgBot.Create(LTransportRef);
  try
    LBot.MaxParallel := 4;
    LBot.OnError :=
      procedure(AError: Exception; ACtx: ITgContext)
      begin
        // Текст пишет только первый (остальные — лишь счётчик).
        if TInterlocked.Increment(LErrorCount) = 1 then
          LFirstError := AError.ClassName + ': ' + AError.Message;
      end;
    LBot.Command('c', NewCountingHandler(@LCount));
    LBot.Start;
    Check(WaitUntil(
      function: Boolean
      begin
        Result := TInterlocked.CompareExchange(LCount, 0, 0) > 0;
      end, 5000), 'поток обновлений идёт');
    LThread := TThread.CreateAnonymousThread(
      procedure
      var
        I, LBefore: Integer;
        LWatch: TStopwatch;
      begin
        LBefore := TInterlocked.CompareExchange(LCount, 0, 0);
        LWatch := TStopwatch.StartNew;
        I := 0;
        // Не меньше AIterations и не меньше 100 обработанных правилами за цикл
        // (регистрация действительно идёт одновременно с маршрутизацией).
        while (I < AIterations) or ((TInterlocked.CompareExchange(LCount, 0, 0) - LBefore < 100) and
          (LWatch.ElapsedMilliseconds < 5000)) do
        begin
          Inc(I);
          // Каждый раз новое замыкание: заменённое/удалённое освобождается на ходу.
          case I mod 6 of
            0: LBot.Command(['c', 'cc'], 'Команда', NewCountingHandler(@LCount));
            1: LBot.TextMatch('^m(\d+)$', NewCountingHandler(@LCount));
            2: LBot.CallbackPrefix('p:', NewCountingHandler(@LCount));
            3:
              begin
                LBot.Command('cc', nil);
                LBot.Text(NewCountingHandler(@LCount));
                LBot.OnUnknownCommand := NewCountingHandler(@LCount);
              end;
            4:
              begin
                LBot.TextMatch('^m(\d+)$', nil);
                LBot.Text(nil);
              end;
          else
            LBot.CallbackPrefix('p:', nil);
            LBot.OnUnknownCommand := nil;
          end;
        end;
      end);
    LThread.FreeOnTerminate := False;
    try
      LThread.Start;
      LThread.WaitFor;
    finally
      LThread.Free;
    end;
    Check(LBot.Stop, 'Stop = True после перерегистраций');
  finally
    LBot.Free;
  end;
  // Ядро могло освободиться в потоке обработчика — ждём, а не проверяем мгновенно.
  WaitTransportReleased(LTransport, 2000);
  CheckEquals(1, LTransport.RefCount, 'бот отпустил транспорт');
  AErrors := TInterlocked.CompareExchange(LErrorCount, 0, 0);
  AFirstError := LFirstError;
  Result := TInterlocked.CompareExchange(LCount, 0, 0);
end;

procedure TestRouterLiveRegistration;
const
  CIterations = 3000;
var
  LBlocks0, LBytes0, LBlocks1, LBytes1: Int64;
  LHandled, LErrors: Integer;
  LFirstError: string;
begin
  // Прогрев: пулы потоков, ленивые синглтоны, PCRE.
  RunRouteSwap(300, LErrors, LFirstError);
  CheckEquals(0, LErrors, 'прогрев: OnError не вызывался: ' + LFirstError);
  MemoryInUse(LBlocks0, LBytes0);
  LHandled := RunRouteSwap(CIterations, LErrors, LFirstError);
  MemoryInUse(LBlocks1, LBytes1);
  GRouteSwapGrowth := LBlocks1 - LBlocks0;
  Writeln(Format('    %d перерегистраций: обработано правилами %d, прирост блоков = %d, байт = %d',
    [CIterations, LHandled, LBlocks1 - LBlocks0, LBytes1 - LBytes0]));
  Check(LHandled > 0, 'обновления обработаны правилами');
  CheckEquals(0, LErrors, 'OnError не вызывался (нет AV и исключений маршрутизатора)' + ': ' + LFirstError);
  Check(LBlocks1 - LBlocks0 < 200,
    Format('память не растёт после %d перерегистраций (%d блоков)', [CIterations, LBlocks1 - LBlocks0]));
end;

{ Фаза 6B2: компонент TTelegramBot }

type
  /// <summary>
  ///   Тестовый наследник: счётчик созданных ботов (CreateBot — точка
  ///   подмены) и режим дизайнера (SetDesigning — защищённый метод TComponent).
  /// </summary>
  TTestTelegramBot = class(TTelegramBot)
  protected
    function CreateBot: TTgBot; override;
  public
    Created: Integer;
    procedure Design;
  end;

  /// <summary>Обработчики событий компонента — методы объекта, как у формы.</summary>
  TComponentEvents = class
  private
    FNotMain: Integer;
    procedure NoteThread;
  public
    Log: TTextLog;
    // Задано — OnUpdate для текста 'hang' ждёт это событие.
    HangUpdate: TEvent;
    constructor Create;
    destructor Destroy; override;
    procedure DoStart(Sender: TObject);
    procedure DoStop(Sender: TObject; Reason: TTgStopReason);
    procedure DoUpdate(Sender: TObject; const Ctx: ITgContext; var Handled: Boolean);
    procedure DoMessage(Sender: TObject; const Ctx: ITgContext);
    procedure DoCommand(Sender: TObject; const Ctx: ITgContext);
    procedure DoCallback(Sender: TObject; const Ctx: ITgContext);
    procedure DoError(Sender: TObject; E: Exception; const Ctx: ITgContext);
    procedure DoFault(Sender: TObject; E: Exception);
    procedure DoExecute(Sender: TObject; const Ctx: ITgContext);
    procedure DoWebhookRegistered(Sender: TObject);
    /// <summary>Сколько событий пришло не в главном потоке.</summary>
    function NotMain: Integer;
  end;

var
  // Замеры 6B2.
  GCompStartMs: Int64 = -1;
  GCompFreeHangMs: Int64 = -1;

function TTestTelegramBot.CreateBot: TTgBot;
begin
  Inc(Created);
  Result := inherited CreateBot;
end;

procedure TTestTelegramBot.Design;
begin
  SetDesigning(True);
end;

constructor TComponentEvents.Create;
begin
  inherited Create;
  Log := TTextLog.Create;
end;

destructor TComponentEvents.Destroy;
begin
  Log.Free;
  HangUpdate.Free;
  inherited Destroy;
end;

procedure TComponentEvents.NoteThread;
begin
  if TThread.CurrentThread.ThreadID <> MainThreadID then
    AtomicIncrement(FNotMain);
end;

function TComponentEvents.NotMain: Integer;
begin
  Result := AtomicCmpExchange(FNotMain, 0, 0);
end;

procedure TComponentEvents.DoStart(Sender: TObject);
begin
  NoteThread;
  Log.Add('start');
end;

procedure TComponentEvents.DoStop(Sender: TObject; Reason: TTgStopReason);
begin
  NoteThread;
  if Reason = TTgStopReason.Fault then
    Log.Add('stop fault')
  else
    Log.Add('stop requested');
end;

procedure TComponentEvents.DoUpdate(Sender: TObject; const Ctx: ITgContext; var Handled: Boolean);
begin
  NoteThread;
  if Assigned(HangUpdate) and (Ctx.Text = 'hang') then
  begin
    Log.Add('hang-begin');
    HangUpdate.WaitFor(5000);
    Log.Add('hang-end');
  end;
  // Перехват: команда /skip дальше не идёт.
  if Ctx.Command = 'skip' then
    Handled := True;
end;

procedure TComponentEvents.DoMessage(Sender: TObject; const Ctx: ITgContext);
begin
  NoteThread;
  Log.Add('msg ' + Ctx.Text);
end;

procedure TComponentEvents.DoCommand(Sender: TObject; const Ctx: ITgContext);
begin
  NoteThread;
  Log.Add('cmd ' + Ctx.Command + ' [' + Ctx.Args + ']');
end;

procedure TComponentEvents.DoCallback(Sender: TObject; const Ctx: ITgContext);
begin
  NoteThread;
  Log.Add('cbq ' + Ctx.Data);
end;

procedure TComponentEvents.DoError(Sender: TObject; E: Exception; const Ctx: ITgContext);
begin
  NoteThread;
  Log.Add(Format('err %s %d ctx=%s', [E.ClassName, ApiCode(E), BoolToStr(Assigned(Ctx), True)]));
end;

procedure TComponentEvents.DoFault(Sender: TObject; E: Exception);
begin
  NoteThread;
  Log.Add(Format('fault %d', [ApiCode(E)]));
end;

procedure TComponentEvents.DoExecute(Sender: TObject; const Ctx: ITgContext);
begin
  NoteThread;
  Log.Add('exec ' + Ctx.Command + ' [' + Ctx.Args + ']');
end;

procedure TComponentEvents.DoWebhookRegistered(Sender: TObject);
begin
  NoteThread;
  Log.Add('registered');
end;

/// <summary>Ждёт условия, обрабатывая очередь главного потока (CheckSynchronize).</summary>
function PumpUntil(const ACondition: TFunc<Boolean>; ATimeoutMs: Integer): Boolean;
var
  LWatch: TStopwatch;
begin
  LWatch := TStopwatch.StartNew;
  while not ACondition() do
  begin
    if LWatch.ElapsedMilliseconds > ATimeoutMs then
      Exit(False);
    CheckSynchronize(5);
  end;
  Result := True;
end;

/// <summary>Загружает свойства компонента из текстового DFM (csLoading, затем Loaded).</summary>
procedure LoadFromDfm(AComponent: TComponent; const AText: string);
var
  LText: TStringStream;
  LBinary: TMemoryStream;
begin
  LText := TStringStream.Create(AText);
  LBinary := TMemoryStream.Create;
  try
    ObjectTextToBinary(LText, LBinary);
    LBinary.Position := 0;
    LBinary.ReadComponent(AComponent);
  finally
    LBinary.Free;
    LText.Free;
  end;
end;

/// <summary>Позиция первой записи журнала, начинающейся с APrefix; -1 — нет.</summary>
function LogIndex(ALog: TTextLog; const APrefix: string): Integer;
begin
  // Text — записи в кавычках через запятую.
  Result := Pos('"' + APrefix, ALog.Text) - 1;
end;

procedure TestComponentBasics;
var
  LEvents: TComponentEvents;
  LBot: TTestTelegramBot;
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LItem: TTgCommandItem;
  LMenu: TArray<string>;
begin
  LEvents := TComponentEvents.Create;
  try
    LBot := TTestTelegramBot.Create(nil);
    try
      Check(LBot.Delivery = TTgDelivery.Main, 'Delivery по умолчанию Main');
      CheckEquals('TGBOT_TOKEN', LBot.TokenEnv, 'TokenEnv по умолчанию');
      CheckEquals(TgDefaultApiUrl, LBot.ApiUrl, 'ApiUrl по умолчанию');
      Check(LBot.AutoAnswerCallbacks and LBot.SetMyCommandsOnStart and not LBot.DropPendingUpdates,
        'умолчания AutoAnswerCallbacks, SetMyCommandsOnStart, DropPendingUpdates');
      Check(not LBot.Active and not Assigned(LBot.Bot) and not Assigned(LBot.Api), 'до запуска Bot и Api = nil');
      // Пустой токен: ни Token, ни переменной окружения — ETgError, как у TTgBot.
      LBot.TokenEnv := 'TGBOT_TEST_NO_SUCH_VARIABLE_6B2';
      Check(Raises(
        procedure
        begin
          LBot.Active := True;
        end, ETgError), 'пустой токен → ETgError');
      Check(not LBot.Active and not Assigned(LBot.Bot), 'после ошибки запуска бота нет');
      // Регистрации проверяются сразу, а не при запуске.
      Check(Raises(
        procedure
        begin
          LBot.Command('a b', nil);
        end, ETgError), 'Command с пробелом → ETgError сразу');
      Check(Raises(
        procedure
        begin
          LBot.TextMatch('(', nil);
        end, Exception), 'неверный шаблон TextMatch → исключение сразу');

      LTransport := TScriptCancellableTransport.Create(RouterScript(TArray<string>.Create(
        MsgUpdate(1, 100, 7, '/start a'),
        MsgUpdate(2, 100, 7, '/go@ThisBot'),
        MsgUpdate(3, 100, 7, '/foo x'),
        MsgUpdate(4, 100, 7, '/skip'),
        MsgUpdate(5, 100, 7, 'hello'),
        MsgUpdate(6, 100, 7, 'кот'),
        CbUpdate(7, 'yes'),
        CbUpdate(8, 'zzz')), False, False));
      LTransportRef := LTransport;
      LBot.Transport := LTransportRef;
      LItem := LBot.Commands.Add;
      LItem.Command := 'start';
      LItem.Aliases := ' go , ';
      LItem.Description := 'Запуск';
      LItem.OnExecute := LEvents.DoExecute;
      // Без OnExecute — в OnCommand компонента.
      LBot.Commands.Add.Command := 'foo';
      CheckEquals('/start', LItem.DisplayName, 'DisplayName элемента');
      LBot.OnStart := LEvents.DoStart;
      LBot.OnStop := LEvents.DoStop;
      LBot.OnUpdate := LEvents.DoUpdate;
      LBot.OnMessage := LEvents.DoMessage;
      LBot.OnCommand := LEvents.DoCommand;
      LBot.OnCallbackQuery := LEvents.DoCallback;
      LBot.OnError := LEvents.DoError;
      LBot
        .Callback('yes',
          procedure(ACtx: ITgContext)
          begin
            LEvents.Log.Add('yes');
          end)
        .Text('кот',
          procedure(ACtx: ITgContext)
          begin
            LEvents.Log.Add('text ' + ACtx.Text);
          end);
      LBot.Active := True;
      Check(LBot.Active and Assigned(LBot.Bot) and Assigned(LBot.Api), 'Active = True: Bot и Api доступны');
      CheckEquals('Running', BotStateName(LBot.State), 'State = Running');
      // Свойства, влияющие на бота, при работе — ETgError; события — можно.
      Check(Raises(
        procedure
        begin
          LBot.Token := 'x';
        end, ETgError), 'Token при Active → ETgError');
      Check(Raises(
        procedure
        begin
          LBot.Delivery := TTgDelivery.Worker;
        end, ETgError), 'Delivery при Active → ETgError');
      Check(Raises(
        procedure
        begin
          LBot.AllowedUpdates := 'message';
        end, ETgError), 'AllowedUpdates при Active → ETgError');
      Check(Raises(
        procedure
        begin
          LBot.Proxy.Host := 'proxy';
        end, ETgError), 'Proxy.Host при Active → ETgError');
      Check(Raises(
        procedure
        begin
          LBot.Commands[0].Description := 'x';
        end, ETgError), 'элемент Commands при Active → ETgError');
      Check(Raises(
        procedure
        begin
          LBot.Commands.Add;
        end, ETgError), 'Commands.Add при Active → ETgError');
      CheckEquals(2, LBot.Commands.Count, 'неудачный Add не оставил элемента');
      LBot.OnFault := LEvents.DoFault;
      Check(PumpUntil(
        function: Boolean
        begin
          Result := LEvents.Log.Has('cbq zzz') and LEvents.Log.Has('yes');
        end, 5000), 'пакет обработан (первый запуск)');
      LBot.Active := False;
      Check(not LBot.Active and not Assigned(LBot.Bot), 'Active := False: бот освобождён');
      // Повторный запуск: новый TTgBot, коллекция и регистрации из кода применены снова.
      LBot.Start;
      Check(PumpUntil(
        function: Boolean
        begin
          Result := (LEvents.Log.CountOf('cbq zzz') = 2) and (LEvents.Log.CountOf('yes') = 2);
        end, 5000), 'пакет обработан (второй запуск)');
      LBot.Stop;
      CheckEquals(3, LBot.Created, 'CreateBot: при каждом запуске (в т.ч. неудачном)');
    finally
      LBot.Free;
    end;
    CheckEquals(2, LEvents.Log.CountOf('exec start [a]'), 'элемент Commands: OnExecute');
    CheckEquals(2, LEvents.Log.CountOf('exec go []'), 'синоним из Aliases, /go@ThisBot после фонового getMe');
    CheckEquals(2, LEvents.Log.CountOf('cmd foo [x]'), 'элемент без OnExecute → OnCommand');
    Check(not LEvents.Log.Has('cmd skip') and not LEvents.Log.Has('msg /skip'), 'OnUpdate: Handled := True');
    CheckEquals(2, LEvents.Log.CountOf('msg hello'), 'OnMessage');
    CheckEquals(2, LEvents.Log.CountOf('text кот'), 'Text из кода — между запусками сохраняется');
    CheckEquals(2, LEvents.Log.CountOf('cbq zzz'), 'OnCallbackQuery');
    CheckEquals(2, LEvents.Log.CountOf('start'), 'OnStart');
    CheckEquals(2, LEvents.Log.CountOf('stop requested'), 'OnStop(Requested)');
    Check(not LEvents.Log.Has('err'), 'OnError не вызывался: ' + LEvents.Log.Text);
    CheckEquals(0, LEvents.NotMain, 'Delivery = Main: все события в главном потоке');
    LMenu := LTransport.Calls('setMyCommands');
    CheckEquals(2, Length(LMenu), 'setMyCommands при каждом запуске');
    if Length(LMenu) > 0 then
    begin
      CheckEquals('start', JsonAt(LMenu[0], 'commands[0].command'), 'меню: start');
      CheckEquals('Запуск', JsonAt(LMenu[0], 'commands[0].description'), 'меню: описание');
      CheckEquals('', JsonAt(LMenu[0], 'commands[1].command'), 'меню: без синонимов и без описания');
    end;
  finally
    LEvents.Free;
  end;
end;

const
  CDfmActive =
    'object TelegramBot1: TTelegramBot' + sLineBreak +
    '  Active = True' + sLineBreak +
    '  PollingTimeout = 1' + sLineBreak +
    '  Commands = <' + sLineBreak +
    '    item' + sLineBreak +
    '      Command = ''start''' + sLineBreak +
    '      Description = ''Run''' + sLineBreak +
    '    end>' + sLineBreak +
    'end';

procedure TestComponentLoaded;
var
  LEvents: TComponentEvents;
  LBot: TTestTelegramBot;
  LTransportRef: ITgTransport;
begin
  LEvents := TComponentEvents.Create;
  try
    // 1. Active из формы: старт отложен до очереди — OnCreate успевает задать транспорт/токен.
    LBot := TTestTelegramBot.Create(nil);
    try
      LoadFromDfm(LBot, CDfmActive);
      CheckEquals(1, LBot.Commands.Count, 'коллекция загружена');
      CheckEquals(1, LBot.PollingTimeout, 'PollingTimeout загружен');
      Check(not LBot.Active and not Assigned(LBot.Bot) and (LBot.Created = 0),
        'после загрузки бот ещё не запущен');
      // «OnCreate формы».
      LTransportRef := TScriptCancellableTransport.Create(RouterScript(nil, False, False));
      LBot.Transport := LTransportRef;
      LBot.OnStart := LEvents.DoStart;
      Check(PumpUntil(
        function: Boolean
        begin
          Result := LBot.Active;
        end, 5000), 'отложенный запуск после Loaded (очередь главного потока)');
      CheckEquals(1, LEvents.Log.CountOf('start'), 'OnStart при отложенном запуске');
      LBot.Active := False;
    finally
      LBot.Free;
    end;
    // 2. Ошибка отложенного запуска — OnError(E, nil), не исключение.
    LBot := TTestTelegramBot.Create(nil);
    try
      LoadFromDfm(LBot, CDfmActive);
      LBot.TokenEnv := 'TGBOT_TEST_NO_SUCH_VARIABLE_6B2';
      LBot.OnError := LEvents.DoError;
      Check(not Raises(
        procedure
        begin
          PumpUntil(
            function: Boolean
            begin
              Result := LEvents.Log.Has('err ETgError');
            end, 2000);
        end, Exception), 'ошибка отложенного запуска не выбрасывается из очереди');
      CheckEquals(1, LEvents.Log.CountOf('err ETgError -1 ctx=False'), 'ошибка отложенного запуска → OnError(E, nil)');
      Check(not LBot.Active, 'после ошибки отложенного запуска Active = False');
    finally
      LBot.Free;
    end;
    // 3. Active := False до очереди отменяет отложенный запуск.
    LBot := TTestTelegramBot.Create(nil);
    try
      LoadFromDfm(LBot, CDfmActive);
      LBot.Transport := LTransportRef;
      LBot.Active := False;
      PumpUntil(
        function: Boolean
        begin
          Result := False;
        end, 100);
      Check(not LBot.Active and (LBot.Created = 0), 'Active := False до очереди: запуска нет');
    finally
      LBot.Free;
    end;
    // 4. Free до очереди: отложенный запуск не обращается к освобождённому компоненту.
    LBot := TTestTelegramBot.Create(nil);
    LoadFromDfm(LBot, CDfmActive);
    LBot.Free;
    Check(not Raises(
      procedure
      begin
        PumpUntil(
          function: Boolean
          begin
            Result := False;
          end, 100);
      end, Exception), 'Free до очереди: отложенный запуск пропущен');
    // 5. Дизайнер: Active только запоминается, свойства можно менять.
    LBot := TTestTelegramBot.Create(nil);
    try
      LBot.Design;
      LBot.Transport := LTransportRef;
      LBot.Active := True;
      Check(LBot.Active and not Assigned(LBot.Bot) and (LBot.Created = 0), 'дизайнер: Active = True без запуска');
      LBot.Token := 'x';
      CheckEquals('x', LBot.Token, 'дизайнер: свойства меняются');
    finally
      LBot.Free;
    end;
  finally
    LEvents.Free;
  end;
end;

procedure TestComponentFaultQueued;
var
  LEvents: TComponentEvents;
  LBot: TTelegramBot;
  LScript: TFaultScriptState;
  LTransportRef: ITgTransport;
  LErr, LFault, LStop: Integer;
begin
  LEvents := TComponentEvents.Create;
  LScript := TFaultScriptState.Create;
  try
    // Mode = 0: getUpdates → 401 (неустранимая ошибка).
    LTransportRef := TScriptCancellableTransport.Create(FaultScript(LScript));
    LBot := TTelegramBot.Create(nil);
    try
      LBot.Transport := LTransportRef;
      LBot.OnError := LEvents.DoError;
      LBot.OnFault := LEvents.DoFault;
      LBot.OnStop := LEvents.DoStop;
      LBot.Active := True;
      // Без подкачки очереди: отказ произошёл в потоке источника, события — в очереди.
      Check(WaitUntil(
        function: Boolean
        begin
          Result := Assigned(LBot.Bot) and (LBot.Bot.State = TTgBotState.Faulted);
        end, 5000), 'бот перешёл в Faulted');
      TThread.Sleep(50);
      Check(not LEvents.Log.Has('err') and not LEvents.Log.Has('fault'),
        'Delivery = Main: OnError/OnFault не вызываются из потока источника');
      Check(not LBot.Active, 'Faulted: Active = False');
      Check(PumpUntil(
        function: Boolean
        begin
          Result := LEvents.Log.Has('stop fault');
        end, 5000), 'OnStop(Fault) доставлен через очередь');
      LErr := LogIndex(LEvents.Log, 'err ETgApiError 401 ctx=False');
      LFault := LogIndex(LEvents.Log, 'fault 401');
      LStop := LogIndex(LEvents.Log, 'stop fault');
      Check((LErr >= 0) and (LErr < LFault) and (LFault < LStop),
        'порядок: OnError(E, nil) → OnFault → OnStop(Fault): ' + LEvents.Log.Text);
      Check(not Assigned(LBot.Bot), 'после OnFault бот освобождён в главном потоке');
      CheckEquals(0, LEvents.NotMain, 'все события в главном потоке');
      // Повторный отказ и Free до доставки: события освобождённого компонента не вызываются.
      LBot.Active := True;
      Check(WaitUntil(
        function: Boolean
        begin
          Result := Assigned(LBot.Bot) and (LBot.Bot.State = TTgBotState.Faulted);
        end, 5000), 'второй отказ');
      TThread.Sleep(50);
    finally
      LBot.Free;
    end;
    PumpUntil(
      function: Boolean
      begin
        Result := False;
      end, 200);
    CheckEquals(1, LEvents.Log.CountOf('fault 401'), 'после Free очередь не вызывает OnFault');
    CheckEquals(1, LEvents.Log.CountOf('err ETgApiError 401 ctx=False'), 'после Free очередь не вызывает OnError');
    CheckEquals(1, LEvents.Log.CountOf('stop fault'), 'после Free очередь не вызывает OnStop');
  finally
    LScript.Free;
    LEvents.Free;
  end;
end;

procedure TestComponentStartNonBlocking;
var
  LEvents: TComponentEvents;
  LBot: TTelegramBot;
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LInner: TFakeHandler;
  LWatch: TStopwatch;
begin
  LEvents := TComponentEvents.Create;
  try
    LInner := RouterScript(TArray<string>.Create(MsgUpdate(1, 100, 7, '/start@ThisBot')), False, False);
    // getMe отвечает через 2 с.
    LTransport := TScriptCancellableTransport.Create(
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      begin
        if AMethod = 'getMe' then
          TThread.Sleep(2000);
        Result := LInner(AMethod, AParams);
      end);
    LTransportRef := LTransport;
    LBot := TTelegramBot.Create(nil);
    try
      LBot.Transport := LTransportRef;
      LBot.OnError := LEvents.DoError;
      LBot.Command('start', 'Run',
        procedure(ACtx: ITgContext)
        begin
          LEvents.Log.Add('routed ' + ACtx.Command);
        end);
      LWatch := TStopwatch.StartNew;
      LBot.Active := True;
      GCompStartMs := LWatch.ElapsedMilliseconds;
      Check(GCompStartMs < 100, Format('Start не ждёт getMe (задержка 2 с): %d мс', [GCompStartMs]));
      CheckEquals('Running', BotStateName(LBot.State), 'сразу после Start — Running');
      Check(PumpUntil(
        function: Boolean
        begin
          Result := LEvents.Log.Has('routed start');
        end, 6000), '/start@ThisBot маршрутизирована после фонового getMe');
      CheckEquals(1, LTransport.Count('getMe'), 'getMe один раз (обработчик дождался фонового)');
      LBot.Active := False;
      // Обработчик ждёт только getMe, меню уходит позже; Stop дожидается
      // фоновой задачи — после него setMyCommands гарантированно отправлен.
      CheckEquals(1, LTransport.Count('setMyCommands'), 'setMyCommands в фоне (дождался Stop)');
    finally
      LBot.Free;
    end;
    Check(not LEvents.Log.Has('err'), 'без ошибок: ' + LEvents.Log.Text);
  finally
    LEvents.Free;
  end;
end;

procedure TestComponentDestroyHanging;
var
  LEvents: TComponentEvents;
  LBot: TTelegramBot;
  LTransportRef: ITgTransport;
  LWatch: TStopwatch;
begin
  LEvents := TComponentEvents.Create;
  try
    LEvents.HangUpdate := TEvent.Create(nil, True, False, '');
    LTransportRef := TScriptCancellableTransport.Create(RouterScript(TArray<string>.Create(
      MsgUpdate(1, 100, 7, 'hang')), False, False));
    LBot := TTelegramBot.Create(nil);
    LBot.Transport := LTransportRef;
    LBot.Delivery := TTgDelivery.Worker;
    LBot.OnUpdate := LEvents.DoUpdate;
    LBot.OnMessage := LEvents.DoMessage;
    LBot.OnError := LEvents.DoError;
    LBot.OnStop := LEvents.DoStop;
    LBot.Active := True;
    Check(WaitUntil(
      function: Boolean
      begin
        Result := LEvents.Log.Has('hang-begin');
      end, 5000), 'обработчик завис в OnUpdate');
    // Обработчик вернётся во время Free; дальше ядро вызвало бы OnMessage.
    TThread.CreateAnonymousThread(
      procedure
      begin
        TThread.Sleep(300);
        LEvents.HangUpdate.SetEvent;
      end).Start;
    LWatch := TStopwatch.StartNew;
    LBot.Free;
    GCompFreeHangMs := LWatch.ElapsedMilliseconds;
    Check(WaitUntil(
      function: Boolean
      begin
        Result := LEvents.Log.Has('hang-end');
      end, 5000), 'обработчик вернулся');
    TThread.Sleep(100);
    PumpUntil(
      function: Boolean
      begin
        Result := False;
      end, 100);
    Check(not LEvents.Log.Has('msg hang'), 'после Free событие формы (OnMessage) не вызвано: ' + LEvents.Log.Text);
    Check(not LEvents.Log.Has('stop'), 'Destroy не вызывает OnStop');
    Check(not LEvents.Log.Has('err'), 'без OnError после Free');
  finally
    LEvents.Free;
  end;
end;

{ Этап 6D1: webhook без HTTP-сервера }

type
  /// <summary>Сервер-заглушка: журнал RegisterBot/UnregisterBot, внешний URL.</summary>
  TTestWebhookServer = class(TTgCustomWebhookServer)
  public
    Log: TTextLog;
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure RegisterBot(const APath: string; ABot: TTelegramBot); override;
    procedure UnregisterBot(const APath: string; ABot: TTelegramBot); override;
    function GetWebhookUrl(const APath: string): string; override;
  end;

var
  // Замеры 6D1.
  GWebhookOverflowMs: Int64 = -1;

constructor TTestWebhookServer.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  Log := TTextLog.Create;
end;

destructor TTestWebhookServer.Destroy;
begin
  Log.Free;
  inherited Destroy;
end;

procedure TTestWebhookServer.RegisterBot(const APath: string; ABot: TTelegramBot);
begin
  Log.Add('reg ' + APath);
end;

procedure TTestWebhookServer.UnregisterBot(const APath: string; ABot: TTelegramBot);
begin
  Log.Add('unreg ' + APath);
end;

function TTestWebhookServer.GetWebhookUrl(const APath: string): string;
begin
  Result := 'https://srv.example' + APath;
end;

/// <summary>Транспорт webhook-тестов: setWebhook — true или 400 (AFailSetWebhook).</summary>
function WebhookScript(AFailSetWebhook: Boolean): TFakeHandler;
begin
  Result :=
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      if (AMethod = 'setWebhook') and AFailSetWebhook then
        raise ETgApiError.Create('setWebhook', 400, 'Bad Request: bad webhook');
      if AMethod = 'getUpdates' then
        Exit(TJSONArray.Create);
      Result := TJSONTrue.Create;
    end;
end;

/// <summary>Ждёт ACount вызовов setWebhook (≤ 5 с).</summary>
function WaitSetWebhook(ATransport: TScriptTransport; ACount: Integer): Boolean;
begin
  Result := WaitUntil(
    function: Boolean
    begin
      Result := ATransport.Count('setWebhook') >= ACount;
    end, 5000);
end;

/// <summary>Параметр AName вызова setWebhook номер AIndex (строкой; '' — нет).</summary>
function SetWebhookParam(ATransport: TScriptTransport; AIndex: Integer; const AName: string): string;
var
  LCalls: TArray<string>;
  LParams: TJSONObject;
  LValue: TJSONValue;
begin
  Result := '';
  LCalls := ATransport.Calls('setWebhook');
  if AIndex >= Length(LCalls) then
    Exit;
  LParams := TTgJson.ParseObject(LCalls[AIndex]);
  try
    LValue := TTgJson.GetValue(LParams, AName);
    if LValue is TJSONArray then
      Result := LValue.ToJSON
    else if Assigned(LValue) then
      Result := TTgJson.ScalarText(LValue);
  finally
    LParams.Free;
  end;
end;

function IsSecretAlphabet(const AValue: string): Boolean;
var
  C: Char;
begin
  Result := AValue <> '';
  for C in AValue do
    if not CharInSet(C, ['A'..'Z', 'a'..'z', '0'..'9', '_', '-']) then
      Exit(False);
end;

procedure TestWebhookBasics;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LLog: TTextLog;
  LSecret, LSecret2, LBig: string;
begin
  LLog := TTextLog.Create;
  try
    LTransport := TScriptCancellableTransport.Create(WebhookScript(False));
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      Check(LBot.Mode = TTgReceiveMode.Polling, 'Mode по умолчанию Polling');
      LBot.Mode := TTgReceiveMode.Webhook;
      LBot.WebhookUrl := 'https://example.org/tg/bot1';
      LBot.WebhookDropPendingUpdates := True;
      LBot.WebhookMaxConnections := 10;
      LBot.OnMessage :=
        procedure(ACtx: ITgContext)
        begin
          LLog.Add('msg ' + ACtx.Text);
        end;
      Check(LBot.HandleWebhook(MsgUpdate(1, 100, 7, 'a'), '') = TTgWebhookResult.Unavailable,
        'до Start: Unavailable');
      LBot.Start;
      Check(LBot.State = TTgBotState.Running, 'Start: Running');
      Check(LBot.SourceState = TTgSourceState.Running, 'SourceState (webhook) = Running');
      Check(WaitSetWebhook(LTransport, 1), 'setWebhook вызван в фоне');
      CheckEquals('https://example.org/tg/bot1', SetWebhookParam(LTransport, 0, 'url'), 'url');
      LSecret := SetWebhookParam(LTransport, 0, 'secret_token');
      Check(Length(LSecret) >= 32, 'secret_token сгенерирован, длина ≥ 32: ' + IntToStr(Length(LSecret)));
      Check(IsSecretAlphabet(LSecret), 'secret_token: только [A-Za-z0-9_-]');
      CheckEquals('[]', SetWebhookParam(LTransport, 0, 'allowed_updates'), 'allowed_updates = []');
      CheckEquals('true', SetWebhookParam(LTransport, 0, 'drop_pending_updates'), 'drop_pending_updates');
      CheckEquals('10', SetWebhookParam(LTransport, 0, 'max_connections'), 'max_connections');
      CheckEquals(0, LTransport.Count('getUpdates'), 'в режиме Webhook getUpdates не вызывается');
      // Верный секрет — Accepted, обработчик вызван.
      Check(LBot.HandleWebhook(MsgUpdate(1, 100, 7, 'one'), LSecret) = TTgWebhookResult.Accepted,
        'верный секрет: Accepted');
      Check(WaitLogHas(LLog, 'msg one'), 'обработчик вызван');
      // Неверный и пустой секрет — Forbidden.
      Check(LBot.HandleWebhook(MsgUpdate(2, 100, 7, 'two'), LSecret + 'x') = TTgWebhookResult.Forbidden,
        'секрет длиннее: Forbidden');
      Check(LBot.HandleWebhook(MsgUpdate(2, 100, 7, 'two'), Copy(LSecret, 1, Length(LSecret) - 1) + '!') =
        TTgWebhookResult.Forbidden, 'последний символ другой: Forbidden');
      Check(LBot.HandleWebhook(MsgUpdate(2, 100, 7, 'two'), Copy(LSecret, 1, 5)) =
        TTgWebhookResult.Forbidden, 'короткий секрет: Forbidden');
      Check(LBot.HandleWebhook(MsgUpdate(2, 100, 7, 'two'), '') = TTgWebhookResult.Forbidden,
        'пустой заголовок: Forbidden');
      // Мусор — BadRequest.
      Check(LBot.HandleWebhook('not json', LSecret) = TTgWebhookResult.BadRequest, 'не JSON: BadRequest');
      Check(LBot.HandleWebhook('', LSecret) = TTgWebhookResult.BadRequest, 'пустое тело: BadRequest');
      Check(LBot.HandleWebhook('[1,2]', LSecret) = TTgWebhookResult.BadRequest, 'массив: BadRequest');
      Check(LBot.HandleWebhook('{"message":{"text":"x"}}', LSecret) = TTgWebhookResult.BadRequest,
        'нет update_id: BadRequest');
      Check(LBot.HandleWebhook('{"update_id":"5"}', LSecret) = TTgWebhookResult.BadRequest,
        'update_id строкой: BadRequest');
      Check(LBot.HandleWebhook('{"update_id":1.5}', LSecret) = TTgWebhookResult.BadRequest,
        'update_id дробный: BadRequest');
      Check(LBot.HandleWebhook(TBytes.Create($FF, $FE, $7B), LSecret) = TTgWebhookResult.BadRequest,
        'некорректный UTF-8: BadRequest');
      // Тело больше 1 МБ — BadRequest (в символах и в байтах UTF-8).
      LBig := '{"update_id":9,"message":{"text":"' + StringOfChar('a', TgDefaultWebhookMaxBodySize) + '"}}';
      Check(LBot.HandleWebhook(LBig, LSecret) = TTgWebhookResult.BadRequest, '> 1 МБ: BadRequest');
      Check(LBot.HandleWebhook(TEncoding.UTF8.GetBytes(LBig), LSecret) = TTgWebhookResult.BadRequest,
        '> 1 МБ (TBytes): BadRequest');
      LBig := '{"update_id":9,"message":{"text":"' + StringOfChar(Char($044F) {'я'}, 600000) + '"}}';
      Check(LBot.HandleWebhook(LBig, LSecret) = TTgWebhookResult.BadRequest,
        '600 тыс. символов = 1,2 МБ UTF-8: BadRequest');
      LBig := '';
      // Перегрузка TBytes (UTF-8).
      Check(LBot.HandleWebhook(TEncoding.UTF8.GetBytes(MsgUpdate(3, 101, 7, 'три')), LSecret) =
        TTgWebhookResult.Accepted, 'TBytes: Accepted');
      Check(WaitLogHas(LLog, 'msg три'), 'TBytes: обработчик вызван, кириллица цела');
      // Повтор того же update_id — Accepted без повторной обработки.
      Check(LBot.HandleWebhook(MsgUpdate(1, 100, 7, 'one'), LSecret) = TTgWebhookResult.Accepted,
        'повтор update_id: Accepted');
      TThread.Sleep(150);
      CheckEquals(1, LLog.CountOf('msg one'), 'повтор не обработан повторно');
      Check(LBot.Stop, 'Stop = True');
      Check(LBot.State = TTgBotState.Idle, 'после Stop: Idle');
      CheckEquals(0, LTransport.Count('deleteWebhook'), 'без DeleteWebhookOnStop deleteWebhook нет');
      Check(LBot.HandleWebhook(MsgUpdate(4, 100, 7, 'four'), LSecret) = TTgWebhookResult.Unavailable,
        'после Stop: Unavailable');
      // Новый запуск — новый секрет; прежний не подходит.
      LBot.Start;
      Check(WaitSetWebhook(LTransport, 2), 'повторный Start: setWebhook');
      LSecret2 := SetWebhookParam(LTransport, 1, 'secret_token');
      Check((LSecret2 <> '') and (LSecret2 <> LSecret), 'повторный Start: новый секрет');
      Check(LBot.HandleWebhook(MsgUpdate(5, 100, 7, 'five'), LSecret) = TTgWebhookResult.Forbidden,
        'старый секрет: Forbidden');
      Check(LBot.HandleWebhook(MsgUpdate(5, 100, 7, 'five'), LSecret2) = TTgWebhookResult.Accepted,
        'новый секрет: Accepted');
      Check(WaitLogHas(LLog, 'msg five'), 'после перезапуска обработчик вызван');
      LBot.Stop;
    finally
      LBot.Free;
    end;
    CheckEquals(200, TgWebhookHttpStatus(TTgWebhookResult.Accepted), 'HTTP Accepted');
    CheckEquals(403, TgWebhookHttpStatus(TTgWebhookResult.Forbidden), 'HTTP Forbidden');
    CheckEquals(400, TgWebhookHttpStatus(TTgWebhookResult.BadRequest), 'HTTP BadRequest');
    CheckEquals(503, TgWebhookHttpStatus(TTgWebhookResult.Unavailable), 'HTTP Unavailable');
  finally
    LLog.Free;
  end;
end;

procedure TestWebhookQueueFull;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LLog: TTextLog;
  LHang: TEvent;
  LSecret: string;
  LWatch: TStopwatch;
  LResult: TTgWebhookResult;
begin
  LLog := TTextLog.Create;
  LHang := TEvent.Create(nil, True, False, '');
  try
    LTransport := TScriptCancellableTransport.Create(WebhookScript(False));
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      LBot.Mode := TTgReceiveMode.Webhook;
      LBot.WebhookUrl := 'https://example.org/hook';
      LBot.QueueCapacity := 1;
      LBot.MaxParallel := 1;
      LBot.OnMessage :=
        procedure(ACtx: ITgContext)
        begin
          if ACtx.Text = 'hang' then
          begin
            LLog.Add('hang-begin');
            LHang.WaitFor(10000);
          end;
          LLog.Add('msg ' + ACtx.Text);
        end;
      LBot.Start;
      Check(WaitSetWebhook(LTransport, 1), 'setWebhook');
      LSecret := SetWebhookParam(LTransport, 0, 'secret_token');
      Check(LBot.HandleWebhook(MsgUpdate(1, 100, 7, 'hang'), LSecret) = TTgWebhookResult.Accepted,
        'u1 (зависнет): Accepted');
      Check(WaitLogHas(LLog, 'hang-begin'), 'обработчик u1 завис');
      Check(LBot.HandleWebhook(MsgUpdate(2, 200, 7, 'q'), LSecret) = TTgWebhookResult.Accepted,
        'u2 занял очередь (ёмкость 1): Accepted');
      LWatch := TStopwatch.StartNew;
      LResult := LBot.HandleWebhook(MsgUpdate(3, 300, 7, 'over'), LSecret);
      GWebhookOverflowMs := LWatch.ElapsedMilliseconds;
      Check(LResult = TTgWebhookResult.Unavailable, 'переполнение: Unavailable');
      Check(GWebhookOverflowMs < 1000, 'переполнение: ответ < 1 с: ' + IntToStr(GWebhookOverflowMs));
      LHang.SetEvent;
      Check(WaitLogHas(LLog, 'msg q'), 'очередь разобрана');
      // update_id отклонённого не запомнен: повтор Telegram принимается.
      Check(LBot.HandleWebhook(MsgUpdate(3, 300, 7, 'over'), LSecret) = TTgWebhookResult.Accepted,
        'повтор после переполнения: Accepted');
      Check(WaitLogHas(LLog, 'msg over'), 'повтор после переполнения обработан');
      Check(LBot.Stop, 'Stop = True');
    finally
      LBot.Free;
    end;
  finally
    LHang.Free;
    LLog.Free;
  end;
end;

procedure TestWebhookFaultAndOptions;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LLog: TTextLog;
  LMethods: TArray<string>;
  LError: string;
begin
  LLog := TTextLog.Create;
  try
    // Ошибка setWebhook — Faulted, OnError затем OnFault.
    LTransport := TScriptCancellableTransport.Create(WebhookScript(True));
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      LBot.Mode := TTgReceiveMode.Webhook;
      LBot.WebhookUrl := 'https://example.org/hook';
      LBot.OnError :=
        procedure(AError: Exception; ACtx: ITgContext)
        begin
          LLog.Add(Format('error %d', [ApiCode(AError)]));
        end;
      LBot.OnFault :=
        procedure(AError: Exception)
        begin
          LLog.Add(Format('fault %d', [ApiCode(AError)]));
        end;
      LBot.Start;
      Check(WaitLogHas(LLog, 'fault 400'), 'ошибка setWebhook → OnFault');
      Check(LBot.State = TTgBotState.Faulted, 'State = Faulted');
      Check(LBot.SourceState = TTgSourceState.Faulted, 'SourceState = Faulted');
      Check(LogIndex(LLog, 'error 400') < LogIndex(LLog, 'fault 400'), 'OnError до OnFault: ' + LLog.Text);
      Check(LBot.HandleWebhook(MsgUpdate(1, 100, 7, 'x'), '') = TTgWebhookResult.Unavailable,
        'в Faulted: Unavailable');
      Check(LBot.Stop, 'Stop из Faulted');
      Check(LBot.State = TTgBotState.Idle, 'Stop из Faulted → Idle');
    finally
      LBot.Free;
    end;
    // DeleteWebhookOnStop, заданный секрет, проверки.
    LTransport := TScriptCancellableTransport.Create(WebhookScript(False));
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      LBot.Mode := TTgReceiveMode.Webhook;
      Check(Raises(
        procedure
        begin
          LBot.Start;
        end, ETgError), 'пустой WebhookUrl → ETgError');
      Check(LBot.State = TTgBotState.Idle, 'после ошибки Start: Idle');
      LBot.WebhookUrl := 'https://example.org/hook';
      LBot.WebhookSecretToken := 'bad secret!';
      LError := '';
      try
        LBot.Start;
      except
        on E: ETgError do
          LError := E.Message;
      end;
      Check(LError <> '', 'недопустимый секрет → ETgError');
      Check(not Contains('bad secret!', LError), 'секрет не попадает в текст ошибки');
      CheckEquals(0, Length(LTransport.Methods), 'ошибки проверки — без запросов');
      LBot.WebhookSecretToken := 'My_Fixed-Secret0123456789';
      LBot.DeleteWebhookOnStop := True;
      LBot.AllowedUpdates := TArray<string>.Create('message');
      // Немедленный Stop: setWebhook дожидается, затем deleteWebhook.
      LBot.Start;
      Check(LBot.Stop, 'Stop сразу после Start');
      LMethods := LTransport.Methods;
      CheckEquals('setWebhook,deleteWebhook', string.Join(',', LMethods), 'порядок вызовов');
      CheckEquals('My_Fixed-Secret0123456789', SetWebhookParam(LTransport, 0, 'secret_token'),
        'заданный секрет передан как есть');
      CheckEquals('["message"]', SetWebhookParam(LTransport, 0, 'allowed_updates'), 'явный allowed_updates');
      LBot.Start;
      Check(WaitSetWebhook(LTransport, 2), 'второй запуск: setWebhook');
      Check(LBot.HandleWebhook(MsgUpdate(1, 100, 7, 'x'), 'My_Fixed-Secret0123456789') =
        TTgWebhookResult.Accepted, 'заданный секрет: Accepted');
      Check(LBot.Stop, 'Stop');
      CheckEquals(2, LTransport.Count('deleteWebhook'), 'DeleteWebhookOnStop → deleteWebhook при каждом Stop');
    finally
      LBot.Free;
    end;
    // Генератор секрета.
    LError := TTgWebhookSource.GenerateSecretToken;
    CheckEquals(TgWebhookSecretLength, Length(LError), 'GenerateSecretToken: длина по умолчанию');
    Check(IsSecretAlphabet(LError), 'GenerateSecretToken: алфавит');
    Check(LError <> TTgWebhookSource.GenerateSecretToken, 'GenerateSecretToken: значения различаются');
    CheckEquals(256, Length(TTgWebhookSource.GenerateSecretToken(1000)), 'GenerateSecretToken: не больше 256');
    Check(not TTgWebhookSource.IsValidSecretToken(StringOfChar('a', 257)), 'IsValidSecretToken: 257 символов');
    Check(not TTgWebhookSource.IsValidSecretToken(''), 'IsValidSecretToken: пусто');
  finally
    LLog.Free;
  end;
end;

procedure TestComponentWebhook;
var
  LEvents: TComponentEvents;
  LBot: TTelegramBot;
  LServer: TTestWebhookServer;
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LSecret: string;
begin
  LEvents := TComponentEvents.Create;
  LServer := TTestWebhookServer.Create(nil);
  try
    LBot := TTelegramBot.Create(nil);
    try
      LBot.Name := 'Bot1';
      Check(LBot.Mode = TTgReceiveMode.Polling, 'Mode по умолчанию Polling');
      Check((LBot.Webhook.Url = '') and (LBot.Webhook.SecretToken = '') and
        (LBot.Webhook.MaxConnections = 0) and not LBot.Webhook.DropPendingUpdates and
        not LBot.Webhook.DeleteOnStop and (LBot.Webhook.Server = nil), 'Webhook: значения по умолчанию');
      CheckEquals('/tg/Bot1', LBot.Webhook.Path, 'Path по умолчанию /tg/ + Name');
      LBot.Webhook.Path := '/hook';
      CheckEquals('/hook', LBot.Webhook.Path, 'Path задан');
      LBot.Webhook.Path := '';
      LBot.Name := 'Bot2';
      CheckEquals('/tg/Bot2', LBot.Webhook.Path, 'Path по умолчанию следует за Name');
      Check(LBot.HandleWebhook(MsgUpdate(1, 100, 7, 'x'), '') = TTgWebhookResult.Unavailable,
        'не запущен: Unavailable');
      LTransport := TScriptCancellableTransport.Create(WebhookScript(False));
      LTransportRef := LTransport;
      LBot.Transport := LTransportRef;
      LBot.Delivery := TTgDelivery.Worker;
      LBot.Mode := TTgReceiveMode.Webhook;
      LSecret := 'CompSecret_1234567890abcdef';
      LBot.Webhook.SecretToken := LSecret;
      LBot.Webhook.DeleteOnStop := True;
      LBot.Webhook.MaxConnections := 5;
      LBot.Webhook.Server := LServer;
      LBot.OnMessage := LEvents.DoMessage;
      LBot.Active := True;
      Check(LServer.Log.Has('reg /tg/Bot2'), 'RegisterBot(Path) при запуске');
      Check(WaitSetWebhook(LTransport, 1), 'setWebhook');
      CheckEquals('https://srv.example/tg/Bot2', SetWebhookParam(LTransport, 0, 'url'),
        'Url пуст — берётся у Server.GetWebhookUrl(Path)');
      CheckEquals(LSecret, SetWebhookParam(LTransport, 0, 'secret_token'), 'secret_token');
      CheckEquals('5', SetWebhookParam(LTransport, 0, 'max_connections'), 'max_connections');
      Check(Raises(
        procedure
        begin
          LBot.Webhook.Url := 'https://other';
        end, ETgError), 'Webhook.Url при работе → ETgError');
      Check(Raises(
        procedure
        begin
          LBot.Mode := TTgReceiveMode.Polling;
        end, ETgError), 'Mode при работе → ETgError');
      Check(LBot.HandleWebhook(MsgUpdate(1, 100, 7, 'hi'), LSecret) = TTgWebhookResult.Accepted,
        'HandleWebhook проксирует: Accepted');
      Check(LBot.HandleWebhook(TEncoding.UTF8.GetBytes(MsgUpdate(2, 100, 7, 'bytes')), LSecret) =
        TTgWebhookResult.Accepted, 'HandleWebhook (TBytes): Accepted');
      Check(LBot.HandleWebhook(MsgUpdate(3, 100, 7, 'x'), 'wrong') = TTgWebhookResult.Forbidden,
        'HandleWebhook: неверный секрет → Forbidden');
      Check(WaitUntil(
        function: Boolean
        begin
          Result := LEvents.Log.Has('msg hi') and LEvents.Log.Has('msg bytes');
        end, 5000), 'обработчики компонента вызваны');
      LBot.Active := False;
      Check(LServer.Log.Has('unreg /tg/Bot2'), 'UnregisterBot при остановке');
      CheckEquals(1, LTransport.Count('deleteWebhook'), 'Webhook.DeleteOnStop → deleteWebhook');
      Check(LBot.HandleWebhook(MsgUpdate(4, 100, 7, 'x'), LSecret) = TTgWebhookResult.Unavailable,
        'после остановки: Unavailable');
      // Уничтожение сервера обнуляет ссылку (Notification).
      FreeAndNil(LServer);
      Check(LBot.Webhook.Server = nil, 'Free сервера → Webhook.Server = nil');
    finally
      LBot.Free;
    end;
  finally
    LServer.Free;
    LEvents.Free;
  end;
end;

type
  /// <summary>Журнал OnRequest/OnError TTgWebhookServer (вызываются в потоках Indy).</summary>
  TServerEvents = class
  public
    Log: TTextLog;
    constructor Create;
    destructor Destroy; override;
    procedure DoRequest(Sender: TObject; const AMethod, APath: string; AStatus: Integer);
    procedure DoError(Sender: TObject; E: Exception);
  end;

var
  // Замеры 6D2.
  GServerPostMs: Int64 = -1;
  GServer413Ms: Int64 = -1;

constructor TServerEvents.Create;
begin
  inherited Create;
  Log := TTextLog.Create;
end;

destructor TServerEvents.Destroy;
begin
  Log.Free;
  inherited Destroy;
end;

procedure TServerEvents.DoRequest(Sender: TObject; const AMethod, APath: string; AStatus: Integer);
begin
  Log.Add(Format('%s %s %d', [AMethod, APath, AStatus]));
end;

procedure TServerEvents.DoError(Sender: TObject; E: Exception);
begin
  Log.Add('error ' + E.ClassName);
end;

/// <summary>Код ответа на GET или POST (тело ABody, заголовок секрета, если задан).</summary>
function HttpStatus(const AMethod, AUrl, ABody, ASecret: string): Integer;
var
  LClient: THTTPClient;
  LSource: TStringStream;
  LHeaders: TNetHeaders;
begin
  LClient := THTTPClient.Create;
  try
    if ASecret <> '' then
      LHeaders := [TNetHeader.Create('X-Telegram-Bot-Api-Secret-Token', ASecret)];
    if AMethod = 'GET' then
      Exit(LClient.Get(AUrl, nil, LHeaders).StatusCode);
    LSource := TStringStream.Create(ABody, TEncoding.UTF8);
    try
      Result := LClient.Post(AUrl, LSource, nil, LHeaders).StatusCode;
    finally
      LSource.Free;
    end;
  finally
    LClient.Free;
  end;
end;

/// <summary>
///   Сырой запрос ARequest (+ ABody) на 127.0.0.1:APort; код из строки
///   статуса ответа, -1 — ответа нет за 5 с.
/// </summary>
function RawHttpStatus(APort: Integer; const ARequest, ABody: string): Integer;
var
  LClient: TIdTCPClient;
  LLine: string;
begin
  LClient := TIdTCPClient.Create(nil);
  try
    LClient.Host := '127.0.0.1';
    LClient.Port := APort;
    LClient.ConnectTimeout := 5000;
    LClient.ReadTimeout := 5000;
    LClient.Connect;
    try
      LClient.IOHandler.Write(ARequest + ABody);
      LLine := LClient.IOHandler.ReadLn;
      // 'HTTP/1.1 413 Payload Too Large'
      Result := StrToIntDef(Copy(LLine, Pos(' ', LLine) + 1, 3), -1);
    finally
      LClient.Disconnect;
    end;
  finally
    LClient.Free;
  end;
end;

procedure TestWebhookServer;
const
  CSecret1 = 'Srv1_secret_ABCdef0123456789';
  CSecret2 = 'Srv2_secret_XYZxyz9876543210';
var
  LServer, LServer2: TTgWebhookServer;
  LSrvEvents: TServerEvents;
  LEvents1, LEvents2: TComponentEvents;
  LBot1, LBot2, LBot3: TTelegramBot;
  LTransport1, LTransport2: TScriptCancellableTransport;
  LRef1, LRef2, LRef3: ITgTransport;
  LBase: string;
  LWatch: TStopwatch;
  LPort: Integer;
begin
  LSrvEvents := TServerEvents.Create;
  LEvents1 := TComponentEvents.Create;
  LEvents2 := TComponentEvents.Create;
  LServer := TTgWebhookServer.Create(nil);
  try
    Check((LServer.Port = 8080) and (LServer.BindAddress = '127.0.0.1') and
      (LServer.MaxBodySize = 1024 * 1024) and (LServer.MaxConnections = 0) and
      not LServer.Active and (LServer.BoundPort = 0) and (LServer.BotCount = 0),
      'значения по умолчанию');
    CheckEquals('', LServer.GetWebhookUrl('/tg/x'), 'PublicUrl пуст → GetWebhookUrl пуст');
    LServer.PublicUrl := 'https://bots.example.com/';
    CheckEquals('https://bots.example.com/tg/x', LServer.GetWebhookUrl('/tg/x'),
      'GetWebhookUrl = PublicUrl (без /) + путь');
    CheckEquals('https://bots.example.com/tg/y', LServer.GetWebhookUrl('tg/y'), 'путь без / — добавлен');
    Check(Raises(
      procedure
      begin
        LServer.Port := 70000;
      end, ETgError), 'Port вне 0–65535 → ETgError');
    Check(Raises(
      procedure
      begin
        LServer.MaxBodySize := 0;
      end, ETgError), 'MaxBodySize = 0 → ETgError');
    // Порт выбирает ОС: параллельные прогоны не конфликтуют.
    LServer.Port := 0;
    LServer.OnRequest := LSrvEvents.DoRequest;
    LServer.OnError := LSrvEvents.DoError;
    LServer.Active := True;
    Check(LServer.Active and (LServer.BoundPort > 0), 'Active, BoundPort — порт ОС');
    Check(Raises(
      procedure
      begin
        LServer.Port := 1234;
      end, ETgError), 'Port при работе → ETgError');
    LPort := LServer.BoundPort;
    LBase := 'http://127.0.0.1:' + IntToStr(LPort);
    LBot2 := nil;
    LBot1 := TTelegramBot.Create(nil);
    try
      LBot2 := TTelegramBot.Create(nil);
      LBot1.Name := 'Bot1';
      LBot2.Name := 'Bot2';
      LTransport1 := TScriptCancellableTransport.Create(WebhookScript(False));
      LRef1 := LTransport1;
      LTransport2 := TScriptCancellableTransport.Create(WebhookScript(False));
      LRef2 := LTransport2;
      LBot1.Transport := LRef1;
      LBot2.Transport := LRef2;
      LBot1.Delivery := TTgDelivery.Worker;
      LBot2.Delivery := TTgDelivery.Worker;
      LBot1.Mode := TTgReceiveMode.Webhook;
      LBot2.Mode := TTgReceiveMode.Webhook;
      LBot1.Webhook.SecretToken := CSecret1;
      LBot2.Webhook.SecretToken := CSecret2;
      LBot1.Webhook.Server := LServer;
      LBot2.Webhook.Server := LServer;
      LBot1.OnMessage := LEvents1.DoMessage;
      LBot2.OnMessage := LEvents2.DoMessage;
      LBot1.Active := True;
      LBot2.Active := True;
      CheckEquals(2, LServer.BotCount, 'два бота на одном сервере');
      Check(WaitSetWebhook(LTransport1, 1) and WaitSetWebhook(LTransport2, 1), 'setWebhook обоих ботов');
      CheckEquals('https://bots.example.com/tg/Bot1', SetWebhookParam(LTransport1, 0, 'url'),
        'url setWebhook = PublicUrl + Path');
      LWatch := TStopwatch.StartNew;
      CheckEquals(200, HttpStatus('POST', LBase + '/tg/Bot1', MsgUpdate(1, 100, 7, 'one'), CSecret1),
        'POST боту 1 с верным секретом → 200');
      GServerPostMs := LWatch.ElapsedMilliseconds;
      CheckEquals(200, HttpStatus('POST', LBase + '/tg/Bot2', MsgUpdate(1, 200, 7, 'two'), CSecret2),
        'POST боту 2 → 200');
      CheckEquals(403, HttpStatus('POST', LBase + '/tg/Bot1', MsgUpdate(2, 100, 7, 'x'), CSecret2),
        'чужой секрет → 403');
      CheckEquals(403, HttpStatus('POST', LBase + '/tg/Bot1', MsgUpdate(2, 100, 7, 'x'), ''),
        'без секрета → 403');
      CheckEquals(400, HttpStatus('POST', LBase + '/tg/Bot1', 'not json', CSecret1), 'не JSON → 400');
      CheckEquals(404, HttpStatus('POST', LBase + '/tg/Unknown', MsgUpdate(2, 100, 7, 'x'), CSecret1),
        'неизвестный путь → 404');
      CheckEquals(404, HttpStatus('POST', LBase + '/tg/bot1', MsgUpdate(2, 100, 7, 'x'), CSecret1),
        'путь сравнивается с учётом регистра → 404');
      CheckEquals(200, HttpStatus('POST', LBase + '/tg/Bot1?a=1', MsgUpdate(3, 100, 7, 'q'), CSecret1),
        'query не мешает → 200');
      CheckEquals(405, HttpStatus('GET', LBase + '/tg/Bot1', '', ''), 'GET → 405');
      Check(WaitUntil(
        function: Boolean
        begin
          Result := LEvents1.Log.Has('msg one') and LEvents1.Log.Has('msg q') and
            LEvents2.Log.Has('msg two');
        end, 5000), 'обработчики ботов вызваны');
      Check(not LEvents1.Log.Has('msg two') and not LEvents2.Log.Has('msg one') and
        not LEvents1.Log.Has('msg x'), 'обновления не перепутаны, отклонённые не обработаны');
      Check(LSrvEvents.Log.Has('POST /tg/Bot1 200') and LSrvEvents.Log.Has('POST /tg/Bot1 403') and
        LSrvEvents.Log.Has('GET /tg/Bot1 405') and LSrvEvents.Log.Has(' /tg/Unknown 404'),
        'OnRequest: метод, путь, код');
      Check((Pos(CSecret1, LSrvEvents.Log.Text) = 0) and (Pos(CSecret2, LSrvEvents.Log.Text) = 0) and
        not LSrvEvents.Log.Has('error'), 'журнал без секретов и ошибок');
      // Лимит тела: отказ до чтения (тело не отправляется вовсе — ответ без ожидания).
      LServer.MaxBodySize := 1000;
      LWatch := TStopwatch.StartNew;
      CheckEquals(413, RawHttpStatus(LPort, 'POST /tg/Bot1 HTTP/1.1'#13#10'Host: x'#13#10 +
        'Content-Length: 50000000'#13#10#13#10, ''), 'Content-Length > MaxBodySize → 413');
      GServer413Ms := LWatch.ElapsedMilliseconds;
      Check(GServer413Ms < 3000, '413 сразу, тело не читается');
      CheckEquals(413, RawHttpStatus(LPort, 'POST /tg/Bot1 HTTP/1.1'#13#10'Host: x'#13#10 +
        'Transfer-Encoding: chunked'#13#10#13#10'FA0'#13#10, StringOfChar('a', 4000)),
        'chunked больше MaxBodySize → 413');
      CheckEquals(404, RawHttpStatus(LPort, 'POST /nope HTTP/1.1'#13#10'Host: x'#13#10 +
        'Content-Length: 50000000'#13#10#13#10, ''), 'неизвестный путь → 404 до чтения тела');
      LServer.MaxBodySize := TgWebhookDefaultMaxBodySize;
      CheckEquals(200, HttpStatus('POST', LBase + '/tg/Bot1', MsgUpdate(4, 100, 7, 'after'), CSecret1),
        'после отказов сервер работает');
      // Путь занят другим ботом: запуск отклонён, регистрации не тронуты.
      LBot3 := TTelegramBot.Create(nil);
      try
        LBot3.Name := 'Bot3';
        LRef3 := TScriptCancellableTransport.Create(WebhookScript(False));
        LBot3.Transport := LRef3;
        LBot3.Mode := TTgReceiveMode.Webhook;
        LBot3.Webhook.Path := '/tg/Bot1';
        LBot3.Webhook.Server := LServer;
        Check(Raises(
          procedure
          begin
            LBot3.Active := True;
          end, ETgError), 'путь занят другим ботом → ETgError');
        Check(not LBot3.Active, 'бот с занятым путём не запущен');
      finally
        LBot3.Free;
      end;
      CheckEquals(2, LServer.BotCount, 'регистрации прежних ботов не тронуты');
      // Остановка и уничтожение бота снимают путь.
      LBot2.Active := False;
      CheckEquals(1, LServer.BotCount, 'Active := False бота снимает путь');
      CheckEquals(404, HttpStatus('POST', LBase + '/tg/Bot2', MsgUpdate(5, 200, 7, 'x'), CSecret2),
        'остановленный бот → 404');
      LBot2.Active := True;
      CheckEquals(2, LServer.BotCount, 'повторный запуск регистрирует снова');
      FreeAndNil(LBot2);
      CheckEquals(1, LServer.BotCount, 'Free работающего бота снимает путь');
      CheckEquals(404, HttpStatus('POST', LBase + '/tg/Bot2', MsgUpdate(6, 200, 7, 'x'), CSecret2),
        'уничтоженный бот → 404');
      // Занятый порт.
      LServer2 := TTgWebhookServer.Create(nil);
      try
        LServer2.Port := LPort;
        Check(Raises(
          procedure
          begin
            LServer2.Active := True;
          end, ETgError), 'занятый порт → ETgError');
        Check(not LServer2.Active and (LServer2.BoundPort = 0), 'после ошибки сервер не активен');
        LServer2.Port := 0;
        LServer2.Active := True;
        Check(LServer2.Active and (LServer2.BoundPort <> LPort), 'второй сервер на другом порту');
        LServer2.Active := False;
        Check(not LServer2.Active and (LServer2.BoundPort = 0), 'Active := False');
      finally
        LServer2.Free;
      end;
      // Free сервера с зарегистрированным работающим ботом.
      FreeAndNil(LServer);
      Check(LBot1.Webhook.Server = nil, 'Free сервера → Webhook.Server = nil');
      Check(LBot1.Active, 'бот продолжает работать без сервера');
      Check(LBot1.HandleWebhook(MsgUpdate(7, 100, 7, 'direct'), CSecret1) = TTgWebhookResult.Accepted,
        'HandleWebhook напрямую работает');
      LBot1.Active := False;
      Check(not LBot1.Active, 'остановка бота после Free сервера');
    finally
      LBot2.Free;
      LBot1.Free;
    end;
  finally
    LServer.Free;
    LEvents2.Free;
    LEvents1.Free;
    LSrvEvents.Free;
  end;
end;

{ Тесты 6E2: доработки API по итогам демо }

var
  // Замеры 6E2.
  GCompRunStopMs: Int64 = -1;
  GCompRunFaultMs: Int64 = -1;
  GCompRunWorkerStopMs: Int64 = -1;

procedure TestEscapeHelpers;
begin
  CheckEquals('', TgHtmlEscape(''), 'HTML: пусто');
  CheckEquals('a &amp; b &lt;i&gt;&quot;q&quot;&lt;/i&gt; ''x''', TgHtmlEscape('a & b <i>"q"</i> ''x'''),
    'HTML: & < > "');
  CheckEquals('Привет, мир 👋', TgHtmlEscape('Привет, мир 👋'), 'HTML: кириллица и эмодзи без изменений');
  CheckEquals('&amp;amp;', TgHtmlEscape('&amp;'), 'HTML: уже экранированное экранируется ещё раз');
  CheckEquals('', TgMarkdownV2Escape(''), 'MarkdownV2: пусто');
  CheckEquals('\_\*\[\]\(\)\~\`\>\#\+\-\=\|\{\}\.\!\\', TgMarkdownV2Escape('_*[]()~`>#+-=|{}.!\'),
    'MarkdownV2: все спецсимволы и обратная косая');
  CheckEquals('Цена 1\.5 руб\. \(скидка \-10%\)\!', TgMarkdownV2Escape('Цена 1.5 руб. (скидка -10%)!'),
    'MarkdownV2: обычный текст');
  CheckEquals('abc 123 Яё @ $ % ^ & ; : , / ? < "', TgMarkdownV2Escape('abc 123 Яё @ $ % ^ & ; : , / ? < "'),
    'MarkdownV2: прочие символы без изменений');
end;

procedure TestComponentRun;
var
  LEvents: TComponentEvents;
  LBot: TTelegramBot;
  LScript: TFaultScriptState;
  LTransportRef: ITgTransport;
  LWatch: TStopwatch;
  LStopAt, LEnd: Int64;
  LResult: Boolean;
  LError: string;
  LThread: TThread;
begin
  LEvents := TComponentEvents.Create;
  LScript := TFaultScriptState.Create;
  try
    // 1) Delivery = Main: RequestStop из другого потока завершает Run < 1 с, True.
    LScript.Arm(1, 1);
    LTransportRef := TScriptCancellableTransport.Create(FaultScript(LScript));
    LBot := TTelegramBot.Create(nil);
    try
      LBot.Transport := LTransportRef;
      LBot.OnStart := LEvents.DoStart;
      LBot.OnStop := LEvents.DoStop;
      LBot.OnMessage := LEvents.DoMessage;
      LBot.OnFault := LEvents.DoFault;
      LStopAt := -1;
      LWatch := TStopwatch.StartNew;
      LThread := TThread.CreateAnonymousThread(
        procedure
        begin
          TThread.Sleep(400);
          LStopAt := LWatch.ElapsedMilliseconds;
          LBot.RequestStop;
        end);
      LThread.FreeOnTerminate := False;
      LThread.Start;
      try
        LResult := LBot.Run;
        LEnd := LWatch.ElapsedMilliseconds;
      finally
        // Поток обращается к LBot: освобождать компонент — после его завершения.
        LThread.WaitFor;
        LThread.Free;
      end;
      GCompRunStopMs := LEnd - LStopAt;
      Check(LResult, 'Run = True: остановлен по RequestStop');
      Check((LStopAt > 0) and (GCompRunStopMs >= 0) and (GCompRunStopMs < 1000),
        Format('Run завершился < 1 с после RequestStop (%d мс)', [GCompRunStopMs]));
      Check(LEvents.Log.Has('msg m1'), 'Delivery = Main: обновление обработано внутри Run');
      Check(LEvents.Log.Has('start') and LEvents.Log.Has('stop requested'), 'OnStart и OnStop(Requested)');
      CheckEquals(0, LEvents.NotMain, 'события — в главном потоке');
      Check(not LBot.Active and not Assigned(LBot.Bot), 'после Run бот остановлен и освобождён');
      // Delivery = Main не из главного потока — ETgError, бот не запускается.
      LError := '';
      LThread := TThread.CreateAnonymousThread(
        procedure
        begin
          try
            LBot.Run;
          except
            on E: ETgError do
              LError := E.ClassName;
          end;
        end);
      LThread.FreeOnTerminate := False;
      LThread.Start;
      LThread.WaitFor;
      LThread.Free;
      CheckEquals('ETgError', LError, 'Run (Main) не из главного потока → ETgError');
      Check(not Assigned(LBot.Bot), 'после ошибки Run бот не создан');
    finally
      LBot.Free;
    end;
    // 2) Delivery = Main, отказ (401): Run = False, OnFault и OnStop(Fault) по одному разу.
    LEvents.Log.Clear;
    LScript.Arm(0, 0);
    LTransportRef := TScriptCancellableTransport.Create(FaultScript(LScript));
    LBot := TTelegramBot.Create(nil);
    try
      LBot.Transport := LTransportRef;
      LBot.OnStop := LEvents.DoStop;
      LBot.OnFault := LEvents.DoFault;
      LBot.OnError := LEvents.DoError;
      LWatch := TStopwatch.StartNew;
      LResult := LBot.Run;
      GCompRunFaultMs := LWatch.ElapsedMilliseconds;
      Check(not LResult, 'Main, 401: Run = False');
      Check(GCompRunFaultMs < 3000, Format('Run при отказе завершился быстро (%d мс)', [GCompRunFaultMs]));
      CheckEquals(1, LEvents.Log.CountOf('fault 401'), 'Main: OnFault один раз');
      CheckEquals(1, LEvents.Log.CountOf('stop fault'), 'Main: OnStop(Fault) один раз');
      CheckEquals(0, LEvents.Log.CountOf('stop requested'), 'Main: без OnStop(Requested)');
      CheckEquals(1, LEvents.Log.CountOf('err ETgApiError 401 ctx=False'), 'Main: OnError один раз');
      Check(not Assigned(LBot.Bot), 'Main: бот освобождён');
      // 3) Delivery = Worker, отказ: Run = False, отказавший бот освобождается без OnStop(Requested).
      LEvents.Log.Clear;
      LBot.Delivery := TTgDelivery.Worker;
      LResult := LBot.Run;
      Check(not LResult, 'Worker, 401: Run = False');
      CheckEquals(1, LEvents.Log.CountOf('fault 401'), 'Worker: OnFault один раз');
      CheckEquals(1, LEvents.Log.CountOf('stop fault'), 'Worker: OnStop(Fault) один раз');
      CheckEquals(0, LEvents.Log.CountOf('stop requested'), 'Worker: без OnStop(Requested)');
      Check(not Assigned(LBot.Bot), 'Worker: отказавший бот освобождён Run');
      // 4) Delivery = Worker, Run в фоновом потоке, RequestStop из главного: True < 1 с.
      LEvents.Log.Clear;
      LScript.Arm(1, 0);
      LResult := False;
      LThread := TThread.CreateAnonymousThread(
        procedure
        begin
          LResult := LBot.Run;
        end);
      LThread.FreeOnTerminate := False;
      LThread.Start;
      Check(WaitUntil(
        function: Boolean
        begin
          Result := LBot.Active;
        end, 3000), 'Worker: Run в фоновом потоке запустил бота');
      LWatch := TStopwatch.StartNew;
      LBot.RequestStop;
      LThread.WaitFor;
      GCompRunWorkerStopMs := LWatch.ElapsedMilliseconds;
      LThread.Free;
      Check(LResult, 'Worker: Run = True по RequestStop');
      Check(GCompRunWorkerStopMs < 1000, Format('Worker: Run завершился < 1 с (%d мс)', [GCompRunWorkerStopMs]));
      CheckEquals(1, LEvents.Log.CountOf('stop requested'), 'Worker: OnStop(Requested)');
    finally
      LBot.Free;
    end;
  finally
    LScript.Free;
    LEvents.Free;
  end;
end;

procedure TestWebhookUrlAndPathChecks;
var
  LServer: TTestWebhookServer;
  LBot: TTelegramBot;
  LTgBot: TTgBot;
  LIndy: TTgWebhookServer;
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LSettings: TTgHttpSettings;
  LError: string;
begin
  // П.3: Webhook.Server задан, Name и Path пусты — понятная ETgError, а не путь '/tg/'.
  LServer := TTestWebhookServer.Create(nil);
  try
    LBot := TTelegramBot.Create(nil);
    try
      LTransportRef := TScriptCancellableTransport.Create(WebhookScript(False));
      LBot.Transport := LTransportRef;
      LBot.Delivery := TTgDelivery.Worker;
      LBot.Mode := TTgReceiveMode.Webhook;
      LBot.Webhook.Server := LServer;
      LError := '';
      try
        LBot.Active := True;
      except
        on E: ETgError do
          LError := E.Message;
      end;
      Check(Contains('Webhook.Path', LError) and Contains('Name', LError),
        'Server задан, Name и Path пусты → ETgError «задайте Name или Webhook.Path»: ' + LError);
      CheckEquals(0, LServer.Log.CountOf('reg /tg/'), 'путь /tg/ не регистрируется');
      Check(not LBot.Active and not Assigned(LBot.Bot), 'бот не запущен');
      LBot.Webhook.Path := '/hook';
      LBot.Active := True;
      Check(LServer.Log.Has('reg /hook'), 'Path задан — бот запущен и зарегистрирован');
      LBot.Active := False;
      // Без Server путь не используется: Name пуст, Url задан — запуск.
      LBot.Webhook.Server := nil;
      LBot.Webhook.Path := '';
      LBot.Webhook.Url := 'https://example.org/hook';
      LBot.Active := True;
      Check(LBot.Active, 'без Server Name и Path не требуются');
      LBot.Active := False;
      // П.7: http:// в Url — ETgError при запуске (облачный Bot API).
      LBot.Webhook.Url := 'http://example.org/hook';
      Check(Raises(
        procedure
        begin
          LBot.Active := True;
        end, ETgError), 'компонент: Webhook.Url http:// → ETgError');
      Check(not LBot.Active, 'после ошибки бот не запущен');
    finally
      LBot.Free;
    end;
  finally
    LServer.Free;
  end;
  // П.7: TTgBot.WebhookUrl — только https (регистр не важен).
  LTransport := TScriptCancellableTransport.Create(WebhookScript(False));
  LTransportRef := LTransport;
  LTgBot := TTgBot.Create(LTransportRef);
  try
    LTgBot.Mode := TTgReceiveMode.Webhook;
    LTgBot.WebhookUrl := 'http://example.org/hook';
    Check(Raises(
      procedure
      begin
        LTgBot.Start;
      end, ETgError), 'TTgBot: http:// → ETgError');
    LTgBot.WebhookUrl := 'example.org/hook';
    Check(Raises(
      procedure
      begin
        LTgBot.Start;
      end, ETgError), 'TTgBot: без схемы → ETgError');
    CheckEquals(0, LTransport.Count('setWebhook'), 'ошибки проверки — без запросов');
    LTgBot.WebhookUrl := 'HTTPS://Example.org/hook';
    LTgBot.Start;
    Check(LTgBot.State = TTgBotState.Running, 'TTgBot: HTTPS:// (регистр) — запуск');
    Check(LTgBot.Stop, 'Stop');
  finally
    LTgBot.Free;
  end;
  // Local Bot API server (адрес Bot API не облачный): http:// допускается.
  LSettings := TTgHttpSettings.Create('123:abc');
  LSettings.ApiUrl := 'http://127.0.0.1:8081';
  LTransportRef := TStubHttpTransport.Create(LSettings,
    function(const AMethod: string): TTgHttpResponse
    begin
      Result := StubResponse(200, '{"ok":true,"result":true}');
    end);
  LTgBot := TTgBot.Create(LTransportRef);
  try
    LTgBot.Mode := TTgReceiveMode.Webhook;
    LTgBot.WebhookUrl := 'http://127.0.0.1:8443/hook';
    LTgBot.Start;
    Check(LTgBot.State = TTgBotState.Running, 'Local Bot API server: http:// допускается');
    Check(LTgBot.Stop, 'Stop (Local Bot API)');
  finally
    LTgBot.Free;
  end;
  // П.7: TTgWebhookServer.PublicUrl — только https, проверка до открытия порта.
  LIndy := TTgWebhookServer.Create(nil);
  try
    LIndy.Port := 0;
    LIndy.PublicUrl := 'http://bots.example.com';
    LError := '';
    try
      LIndy.Active := True;
    except
      on E: ETgError do
        LError := E.Message;
    end;
    Check(Contains('https://', LError), 'PublicUrl http:// → ETgError: ' + LError);
    Check(not LIndy.Active, 'сервер не запущен');
    LIndy.PublicUrl := 'HTTPS://bots.example.com';
    LIndy.Active := True;
    Check(LIndy.Active and (LIndy.BoundPort > 0), 'PublicUrl HTTPS:// — запуск');
    LIndy.Active := False;
    LIndy.PublicUrl := '';
    LIndy.Active := True;
    Check(LIndy.Active, 'пустой PublicUrl — запуск');
    LIndy.Active := False;
  finally
    LIndy.Free;
  end;
  // П.9: классы зарегистрированы для потоковой загрузки без объявленного поля.
  Check(GetClass('TTelegramBot') = TTelegramBot, 'RegisterClasses: TTelegramBot');
  Check(GetClass('TTgWebhookServer') = TTgWebhookServer, 'RegisterClasses: TTgWebhookServer');
end;

/// <summary>
///   Транспорт: getMe — ошибка AGetMeCode через AGetMeDelayMs мс,
///   setMyCommands — 400, getUpdates и setWebhook — 401, deleteWebhook — True.
/// </summary>
function StartJobScript(AGetMeCode, AGetMeDelayMs: Integer): TFakeHandler;
begin
  Result :=
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    begin
      if AMethod = 'getMe' then
      begin
        if AGetMeDelayMs > 0 then
          TThread.Sleep(AGetMeDelayMs);
        raise ETgApiError.Create('getMe', AGetMeCode, 'Error');
      end;
      if AMethod = 'setMyCommands' then
        raise ETgApiError.Create('setMyCommands', 400, 'Bad Request: invalid command');
      if (AMethod = 'getUpdates') or (AMethod = 'setWebhook') then
        raise ETgApiError.Create(AMethod, 401, 'Unauthorized');
      Result := TJSONTrue.Create;
    end;
end;

/// <summary>
///   TTgBot с командой (getMe и setMyCommands в фоне) и транспортом
///   StartJobScript: ждёт отказа и ещё ≈AQuietMs. Журнал: 'error <код>', 'fault <код>'.
/// </summary>
procedure RunStartJobFault(AMode: TTgReceiveMode; AGetMeCode, AGetMeDelayMs, AQuietMs: Integer;
  ALog: TTextLog; out ASetMyCommands: Integer);
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
begin
  LTransport := TScriptCancellableTransport.Create(StartJobScript(AGetMeCode, AGetMeDelayMs));
  LTransportRef := LTransport;
  LBot := TTgBot.Create(LTransportRef);
  try
    LBot.Mode := AMode;
    LBot.WebhookUrl := 'https://example.org/hook';
    LBot.Command('start', 'Запуск',
      procedure(ACtx: ITgContext)
      begin
      end);
    LBot.OnError :=
      procedure(AError: Exception; ACtx: ITgContext)
      begin
        ALog.Add(Format('error %d', [ApiCode(AError)]));
      end;
    LBot.OnFault :=
      procedure(AError: Exception)
      begin
        ALog.Add(Format('fault %d', [ApiCode(AError)]));
      end;
    LBot.Start;
    Check(WaitLogHas(ALog, 'fault 401'), 'отказ (401) доставлен');
    TThread.Sleep(AQuietMs);
    Check(LBot.State = TTgBotState.Faulted, 'State = Faulted');
    LBot.Stop;
    ASetMyCommands := LTransport.Count('setMyCommands');
  finally
    LBot.Free;
  end;
end;

procedure TestStartJobAfterFault;
var
  LLog: TTextLog;
  LMenu: Integer;
begin
  LLog := TTextLog.Create;
  try
    // getMe и getUpdates — 401: ровно один OnError и один OnFault (о токене сообщает отказ).
    RunStartJobFault(TTgReceiveMode.Polling, 401, 0, 300, LLog, LMenu);
    CheckEquals(1, LLog.CountOf('error 401'), 'polling, 401: OnError ровно один: ' + LLog.Text);
    CheckEquals(1, LLog.CountOf('fault 401'), 'polling, 401: OnFault ровно один');
    CheckEquals(2, LLog.Count, 'polling, 401: других событий нет: ' + LLog.Text);
    CheckEquals(0, LMenu, 'polling, 401: setMyCommands после 401 getMe не вызывается');
    // Webhook: setWebhook и getMe — 401.
    LLog.Clear;
    RunStartJobFault(TTgReceiveMode.Webhook, 401, 0, 300, LLog, LMenu);
    CheckEquals(1, LLog.CountOf('error 401'), 'webhook, 401: OnError ровно один: ' + LLog.Text);
    CheckEquals(1, LLog.CountOf('fault 401'), 'webhook, 401: OnFault ровно один');
    CheckEquals(2, LLog.Count, 'webhook, 401: других событий нет: ' + LLog.Text);
    CheckEquals(0, LMenu, 'webhook, 401: setMyCommands не вызывается');
    // getMe отвечает 502 уже после отказа: ошибка не сообщается, меню не отправляется.
    LLog.Clear;
    RunStartJobFault(TTgReceiveMode.Polling, 502, 400, 700, LLog, LMenu);
    CheckEquals(0, LLog.CountOf('error 502'), 'ошибка getMe после Faulted не сообщается: ' + LLog.Text);
    CheckEquals(2, LLog.Count, 'после Faulted только первичный отказ: ' + LLog.Text);
    CheckEquals(0, LMenu, 'после Faulted setMyCommands не вызывается');
  finally
    LLog.Free;
  end;
end;

{ Владение, фаза 2: фоновая подготовка запуска (ITgStartJob) }

var
  // Замеры OWN2, мс.
  GOwnFreeCancellableMs: Int64 = -1;
  GOwnFreePlainMs: Int64 = -1;
  GOwnChurnMs: Int64 = -1;
  // Замеры FREEWAIT, мс.
  GFreeWaitStopMs: Int64 = -1;
  GFreeWaitCompMs: Int64 = -1;

/// <summary>
///   Живые ядра ботов (хук TGBOT_TESTHOOKS модуля TgBot.Bot.Core); без
///   хуков -1.
/// </summary>
function LiveBotCores: Integer;
begin
{$IFDEF TGBOT_TESTHOOKS}
  Result := TgTestLiveBotCores;
{$ELSE}
  Result := -1;
{$ENDIF}
end;

/// <summary>Живые задачи фоновой подготовки (хук TGBOT_TESTHOOKS); без хуков -1.</summary>
function LiveStartJobs: Integer;
begin
{$IFDEF TGBOT_TESTHOOKS}
  Result := TgTestLiveStartJobs;
{$ELSE}
  Result := -1;
{$ENDIF}
end;

/// <summary>
///   Ждёт, пока живых ядер и задач подготовки станет не больше ACores и
///   AJobs (обычно — значений до теста). Без хуков — сразу True.
/// </summary>
function WaitLiveAtMost(ACores, AJobs, ATimeoutMs: Integer): Boolean;
begin
{$IFDEF TGBOT_TESTHOOKS}
  Result := WaitUntil(
    function: Boolean
    begin
      Result := (TgTestLiveBotCores <= ACores) and (TgTestLiveStartJobs <= AJobs);
    end, ATimeoutMs);
{$ELSE}
  Result := True;
{$ENDIF}
end;

/// <summary>Ответ getMe с username AName.</summary>
function BotUserJson(const AName: string): TJSONValue;
begin
  Result := JsonOf('{"id":42,"is_bot":true,"first_name":"B","username":"' + AName + '"}');
end;

/// <summary>getMe, висящий до отмены окружающего токена (не дольше 30 с), затем — @AName.</summary>
function HangGetMe(const AName: string): TJSONValue;
var
  LToken: ITgCancellation;
begin
  LToken := TTgCancelScope.Current;
  if Assigned(LToken) then
  begin
    LToken.WaitFor(30000);
    LToken.ThrowIfCancelled;
  end;
  Result := BotUserJson(AName);
end;

/// <summary>getUpdates без обновлений: итоговое подтверждение (timeout = 0) — пусто, приём висит до отмены.</summary>
function IdleUpdates(AParams: TTgParams): TJSONValue;
begin
  if TTgJson.GetInt(AParams.Json, 'timeout') = 0 then
    Exit(TJSONArray.Create);
  Result := HangUntilCancelled;
end;

/// <summary>
///   TTgBot с командой (getMe и меню — в фоне), getMe висит: ACancellable —
///   транспорт с токенами, getMe ждёт отмены; иначе — транспорт без токенов,
///   getMe ждёт события (неотменяемо) и отпускается после Free. Free без
///   Stop: ждёт задачу TgDefaultBotFreeStartJobWaitMs (не бюджет Stop),
///   затем отменяет её; Stop внутри Free снятую задачу уже не ждёт.
/// </summary>
procedure RunFreeWithHangingGetMe(ACancellable: Boolean; out AFreeMs: Int64);
var
  LTransport: TScriptTransport;
  LTransportRef: ITgTransport;
  LHandler: TFakeHandler;
  LBot: TTgBot;
  LGate: TEvent;
  LErrors: TTextLog;
  LEntered, LBaseCores, LBaseJobs: Integer;
  LWatch: TStopwatch;
  LReleased: Boolean;
  LWhat: string;
begin
  if ACancellable then
    LWhat := 'отменяемый транспорт'
  else
    LWhat := 'неотменяемый транспорт';
  LBaseCores := LiveBotCores;
  LBaseJobs := LiveStartJobs;
  LEntered := 0;
  LReleased := False;
  AFreeMs := -1;
  LGate := TEvent.Create(nil, True, False, '');
  LErrors := TTextLog.Create;
  try
    LHandler :=
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      begin
        if AMethod = 'getUpdates' then
          Exit(IdleUpdates(AParams));
        if AMethod = 'getMe' then
        begin
          TInterlocked.Increment(LEntered);
          if ACancellable then
            Exit(HangGetMe('LateBot'));
          LGate.WaitFor(30000);
          Exit(BotUserJson('LateBot'));
        end;
        Result := TJSONTrue.Create;
      end;
    if ACancellable then
      LTransport := TScriptCancellableTransport.Create(LHandler)
    else
      LTransport := TScriptTransport.Create(LHandler);
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      LBot.Command('start', 'Запуск',
        procedure(ACtx: ITgContext)
        begin
        end);
      LBot.OnError :=
        procedure(AError: Exception; ACtx: ITgContext)
        begin
          LErrors.Add(AError.ClassName + ': ' + AError.Message);
        end;
      LBot.Start;
      Check(WaitUntil(
        function: Boolean
        begin
          Result := TInterlocked.CompareExchange(LEntered, 0, 0) > 0;
        end, 5000), LWhat + ': getMe фоновой подготовки начат');
    finally
      LWatch := TStopwatch.StartNew;
      LBot.Free;
      AFreeMs := LWatch.ElapsedMilliseconds;
    end;
    Check(AFreeMs < TgDefaultBotFreeStartJobWaitMs + 1000,
      Format('%s: Free при висящем getMe — короткое ожидание подготовки, не бюджет Stop (%d мс)',
      [LWhat, AFreeMs]));
    Check(AFreeMs >= TgDefaultBotFreeStartJobWaitMs - 100,
      Format('%s: Free сначала ждал подготовку ≈%d мс (%d мс)',
      [LWhat, TgDefaultBotFreeStartJobWaitMs, AFreeMs]));
    if not ACancellable then
    begin
      // Задача отпущена (Stop = False): замыкание пула держит ядро, ядро —
      // задачу; бот уже освобождён.
      Check(LTransport.RefCount > 1, LWhat + ': пока getMe висит, ядро (клиент) живо');
{$IFDEF TGBOT_TESTHOOKS}
      Check(TgTestLiveBotCores > LBaseCores, LWhat + ': ядро живо до завершения задачи (счётчик)');
      Check(TgTestLiveStartJobs > LBaseJobs, LWhat + ': задача жива до завершения (счётчик)');
{$ENDIF}
      LGate.SetEvent;
    end;
    LReleased := WaitTransportReleased(LTransport, 5000);
    Check(LReleased, LWhat + ': ядро и клиент освобождены (неотменяемый — в потоке пула)');
    Check(WaitLiveAtMost(LBaseCores, LBaseJobs, 5000),
      LWhat + ': живых ядер и задач подготовки — как до теста');
    CheckEquals(0, LTransport.Count('setMyCommands'), LWhat + ': меню отменённой задачи не отправлялось');
    CheckEquals(0, LErrors.Count, LWhat + ': OnError не вызывался: ' + LErrors.Text);
  finally
    LGate.SetEvent;
    LErrors.Free;
    // Не дождались освобождения — событие может быть ещё нужно транспорту.
    if LReleased then
      LGate.Free;
  end;
end;

procedure TestStartJobFreeHangingGetMe;
begin
  RunFreeWithHangingGetMe(True, GOwnFreeCancellableMs);
  RunFreeWithHangingGetMe(False, GOwnFreePlainMs);
end;

/// <summary>
///   Явный Stop(300) при висящем getMe (отменяемый транспорт): ждёт
///   подготовку в пределах переданного бюджета (≈300 мс, а не
///   TgDefaultBotFreeStartJobWaitMs Free), затем отменяет её.
/// </summary>
procedure TestStartJobStopBudget;
const
  CWaitMs = 300;
var
  LTransport: TScriptTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LErrors: TTextLog;
  LEntered, LBaseCores, LBaseJobs: Integer;
  LWatch: TStopwatch;
  LStopped: Boolean;
begin
  LBaseCores := LiveBotCores;
  LBaseJobs := LiveStartJobs;
  LEntered := 0;
  LErrors := TTextLog.Create;
  try
    LTransport := TScriptCancellableTransport.Create(
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      begin
        if AMethod = 'getUpdates' then
          Exit(IdleUpdates(AParams));
        if AMethod = 'getMe' then
        begin
          TInterlocked.Increment(LEntered);
          Exit(HangGetMe('LateBot'));
        end;
        Result := TJSONTrue.Create;
      end);
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      LBot.Command('start', 'Запуск',
        procedure(ACtx: ITgContext)
        begin
        end);
      LBot.OnError :=
        procedure(AError: Exception; ACtx: ITgContext)
        begin
          LErrors.Add(AError.ClassName + ': ' + AError.Message);
        end;
      LBot.Start;
      Check(WaitUntil(
        function: Boolean
        begin
          Result := TInterlocked.CompareExchange(LEntered, 0, 0) > 0;
        end, 5000), 'getMe фоновой подготовки начат');
      LWatch := TStopwatch.StartNew;
      LStopped := LBot.Stop(CWaitMs);
      GFreeWaitStopMs := LWatch.ElapsedMilliseconds;
      Check(GFreeWaitStopMs >= CWaitMs - 50,
        Format('Stop(%d) ждал подготовку весь бюджет (%d мс, Stop = %s)',
        [CWaitMs, GFreeWaitStopMs, BoolToStr(LStopped, True)]));
      Check(GFreeWaitStopMs < CWaitMs + 1000,
        Format('Stop(%d) уложился в свой бюджет (%d мс)', [CWaitMs, GFreeWaitStopMs]));
      CheckEquals('Idle', BotStateName(LBot.State), 'после Stop — Idle');
    finally
      LBot.Free;
    end;
    Check(WaitTransportReleased(LTransport, 5000), 'ядро и клиент освобождены');
    Check(WaitLiveAtMost(LBaseCores, LBaseJobs, 5000), 'живых ядер и задач подготовки — как до теста');
    CheckEquals(0, LTransport.Count('setMyCommands'), 'меню отменённой задачи не отправлялось');
    CheckEquals(0, LErrors.Count, 'OnError не вызывался: ' + LErrors.Text);
  finally
    LErrors.Free;
  end;
end;

/// <summary>
///   TTelegramBot (без формы) с командой: Free при висящем getMe фоновой
///   подготовки (отменяемый транспорт) — не дольше
///   TgDefaultBotFreeStartJobWaitMs + 1 с (закрытие формы без фриза).
/// </summary>
procedure TestComponentFreeHangingGetMe;
var
  LEvents: TComponentEvents;
  LBot: TTelegramBot;
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LEntered, LBaseCores, LBaseJobs: Integer;
  LWatch: TStopwatch;
begin
  LBaseCores := LiveBotCores;
  LBaseJobs := LiveStartJobs;
  LEntered := 0;
  LEvents := TComponentEvents.Create;
  try
    LTransport := TScriptCancellableTransport.Create(
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      begin
        if AMethod = 'getUpdates' then
          Exit(IdleUpdates(AParams));
        if AMethod = 'getMe' then
        begin
          TInterlocked.Increment(LEntered);
          Exit(HangGetMe('LateBot'));
        end;
        Result := TJSONTrue.Create;
      end);
    LTransportRef := LTransport;
    LBot := TTelegramBot.Create(nil);
    try
      LBot.Transport := LTransportRef;
      LBot.OnError := LEvents.DoError;
      LBot.Command('start', 'Run',
        procedure(ACtx: ITgContext)
        begin
        end);
      LBot.Active := True;
      Check(PumpUntil(
        function: Boolean
        begin
          Result := TInterlocked.CompareExchange(LEntered, 0, 0) > 0;
        end, 5000), 'getMe фоновой подготовки начат');
    finally
      LWatch := TStopwatch.StartNew;
      LBot.Free;
      GFreeWaitCompMs := LWatch.ElapsedMilliseconds;
    end;
    Check(GFreeWaitCompMs < TgDefaultBotFreeStartJobWaitMs + 1000,
      Format('Free компонента при висящем getMe — без ожидания бюджета Stop (%d мс)', [GFreeWaitCompMs]));
    Check(WaitTransportReleased(LTransport, 5000), 'ядро и клиент освобождены');
    Check(WaitLiveAtMost(LBaseCores, LBaseJobs, 5000), 'живых ядер и задач подготовки — как до теста');
    CheckEquals(0, LTransport.Count('setMyCommands'), 'меню отменённой задачи не отправлялось');
    // Записи OnError — 'err <класс> ...' (Has сравнивает строку целиком).
    CheckEquals(0, Pos('err ', LEvents.Log.Text), 'без ошибок: ' + LEvents.Log.Text);
  finally
    LEvents.Free;
  end;
end;

procedure TestStartJobRestartLateReply;
var
  LTransport: TScriptTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LGetMeGate, LSetGate: TEvent;
  LErrors: TTextLog;
  LGetMeCalls, LGetMeLate, LSetCalls, LSetLate, LBaseCores, LBaseJobs: Integer;
  LMenus: TArray<string>;
  LReleased: Boolean;
begin
  LBaseCores := LiveBotCores;
  LBaseJobs := LiveStartJobs;
  LGetMeCalls := 0;
  LGetMeLate := 0;
  LSetCalls := 0;
  LSetLate := 0;
  LReleased := False;
  LGetMeGate := TEvent.Create(nil, True, False, '');
  LSetGate := TEvent.Create(nil, True, False, '');
  LErrors := TTextLog.Create;
  try
    // Без токенов: зависший запрос не прерывается и отвечает поздно.
    LTransport := TScriptTransport.Create(
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      begin
        if AMethod = 'getUpdates' then
          Exit(IdleUpdates(AParams));
        if AMethod = 'getMe' then
        begin
          // Первый getMe (задача запуска 1) висит и отвечает чужим именем.
          if TInterlocked.Increment(LGetMeCalls) = 1 then
          begin
            LGetMeGate.WaitFor(30000);
            Result := BotUserJson('LateBot');
            TInterlocked.Increment(LGetMeLate);
            Exit;
          end;
          Exit(BotUserJson('NewBot'));
        end;
        if AMethod = 'setMyCommands' then
        begin
          // Первое меню (задача запуска 2) висит и отвечает поздно.
          if TInterlocked.Increment(LSetCalls) = 1 then
          begin
            LSetGate.WaitFor(30000);
            TInterlocked.Increment(LSetLate);
          end;
          Exit(TJSONTrue.Create);
        end;
        Result := TJSONTrue.Create;
      end);
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      LBot.OnError :=
        procedure(AError: Exception; ACtx: ITgContext)
        begin
          LErrors.Add(AError.ClassName + ': ' + AError.Message);
        end;
      LBot.Command('a', 'Команда A',
        procedure(ACtx: ITgContext)
        begin
        end);
      // Запуск 1: getMe висит; Stop с малым ожиданием отпускает задачу.
      LBot.Start;
      Check(WaitUntil(
        function: Boolean
        begin
          Result := TInterlocked.CompareExchange(LGetMeCalls, 0, 0) >= 1;
        end, 5000), 'запуск 1: getMe начат');
      Check(not LBot.Stop(50), 'запуск 1: Stop(50) = False — задача отпущена (getMe висит)');
      // Запуск 2 сразу: своя задача — свой getMe; меню висит.
      LBot.Start;
      Check(WaitUntil(
        function: Boolean
        begin
          Result := TInterlocked.CompareExchange(LSetCalls, 0, 0) >= 1;
        end, 5000), 'запуск 2: getMe выполнен, setMyCommands начат');
      CheckEquals('NewBot', LBot.BotUserName, 'запуск 2: username из getMe новой задачи');
      // Поздний getMe задачи 1: она отменена — username не меняется, OnError нет.
      LGetMeGate.SetEvent;
      Check(WaitUntil(
        function: Boolean
        begin
          Result := TInterlocked.CompareExchange(LGetMeLate, 0, 0) = 1;
        end, 5000), 'поздний getMe задачи 1 вернулся');
      Check(WaitLiveAtMost(LBaseCores + 1, LBaseJobs + 1, 5000),
        'задача 1 освобождена после позднего ответа (жива только задача 2)');
      TThread.Sleep(100);
      CheckEquals('NewBot', LBot.BotUserName, 'поздний getMe старой задачи не трогает username');
      Check(not LBot.Stop(50), 'запуск 2: Stop(50) = False — задача отпущена (меню висит)');
      // Запуск 3: другое меню; username из кэша — только setMyCommands.
      LBot.Command('a', nil);
      LBot.Command('b', 'Команда B',
        procedure(ACtx: ITgContext)
        begin
        end);
      LBot.Start;
      Check(WaitUntil(
        function: Boolean
        begin
          Result := TInterlocked.CompareExchange(LSetCalls, 0, 0) >= 2;
        end, 5000), 'запуск 3: setMyCommands нового меню');
      // Поздний ответ меню задачи 2 — после меню задачи 3.
      LSetGate.SetEvent;
      Check(WaitUntil(
        function: Boolean
        begin
          Result := TInterlocked.CompareExchange(LSetLate, 0, 0) = 1;
        end, 5000), 'поздний setMyCommands задачи 2 вернулся');
      Check(WaitLiveAtMost(LBaseCores + 1, LBaseJobs + 1, 5000),
        'задача 2 освобождена после позднего ответа');
      TThread.Sleep(100);
      Check(LBot.Stop, 'запуск 3: Stop = True — задача 3 завершена, поздние ответы её не задели');
      CheckEquals('NewBot', LBot.BotUserName, 'username после всех поздних ответов');
    finally
      LBot.Free;
    end;
    LReleased := WaitTransportReleased(LTransport, 5000);
    Check(LReleased, 'ядро и клиент освобождены');
    Check(WaitLiveAtMost(LBaseCores, LBaseJobs, 5000), 'живых ядер и задач подготовки — как до теста');
    CheckEquals(2, LTransport.Count('getMe'), 'getMe: задача 1 (поздний) и задача 2; задача 3 — из кэша');
    LMenus := LTransport.Calls('setMyCommands');
    CheckEquals(2, Length(LMenus), 'setMyCommands: задача 2 (поздний) и задача 3');
    if Length(LMenus) = 2 then
    begin
      CheckEquals('a', JsonAt(LMenus[0], 'commands[0].command'), 'меню задачи 2: a');
      CheckEquals('b', JsonAt(LMenus[1], 'commands[0].command'), 'меню задачи 3: b');
      CheckEquals('', JsonAt(LMenus[1], 'commands[1].command'), 'меню задачи 3: только b');
    end;
    CheckEquals(0, LErrors.Count, 'поздние ответы отменённых задач — без OnError: ' + LErrors.Text);
  finally
    LGetMeGate.SetEvent;
    LSetGate.SetEvent;
    LErrors.Free;
    if LReleased then
    begin
      LSetGate.Free;
      LGetMeGate.Free;
    end;
  end;
end;

procedure TestStartJobHandlerWaitsName;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LLog: TTextLog;
  LGetMe, LBaseCores, LBaseJobs: Integer;
  LReleased: Boolean;
begin
  LBaseCores := LiveBotCores;
  LBaseJobs := LiveStartJobs;
  LGetMe := 0;
  LReleased := False;
  LLog := TTextLog.Create;
  try
    LTransport := TScriptCancellableTransport.Create(
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      begin
        if AMethod = 'getUpdates' then
        begin
          if TTgJson.GetInt(AParams.Json, 'timeout') = 0 then
            Exit(TJSONArray.Create);
          if not TTgJson.Has(AParams.Json, 'offset') then
            Exit(Batch([MsgUpdate(1, 100, 7, '/start@ThisBot')]));
          Exit(HangUntilCancelled);
        end;
        if AMethod = 'getMe' then
        begin
          // И getMe задачи, и ленивый getMe обработчика висят до отмены.
          TInterlocked.Increment(LGetMe);
          Exit(HangGetMe('ThisBot'));
        end;
        Result := TJSONTrue.Create;
      end);
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      LBot.Command('start', 'Запуск',
        procedure(ACtx: ITgContext)
        begin
          LLog.Add('routed');
        end);
      LBot.OnUpdate :=
        procedure(ACtx: ITgContext)
        begin
          LLog.Add('upd ' + ACtx.Text);
        end;
      LBot.OnError :=
        procedure(AError: Exception; ACtx: ITgContext)
        begin
          LLog.Add('error ' + AError.ClassName);
        end;
      LBot.Start;
      Check(WaitUntil(
        function: Boolean
        begin
          Result := (LTransport.Count('getUpdates') >= 2) and
            (TInterlocked.CompareExchange(LGetMe, 0, 0) >= 1);
        end, 5000), 'пакет принят, getMe задачи висит');
      // Обработчик '/start@ThisBot' ждёт username (getMe задачи): OnUpdate — после разбора команды.
      TThread.Sleep(100);
      Check(not LLog.Has('upd /start@ThisBot'), 'обработчик ждёт username');
      // Stop параллельно ожиданию: отмена задачи по таймауту, затем — обработчика.
      LBot.Stop(200);
    finally
      // Free сразу: обработчик может ещё выполняться (ядро отсоединяется).
      LBot.Free;
    end;
    LReleased := WaitTransportReleased(LTransport, 5000);
    Check(LReleased, 'обработчик вышел: ядро и клиент освобождены');
    Check(WaitLiveAtMost(LBaseCores, LBaseJobs, 5000), 'живых ядер и задач подготовки — как до теста');
    Check(not LLog.Has('routed'), 'username не получен — /start@ThisBot не маршрутизирована: ' + LLog.Text);
    Check(not Contains('error', LLog.Text), 'отмена ожидания — без OnError: ' + LLog.Text);
  finally
    // Не дождались освобождения — журнал может быть ещё нужен обработчику.
    if LReleased then
      LLog.Free;
  end;
end;

/// <summary>
///   Транспорт цикла Start/Stop/Free: getMe отвечает через ADelayMs мс
///   (ACancellable — ожидание прерывается токеном), меню — True.
/// </summary>
function ChurnScript(ADelayMs: Integer; ACancellable: Boolean): TFakeHandler;
begin
  Result :=
    function(const AMethod: string; AParams: TTgParams): TJSONValue
    var
      LToken: ITgCancellation;
    begin
      if AMethod = 'getUpdates' then
        Exit(IdleUpdates(AParams));
      if AMethod = 'getMe' then
      begin
        LToken := TTgCancelScope.Current;
        if ACancellable and Assigned(LToken) then
        begin
          LToken.WaitFor(ADelayMs);
          LToken.ThrowIfCancelled;
        end
        else
          TThread.Sleep(ADelayMs);
        Exit(BotUserJson('ThisBot'));
      end;
      Result := TJSONTrue.Create;
    end;
end;

procedure TestStartJobChurn;
const
  CCycles = 200;
var
  LTransports: TArray<TScriptTransport>;
  LRefs: TArray<ITgTransport>;
  LBot: TTgBot;
  LErrors: TTextLog;
  LSeed: Int64;
  LDelay, I, LBaseCores, LBaseJobs: Integer;
  LWatch: TStopwatch;
  LEmpty: TProc<ITgContext>;
  LOnError: TProc<Exception, ITgContext>;
  LReleased: Boolean;
begin
  LBaseCores := LiveBotCores;
  LBaseJobs := LiveStartJobs;
  LReleased := False;
  LErrors := TTextLog.Create;
  try
    SetLength(LTransports, CCycles);
    SetLength(LRefs, CCycles);
    LEmpty :=
      procedure(ACtx: ITgContext)
      begin
      end;
    LOnError :=
      procedure(AError: Exception; ACtx: ITgContext)
      begin
        LErrors.Add(AError.ClassName + ': ' + AError.Message);
      end;
    // Детерминированные «случайные» задержки (ЛКГ): прогон воспроизводим.
    LSeed := 20261015;
    LWatch := TStopwatch.StartNew;
    for I := 0 to CCycles - 1 do
    begin
      LSeed := (LSeed * 1103515245 + 12345) mod 2147483648;
      LDelay := (LSeed shr 16) mod 51;
      if Odd(I div 4) then
        LTransports[I] := TScriptTransport.Create(ChurnScript(LDelay, False))
      else
        LTransports[I] := TScriptCancellableTransport.Create(ChurnScript(LDelay, True));
      LRefs[I] := LTransports[I];
      LBot := TTgBot.Create(LRefs[I]);
      try
        LBot.OnError := LOnError;
        LBot.Command('start', 'Запуск', LEmpty);
        LBot.Start;
        case I mod 4 of
          // Stop с малым ожиданием: задача может быть отменена на getMe.
          1: LBot.Stop(10);
          // Перезапуск: вторая задача — только меню (username в кэше).
          2:
            begin
              LBot.Stop;
              LBot.Start;
            end;
          // Free посреди getMe.
          3: TThread.Sleep(LDelay div 2);
        end;
      finally
        // 0: Free сразу после Start (Stop внутри Free).
        LBot.Free;
      end;
    end;
    GOwnChurnMs := LWatch.ElapsedMilliseconds;
    LReleased := WaitUntil(
      function: Boolean
      var
        J: Integer;
      begin
        for J := 0 to High(LTransports) do
          if LTransports[J].RefCount <> 1 then
            Exit(False);
        Result := True;
      end, 10000);
    Check(LReleased, Format('%d циклов: все ядра и клиенты освобождены', [CCycles]));
    Check(WaitLiveAtMost(LBaseCores, LBaseJobs, 5000), 'живых ядер и задач подготовки — как до теста');
    Check(GOwnChurnMs < 60000, Format('%d циклов Start/Stop/Free за %d мс (< 60 с)', [CCycles, GOwnChurnMs]));
    CheckEquals(0, LErrors.Count, 'без OnError: ' + LErrors.Text);
  finally
    LOnError := nil;
    LEmpty := nil;
    LRefs := nil;
    if LReleased then
      LErrors.Free;
  end;
end;

procedure TestComponentStartJobFault;
var
  LEvents: TComponentEvents;
  LBot: TTelegramBot;
  LTransportRef: ITgTransport;
  LItem: TTgCommandItem;
begin
  LEvents := TComponentEvents.Create;
  try
    LTransportRef := TScriptCancellableTransport.Create(StartJobScript(401, 0));
    LBot := TTelegramBot.Create(nil);
    try
      LBot.Transport := LTransportRef;
      LItem := LBot.Commands.Add;
      LItem.Command := 'start';
      LItem.Description := 'Запуск';
      LBot.OnError := LEvents.DoError;
      LBot.OnFault := LEvents.DoFault;
      LBot.OnStop := LEvents.DoStop;
      LBot.Active := True;
      Check(PumpUntil(
        function: Boolean
        begin
          Result := LEvents.Log.Has('stop fault');
        end, 5000), 'компонент: OnStop(Fault)');
      PumpUntil(
        function: Boolean
        begin
          Result := False;
        end, 300);
      CheckEquals(1, LEvents.Log.CountOf('err ETgApiError 401 ctx=False'),
        'компонент, 401: OnError ровно один: ' + LEvents.Log.Text);
      CheckEquals(1, LEvents.Log.CountOf('fault 401'), 'компонент, 401: OnFault ровно один');
      CheckEquals(3, LEvents.Log.Count, 'компонент, 401: только OnError, OnFault, OnStop: ' +
        LEvents.Log.Text);
    finally
      LBot.Free;
    end;
  finally
    LEvents.Free;
  end;
end;

procedure TestWebhookRegisteredEvent;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LTgBot: TTgBot;
  LLog: TTextLog;
  LEvents: TComponentEvents;
  LBot: TTelegramBot;
  LStart, LReg: Integer;
begin
  LLog := TTextLog.Create;
  try
    // TTgBot: в фоне после успешного setWebhook, при каждом запуске.
    LTransport := TScriptCancellableTransport.Create(WebhookScript(False));
    LTransportRef := LTransport;
    LTgBot := TTgBot.Create(LTransportRef);
    try
      LTgBot.Mode := TTgReceiveMode.Webhook;
      LTgBot.WebhookUrl := 'https://example.org/hook';
      LTgBot.OnWebhookRegistered :=
        procedure
        begin
          if TThread.CurrentThread.ThreadID = MainThreadID then
            LLog.Add('registered main')
          else
            LLog.Add('registered bg');
        end;
      LTgBot.Start;
      Check(WaitLogHas(LLog, 'registered bg'), 'TTgBot.OnWebhookRegistered — в фоне');
      Check(LTgBot.Stop, 'Stop');
      LTgBot.Start;
      Check(WaitUntil(
        function: Boolean
        begin
          Result := LLog.CountOf('registered bg') = 2;
        end, 5000), 'повторный запуск — событие ещё раз');
      Check(LTgBot.Stop, 'Stop (2)');
      CheckEquals(2, LLog.Count, 'TTgBot: событие по разу на запуск: ' + LLog.Text);
    finally
      LTgBot.Free;
    end;
    // Ошибка setWebhook — без события.
    LLog.Clear;
    LTransportRef := TScriptCancellableTransport.Create(WebhookScript(True));
    LTgBot := TTgBot.Create(LTransportRef);
    try
      LTgBot.Mode := TTgReceiveMode.Webhook;
      LTgBot.WebhookUrl := 'https://example.org/hook';
      LTgBot.OnWebhookRegistered :=
        procedure
        begin
          LLog.Add('registered');
        end;
      LTgBot.OnFault :=
        procedure(AError: Exception)
        begin
          LLog.Add('fault');
        end;
      LTgBot.Start;
      Check(WaitLogHas(LLog, 'fault'), 'ошибка setWebhook → OnFault');
      TThread.Sleep(100);
      Check(not LLog.Has('registered'), 'ошибка setWebhook — OnWebhookRegistered не вызван');
    finally
      LTgBot.Free;
    end;
  finally
    LLog.Free;
  end;
  // Компонент, Delivery = Main: OnStart → OnWebhookRegistered, в главном потоке.
  LEvents := TComponentEvents.Create;
  try
    LTransportRef := TScriptCancellableTransport.Create(WebhookScript(False));
    LBot := TTelegramBot.Create(nil);
    try
      LBot.Transport := LTransportRef;
      LBot.Mode := TTgReceiveMode.Webhook;
      LBot.Webhook.Url := 'https://example.org/hook';
      LBot.OnStart := LEvents.DoStart;
      LBot.OnWebhookRegistered := LEvents.DoWebhookRegistered;
      LBot.Active := True;
      Check(LEvents.Log.Has('start'), 'OnStart — при запуске');
      Check(PumpUntil(
        function: Boolean
        begin
          Result := LEvents.Log.Has('registered');
        end, 5000), 'компонент: OnWebhookRegistered через очередь');
      // Записи без пробелов CommaText не берёт в кавычки — позиции в тексте.
      LStart := Pos('start', LEvents.Log.Text);
      LReg := Pos('registered', LEvents.Log.Text);
      Check((LStart > 0) and (LStart < LReg), 'порядок: OnStart → OnWebhookRegistered: ' + LEvents.Log.Text);
      CheckEquals(0, LEvents.NotMain, 'OnStart и OnWebhookRegistered — в главном потоке');
      CheckEquals(1, LEvents.Log.CountOf('registered'), 'OnWebhookRegistered один раз');
      LBot.Active := False;
    finally
      LBot.Free;
    end;
  finally
    LEvents.Free;
  end;
end;

procedure TestContextEditNotModified;
var
  LTransport: TScriptCancellableTransport;
  LTransportRef: ITgTransport;
  LBot: TTgBot;
  LLog: TTextLog;
begin
  LLog := TTextLog.Create;
  try
    LTransport := TScriptCancellableTransport.Create(
      function(const AMethod: string; AParams: TTgParams): TJSONValue
      var
        LText: string;
      begin
        if AMethod = 'getUpdates' then
        begin
          if TTgJson.GetInt(AParams.Json, 'timeout') = 0 then
            Exit(TJSONArray.Create);
          if not TTgJson.Has(AParams.Json, 'offset') then
            Exit(Batch([CbUpdate(1, 'same'), CbUpdate(2, 'bad'),
              '{"update_id":3,"callback_query":{"id":"cb3","from":{"id":7,"is_bot":false,' +
              '"first_name":"U"},"chat_instance":"ci","inline_message_id":"im1","data":"inline"}}',
              CbUpdate(4, 'ok')]));
          Exit(HangUntilCancelled);
        end;
        if (AMethod = 'editMessageText') then
        begin
          LText := TTgJson.GetStr(AParams.Json, 'text');
          if LText = 'same' then
            raise ETgApiError.Create(AMethod, 400, 'Bad Request: message is not modified: specified ' +
              'new message content and reply markup are exactly the same as a current content and ' +
              'reply markup of the message');
          if LText = 'bad' then
            raise ETgApiError.Create(AMethod, 400, 'Bad Request: message to edit not found');
          if TTgJson.Has(AParams.Json, 'inline_message_id') then
            Exit(TJSONTrue.Create);
          Exit(JsonOf(CShortMessageJson));
        end;
        Result := TJSONTrue.Create;
      end);
    LTransportRef := LTransport;
    LBot := TTgBot.Create(LTransportRef);
    try
      LBot.OnCallbackQuery :=
        procedure(ACtx: ITgContext)
        begin
          if ACtx.Data = 'same' then
          begin
            LLog.Add('edit same ' + BoolToStr(ACtx.Edit('same'), True));
            // Сырой метод Api — как прежде: исключение.
            try
              ACtx.Api.EditMessageText(ACtx.ChatId, 55, 'same');
              LLog.Add('raw no error');
            except
              on E: ETgApiError do
                LLog.Add(Format('raw %d', [E.ErrorCode]));
            end;
          end
          else if ACtx.Data = 'bad' then
            ACtx.Edit('bad')
          else if ACtx.Data = 'inline' then
            LLog.Add('edit inline ' + BoolToStr(ACtx.Edit('same', nil), True))
          else
            LLog.Add('edit ok ' + BoolToStr(ACtx.Edit('new'), True));
        end;
      LBot.OnError :=
        procedure(AError: Exception; ACtx: ITgContext)
        begin
          LLog.Add(Format('error %d ctx=%s', [ApiCode(AError), BoolToStr(Assigned(ACtx), True)]));
        end;
      LBot.Start;
      Check(WaitUntil(
        function: Boolean
        begin
          Result := LLog.Has('edit ok True') and LLog.Has('error 400 ctx=True') and
            LLog.Has('edit inline False') and LLog.Has('raw 400');
        end, 5000), 'все нажатия обработаны: ' + LLog.Text);
      Check(LBot.Stop, 'Stop');
    finally
      LBot.Free;
    end;
    Check(LLog.Has('edit same False'), 'Ctx.Edit: «message is not modified» → False без исключения');
    Check(LLog.Has('edit inline False'), 'Ctx.Edit (inline): «message is not modified» → False');
    Check(LLog.Has('raw 400'), 'Api.EditMessageText: поведение прежнее — ETgApiError 400');
    CheckEquals(1, LLog.CountOf('error 400 ctx=True'), 'другая ошибка 400 — исключение (OnError с контекстом)');
    Check(LLog.Has('edit ok True'), 'успешное изменение — True');
  finally
    LLog.Free;
  end;
end;

procedure TestComponentWebhookCertificate;
var
  LFake: TFakeTransport;
  LTransportRef: ITgTransport;
  LBot, LCopy: TTelegramBot;
  LFile: string;
  LNames, LPaths: TArray<string>;
begin
  LFile := TPath.Combine(TPath.GetTempPath, 'tgbot6e2_' + IntToStr(TThread.CurrentThread.ThreadID) + '.pem');
  TFile.WriteAllText(LFile, '-----BEGIN CERTIFICATE-----'#13#10'MIIB'#13#10'-----END CERTIFICATE-----'#13#10);
  try
    LFake := TFakeTransport.Create(nil);
    LTransportRef := LFake;
    LBot := TTelegramBot.Create(nil);
    try
      Check((LBot.Webhook.IpAddress = '') and (LBot.Webhook.Certificate = ''),
        'IpAddress и Certificate по умолчанию пусты');
      LBot.Transport := LTransportRef;
      LBot.Delivery := TTgDelivery.Worker;
      LBot.Mode := TTgReceiveMode.Webhook;
      LBot.Webhook.Url := 'https://203.0.113.5:8443/hook';
      LBot.Webhook.IpAddress := '203.0.113.5';
      LBot.Webhook.Certificate := LFile;
      LCopy := TTelegramBot.Create(nil);
      try
        LCopy.Webhook := LBot.Webhook;
        Check((LCopy.Webhook.IpAddress = '203.0.113.5') and (LCopy.Webhook.Certificate = LFile),
          'Assign копирует IpAddress и Certificate');
      finally
        LCopy.Free;
      end;
      LBot.Active := True;
      Check(WaitUntil(
        function: Boolean
        begin
          Result := LFake.LastMethod = 'setWebhook';
        end, 5000), 'setWebhook вызван');
      LBot.Active := False;
      LNames := LFake.LastFileNames;
      LPaths := LFake.LastFilePaths;
      Check(Contains('"ip_address":"203.0.113.5"', LFake.LastJson), 'ip_address передан: ' + LFake.LastJson);
      Check((Length(LNames) = 1) and (LNames[0] = 'certificate'), 'certificate — файлом (multipart)');
      Check((Length(LPaths) = 1) and SameText(LPaths[0], LFile), 'certificate — путь к .pem');
      Check(Raises(
        procedure
        begin
          LBot.Webhook.IpAddress := '1.2.3.4';
          LBot.Active := True;
          LBot.Webhook.IpAddress := '5.6.7.8';
        end, ETgError), 'IpAddress при работе → ETgError');
      LBot.Active := False;
      // Файла нет — ETgError при запуске, без запросов.
      LBot.Webhook.Certificate := LFile + '.missing';
      Check(Raises(
        procedure
        begin
          LBot.Active := True;
        end, ETgError), 'нет файла сертификата → ETgError при запуске');
      Check(not LBot.Active, 'бот не запущен');
    finally
      LBot.Free;
    end;
  finally
    TFile.Delete(LFile);
  end;
end;

{ 5b-1: DtoNotObject с именем поля; полнота текстов RU/EN }

type
  /// <summary>DTO с доступом к защищённым SetStr/AppendRow (тест DtoNotObject).</summary>
  TTestDto = class(TTgJsonDto)
  public
    procedure PutStr(const AName, AValue: string);
    procedure PutRow(const AName: string);
  end;

  /// <summary>Пара ресурсных строк TgBot.Consts (SRu…/SEn…).</summary>
  TTextPair = record
    Name: string;
    Ru, En: PResStringRec;
  end;

const
  // Пары TgBot.Consts, не покрытые TTgText, TTgUpdatesText и TTgRouterText
  // (модули берут их через TgLangText напрямую). Новую такую пару — сюда.
  CConstPairs: array[0..25] of TTextPair = (
    (Name: 'ArgNil'; Ru: @SRuArgNil; En: @SEnArgNil),
    (Name: 'ArgOutOfRange'; Ru: @SRuArgOutOfRange; En: @SEnArgOutOfRange),
    (Name: 'JsonNotInteger'; Ru: @SRuJsonNotInteger; En: @SEnJsonNotInteger),
    (Name: 'JsonIntegerRange'; Ru: @SRuJsonIntegerRange; En: @SEnJsonIntegerRange),
    (Name: 'JsonNotFloat'; Ru: @SRuJsonNotFloat; En: @SEnJsonNotFloat),
    (Name: 'JsonFloatInvalid'; Ru: @SRuJsonFloatInvalid; En: @SEnJsonFloatInvalid),
    (Name: 'DtoNotObject'; Ru: @SRuDtoNotObject; En: @SEnDtoNotObject),
    (Name: 'DtoFileUpload'; Ru: @SRuDtoFileUpload; En: @SEnDtoFileUpload),
    (Name: 'DtoUnsupported'; Ru: @SRuDtoUnsupported; En: @SEnDtoUnsupported),
    (Name: 'DtoEmptyItem'; Ru: @SRuDtoEmptyItem; En: @SEnDtoEmptyItem),
    (Name: 'DtoNotJsonDto'; Ru: @SRuDtoNotJsonDto; En: @SEnDtoNotJsonDto),
    (Name: 'UpdNoRandom'; Ru: @SRuUpdNoRandom; En: @SEnUpdNoRandom),
    (Name: 'BotWebhookNotHttps'; Ru: @SRuBotWebhookNotHttps; En: @SEnBotWebhookNotHttps),
    (Name: 'CompBotActive'; Ru: @SRuCompBotActive; En: @SEnCompBotActive),
    (Name: 'CompNoWebhookPath'; Ru: @SRuCompNoWebhookPath; En: @SEnCompNoWebhookPath),
    (Name: 'CompNoCertificate'; Ru: @SRuCompNoCertificate; En: @SEnCompNoCertificate),
    (Name: 'CompRunNotMain'; Ru: @SRuCompRunNotMain; En: @SEnCompRunNotMain),
    (Name: 'CompRunUnsupported'; Ru: @SRuCompRunUnsupported; En: @SEnCompRunUnsupported),
    (Name: 'WhsServerActive'; Ru: @SRuWhsServerActive; En: @SEnWhsServerActive),
    (Name: 'WhsBadPort'; Ru: @SRuWhsBadPort; En: @SEnWhsBadPort),
    (Name: 'WhsBadBodySize'; Ru: @SRuWhsBadBodySize; En: @SEnWhsBadBodySize),
    (Name: 'WhsBadConnections'; Ru: @SRuWhsBadConnections; En: @SEnWhsBadConnections),
    (Name: 'WhsStartFailed'; Ru: @SRuWhsStartFailed; En: @SEnWhsStartFailed),
    (Name: 'WhsPathTaken'; Ru: @SRuWhsPathTaken; En: @SEnWhsPathTaken),
    (Name: 'WhsBadPath'; Ru: @SRuWhsBadPath; En: @SEnWhsBadPath),
    (Name: 'WhsPublicUrlNotHttps'; Ru: @SRuWhsPublicUrlNotHttps; En: @SEnWhsPublicUrlNotHttps)
  );
  // Всего пар SRu…/SEn… в TgBot.Consts: перечисления TTgText, TTgUpdatesText,
  // TTgRouterText и CConstPairs. Обновите при добавлении пары в TgBot.Consts.
  CExpectedConstPairs = 60;

{ TTestDto }

procedure TTestDto.PutStr(const AName, AValue: string);
begin
  SetStr(AName, AValue);
end;

procedure TTestDto.PutRow(const AName: string);
begin
  AppendRow(AName, nil);
end;

/// <summary>Текст исключения класса AClass из AProc; иначе — описание того, что произошло.</summary>
function RaisedText(const AProc: TProc; AClass: ExceptClass): string;
begin
  try
    AProc();
    Result := '<нет исключения>';
  except
    on E: Exception do
      if E is AClass then
        Result := E.Message
      else
        Result := '<' + E.ClassName + '> ' + E.Message;
  end;
end;

procedure TestDtoNotObjectField;
var
  LDto: TTestDto;
  LRef: ITgJsonObject;
  LLanguage, LLang: TTgLanguage;
  LText: string;
begin
  // DTO над JSON-массивом: FJson = nil, Set*/AppendRow → ETgError DtoNotObject.
  LDto := TTestDto.CreateValue(TJSONArray.Create);
  LRef := LDto;
  LLanguage := TgGetLanguage;
  try
    for LLang := Low(TTgLanguage) to High(TTgLanguage) do
    begin
      TgSetLanguage(LLang);
      LText := RaisedText(
        procedure
        begin
          LDto.PutStr('field_x', 'значение');
        end, ETgError);
      Check(Contains('field_x', LText), 'SetStr: имя поля в сообщении — "' + LText + '"');
      Check(not Contains(LDto.ClassName, LText), 'SetStr: имя класса не подставляется');
      CheckEquals(TgLangTextFmt(@SRuDtoNotObject, @SEnDtoNotObject, ['field_x']), LText,
        'SetStr: текст DtoNotObject');
      LText := RaisedText(
        procedure
        begin
          LDto.PutRow('rows_y');
        end, ETgError);
      CheckEquals(TgLangTextFmt(@SRuDtoNotObject, @SEnDtoNotObject, ['rows_y']), LText,
        'AppendRow: текст DtoNotObject');
    end;
  finally
    TgSetLanguage(LLanguage);
  end;
  CheckEquals('[]', LRef.AsJson, 'массив не изменён');
  Check(LDto.GetRaw = nil, 'GetRaw = nil');
end;

/// <summary>
///   Спецификаторы Format по порядку ('%s %d %.2f '), %% пропускается.
///   AValid = False — неизвестный тип или обрыв в конце строки.
/// </summary>
function FormatSpecs(const AText: string; out AValid: Boolean): string;
var
  I, J: Integer;
begin
  Result := '';
  AValid := True;
  I := 1;
  while I <= Length(AText) do
  begin
    if AText[I] <> '%' then
    begin
      Inc(I);
      Continue;
    end;
    if (I < Length(AText)) and (AText[I + 1] = '%') then
    begin
      Inc(I, 2);
      Continue;
    end;
    // %[индекс:][-][ширина][.точность]тип
    J := I + 1;
    while (J <= Length(AText)) and CharInSet(AText[J], ['0'..'9', ':', '-', '.', '*']) do
      Inc(J);
    if (J > Length(AText)) or not CharInSet(AText[J],
      ['d', 'u', 'e', 'f', 'g', 'n', 'm', 'p', 's', 'x', 'D', 'U', 'E', 'F', 'G', 'N', 'M', 'P', 'S', 'X']) then
      AValid := False;
    Result := Result + Copy(AText, I, J - I + 1) + ' ';
    I := J + 1;
  end;
end;

function HasCyrillic(const AText: string): Boolean;
var
  LChar: Char;
begin
  for LChar in AText do
    if (LChar >= #$0400) and (LChar <= #$04FF) then
      Exit(True);
  Result := False;
end;

/// <summary>
///   8 проверок пары: оба текста непусты, RU ≠ EN, RU с кириллицей, EN без
///   неё (пара не перепутана), спецификаторы допустимы и совпадают по порядку.
/// </summary>
procedure CheckTextPair(const AName, ARu, AEn: string);
var
  LRuSpecs, LEnSpecs: string;
  LRuValid, LEnValid: Boolean;
begin
  Check(Trim(ARu) <> '', AName + ': RU пуст');
  Check(Trim(AEn) <> '', AName + ': EN пуст');
  Check(ARu <> AEn, AName + ': RU = EN — "' + ARu + '"');
  Check(HasCyrillic(ARu), AName + ': RU без кириллицы — "' + ARu + '"');
  Check(not HasCyrillic(AEn), AName + ': кириллица в EN — "' + AEn + '"');
  LRuSpecs := FormatSpecs(ARu, LRuValid);
  LEnSpecs := FormatSpecs(AEn, LEnValid);
  Check(LRuValid, AName + ': недопустимый спецификатор в RU — "' + ARu + '"');
  Check(LEnValid, AName + ': недопустимый спецификатор в EN — "' + AEn + '"');
  CheckEquals(LRuSpecs, LEnSpecs, AName + ': спецификаторы RU/EN');
end;

procedure TestTextsComplete;
var
  LLanguage: TTgLanguage;
  LText: TTgText;
  LUpdText: TTgUpdatesText;
  LRouteText: TTgRouterText;
  LRu, LEn, LDuplicate: string;
  I, J: Integer;
begin
  LLanguage := TgGetLanguage;
  try
    for LText := Low(TTgText) to High(TTgText) do
    begin
      TgSetLanguage(TTgLanguage.Ru);
      LRu := TgText(LText);
      TgSetLanguage(TTgLanguage.En);
      LEn := TgText(LText);
      CheckTextPair('TTgText.' + GetEnumName(TypeInfo(TTgText), Ord(LText)), LRu, LEn);
    end;
    for LUpdText := Low(TTgUpdatesText) to High(TTgUpdatesText) do
    begin
      TgSetLanguage(TTgLanguage.Ru);
      LRu := TgUpdatesText(LUpdText);
      TgSetLanguage(TTgLanguage.En);
      LEn := TgUpdatesText(LUpdText);
      CheckTextPair('TTgUpdatesText.' + GetEnumName(TypeInfo(TTgUpdatesText), Ord(LUpdText)), LRu, LEn);
    end;
    for LRouteText := Low(TTgRouterText) to High(TTgRouterText) do
    begin
      TgSetLanguage(TTgLanguage.Ru);
      LRu := TgRouterText(LRouteText);
      TgSetLanguage(TTgLanguage.En);
      LEn := TgRouterText(LRouteText);
      CheckTextPair('TTgRouterText.' + GetEnumName(TypeInfo(TTgRouterText), Ord(LRouteText)), LRu, LEn);
    end;
    // Пары без перечислений: напрямую (LoadResString) и выбор языка в TgLangText.
    for I := Low(CConstPairs) to High(CConstPairs) do
    begin
      LRu := LoadResString(CConstPairs[I].Ru);
      LEn := LoadResString(CConstPairs[I].En);
      CheckTextPair('Consts.' + CConstPairs[I].Name, LRu, LEn);
      TgSetLanguage(TTgLanguage.Ru);
      CheckEquals(LRu, TgLangText(CConstPairs[I].Ru, CConstPairs[I].En),
        'Consts.' + CConstPairs[I].Name + ': TgLangText (Ru)');
      TgSetLanguage(TTgLanguage.En);
      CheckEquals(LEn, TgLangText(CConstPairs[I].Ru, CConstPairs[I].En),
        'Consts.' + CConstPairs[I].Name + ': TgLangText (En)');
      // Повтор пары завысил бы счёт полноты ниже.
      LDuplicate := '';
      for J := Low(CConstPairs) to I - 1 do
        if CConstPairs[J].Ru = CConstPairs[I].Ru then
          LDuplicate := CConstPairs[J].Name;
      Check(LDuplicate = '', 'Consts.' + CConstPairs[I].Name + ': повтор пары ' + LDuplicate);
    end;
    // Полнота: пары перечислений и CConstPairs покрывают все пары TgBot.Consts.
    CheckEquals(CExpectedConstPairs, (Ord(High(TTgText)) + 1) + (Ord(High(TTgUpdatesText)) + 1) +
      (Ord(High(TTgRouterText)) + 1) + Length(CConstPairs),
      'число проверенных пар = CExpectedConstPairs (новую пару TgBot.Consts — в перечисление или CConstPairs)');
  finally
    TgSetLanguage(LLanguage);
  end;
  Check(TgGetLanguage = LLanguage, 'язык восстановлен');
end;

{ Владение, фаза 5: ITgJsonHolder, ITgOwnerLink, номер запуска компонента }

type
  /// <summary>DTO с доступом к защищённому JsonOwner.</summary>
  IOwnerDto = interface(ITgJsonObject)
    ['{EB41F43D-8271-4822-88F2-204BD4445B5E}']
    function Owner: IInterface;
  end;

  TOwnerDto = class(TTgJsonDto, IOwnerDto)
  public
    function Owner: IInterface;
  end;

  /// <summary>Посторонний владелец JSON (не держатель): считает освобождения.</summary>
  TOwnerProbe = class(TInterfacedObject)
  private
    FFreed: PInteger;
  public
    constructor Create(AFreed: PInteger);
    destructor Destroy; override;
  end;

var
  // Замер OWN5: сколько перезапусков компонента получили бота по прежнему адресу.
  GOwnAbaSameAddress: Integer = -1;
  GOwnAbaRestarts: Integer = 0;

function TOwnerDto.Owner: IInterface;
begin
  Result := JsonOwner;
end;

constructor TOwnerProbe.Create(AFreed: PInteger);
begin
  inherited Create;
  FFreed := AFreed;
end;

destructor TOwnerProbe.Destroy;
begin
  Inc(FFreed^);
  inherited Destroy;
end;

/// <summary>Тождество объектов за интерфейсами (канонический IInterface).</summary>
function SameIntf(const A, B: IInterface): Boolean;
begin
  Result := Assigned(A) and Assigned(B) and ((A as IInterface) = (B as IInterface));
end;

{ Хелперы TestJsonHolderIntf: временные ссылки на держателя живут до выхода
  из функции, а не до конца теста. }

/// <summary>Владелец ADto — держатель, владеющий JSON самого ADto.</summary>
function HolderOwnsValue(const ADto: IOwnerDto): Boolean;
var
  LHolder: ITgJsonHolder;
begin
  Result := Supports(ADto.Owner, ITgJsonHolder, LHolder) and (LHolder.Value = ADto.RawValue);
end;

/// <summary>Вложенный DTO над полем AName корня ARoot (владелец — держатель корня).</summary>
function NewNestedDto(const ARoot: IOwnerDto; const AName: string): IOwnerDto;
begin
  Result := TOwnerDto.Create(ARoot.Raw.GetValue(AName), ARoot.Owner);
end;

function SameOwner(const A, B: IOwnerDto): Boolean;
begin
  Result := SameIntf(A.Owner, B.Owner);
end;

/// <summary>Владелец JSON у ADto — держатель (ITgJsonHolder), а не AForeign.</summary>
function OwnerIsOwnHolder(const ADto: IOwnerDto; const AForeign: IInterface): Boolean;
var
  LOwner: IInterface;
begin
  LOwner := ADto.Owner;
  Result := Supports(LOwner, ITgJsonHolder) and not SameIntf(LOwner, AForeign);
end;

procedure TestJsonHolderIntf;
var
  LRoot, LNested, LForeign: IOwnerDto;
  LProbe: IInterface;
  LJson: TJSONObject;
  LFreed: Integer;
begin
  LRoot := TOwnerDto.Create(JsonOf('{"a":{"b":1}}'), nil);
  Check(HolderOwnsValue(LRoot), 'корень: владелец — ITgJsonHolder с JSON корня');
  // Вложенный DTO над частью JSON корня — тот же держатель (Supports, без приведения к классу).
  LNested := NewNestedDto(LRoot, 'a');
  Check(SameOwner(LNested, LRoot), 'вложенный DTO — общий держатель корня');
  Check(not HolderOwnsValue(LNested), 'держатель вложенного — корневой (JSON корня)');
  CheckEquals('{"b":1}', LNested.AsJson, 'вложенный DTO читает JSON корня');
  // Корень отпущен — вложенный удерживает держателя и JSON.
  LRoot := nil;
  CheckEquals('{"b":1}', LNested.AsJson, 'после отпускания корня JSON жив');
  LNested := nil;
  // Посторонний владелец: новый держатель удерживает его, JSON не освобождает.
  LFreed := 0;
  LJson := TJSONObject.Create;
  try
    LProbe := TOwnerProbe.Create(@LFreed);
    LForeign := TOwnerDto.Create(LJson, LProbe);
    // Отдельная функция: временные ссылки на держателя отпускаются при выходе из неё.
    Check(OwnerIsOwnHolder(LForeign, LProbe), 'посторонний владелец: создан свой держатель');
    LProbe := nil;
    CheckEquals(0, LFreed, 'посторонний владелец удерживается DTO');
    LForeign := nil;
    CheckEquals(1, LFreed, 'посторонний владелец отпущен вместе с DTO');
  finally
    // Держатель постороннего JSON им не владеет — освобождает создатель.
    LJson.Free;
  end;
end;

procedure TestOwnerLink;
const
  CReaders = 4;
var
  LObj: TObject;
  LLink: ITgOwnerLink;
  LStop, LBad, LReads, LSawNil, I: Integer;
  LThreads: array[0..CReaders - 1] of TThread;
begin
  LObj := TObject.Create;
  try
    LLink := TgNewOwnerLink(LObj);
    Check(LLink.Owner = LObj, 'Owner — владелец');
    LStop := 0;
    LBad := 0;
    LReads := 0;
    LSawNil := 0;
    for I := 0 to CReaders - 1 do
    begin
      LThreads[I] := TThread.CreateAnonymousThread(
        procedure
        var
          LSeenNil: Boolean;
          LOwner: TObject;
        begin
          LSeenNil := False;
          while AtomicCmpExchange(LStop, 0, 0) = 0 do
          begin
            LOwner := LLink.Owner;
            AtomicIncrement(LReads);
            if not Assigned(LOwner) then
            begin
              if not LSeenNil then
                AtomicIncrement(LSawNil);
              LSeenNil := True;
            end
            // Только владелец или nil; после nil владелец не возвращается.
            else if (LOwner <> LObj) or LSeenNil then
              AtomicIncrement(LBad);
          end;
        end);
      LThreads[I].FreeOnTerminate := False;
      LThreads[I].Start;
    end;
    try
      Check(WaitUntil(
        function: Boolean
        begin
          Result := AtomicCmpExchange(LReads, 0, 0) > 10000;
        end, 5000), 'читатели работают');
      LLink.Clear;
      Check(not Assigned(LLink.Owner), 'Clear → Owner = nil');
      Check(WaitUntil(
        function: Boolean
        begin
          Result := AtomicCmpExchange(LSawNil, 0, 0) = CReaders;
        end, 5000), 'все читатели увидели nil');
      LLink.Clear;
      Check(not Assigned(LLink.Owner), 'повторный Clear — nil');
    finally
      AtomicExchange(LStop, 1);
      for I := 0 to CReaders - 1 do
      begin
        LThreads[I].WaitFor;
        LThreads[I].Free;
      end;
    end;
    CheckEquals(0, LBad, 'чтения: только владелец или nil, без возврата владельца после nil');
  finally
    LLink := nil;
    LObj.Free;
  end;
end;

/// <summary>
///   Выполняет AProc в отдельном потоке и ждёт его завершения: события,
///   поставленные AProc в очередь, остаются в ней (CheckSynchronize не
///   вызывается до сигнала завершения).
/// </summary>
procedure RunInBackground(const AProc: TProc);
var
  LDone: TEvent;
  LThread: TThread;
begin
  LDone := TEvent.Create(nil, True, False, '');
  try
    LThread := TThread.CreateAnonymousThread(
      procedure
      begin
        try
          AProc();
        finally
          LDone.SetEvent;
        end;
      end);
    LThread.FreeOnTerminate := False;
    try
      LThread.Start;
      Check(LDone.WaitFor(5000) = wrSignaled, 'фоновый вызов завершён');
    finally
      LThread.WaitFor;
      LThread.Free;
    end;
  finally
    LDone.Free;
  end;
end;

/// <summary>
///   Вызывает обработчики бота (ARegistered, AFault с ETgApiError 500) из
///   фонового потока — они ставят события в очередь главного потока, — затем
///   метку 'mark' в ALog и обрабатывает очередь (CheckSynchronize) до метки
///   номер AMarks + 1.
/// </summary>
procedure PostLateEvents(ALog: TTextLog; var AMarks: Integer; const ARegistered: TProc;
  const AFault: TProc<Exception>);
var
  LExpected: Integer;
begin
  RunInBackground(
    procedure
    var
      LError: Exception;
    begin
      if Assigned(ARegistered) then
        ARegistered();
      if Assigned(AFault) then
      begin
        LError := ETgApiError.Create('stale', 500, 'stale');
        try
          AFault(LError);
        finally
          LError.Free;
        end;
      end;
      // Очередь FIFO: метка обрабатывается после поставленных выше событий.
      TThread.Queue(nil,
        procedure
        begin
          ALog.Add('mark');
        end);
    end);
  Inc(AMarks);
  LExpected := AMarks;
  Check(PumpUntil(
    function: Boolean
    begin
      Result := ALog.CountOf('mark') = LExpected;
    end, 5000), 'очередь обработана (метка ' + IntToStr(LExpected) + ')');
end;

/// <summary>
///   Поздние события старого запуска (Delivery = Main): обработчики
///   OnWebhookRegistered/OnFault прежнего бота, вызванные из фонового потока
///   после Stop → Start, ставят события в очередь; затем CheckSynchronize.
///   Событие прежнего запуска не должно сработать для нового (сверяется номер
///   запуска, а не указатель бота — новый бот часто занимает адрес прежнего).
///   Событие, поставленное в очередь до Stop, сюда не годится: Stop из
///   главного потока сам обрабатывает очередь (прежний бот ещё Stopping).
/// </summary>
procedure TestComponentGenerationABA;
const
  CRestarts = 5;
var
  LEvents: TComponentEvents;
  LTransportRef: ITgTransport;
  LBot: TTelegramBot;
  LOldRegistered, LCurrentRegistered: TProc;
  LOldFault: TProc<Exception>;
  LOldBot: Pointer;
  I, LMarks: Integer;
begin
  LMarks := 0;
  GOwnAbaSameAddress := 0;
  GOwnAbaRestarts := CRestarts;
  LEvents := TComponentEvents.Create;
  try
    LTransportRef := TScriptCancellableTransport.Create(WebhookScript(False));
    LBot := TTelegramBot.Create(nil);
    try
      LBot.Transport := LTransportRef;
      LBot.Mode := TTgReceiveMode.Webhook;
      LBot.Webhook.Url := 'https://example.org/hook';
      LBot.OnStop := LEvents.DoStop;
      LBot.OnFault := LEvents.DoFault;
      LBot.OnWebhookRegistered := LEvents.DoWebhookRegistered;
      LBot.Active := True;
      Check(PumpUntil(
        function: Boolean
        begin
          Result := LEvents.Log.CountOf('registered') = 1;
        end, 5000), 'первый запуск: OnWebhookRegistered');
      for I := 1 to CRestarts do
      begin
        // Обработчики, назначенные компонентом этому боту (его запуску).
        LOldRegistered := LBot.Bot.OnWebhookRegistered;
        LOldFault := LBot.Bot.OnFault;
        LOldBot := Pointer(LBot.Bot);
        LBot.Active := False;
        LBot.Active := True;
        if Pointer(LBot.Bot) = LOldBot then
          Inc(GOwnAbaSameAddress);
        Check(PumpUntil(
          function: Boolean
          begin
            Result := LEvents.Log.CountOf('registered') = I + 1;
          end, 5000), Format('перезапуск %d: OnWebhookRegistered нового бота', [I]));
        PostLateEvents(LEvents.Log, LMarks, LOldRegistered, LOldFault);
        CheckEquals(I + 1, LEvents.Log.CountOf('registered'),
          Format('перезапуск %d: OnWebhookRegistered прежнего запуска не вызван', [I]));
        // OnFault прежнего запуска доставляется, как и раньше (ошибка была),
        // но новый бот не останавливается и OnStop(Fault) не вызывается.
        CheckEquals(I, LEvents.Log.CountOf('fault 500'),
          Format('перезапуск %d: OnFault прежнего запуска доставлен', [I]));
        CheckEquals(0, LEvents.Log.CountOf('stop fault'),
          Format('перезапуск %d: OnStop(Fault) от прежнего запуска не вызван', [I]));
        Check(LBot.Active and (LBot.State = TTgBotState.Running),
          Format('перезапуск %d: новый бот работает', [I]));
      end;
      CheckEquals(CRestarts, LEvents.Log.CountOf('stop requested'), 'OnStop(Requested) — по разу на Stop');
      // Контроль: обработчик текущего запуска через ту же очередь срабатывает.
      LCurrentRegistered := LBot.Bot.OnWebhookRegistered;
      PostLateEvents(LEvents.Log, LMarks, LCurrentRegistered, nil);
      CheckEquals(CRestarts + 2, LEvents.Log.CountOf('registered'),
        'обработчик текущего запуска — событие доставлено');
      CheckEquals(0, LEvents.NotMain, 'события — в главном потоке');
      LBot.Active := False;
    finally
      LBot.Free;
    end;
    // Компонент освобождён: связь отцеплена, поздний обработчик — без события и без AV.
    PostLateEvents(LEvents.Log, LMarks, LCurrentRegistered, LOldFault);
    CheckEquals(CRestarts + 2, LEvents.Log.CountOf('registered'), 'после Free — OnWebhookRegistered не вызван');
    CheckEquals(CRestarts, LEvents.Log.CountOf('fault 500'), 'после Free — OnFault не вызван');
  finally
    LEvents.Free;
  end;
end;

procedure RunAll;
begin
  Writeln('TgBot ', TgBotVersion, ' (Bot API ', TgBotApiVersion, ') — офлайн-тесты');
  // Первым: замер памяти точнее, пока нет фоновых потоков других тестов.
  RunTest('Заглушка TFakeTransport: 8 потоков, память не растёт', TestFakeTransportConcurrency);
  // Долгое воспроизведение — только явно: TG_ONLY=STRESS.
  if GetEnvironmentVariable('TG_ONLY') <> '' then
    RunTest('STRESS TFakeTransport: 8 потоков x 100000', TestFakeTransportStress);
  RunTest('Разбор Update: кириллица, entities, reply_to_message, Int64', TestUpdateParsing);
  RunTest('ChatMember: Kind/As*/Supports/Unknown/KindText', TestChatMember);
  RunTest('MaybeInaccessibleMessage: date = 0', TestMaybeInaccessibleMessage);
  RunTest('RichText: строка, массив, неизвестный вид', TestRichText);
  RunTest('With*: нет use-after-free (InlineKeyboard, MessageEntity.WithUser)', TestWithUseAfterFree);
  RunTest('InlineKeyboardMarkup: фабрика/With → JSON → FromJson', TestInlineKeyboardRoundTrip);
  RunTest('sendMediaGroup: 2 файла и attach://', TestSendMediaGroup);
  RunTest('Опции-массивы: [] отправляется, незаданное — нет', TestOptionsArrays);
  RunTest('Async: параметры синхронно, ошибки проверки сразу, AOnError', TestAsync);
  RunTest('Деструктор ждёт Async; владение транспортом; Settings', TestDestructorWaitsAsync);
  RunTest('TrySendMessage с ошибкой API', TestTrySendMessageApiError);
  RunTest('edit-метод: ответ true → nil', TestEditReturnsTrue);
  RunTest('Локаль с запятой, NaN/Infinity → ETgError', TestLocaleAndNaN);
  RunTest('Clone/Detach', TestCloneDetach);
  RunTest('Ядро: GetMe, CallJson, DownloadFile, язык, версия', TestCoreMisc);
  RunTest('5b-1: DTO над JSON-массивом — DtoNotObject с именем поля (SetStr, AppendRow; RU/EN)',
    TestDtoNotObjectField);
  RunTest('5b-1: тексты TTgText/TTgUpdatesText/TTgRouterText и пары TgBot.Consts — ' +
    'непусты, RU ≠ EN, спецификаторы совпадают', TestTextsComplete);
  RunTest('Варианты edit-методов: позиционные, inline → Boolean, chat_id любого вида', TestEditVariants);
  RunTest('Варианты answerCallbackQuery/sendMessage/sendPhoto/sendDocument', TestSendAndAnswerVariants);
  RunTest('Варианты: Async и Try', TestVariantsAsyncAndTry);
  RunTest('Построители клавиатур: Inline, Reply, Remove, ForceReply, TgRow → JSON', TestKeyboardBuilders);
  RunTest('Токены отмены: Cancel, Register, отписка, связанные, Linked, WaitFor', TestCancellationTokens);
  RunTest('Владение: ITgCancellationSource — New, Cancel, связанные, отписка, ' +
    'стресс 4 потока x 10000, кнопка Cancel', TestCancellationSourceOwnership);
  RunTest('TTgCancelScope: вложенность и разные потоки', TestCancelScope);
  RunTest('Call: окружающий и явный токен, транспорт без токенов', TestCallCancellation);
  RunTest('HTTP-транспорт: retry_after и лимитёр прерываются токеном; Cancel/ResetCancel',
    TestTransportWaitsCancel);
  RunTest('409 → ETgConflictError', TestConflict409);
  RunTest('Destroy при 10 висящих Async; общий транспорт исправен', TestDestroyWithHangingAsync);
  RunTest('Шлюз Async: пул пользователя, задачи после закрытия не выполняются', TestGateWithUserPool);
  RunTest('Async — в пуле библиотеки; TgSetAsyncPoolSize', TestLibraryPool);
{$IFDEF MSWINDOWS}
  RunTest('Реальный THTTPClient: отмена висящего запроса и Destroy', TestRealHttpCancel);
{$ENDIF}
  RunTest('ITgRawUpdate: Kind и ChatKey для видов обновлений', TestRawUpdateKeys);
  RunTest('Long polling: Stop при висящем getUpdates', TestPollStopHanging);
  RunTest('Long polling: неотменяемый транспорт — поток отпущен, поздний пакет выброшен',
    TestPollAbandon);
  RunTest('Long polling: AfterReceive/AfterBatch, дренаж и итоговое подтверждение', TestPollAckPolicies);
  RunTest('Long polling: паузы 1→2→4, разброс, 409 webhook/other, 401/404', TestPollErrors);
  RunTest('Диспетчер: 100 обновлений на 5 чатов, MaxParallel = 4', TestDispatcherOrder);
  RunTest('Диспетчер: исключение → OnError, цикл жив', TestDispatcherErrors);
  RunTest('Диспетчер: Delivery = Main (CheckSynchronize), Stop без блокировки', TestDeliveryMain);
  RunTest('TTgMemoryStateStorage: API и 8 потоков', TestStateStorage);
  RunTest('TTgBot: message + callback_query, Reply/Answer/Edit/State', TestBotEndToEnd);
  RunTest('TTgBot.Run: Delivery = Main, RequestStop; TTgShutdownSignal', TestBotRunMain);
  RunTest('TTgBot: allowed_updates по умолчанию [], явный список, предупреждение', TestBotAllowedUpdates);
  RunTest('TTgApi.Shutdown: идемпотентен, Call → ETgCancelledError, Async → AOnError', TestApiShutdown);
  RunTest('TTgBot.Free при зависшем обработчике: быстро, Api → ETgCancelledError, без OnError',
    TestBotFreeWithHangingHandler);
  RunTest('ITgContext переживает TTgBot: Text/State/Api, вызовы → ETgCancelledError ' +
    '(владение, фаза 3: Api через ITgApiOwner ядра, ядро освобождается с контекстом)',
    TestBotContextOutlivesBot);
  RunTest('Владение, фаза 3: смена StateStorage на ходу — контекст работает со своим снимком',
    TestContextStateStorageSnapshot);
  RunTest('TTgBot: OnMessage переназначается на ходу 10000 раз', TestBotHandlerSwap);
  RunTest('Free диспетчера при зависшем обработчике (без Stop и после Stop = False) < 100 мс',
    TestDispatcherFreeNonBlocking);
  RunTest('Free источника при висящем getUpdates (без Stop и после Stop = False) < 100 мс',
    TestSourceFreeNonBlocking);
  RunTest('Delivery = Main: Free/Stop при заданиях в очереди — сняты без CheckSynchronize',
    TestDeliveryMainOrphans);
  RunTest('TTgBot: 401 → Faulted, Active = False, OnError затем OnFault (один раз), дообработка',
    TestBotFaultState);
  RunTest('TTgBot: после Faulted — Stop → Idle и Start; Start без Stop; Free в Faulted',
    TestBotFaultRestart);
  RunTest('TTgBot.Run при Faulted: < 1 с, без исключения, False', TestBotRunFaulted);
  RunTest('TTgBot.State: Idle → Running → Stopping → Idle', TestBotStateTransitions);
  RunTest('Маршрутизатор: команды (@бот, регистр, Args, синонимы, Unknown), Text/TextMatch, ' +
    'Handled, OnMessage, getMe/setMyCommands', TestRouterMessages);
  RunTest('Маршрутизатор: Callback/CallbackPrefix, OnCallbackQuery, AutoAnswer, ленивый getMe',
    TestRouterCallbacks);
  RunTest('Маршрутизатор: ошибки getMe/setMyCommands → OnError, бот работает; SetMyCommandsOnStart',
    TestRouterStartErrors);
  RunTest('Маршрутизатор: проверка ключей, Self, удаление (nil)', TestRouterValidation);
  RunTest('Маршрутизатор: регистрация на ходу из другого потока (3000 раз)', TestRouterLiveRegistration);
  RunTest('Компонент: свойства, коллекция команд, события of object, регистрации между запусками',
    TestComponentBasics);
  RunTest('Компонент: Active из формы — отложенный запуск после Loaded, ошибка → OnError, дизайнер',
    TestComponentLoaded);
  RunTest('Компонент: OnError/OnFault/OnStop(Fault) при Delivery = Main — через очередь', TestComponentFaultQueued);
  RunTest('Компонент: Start не ждёт getMe/setMyCommands (getMe 2 с)', TestComponentStartNonBlocking);
  RunTest('Компонент: Free при зависшем обработчике — события формы не вызываются', TestComponentDestroyHanging);
  RunTest('Webhook: setWebhook при Start, секрет, HandleWebhook (403/400/дубль/лимит), Stop, новый секрет',
    TestWebhookBasics);
  RunTest('Webhook: переполнение очереди → Unavailable < 1 с, повтор принят', TestWebhookQueueFull);
  RunTest('Webhook: ошибка setWebhook → Faulted/OnFault; DeleteWebhookOnStop; проверки; генератор секрета',
    TestWebhookFaultAndOptions);
  RunTest('Компонент: Mode/Webhook, Server (Register/Unregister, URL, Notification), HandleWebhook',
    TestComponentWebhook);
  RunTest('TTgWebhookServer (Indy): 200/403/400/404/405/413, 2 бота, занятый путь и порт, Free сервера',
    TestWebhookServer);
  RunTest('6E2: TgHtmlEscape и TgMarkdownV2Escape', TestEscapeHelpers);
  RunTest('6E2: TTelegramBot.Run — RequestStop из другого потока < 1 с, Faulted → False, Main не из главного → ETgError',
    TestComponentRun);
  RunTest('6E2: путь webhook без Name/Path, https у WebhookUrl/PublicUrl, Local Bot API, RegisterClasses',
    TestWebhookUrlAndPathChecks);
  RunTest('6E2: 401 при getMe/setMyCommands/setWebhook — один OnError и один OnFault; тишина после Faulted',
    TestStartJobAfterFault);
  RunTest('Владение, фаза 2: Free при висящем getMe (отменяемый и неотменяемый транспорт) — ' +
    'ожидание подготовки ≈0,5 с, не бюджет Stop; ядро освобождается после задачи',
    TestStartJobFreeHangingGetMe);
  RunTest('Free бота: явный Stop(300) при висящем getMe ждёт подготовку в своём бюджете ≈300 мс',
    TestStartJobStopBudget);
  RunTest('Free бота: TTelegramBot.Free при висящем getMe — не дольше 1,5 с',
    TestComponentFreeHangingGetMe);
  RunTest('Владение, фаза 2: Stop(50) при висящих getMe/setMyCommands, сразу Start — ' +
    'поздние ответы старых задач не трогают новую', TestStartJobRestartLateReply);
  RunTest('Владение, фаза 2: обработчик /cmd@бот ждёт username, Stop и Free — выход без AV',
    TestStartJobHandlerWaitsName);
  RunTest('Владение, фаза 2: 200 циклов Start/Stop/Free, getMe 0–50 мс — без утечек',
    TestStartJobChurn);
  RunTest('6E2: компонент, 401 с командами — один OnError, один OnFault, OnStop(Fault)',
    TestComponentStartJobFault);
  RunTest('6E2: OnWebhookRegistered — TTgBot в фоне, компонент OnStart → событие в главном потоке',
    TestWebhookRegisteredEvent);
  RunTest('6E2: Ctx.Edit — «message is not modified» → False, сырые Api — исключение', TestContextEditNotModified);
  RunTest('6E2: Webhook.IpAddress и Certificate → setWebhook (ip_address, certificate multipart)',
    TestComponentWebhookCertificate);
  RunTest('Владение, фаза 5: ITgJsonHolder — общий держатель вложенных DTO, посторонний владелец',
    TestJsonHolderIntf);
  RunTest('Владение, фаза 5: ITgOwnerLink — Clear → Owner = nil, чтение из 4 потоков',
    TestOwnerLink);
  RunTest('Владение, фаза 5: компонент (Main) — поздние события старого запуска после ' +
    'Stop → Start не срабатывают для нового (номер запуска, а не указатель)',
    TestComponentGenerationABA);
{$IFDEF MSWINDOWS}
  RunTest('Завершение процесса при висящих обработчиках: < 2 с, код 0',
    TestProcessExitWithHangingHandlers);
{$ENDIF}
{$IFDEF MSWINDOWS}
  RunTest('DownloadFile: отмена висящего GET и гонка отмены', TestDownloadCancelRace);
{$ENDIF}
  Writeln;
  Writeln(Format('Замеры, мс: WaitFor после Cancel(50 мс) = %d; Destroy (10 висящих) = %d; ' +
    'Destroy (пул пользователя) = %d; реальный HTTP: вызов = %d (Cancel через 300), Destroy = %d',
    [GWaitWakeMs, GDestroyHangingMs, GDestroyUserPoolMs, GRealHttpCancelMs, GRealHttpDestroyMs]));
  Writeln(Format('Замеры 5B, мс: Stop (висящий getUpdates) = %d; Stop (отпускание) = %d; ' +
    'Stop диспетчера (Main) = %d; TTgBot.Stop = %d; TTgBot.Run = %d; DownloadFile Cancel = %d, ' +
    'гонка max = %d; параллельно обработчиков = %d',
    [GStopHangingMs, GStopAbandonMs, GDispatcherMainStopMs, GBotStopMs, GBotRunMs,
    GDownloadCancelMs, GDownloadRaceMaxMs, GMaxConcurrency]));
  Writeln(Format('Замеры 6A2: TTgBot.Free (зависший обработчик) = %d мс; прирост блоков ' +
    '(10000 переназначений) = %d', [GBotFreeHangingMs, GHandlerSwapGrowth]));
  Writeln(Format('Замеры 6A3, мс: Free диспетчера (зависший обработчик) = %d, после Stop = False = %d; ' +
    'Free источника (висящий запрос) = %d, после Stop = False = %d; Free (Main, очередь) = %d; ' +
    'выход процесса с висящими обработчиками = %d',
    [GDispatcherFreeHangingMs, GDispatcherFreeAfterStopMs, GSourceFreeHangingMs,
    GSourceFreeAfterStopMs, GMainOrphanFreeMs, GExitHangMs]));
  Writeln(Format('Замеры 6A4, мс: Run при Faulted = %d; Stop из Faulted = %d; Free в Faulted = %d',
    [GRunFaultedMs, GStopFaultedMs, GFreeFaultedMs]));
  Writeln(Format('Замеры 6B1: прирост блоков (3000 перерегистраций правил) = %d', [GRouteSwapGrowth]));
  Writeln(Format('Замеры 6B2, мс: TTelegramBot.Active := True (getMe 2 с) = %d; Free (зависший обработчик) = %d',
    [GCompStartMs, GCompFreeHangMs]));
  Writeln(Format('Замеры 6D1, мс: HandleWebhook при переполнении очереди = %d', [GWebhookOverflowMs]));
  Writeln(Format('Замеры 6D2, мс: POST на TTgWebhookServer = %d; ответ 413 = %d',
    [GServerPostMs, GServer413Ms]));
  Writeln(Format('Замеры 6E2, мс: TTelegramBot.Run после RequestStop (Main) = %d, (Worker) = %d; ' +
    'Run при отказе = %d', [GCompRunStopMs, GCompRunWorkerStopMs, GCompRunFaultMs]));
  Writeln(Format('Замеры OWN2, мс: Free при висящем getMe (отменяемый) = %d, (неотменяемый) = %d ' +
    '(ожидание подготовки при Free = %d); 200 циклов Start/Stop/Free = %d; счётчики живых объектов: %s',
    [GOwnFreeCancellableMs, GOwnFreePlainMs, TgDefaultBotFreeStartJobWaitMs, GOwnChurnMs,
    {$IFDEF TGBOT_TESTHOOKS}'включены'{$ELSE}'выключены (без TGBOT_TESTHOOKS)'{$ENDIF}]));
  Writeln(Format('Замеры FREEWAIT, мс: Stop(300) при висящем getMe = %d; ' +
    'TTelegramBot.Free при висящем getMe = %d', [GFreeWaitStopMs, GFreeWaitCompMs]));
  Writeln(Format('Замеры OWN5: новый бот по адресу прежнего — %d из %d перезапусков',
    [GOwnAbaSameAddress, GOwnAbaRestarts]));
  Writeln(Format('Тестов: %d, не прошло: %d; проверок: %d, ошибок: %d',
    [GTests, GTestsFailed, GPassed + GFailed, GFailed]));
  if GFailed > 0 then
    ExitCode := 1;
end;

begin
{$IFDEF MSWINDOWS}
  // Дочерний процесс теста завершения: висящие потоки намеренно не
  // освобождаются, поэтому отчёт об утечках здесь не включается.
  if ParamStr(1) = CExitHangSwitch then
  begin
    try
      ExitCode := RunExitHangChild;
    except
      ExitCode := 2;
    end;
    Exit;
  end;
{$ENDIF}
  ReportMemoryLeaksOnShutdown := True;
{$IFDEF MSWINDOWS}
  SetConsoleOutputCP(CP_UTF8);
  SetTextCodePage(Output, CP_UTF8);
{$ENDIF}
  try
    RunAll;
  except
    on E: Exception do
    begin
      Writeln('Необработанное исключение: ', E.ClassName, ': ', E.Message);
      ExitCode := 2;
    end;
  end;
end.
