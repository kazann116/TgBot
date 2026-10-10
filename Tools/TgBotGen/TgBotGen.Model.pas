unit TgBotGen.Model;

{
  TgBotGen — модель спецификации Telegram Bot API для кодогенератора.

  - TGenTypeRef — разобранная строка типа ('Integer', 'Array of X',
    'Integer or String', 'A, B and C' и т.п.);
  - TGenField / TGenParam — поле типа / параметр метода;
  - TGenType / TGenMethod — сущности спецификации;
  - TGenModel — корень модели: владеет всеми объектами (TObjectList),
    строит индексы, связывает подтипы, выгружает модель в JSON.

  Многострочные описания хранятся с разделителем строк #10.
  Модуль использует только RTL, совместим с Delphi 10.4.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.Classes,
  System.Generics.Collections;

type
  /// <summary>Вид ссылки на тип.</summary>
  TGenTypeKind = (
    /// <summary>Строка типа не распознана (исходный текст — в Source).</summary>
    Unknown,
    /// <summary>Integer (в спецификации также 'Int').</summary>
    Int,
    /// <summary>Float (в спецификации также 'Float number').</summary>
    Float,
    /// <summary>String.</summary>
    Str,
    /// <summary>Boolean.</summary>
    Bool,
    /// <summary>True — логическое значение, всегда равное true.</summary>
    TrueConst,
    /// <summary>Ссылка на тип спецификации по имени (Message, InputFile…).</summary>
    Named,
    /// <summary>Array of Element.</summary>
    ArrayOf,
    /// <summary>Один из вариантов: 'A or B', 'A, B and C'.</summary>
    Union
  );

  /// <summary>
  ///   Ссылка на тип. Владеет вложенными ссылками (Element, Variants).
  ///   Создаётся разбором строки (Parse) или фабриками.
  /// </summary>
  TGenTypeRef = class
  private
    FKind: TGenTypeKind;
    FName: string;
    FSource: string;
    FElement: TGenTypeRef;
    FVariants: TObjectList<TGenTypeRef>;
    function GetVariantCount: Integer;
    function GetVariant(AIndex: Integer): TGenTypeRef;
    class function ParseAtom(const AText: string): TGenTypeRef; static;
    class function ParseExpr(const AText: string): TGenTypeRef; static;
  public
    /// <summary>Создаёт ссылку вида AKind; AName — имя для Named/Unknown.</summary>
    constructor Create(AKind: TGenTypeKind; const AName: string = '');
    destructor Destroy; override;
    /// <summary>
    ///   Разбирает строку типа из спецификации. Никогда не возвращает nil:
    ///   нераспознанная строка даёт Kind = Unknown. Результат освобождает вызывающий.
    /// </summary>
    class function Parse(const AText: string): TGenTypeRef; static;
    /// <summary>Array of AElement; владение AElement переходит к результату.</summary>
    class function CreateArray(AElement: TGenTypeRef): TGenTypeRef; static;
    /// <summary>Добавляет вариант в Union; владение AVariant переходит к Self.</summary>
    procedure AddVariant(AVariant: TGenTypeRef);
    /// <summary>Глубокая копия.</summary>
    function Clone: TGenTypeRef;
    /// <summary>
    ///   Каноническая запись: 'Array of Message', 'Integer or String'.
    ///   Неоднозначные сочетания берутся в скобки: 'Array of (A or B)',
    ///   '(Array of A) or B'.
    /// </summary>
    function ToString: string; override;
    /// <summary>
    ///   Структурированное представление в однострочном JSON:
    ///   {"kind": "array", "element": {"kind": "named", "name": "Message"}}.
    /// </summary>
    function ToJson: string;
    /// <summary>Внутри нет нераспознанных частей.</summary>
    function IsKnown: Boolean;
    /// <summary>Примитив (Integer, Float, String, Boolean, True).</summary>
    function IsPrimitive: Boolean;
    /// <summary>'Integer or String' — соответствует TTgChatId.</summary>
    function IsChatId: Boolean;
    /// <summary>'InputFile or String' — соответствует TTgInputFile.</summary>
    function IsInputFileOrString: Boolean;
    /// <summary>Тип InputFile встречается где-либо внутри ссылки.</summary>
    function UsesInputFile: Boolean;
    /// <summary>Глубина вложенности массивов (0 — не массив).</summary>
    function ArrayDepth: Integer;
    /// <summary>Тип элемента самого внутреннего массива (для не массива — Self).</summary>
    function InnermostElement: TGenTypeRef;
    /// <summary>Добавляет в AList имена всех Named-ссылок (без повторов).</summary>
    procedure CollectNamed(AList: TStrings);
    /// <summary>Вид ссылки.</summary>
    property Kind: TGenTypeKind read FKind;
    /// <summary>Имя типа для Named; исходный текст для Unknown.</summary>
    property Name: string read FName;
    /// <summary>Исходная строка спецификации (для корня разбора).</summary>
    property Source: string read FSource write FSource;
    /// <summary>Элемент массива (Kind = ArrayOf), иначе nil.</summary>
    property Element: TGenTypeRef read FElement;
    /// <summary>Количество вариантов (Kind = Union).</summary>
    property VariantCount: Integer read GetVariantCount;
    /// <summary>Варианты Union.</summary>
    property Variants[AIndex: Integer]: TGenTypeRef read GetVariant;
  end;

  /// <summary>Общая часть поля типа и параметра метода.</summary>
  TGenMember = class
  private
    FName: string;
    FTypeRef: TGenTypeRef;
    FRequired: Boolean;
    FDescription: string;
    function GetMayExceed32Bits: Boolean;
  public
    /// <summary>Владение ATypeRef переходит к члену (nil — Unknown).</summary>
    constructor Create(const AName: string; ATypeRef: TGenTypeRef;
      ARequired: Boolean; const ADescription: string);
    destructor Destroy; override;
    /// <summary>Имя в спецификации (snake_case).</summary>
    property Name: string read FName;
    /// <summary>Тип. Владелец — член.</summary>
    property TypeRef: TGenTypeRef read FTypeRef;
    /// <summary>Обязательный.</summary>
    property Required: Boolean read FRequired;
    /// <summary>Описание (текст без разметки).</summary>
    property Description: string read FDescription;
    /// <summary>
    ///   Описание предупреждает, что число может не уместиться в 32 бита
    ///   (кандидат на Int64).
    /// </summary>
    property MayExceed32Bits: Boolean read GetMayExceed32Bits;
  end;

  /// <summary>Поле типа (колонки Field | Type | Description).</summary>
  TGenField = class(TGenMember)
  private
    FConstValue: string;
    function GetOptional: Boolean;
  public
    /// <summary>Описание начинается с «Optional.».</summary>
    property Optional: Boolean read GetOptional;
    /// <summary>
    ///   Постоянное значение поля («always “photo”», «must be article») —
    ///   кандидат в значения дискриминатора; пусто, если не задано.
    /// </summary>
    property ConstValue: string read FConstValue write FConstValue;
  end;

  /// <summary>Параметр метода (колонки Parameter | Type | Required | Description).</summary>
  TGenParam = class(TGenMember);

  /// <summary>Общая часть типа и метода.</summary>
  TGenEntity = class
  private
    FName: string;
    FAnchor: string;
    FSection: string;
    FDescription: string;
  public
    constructor Create(const AName, AAnchor, ASection: string);
    /// <summary>Имя в спецификации (Message, sendMessage).</summary>
    property Name: string read FName;
    /// <summary>Якорь на странице документации (без '#').</summary>
    property Anchor: string read FAnchor;
    /// <summary>Раздел страницы (заголовок h3).</summary>
    property Section: string read FSection;
    /// <summary>Описание (абзацы через #10).</summary>
    property Description: string read FDescription write FDescription;
  end;

  /// <summary>Тип Bot API (объект, полиморфный базовый тип или заглушка).</summary>
  TGenType = class(TGenEntity)
  private
    FFields: TObjectList<TGenField>;
    FSubtypes: TList<string>;
    FParents: TList<string>;
    FExtraVariants: TObjectList<TGenTypeRef>;
    FDiscriminator: string;
    FDiscriminatorUnique: Boolean;
  public
    constructor Create(const AName, AAnchor, ASection: string);
    destructor Destroy; override;
    /// <summary>Добавляет поле; владение переходит к типу.</summary>
    function AddField(AField: TGenField): TGenField;
    /// <summary>Поле по имени или nil.</summary>
    function FindField(const AName: string): TGenField;
    /// <summary>Тип перечисляет варианты («can be one of …»).</summary>
    function IsUnion: Boolean;
    /// <summary>Union без собственных полей: сам по себе не создаётся.</summary>
    function IsAbstract: Boolean;
    /// <summary>Нет ни полей, ни вариантов (InputFile, CallbackGame…).</summary>
    function IsPlaceholder: Boolean;
    /// <summary>Поля. Владелец — тип.</summary>
    property Fields: TObjectList<TGenField> read FFields;
    /// <summary>Имена вариантов (для union) в порядке спецификации.</summary>
    property Subtypes: TList<string> read FSubtypes;
    /// <summary>Union-типы, в которые входит этот тип (заполняет TGenModel.Link).</summary>
    property Parents: TList<string> read FParents;
    /// <summary>
    ///   Дополнительные варианты union, не являющиеся объектами из списка
    ///   Subtypes (RichText: «either a String…, an Array of RichText…»).
    ///   Владелец ссылок — тип.
    /// </summary>
    property ExtraVariants: TObjectList<TGenTypeRef> read FExtraVariants;
    /// <summary>
    ///   Поле-дискриминатор union: у всех вариантов есть это поле с ConstValue
    ///   (заполняет TGenModel.Link); пусто — варианты различаются иначе.
    /// </summary>
    property Discriminator: string read FDiscriminator write FDiscriminator;
    /// <summary>Значения дискриминатора у вариантов не повторяются.</summary>
    property DiscriminatorUnique: Boolean read FDiscriminatorUnique write FDiscriminatorUnique;
  end;

  /// <summary>Метод Bot API.</summary>
  TGenMethod = class(TGenEntity)
  private
    FParams: TObjectList<TGenParam>;
    FReturnType: TGenTypeRef;
    FReturnSentence: string;
    procedure SetReturnType(AValue: TGenTypeRef);
  public
    constructor Create(const AName, AAnchor, ASection: string);
    destructor Destroy; override;
    /// <summary>Добавляет параметр; владение переходит к методу.</summary>
    function AddParam(AParam: TGenParam): TGenParam;
    /// <summary>Параметр по имени или nil.</summary>
    function FindParam(const AName: string): TGenParam;
    /// <summary>Тип результата не удалось извлечь из описания.</summary>
    function ReturnUnknown: Boolean;
    /// <summary>Есть параметр, допускающий загрузку файла (InputFile).</summary>
    function UsesInputFile: Boolean;
    /// <summary>Параметры. Владелец — метод.</summary>
    property Params: TObjectList<TGenParam> read FParams;
    /// <summary>
    ///   Тип результата; никогда не nil (Kind = Unknown, если не определён).
    ///   Присваивание передаёт владение методу и освобождает прежнее значение.
    /// </summary>
    property ReturnType: TGenTypeRef read FReturnType write SetReturnType;
    /// <summary>Предложение описания, из которого извлечён тип результата.</summary>
    property ReturnSentence: string read FReturnSentence write FReturnSentence;
  end;

  /// <summary>Модель спецификации Bot API. Владеет всеми типами и методами.</summary>
  TGenModel = class
  private
    FVersion: string;
    FDate: string;
    FSourceFile: string;
    FTypes: TObjectList<TGenType>;
    FMethods: TObjectList<TGenMethod>;
    FTypeIndex: TDictionary<string, TGenType>;
    FMethodIndex: TDictionary<string, TGenMethod>;
    FWarnings: TStringList;
    FUnresolved: TStringList;
    FSkippedHeadings: TStringList;
    procedure CheckTypeRef(ARef: TGenTypeRef; const AOwner: string);
    procedure DetectDiscriminator(AType: TGenType);
  public
    constructor Create;
    destructor Destroy; override;
    /// <summary>Очищает модель.</summary>
    procedure Clear;
    /// <summary>
    ///   Добавляет тип. Владение AType всегда переходит к модели; при повторе
    ///   имени дубликат освобождается, пишется предупреждение и возвращается nil.
    /// </summary>
    function AddType(AType: TGenType): TGenType;
    /// <summary>Добавляет метод (правила владения — как у AddType).</summary>
    function AddMethod(AMethod: TGenMethod): TGenMethod;
    /// <summary>Тип по имени (с учётом регистра) или nil.</summary>
    function FindType(const AName: string): TGenType;
    /// <summary>Метод по имени (с учётом регистра) или nil.</summary>
    function FindMethod(const AName: string): TGenMethod;
    /// <summary>Добавляет предупреждение разбора.</summary>
    procedure AddWarning(const AText: string); overload;
    procedure AddWarning(const AFormat: string; const AArgs: array of const); overload;
    /// <summary>
    ///   Связывает модель после разбора: Parents у вариантов, дискриминаторы
    ///   union-типов, список нераспознанных ссылок на типы (Unresolved).
    /// </summary>
    procedure Link;
    /// <summary>Дата релиза в формате ГГГГ-ММ-ДД или '', если не распознана.</summary>
    function DateIso: string;
    /// <summary>Общее число полей всех типов.</summary>
    function FieldCount: Integer;
    /// <summary>Общее число параметров всех методов.</summary>
    function ParamCount: Integer;
    /// <summary>Union-типы (полиморфные) в порядке спецификации.</summary>
    function UnionTypes: TArray<TGenType>;
    /// <summary>Методы с нераспознанным типом результата.</summary>
    function UnknownReturnMethods: TArray<TGenMethod>;
    /// <summary>Модель в JSON-тексте (отступ 2, порядок как в спецификации).</summary>
    function ToJson: string;
    /// <summary>Сохраняет ToJson в файл (UTF-8 без BOM).</summary>
    procedure SaveToJson(const AFileName: string);
    /// <summary>
    ///   Сохраняет эталон типов результата методов (имя → строка типа)
    ///   в JSON (UTF-8 без BOM).
    /// </summary>
    procedure SaveReturnsEtalon(const AFileName: string);
    /// <summary>
    ///   Сверяет типы результата методов с эталоном (SaveReturnsEtalon).
    ///   Каждое расхождение добавляется в Warnings; результат — их число.
    /// </summary>
    function CheckReturnsEtalon(const AFileName: string): Integer;
    /// <summary>Версия Bot API ('10.3').</summary>
    property Version: string read FVersion write FVersion;
    /// <summary>Дата релиза, как на странице ('August 24, 2026').</summary>
    property Date: string read FDate write FDate;
    /// <summary>Имя исходного HTML-файла.</summary>
    property SourceFile: string read FSourceFile write FSourceFile;
    /// <summary>Типы в порядке спецификации. Владелец — модель.</summary>
    property Types: TObjectList<TGenType> read FTypes;
    /// <summary>Методы в порядке спецификации. Владелец — модель.</summary>
    property Methods: TObjectList<TGenMethod> read FMethods;
    /// <summary>Предупреждения разбора.</summary>
    property Warnings: TStringList read FWarnings;
    /// <summary>Нераспознанные ссылки на типы: 'Владелец.член: строка'.</summary>
    property Unresolved: TStringList read FUnresolved;
    /// <summary>Пропущенные заголовки h4 (не сущности): 'Раздел / Заголовок'.</summary>
    property SkippedHeadings: TStringList read FSkippedHeadings;
  end;

implementation

uses
  System.StrUtils,
  System.RegularExpressions,
  System.IOUtils,
  System.JSON;

const
  CNameInputFile = 'InputFile';

{ TGenJsonWriter }

type
  /// <summary>Простой писатель JSON с отступами и стабильным порядком ключей.</summary>
  TGenJsonWriter = class
  private
    FSb: TStringBuilder;
    FLevel: Integer;
    FEmpty: TStack<Boolean>;
    procedure BeginItem(const AKey: string);
    procedure WriteIndent;
  public
    constructor Create;
    destructor Destroy; override;
    class function Quote(const AValue: string): string; static;
    procedure BeginObject(const AKey: string = '');
    procedure EndObject;
    procedure BeginArray(const AKey: string = '');
    procedure EndArray;
    procedure Str(const AKey, AValue: string);
    procedure Int(const AKey: string; AValue: Integer);
    procedure Bool(const AKey: string; AValue: Boolean);
    procedure StrItem(const AValue: string);
    /// <summary>Готовое JSON-значение (однострочное) под ключом AKey.</summary>
    procedure Raw(const AKey, AJson: string);
    function Text: string;
  end;

constructor TGenJsonWriter.Create;
begin
  inherited Create;
  FSb := TStringBuilder.Create;
  FEmpty := TStack<Boolean>.Create;
end;

destructor TGenJsonWriter.Destroy;
begin
  FEmpty.Free;
  FSb.Free;
  inherited;
end;

class function TGenJsonWriter.Quote(const AValue: string): string;
var
  LSb: TStringBuilder;
  LCh: Char;
begin
  LSb := TStringBuilder.Create(Length(AValue) + 2);
  try
    LSb.Append('"');
    for LCh in AValue do
      case LCh of
        '"': LSb.Append('\"');
        '\': LSb.Append('\\');
        #8: LSb.Append('\b');
        #9: LSb.Append('\t');
        #10: LSb.Append('\n');
        #12: LSb.Append('\f');
        #13: LSb.Append('\r');
      else
        if Ord(LCh) < 32 then
          LSb.Append('\u').Append(IntToHex(Ord(LCh), 4))
        else
          LSb.Append(LCh);
      end;
    LSb.Append('"');
    Result := LSb.ToString;
  finally
    LSb.Free;
  end;
end;

procedure TGenJsonWriter.WriteIndent;
begin
  FSb.Append(StringOfChar(' ', FLevel * 2));
end;

procedure TGenJsonWriter.BeginItem(const AKey: string);
begin
  if FEmpty.Count > 0 then
  begin
    if not FEmpty.Pop then
      FSb.Append(',');
    FEmpty.Push(False);
    FSb.Append(sLineBreak);
    WriteIndent;
  end;
  if AKey <> '' then
    FSb.Append(Quote(AKey)).Append(': ');
end;

procedure TGenJsonWriter.BeginObject(const AKey: string);
begin
  BeginItem(AKey);
  FSb.Append('{');
  FEmpty.Push(True);
  Inc(FLevel);
end;

procedure TGenJsonWriter.EndObject;
begin
  Dec(FLevel);
  if not FEmpty.Pop then
  begin
    FSb.Append(sLineBreak);
    WriteIndent;
  end;
  FSb.Append('}');
end;

procedure TGenJsonWriter.BeginArray(const AKey: string);
begin
  BeginItem(AKey);
  FSb.Append('[');
  FEmpty.Push(True);
  Inc(FLevel);
end;

procedure TGenJsonWriter.EndArray;
begin
  Dec(FLevel);
  if not FEmpty.Pop then
  begin
    FSb.Append(sLineBreak);
    WriteIndent;
  end;
  FSb.Append(']');
end;

procedure TGenJsonWriter.Str(const AKey, AValue: string);
begin
  BeginItem(AKey);
  FSb.Append(Quote(AValue));
end;

procedure TGenJsonWriter.Int(const AKey: string; AValue: Integer);
begin
  BeginItem(AKey);
  FSb.Append(AValue);
end;

procedure TGenJsonWriter.Bool(const AKey: string; AValue: Boolean);
begin
  BeginItem(AKey);
  FSb.Append(IfThen(AValue, 'true', 'false'));
end;

procedure TGenJsonWriter.StrItem(const AValue: string);
begin
  BeginItem('');
  FSb.Append(Quote(AValue));
end;

procedure TGenJsonWriter.Raw(const AKey, AJson: string);
begin
  BeginItem(AKey);
  FSb.Append(AJson);
end;

function TGenJsonWriter.Text: string;
begin
  Result := FSb.ToString + sLineBreak;
end;

{ TGenTypeRef }

constructor TGenTypeRef.Create(AKind: TGenTypeKind; const AName: string);
begin
  inherited Create;
  FKind := AKind;
  FName := AName;
  if FKind = TGenTypeKind.Union then
    FVariants := TObjectList<TGenTypeRef>.Create(True);
end;

destructor TGenTypeRef.Destroy;
begin
  FVariants.Free;
  FElement.Free;
  inherited;
end;

class function TGenTypeRef.CreateArray(AElement: TGenTypeRef): TGenTypeRef;
begin
  Result := TGenTypeRef.Create(TGenTypeKind.ArrayOf);
  Result.FElement := AElement;
end;

procedure TGenTypeRef.AddVariant(AVariant: TGenTypeRef);
begin
  if FKind <> TGenTypeKind.Union then
  begin
    AVariant.Free;
    raise EInvalidOperation.Create('TGenTypeRef.AddVariant: ссылка не является Union');
  end;
  FVariants.Add(AVariant);
end;

function TGenTypeRef.GetVariantCount: Integer;
begin
  if FVariants = nil then
    Result := 0
  else
    Result := FVariants.Count;
end;

function TGenTypeRef.GetVariant(AIndex: Integer): TGenTypeRef;
begin
  Result := FVariants[AIndex];
end;

class function TGenTypeRef.ParseAtom(const AText: string): TGenTypeRef;
begin
  if SameStr(AText, 'Integer') or SameStr(AText, 'Int') then
    Result := TGenTypeRef.Create(TGenTypeKind.Int)
  else if SameStr(AText, 'Float') or SameStr(AText, 'Float number') then
    Result := TGenTypeRef.Create(TGenTypeKind.Float)
  else if SameStr(AText, 'String') then
    Result := TGenTypeRef.Create(TGenTypeKind.Str)
  else if SameStr(AText, 'Boolean') then
    Result := TGenTypeRef.Create(TGenTypeKind.Bool)
  else if SameStr(AText, 'True') then
    Result := TGenTypeRef.Create(TGenTypeKind.TrueConst)
  else if TRegEx.IsMatch(AText, '^[A-Z][A-Za-z0-9]*$') then
    Result := TGenTypeRef.Create(TGenTypeKind.Named, AText)
  else
    Result := TGenTypeRef.Create(TGenTypeKind.Unknown, AText);
end;

class function TGenTypeRef.ParseExpr(const AText: string): TGenTypeRef;
const
  CArrayPrefix = 'Array of ';
var
  LParts: TArray<string>;
  LPart: string;
begin
  // 'Array of' связывает всё, что справа: 'Array of A, B and C' = Array of (A|B|C).
  if StartsText(CArrayPrefix, AText) then
    Exit(CreateArray(ParseExpr(Trim(Copy(AText, Length(CArrayPrefix) + 1, MaxInt)))));

  LParts := TRegEx.Split(AText, '\s*,\s*|\s+or\s+|\s+and\s+');
  if Length(LParts) <= 1 then
    Exit(ParseAtom(AText));

  Result := TGenTypeRef.Create(TGenTypeKind.Union);
  try
    for LPart in LParts do
      if Trim(LPart) <> '' then
        Result.AddVariant(ParseExpr(Trim(LPart)));
  except
    Result.Free;
    raise;
  end;
end;

class function TGenTypeRef.Parse(const AText: string): TGenTypeRef;
var
  LText: string;
begin
  LText := Trim(TRegEx.Replace(AText, '\s+', ' '));
  if LText = '' then
    Result := TGenTypeRef.Create(TGenTypeKind.Unknown, '')
  else
    Result := ParseExpr(LText);
  Result.FSource := LText;
end;

function TGenTypeRef.Clone: TGenTypeRef;
var
  I: Integer;
begin
  Result := TGenTypeRef.Create(FKind, FName);
  try
    Result.FSource := FSource;
    if FElement <> nil then
      Result.FElement := FElement.Clone;
    for I := 0 to VariantCount - 1 do
      Result.AddVariant(FVariants[I].Clone);
  except
    Result.Free;
    raise;
  end;
end;

function TGenTypeRef.ToString: string;
var
  I: Integer;
begin
  case FKind of
    TGenTypeKind.Int: Result := 'Integer';
    TGenTypeKind.Float: Result := 'Float';
    TGenTypeKind.Str: Result := 'String';
    TGenTypeKind.Bool: Result := 'Boolean';
    TGenTypeKind.TrueConst: Result := 'True';
    TGenTypeKind.Named: Result := FName;
    TGenTypeKind.ArrayOf:
      if FElement = nil then
        Result := 'Array of ?'
      else if FElement.Kind = TGenTypeKind.Union then
        // 'Array of A or B' читается двояко — элемент-union берём в скобки.
        Result := 'Array of (' + FElement.ToString + ')'
      else
        Result := 'Array of ' + FElement.ToString;
    TGenTypeKind.Union:
      begin
        Result := '';
        for I := 0 to VariantCount - 1 do
        begin
          if I > 0 then
            Result := Result + ' or ';
          // Массив не последним вариантом ('Array of A or B') и вложенный
          // union — в скобках.
          if ((FVariants[I].Kind = TGenTypeKind.ArrayOf) and (I < VariantCount - 1)) or
            (FVariants[I].Kind = TGenTypeKind.Union) then
            Result := Result + '(' + FVariants[I].ToString + ')'
          else
            Result := Result + FVariants[I].ToString;
        end;
      end;
  else
    Result := '?' + FName;
  end;
end;

function TGenTypeRef.ToJson: string;
var
  I: Integer;
begin
  case FKind of
    TGenTypeKind.Int: Result := '{"kind": "integer"}';
    TGenTypeKind.Float: Result := '{"kind": "float"}';
    TGenTypeKind.Str: Result := '{"kind": "string"}';
    TGenTypeKind.Bool: Result := '{"kind": "boolean"}';
    TGenTypeKind.TrueConst: Result := '{"kind": "true"}';
    TGenTypeKind.Named:
      Result := '{"kind": "named", "name": ' + TGenJsonWriter.Quote(FName) + '}';
    TGenTypeKind.ArrayOf:
      if FElement = nil then
        Result := '{"kind": "array", "element": null}'
      else
        Result := '{"kind": "array", "element": ' + FElement.ToJson + '}';
    TGenTypeKind.Union:
      begin
        Result := '{"kind": "union", "variants": [';
        for I := 0 to VariantCount - 1 do
        begin
          if I > 0 then
            Result := Result + ', ';
          Result := Result + FVariants[I].ToJson;
        end;
        Result := Result + ']}';
      end;
  else
    Result := '{"kind": "unknown", "source": ' + TGenJsonWriter.Quote(FName) + '}';
  end;
end;

function TGenTypeRef.IsKnown: Boolean;
var
  I: Integer;
begin
  case FKind of
    TGenTypeKind.Unknown:
      Result := False;
    TGenTypeKind.ArrayOf:
      Result := (FElement <> nil) and FElement.IsKnown;
    TGenTypeKind.Union:
      begin
        Result := VariantCount > 0;
        for I := 0 to VariantCount - 1 do
          if not FVariants[I].IsKnown then
            Exit(False);
      end;
  else
    Result := True;
  end;
end;

function TGenTypeRef.IsPrimitive: Boolean;
begin
  Result := FKind in [TGenTypeKind.Int, TGenTypeKind.Float, TGenTypeKind.Str,
    TGenTypeKind.Bool, TGenTypeKind.TrueConst];
end;

function TGenTypeRef.IsChatId: Boolean;
begin
  Result := (FKind = TGenTypeKind.Union) and (VariantCount = 2) and
    (FVariants[0].Kind = TGenTypeKind.Int) and (FVariants[1].Kind = TGenTypeKind.Str);
end;

function TGenTypeRef.IsInputFileOrString: Boolean;
begin
  Result := (FKind = TGenTypeKind.Union) and (VariantCount = 2) and
    (FVariants[0].Kind = TGenTypeKind.Named) and SameStr(FVariants[0].Name, CNameInputFile) and
    (FVariants[1].Kind = TGenTypeKind.Str);
end;

function TGenTypeRef.UsesInputFile: Boolean;
var
  I: Integer;
begin
  case FKind of
    TGenTypeKind.Named:
      Result := SameStr(FName, CNameInputFile);
    TGenTypeKind.ArrayOf:
      Result := (FElement <> nil) and FElement.UsesInputFile;
    TGenTypeKind.Union:
      begin
        Result := False;
        for I := 0 to VariantCount - 1 do
          if FVariants[I].UsesInputFile then
            Exit(True);
      end;
  else
    Result := False;
  end;
end;

function TGenTypeRef.ArrayDepth: Integer;
var
  LRef: TGenTypeRef;
begin
  Result := 0;
  LRef := Self;
  while (LRef.Kind = TGenTypeKind.ArrayOf) and (LRef.Element <> nil) do
  begin
    Inc(Result);
    LRef := LRef.Element;
  end;
end;

function TGenTypeRef.InnermostElement: TGenTypeRef;
begin
  Result := Self;
  while (Result.Kind = TGenTypeKind.ArrayOf) and (Result.Element <> nil) do
    Result := Result.Element;
end;

procedure TGenTypeRef.CollectNamed(AList: TStrings);
var
  I: Integer;
begin
  case FKind of
    TGenTypeKind.Named:
      if AList.IndexOf(FName) < 0 then
        AList.Add(FName);
    TGenTypeKind.ArrayOf:
      if FElement <> nil then
        FElement.CollectNamed(AList);
    TGenTypeKind.Union:
      for I := 0 to VariantCount - 1 do
        FVariants[I].CollectNamed(AList);
  end;
end;

{ TGenMember }

constructor TGenMember.Create(const AName: string; ATypeRef: TGenTypeRef;
  ARequired: Boolean; const ADescription: string);
begin
  inherited Create;
  FName := AName;
  if ATypeRef = nil then
    FTypeRef := TGenTypeRef.Create(TGenTypeKind.Unknown)
  else
    FTypeRef := ATypeRef;
  FRequired := ARequired;
  FDescription := ADescription;
end;

destructor TGenMember.Destroy;
begin
  FTypeRef.Free;
  inherited;
end;

function TGenMember.GetMayExceed32Bits: Boolean;
begin
  Result := ContainsText(FDescription, 'more than 32 significant bits') or
    ContainsText(FDescription, '64-bit integer') or
    ContainsText(FDescription, '64 bit integer');
end;

{ TGenField }

function TGenField.GetOptional: Boolean;
begin
  Result := not Required;
end;

{ TGenEntity }

constructor TGenEntity.Create(const AName, AAnchor, ASection: string);
begin
  inherited Create;
  FName := AName;
  FAnchor := AAnchor;
  FSection := ASection;
end;

{ TGenType }

constructor TGenType.Create(const AName, AAnchor, ASection: string);
begin
  inherited Create(AName, AAnchor, ASection);
  FFields := TObjectList<TGenField>.Create(True);
  FSubtypes := TList<string>.Create;
  FParents := TList<string>.Create;
  FExtraVariants := TObjectList<TGenTypeRef>.Create(True);
end;

destructor TGenType.Destroy;
begin
  FExtraVariants.Free;
  FParents.Free;
  FSubtypes.Free;
  FFields.Free;
  inherited;
end;

function TGenType.AddField(AField: TGenField): TGenField;
begin
  FFields.Add(AField);
  Result := AField;
end;

function TGenType.FindField(const AName: string): TGenField;
var
  LField: TGenField;
begin
  for LField in FFields do
    if SameStr(LField.Name, AName) then
      Exit(LField);
  Result := nil;
end;

function TGenType.IsUnion: Boolean;
begin
  Result := FSubtypes.Count > 0;
end;

function TGenType.IsAbstract: Boolean;
begin
  Result := IsUnion and (FFields.Count = 0);
end;

function TGenType.IsPlaceholder: Boolean;
begin
  Result := (FFields.Count = 0) and not IsUnion;
end;

{ TGenMethod }

constructor TGenMethod.Create(const AName, AAnchor, ASection: string);
begin
  inherited Create(AName, AAnchor, ASection);
  FParams := TObjectList<TGenParam>.Create(True);
  FReturnType := TGenTypeRef.Create(TGenTypeKind.Unknown);
end;

destructor TGenMethod.Destroy;
begin
  FReturnType.Free;
  FParams.Free;
  inherited;
end;

procedure TGenMethod.SetReturnType(AValue: TGenTypeRef);
begin
  if AValue = FReturnType then
    Exit;
  FReturnType.Free;
  if AValue = nil then
    FReturnType := TGenTypeRef.Create(TGenTypeKind.Unknown)
  else
    FReturnType := AValue;
end;

function TGenMethod.AddParam(AParam: TGenParam): TGenParam;
begin
  FParams.Add(AParam);
  Result := AParam;
end;

function TGenMethod.FindParam(const AName: string): TGenParam;
var
  LParam: TGenParam;
begin
  for LParam in FParams do
    if SameStr(LParam.Name, AName) then
      Exit(LParam);
  Result := nil;
end;

function TGenMethod.ReturnUnknown: Boolean;
begin
  Result := not FReturnType.IsKnown;
end;

function TGenMethod.UsesInputFile: Boolean;
var
  LParam: TGenParam;
begin
  for LParam in FParams do
    if LParam.TypeRef.UsesInputFile then
      Exit(True);
  Result := False;
end;

{ TGenModel }

constructor TGenModel.Create;
begin
  inherited Create;
  FTypes := TObjectList<TGenType>.Create(True);
  FMethods := TObjectList<TGenMethod>.Create(True);
  FTypeIndex := TDictionary<string, TGenType>.Create;
  FMethodIndex := TDictionary<string, TGenMethod>.Create;
  FWarnings := TStringList.Create;
  FUnresolved := TStringList.Create;
  FSkippedHeadings := TStringList.Create;
end;

destructor TGenModel.Destroy;
begin
  FSkippedHeadings.Free;
  FUnresolved.Free;
  FWarnings.Free;
  FMethodIndex.Free;
  FTypeIndex.Free;
  FMethods.Free;
  FTypes.Free;
  inherited;
end;

procedure TGenModel.Clear;
begin
  FVersion := '';
  FDate := '';
  FSourceFile := '';
  FTypeIndex.Clear;
  FMethodIndex.Clear;
  FTypes.Clear;
  FMethods.Clear;
  FWarnings.Clear;
  FUnresolved.Clear;
  FSkippedHeadings.Clear;
end;

function TGenModel.AddType(AType: TGenType): TGenType;
begin
  if FTypeIndex.ContainsKey(AType.Name) then
  begin
    AddWarning('Повтор типа %s (раздел «%s») — пропущен', [AType.Name, AType.Section]);
    AType.Free;
    Exit(nil);
  end;
  FTypes.Add(AType);
  FTypeIndex.Add(AType.Name, AType);
  Result := AType;
end;

function TGenModel.AddMethod(AMethod: TGenMethod): TGenMethod;
begin
  if FMethodIndex.ContainsKey(AMethod.Name) then
  begin
    AddWarning('Повтор метода %s (раздел «%s») — пропущен', [AMethod.Name, AMethod.Section]);
    AMethod.Free;
    Exit(nil);
  end;
  FMethods.Add(AMethod);
  FMethodIndex.Add(AMethod.Name, AMethod);
  Result := AMethod;
end;

function TGenModel.FindType(const AName: string): TGenType;
begin
  if not FTypeIndex.TryGetValue(AName, Result) then
    Result := nil;
end;

function TGenModel.FindMethod(const AName: string): TGenMethod;
begin
  if not FMethodIndex.TryGetValue(AName, Result) then
    Result := nil;
end;

procedure TGenModel.AddWarning(const AText: string);
begin
  FWarnings.Add(AText);
end;

procedure TGenModel.AddWarning(const AFormat: string; const AArgs: array of const);
begin
  FWarnings.Add(Format(AFormat, AArgs));
end;

procedure TGenModel.CheckTypeRef(ARef: TGenTypeRef; const AOwner: string);
var
  LNames: TStringList;
  LName: string;
begin
  if not ARef.IsKnown then
  begin
    FUnresolved.Add(Format('%s: «%s» — строка типа не распознана', [AOwner, ARef.Source]));
    Exit;
  end;
  LNames := TStringList.Create;
  try
    ARef.CollectNamed(LNames);
    for LName in LNames do
      if FindType(LName) = nil then
        FUnresolved.Add(Format('%s: «%s» — нет типа %s', [AOwner, ARef.Source, LName]));
  finally
    LNames.Free;
  end;
end;

procedure TGenModel.DetectDiscriminator(AType: TGenType);
var
  LFirst, LSub: TGenType;
  LCandidate, LOther: TGenField;
  LValues: TStringList;
  LName: string;
  LAll: Boolean;
begin
  AType.Discriminator := '';
  AType.DiscriminatorUnique := False;
  LFirst := FindType(AType.Subtypes[0]);
  if LFirst = nil then
    Exit;
  for LCandidate in LFirst.Fields do
  begin
    if LCandidate.ConstValue = '' then
      Continue;
    LAll := True;
    for LName in AType.Subtypes do
    begin
      LSub := FindType(LName);
      if LSub = nil then
      begin
        LAll := False;
        Break;
      end;
      LOther := LSub.FindField(LCandidate.Name);
      if (LOther = nil) or (LOther.ConstValue = '') then
      begin
        LAll := False;
        Break;
      end;
    end;
    if not LAll then
      Continue;

    AType.Discriminator := LCandidate.Name;
    LValues := TStringList.Create;
    try
      LValues.Sorted := True;
      LValues.Duplicates := dupIgnore;
      LValues.CaseSensitive := True;
      for LName in AType.Subtypes do
        LValues.Add(FindType(LName).FindField(LCandidate.Name).ConstValue);
      AType.DiscriminatorUnique := LValues.Count = AType.Subtypes.Count;
    finally
      LValues.Free;
    end;
    Exit;
  end;
end;

procedure TGenModel.Link;
var
  LType, LSub: TGenType;
  LMethod: TGenMethod;
  LField: TGenField;
  LParam: TGenParam;
  LExtra: TGenTypeRef;
  LName: string;
begin
  FUnresolved.Clear;
  for LType in FTypes do
    LType.Parents.Clear;

  for LType in FTypes do
  begin
    for LName in LType.Subtypes do
    begin
      LSub := FindType(LName);
      if LSub = nil then
        FUnresolved.Add(Format('%s: вариант %s — нет такого типа', [LType.Name, LName]))
      else if LSub.Parents.IndexOf(LType.Name) < 0 then
        LSub.Parents.Add(LType.Name);
    end;
    for LExtra in LType.ExtraVariants do
      CheckTypeRef(LExtra, LType.Name + ' → вариант');
    for LField in LType.Fields do
      CheckTypeRef(LField.TypeRef, LType.Name + '.' + LField.Name);
  end;

  for LType in FTypes do
    if LType.IsUnion then
      DetectDiscriminator(LType);

  for LMethod in FMethods do
  begin
    for LParam in LMethod.Params do
      CheckTypeRef(LParam.TypeRef, LMethod.Name + '.' + LParam.Name);
    if not LMethod.ReturnUnknown then
      CheckTypeRef(LMethod.ReturnType, LMethod.Name + ' → результат');
  end;
end;

function TGenModel.DateIso: string;
const
  CMonths: array[1..12] of string = ('January', 'February', 'March', 'April',
    'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December');
var
  LMatch: TMatch;
  LMonth: Integer;
  I: Integer;
begin
  Result := '';
  LMatch := TRegEx.Match(FDate, '^([A-Za-z]+)\s+(\d{1,2}),\s*(\d{4})$');
  if not LMatch.Success then
    Exit;
  LMonth := 0;
  for I := Low(CMonths) to High(CMonths) do
    if SameText(CMonths[I], LMatch.Groups[1].Value) then
      LMonth := I;
  if LMonth = 0 then
    Exit;
  Result := Format('%s-%.2d-%.2d', [LMatch.Groups[3].Value, LMonth,
    StrToInt(LMatch.Groups[2].Value)]);
end;

function TGenModel.FieldCount: Integer;
var
  LType: TGenType;
begin
  Result := 0;
  for LType in FTypes do
    Inc(Result, LType.Fields.Count);
end;

function TGenModel.ParamCount: Integer;
var
  LMethod: TGenMethod;
begin
  Result := 0;
  for LMethod in FMethods do
    Inc(Result, LMethod.Params.Count);
end;

function TGenModel.UnionTypes: TArray<TGenType>;
var
  LList: TList<TGenType>;
  LType: TGenType;
begin
  LList := TList<TGenType>.Create;
  try
    for LType in FTypes do
      if LType.IsUnion then
        LList.Add(LType);
    Result := LList.ToArray;
  finally
    LList.Free;
  end;
end;

function TGenModel.UnknownReturnMethods: TArray<TGenMethod>;
var
  LList: TList<TGenMethod>;
  LMethod: TGenMethod;
begin
  LList := TList<TGenMethod>.Create;
  try
    for LMethod in FMethods do
      if LMethod.ReturnUnknown then
        LList.Add(LMethod);
    Result := LList.ToArray;
  finally
    LList.Free;
  end;
end;

function TGenModel.ToJson: string;
var
  LWriter: TGenJsonWriter;
  LType: TGenType;
  LMethod: TGenMethod;
  LField: TGenField;
  LParam: TGenParam;
  LExtra: TGenTypeRef;
  LName, LKind: string;
begin
  LWriter := TGenJsonWriter.Create;
  try
    LWriter.BeginObject;
    LWriter.Str('version', FVersion);
    LWriter.Str('date', FDate);
    LWriter.Str('dateIso', DateIso);
    LWriter.Str('source', ExtractFileName(FSourceFile));

    LWriter.BeginObject('stats');
    LWriter.Int('types', FTypes.Count);
    LWriter.Int('methods', FMethods.Count);
    LWriter.Int('fields', FieldCount);
    LWriter.Int('params', ParamCount);
    LWriter.Int('unionTypes', Length(UnionTypes));
    LWriter.Int('unknownReturns', Length(UnknownReturnMethods));
    LWriter.Int('unresolved', FUnresolved.Count);
    LWriter.Int('warnings', FWarnings.Count);
    LWriter.EndObject;

    LWriter.BeginArray('types');
    for LType in FTypes do
    begin
      LWriter.BeginObject;
      LWriter.Str('name', LType.Name);
      if LType.IsUnion then
        LKind := 'union'
      else if LType.IsPlaceholder then
        LKind := 'placeholder'
      else
        LKind := 'object';
      LWriter.Str('kind', LKind);
      LWriter.Str('anchor', LType.Anchor);
      LWriter.Str('section', LType.Section);
      LWriter.Str('description', LType.Description);
      if LType.IsUnion then
      begin
        LWriter.Str('discriminator', LType.Discriminator);
        if LType.Discriminator <> '' then
          LWriter.Bool('discriminatorUnique', LType.DiscriminatorUnique);
        LWriter.BeginArray('subtypes');
        for LName in LType.Subtypes do
          LWriter.StrItem(LName);
        LWriter.EndArray;
        if LType.ExtraVariants.Count > 0 then
        begin
          LWriter.BeginArray('extraVariants');
          for LExtra in LType.ExtraVariants do
          begin
            LWriter.BeginObject;
            LWriter.Str('type', LExtra.ToString);
            LWriter.Raw('typeRef', LExtra.ToJson);
            LWriter.EndObject;
          end;
          LWriter.EndArray;
        end;
      end;
      if LType.Parents.Count > 0 then
      begin
        LWriter.BeginArray('parents');
        for LName in LType.Parents do
          LWriter.StrItem(LName);
        LWriter.EndArray;
      end;
      LWriter.BeginArray('fields');
      for LField in LType.Fields do
      begin
        LWriter.BeginObject;
        LWriter.Str('name', LField.Name);
        LWriter.Str('type', LField.TypeRef.ToString);
        LWriter.Raw('typeRef', LField.TypeRef.ToJson);
        LWriter.Bool('required', LField.Required);
        if LField.ConstValue <> '' then
          LWriter.Str('const', LField.ConstValue);
        if LField.MayExceed32Bits then
          LWriter.Bool('int64', True);
        LWriter.Str('description', LField.Description);
        LWriter.EndObject;
      end;
      LWriter.EndArray;
      LWriter.EndObject;
    end;
    LWriter.EndArray;

    LWriter.BeginArray('methods');
    for LMethod in FMethods do
    begin
      LWriter.BeginObject;
      LWriter.Str('name', LMethod.Name);
      LWriter.Str('anchor', LMethod.Anchor);
      LWriter.Str('section', LMethod.Section);
      LWriter.Str('returns', LMethod.ReturnType.ToString);
      LWriter.Raw('returnsRef', LMethod.ReturnType.ToJson);
      LWriter.Str('returnSentence', LMethod.ReturnSentence);
      LWriter.Bool('multipart', LMethod.UsesInputFile);
      LWriter.Str('description', LMethod.Description);
      LWriter.BeginArray('params');
      for LParam in LMethod.Params do
      begin
        LWriter.BeginObject;
        LWriter.Str('name', LParam.Name);
        LWriter.Str('type', LParam.TypeRef.ToString);
        LWriter.Raw('typeRef', LParam.TypeRef.ToJson);
        LWriter.Bool('required', LParam.Required);
        if LParam.MayExceed32Bits then
          LWriter.Bool('int64', True);
        LWriter.Str('description', LParam.Description);
        LWriter.EndObject;
      end;
      LWriter.EndArray;
      LWriter.EndObject;
    end;
    LWriter.EndArray;

    LWriter.BeginArray('unresolved');
    for LName in FUnresolved do
      LWriter.StrItem(LName);
    LWriter.EndArray;

    LWriter.BeginArray('warnings');
    for LName in FWarnings do
      LWriter.StrItem(LName);
    LWriter.EndArray;

    LWriter.EndObject;
    Result := LWriter.Text;
  finally
    LWriter.Free;
  end;
end;

procedure TGenModel.SaveToJson(const AFileName: string);
var
  LDir: string;
begin
  LDir := ExtractFileDir(AFileName);
  if LDir <> '' then
    ForceDirectories(LDir);
  TFile.WriteAllBytes(AFileName, TEncoding.UTF8.GetBytes(ToJson));
end;

procedure TGenModel.SaveReturnsEtalon(const AFileName: string);
var
  LWriter: TGenJsonWriter;
  LMethod: TGenMethod;
  LDir: string;
begin
  LWriter := TGenJsonWriter.Create;
  try
    LWriter.BeginObject;
    LWriter.Str('version', FVersion);
    LWriter.BeginObject('returns');
    for LMethod in FMethods do
      LWriter.Str(LMethod.Name, LMethod.ReturnType.ToString);
    LWriter.EndObject;
    LWriter.EndObject;
    LDir := ExtractFileDir(AFileName);
    if LDir <> '' then
      ForceDirectories(LDir);
    TFile.WriteAllBytes(AFileName, TEncoding.UTF8.GetBytes(LWriter.Text));
  finally
    LWriter.Free;
  end;
end;

function TGenModel.CheckReturnsEtalon(const AFileName: string): Integer;
var
  LRoot, LValue: TJSONValue;
  LReturns: TJSONObject;
  LPair: TJSONPair;
  LExpected: TDictionary<string, string>;
  LRest: TStringList;
  LMethod: TGenMethod;
  LFile, LName, LActual, LExpectedType: string;
  I: Integer;
begin
  Result := 0;
  LFile := ExtractFileName(AFileName);
  LRoot := TJSONObject.ParseJSONValue(TFile.ReadAllText(AFileName, TEncoding.UTF8));
  if LRoot = nil then
  begin
    AddWarning('Эталон %s: не удалось разобрать JSON', [LFile]);
    Exit(1);
  end;
  LExpected := TDictionary<string, string>.Create;
  LRest := TStringList.Create;
  try
    LValue := nil;
    if LRoot is TJSONObject then
      LValue := TJSONObject(LRoot).GetValue('returns');
    if not (LValue is TJSONObject) then
    begin
      AddWarning('Эталон %s: нет объекта "returns"', [LFile]);
      Exit(1);
    end;
    LReturns := TJSONObject(LValue);

    LValue := TJSONObject(LRoot).GetValue('version');
    if (LValue is TJSONString) and not SameStr(LValue.Value, FVersion) then
    begin
      AddWarning('Эталон %s: версия эталона %s не совпадает с версией модели %s',
        [LFile, LValue.Value, FVersion]);
      Inc(Result);
    end;

    for I := 0 to LReturns.Count - 1 do
    begin
      LPair := LReturns.Pairs[I];
      LExpected.AddOrSetValue(LPair.JsonString.Value, LPair.JsonValue.Value);
    end;

    for LMethod in FMethods do
    begin
      LActual := LMethod.ReturnType.ToString;
      if not LExpected.TryGetValue(LMethod.Name, LExpectedType) then
      begin
        AddWarning('Эталон %s: метода %s нет в эталоне (результат «%s»)',
          [LFile, LMethod.Name, LActual]);
        Inc(Result);
        Continue;
      end;
      if not SameStr(LExpectedType, LActual) then
      begin
        AddWarning('Эталон %s: %s — ожидалось «%s», получено «%s» (%s)',
          [LFile, LMethod.Name, LExpectedType, LActual, LMethod.ReturnSentence]);
        Inc(Result);
      end;
      LExpected.Remove(LMethod.Name);
    end;

    // Методы эталона, которых нет в модели (в алфавитном порядке).
    for LName in LExpected.Keys do
      LRest.Add(LName);
    LRest.Sort;
    for LName in LRest do
    begin
      AddWarning('Эталон %s: метод %s отсутствует в модели', [LFile, LName]);
      Inc(Result);
    end;
  finally
    LRest.Free;
    LExpected.Free;
    LRoot.Free;
  end;
end;

end.
