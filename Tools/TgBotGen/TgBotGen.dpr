program TgBotGen;

{
  TgBotGen — кодогенератор библиотеки TgBot (фаза 2: загрузка спецификации,
  разбор HTML, модель, дамп; фаза 3: анализ модели и генерация .inc).

  Команды:
    --fetch [--out <папка>] [--force] скачать https://core.telegram.org/bots/api
                                      в <папка>\api-<версия>.html (по умолчанию ..\Spec)
    --parse <file.html> [--verbose]   разобрать и вывести статистику
    --dump <file.html> [<out.json>]   сохранить модель в JSON
                                      (по умолчанию рядом: model-<версия>.json)
    --returns <file.html> [<out.json>] сохранить эталон типов результата
                                      (по умолчанию рядом: returns-<версия>.json)
    --analyze <file.html>             отчёт анализа модели (направления,
                                      объединения, файлы, Int64, конфликты имён)
    --gen <file.html> --out <папка> [--only <список>]
                                      сгенерировать .inc-файлы; --only — типы
                                      и методы через запятую (с зависимостями)
  --parse/--dump сверяют типы результата с returns-<версия>.json рядом с HTML
  (если он есть); --strict — код 1 при предупреждениях, нераспознанных
  ссылках или методах с неизвестным типом результата. Опции — в любой позиции.
  --analyze/--gen читают переопределения из overrides.json рядом с HTML
  (или из файла --overrides <файл>).

  Код возврата: 0 — успех, 1 — ошибка, 2 — неверные параметры.
}

{$APPTYPE CONSOLE}

uses
  System.SysUtils,
  System.Classes,
  System.StrUtils,
  System.IOUtils,
  System.RegularExpressions,
  System.Net.HttpClient,
  Winapi.Windows,
  TgBotGen.Model in 'TgBotGen.Model.pas',
  TgBotGen.Parser in 'TgBotGen.Parser.pas',
  TgBotGen.Analysis in 'TgBotGen.Analysis.pas',
  TgBotGen.Emitter in 'TgBotGen.Emitter.pas';

const
  CSpecUrl = 'https://core.telegram.org/bots/api';
  CUserAgent = 'TgBotGen/0.2 (Delphi)';
  CExitOk = 0;
  CExitError = 1;
  CExitUsage = 2;
  // Таймауты загрузки спецификации, мс.
  CConnectTimeout = 15000;
  CResponseTimeout = 60000;

type
  /// <summary>Разобранная командная строка.</summary>
  TGenCmdLine = record
    /// <summary>Команда в нижнем регистре ('--parse') или ''.</summary>
    Command: string;
    /// <summary>Позиционные аргументы команды (без опций).</summary>
    Args: TArray<string>;
    /// <summary>Значение --out ('' — не задано).</summary>
    OutDir: string;
    /// <summary>Значение --only ('' — генерировать всё).</summary>
    Only: string;
    /// <summary>Значение --overrides ('' — overrides.json рядом с HTML).</summary>
    OverridesFile: string;
    Verbose: Boolean;
    StrictMode: Boolean;
    Force: Boolean;
  end;

procedure PrintUsage;
begin
  Writeln('TgBotGen — генератор кода TgBot по спецификации Telegram Bot API');
  Writeln;
  Writeln('Использование:');
  Writeln('  TgBotGen --fetch [--out <папка>] [--force]');
  Writeln('      Скачать ', CSpecUrl, ' и сохранить в <папка>\api-<версия>.html');
  Writeln('      (по умолчанию — папка Spec рядом с Bin). Если файл этой версии уже есть');
  Writeln('      и отличается, новый сохраняется как api-<версия>-<ггггммдд>.html;');
  Writeln('      --force — перезаписать.');
  Writeln('  TgBotGen --parse <file.html> [--verbose] [--strict]');
  Writeln('      Разобрать страницу и вывести статистику; --verbose — все методы');
  Writeln('      с типами результата.');
  Writeln('  TgBotGen --dump <file.html> [<out.json>] [--strict]');
  Writeln('      Сохранить модель в JSON (по умолчанию model-<версия>.json рядом с HTML).');
  Writeln('  TgBotGen --returns <file.html> [<out.json>]');
  Writeln('      Сохранить эталон типов результата методов (по умолчанию');
  Writeln('      returns-<версия>.json рядом с HTML). --parse/--dump сверяются с ним.');
  Writeln('  TgBotGen --analyze <file.html> [--overrides <файл>] [--strict]');
  Writeln('      Отчёт анализа: направления типов, полиморфные типы и объединения,');
  Writeln('      файлы, Int64, переименования, конфликты имён.');
  Writeln('  TgBotGen --gen <file.html> --out <папка> [--only <список>] [--overrides <файл>]');
  Writeln('      Сгенерировать Gen.*.inc в <папка>. --only Message,sendMessage,... —');
  Writeln('      только перечисленные типы и методы с транзитивными зависимостями.');
  Writeln('  По умолчанию переопределения — overrides.json рядом с HTML.');
  Writeln;
  Writeln('  --strict: код возврата 1, если есть предупреждения, нераспознанные ссылки');
  Writeln('  на типы или методы с неизвестным типом результата.');
