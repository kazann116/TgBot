unit TgBot.Context;

{
  TgBot — контекст обработчика обновления: интерфейс ITgContext и его
  реализация (ответы Reply/ReplyHtml/Answer/Edit, состояние диалога, поля
  маршрутизатора Command/Args/Handled).

  Указывать этот модуль в uses не нужно: TgBot реэкспортирует ITgContext
  псевдонимом. ITgApiOwner, ITgRoutableContext и фабрика TgNewContext —
  служебные (ими пользуются ядро TTgBot и маршрутизатор), не часть
  публичного API библиотеки; класс реализации — в implementation.
}

{$SCOPEDENUMS ON}

interface

uses
  TgBot.Base,
  TgBot.Types,
  TgBot.Updates,
  TgBot.State;

type
  /// <summary>
  ///   Контекст обработки одного обновления (TTgBot.OnUpdate/OnMessage/
  ///   OnCallbackQuery). Используйте только внутри обработчика и в его потоке.
  ///
  ///   Сообщение обновления (Message) — message, edited_message, channel_post,
  ///   edited_channel_post, business_message, edited_business_message,
  ///   guest_message или message из callback_query (если доступно).
  ///   Text — текст (или подпись) этого сообщения; для callback_query —
  ///   callback data (то же, что Data); для inline_query и
  ///   chosen_inline_result — query; иначе ''. Data — только callback data.
  ///
  ///   Вызовы Api внутри обработчика прерываются при остановке бота (Cancel —
  ///   окружающий токен обработчика).
  /// </summary>
  ITgContext = interface
    ['{49678079-CCCC-45F5-A4ED-8064A44C34EA}']
    function GetUpdate: ITgUpdate;
    function GetRaw: ITgRawUpdate;
    function GetKind: string;
    function GetApi: TTgApi;
    function GetCancel: ITgCancellation;
    function GetChatId: TTgChatId;
    function GetFrom: ITgUser;
    function GetMessage: ITgMessage;
    function GetText: string;
    function GetData: string;
    function GetStateKey: string;
    function GetState(const AName: string): string;
    procedure SetState(const AName, AValue: string);
    /// <summary>
    ///   Отправляет сообщение в чат обновления (в той же теме форума и том же
    ///   бизнес-подключении). Нет чата — ETgError.
    /// </summary>
    function Reply(const AText: string): ITgMessage; overload;
    /// <summary>Reply с клавиатурой (TTgKeyboard.Inline/Reply/Remove/ForceReply).</summary>
    function Reply(const AText: string; const AKeyboard: TTgReplyMarkup): ITgMessage; overload;
    /// <summary>Reply с parse_mode = HTML.</summary>
    function ReplyHtml(const AText: string): ITgMessage; overload;
    /// <summary>ReplyHtml с клавиатурой.</summary>
    function ReplyHtml(const AText: string; const AKeyboard: TTgReplyMarkup): ITgMessage; overload;
    /// <summary>
    ///   answerCallbackQuery для callback_query (AText — уведомление, AShowAlert —
    ///   окном). Обновление другого вида — False без запроса.
    /// </summary>
    function Answer(const AText: string = ''; AShowAlert: Boolean = False): Boolean;
    /// <summary>
    ///   Меняет текст сообщения с нажатой кнопкой (callback_query): обычное
    ///   сообщение — editMessageText(chat_id, message_id), inline —
    ///   editMessageText(inline_message_id). Не callback_query или нет
    ///   сообщения — False без запроса; ответ 400 «message is not modified»
    ///   (текст и клавиатура не изменились, например повторное нажатие) —
    ///   False без исключения; другая ошибка Bot API — исключение.
    ///   Без AKeyboard инлайн-клавиатура сообщения убирается (так Bot API
    ///   обрабатывает отсутствие reply_markup).
    /// </summary>
    function Edit(const AText: string): Boolean; overload;
    /// <summary>Edit с новой инлайн-клавиатурой (nil — клавиатура убирается).</summary>
    function Edit(const AText: string; const AKeyboard: ITgInlineKeyboardMarkup): Boolean; overload;
    /// <summary>Удаляет все значения состояния StateKey.</summary>
    procedure ClearState;
    function GetCommand: string;
    function GetArgs: string;
    function GetHandled: Boolean;
    procedure SetHandled(AValue: Boolean);
    /// <summary>
    ///   Команда сообщения без '/' и '@бот', в нижнем регистре ('/Start@MyBot a'
    ///   → 'start'); '' — не команда или команда другому боту. Заполняется до
    ///   OnUpdate.
    /// </summary>
    property Command: string read GetCommand;
    /// <summary>
    ///   Аргументы сработавшего правила: текст после команды (без крайних
    ///   пробелов), первая группа TextMatch (нет групп — всё совпадение),
    ///   остаток callback data после префикса CallbackPrefix; иначе ''.
    /// </summary>
    property Args: string read GetArgs;
    /// <summary>
    ///   Обновление обработано: дальнейшие правила, OnMessage и OnCallbackQuery
    ///   не вызываются. OnUpdate может выставить True (перехват); правило
    ///   маршрутизатора выставляет True перед вызовом своего обработчика —
    ///   обработчик может сбросить в False, чтобы обработка шла дальше.
    /// </summary>
    property Handled: Boolean read GetHandled write SetHandled;
    /// <summary>Обновление (типизированное; разделяет JSON с Raw).</summary>
    property Update: ITgUpdate read GetUpdate;
    /// <summary>Обновление в сыром виде.</summary>
    property Raw: ITgRawUpdate read GetRaw;
    /// <summary>Вид обновления (TTgUpdateType.*).</summary>
    property Kind: string read GetKind;
    /// <summary>Клиент Bot API бота.</summary>
    property Api: TTgApi read GetApi;
    /// <summary>Токен отмены обработчика (отменяется при остановке бота).</summary>
    property Cancel: ITgCancellation read GetCancel;
    /// <summary>Чат обновления; пусто (IsEmpty), если чата нет (inline_query и т.п.).</summary>
    property ChatId: TTgChatId read GetChatId;
    /// <summary>Автор: from (или user) полезной нагрузки; nil, если нет (посты каналов).</summary>
    property From: ITgUser read GetFrom;
    /// <summary>Сообщение обновления или nil (см. описание интерфейса).</summary>
    property Message: ITgMessage read GetMessage;
    /// <summary>Текст (см. описание интерфейса).</summary>
    property Text: string read GetText;
    /// <summary>callback data (только callback_query), иначе ''.</summary>
    property Data: string read GetData;
    /// <summary>Ключ состояния 'чат:пользователь' (пустая часть, если её нет).</summary>
    property StateKey: string read GetStateKey;
    /// <summary>
    ///   Значение состояния диалога (ключ StateKey); '' — нет значения.
    ///   Присваивание '' удаляет значение.
    /// </summary>
    property State[const AName: string]: string read GetState write SetState;
  end;

  /// <summary>
  ///   Служебное: владелец клиента Bot API (ядро бота, TgBot.Bot.Core).
  ///   Контекст обработчика удерживает владельца этой ссылкой: клиент
  ///   действителен, пока жив контекст, даже после Free бота (вызовы
  ///   клиента тогда — ETgCancelledError). Не часть публичного API
  ///   библиотеки.
  /// </summary>
  ITgApiOwner = interface
    ['{5FA06BA5-E929-437A-9A85-0E178027B7E3}']
    function GetApi: TTgApi;
    /// <summary>Клиент Bot API (во владении; не меняется за жизнь владельца).</summary>
    property Api: TTgApi read GetApi;
  end;

  /// <summary>
  ///   Служебное: контекст со стороны ядра бота и маршрутизатора (TTgRouter,
  ///   TgBot.Router) — заполнение Command/Args, текст для разбора команды,
  ///   признак ответа на нажатие для автоответа. Обработчики получают
  ///   ITgContext; не часть публичного API библиотеки.
  /// </summary>
  ITgRoutableContext = interface(ITgContext)
    ['{E951376C-E55F-40D3-8686-8F94D6F820E8}']
    /// <summary>Ключ разобранной команды (TTgRouter.ParseCommand по вызову ядра).</summary>
    procedure SetCommand(const AValue: string);
    /// <summary>Аргументы сработавшего правила (TTgRouter по вызову ядра).</summary>
    procedure SetArgs(const AValue: string);
    /// <summary>Поле text сообщения вида message ('' — нет текста или другой вид).</summary>
    function MessageText: string;
    function GetAnswered: Boolean;
    /// <summary>Вызван Answer (для автоматического ответа на callback_query).</summary>
    property Answered: Boolean read GetAnswered;
  end;

