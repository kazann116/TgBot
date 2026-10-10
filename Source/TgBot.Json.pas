unit TgBot.Json;

{
  TgBot — хелперы JSON поверх System.JSON:
  - TTgJson: безопасное чтение полей (без исключений на отсутствующих полях);
  - TTgParams: построитель параметров запроса Bot API (JSON или multipart).
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.Generics.Collections,
  System.JSON,
  TgBot.Base;

type
  /// <summary>
  ///   Безопасное чтение JSON. Все методы допускают AObj = nil, отсутствующее
  ///   поле и значение null — в этих случаях возвращается значение по умолчанию.
  ///   Политика чисел (единая для полей, массивов и результатов методов):
  ///   значение другого типа — значение по умолчанию; JSON-число, которое не
  ///   является целым или не помещается в тип (Integer/Int64), — ETgError.
  ///   Текст чисел не зависит от локали (FormatSettings).
  /// </summary>
  TTgJson = record
  public
    /// <summary>Значение поля или nil (нет поля, null или AObj = nil).</summary>
    class function GetValue(AObj: TJSONObject; const AName: string): TJSONValue; static;
    /// <summary>Поле присутствует и не равно null.</summary>
    class function Has(AObj: TJSONObject; const AName: string): Boolean; static;
    /// <summary>Строковое поле (для чисел/bool — их JSON-текст).</summary>
    class function GetStr(AObj: TJSONObject; const AName: string;
      const ADefault: string = ''): string; static;
    /// <summary>Целое поле (Integer). Вне диапазона Integer — ETgError.</summary>
    class function GetInt(AObj: TJSONObject; const AName: string;
      ADefault: Integer = 0): Integer; static;
    /// <summary>Целое поле (Int64) — для id пользователей и чатов. Не целое число — ETgError.</summary>
    class function GetInt64(AObj: TJSONObject; const AName: string;
      ADefault: Int64 = 0): Int64; static;
    /// <summary>Логическое поле.</summary>
    class function GetBool(AObj: TJSONObject; const AName: string;
      ADefault: Boolean = False): Boolean; static;
    /// <summary>Вещественное поле (разбор не зависит от локали).</summary>
    class function GetDouble(AObj: TJSONObject; const AName: string;
      ADefault: Double = 0): Double; static;
    /// <summary>
    ///   Текст скалярного значения: строка — как есть, число — JSON-текст
    ///   (независимо от локали), bool — true/false; иначе ''.
    /// </summary>
    class function ScalarText(AValue: TJSONValue): string; static;
    /// <summary>
    ///   Целое Int64 из значения: nil, null и нечисловые значения — ADefault;
    ///   строка из цифр — её значение; JSON-число не целое или вне Int64 —
    ///   ETgError (AName — имя поля для сообщения).
    /// </summary>
    class function ToInt64(AValue: TJSONValue; const AName: string;
      ADefault: Int64 = 0): Int64; static;
    /// <summary>Как ToInt64, плюс ETgError вне диапазона Integer.</summary>
    class function ToInt(AValue: TJSONValue; const AName: string;
      ADefault: Integer = 0): Integer; static;
    /// <summary>
    ///   Вещественное из JSON-числа (инвариантная локаль); прочие значения —
    ///   ADefault; число, не представимое Double, — ETgError.
    /// </summary>
    class function ToDouble(AValue: TJSONValue; const AName: string;
      ADefault: Double = 0): Double; static;
    /// <summary>
    ///   JSON-число из Double независимо от локали. NaN и бесконечность —
    ///   ETgError (AName — имя поля/параметра). Результат освобождает вызывающий.
    /// </summary>
    class function FloatNumber(AValue: Double; const AName: string): TJSONNumber; static;
    /// <summary>Вложенный объект или nil. Владелец — AObj.</summary>
    class function GetObj(AObj: TJSONObject; const AName: string): TJSONObject; static;
    /// <summary>Вложенный массив или nil. Владелец — AObj.</summary>
    class function GetArr(AObj: TJSONObject; const AName: string): TJSONArray; static;
    /// <summary>Разбор текста; при ошибке — nil. Результат освобождает вызывающий.</summary>
    class function Parse(const AText: string): TJSONValue; static;
    /// <summary>Разбор текста в объект; не объект или ошибка — nil.</summary>
    class function ParseObject(const AText: string): TJSONObject; static;
    /// <summary>
    ///   Разбор байтов UTF-8 (например, тела HTTP-ответа); пусто, ошибка
    ///   разбора или некорректный UTF-8 — nil. Результат освобождает вызывающий.
    /// </summary>
    class function ParseUtf8(const ABytes: TBytes): TJSONValue; static;
    /// <summary>Разбор байтов UTF-8 в объект; не объект или ошибка — nil.</summary>
    class function ParseObjectUtf8(const ABytes: TBytes): TJSONObject; static;
    /// <summary>
    ///   Компактный JSON-текст. Символы Unicode не экранируются (\uXXXX),
    ///   текст предназначен для кодирования в UTF-8. nil — 'null'.
    /// </summary>
    class function ToText(AValue: TJSONValue): string; static;
    /// <summary>
    ///   Значение для поля формы (multipart): строки и числа — как есть,
    ///   bool — true/false, объекты и массивы — JSON-текстом.
    /// </summary>
    class function ToFormText(AValue: TJSONValue): string; static;
  end;

  /// <summary>Файл, прикреплённый к запросу как поле multipart.</summary>
  TTgParamFile = record
    /// <summary>Имя поля формы.</summary>
    Name: string;
    /// <summary>Загружаемый файл (IsUpload = True).</summary>
    InputFile: TTgInputFile;
  end;

  /// <summary>
  ///   Параметры вызова метода Bot API. Обычные поля хранятся в JSON-объекте,
  ///   загружаемые файлы — отдельным списком; при их наличии запрос
  ///   отправляется как multipart/form-data (HasFiles). Повторное добавление
  ///   параметра с тем же именем заменяет прежнее значение.
  ///   Методы Add* возвращают Self для цепочек вызовов.
  /// </summary>
  TTgParams = class
  private
    FJson: TJSONObject;
    FFiles: TList<TTgParamFile>;
    FAttachCounter: Integer;
    function GetFileCount: Integer;
    function GetFile(AIndex: Integer): TTgParamFile;
    procedure RemoveJsonPair(const AName: string);
    procedure RemoveFile(const AName: string);
    procedure CheckName(const AName: string);
  public
    constructor Create;
    destructor Destroy; override;
    /// <summary>Строковый параметр (добавляется и пустая строка).</summary>
    function Add(const AName, AValue: string): TTgParams; overload;
    /// <summary>Целый параметр (Integer).</summary>
    function Add(const AName: string; AValue: Integer): TTgParams; overload;
    /// <summary>Целый параметр (Int64) — для id чатов, пользователей, сообщений.</summary>
    function Add(const AName: string; AValue: Int64): TTgParams; overload;
    /// <summary>Логический параметр.</summary>
    function Add(const AName: string; AValue: Boolean): TTgParams; overload;
    /// <summary>Вещественный параметр (не зависит от локали). NaN и бесконечность — ETgError.</summary>
    function Add(const AName: string; AValue: Double): TTgParams; overload;
    /// <summary>Строковый параметр, если AValue не пустая строка.</summary>
    function AddNotEmpty(const AName, AValue: string): TTgParams;
    /// <summary>Опциональные параметры: добавляются, только если HasValue.</summary>
    function AddOptional(const AName: string; const AValue: TTgOptional<string>): TTgParams; overload;
    function AddOptional(const AName: string; const AValue: TTgOptional<Int64>): TTgParams; overload;
    function AddOptional(const AName: string; const AValue: TTgOptional<Boolean>): TTgParams; overload;
    function AddOptional(const AName: string; const AValue: TTgOptional<Double>): TTgParams; overload;
    /// <summary>Идентификатор чата (число или '@username'). Пустой — ETgError.</summary>
    function AddChatId(const AName: string; const AChatId: TTgChatId): TTgParams;
    /// <summary>
    ///   Файл: загрузка уходит в multipart, file_id/URL/file:// — строкой.
    ///   Пустой файл — ETgError.
    /// </summary>
    function AddFile(const AName: string; const AFile: TTgInputFile): TTgParams;
    /// <summary>
    ///   Регистрирует файл для ссылки из JSON (InputMedia и т.п.) и возвращает
    ///   строку для поля media: 'attach://имя' для загрузок либо file_id/URL.
    /// </summary>
    function AddAttachment(const AFile: TTgInputFile): string;
    /// <summary>Вложенное JSON-значение; владение AValue переходит к параметрам. nil — пропуск.</summary>
    function AddJson(const AName: string; AValue: TJSONValue): TTgParams;
    /// <summary>
    ///   Вложенное значение из JSON-текста (например, reply_markup).
    ///   Пустой текст — пропуск, некорректный JSON — ETgError.
    /// </summary>
    function AddJsonText(const AName, AJsonText: string): TTgParams;
    /// <summary>Массив строк (например, allowed_updates). Пустой массив передаётся как [].</summary>
    function AddStrings(const AName: string; const AValues: TArray<string>): TTgParams;
    /// <summary>Массив целых (например, message_ids). Пустой массив передаётся как [].</summary>
    function AddInt64s(const AName: string; const AValues: TArray<Int64>): TTgParams;
    /// <summary>Удаляет параметр (обычный или файл).</summary>
    procedure Remove(const AName: string);
    /// <summary>Параметр задан (обычный или файл).</summary>
    function Contains(const AName: string): Boolean;
    /// <summary>Текст обычного параметра (как для поля формы) или ''.</summary>
    function GetText(const AName: string): string;
    /// <summary>Есть загружаемые файлы — нужен multipart/form-data.</summary>
    function HasFiles: Boolean;
    /// <summary>Тело JSON-запроса (без файлов).</summary>
    function ToJsonText: string;
    /// <summary>Обычные параметры. Владелец — TTgParams.</summary>
    property Json: TJSONObject read FJson;
    /// <summary>Количество загружаемых файлов.</summary>
    property FileCount: Integer read GetFileCount;
    /// <summary>Загружаемые файлы.</summary>
    property Files[AIndex: Integer]: TTgParamFile read GetFile;
  end;

implementation

uses
  System.Math;

type
  TJsonText = (NotInteger, IntegerRange, NotFloat, FloatInvalid);

const
  CJsonTexts: array[TTgLanguage, TJsonText] of string = (
    ('Поле «%s»: значение %s не является целым числом в диапазоне Int64',
     'Поле «%s»: значение %s вне диапазона Integer',
     'Поле «%s»: значение %s не представимо вещественным числом',
     'Параметр «%s»: недопустимое вещественное значение (NaN или бесконечность)'),
    ('Field "%s": value %s is not an integer within the Int64 range',
     'Field "%s": value %s is out of the Integer range',
     'Field "%s": value %s cannot be represented as a floating-point number',
     'Parameter "%s": invalid floating-point value (NaN or infinity)'));

function JsonError(AText: TJsonText; const AName, AValue: string): ETgError;
begin
  if AText = TJsonText.FloatInvalid then
    Result := ETgError.Create(Format(CJsonTexts[TgGetLanguage, AText], [AName]))
  else
    Result := ETgError.Create(Format(CJsonTexts[TgGetLanguage, AText], [AName, AValue]));
end;

{ TTgJson }

class function TTgJson.GetValue(AObj: TJSONObject; const AName: string): TJSONValue;
begin
  Result := nil;
  if not Assigned(AObj) then
    Exit;
  Result := AObj.GetValue(AName);
  if Result is TJSONNull then
    Result := nil;
end;

class function TTgJson.Has(AObj: TJSONObject; const AName: string): Boolean;
begin
  Result := Assigned(GetValue(AObj, AName));
end;

class function TTgJson.GetStr(AObj: TJSONObject; const AName,
  ADefault: string): string;
var
  LValue: TJSONValue;
begin
  LValue := GetValue(AObj, AName);
  if (LValue is TJSONString) or (LValue is TJSONBool) then
    Result := ScalarText(LValue)
  else
    Result := ADefault;
end;

class function TTgJson.GetInt(AObj: TJSONObject; const AName: string;
  ADefault: Integer): Integer;
begin
  Result := ToInt(GetValue(AObj, AName), AName, ADefault);
end;

class function TTgJson.GetInt64(AObj: TJSONObject; const AName: string;
  ADefault: Int64): Int64;
begin
  Result := ToInt64(GetValue(AObj, AName), AName, ADefault);
end;

class function TTgJson.ScalarText(AValue: TJSONValue): string;
begin
  // TJSONNumber — наследник TJSONString, но его Value в 10.4 форматирует
  // число по локали (FloatToStr); JSON-текст числа берётся из ToJSON.
  if AValue is TJSONNumber then
    Result := AValue.ToJSON
  else if (AValue is TJSONString) or (AValue is TJSONBool) then
    Result := AValue.Value
  else
    Result := '';
end;

class function TTgJson.ToInt64(AValue: TJSONValue; const AName: string;
  ADefault: Int64): Int64;
var
  LText: string;
begin
  if AValue is TJSONNumber then
  begin
    LText := AValue.ToJSON;
    if not TryStrToInt64(LText, Result) then
      raise JsonError(TJsonText.NotInteger, AName, LText);
  end
  else if not ((AValue is TJSONString) and TryStrToInt64(AValue.Value, Result)) then
    Result := ADefault;
end;

class function TTgJson.ToInt(AValue: TJSONValue; const AName: string;
  ADefault: Integer): Integer;
var
  LValue: Int64;
begin
  LValue := ToInt64(AValue, AName, ADefault);
  if (LValue < Low(Integer)) or (LValue > High(Integer)) then
    raise JsonError(TJsonText.IntegerRange, AName, IntToStr(LValue));
  Result := Integer(LValue);
end;

class function TTgJson.ToDouble(AValue: TJSONValue; const AName: string;
  ADefault: Double): Double;
var
  LText: string;
begin
  if not (AValue is TJSONNumber) then
    Exit(ADefault);
  LText := AValue.ToJSON;
  if not TryStrToFloat(LText, Result, TFormatSettings.Invariant) or IsNan(Result) or
    IsInfinite(Result) then
    raise JsonError(TJsonText.NotFloat, AName, LText);
end;

class function TTgJson.FloatNumber(AValue: Double; const AName: string): TJSONNumber;
var
  LText: string;
  LBack: Double;
begin
  if IsNan(AValue) or IsInfinite(AValue) then
    raise JsonError(TJsonText.FloatInvalid, AName, '');
  // Кратчайшая запись (15 знаков), если она восстанавливает значение точно,
  // иначе 17 знаков. Инвариантная локаль: разделитель всегда '.'.
  LText := FloatToStrF(AValue, ffGeneral, 15, 0, TFormatSettings.Invariant);
  if not TryStrToFloat(LText, LBack, TFormatSettings.Invariant) or (LBack <> AValue) then
    LText := FloatToStrF(AValue, ffGeneral, 17, 0, TFormatSettings.Invariant);
  Result := TJSONNumber.Create(LText);
end;

class function TTgJson.GetBool(AObj: TJSONObject; const AName: string;
  ADefault: Boolean): Boolean;
var
  LValue: TJSONValue;
begin
  LValue := GetValue(AObj, AName);
  if LValue is TJSONBool then
    Result := TJSONBool(LValue).AsBoolean
  else
    Result := ADefault;
end;

class function TTgJson.GetDouble(AObj: TJSONObject; const AName: string;
  ADefault: Double): Double;
begin
  Result := ToDouble(GetValue(AObj, AName), AName, ADefault);
end;

class function TTgJson.GetObj(AObj: TJSONObject; const AName: string): TJSONObject;
var
  LValue: TJSONValue;
begin
  LValue := GetValue(AObj, AName);
  if LValue is TJSONObject then
    Result := TJSONObject(LValue)
  else
    Result := nil;
end;

class function TTgJson.GetArr(AObj: TJSONObject; const AName: string): TJSONArray;
var
  LValue: TJSONValue;
begin
  LValue := GetValue(AObj, AName);
  if LValue is TJSONArray then
    Result := TJSONArray(LValue)
  else
    Result := nil;
end;

class function TTgJson.Parse(const AText: string): TJSONValue;
begin
  if AText = '' then
    Exit(nil);
  // UseBool = True: логические значения — TJSONBool; RaiseExc = False: ошибка -> nil.
  Result := TJSONObject.ParseJSONValue(AText, True, False);
end;

class function TTgJson.ParseObject(const AText: string): TJSONObject;
var
  LValue: TJSONValue;
begin
  LValue := Parse(AText);
  if LValue is TJSONObject then
    Result := TJSONObject(LValue)
  else
  begin
    LValue.Free;
    Result := nil;
  end;
end;

class function TTgJson.ParseUtf8(const ABytes: TBytes): TJSONValue;
begin
  if Length(ABytes) = 0 then
    Exit(nil);
  // Без RaiseExc ошибка разбора (в т.ч. некорректный UTF-8) даёт nil, а не исключение.
  // TJSONParseOption объявлен в TJSONObject (10.4) или в его предке TJSONValue (12):
  // обращение через TJSONObject компилируется в обеих версиях.
  Result := TJSONObject.ParseJSONValue(ABytes, 0,
    [TJSONObject.TJSONParseOption.IsUTF8, TJSONObject.TJSONParseOption.UseBool]);
end;

class function TTgJson.ParseObjectUtf8(const ABytes: TBytes): TJSONObject;
var
  LValue: TJSONValue;
begin
  LValue := ParseUtf8(ABytes);
  if LValue is TJSONObject then
    Result := TJSONObject(LValue)
  else
  begin
    LValue.Free;
    Result := nil;
  end;
end;

class function TTgJson.ToText(AValue: TJSONValue): string;
begin
  if not Assigned(AValue) then
    Exit('null');
  Result := AValue.ToJSON([TJSONAncestor.TJSONOutputOption.EncodeBelow32]);
end;

class function TTgJson.ToFormText(AValue: TJSONValue): string;
begin
  if not Assigned(AValue) or (AValue is TJSONNull) then
    Result := ''
  else if (AValue is TJSONString) or (AValue is TJSONBool) then
    Result := ScalarText(AValue)
  else
    Result := ToText(AValue);
end;

{ TTgParams }

constructor TTgParams.Create;
begin
  inherited Create;
  FJson := TJSONObject.Create;
  FFiles := TList<TTgParamFile>.Create;
end;

destructor TTgParams.Destroy;
begin
  FreeAndNil(FFiles);
  FreeAndNil(FJson);
  inherited Destroy;
end;

procedure TTgParams.CheckName(const AName: string);
begin
  if AName = '' then
    raise ETgError.Create(TgText(TTgText.ParamNameEmpty));
end;

procedure TTgParams.RemoveJsonPair(const AName: string);
begin
  // RemovePair возвращает пару, освобождать её должен вызывающий.
  FJson.RemovePair(AName).Free;
end;

procedure TTgParams.RemoveFile(const AName: string);
var
  I: Integer;
begin
  for I := FFiles.Count - 1 downto 0 do
    if FFiles[I].Name = AName then
      FFiles.Delete(I);
end;

function TTgParams.AddJson(const AName: string; AValue: TJSONValue): TTgParams;
begin
  Result := Self;
  if not Assigned(AValue) then
    Exit;
  try
    CheckName(AName);
    Remove(AName);
  except
    AValue.Free;
    raise;
  end;
  FJson.AddPair(AName, AValue);
end;

function TTgParams.Add(const AName, AValue: string): TTgParams;
begin
  Result := AddJson(AName, TJSONString.Create(AValue));
end;

function TTgParams.Add(const AName: string; AValue: Integer): TTgParams;
begin
  Result := AddJson(AName, TJSONNumber.Create(AValue));
end;

function TTgParams.Add(const AName: string; AValue: Int64): TTgParams;
begin
  Result := AddJson(AName, TJSONNumber.Create(AValue));
end;

function TTgParams.Add(const AName: string; AValue: Boolean): TTgParams;
begin
  Result := AddJson(AName, TJSONBool.Create(AValue));
end;

function TTgParams.Add(const AName: string; AValue: Double): TTgParams;
begin
  Result := AddJson(AName, TTgJson.FloatNumber(AValue, AName));
end;

function TTgParams.AddNotEmpty(const AName, AValue: string): TTgParams;
begin
  Result := Self;
  if AValue <> '' then
    Add(AName, AValue);
end;

function TTgParams.AddOptional(const AName: string;
  const AValue: TTgOptional<string>): TTgParams;
begin
  Result := Self;
  if AValue.HasValue then
    Add(AName, AValue.Value);
end;

function TTgParams.AddOptional(const AName: string;
  const AValue: TTgOptional<Int64>): TTgParams;
begin
  Result := Self;
  if AValue.HasValue then
    Add(AName, AValue.Value);
end;

function TTgParams.AddOptional(const AName: string;
  const AValue: TTgOptional<Boolean>): TTgParams;
begin
  Result := Self;
  if AValue.HasValue then
    Add(AName, AValue.Value);
end;

function TTgParams.AddOptional(const AName: string;
  const AValue: TTgOptional<Double>): TTgParams;
begin
  Result := Self;
  if AValue.HasValue then
    Add(AName, AValue.Value);
end;

function TTgParams.AddChatId(const AName: string;
  const AChatId: TTgChatId): TTgParams;
begin
  Result := AddJson(AName, AChatId.ToJson);
end;

function TTgParams.AddFile(const AName: string;
  const AFile: TTgInputFile): TTgParams;
var
  LFile: TTgParamFile;
begin
  Result := Self;
  CheckName(AName);
  if AFile.IsEmpty then
    raise ETgError.Create(TgText(TTgText.InputFileEmpty));
  if not AFile.IsUpload then
  begin
    Add(AName, AFile.ToParamValue);
    Exit;
  end;
  Remove(AName);
  LFile.Name := AName;
  LFile.InputFile := AFile;
  FFiles.Add(LFile);
end;

function TTgParams.AddAttachment(const AFile: TTgInputFile): string;
var
  LName: string;
begin
  if AFile.IsEmpty then
    raise ETgError.Create(TgText(TTgText.InputFileEmpty));
  if not AFile.IsUpload then
    Exit(AFile.ToParamValue);
  repeat
    Inc(FAttachCounter);
    LName := 'tgfile' + IntToStr(FAttachCounter);
  until not Contains(LName);
  AddFile(LName, AFile);
  Result := 'attach://' + LName;
end;

function TTgParams.AddJsonText(const AName, AJsonText: string): TTgParams;
var
  LValue: TJSONValue;
begin
  Result := Self;
  if Trim(AJsonText) = '' then
    Exit;
  LValue := TTgJson.Parse(AJsonText);
  if not Assigned(LValue) then
    raise ETgError.Create(TgTextFmt(TTgText.InvalidJson, [AName]));
  AddJson(AName, LValue);
end;

function TTgParams.AddStrings(const AName: string;
  const AValues: TArray<string>): TTgParams;
var
  LArray: TJSONArray;
  LValue: string;
begin
  LArray := TJSONArray.Create;
  try
    for LValue in AValues do
      LArray.Add(LValue);
  except
    LArray.Free;
    raise;
  end;
  Result := AddJson(AName, LArray);
end;

function TTgParams.AddInt64s(const AName: string;
  const AValues: TArray<Int64>): TTgParams;
var
  LArray: TJSONArray;
  LValue: Int64;
begin
  LArray := TJSONArray.Create;
  try
    for LValue in AValues do
      LArray.AddElement(TJSONNumber.Create(LValue));
  except
    LArray.Free;
    raise;
  end;
  Result := AddJson(AName, LArray);
end;

procedure TTgParams.Remove(const AName: string);
begin
  RemoveJsonPair(AName);
  RemoveFile(AName);
end;

function TTgParams.Contains(const AName: string): Boolean;
var
  I: Integer;
begin
  Result := Assigned(FJson.GetValue(AName));
  if Result then
    Exit;
  for I := 0 to FFiles.Count - 1 do
    if FFiles[I].Name = AName then
      Exit(True);
end;

function TTgParams.GetText(const AName: string): string;
begin
  Result := TTgJson.ToFormText(FJson.GetValue(AName));
end;

function TTgParams.HasFiles: Boolean;
begin
  Result := FFiles.Count > 0;
end;

function TTgParams.ToJsonText: string;
begin
  Result := TTgJson.ToText(FJson);
end;

function TTgParams.GetFileCount: Integer;
begin
  Result := FFiles.Count;
end;

function TTgParams.GetFile(AIndex: Integer): TTgParamFile;
begin
  Result := FFiles[AIndex];
end;

end.
