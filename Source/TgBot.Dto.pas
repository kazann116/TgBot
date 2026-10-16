unit TgBot.Dto;

{
  TgBot — рантайм-базы для кода, генерируемого TgBotGen.

  - ITgJsonObject / TTgJsonDto — входящие и двунаправленные объекты поверх
    JSON. Корневой объект владеет JSON (или его держателем), вложенные
    ссылаются на часть JSON корня и удерживают корень ссылкой на интерфейс.
  - ITgOutObject / TTgOutObject — исходящие объекты: простые значения
    хранятся в JSON, файлы и вложенные объекты — отдельно; Serialize
    регистрирует загружаемые файлы в TTgParams (attach://…).
  - TTgDto — хелперы: массивы из JSON, разбор результатов методов,
    сериализация вложенных объектов.
  - Клиент Bot API (TTgApiCore) — в TgBot.Core.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.Generics.Collections,
  System.JSON,
  TgBot.Base,
  TgBot.Json;

type
  /// <summary>
  ///   Объект Bot API поверх JSON (входящий или двунаправленный).
  ///   Вложенные объекты и элементы результатов-массивов (например, каждое
  ///   Update из getUpdates) разделяют JSON всего ответа и удерживают его
  ///   целиком, пока жив хотя бы один из них. Для длительного хранения
  ///   отдельного объекта возьмите независимую копию: Clone или TTgDto.Detach&lt;T&gt;.
  /// </summary>
  ITgJsonObject = interface
    ['{FD25460D-3387-4DB1-B06B-778E3F6139D2}']
    function GetRaw: TJSONObject;
    function GetRawValue: TJSONValue;
    /// <summary>JSON-текст объекта.</summary>
    function AsJson: string;
    /// <summary>
    ///   Независимая копия объекта того же типа со своим JSON: не удерживает
    ///   JSON исходного ответа (пакета getUpdates и т.п.) и не зависит от
    ///   последующих изменений оригинала. Приведение к нужному интерфейсу —
    ///   через Supports/as или TTgDto.Detach&lt;T&gt;.
    /// </summary>
    function Clone: ITgJsonObject;
    /// <summary>
    ///   JSON-объект; nil, если значение не объект (например, RichText-строка).
    ///   Владелец — DTO, не освобождайте его.
    /// </summary>
    property Raw: TJSONObject read GetRaw;
    /// <summary>JSON-значение (объект, строка или массив). Владелец — DTO.</summary>
    property RawValue: TJSONValue read GetRawValue;
  end;

  /// <summary>Исходящий объект Bot API (параметр метода или его часть).</summary>
  ITgOutObject = interface
    ['{E1CA1CC1-263D-49FB-A020-07BC3BD2FDB6}']
    /// <summary>
    ///   JSON-представление (освобождает вызывающий). Загружаемые файлы
    ///   регистрируются в AParams (поле получает 'attach://имя'); при
    ///   AParams = nil загрузка файлов невозможна — ETgError.
    /// </summary>
    function Serialize(AParams: TTgParams): TJSONObject;
  end;

  /// <summary>
  ///   Служебный интерфейс держателя JSON (TTgJsonHolder): через него DTO
  ///   хранит держателя и узнаёт его среди владельцев (Supports). В
  ///   прикладном коде не нужен.
  /// </summary>
  ITgJsonHolder = interface
    ['{F668E69E-3ECF-4BCF-8640-8D01C3E3B8AA}']
    function GetValue: TJSONValue;
    /// <summary>На часть JSON ссылается вложенный DTO: вытесненные значения сохраняются.</summary>
    procedure MarkShared;
    /// <summary>
    ///   Принимает значение, удалённое из JSON (владение переходит к держателю):
    ///   освобождает сразу или, если есть вложенные DTO, хранит до уничтожения.
    /// </summary>
    procedure Retire(AValue: TJSONAncestor);
    /// <summary>Корневое значение (nil для держателя чужого JSON).</summary>
    property Value: TJSONValue read GetValue;
  end;

  /// <summary>
  ///   Владелец JSON-значения, разделяемого несколькими DTO (корень и вложенные).
  ///   Значения, вытесненные из JSON при замене полей (Set*/With*), не
  ///   освобождаются сразу, если на часть JSON уже ссылаются вложенные DTO:
  ///   они хранятся до уничтожения держателя (защита от use-after-free).
  ///   Живёт по счётчику ссылок: храните как ITgJsonHolder (или IInterface).
  /// </summary>
  TTgJsonHolder = class(TInterfacedObject, ITgJsonHolder)
  private
    FValue: TJSONValue;
    FParent: IInterface;
    FRetired: TObjectList<TJSONAncestor>;
    FShared: Boolean;
    function GetValue: TJSONValue;
  public
    /// <summary>Держатель, владеющий AValue (nil допустим).</summary>
    constructor Create(AValue: TJSONValue);
    /// <summary>
    ///   Держатель чужого JSON: удерживает AParent (владельца JSON) и владеет
    ///   только вытесненными значениями.
    /// </summary>
    constructor CreateFor(const AParent: IInterface);
    destructor Destroy; override;
    /// <summary>На часть JSON ссылается вложенный DTO: вытесненные значения сохраняются.</summary>
    procedure MarkShared;
    /// <summary>
    ///   Принимает значение, удалённое из JSON (владение переходит к держателю):
    ///   освобождает сразу или, если есть вложенные DTO, хранит до уничтожения.
    /// </summary>
    procedure Retire(AValue: TJSONAncestor);
    /// <summary>Корневое значение (nil для держателя чужого JSON).</summary>
    property Value: TJSONValue read GetValue;
  end;

  TTgJsonDto = class;
  /// <summary>Класс DTO (для Clone — создание копии того же класса).</summary>
  TTgJsonDtoClass = class of TTgJsonDto;

  /// <summary>
  ///   База DTO поверх JSON. Методы Set* изменяют JSON (fluent With* у
  ///   двунаправленных типов); для вложенного DTO меняется JSON корня.
  ///   JSON всегда принадлежит держателю (ITgJsonHolder), общему для корня и
  ///   вложенных DTO.
  /// </summary>
  TTgJsonDto = class(TInterfacedObject, ITgJsonObject)
  private
    FValue: TJSONValue;
    // Единственная (счётная) ссылка на держателя: удерживает JSON.
    FHolder: ITgJsonHolder;
    /// <summary>JSON-объект DTO; значение — не объект: ETgError с именем поля AName.</summary>
    function RequireJson(const AName: string): TJSONObject;
  protected
    /// <summary>JSON-объект DTO или nil, если значение — не объект.</summary>
    FJson: TJSONObject;
    /// <summary>Владелец JSON для вложенных DTO (держатель).</summary>
    function JsonOwner: IInterface;
    /// <summary>Значение-строка (RichText Plain); иначе ''.</summary>
    function ValueText: string;
    /// <summary>Значение-массив (RichText List); иначе nil.</summary>
    function ValueArray: TJSONArray;
    /// <summary>
    ///   Заменяет поле AName; владение AValue переходит к DTO. nil — удалить поле.
    ///   Прежнее значение передаётся держателю (вложенные DTO, полученные
    ///   ранее, остаются действительными и видят прежние данные).
    /// </summary>
    procedure SetValue(const AName: string; AValue: TJSONValue);
    procedure SetStr(const AName, AValue: string);
    procedure SetInt(const AName: string; AValue: Integer);
    procedure SetInt64(const AName: string; AValue: Int64);
    procedure SetDouble(const AName: string; AValue: Double);
    procedure SetBool(const AName: string; AValue: Boolean);
    procedure SetChatId(const AName: string; const AValue: TTgChatId);
    /// <summary>file_id/URL — строкой; загрузка невозможна (ETgError).</summary>
    procedure SetFile(const AName: string; const AValue: TTgInputFile);
    /// <summary>Вложенный объект (ITgJsonObject) копируется в JSON; nil — удалить поле.</summary>
    procedure SetObject(const AName: string; const AValue: IInterface);
    procedure SetObjects(const AName: string; const AValues: TArray<IInterface>);
    procedure SetObjects2(const AName: string; const AValues: TArray<TArray<IInterface>>);
    /// <summary>Добавляет строку в двумерный массив AName (создаёт массив при отсутствии).</summary>
    procedure AppendRow(const AName: string; const ARow: TArray<IInterface>);
    procedure SetStrings(const AName: string; const AValues: TArray<string>);
    procedure SetIntegers(const AName: string; const AValues: TArray<Integer>);
    procedure SetInt64s(const AName: string; const AValues: TArray<Int64>);
    procedure SetDoubles(const AName: string; const AValues: TArray<Double>);
    procedure SetBooleans(const AName: string; const AValues: TArray<Boolean>);
  public
    /// <summary>
    ///   DTO над AValue. AOwner = nil — владение AValue переходит к новому
    ///   держателю DTO; иначе AValue — часть JSON владельца (держателя или
    ///   другого объекта), которого DTO удерживает.
    /// </summary>
    constructor Create(AValue: TJSONValue; const AOwner: IInterface); virtual;
    /// <summary>Новый пустой JSON-объект (фабрики исходящих объектов).</summary>
    constructor CreateNew;
    /// <summary>Новый DTO, владеющий AValue (RichText Plain/List).</summary>
    constructor CreateValue(AValue: TJSONValue);
    destructor Destroy; override;
    function GetRaw: TJSONObject;
    function GetRawValue: TJSONValue;
    function AsJson: string;
    function Clone: ITgJsonObject;
  end;

  /// <summary>
  ///   База исходящего объекта: простые значения — в JSON, файлы и вложенные
  ///   объекты — отдельно до сериализации. Повторная установка поля заменяет
  ///   прежнее значение.
  /// </summary>
  TTgOutObject = class(TInterfacedObject, ITgOutObject)
  private type
    TPartKind = (InputFile, Obj, Objs, Objs2);
    TPart = record
      Name: string;
      Kind: TPartKind;
      FileValue: TTgInputFile;
      Obj: IInterface;
      Objs: TArray<IInterface>;
      Objs2: TArray<TArray<IInterface>>;
    end;
  private
    FJson: TJSONObject;
    FParts: TList<TPart>;
    function IndexOfPart(const AName: string): Integer;
    procedure RemoveField(const AName: string);
    procedure SetJsonValue(const AName: string; AValue: TJSONValue);
    procedure AddPart(const APart: TPart);
  protected
    procedure SetStr(const AName, AValue: string);
    procedure SetInt(const AName: string; AValue: Integer);
    procedure SetInt64(const AName: string; AValue: Int64);
    procedure SetDouble(const AName: string; AValue: Double);
    procedure SetBool(const AName: string; AValue: Boolean);
    procedure SetChatId(const AName: string; const AValue: TTgChatId);
    /// <summary>Файл; пустой — удалить поле.</summary>
    procedure SetFile(const AName: string; const AValue: TTgInputFile);
    /// <summary>Вложенный объект (ITgOutObject или ITgJsonObject); nil — удалить поле.</summary>
    procedure SetObject(const AName: string; const AValue: IInterface);
    procedure SetObjects(const AName: string; const AValues: TArray<IInterface>);
    procedure SetObjects2(const AName: string; const AValues: TArray<TArray<IInterface>>);
    procedure AppendRow(const AName: string; const ARow: TArray<IInterface>);
    procedure SetStrings(const AName: string; const AValues: TArray<string>);
    procedure SetIntegers(const AName: string; const AValues: TArray<Integer>);
    procedure SetInt64s(const AName: string; const AValues: TArray<Int64>);
    procedure SetDoubles(const AName: string; const AValues: TArray<Double>);
    procedure SetBooleans(const AName: string; const AValues: TArray<Boolean>);
  public
    constructor CreateNew;
    destructor Destroy; override;
    function Serialize(AParams: TTgParams): TJSONObject;
  end;

  /// <summary>Фабрика DTO по JSON-значению; неподходящее значение — nil.</summary>
  TTgDtoFactory<T> = reference to function(AJson: TJSONValue; const AOwner: IInterface): T;

  /// <summary>Хелперы генерируемого кода.</summary>
  TTgDto = record
  private
    /// <summary>
    ///   Освобождает AValue и возвращает исключение «неожиданный результат».
    ///   Объявлено в интерфейсе: используется generic-методами.
    /// </summary>
    class function UnexpectedResult(AValue: TJSONValue; const AMethod: string): ETgError; static;
    /// <summary>
    ///   Копия AValue (ITgJsonObject.Clone), приведённая к интерфейсу с
    ///   RTTI ATypeInfo, в AResult. Объявлено в интерфейсе: используется Detach&lt;T&gt;.
    /// </summary>
    class procedure DetachTo(const AValue: IInterface; ATypeInfo: Pointer; out AResult); static;
  public
    /// <summary>Массив DTO из JSON-массива (nil — пустой результат).</summary>
    class function Objects<T>(AArray: TJSONArray; const AOwner: IInterface;
      const AFactory: TTgDtoFactory<T>): TArray<T>; static;
    /// <summary>Двумерный массив DTO.</summary>
    class function Objects2<T>(AArray: TJSONArray; const AOwner: IInterface;
      const AFactory: TTgDtoFactory<T>): TArray<TArray<T>>; static;
    /// <summary>
    ///   Массивы скаляров. Элемент другого типа — значение по умолчанию;
    ///   число не целое или вне диапазона типа — ETgError (политика TTgJson;
    ///   AName — имя поля для сообщения).
    /// </summary>
    class function Strings(AArray: TJSONArray): TArray<string>; static;
    class function Integers(AArray: TJSONArray; const AName: string = ''): TArray<Integer>; static;
    class function Int64s(AArray: TJSONArray; const AName: string = ''): TArray<Int64>; static;
    class function Doubles(AArray: TJSONArray; const AName: string = ''): TArray<Double>; static;
    class function Booleans(AArray: TJSONArray): TArray<Boolean>; static;
    /// <summary>Идентификатор чата из поля (число или строка); нет поля — пустой.</summary>
    class function GetChatId(AObj: TJSONObject; const AName: string): TTgChatId; static;
    /// <summary>Индекс строкового значения поля AField в AValues или -1.</summary>
    class function IndexOfValue(AObj: TJSONObject; const AField: string;
      const AValues: array of string): Integer; static;
    /// <summary>Открытый массив интерфейсов → TArray&lt;IInterface&gt;.</summary>
    class function ToIntf<T: IInterface>(const AValues: array of T): TArray<IInterface>; static;
    class function ToIntf2<T: IInterface>(const AValues: array of TArray<T>): TArray<TArray<IInterface>>; static;
    /// <summary>Копия открытого массива (для захвата анонимным методом).</summary>
    class function CopyArray<T>(const AValues: array of T): TArray<T>; static;
    /// <summary>
    ///   JSON вложенного объекта: ITgOutObject.Serialize или копия JSON
    ///   ITgJsonObject; nil — nil. Результат освобождает вызывающий.
    /// </summary>
    class function Serialize(const AValue: IInterface; AParams: TTgParams): TJSONValue; static;
    /// <summary>
    ///   JSON-массив объектов. Пустой элемент (nil или незаданная
    ///   запись-объединение) — ETgError; AName — имя поля для сообщения.
    /// </summary>
    class function SerializeArray(const AValues: TArray<IInterface>; AParams: TTgParams;
      const AName: string = ''): TJSONArray; static;
    class function SerializeArray2(const AValues: TArray<TArray<IInterface>>;
      AParams: TTgParams; const AName: string = ''): TJSONArray; static;
    class function StringsJson(const AValues: TArray<string>): TJSONArray; static;
    class function IntegersJson(const AValues: TArray<Integer>): TJSONArray; static;
    class function Int64sJson(const AValues: TArray<Int64>): TJSONArray; static;
    /// <summary>Массив вещественных (не зависит от локали); NaN/бесконечность — ETgError.</summary>
    class function DoublesJson(const AValues: TArray<Double>; const AName: string = ''): TJSONArray; static;
    class function BooleansJson(const AValues: TArray<Boolean>): TJSONArray; static;
    /// <summary>
    ///   Независимая копия DTO (ITgJsonObject.Clone) с приведением к T.
    ///   Используйте для длительного хранения элементов результатов-массивов
    ///   (например, Update из getUpdates), чтобы не удерживать весь ответ.
    ///   nil — nil; объект не DTO поверх JSON — ETgError.
    /// </summary>
    class function Detach<T: IInterface>(const AValue: T): T; static;
    /// <summary>Разбор JSON-текста фабрикой; ошибка разбора или неподходящее значение — nil.</summary>
    class function Parse<T>(const AJsonText: string; const AFactory: TTgDtoFactory<T>): T; static;
    /// <summary>Результат-объект метода; владение AValue переходит к результату.</summary>
    class function ResultObject<T>(AValue: TJSONValue; const AMethod: string;
      const AFactory: TTgDtoFactory<T>): T; static;
    /// <summary>Результат «объект или True»: True — Default(T) (nil).</summary>
    class function ResultObjectOrTrue<T>(AValue: TJSONValue; const AMethod: string;
      const AFactory: TTgDtoFactory<T>): T; static;
    /// <summary>
    ///   Результат-массив объектов. Элементы разделяют JSON всего ответа
    ///   (см. ITgJsonObject.Clone, TTgDto.Detach).
    /// </summary>
    class function ResultArray<T>(AValue: TJSONValue; const AMethod: string;
      const AFactory: TTgDtoFactory<T>): TArray<T>; static;
    class function ResultBool(AValue: TJSONValue; const AMethod: string): Boolean; static;
    class function ResultStr(AValue: TJSONValue; const AMethod: string): string; static;
    /// <summary>
    ///   Целые результаты: не число — ETgError «неожиданный результат»;
    ///   число не целое или вне диапазона — ETgError (политика TTgJson).
    /// </summary>
    class function ResultInt(AValue: TJSONValue; const AMethod: string): Integer; static;
    class function ResultInt64(AValue: TJSONValue; const AMethod: string): Int64; static;
    class function ResultDouble(AValue: TJSONValue; const AMethod: string): Double; static;
  end;

implementation

uses
  System.TypInfo,
  TgBot.Consts;

/// <summary>
///   Имя класса реализации интерфейса для текста ошибки; '?' для nil и
///   для реализации не на Delphi (без EIntfCastError от as TObject).
/// </summary>
function IntfClassName(const AValue: IInterface): string;
begin
  // Только диагностика (имя класса в тексте ошибки): приведение после проверки is.
  if AValue is TObject then
    Result := TObject(AValue).ClassName
  else
    Result := '?';
end;

{ TTgJsonHolder }

constructor TTgJsonHolder.Create(AValue: TJSONValue);
begin
  inherited Create;
  FValue := AValue;
end;

constructor TTgJsonHolder.CreateFor(const AParent: IInterface);
begin
  inherited Create;
  FParent := AParent;
end;

destructor TTgJsonHolder.Destroy;
begin
  // Вытесненные значения могли ссылаться на объекты корня — освобождаем раньше корня.
  FreeAndNil(FRetired);
  FreeAndNil(FValue);
  FParent := nil;
  inherited Destroy;
end;

function TTgJsonHolder.GetValue: TJSONValue;
begin
  Result := FValue;
end;

procedure TTgJsonHolder.MarkShared;
begin
  FShared := True;
end;

procedure TTgJsonHolder.Retire(AValue: TJSONAncestor);
begin
  if not Assigned(AValue) then
    Exit;
  if not FShared then
  begin
    // Вложенных DTO нет — на вытесненное значение никто не ссылается.
    AValue.Free;
    Exit;
  end;
  try
    if not Assigned(FRetired) then
      FRetired := TObjectList<TJSONAncestor>.Create(True);
    FRetired.Add(AValue);
  except
    AValue.Free;
    raise;
  end;
end;

{ TTgJsonDto }

constructor TTgJsonDto.Create(AValue: TJSONValue; const AOwner: IInterface);
begin
  inherited Create;
  FValue := AValue;
  if not Assigned(AOwner) then
    FHolder := TTgJsonHolder.Create(AValue)
  // Владелец — держатель (корня или ответа): тот же держатель, общий JSON.
  else if not Supports(AOwner, ITgJsonHolder, FHolder) then
    FHolder := TTgJsonHolder.CreateFor(AOwner);
  // DTO над частью JSON держателя: вытесненные значения больше нельзя освобождать сразу.
  if FValue <> FHolder.Value then
    FHolder.MarkShared;
  if FValue is TJSONObject then
    FJson := TJSONObject(FValue);
end;

constructor TTgJsonDto.CreateNew;
begin
  CreateValue(TJSONObject.Create);
end;

constructor TTgJsonDto.CreateValue(AValue: TJSONValue);
begin
  Create(AValue, nil);
end;

destructor TTgJsonDto.Destroy;
begin
  FJson := nil;
  FValue := nil;
  // Последняя ссылка на держателя освобождает JSON.
  FHolder := nil;
  inherited Destroy;
end;

function TTgJsonDto.JsonOwner: IInterface;
begin
  Result := FHolder;
end;

function TTgJsonDto.Clone: ITgJsonObject;
var
  LCopy: TJSONValue;
begin
  if Assigned(FValue) then
    LCopy := TJSONValue(FValue.Clone)
  else
    LCopy := nil;
  // Виртуальный конструктор: копия того же (сгенерированного) класса.
  Result := TTgJsonDtoClass(ClassType).Create(LCopy, nil);
end;

function TTgJsonDto.RequireJson(const AName: string): TJSONObject;
begin
  if not Assigned(FJson) then
    raise ETgError.Create(TgLangTextFmt(@SRuDtoNotObject, @SEnDtoNotObject, [AName]));
  Result := FJson;
end;

function TTgJsonDto.ValueText: string;
begin
  if FValue is TJSONString then
    Result := FValue.Value
  else
    Result := '';
end;

function TTgJsonDto.ValueArray: TJSONArray;
begin
  if FValue is TJSONArray then
    Result := TJSONArray(FValue)
  else
    Result := nil;
end;

function TTgJsonDto.GetRaw: TJSONObject;
begin
  Result := FJson;
end;

function TTgJsonDto.GetRawValue: TJSONValue;
begin
  Result := FValue;
end;

function TTgJsonDto.AsJson: string;
begin
  Result := TTgJson.ToText(FValue);
end;

procedure TTgJsonDto.SetValue(const AName: string; AValue: TJSONValue);
var
  LJson: TJSONObject;
begin
  try
    LJson := RequireJson(AName);
    // Прежнее значение может читаться вложенными DTO — передаём держателю, не освобождаем.
    FHolder.Retire(LJson.RemovePair(AName));
  except
    AValue.Free;
    raise;
  end;
  if Assigned(AValue) then
    LJson.AddPair(AName, AValue);
end;

procedure TTgJsonDto.SetStr(const AName, AValue: string);
begin
  SetValue(AName, TJSONString.Create(AValue));
end;

procedure TTgJsonDto.SetInt(const AName: string; AValue: Integer);
begin
  SetValue(AName, TJSONNumber.Create(AValue));
end;

procedure TTgJsonDto.SetInt64(const AName: string; AValue: Int64);
begin
  SetValue(AName, TJSONNumber.Create(AValue));
end;

procedure TTgJsonDto.SetDouble(const AName: string; AValue: Double);
begin
  SetValue(AName, TTgJson.FloatNumber(AValue, AName));
end;

procedure TTgJsonDto.SetBool(const AName: string; AValue: Boolean);
begin
  SetValue(AName, TJSONBool.Create(AValue));
end;

procedure TTgJsonDto.SetChatId(const AName: string; const AValue: TTgChatId);
begin
  if AValue.IsEmpty then
    SetValue(AName, nil)
  else
    SetValue(AName, AValue.ToJson);
end;

procedure TTgJsonDto.SetFile(const AName: string; const AValue: TTgInputFile);
begin
  if AValue.IsEmpty then
    SetValue(AName, nil)
  else if AValue.IsUpload then
    raise ETgError.Create(TgLangTextFmt(@SRuDtoFileUpload, @SEnDtoFileUpload, [AName]))
  else
    SetValue(AName, TJSONString.Create(AValue.ToParamValue));
end;

procedure TTgJsonDto.SetObject(const AName: string; const AValue: IInterface);
begin
  SetValue(AName, TTgDto.Serialize(AValue, nil));
end;

procedure TTgJsonDto.SetObjects(const AName: string; const AValues: TArray<IInterface>);
begin
  SetValue(AName, TTgDto.SerializeArray(AValues, nil, AName));
end;

procedure TTgJsonDto.SetObjects2(const AName: string; const AValues: TArray<TArray<IInterface>>);
begin
  SetValue(AName, TTgDto.SerializeArray2(AValues, nil, AName));
end;

procedure TTgJsonDto.AppendRow(const AName: string; const ARow: TArray<IInterface>);
var
  LArray: TJSONArray;
begin
  LArray := TTgJson.GetArr(RequireJson(AName), AName);
  if not Assigned(LArray) then
  begin
    LArray := TJSONArray.Create;
    SetValue(AName, LArray);
  end;
  LArray.AddElement(TTgDto.SerializeArray(ARow, nil, AName));
end;

procedure TTgJsonDto.SetStrings(const AName: string; const AValues: TArray<string>);
begin
  SetValue(AName, TTgDto.StringsJson(AValues));
end;

procedure TTgJsonDto.SetIntegers(const AName: string; const AValues: TArray<Integer>);
begin
  SetValue(AName, TTgDto.IntegersJson(AValues));
end;

procedure TTgJsonDto.SetInt64s(const AName: string; const AValues: TArray<Int64>);
begin
  SetValue(AName, TTgDto.Int64sJson(AValues));
end;

procedure TTgJsonDto.SetDoubles(const AName: string; const AValues: TArray<Double>);
begin
  SetValue(AName, TTgDto.DoublesJson(AValues, AName));
end;

procedure TTgJsonDto.SetBooleans(const AName: string; const AValues: TArray<Boolean>);
begin
  SetValue(AName, TTgDto.BooleansJson(AValues));
end;

{ TTgOutObject }

constructor TTgOutObject.CreateNew;
begin
  inherited Create;
  FJson := TJSONObject.Create;
  FParts := TList<TPart>.Create;
end;

destructor TTgOutObject.Destroy;
begin
  FParts.Free;
  FJson.Free;
  inherited Destroy;
end;

function TTgOutObject.IndexOfPart(const AName: string): Integer;
var
  I: Integer;
begin
  for I := 0 to FParts.Count - 1 do
    if SameStr(FParts[I].Name, AName) then
      Exit(I);
  Result := -1;
end;

procedure TTgOutObject.RemoveField(const AName: string);
var
  LIndex: Integer;
begin
  FJson.RemovePair(AName).Free;
  LIndex := IndexOfPart(AName);
  if LIndex >= 0 then
    FParts.Delete(LIndex);
end;

procedure TTgOutObject.SetJsonValue(const AName: string; AValue: TJSONValue);
begin
  try
    RemoveField(AName);
  except
    AValue.Free;
    raise;
  end;
  if Assigned(AValue) then
    FJson.AddPair(AName, AValue);
end;

procedure TTgOutObject.AddPart(const APart: TPart);
begin
  RemoveField(APart.Name);
  FParts.Add(APart);
end;

procedure TTgOutObject.SetStr(const AName, AValue: string);
begin
  SetJsonValue(AName, TJSONString.Create(AValue));
end;

procedure TTgOutObject.SetInt(const AName: string; AValue: Integer);
begin
  SetJsonValue(AName, TJSONNumber.Create(AValue));
end;

procedure TTgOutObject.SetInt64(const AName: string; AValue: Int64);
begin
  SetJsonValue(AName, TJSONNumber.Create(AValue));
end;

procedure TTgOutObject.SetDouble(const AName: string; AValue: Double);
begin
  SetJsonValue(AName, TTgJson.FloatNumber(AValue, AName));
end;

procedure TTgOutObject.SetBool(const AName: string; AValue: Boolean);
begin
  SetJsonValue(AName, TJSONBool.Create(AValue));
end;

procedure TTgOutObject.SetChatId(const AName: string; const AValue: TTgChatId);
begin
  if AValue.IsEmpty then
    RemoveField(AName)
  else
    SetJsonValue(AName, AValue.ToJson);
end;

procedure TTgOutObject.SetFile(const AName: string; const AValue: TTgInputFile);
var
  LPart: TPart;
begin
  if AValue.IsEmpty then
  begin
    RemoveField(AName);
    Exit;
  end;
  LPart := Default(TPart);
  LPart.Name := AName;
  LPart.Kind := TPartKind.InputFile;
  LPart.FileValue := AValue;
  AddPart(LPart);
end;

procedure TTgOutObject.SetObject(const AName: string; const AValue: IInterface);
var
  LPart: TPart;
begin
  if not Assigned(AValue) then
  begin
    RemoveField(AName);
    Exit;
  end;
  LPart := Default(TPart);
  LPart.Name := AName;
  LPart.Kind := TPartKind.Obj;
  LPart.Obj := AValue;
  AddPart(LPart);
end;

procedure TTgOutObject.SetObjects(const AName: string; const AValues: TArray<IInterface>);
var
  LPart: TPart;
begin
  LPart := Default(TPart);
  LPart.Name := AName;
  LPart.Kind := TPartKind.Objs;
  LPart.Objs := AValues;
  AddPart(LPart);
end;

procedure TTgOutObject.SetObjects2(const AName: string; const AValues: TArray<TArray<IInterface>>);
var
  LPart: TPart;
begin
  LPart := Default(TPart);
  LPart.Name := AName;
  LPart.Kind := TPartKind.Objs2;
  LPart.Objs2 := AValues;
  AddPart(LPart);
end;

procedure TTgOutObject.AppendRow(const AName: string; const ARow: TArray<IInterface>);
var
  LIndex: Integer;
  LPart: TPart;
begin
  LIndex := IndexOfPart(AName);
  if (LIndex >= 0) and (FParts[LIndex].Kind = TPartKind.Objs2) then
  begin
    LPart := FParts[LIndex];
    LPart.Objs2 := LPart.Objs2 + [ARow];
    FParts[LIndex] := LPart;
  end
  else
    SetObjects2(AName, [ARow]);
end;

procedure TTgOutObject.SetStrings(const AName: string; const AValues: TArray<string>);
begin
  SetJsonValue(AName, TTgDto.StringsJson(AValues));
end;

procedure TTgOutObject.SetIntegers(const AName: string; const AValues: TArray<Integer>);
begin
  SetJsonValue(AName, TTgDto.IntegersJson(AValues));
end;

procedure TTgOutObject.SetInt64s(const AName: string; const AValues: TArray<Int64>);
begin
  SetJsonValue(AName, TTgDto.Int64sJson(AValues));
end;

procedure TTgOutObject.SetDoubles(const AName: string; const AValues: TArray<Double>);
begin
  SetJsonValue(AName, TTgDto.DoublesJson(AValues, AName));
end;

procedure TTgOutObject.SetBooleans(const AName: string; const AValues: TArray<Boolean>);
begin
  SetJsonValue(AName, TTgDto.BooleansJson(AValues));
end;

function TTgOutObject.Serialize(AParams: TTgParams): TJSONObject;
var
  LPart: TPart;
  LValue: TJSONValue;
begin
  Result := TJSONObject(FJson.Clone);
  try
    for LPart in FParts do
    begin
      case LPart.Kind of
        TPartKind.InputFile:
          if Assigned(AParams) then
            LValue := TJSONString.Create(AParams.AddAttachment(LPart.FileValue))
          else if LPart.FileValue.IsUpload then
            raise ETgError.Create(TgLangTextFmt(@SRuDtoFileUpload, @SEnDtoFileUpload,
              [LPart.Name]))
          else
            LValue := TJSONString.Create(LPart.FileValue.ToParamValue);
        TPartKind.Obj:
          LValue := TTgDto.Serialize(LPart.Obj, AParams);
        TPartKind.Objs:
          LValue := TTgDto.SerializeArray(LPart.Objs, AParams, LPart.Name);
      else
        LValue := TTgDto.SerializeArray2(LPart.Objs2, AParams, LPart.Name);
      end;
      if Assigned(LValue) then
        Result.AddPair(LPart.Name, LValue);
    end;
  except
    Result.Free;
    raise;
  end;
end;

{ TTgDto }

class function TTgDto.UnexpectedResult(AValue: TJSONValue; const AMethod: string): ETgError;
begin
  AValue.Free;
  Result := ETgError.Create(TgTextFmt(TTgText.UnexpectedResult, [AMethod]));
end;

class function TTgDto.Objects<T>(AArray: TJSONArray; const AOwner: IInterface;
  const AFactory: TTgDtoFactory<T>): TArray<T>;
var
  I: Integer;
begin
  Result := nil;
  if not Assigned(AArray) then
    Exit;
  SetLength(Result, AArray.Count);
  for I := 0 to AArray.Count - 1 do
    Result[I] := AFactory(AArray.Items[I], AOwner);
end;

class function TTgDto.Objects2<T>(AArray: TJSONArray; const AOwner: IInterface;
  const AFactory: TTgDtoFactory<T>): TArray<TArray<T>>;
var
  I: Integer;
  LItem: TJSONValue;
begin
  Result := nil;
  if not Assigned(AArray) then
    Exit;
  SetLength(Result, AArray.Count);
  for I := 0 to AArray.Count - 1 do
  begin
    LItem := AArray.Items[I];
    if LItem is TJSONArray then
      Result[I] := Objects<T>(TJSONArray(LItem), AOwner, AFactory);
  end;
end;

class function TTgDto.Strings(AArray: TJSONArray): TArray<string>;
var
  I: Integer;
begin
  Result := nil;
  if not Assigned(AArray) then
    Exit;
  SetLength(Result, AArray.Count);
  for I := 0 to AArray.Count - 1 do
    Result[I] := TTgJson.ScalarText(AArray.Items[I]);
end;

class function TTgDto.Integers(AArray: TJSONArray; const AName: string): TArray<Integer>;
var
  I: Integer;
begin
  Result := nil;
  if not Assigned(AArray) then
    Exit;
  SetLength(Result, AArray.Count);
  for I := 0 to AArray.Count - 1 do
    Result[I] := TTgJson.ToInt(AArray.Items[I], AName);
end;

class function TTgDto.Int64s(AArray: TJSONArray; const AName: string): TArray<Int64>;
var
  I: Integer;
begin
  Result := nil;
  if not Assigned(AArray) then
    Exit;
  SetLength(Result, AArray.Count);
  for I := 0 to AArray.Count - 1 do
    Result[I] := TTgJson.ToInt64(AArray.Items[I], AName);
end;

class function TTgDto.Doubles(AArray: TJSONArray; const AName: string): TArray<Double>;
var
  I: Integer;
begin
  Result := nil;
  if not Assigned(AArray) then
    Exit;
  SetLength(Result, AArray.Count);
  for I := 0 to AArray.Count - 1 do
    Result[I] := TTgJson.ToDouble(AArray.Items[I], AName);
end;

class function TTgDto.Booleans(AArray: TJSONArray): TArray<Boolean>;
var
  I: Integer;
begin
  Result := nil;
  if not Assigned(AArray) then
    Exit;
  SetLength(Result, AArray.Count);
  for I := 0 to AArray.Count - 1 do
    // Парсер создаёт TJSONBool (TJSONTrue — лишь его потомок).
    Result[I] := (AArray.Items[I] is TJSONBool) and TJSONBool(AArray.Items[I]).AsBoolean;
end;

class function TTgDto.GetChatId(AObj: TJSONObject; const AName: string): TTgChatId;
var
  LValue: TJSONValue;
begin
  Result := Default(TTgChatId);
  LValue := TTgJson.GetValue(AObj, AName);
  if LValue is TJSONNumber then
    Result := TTgChatId.FromId(TTgJson.ToInt64(LValue, AName))
  else if (LValue is TJSONString) and (LValue.Value <> '') then
    Result := LValue.Value;
end;

class function TTgDto.IndexOfValue(AObj: TJSONObject; const AField: string;
  const AValues: array of string): Integer;
var
  LValue: string;
  I: Integer;
begin
  LValue := TTgJson.GetStr(AObj, AField);
  for I := 0 to High(AValues) do
    if SameStr(AValues[I], LValue) then
      Exit(I);
  Result := -1;
end;

class function TTgDto.ToIntf<T>(const AValues: array of T): TArray<IInterface>;
var
  I: Integer;
begin
  SetLength(Result, Length(AValues));
  for I := 0 to High(AValues) do
    Result[I] := AValues[I];
end;

class function TTgDto.ToIntf2<T>(const AValues: array of TArray<T>): TArray<TArray<IInterface>>;
var
  I: Integer;
begin
  SetLength(Result, Length(AValues));
  for I := 0 to High(AValues) do
    Result[I] := ToIntf<T>(AValues[I]);
end;

class function TTgDto.CopyArray<T>(const AValues: array of T): TArray<T>;
var
  I: Integer;
begin
  SetLength(Result, Length(AValues));
  for I := 0 to High(AValues) do
    Result[I] := AValues[I];
end;

class function TTgDto.Serialize(const AValue: IInterface; AParams: TTgParams): TJSONValue;
var
  LOut: ITgOutObject;
  LJson: ITgJsonObject;
begin
  if not Assigned(AValue) then
    Exit(nil);
  if Supports(AValue, ITgOutObject, LOut) then
    Exit(LOut.Serialize(AParams));
  if Supports(AValue, ITgJsonObject, LJson) then
  begin
    if Assigned(LJson.RawValue) then
      Exit(TJSONValue(LJson.RawValue.Clone));
    Exit(TJSONNull.Create);
  end;
  raise ETgError.Create(TgLangTextFmt(@SRuDtoUnsupported, @SEnDtoUnsupported,
    [IntfClassName(AValue)]));
end;

class function TTgDto.SerializeArray(const AValues: TArray<IInterface>;
  AParams: TTgParams; const AName: string): TJSONArray;
var
  I: Integer;
begin
  Result := TJSONArray.Create;
  try
    for I := 0 to High(AValues) do
    begin
      // null в массиве Bot API недопустим: пустой элемент — ошибка в точке вызова.
      if not Assigned(AValues[I]) then
        raise ETgError.Create(TgLangTextFmt(@SRuDtoEmptyItem, @SEnDtoEmptyItem, [I, AName]));
      Result.AddElement(Serialize(AValues[I], AParams));
    end;
  except
    Result.Free;
    raise;
  end;
end;

class function TTgDto.SerializeArray2(const AValues: TArray<TArray<IInterface>>;
  AParams: TTgParams; const AName: string): TJSONArray;
var
  LRow: TArray<IInterface>;
begin
  Result := TJSONArray.Create;
  try
    for LRow in AValues do
      Result.AddElement(SerializeArray(LRow, AParams, AName));
  except
    Result.Free;
    raise;
  end;
end;

class function TTgDto.StringsJson(const AValues: TArray<string>): TJSONArray;
var
  LValue: string;
begin
  Result := TJSONArray.Create;
  for LValue in AValues do
    Result.Add(LValue);
end;

class function TTgDto.IntegersJson(const AValues: TArray<Integer>): TJSONArray;
var
  LValue: Integer;
begin
  Result := TJSONArray.Create;
  for LValue in AValues do
    Result.Add(LValue);
end;

class function TTgDto.Int64sJson(const AValues: TArray<Int64>): TJSONArray;
var
  LValue: Int64;
begin
  Result := TJSONArray.Create;
  for LValue in AValues do
    Result.AddElement(TJSONNumber.Create(LValue));
end;

class function TTgDto.DoublesJson(const AValues: TArray<Double>; const AName: string): TJSONArray;
var
  LValue: Double;
begin
  Result := TJSONArray.Create;
  try
    for LValue in AValues do
      Result.AddElement(TTgJson.FloatNumber(LValue, AName));
  except
    Result.Free;
    raise;
  end;
end;

class function TTgDto.BooleansJson(const AValues: TArray<Boolean>): TJSONArray;
var
  LValue: Boolean;
begin
  Result := TJSONArray.Create;
  for LValue in AValues do
    Result.Add(LValue);
end;

class procedure TTgDto.DetachTo(const AValue: IInterface; ATypeInfo: Pointer; out AResult);
var
  LJson: ITgJsonObject;
begin
  IInterface(AResult) := nil;
  if not Assigned(AValue) then
    Exit;
  // Копия того же класса реализует тот же интерфейс.
  if not Supports(AValue, ITgJsonObject, LJson) or
    not Supports(LJson.Clone, GetTypeData(PTypeInfo(ATypeInfo))^.Guid, AResult) then
    raise ETgError.Create(TgLangTextFmt(@SRuDtoNotJsonDto, @SEnDtoNotJsonDto,
      [IntfClassName(AValue)]));
end;

class function TTgDto.Detach<T>(const AValue: T): T;
begin
  Result := Default(T);
  DetachTo(AValue, TypeInfo(T), Result);
end;

class function TTgDto.Parse<T>(const AJsonText: string; const AFactory: TTgDtoFactory<T>): T;
var
  LValue: TJSONValue;
  LHolder: IInterface;
begin
  LValue := TTgJson.Parse(AJsonText);
  if not Assigned(LValue) then
    Exit(Default(T));
  // Держатель освобождает JSON, если фабрика его не приняла.
  LHolder := TTgJsonHolder.Create(LValue);
  Result := AFactory(LValue, LHolder);
end;

class function TTgDto.ResultObject<T>(AValue: TJSONValue; const AMethod: string;
  const AFactory: TTgDtoFactory<T>): T;
var
  LHolder: IInterface;
begin
  if not (AValue is TJSONObject) then
    raise UnexpectedResult(AValue, AMethod);
  LHolder := TTgJsonHolder.Create(AValue);
  Result := AFactory(AValue, LHolder);
end;

class function TTgDto.ResultObjectOrTrue<T>(AValue: TJSONValue; const AMethod: string;
  const AFactory: TTgDtoFactory<T>): T;
begin
  if AValue is TJSONBool then
  begin
    AValue.Free;
    Exit(Default(T));
  end;
  Result := ResultObject<T>(AValue, AMethod, AFactory);
end;

class function TTgDto.ResultArray<T>(AValue: TJSONValue; const AMethod: string;
  const AFactory: TTgDtoFactory<T>): TArray<T>;
var
  LHolder: IInterface;
  LArray: TJSONArray;
  I: Integer;
begin
  if not (AValue is TJSONArray) then
    raise UnexpectedResult(AValue, AMethod);
  // Массив целиком принадлежит держателю; элементы ссылаются на его части.
  LHolder := TTgJsonHolder.Create(AValue);
  LArray := TJSONArray(AValue);
  SetLength(Result, LArray.Count);
  for I := 0 to LArray.Count - 1 do
  begin
    if not (LArray.Items[I] is TJSONObject) then
      raise ETgError.Create(TgTextFmt(TTgText.UnexpectedResult, [AMethod]));
    Result[I] := AFactory(LArray.Items[I], LHolder);
  end;
end;

class function TTgDto.ResultBool(AValue: TJSONValue; const AMethod: string): Boolean;
begin
  if not (AValue is TJSONBool) then
    raise UnexpectedResult(AValue, AMethod);
  Result := TJSONBool(AValue).AsBoolean;
  AValue.Free;
end;

class function TTgDto.ResultStr(AValue: TJSONValue; const AMethod: string): string;
begin
  if not (AValue is TJSONString) or (AValue is TJSONNumber) then
    raise UnexpectedResult(AValue, AMethod);
  Result := AValue.Value;
  AValue.Free;
end;

class function TTgDto.ResultInt(AValue: TJSONValue; const AMethod: string): Integer;
begin
  if not (AValue is TJSONNumber) then
    raise UnexpectedResult(AValue, AMethod);
  try
    Result := TTgJson.ToInt(AValue, AMethod);
  finally
    AValue.Free;
  end;
end;

class function TTgDto.ResultInt64(AValue: TJSONValue; const AMethod: string): Int64;
begin
  if not (AValue is TJSONNumber) then
    raise UnexpectedResult(AValue, AMethod);
  try
    Result := TTgJson.ToInt64(AValue, AMethod);
  finally
    AValue.Free;
  end;
end;

class function TTgDto.ResultDouble(AValue: TJSONValue; const AMethod: string): Double;
begin
  if not (AValue is TJSONNumber) then
    raise UnexpectedResult(AValue, AMethod);
  try
    Result := TTgJson.ToDouble(AValue, AMethod);
  finally
    AValue.Free;
  end;
end;

end.