/// <summary>
///   Служебное (вызывает ядро бота): контекст обновления ARaw. AApiOwner —
///   владелец клиента (удерживается контекстом); ACancel — токен
///   обработчика; AStorage — снимок хранилища состояния на начало обработки
///   (смена StateStorage на ходу этот контекст не затрагивает).
/// </summary>
function TgNewContext(const AApiOwner: ITgApiOwner; const ARaw: ITgRawUpdate;
  const ACancel: ITgCancellation; const AStorage: ITgStateStorage): ITgRoutableContext;

implementation

uses
  System.SysUtils,
  System.JSON,
  TgBot.Json;

type
  /// <summary>
  ///   Реализация ITgContext и ITgRoutableContext. Поля читаются из сырого
  ///   JSON обновления; типизированные объекты (Update, From, Message)
  ///   разделяют этот JSON и удерживают обновление. FApiOwner удерживает
  ///   владельца клиента (ядро бота), пока жив контекст: Api действителен,
  ///   пока жив контекст, даже после Free бота.
  /// </summary>
  TTgContext = class(TInterfacedObject, ITgContext, ITgRoutableContext)
  private
    FApiOwner: ITgApiOwner;
    FRaw: ITgRawUpdate;
    FCancel: ITgCancellation;
    FStorage: ITgStateStorage;
    FPayload: TJSONObject;
    FUpdate: ITgUpdate;
    FAnswered: Boolean;
    // Маршрутизатор (заполняет TTgRouter в потоке обработчика).
    FCommand: string;
    FArgs: string;
    FHandled: Boolean;
    function IsCallback: Boolean;
    function MessageJson: TJSONObject;
    function ChatJson: TJSONObject;
    function UserJson: TJSONObject;
    function SendText(const AText, AParseMode: string; const AKeyboard: TTgReplyMarkup): ITgMessage;
    function EditText(const AText: string; const AKeyboard: ITgInlineKeyboardMarkup): Boolean;
  public
    /// <summary>AApiOwner — владелец клиента (удерживается контекстом).</summary>
    constructor Create(const AApiOwner: ITgApiOwner; const ARaw: ITgRawUpdate;
      const ACancel: ITgCancellation; const AStorage: ITgStateStorage);
    function GetUpdate: ITgUpdate;
    function GetRaw: ITgRawUpdate;
    function GetKind: string;
    function GetApi: TTgApi;
    function GetCancel: ITgCancellation;
    function GetChatId: TTgChatId;
    function GetFrom: ITgUser;
    function GetMessage: ITgMessage;
    function GetText: string;
    function GetData: string;
    function GetStateKey: string;
    function GetState(const AName: string): string;
    procedure SetState(const AName, AValue: string);
    function Reply(const AText: string): ITgMessage; overload;
    function Reply(const AText: string; const AKeyboard: TTgReplyMarkup): ITgMessage; overload;
    function ReplyHtml(const AText: string): ITgMessage; overload;
    function ReplyHtml(const AText: string; const AKeyboard: TTgReplyMarkup): ITgMessage; overload;
    function Answer(const AText: string = ''; AShowAlert: Boolean = False): Boolean;
    function Edit(const AText: string): Boolean; overload;
    function Edit(const AText: string; const AKeyboard: ITgInlineKeyboardMarkup): Boolean; overload;
    procedure ClearState;
    function GetCommand: string;
    function GetArgs: string;
    function GetHandled: Boolean;
    procedure SetHandled(AValue: Boolean);
    { ITgRoutableContext }
    procedure SetCommand(const AValue: string);
    procedure SetArgs(const AValue: string);
    function MessageText: string;
    function GetAnswered: Boolean;
  end;

