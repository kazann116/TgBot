unit TgBot.Router;

{
  TgBot — маршрутизатор TTgBot: правила (Command, Callback, CallbackPrefix,
  Text, TextMatch), разбор команды сообщения ('/имя[@бот] аргументы') и
  выбор правила для message и callback_query.

  Указывать этот модуль в uses не нужно: служебный модуль TgBot, не часть
  публичного API библиотеки. Таблицу правил хранит ядро бота
  (TgBot.Bot.Core), регистрация — методы TTgBot; username бота
  маршрутизатор получает от ядра колбэком (TTgBotUserNameResolver), ссылки
  на ядро у него нет.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.SyncObjs,
  System.RegularExpressions,
  TgBot.Base,
  TgBot.Context;

type
  /// <summary>Тексты ошибок регистрации правил (язык — TgSetLanguage).</summary>
  TTgRouterText = (EmptyKey, BadCommand);

  /// <summary>Вид правила маршрутизатора с ключом.</summary>
  TTgRouteKind = (Command, Callback, CallbackPrefix, Text);

  /// <summary>
  ///   Правило: ключ (команда — TTgRouter.CommandKey, callback data,
  ///   префикс, текст — TTgRouter.TextKey), описание (только команды, для
  ///   меню) и обработчик.
  /// </summary>
  TTgRoute = record
    Key: string;
    Description: string;
    Handler: TProc<ITgContext>;
  end;

  /// <summary>Регулярное выражение правила TextMatch (потокобезопасный поиск).</summary>
  ITgTextMatcher = interface
    ['{0E5C1B7A-8F42-4D6B-9C3E-7A1D2B4F6E58}']
    function GetPattern: string;
    /// <summary>Найдено совпадение; AArgs — первая группа или всё совпадение.</summary>
    function TryMatch(const AText: string; out AArgs: string): Boolean;
    property Pattern: string read GetPattern;
  end;

  /// <summary>
  ///   TRegEx не потокобезопасен (Match меняет Subject общего TPerlRegEx,
  ///   группы TMatch читаются лениво из него же): поиск — под блокировкой.
  ///   Шаблон компилируется один раз, в конструкторе (ошибка — исключение).
  /// </summary>
  TTgTextMatcher = class(TInterfacedObject, ITgTextMatcher)
  private
    FLock: TCriticalSection;
    FPattern: string;
    FRegEx: TRegEx;
    function DoMatch(const AText: string; out AArgs: string): Boolean;
  public
    constructor Create(const APattern: string);
    destructor Destroy; override;
    function GetPattern: string;
    function TryMatch(const AText: string; out AArgs: string): Boolean;
  end;

  /// <summary>Правило TextMatch.</summary>
  TTgMatchRoute = record
    Matcher: ITgTextMatcher;
    Handler: TProc<ITgContext>;
  end;

  /// <summary>
  ///   Таблица правил — снимок: массивы не меняются на месте (изменение
  ///   создаёт копию под блокировкой ядра), поэтому копия записи, сделанная
  ///   под блокировкой, безопасна для чтения в любом потоке.
  /// </summary>
  TTgRoutes = record
    Lists: array[TTgRouteKind] of TArray<TTgRoute>;
    Matches: TArray<TTgMatchRoute>;
    AnyText: TProc<ITgContext>;
    UnknownCommand: TProc<ITgContext>;
    /// <summary>
    ///   Есть правила message: Command, Text, TextMatch, Text(любой текст),
    ///   OnUnknownCommand.
    /// </summary>
    function HasMessageRules: Boolean;
    /// <summary>Есть правила callback_query: Callback, CallbackPrefix.</summary>
    function HasCallbackRules: Boolean;
  end;

  /// <summary>
  ///   username бота для '/cmd@бот'. ACancel — токен обработчика: его отмена
  ///   прерывает ожидание; '' — username не получен (команда считается
  ///   адресованной другому боту). Ядро передаёт свой ResolveBotUserName
  ///   (ожидание getMe фоновой подготовки, затем ленивый getMe).
  /// </summary>
  TTgBotUserNameResolver = function(const ACancel: ITgCancellation): string of object;

  /// <summary>
  ///   Алгоритм маршрутизации без состояния: ядро передаёт снимок таблицы
  ///   правил (TTgRoutes, сделан под блокировкой ядра); вызывается в потоке
  ///   обработчика.
  /// </summary>
  TTgRouter = record
  private
    /// <summary>
    ///   Вызов обработчика правила с аргументами AArgs; True — обработано
    ///   (обработчик не сбросил Handled). ARef — интерфейсная ссылка на
    ///   AContext, удерживаемая вызывающим.
    /// </summary>
    class function Fire(AContext: TTgContext; const ARef: ITgContext;
      const AHandler: TProc<ITgContext>; const AArgs: string): Boolean; static;
  public
    /// <summary>
    ///   Ключ правила команды по имени без '/' и '@бот' (нижний регистр):
    ///   и при регистрации (NormalizeCommandName), и при разборе сообщения.
    /// </summary>
    class function CommandKey(const AName: string): string; static;
    /// <summary>
    ///   Ключ правила Text по тексту (нижний регистр): и при регистрации,
    ///   и при сравнении с текстом сообщения.
    /// </summary>
    class function TextKey(const AText: string): string; static;
    /// <summary>
    ///   Разбор команды сообщения в Command/Args контекста (SetCommand/
    ///   SetArgs; только команда этому боту: без '@' или '@' + username от
    ///   AResolveBotUserName — вызывается только для '/cmd@бот');
    ///   результат — сообщение является такой командой.
    /// </summary>
    class function ParseCommand(AContext: TTgContext;
      const AResolveBotUserName: TTgBotUserNameResolver): Boolean; static;
    /// <summary>Правила message (итог — AContext.Handled).</summary>
    class procedure RouteMessage(AContext: TTgContext; const ARoutes: TTgRoutes;
      AIsCommand: Boolean); static;
    /// <summary>Правила callback_query.</summary>
    class procedure RouteCallback(AContext: TTgContext; const ARoutes: TTgRoutes); static;
  end;

/// <summary>Текст TTgRouterText на текущем языке библиотеки (TgGetLanguage).</summary>
function TgRouterText(AText: TTgRouterText): string;
/// <summary>Имя команды: без ведущего '/', в нижнем регистре; пустое или с пробелом/'@' — ETgError.</summary>
function NormalizeCommandName(const AName: string): string;
/// <summary>Пустой ключ правила — ETgError (ARule — имя метода регистрации).</summary>
procedure CheckRouteKey(const AKey, ARule: string);

implementation

resourcestring
  SRuRouteEmptyKey = 'Пустой ключ правила маршрутизатора (%s)';
  SEnRouteEmptyKey = 'Empty router rule key (%s)';
  SRuRouteBadCommand = 'Недопустимое имя команды "%s": пробелы и "@" не допускаются';
  SEnRouteBadCommand = 'Invalid command name "%s": spaces and "@" are not allowed';

const
  CRouterTexts: array[TTgRouterText, TTgLanguage] of PResStringRec = (
    (@SRuRouteEmptyKey, @SEnRouteEmptyKey),
    (@SRuRouteBadCommand, @SEnRouteBadCommand)
  );

function TgRouterText(AText: TTgRouterText): string;
begin
  Result := LoadResString(CRouterTexts[AText, TgBot.Base.TgGetLanguage]);
end;

{ TTgTextMatcher }

constructor TTgTextMatcher.Create(const APattern: string);
begin
  inherited Create;
  // Сначала шаблон: при ошибке компиляции блокировка ещё не создана.
  // roCompiled — компиляция здесь (без него TRegEx компилирует при первом
  // поиске, и неверный шаблон проявился бы только в обработчике).
  FRegEx := TRegEx.Create(APattern, [roNotEmpty, roCompiled]);
  FPattern := APattern;
  FLock := TCriticalSection.Create;
end;

destructor TTgTextMatcher.Destroy;
begin
  FreeAndNil(FLock);
  inherited Destroy;
end;

function TTgTextMatcher.GetPattern: string;
begin
  Result := FPattern;
end;

function TTgTextMatcher.DoMatch(const AText: string; out AArgs: string): Boolean;
var
  LMatch: TMatch;
begin
  // Отдельный метод: TMatch (ссылается на общий TPerlRegEx) финализируется
  // до выхода из блокировки TryMatch.
  LMatch := FRegEx.Match(AText);
  Result := LMatch.Success;
  if not Result then
    AArgs := ''
  else if LMatch.Groups.Count > 1 then
    AArgs := LMatch.Groups[1].Value
  else
    AArgs := LMatch.Value;
end;

function TTgTextMatcher.TryMatch(const AText: string; out AArgs: string): Boolean;
begin
  FLock.Enter;
  try
    Result := DoMatch(AText, AArgs);
  finally
    FLock.Leave;
  end;
end;

function NormalizeCommandName(const AName: string): string;
var
  C: Char;
begin
  Result := AName;
  if Copy(Result, 1, 1) = '/' then
    Delete(Result, 1, 1);
  if Result = '' then
    raise ETgError.Create(Format(TgRouterText(TTgRouterText.EmptyKey), ['Command']));
  for C in Result do
    if (C <= ' ') or (C = '@') then
      raise ETgError.Create(Format(TgRouterText(TTgRouterText.BadCommand), [AName]));
  Result := TTgRouter.CommandKey(Result);
end;

procedure CheckRouteKey(const AKey, ARule: string);
begin
  if AKey = '' then
    raise ETgError.Create(Format(TgRouterText(TTgRouterText.EmptyKey), [ARule]));
end;

{ TTgRoutes }

function TTgRoutes.HasMessageRules: Boolean;
begin
  Result := (Length(Lists[TTgRouteKind.Command]) > 0) or
    (Length(Lists[TTgRouteKind.Text]) > 0) or (Length(Matches) > 0) or
    Assigned(AnyText) or Assigned(UnknownCommand);
end;

function TTgRoutes.HasCallbackRules: Boolean;
begin
  Result := (Length(Lists[TTgRouteKind.Callback]) > 0) or
    (Length(Lists[TTgRouteKind.CallbackPrefix]) > 0);
end;

{ TTgRouter }

class function TTgRouter.Fire(AContext: TTgContext; const ARef: ITgContext;
  const AHandler: TProc<ITgContext>; const AArgs: string): Boolean;
begin
  AContext.SetArgs(AArgs);
  AContext.SetHandled(True);
  AHandler(ARef);
  Result := AContext.GetHandled;
end;

class function TTgRouter.CommandKey(const AName: string): string;
begin
  Result := AnsiLowerCase(AName);
end;

class function TTgRouter.TextKey(const AText: string): string;
begin
  Result := AnsiLowerCase(AText);
end;

class function TTgRouter.ParseCommand(AContext: TTgContext;
  const AResolveBotUserName: TTgBotUserNameResolver): Boolean;
var
  LText, LToken, LName, LBot: string;
  LEnd, LAt: Integer;
begin
  Result := False;
  LText := AContext.MessageText;
  if (Length(LText) < 2) or (LText[1] <> '/') then
    Exit;
  // Команда — до первого пробельного символа: '/name[@bot] аргументы'.
  LEnd := 2;
  while (LEnd <= Length(LText)) and (LText[LEnd] > ' ') do
    Inc(LEnd);
  LToken := Copy(LText, 2, LEnd - 2);
  LAt := Pos('@', LToken);
  if LAt > 0 then
  begin
    LName := Copy(LToken, 1, LAt - 1);
    LBot := Copy(LToken, LAt + 1, MaxInt);
  end
  else
  begin
    LName := LToken;
    LBot := '';
  end;
  if LName = '' then
    Exit;
  // username в Telegram без учёта регистра (латиница, цифры, '_').
  if (LBot <> '') and not SameText(LBot, AResolveBotUserName(AContext.GetCancel)) then
    Exit;
  AContext.SetCommand(CommandKey(LName));
  AContext.SetArgs(Trim(Copy(LText, LEnd, MaxInt)));
  Result := True;
end;

class procedure TTgRouter.RouteMessage(AContext: TTgContext; const ARoutes: TTgRoutes;
  AIsCommand: Boolean);
var
  LRef: ITgContext;
  LText, LLower, LCommandArgs, LArgs: string;
  LRoute: TTgRoute;
  LMatch: TTgMatchRoute;
  LFound: Boolean;
begin
  LRef := AContext;
  LCommandArgs := AContext.GetArgs;
  if AIsCommand then
  begin
    LFound := False;
    for LRoute in ARoutes.Lists[TTgRouteKind.Command] do
      if LRoute.Key = AContext.GetCommand then
      begin
        LFound := True;
        if Fire(AContext, LRef, LRoute.Handler, LCommandArgs) then
          Exit;
        Break;
      end;
    if not LFound and Assigned(ARoutes.UnknownCommand) and
      Fire(AContext, LRef, ARoutes.UnknownCommand, LCommandArgs) then
      Exit;
  end;
  LText := AContext.MessageText;
  if LText = '' then
    Exit;
  LLower := TextKey(LText);
  for LRoute in ARoutes.Lists[TTgRouteKind.Text] do
    if LRoute.Key = LLower then
    begin
      if Fire(AContext, LRef, LRoute.Handler, LCommandArgs) then
        Exit;
      Break;
    end;
  for LMatch in ARoutes.Matches do
    if LMatch.Matcher.TryMatch(LText, LArgs) and Fire(AContext, LRef, LMatch.Handler, LArgs) then
      Exit;
  if Assigned(ARoutes.AnyText) then
    Fire(AContext, LRef, ARoutes.AnyText, LCommandArgs);
end;

class procedure TTgRouter.RouteCallback(AContext: TTgContext; const ARoutes: TTgRoutes);
var
  LRef: ITgContext;
  LData: string;
  LRoute: TTgRoute;
begin
  LRef := AContext;
  LData := AContext.GetData;
  if LData = '' then
    Exit;
  for LRoute in ARoutes.Lists[TTgRouteKind.Callback] do
    if LRoute.Key = LData then
    begin
      if Fire(AContext, LRef, LRoute.Handler, '') then
        Exit;
      Break;
    end;
  for LRoute in ARoutes.Lists[TTgRouteKind.CallbackPrefix] do
    if (Copy(LData, 1, Length(LRoute.Key)) = LRoute.Key) and
      Fire(AContext, LRef, LRoute.Handler, Copy(LData, Length(LRoute.Key) + 1, MaxInt)) then
      Exit;
end;

end.
