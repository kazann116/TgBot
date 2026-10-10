unit TgBot.Api;

{
  TgBot — ВРЕМЕННЫЙ ручной клиент Bot API (фаза 1).
  Позже будет заменён генерируемым кодом; контракты ядра (TgBot.Base,
  TgBot.Json, TgBot.Http) остаются прежними.

  DTO — интерфейсы с автоосвобождением. Каждый DTO хранит JSON-объект:
  корневой DTO владеет своей копией JSON, вложенные ссылаются на часть
  JSON родителя и удерживают родителя ссылкой на интерфейс.
  Доступ к полям, которых нет в интерфейсе, — через Raw/AsJson.

  Асинхронные методы (...Async) выполняются в пуле потоков (TTask).
  Колбэки вызываются В РАБОЧЕМ ПОТОКЕ: для обращения к UI используйте
  TThread.Queue/Synchronize сами (встроенная синхронизация — в следующих фазах).
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.Classes,
  System.SyncObjs,
  System.JSON,
  System.Threading,
  TgBot.Base,
  TgBot.Json,
  TgBot.Http;

const
  /// <summary>parse_mode: HTML.</summary>
  TgParseModeHtml = 'HTML';
  /// <summary>parse_mode: MarkdownV2.</summary>
  TgParseModeMarkdownV2 = 'MarkdownV2';
  /// <summary>parse_mode: Markdown (устаревший).</summary>
  TgParseModeMarkdown = 'Markdown';

type
  /// <summary>Базовый интерфейс DTO на основе JSON.</summary>
  ITgJsonObject = interface
    ['{54EC6FB3-98E8-440F-95AA-DC7FD7EA3E79}']
    function GetRaw: TJSONObject;
    /// <summary>JSON-текст объекта.</summary>
    function AsJson: string;
    /// <summary>JSON-объект DTO. Владелец — DTO, не освобождайте его.</summary>
    property Raw: TJSONObject read GetRaw;
  end;

  /// <summary>Пользователь или бот (User).</summary>
  ITgUser = interface(ITgJsonObject)
    ['{5D47BE0E-58A0-407E-AEB1-391CCA5B484A}']
    function GetId: Int64;
    function GetIsBot: Boolean;
    function GetFirstName: string;
    function GetLastName: string;
    function GetUsername: string;
    function GetLanguageCode: string;
    property Id: Int64 read GetId;
    property IsBot: Boolean read GetIsBot;
    property FirstName: string read GetFirstName;
    property LastName: string read GetLastName;
    /// <summary>Имя пользователя без '@'.</summary>
    property Username: string read GetUsername;
    property LanguageCode: string read GetLanguageCode;
  end;

  /// <summary>Чат (Chat).</summary>
  ITgChat = interface(ITgJsonObject)
    ['{ADB5AAFE-492A-4436-9535-B6107C9C4C93}']
    function GetId: Int64;
    function GetChatType: string;
    function GetTitle: string;
    function GetUsername: string;
    function GetFirstName: string;
    function GetLastName: string;
    property Id: Int64 read GetId;
    /// <summary>Тип чата: private, group, supergroup, channel.</summary>
    property ChatType: string read GetChatType;
    property Title: string read GetTitle;
    property Username: string read GetUsername;
    property FirstName: string read GetFirstName;
    property LastName: string read GetLastName;
  end;

  /// <summary>Сообщение (Message), минимальный набор полей.</summary>
  ITgMessage = interface(ITgJsonObject)
    ['{EF733DA7-B0DB-47F7-B3D6-66FFFB1B4D18}']
    function GetMessageId: Int64;
    function GetMessageThreadId: Int64;
    function GetFrom: ITgUser;
    function GetChat: ITgChat;
    function GetDate: Int64;
    function GetText: string;
    function GetCaption: string;
    function GetReplyToMessage: ITgMessage;
    property MessageId: Int64 read GetMessageId;
    /// <summary>Идентификатор темы форума или 0.</summary>
    property MessageThreadId: Int64 read GetMessageThreadId;
    /// <summary>Отправитель или nil (например, в каналах).</summary>
    property From: ITgUser read GetFrom;
    property Chat: ITgChat read GetChat;
    /// <summary>Дата в Unix time (UTC).</summary>
    property Date: Int64 read GetDate;
    property Text: string read GetText;
    property Caption: string read GetCaption;
    /// <summary>Сообщение, на которое дан ответ, или nil.</summary>
    property ReplyToMessage: ITgMessage read GetReplyToMessage;
  end;

  /// <summary>Входящее обновление (Update), минимальный набор полей.</summary>
  ITgUpdate = interface(ITgJsonObject)
    ['{45EF96B2-8A1C-4634-8A57-A7B184C5FEBA}']
    function GetUpdateId: Int64;
    function GetMessage: ITgMessage;
    function GetEditedMessage: ITgMessage;
    function GetChannelPost: ITgMessage;
    function GetEditedChannelPost: ITgMessage;
    property UpdateId: Int64 read GetUpdateId;
    property Message: ITgMessage read GetMessage;
    property EditedMessage: ITgMessage read GetEditedMessage;
    property ChannelPost: ITgMessage read GetChannelPost;
    property EditedChannelPost: ITgMessage read GetEditedChannelPost;
  end;

  /// <summary>
  ///   Необязательные параметры sendMessage. Неинициализированная запись
  ///   пуста (все поля управляемые), Create — для наглядности.
  /// </summary>
  TTgSendMessageOptions = record
    /// <summary>Режим разметки: TgParseModeHtml, TgParseModeMarkdownV2…</summary>
    ParseMode: string;
    /// <summary>reply_markup — JSON-текст клавиатуры.</summary>
    ReplyMarkup: string;
    /// <summary>link_preview_options — JSON-текст.</summary>
    LinkPreviewOptions: string;
    /// <summary>reply_parameters — JSON-текст (приоритетнее ReplyToMessageId).</summary>
    ReplyParameters: string;
    /// <summary>business_connection_id.</summary>
    BusinessConnectionId: string;
    /// <summary>Ответить на сообщение (формирует reply_parameters).</summary>
    ReplyToMessageId: TTgOptional<Int64>;
    /// <summary>message_thread_id — тема форума.</summary>
    MessageThreadId: TTgOptional<Int64>;
    /// <summary>disable_notification.</summary>
    DisableNotification: TTgOptional<Boolean>;
    /// <summary>protect_content.</summary>
    ProtectContent: TTgOptional<Boolean>;
    /// <summary>Пустые опции.</summary>
    class function Create: TTgSendMessageOptions; static;
    /// <summary>Добавляет заданные опции в параметры запроса.</summary>
    procedure ApplyTo(AParams: TTgParams);
  end;

  /// <summary>
  ///   Клиент Bot API (временная ручная версия). Потокобезопасен: методы можно
  ///   вызывать из разных потоков. Не уничтожайте объект из колбэка Async.
  /// </summary>
  TTgApi = class
  private
    FTransport: ITgTransport;
    FPendingAsync: Integer;
    procedure WaitPendingAsync;
  public
    /// <summary>Клиент облачного Bot API с настройками по умолчанию.</summary>
    constructor Create(const AToken: string); overload;
    /// <summary>Клиент с настройками транспорта (прокси, ApiUrl, таймауты…).</summary>
    constructor Create(const ASettings: TTgHttpSettings); overload;
    /// <summary>Клиент с собственным транспортом (например, тестовым).</summary>
    constructor Create(const ATransport: ITgTransport); overload;
    /// <summary>
    ///   Отменяет ожидания транспорта и дожидается завершения Async-вызовов.
    /// </summary>
    destructor Destroy; override;

    /// <summary>
    ///   Универсальный вызов метода Bot API. Результат (поле result)
    ///   освобождает вызывающий. AParams остаётся во владении вызывающего.
    /// </summary>
    function Call(const AMethod: string; AParams: TTgParams = nil): TJSONValue;
    /// <summary>Универсальный вызов; результат — JSON-текст поля result.</summary>
    function CallJson(const AMethod: string; AParams: TTgParams = nil): string;

    /// <summary>getMe — информация о боте.</summary>
    function GetMe: ITgUser;
    /// <summary>
    ///   getUpdates — long polling. AOffset = 0 и пустой AAllowedUpdates
    ///   не передаются. ATimeout — секунды ожидания на сервере.
    /// </summary>
    function GetUpdates(AOffset: Int64 = 0; ALimit: Integer = 100;
      ATimeout: Integer = 0; const AAllowedUpdates: TArray<string> = nil): TArray<ITgUpdate>;
    /// <summary>sendMessage — отправка текста.</summary>
    function SendMessage(const AChatId: TTgChatId; const AText: string): ITgMessage; overload;
    /// <summary>sendMessage с опциями.</summary>
    function SendMessage(const AChatId: TTgChatId; const AText: string;
      const AOptions: TTgSendMessageOptions): ITgMessage; overload;
    /// <summary>sendMessage без исключений: False и сведения об ошибке в AError.</summary>
    function TrySendMessage(const AChatId: TTgChatId; const AText: string;
      out AMessage: ITgMessage; out AError: TTgErrorInfo): Boolean; overload;
    /// <summary>sendMessage с опциями без исключений.</summary>
    function TrySendMessage(const AChatId: TTgChatId; const AText: string;
      const AOptions: TTgSendMessageOptions; out AMessage: ITgMessage;
      out AError: TTgErrorInfo): Boolean; overload;
    /// <summary>Скачивает файл по file_path (из getFile) в поток.</summary>
    procedure DownloadFile(const AFilePath: string; ADest: TStream);

    /// <summary>
    ///   Выполняет AFunc в пуле потоков. При успехе вызывает AOnSuccess,
    ///   при ошибке — AOnError (объект исключения действителен только внутри
    ///   колбэка). Если AOnError не задан, исключение сохраняется в ITask
    ///   (ITask.Wait выбросит EAggregateException). Колбэки — в рабочем потоке.
    /// </summary>
    function RunAsync<T>(const AFunc: TFunc<T>; const AOnSuccess: TProc<T>;
      const AOnError: TProc<Exception>): ITask;
    /// <summary>Асинхронный getMe.</summary>
    function GetMeAsync(const AOnSuccess: TProc<ITgUser>;
      const AOnError: TProc<Exception> = nil): ITask;
    /// <summary>Асинхронный sendMessage.</summary>
    function SendMessageAsync(const AChatId: TTgChatId; const AText: string;
      const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;
    /// <summary>Асинхронный sendMessage с опциями.</summary>
    function SendMessageAsync(const AChatId: TTgChatId; const AText: string;
      const AOptions: TTgSendMessageOptions; const AOnSuccess: TProc<ITgMessage>;
      const AOnError: TProc<Exception> = nil): ITask; overload;

    /// <summary>Транспорт клиента.</summary>
    property Transport: ITgTransport read FTransport;
  end;

/// <summary>Разбирает Update из JSON-текста (например, тела webhook); ошибка — nil.</summary>
function TgParseUpdate(const AJsonText: string): ITgUpdate;

implementation

uses
  System.Generics.Collections;

type
  /// <summary>Владелец JSON-значения, разделяемого несколькими DTO.</summary>
  TTgJsonHolder = class(TInterfacedObject)
  private
    FValue: TJSONValue;
  public
    constructor Create(AValue: TJSONValue);
    destructor Destroy; override;
  end;

  /// <summary>
  ///   Базовый DTO. AOwner = nil — DTO владеет AJson; иначе AJson — часть
  ///   JSON владельца, которого DTO удерживает ссылкой.
  /// </summary>
  TTgJsonDto = class(TInterfacedObject, ITgJsonObject)
  private
    FJson: TJSONObject;
    FOwner: IInterface;
  protected
    /// <summary>Владелец JSON для вложенных DTO.</summary>
    function JsonOwner: IInterface;
  public
    constructor Create(AJson: TJSONObject; const AOwner: IInterface);
    destructor Destroy; override;
    function GetRaw: TJSONObject;
    function AsJson: string;
  end;

  TTgUser = class(TTgJsonDto, ITgUser)
  public
    function GetId: Int64;
    function GetIsBot: Boolean;
    function GetFirstName: string;
    function GetLastName: string;
    function GetUsername: string;
    function GetLanguageCode: string;
  end;

  TTgChat = class(TTgJsonDto, ITgChat)
  public
    function GetId: Int64;
    function GetChatType: string;
    function GetTitle: string;
    function GetUsername: string;
    function GetFirstName: string;
    function GetLastName: string;
  end;

  TTgMessage = class(TTgJsonDto, ITgMessage)
  public
    function GetMessageId: Int64;
    function GetMessageThreadId: Int64;
    function GetFrom: ITgUser;
    function GetChat: ITgChat;
    function GetDate: Int64;
    function GetText: string;
    function GetCaption: string;
    function GetReplyToMessage: ITgMessage;
  end;

  TTgUpdate = class(TTgJsonDto, ITgUpdate)
  public
    function GetUpdateId: Int64;
    function GetMessage: ITgMessage;
    function GetEditedMessage: ITgMessage;
    function GetChannelPost: ITgMessage;
    function GetEditedChannelPost: ITgMessage;
  end;

// Фабрики: nil JSON -> nil интерфейс. При AOwner = nil DTO забирает AJson.

function MakeUser(AJson: TJSONObject; const AOwner: IInterface): ITgUser;
begin
  if Assigned(AJson) then
    Result := TTgUser.Create(AJson, AOwner)
  else
    Result := nil;
end;

function MakeChat(AJson: TJSONObject; const AOwner: IInterface): ITgChat;
begin
  if Assigned(AJson) then
    Result := TTgChat.Create(AJson, AOwner)
  else
    Result := nil;
end;

function MakeMessage(AJson: TJSONObject; const AOwner: IInterface): ITgMessage;
begin
  if Assigned(AJson) then
    Result := TTgMessage.Create(AJson, AOwner)
  else
    Result := nil;
end;

function MakeUpdate(AJson: TJSONObject; const AOwner: IInterface): ITgUpdate;
begin
  if Assigned(AJson) then
    Result := TTgUpdate.Create(AJson, AOwner)
  else
    Result := nil;
end;

/// <summary>
///   Проверяет, что результат метода — объект, и возвращает его.
///   При несоответствии освобождает AValue и выбрасывает ETgError.
/// </summary>
function ExpectObject(AValue: TJSONValue; const AMethod: string): TJSONObject;
begin
  if AValue is TJSONObject then
    Result := TJSONObject(AValue)
  else
  begin
    AValue.Free;
    raise ETgError.Create(TgTextFmt(TTgText.UnexpectedResult, [AMethod]));
  end;
end;

function TgParseUpdate(const AJsonText: string): ITgUpdate;
var
  LJson: TJSONObject;
begin
  LJson := TTgJson.ParseObject(AJsonText);
  if not Assigned(LJson) then
    Exit(nil);
  try
    Result := MakeUpdate(LJson, nil);
  except
    LJson.Free;
    raise;
  end;
end;

{ TTgJsonHolder }

constructor TTgJsonHolder.Create(AValue: TJSONValue);
begin
  inherited Create;
  FValue := AValue;
end;

destructor TTgJsonHolder.Destroy;
begin
  FreeAndNil(FValue);
  inherited Destroy;
end;

{ TTgJsonDto }

constructor TTgJsonDto.Create(AJson: TJSONObject; const AOwner: IInterface);
begin
  inherited Create;
  FJson := AJson;
  FOwner := AOwner;
end;

destructor TTgJsonDto.Destroy;
begin
  if Assigned(FOwner) then
  begin
    FJson := nil;
    FOwner := nil;
  end
  else
    FreeAndNil(FJson);
  inherited Destroy;
end;

function TTgJsonDto.JsonOwner: IInterface;
begin
  // Вложенные DTO удерживают корневого владельца JSON.
  if Assigned(FOwner) then
    Result := FOwner
  else
    Result := Self;
end;

function TTgJsonDto.GetRaw: TJSONObject;
begin
  Result := FJson;
end;

function TTgJsonDto.AsJson: string;
begin
  Result := TTgJson.ToText(FJson);
end;

{ TTgUser }

function TTgUser.GetId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'id');
end;

function TTgUser.GetIsBot: Boolean;
begin
  Result := TTgJson.GetBool(FJson, 'is_bot');
end;

function TTgUser.GetFirstName: string;
begin
  Result := TTgJson.GetStr(FJson, 'first_name');
end;

function TTgUser.GetLastName: string;
begin
  Result := TTgJson.GetStr(FJson, 'last_name');
end;

function TTgUser.GetUsername: string;
begin
  Result := TTgJson.GetStr(FJson, 'username');
end;

function TTgUser.GetLanguageCode: string;
begin
  Result := TTgJson.GetStr(FJson, 'language_code');
end;

{ TTgChat }

function TTgChat.GetId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'id');
end;