const
  // Виды обновлений, полезная нагрузка которых — сообщение.
  CMessageKinds: array[0..6] of string = (TTgUpdateType.Message, TTgUpdateType.EditedMessage,
    TTgUpdateType.ChannelPost, TTgUpdateType.EditedChannelPost, TTgUpdateType.BusinessMessage,
    TTgUpdateType.EditedBusinessMessage, TTgUpdateType.GuestMessage);

/// <summary>Id объекта (chat/user) строкой; '' — нет объекта или id.</summary>
function JsonIdText(AObj: TJSONObject): string;
begin
  if TTgJson.Has(AObj, 'id') then
    Result := IntToStr(TTgJson.GetInt64(AObj, 'id'))
  else
    Result := '';
end;

function TgNewContext(const AApiOwner: ITgApiOwner; const ARaw: ITgRawUpdate;
  const ACancel: ITgCancellation; const AStorage: ITgStateStorage): ITgRoutableContext;
begin
  Result := TTgContext.Create(AApiOwner, ARaw, ACancel, AStorage);
end;

{ TTgContext }

constructor TTgContext.Create(const AApiOwner: ITgApiOwner; const ARaw: ITgRawUpdate;
  const ACancel: ITgCancellation; const AStorage: ITgStateStorage);
begin
  inherited Create;
  FApiOwner := AApiOwner;
  FRaw := ARaw;
  FCancel := ACancel;
  FStorage := AStorage;
  FPayload := TTgJson.GetObj(ARaw.Json, ARaw.Kind);
