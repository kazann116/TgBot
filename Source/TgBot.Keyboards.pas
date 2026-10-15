unit TgBot.Keyboards;

{
  TgBot — построители клавиатур (ручной код поверх сгенерированного слоя
  TgBot.Types): TTgKeyboard.Inline / Reply / Remove / ForceReply и TgRow
  для фабрик с массивами строк кнопок.

  Указывать этот модуль в uses не нужно: TgBot реэкспортирует его типы
  псевдонимами, а TgRow — функциями-обёртками.
}

{$SCOPEDENUMS ON}

interface

uses
  TgBot.Types;

type
  /// <summary>
  ///   Построитель инлайн-клавиатуры: TTgKeyboard.Inline.Row.Button('Да', 'yes')
  ///   .Button('Нет', 'no').Row.Url('Сайт', 'https://…'). Запись-значение:
  ///   каждый вызов возвращает изменённую копию, исходная не меняется. Первая
  ///   кнопка без Row сама начинает строку; пустые строки не передаются.
  ///   Неявно приводится к ITgInlineKeyboardMarkup (edit-методы, поля ReplyMarkup
  ///   инлайн-типа) и к TTgReplyMarkup (send-методы); явно — Build и AsReplyMarkup.
  /// </summary>
  TTgInlineKeyboardBuilder = record
  private
    FRows: TArray<TArray<ITgInlineKeyboardButton>>;
  public
    /// <summary>Начинает новую строку кнопок.</summary>
    function Row: TTgInlineKeyboardBuilder;
    /// <summary>Добавляет готовую кнопку (стиль, иконка и т.п. — через With*) в текущую строку.</summary>
    function Add(const AButton: ITgInlineKeyboardButton): TTgInlineKeyboardBuilder;
    /// <summary>Кнопка с callback_data (1–64 байта): нажатие приходит как Update.CallbackQuery.</summary>
    function Button(const AText, ACallbackData: string): TTgInlineKeyboardBuilder;
    /// <summary>Кнопка-ссылка (http(s)://, tg://).</summary>
    function Url(const AText, AUrl: string): TTgInlineKeyboardBuilder;
    /// <summary>Кнопка Web App (только в личных чатах с ботом).</summary>
    function WebApp(const AText, AUrl: string): TTgInlineKeyboardBuilder;
    /// <summary>Кнопка авторизации на сайте (Telegram Login).</summary>
    function LoginUrl(const AText, AUrl: string): TTgInlineKeyboardBuilder;
    /// <summary>Выбор чата и inline-запрос к боту с текстом AQuery ('' — только имя бота).</summary>
    function SwitchInline(const AText: string; const AQuery: string = ''): TTgInlineKeyboardBuilder;
    /// <summary>Inline-запрос к боту в текущем чате.</summary>
    function SwitchInlineCurrentChat(const AText: string;
      const AQuery: string = ''): TTgInlineKeyboardBuilder;
    /// <summary>Кнопка копирования ACopyText в буфер обмена.</summary>
    function CopyText(const AText, ACopyText: string): TTgInlineKeyboardBuilder;
    /// <summary>Кнопка оплаты (первая кнопка первой строки для sendInvoice).</summary>
    function Pay(const AText: string): TTgInlineKeyboardBuilder;
    /// <summary>Кнопка запуска игры (первая кнопка первой строки для sendGame).</summary>
    function Game(const AText: string): TTgInlineKeyboardBuilder;
    /// <summary>Число непустых строк.</summary>
    function RowCount: Integer;
    /// <summary>Нет ни одной кнопки.</summary>
    function IsEmpty: Boolean;
    /// <summary>Новая разметка ITgInlineKeyboardMarkup из текущих кнопок.</summary>
    function Build: ITgInlineKeyboardMarkup;
    /// <summary>Разметка для параметра reply_markup send-методов.</summary>
    function AsReplyMarkup: TTgReplyMarkup;
    class operator Implicit(const ABuilder: TTgInlineKeyboardBuilder): ITgInlineKeyboardMarkup;
    class operator Implicit(const ABuilder: TTgInlineKeyboardBuilder): TTgReplyMarkup;
  end;

  /// <summary>
  ///   Построитель обычной клавиатуры: TTgKeyboard.Reply.Row.Text('Меню')
  ///   .RequestContact('Телефон').Resize.OneTime. Запись-значение, как
  ///   TTgInlineKeyboardBuilder. Неявно приводится к ITgReplyKeyboardMarkup
  ///   и TTgReplyMarkup.
  /// </summary>
  TTgReplyKeyboardBuilder = record
  private
    FRows: TArray<TArray<ITgKeyboardButton>>;
    FResize: Boolean;
    FOneTime: Boolean;
    FPersistent: Boolean;
    FSelective: Boolean;
    FPlaceholder: string;
  public
    /// <summary>Начинает новую строку кнопок.</summary>
    function Row: TTgReplyKeyboardBuilder;
    /// <summary>Добавляет готовую кнопку (RequestUsers, RequestChat и т.п.) в текущую строку.</summary>
    function Add(const AButton: ITgKeyboardButton): TTgReplyKeyboardBuilder;
    /// <summary>Текстовая кнопка: нажатие отправляет AText как сообщение.</summary>
    function Text(const AText: string): TTgReplyKeyboardBuilder;
    /// <summary>Кнопка отправки своего контакта (только в личных чатах).</summary>
    function RequestContact(const AText: string): TTgReplyKeyboardBuilder;
    /// <summary>Кнопка отправки своей геопозиции (только в личных чатах).</summary>
    function RequestLocation(const AText: string): TTgReplyKeyboardBuilder;
    /// <summary>Кнопка создания опроса; APollType — TTgPollType.Quiz/Regular или '' (любой).</summary>
    function RequestPoll(const AText: string; const APollType: string = ''): TTgReplyKeyboardBuilder;
    /// <summary>Кнопка Web App (только в личных чатах).</summary>
    function WebApp(const AText, AUrl: string): TTgReplyKeyboardBuilder;
    /// <summary>resize_keyboard: подогнать высоту клавиатуры под кнопки.</summary>
    function Resize(AValue: Boolean = True): TTgReplyKeyboardBuilder;
    /// <summary>one_time_keyboard: скрыть клавиатуру после нажатия.</summary>
    function OneTime(AValue: Boolean = True): TTgReplyKeyboardBuilder;
    /// <summary>is_persistent: не скрывать клавиатуру.</summary>
    function Persistent(AValue: Boolean = True): TTgReplyKeyboardBuilder;
    /// <summary>selective: только упомянутым пользователям или автору исходного сообщения.</summary>
    function Selective(AValue: Boolean = True): TTgReplyKeyboardBuilder;
    /// <summary>input_field_placeholder: подсказка в поле ввода (1–64 символа).</summary>
    function Placeholder(const AText: string): TTgReplyKeyboardBuilder;
    /// <summary>Число непустых строк.</summary>
    function RowCount: Integer;
    /// <summary>Нет ни одной кнопки.</summary>
    function IsEmpty: Boolean;
    /// <summary>Новая разметка ITgReplyKeyboardMarkup из текущих кнопок и флагов.</summary>
    function Build: ITgReplyKeyboardMarkup;
    /// <summary>Разметка для параметра reply_markup send-методов.</summary>
    function AsReplyMarkup: TTgReplyMarkup;
    class operator Implicit(const ABuilder: TTgReplyKeyboardBuilder): ITgReplyKeyboardMarkup;
    class operator Implicit(const ABuilder: TTgReplyKeyboardBuilder): TTgReplyMarkup;
  end;

  /// <summary>
  ///   Точка входа построителей клавиатур:
  ///   <code>
  ///     LApi.SendMessage(LChatId, 'Выберите:',
  ///       TTgKeyboard.Inline.Row.Button('Да', 'yes').Button('Нет', 'no'));
  ///     LApi.SendMessage(LChatId, 'Меню', TTgKeyboard.Reply.Row.Text('Помощь').Resize);
  ///     LApi.SendMessage(LChatId, 'Готово', TTgKeyboard.Remove);
  ///   </code>
  /// </summary>
  TTgKeyboard = record
  public
    /// <summary>Пустая инлайн-клавиатура (кнопки под сообщением).</summary>
    class function &Inline: TTgInlineKeyboardBuilder; static;
    /// <summary>Пустая обычная клавиатура (вместо клавиатуры устройства).</summary>
    class function Reply: TTgReplyKeyboardBuilder; static;
    /// <summary>Убрать обычную клавиатуру (ReplyKeyboardRemove).</summary>
    class function Remove(ASelective: Boolean = False): ITgReplyKeyboardRemove; static;
    /// <summary>Принудительный ответ на сообщение (ForceReply) с подсказкой APlaceholder.</summary>
    class function ForceReply(const APlaceholder: string = '';
      ASelective: Boolean = False): ITgForceReply; static;
  end;

