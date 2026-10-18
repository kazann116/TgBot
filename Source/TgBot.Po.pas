unit TgBot.Po;

{
  TgBot — загрузчик переводов gettext (.po) для сообщений библиотеки.

  TgLoadPoTranslator (файл) и TgLoadPoTranslatorFromStream (поток — например,
  TResourceStream или asset на Android) читают .po и возвращают
  ITgPoTranslator — переводчик для TgSetTranslator (TgBot.Base). Ключ
  перевода (msgid) — английский текст сообщения библиотеки до подстановки
  аргументов (см. ITgTranslator):

    TgSetTranslator(TgLoadPoTranslator(TPath.Combine(LDir, 'de.po')));
    …
    TgSetTranslator(nil); // до завершения программы

  Модуль подключается по желанию: фасад TgBot его не реэкспортирует.

  Разбор .po:
  - кодировка UTF-8 (BOM необязателен; недопустимые байты UTF-8 — ошибка),
    переводы строк CRLF, LF или CR;
  - заголовок (msgid "" без msgctxt): charset в Content-Type, отличная от
    UTF-8 (допустимы UTF-8, UTF8, ASCII, US-ASCII), — ошибка; Language: —
    свойство Language; заголовок разбирается и с флагом fuzzy;
  - комментарии #…; флаг fuzzy (#, fuzzy) — запись пропускается;
    устаревшие записи (#~) пропускаются;
  - msgctxt разбирается, но записи с контекстом пропускаются (у библиотеки
    контекста нет); непустой перевод такой записи — с предупреждением;
  - строки "…" подряд (и на одной строке, через пробел) склеиваются;
    escape-последовательности C: \\ \" \' \? \n \t \r \a \b \f \v,
    восьмеричные \ooo (1–3 цифры) и \xHH… — только для символов ASCII
    1–127 (байты других кодировок не поддерживаются); иное — ошибка;
  - msgid_plural и msgstr[n] разбираются (пробелы вокруг '[', номера и ']'
    допустимы: msgstr [0]), перевод — msgstr[0];
  - пустой перевод — записи нет (не переведено);
  - знак процента. msgid с '%' — строка формата Format (все сообщения
    библиотеки с аргументами содержат спецификаторы): перевод, аргументы
    Format которого не совпадают с msgid (TgSameFormatSignature),
    отбрасывается с предупреждением; литерал процента в таком переводе —
    '%%', одиночный '%' — несовпадение. msgid без '%' — простой текст:
    библиотека отдаёт его перевод как есть, без Format (TgLangText), поэтому
    '%' в переводе — литерал («100% готово»), а '%%' выводится как два
    знака; отбрасывается (с предупреждением) только перевод с корректными
    спецификаторами Format (%s, %d…) — аргументов для них нет;
  - повтор msgid среди принятых записей — действует последняя, с
    предупреждением;
  - синтаксическая ошибка (строка в кавычках вне записи, незакрытая
    кавычка, лишний текст, неизвестное ключевое слово, запись без msgstr) —
    ETgPoError с именем источника и номером строки.
  Разбор линейный, без регулярных выражений. Тексты ошибок и предупреждений
  — на языке библиотеки (TgSetLanguage) в момент загрузки.

  Известные отличия от GNU gettext (msgfmt):
  - ключевое слово (msgctxt, msgid, msgid_plural, msgstr) и первая строка
    "…" должны быть на одной строке файла: «msgid» и «"текст"» на разных
    строках — ETgPoError (GNU допускает перенос между лексемами);
  - escape \ooo и \x — только символы ASCII (GNU вставляет байт);
  - кодировка только UTF-8 (и ASCII);
  - записи с msgctxt не используются;
  - формы множественного числа не выбираются: перевод — всегда msgstr[0].

  Переводчик неизменяем после загрузки: TryTranslate только читает словарь
  и безопасен из любых потоков.

  Модуль использует только RTL и компилируется под Win32, Win64, Linux64,
  Android/Android64.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.Classes,
  System.Generics.Collections,
  TgBot.Base;

type
  /// <summary>
  ///   Ошибка разбора .po: текст — «место (имя источника, строка): описание».
  /// </summary>
  ETgPoError = class(ETgError)
  private
    FFileName: string;
    FLineNumber: Integer;
  public
    /// <summary>
    ///   Создаёт исключение с локализованным текстом; ADetail — описание
    ///   ошибки, AFileName — имя файла или источника ('' — поток без имени),
    ///   ALineNumber — номер строки (с 1).
    /// </summary>
    constructor Create(const ADetail, AFileName: string; ALineNumber: Integer);
    /// <summary>Имя файла или источника; '' — поток без имени.</summary>
    property FileName: string read FFileName;
    /// <summary>Номер строки с ошибкой (с 1).</summary>
    property LineNumber: Integer read FLineNumber;
  end;

  /// <summary>
  ///   Переводчик из .po (TgLoadPoTranslator, TgLoadPoTranslatorFromStream).
  ///   Неизменяем после загрузки, все методы потокобезопасны.
  /// </summary>
  ITgPoTranslator = interface(ITgTranslator)
    ['{C5FDBAEC-278F-4FC9-AE81-FCAE7B4BF947}']
    function GetCount: Integer;
    function GetWarnings: TArray<string>;
    function GetLanguage: string;
    /// <summary>Число загруженных переводов.</summary>
    property Count: Integer read GetCount;
    /// <summary>
    ///   Предупреждения загрузки («место: описание»): запись с msgctxt и
    ///   непустым переводом пропущена; перевод, спецификаторы Format которого
    ///   не совпадают с msgid, отброшен; повтор msgid — действует последняя
    ///   запись. Неточные (fuzzy), непереведённые (пустой msgstr) и
    ///   устаревшие (#~) записи пропускаются молча, без предупреждения.
    ///   Каждый вызов возвращает новую копию массива.
    /// </summary>
    property Warnings: TArray<string> read GetWarnings;
    /// <summary>Значение Language: заголовка .po; '' — не задано.</summary>
    property Language: string read GetLanguage;
  end;

  /// <summary>
  ///   Реализация ITgPoTranslator: словарь «msgid → перевод», заполняется в
  ///   конструкторе и дальше только читается. Используйте через интерфейс
  ///   (ITgPoTranslator или ITgTranslator), а не как объект.
  /// </summary>
  TTgPoTranslator = class(TInterfacedObject, ITgTranslator, ITgPoTranslator)
  private
    FMap: TDictionary<string, string>;
    FWarnings: TArray<string>;
    FLanguage: string;
    function GetCount: Integer;
    function GetWarnings: TArray<string>;
    function GetLanguage: string;
  public
    /// <summary>
    ///   Загружает .po из AStream с текущей позиции до конца (поток не
    ///   освобождается). ASourceName — имя для текстов ошибок и
    ///   предупреждений ('' — только номер строки). Ошибка разбора —
    ///   ETgPoError; AStream = nil — EArgumentNilException.
    /// </summary>
    constructor Create(AStream: TStream; const ASourceName: string = '');
    destructor Destroy; override;
    /// <summary>ITgTranslator: перевод ключа AMsgId.</summary>
    function TryTranslate(const AMsgId: string; out AText: string): Boolean;
  end;

/// <summary>
///   Загружает переводчик из файла .po. Ошибка разбора — ETgPoError (имя
///   файла и номер строки); ошибка открытия файла — исключение RTL
///   (EFOpenError).
/// </summary>
function TgLoadPoTranslator(const AFileName: string): ITgPoTranslator;
/// <summary>
///   Загружает переводчик из потока (с текущей позиции до конца; поток не
///   освобождается) — например, TResourceStream или asset на Android.
///   ASourceName — имя для текстов ошибок и предупреждений ('' — только
///   номер строки). Ошибка разбора — ETgPoError; nil — EArgumentNilException.
/// </summary>
function TgLoadPoTranslatorFromStream(AStream: TStream;
  const ASourceName: string = ''): ITgPoTranslator;

implementation

uses
  TgBot.Consts;

const
  // Наибольшая длина msgid/msgctxt/текста в сообщении (символов).
  CPoShortMax = 60;
  // Начальная ёмкость буфера чтения потока, если размер потока неизвестен.
  CPoReadChunk = 64 * 1024;
  // Наибольший индекс msgstr[n], который хранится точно (больше — не важен:
  // нужен только msgstr[0]).
  CPoMaxPluralIndex = 1000000;

type
  // Поле записи .po, в которое идут строки "…" (ключевое слово строки).
  TTgPoField = (None, Context, Id, IdPlural, Str, StrPlural);

  /// <summary>
  ///   Разбор текста .po в словарь переводчика. Объект — на время одной
  ///   загрузки.
  /// </summary>
  TTgPoReader = class
  private
    FSourceName: string;
    // Словарь переводчика (не владеет).
    FMap: TDictionary<string, string>;
    // msgid принятой записи → номер её строки (предупреждение о повторе).
    FAccepted: TDictionary<string, Integer>;
    FWarnings: TList<string>;
    FLanguage: string;
    // Текст текущего поля (склейка строк "…").
    FBuf: TStringBuilder;
    // Номер текущей строки файла (с 1).
    FLine: Integer;
    // Текущая запись: поле строк продолжения, строка начала записи, индекс
    // текущего msgstr[n], наличие msgctxt, флаг fuzzy и готовые поля.
    FField: TTgPoField;
    FEntryLine: Integer;
    FPluralIndex: Integer;
    FHasContext: Boolean;
    FFuzzy: Boolean;
    FContext: string;
    FId: string;
    FStr: string;
    procedure Fail(ALine: Integer; const ADetail: string);
    procedure Warn(ALine: Integer; const ADetail: string);
    function EntryComplete: Boolean;
    procedure FlushField;
    procedure ResetEntry;
    procedure FinishEntry;
    procedure ProcessHeader;
    procedure CheckCharset(const AContentType: string);
    procedure ParseLine(P, AEnd: PChar);
    procedure ParseComment(P, AEnd: PChar);
    procedure ParseKeyword(P, AEnd: PChar);
    procedure ReadStrings(P, AEnd: PChar);
  public
    constructor Create(const ASourceName: string; AMap: TDictionary<string, string>);
    destructor Destroy; override;
    /// <summary>Разбирает байты .po (UTF-8, BOM необязателен).</summary>
    procedure Parse(const ABytes: TBytes);
    /// <summary>Предупреждения загрузки (копия).</summary>
    function WarningsArray: TArray<string>;
    property Language: string read FLanguage;
  end;

// Место в источнике для текстов: «имя, строка N» или «строка N».
function TgPoLocation(const ASourceName: string; ALine: Integer): string;
begin
  if ASourceName <> '' then
    Result := TgLangTextFmt(@SRuPoLocation, @SEnPoLocation, [ASourceName, ALine])
  else
    Result := TgLangTextFmt(@SRuPoLine, @SEnPoLine, [ALine]);
end;

// Текст для сообщения: не длиннее CPoShortMax символов (с '…'), управляющие
// символы заменены пробелами — сообщение остаётся одной строкой.
function TgPoShort(const AText: string): string;
var
  I: Integer;
begin
  if Length(AText) > CPoShortMax then
  begin
    Result := Copy(AText, 1, CPoShortMax);
    // Не разрезать суррогатную пару.
    if (Result[High(Result)] >= #$D800) and (Result[High(Result)] <= #$DBFF) then
      SetLength(Result, Length(Result) - 1);
    Result := Result + '…';
  end
  else
    Result := AText;
  for I := Low(Result) to High(Result) do
    if Result[I] < ' ' then
      Result[I] := ' ';
end;

// Текст от P до AEnd (без хвостовых пробелов и управляющих символов, как
// TrimRight) для сообщения. Копируется не больше CPoShortMax + 1 символов —
// столько нужно TgPoShort, чтобы сократить текст: хвост длинной строки не
// копируется.
function TgPoRest(P, AEnd: PChar): string;
begin
  while (AEnd > P) and ((AEnd - 1)^ <= ' ') do
    Dec(AEnd);
  if AEnd - P > CPoShortMax + 1 then
    AEnd := P + CPoShortMax + 1;
  SetString(Result, P, AEnd - P);
  Result := TgPoShort(Result);
end;

// Перевод AStr подходит к ключу AMsgId по спецификаторам Format. Ключ с '%'
// — строка формата: аргументы совпадают (TgSameFormatSignature). Ключ без
// '%' — простой текст: TgLangText отдаёт перевод без Format, '%' в нём —
// литерал; отбрасывается только перевод, подпись которого определена и не
// пуста (корректные спецификаторы, для которых нет аргументов). Если такой
// ключ всё же форматируется (TgLangTextFmt), перевод с одиночным '%' там
// не пройдёт TgSameFormatSignature — будет встроенный текст.
function TgPoSameFormat(const AStr, AMsgId: string): Boolean;
begin
  if Pos('%', AMsgId) > 0 then
    Result := TgSameFormatSignature(AStr, AMsgId)
  else
    // Подпись не определена (одиночный '%') или пуста (нет спецификаторов).
    Result := not TgSameFormatSignature(AStr, AStr) or TgSameFormatSignature(AStr, '');
end;

// Индекс первого байта, нарушающего UTF-8 (строгая проверка: без
// избыточных форм, суррогатов и значений больше U+10FFFF), начиная с
// AStart; -1 — текст корректен.
function TgPoUtf8Invalid(const ABytes: TBytes; AStart: Integer): Integer;
var
  I, J, LCount, LNeed: Integer;
  B, LLow, LHigh: Byte;
begin
  I := AStart;
  LCount := Length(ABytes);
  while I < LCount do
  begin
    B := ABytes[I];
    if B < $80 then
    begin
      Inc(I);
      Continue;
    end;
    // Число байт продолжения и допустимый диапазон первого из них.
    LLow := $80;
    LHigh := $BF;
    if (B >= $C2) and (B <= $DF) then
      LNeed := 1
    else if B = $E0 then
    begin
      LNeed := 2;
      LLow := $A0;
    end
    else if ((B >= $E1) and (B <= $EC)) or (B = $EE) or (B = $EF) then
      LNeed := 2
    else if B = $ED then
    begin
      LNeed := 2;
      LHigh := $9F;
    end
    else if B = $F0 then
    begin
      LNeed := 3;
      LLow := $90;
    end
    else if (B >= $F1) and (B <= $F3) then
      LNeed := 3
    else if B = $F4 then
    begin
      LNeed := 3;
      LHigh := $8F;
    end
    else
      Exit(I);
    if I + LNeed >= LCount then
      Exit(I);
    if (ABytes[I + 1] < LLow) or (ABytes[I + 1] > LHigh) then
      Exit(I);
    for J := 2 to LNeed do
      if (ABytes[I + J] < $80) or (ABytes[I + J] > $BF) then
        Exit(I);
    Inc(I, LNeed + 1);
  end;
  Result := -1;
end;

// Номер строки (с 1) байта AIndex: переводы строк CRLF, LF, CR с AStart.
function TgPoByteLine(const ABytes: TBytes; AStart, AIndex: Integer): Integer;
var
  I: Integer;
begin
  Result := 1;
  I := AStart;
  while I < AIndex do
  begin
    if ABytes[I] = 13 then
    begin
      Inc(Result);
      if (I + 1 < AIndex) and (ABytes[I + 1] = 10) then
        Inc(I);
    end
    else if ABytes[I] = 10 then
      Inc(Result);
    Inc(I);
  end;
end;

// Всё содержимое потока с текущей позиции до конца: чтение до нуля
// прочитанных байт (Read может возвращать меньше запрошенного). Начальная
// ёмкость — остаток потока (Size - Position) + 1, если поток его сообщает
// (лишний байт — для завершающего Read, вернувшего 0), иначе CPoReadChunk;
// заполненный буфер растёт вдвое — копирование линейное.
function TgPoReadAll(AStream: TStream): TBytes;
var
  LRest: Int64;
  LCount, LCapacity, LRead: Integer;
begin
  try
    LRest := AStream.Size - AStream.Position;
  except
    on Exception do
      LRest := -1; // поток без Size/Seek — размер неизвестен
  end;
  if (LRest >= 0) and (LRest < MaxInt) then
    LCapacity := Integer(LRest) + 1
  else
    LCapacity := CPoReadChunk;
  SetLength(Result, LCapacity);
  LCount := 0;
  repeat
    if LCount = Length(Result) then
    begin
      if Length(Result) = MaxInt then
        OutOfMemoryError; // больше не помещается в TBytes
      if Length(Result) > MaxInt div 2 then
        LCapacity := MaxInt
      else
        LCapacity := Length(Result) * 2;
      SetLength(Result, LCapacity);
    end;
    LRead := AStream.Read(Result[LCount], Length(Result) - LCount);
    if LRead > 0 then
      Inc(LCount, LRead);
  until LRead <= 0;
  SetLength(Result, LCount);
end;

{ ETgPoError }

constructor ETgPoError.Create(const ADetail, AFileName: string; ALineNumber: Integer);
begin
  inherited Create(TgLangTextFmt(@SRuPoError, @SEnPoError,
    [TgPoLocation(AFileName, ALineNumber), ADetail]));
  FFileName := AFileName;
  FLineNumber := ALineNumber;
end;

{ TTgPoReader }

constructor TTgPoReader.Create(const ASourceName: string; AMap: TDictionary<string, string>);
begin
  inherited Create;
  FSourceName := ASourceName;
  FMap := AMap;
  FAccepted := TDictionary<string, Integer>.Create;
  FWarnings := TList<string>.Create;
  FBuf := TStringBuilder.Create;
  ResetEntry;
end;

destructor TTgPoReader.Destroy;
begin
  FreeAndNil(FBuf);
  FreeAndNil(FWarnings);
  FreeAndNil(FAccepted);
  inherited Destroy;
end;

procedure TTgPoReader.Fail(ALine: Integer; const ADetail: string);
begin
  raise ETgPoError.Create(ADetail, FSourceName, ALine);
end;

procedure TTgPoReader.Warn(ALine: Integer; const ADetail: string);
begin
  FWarnings.Add(TgPoLocation(FSourceName, ALine) + ': ' + ADetail);
end;

function TTgPoReader.WarningsArray: TArray<string>;
begin
  Result := FWarnings.ToArray;
end;

function TTgPoReader.EntryComplete: Boolean;
begin
  Result := FField in [TTgPoField.Str, TTgPoField.StrPlural];
end;

procedure TTgPoReader.FlushField;
var
  LValue: string;
begin
  LValue := FBuf.ToString;
  FBuf.Clear;
  case FField of
    TTgPoField.Context:
      FContext := LValue;
    TTgPoField.Id:
      FId := LValue;
    TTgPoField.Str:
      FStr := LValue;
    TTgPoField.StrPlural:
      if FPluralIndex = 0 then
        FStr := LValue;
  end;
  // TTgPoField.IdPlural (форма множественного числа msgid) не нужна.
end;

procedure TTgPoReader.ResetEntry;
begin
  FField := TTgPoField.None;
  FEntryLine := 0;
  FPluralIndex := -1;
  FHasContext := False;
  FFuzzy := False;
  FContext := '';
  FId := '';
  FStr := '';
  FBuf.Clear;
end;

procedure TTgPoReader.FinishEntry;
var
  LPrevLine: Integer;
begin
  FlushField;
  if not FHasContext and (FId = '') then
    ProcessHeader // заголовок — и с флагом fuzzy
  // Неточный (fuzzy) и пустой перевод не используются, без предупреждения.
  else if not FFuzzy and (FStr <> '') then
  begin
    if FHasContext then
      // Контекста у ключей библиотеки нет.
      Warn(FEntryLine, TgLangTextFmt(@SRuPoWarnContext, @SEnPoWarnContext,
        [TgPoShort(FContext)]))
    else if not TgPoSameFormat(FStr, FId) then
      Warn(FEntryLine, TgLangTextFmt(@SRuPoWarnFormat, @SEnPoWarnFormat, [TgPoShort(FId)]))
    else
    begin
      if FAccepted.TryGetValue(FId, LPrevLine) then
        Warn(FEntryLine, TgLangTextFmt(@SRuPoWarnDuplicate, @SEnPoWarnDuplicate,
          [TgPoShort(FId), LPrevLine]));
      FMap.AddOrSetValue(FId, FStr);
      FAccepted.AddOrSetValue(FId, FEntryLine);
    end;
  end;
  ResetEntry;
end;

procedure TTgPoReader.ProcessHeader;
var
  LLine, LName, LValue: string;
  LPos: Integer;
begin
  // Строки заголовка «Имя: значение», разделитель — \n.
  for LLine in FStr.Split([#10]) do
  begin
    LPos := Pos(':', LLine);
    if LPos = 0 then
      Continue;
    LName := Trim(Copy(LLine, 1, LPos - 1));
    LValue := Trim(Copy(LLine, LPos + 1, MaxInt));
    if SameText(LName, 'Language') then
      FLanguage := LValue
    else if SameText(LName, 'Content-Type') then
      CheckCharset(LValue);
  end;
end;

procedure TTgPoReader.CheckCharset(const AContentType: string);
const
  CCharsetParam = 'charset=';
var
  LCharset: string;
  LPos: Integer;
begin
  // text/plain; charset=UTF-8 — параметр без учёта регистра, значение до ';'.
  LPos := Pos(CCharsetParam, LowerCase(AContentType));
  if LPos = 0 then
    Exit;
  LCharset := Copy(AContentType, LPos + Length(CCharsetParam), MaxInt);
  LPos := Pos(';', LCharset);
  if LPos > 0 then
    LCharset := Copy(LCharset, 1, LPos - 1);
  LCharset := Trim(LCharset);
  if (Length(LCharset) >= 2) and (LCharset[Low(string)] = '"') and
    (LCharset[High(LCharset)] = '"') then
    LCharset := Copy(LCharset, 2, Length(LCharset) - 2);
  // ASCII — подмножество UTF-8: текст декодирован верно.
  if not (SameText(LCharset, 'UTF-8') or SameText(LCharset, 'UTF8') or
    SameText(LCharset, 'ASCII') or SameText(LCharset, 'US-ASCII')) then
    Fail(FEntryLine, TgLangTextFmt(@SRuPoCharset, @SEnPoCharset, [TgPoShort(LCharset)]));
end;

procedure TTgPoReader.Parse(const ABytes: TBytes);
var
  LStart, LBad: Integer;
  LText: string;
  P, LEnd, LLineStart: PChar;
begin
  LStart := 0;
  if (Length(ABytes) >= 3) and (ABytes[0] = $EF) and (ABytes[1] = $BB) and (ABytes[2] = $BF) then
    LStart := 3;
  // Строгая проверка: TEncoding.UTF8 молча заменил бы неверные байты.
  LBad := TgPoUtf8Invalid(ABytes, LStart);
  if LBad >= 0 then
    Fail(TgPoByteLine(ABytes, LStart, LBad), TgLangText(@SRuPoBadUtf8, @SEnPoBadUtf8));
  if Length(ABytes) > LStart then
    LText := TEncoding.UTF8.GetString(ABytes, LStart, Length(ABytes) - LStart)
  else
    LText := '';
  P := PChar(LText);
  LEnd := P + Length(LText);
  FLine := 0;
  while P < LEnd do
  begin
    LLineStart := P;
    while (P < LEnd) and (P^ <> #10) and (P^ <> #13) do
      Inc(P);
    Inc(FLine);
    ParseLine(LLineStart, P);
    // Перевод строки: CRLF, CR или LF.
    if P < LEnd then
    begin
      if (P^ = #13) and (P + 1 < LEnd) and ((P + 1)^ = #10) then
        Inc(P);
      Inc(P);
    end;
  end;
  if EntryComplete then
    FinishEntry
  else if FField <> TTgPoField.None then
    Fail(FEntryLine, TgLangText(@SRuPoNoMsgstr, @SEnPoNoMsgstr));
end;

procedure TTgPoReader.ParseLine(P, AEnd: PChar);
begin
  while (P < AEnd) and ((P^ = ' ') or (P^ = #9)) do
    Inc(P);
  if P >= AEnd then
  begin
    // Пустая строка завершает готовую запись; внутри записи — пропуск.
    if EntryComplete then
      FinishEntry;
    Exit;
  end;
  case P^ of
    '#':
      ParseComment(P + 1, AEnd);
    '"':
      begin
        if FField = TTgPoField.None then
          Fail(FLine, TgLangText(@SRuPoOrphanString, @SEnPoOrphanString));
        ReadStrings(P, AEnd);
      end;
  else
    ParseKeyword(P, AEnd);
  end;
end;

procedure TTgPoReader.ParseComment(P, AEnd: PChar);
var
  LStart: PChar;
  LFlag: string;
begin
  // Комментарий относится к следующей записи: готовая запись завершается.
  if EntryComplete then
    FinishEntry;
  if (P < AEnd) and (P^ = '~') then
  begin
    // Устаревшая запись (#~) пропускается; её флаги (#, перед ней) к
    // следующей записи не относятся.
    if FField = TTgPoField.None then
      FFuzzy := False;
    Exit;
  end;
  if (P >= AEnd) or (P^ <> ',') then
    Exit; // #, #., #:, #| — не нужны
  // Флаги: «#, fuzzy, c-format».
  Inc(P);
  while P < AEnd do
  begin
    while (P < AEnd) and ((P^ = ' ') or (P^ = #9) or (P^ = ',')) do
      Inc(P);
    LStart := P;
    while (P < AEnd) and (P^ <> ' ') and (P^ <> #9) and (P^ <> ',') do
      Inc(P);
    if P > LStart then
    begin
      SetString(LFlag, LStart, P - LStart);
      if LFlag = 'fuzzy' then
        FFuzzy := True;
    end;
  end;
end;

procedure TTgPoReader.ParseKeyword(P, AEnd: PChar);
var
  LStart, LAfterWord: PChar;
  LWord: string;
  LKind: TTgPoField;
  LIndex: Integer;

  // Пропуск пробелов и табуляций с P.
  procedure SkipBlanks;
  begin
    while (P < AEnd) and ((P^ = ' ') or (P^ = #9)) do
      Inc(P);
  end;

begin
  LStart := P;
  while (P < AEnd) and (CharInSet(P^, ['a'..'z', 'A'..'Z', '_'])) do
    Inc(P);
  SetString(LWord, LStart, P - LStart);
  LIndex := -1;
  LAfterWord := P;
  if LWord = 'msgstr' then
    SkipBlanks; // msgstr [n] — пробел перед '[' допустим, как в GNU
  if LWord = 'msgctxt' then
    LKind := TTgPoField.Context
  else if LWord = 'msgid' then
    LKind := TTgPoField.Id
  else if LWord = 'msgid_plural' then
    LKind := TTgPoField.IdPlural
  else if (LWord = 'msgstr') and (P < AEnd) and (P^ = '[') then
  begin
    // msgstr[n]; пробелы вокруг номера допустимы.
    LKind := TTgPoField.StrPlural;
    Inc(P);
    SkipBlanks;
    LIndex := 0;
    if (P >= AEnd) or not CharInSet(P^, ['0'..'9']) then
      Fail(FLine, TgLangTextFmt(@SRuPoUnexpected, @SEnPoUnexpected, [TgPoRest(LStart, AEnd)]));
    while (P < AEnd) and CharInSet(P^, ['0'..'9']) do
    begin
      if LIndex <= CPoMaxPluralIndex then
        LIndex := LIndex * 10 + (Ord(P^) - Ord('0'));
      Inc(P);
    end;
    SkipBlanks;
    if (P >= AEnd) or (P^ <> ']') then
      Fail(FLine, TgLangTextFmt(@SRuPoUnexpected, @SEnPoUnexpected, [TgPoRest(LStart, AEnd)]));
    Inc(P);
    // Для сообщений: как в файле, длинный номер сокращён.
    LWord := TgPoRest(LStart, P);
  end
  else if LWord = 'msgstr' then
  begin
    LKind := TTgPoField.Str;
    P := LAfterWord;
  end
  else
  begin
    Fail(FLine, TgLangTextFmt(@SRuPoUnexpected, @SEnPoUnexpected, [TgPoRest(LStart, AEnd)]));
    Exit;
  end;
  // После ключевого слова — пробел или сразу кавычка.
  if (P < AEnd) and (P^ <> ' ') and (P^ <> #9) and (P^ <> '"') then
    Fail(FLine, TgLangTextFmt(@SRuPoUnexpected, @SEnPoUnexpected, [TgPoRest(LStart, AEnd)]));
  SkipBlanks;
  if (P >= AEnd) or (P^ <> '"') then
    Fail(FLine, TgLangTextFmt(@SRuPoExpectedString, @SEnPoExpectedString, [LWord]));

  // Порядок: [msgctxt] msgid (msgstr | msgid_plural msgstr[n]…).
  case LKind of
    TTgPoField.Context:
      begin
        if EntryComplete then
          FinishEntry;
        if FField = TTgPoField.Context then
          Fail(FLine, TgLangTextFmt(@SRuPoMisplaced, @SEnPoMisplaced, [LWord]));
        if FField <> TTgPoField.None then
          Fail(FEntryLine, TgLangText(@SRuPoNoMsgstr, @SEnPoNoMsgstr));
        FEntryLine := FLine;
        FHasContext := True;
      end;
    TTgPoField.Id:
      begin
        if EntryComplete then
          FinishEntry;
        if FField = TTgPoField.None then
          FEntryLine := FLine
        else if FField = TTgPoField.Context then
          FlushField
        else
          Fail(FEntryLine, TgLangText(@SRuPoNoMsgstr, @SEnPoNoMsgstr));
      end;
    TTgPoField.IdPlural, TTgPoField.Str:
      begin
        if FField <> TTgPoField.Id then
          Fail(FLine, TgLangTextFmt(@SRuPoMisplaced, @SEnPoMisplaced, [LWord]));
        FlushField;
      end;
    TTgPoField.StrPlural:
      begin
        if not (FField in [TTgPoField.IdPlural, TTgPoField.StrPlural]) then
          Fail(FLine, TgLangTextFmt(@SRuPoMisplaced, @SEnPoMisplaced, [LWord]));
        FlushField;
        FPluralIndex := LIndex;
      end;
  end;
  FField := LKind;
  ReadStrings(P, AEnd);
end;

procedure TTgPoReader.ReadStrings(P, AEnd: PChar);
var
  LDone: Boolean;

  // Символ ASCII escape-последовательности (\ooo, \xHH) с ASeq; 0 и
  // не-ASCII — ошибка: байты других кодировок в UTF-16 не переводятся.
  procedure AppendCode(ACode: Integer; ASeq: PChar);
  var
    LSeq: string;
  begin
    if (ACode < 1) or (ACode > $7F) then
    begin
      SetString(LSeq, ASeq, P - ASeq);
      Fail(FLine, TgLangTextFmt(@SRuPoBadEscape, @SEnPoBadEscape, [TgPoShort(LSeq)]));
    end;
    FBuf.Append(Char(ACode));
  end;

  // Escape-последовательность с '\' в P.
  procedure ReadEscape;
  var
    LSeq: PChar;
    LChar: Char;
    LCode, LDigits: Integer;
    LText: string;
  begin
    LSeq := P;
    Inc(P);
    if P >= AEnd then
      Fail(FLine, TgLangTextFmt(@SRuPoBadEscape, @SEnPoBadEscape, ['\']));
    LChar := P^;
    Inc(P);
    case LChar of
      'n': FBuf.Append(#10);
      't': FBuf.Append(#9);
      'r': FBuf.Append(#13);
      'a': FBuf.Append(#7);
      'b': FBuf.Append(#8);
      'f': FBuf.Append(#12);
      'v': FBuf.Append(#11);
      '\', '"', '''', '?': FBuf.Append(LChar);
      '0'..'7':
        begin
          LCode := Ord(LChar) - Ord('0');
          LDigits := 1;
          while (LDigits < 3) and (P < AEnd) and CharInSet(P^, ['0'..'7']) do
          begin
            LCode := LCode * 8 + (Ord(P^) - Ord('0'));
            Inc(P);
            Inc(LDigits);
          end;
          AppendCode(LCode, LSeq);
        end;
      'x':
        begin
          // Как в C: все шестнадцатеричные цифры подряд.
          LCode := 0;
          LDigits := 0;
          while (P < AEnd) and CharInSet(P^, ['0'..'9', 'a'..'f', 'A'..'F']) do
          begin
            if LCode <= $FF then
            begin
              case P^ of
                '0'..'9': LCode := LCode * 16 + (Ord(P^) - Ord('0'));
                'a'..'f': LCode := LCode * 16 + (Ord(P^) - Ord('a') + 10);
              else
                LCode := LCode * 16 + (Ord(P^) - Ord('A') + 10);
              end;
            end;
            Inc(P);
            Inc(LDigits);
          end;
          if LDigits = 0 then
            LCode := 0; // «\x» без цифр — ошибка в AppendCode
          AppendCode(LCode, LSeq);
        end;
    else
      SetString(LText, LSeq, P - LSeq);
      Fail(FLine, TgLangTextFmt(@SRuPoBadEscape, @SEnPoBadEscape, [TgPoShort(LText)]));
    end;
  end;

begin
  // P — на открывающей кавычке; строк "…" на одной строке может быть несколько.
  repeat
    Inc(P);
    LDone := False;
    while not LDone do
    begin
      if P >= AEnd then
        Fail(FLine, TgLangText(@SRuPoUnterminated, @SEnPoUnterminated));
      case P^ of
        '"':
          begin
            Inc(P);
            LDone := True;
          end;
        '\':
          ReadEscape;
      else
        FBuf.Append(P^);
        Inc(P);
      end;
    end;
    while (P < AEnd) and ((P^ = ' ') or (P^ = #9)) do
      Inc(P);
    if P >= AEnd then
      Exit;
    if P^ <> '"' then
      Fail(FLine, TgLangTextFmt(@SRuPoUnexpected, @SEnPoUnexpected, [TgPoRest(P, AEnd)]));
  until False;
end;

{ TTgPoTranslator }

constructor TTgPoTranslator.Create(AStream: TStream; const ASourceName: string);
var
  LReader: TTgPoReader;
begin
  inherited Create;
  if AStream = nil then
    raise EArgumentNilException.Create(TgLangTextFmt(@SRuArgNil, @SEnArgNil, ['AStream']));
  FMap := TDictionary<string, string>.Create;
  LReader := TTgPoReader.Create(ASourceName, FMap);
  try
    LReader.Parse(TgPoReadAll(AStream));
    FWarnings := LReader.WarningsArray;
    FLanguage := LReader.Language;
  finally
    LReader.Free;
  end;
  FMap.TrimExcess;
end;

destructor TTgPoTranslator.Destroy;
begin
  FreeAndNil(FMap);
  inherited Destroy;
end;

function TTgPoTranslator.TryTranslate(const AMsgId: string; out AText: string): Boolean;
begin
  // Только чтение неизменяемого словаря — безопасно из любых потоков.
  Result := FMap.TryGetValue(AMsgId, AText);
end;

function TTgPoTranslator.GetCount: Integer;
begin
  Result := FMap.Count;
end;

function TTgPoTranslator.GetWarnings: TArray<string>;
begin
  // Копия: элементы общего массива вызывающий изменить не может.
  Result := Copy(FWarnings, 0, Length(FWarnings));
end;

function TTgPoTranslator.GetLanguage: string;
begin
  Result := FLanguage;
end;

function TgLoadPoTranslator(const AFileName: string): ITgPoTranslator;
var
  LStream: TFileStream;
begin
  LStream := TFileStream.Create(AFileName, fmOpenRead or fmShareDenyWrite);
  try
    Result := TTgPoTranslator.Create(LStream, AFileName);
  finally
    LStream.Free;
  end;
end;

function TgLoadPoTranslatorFromStream(AStream: TStream;
  const ASourceName: string): ITgPoTranslator;
begin
  Result := TTgPoTranslator.Create(AStream, ASourceName);
end;

end.