function TTgChat.GetChatType: string;
begin
  Result := TTgJson.GetStr(FJson, 'type');
end;

function TTgChat.GetTitle: string;
begin
  Result := TTgJson.GetStr(FJson, 'title');
end;

function TTgChat.GetUsername: string;
begin
  Result := TTgJson.GetStr(FJson, 'username');
end;

function TTgChat.GetFirstName: string;
begin
  Result := TTgJson.GetStr(FJson, 'first_name');
end;

function TTgChat.GetLastName: string;
begin
  Result := TTgJson.GetStr(FJson, 'last_name');
end;

{ TTgMessage }

function TTgMessage.GetMessageId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'message_id');
end;

function TTgMessage.GetMessageThreadId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'message_thread_id');
end;

function TTgMessage.GetFrom: ITgUser;
begin
  Result := MakeUser(TTgJson.GetObj(FJson, 'from'), JsonOwner);
end;

function TTgMessage.GetChat: ITgChat;
begin
  Result := MakeChat(TTgJson.GetObj(FJson, 'chat'), JsonOwner);
end;

function TTgMessage.GetDate: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'date');
end;

function TTgMessage.GetText: string;
begin
  Result := TTgJson.GetStr(FJson, 'text');
end;

function TTgMessage.GetCaption: string;
begin
  Result := TTgJson.GetStr(FJson, 'caption');