/// <summary>
///   Строка инлайн-клавиатуры для фабрик с массивами массивов: вложенный
///   литерал [[A, B]] компилятор принимает за множество, поэтому
///   TTgInlineKeyboardMarkup.Create([TgRow([A, B]), TgRow([C])]).
/// </summary>
function TgRow(const AButtons: array of ITgInlineKeyboardButton): TArray<ITgInlineKeyboardButton>;
  overload;
/// <summary>Строка обычной клавиатуры: TTgReplyKeyboardMarkup.Create([TgRow([A, B])]).</summary>
function TgRow(const AButtons: array of ITgKeyboardButton): TArray<ITgKeyboardButton>; overload;

implementation

uses
  System.SysUtils,
  TgBot.Base,
  TgBot.Consts,
  TgBot.Dto;

{ Построители клавиатур }

function TgRow(const AButtons: array of ITgInlineKeyboardButton): TArray<ITgInlineKeyboardButton>;
begin
  Result := TTgDto.CopyArray<ITgInlineKeyboardButton>(AButtons);
end;

function TgRow(const AButtons: array of ITgKeyboardButton): TArray<ITgKeyboardButton>;
begin
  Result := TTgDto.CopyArray<ITgKeyboardButton>(AButtons);
end;

{ TTgInlineKeyboardBuilder }

