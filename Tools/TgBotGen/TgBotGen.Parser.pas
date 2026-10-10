unit TgBotGen.Parser;

{
  TgBotGen — разбор HTML-страницы https://core.telegram.org/bots/api
  в модель TGenModel.

  Порядок работы:
  1. Терпимый к ошибкам разметки построитель DOM (только RTL): комментарии,
     void-теги, script/style, неявное закрытие p/li/tr/td, лишние
     закрывающие теги игнорируются.
  2. Обход прямых потомков <div id="dev_page_content">: h3 — раздел,
     h4 с якорем — сущность (имя без пробелов; с заглавной — тип,
     со строчной — метод), далее p/table/ul до следующего h3/h4.
  3. Таблицы Field|Type|Description — поля типа, Parameter|Type|Required|
     Description — параметры метода; <ul> из одних ссылок на типы при
     отсутствии таблицы — варианты union-типа.
  4. Тип результата метода — из предложений описания с «Returns …» /
     «… is returned» по ссылкам на типы и выделенным <em>True</em>/<em>Int</em>.

  Неизвестная разметка не прерывает разбор, а даёт предупреждения в модели.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.Classes,
  TgBotGen.Model;

type
  /// <summary>
  ///   Разбор невозможен: страница не в UTF-8, нет dev_page_content,
  ///   не найдено ни одного типа или метода.
  /// </summary>
  EGenParseError = class(Exception);

  /// <summary>Разбор страницы документации Bot API.</summary>
  TGenParser = class
  public
    /// <summary>Разбирает HTML-файл (UTF-8) в AModel (модель предварительно очищается).</summary>
    class procedure ParseFile(const AFileName: string; AModel: TGenModel); static;
    /// <summary>
    ///   Разбирает HTML-текст в AModel (модель предварительно очищается).
    ///   Нет &lt;div id="dev_page_content"&gt; или пустая модель — EGenParseError.
    /// </summary>
    class procedure ParseHtml(const AHtml: string; AModel: TGenModel); static;
    /// <summary>
    ///   Декодирует байты UTF-8 (BOM допускается). Некорректная
    ///   последовательность — EGenParseError с именем источника ASource.
    /// </summary>
    class function DecodeUtf8(const ABytes: TBytes; const ASource: string): string; static;
    /// <summary>Версия Bot API со страницы ('10.3') или ''.</summary>
    class function ExtractVersion(const AHtml: string): string; static;
    /// <summary>
    ///   Декодирует HTML-сущности (&amp;amp; &amp;lt; &amp;gt; &amp;quot; &amp;#39;
    ///   &amp;nbsp; числовые и распространённые именованные). Неизвестные
    ///   сущности остаются как есть; при AUnknown &lt;&gt; nil их имена добавляются туда.
    /// </summary>
    class function DecodeEntities(const AText: string; AUnknown: TStrings = nil): string; static;
  end;

implementation

uses
  System.StrUtils,
  System.Character,
  System.IOUtils,
  System.RegularExpressions,
  System.Generics.Collections;

const
  // Маркеры аннотированного текста (для поиска типа результата и констант).
  CMarkLinkBegin = #1;  // #1 якорь #2 текст ссылки #3
  CMarkLinkText = #2;
  CMarkLinkEnd = #3;
  CMarkEmBegin = #4;    // #4 текст <em> #5
  CMarkEmEnd = #5;

  CSectionRecentChanges = 'Recent changes';

  CVoidTags: array[0..13] of string = ('area', 'base', 'br', 'col', 'embed',
    'hr', 'img', 'input', 'link', 'meta', 'param', 'source', 'track', 'wbr');
  CRawTextTags: array[0..2] of string = ('script', 'style', 'textarea');
  // Корни «чужого» содержимого: внутри них допустимы самозакрывающиеся «/>».
  CForeignTags: array[0..1] of string = ('svg', 'math');
  // Открытие этих элементов неявно закрывает открытый <p>.
  CParagraphClosers: array[0..15] of string = ('p', 'div', 'table', 'ul', 'ol',
    'dl', 'h1', 'h2', 'h3', 'h4', 'h5', 'h6', 'blockquote', 'pre', 'hr', 'section');
  // Блочные элементы при извлечении текста дают перевод строки.
  CTextBlockTags: array[0..16] of string = ('p', 'div', 'ul', 'ol', 'li', 'table',
    'tr', 'blockquote', 'pre', 'h1', 'h2', 'h3', 'h4', 'h5', 'h6', 'dl', 'section');

type
  TGenTextMode = (Plain, Annotated);

  /// <summary>Узел упрощённого DOM: элемент (Tag &lt;&gt; '') или текст.</summary>
  TGenHtmlNode = class
  private
    FTag: string;
    FText: string;
    FParent: TGenHtmlNode;
    FChildren: TObjectList<TGenHtmlNode>;
    FAttrNames: TArray<string>;
    FAttrValues: TArray<string>;
    function GetChildCount: Integer;
    function GetChild(AIndex: Integer): TGenHtmlNode;
  public
    constructor CreateElement(AParent: TGenHtmlNode; const ATag: string);
    constructor CreateText(AParent: TGenHtmlNode; const AText: string);
    destructor Destroy; override;
    procedure AddChild(ANode: TGenHtmlNode);
    procedure SetAttr(const AName, AValue: string);
    function Attr(const AName: string): string;
    function HasClass(const AClass: string): Boolean;
    function IsText: Boolean;
    function IsTag(const ATag: string): Boolean;
    function FindById(const AId: string): TGenHtmlNode;
    procedure FindAll(const ATag: string; AList: TList<TGenHtmlNode>);
    property Tag: string read FTag;
    property Text: string read FText;
    property Parent: TGenHtmlNode read FParent;
    property ChildCount: Integer read GetChildCount;
    property Children[AIndex: Integer]: TGenHtmlNode read GetChild;
  end;

  /// <summary>Построитель DOM из HTML-текста.</summary>
  TGenDomBuilder = class
  private
    FHtml: string;
    FPos: Integer;
    FLen: Integer;
    FCurrent: TGenHtmlNode;
    FStrayCloseTags: Integer;
    FUnknownEntities: TStringList;
    function StartsAt(const AText: string): Boolean;
    function FindOpen(const ATag: string; const ABoundary: array of string): TGenHtmlNode;
    procedure CloseTo(ANode: TGenHtmlNode);
    procedure ImplicitClose(const ATag: string);
    procedure ReadText;
    procedure ReadOpenTag;
    procedure ReadCloseTag;
    procedure SkipTo(const ATerminator: string);
    procedure SkipRawText(const ATag: string);
  public
    constructor Create;
    destructor Destroy; override;
    /// <summary>Строит DOM; корень (Tag = '#root') освобождает вызывающий.</summary>
    function Build(const AHtml: string): TGenHtmlNode;
    property StrayCloseTags: Integer read FStrayCloseTags;
    property UnknownEntities: TStringList read FUnknownEntities;
  end;

  /// <summary>Отложенный разбор типа результата метода.</summary>
  TGenPendingReturn = record
    Method: TGenMethod;
    Annotated: string;
  end;

  /// <summary>Отложенный разбор дополнительных вариантов union («either a String…»).</summary>
  TGenPendingExtra = record
    UnionType: TGenType;
    /// <summary>Аннотированный текст абзацев перед списком вариантов.</summary>
    Annotated: string;
  end;

  /// <summary>Разбор содержимого страницы в модель.</summary>
  TGenPageParser = class
  private
    FModel: TGenModel;
    FSection: string;
    FEntityName: string;
    FEntityAnchor: string;
    FEntityNodes: TList<TGenHtmlNode>;
    FAnchorTypes: TDictionary<string, string>;
    FPendingReturns: TList<TGenPendingReturn>;
    FPendingExtras: TList<TGenPendingExtra>;
    FConstRegEx: TRegEx;
    FReturnsRegEx: TRegEx;
    FReturnedRegEx: TRegEx;
    FHeadingCount: Integer;
    procedure HandleHeading4(ANode: TGenHtmlNode);
    procedure FlushEntity;
    procedure ParseTable(ATable: TGenHtmlNode; AType: TGenType; AMethod: TGenMethod);
    function IsSubtypeList(AList: TGenHtmlNode; ANames: TList<string>): Boolean;
    function DetectReturnType(const AAnnotated: string; out ASentence: string): TGenTypeRef;
    /// <summary>
    ///   Собирает в ATokens ссылки на типы из ASentence[AFrom..ATo]: ссылки
    ///   на типы, &lt;em&gt;True/Int/String…&lt;/em&gt;, при APlainPrimitives —
    ///   и слова String/Integer/Float/Boolean обычным текстом. «array of»
    ///   перед токеном делает его массивом.
    /// </summary>
    procedure ScanTypeTokens(const ASentence: string; AFrom, ATo: Integer;
      APlainPrimitives: Boolean; ATokens: TObjectList<TGenTypeRef>);
    /// <summary>
    ///   Забирает токены из ATokens (список очищается): nil — токенов нет,
    ///   один — он сам, несколько — Union без повторов.
    /// </summary>
    function TokensToTypeRef(ATokens: TObjectList<TGenTypeRef>): TGenTypeRef;
    function ScanReturnTokens(const ASentence: string; AFrom: Integer): TGenTypeRef;
    /// <summary>
    ///   Для каждого «… is returned» в предложении собирает токены из окна от
    ///   начала его фрагмента (запятая, союз, начало предложения) до глагола.
    /// </summary>
    function ScanReturnedClauses(const ASentence: string): TGenTypeRef;
    procedure ResolveReturnTypes;
    procedure ResolveExtraVariants;
  public
    constructor Create(AModel: TGenModel);
    destructor Destroy; override;
    procedure Execute(AContent: TGenHtmlNode);
    /// <summary>Число обработанных h4 с якорем на верхнем уровне контента.</summary>
    property HeadingCount: Integer read FHeadingCount;
  end;

function IsInArray(const AValue: string; const AArray: array of string): Boolean;
var
  LItem: string;
begin
  for LItem in AArray do
    if SameStr(LItem, AValue) then
      Exit(True);
  Result := False;
end;

/// <summary>Убирает маркеры аннотации, оставляя видимый текст.</summary>
function StripMarkers(const AText: string): string;
var
  LSb: TStringBuilder;
  I: Integer;
begin
  LSb := TStringBuilder.Create(Length(AText));
  try
    I := 1;
    while I <= Length(AText) do
    begin
      case AText[I] of
        CMarkLinkBegin:
          begin
            // Пропускаем якорь до маркера текста ссылки.
            while (I <= Length(AText)) and (AText[I] <> CMarkLinkText) do
              Inc(I);
          end;
        CMarkLinkText, CMarkLinkEnd, CMarkEmBegin, CMarkEmEnd:
          ;
      else
        LSb.Append(AText[I]);
      end;
      Inc(I);
    end;
    Result := LSb.ToString;
  finally
    LSb.Free;
  end;
end;

/// <summary>
///   Примитивный тип по слову или nil. APlain = False — текст &lt;em&gt;
///   (True, Int, Integer, String, Float, Boolean); APlain = True — обычный
///   текст (только String, Integer, Float, Boolean).
/// </summary>
function PrimitiveRef(const AWord: string; APlain: Boolean): TGenTypeRef;
begin
  if SameStr(AWord, 'String') then
    Result := TGenTypeRef.Create(TGenTypeKind.Str)
  else if SameStr(AWord, 'Integer') or (not APlain and SameStr(AWord, 'Int')) then
    Result := TGenTypeRef.Create(TGenTypeKind.Int)
  else if SameStr(AWord, 'Float') then
    Result := TGenTypeRef.Create(TGenTypeKind.Float)
  else if SameStr(AWord, 'Boolean') then
    Result := TGenTypeRef.Create(TGenTypeKind.Bool)
  else if not APlain and SameStr(AWord, 'True') then
    Result := TGenTypeRef.Create(TGenTypeKind.TrueConst)
  else
    Result := nil;
end;

/// <summary>
///   Начало фрагмента предложения перед позицией AEnd: позиция после последней
///   запятой, «;», «:» или союза (otherwise, if, else, but, when, unless,
///   while) вне маркеров; 1 — начало предложения. «and»/«or» границей не
///   считаются: они соединяют варианты типа («Message or True is returned»).
/// </summary>
function ClauseStart(const ASentence: string; AEnd: Integer): Integer;
const
  CConjunctions: array[0..6] of string = ('otherwise', 'if', 'else', 'but',
    'when', 'unless', 'while');
var
  I, LWordEnd, LDepth: Integer;
  LCh: Char;
begin
  Result := 1;
  LDepth := 0;
  I := 1;
  while I < AEnd do
  begin
    LCh := ASentence[I];
    case LCh of
      CMarkLinkBegin, CMarkEmBegin:
        Inc(LDepth);
      CMarkLinkEnd, CMarkEmEnd:
        if LDepth > 0 then
          Dec(LDepth);
      ',', ';', ':':
        if LDepth = 0 then
          Result := I + 1;
    else
      if (LDepth = 0) and LCh.IsLetter and ((I = 1) or not ASentence[I - 1].IsLetterOrDigit) then
      begin
        LWordEnd := I;
        while (LWordEnd < AEnd) and ASentence[LWordEnd].IsLetter do
          Inc(LWordEnd);
        if IsInArray(LowerCase(Copy(ASentence, I, LWordEnd - I)), CConjunctions) then
          Result := LWordEnd;
        I := LWordEnd;
        Continue;
      end;
    end;
    Inc(I);
  end;
end;

/// <summary>
///   Нормализует пробелы: серии пробелов — в один, без пробелов у переводов
///   строк, без пустых строк, без пробелов по краям.
/// </summary>
function NormalizeText(const AText: string): string;
var
  LSb: TStringBuilder;
  LCh: Char;
  LPendingSpace, LPendingBreak: Boolean;
begin
  LSb := TStringBuilder.Create(Length(AText));
  try
    LPendingSpace := False;
    LPendingBreak := False;
    for LCh in AText do
    begin
      if LCh = #10 then
      begin
        LPendingBreak := LSb.Length > 0;
        LPendingSpace := False;
      end
      else if (LCh = ' ') or (LCh = #9) or (LCh = #13) or (LCh = #$00A0) then
        LPendingSpace := LSb.Length > 0
      else
      begin
        if LPendingBreak then
          LSb.Append(#10)
        else if LPendingSpace then
          LSb.Append(' ');
        LPendingBreak := False;
        LPendingSpace := False;
        LSb.Append(LCh);
      end;
    end;
    Result := LSb.ToString;
  finally
    LSb.Free;
  end;
end;

procedure AppendNodeText(ANode: TGenHtmlNode; ASb: TStringBuilder; AMode: TGenTextMode);
var
  LBlock, LLink: Boolean;
  LHref: string;
  I: Integer;
begin
  if ANode.IsText then
  begin
    ASb.Append(ANode.Text);
    Exit;
  end;
  if ANode.IsTag('br') then
  begin
    ASb.Append(#10);
    Exit;
  end;
  if ANode.IsTag('img') then
  begin
    ASb.Append(ANode.Attr('alt'));
    Exit;
  end;

  LBlock := IsInArray(ANode.Tag, CTextBlockTags);
  if LBlock then
    ASb.Append(#10);
  if ANode.IsTag('li') then
    ASb.Append('- ');

  LLink := False;
  if AMode = TGenTextMode.Annotated then
  begin
    if ANode.IsTag('a') then
    begin
      LHref := ANode.Attr('href');
      LLink := StartsStr('#', LHref);
      if LLink then
        ASb.Append(CMarkLinkBegin).Append(LowerCase(Copy(LHref, 2, MaxInt))).Append(CMarkLinkText);
    end
    else if ANode.IsTag('em') then
      ASb.Append(CMarkEmBegin);
  end;

  for I := 0 to ANode.ChildCount - 1 do
    AppendNodeText(ANode.Children[I], ASb, AMode);

  if LLink then
    ASb.Append(CMarkLinkEnd)
  else if (AMode = TGenTextMode.Annotated) and ANode.IsTag('em') then
    ASb.Append(CMarkEmEnd);

  if ANode.IsTag('td') or ANode.IsTag('th') then
    ASb.Append(' ');
  if LBlock then
    ASb.Append(#10);
end;

/// <summary>Текст узла с нормализованными пробелами.</summary>
function NodeText(ANode: TGenHtmlNode; AMode: TGenTextMode = TGenTextMode.Plain): string;
var
  LSb: TStringBuilder;
begin
  LSb := TStringBuilder.Create;
  try
    AppendNodeText(ANode, LSb, AMode);
    Result := NormalizeText(LSb.ToString);
  finally
    LSb.Free;
  end;
end;

/// <summary>Текст содержимого узла без оформления самого элемента (маркера «- » у li).</summary>
function NodeInnerText(ANode: TGenHtmlNode): string;
var
  LSb: TStringBuilder;
  I: Integer;
begin
  LSb := TStringBuilder.Create;
  try
    for I := 0 to ANode.ChildCount - 1 do
      AppendNodeText(ANode.Children[I], LSb, TGenTextMode.Plain);
    Result := NormalizeText(LSb.ToString);
  finally
    LSb.Free;
  end;
end;

{ TGenHtmlNode }

constructor TGenHtmlNode.CreateElement(AParent: TGenHtmlNode; const ATag: string);
begin
  inherited Create;
  FParent := AParent;
  FTag := ATag;
  FChildren := TObjectList<TGenHtmlNode>.Create(True);
end;

constructor TGenHtmlNode.CreateText(AParent: TGenHtmlNode; const AText: string);
begin
  inherited Create;
  FParent := AParent;
  FText := AText;
end;

destructor TGenHtmlNode.Destroy;
begin
  FChildren.Free;
  inherited;
end;

procedure TGenHtmlNode.AddChild(ANode: TGenHtmlNode);
begin
  FChildren.Add(ANode);
end;

function TGenHtmlNode.GetChildCount: Integer;
begin
  if FChildren = nil then
    Result := 0
  else
    Result := FChildren.Count;
end;

function TGenHtmlNode.GetChild(AIndex: Integer): TGenHtmlNode;
begin
  Result := FChildren[AIndex];
end;

procedure TGenHtmlNode.SetAttr(const AName, AValue: string);
var
  I: Integer;
begin
  for I := 0 to High(FAttrNames) do
    if SameStr(FAttrNames[I], AName) then
    begin
      FAttrValues[I] := AValue;
      Exit;
    end;
  I := Length(FAttrNames);
  SetLength(FAttrNames, I + 1);
  SetLength(FAttrValues, I + 1);
  FAttrNames[I] := AName;
  FAttrValues[I] := AValue;
end;

function TGenHtmlNode.Attr(const AName: string): string;
var
  I: Integer;
begin
  for I := 0 to High(FAttrNames) do
    if SameStr(FAttrNames[I], AName) then
      Exit(FAttrValues[I]);
  Result := '';
end;

function TGenHtmlNode.HasClass(const AClass: string): Boolean;
var
  LItem: string;
begin
  for LItem in Attr('class').Split([' ', #9, #10, #13], TStringSplitOptions.ExcludeEmpty) do
    if SameStr(LItem, AClass) then
      Exit(True);
  Result := False;
end;

function TGenHtmlNode.IsText: Boolean;
begin
  Result := FTag = '';
end;

function TGenHtmlNode.IsTag(const ATag: string): Boolean;
begin
  Result := SameStr(FTag, ATag);
end;

function TGenHtmlNode.FindById(const AId: string): TGenHtmlNode;
var
  I: Integer;
begin
  if (not IsText) and SameStr(Attr('id'), AId) then
    Exit(Self);
  for I := 0 to ChildCount - 1 do
  begin
    Result := FChildren[I].FindById(AId);
    if Result <> nil then
      Exit;
  end;
  Result := nil;
end;

procedure TGenHtmlNode.FindAll(const ATag: string; AList: TList<TGenHtmlNode>);
var
  I: Integer;
begin
  for I := 0 to ChildCount - 1 do
  begin
    if FChildren[I].IsTag(ATag) then
      AList.Add(FChildren[I]);
    FChildren[I].FindAll(ATag, AList);
  end;
end;

/// <summary>Якорь заголовка: name первого &lt;a class="anchor"&gt; внутри узла или ''.</summary>
function HeadingAnchor(ANode: TGenHtmlNode): string;
var
  LLinks: TList<TGenHtmlNode>;
  LLink: TGenHtmlNode;
begin
  Result := '';
  LLinks := TList<TGenHtmlNode>.Create;
  try
    ANode.FindAll('a', LLinks);
    for LLink in LLinks do
      if LLink.HasClass('anchor') then
        Exit(LLink.Attr('name'));
  finally
    LLinks.Free;
  end;
end;

{ TGenDomBuilder }

constructor TGenDomBuilder.Create;
begin
  inherited Create;
  FUnknownEntities := TStringList.Create;
  FUnknownEntities.Sorted := True;
  FUnknownEntities.Duplicates := dupIgnore;
end;

destructor TGenDomBuilder.Destroy;
begin
  FUnknownEntities.Free;
  inherited;
end;

function TGenDomBuilder.StartsAt(const AText: string): Boolean;
begin
  Result := SameText(Copy(FHtml, FPos, Length(AText)), AText);
end;

procedure TGenDomBuilder.SkipTo(const ATerminator: string);
var
  LFound: Integer;
begin
  LFound := Pos(ATerminator, FHtml, FPos);
  if LFound = 0 then
    FPos := FLen + 1
  else
    FPos := LFound + Length(ATerminator);
end;

procedure TGenDomBuilder.SkipRawText(const ATag: string);
var
  LFound, LAfter: Integer;
begin
  // Содержимое script/style не разбирается: ищем закрывающий тег без учёта
  // регистра, не копируя остаток документа.
  LFound := Pos('</', FHtml, FPos);
  while LFound > 0 do
  begin
    LAfter := LFound + 2 + Length(ATag);
    if SameText(Copy(FHtml, LFound + 2, Length(ATag)), ATag) and
      ((LAfter > FLen) or not FHtml[LAfter].IsLetterOrDigit) then
    begin
      FPos := LFound;
      SkipTo('>');
      Exit;
    end;
    LFound := Pos('</', FHtml, LFound + 2);
  end;
  FPos := FLen + 1;
end;

function TGenDomBuilder.FindOpen(const ATag: string;
  const ABoundary: array of string): TGenHtmlNode;
begin
  Result := FCurrent;
  while (Result <> nil) and (Result.Parent <> nil) do
  begin
    if Result.IsTag(ATag) then
      Exit;
    if IsInArray(Result.Tag, ABoundary) then
      Exit(nil);
    Result := Result.Parent;
  end;
  Result := nil;
end;

procedure TGenDomBuilder.CloseTo(ANode: TGenHtmlNode);
begin
  FCurrent := ANode.Parent;
end;

procedure TGenDomBuilder.ImplicitClose(const ATag: string);
var
  LOpen: TGenHtmlNode;
begin
  if IsInArray(ATag, CParagraphClosers) and FCurrent.IsTag('p') then
    CloseTo(FCurrent);
  if ATag = 'li' then
  begin
    LOpen := FindOpen('li', ['ul', 'ol']);
    if LOpen <> nil then
      CloseTo(LOpen);
  end
  else if ATag = 'tr' then
  begin
    LOpen := FindOpen('tr', ['table']);
    if LOpen <> nil then
      CloseTo(LOpen);
  end
  else if (ATag = 'td') or (ATag = 'th') then
  begin
    LOpen := FindOpen('td', ['tr', 'table']);
    if LOpen = nil then
      LOpen := FindOpen('th', ['tr', 'table']);
    if LOpen <> nil then
      CloseTo(LOpen);
  end;
end;

procedure TGenDomBuilder.ReadText;
var
  LStart: Integer;
  LText: string;
begin
  LStart := FPos;
  Inc(FPos);
  while (FPos <= FLen) and (FHtml[FPos] <> '<') do
    Inc(FPos);
  LText := TGenParser.DecodeEntities(Copy(FHtml, LStart, FPos - LStart), FUnknownEntities);
  // Переводы строк исходника — обычные пробелы (как в HTML).
  LText := StringReplace(LText, #13, ' ', [rfReplaceAll]);
  LText := StringReplace(LText, #10, ' ', [rfReplaceAll]);
  LText := StringReplace(LText, #9, ' ', [rfReplaceAll]);
  FCurrent.AddChild(TGenHtmlNode.CreateText(FCurrent, LText));
end;

procedure TGenDomBuilder.ReadOpenTag;
var
  LStart: Integer;
  LTag, LName, LValue: string;
  LQuote: Char;
  LNode: TGenHtmlNode;
  LSelfClosing: Boolean;
begin
  Inc(FPos); // '<'
  LStart := FPos;
  while (FPos <= FLen) and (FHtml[FPos].IsLetterOrDigit or (FHtml[FPos] = '-')) do
    Inc(FPos);
  LTag := LowerCase(Copy(FHtml, LStart, FPos - LStart));
  LNode := TGenHtmlNode.CreateElement(nil, LTag);
  try
    LSelfClosing := False;
    // Атрибуты.
    while FPos <= FLen do
    begin
      while (FPos <= FLen) and FHtml[FPos].IsWhiteSpace do
        Inc(FPos);
      if FPos > FLen then
        Break;
      if FHtml[FPos] = '>' then
      begin
        Inc(FPos);
        Break;
      end;
      if FHtml[FPos] = '/' then
      begin
        LSelfClosing := True;
        Inc(FPos);
        Continue;
      end;
      LStart := FPos;
      while (FPos <= FLen) and not FHtml[FPos].IsWhiteSpace and
        not CharInSet(FHtml[FPos], ['=', '>', '/']) do
        Inc(FPos);
      LName := LowerCase(Copy(FHtml, LStart, FPos - LStart));
      if LName = '' then
      begin
        Inc(FPos); // неожиданный символ — пропускаем
        Continue;
      end;
      // '/' считается признаком «/>» только перед самым '>'.
      LSelfClosing := False;
      LValue := '';
      while (FPos <= FLen) and FHtml[FPos].IsWhiteSpace do
        Inc(FPos);
      if (FPos <= FLen) and (FHtml[FPos] = '=') then
      begin
        Inc(FPos);
        while (FPos <= FLen) and FHtml[FPos].IsWhiteSpace do
          Inc(FPos);
        if (FPos <= FLen) and CharInSet(FHtml[FPos], ['"', '''']) then
        begin
          LQuote := FHtml[FPos];
          Inc(FPos);
          LStart := FPos;
          while (FPos <= FLen) and (FHtml[FPos] <> LQuote) do
            Inc(FPos);
          LValue := Copy(FHtml, LStart, FPos - LStart);
          Inc(FPos);
        end
        else
        begin
          LStart := FPos;
          while (FPos <= FLen) and not FHtml[FPos].IsWhiteSpace and (FHtml[FPos] <> '>') do
            Inc(FPos);
          LValue := Copy(FHtml, LStart, FPos - LStart);
        end;
      end;
      LNode.SetAttr(LName, TGenParser.DecodeEntities(LValue, FUnknownEntities));
    end;
  except
    LNode.Free;
    raise;
  end;

  ImplicitClose(LTag);
  // В HTML «/>» у обычных элементов (<div/>) игнорируется; самозакрывающимися
  // бывают только элементы SVG/MathML.
  if LSelfClosing then
    LSelfClosing := IsInArray(LTag, CForeignTags) or (FindOpen('svg', []) <> nil) or
      (FindOpen('math', []) <> nil);
  LNode.FParent := FCurrent;
  FCurrent.AddChild(LNode);

  if IsInArray(LTag, CRawTextTags) then
    SkipRawText(LTag)
  else if not (LSelfClosing or IsInArray(LTag, CVoidTags)) then
    FCurrent := LNode;
end;

procedure TGenDomBuilder.ReadCloseTag;
var
  LStart: Integer;
  LTag: string;
  LOpen: TGenHtmlNode;
begin
  Inc(FPos, 2); // '</'
  LStart := FPos;
  while (FPos <= FLen) and (FHtml[FPos].IsLetterOrDigit or (FHtml[FPos] = '-')) do
    Inc(FPos);
  LTag := LowerCase(Copy(FHtml, LStart, FPos - LStart));
  SkipTo('>');
  if IsInArray(LTag, CVoidTags) then
    Exit;
  // Лишний </li>, </td>, </tr> не должен закрывать элементы за пределами
  // своего списка/таблицы (границы — как в ImplicitClose).
  if LTag = 'li' then
    LOpen := FindOpen(LTag, ['ul', 'ol'])
  else if (LTag = 'td') or (LTag = 'th') then
    LOpen := FindOpen(LTag, ['tr', 'table'])
  else if LTag = 'tr' then
    LOpen := FindOpen(LTag, ['table'])
  else
    LOpen := FindOpen(LTag, []);
  if LOpen = nil then
    Inc(FStrayCloseTags)
  else
    CloseTo(LOpen);
end;

function TGenDomBuilder.Build(const AHtml: string): TGenHtmlNode;
var
  LNext: Char;
begin
  FHtml := AHtml;
  FLen := Length(AHtml);
  FPos := 1;
  FStrayCloseTags := 0;
  FUnknownEntities.Clear;
  Result := TGenHtmlNode.CreateElement(nil, '#root');
  try
    FCurrent := Result;
    while FPos <= FLen do
    begin
      if FHtml[FPos] <> '<' then
      begin
        ReadText;
        Continue;
      end;
      if StartsAt('<!--') then
      begin
        SkipTo('-->');
        Continue;
      end;
      if FPos < FLen then
        LNext := FHtml[FPos + 1]
      else
        LNext := #0;
      if (LNext = '!') or (LNext = '?') then
        SkipTo('>')
      else if LNext = '/' then
        ReadCloseTag
      else if LNext.IsLetter then
        ReadOpenTag
      else
      begin
        // Одиночный '<' — обычный текст.
        FCurrent.AddChild(TGenHtmlNode.CreateText(FCurrent, '<'));
        Inc(FPos);
      end;
    end;
  except
    Result.Free;
    raise;
  end;
end;

{ TGenPageParser }

constructor TGenPageParser.Create(AModel: TGenModel);
begin
  inherited Create;
  FModel := AModel;
  FEntityNodes := TList<TGenHtmlNode>.Create;
  FAnchorTypes := TDictionary<string, string>.Create;
  FPendingReturns := TList<TGenPendingReturn>.Create;
  FPendingExtras := TList<TGenPendingExtra>.Create;
  // «always “photo”», «must be “x”», «must be <em>article</em>».
  FConstRegEx := TRegEx.Create('\b(?:always|must be)\s+(?:“([^”]+)”|"([^"]+)"|' +
    CMarkEmBegin + '([^' + CMarkEmEnd + CMarkLinkBegin + ']+)' + CMarkEmEnd + ')');
  // Глагол «Returns …»/«… returns …»; не «return»/«returned» и не
  // существительное («returns value/code/type»).
  FReturnsRegEx := TRegEx.Create('(?<![\w-])(?:Returns|returns)\b(?!\s+(?:value|values|code|codes|type|types)\b)');
  FReturnedRegEx := TRegEx.Create('\b(?:is|are) returned\b');
end;

destructor TGenPageParser.Destroy;
begin
  FPendingExtras.Free;
  FPendingReturns.Free;
  FAnchorTypes.Free;
  FEntityNodes.Free;
  inherited;
end;

procedure TGenPageParser.Execute(AContent: TGenHtmlNode);
var
  I: Integer;
  LNode: TGenHtmlNode;
  LMatch: TMatch;
begin
  FSection := '';
  FEntityName := '';
  FHeadingCount := 0;
  for I := 0 to AContent.ChildCount - 1 do
  begin
    LNode := AContent.Children[I];
    if LNode.IsText then
      Continue;
    if LNode.IsTag('h3') then
    begin
      FlushEntity;
      FSection := NodeText(LNode);
    end
    else if LNode.IsTag('h4') then
    begin
      FlushEntity;
      HandleHeading4(LNode);
    end
    else if SameStr(FSection, CSectionRecentChanges) then
    begin
      // Версия — первый абзац «Bot API X.Y» в журнале изменений.
      if (FModel.Version = '') and LNode.IsTag('p') then
      begin
        LMatch := TRegEx.Match(NodeText(LNode), '^Bot API (\d+(?:\.\d+)*)$');
        if LMatch.Success then
          FModel.Version := LMatch.Groups[1].Value;
      end;
    end
    else if FEntityName <> '' then
      FEntityNodes.Add(LNode);
  end;
  FlushEntity;
  ResolveReturnTypes;
  ResolveExtraVariants;
end;

procedure TGenPageParser.HandleHeading4(ANode: TGenHtmlNode);
var
  LName, LAnchor: string;
begin
  LName := NodeText(ANode);
  LAnchor := HeadingAnchor(ANode);
  if LAnchor <> '' then
    Inc(FHeadingCount);
  if SameStr(FSection, CSectionRecentChanges) then
  begin
    // Заголовки журнала изменений — даты релизов; первая — текущий релиз.
    if FModel.Date = '' then
      FModel.Date := LName;
    Exit;
  end;
  if not TRegEx.IsMatch(LName, '^[A-Za-z][A-Za-z0-9]*$') then
  begin
    FModel.SkippedHeadings.Add(FSection + ' / ' + LName);
    Exit;
  end;

  if LAnchor = '' then
  begin
    FModel.AddWarning('%s: у заголовка нет якоря <a class="anchor" name="...">, якорь взят из имени', [LName]);
    LAnchor := LowerCase(LName);
  end;

  FEntityName := LName;
  FEntityAnchor := LAnchor;
  FEntityNodes.Clear;
end;

function TGenPageParser.IsSubtypeList(AList: TGenHtmlNode; ANames: TList<string>): Boolean;
var
  I: Integer;
  LItem: TGenHtmlNode;
  LLinks: TList<TGenHtmlNode>;
  LText: string;
begin
  ANames.Clear;
  LLinks := TList<TGenHtmlNode>.Create;
  try
    for I := 0 to AList.ChildCount - 1 do
    begin
      LItem := AList.Children[I];
      if LItem.IsText then
      begin
        if Trim(LItem.Text) <> '' then
          Exit(False);
        Continue;
      end;
      if not LItem.IsTag('li') then
        Exit(False);
      LLinks.Clear;
      LItem.FindAll('a', LLinks);
      if LLinks.Count <> 1 then
        Exit(False);
      LText := NodeInnerText(LItem);
      if not SameStr(LText, NodeText(LLinks[0])) or
        not StartsStr('#', LLinks[0].Attr('href')) or
        not TRegEx.IsMatch(LText, '^[A-Z][A-Za-z0-9]*$') then
        Exit(False);
      ANames.Add(LText);
    end;
  finally
    LLinks.Free;
  end;
  Result := ANames.Count > 0;
end;

procedure TGenPageParser.FlushEntity;
var
  LIsMethod: Boolean;
  LDescription, LAnnotated: TStringList;
  LTable, LNode: TGenHtmlNode;
  LSubtypes: TList<string>;
  LHasSubtypes: Boolean;
  LType: TGenType;
  LMethod: TGenMethod;
  LPending: TGenPendingReturn;
  LPendingExtra: TGenPendingExtra;
  LNested: TList<TGenHtmlNode>;
  LInner: TGenHtmlNode;
  LText, LName, LIntro: string;
begin
  if FEntityName = '' then
    Exit;
  LIsMethod := FEntityName[1].IsLower;
  LTable := nil;
  LHasSubtypes := False;
  LIntro := '';
  LDescription := TStringList.Create;
  LAnnotated := TStringList.Create;
  LSubtypes := TList<string>.Create;
  LNested := TList<TGenHtmlNode>.Create;
  try
    for LNode in FEntityNodes do
    begin
      if LNode.IsTag('table') and LNode.HasClass('table') then
      begin
        if LTable = nil then
          LTable := LNode
        else
          FModel.AddWarning('%s: лишняя таблица после первой — пропущена', [FEntityName]);
        Continue;
      end;
      if (LNode.IsTag('ul') or LNode.IsTag('ol')) and not LIsMethod and
        (LTable = nil) and not LHasSubtypes and IsSubtypeList(LNode, LSubtypes) then
      begin
        LHasSubtypes := True;
        // Абзацы перед списком — источник дополнительных вариантов («either a String…»).
        LIntro := LAnnotated.Text;
        Continue;
      end;
      if LNode.IsTag('table') then
        FModel.AddWarning('%s: таблица без class="table" — добавлена в описание', [FEntityName]);
      LText := NodeText(LNode);
      if LText <> '' then
      begin
        LDescription.Add(LText);
        LAnnotated.Add(NodeText(LNode, TGenTextMode.Annotated));
      end;
    end;

    // Среди прямых потомков таблицы нет — ищем вложенную (разметка изменилась
    // или лишний/недостающий тег сместил её внутрь другого элемента).
    if LTable = nil then
      for LNode in FEntityNodes do
      begin
        LNested.Clear;
        LNode.FindAll('table', LNested);
        for LInner in LNested do
          if LInner.HasClass('table') then
          begin
            LTable := LInner;
            Break;
          end;
        if LTable <> nil then
        begin
          FModel.AddWarning('%s: таблица найдена не на верхнем уровне (внутри <%s>) — использована',
            [FEntityName, LNode.Tag]);
          Break;
        end;
      end;

    if LIsMethod then
    begin
      LMethod := FModel.AddMethod(TGenMethod.Create(FEntityName, FEntityAnchor, FSection));
      if LMethod <> nil then
      begin
        LMethod.Description := Trim(StringReplace(LDescription.Text, sLineBreak, #10, [rfReplaceAll]));
        if LTable <> nil then
          ParseTable(LTable, nil, LMethod)
        else if not ContainsText(LMethod.Description, 'no parameters') then
          FModel.AddWarning('%s: нет таблицы параметров и нет фразы «Requires no parameters»', [FEntityName]);
        LPending.Method := LMethod;
        LPending.Annotated := LAnnotated.Text;
        FPendingReturns.Add(LPending);
      end;
    end
    else
    begin
      LType := FModel.AddType(TGenType.Create(FEntityName, FEntityAnchor, FSection));
      if LType <> nil then
      begin
        FAnchorTypes.AddOrSetValue(LowerCase(FEntityAnchor), LType.Name);
        LType.Description := Trim(StringReplace(LDescription.Text, sLineBreak, #10, [rfReplaceAll]));
        if LTable <> nil then
          ParseTable(LTable, LType, nil);
        for LName in LSubtypes do
          LType.Subtypes.Add(LName);
        if LHasSubtypes and not TRegEx.IsMatch(LType.Description,
          '\bone of\b|\bfollowing\b|\bsupported\b', [roIgnoreCase]) then
          FModel.AddWarning('%s: варианты взяты из списка без фразы «one of»/«following»', [FEntityName]);
        if LHasSubtypes then
        begin
          LPendingExtra.UnionType := LType;
          LPendingExtra.Annotated := LIntro;
          FPendingExtras.Add(LPendingExtra);
        end;
        // Тип без полей и вариантов допустим, только если спецификация прямо
        // называет его заглушкой; InputFile — особый тип (содержимое файла).
        if (LType.Fields.Count = 0) and not LHasSubtypes and
          not SameStr(LType.Name, 'InputFile') and
          not TRegEx.IsMatch(LType.Description, '\bholds no information\b|\bplaceholder\b',
          [roIgnoreCase]) then
          FModel.AddWarning('%s: нет ни полей, ни вариантов, а в описании нет «holds no information»/' +
            '«placeholder» — таблица полей не распознана?', [FEntityName]);
      end;
    end;
  finally
    LNested.Free;
    LSubtypes.Free;
    LAnnotated.Free;
    LDescription.Free;
    FEntityName := '';
    FEntityAnchor := '';
    FEntityNodes.Clear;
  end;
end;

procedure TGenPageParser.ParseTable(ATable: TGenHtmlNode; AType: TGenType;
  AMethod: TGenMethod);
var
  LRows, LCells: TList<TGenHtmlNode>;
  LRow: TGenHtmlNode;
  LHeaders: string;
  LIsFields, LIsParams, LRequired: Boolean;
  LOwner, LName, LRequiredText, LDescription: string;
  LTypeRef: TGenTypeRef;
  LField: TGenField;
  LMatch: TMatch;
  I, LRowNo: Integer;
begin
  if AType <> nil then
    LOwner := AType.Name
  else
    LOwner := AMethod.Name;
  LRows := TList<TGenHtmlNode>.Create;
  LCells := TList<TGenHtmlNode>.Create;
  try
    ATable.FindAll('tr', LRows);
    LHeaders := '';
    LIsFields := False;
    LIsParams := False;
    LRowNo := 0;
    for LRow in LRows do
    begin
      LCells.Clear;
      for I := 0 to LRow.ChildCount - 1 do
        if LRow.Children[I].IsTag('td') or LRow.Children[I].IsTag('th') then
          LCells.Add(LRow.Children[I]);
      if LCells.Count = 0 then
        Continue;

      if LCells[0].IsTag('th') then
      begin
        LHeaders := '';
        for I := 0 to LCells.Count - 1 do
        begin
          if I > 0 then
            LHeaders := LHeaders + '|';
          LHeaders := LHeaders + NodeText(LCells[I]);
        end;
        LIsFields := SameText(LHeaders, 'Field|Type|Description');
        LIsParams := SameText(LHeaders, 'Parameter|Type|Required|Description');
        if not (LIsFields or LIsParams) then
          FModel.AddWarning('%s: неизвестные заголовки таблицы «%s» — таблица пропущена', [LOwner, LHeaders])
        else if LIsFields and (AType = nil) then
          FModel.AddWarning('%s: у метода таблица полей (Field|Type|Description) — пропущена', [LOwner])
        else if LIsParams and (AMethod = nil) then
          FModel.AddWarning('%s: у типа таблица параметров (Parameter|…|Required) — пропущена', [LOwner]);
        Continue;
      end;

      Inc(LRowNo);
      if LIsFields and (AType <> nil) then
      begin
        if LCells.Count <> 3 then
        begin
          FModel.AddWarning('%s: строка %d таблицы полей содержит %d ячеек вместо 3 — пропущена',
            [LOwner, LRowNo, LCells.Count]);
          Continue;
        end;
        LName := NodeText(LCells[0]);
        LDescription := NodeText(LCells[2]);
        LTypeRef := TGenTypeRef.Parse(NodeText(LCells[1]));
        LField := AType.AddField(TGenField.Create(LName, LTypeRef,
          not TRegEx.IsMatch(LDescription, '^Optional\b'), LDescription));
        if LTypeRef.Kind = TGenTypeKind.Str then
        begin
          LMatch := FConstRegEx.Match(NodeText(LCells[2], TGenTextMode.Annotated));
          if LMatch.Success then
            for I := 1 to LMatch.Groups.Count - 1 do
              if LMatch.Groups[I].Success and (Trim(StripMarkers(LMatch.Groups[I].Value)) <> '') then
              begin
                // Внутри кавычек может оказаться <em>/ссылка — маркеры убираем.
                LField.ConstValue := Trim(StripMarkers(LMatch.Groups[I].Value));
                Break;
              end;
        end;
      end
      else if LIsParams and (AMethod <> nil) then
      begin
        if LCells.Count <> 4 then
        begin
          FModel.AddWarning('%s: строка %d таблицы параметров содержит %d ячеек вместо 4 — пропущена',
            [LOwner, LRowNo, LCells.Count]);
          Continue;
        end;
        LName := NodeText(LCells[0]);
        LRequiredText := NodeText(LCells[2]);
        if SameText(LRequiredText, 'Yes') then
          LRequired := True
        else if SameText(LRequiredText, 'Optional') then
          LRequired := False
        else
        begin
          FModel.AddWarning('%s.%s: неизвестное значение Required «%s» — считаем Optional',
            [LOwner, LName, LRequiredText]);
          LRequired := False;
        end;
        AMethod.AddParam(TGenParam.Create(LName, TGenTypeRef.Parse(NodeText(LCells[1])),
          LRequired, NodeText(LCells[3])));
      end;
    end;
    if LHeaders = '' then
      FModel.AddWarning('%s: таблица без строки заголовков — пропущена', [LOwner]);
  finally
    LCells.Free;
    LRows.Free;
  end;
end;

procedure TGenPageParser.ScanTypeTokens(const ASentence: string; AFrom, ATo: Integer;
  APlainPrimitives: Boolean; ATokens: TObjectList<TGenTypeRef>);
var
  LToken: TGenTypeRef;
  I, LTextPos, LEndPos, LSegmentStart, LTokenStart: Integer;
  LAnchor, LText, LName: string;
begin
  if ATo > Length(ASentence) then
    ATo := Length(ASentence);
  I := AFrom;
  LSegmentStart := AFrom;
  while I <= ATo do
  begin
    LToken := nil;
    LTokenStart := I;
    if ASentence[I] = CMarkLinkBegin then
    begin
      LTextPos := Pos(CMarkLinkText, ASentence, I);
      LEndPos := Pos(CMarkLinkEnd, ASentence, I);
      if (LTextPos = 0) or (LEndPos = 0) then
        Break;
      LAnchor := Copy(ASentence, I + 1, LTextPos - I - 1);
      if FAnchorTypes.TryGetValue(LAnchor, LName) then
        LToken := TGenTypeRef.Create(TGenTypeKind.Named, LName);
      I := LEndPos + 1;
    end
    else if ASentence[I] = CMarkEmBegin then
    begin
      LEndPos := Pos(CMarkEmEnd, ASentence, I);
      if LEndPos = 0 then
        Break;
      LText := Trim(StripMarkers(Copy(ASentence, I + 1, LEndPos - I - 1)));
      LToken := PrimitiveRef(LText, False);
      I := LEndPos + 1;
    end
    else if APlainPrimitives and ASentence[I].IsLetter and
      ((I = 1) or not ASentence[I - 1].IsLetterOrDigit) then
    begin
      // Слово обычного текста: «a String for plain text».
      LEndPos := I;
      while (LEndPos <= ATo) and ASentence[LEndPos].IsLetterOrDigit do
        Inc(LEndPos);
      LToken := PrimitiveRef(Copy(ASentence, I, LEndPos - I), True);
      I := LEndPos;
    end
    else
      Inc(I);

    if LToken = nil then
      Continue;
    // «an Array of <Update> objects» — между предыдущим токеном и этим есть «array of».
    if ContainsText(StripMarkers(Copy(ASentence, LSegmentStart, LTokenStart - LSegmentStart)),
      'array of') then
      LToken := TGenTypeRef.CreateArray(LToken);
    LSegmentStart := I;
    ATokens.Add(LToken);
  end;
end;

function TGenPageParser.TokensToTypeRef(ATokens: TObjectList<TGenTypeRef>): TGenTypeRef;
var
  LToken: TGenTypeRef;
  I: Integer;
  LDuplicate: Boolean;
begin
  if ATokens.Count = 0 then
    Exit(nil);
  if ATokens.Count = 1 then
    Exit(ATokens.Extract(ATokens[0]));
  Result := TGenTypeRef.Create(TGenTypeKind.Union);
  try
    while ATokens.Count > 0 do
    begin
      LToken := ATokens.Extract(ATokens[0]);
      LDuplicate := False;
      for I := 0 to Result.VariantCount - 1 do
        if SameStr(Result.Variants[I].ToString, LToken.ToString) then
          LDuplicate := True;
      if LDuplicate then
        LToken.Free
      else
        Result.AddVariant(LToken);
    end;
    if Result.VariantCount = 1 then
    begin
      LToken := Result.Variants[0].Clone;
      Result.Free;
      Result := LToken;
    end;
  except
    Result.Free;
    raise;
  end;
end;

function TGenPageParser.ScanReturnTokens(const ASentence: string; AFrom: Integer): TGenTypeRef;
var
  LTokens: TObjectList<TGenTypeRef>;
begin
  LTokens := TObjectList<TGenTypeRef>.Create(True);
  try
    ScanTypeTokens(ASentence, AFrom, Length(ASentence), False, LTokens);
    Result := TokensToTypeRef(LTokens);
  finally
    LTokens.Free;
  end;
end;

function TGenPageParser.ScanReturnedClauses(const ASentence: string): TGenTypeRef;
var
  LTokens: TObjectList<TGenTypeRef>;
  LMatches: TMatchCollection;
  I: Integer;
begin
  LTokens := TObjectList<TGenTypeRef>.Create(True);
  try
    // «…, the edited Message is returned, otherwise True is returned»:
    // каждое «is returned» относится только к своему фрагменту.
    LMatches := FReturnedRegEx.Matches(ASentence);
    for I := 0 to LMatches.Count - 1 do
      ScanTypeTokens(ASentence, ClauseStart(ASentence, LMatches[I].Index),
        LMatches[I].Index - 1, False, LTokens);
    Result := TokensToTypeRef(LTokens);
  finally
    LTokens.Free;
  end;
end;

function TGenPageParser.DetectReturnType(const AAnnotated: string;
  out ASentence: string): TGenTypeRef;
var
  LSentences: TStringList;
  LSb: TStringBuilder;
  LSentence: string;
  LMatch: TMatch;
  I, LDepth: Integer;
  LCh: Char;
  LBreak: Boolean;
begin
  Result := nil;
  ASentence := '';
  LSentences := TStringList.Create;
  LSb := TStringBuilder.Create;
  try
    // Деление на предложения: по '.'/'!'/'?' + пробел и по переводу строки,
    // не внутри маркеров и не после сокращений вида «e.g.»/«i.e.».
    LDepth := 0;
    for I := 1 to Length(AAnnotated) do
    begin
      LCh := AAnnotated[I];
      case LCh of
        CMarkLinkBegin, CMarkEmBegin: Inc(LDepth);
        CMarkLinkEnd, CMarkEmEnd: if LDepth > 0 then Dec(LDepth);
      end;
      if (LCh = #10) or (LCh = #13) then
      begin
        if LDepth = 0 then
        begin
          LSentences.Add(LSb.ToString);
          LSb.Clear;
        end
        else
          LSb.Append(' ');
        Continue;
      end;
      LSb.Append(LCh);
      LBreak := (LDepth = 0) and CharInSet(LCh, ['.', '!', '?']) and
        ((I = Length(AAnnotated)) or AAnnotated[I + 1].IsWhiteSpace);
      if LBreak and (LCh = '.') and (I >= 3) and (AAnnotated[I - 2] = '.') then
        LBreak := False; // «e.g.», «i.e.»
      if LBreak then
      begin
        LSentences.Add(LSb.ToString);
        LSb.Clear;
      end;
    end;
    if LSb.Length > 0 then
      LSentences.Add(LSb.ToString);

    for LSentence in LSentences do
    begin
      // «Returns X» — тип после глагола; иначе «X is returned» — тип перед ним.
      LMatch := FReturnsRegEx.Match(LSentence);
      if LMatch.Success then
        Result := ScanReturnTokens(LSentence, LMatch.Index + LMatch.Length);
      if Result = nil then
        Result := ScanReturnedClauses(LSentence);
      if Result <> nil then
      begin
        ASentence := Trim(StripMarkers(LSentence));
        Exit;
      end;
    end;
  finally
    LSb.Free;
    LSentences.Free;
  end;
end;

procedure TGenPageParser.ResolveReturnTypes;
var
  LPending: TGenPendingReturn;
  LSentence: string;
  LRef: TGenTypeRef;
begin
  for LPending in FPendingReturns do
  begin
    LRef := DetectReturnType(LPending.Annotated, LSentence);
    if LRef <> nil then
    begin
      LRef.Source := LSentence;
      LPending.Method.ReturnType := LRef;
      LPending.Method.ReturnSentence := LSentence;
    end;
  end;
end;

procedure TGenPageParser.ResolveExtraVariants;
var
  LPending: TGenPendingExtra;
  LType: TGenType;
  LTokens: TObjectList<TGenTypeRef>;
  LToken, LExisting: TGenTypeRef;
  LMatch: TMatch;
  LPlain: string;
  LDuplicate, LHasPrimitive, LHasArray: Boolean;
begin
  LTokens := TObjectList<TGenTypeRef>.Create(True);
  try
    for LPending in FPendingExtras do
    begin
      LType := LPending.UnionType;
      LTokens.Clear;
      // «it can be either a String for plain text, an Array of RichText, or any
      // of the following types:» — варианты между «either» и «… of the following».
      LMatch := TRegEx.Match(LPending.Annotated,
        '\beither\b(.*?)\b(?:any|one) of the following\b', [roIgnoreCase]);
      if LMatch.Success then
        ScanTypeTokens(LPending.Annotated, LMatch.Groups[1].Index,
          LMatch.Groups[1].Index + LMatch.Groups[1].Length - 1, True, LTokens);

      while LTokens.Count > 0 do
      begin
        LToken := LTokens.Extract(LTokens[0]);
        // Объекты из списка вариантов и повторы не дублируем.
        LDuplicate := (LToken.Kind = TGenTypeKind.Named) and LType.Subtypes.Contains(LToken.Name);
        for LExisting in LType.ExtraVariants do
          if SameStr(LExisting.ToString, LToken.ToString) then
            LDuplicate := True;
        if LDuplicate then
          LToken.Free
        else
          LType.ExtraVariants.Add(LToken);
      end;

      // Описание упоминает String/Array of, а соответствующий вариант не извлечён.
      LHasPrimitive := False;
      LHasArray := False;
      for LExisting in LType.ExtraVariants do
        if LExisting.IsPrimitive then
          LHasPrimitive := True
        else if LExisting.Kind = TGenTypeKind.ArrayOf then
          LHasArray := True;
      LPlain := StripMarkers(LPending.Annotated);
      if (TRegEx.IsMatch(LPlain, '\bString\b') and not LHasPrimitive) or
        (TRegEx.IsMatch(LPlain, '\bArray of\b', [roIgnoreCase]) and not LHasArray) then
        FModel.AddWarning('%s: в описании вариантов упомянуты «String»/«Array of», но ' +
          'дополнительные (не объектные) варианты не извлечены', [LType.Name]);
    end;
  finally
    LTokens.Free;
  end;
end;

{ TGenParser }

class function TGenParser.DecodeEntities(const AText: string; AUnknown: TStrings): string;

  function ResolveNamed(const AName: string; out AValue: string): Boolean;
  const
    CNames: array[0..27] of string = ('amp', 'lt', 'gt', 'quot', 'apos', 'nbsp',
      'mdash', 'ndash', 'hellip', 'laquo', 'raquo', 'lsquo', 'rsquo', 'ldquo',
      'rdquo', 'copy', 'reg', 'trade', 'times', 'rarr', 'larr', 'middot', 'bull',
      'deg', 'shy', 'thinsp', 'minus', 'sbquo');
    CValues: array[0..27] of string = ('&', '<', '>', '"', '''', ' ',
      #$2014, #$2013, #$2026, #$00AB, #$00BB, #$2018, #$2019, #$201C,
      #$201D, #$00A9, #$00AE, #$2122, #$00D7, #$2192, #$2190, #$00B7, #$2022,
      #$00B0, '', ' ', #$2212, #$201A);
  var
    I: Integer;
  begin
    for I := Low(CNames) to High(CNames) do
      if SameStr(CNames[I], AName) then
      begin
        AValue := CValues[I];
        Exit(True);
      end;
    Result := False;
  end;

  function ResolveNumeric(const ABody: string; out AValue: string): Boolean;
  var
    LCode: Integer;
  begin
    // Только &#ddd; и &#xhhh;. TryStrToInt понимает и «0x…»/«$…», поэтому
    // состав цифр проверяется явно: &#0x41; — не сущность.
    LCode := 0;
    if (Length(ABody) > 1) and CharInSet(ABody[1], ['x', 'X']) then
      Result := (Length(ABody) <= 7) and
        TRegEx.IsMatch(Copy(ABody, 2, MaxInt), '^[0-9A-Fa-f]+$') and
        TryStrToInt('$' + Copy(ABody, 2, MaxInt), LCode)
    else
      Result := (Length(ABody) <= 7) and TRegEx.IsMatch(ABody, '^[0-9]+$') and
        TryStrToInt(ABody, LCode);
    Result := Result and (LCode > 0) and (LCode <= $10FFFF) and
      not ((LCode >= $D800) and (LCode <= $DFFF));
    if Result then
    begin
      if LCode = $A0 then
        AValue := ' '
      else
        AValue := Char.ConvertFromUtf32(UCS4Char(LCode));
    end;
  end;

var
  LSb: TStringBuilder;
  I, J: Integer;
  LName, LValue: string;
  LOk: Boolean;
begin
  if Pos('&', AText) = 0 then
    Exit(AText);
  LSb := TStringBuilder.Create(Length(AText));
  try
    I := 1;
    while I <= Length(AText) do
    begin
      if AText[I] <> '&' then
      begin
        LSb.Append(AText[I]);
        Inc(I);
        Continue;
      end;
      J := I + 1;
      while (J <= Length(AText)) and (J - I <= 32) and
        (AText[J].IsLetterOrDigit or (AText[J] = '#')) do
        Inc(J);
      LOk := False;
      if (J <= Length(AText)) and (AText[J] = ';') and (J > I + 1) then
      begin
        LName := Copy(AText, I + 1, J - I - 1);
        if LName[1] = '#' then
          LOk := ResolveNumeric(Copy(LName, 2, MaxInt), LValue)
        else
          LOk := ResolveNamed(LName, LValue);
        if not LOk and (AUnknown <> nil) then
          AUnknown.Add('&' + LName + ';');
      end;
      if LOk then
      begin
        LSb.Append(LValue);
        I := J + 1;
      end
      else
      begin
        LSb.Append('&');
        Inc(I);
      end;
    end;
    Result := LSb.ToString;
  finally
    LSb.Free;
  end;
end;

class function TGenParser.ExtractVersion(const AHtml: string): string;
var
  LMatch: TMatch;
begin
  LMatch := TRegEx.Match(AHtml, '<strong>\s*Bot API (\d+(?:\.\d+)+)\s*</strong>');
  if not LMatch.Success then
    LMatch := TRegEx.Match(AHtml, '\bBot API (\d+\.\d+(?:\.\d+)?)\b');
  if LMatch.Success then
    Result := LMatch.Groups[1].Value
  else
    Result := '';
end;

class function TGenParser.DecodeUtf8(const ABytes: TBytes; const ASource: string): string;
var
  LOffset: Integer;
begin
  LOffset := 0;
  if (Length(ABytes) >= 3) and (ABytes[0] = $EF) and (ABytes[1] = $BB) and (ABytes[2] = $BF) then
    LOffset := 3;
  try
    // TEncoding.UTF8 создан с MB_ERR_INVALID_CHARS: ошибка декодирования —
    // EEncodingError с невнятным текстом; переводим её в понятную.
    Result := TEncoding.UTF8.GetString(ABytes, LOffset, Length(ABytes) - LOffset);
  except
    on E: EEncodingError do
      raise EGenParseError.CreateFmt('%s: содержимое не является корректным UTF-8 (%s)',
        [ASource, E.Message]);
  end;
end;

class procedure TGenParser.ParseFile(const AFileName: string; AModel: TGenModel);
begin
  ParseHtml(DecodeUtf8(TFile.ReadAllBytes(AFileName), AFileName), AModel);
  AModel.SourceFile := AFileName;
end;

class procedure TGenParser.ParseHtml(const AHtml: string; AModel: TGenModel);
var
  LBuilder: TGenDomBuilder;
  LRoot, LContent, LHeading: TGenHtmlNode;
  LPage: TGenPageParser;
  LHeadings: TList<TGenHtmlNode>;
  LAnchored, LHandled: Integer;
begin
  AModel.Clear;
  LBuilder := TGenDomBuilder.Create;
  try
    LRoot := LBuilder.Build(AHtml);
    try
      if LBuilder.UnknownEntities.Count > 0 then
        AModel.AddWarning('HTML: неизвестные сущности оставлены как есть: %s',
          [String.Join(' ', LBuilder.UnknownEntities.ToStringArray)]);
      LContent := LRoot.FindById('dev_page_content');
      if LContent = nil then
        raise EGenParseError.Create('HTML: не найден <div id="dev_page_content"> — разбор невозможен');
      LPage := TGenPageParser.Create(AModel);
      try
        LPage.Execute(LContent);
        LHandled := LPage.HeadingCount;
      finally
        LPage.Free;
      end;

      // Все h4 с якорем должны быть прямыми потомками контента; иначе лишний
      // или недостающий тег увёл часть сущностей внутрь другого элемента.
      LAnchored := 0;
      LHeadings := TList<TGenHtmlNode>.Create;
      try
        LContent.FindAll('h4', LHeadings);
        for LHeading in LHeadings do
          if HeadingAnchor(LHeading) <> '' then
            Inc(LAnchored);
      finally
        LHeadings.Free;
      end;
      if LAnchored <> LHandled then
        AModel.AddWarning('HTML: заголовков h4 с якорем %d, обработано и пропущено %d — ' +
          '%d вложены в другие элементы (ошибка разметки?)', [LAnchored, LHandled, LAnchored - LHandled]);
      if AModel.Version = '' then
      begin
        AModel.Version := ExtractVersion(AHtml);
        AModel.AddWarning('Версия не найдена в «Recent changes», взята поиском по странице: «%s»',
          [AModel.Version]);
      end;
      if AModel.Date = '' then
        AModel.AddWarning('Дата релиза не найдена в «Recent changes»');
      if (AModel.Types.Count = 0) or (AModel.Methods.Count = 0) then
        raise EGenParseError.CreateFmt('Не найдено ни одного типа или метода (типов %d, методов %d) — ' +
          'разметка страницы изменилась?', [AModel.Types.Count, AModel.Methods.Count]);
      AModel.Link;
    finally
      LRoot.Free;
    end;
  finally
    LBuilder.Free;
  end;
end;

end.