end;

function TTgContext.IsCallback: Boolean;
begin
  Result := FRaw.Kind = TTgUpdateType.CallbackQuery;
end;

function TTgContext.MessageJson: TJSONObject;
var
  LKind: string;
begin
  if IsCallback then
    Exit(TTgJson.GetObj(FPayload, 'message'));
  for LKind in CMessageKinds do
    if FRaw.Kind = LKind then
      Exit(FPayload);
  Result := nil;
end;

function TTgContext.ChatJson: TJSONObject;
var
  LMessage: TJSONObject;
begin
  LMessage := MessageJson;
  if Assigned(LMessage) then
    Result := TTgJson.GetObj(LMessage, 'chat')
  else
    Result := TTgJson.GetObj(FPayload, 'chat');
end;

function TTgContext.UserJson: TJSONObject;
begin
  Result := TTgJson.GetObj(FPayload, 'from');
  if not Assigned(Result) then
    Result := TTgJson.GetObj(FPayload, 'user');
end;

function TTgContext.GetUpdate: ITgUpdate;
begin
  // Без копии JSON: DTO удерживает сырое обновление (владельца JSON).
  if not Assigned(FUpdate) then
    FUpdate := TgMakeUpdate(FRaw.Json, FRaw);
  Result := FUpdate;
end;

function TTgContext.GetRaw: ITgRawUpdate;
begin
  Result := FRaw;
end;

function TTgContext.GetKind: string;
begin
  Result := FRaw.Kind;
end;

function TTgContext.GetApi: TTgApi;
begin
  Result := FApiOwner.Api;
end;

function TTgContext.GetCancel: ITgCancellation;
begin
  Result := FCancel;
end;

function TTgContext.GetChatId: TTgChatId;
var
  LChat: TJSONObject;
begin
  LChat := ChatJson;
  if TTgJson.Has(LChat, 'id') then
    Result := TTgChatId.FromId(TTgJson.GetInt64(LChat, 'id'))
  else
    Result := Default(TTgChatId);