function TTgInlineKeyboardBuilder.Row: TTgInlineKeyboardBuilder;
begin
  // Копия внешнего массива: изменения не видны прежним копиям записи.
  Result := Self;
  Result.FRows := Copy(FRows);
  SetLength(Result.FRows, Length(Result.FRows) + 1);
end;

function TTgInlineKeyboardBuilder.Add(const AButton: ITgInlineKeyboardButton): TTgInlineKeyboardBuilder;
var
  LLast: Integer;
begin
  if not Assigned(AButton) then
    raise EArgumentNilException.Create(TgLangTextFmt(@SRuArgNil, @SEnArgNil, ['AButton']));
  Result := Self;
  Result.FRows := Copy(FRows);
  if Length(Result.FRows) = 0 then
    SetLength(Result.FRows, 1);
  LLast := High(Result.FRows);
  // «+» создаёт новый массив строки — прежняя строка не меняется.
  Result.FRows[LLast] := Result.FRows[LLast] + [AButton];
end;

function TTgInlineKeyboardBuilder.Button(const AText, ACallbackData: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText).WithCallbackData(ACallbackData));
end;

function TTgInlineKeyboardBuilder.Url(const AText, AUrl: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText).WithUrl(AUrl));
end;

function TTgInlineKeyboardBuilder.WebApp(const AText, AUrl: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText).WithWebApp(TTgWebAppInfo.Create(AUrl)));
end;

function TTgInlineKeyboardBuilder.LoginUrl(const AText, AUrl: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText).WithLoginUrl(TTgLoginUrl.Create(AUrl)));
end;

function TTgInlineKeyboardBuilder.SwitchInline(const AText, AQuery: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText).WithSwitchInlineQuery(AQuery));
end;