end;

function TTgMessage.GetReplyToMessage: ITgMessage;
begin
  Result := MakeMessage(TTgJson.GetObj(FJson, 'reply_to_message'), JsonOwner);
end;

{ TTgUpdate }

function TTgUpdate.GetUpdateId: Int64;
begin
  Result := TTgJson.GetInt64(FJson, 'update_id');
end;

function TTgUpdate.GetMessage: ITgMessage;
begin
  Result := MakeMessage(TTgJson.GetObj(FJson, 'message'), JsonOwner);
end;

function TTgUpdate.GetEditedMessage: ITgMessage;
begin
  Result := MakeMessage(TTgJson.GetObj(FJson, 'edited_message'), JsonOwner);
end;

function TTgUpdate.GetChannelPost: ITgMessage;
begin
  Result := MakeMessage(TTgJson.GetObj(FJson, 'channel_post'), JsonOwner);
end;

function TTgUpdate.GetEditedChannelPost: ITgMessage;
begin
  Result := MakeMessage(TTgJson.GetObj(FJson, 'edited_channel_post'), JsonOwner);
end;

{ TTgSendMessageOptions }

class function TTgSendMessageOptions.Create: TTgSendMessageOptions;
begin
  Result := Default(TTgSendMessageOptions);
end;

procedure TTgSendMessageOptions.ApplyTo(AParams: TTgParams);
var
  LReply: TJSONObject;