end;

function TTgContext.GetFrom: ITgUser;
var
  LUser: TJSONObject;
begin
  LUser := UserJson;
  if Assigned(LUser) then
    Result := TgMakeUser(LUser, FRaw)
  else
    Result := nil;
end;

function TTgContext.GetMessage: ITgMessage;
var
  LMessage: TJSONObject;
begin
  LMessage := MessageJson;
  // Недоступное сообщение callback_query (date = 0) — не Message.
  if not Assigned(LMessage) or (IsCallback and (TTgJson.GetInt64(LMessage, 'date') = 0)) then
    Exit(nil);
  Result := TgMakeMessage(LMessage, FRaw);
end;

function TTgContext.GetText: string;
var
  LMessage: TJSONObject;
begin
  if IsCallback then
    Exit(TTgJson.GetStr(FPayload, 'data'));
  if (FRaw.Kind = TTgUpdateType.InlineQuery) or (FRaw.Kind = TTgUpdateType.ChosenInlineResult) then
    Exit(TTgJson.GetStr(FPayload, 'query'));
  LMessage := MessageJson;
  Result := TTgJson.GetStr(LMessage, 'text');
  if Result = '' then
    Result := TTgJson.GetStr(LMessage, 'caption');
end;

function TTgContext.GetData: string;
begin
  if IsCallback then
    Result := TTgJson.GetStr(FPayload, 'data')
  else
    Result := '';
end;

function TTgContext.GetStateKey: string;
begin
  Result := JsonIdText(ChatJson) + ':' + JsonIdText(UserJson);
end;

function TTgContext.GetState(const AName: string): string;
begin
  if not FStorage.TryGet(GetStateKey, AName, Result) then
    Result := '';
end;

procedure TTgContext.SetState(const AName, AValue: string);
begin
  if AValue = '' then
    FStorage.Delete(GetStateKey, AName)
  else
    FStorage.Put(GetStateKey, AName, AValue);
end;

procedure TTgContext.ClearState;
begin
  FStorage.Delete(GetStateKey);
end;

function TTgContext.GetCommand: string;
begin
  Result := FCommand;
end;

function TTgContext.GetArgs: string;
begin
  Result := FArgs;
end;

function TTgContext.GetHandled: Boolean;
begin
  Result := FHandled;
end;

procedure TTgContext.SetHandled(AValue: Boolean);
begin
  FHandled := AValue;
end;

procedure TTgContext.SetCommand(const AValue: string);
begin
  FCommand := AValue;
end;

procedure TTgContext.SetArgs(const AValue: string);
begin
  FArgs := AValue;
end;

function TTgContext.MessageText: string;
begin
  if FRaw.Kind = TTgUpdateType.Message then
    Result := TTgJson.GetStr(FPayload, 'text')
  else
    Result := '';
end;

function TTgContext.GetAnswered: Boolean;
begin
  Result := FAnswered;
end;

function TTgContext.SendText(const AText, AParseMode: string;
  const AKeyboard: TTgReplyMarkup): ITgMessage;
var
  LChat: TTgChatId;
  LOptions: TTgSendMessageOptions;
  LMessage: TJSONObject;
  LBusiness: string;
begin
  LChat := GetChatId;
  if LChat.IsEmpty then
    raise ETgError.Create(TgUpdatesText(TTgUpdatesText.NoChat));
  LOptions := Default(TTgSendMessageOptions);
  LMessage := MessageJson;
  // Ответ — в то же бизнес-подключение и ту же тему форума.
  LBusiness := TTgJson.GetStr(LMessage, 'business_connection_id');
  if LBusiness <> '' then
    LOptions.BusinessConnectionId := LBusiness;
  if TTgJson.GetBool(LMessage, 'is_topic_message') and TTgJson.Has(LMessage, 'message_thread_id') then
    LOptions.MessageThreadId := TTgJson.GetInt64(LMessage, 'message_thread_id');
  if AParseMode <> '' then
    LOptions.ParseMode := AParseMode;
  if not AKeyboard.IsEmpty then
    LOptions.ReplyMarkup := AKeyboard;
  Result := FApiOwner.Api.SendMessage(LChat, AText, LOptions);