function TTgInlineKeyboardBuilder.SwitchInlineCurrentChat(const AText,
  AQuery: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText).WithSwitchInlineQueryCurrentChat(AQuery));
end;

function TTgInlineKeyboardBuilder.CopyText(const AText, ACopyText: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText)
    .WithCopyText(TTgCopyTextButton.Create(ACopyText)));
end;

function TTgInlineKeyboardBuilder.Pay(const AText: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText).WithPay(True));
end;

function TTgInlineKeyboardBuilder.Game(const AText: string): TTgInlineKeyboardBuilder;
begin
  Result := Add(TTgInlineKeyboardButton.Create(AText).WithCallbackGame(TTgCallbackGame.Create));
end;

function TTgInlineKeyboardBuilder.RowCount: Integer;
var
  LRow: TArray<ITgInlineKeyboardButton>;
begin
  Result := 0;
  for LRow in FRows do
    if Length(LRow) > 0 then
      Inc(Result);
end;

function TTgInlineKeyboardBuilder.IsEmpty: Boolean;
begin
  Result := RowCount = 0;
end;

function TTgInlineKeyboardBuilder.Build: ITgInlineKeyboardMarkup;
var
  LRows: TArray<TArray<ITgInlineKeyboardButton>>;
  LRow: TArray<ITgInlineKeyboardButton>;
begin
  LRows := nil;
  for LRow in FRows do
    if Length(LRow) > 0 then
      LRows := LRows + [LRow];
  Result := TTgInlineKeyboardMarkup.Create(LRows);
end;

function TTgInlineKeyboardBuilder.AsReplyMarkup: TTgReplyMarkup;
begin
  Result := Build;
end;

class operator TTgInlineKeyboardBuilder.Implicit(
  const ABuilder: TTgInlineKeyboardBuilder): ITgInlineKeyboardMarkup;
begin
  Result := ABuilder.Build;
end;

class operator TTgInlineKeyboardBuilder.Implicit(const ABuilder: TTgInlineKeyboardBuilder): TTgReplyMarkup;
begin
  Result := ABuilder.Build;
end;

{ TTgReplyKeyboardBuilder }

function TTgReplyKeyboardBuilder.Row: TTgReplyKeyboardBuilder;
begin
  Result := Self;
  Result.FRows := Copy(FRows);
  SetLength(Result.FRows, Length(Result.FRows) + 1);
end;

function TTgReplyKeyboardBuilder.Add(const AButton: ITgKeyboardButton): TTgReplyKeyboardBuilder;
var
  LLast: Integer;
begin
  if not Assigned(AButton) then
    raise EArgumentNilException.Create(TgLangTextFmt(@SRuArgNil, @SEnArgNil, ['AButton']));
  Result := Self;
  Result.FRows := Copy(FRows);
  if Length(Result.FRows) = 0 then
    SetLength(Result.FRows, 1);
  LLast := High(Result.FRows);
  Result.FRows[LLast] := Result.FRows[LLast] + [AButton];
end;

function TTgReplyKeyboardBuilder.Text(const AText: string): TTgReplyKeyboardBuilder;
begin
  Result := Add(TTgKeyboardButton.Create(AText));
end;

function TTgReplyKeyboardBuilder.RequestContact(const AText: string): TTgReplyKeyboardBuilder;
begin
  Result := Add(TTgKeyboardButton.Create(AText).WithRequestContact(True));
end;

function TTgReplyKeyboardBuilder.RequestLocation(const AText: string): TTgReplyKeyboardBuilder;
begin
  Result := Add(TTgKeyboardButton.Create(AText).WithRequestLocation(True));
end;

function TTgReplyKeyboardBuilder.RequestPoll(const AText, APollType: string): TTgReplyKeyboardBuilder;
var
  LPollType: ITgKeyboardButtonPollType;
begin
  LPollType := TTgKeyboardButtonPollType.Create;
  if APollType <> '' then
    LPollType.WithKeyboardButtonPollTypeType(APollType);
  Result := Add(TTgKeyboardButton.Create(AText).WithRequestPoll(LPollType));