begin
  AParams.AddNotEmpty('business_connection_id', BusinessConnectionId);
  AParams.AddOptional('message_thread_id', MessageThreadId);
  AParams.AddNotEmpty('parse_mode', ParseMode);
  AParams.AddJsonText('link_preview_options', LinkPreviewOptions);
  AParams.AddOptional('disable_notification', DisableNotification);
  AParams.AddOptional('protect_content', ProtectContent);
  if ReplyParameters <> '' then
    AParams.AddJsonText('reply_parameters', ReplyParameters)
  else if ReplyToMessageId.HasValue then
  begin
    LReply := TJSONObject.Create;
    try
      LReply.AddPair('message_id', TJSONNumber.Create(ReplyToMessageId.Value));
    except
      LReply.Free;
      raise;
    end;
    AParams.AddJson('reply_parameters', LReply);
  end;
  AParams.AddJsonText('reply_markup', ReplyMarkup);
end;

{ TTgApi }

constructor TTgApi.Create(const AToken: string);
begin
  Create(TTgHttpSettings.Create(AToken));
end;

constructor TTgApi.Create(const ASettings: TTgHttpSettings);
begin
  Create(TTgHttpTransport.Create(ASettings) as ITgTransport);
end;

constructor TTgApi.Create(const ATransport: ITgTransport);
begin
  inherited Create;
  if not Assigned(ATransport) then
    raise ETgError.Create(TgText(TTgText.TransportRequired));
  FTransport := ATransport;
