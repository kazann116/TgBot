unit TgBotGen.Emitter;

{
  TgBotGen — генерация .inc-файлов библиотеки TgBot по результатам анализа.

  Файлы (раскладка для ручного модуля TgBot.pas):
    interface, один type-блок:
      Gen.Forward.inc    — forward-объявления интерфейсов;
      Gen.Enums.inc      — enum Kind полиморфных типов, записи констант;
      Gen.Unions.inc     — записи-объединения (исходящие union, алиасы);
      Gen.Intf.inc       — интерфейсы (топологический порядок);
      Gen.Factories.inc  — record-фабрики TTg<Name> (Create, FromJson);
      Gen.Options.inc    — записи необязательных параметров методов;
      Gen.Methods.inc    — объявления методов TTgApi (внутри класса: private-хелперы
                           Build*Params/Exec*, затем public-методы и их варианты
                           из overrides methods.*.variants);
    implementation:
      Gen.ImplClasses.inc — скрытые классы реализации (с type);
      Gen.ImplMake.inc    — фабрики DTO из JSON (TgMake<Name>);
      Gen.ImplTypes.inc   — тела классов, фабрик и записей-объединений;
      Gen.ImplMethods.inc — ApplyTo записей опций и методы TTgApi.

  Файлы пишутся в UTF-8 с BOM и переводами строк CRLF. Генерация атомарна:
  все файлы создаются во временной папке рядом с целевой и только после
  успешного завершения заменяют прежние (каждый файл — атомарной заменой).
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.Classes,
  System.Generics.Collections,
  TgBotGen.Model,
  TgBotGen.Analysis;

type
  /// <summary>Писатель исходного кода с отступами.</summary>
  TGenCodeWriter = class
  private
    FLines: TStringList;
    FIndent: Integer;
    function Prefix: string;
  public
    constructor Create;
    destructor Destroy; override;
    /// <summary>Строка с текущим отступом (пустая — без отступа).</summary>
    procedure Add(const AText: string = '');
    /// <summary>
    ///   Строка объявления; при длине больше 100 символов переносится
    ///   по '; ' и ', ' (не внутри скобок &lt;&gt; и строковых литералов).
    /// </summary>
    procedure AddWrapped(const AText: string);
    /// <summary>XML-комментарий /// &lt;summary&gt; с переносом по словам.</summary>
    procedure Doc(const AText: string);
    procedure Indent;
    procedure Outdent;
    /// <summary>Сохраняет в UTF-8 с BOM, CRLF.</summary>
    procedure SaveToFile(const AFileName: string);
    function LineCount: Integer;
  end;

  /// <summary>Генератор .inc-файлов.</summary>
  TGenEmitter = class
  private
    FAnalysis: TGenAnalysis;
    FOutDir: string;
    FWorkDir: string;
    FFiles: TStringList;
    function NewWriter(const ATitle: string): TGenCodeWriter;
    procedure Save(AWriter: TGenCodeWriter; const AFileName: string);
    // типы
    function ElemType(const AValue: TGenValue): string;
    function ValueType(const AValue: TGenValue): string;
    function ParamDecl(const AValue: TGenValue; const AName: string): string;
    function OptionType(const AValue: TGenValue): string;
    function ResultType(const AValue: TGenValue): string;
    function ReadExpr(const AValue: TGenValue; const AJsonName: string): string;
    function WriteStmt(const AValue: TGenValue; const AJsonName, AExpr: string): string;
    function ConstStmt(AMember: TGenMemberInfo): string;
    function ParamsAddStmt(const AValue: TGenValue; const AParamsVar, AJsonName, AExpr: string): string;
    function OptionalCond(const AValue: TGenValue; const AExpr: string): string;
    function OptionalValue(const AValue: TGenValue; const AExpr: string): string;
    function ResultExpr(AMethod: TGenMethodInfo): string;
    function IsOpenArray(const AValue: TGenValue): Boolean;
    function OptionDoc(AParam: TGenMemberInfo): string;
    // типы и члены
    function IncludedTypes: TArray<TGenTypeInfo>;
    function ParentIntf(AInfo: TGenTypeInfo): string;
    function ParentImpl(AInfo: TGenTypeInfo): string;
    function ImplInterfaces(AInfo: TGenTypeInfo): string;
    function OwnGetters(AInfo: TGenTypeInfo): TArray<TGenMemberInfo>;
    function Writable(AInfo: TGenTypeInfo): TArray<TGenMemberInfo>;
    function CreateArgs(AInfo: TGenTypeInfo): TArray<TGenMemberInfo>;
    function HasWith(AInfo: TGenTypeInfo): Boolean;
    function HasCreate(AInfo: TGenTypeInfo): Boolean;
    function HasMake(AInfo: TGenTypeInfo): Boolean;
    function KindRef(ABase, AVariant: TGenTypeInfo): string;
    function CreateSignature(AInfo: TGenTypeInfo; AQualified: Boolean): string;
    // методы
    function MethodArgs(AMethod: TGenMethodInfo; AWithOptions: Boolean): string;
    function MethodCallArgs(AMethod: TGenMethodInfo; const APrefix: string; AWithOptions: Boolean): string;
    function SyncDecl(AMethod: TGenMethodInfo; AWithOptions, AQualified: Boolean): string;
    function AsyncDecl(AMethod: TGenMethodInfo; AWithOptions, AQualified: Boolean): string;
    function TryDecl(AMethod: TGenMethodInfo; AWithOptions, AQualified: Boolean): string;
    function BuildDecl(AMethod: TGenMethodInfo; AQualified: Boolean): string;
    function ExecDecl(AMethod: TGenMethodInfo; AQualified: Boolean): string;
    function VariantDoc(AVariant: TGenMethodInfo): string;
    // файлы
    procedure EmitForward;
    procedure EmitEnums;
    procedure EmitUnions;
    procedure EmitIntf;
    procedure EmitFactories;
    procedure EmitOptions;
    procedure EmitMethods;
    procedure EmitImplClasses;
    procedure EmitImplMake;
    procedure EmitImplTypes;
    procedure EmitImplMethods;
    procedure EmitClassBodies(W: TGenCodeWriter; AInfo: TGenTypeInfo);
    procedure EmitMethodDecls(W: TGenCodeWriter; AMethod: TGenMethodInfo);
    procedure EmitMethodBodies(W: TGenCodeWriter; AMethod: TGenMethodInfo);
    procedure EmitVariantBuild(W: TGenCodeWriter; AVariant: TGenMethodInfo);
  public
    constructor Create(AAnalysis: TGenAnalysis; const AOutDir: string);
    destructor Destroy; override;
    /// <summary>
    ///   Генерирует все файлы (атомарно: временная папка → замена).
    ///   Ошибки анализа — EGenAnalysisError; при любой ошибке прежние файлы не меняются.
    /// </summary>
    procedure Generate;
    /// <summary>Созданные файлы: 'имя=число строк'.</summary>
    property Files: TStringList read FFiles;
  end;

/// <summary>Идентификатор Delphi с экранированием ключевых слов и директив видимости.</summary>
function GenIdent(const AName: string): string;

implementation

uses
{$IFDEF MSWINDOWS}
  Winapi.Windows,
{$ENDIF}
  System.StrUtils,
  System.IOUtils,
  System.RegularExpressions;

const
  CLineWidth = 100;
  CVisibilityWords: array[0..5] of string = ('private', 'protected', 'public', 'published',
    'strict', 'automated');
  // Типы, к полям которых добавляется подсказка о построителе клавиатур.
  CInlineKeyboardType = 'InlineKeyboardMarkup';
  CReplyMarkupUnion = 'ReplyMarkup';

function GenIdent(const AName: string): string;
begin
  if TGenAnalysis.IsKeyword(AName) or MatchText(AName, CVisibilityWords) then
    Result := '&' + AName
  else
    Result := AName;
end;

function Q(const AText: string): string;
begin
  Result := QuotedStr(AText);
end;

function XmlEscape(const AText: string): string;
begin
  Result := StringReplace(AText, '&', '&amp;', [rfReplaceAll]);
  Result := StringReplace(Result, '<', '&lt;', [rfReplaceAll]);
  Result := StringReplace(Result, '>', '&gt;', [rfReplaceAll]);
end;

/// <summary>
///   Убирает вводные фразы спецификации перед списком вариантов («It should be
///   one of», «Currently, it can be one of»): сам список в описание не попадает.
/// </summary>
function CleanDescription(const AText: string): string;
begin
  Result := TRegEx.Replace(AText,
    '[ \t]*(?:Currently, it can be one of|It (?:should|can|must) be one of)[ \t]*:?[ \t]*(?=\n|$)', '',
    [roIgnoreCase]);
end;

/// <summary>Текст, завершённый точкой (для дописывания следующего предложения).</summary>
function Sentence(const AText: string): string;
begin
  Result := TrimRight(AText);
  if (Result <> '') and not CharInSet(Result[Length(Result)], ['.', '!', '?', ':']) then
    Result := Result + '.';
end;

/// <summary>Заменяет ADest файлом ASource (на Windows — атомарно).</summary>
procedure MoveReplace(const ASource, ADest: string);
begin
{$IFDEF MSWINDOWS}
  if not MoveFileEx(PChar(ASource), PChar(ADest), MOVEFILE_REPLACE_EXISTING or MOVEFILE_WRITE_THROUGH) then
    raise EInOutError.CreateFmt('Не удалось заменить %s: %s', [ADest, SysErrorMessage(GetLastError)]);
{$ELSE}
  if TFile.Exists(ADest) then
    TFile.Delete(ADest);
  TFile.Move(ASource, ADest);
{$ENDIF}
end;

function FirstParagraph(const AText: string): string;
var
  LPos: Integer;
begin
  LPos := Pos(#10, AText);
  if LPos > 0 then
    Result := Copy(AText, 1, LPos - 1)
  else
    Result := AText;
end;

function JoinArgs(const AItems: TArray<string>; const ASeparator: string): string;
var
  I: Integer;
begin
  Result := '';
  for I := 0 to High(AItems) do
  begin
    if I > 0 then
      Result := Result + ASeparator;
    Result := Result + AItems[I];
  end;
end;

/// <summary>Аргументы вызова через ', ' без пустых элементов.</summary>
function JoinCall(const AItems: array of string): string;
var
  LItem: string;
begin
  Result := '';
  for LItem in AItems do
    if LItem <> '' then
    begin
      if Result <> '' then
        Result := Result + ', ';
      Result := Result + LItem;
    end;
end;

/// <summary>AName или AName(AArgs), если аргументы есть.</summary>
function CallText(const AName, AArgs: string): string;
begin
  if AArgs = '' then
    Result := AName
  else
    Result := AName + '(' + AArgs + ')';
end;

{ TGenCodeWriter }

constructor TGenCodeWriter.Create;
begin
  inherited Create;
  FLines := TStringList.Create;
  FLines.LineBreak := #13#10;
end;

destructor TGenCodeWriter.Destroy;
begin
  FLines.Free;
  inherited Destroy;
end;

function TGenCodeWriter.Prefix: string;
begin
  Result := StringOfChar(' ', FIndent * 2);
end;

procedure TGenCodeWriter.Add(const AText: string);
begin
  if AText = '' then
    FLines.Add('')
  else
    FLines.Add(Prefix + AText);
end;

procedure TGenCodeWriter.AddWrapped(const AText: string);
var
  LLine, LRest, LCont: string;
  LDepth, I, LBreak, LLimit: Integer;
  LInQuote: Boolean;
begin
  LRest := AText;
  LCont := '';
  LLimit := CLineWidth - Length(Prefix);
  while Length(LCont + LRest) > LLimit do
  begin
    // Последняя точка переноса '; ' или ', ' вне <>, () и строковых литералов
    // до границы строки (удвоенная кавычка внутри литерала переключает дважды).
    LBreak := 0;
    LDepth := 0;
    LInQuote := False;
    for I := 1 to Length(LRest) do
    begin
      if LRest[I] = '''' then
        LInQuote := not LInQuote
      else if not LInQuote then
        case LRest[I] of
          '<', '(', '[': Inc(LDepth);
          '>', ')', ']': Dec(LDepth);
        end;
      if Length(LCont) + I > LLimit then
        Break;
      if not LInQuote and ((LDepth = 1) or (LDepth = 0)) and (I < Length(LRest)) and
        CharInSet(LRest[I], [';', ',']) and (LRest[I + 1] = ' ') then
        LBreak := I;
    end;
    if LBreak = 0 then
      Break;
    LLine := Copy(LRest, 1, LBreak);
    Add(LCont + LLine);
    LRest := Copy(LRest, LBreak + 2, MaxInt);
    LCont := '  ';
  end;
  Add(LCont + LRest);
end;

procedure TGenCodeWriter.Doc(const AText: string);
var
  LWords: TArray<string>;
  LWord, LLine: string;
  LWidth: Integer;
begin
  if Trim(AText) = '' then
    Exit;
  LWidth := CLineWidth - Length(Prefix) - 6;
  LWords := XmlEscape(StringReplace(Trim(AText), #10, ' ', [rfReplaceAll])).Split([' '],
    TStringSplitOptions.ExcludeEmpty);
  if Length(XmlEscape(AText)) + 25 <= LWidth then
  begin
    Add('/// <summary>' + JoinArgs(LWords, ' ') + '</summary>');
    Exit;
  end;
  Add('/// <summary>');
  LLine := '';
  for LWord in LWords do
  begin
    if (LLine <> '') and (Length(LLine) + 1 + Length(LWord) > LWidth) then
    begin
      Add('///   ' + LLine);
      LLine := '';
    end;
    if LLine = '' then
      LLine := LWord
    else
      LLine := LLine + ' ' + LWord;
  end;
  if LLine <> '' then
    Add('///   ' + LLine);
  Add('/// </summary>');
end;

procedure TGenCodeWriter.Indent;
begin
  Inc(FIndent);
end;

procedure TGenCodeWriter.Outdent;
begin
  if FIndent > 0 then
    Dec(FIndent);
end;

procedure TGenCodeWriter.SaveToFile(const AFileName: string);
begin
  FLines.WriteBOM := True;
  FLines.SaveToFile(AFileName, TEncoding.UTF8);
end;

function TGenCodeWriter.LineCount: Integer;
begin
  Result := FLines.Count;
end;

{ TGenEmitter }

constructor TGenEmitter.Create(AAnalysis: TGenAnalysis; const AOutDir: string);
begin
  inherited Create;
  FAnalysis := AAnalysis;
  FOutDir := AOutDir;
  FFiles := TStringList.Create;
end;

destructor TGenEmitter.Destroy;
begin
  FFiles.Free;
  inherited Destroy;
end;

function TGenEmitter.NewWriter(const ATitle: string): TGenCodeWriter;
var
  LModel: TGenModel;
begin
  LModel := FAnalysis.Model;
  Result := TGenCodeWriter.Create;
  Result.Add('// ' + ATitle);
  Result.Add('// Сгенерировано TgBotGen по Telegram Bot API ' + LModel.Version + ' (' + LModel.Date +
    '). Не редактируйте вручную.');
  if FAnalysis.Restricted then
    Result.Add('// Подмножество типов и методов (--only) с транзитивными зависимостями.');
  Result.Add('');
end;

procedure TGenEmitter.Save(AWriter: TGenCodeWriter; const AFileName: string);
begin
  try
    AWriter.SaveToFile(TPath.Combine(FWorkDir, AFileName));
    FFiles.Add(AFileName + '=' + IntToStr(AWriter.LineCount));
  finally
    AWriter.Free;
  end;
end;

{ отображение типов }

function TGenEmitter.ElemType(const AValue: TGenValue): string;
begin
  case AValue.Kind of
    TGenValueKind.Str: Result := 'string';
    TGenValueKind.Int: Result := 'Integer';
    TGenValueKind.Int64: Result := 'Int64';
    TGenValueKind.Float: Result := 'Double';
    TGenValueKind.Bool, TGenValueKind.TrueValue: Result := 'Boolean';
    TGenValueKind.ChatId: Result := 'TTgChatId';
    TGenValueKind.InputFile: Result := 'TTgInputFile';
    TGenValueKind.Obj: Result := 'ITg' + AValue.TypeName;
  else
    Result := 'TTg' + AValue.TypeName;
  end;
end;

function TGenEmitter.ValueType(const AValue: TGenValue): string;
var
  I: Integer;
begin
  Result := ElemType(AValue);
  for I := 1 to AValue.Depth do
    Result := 'TArray<' + Result + '>';
end;

function TGenEmitter.IsOpenArray(const AValue: TGenValue): Boolean;
begin
  Result := AValue.IsArray and (AValue.Kind in [TGenValueKind.Obj, TGenValueKind.UnionRec]);
end;

function TGenEmitter.ParamDecl(const AValue: TGenValue; const AName: string): string;
var
  LType: string;
begin
  if IsOpenArray(AValue) then
  begin
    if AValue.Depth = 1 then
      LType := 'array of ' + ElemType(AValue)
    else
      LType := 'array of TArray<' + ElemType(AValue) + '>';
  end
  else
    LType := ValueType(AValue);
  if AValue.IsArray or not (AValue.Kind in [TGenValueKind.Int, TGenValueKind.Int64,
    TGenValueKind.Float, TGenValueKind.Bool, TGenValueKind.TrueValue]) then
    Result := 'const ' + AName + ': ' + LType
  else
    Result := AName + ': ' + LType;
end;

function TGenEmitter.OptionType(const AValue: TGenValue): string;
begin
  // Массивы — тоже опциональные: [] передаётся как пустой список, «не задано» — не передаётся.
  if AValue.IsArray or (AValue.Kind in [TGenValueKind.Str, TGenValueKind.Int,
    TGenValueKind.Int64, TGenValueKind.Float, TGenValueKind.Bool, TGenValueKind.TrueValue]) then
    Result := 'TTgOptional<' + ValueType(AValue) + '>'
  else
    Result := ValueType(AValue);
end;

function TGenEmitter.ResultType(const AValue: TGenValue): string;
begin
  Result := ValueType(AValue);
end;

function TGenEmitter.ReadExpr(const AValue: TGenValue; const AJsonName: string): string;
var
  LInfo: TGenTypeInfo;
  LMake: string;
begin
  if AValue.Kind = TGenValueKind.Obj then
  begin
    LInfo := FAnalysis.FindType(AValue.TypeName);
    LMake := LInfo.MakeName;
    case AValue.Depth of
      0: Exit(LMake + '(TTgJson.GetValue(FJson, ' + Q(AJsonName) + '), JsonOwner)');
      1: Exit('TTgDto.Objects<' + ElemType(AValue) + '>(TTgJson.GetArr(FJson, ' + Q(AJsonName) +
        '), JsonOwner, ' + LMake + ')');
    else
      Exit('TTgDto.Objects2<' + ElemType(AValue) + '>(TTgJson.GetArr(FJson, ' + Q(AJsonName) +
        '), JsonOwner, ' + LMake + ')');
    end;
  end;
  if AValue.Depth = 1 then
  begin
    case AValue.Kind of
      TGenValueKind.Str: Result := 'TTgDto.Strings';
      TGenValueKind.Int: Result := 'TTgDto.Integers';
      TGenValueKind.Int64: Result := 'TTgDto.Int64s';
      TGenValueKind.Float: Result := 'TTgDto.Doubles';
      TGenValueKind.Bool, TGenValueKind.TrueValue: Result := 'TTgDto.Booleans';
    else
      raise EGenAnalysisError.CreateFmt('Чтение массива «%s» (%s) не поддерживается',
        [AJsonName, AValue.ToString]);
    end;
    if AValue.Kind in [TGenValueKind.Int, TGenValueKind.Int64, TGenValueKind.Float] then
      Exit(Result + '(TTgJson.GetArr(FJson, ' + Q(AJsonName) + '), ' + Q(AJsonName) + ')');
    Exit(Result + '(TTgJson.GetArr(FJson, ' + Q(AJsonName) + '))');
  end;
  if AValue.Depth > 1 then
    raise EGenAnalysisError.CreateFmt('Чтение «%s» (%s) не поддерживается', [AJsonName, AValue.ToString]);
  case AValue.Kind of
    TGenValueKind.Str: Result := 'TTgJson.GetStr';
    TGenValueKind.Int: Result := 'TTgJson.GetInt';
    TGenValueKind.Int64: Result := 'TTgJson.GetInt64';
    TGenValueKind.Float: Result := 'TTgJson.GetDouble';
    TGenValueKind.Bool, TGenValueKind.TrueValue: Result := 'TTgJson.GetBool';
    TGenValueKind.ChatId: Result := 'TTgDto.GetChatId';
  else
    raise EGenAnalysisError.CreateFmt('Чтение «%s» (%s) во входящем типе не поддерживается',
      [AJsonName, AValue.ToString]);
  end;
  Result := Result + '(FJson, ' + Q(AJsonName) + ')';
end;

function TGenEmitter.WriteStmt(const AValue: TGenValue; const AJsonName, AExpr: string): string;
var
  LName: string;
begin
  LName := Q(AJsonName);
  if AValue.Depth = 0 then
  begin
    case AValue.Kind of
      TGenValueKind.Str: Result := 'SetStr(' + LName + ', ' + AExpr + ');';
      TGenValueKind.Int: Result := 'SetInt(' + LName + ', ' + AExpr + ');';
      TGenValueKind.Int64: Result := 'SetInt64(' + LName + ', ' + AExpr + ');';
      TGenValueKind.Float: Result := 'SetDouble(' + LName + ', ' + AExpr + ');';
      TGenValueKind.Bool, TGenValueKind.TrueValue: Result := 'SetBool(' + LName + ', ' + AExpr + ');';
      TGenValueKind.ChatId: Result := 'SetChatId(' + LName + ', ' + AExpr + ');';
      TGenValueKind.InputFile: Result := 'SetFile(' + LName + ', ' + AExpr + ');';
      TGenValueKind.Obj: Result := 'SetObject(' + LName + ', ' + AExpr + ');';
    else
      Result := 'SetObject(' + LName + ', ' + AExpr + '.Value);';
    end;
    Exit;
  end;
  case AValue.Kind of
    TGenValueKind.Obj:
      if AValue.Depth = 1 then
        Exit('SetObjects(' + LName + ', TTgDto.ToIntf<' + ElemType(AValue) + '>(' + AExpr + '));')
      else
        Exit('SetObjects2(' + LName + ', TTgDto.ToIntf2<' + ElemType(AValue) + '>(' + AExpr + '));');
    TGenValueKind.UnionRec:
      if AValue.Depth = 1 then
        Exit('SetObjects(' + LName + ', ' + ElemType(AValue) + '.Values(' + AExpr + '));');
  end;
  if AValue.Depth = 1 then
    case AValue.Kind of
      TGenValueKind.Str: Exit('SetStrings(' + LName + ', ' + AExpr + ');');
      TGenValueKind.Int: Exit('SetIntegers(' + LName + ', ' + AExpr + ');');
      TGenValueKind.Int64: Exit('SetInt64s(' + LName + ', ' + AExpr + ');');
      TGenValueKind.Float: Exit('SetDoubles(' + LName + ', ' + AExpr + ');');
      TGenValueKind.Bool, TGenValueKind.TrueValue: Exit('SetBooleans(' + LName + ', ' + AExpr + ');');
    end;
  raise EGenAnalysisError.CreateFmt('Запись «%s» (%s) не поддерживается', [AJsonName, AValue.ToString]);
end;

function TGenEmitter.ConstStmt(AMember: TGenMemberInfo): string;
var
  LValue: string;
begin
  LValue := AMember.ConstValue;
  case AMember.Value.Kind of
    TGenValueKind.Bool, TGenValueKind.TrueValue:
      Result := 'SetBool(' + Q(AMember.Name) + ', ' + IfThen(SameText(LValue, 'false'), 'False', 'True') + ');';
    TGenValueKind.Int, TGenValueKind.Int64:
      Result := 'SetInt64(' + Q(AMember.Name) + ', ' + IntToStr(StrToInt64(LValue)) + ');';
  else
    Result := 'SetStr(' + Q(AMember.Name) + ', ' + Q(LValue) + ');';
  end;
end;

function TGenEmitter.ParamsAddStmt(const AValue: TGenValue; const AParamsVar, AJsonName,
  AExpr: string): string;
var
  LName, P: string;
begin
  LName := Q(AJsonName);
  P := AParamsVar;
  if AValue.Depth = 0 then
  begin
    case AValue.Kind of
      TGenValueKind.ChatId: Result := P + '.AddChatId(' + LName + ', ' + AExpr + ');';
      TGenValueKind.InputFile: Result := P + '.AddFile(' + LName + ', ' + AExpr + ');';
      TGenValueKind.Obj: Result := P + '.AddJson(' + LName + ', TTgDto.Serialize(' + AExpr + ', ' + P + '));';
      TGenValueKind.UnionRec:
        Result := P + '.AddJson(' + LName + ', TTgDto.Serialize(' + AExpr + '.Value, ' + P + '));';
    else
      Result := P + '.Add(' + LName + ', ' + AExpr + ');';
    end;
    Exit;
  end;
  case AValue.Kind of
    TGenValueKind.Obj:
      if AValue.Depth = 1 then
        Exit(P + '.AddJson(' + LName + ', TTgDto.SerializeArray(TTgDto.ToIntf<' + ElemType(AValue) +
          '>(' + AExpr + '), ' + P + ', ' + LName + '));')
      else
        Exit(P + '.AddJson(' + LName + ', TTgDto.SerializeArray2(TTgDto.ToIntf2<' + ElemType(AValue) +
          '>(' + AExpr + '), ' + P + ', ' + LName + '));');
    TGenValueKind.UnionRec:
      if AValue.Depth = 1 then
        Exit(P + '.AddJson(' + LName + ', TTgDto.SerializeArray(' + ElemType(AValue) + '.Values(' + AExpr +
          '), ' + P + ', ' + LName + '));');
  end;
  if AValue.Depth = 1 then
    case AValue.Kind of
      TGenValueKind.Str: Exit(P + '.AddStrings(' + LName + ', ' + AExpr + ');');
      TGenValueKind.Int64: Exit(P + '.AddInt64s(' + LName + ', ' + AExpr + ');');
      TGenValueKind.Int: Exit(P + '.AddJson(' + LName + ', TTgDto.IntegersJson(' + AExpr + '));');
      TGenValueKind.Float: Exit(P + '.AddJson(' + LName + ', TTgDto.DoublesJson(' + AExpr + ', ' + LName + '));');
      TGenValueKind.Bool, TGenValueKind.TrueValue:
        Exit(P + '.AddJson(' + LName + ', TTgDto.BooleansJson(' + AExpr + '));');
    end;
  raise EGenAnalysisError.CreateFmt('Параметр «%s» (%s) не поддерживается', [AJsonName, AValue.ToString]);
end;

function TGenEmitter.OptionalCond(const AValue: TGenValue; const AExpr: string): string;
begin
  if AValue.IsArray then
    Exit(AExpr + '.HasValue');
  case AValue.Kind of
    TGenValueKind.ChatId, TGenValueKind.InputFile, TGenValueKind.UnionRec:
      Result := 'not ' + AExpr + '.IsEmpty';
    TGenValueKind.Obj:
      Result := 'System.Assigned(' + AExpr + ')';
  else
    Result := AExpr + '.HasValue';
  end;
end;

function TGenEmitter.OptionalValue(const AValue: TGenValue; const AExpr: string): string;
begin
  if AValue.IsArray or (AValue.Kind in [TGenValueKind.Str, TGenValueKind.Int,
    TGenValueKind.Int64, TGenValueKind.Float, TGenValueKind.Bool, TGenValueKind.TrueValue]) then
    Result := AExpr + '.Value'
  else
    Result := AExpr;
end;

function TGenEmitter.ResultExpr(AMethod: TGenMethodInfo): string;
var
  LValue: TGenValue;
  LMake, LName: string;
begin
  LValue := AMethod.Result;
  LName := Q(AMethod.Name);
  if LValue.Kind = TGenValueKind.Obj then
  begin
    LMake := FAnalysis.FindType(LValue.TypeName).MakeName;
    if LValue.IsArray then
      Exit('TTgDto.ResultArray<' + ElemType(LValue) + '>(LValue, ' + LName + ', ' + LMake + ')');
    if LValue.OrTrue then
      Exit('TTgDto.ResultObjectOrTrue<' + ElemType(LValue) + '>(LValue, ' + LName + ', ' + LMake + ')');
    Exit('TTgDto.ResultObject<' + ElemType(LValue) + '>(LValue, ' + LName + ', ' + LMake + ')');
  end;
  case LValue.Kind of
    TGenValueKind.Str: Result := 'TTgDto.ResultStr';
    TGenValueKind.Int: Result := 'TTgDto.ResultInt';
    TGenValueKind.Int64: Result := 'TTgDto.ResultInt64';
    TGenValueKind.Float: Result := 'TTgDto.ResultDouble';
  else
    Result := 'TTgDto.ResultBool';
  end;
  Result := Result + '(LValue, ' + LName + ')';
end;

{ типы и члены }

function TGenEmitter.IncludedTypes: TArray<TGenTypeInfo>;
var
  LInfo: TGenTypeInfo;
begin
  Result := nil;
  for LInfo in FAnalysis.Ordered do
    if LInfo.Included then
      Result := Result + [LInfo];
end;

function TGenEmitter.ParentIntf(AInfo: TGenTypeInfo): string;
begin
  if Assigned(AInfo.Base) then
    Result := AInfo.Base.IntfName
  else if AInfo.IsIn then
    Result := 'ITgJsonObject'
  else
    Result := 'ITgOutObject';
end;

function TGenEmitter.ParentImpl(AInfo: TGenTypeInfo): string;
begin
  if Assigned(AInfo.Base) then
    Result := AInfo.Base.ImplName
  else if AInfo.IsIn then
    Result := 'TTgJsonDto'
  else
    Result := 'TTgOutObject';
end;

function TGenEmitter.ImplInterfaces(AInfo: TGenTypeInfo): string;
var
  LBase: TGenTypeInfo;
begin
  Result := AInfo.IntfName;
  LBase := AInfo.Base;
  while Assigned(LBase) do
  begin
    Result := Result + ', ' + LBase.IntfName;
    LBase := LBase.Base;
  end;
end;

function TGenEmitter.OwnGetters(AInfo: TGenTypeInfo): TArray<TGenMemberInfo>;
var
  LMember: TGenMemberInfo;
begin
  Result := nil;
  if not AInfo.IsIn then
    Exit;
  for LMember in AInfo.Members do
    if not LMember.Hidden and not (Assigned(AInfo.Base) and LMember.IsCommon) then
      Result := Result + [LMember];
end;

function TGenEmitter.HasWith(AInfo: TGenTypeInfo): Boolean;
begin
  Result := AInfo.IsOut and (AInfo.Category = TGenCategory.Regular);
end;

function TGenEmitter.Writable(AInfo: TGenTypeInfo): TArray<TGenMemberInfo>;
var
  LMember: TGenMemberInfo;
begin
  Result := nil;
  if not HasWith(AInfo) then
    Exit;
  for LMember in AInfo.Members do
    if not LMember.Hidden and (LMember.ConstValue = '') then
      Result := Result + [LMember];
end;

function TGenEmitter.CreateArgs(AInfo: TGenTypeInfo): TArray<TGenMemberInfo>;
var
  LMember: TGenMemberInfo;
begin
  Result := nil;
  for LMember in Writable(AInfo) do
    if LMember.Required then
      Result := Result + [LMember];
end;

function TGenEmitter.HasCreate(AInfo: TGenTypeInfo): Boolean;
begin
  Result := AInfo.IsOut and (AInfo.Category in [TGenCategory.Regular, TGenCategory.PlainVariant,
    TGenCategory.ListVariant]);
end;

function TGenEmitter.HasMake(AInfo: TGenTypeInfo): Boolean;
begin
  Result := AInfo.IsIn and not AInfo.IsSynthetic;
end;

function TGenEmitter.KindRef(ABase, AVariant: TGenTypeInfo): string;
begin
  if Assigned(AVariant) then
    Result := ABase.KindEnumName + '.' + GenIdent(AVariant.KindName)
  else
    Result := ABase.KindEnumName + '.Unknown';
end;

function TGenEmitter.CreateSignature(AInfo: TGenTypeInfo; AQualified: Boolean): string;
var
  LArgs: TArray<string>;
  LMember: TGenMemberInfo;
  LName: string;
begin
  LArgs := nil;
  case AInfo.Category of
    TGenCategory.PlainVariant:
      LArgs := ['const AText: string'];
    TGenCategory.ListVariant:
      LArgs := ['const AItems: array of ' + AInfo.Base.IntfName];
  else
    for LMember in CreateArgs(AInfo) do
      LArgs := LArgs + [ParamDecl(LMember.Value, LMember.ArgName)];
  end;
  if AQualified then
    LName := AInfo.RecName + '.Create'
  else
    LName := 'Create';
  if Length(LArgs) = 0 then
    Result := 'class function ' + LName + ': ' + AInfo.IntfName + ';'
  else
    Result := 'class function ' + LName + '(' + JoinArgs(LArgs, '; ') + '): ' + AInfo.IntfName + ';';
  if not AQualified then
    Result := Result + ' static;';
end;

{ методы }

function TGenEmitter.MethodArgs(AMethod: TGenMethodInfo; AWithOptions: Boolean): string;
var
  LArgs: TArray<string>;
  LParam: TGenMemberInfo;
begin
  LArgs := nil;
  for LParam in AMethod.Positional do
    LArgs := LArgs + [ParamDecl(LParam.Value, LParam.ArgName)];
  if AWithOptions then
    LArgs := LArgs + ['const AOptions: ' + AMethod.OptionsName];
  Result := JoinArgs(LArgs, '; ');
end;

function TGenEmitter.MethodCallArgs(AMethod: TGenMethodInfo; const APrefix: string;
  AWithOptions: Boolean): string;
var
  LArgs: TArray<string>;
  LParam: TGenMemberInfo;
begin
  LArgs := nil;
  for LParam in AMethod.Positional do
    LArgs := LArgs + [LParam.ArgName];
  if AWithOptions then
    LArgs := LArgs + [APrefix + 'Options'];
  Result := JoinArgs(LArgs, ', ');
end;

function JoinDecl(const AFirst, ASecond: string): string;
begin
  if AFirst = '' then
    Result := ASecond
  else if ASecond = '' then
    Result := AFirst
  else
    Result := AFirst + '; ' + ASecond;
end;

function TGenEmitter.SyncDecl(AMethod: TGenMethodInfo; AWithOptions, AQualified: Boolean): string;
var
  LArgs, LName: string;
begin
  LArgs := MethodArgs(AMethod, AWithOptions);
  LName := IfThen(AQualified, 'TTgApi.', '') + AMethod.PasName;
  if LArgs <> '' then
    LName := LName + '(' + LArgs + ')';
  Result := 'function ' + LName + ': ' + ResultType(AMethod.Result) + ';';
  if not AQualified then
    Result := Result + ' overload;';
end;

function TGenEmitter.AsyncDecl(AMethod: TGenMethodInfo; AWithOptions, AQualified: Boolean): string;
var
  LArgs: string;
begin
  LArgs := JoinDecl(MethodArgs(AMethod, AWithOptions), 'const AOnSuccess: TProc<' +
    ResultType(AMethod.Result) + '>; const AOnError: TProc<Exception>' + IfThen(AQualified, '', ' = nil'));
  Result := 'function ' + IfThen(AQualified, 'TTgApi.', '') + AMethod.PasName + 'Async(' + LArgs + '): ITask;';
  if not AQualified then
    Result := Result + ' overload;';
end;

function TGenEmitter.TryDecl(AMethod: TGenMethodInfo; AWithOptions, AQualified: Boolean): string;
var
  LOut: string;
begin
  if AMethod.Result.Kind = TGenValueKind.TrueValue then
    LOut := 'out AError: TTgErrorInfo'
  else
    LOut := 'out AResult: ' + ResultType(AMethod.Result) + '; out AError: TTgErrorInfo';
  Result := 'function ' + IfThen(AQualified, 'TTgApi.', '') + 'Try' + AMethod.PasName + '(' +
    JoinDecl(MethodArgs(AMethod, AWithOptions), LOut) + '): Boolean;';
  if not AQualified then
    Result := Result + ' overload;';
end;

function TGenEmitter.BuildDecl(AMethod: TGenMethodInfo; AQualified: Boolean): string;
begin
  Result := 'function ' + IfThen(AQualified, 'TTgApi.', '') + CallText(AMethod.BuildName,
    MethodArgs(AMethod, AMethod.HasOptions)) + ': TTgParams;';
end;

function TGenEmitter.ExecDecl(AMethod: TGenMethodInfo; AQualified: Boolean): string;
begin
  Result := 'function ' + IfThen(AQualified, 'TTgApi.', '') + AMethod.ExecName +
    '(AParams: TTgParams): ' + ResultType(AMethod.Result) + ';';
end;

function TGenEmitter.OptionDoc(AParam: TGenMemberInfo): string;
var
  LElem: string;
  LInfo: TGenTypeInfo;
  LMixed: Boolean;
begin
  Result := AParam.Description;
  // Подсказки о построителе клавиатур (TTgKeyboard в TgBot.pas).
  if not AParam.Value.IsArray and (AParam.Value.Kind = TGenValueKind.Obj) and
    SameStr(AParam.Value.TypeName, CInlineKeyboardType) then
    Result := Sentence(Result) + ' Только инлайн-клавиатура (ITgInlineKeyboardMarkup): ' +
      'TTgKeyboard.Inline.Row.Button(…) или TTgInlineKeyboardMarkup.Create; обычная клавиатура, ' +
      'Remove и ForceReply здесь не принимаются.';
  if not AParam.Value.IsArray and (AParam.Value.Kind = TGenValueKind.UnionRec) and
    SameStr(AParam.Value.TypeName, CReplyMarkupUnion) then
    Result := Sentence(Result) + ' Построитель: TTgKeyboard.Inline…, TTgKeyboard.Reply…, ' +
      'TTgKeyboard.Remove, TTgKeyboard.ForceReply.';
  if not AParam.Value.IsArray then
    Exit;
  Result := Result + ' Не задано — параметр не передаётся; [] — передаётся пустой список.';
  // Литерал массива из элементов разных подтипов не приводится к TTgOptional<TArray<T>>.
  LMixed := AParam.Value.Kind = TGenValueKind.UnionRec;
  if AParam.Value.Kind = TGenValueKind.Obj then
  begin
    LInfo := FAnalysis.FindType(AParam.Value.TypeName);
    LMixed := Assigned(LInfo) and (LInfo.Category = TGenCategory.Polymorphic);
  end;
  if LMixed and (AParam.Value.Depth = 1) then
  begin
    LElem := ElemType(AParam.Value);
    Result := Result + ' Элементы приводите к ' + LElem + ': [' + LElem + '(A), ' + LElem +
      '(B)] или TArray<' + LElem + '>.Create(A, B).';
  end;
end;

{ Gen.Forward.inc }

procedure TGenEmitter.EmitForward;
var
  W: TGenCodeWriter;
  LInfo: TGenTypeInfo;
begin
  W := NewWriter('Gen.Forward.inc — forward-объявления интерфейсов (interface, type-блок).');
  W.Indent;
  for LInfo in IncludedTypes do
    W.Add(LInfo.IntfName + ' = interface;');
  Save(W, 'Gen.Forward.inc');
end;

{ Gen.Enums.inc }

procedure TGenEmitter.EmitEnums;
var
  W: TGenCodeWriter;
  LInfo, LSub: TGenTypeInfo;
  LConst: TGenConstInfo;
  I: Integer;
  LDoc: string;
begin
  W := NewWriter('Gen.Enums.inc — виды полиморфных типов и записи констант.');
  W.Indent;
  for LInfo in IncludedTypes do
  begin
    if LInfo.Category <> TGenCategory.Polymorphic then
      Continue;
    W.Doc('Вид объекта ' + LInfo.Name + ' (свойство Kind интерфейса ' + LInfo.IntfName + ').');
    W.Add(LInfo.KindEnumName + ' = (');
    W.Indent;
    W.Doc('Значение, неизвестное этой версии библиотеки.');
    W.Add('Unknown' + IfThen(LInfo.Variants.Count > 0, ',', ''));
    for I := 0 to LInfo.Variants.Count - 1 do
    begin
      LSub := LInfo.Variants[I];
      LDoc := LSub.Name;
      if LSub.DiscriminatorValue <> '' then
        LDoc := LDoc + ' (' + LInfo.DispatchField + ' = "' + LSub.DiscriminatorValue + '")';
      W.Doc(LDoc + '.');
      W.Add(GenIdent(LSub.KindName) + IfThen(I < LInfo.Variants.Count - 1, ',', ''));
    end;
    W.Outdent;
    W.Add(');');
    W.Add('');
  end;
  for LConst in FAnalysis.Constants do
  begin
    W.Doc(LConst.Description);
    W.Add(LConst.RecName + ' = record');
    W.Add('const');
    W.Indent;
    for I := 0 to LConst.Names.Count - 1 do
      W.Add(GenIdent(LConst.Names[I]) + ' = ' + Q(LConst.Values[I]) + ';');
    W.Outdent;
    W.Add('end;');
    W.Add('');
  end;
  Save(W, 'Gen.Enums.inc');
end;

{ Gen.Unions.inc }

procedure TGenEmitter.EmitUnions;
var
  W: TGenCodeWriter;
  LUnion: TGenUnionInfo;
  LVariant: TGenTypeInfo;
  LNames: string;
begin
  W := NewWriter('Gen.Unions.inc — записи-объединения исходящих типов.');
  W.Indent;
  for LUnion in FAnalysis.Unions do
  begin
    if not LUnion.Included then
      Continue;
    LNames := '';
    for LVariant in LUnion.Variants do
      LNames := LNames + IfThen(LNames <> '', ', ', '') + LVariant.IntfName;
    W.Doc(Trim(CleanDescription(FirstParagraph(LUnion.Description)) + ' Принимает (неявное приведение): ' +
      LNames + '.'));
    W.Add(LUnion.RecName + ' = record');
    W.Add('private');
    W.Indent;
    W.Add('FValue: IInterface;');
    W.Outdent;
    W.Add('public');
    W.Indent;
    for LVariant in LUnion.Variants do
      W.Add('class operator Implicit(const AValue: ' + LVariant.IntfName + '): ' + LUnion.RecName + ';');
    W.Doc('Значения элементов массива (для сериализации).');
    W.Add('class function Values(const AItems: array of ' + LUnion.RecName + '): TArray<IInterface>; static;');
    W.Doc('Значение не задано.');
    W.Add('function IsEmpty: Boolean;');
    W.Doc('Объект-вариант (ITgOutObject или ITgJsonObject).');
    W.Add('property Value: IInterface read FValue;');
    W.Outdent;
    W.Add('end;');
    W.Add('');
  end;
  Save(W, 'Gen.Unions.inc');
end;

{ Gen.Intf.inc }

procedure TGenEmitter.EmitIntf;
var
  W: TGenCodeWriter;
  LInfo, LSub: TGenTypeInfo;
  LMember: TGenMemberInfo;
  LGetters: TArray<TGenMemberInfo>;
  LDoc, LCopyNote: string;
begin
  W := NewWriter('Gen.Intf.inc — интерфейсы объектов Bot API (база раньше вариантов).');
  W.Indent;
  for LInfo in IncludedTypes do
  begin
    LDoc := Trim(CleanDescription(LInfo.Description));
    if LInfo.Category = TGenCategory.Polymorphic then
    begin
      LDoc := LDoc + #10'Виды (Kind, As*):';
      for LSub in LInfo.Variants do
        LDoc := LDoc + ' ' + LSub.IntfName + IfThen(LSub = LInfo.Variants.Last, '.', ',');
    end;
    W.Doc(LDoc);
    W.Add(LInfo.IntfName + ' = interface(' + ParentIntf(LInfo) + ')');
    W.Indent;
    W.Add('[''' + LInfo.Guid + ''']');
    LGetters := OwnGetters(LInfo);
    // Методы доступа.
    if LInfo.Category = TGenCategory.Polymorphic then
    begin
      W.Add('function GetKind: ' + LInfo.KindEnumName + ';');
      W.Add('function GetKindText: string;');
    end;
    for LMember in LGetters do
    begin
      W.Add('function Get' + LMember.PasName + ': ' + ValueType(LMember.Value) + ';');
      if LMember.HasName <> '' then
        W.Add('function Get' + LMember.HasName + ': Boolean;');
    end;
    case LInfo.Category of
      TGenCategory.PlainVariant:
        W.Add('function GetText: string;');
      TGenCategory.ListVariant:
        W.Add('function GetItems: TArray<' + LInfo.Base.IntfName + '>;');
    end;
    if LInfo.Category = TGenCategory.Polymorphic then
      for LSub in LInfo.Variants do
      begin
        W.Doc(LSub.IntfName + ' или nil, если объект другого вида.');
        W.Add('function As' + LSub.KindName + ': ' + LSub.IntfName + ';');
      end;
    // Двунаправленный тип хранит JSON: аргументы With* сериализуются сразу.
    LCopyNote := IfThen(LInfo.IsIn, ' Значение копируется в момент вызова: последующие изменения ' +
      'переданного объекта на этот не влияют.', '');
    for LMember in Writable(LInfo) do
    begin
      if LCopyNote <> '' then
        W.Doc('Задаёт ' + LMember.Name + ': ' + Sentence(FirstParagraph(LMember.Description)) + LCopyNote)
      else
        W.Doc('Задаёт ' + LMember.Name + ': ' + FirstParagraph(LMember.Description));
      W.AddWrapped('function With' + LMember.PasName + '(' + ParamDecl(LMember.Value, 'AValue') + '): ' +
        LInfo.IntfName + ';');
      if (LMember.Value.Kind = TGenValueKind.Obj) and (LMember.Value.Depth = 2) then
      begin
        W.Doc('Добавляет строку в ' + LMember.Name + '.' + LCopyNote);
        W.AddWrapped('function With' + LMember.PasName + 'Row(const ARow: array of ' +
          ElemType(LMember.Value) + '): ' + LInfo.IntfName + ';');
      end;
    end;
    // Свойства.
    if LInfo.Category = TGenCategory.Polymorphic then
    begin
      W.Doc('Вид объекта (Unknown — неизвестный этой версии библиотеки).');
      W.Add('property Kind: ' + LInfo.KindEnumName + ' read GetKind;');
      W.Doc('Значение поля ' + LInfo.DispatchField + ' в JSON как есть (в т.ч. при Kind = Unknown); ' +
        'для вариантов-строк и массивов — пустая строка.');
      W.Add('property KindText: string read GetKindText;');
    end;
    for LMember in LGetters do
    begin
      W.Doc(LMember.Description);
      W.Add('property ' + GenIdent(LMember.PasName) + ': ' + ValueType(LMember.Value) + ' read Get' +
        LMember.PasName + ';');
      if LMember.HasName <> '' then
      begin
        W.Doc('Поле ' + LMember.Name + ' присутствует.');
        W.Add('property ' + LMember.HasName + ': Boolean read Get' + LMember.HasName + ';');
      end;
    end;
    case LInfo.Category of
      TGenCategory.PlainVariant:
        begin
          W.Doc('Текст.');
          W.Add('property Text: string read GetText;');
        end;
      TGenCategory.ListVariant:
        begin
          W.Doc('Фрагменты.');
          W.Add('property Items: TArray<' + LInfo.Base.IntfName + '> read GetItems;');
        end;
    end;
    W.Outdent;
    W.Add('end;');
    W.Add('');
  end;
  Save(W, 'Gen.Intf.inc');
end;

{ Gen.Factories.inc }

procedure TGenEmitter.EmitFactories;
var
  W: TGenCodeWriter;
  LInfo: TGenTypeInfo;
  LMember: TGenMemberInfo;
  LDoc: string;
begin
  W := NewWriter('Gen.Factories.inc — record-фабрики TTg<Name>: Create (исходящие), FromJson (входящие).');
  W.Indent;
  for LInfo in IncludedTypes do
  begin
    if not HasCreate(LInfo) and not HasMake(LInfo) then
      Continue;
    W.Doc('Создание ' + LInfo.IntfName + '.');
    W.Add(LInfo.RecName + ' = record');
    W.Add('public');
    W.Indent;
    if HasCreate(LInfo) then
    begin
      LDoc := 'Новый объект ' + LInfo.Name;
      if Length(CreateArgs(LInfo)) > 0 then
      begin
        LDoc := LDoc + ' с обязательными полями:';
        for LMember in CreateArgs(LInfo) do
          LDoc := LDoc + ' ' + LMember.Name;
      end;
      LDoc := LDoc + '. Необязательные поля задаются методами With*.';
      if LInfo.IsIn then
        LDoc := LDoc + ' Аргументы копируются в момент вызова: последующие изменения переданных ' +
          'объектов на этот не влияют.';
      W.Doc(LDoc);
      W.AddWrapped(CreateSignature(LInfo, False));
    end;
    if HasMake(LInfo) then
    begin
      W.Doc('Разбор JSON-текста (например, тела webhook); ошибка — nil.');
      W.Add('class function FromJson(const AJsonText: string): ' + LInfo.IntfName + '; static;');
    end;
    W.Outdent;
    W.Add('end;');
    W.Add('');
  end;
  Save(W, 'Gen.Factories.inc');
end;

{ Gen.Options.inc }

procedure TGenEmitter.EmitOptions;
var
  W: TGenCodeWriter;
  LMethod: TGenMethodInfo;
  LParam: TGenMemberInfo;
begin
  W := NewWriter('Gen.Options.inc — необязательные параметры методов.');
  W.Indent;
  for LMethod in FAnalysis.Methods do
  begin
    if not LMethod.Included or not LMethod.HasOptions then
      Continue;
    W.Doc('Необязательные параметры ' + LMethod.Name + '. Неинициализированная запись пуста ' +
      '(Default(' + LMethod.OptionsName + ')).');
    W.Add(LMethod.OptionsName + ' = record');
    W.Indent;
    for LParam in LMethod.Optional do
    begin
      W.Doc(OptionDoc(LParam));
      W.Add(GenIdent(LParam.PasName) + ': ' + OptionType(LParam.Value) + ';');
    end;
    W.Doc('Добавляет заданные параметры в запрос.');
    W.Add('procedure ApplyTo(AParams: TTgParams);');
    W.Outdent;
    W.Add('end;');
    W.Add('');
  end;
  Save(W, 'Gen.Options.inc');
end;

{ Gen.Methods.inc }

procedure TGenEmitter.EmitMethods;
var
  W: TGenCodeWriter;
  LMethod, LVariant: TGenMethodInfo;
begin
  W := NewWriter('Gen.Methods.inc — методы Bot API (внутри класса TTgApi: private-хелперы, public-методы).');
  W.Indent;
  // Хелперы: Build*Params — параметры в вызывающем потоке, Exec* — вызов и разбор результата.
  W.Add('private');
  W.Indent;
  for LMethod in FAnalysis.Methods do
  begin
    if not LMethod.Included then
      Continue;
    if LMethod.Params.Count > 0 then
      W.AddWrapped(BuildDecl(LMethod, False));
    W.AddWrapped(ExecDecl(LMethod, False));
    // Варианты: свой Build (опции из позиционных) и, если результат другой, свой Exec.
    for LVariant in LMethod.Variants do
    begin
      W.AddWrapped(BuildDecl(LVariant, False));
      if LVariant.OwnExec then
        W.AddWrapped(ExecDecl(LVariant, False));
    end;
  end;
  W.Outdent;
  W.Add('public');
  W.Indent;
  for LMethod in FAnalysis.Methods do
  begin
    if not LMethod.Included then
      Continue;
    if (LMethod.Result.Kind = TGenValueKind.Obj) and LMethod.Result.IsArray then
      W.Doc(LMethod.Name + ': ' + FirstParagraph(LMethod.Spec.Description) + ' Элементы результата ' +
        'разделяют JSON всего ответа и удерживают его; для длительного хранения отдельных элементов ' +
        'используйте TTgDto.Detach.')
    else
      W.Doc(LMethod.Name + ': ' + FirstParagraph(LMethod.Spec.Description));
    EmitMethodDecls(W, LMethod);
    for LVariant in LMethod.Variants do
    begin
      W.Doc(VariantDoc(LVariant));
      EmitMethodDecls(W, LVariant);
    end;
  end;
  Save(W, 'Gen.Methods.inc');
end;

function TGenEmitter.VariantDoc(AVariant: TGenMethodInfo): string;
var
  LParam: TGenMemberInfo;
  LNames, LFields: string;
begin
  LNames := '';
  for LParam in AVariant.Positional do
    LNames := LNames + IfThen(LNames <> '', ', ', '') + LParam.Name;
  LFields := '';
  for LParam in AVariant.Promoted do
    LFields := LFields + IfThen(LFields <> '', ', ', '') + GenIdent(LParam.PasName);
  Result := AVariant.Name + ' (вариант: ' + LNames + ').';
  if AVariant.Description <> '' then
    Result := Result + ' ' + Sentence(AVariant.Description);
  if AVariant.OwnExec then
    Result := Result + ' Результат True — запрос выполнен (Bot API вернул true).';
  if AVariant.HasOptions then
    Result := Result + ' Поля AOptions (' + LFields + ') заменяются значениями параметров.';
end;

procedure TGenEmitter.EmitMethodDecls(W: TGenCodeWriter; AMethod: TGenMethodInfo);
var
  LTitle: string;
begin
  // Документацию синхронного вызова пишет вызывающий (метод или вариант).
  W.AddWrapped(SyncDecl(AMethod, False, False));
  if AMethod.HasOptions then
    W.AddWrapped(SyncDecl(AMethod, True, False));
  LTitle := AMethod.Name;
  if AMethod.IsVariant then
    LTitle := AMethod.PasName + ' (' + AMethod.Name + ', вариант)';
  W.Doc('Асинхронный ' + LTitle + ': параметры проверяются и строятся в вызывающем потоке ' +
    '(ошибки — исключением здесь же), колбэки вызываются в рабочем потоке.');
  W.AddWrapped(AsyncDecl(AMethod, False, False));
  if AMethod.HasOptions then
    W.AddWrapped(AsyncDecl(AMethod, True, False));
  W.Doc(LTitle + ' без исключений: False и сведения об ошибке в AError.');
  W.AddWrapped(TryDecl(AMethod, False, False));
  if AMethod.HasOptions then
    W.AddWrapped(TryDecl(AMethod, True, False));
  W.Add('');
end;

{ Gen.ImplClasses.inc }

procedure TGenEmitter.EmitImplClasses;
var
  W: TGenCodeWriter;
  LInfo, LSub: TGenTypeInfo;
  LMember: TGenMemberInfo;
begin
  W := NewWriter('Gen.ImplClasses.inc — скрытые классы реализации (implementation).');
  W.Add('type');
  W.Indent;
  for LInfo in IncludedTypes do
  begin
    W.Add(LInfo.ImplName + ' = class(' + ParentImpl(LInfo) + ', ' + ImplInterfaces(LInfo) + ')');
    W.Add('public');
    W.Indent;
    if LInfo.Category = TGenCategory.Polymorphic then
    begin
      W.Add('function GetKind: ' + LInfo.KindEnumName + '; virtual;');
      W.Add('function GetKindText: string;');
    end
    else if Assigned(LInfo.Base) then
      W.Add('function GetKind: ' + LInfo.Base.KindEnumName + '; override;');
    for LMember in OwnGetters(LInfo) do
    begin
      W.Add('function Get' + LMember.PasName + ': ' + ValueType(LMember.Value) + ';');
      if LMember.HasName <> '' then
        W.Add('function Get' + LMember.HasName + ': Boolean;');
    end;
    case LInfo.Category of
      TGenCategory.PlainVariant:
        W.Add('function GetText: string;');
      TGenCategory.ListVariant:
        W.Add('function GetItems: TArray<' + LInfo.Base.IntfName + '>;');
      TGenCategory.Polymorphic:
        for LSub in LInfo.Variants do
          W.Add('function As' + LSub.KindName + ': ' + LSub.IntfName + ';');
    end;
    for LMember in Writable(LInfo) do
    begin
      W.AddWrapped('function With' + LMember.PasName + '(' + ParamDecl(LMember.Value, 'AValue') + '): ' +
        LInfo.IntfName + ';');
      if (LMember.Value.Kind = TGenValueKind.Obj) and (LMember.Value.Depth = 2) then
        W.AddWrapped('function With' + LMember.PasName + 'Row(const ARow: array of ' +
          ElemType(LMember.Value) + '): ' + LInfo.IntfName + ';');
    end;
    W.Outdent;
    W.Add('end;');
    W.Add('');
  end;
  Save(W, 'Gen.ImplClasses.inc');
end;

{ Gen.ImplMake.inc }

procedure TGenEmitter.EmitImplMake;
var
  W: TGenCodeWriter;
  LInfo, LSub, LPlain, LList, LDefault: TGenTypeInfo;
  LValues: TArray<TGenTypeInfo>;
  LRule: TGenDispatchRule;
  I: Integer;
  LFirst: Boolean;
begin
  W := NewWriter('Gen.ImplMake.inc — фабрики DTO из JSON (implementation). nil — значение не подходит.');
  for LInfo in IncludedTypes do
  begin
    if not HasMake(LInfo) then
      Continue;
    W.Add('function ' + LInfo.MakeName + '(AJson: TJSONValue; const AOwner: IInterface): ' + LInfo.IntfName + ';');
    if LInfo.Category <> TGenCategory.Polymorphic then
    begin
      W.Add('begin');
      W.Indent;
      W.Add('if AJson is TJSONObject then');
      W.Add('  Result := ' + LInfo.ImplName + '.Create(AJson, AOwner)');
      W.Add('else');
      W.Add('  Result := nil;');
      W.Outdent;
      W.Add('end;');
      W.Add('');
      Continue;
    end;

    LPlain := nil;
    LList := nil;
    LValues := nil;
    for LSub in LInfo.Variants do
      case LSub.Category of
        TGenCategory.PlainVariant: LPlain := LSub;
        TGenCategory.ListVariant: LList := LSub;
      else
        LValues := LValues + [LSub];
      end;
    if LInfo.DispatchRules.Count > 0 then
    begin
      W.Add('var');
      W.Add('  LValue: string;');
    end;
    W.Add('begin');
    W.Indent;
    if Assigned(LList) then
    begin
      W.Add('if AJson is TJSONArray then');
      W.Add('  Exit(' + LList.ImplName + '.Create(AJson, AOwner));');
    end;
    if Assigned(LPlain) then
    begin
      W.Add('if (AJson is TJSONString) and not (AJson is TJSONNumber) then');
      W.Add('  Exit(' + LPlain.ImplName + '.Create(AJson, AOwner));');
    end;
    W.Add('if not (AJson is TJSONObject) then');
    W.Add('  Exit(nil);');
    if LInfo.DispatchRules.Count > 0 then
    begin
      // Правила из overrides: сравнение текстового значения поля.
      W.Add('LValue := TTgJson.GetStr(TJSONObject(AJson), ' + Q(LInfo.DispatchField) + ');');
      LFirst := True;
      for LRule in LInfo.DispatchRules do
      begin
        W.Add(IfThen(LFirst, 'if ', 'else if ') + 'LValue = ' + Q(LRule.Value) + ' then');
        W.Add('  Result := ' + LRule.Target.ImplName + '.Create(AJson, AOwner)');
        LFirst := False;
      end;
      LDefault := LInfo.DispatchDefault;
      W.Add('else');
      if Assigned(LDefault) then
        W.Add('  Result := ' + LDefault.ImplName + '.Create(AJson, AOwner);')
      else
        W.Add('  Result := ' + LInfo.ImplName + '.Create(AJson, AOwner);');
    end
    else
    begin
      W.Add('case TTgDto.IndexOfValue(TJSONObject(AJson), ' + Q(LInfo.DispatchField) + ', [');
      W.Indent;
      for I := 0 to High(LValues) do
        W.Add(Q(LValues[I].DiscriminatorValue) + IfThen(I < High(LValues), ',', ']) of'));
      W.Outdent;
      W.Indent;
      for I := 0 to High(LValues) do
        W.Add(IntToStr(I) + ': Result := ' + LValues[I].ImplName + '.Create(AJson, AOwner);');
      W.Outdent;
      W.Add('else');
      W.Add('  Result := ' + LInfo.ImplName + '.Create(AJson, AOwner);');
      W.Add('end;');
    end;
    W.Outdent;
    W.Add('end;');
    W.Add('');
  end;
  Save(W, 'Gen.ImplMake.inc');
end;

{ Gen.ImplTypes.inc }

procedure TGenEmitter.EmitClassBodies(W: TGenCodeWriter; AInfo: TGenTypeInfo);
var
  LMember: TGenMemberInfo;
  LSub: TGenTypeInfo;
  LCls: string;
begin
  LCls := AInfo.ImplName;
  if AInfo.Category = TGenCategory.Polymorphic then
  begin
    W.Add('function ' + LCls + '.GetKind: ' + AInfo.KindEnumName + ';');
    W.Add('begin');
    W.Add('  Result := ' + KindRef(AInfo, nil) + ';');
    W.Add('end;');
    W.Add('');
    W.Add('function ' + LCls + '.GetKindText: string;');
    W.Add('begin');
    W.Add('  Result := TTgJson.GetStr(FJson, ' + Q(AInfo.DispatchField) + ');');
    W.Add('end;');
    W.Add('');
  end
  else if Assigned(AInfo.Base) then
  begin
    W.Add('function ' + LCls + '.GetKind: ' + AInfo.Base.KindEnumName + ';');
    W.Add('begin');
    W.Add('  Result := ' + KindRef(AInfo.Base, AInfo) + ';');
    W.Add('end;');
    W.Add('');
  end;
  for LMember in OwnGetters(AInfo) do
  begin
    W.Add('function ' + LCls + '.Get' + LMember.PasName + ': ' + ValueType(LMember.Value) + ';');
    W.Add('begin');
    W.Add('  Result := ' + ReadExpr(LMember.Value, LMember.Name) + ';');
    W.Add('end;');
    W.Add('');
    if LMember.HasName <> '' then
    begin
      W.Add('function ' + LCls + '.Get' + LMember.HasName + ': Boolean;');
      W.Add('begin');
      W.Add('  Result := TTgJson.Has(FJson, ' + Q(LMember.Name) + ');');
      W.Add('end;');
      W.Add('');
    end;
  end;
  case AInfo.Category of
    TGenCategory.PlainVariant:
      begin
        W.Add('function ' + LCls + '.GetText: string;');
        W.Add('begin');
        W.Add('  Result := ValueText;');
        W.Add('end;');
        W.Add('');
      end;
    TGenCategory.ListVariant:
      begin
        W.Add('function ' + LCls + '.GetItems: TArray<' + AInfo.Base.IntfName + '>;');
        W.Add('begin');
        W.Add('  Result := TTgDto.Objects<' + AInfo.Base.IntfName + '>(ValueArray, JsonOwner, ' +
          AInfo.Base.MakeName + ');');
        W.Add('end;');
        W.Add('');
      end;
    TGenCategory.Polymorphic:
      for LSub in AInfo.Variants do
      begin
        W.Add('function ' + LCls + '.As' + LSub.KindName + ': ' + LSub.IntfName + ';');
        W.Add('begin');
        W.Add('  if not Supports(Self, ' + LSub.IntfName + ', Result) then');
        W.Add('    Result := nil;');
        W.Add('end;');
        W.Add('');
      end;
  end;
  for LMember in Writable(AInfo) do
  begin
    W.AddWrapped('function ' + LCls + '.With' + LMember.PasName + '(' + ParamDecl(LMember.Value, 'AValue') +
      '): ' + AInfo.IntfName + ';');
    W.Add('begin');
    W.Add('  ' + WriteStmt(LMember.Value, LMember.Name, 'AValue'));
    W.Add('  Result := Self;');
    W.Add('end;');
    W.Add('');
    if (LMember.Value.Kind = TGenValueKind.Obj) and (LMember.Value.Depth = 2) then
    begin
      W.AddWrapped('function ' + LCls + '.With' + LMember.PasName + 'Row(const ARow: array of ' +
        ElemType(LMember.Value) + '): ' + AInfo.IntfName + ';');
      W.Add('begin');
      W.Add('  AppendRow(' + Q(LMember.Name) + ', TTgDto.ToIntf<' + ElemType(LMember.Value) + '>(ARow));');
      W.Add('  Result := Self;');
      W.Add('end;');
      W.Add('');
    end;
  end;
end;

procedure TGenEmitter.EmitImplTypes;
var
  W: TGenCodeWriter;
  LUnion: TGenUnionInfo;
  LVariant, LInfo: TGenTypeInfo;
  LMember: TGenMemberInfo;
  LConsts, LArgs: TArray<TGenMemberInfo>;
begin
  W := NewWriter('Gen.ImplTypes.inc — реализация записей-объединений, классов и фабрик (implementation).');

  for LUnion in FAnalysis.Unions do
  begin
    if not LUnion.Included then
      Continue;
    W.Add('{ ' + LUnion.RecName + ' }');
    W.Add('');
    for LVariant in LUnion.Variants do
    begin
      W.Add('class operator ' + LUnion.RecName + '.Implicit(const AValue: ' + LVariant.IntfName + '): ' +
        LUnion.RecName + ';');
      W.Add('begin');
      W.Add('  Result.FValue := AValue;');
      W.Add('end;');
      W.Add('');
    end;
    W.Add('class function ' + LUnion.RecName + '.Values(const AItems: array of ' + LUnion.RecName +
      '): TArray<IInterface>;');
    W.Add('var');
    W.Add('  I: Integer;');
    W.Add('begin');
    W.Add('  SetLength(Result, Length(AItems));');
    W.Add('  for I := 0 to High(AItems) do');
    W.Add('    Result[I] := AItems[I].FValue;');
    W.Add('end;');
    W.Add('');
    W.Add('function ' + LUnion.RecName + '.IsEmpty: Boolean;');
    W.Add('begin');
    W.Add('  Result := not Assigned(FValue);');
    W.Add('end;');
    W.Add('');
  end;

  for LInfo in IncludedTypes do
  begin
    W.Add('{ ' + LInfo.ImplName + ' }');
    W.Add('');
    EmitClassBodies(W, LInfo);
  end;

  for LInfo in IncludedTypes do
  begin
    if not HasCreate(LInfo) and not HasMake(LInfo) then
      Continue;
    W.Add('{ ' + LInfo.RecName + ' }');
    W.Add('');
    if HasCreate(LInfo) then
    begin
      W.AddWrapped(CreateSignature(LInfo, True));
      case LInfo.Category of
        TGenCategory.PlainVariant:
          begin
            W.Add('begin');
            W.Add('  Result := ' + LInfo.ImplName + '.CreateValue(TJSONString.Create(AText));');
            W.Add('end;');
          end;
        TGenCategory.ListVariant:
          begin
            W.Add('begin');
            W.Add('  Result := ' + LInfo.ImplName + '.CreateValue(TTgDto.SerializeArray(TTgDto.ToIntf<' +
              LInfo.Base.IntfName + '>(AItems), nil));');
            W.Add('end;');
          end;
      else
        LConsts := nil;
        for LMember in LInfo.Members do
          if LMember.ConstValue <> '' then
            LConsts := LConsts + [LMember];
        LArgs := CreateArgs(LInfo);
        if Length(LConsts) + Length(LArgs) = 0 then
        begin
          W.Add('begin');
          W.Add('  Result := ' + LInfo.ImplName + '.CreateNew;');
          W.Add('end;');
        end
        else
        begin
          W.Add('var');
          W.Add('  LObj: ' + LInfo.ImplName + ';');
          W.Add('begin');
          W.Indent;
          W.Add('LObj := ' + LInfo.ImplName + '.CreateNew;');
          W.Add('Result := LObj;');
          for LMember in LConsts do
            W.Add('LObj.' + ConstStmt(LMember));
          for LMember in LArgs do
            W.Add('LObj.' + WriteStmt(LMember.Value, LMember.Name, LMember.ArgName));
          W.Outdent;
          W.Add('end;');
        end;
      end;
      W.Add('');
    end;
    if HasMake(LInfo) then
    begin
      W.Add('class function ' + LInfo.RecName + '.FromJson(const AJsonText: string): ' + LInfo.IntfName + ';');
      W.Add('begin');
      W.Add('  Result := TTgDto.Parse<' + LInfo.IntfName + '>(AJsonText, ' + LInfo.MakeName + ');');
      W.Add('end;');
      W.Add('');
    end;
  end;
  Save(W, 'Gen.ImplTypes.inc');
end;

{ Gen.ImplMethods.inc }

procedure TGenEmitter.EmitMethodBodies(W: TGenCodeWriter; AMethod: TGenMethodInfo);
var
  LParam: TGenMemberInfo;
  LRes, LDefault, LCall, LBuild, LExec: string;
  LIsTrue, LOpts, LHasParams: Boolean;
begin
  LRes := ResultType(AMethod.Result);
  LIsTrue := AMethod.Result.Kind = TGenValueKind.TrueValue;
  LOpts := AMethod.HasOptions;
  LHasParams := AMethod.Params.Count > 0;
  LExec := AMethod.ExecName;
  if LOpts then
    LDefault := 'Default(' + AMethod.OptionsName + ')'
  else
    LDefault := '';

  // Построение параметров: всегда в вызывающем потоке, ошибки проверки — в точке вызова.
  if AMethod.IsVariant then
  begin
    LBuild := CallText(AMethod.BuildName, MethodCallArgs(AMethod, 'A', LOpts));
    EmitVariantBuild(W, AMethod);
  end
  else if LHasParams then
  begin
    LBuild := CallText(AMethod.BuildName, MethodCallArgs(AMethod, 'A', LOpts));
    W.AddWrapped(BuildDecl(AMethod, True));
    W.Add('begin');
    W.Indent;
    W.Add('Result := TTgParams.Create;');
    W.Add('try');
    W.Indent;
    for LParam in AMethod.Positional do
      W.AddWrapped(ParamsAddStmt(LParam.Value, 'Result', LParam.Name, LParam.ArgName));
    if LOpts then
      W.Add('AOptions.ApplyTo(Result);');
    W.Outdent;
    W.Add('except');
    W.Add('  Result.Free;');
    W.Add('  raise;');
    W.Add('end;');
    W.Outdent;
    W.Add('end;');
    W.Add('');
  end
  else
    LBuild := 'nil';

  // Выполнение над готовыми параметрами и разбор результата (общее для Sync/Async/Try).
  // Вариант с тем же результатом использует Exec базового метода.
  if not AMethod.IsVariant or AMethod.OwnExec then
  begin
    W.AddWrapped(ExecDecl(AMethod, True));
    W.Add('var');
    W.Add('  LValue: TJSONValue;');
    W.Add('begin');
    W.Indent;
    W.Add('LValue := Call(' + Q(AMethod.Name) + ', AParams);');
    W.AddWrapped('Result := ' + ResultExpr(AMethod) + ';');
    W.Outdent;
    W.Add('end;');
    W.Add('');
  end;

  // Синхронный вызов (полная форма — с опциями, если они есть).
  W.AddWrapped(SyncDecl(AMethod, LOpts, True));
  if LHasParams then
  begin
    W.Add('var');
    W.Add('  LParams: TTgParams;');
    W.Add('begin');
    W.Indent;
    W.AddWrapped('LParams := ' + LBuild + ';');
    W.Add('try');
    W.Add('  Result := ' + LExec + '(LParams);');
    W.Add('finally');
    W.Add('  LParams.Free;');
    W.Add('end;');
    W.Outdent;
  end
  else
  begin
    W.Add('begin');
    W.Add('  Result := ' + LExec + '(nil);');
  end;
  W.Add('end;');
  W.Add('');
  if LOpts then
  begin
    W.AddWrapped(SyncDecl(AMethod, False, True));
    W.Add('begin');
    W.AddWrapped('  Result := ' + CallText(AMethod.PasName,
      JoinCall([MethodCallArgs(AMethod, 'A', False), LDefault])) + ';');
    W.Add('end;');
    W.Add('');
  end;

  // Асинхронный вызов: параметры строятся здесь, в рабочий поток уходят готовыми
  // (владение — у RunAsyncCall, в т.ч. если задача не запустится).
  W.AddWrapped(AsyncDecl(AMethod, LOpts, True));
  W.Add('var');
  W.Add('  LExec: TTgExecFunc<' + LRes + '>;');
  W.Add('begin');
  W.Indent;
  W.Add('LExec := ' + LExec + ';');
  W.AddWrapped('Result := RunAsyncCall<' + LRes + '>(' + LBuild + ', LExec, AOnSuccess, AOnError);');
  W.Outdent;
  W.Add('end;');
  W.Add('');
  if LOpts then
  begin
    W.AddWrapped(AsyncDecl(AMethod, False, True));
    W.Add('begin');
    W.AddWrapped('  Result := ' + AMethod.PasName + 'Async(' + JoinCall([MethodCallArgs(AMethod, 'A', False),
      LDefault, 'AOnSuccess', 'AOnError']) + ');');
    W.Add('end;');
    W.Add('');
  end;

  // Try-вариант.
  W.AddWrapped(TryDecl(AMethod, LOpts, True));
  W.Add('begin');
  W.Indent;
  if not LIsTrue then
    W.Add('AResult := Default(' + LRes + ');');
  W.Add('AError := TTgErrorInfo.Empty;');
  W.Add('try');
  W.Indent;
  LCall := CallText(AMethod.PasName, MethodCallArgs(AMethod, 'A', LOpts)) + ';';
  if LIsTrue then
    W.AddWrapped(LCall)
  else
    W.AddWrapped('AResult := ' + LCall);
  W.Add('Result := True;');
  W.Outdent;
  W.Add('except');
  W.Indent;
  W.Add('on E: Exception do');
  W.Add('begin');
  W.Add('  AError := TTgErrorInfo.FromException(E);');
  W.Add('  Result := False;');
  W.Add('end;');
  W.Outdent;
  W.Add('end;');
  W.Outdent;
  W.Add('end;');
  W.Add('');
  if LOpts then
  begin
    W.AddWrapped(TryDecl(AMethod, False, True));
    W.Add('begin');
    W.AddWrapped('  Result := Try' + AMethod.PasName + '(' + JoinCall([MethodCallArgs(AMethod, 'A', False),
      LDefault, IfThen(LIsTrue, '', 'AResult'), 'AError']) + ');');
    W.Add('end;');
    W.Add('');
  end;
end;

procedure TGenEmitter.EmitVariantBuild(W: TGenCodeWriter; AVariant: TGenMethodInfo);
var
  LBase: TGenMethodInfo;
  LParam: TGenMemberInfo;
begin
  // Опции базового метода: копия AOptions (или пустая запись), вынесенные поля —
  // из позиционных параметров; запрос строит Build базового метода.
  LBase := AVariant.Base;
  W.AddWrapped(BuildDecl(AVariant, True));
  W.Add('var');
  W.Add('  LOptions: ' + LBase.OptionsName + ';');
  W.Add('begin');
  W.Indent;
  if AVariant.HasOptions then
    W.Add('LOptions := AOptions;')
  else
    W.Add('LOptions := Default(' + LBase.OptionsName + ');');
  for LParam in AVariant.Promoted do
    W.Add('LOptions.' + GenIdent(LParam.PasName) + ' := ' + LParam.ArgName + ';');
  W.AddWrapped('Result := ' + CallText(LBase.BuildName, MethodCallArgs(LBase, 'L', True)) + ';');
  W.Outdent;
  W.Add('end;');
  W.Add('');
end;

procedure TGenEmitter.EmitImplMethods;
var
  W: TGenCodeWriter;
  LMethod, LVariant: TGenMethodInfo;
  LParam: TGenMemberInfo;
  LName: string;
begin
  W := NewWriter('Gen.ImplMethods.inc — записи опций и методы TTgApi (implementation).');
  for LMethod in FAnalysis.Methods do
  begin
    if not LMethod.Included or not LMethod.HasOptions then
      Continue;
    W.Add('{ ' + LMethod.OptionsName + ' }');
    W.Add('');
    W.Add('procedure ' + LMethod.OptionsName + '.ApplyTo(AParams: TTgParams);');
    W.Add('begin');
    W.Indent;
    for LParam in LMethod.Optional do
    begin
      LName := GenIdent(LParam.PasName);
      W.Add('if ' + OptionalCond(LParam.Value, LName) + ' then');
      W.Add('  ' + ParamsAddStmt(LParam.Value, 'AParams', LParam.Name, OptionalValue(LParam.Value, LName)));
    end;
    W.Outdent;
    W.Add('end;');
    W.Add('');
  end;
  W.Add('{ TTgApi }');
  W.Add('');
  for LMethod in FAnalysis.Methods do
    if LMethod.Included then
    begin
      EmitMethodBodies(W, LMethod);
      for LVariant in LMethod.Variants do
        EmitMethodBodies(W, LVariant);
    end;
  Save(W, 'Gen.ImplMethods.inc');
end;

procedure TGenEmitter.Generate;
var
  LTarget, LTemp, LFile: string;
  I: Integer;
begin
  if FAnalysis.Errors.Count > 0 then
    raise EGenAnalysisError.CreateFmt('Анализ завершился с ошибками (%d) — генерация невозможна; ' +
      'подробности: --analyze', [FAnalysis.Errors.Count]);
  FFiles.Clear;
  // Временная папка рядом с целевой (тот же том — замена файлов переименованием).
  LTarget := ExcludeTrailingPathDelimiter(FOutDir);
  LTemp := LTarget + '.~gen' + IntToHex(TThread.GetTickCount, 8);
  ForceDirectories(LTemp);
  try
    FWorkDir := LTemp;
    EmitForward;
    EmitEnums;
    EmitUnions;
    EmitIntf;
    EmitFactories;
    EmitOptions;
    EmitMethods;
    EmitImplClasses;
    EmitImplMake;
    EmitImplTypes;
    EmitImplMethods;
    // Все файлы созданы — заменяем прежние.
    ForceDirectories(LTarget);
    for I := 0 to FFiles.Count - 1 do
      MoveReplace(TPath.Combine(LTemp, FFiles.Names[I]), TPath.Combine(LTarget, FFiles.Names[I]));
  finally
    FWorkDir := '';
    // Остатки временной папки (только созданные здесь файлы) — при ошибке генерации.
    for LFile in TDirectory.GetFiles(LTemp) do
      TFile.Delete(LFile);
    RemoveDir(LTemp);
  end;
end;

end.