end;

function TTgReplyKeyboardBuilder.WebApp(const AText, AUrl: string): TTgReplyKeyboardBuilder;
begin
  Result := Add(TTgKeyboardButton.Create(AText).WithWebApp(TTgWebAppInfo.Create(AUrl)));
end;

function TTgReplyKeyboardBuilder.Resize(AValue: Boolean): TTgReplyKeyboardBuilder;
begin
  Result := Self;
  Result.FResize := AValue;
end;

function TTgReplyKeyboardBuilder.OneTime(AValue: Boolean): TTgReplyKeyboardBuilder;
begin
  Result := Self;
  Result.FOneTime := AValue;
end;

function TTgReplyKeyboardBuilder.Persistent(AValue: Boolean): TTgReplyKeyboardBuilder;
begin
  Result := Self;
  Result.FPersistent := AValue;
end;

function TTgReplyKeyboardBuilder.Selective(AValue: Boolean): TTgReplyKeyboardBuilder;
begin
  Result := Self;
  Result.FSelective := AValue;
end;

function TTgReplyKeyboardBuilder.Placeholder(const AText: string): TTgReplyKeyboardBuilder;
begin
  Result := Self;
  Result.FPlaceholder := AText;
end;

function TTgReplyKeyboardBuilder.RowCount: Integer;
var
  LRow: TArray<ITgKeyboardButton>;
begin
  Result := 0;
  for LRow in FRows do
    if Length(LRow) > 0 then
      Inc(Result);
end;

function TTgReplyKeyboardBuilder.IsEmpty: Boolean;
begin
  Result := RowCount = 0;
end;

function TTgReplyKeyboardBuilder.Build: ITgReplyKeyboardMarkup;
var
  LRows: TArray<TArray<ITgKeyboardButton>>;
  LRow: TArray<ITgKeyboardButton>;
begin
  LRows := nil;
  for LRow in FRows do
    if Length(LRow) > 0 then
      LRows := LRows + [LRow];
  Result := TTgReplyKeyboardMarkup.Create(LRows);
  // Флаги передаются, только если включены (false — значение Bot API по умолчанию).
  if FResize then
    Result.WithResizeKeyboard(True);
  if FOneTime then
    Result.WithOneTimeKeyboard(True);
  if FPersistent then
    Result.WithIsPersistent(True);
  if FSelective then
    Result.WithSelective(True);
  if FPlaceholder <> '' then
    Result.WithInputFieldPlaceholder(FPlaceholder);
end;

function TTgReplyKeyboardBuilder.AsReplyMarkup: TTgReplyMarkup;
begin
  Result := Build;
end;

class operator TTgReplyKeyboardBuilder.Implicit(const ABuilder: TTgReplyKeyboardBuilder): ITgReplyKeyboardMarkup;
begin
  Result := ABuilder.Build;
end;

class operator TTgReplyKeyboardBuilder.Implicit(const ABuilder: TTgReplyKeyboardBuilder): TTgReplyMarkup;
begin
  Result := ABuilder.Build;
end;

{ TTgKeyboard }

class function TTgKeyboard.&Inline: TTgInlineKeyboardBuilder;
begin
  Result := Default(TTgInlineKeyboardBuilder);
end;

class function TTgKeyboard.Reply: TTgReplyKeyboardBuilder;
begin
  Result := Default(TTgReplyKeyboardBuilder);
end;

class function TTgKeyboard.Remove(ASelective: Boolean): ITgReplyKeyboardRemove;
begin
  Result := TTgReplyKeyboardRemove.Create;
  if ASelective then
    Result.WithSelective(True);
end;

class function TTgKeyboard.ForceReply(const APlaceholder: string; ASelective: Boolean): ITgForceReply;
begin
  Result := TTgForceReply.Create;
  if APlaceholder <> '' then
    Result.WithInputFieldPlaceholder(APlaceholder);
  if ASelective then
    Result.WithSelective(True);
end;

end.