end;

destructor TTgApi.Destroy;
begin
  if Assigned(FTransport) then
  begin
    if TInterlocked.CompareExchange(FPendingAsync, 0, 0) > 0 then
      FTransport.Cancel;
    WaitPendingAsync;
  end;
  FTransport := nil;
  inherited Destroy;
end;

procedure TTgApi.WaitPendingAsync;
begin
  while TInterlocked.CompareExchange(FPendingAsync, 0, 0) > 0 do
  begin
    // В главном потоке обрабатываем очередь Synchronize, чтобы колбэки,
    // ожидающие главный поток, не привели к взаимоблокировке.
    if TThread.CurrentThread.ThreadID = MainThreadID then
      CheckSynchronize(10)
    else
      TThread.Sleep(10);
  end;
end;

function TTgApi.Call(const AMethod: string; AParams: TTgParams): TJSONValue;
begin
  Result := FTransport.Execute(AMethod, AParams);
end;

function TTgApi.CallJson(const AMethod: string; AParams: TTgParams): string;
var
  LValue: TJSONValue;
begin
  LValue := Call(AMethod, AParams);
  try
    Result := TTgJson.ToText(LValue);
  finally
    LValue.Free;
  end;
end;

function TTgApi.GetMe: ITgUser;
begin
  Result := MakeUser(ExpectObject(Call('getMe'), 'getMe'), nil);
