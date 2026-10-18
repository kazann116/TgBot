unit TgBotGen.Analysis;

{
  TgBotGen — анализ модели перед генерацией кода (фаза 3).

  По модели спецификации (TgBotGen.Model) и файлу переопределений
  (Spec\overrides.json) вычисляет:
  - направление каждого типа: входящий (результаты методов, Update),
    исходящий (параметры методов), оба — транзитивно по полям и вариантам;
  - категорию: обычный объект, полиморфный (union In/Both → базовый
    интерфейс с Kind), исходящее объединение (union Out → record);
  - разрешение безымянных объединений (наименьший покрывающий union
    или алиас из overrides), TTgChatId, TTgInputFile, «Message or True»;
  - файловые поля и типы с файлами (транзитивно), Int64-поля;
  - имена Delphi (PascalCase, ключевые слова, Has*/With*/As*), конфликты;
  - общие поля полиморфных типов, диспетчеризацию, детерминированные GUID;
  - варианты методов (methods.X.variants) и неоднозначность перегрузок;
  - топологический порядок интерфейсов и замыкание зависимостей (--only).
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.Classes,
  System.Generics.Collections,
  System.JSON,
  TgBotGen.Model;

type
  /// <summary>Ошибка анализа (неверные overrides, неизвестные имена).</summary>
  EGenAnalysisError = class(Exception);

  /// <summary>Направление типа.</summary>
  TGenDirection = (
    /// <summary>Не используется ни методами, ни Update (генерируется как входящий).</summary>
    Unused,
    /// <summary>Только входящий: только чтение.</summary>
    Incoming,
    /// <summary>Только исходящий: фабрика и With*.</summary>
    Outgoing,
    /// <summary>И входящий, и исходящий.</summary>
    Both
  );

  /// <summary>Категория типа для генерации.</summary>
  TGenCategory = (
    /// <summary>Обычный объект: интерфейс ITg&lt;Name&gt;.</summary>
    Regular,
    /// <summary>Union In/Both: базовый интерфейс с Kind и As*.</summary>
    Polymorphic,
    /// <summary>Union только Out: record TTg&lt;Name&gt; с Implicit из вариантов.</summary>
    OutUnion,
    /// <summary>InputFile: отображается на TTgInputFile.</summary>
    InputFile,
    /// <summary>Синтетический вариант-строка полиморфного типа (RichText Plain).</summary>
    PlainVariant,
    /// <summary>Синтетический вариант-массив полиморфного типа (RichText List).</summary>
    ListVariant
  );

  /// <summary>Вид значения поля, параметра или результата.</summary>
  TGenValueKind = (Str, Int, Int64, Float, Bool, TrueValue, ChatId, InputFile, Obj, UnionRec);

  /// <summary>Разрешённый тип значения.</summary>
  TGenValue = record
    /// <summary>Вид значения (для массивов — вид элемента).</summary>
    Kind: TGenValueKind;
    /// <summary>Имя типа спецификации (Obj) или объединения (UnionRec).</summary>
    TypeName: string;
    /// <summary>Глубина массива: 0 — скаляр, 1 — массив, 2 — массив массивов.</summary>
    Depth: Integer;
    /// <summary>Результат «Объект or True»: True означает nil.</summary>
    OrTrue: Boolean;
    class function Make(AKind: TGenValueKind; const ATypeName: string = ''): TGenValue; static;
    function IsArray: Boolean;
    function SameAs(const AOther: TGenValue): Boolean;
    function ToString: string;
  end;

  /// <summary>Поле типа или параметр метода после анализа.</summary>
  TGenMemberInfo = class
  private
    FName: string;
    FPasName: string;
    FArgName: string;
    FHasName: string;
    FValue: TGenValue;
    FRequired: Boolean;
    FConstValue: string;
    FDiscriminator: Boolean;
    FHidden: Boolean;
    FIsCommon: Boolean;
    FDescription: string;
  public
    /// <summary>Копия (для общих полей полиморфного базового типа).</summary>
    function Clone: TGenMemberInfo;
    /// <summary>Имя в JSON (snake_case).</summary>
    property Name: string read FName write FName;
    /// <summary>Имя свойства / поля записи опций (PascalCase).</summary>
    property PasName: string read FPasName write FPasName;
    /// <summary>Имя параметра (A&lt;PasName&gt;).</summary>
    property ArgName: string read FArgName write FArgName;
    /// <summary>Имя свойства Has* ('' — не нужно).</summary>
    property HasName: string read FHasName write FHasName;
    property Value: TGenValue read FValue write FValue;
    /// <summary>Обязательный (для параметров — передаётся позиционно).</summary>
    property Required: Boolean read FRequired write FRequired;
    /// <summary>
    ///   Постоянное значение, которое фабрика исходящего объекта задаёт сама
    ///   ('' — нет). Для обязательных полей типа True — 'true'.
    /// </summary>
    property ConstValue: string read FConstValue write FConstValue;
    /// <summary>Поле — дискриминатор полиморфного типа.</summary>
    property Discriminator: Boolean read FDiscriminator write FDiscriminator;
    /// <summary>Свойство не генерируется (дискриминатор-ключевое слово заменён Kind).</summary>
    property Hidden: Boolean read FHidden write FHidden;
    /// <summary>Поле объявлено в полиморфном базовом интерфейсе.</summary>
    property IsCommon: Boolean read FIsCommon write FIsCommon;
    property Description: string read FDescription write FDescription;
  end;

  TGenTypeInfo = class;

  /// <summary>Правило диспетчеризации полиморфного типа из overrides.</summary>
  TGenDispatchRule = record
    /// <summary>Строковое значение поля (числа сравниваются текстом).</summary>
    Value: string;
    Target: TGenTypeInfo;
  end;

  /// <summary>Тип после анализа.</summary>
  TGenTypeInfo = class
  private
    FName: string;
    FSpec: TGenType;
    FDirection: TGenDirection;
    FCategory: TGenCategory;
    FHasFiles: Boolean;
    FMembers: TObjectList<TGenMemberInfo>;
    FBase: TGenTypeInfo;
    FPolyParents: TList<TGenTypeInfo>;
    FVariants: TList<TGenTypeInfo>;
    FKindName: string;
    FDiscriminatorValue: string;
    FDispatchField: string;
    FDispatchRules: TList<TGenDispatchRule>;
    FDispatchDefault: TGenTypeInfo;
    FGuid: string;
    FIncluded: Boolean;
    FDescription: string;
  public
    constructor Create(const AName: string; ASpec: TGenType);
    destructor Destroy; override;
    /// <summary>ITg&lt;Name&gt;.</summary>
    function IntfName: string;
    /// <summary>TTg&lt;Name&gt;Impl (скрытый класс реализации).</summary>
    function ImplName: string;
    /// <summary>TTg&lt;Name&gt; (record-фабрика или запись-объединение).</summary>
    function RecName: string;
    /// <summary>TTg&lt;Name&gt;Kind (enum полиморфного типа).</summary>
    function KindEnumName: string;
    /// <summary>TgMake&lt;Name&gt; (фабрика DTO из JSON в implementation).</summary>
    function MakeName: string;
    /// <summary>Генерируется интерфейс (не OutUnion и не InputFile).</summary>
    function IsInterface: Boolean;
    /// <summary>Есть чтение (Incoming, Both, Unused).</summary>
    function IsIn: Boolean;
    /// <summary>Есть запись (Outgoing, Both).</summary>
    function IsOut: Boolean;
    /// <summary>Исходящий объект без чтения (база TTgOutObject).</summary>
    function IsOutOnly: Boolean;
    /// <summary>Синтетический вариант (Plain/List).</summary>
    function IsSynthetic: Boolean;
    /// <summary>Член по имени JSON или nil.</summary>
    function FindMember(const AName: string): TGenMemberInfo;
    property Name: string read FName;
    /// <summary>Тип спецификации; nil для синтетических вариантов.</summary>
    property Spec: TGenType read FSpec;
    property Direction: TGenDirection read FDirection write FDirection;
    property Category: TGenCategory read FCategory write FCategory;
    /// <summary>В поддереве есть загружаемые файлы.</summary>
    property HasFiles: Boolean read FHasFiles write FHasFiles;
    /// <summary>
    ///   Поля. У полиморфного базового типа — общие поля вариантов;
    ///   у варианта общие поля помечены IsCommon.
    /// </summary>
    property Members: TObjectList<TGenMemberInfo> read FMembers;
    /// <summary>Полиморфный базовый тип (основной родитель) или nil.</summary>
    property Base: TGenTypeInfo read FBase write FBase;
    /// <summary>Все полиморфные родители (обычно один).</summary>
    property PolyParents: TList<TGenTypeInfo> read FPolyParents;
    /// <summary>Варианты union (для Polymorphic/OutUnion), включая синтетические.</summary>
    property Variants: TList<TGenTypeInfo> read FVariants;
    /// <summary>Имя значения в enum Kind базового типа.</summary>
    property KindName: string read FKindName write FKindName;
    /// <summary>Значение дискриминатора в JSON.</summary>
    property DiscriminatorValue: string read FDiscriminatorValue write FDiscriminatorValue;
    /// <summary>Поле дискриминатора полиморфного типа ('' — правила из overrides).</summary>
    property DispatchField: string read FDispatchField write FDispatchField;
    /// <summary>Правила диспетчеризации из overrides (поле DispatchField).</summary>
    property DispatchRules: TList<TGenDispatchRule> read FDispatchRules;
    /// <summary>Вариант по умолчанию для правил из overrides.</summary>
    property DispatchDefault: TGenTypeInfo read FDispatchDefault write FDispatchDefault;
    /// <summary>GUID интерфейса '{…}'.</summary>
    property Guid: string read FGuid write FGuid;
    /// <summary>Входит в генерируемое подмножество.</summary>
    property Included: Boolean read FIncluded write FIncluded;
    property Description: string read FDescription write FDescription;
  end;

  /// <summary>Запись-объединение: исходящий union или алиас из overrides.</summary>
  TGenUnionInfo = class
  private
    FName: string;
    FDescription: string;
    FIsAlias: Boolean;
    FVariants: TList<TGenTypeInfo>;
    FIncluded: Boolean;
    FUsages: TStringList;
  public
    constructor Create(const AName: string; AIsAlias: Boolean);
    destructor Destroy; override;
    /// <summary>TTg&lt;Name&gt;.</summary>
    function RecName: string;
    function HasFiles: Boolean;
    property Name: string read FName;
    property Description: string read FDescription write FDescription;
    property IsAlias: Boolean read FIsAlias;
    property Variants: TList<TGenTypeInfo> read FVariants;
    property Included: Boolean read FIncluded write FIncluded;
    /// <summary>Где используется ('Тип.поле', 'метод.параметр').</summary>
    property Usages: TStringList read FUsages;
  end;

  /// <summary>
  ///   Метод после анализа. Вариант метода (overrides methods.X.variants) —
  ///   тоже TGenMethodInfo: дополнительная перегрузка с иным набором
  ///   позиционных параметров (часть полей опций вынесена в параметры),
  ///   при необходимости с другим именем и результатом True вместо
  ///   «Объект or True». Вариант разделяет параметры (TGenMemberInfo) и запись
  ///   опций с базовым методом и строит запрос через его Build*Params.
  /// </summary>
  TGenMethodInfo = class
  private
    FName: string;
    FPasName: string;
    FSpec: TGenMethod;
    FParams: TObjectList<TGenMemberInfo>;
    FResult: TGenValue;
    FHasFiles: Boolean;
    FIncluded: Boolean;
    FBase: TGenMethodInfo;
    FVariantIndex: Integer;
    FVariantParams: TArray<TGenMemberInfo>;
    FVariants: TObjectList<TGenMethodInfo>;
    FDescription: string;
  public
    constructor Create(ASpec: TGenMethod);
    /// <summary>
    ///   Вариант метода ABase (номер AIndex с 1) с позиционными параметрами
    ///   AParams (параметры ABase, в порядке объявления варианта).
    /// </summary>
    constructor CreateVariant(ABase: TGenMethodInfo; AIndex: Integer;
      const AParams: TArray<TGenMemberInfo>);
    destructor Destroy; override;
    /// <summary>
    ///   Позиционные параметры: у метода — обязательные в порядке спецификации,
    ///   у варианта — объявленные в overrides.
    /// </summary>
    function Positional: TArray<TGenMemberInfo>;
    /// <summary>Необязательные параметры (поля записи опций, кроме вынесенных в позиционные).</summary>
    function Optional: TArray<TGenMemberInfo>;
    function HasOptions: Boolean;
    /// <summary>TTg&lt;PasName&gt;Options (у варианта — запись базового метода).</summary>
    function OptionsName: string;
    /// <summary>Вариант: необязательные параметры базового метода, вынесенные в позиционные.</summary>
    function Promoted: TArray<TGenMemberInfo>;
    /// <summary>Это вариант (Base &lt;&gt; nil).</summary>
    function IsVariant: Boolean;
    /// <summary>Вариант со своим разбором результата (Exec*): результат отличается от базового.</summary>
    function OwnExec: Boolean;
    /// <summary>Имя private-хелпера построения параметров.</summary>
    function BuildName: string;
    /// <summary>Имя private-хелпера выполнения (у варианта без своего Exec — базовое).</summary>
    function ExecName: string;
    /// <summary>Имя метода Bot API (у варианта — как у базового).</summary>
    property Name: string read FName;
    property PasName: string read FPasName write FPasName;
    property Spec: TGenMethod read FSpec;
    /// <summary>Параметры (у варианта — ссылки на параметры базового метода).</summary>
    property Params: TObjectList<TGenMemberInfo> read FParams;
    property Result: TGenValue read FResult write FResult;
    /// <summary>Параметры могут содержать загружаемые файлы (multipart).</summary>
    property HasFiles: Boolean read FHasFiles write FHasFiles;
    property Included: Boolean read FIncluded write FIncluded;
    /// <summary>Базовый метод варианта или nil.</summary>
    property Base: TGenMethodInfo read FBase;
    /// <summary>Номер варианта (с 1); 0 — не вариант.</summary>
    property VariantIndex: Integer read FVariantIndex;
    /// <summary>Варианты метода (владеет).</summary>
    property Variants: TObjectList<TGenMethodInfo> read FVariants;
    /// <summary>Описание варианта из overrides ('' — нет).</summary>
    property Description: string read FDescription write FDescription;
  end;

  /// <summary>Запись строковых констант (TTgParseMode.Html и т.п.).</summary>
  TGenConstInfo = class
  private
    FName: string;
    FDescription: string;
    FNames: TStringList;
    FValues: TStringList;
  public
    constructor Create(const AName: string);
    destructor Destroy; override;
    /// <summary>TTg&lt;Name&gt;.</summary>
    function RecName: string;
    property Name: string read FName;
    property Description: string read FDescription write FDescription;
    property Names: TStringList read FNames;
    property Values: TStringList read FValues;
  end;

  /// <summary>Анализ модели. Не владеет моделью.</summary>
  TGenAnalysis = class
  private
    FModel: TGenModel;
    FOverrides: TJSONObject;
    FOverridesFile: string;
    FTypes: TObjectList<TGenTypeInfo>;
    FTypeIndex: TDictionary<string, TGenTypeInfo>;
    FOrdered: TList<TGenTypeInfo>;
    FUnions: TObjectList<TGenUnionInfo>;
    FUnionIndex: TDictionary<string, TGenUnionInfo>;
    FMethods: TObjectList<TGenMethodInfo>;
    FConstants: TObjectList<TGenConstInfo>;
    FErrors: TStringList;
    FWarnings: TStringList;
    FRenames: TStringList;
    FResolvedUnions: TStringList;
    FInt64Members: TStringList;
    FFileMembers: TStringList;
    FRestricted: Boolean;
    // overrides
    function OvSection(const AKey: string): TJSONObject;
    function OvType(const AName: string): TJSONObject;
    function OvMethod(const AName: string): TJSONObject;
    function OvList(AObj: TJSONObject; const AKey: string): TArray<string>;
    function OvStr(AObj: TJSONObject; const AKey: string): string;
    function OvMap(AObj: TJSONObject; const AKey, AName: string): string;
    procedure ValidateOverrides;
    // этапы
    procedure BuildTypes;
    procedure ComputeDirections;
    procedure AssignCategories;
    procedure LinkPolymorphic;
    procedure ResolveTypeMembers;
    procedure ComputeHasFiles;
    procedure ComputeCommonMembers;
    procedure BuildOutUnions;
    procedure ResolveMethods;
    procedure ResolveVariants;
    procedure BuildConstants;
    procedure ComputeGuids;
    procedure CheckSupport;
    procedure CheckNames;
    procedure CheckOverloads;
    procedure CheckUnusedAliases;
    procedure BuildOrder;
    // хелперы
    function ResolveRef(ARef: TGenTypeRef; const AWhere: string; AInt64, AFile,
      AAllowOrTrue: Boolean): TGenValue;
    function ResolveUnion(ARef: TGenTypeRef; const AWhere: string): TGenValue;
    function IsInt64Member(AMember: TGenMember; AOverride: TJSONObject): Boolean;
    function IsFileMember(AMember: TGenMember; AOverride: TJSONObject; AOutType: Boolean): Boolean;
    function MakeMember(AMember: TGenMember; const AOwnerName: string; AOverride: TJSONObject;
      const ARenameKey: string; AOutType: Boolean; const AKeywordPrefix: string): TGenMemberInfo;
    function NeedsHasName(AMember: TGenMemberInfo; ARequired: Boolean): Boolean;
    function CanRead(const AValue: TGenValue): Boolean;
    function CanWrite(const AValue: TGenValue): Boolean;
    function ValueHasFiles(const AValue: TGenValue): Boolean;
    procedure AddUnionUsage(const AValue: TGenValue; const AWhere: string);
    procedure IncludeType(AType: TGenTypeInfo);
    procedure IncludeValue(const AValue: TGenValue);
    procedure IncludeUnion(AUnion: TGenUnionInfo);
    procedure IncludeMethod(AMethod: TGenMethodInfo);
    procedure Error(const AFormat: string; const AArgs: array of const);
    procedure Warning(const AFormat: string; const AArgs: array of const);
  public
    constructor Create(AModel: TGenModel);
    destructor Destroy; override;
    /// <summary>Загружает overrides.json (UTF-8). Ошибка формата — EGenAnalysisError.</summary>
    procedure LoadOverrides(const AFileName: string);
    /// <summary>Выполняет анализ; проблемы — в Errors/Warnings.</summary>
    procedure Run;
    /// <summary>
    ///   Ограничивает генерацию списком типов/методов (через запятую)
    ///   с транзитивным замыканием зависимостей. Неизвестное имя — EGenAnalysisError.
    /// </summary>
    procedure Restrict(const AOnly: string);
    /// <summary>Тип по имени спецификации или nil.</summary>
    function FindType(const AName: string): TGenTypeInfo;
    /// <summary>Объединение-запись по имени или nil.</summary>
    function FindUnion(const AName: string): TGenUnionInfo;
    /// <summary>Текстовый отчёт анализа.</summary>
    procedure WriteReport(AOut: TStrings);
    /// <summary>PascalCase из snake_case ('is_bot' → 'IsBot').</summary>
    class function PascalCase(const AName: string): string; static;
    /// <summary>Зарезервированное слово Delphi (без учёта регистра).</summary>
    class function IsKeyword(const AName: string): Boolean; static;
    /// <summary>Идентификатор, при необходимости экранированный '&amp;'.</summary>
    class function SafeIdent(const AName: string): string; static;
    /// <summary>Детерминированный GUID (UUIDv5) для имени.</summary>
    class function NameGuid(const AName: string): string; static;
    property Model: TGenModel read FModel;
    /// <summary>Типы в порядке спецификации (синтетические — после базового).</summary>
    property Types: TObjectList<TGenTypeInfo> read FTypes;
    /// <summary>Интерфейсные типы в топологическом порядке (база раньше вариантов).</summary>
    property Ordered: TList<TGenTypeInfo> read FOrdered;
    property Unions: TObjectList<TGenUnionInfo> read FUnions;
    property Methods: TObjectList<TGenMethodInfo> read FMethods;
    property Constants: TObjectList<TGenConstInfo> read FConstants;
    property Errors: TStringList read FErrors;
    property Warnings: TStringList read FWarnings;
    /// <summary>Генерация ограничена (--only).</summary>
    property Restricted: Boolean read FRestricted;
    property OverridesFile: string read FOverridesFile;
  end;

implementation

uses
  System.Math,
  System.StrUtils,
  System.Hash,
  System.IOUtils;

const
  CNameInputFile = 'InputFile';
  CNameUpdate = 'Update';
  // Пространство имён UUIDv5 для GUID интерфейсов TgBot.
  CGuidNamespace: array[0..15] of Byte = ($6A, $1D, $3B, $7E, $54, $C2, $4F, $0A,
    $9E, $11, $8B, $2C, $D3, $47, $60, $F5);

  CKeywords: array[0..64] of string = ('and', 'array', 'as', 'asm', 'begin', 'case',
    'class', 'const', 'constructor', 'destructor', 'dispinterface', 'div', 'do',
    'downto', 'else', 'end', 'except', 'exports', 'file', 'finalization', 'finally',
    'for', 'function', 'goto', 'if', 'implementation', 'in', 'inherited',
    'initialization', 'inline', 'interface', 'is', 'label', 'library', 'mod', 'nil',
    'not', 'object', 'of', 'or', 'packed', 'procedure', 'program', 'property',
    'raise', 'record', 'repeat', 'resourcestring', 'set', 'shl', 'shr', 'string',
    'then', 'threadvar', 'to', 'try', 'type', 'unit', 'until', 'uses', 'var',
    'while', 'with', 'xor', 'operator');

  // Имена ядра и рантайма, с которыми не должны совпадать генерируемые.
  CRuntimeNames: array[0..30] of string = ('TTgLanguage', 'TTgText', 'TTgErrorKind',
    'TTgErrorInfo', 'TTgOptional', 'TTgChatId', 'TTgInputFileKind', 'TTgInputFile',
    'TTgParamFile', 'TTgParams', 'TTgJson', 'TTgProxySettings', 'TTgHttpSettings',
    'TTgHttpResponse', 'ITgTransport', 'TTgRateLimiter', 'TTgHttpTransport',
    'ITgJsonObject', 'ITgOutObject', 'TTgJsonHolder', 'TTgJsonDto', 'TTgOutObject',
    'TTgDtoFactory', 'TTgDto', 'TTgApiCore', 'TTgApi', 'ETgError', 'ITgTranslator',
    // Построители клавиатур (TgBot.pas).
    'TTgKeyboard', 'TTgInlineKeyboardBuilder', 'TTgReplyKeyboardBuilder');

  // Члены TObject/TInterfacedObject, которые нельзя скрывать или перекрывать
  // генерируемыми методами (Get*/With*/As*) и методами TTgApi.
  CObjectMemberNames: array[0..17] of string = ('QueryInterface', 'GetInterface',
    'GetInterfaceEntry', 'GetInterfaceTable', 'Dispatch', 'Equals', 'ToString',
    'GetHashCode', 'DisposeOf', 'FreeInstance', 'NewInstance', 'Free', 'ClassName',
    'ClassType', 'InheritsFrom', 'AfterConstruction', 'BeforeDestruction', 'DefaultHandler');

  // Члены базовых интерфейсов и классов DTO.
  CDtoMemberNames: array[0..7] of string = ('Raw', 'RawValue', 'AsJson', 'GetRaw',
    'GetRawValue', 'Serialize', 'Clone', 'JsonOwner');

  // Члены TTgApiCore, которые не могут совпасть с методами Bot API.
  CApiCoreNames: array[0..8] of string = ('Call', 'CallJson', 'DownloadFile',
    'RunAsync', 'RunAsyncCall', 'NewParamsBox', 'Transport', 'Create', 'Destroy');

  // Имена параметров и локальных переменных генерируемых методов.
  CMethodReservedArgs: array[0..8] of string = ('AOptions', 'AOnSuccess', 'AOnError',
    'AResult', 'AError', 'LParams', 'LValue', 'LOptions', 'LExec');

function DirectionText(ADirection: TGenDirection): string;
begin
  case ADirection of
    TGenDirection.Incoming: Result := 'In';
    TGenDirection.Outgoing: Result := 'Out';
    TGenDirection.Both: Result := 'Both';
  else
    Result := 'Unused';
  end;
end;

function SortedKey(const ANames: TArray<string>): string;
var
  LList: TStringList;
begin
  LList := TStringList.Create;
  try
    LList.CaseSensitive := True;
    LList.AddStrings(ANames);
    LList.Sort;
    LList.Delimiter := '|';
    LList.StrictDelimiter := True;
    Result := LList.DelimitedText;
  finally
    LList.Free;
  end;
end;

{ TGenValue }

class function TGenValue.Make(AKind: TGenValueKind; const ATypeName: string): TGenValue;
begin
  Result := Default(TGenValue);
  Result.Kind := AKind;
  Result.TypeName := ATypeName;
end;

function TGenValue.IsArray: Boolean;
begin
  Result := Depth > 0;
end;

function TGenValue.SameAs(const AOther: TGenValue): Boolean;
begin
  Result := (Kind = AOther.Kind) and SameStr(TypeName, AOther.TypeName) and
    (Depth = AOther.Depth) and (OrTrue = AOther.OrTrue);
end;

function TGenValue.ToString: string;
const
  CNames: array[TGenValueKind] of string = ('string', 'Integer', 'Int64', 'Double',
    'Boolean', 'True', 'TTgChatId', 'TTgInputFile', '', '');
var
  I: Integer;
begin
  case Kind of
    TGenValueKind.Obj: Result := 'ITg' + TypeName;
    TGenValueKind.UnionRec: Result := 'TTg' + TypeName;
  else
    Result := CNames[Kind];
  end;
  for I := 1 to Depth do
    Result := 'TArray<' + Result + '>';
  if OrTrue then
    Result := Result + ' | True';
end;

{ TGenMemberInfo }

function TGenMemberInfo.Clone: TGenMemberInfo;
begin
  Result := TGenMemberInfo.Create;
  Result.FName := FName;
  Result.FPasName := FPasName;
  Result.FArgName := FArgName;
  Result.FHasName := FHasName;
  Result.FValue := FValue;
  Result.FRequired := FRequired;
  Result.FConstValue := FConstValue;
  Result.FDiscriminator := FDiscriminator;
  Result.FHidden := FHidden;
  Result.FIsCommon := FIsCommon;
  Result.FDescription := FDescription;
end;

{ TGenTypeInfo }

constructor TGenTypeInfo.Create(const AName: string; ASpec: TGenType);
begin
  inherited Create;
  FName := AName;
  FSpec := ASpec;
  FMembers := TObjectList<TGenMemberInfo>.Create(True);
  FPolyParents := TList<TGenTypeInfo>.Create;
  FVariants := TList<TGenTypeInfo>.Create;
  FDispatchRules := TList<TGenDispatchRule>.Create;
  if Assigned(ASpec) then
    FDescription := ASpec.Description;
end;

destructor TGenTypeInfo.Destroy;
begin
  FDispatchRules.Free;
  FVariants.Free;
  FPolyParents.Free;
  FMembers.Free;
  inherited Destroy;
end;

function TGenTypeInfo.IntfName: string;
begin
  Result := 'ITg' + FName;
end;

function TGenTypeInfo.ImplName: string;
begin
  Result := 'TTg' + FName + 'Impl';
end;

function TGenTypeInfo.RecName: string;
begin
  Result := 'TTg' + FName;
end;

function TGenTypeInfo.KindEnumName: string;
begin
  Result := 'TTg' + FName + 'Kind';
end;

function TGenTypeInfo.MakeName: string;
begin
  Result := 'TgMake' + FName;
end;

function TGenTypeInfo.IsInterface: Boolean;
begin
  Result := not (FCategory in [TGenCategory.OutUnion, TGenCategory.InputFile]);
end;

function TGenTypeInfo.IsIn: Boolean;
begin
  Result := FDirection <> TGenDirection.Outgoing;
end;

function TGenTypeInfo.IsOut: Boolean;
begin
  Result := FDirection in [TGenDirection.Outgoing, TGenDirection.Both];
end;

function TGenTypeInfo.IsOutOnly: Boolean;
begin
  Result := FDirection = TGenDirection.Outgoing;
end;

function TGenTypeInfo.IsSynthetic: Boolean;
begin
  Result := FCategory in [TGenCategory.PlainVariant, TGenCategory.ListVariant];
end;

function TGenTypeInfo.FindMember(const AName: string): TGenMemberInfo;
var
  LMember: TGenMemberInfo;
begin
  for LMember in FMembers do
    if SameStr(LMember.Name, AName) then
      Exit(LMember);
  Result := nil;
end;

{ TGenUnionInfo }

constructor TGenUnionInfo.Create(const AName: string; AIsAlias: Boolean);
begin
  inherited Create;
  FName := AName;
  FIsAlias := AIsAlias;
  FVariants := TList<TGenTypeInfo>.Create;
  FUsages := TStringList.Create;
end;

destructor TGenUnionInfo.Destroy;
begin
  FUsages.Free;
  FVariants.Free;
  inherited Destroy;
end;

function TGenUnionInfo.RecName: string;
begin
  Result := 'TTg' + FName;
end;

function TGenUnionInfo.HasFiles: Boolean;
var
  LVariant: TGenTypeInfo;
begin
  for LVariant in FVariants do
    if LVariant.HasFiles then
      Exit(True);
  Result := False;
end;

{ TGenMethodInfo }

constructor TGenMethodInfo.Create(ASpec: TGenMethod);
begin
  inherited Create;
  FSpec := ASpec;
  FName := ASpec.Name;
  FParams := TObjectList<TGenMemberInfo>.Create(True);
  FVariants := TObjectList<TGenMethodInfo>.Create(True);
end;

constructor TGenMethodInfo.CreateVariant(ABase: TGenMethodInfo; AIndex: Integer;
  const AParams: TArray<TGenMemberInfo>);
begin
  inherited Create;
  FBase := ABase;
  FVariantIndex := AIndex;
  FSpec := ABase.Spec;
  FName := ABase.Name;
  FPasName := ABase.PasName;
  FResult := ABase.Result;
  FHasFiles := ABase.HasFiles;
  FVariantParams := AParams;
  // Параметры принадлежат базовому методу.
  FParams := TObjectList<TGenMemberInfo>.Create(False);
  FParams.AddRange(ABase.Params);
  FVariants := TObjectList<TGenMethodInfo>.Create(True);
end;

destructor TGenMethodInfo.Destroy;
begin
  FVariants.Free;
  FParams.Free;
  inherited Destroy;
end;

function TGenMethodInfo.Positional: TArray<TGenMemberInfo>;
var
  LParam: TGenMemberInfo;
begin
  if IsVariant then
    Exit(FVariantParams);
  Result := nil;
  for LParam in FParams do
    if LParam.Required then
      Result := Result + [LParam];
end;

function TGenMethodInfo.Optional: TArray<TGenMemberInfo>;
var
  LParam, LPositional: TGenMemberInfo;
  LFound: Boolean;
begin
  Result := nil;
  for LParam in FParams do
  begin
    if LParam.Required then
      Continue;
    LFound := False;
    if IsVariant then
      for LPositional in FVariantParams do
        if LPositional = LParam then
          LFound := True;
    if not LFound then
      Result := Result + [LParam];
  end;
end;

function TGenMethodInfo.HasOptions: Boolean;
begin
  Result := Length(Optional) > 0;
end;

function TGenMethodInfo.OptionsName: string;
begin
  if IsVariant then
    Result := FBase.OptionsName
  else
    Result := 'TTg' + FPasName + 'Options';
end;

function TGenMethodInfo.Promoted: TArray<TGenMemberInfo>;
var
  LParam: TGenMemberInfo;
begin
  Result := nil;
  if IsVariant then
    for LParam in FVariantParams do
      if not LParam.Required then
        Result := Result + [LParam];
end;

function TGenMethodInfo.IsVariant: Boolean;
begin
  Result := Assigned(FBase);
end;

function TGenMethodInfo.OwnExec: Boolean;
begin
  Result := IsVariant and not FResult.SameAs(FBase.Result);
end;

function TGenMethodInfo.BuildName: string;
begin
  if IsVariant then
    Result := 'Build' + FBase.PasName + 'Variant' + IntToStr(FVariantIndex) + 'Params'
  else
    Result := 'Build' + FPasName + 'Params';
end;

function TGenMethodInfo.ExecName: string;
begin
  if OwnExec then
    Result := 'Exec' + FBase.PasName + 'Variant' + IntToStr(FVariantIndex)
  else if IsVariant then
    Result := FBase.ExecName
  else
    Result := 'Exec' + FPasName;
end;

{ TGenConstInfo }

constructor TGenConstInfo.Create(const AName: string);
begin
  inherited Create;
  FName := AName;
  FNames := TStringList.Create;
  FValues := TStringList.Create;
end;

destructor TGenConstInfo.Destroy;
begin
  FValues.Free;
  FNames.Free;
  inherited Destroy;
end;

function TGenConstInfo.RecName: string;
begin
  Result := 'TTg' + FName;
end;

{ TGenAnalysis }

constructor TGenAnalysis.Create(AModel: TGenModel);
begin
  inherited Create;
  FModel := AModel;
  FTypes := TObjectList<TGenTypeInfo>.Create(True);
  FTypeIndex := TDictionary<string, TGenTypeInfo>.Create;
  FOrdered := TList<TGenTypeInfo>.Create;
  FUnions := TObjectList<TGenUnionInfo>.Create(True);
  FUnionIndex := TDictionary<string, TGenUnionInfo>.Create;
  FMethods := TObjectList<TGenMethodInfo>.Create(True);
  FConstants := TObjectList<TGenConstInfo>.Create(True);
  FErrors := TStringList.Create;
  FWarnings := TStringList.Create;
  FRenames := TStringList.Create;
  FResolvedUnions := TStringList.Create;
  FResolvedUnions.Sorted := True;
  FResolvedUnions.Duplicates := dupIgnore;
  FInt64Members := TStringList.Create;
  FFileMembers := TStringList.Create;
end;

destructor TGenAnalysis.Destroy;
begin
  FFileMembers.Free;
  FInt64Members.Free;
  FResolvedUnions.Free;
  FRenames.Free;
  FWarnings.Free;
  FErrors.Free;
  FConstants.Free;
  FMethods.Free;
  FUnionIndex.Free;
  FUnions.Free;
  FOrdered.Free;
  FTypeIndex.Free;
  FTypes.Free;
  FOverrides.Free;
  inherited Destroy;
end;

procedure TGenAnalysis.Error(const AFormat: string; const AArgs: array of const);
begin
  FErrors.Add(Format(AFormat, AArgs));
end;

procedure TGenAnalysis.Warning(const AFormat: string; const AArgs: array of const);
begin
  FWarnings.Add(Format(AFormat, AArgs));
end;

class function TGenAnalysis.PascalCase(const AName: string): string;
var
  LPart: string;
begin
  Result := '';
  for LPart in AName.Split(['_'], TStringSplitOptions.ExcludeEmpty) do
    Result := Result + UpperCase(LPart.Substring(0, 1)) + LPart.Substring(1);
end;

class function TGenAnalysis.IsKeyword(const AName: string): Boolean;
begin
  Result := MatchText(AName, CKeywords);
end;

class function TGenAnalysis.SafeIdent(const AName: string): string;
begin
  if IsKeyword(AName) then
    Result := '&' + AName
  else
    Result := AName;
end;

class function TGenAnalysis.NameGuid(const AName: string): string;
var
  LHash: THashSHA1;
  LNs, LBytes: TBytes;
  I: Integer;
  LHex: string;
begin
  SetLength(LNs, Length(CGuidNamespace));
  for I := 0 to High(CGuidNamespace) do
    LNs[I] := CGuidNamespace[I];
  LHash := THashSHA1.Create;
  LHash.Update(LNs);
  LHash.Update(TEncoding.UTF8.GetBytes(AName));
  LBytes := LHash.HashAsBytes;
  // UUIDv5: версия 5 и вариант RFC 4122.
  LBytes[6] := (LBytes[6] and $0F) or $50;
  LBytes[8] := (LBytes[8] and $3F) or $80;
  LHex := '';
  for I := 0 to 15 do
    LHex := LHex + IntToHex(LBytes[I], 2);
  Result := '{' + Copy(LHex, 1, 8) + '-' + Copy(LHex, 9, 4) + '-' + Copy(LHex, 13, 4) + '-' +
    Copy(LHex, 17, 4) + '-' + Copy(LHex, 21, 12) + '}';
end;

{ overrides }

procedure TGenAnalysis.LoadOverrides(const AFileName: string);
var
  LValue: TJSONValue;
begin
  FreeAndNil(FOverrides);
  FOverridesFile := AFileName;
  try
    LValue := TJSONObject.ParseJSONValue(TFile.ReadAllText(AFileName, TEncoding.UTF8), False, True);
  except
    on E: EJSONParseException do
      raise EGenAnalysisError.CreateFmt('%s: ошибка разбора JSON — строка %d, позиция %d ' +
        '(смещение %d): %s', [AFileName, E.Line, E.Position, E.Offset, E.Message]);
  end;
  if not (LValue is TJSONObject) then
  begin
    LValue.Free;
    raise EGenAnalysisError.CreateFmt('%s: корень файла должен быть JSON-объектом', [AFileName]);
  end;
  FOverrides := TJSONObject(LValue);
end;

/// <summary>Строковое JSON-значение (не число).</summary>
function IsJsonText(AValue: TJSONValue): Boolean;
begin
  Result := (AValue is TJSONString) and not (AValue is TJSONNumber);
end;

/// <summary>JSON-массив строк.</summary>
function IsJsonTextList(AValue: TJSONValue): Boolean;
var
  LItem: TJSONValue;
begin
  Result := AValue is TJSONArray;
  if Result then
    for LItem in TJSONArray(AValue) do
      if not IsJsonText(LItem) then
        Exit(False);
end;

function TGenAnalysis.OvSection(const AKey: string): TJSONObject;
var
  LValue: TJSONValue;
begin
  Result := nil;
  if not Assigned(FOverrides) then
    Exit;
  LValue := FOverrides.GetValue(AKey);
  if LValue is TJSONObject then
    Result := TJSONObject(LValue);
end;

function TGenAnalysis.OvType(const AName: string): TJSONObject;
var
  LSection: TJSONObject;
  LValue: TJSONValue;
begin
  Result := nil;
  LSection := OvSection('types');
  if not Assigned(LSection) then
    Exit;
  LValue := LSection.GetValue(AName);
  if LValue is TJSONObject then
    Result := TJSONObject(LValue);
end;

function TGenAnalysis.OvMethod(const AName: string): TJSONObject;
var
  LSection: TJSONObject;
  LValue: TJSONValue;
begin
  Result := nil;
  LSection := OvSection('methods');
  if not Assigned(LSection) then
    Exit;
  LValue := LSection.GetValue(AName);
  if LValue is TJSONObject then
    Result := TJSONObject(LValue);
end;

function TGenAnalysis.OvList(AObj: TJSONObject; const AKey: string): TArray<string>;
var
  LValue: TJSONValue;
  LItem: TJSONValue;
begin
  Result := nil;
  if not Assigned(AObj) then
    Exit;
  LValue := AObj.GetValue(AKey);
  if not Assigned(LValue) or (LValue is TJSONNull) then
    Exit;
  // ValidateOverrides сообщает о неверном типе с путём; здесь — защита от обхода проверки.
  if not IsJsonTextList(LValue) then
    raise EGenAnalysisError.CreateFmt('overrides: ключ «%s» — ожидается массив строк, получено %s',
      [AKey, LValue.ToJSON]);
  for LItem in TJSONArray(LValue) do
    Result := Result + [LItem.Value];
end;

function TGenAnalysis.OvStr(AObj: TJSONObject; const AKey: string): string;
var
  LValue: TJSONValue;
begin
  Result := '';
  if not Assigned(AObj) then
    Exit;
  LValue := AObj.GetValue(AKey);
  if Assigned(LValue) and not (LValue is TJSONNull) then
    Result := LValue.Value;
end;

function TGenAnalysis.OvMap(AObj: TJSONObject; const AKey, AName: string): string;
var
  LValue: TJSONValue;
begin
  Result := '';
  if not Assigned(AObj) then
    Exit;
  LValue := AObj.GetValue(AKey);
  if LValue is TJSONObject then
    Result := OvStr(TJSONObject(LValue), AName);
end;

procedure TGenAnalysis.ValidateOverrides;
const
  CRootKeys: array[0..4] of string = ('$comment', 'types', 'unions', 'methods', 'constants');
  CTypeKeys: array[0..9] of string = ('$comment', 'fields', 'dispatch', 'direction',
    'int64', 'int32', 'fileField', 'primaryParent', 'kindName', 'variantNames');
  CTypeLists: array[0..2] of string = ('int64', 'int32', 'fileField');
  CTypeTexts: array[0..2] of string = ('direction', 'primaryParent', 'kindName');
  CMethodKeys: array[0..5] of string = ('$comment', 'rename', 'positional', 'int64',
    'int32', 'variants');
  CMethodLists: array[0..2] of string = ('positional', 'int64', 'int32');
  CDispatchKeys: array[0..3] of string = ('$comment', 'field', 'rules', 'default');
  CVariantNameKeys: array[0..1] of string = ('String', 'Array');
  CUnionKeys: array[0..2] of string = ('$comment', 'variants', 'description');
  CConstKeys: array[0..2] of string = ('$comment', 'description', 'values');
  CVariantKeys: array[0..4] of string = ('$comment', 'params', 'name', 'result', 'description');
  // «Объект or True» → True: результат Boolean (успех), без разбора объекта.
  CVariantResults: array[0..0] of string = ('Boolean');

  /// <summary>Раздел верхнего уровня: объект или nil (другой тип — ошибка).</summary>
  function Section(const AKey: string): TJSONObject;
  var
    LValue: TJSONValue;
  begin
    Result := nil;
    LValue := FOverrides.GetValue(AKey);
    if LValue is TJSONObject then
      Result := TJSONObject(LValue)
    else if Assigned(LValue) then
      Error('overrides.%s: ожидается объект', [AKey]);
  end;

  /// <summary>Ключ отсутствует или строка; иначе ошибка. True — ключ есть и он строка.</summary>
  function CheckText(AObj: TJSONObject; const AKey, APath: string): Boolean;
  var
    LValue: TJSONValue;
  begin
    LValue := AObj.GetValue(AKey);
    Result := IsJsonText(LValue);
    if Assigned(LValue) and not Result then
      Error('%s.%s: ожидается строка', [APath, AKey]);
  end;

  /// <summary>Ключ отсутствует или массив строк; иначе ошибка. True — массив есть.</summary>
  function CheckList(AObj: TJSONObject; const AKey, APath: string): Boolean;
  var
    LValue: TJSONValue;
  begin
    LValue := AObj.GetValue(AKey);
    Result := IsJsonTextList(LValue);
    if Assigned(LValue) and not Result then
      Error('%s.%s: ожидается массив строк', [APath, AKey]);
  end;

  /// <summary>Ключ отсутствует или объект; иначе ошибка. Результат — объект или nil.</summary>
  function CheckObject(AObj: TJSONObject; const AKey, APath: string): TJSONObject;
  var
    LValue: TJSONValue;
  begin
    Result := nil;
    LValue := AObj.GetValue(AKey);
    if LValue is TJSONObject then
      Result := TJSONObject(LValue)
    else if Assigned(LValue) then
      Error('%s.%s: ожидается объект', [APath, AKey]);
  end;

  procedure CheckKeys(AObj: TJSONObject; const AKeys: array of string; const APath: string);
  var
    LPair: TJSONPair;
  begin
    for LPair in AObj do
      if not MatchStr(LPair.JsonString.Value, AKeys) then
        Warning('%s: неизвестный ключ «%s»', [APath, LPair.JsonString.Value]);
  end;

  /// <summary>Значения объекта — идентификаторы Delphi (имена членов).</summary>
  procedure CheckIdents(AObj: TJSONObject; const APath: string);
  var
    LPair: TJSONPair;
  begin
    for LPair in AObj do
      if LPair.JsonString.Value <> '$comment' then
        if not IsJsonText(LPair.JsonValue) or not IsValidIdent(LPair.JsonValue.Value) or
          IsKeyword(LPair.JsonValue.Value) then
          Error('%s.%s: ожидается идентификатор Delphi (не ключевое слово)',
            [APath, LPair.JsonString.Value]);
  end;

var
  LPair, LInner: TJSONPair;
  LObj, LSub, LMap: TJSONObject;
  LType: TGenType;
  LMethod: TGenMethod;
  LName, LPath: string;
  LItem, LRules, LVariants, LParamItem: TJSONValue;
  LIndex: Integer;
begin
  if not Assigned(FOverrides) then
    Exit;
  CheckKeys(FOverrides, CRootKeys, 'overrides');

  // types: {Тип: {fields {json: PasName}, dispatch {...}, direction, int64/int32/fileField [...], ...}}.
  LObj := Section('types');
  if Assigned(LObj) then
    for LPair in LObj do
    begin
      LPath := 'overrides.types.' + LPair.JsonString.Value;
      if LPair.JsonString.Value = '$comment' then
        Continue;
      if not (LPair.JsonValue is TJSONObject) then
      begin
        Error('%s: ожидается объект', [LPath]);
        Continue;
      end;
      LSub := TJSONObject(LPair.JsonValue);
      CheckKeys(LSub, CTypeKeys, LPath);
      LType := FModel.FindType(LPair.JsonString.Value);
      if not Assigned(LType) then
        Warning('overrides.types: нет типа %s', [LPair.JsonString.Value]);
      for LName in CTypeTexts do
        CheckText(LSub, LName, LPath);
      for LName in CTypeLists do
        if CheckList(LSub, LName, LPath) and Assigned(LType) then
          for LItem in TJSONArray(LSub.GetValue(LName)) do
            if not Assigned(LType.FindField(LItem.Value)) then
              Warning('%s.%s: нет поля %s', [LPath, LName, LItem.Value]);
      // Переименование полей — только ключ fields (параметры методов — rename).
      LMap := CheckObject(LSub, 'fields', LPath);
      if Assigned(LMap) then
      begin
        CheckIdents(LMap, LPath + '.fields');
        if Assigned(LType) then
          for LInner in LMap do
            if (LInner.JsonString.Value <> '$comment') and
              not Assigned(LType.FindField(LInner.JsonString.Value)) then
              Warning('%s.fields: нет поля %s', [LPath, LInner.JsonString.Value]);
      end;
      LMap := CheckObject(LSub, 'variantNames', LPath);
      if Assigned(LMap) then
      begin
        CheckKeys(LMap, CVariantNameKeys, LPath + '.variantNames');
        CheckIdents(LMap, LPath + '.variantNames');
      end;
      LMap := CheckObject(LSub, 'dispatch', LPath);
      if Assigned(LMap) then
      begin
        CheckKeys(LMap, CDispatchKeys, LPath + '.dispatch');
        CheckText(LMap, 'field', LPath + '.dispatch');
        CheckText(LMap, 'default', LPath + '.dispatch');
        LRules := LMap.GetValue('rules');
        if Assigned(LRules) and not (LRules is TJSONArray) then
          Error('%s.dispatch.rules: ожидается массив объектов {value, type}', [LPath])
        else if LRules is TJSONArray then
          for LItem in TJSONArray(LRules) do
            if not (LItem is TJSONObject) or
              not (TJSONObject(LItem).GetValue('value') is TJSONString) or
              not IsJsonText(TJSONObject(LItem).GetValue('type')) then
              Error('%s.dispatch.rules: элемент %s — ожидается {"value": строка или число, ' +
                '"type": строка}', [LPath, LItem.ToJSON]);
      end;
    end;

  // methods: {метод: {rename {json: PasName}, positional/int64/int32 [...], variants}}.
  LObj := Section('methods');
  if Assigned(LObj) then
    for LPair in LObj do
    begin
      LPath := 'overrides.methods.' + LPair.JsonString.Value;
      if LPair.JsonString.Value = '$comment' then
        Continue;
      if not (LPair.JsonValue is TJSONObject) then
      begin
        Error('%s: ожидается объект', [LPath]);
        Continue;
      end;
      LSub := TJSONObject(LPair.JsonValue);
      CheckKeys(LSub, CMethodKeys, LPath);
      LMethod := FModel.FindMethod(LPair.JsonString.Value);
      if not Assigned(LMethod) then
        Warning('overrides.methods: нет метода %s', [LPair.JsonString.Value]);
      for LName in CMethodLists do
        if CheckList(LSub, LName, LPath) and Assigned(LMethod) then
          for LItem in TJSONArray(LSub.GetValue(LName)) do
            if not Assigned(LMethod.FindParam(LItem.Value)) then
              Warning('%s.%s: нет параметра %s', [LPath, LName, LItem.Value]);
      // Переименование параметров — только ключ rename (поля типов — fields).
      LMap := CheckObject(LSub, 'rename', LPath);
      if Assigned(LMap) then
      begin
        CheckIdents(LMap, LPath + '.rename');
        if Assigned(LMethod) then
          for LInner in LMap do
            if (LInner.JsonString.Value <> '$comment') and
              not Assigned(LMethod.FindParam(LInner.JsonString.Value)) then
              Warning('%s.rename: нет параметра %s', [LPath, LInner.JsonString.Value]);
      end;
      // variants: [{params [...], name, result, description}] — смысловые проверки в ResolveVariants.
      LVariants := LSub.GetValue('variants');
      if Assigned(LVariants) and not (LVariants is TJSONArray) then
        Error('%s.variants: ожидается массив объектов {params, name, result, description}', [LPath])
      else if LVariants is TJSONArray then
        for LIndex := 0 to TJSONArray(LVariants).Count - 1 do
        begin
          LItem := TJSONArray(LVariants).Items[LIndex];
          LName := Format('%s.variants[%d]', [LPath, LIndex]);
          if not (LItem is TJSONObject) then
          begin
            Error('%s: ожидается объект {params, name, result, description}', [LName]);
            Continue;
          end;
          CheckKeys(TJSONObject(LItem), CVariantKeys, LName);
          if not CheckList(TJSONObject(LItem), 'params', LName) then
            Error('%s: нужен непустой массив params', [LName])
          else if TJSONArray(TJSONObject(LItem).GetValue('params')).Count = 0 then
            Error('%s: нужен непустой массив params', [LName])
          else if Assigned(LMethod) then
            for LParamItem in TJSONArray(TJSONObject(LItem).GetValue('params')) do
              if not Assigned(LMethod.FindParam(LParamItem.Value)) then
                Error('%s.params: нет параметра %s', [LName, LParamItem.Value]);
          if CheckText(TJSONObject(LItem), 'name', LName) and
            (not IsValidIdent(OvStr(TJSONObject(LItem), 'name')) or
            IsKeyword(OvStr(TJSONObject(LItem), 'name'))) then
            Error('%s.name: ожидается идентификатор (имя метода в стиле Bot API)', [LName]);
          CheckText(TJSONObject(LItem), 'description', LName);
          if CheckText(TJSONObject(LItem), 'result', LName) and
            not MatchStr(OvStr(TJSONObject(LItem), 'result'), CVariantResults) then
            Error('%s.result: допустимо только %s', [LName, string.Join(', ', CVariantResults)]);
        end;
    end;

  // unions: {Алиас: {variants [...], description}} или краткая форма {Алиас: [...]}.
  LObj := Section('unions');
  if Assigned(LObj) then
    for LPair in LObj do
    begin
      LPath := 'overrides.unions.' + LPair.JsonString.Value;
      if LPair.JsonString.Value = '$comment' then
        Continue;
      if not IsValidIdent(LPair.JsonString.Value) then
        Error('%s: имя алиаса должно быть идентификатором Delphi', [LPath]);
      if LPair.JsonValue is TJSONObject then
      begin
        LSub := TJSONObject(LPair.JsonValue);
        CheckKeys(LSub, CUnionKeys, LPath);
        CheckText(LSub, 'description', LPath);
        LVariants := LSub.GetValue('variants');
      end
      else
        LVariants := LPair.JsonValue;
      if not IsJsonTextList(LVariants) then
      begin
        Error('%s: ожидается {"variants": [имена типов], "description": строка} или массив имён',
          [LPath]);
        Continue;
      end;
      if TJSONArray(LVariants).Count < 2 then
        Error('%s.variants: нужно не меньше двух вариантов', [LPath]);
      for LItem in TJSONArray(LVariants) do
        if not Assigned(FModel.FindType(LItem.Value)) then
          Error('%s.variants: нет типа %s', [LPath, LItem.Value]);
    end;

  // constants: {Имя: {description, values {Имя: значение}}}.
  LObj := Section('constants');
  if Assigned(LObj) then
    for LPair in LObj do
    begin
      LPath := 'overrides.constants.' + LPair.JsonString.Value;
      if LPair.JsonString.Value = '$comment' then
        Continue;
      if not IsValidIdent(LPair.JsonString.Value) then
        Error('%s: имя должно быть идентификатором Delphi', [LPath]);
      if not (LPair.JsonValue is TJSONObject) then
      begin
        Error('%s: ожидается объект', [LPath]);
        Continue;
      end;
      LSub := TJSONObject(LPair.JsonValue);
      CheckKeys(LSub, CConstKeys, LPath);
      CheckText(LSub, 'description', LPath);
      LMap := CheckObject(LSub, 'values', LPath);
      if not Assigned(LMap) then
      begin
        Error('%s: нужен объект values', [LPath]);
        Continue;
      end;
      for LInner in LMap do
        if not IsValidIdent(LInner.JsonString.Value) or not IsJsonText(LInner.JsonValue) then
          Error('%s.values.%s: ожидается {"Идентификатор": "строка"}',
            [LPath, LInner.JsonString.Value]);
    end;
end;

{ этапы анализа }

procedure TGenAnalysis.BuildTypes;
var
  LType: TGenType;
  LInfo: TGenTypeInfo;
begin
  for LType in FModel.Types do
  begin
    LInfo := TGenTypeInfo.Create(LType.Name, LType);
    FTypes.Add(LInfo);
    FTypeIndex.Add(LInfo.Name, LInfo);
  end;
end;

procedure TGenAnalysis.ComputeDirections;

  procedure AddNamed(ARef: TGenTypeRef; AList: TStrings);
  begin
    ARef.CollectNamed(AList);
  end;

  procedure Propagate(ARoots: TStrings; ASet: TDictionary<string, Boolean>);
  var
    LStack: TStack<string>;
    LName: string;
    LType: TGenType;
    LField: TGenField;
    LExtra: TGenTypeRef;
    LRefs: TStringList;
  begin
    LStack := TStack<string>.Create;
    LRefs := TStringList.Create;
    try
      for LName in ARoots do
        LStack.Push(LName);
      while LStack.Count > 0 do
      begin
        LName := LStack.Pop;
        if ASet.ContainsKey(LName) or SameStr(LName, CNameInputFile) then
          Continue;
        LType := FModel.FindType(LName);
        if not Assigned(LType) then
          Continue;
        ASet.Add(LName, True);
        LRefs.Clear;
        for LField in LType.Fields do
          LField.TypeRef.CollectNamed(LRefs);
        for LExtra in LType.ExtraVariants do
          LExtra.CollectNamed(LRefs);
        for LName in LType.Subtypes do
          LRefs.Add(LName);
        for LName in LRefs do
          LStack.Push(LName);
      end;
    finally
      LRefs.Free;
      LStack.Free;
    end;
  end;

var
  LInRoots, LOutRoots: TStringList;
  LIn, LOut: TDictionary<string, Boolean>;
  LMethod: TGenMethod;
  LParam: TGenParam;
  LInfo: TGenTypeInfo;
  LForced: string;
begin
  LInRoots := TStringList.Create;
  LOutRoots := TStringList.Create;
  LIn := TDictionary<string, Boolean>.Create;
  LOut := TDictionary<string, Boolean>.Create;
  try
    LInRoots.Add(CNameUpdate);
    for LMethod in FModel.Methods do
    begin
      AddNamed(LMethod.ReturnType, LInRoots);
      for LParam in LMethod.Params do
        AddNamed(LParam.TypeRef, LOutRoots);
    end;
    for LInfo in FTypes do
    begin
      LForced := LowerCase(OvStr(OvType(LInfo.Name), 'direction'));
      if (LForced = 'in') or (LForced = 'both') then
        LInRoots.Add(LInfo.Name);
      if (LForced = 'out') or (LForced = 'both') then
        LOutRoots.Add(LInfo.Name);
      if (LForced <> '') and not MatchStr(LForced, ['in', 'out', 'both']) then
        Error('overrides.types.%s.direction: «%s» — ожидается in, out или both', [LInfo.Name, LForced]);
    end;
    Propagate(LInRoots, LIn);
    Propagate(LOutRoots, LOut);
    for LInfo in FTypes do
      if LIn.ContainsKey(LInfo.Name) and LOut.ContainsKey(LInfo.Name) then
        LInfo.Direction := TGenDirection.Both
      else if LIn.ContainsKey(LInfo.Name) then
        LInfo.Direction := TGenDirection.Incoming
      else if LOut.ContainsKey(LInfo.Name) then
        LInfo.Direction := TGenDirection.Outgoing
      else
        LInfo.Direction := TGenDirection.Unused;
  finally
    LOut.Free;
    LIn.Free;
    LOutRoots.Free;
    LInRoots.Free;
  end;
end;

procedure TGenAnalysis.AssignCategories;
var
  LInfo, LSynth: TGenTypeInfo;
  LExtra: TGenTypeRef;
  LTypes: TArray<TGenTypeInfo>;
  LName, LSuffix: string;
  LCategory: TGenCategory;
  LInsertAt: Integer;
begin
  LTypes := FTypes.ToArray;
  for LInfo in LTypes do
  begin
    if SameStr(LInfo.Name, CNameInputFile) then
      LInfo.Category := TGenCategory.InputFile
    else if LInfo.Spec.IsUnion then
    begin
      if LInfo.Direction = TGenDirection.Outgoing then
        LInfo.Category := TGenCategory.OutUnion
      else
        LInfo.Category := TGenCategory.Polymorphic;
    end
    else
      LInfo.Category := TGenCategory.Regular;

    if LInfo.Spec.ExtraVariants.Count = 0 then
      Continue;
    if LInfo.Category <> TGenCategory.Polymorphic then
    begin
      Error('%s: дополнительные варианты (строка/массив) поддерживаются только у входящих ' +
        'полиморфных типов', [LInfo.Name]);
      Continue;
    end;
    // Синтетические варианты: строка → Plain, массив самого типа → List.
    LInsertAt := FTypes.IndexOf(LInfo) + 1;
    for LExtra in LInfo.Spec.ExtraVariants do
    begin
      if LExtra.Kind = TGenTypeKind.Str then
      begin
        LCategory := TGenCategory.PlainVariant;
        LSuffix := OvMap(OvType(LInfo.Name), 'variantNames', 'String');
        if LSuffix = '' then
          LSuffix := 'Plain';
      end
      else if (LExtra.Kind = TGenTypeKind.ArrayOf) and (LExtra.ArrayDepth = 1) and
        (LExtra.Element.Kind = TGenTypeKind.Named) and SameStr(LExtra.Element.Name, LInfo.Name) then
      begin
        LCategory := TGenCategory.ListVariant;
        LSuffix := OvMap(OvType(LInfo.Name), 'variantNames', 'Array');
        if LSuffix = '' then
          LSuffix := 'List';
      end
      else
      begin
        Error('%s: дополнительный вариант «%s» не поддерживается', [LInfo.Name, LExtra.ToString]);
        Continue;
      end;
      LName := LInfo.Name + LSuffix;
      if FTypeIndex.ContainsKey(LName) then
      begin
        Error('%s: имя синтетического варианта %s совпадает с типом спецификации', [LInfo.Name, LName]);
        Continue;
      end;
      LSynth := TGenTypeInfo.Create(LName, nil);
      LSynth.Category := LCategory;
      LSynth.Direction := LInfo.Direction;
      LSynth.KindName := LSuffix;
      if LCategory = TGenCategory.PlainVariant then
        LSynth.Description := LInfo.Name + ': простой текст (JSON-строка).'
      else
        LSynth.Description := LInfo.Name + ': последовательность фрагментов (JSON-массив).';
      FTypes.Insert(LInsertAt, LSynth);
      Inc(LInsertAt);
      FTypeIndex.Add(LName, LSynth);
    end;
  end;
end;

procedure TGenAnalysis.LinkPolymorphic;
var
  LInfo, LSub, LParent, LTarget: TGenTypeInfo;
  LName, LPrimary, LKindName, LValue: string;
  LField: TGenField;
  LDispatch, LRule: TJSONObject;
  LRules: TJSONValue;
  LItem: TJSONValue;
  LDispatchRule: TGenDispatchRule;
  LSeen: TStringList;
begin
  // Варианты и полиморфные родители.
  for LInfo in FTypes do
  begin
    if not (LInfo.Category in [TGenCategory.Polymorphic, TGenCategory.OutUnion]) then
      Continue;
    for LName in LInfo.Spec.Subtypes do
    begin
      LSub := FindType(LName);
      if not Assigned(LSub) then
      begin
        Error('%s: вариант %s не найден', [LInfo.Name, LName]);
        Continue;
      end;
      LInfo.Variants.Add(LSub);
      if LInfo.Category = TGenCategory.Polymorphic then
        LSub.PolyParents.Add(LInfo);
    end;
  end;
  // Синтетические варианты — сразу после типа-владельца.
  for LInfo in FTypes do
    if LInfo.IsSynthetic then
    begin
      LParent := FindType(Copy(LInfo.Name, 1, Length(LInfo.Name) - Length(LInfo.KindName)));
      LInfo.Base := LParent;
      LInfo.PolyParents.Add(LParent);
      LParent.Variants.Add(LInfo);
    end;

  // Основной родитель.
  for LInfo in FTypes do
  begin
    if LInfo.IsSynthetic or (LInfo.PolyParents.Count = 0) then
      Continue;
    if LInfo.PolyParents.Count = 1 then
      LInfo.Base := LInfo.PolyParents[0]
    else
    begin
      LPrimary := OvStr(OvType(LInfo.Name), 'primaryParent');
      for LParent in LInfo.PolyParents do
        if SameStr(LParent.Name, LPrimary) then
          LInfo.Base := LParent;
      if not Assigned(LInfo.Base) then
        Error('%s входит в несколько полиморфных типов — задайте overrides.types.%s.primaryParent',
          [LInfo.Name, LInfo.Name]);
    end;
    if Assigned(LInfo.Base) and LInfo.Spec.IsUnion then
      Error('%s: вложенные полиморфные типы не поддерживаются', [LInfo.Name]);
  end;

  // Kind и диспетчеризация.
  for LInfo in FTypes do
  begin
    if LInfo.Category <> TGenCategory.Polymorphic then
      Continue;
    LSeen := TStringList.Create;
    try
      LSeen.CaseSensitive := False;
      LSeen.Add('Unknown');
      for LSub in LInfo.Variants do
      begin
        if LSub.Base <> LInfo then
        begin
          if Assigned(LSub.Base) then
            Error('%s: вариант %s имеет другой основной родитель (%s) — диспетчеризация невозможна',
              [LInfo.Name, LSub.Name, LSub.Base.Name]);
          Continue;
        end;
        if not LSub.IsSynthetic then
        begin
          LKindName := OvStr(OvType(LSub.Name), 'kindName');
          if LKindName = '' then
          begin
            if StartsStr(LInfo.Name, LSub.Name) and (Length(LSub.Name) > Length(LInfo.Name)) then
              LKindName := Copy(LSub.Name, Length(LInfo.Name) + 1, MaxInt)
            else
              LKindName := LSub.Name;
          end;
          LSub.KindName := LKindName;
        end;
        if LSeen.IndexOf(LSub.KindName) >= 0 then
          Error('%s: повтор имени варианта Kind «%s» (%s)', [LInfo.Name, LSub.KindName, LSub.Name])
        else
          LSeen.Add(LSub.KindName);
      end;
    finally
      LSeen.Free;
    end;

    LDispatch := nil;
    if Assigned(OvType(LInfo.Name)) and (OvType(LInfo.Name).GetValue('dispatch') is TJSONObject) then
      LDispatch := TJSONObject(OvType(LInfo.Name).GetValue('dispatch'));
    if Assigned(LDispatch) then
    begin
      // Правила из overrides: {"field": "date", "rules": [{"value": "0", "type": "X"}], "default": "Y"}.
      LInfo.DispatchField := OvStr(LDispatch, 'field');
      LRules := LDispatch.GetValue('rules');
      if LRules is TJSONArray then
        for LItem in TJSONArray(LRules) do
        begin
          if not (LItem is TJSONObject) then
            Continue;
          LRule := TJSONObject(LItem);
          LTarget := FindType(OvStr(LRule, 'type'));
          if not Assigned(LTarget) or (LInfo.Variants.IndexOf(LTarget) < 0) then
          begin
            Error('overrides.types.%s.dispatch: «%s» не вариант типа', [LInfo.Name, OvStr(LRule, 'type')]);
            Continue;
          end;
          LDispatchRule.Value := OvStr(LRule, 'value');
          LDispatchRule.Target := LTarget;
          LInfo.DispatchRules.Add(LDispatchRule);
        end;
      LValue := OvStr(LDispatch, 'default');
      if LValue <> '' then
      begin
        LInfo.DispatchDefault := FindType(LValue);
        if not Assigned(LInfo.DispatchDefault) or (LInfo.Variants.IndexOf(LInfo.DispatchDefault) < 0) then
          Error('overrides.types.%s.dispatch.default: «%s» не вариант типа', [LInfo.Name, LValue]);
      end;
      if (LInfo.DispatchField = '') or (LInfo.DispatchRules.Count = 0) then
        Error('overrides.types.%s.dispatch: нужны field и rules', [LInfo.Name]);
    end
    else if LInfo.Spec.Discriminator <> '' then
    begin
      LInfo.DispatchField := LInfo.Spec.Discriminator;
      if not LInfo.Spec.DiscriminatorUnique then
        Error('%s: значения дискриминатора %s повторяются — задайте dispatch в overrides',
          [LInfo.Name, LInfo.DispatchField]);
      for LSub in LInfo.Variants do
        if not LSub.IsSynthetic then
        begin
          LField := LSub.Spec.FindField(LInfo.DispatchField);
          if Assigned(LField) then
            LSub.DiscriminatorValue := LField.ConstValue;
        end;
    end
    else
      Error('%s: нет дискриминатора — задайте overrides.types.%s.dispatch', [LInfo.Name, LInfo.Name]);
  end;
end;

function TGenAnalysis.IsInt64Member(AMember: TGenMember; AOverride: TJSONObject): Boolean;
var
  LName: string;
begin
  LName := AMember.Name;
  if MatchStr(LName, OvList(AOverride, 'int32')) then
    Exit(False);
  if MatchStr(LName, OvList(AOverride, 'int64')) then
    Exit(True);
  Result := AMember.MayExceed32Bits or SameStr(LName, 'id') or EndsStr('_id', LName) or
    EndsStr('_ids', LName) or SameStr(LName, 'date') or EndsStr('_date', LName) or
    SameStr(LName, 'file_size');
end;

function TGenAnalysis.IsFileMember(AMember: TGenMember; AOverride: TJSONObject;
  AOutType: Boolean): Boolean;
begin
  if MatchStr(AMember.Name, OvList(AOverride, 'fileField')) then
    Exit(True);
  Result := AOutType and (AMember.TypeRef.Kind = TGenTypeKind.Str) and
    ContainsText(AMember.Description, 'attach://');
end;

function TGenAnalysis.ResolveUnion(ARef: TGenTypeRef; const AWhere: string): TGenValue;
var
  LNames: TStringList;
  LInfo, LBest: TGenTypeInfo;
  LName, LKey, LAliasName, LExtra: string;
  LAll: Boolean;
  I: Integer;
  LAliases: TJSONObject;
  LPair: TJSONPair;
  LAliasVariants: TArray<string>;
  LUnion: TGenUnionInfo;
  LVariant: TGenTypeInfo;
begin
  Result := TGenValue.Make(TGenValueKind.Str);
  for I := 0 to ARef.VariantCount - 1 do
    if ARef.Variants[I].Kind <> TGenTypeKind.Named then
    begin
      Error('%s: объединение «%s» с не-объектными вариантами не поддерживается', [AWhere, ARef.ToString]);
      Exit;
    end;
  LNames := TStringList.Create;
  try
    ARef.CollectNamed(LNames);
    // 1. Наименьший именованный union, содержащий все варианты.
    LBest := nil;
    for LInfo in FTypes do
    begin
      if not (LInfo.Category in [TGenCategory.Polymorphic, TGenCategory.OutUnion]) then
        Continue;
      LAll := True;
      for LName in LNames do
        if LInfo.Spec.Subtypes.IndexOf(LName) < 0 then
        begin
          LAll := False;
          Break;
        end;
      if LAll and (not Assigned(LBest) or (LInfo.Spec.Subtypes.Count < LBest.Spec.Subtypes.Count)) then
        LBest := LInfo;
    end;
    // Точное совпадение набора вариантов — сразу этот union.
    if Assigned(LBest) and (LBest.Spec.Subtypes.Count = LNames.Count) then
    begin
      FResolvedUnions.Add(Format('%s → %s', [ARef.ToString, LBest.Name]));
      if LBest.Category = TGenCategory.Polymorphic then
        Result := TGenValue.Make(TGenValueKind.Obj, LBest.Name)
      else
        Result := TGenValue.Make(TGenValueKind.UnionRec, LBest.Name);
      Exit;
    end;

    // 2. Алиас из overrides.unions (точный набор вариантов) — приоритетнее
    //    более широкого покрывающего union: {"ReplyMarkup": {"variants": [...], "description": "..."}}.
    LKey := SortedKey(LNames.ToStringArray);
    LAliases := OvSection('unions');
    if Assigned(LAliases) then
      for LPair in LAliases do
      begin
        if LPair.JsonValue is TJSONArray then
          LAliasVariants := OvList(LAliases, LPair.JsonString.Value)
        else if LPair.JsonValue is TJSONObject then
          LAliasVariants := OvList(TJSONObject(LPair.JsonValue), 'variants')
        else
          Continue;
        if not SameStr(SortedKey(LAliasVariants), LKey) then
          Continue;
        LAliasName := LPair.JsonString.Value;
        if not FUnionIndex.TryGetValue(LAliasName, LUnion) then
        begin
          if FTypeIndex.ContainsKey(LAliasName) then
          begin
            Error('overrides.unions.%s: имя совпадает с типом спецификации', [LAliasName]);
            Exit;
          end;
          LUnion := TGenUnionInfo.Create(LAliasName, True);
          FUnions.Add(LUnion);
          FUnionIndex.Add(LAliasName, LUnion);
          if LPair.JsonValue is TJSONObject then
            LUnion.Description := OvStr(TJSONObject(LPair.JsonValue), 'description');
          // Порядок вариантов — как в спецификации.
          for I := 0 to ARef.VariantCount - 1 do
          begin
            LVariant := FindType(ARef.Variants[I].Name);
            if Assigned(LVariant) then
              LUnion.Variants.Add(LVariant);
          end;
        end;
        FResolvedUnions.Add(Format('%s → %s (алиас)', [ARef.ToString, LAliasName]));
        Exit(TGenValue.Make(TGenValueKind.UnionRec, LAliasName));
      end;

    // 3. Покрывающий union строго шире: работает, но принимает лишние варианты.
    if Assigned(LBest) then
    begin
      LExtra := '';
      for LName in LBest.Spec.Subtypes do
        if LNames.IndexOf(LName) < 0 then
          LExtra := LExtra + IfThen(LExtra <> '', ', ', '') + LName;
      Warning('%s: объединение «%s» представлено более широким %s (лишние варианты: %s) — ' +
        'для точного типа добавьте алиас в overrides.unions', [AWhere, ARef.ToString, LBest.Name, LExtra]);
      FResolvedUnions.Add(Format('%s → %s (шире: +%s)', [ARef.ToString, LBest.Name, LExtra]));
      if LBest.Category = TGenCategory.Polymorphic then
        Result := TGenValue.Make(TGenValueKind.Obj, LBest.Name)
      else
        Result := TGenValue.Make(TGenValueKind.UnionRec, LBest.Name);
      Exit;
    end;
    Error('%s: для объединения «%s» нет покрывающего типа — добавьте алиас в overrides.unions',
      [AWhere, ARef.ToString]);
  finally
    LNames.Free;
  end;
end;

function TGenAnalysis.ResolveRef(ARef: TGenTypeRef; const AWhere: string; AInt64, AFile,
  AAllowOrTrue: Boolean): TGenValue;
var
  LInfo: TGenTypeInfo;
begin
  Result := TGenValue.Make(TGenValueKind.Str);
  case ARef.Kind of
    TGenTypeKind.Int:
      if AInt64 then
        Result := TGenValue.Make(TGenValueKind.Int64)
      else
        Result := TGenValue.Make(TGenValueKind.Int);
    TGenTypeKind.Float:
      Result := TGenValue.Make(TGenValueKind.Float);
    TGenTypeKind.Str:
      if AFile then
        Result := TGenValue.Make(TGenValueKind.InputFile)
      else
        Result := TGenValue.Make(TGenValueKind.Str);
    TGenTypeKind.Bool:
      Result := TGenValue.Make(TGenValueKind.Bool);
    TGenTypeKind.TrueConst:
      Result := TGenValue.Make(TGenValueKind.TrueValue);
    TGenTypeKind.Named:
      if SameStr(ARef.Name, CNameInputFile) then
        Result := TGenValue.Make(TGenValueKind.InputFile)
      else
      begin
        LInfo := FindType(ARef.Name);
        if not Assigned(LInfo) then
          Error('%s: неизвестный тип %s', [AWhere, ARef.Name])
        else if LInfo.Category = TGenCategory.OutUnion then
          Result := TGenValue.Make(TGenValueKind.UnionRec, LInfo.Name)
        else
          Result := TGenValue.Make(TGenValueKind.Obj, LInfo.Name);
      end;
    TGenTypeKind.ArrayOf:
      begin
        Result := ResolveRef(ARef.Element, AWhere, AInt64, AFile, False);
        Inc(Result.Depth);
        if Result.Depth > 2 then
          Error('%s: массивы глубже 2 не поддерживаются', [AWhere]);
      end;
    TGenTypeKind.Union:
      if ARef.IsChatId then
        Result := TGenValue.Make(TGenValueKind.ChatId)
      else if ARef.IsInputFileOrString then
        Result := TGenValue.Make(TGenValueKind.InputFile)
      else if AAllowOrTrue and (ARef.VariantCount = 2) and
        (ARef.Variants[0].Kind = TGenTypeKind.Named) and
        (ARef.Variants[1].Kind = TGenTypeKind.TrueConst) then
      begin
        Result := ResolveRef(ARef.Variants[0], AWhere, AInt64, AFile, False);
        Result.OrTrue := True;
      end
      else
        Result := ResolveUnion(ARef, AWhere);
  else
    Error('%s: нераспознанный тип «%s»', [AWhere, ARef.Source]);
  end;
end;

function TGenAnalysis.MakeMember(AMember: TGenMember; const AOwnerName: string;
  AOverride: TJSONObject; const ARenameKey: string; AOutType: Boolean;
  const AKeywordPrefix: string): TGenMemberInfo;
var
  LWhere, LRename: string;
  LInt64, LFile: Boolean;
begin
  LWhere := AOwnerName + '.' + AMember.Name;
  Result := TGenMemberInfo.Create;
  try
    Result.Name := AMember.Name;
    Result.Required := AMember.Required;
    Result.Description := AMember.Description;
    // Переименование: types.X.fields (поля) или methods.X.rename (параметры) —
    // тот же ключ, что проверяет ValidateOverrides.
    LRename := OvMap(AOverride, ARenameKey, AMember.Name);
    if LRename <> '' then
      Result.PasName := LRename
    else
    begin
      Result.PasName := PascalCase(AMember.Name);
      if IsKeyword(Result.PasName) then
      begin
        Result.PasName := AKeywordPrefix + Result.PasName;
        FRenames.Add(Format('%s → %s (ключевое слово)', [LWhere, Result.PasName]));
      end;
    end;
    Result.ArgName := 'A' + Result.PasName;
    LInt64 := IsInt64Member(AMember, AOverride);
    LFile := IsFileMember(AMember, AOverride, AOutType);
    Result.Value := ResolveRef(AMember.TypeRef, LWhere, LInt64, LFile, False);
    if (Result.Value.Kind = TGenValueKind.Int64) then
      FInt64Members.Add(LWhere);
    if Result.Value.Kind = TGenValueKind.InputFile then
      FFileMembers.Add(Format('%s: %s', [LWhere, AMember.TypeRef.ToString]));
    AddUnionUsage(Result.Value, LWhere);
  except
    Result.Free;
    raise;
  end;
end;

function TGenAnalysis.NeedsHasName(AMember: TGenMemberInfo; ARequired: Boolean): Boolean;
var
  LName: string;
begin
  // Has* — для необязательных числовых и логических полей входящих типов.
  // Поля типа True (TrueValue) не получают Has*: значение и есть признак наличия.
  // Поля has_* не получают Has* (HasHas*): отсутствие поля читается как False.
  LName := AMember.PasName;
  Result := not ARequired and not AMember.Value.IsArray and
    (AMember.Value.Kind in [TGenValueKind.Int, TGenValueKind.Int64, TGenValueKind.Float,
      TGenValueKind.Bool]) and
    not (StartsStr('Has', LName) and (Length(LName) > 3) and CharInSet(LName[4], ['A'..'Z']));
end;

function TGenAnalysis.CanRead(const AValue: TGenValue): Boolean;
begin
  // Должно соответствовать TGenEmitter.ReadExpr.
  if AValue.Kind = TGenValueKind.Obj then
    Exit(AValue.Depth <= 2);
  case AValue.Depth of
    0: Result := AValue.Kind in [TGenValueKind.Str, TGenValueKind.Int, TGenValueKind.Int64,
         TGenValueKind.Float, TGenValueKind.Bool, TGenValueKind.TrueValue, TGenValueKind.ChatId];
    1: Result := AValue.Kind in [TGenValueKind.Str, TGenValueKind.Int, TGenValueKind.Int64,
         TGenValueKind.Float, TGenValueKind.Bool, TGenValueKind.TrueValue];
  else
    Result := False;
  end;
end;

function TGenAnalysis.CanWrite(const AValue: TGenValue): Boolean;
begin
  // Должно соответствовать TGenEmitter.WriteStmt и TGenEmitter.ParamsAddStmt.
  case AValue.Depth of
    0: Result := True;
    1: Result := AValue.Kind in [TGenValueKind.Obj, TGenValueKind.UnionRec, TGenValueKind.Str,
         TGenValueKind.Int, TGenValueKind.Int64, TGenValueKind.Float, TGenValueKind.Bool,
         TGenValueKind.TrueValue];
    2: Result := AValue.Kind = TGenValueKind.Obj;
  else
    Result := False;
  end;
end;

procedure TGenAnalysis.AddUnionUsage(const AValue: TGenValue; const AWhere: string);
var
  LUnion: TGenUnionInfo;
begin
  if (AValue.Kind = TGenValueKind.UnionRec) and FUnionIndex.TryGetValue(AValue.TypeName, LUnion) then
    LUnion.Usages.Add(AWhere);
end;

procedure TGenAnalysis.BuildOutUnions;
var
  LInfo: TGenTypeInfo;
  LUnion: TGenUnionInfo;
begin
  // Создаются до разрешения полей, чтобы учитывать использование.
  for LInfo in FTypes do
    if LInfo.Category = TGenCategory.OutUnion then
    begin
      LUnion := TGenUnionInfo.Create(LInfo.Name, False);
      LUnion.Description := LInfo.Description;
      LUnion.Variants.AddRange(LInfo.Variants);
      FUnions.Add(LUnion);
      FUnionIndex.Add(LUnion.Name, LUnion);
    end;
end;

procedure TGenAnalysis.ResolveTypeMembers;
var
  LInfo: TGenTypeInfo;
  LField: TGenField;
  LMember: TGenMemberInfo;
  LOverride: TJSONObject;
  LDiscriminators: TStringList;
  LParent: TGenTypeInfo;
  LName: string;
begin
  LDiscriminators := TStringList.Create;
  try
    for LInfo in FTypes do
    begin
      if not (LInfo.Category in [TGenCategory.Regular]) then
        Continue;
      LOverride := OvType(LInfo.Name);
      // Дискриминаторы всех родительских union (полиморфных и исходящих).
      LDiscriminators.Clear;
      for LName in LInfo.Spec.Parents do
      begin
        LParent := FindType(LName);
        if not Assigned(LParent) then
          Continue;
        if LParent.DispatchField <> '' then
          LDiscriminators.Add(LParent.DispatchField)
        else if LParent.Spec.Discriminator <> '' then
          LDiscriminators.Add(LParent.Spec.Discriminator);
      end;
      for LField in LInfo.Spec.Fields do
      begin
        LMember := MakeMember(LField, LInfo.Name, LOverride, 'fields', LInfo.IsOut, LInfo.Name);
        LInfo.Members.Add(LMember);
        if (LDiscriminators.IndexOf(LField.Name) >= 0) and (LField.ConstValue <> '') then
        begin
          LMember.Discriminator := True;
          LMember.ConstValue := LField.ConstValue;
          // Дискриминатор-ключевое слово заменяется свойством Kind полиморфного родителя.
          if IsKeyword(PascalCase(LField.Name)) then
          begin
            LMember.Hidden := True;
            LMember.PasName := 'Kind';
            LMember.ArgName := 'AKind';
          end;
        end
        else if LInfo.IsOut and (LField.ConstValue <> '') then
          LMember.ConstValue := LField.ConstValue
        else if LInfo.IsOut and LField.Required and (LMember.Value.Kind = TGenValueKind.TrueValue) and
          not LMember.Value.IsArray then
          LMember.ConstValue := 'true';
        if LInfo.IsIn and NeedsHasName(LMember, LField.Required) then
          LMember.HasName := 'Has' + LMember.PasName;
      end;
    end;
  finally
    LDiscriminators.Free;
  end;
end;

function TGenAnalysis.ValueHasFiles(const AValue: TGenValue): Boolean;
var
  LInfo: TGenTypeInfo;
  LUnion: TGenUnionInfo;
begin
  case AValue.Kind of
    TGenValueKind.InputFile:
      Result := True;
    TGenValueKind.Obj:
      begin
        LInfo := FindType(AValue.TypeName);
        Result := Assigned(LInfo) and LInfo.HasFiles;
      end;
    TGenValueKind.UnionRec:
      Result := FUnionIndex.TryGetValue(AValue.TypeName, LUnion) and LUnion.HasFiles;
  else
    Result := False;
  end;
end;

procedure TGenAnalysis.ComputeHasFiles;
var
  LChanged: Boolean;
  LInfo, LVariant: TGenTypeInfo;
  LMember: TGenMemberInfo;
  LHas: Boolean;
begin
  repeat
    LChanged := False;
    for LInfo in FTypes do
    begin
      if LInfo.HasFiles then
        Continue;
      LHas := False;
      for LMember in LInfo.Members do
        if ValueHasFiles(LMember.Value) then
          LHas := True;
      for LVariant in LInfo.Variants do
        if LVariant.HasFiles then
          LHas := True;
      if LHas then
      begin
        LInfo.HasFiles := True;
        LChanged := True;
      end;
    end;
  until not LChanged;

  for LInfo in FTypes do
    if LInfo.HasFiles and (LInfo.Direction = TGenDirection.Both) then
      Error('%s: двунаправленный тип (Both) содержит файлы — так генерировать нельзя', [LInfo.Name]);
end;

procedure TGenAnalysis.ComputeCommonMembers;
var
  LInfo, LFirst, LSub: TGenTypeInfo;
  LMember, LOther, LCommon: TGenMemberInfo;
  LAll, LRequired: Boolean;
begin
  for LInfo in FTypes do
  begin
    if LInfo.Category <> TGenCategory.Polymorphic then
      Continue;
    LFirst := nil;
    for LSub in LInfo.Variants do
      if not LSub.IsSynthetic and (LSub.Base = LInfo) then
      begin
        LFirst := LSub;
        Break;
      end;
    if not Assigned(LFirst) then
      Continue;
    for LMember in LFirst.Members do
    begin
      LAll := True;
      LRequired := LMember.Required;
      for LSub in LInfo.Variants do
      begin
        if LSub.IsSynthetic or (LSub.Base <> LInfo) then
          Continue;
        LOther := LSub.FindMember(LMember.Name);
        if not Assigned(LOther) or not LOther.Value.SameAs(LMember.Value) or
          not SameText(LOther.PasName, LMember.PasName) then
        begin
          LAll := False;
          Break;
        end;
        LRequired := LRequired and LOther.Required;
      end;
      if not LAll then
        Continue;
      LCommon := LMember.Clone;
      LCommon.Required := LRequired;
      LCommon.ConstValue := '';
      // Описание первого варианта у дискриминатора неверно для базового типа.
      if LCommon.Discriminator then
        LCommon.Description := Format('Значение поля %s в JSON; вид объекта — свойство Kind.',
          [LCommon.Name]);
      if NeedsHasName(LCommon, LRequired) then
        LCommon.HasName := 'Has' + LCommon.PasName
      else
        LCommon.HasName := '';
      LInfo.Members.Add(LCommon);
      for LSub in LInfo.Variants do
        if not LSub.IsSynthetic and (LSub.Base = LInfo) then
          LSub.FindMember(LMember.Name).IsCommon := True;
    end;
  end;
end;

procedure TGenAnalysis.ResolveMethods;
var
  LMethod: TGenMethod;
  LInfo: TGenMethodInfo;
  LParam: TGenParam;
  LMember: TGenMemberInfo;
  LOverride: TJSONObject;
  LPrefix: string;
  LMatch: Integer;
begin
  for LMethod in FModel.Methods do
  begin
    LInfo := TGenMethodInfo.Create(LMethod);
    FMethods.Add(LInfo);
    LInfo.PasName := UpperCase(LMethod.Name.Substring(0, 1)) + LMethod.Name.Substring(1);
    LOverride := OvMethod(LMethod.Name);
    // Префикс для параметров-ключевых слов: имя метода без глагола (sendPoll → Poll).
    LMatch := 1;
    while (LMatch < Length(LMethod.Name)) and not CharInSet(LMethod.Name.Chars[LMatch], ['A'..'Z']) do
      Inc(LMatch);
    LPrefix := LMethod.Name.Substring(LMatch);
    if LPrefix = '' then
      LPrefix := LInfo.PasName;
    for LParam in LMethod.Params do
    begin
      LMember := MakeMember(LParam, LMethod.Name, LOverride, 'rename', True, LPrefix);
      LInfo.Params.Add(LMember);
      // Аргумент совпадает со служебным именем генерируемого метода
      // (sendPoll.options → AOptions) — префикс метода.
      if MatchText(LMember.ArgName, CMethodReservedArgs) then
      begin
        LMember.ArgName := 'A' + LPrefix + LMember.PasName;
        FRenames.Add(Format('%s.%s: аргумент %s (служебное имя)', [LMethod.Name, LParam.Name,
          LMember.ArgName]));
      end;
      if not LMember.Required and MatchStr(LParam.Name, OvList(LOverride, 'positional')) then
        LMember.Required := True;
      if ValueHasFiles(LMember.Value) then
        LInfo.HasFiles := True;
    end;
    LInfo.Result := ResolveRef(LMethod.ReturnType, LMethod.Name + ' → результат', False, False, True);
    if (LInfo.Result.Kind in [TGenValueKind.ChatId, TGenValueKind.InputFile, TGenValueKind.UnionRec]) or
      (LInfo.Result.IsArray and (LInfo.Result.Kind <> TGenValueKind.Obj)) or (LInfo.Result.Depth > 1) then
      Error('%s: тип результата «%s» не поддерживается', [LMethod.Name, LMethod.ReturnType.ToString]);
  end;
end;

procedure TGenAnalysis.ResolveVariants;
var
  LMethod, LVariant: TGenMethodInfo;
  LOverride, LObj: TJSONObject;
  LList, LItem: TJSONValue;
  LParams: TArray<TGenMemberInfo>;
  LParam, LMember, LPrev: TGenMemberInfo;
  LWhere, LName, LVariantName: string;
  LIndex: Integer;
  LValid, LFound: Boolean;
begin
  // Структура ключа проверена в ValidateOverrides; здесь — смысл и создание вариантов.
  for LMethod in FMethods do
  begin
    LOverride := OvMethod(LMethod.Name);
    if not Assigned(LOverride) then
      Continue;
    LList := LOverride.GetValue('variants');
    if not (LList is TJSONArray) then
      Continue;
    LIndex := 0;
    for LItem in TJSONArray(LList) do
    begin
      Inc(LIndex);
      LWhere := Format('overrides.methods.%s.variants[%d]', [LMethod.Name, LIndex - 1]);
      if not (LItem is TJSONObject) then
        Continue;
      LObj := TJSONObject(LItem);
      LParams := nil;
      LValid := True;
      for LName in OvList(LObj, 'params') do
      begin
        LMember := nil;
        for LParam in LMethod.Params do
          if SameStr(LParam.Name, LName) then
            LMember := LParam;
        if not Assigned(LMember) then
        begin
          Error('%s.params: нет параметра %s', [LWhere, LName]);
          LValid := False;
          Continue;
        end;
        for LPrev in LParams do
          if LPrev = LMember then
          begin
            Error('%s.params: параметр %s указан дважды', [LWhere, LName]);
            LValid := False;
          end;
        // Позиционный параметр присваивается полю опций: массивы (open array) так не передать.
        if not LMember.Required and LMember.Value.IsArray then
        begin
          Error('%s.params: необязательный параметр-массив %s нельзя сделать позиционным',
            [LWhere, LName]);
          LValid := False;
        end;
        LParams := LParams + [LMember];
      end;
      // Вариант строит запрос через Build базового метода — нужны все его позиционные.
      for LParam in LMethod.Positional do
      begin
        LFound := False;
        for LPrev in LParams do
          if LPrev = LParam then
            LFound := True;
        if not LFound then
        begin
          Error('%s.params: нет обязательного параметра %s', [LWhere, LParam.Name]);
          LValid := False;
        end;
      end;
      if not LValid then
        Continue;

      LVariant := TGenMethodInfo.CreateVariant(LMethod, LIndex, LParams);
      LMethod.Variants.Add(LVariant);
      LVariant.Description := OvStr(LObj, 'description');
      LVariantName := OvStr(LObj, 'name');
      if LVariantName <> '' then
        LVariant.PasName := UpperCase(LVariantName.Substring(0, 1)) + LVariantName.Substring(1);
      if Length(LVariant.Promoted) = 0 then
        Error('%s: вариант не выносит в позиционные ни одного необязательного параметра', [LWhere]);
      if OvStr(LObj, 'result') = 'Boolean' then
      begin
        if LMethod.Result.OrTrue then
          LVariant.Result := TGenValue.Make(TGenValueKind.TrueValue)
        else
          Error('%s.result: Boolean допустим только для результата «Объект or True» (у %s — %s)',
            [LWhere, LMethod.Name, LMethod.Result.ToString]);
      end;
      if LVariant.OwnExec and SameText(LVariant.PasName, LMethod.PasName) then
        Error('%s: вариант с другим результатом должен иметь своё имя (name)', [LWhere]);
    end;
  end;
end;

procedure TGenAnalysis.BuildConstants;
var
  LSection, LObj, LValues: TJSONObject;
  LPair, LValuePair: TJSONPair;
  LConst: TGenConstInfo;
  LUpdate: TGenType;
  LField: TGenField;
begin
  LSection := OvSection('constants');
  if Assigned(LSection) then
    for LPair in LSection do
    begin
      if not (LPair.JsonValue is TJSONObject) then
        Continue;
      LObj := TJSONObject(LPair.JsonValue);
      LConst := TGenConstInfo.Create(LPair.JsonString.Value);
      FConstants.Add(LConst);
      LConst.Description := OvStr(LObj, 'description');
      if LObj.GetValue('values') is TJSONObject then
      begin
        LValues := TJSONObject(LObj.GetValue('values'));
        for LValuePair in LValues do
        begin
          LConst.Names.Add(LValuePair.JsonString.Value);
          LConst.Values.Add(LValuePair.JsonValue.Value);
        end;
      end;
    end;
  // Типы обновлений для allowed_updates — из полей Update.
  if Assigned(LSection) and Assigned(LSection.GetValue('UpdateType')) then
    Exit;
  LUpdate := FModel.FindType(CNameUpdate);
  if not Assigned(LUpdate) then
    Exit;
  LConst := TGenConstInfo.Create('UpdateType');
  FConstants.Add(LConst);
  LConst.Description := 'Типы обновлений (значения allowed_updates), по полям Update.';
  for LField in LUpdate.Fields do
    if not LField.Required then
    begin
      LConst.Names.Add(PascalCase(LField.Name));
      LConst.Values.Add(LField.Name);
    end;
end;

procedure TGenAnalysis.ComputeGuids;
var
  LInfo: TGenTypeInfo;
begin
  for LInfo in FTypes do
    if LInfo.IsInterface then
      LInfo.Guid := NameGuid('TgBot/' + LInfo.IntfName);
end;

procedure TGenAnalysis.CheckSupport;
var
  LInfo: TGenTypeInfo;
  LMember: TGenMemberInfo;
  LMethod: TGenMethodInfo;
begin
  // Те же правила, что у генератора (ReadExpr/WriteStmt/ParamsAddStmt): неподдерживаемое
  // значение — ошибка анализа с местом, а не исключение посреди генерации.
  for LInfo in FTypes do
  begin
    if not LInfo.IsInterface then
      Continue;
    for LMember in LInfo.Members do
    begin
      if LMember.Hidden then
        Continue;
      if LInfo.IsIn and not CanRead(LMember.Value) then
        Error('%s.%s: чтение значения «%s» не поддерживается', [LInfo.Name, LMember.Name,
          LMember.Value.ToString]);
      if LInfo.IsOut and (LInfo.Category = TGenCategory.Regular) and (LMember.ConstValue = '') and
        not CanWrite(LMember.Value) then
        Error('%s.%s: запись значения «%s» не поддерживается', [LInfo.Name, LMember.Name,
          LMember.Value.ToString]);
    end;
  end;
  for LMethod in FMethods do
    for LMember in LMethod.Params do
      if not CanWrite(LMember.Value) then
        Error('%s.%s: параметр «%s» не поддерживается', [LMethod.Name, LMember.Name,
          LMember.Value.ToString]);
end;

procedure TGenAnalysis.CheckUnusedAliases;
var
  LSection: TJSONObject;
  LPair: TJSONPair;
begin
  LSection := OvSection('unions');
  if not Assigned(LSection) then
    Exit;
  for LPair in LSection do
    if (LPair.JsonString.Value <> '$comment') and not FUnionIndex.ContainsKey(LPair.JsonString.Value) then
      Warning('overrides.unions.%s: алиас не использован (нет объединения с таким набором вариантов)',
        [LPair.JsonString.Value]);
end;

procedure TGenAnalysis.CheckNames;
var
  LGlobal: TDictionary<string, string>;

  procedure AddGlobal(const AName, AOwner: string);
  var
    LPrev: string;
  begin
    if LGlobal.TryGetValue(UpperCase(AName), LPrev) then
      Error('Конфликт имён: %s (%s и %s)', [AName, LPrev, AOwner])
    else
      LGlobal.Add(UpperCase(AName), AOwner);
  end;

  procedure CheckLocal(ANames: TStrings; const AName, AOwner: string);
  begin
    if ANames.IndexOf(AName) >= 0 then
      Error('%s: конфликт имён членов «%s»', [AOwner, AName])
    else
      ANames.Add(AName);
  end;

  procedure AddTypeMembers(AInfo: TGenTypeInfo; ANames: TStrings; ADeclaring: Boolean);
  var
    LMember: TGenMemberInfo;
    LSub: TGenTypeInfo;
  begin
    if AInfo.Category = TGenCategory.Polymorphic then
    begin
      CheckLocal(ANames, 'Kind', AInfo.Name);
      CheckLocal(ANames, 'GetKind', AInfo.Name);
      CheckLocal(ANames, 'KindText', AInfo.Name);
      CheckLocal(ANames, 'GetKindText', AInfo.Name);
      for LSub in AInfo.Variants do
        CheckLocal(ANames, 'As' + LSub.KindName, AInfo.Name);
    end;
    for LMember in AInfo.Members do
    begin
      if LMember.Hidden or (ADeclaring and LMember.IsCommon) then
        Continue;
      if AInfo.IsIn then
      begin
        CheckLocal(ANames, LMember.PasName, AInfo.Name);
        CheckLocal(ANames, 'Get' + LMember.PasName, AInfo.Name);
        if LMember.HasName <> '' then
        begin
          CheckLocal(ANames, LMember.HasName, AInfo.Name);
          CheckLocal(ANames, 'Get' + LMember.HasName, AInfo.Name);
        end;
      end;
    end;
  end;

var
  LInfo, LBase: TGenTypeInfo;
  LUnion: TGenUnionInfo;
  LMethod, LVariant: TGenMethodInfo;
  LConst: TGenConstInfo;
  LMember: TGenMemberInfo;
  LNames, LGroup: TStringList;
  LName: string;
begin
  LGlobal := TDictionary<string, string>.Create;
  LGroup := TStringList.Create;
  LNames := TStringList.Create;
  try
    LNames.CaseSensitive := False;
    LGroup.CaseSensitive := False;
    for LName in CRuntimeNames do
      if not LGlobal.ContainsKey(UpperCase(LName)) then
        LGlobal.Add(UpperCase(LName), 'рантайм');
    for LInfo in FTypes do
      if LInfo.IsInterface then
      begin
        AddGlobal(LInfo.IntfName, LInfo.Name);
        AddGlobal(LInfo.RecName, LInfo.Name);
        AddGlobal(LInfo.ImplName, LInfo.Name);
        AddGlobal(LInfo.MakeName, LInfo.Name);
        if LInfo.Category = TGenCategory.Polymorphic then
          AddGlobal(LInfo.KindEnumName, LInfo.Name);
      end;
    for LUnion in FUnions do
      AddGlobal(LUnion.RecName, 'union ' + LUnion.Name);
    for LConst in FConstants do
      AddGlobal(LConst.RecName, 'константы ' + LConst.Name);
    for LMethod in FMethods do
      if LMethod.HasOptions then
        AddGlobal(LMethod.OptionsName, LMethod.Name);

    // Члены интерфейсов (с учётом базового).
    for LInfo in FTypes do
    begin
      if not LInfo.IsInterface then
        Continue;
      LNames.Clear;
      for LName in CDtoMemberNames do
        LNames.Add(LName);
      for LName in CObjectMemberNames do
        LNames.Add(LName);
      LBase := LInfo.Base;
      if Assigned(LBase) then
        AddTypeMembers(LBase, LNames, False);
      AddTypeMembers(LInfo, LNames, Assigned(LBase));
      if LInfo.IsOut and not (LInfo.Category = TGenCategory.Polymorphic) then
        for LMember in LInfo.Members do
          if not LMember.Hidden and (LMember.ConstValue = '') then
            CheckLocal(LNames, 'With' + LMember.PasName, LInfo.Name);
      for LMember in LInfo.Members do
        if (LMember.PasName = 'Kind') and not LMember.Hidden and Assigned(LBase) then
          Error('%s: поле %s совпадает со свойством Kind', [LInfo.Name, LMember.Name]);
    end;

    // Методы клиента.
    LNames.Clear;
    for LName in CApiCoreNames do
      LNames.Add(LName);
    for LName in CObjectMemberNames do
      LNames.Add(LName);
    for LMethod in FMethods do
    begin
      CheckLocal(LNames, LMethod.PasName, 'TTgApi');
      CheckLocal(LNames, LMethod.PasName + 'Async', 'TTgApi');
      CheckLocal(LNames, 'Try' + LMethod.PasName, 'TTgApi');
      // Приватные хелперы: построение параметров и выполнение.
      CheckLocal(LNames, LMethod.BuildName, 'TTgApi');
      CheckLocal(LNames, LMethod.ExecName, 'TTgApi');
      // Варианты: одноимённые с методом (или друг с другом) — перегрузки,
      // их различимость проверяет CheckOverloads; новое имя не должно быть занято.
      LGroup.Clear;
      LGroup.Add(LMethod.PasName);
      for LVariant in LMethod.Variants do
      begin
        if LGroup.IndexOf(LVariant.PasName) < 0 then
        begin
          LGroup.Add(LVariant.PasName);
          CheckLocal(LNames, LVariant.PasName, 'TTgApi');
          CheckLocal(LNames, LVariant.PasName + 'Async', 'TTgApi');
          CheckLocal(LNames, 'Try' + LVariant.PasName, 'TTgApi');
        end;
        CheckLocal(LNames, LVariant.BuildName, 'TTgApi');
        if LVariant.OwnExec then
          CheckLocal(LNames, LVariant.ExecName, 'TTgApi');
      end;
    end;
    for LMethod in FMethods do
    begin
      LNames.Clear;
      for LName in CMethodReservedArgs do
        LNames.Add(LName);
      LNames.Add('ApplyTo');
      for LMember in LMethod.Params do
      begin
        CheckLocal(LNames, LMember.ArgName, LMethod.Name);
        if not LMember.Required then
          CheckLocal(LNames, LMember.PasName, LMethod.Name + ' (опции)');
      end;
    end;
  finally
    LNames.Free;
    LGroup.Free;
    LGlobal.Free;
  end;
end;

type
  /// <summary>Параметр перегрузки TTgApi (CheckOverloads).</summary>
  TGenSigItem = record
    /// <summary>Тип параметра; одинаковые ключи — одинаковые типы.</summary>
    Key: string;
    Kind: TGenValueKind;
    /// <summary>Скаляр, принимающий аргумент с неявным преобразованием (не out, не колбэк, не опции).</summary>
    Convertible: Boolean;
  end;

  /// <summary>Перегрузка метода TTgApi: параметры и минимум аргументов (с учётом AOnError = nil).</summary>
  TGenOverload = record
    Name: string;
    Owner: string;
    Items: TArray<TGenSigItem>;
    MinArgs: Integer;
  end;

function SigItem(const AKey: string; AKind: TGenValueKind; AConvertible: Boolean): TGenSigItem;
begin
  Result.Key := AKey;
  Result.Kind := AKind;
  Result.Convertible := AConvertible;
end;

/// <summary>
///   Разные типы, между которыми аргумент может неявно преобразоваться:
///   TTgChatId ← string/Integer/Int64 (Implicit), числа между собой.
/// </summary>
function ImplicitPair(const A, B: TGenSigItem): Boolean;
const
  CNumbers: set of TGenValueKind = [TGenValueKind.Int, TGenValueKind.Int64, TGenValueKind.Float];
  CToChatId: set of TGenValueKind = [TGenValueKind.Str, TGenValueKind.Int, TGenValueKind.Int64];
begin
  Result := A.Convertible and B.Convertible and (
    ((A.Kind = TGenValueKind.ChatId) and (B.Kind in CToChatId)) or
    ((B.Kind = TGenValueKind.ChatId) and (A.Kind in CToChatId)) or
    ((A.Kind in CNumbers) and (B.Kind in CNumbers)));
end;

procedure TGenAnalysis.CheckOverloads;
var
  LList: TList<TGenOverload>;

  function ParamItems(AMethod: TGenMethodInfo; AWithOptions: Boolean): TArray<TGenSigItem>;
  var
    LParam: TGenMemberInfo;
  begin
    Result := nil;
    for LParam in AMethod.Positional do
      Result := Result + [SigItem(LParam.Value.ToString, LParam.Value.Kind, not LParam.Value.IsArray)];
    if AWithOptions then
      Result := Result + [SigItem(AMethod.OptionsName, TGenValueKind.UnionRec, False)];
  end;

  procedure Add(const AName: string; AMethod: TGenMethodInfo; const AItems: TArray<TGenSigItem>;
    AMinArgs: Integer);
  var
    LOverload: TGenOverload;
    LItem: TGenSigItem;
    LText: string;
  begin
    LText := '';
    for LItem in AItems do
      LText := LText + IfThen(LText <> '', '; ', '') + LItem.Key;
    LOverload.Name := AName;
    LOverload.Owner := Format('%s%s(%s)', [AMethod.Name,
      IfThen(AMethod.IsVariant, Format(' [вариант %d]', [AMethod.VariantIndex]), ''), LText]);
    LOverload.Items := AItems;
    LOverload.MinArgs := AMinArgs;
    LList.Add(LOverload);
  end;

  procedure AddMethod(AMethod: TGenMethodInfo);
  var
    LItems: TArray<TGenSigItem>;
    LValue: TGenValue;
    LResult: string;
    LWithOptions: Boolean;
  begin
    // Тип результата в Delphi: «Объект or True» — тот же интерфейс, True — Boolean.
    LValue := AMethod.Result;
    LValue.OrTrue := False;
    if LValue.Kind = TGenValueKind.TrueValue then
      LResult := 'Boolean'
    else
      LResult := LValue.ToString;
    for LWithOptions in [False, True] do
    begin
      if LWithOptions and not AMethod.HasOptions then
        Continue;
      LItems := ParamItems(AMethod, LWithOptions);
      Add(AMethod.PasName, AMethod, LItems, Length(LItems));
      Add(AMethod.PasName + 'Async', AMethod, LItems + [
        SigItem('TProc<' + LResult + '>', TGenValueKind.Obj, False),
        SigItem('TProc<Exception>', TGenValueKind.Obj, False)], Length(LItems) + 1);
      if AMethod.Result.Kind <> TGenValueKind.TrueValue then
        LItems := LItems + [SigItem('out ' + LResult, TGenValueKind.Obj, False)];
      LItems := LItems + [SigItem('out TTgErrorInfo', TGenValueKind.Obj, False)];
      Add('Try' + AMethod.PasName, AMethod, LItems, Length(LItems));
    end;
  end;

var
  LMethod, LVariant: TGenMethodInfo;
  A, B: TGenOverload;
  I, J, K, P: Integer;
  LSame, LImplicit: Boolean;
begin
  // Перегрузки одного имени должны различаться при любом допустимом числе
  // аргументов: одинаковые типы — ошибка компиляции объявления, типы с
  // неявным преобразованием (TTgChatId ← string/Int64, числа) — риск
  // неоднозначного вызова. Колбэки, опции и out-параметры — точное совпадение.
  LList := TList<TGenOverload>.Create;
  try
    for LMethod in FMethods do
    begin
      AddMethod(LMethod);
      for LVariant in LMethod.Variants do
        AddMethod(LVariant);
    end;
    for I := 0 to LList.Count - 1 do
      for J := I + 1 to LList.Count - 1 do
      begin
        A := LList[I];
        B := LList[J];
        if not SameText(A.Name, B.Name) then
          Continue;
        for K := Max(A.MinArgs, B.MinArgs) to Min(Length(A.Items), Length(B.Items)) do
        begin
          LSame := True;
          LImplicit := True;
          for P := 0 to K - 1 do
            if A.Items[P].Key <> B.Items[P].Key then
            begin
              LSame := False;
              if not ImplicitPair(A.Items[P], B.Items[P]) then
                LImplicit := False;
            end;
          if LSame then
            Error('TTgApi.%s: перегрузки %s и %s неразличимы при %d аргументах', [A.Name, A.Owner,
              B.Owner, K])
          else if LImplicit then
            Error('TTgApi.%s: перегрузки %s и %s неоднозначны при %d аргументах (неявные ' +
              'преобразования TTgChatId/чисел)', [A.Name, A.Owner, B.Owner, K]);
          if LSame or LImplicit then
            Break;
        end;
      end;
  finally
    LList.Free;
  end;
end;

procedure TGenAnalysis.BuildOrder;
var
  LVisited: TDictionary<TGenTypeInfo, Boolean>;

  procedure Visit(AInfo: TGenTypeInfo);
  begin
    if LVisited.ContainsKey(AInfo) then
      Exit;
    LVisited.Add(AInfo, True);
    if Assigned(AInfo.Base) then
      Visit(AInfo.Base);
    FOrdered.Add(AInfo);
  end;

var
  LInfo: TGenTypeInfo;
begin
  FOrdered.Clear;
  LVisited := TDictionary<TGenTypeInfo, Boolean>.Create;
  try
    for LInfo in FTypes do
      if LInfo.IsInterface then
        Visit(LInfo);
  finally
    LVisited.Free;
  end;
end;

procedure TGenAnalysis.Run;
var
  LInfo: TGenTypeInfo;
  LUnion: TGenUnionInfo;
  LMethod: TGenMethodInfo;
begin
  ValidateOverrides;
  // Неверные overrides: дальнейший анализ опирался бы на них — только отчёт об ошибках.
  if FErrors.Count > 0 then
    Exit;
  BuildTypes;
  ComputeDirections;
  AssignCategories;
  LinkPolymorphic;
  BuildOutUnions;
  ResolveTypeMembers;
  ComputeHasFiles;
  ComputeCommonMembers;
  ResolveMethods;
  ResolveVariants;
  CheckUnusedAliases;
  BuildConstants;
  ComputeGuids;
  CheckSupport;
  CheckNames;
  CheckOverloads;
  BuildOrder;
  // По умолчанию генерируется всё.
  for LInfo in FTypes do
    LInfo.Included := LInfo.IsInterface;
  for LUnion in FUnions do
    LUnion.Included := True;
  for LMethod in FMethods do
    LMethod.Included := True;
end;

function TGenAnalysis.FindType(const AName: string): TGenTypeInfo;
begin
  if not FTypeIndex.TryGetValue(AName, Result) then
    Result := nil;
end;

function TGenAnalysis.FindUnion(const AName: string): TGenUnionInfo;
begin
  if not FUnionIndex.TryGetValue(AName, Result) then
    Result := nil;
end;

procedure TGenAnalysis.IncludeUnion(AUnion: TGenUnionInfo);
var
  LVariant: TGenTypeInfo;
begin
  if AUnion.Included then
    Exit;
  AUnion.Included := True;
  for LVariant in AUnion.Variants do
    IncludeType(LVariant);
end;

procedure TGenAnalysis.IncludeValue(const AValue: TGenValue);
var
  LUnion: TGenUnionInfo;
  LInfo: TGenTypeInfo;
begin
  case AValue.Kind of
    TGenValueKind.Obj:
      begin
        LInfo := FindType(AValue.TypeName);
        if Assigned(LInfo) then
          IncludeType(LInfo);
      end;
    TGenValueKind.UnionRec:
      if FUnionIndex.TryGetValue(AValue.TypeName, LUnion) then
        IncludeUnion(LUnion);
  end;
end;

procedure TGenAnalysis.IncludeType(AType: TGenTypeInfo);
var
  LMember: TGenMemberInfo;
  LVariant: TGenTypeInfo;
  LUnion: TGenUnionInfo;
begin
  if AType.Category = TGenCategory.OutUnion then
  begin
    if FUnionIndex.TryGetValue(AType.Name, LUnion) then
      IncludeUnion(LUnion);
    Exit;
  end;
  if not AType.IsInterface or AType.Included then
    Exit;
  AType.Included := True;
  if Assigned(AType.Base) then
    IncludeType(AType.Base);
  for LMember in AType.Members do
    IncludeValue(LMember.Value);
  if AType.Category = TGenCategory.Polymorphic then
    for LVariant in AType.Variants do
      if LVariant.Base = AType then
        IncludeType(LVariant);
end;

procedure TGenAnalysis.IncludeMethod(AMethod: TGenMethodInfo);
var
  LParam: TGenMemberInfo;
begin
  if AMethod.Included then
    Exit;
  AMethod.Included := True;
  for LParam in AMethod.Params do
    IncludeValue(LParam.Value);
  IncludeValue(AMethod.Result);
end;

procedure TGenAnalysis.Restrict(const AOnly: string);
var
  LName: string;
  LInfo: TGenTypeInfo;
  LUnion: TGenUnionInfo;
  LMethod, LFound: TGenMethodInfo;
begin
  FRestricted := True;
  for LInfo in FTypes do
    LInfo.Included := False;
  for LUnion in FUnions do
    LUnion.Included := False;
  for LMethod in FMethods do
    LMethod.Included := False;
  for LName in AOnly.Split([','], TStringSplitOptions.ExcludeEmpty) do
  begin
    LInfo := FindType(Trim(LName));
    if Assigned(LInfo) then
    begin
      IncludeType(LInfo);
      Continue;
    end;
    LUnion := FindUnion(Trim(LName));
    if Assigned(LUnion) then
    begin
      IncludeUnion(LUnion);
      Continue;
    end;
    LFound := nil;
    for LMethod in FMethods do
      if SameText(LMethod.Name, Trim(LName)) then
        LFound := LMethod;
    if not Assigned(LFound) then
      raise EGenAnalysisError.CreateFmt('--only: неизвестный тип или метод «%s»', [Trim(LName)]);
    IncludeMethod(LFound);
  end;
end;

procedure TGenAnalysis.WriteReport(AOut: TStrings);

  procedure Section(const ATitle: string; ACount: Integer);
  begin
    AOut.Add('');
    AOut.Add(Format('%s (%d):', [ATitle, ACount]));
    if ACount = 0 then
      AOut.Add('  нет');
  end;

  procedure List(const ATitle: string; AItems: TStrings);
  var
    LItem: string;
  begin
    Section(ATitle, AItems.Count);
    for LItem in AItems do
      AOut.Add('  ' + LItem);
  end;

var
  LInfo, LSub: TGenTypeInfo;
  LUnion: TGenUnionInfo;
  LMethod, LVariant: TGenMethodInfo;
  LConst: TGenConstInfo;
  LCounts: array[TGenDirection] of Integer;
  LDir: TGenDirection;
  LLines: TStringList;
  LLine, LVariants: string;
  LRule: TGenDispatchRule;
  LMultipart, LOptions, LCommon: Integer;
  LMember: TGenMemberInfo;
begin
  LLines := TStringList.Create;
  try
    for LDir := Low(TGenDirection) to High(TGenDirection) do
      LCounts[LDir] := 0;
    for LInfo in FTypes do
      if LInfo.Category <> TGenCategory.InputFile then
        Inc(LCounts[LInfo.Direction]);
    AOut.Add(Format('Bot API %s: типов %d, методов %d; overrides: %s', [FModel.Version,
      FModel.Types.Count, FModel.Methods.Count, IfThen(FOverridesFile <> '', FOverridesFile, 'нет')]));
    AOut.Add(Format('Направления: In %d, Out %d, Both %d, не используются %d',
      [LCounts[TGenDirection.Incoming], LCounts[TGenDirection.Outgoing], LCounts[TGenDirection.Both],
      LCounts[TGenDirection.Unused]]));

    LLines.Clear;
    for LInfo in FTypes do
      if (LInfo.Direction in [TGenDirection.Both, TGenDirection.Unused]) and
        (LInfo.Category <> TGenCategory.InputFile) then
        LLines.Add(Format('%-36s %s', [LInfo.Name, DirectionText(LInfo.Direction)]));
    List('Типы Both и неиспользуемые', LLines);

    LLines.Clear;
    for LInfo in FTypes do
      if LInfo.Category = TGenCategory.Polymorphic then
      begin
        LCommon := 0;
        for LMember in LInfo.Members do
          if not LMember.Hidden then
            Inc(LCommon);
        if LInfo.DispatchRules.Count > 0 then
        begin
          LLine := Format('%s [%s; правила:', [LInfo.Name, DirectionText(LInfo.Direction)]);
          for LRule in LInfo.DispatchRules do
            LLine := LLine + Format(' %s=%s→%s', [LInfo.DispatchField, LRule.Value, LRule.Target.Name]);
          if Assigned(LInfo.DispatchDefault) then
            LLine := LLine + ', иначе ' + LInfo.DispatchDefault.Name;
          LLine := LLine + ']';
        end
        else
          LLine := Format('%s [%s; по %s]', [LInfo.Name, DirectionText(LInfo.Direction), LInfo.DispatchField]);
        LLine := LLine + Format(' общих свойств %d; Kind:', [LCommon]);
        for LSub in LInfo.Variants do
          if LSub.DiscriminatorValue <> '' then
            LLine := LLine + Format(' %s=%s', [LSub.KindName, LSub.DiscriminatorValue])
          else
            LLine := LLine + ' ' + LSub.KindName;
        LLines.Add(LLine);
      end;
    List('Полиморфные типы (интерфейс + Kind + As*)', LLines);

    LLines.Clear;
    for LUnion in FUnions do
    begin
      LVariants := '';
      for LSub in LUnion.Variants do
        LVariants := LVariants + IfThen(LVariants <> '', ', ', '') + LSub.Name;
      LLines.Add(Format('%s%s%s: %s', [LUnion.RecName, IfThen(LUnion.IsAlias, ' (алиас)', ''),
        IfThen(LUnion.HasFiles, ' [файлы]', ''), LVariants]));
    end;
    List('Записи-объединения (исходящие)', LLines);
    List('Разрешённые безымянные объединения', FResolvedUnions);

    LLines.Clear;
    for LInfo in FTypes do
      if LInfo.HasFiles and (LInfo.Category <> TGenCategory.InputFile) then
        LLines.Add(LInfo.Name);
    List('Типы с файлами (транзитивно)', LLines);
    List('Файловые поля и параметры (TTgInputFile)', FFileMembers);
    List('Int64-поля и параметры', FInt64Members);
    List('Переименования (ключевые слова)', FRenames);

    LLines.Clear;
    LMultipart := 0;
    LOptions := 0;
    for LMethod in FMethods do
    begin
      if LMethod.HasFiles then
      begin
        Inc(LMultipart);
        LLines.Add(LMethod.Name);
      end;
      if LMethod.HasOptions then
        Inc(LOptions);
    end;
    List('Методы с файлами в параметрах (multipart при загрузке)', LLines);
    AOut.Add('');
    AOut.Add(Format('Методы: %d, с записью опций: %d, с файлами: %d', [FMethods.Count, LOptions, LMultipart]));

    LLines.Clear;
    for LMethod in FMethods do
      for LVariant in LMethod.Variants do
      begin
        LVariants := '';
        for LMember in LVariant.Positional do
          LVariants := LVariants + IfThen(LVariants <> '', ', ', '') + LMember.Name;
        LLines.Add(Format('%s → %s(%s)%s%s', [LMethod.Name, LVariant.PasName, LVariants,
          IfThen(LVariant.HasOptions, ' [+ опции]', ''),
          IfThen(LVariant.OwnExec, ': Boolean (ответ true)', '')]));
      end;
    List('Варианты методов (overrides methods.*.variants)', LLines);

    LLines.Clear;
    for LConst in FConstants do
      LLines.Add(Format('%s: %d значений', [LConst.RecName, LConst.Names.Count]));
    List('Константы', LLines);

    List('Предупреждения', FWarnings);
    List('Ошибки (в т.ч. конфликты имён)', FErrors);
  finally
    LLines.Free;
  end;
end;

end.