end;

function TTgContext.Reply(const AText: string): ITgMessage;
begin
  Result := SendText(AText, '', Default(TTgReplyMarkup));
end;

function TTgContext.Reply(const AText: string; const AKeyboard: TTgReplyMarkup): ITgMessage;
begin
  Result := SendText(AText, '', AKeyboard);
end;

function TTgContext.ReplyHtml(const AText: string): ITgMessage;
begin
  Result := SendText(AText, TTgParseMode.Html, Default(TTgReplyMarkup));
end;

function TTgContext.ReplyHtml(const AText: string; const AKeyboard: TTgReplyMarkup): ITgMessage;
begin
  Result := SendText(AText, TTgParseMode.Html, AKeyboard);
end;

function TTgContext.Answer(const AText: string; AShowAlert: Boolean): Boolean;
var
  LId: string;
begin
  if not IsCallback then
    Exit(False);
  LId := TTgJson.GetStr(FPayload, 'id');
  // До вызова: при ошибке автоматический ответ не повторяет запрос.
  FAnswered := True;
  if AShowAlert then
    Result := FApiOwner.Api.AnswerCallbackQuery(LId, AText, True)
  else if AText <> '' then
    Result := FApiOwner.Api.AnswerCallbackQuery(LId, AText)
  else
    Result := FApiOwner.Api.AnswerCallbackQuery(LId);
end;

/// <summary>400 «Bad Request: message is not modified…» от edit-метода.</summary>
function IsMessageNotModified(AError: ETgApiError): Boolean;
begin
  Result := (AError.ErrorCode = 400) and
    (Pos('message is not modified', LowerCase(AError.Description)) > 0);
end;

function TTgContext.EditText(const AText: string;
  const AKeyboard: ITgInlineKeyboardMarkup): Boolean;
var
  LOptions: TTgEditMessageTextOptions;
  LInlineId, LBusiness: string;
  LMessage, LChat: TJSONObject;
begin
  if not IsCallback then
    Exit(False);
  LOptions := Default(TTgEditMessageTextOptions);
  if Assigned(AKeyboard) then
    LOptions.ReplyMarkup := AKeyboard;
  try
    LInlineId := TTgJson.GetStr(FPayload, 'inline_message_id');
    if LInlineId <> '' then
      Exit(FApiOwner.Api.EditInlineMessageText(LInlineId, AText, LOptions));
    LMessage := TTgJson.GetObj(FPayload, 'message');
    LChat := TTgJson.GetObj(LMessage, 'chat');
    if not TTgJson.Has(LChat, 'id') or not TTgJson.Has(LMessage, 'message_id') then
      Exit(False);
    LBusiness := TTgJson.GetStr(LMessage, 'business_connection_id');
    if LBusiness <> '' then
      LOptions.BusinessConnectionId := LBusiness;
    FApiOwner.Api.EditMessageText(TTgChatId.FromId(TTgJson.GetInt64(LChat, 'id')),
      TTgJson.GetInt64(LMessage, 'message_id'), AText, LOptions);
    Result := True;
  except
    // Повторное нажатие той же кнопки: текст и клавиатура не изменились —
    // это не ошибка обработчика (только в хелпере, сырые методы Api — как есть).
    on E: ETgApiError do
      if IsMessageNotModified(E) then
        Result := False
      else
        raise;
  end;
end;

function TTgContext.Edit(const AText: string): Boolean;
begin
  Result := EditText(AText, nil);
end;

function TTgContext.Edit(const AText: string; const AKeyboard: ITgInlineKeyboardMarkup): Boolean;
begin
  Result := EditText(AText, AKeyboard);
end;

end.