end;

function TTgApi.GetUpdates(AOffset: Int64; ALimit, ATimeout: Integer;
  const AAllowedUpdates: TArray<string>): TArray<ITgUpdate>;
var
  LParams: TTgParams;
  LValue: TJSONValue;
  LHolder: IInterface;
  LArray: TJSONArray;
  I: Integer;
begin
  Result := nil;
  LParams := TTgParams.Create;
  try
    if AOffset <> 0 then
      LParams.Add('offset', AOffset);
    if ALimit > 0 then
      LParams.Add('limit', ALimit);
    if ATimeout > 0 then
      LParams.Add('timeout', ATimeout);
    if Length(AAllowedUpdates) > 0 then
      LParams.AddStrings('allowed_updates', AAllowedUpdates);
    LValue := Call('getUpdates', LParams);
  finally
    LParams.Free;
  end;
  // Массив целиком принадлежит держателю; обновления ссылаются на его элементы.
  LHolder := TTgJsonHolder.Create(LValue);
  if not (LValue is TJSONArray) then
    raise ETgError.Create(TgTextFmt(TTgText.UnexpectedResult, ['getUpdates']));
  LArray := TJSONArray(LValue);
  SetLength(Result, LArray.Count);
  for I := 0 to LArray.Count - 1 do
  begin
    if not (LArray.Items[I] is TJSONObject) then
      raise ETgError.Create(TgTextFmt(TTgText.UnexpectedResult, ['getUpdates']));
    Result[I] := MakeUpdate(TJSONObject(LArray.Items[I]), LHolder);
  end;