end;

/// <summary>Папка Spec по умолчанию: ..\Spec относительно exe (exe лежит в Bin).</summary>
function DefaultSpecDir: string;
begin
  Result := ExpandFileName(TPath.Combine(ExtractFilePath(ParamStr(0)), '..\Spec'));
end;

/// <summary>
///   Разбирает командную строку: опции (--verbose, -v, --strict, --force,
///   --out &lt;папка&gt;) допускаются в любой позиции. Ошибка — EArgumentException.
/// </summary>
function ParseCommandLine: TGenCmdLine;
var
  I: Integer;
  LArg: string;
begin
  Result := Default(TGenCmdLine);
  I := 1;
  while I <= ParamCount do
  begin
    LArg := ParamStr(I);
    if SameText(LArg, '--verbose') or SameText(LArg, '-v') then
      Result.Verbose := True
    else if SameText(LArg, '--strict') then
      Result.StrictMode := True
    else if SameText(LArg, '--force') then
      Result.Force := True
    else if SameText(LArg, '--out') then
    begin
      if (I = ParamCount) or ParamStr(I + 1).StartsWith('-') then
        raise EArgumentException.Create('После --out нужно указать папку');
      Inc(I);
      Result.OutDir := ParamStr(I);
    end
    else if SameText(LArg, '--only') then
    begin
      if (I = ParamCount) or ParamStr(I + 1).StartsWith('-') then
        raise EArgumentException.Create('После --only нужно указать список типов и методов');
      Inc(I);
      Result.Only := ParamStr(I);
    end
    else if SameText(LArg, '--overrides') then
    begin
      if (I = ParamCount) or ParamStr(I + 1).StartsWith('-') then
        raise EArgumentException.Create('После --overrides нужно указать файл');
      Inc(I);
      Result.OverridesFile := ParamStr(I);
    end
    else if MatchText(LArg, ['--fetch', '--parse', '--dump', '--returns', '--analyze', '--gen']) then
    begin
      if Result.Command <> '' then
        raise EArgumentException.CreateFmt('Указано несколько команд: %s и %s', [Result.Command, LArg]);
      Result.Command := LowerCase(LArg);
    end
    else if LArg.StartsWith('-') then
      raise EArgumentException.CreateFmt('Неизвестная опция: %s', [LArg])
    else
      Result.Args := Result.Args + [LArg];
    Inc(I);
  end;

  if (Result.Command = '') and (Length(Result.Args) > 0) then
    raise EArgumentException.CreateFmt('Не указана команда для аргумента «%s»', [Result.Args[0]]);
  if (Result.Command <> '--fetch') and Result.Force then
    raise EArgumentException.Create('Опция --force относится только к --fetch');
  if not MatchText(Result.Command, ['--fetch', '--gen']) and (Result.OutDir <> '') then
    raise EArgumentException.Create('Опция --out относится только к --fetch и --gen');
  if (Result.Command <> '--gen') and (Result.Only <> '') then
    raise EArgumentException.Create('Опция --only относится только к --gen');
  if not MatchText(Result.Command, ['--analyze', '--gen']) and (Result.OverridesFile <> '') then
    raise EArgumentException.Create('Опция --overrides относится только к --analyze и --gen');
  if (Result.Command = '--gen') and (Result.OutDir = '') then
    raise EArgumentException.Create('Для --gen нужно указать папку --out');
  if MatchText(Result.Command, ['--analyze', '--gen']) and (Length(Result.Args) > 1) then
    raise EArgumentException.CreateFmt('Лишний аргумент %s: «%s»', [Result.Command, Result.Args[1]]);
  if (Result.Command = '--fetch') and (Length(Result.Args) > 0) then
    raise EArgumentException.CreateFmt('Лишний аргумент --fetch: «%s» (папка задаётся через --out)',
      [Result.Args[0]]);
  if (Result.Command = '--parse') and (Length(Result.Args) > 1) then
    raise EArgumentException.CreateFmt('Лишний аргумент --parse: «%s»', [Result.Args[1]]);
  if MatchText(Result.Command, ['--dump', '--returns']) and (Length(Result.Args) > 2) then
    raise EArgumentException.CreateFmt('Лишний аргумент %s: «%s»', [Result.Command, Result.Args[2]]);
end;

/// <summary>Версия из имени файла api-&lt;версия&gt;[-ггггммдд].html или ''.</summary>
function VersionFromFileName(const AFileName: string): string;
var
  LMatch: TMatch;
begin
  LMatch := TRegEx.Match(ExtractFileName(AFileName), '^api-(\d+(?:\.\d+)*)(?:-\d{8})?\.html?$',
    [roIgnoreCase]);
  if LMatch.Success then
    Result := LMatch.Groups[1].Value
  else
    Result := '';
end;

/// <summary>
///   Сохранённая спецификация AOld совпадает с загруженной (ANew, ANewText —
///   её байты и текст): байты равны или различаются только служебным
///   комментарием «&lt;!-- page generated in N ms --&gt;», который сервер
///   меняет при каждой загрузке.
/// </summary>
function SameSpec(const AOld, ANew: TBytes; const ANewText: string): Boolean;
const
  CVolatile = '<!--\s*page generated in [\d.]+\s*ms\s*-->';
var
  LOldText: string;
begin
  if (Length(AOld) = Length(ANew)) and
    ((Length(AOld) = 0) or CompareMem(@AOld[0], @ANew[0], Length(AOld))) then
    Exit(True);
  try
    LOldText := TGenParser.DecodeUtf8(AOld, '');
  except
    on EGenParseError do
      Exit(False);
  end;
  Result := SameStr(TRegEx.Replace(LOldText, CVolatile, ''), TRegEx.Replace(ANewText, CVolatile, ''));
end;

function DoFetch(const ACmd: TGenCmdLine): Integer;
var
  LClient: THTTPClient;
  LStream: TBytesStream;
  LResponse: IHTTPResponse;
  LModel: TGenModel;
  LBytes: TBytes;
  LHtml, LVersion, LPageVersion, LDir, LFileName: string;