end;

function TTgApi.SendMessage(const AChatId: TTgChatId;
  const AText: string): ITgMessage;
begin
  Result := SendMessage(AChatId, AText, TTgSendMessageOptions.Create);
end;

function TTgApi.SendMessage(const AChatId: TTgChatId; const AText: string;
  const AOptions: TTgSendMessageOptions): ITgMessage;
var
  LParams: TTgParams;
  LValue: TJSONValue;
begin
  LParams := TTgParams.Create;
  try
    LParams.AddChatId('chat_id', AChatId);
    LParams.Add('text', AText);
    AOptions.ApplyTo(LParams);
    LValue := Call('sendMessage', LParams);
  finally
    LParams.Free;
  end;
  Result := MakeMessage(ExpectObject(LValue, 'sendMessage'), nil);
end;

function TTgApi.TrySendMessage(const AChatId: TTgChatId; const AText: string;
  out AMessage: ITgMessage; out AError: TTgErrorInfo): Boolean;
begin
  Result := TrySendMessage(AChatId, AText, TTgSendMessageOptions.Create,
    AMessage, AError);
end;

function TTgApi.TrySendMessage(const AChatId: TTgChatId; const AText: string;
  const AOptions: TTgSendMessageOptions; out AMessage: ITgMessage;
  out AError: TTgErrorInfo): Boolean;
begin
  AMessage := nil;
  AError := TTgErrorInfo.Empty;
  try
    AMessage := SendMessage(AChatId, AText, AOptions);
    Result := True;
  except
    on E: Exception do
    begin
      AError := TTgErrorInfo.FromException(E);
      Result := False;
    end;
  end;
end;

procedure TTgApi.DownloadFile(const AFilePath: string; ADest: TStream);
begin
  FTransport.DownloadFile(AFilePath, ADest);
end;

function TTgApi.RunAsync<T>(const AFunc: TFunc<T>; const AOnSuccess: TProc<T>;
  const AOnError: TProc<Exception>): ITask;
begin
  TInterlocked.Increment(FPendingAsync);
  try
    Result := TTask.Run(
      procedure
      var
        LResult: T;
      begin
        try
          try
            LResult := AFunc();
          except
            on E: Exception do
            begin
              if not Assigned(AOnError) then
                raise;
              AOnError(E);
              Exit;
            end;
          end;
          // Исключение из AOnSuccess не перехватывается и сохраняется в ITask.
          if Assigned(AOnSuccess) then
            AOnSuccess(LResult);
        finally
          TInterlocked.Decrement(FPendingAsync);
        end;
      end);
  except
    TInterlocked.Decrement(FPendingAsync);
    raise;
  end;
end;

function TTgApi.GetMeAsync(const AOnSuccess: TProc<ITgUser>;
  const AOnError: TProc<Exception>): ITask;
begin
  Result := RunAsync<ITgUser>(
    function: ITgUser
    begin
      Result := GetMe;
    end,
    AOnSuccess, AOnError);
end;

function TTgApi.SendMessageAsync(const AChatId: TTgChatId; const AText: string;
  const AOnSuccess: TProc<ITgMessage>; const AOnError: TProc<Exception>): ITask;
begin
  Result := SendMessageAsync(AChatId, AText, TTgSendMessageOptions.Create,
    AOnSuccess, AOnError);
end;

function TTgApi.SendMessageAsync(const AChatId: TTgChatId; const AText: string;
  const AOptions: TTgSendMessageOptions; const AOnSuccess: TProc<ITgMessage>;
  const AOnError: TProc<Exception>): ITask;
var
  LChatId: TTgChatId;
  LText: string;
  LOptions: TTgSendMessageOptions;
begin
  // Копии параметров для захвата анонимным методом.
  LChatId := AChatId;
  LText := AText;
  LOptions := AOptions;
  Result := RunAsync<ITgMessage>(
    function: ITgMessage
    begin
      Result := SendMessage(LChatId, LText, LOptions);
    end,
    AOnSuccess, AOnError);
end;

end.