begin
  if ACmd.OutDir = '' then
    LDir := DefaultSpecDir
  else
    LDir := ExpandFileName(ACmd.OutDir);
  Writeln('Загрузка ', CSpecUrl, ' ...');
  LClient := THTTPClient.Create;
  try
    LClient.UserAgent := CUserAgent;
    LClient.ConnectionTimeout := CConnectTimeout;
    LClient.ResponseTimeout := CResponseTimeout;
    LStream := TBytesStream.Create;
    try
      LResponse := LClient.Get(CSpecUrl, LStream);
      if LResponse.StatusCode <> 200 then
        raise Exception.CreateFmt('HTTP %d %s', [LResponse.StatusCode, LResponse.StatusText]);
      LResponse := nil;
      LBytes := Copy(LStream.Bytes, 0, LStream.Size);
    finally
      LStream.Free;
    end;
  finally
    LClient.Free;
  end;

  // Перед сохранением страница должна разбираться в непустую модель
  // (ParseHtml бросает EGenParseError, если нет контента, типов или методов).
  LHtml := TGenParser.DecodeUtf8(LBytes, CSpecUrl);
  LModel := TGenModel.Create;
  try
    TGenParser.ParseHtml(LHtml, LModel);
    LVersion := LModel.Version;
    if LVersion = '' then
      raise Exception.Create('На странице не найдена версия «Bot API X.Y» — страница изменилась?');
    LPageVersion := TGenParser.ExtractVersion(LHtml);
    if not SameStr(LPageVersion, LVersion) then
      Writeln('Внимание: версия в «Recent changes» ', LVersion, ', а первая на странице — ',
        LPageVersion, '; используется ', LVersion);
    Writeln('Bot API ', LVersion, ': типов ', LModel.Types.Count, ', методов ', LModel.Methods.Count,
      ', предупреждений ', LModel.Warnings.Count);
  finally
    LModel.Free;
  end;

  ForceDirectories(LDir);
  LFileName := TPath.Combine(LDir, 'api-' + LVersion + '.html');
  if TFile.Exists(LFileName) then
  begin
    if SameSpec(TFile.ReadAllBytes(LFileName), LBytes, LHtml) then
    begin
      Writeln('Спецификация не изменилась, файл не перезаписан: ', LFileName);
      Exit(CExitOk);
    end;
    if ACmd.Force then
      Writeln('Файл версии ', LVersion, ' отличается и будет перезаписан (--force): ', LFileName)
    else
    begin
      LFileName := TPath.Combine(LDir, Format('api-%s-%s.html', [LVersion, FormatDateTime('yyyymmdd', Now)]));
      Writeln('Файл версии ', LVersion, ' уже есть и отличается — новый сохраняется отдельно ',
        '(перезапись — --force)');
      if TFile.Exists(LFileName) then
      begin
        if SameSpec(TFile.ReadAllBytes(LFileName), LBytes, LHtml) then
        begin
          Writeln('Такая же копия уже сохранена: ', LFileName);
          Exit(CExitOk);
        end;
        Writeln('Копия за сегодня отличается и будет перезаписана: ', LFileName);
      end;
    end;
  end;

  // Имя файла должно указывать ту же версию, что и модель.
  if not SameStr(VersionFromFileName(LFileName), LVersion) then
    raise Exception.CreateFmt('Версия в имени файла «%s» не совпадает с версией модели %s',
      [ExtractFileName(LFileName), LVersion]);
  TFile.WriteAllBytes(LFileName, LBytes);
  Writeln('Bot API ', LVersion, ': сохранено ', Length(LBytes), ' байт в ', LFileName);
  Result := CExitOk;
end;

procedure PrintList(const ATitle: string; AList: TStrings);
var
  LItem: string;
begin
  Writeln;
  Writeln(ATitle, ' (', AList.Count, '):');
  if AList.Count = 0 then
    Writeln('  нет');
  for LItem in AList do
    Writeln('  ', LItem);
end;

procedure PrintStats(AModel: TGenModel; AVerbose: Boolean);
var
  LType, LSub: TGenType;
  LMethod: TGenMethod;
  LField: TGenField;
  LParam: TGenParam;
  LList: TStringList;
  LName, LLine, LValue: string;
  LObjects, LPlaceholders, LOptionalFields, LRequiredParams, LMultipart: Integer;
begin
  LObjects := 0;
  LPlaceholders := 0;
  LOptionalFields := 0;
  for LType in AModel.Types do
  begin
    if LType.IsPlaceholder then
      Inc(LPlaceholders)
    else if not LType.IsUnion then
      Inc(LObjects);
    for LField in LType.Fields do
      if LField.Optional then
        Inc(LOptionalFields);
  end;
  LRequiredParams := 0;
  LMultipart := 0;
  for LMethod in AModel.Methods do
  begin
    if LMethod.UsesInputFile then
      Inc(LMultipart);
    for LParam in LMethod.Params do
      if LParam.Required then
        Inc(LRequiredParams);
  end;

  Writeln('Файл:      ', AModel.SourceFile);
  Writeln('Bot API:   ', AModel.Version, ' (', AModel.Date, ', ', AModel.DateIso, ')');
  Writeln('Типы:      ', AModel.Types.Count, ' (объекты: ', LObjects, ', union: ',
    Length(AModel.UnionTypes), ', заглушки без полей: ', LPlaceholders, ')');
  Writeln('Методы:    ', AModel.Methods.Count, ' (с загрузкой файлов InputFile: ', LMultipart, ')');
  Writeln('Поля:      ', AModel.FieldCount, ' (обязательных: ', AModel.FieldCount - LOptionalFields,
    ', Optional: ', LOptionalFields, ')');
  Writeln('Параметры: ', AModel.ParamCount, ' (обязательных: ', LRequiredParams,
    ', необязательных: ', AModel.ParamCount - LRequiredParams, ')');
  Writeln('Пропущено заголовков h4 (не сущности): ', AModel.SkippedHeadings.Count);

  LList := TStringList.Create;
  try
    // Полиморфные типы.
    for LType in AModel.UnionTypes do
    begin
      LLine := LType.Name + ' [' + IfThen(LType.Discriminator <> '', LType.Discriminator,
        'нет дискриминатора') + ']';
      if (LType.Discriminator <> '') and not LType.DiscriminatorUnique then
        LLine := LLine + ' (значения повторяются)';
      LLine := LLine + ': ';
      for LName in LType.Subtypes do
      begin
        LValue := '';
        LSub := AModel.FindType(LName);
        if (LSub <> nil) and (LType.Discriminator <> '') then
          LValue := '=' + LSub.FindField(LType.Discriminator).ConstValue;
        if not LLine.EndsWith(': ') then
          LLine := LLine + ', ';
        LLine := LLine + LName + LValue;
      end;
      LList.Add(LLine);
    end;
    PrintList('Полиморфные (union) типы', LList);

    LList.Clear;
    for LType in AModel.Types do
      if LType.IsPlaceholder then
        LList.Add(LType.Name);
    PrintList('Типы-заглушки без полей', LList);

    LList.Clear;
    for LMethod in AModel.UnknownReturnMethods do
      LList.Add(LMethod.Name + ': ' + StringReplace(LMethod.Description, #10, ' ', [rfReplaceAll]));
    PrintList('Методы с ReturnType = Unknown', LList);

    PrintList('Нераспознанные строки и ссылки на типы', AModel.Unresolved);
    PrintList('Предупреждения парсера', AModel.Warnings);

    if AVerbose then
    begin
      LList.Clear;
      for LMethod in AModel.Methods do
        LList.Add(Format('%-36s -> %-40s | %s', [LMethod.Name, LMethod.ReturnType.ToString,
          LMethod.ReturnSentence]));
      PrintList('Методы и типы результата', LList);
      PrintList('Пропущенные заголовки h4', AModel.SkippedHeadings);
    end;
  finally
    LList.Free;
  end;
end;

/// <summary>HTML-файл спецификации — первый позиционный аргумент команды.</summary>
function RequireHtmlArg(const ACmd: TGenCmdLine): string;
begin
  if Length(ACmd.Args) = 0 then
    raise EArgumentException.Create('Не указан HTML-файл спецификации');
  Result := ExpandFileName(ACmd.Args[0]);
  if not TFile.Exists(Result) then
    raise EFileNotFoundException.CreateFmt('Файл не найден: %s', [Result]);
end;

/// <summary>
///   Разбирает AHtmlFile в AModel; сверяет версию из имени файла с моделью
///   и, если ACheckEtalon и рядом есть returns-&lt;версия&gt;.json, типы
///   результата с эталоном. Расхождения попадают в предупреждения модели.
/// </summary>
procedure LoadModel(const AHtmlFile: string; AModel: TGenModel; ACheckEtalon: Boolean);
var
  LNameVersion, LEtalon: string;
  LDiffs: Integer;
begin
  TGenParser.ParseFile(AHtmlFile, AModel);
  LNameVersion := VersionFromFileName(AHtmlFile);
  if (LNameVersion <> '') and not SameStr(LNameVersion, AModel.Version) then
    AModel.AddWarning('Имя файла %s указывает версию %s, а страница — %s',
      [ExtractFileName(AHtmlFile), LNameVersion, AModel.Version]);
  if not ACheckEtalon then
    Exit;
  LEtalon := TPath.Combine(ExtractFilePath(AHtmlFile), 'returns-' + AModel.Version + '.json');
  if TFile.Exists(LEtalon) then
  begin
    LDiffs := AModel.CheckReturnsEtalon(LEtalon);
    Writeln('Эталон типов результата ', ExtractFileName(LEtalon), ': расхождений ', LDiffs);
  end
  else
    Writeln('Эталон типов результата ', ExtractFileName(LEtalon),
      ' не найден — сверка пропущена (создать: --returns)');
end;

/// <summary>Код возврата с учётом --strict.</summary>
function StrictExitCode(const ACmd: TGenCmdLine; AModel: TGenModel): Integer;
var
  LUnknown: Integer;
begin
  Result := CExitOk;
  if not ACmd.StrictMode then
    Exit;
  LUnknown := Length(AModel.UnknownReturnMethods);
  if (AModel.Warnings.Count > 0) or (AModel.Unresolved.Count > 0) or (LUnknown > 0) then
  begin
    Writeln(ErrOutput, Format('--strict: предупреждений %d, нераспознанных ссылок %d, ' +
      'методов с неизвестным результатом %d', [AModel.Warnings.Count, AModel.Unresolved.Count, LUnknown]));
    Result := CExitError;
  end;
end;

function DoParse(const ACmd: TGenCmdLine): Integer;
var
  LModel: TGenModel;
begin
  LModel := TGenModel.Create;
  try
    LoadModel(RequireHtmlArg(ACmd), LModel, True);
    PrintStats(LModel, ACmd.Verbose);
    Result := StrictExitCode(ACmd, LModel);
  finally
    LModel.Free;
  end;
end;

function DoDump(const ACmd: TGenCmdLine): Integer;
var
  LModel: TGenModel;
  LHtml, LOut: string;
begin
  LHtml := RequireHtmlArg(ACmd);
  LModel := TGenModel.Create;
  try
    LoadModel(LHtml, LModel, True);
    if Length(ACmd.Args) >= 2 then
      LOut := ExpandFileName(ACmd.Args[1])
    else
      LOut := TPath.Combine(ExtractFilePath(LHtml), 'model-' + LModel.Version + '.json');
    LModel.SaveToJson(LOut);
    Writeln('Bot API ', LModel.Version, ': типов ', LModel.Types.Count, ', методов ',
      LModel.Methods.Count, ', предупреждений ', LModel.Warnings.Count);
    Writeln('Модель сохранена: ', LOut);
    Result := StrictExitCode(ACmd, LModel);
  finally
    LModel.Free;
  end;
end;

function DoReturns(const ACmd: TGenCmdLine): Integer;
var
  LModel: TGenModel;
  LHtml, LOut: string;
  LUnknown: Integer;
begin
  LHtml := RequireHtmlArg(ACmd);
  LModel := TGenModel.Create;
  try
    LoadModel(LHtml, LModel, False);
    if Length(ACmd.Args) >= 2 then
      LOut := ExpandFileName(ACmd.Args[1])
    else
      LOut := TPath.Combine(ExtractFilePath(LHtml), 'returns-' + LModel.Version + '.json');
    LModel.SaveReturnsEtalon(LOut);
    LUnknown := Length(LModel.UnknownReturnMethods);
    Writeln('Bot API ', LModel.Version, ': методов ', LModel.Methods.Count,
      ', с неизвестным результатом ', LUnknown);
    Writeln('Эталон сохранён: ', LOut);
    if LUnknown > 0 then
      Writeln('Внимание: в эталон попали методы с неизвестным результатом — проверьте вручную');
    Result := CExitOk;
  finally
    LModel.Free;
  end;
end;

/// <summary>Файл переопределений: --overrides или overrides.json рядом с HTML ('' — нет файла).</summary>
function OverridesFileFor(const ACmd: TGenCmdLine; const AHtmlFile: string): string;
begin
  if ACmd.OverridesFile <> '' then
  begin
    Result := ExpandFileName(ACmd.OverridesFile);
    if not TFile.Exists(Result) then
      raise EFileNotFoundException.CreateFmt('Файл не найден: %s', [Result]);
  end
  else
  begin
    Result := TPath.Combine(ExtractFilePath(AHtmlFile), 'overrides.json');
    if not TFile.Exists(Result) then
      Result := '';
  end;
end;

/// <summary>Разбирает HTML и выполняет анализ модели с переопределениями.</summary>
procedure RunAnalysis(const ACmd: TGenCmdLine; const AHtmlFile: string; AModel: TGenModel;
  AAnalysis: TGenAnalysis);
var
  LOverrides: string;
begin
  LoadModel(AHtmlFile, AModel, False);
  LOverrides := OverridesFileFor(ACmd, AHtmlFile);
  if LOverrides <> '' then
    AAnalysis.LoadOverrides(LOverrides);
  AAnalysis.Run;
end;

function DoAnalyze(const ACmd: TGenCmdLine): Integer;
var
  LModel: TGenModel;
  LAnalysis: TGenAnalysis;
  LReport: TStringList;
  LLine: string;
begin
  LModel := TGenModel.Create;
  try
    LAnalysis := TGenAnalysis.Create(LModel);
    try
      RunAnalysis(ACmd, RequireHtmlArg(ACmd), LModel, LAnalysis);
      LReport := TStringList.Create;
      try
        LAnalysis.WriteReport(LReport);
        for LLine in LReport do
          Writeln(LLine);
      finally
        LReport.Free;
      end;
      if LAnalysis.Errors.Count > 0 then
        Result := CExitError
      else if ACmd.StrictMode and (LAnalysis.Warnings.Count > 0) then
      begin
        Writeln(ErrOutput, Format('--strict: предупреждений анализа %d', [LAnalysis.Warnings.Count]));
        Result := CExitError;
      end
      else
        Result := CExitOk;
    finally
      LAnalysis.Free;
    end;
  finally
    LModel.Free;
  end;
end;

function DoGen(const ACmd: TGenCmdLine): Integer;
var
  LModel: TGenModel;
  LAnalysis: TGenAnalysis;
  LEmitter: TGenEmitter;
  LDir, LItem: string;
  LTotal, I: Integer;
begin
  LModel := TGenModel.Create;
  try
    LAnalysis := TGenAnalysis.Create(LModel);
    try
      RunAnalysis(ACmd, RequireHtmlArg(ACmd), LModel, LAnalysis);
      if LAnalysis.Errors.Count > 0 then
      begin
        Writeln(ErrOutput, 'Ошибки анализа (', LAnalysis.Errors.Count, '):');
        for LItem in LAnalysis.Errors do
          Writeln(ErrOutput, '  ', LItem);
        Exit(CExitError);
      end;
      if ACmd.Only <> '' then
        LAnalysis.Restrict(ACmd.Only);
      LDir := ExpandFileName(ACmd.OutDir);
      LEmitter := TGenEmitter.Create(LAnalysis, LDir);
      try
        LEmitter.Generate;
        LTotal := 0;
        for I := 0 to LEmitter.Files.Count - 1 do
        begin
          Writeln(Format('  %-22s %6s строк', [LEmitter.Files.Names[I], LEmitter.Files.ValueFromIndex[I]]));
          Inc(LTotal, StrToIntDef(LEmitter.Files.ValueFromIndex[I], 0));
        end;
        Writeln(Format('Bot API %s: файлов %d, строк %d → %s', [LModel.Version, LEmitter.Files.Count,
          LTotal, LDir]));
      finally
        LEmitter.Free;
      end;
      if ACmd.StrictMode and (LAnalysis.Warnings.Count > 0) then
        Result := CExitError
      else
        Result := CExitOk;
    finally
      LAnalysis.Free;
    end;
  finally
    LModel.Free;
  end;
end;

var
  GOldOutputCP: UINT;

procedure SetupConsole;
begin
  // Вывод в UTF-8: корректная кириллица и в консоли, и при перенаправлении в файл.
  // Исходная кодовая страница консоли восстанавливается при выходе
  // (0 — консоли нет, восстанавливать нечего).
  GOldOutputCP := GetConsoleOutputCP;
  SetConsoleOutputCP(CP_UTF8);
  SetTextCodePage(Output, CP_UTF8);
  SetTextCodePage(ErrOutput, CP_UTF8);
end;

procedure RestoreConsole;
begin
  Flush(Output);
  Flush(ErrOutput);
  if GOldOutputCP <> 0 then
    SetConsoleOutputCP(GOldOutputCP);
end;

var
  GCmd: TGenCmdLine;

begin
{$IFDEF DEBUG}
  ReportMemoryLeaksOnShutdown := True;
{$ENDIF}
  SetupConsole;
  try
    try
      GCmd := ParseCommandLine;
      if GCmd.Command = '--fetch' then
        ExitCode := DoFetch(GCmd)
      else if GCmd.Command = '--parse' then
        ExitCode := DoParse(GCmd)
      else if GCmd.Command = '--dump' then
        ExitCode := DoDump(GCmd)
      else if GCmd.Command = '--returns' then
        ExitCode := DoReturns(GCmd)
      else if GCmd.Command = '--analyze' then
        ExitCode := DoAnalyze(GCmd)
      else if GCmd.Command = '--gen' then
        ExitCode := DoGen(GCmd)
      else
        PrintUsage;
    except
      on E: EArgumentException do
      begin
        Writeln(ErrOutput, 'Ошибка: ', E.Message);
        PrintUsage;
        ExitCode := CExitUsage;
      end;
      on E: Exception do
      begin
        Writeln(ErrOutput, 'Ошибка (', E.ClassName, '): ', E.Message);
        ExitCode := CExitError;
      end;
    end;
  finally
    RestoreConsole;
  end;
end.
