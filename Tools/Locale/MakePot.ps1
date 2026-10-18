<#
.SYNOPSIS
  Каталоги перевода gettext сообщений TgBot: Locale\tgbot.pot (шаблон) и Locale\ru.po (русский).

.DESCRIPTION
  Разбирает раздел resourcestring Source\TgBot.Consts.pas — пары SRu<Имя>/SEn<Имя> — и строит:
    tgbot.pot — шаблон для переводчиков: msgid — английский текст (SEn…), msgstr пуст;
    ru.po     — русский перевод: msgstr — текст SRu….
  Ключ перевода (msgid) — английский текст, как его вернёт LoadResString(@SEn…) (см. ITgTranslator
  в TgBot.Base и загрузчик TgBot.Po). Порядок записей — порядок SEn… в TgBot.Consts.pas.

  Разбор Pascal: строки '…' (удвоенная '' — апостроф), коды символов #NN и #$NN, склейка через '+',
  выражение на нескольких строках, комментарии { }, (* *) и //. Директива {$…} внутри раздела — ошибка.
  Исходник читается строго как UTF-8 (BOM допускается).
  Ошибки (код 1): имя не вида SRu<Имя>/SEn<Имя>, повтор имени, SEn без пары SRu или наоборот, пустой
  текст, две строки подряд без '+', символ #0 или одиночный суррогат UTF-16 (#$D800..#$DFFF без
  пары), спецификаторы Format у SRu и SEn разные или некорректные (индекс аргумента больше
  CTgFormatMaxArgIndex из TgBot.Base — загрузчик .po отбросил бы перевод), два SEn с одинаковым
  текстом, но разными SRu (конфликт msgid). Одинаковые пары текстов — одна запись.

  Формат вывода — стандарт gettext: UTF-8 без BOM, переводы строк LF. Вывод детерминирован (нет
  POT-Creation-Date; PO-Revision-Date в ru.po — постоянная $Script:PoRevisionDate, в tgbot.pot —
  заготовка gettext): повторный запуск без изменений в исходнике даёт те же байты, файлы с тем же
  содержимым не перезаписываются. Записи с '%' в msgid — флаг object-pascal-format (синтаксис
  Format Delphi; GNU msgfmt -c сверит спецификаторы msgstr).

  Коды выхода: 0 — готово (или -Check: файлы актуальны); 1 — ошибка разбора или (-Check) файлы
  устарели.

.PARAMETER Check
  Не писать файлы: сравнить построенный текст с файлами в OutDir. Расхождение — код 1 и первая
  различающаяся строка.
.PARAMETER OutDir
  Папка каталогов (по умолчанию <корень проекта>\Locale). Относительный путь — от текущей папки.

.EXAMPLE
  powershell -NoProfile -ExecutionPolicy Bypass -File Tools\Locale\MakePot.ps1
.EXAMPLE
  powershell -NoProfile -ExecutionPolicy Bypass -File Tools\Locale\MakePot.ps1 -Check
#>
param(
    [switch]$Check,
    [string]$OutDir = ''
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$Script:Root = Split-Path -Parent (Split-Path -Parent $PSScriptRoot)
# Пути в ссылках #: и сообщениях — относительно корня, с '/' (как принято в gettext).
$Script:ConstsRel = 'Source/TgBot.Consts.pas'
$Script:BaseRel = 'Source/TgBot.Base.pas'
$Script:ScriptRel = 'Tools/Locale/MakePot.ps1'
$Script:Generator = "TgBot $Script:ScriptRel"
$Script:PluralRu = 'nplurals=3; plural=(n%10==1 && n%100!=11 ? 0 : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2);'
# Заголовок ru.po: постоянные значения (вывод детерминирован). PO-Revision-Date — дата пересмотра
# перевода; меняйте вручную при существенной правке русских текстов.
$Script:PoRevisionDate = '2026-10-18 00:00+0000'
$Script:PoTeam = 'TgBot <https://github.com/kazann116/TgBot>'
# Вывод: UTF-8 без BOM, LF. Чтение исходников — строгий UTF-8 (BOM распознаётся).
$Script:Utf8NoBom = New-Object Text.UTF8Encoding($false)
$Script:Utf8Strict = New-Object Text.UTF8Encoding($false, $true)
$Script:IdentRegex = [regex]'\G[A-Za-z_][A-Za-z0-9_]*'
$Script:CharCodeRegex = [regex]'\G#(?:\$([0-9A-Fa-f]+)|([0-9]+))'
$Script:ImplementationRegex = [regex]'(?mi)^[ \t]*implementation[ \t]*$'
# Наибольший индекс аргумента Format — CTgFormatMaxArgIndex из TgBot.Base (читается при запуске).
$Script:FormatMaxArgIndex = -1

function Get-FullPath {
    param([string]$Rel)
    return Join-Path $Script:Root ($Rel.Replace('/', '\'))
}

# Ошибка в исходнике: «файл:строка: описание».
function Stop-Source {
    param([int]$Line, [string]$Message)
    throw ('{0}:{1}: {2}' -f $Script:ConstsRel, $Line, $Message)
}

function Get-NewLineCount {
    param([string]$Text, [int]$From, [int]$To)
    $count = 0
    for ($k = $From; $k -lt $To; $k++) { if ($Text[$k] -eq "`n") { $count++ } }
    return $count
}

# Текст исходника проекта (путь относительно корня): строгий UTF-8, BOM отбрасывается.
function Read-SourceText {
    param([string]$Rel)
    $bytes = [IO.File]::ReadAllBytes((Get-FullPath $Rel))
    try {
        $text = $Script:Utf8Strict.GetString($bytes)
    } catch {
        # .NET-исключение приходит обёрнутым (MethodInvocationException) — ищем причину.
        $e = $_.Exception
        while ($e -and -not ($e -is [Text.DecoderFallbackException])) { $e = $e.InnerException }
        if (-not $e) { throw }
        if ($e.Index -lt 0 -or $e.Index -gt $bytes.Length) { throw "$Rel`: файл не в кодировке UTF-8; сохраните его как UTF-8." }
        $line = 1
        for ($k = 0; $k -lt $e.Index; $k++) { if ($bytes[$k] -eq 10) { $line++ } }
        throw ("{0}:{1}: файл не в кодировке UTF-8 (байт 0x{2:X2}, смещение {3}); сохраните его как UTF-8." -f
            $Rel, $line, @($e.BytesUnknown)[0], $e.Index)
    }
    return $text.TrimStart([char]0xFEFF)
}

function Read-PasConst {
    param([string]$Rel, [string]$Name)
    $text = Read-SourceText $Rel
    $m = [regex]::Match($text, '\b' + $Name + "\s*=\s*'([^']+)'")
    if (-not $m.Success) { throw "Не найдена константа $Name в $Rel." }
    return $m.Groups[1].Value
}

function Read-PasIntConst {
    param([string]$Rel, [string]$Name)
    $text = Read-SourceText $Rel
    $m = [regex]::Match($text, '\b' + $Name + '\s*=\s*([0-9]{1,9})\s*;')
    if (-not $m.Success) { throw "Не найдена целая константа $Name в $Rel." }
    return [int]$m.Groups[1].Value
}

# Индекс первого одиночного суррогата UTF-16 в AText (старший без младшего за ним или младший без
# старшего перед ним); -1 — нет.
function Find-LoneSurrogate {
    param([string]$Text)
    for ($k = 0; $k -lt $Text.Length; $k++) {
        if ([char]::IsHighSurrogate($Text[$k])) {
            if ($k + 1 -lt $Text.Length -and [char]::IsLowSurrogate($Text[$k + 1])) { $k++; continue }
            return $k
        }
        if ([char]::IsLowSurrogate($Text[$k])) { return $k }
    }
    return -1
}

# Лексемы раздела resourcestring: Id (имя), Sym (= + ;), Str (строковый литерал: подряд идущие
# '…' и #NN/#$NN без пробелов — одна строка Delphi). AFirstLine — номер первой строки AText.
function Get-PasTokens {
    param([string]$Text, [int]$FirstLine)
    $tokens = New-Object System.Collections.Generic.List[object]
    $i = 0
    $line = $FirstLine
    $n = $Text.Length
    while ($i -lt $n) {
        $c = $Text[$i]
        if ($c -eq "`n") { $line++; $i++; continue }
        if ([char]::IsWhiteSpace($c)) { $i++; continue }
        if ($c -eq '/' -and $i + 1 -lt $n -and $Text[$i + 1] -eq '/') {
            while ($i -lt $n -and $Text[$i] -ne "`n") { $i++ }
            continue
        }
        if ($c -eq '{' -or ($c -eq '(' -and $i + 1 -lt $n -and $Text[$i + 1] -eq '*')) {
            $close = if ($c -eq '{') { '}' } else { '*)' }
            $from = if ($c -eq '{') { $i + 1 } else { $i + 2 }
            if ($from -lt $n -and $Text[$from] -eq '$') { Stop-Source $line 'директива компилятора в разделе resourcestring не поддерживается' }
            $end = $Text.IndexOf($close, $from, [StringComparison]::Ordinal)
            if ($end -lt 0) { Stop-Source $line "незакрытый комментарий $c" }
            $line += Get-NewLineCount $Text $i $end
            $i = $end + $close.Length
            continue
        }
        if ($c -eq "'" -or $c -eq '#') {
            $start = $line
            $sb = New-Object Text.StringBuilder
            while ($i -lt $n -and ($Text[$i] -eq "'" -or $Text[$i] -eq '#')) {
                if ($Text[$i] -eq "'") {
                    $i++
                    while ($true) {
                        if ($i -ge $n -or $Text[$i] -eq "`n" -or $Text[$i] -eq "`r") { Stop-Source $start 'незакрытая строка' }
                        if ($Text[$i] -eq "'") {
                            if ($i + 1 -lt $n -and $Text[$i + 1] -eq "'") { [void]$sb.Append("'"); $i += 2; continue }
                            $i++
                            break
                        }
                        [void]$sb.Append($Text[$i])
                        $i++
                    }
                } else {
                    $m = $Script:CharCodeRegex.Match($Text, $i)
                    if (-not $m.Success) { Stop-Source $line 'после # ожидается код символа (#NN или #$NN)' }
                    $digits = if ($m.Groups[1].Success) { $m.Groups[1].Value } else { $m.Groups[2].Value }
                    if ($digits.Length -gt 6) { Stop-Source $line "код символа $($m.Value) вне диапазона" }
                    $code = if ($m.Groups[1].Success) { [Convert]::ToInt32($digits, 16) } else { [int]$digits }
                    if ($code -gt 0xFFFF) { Stop-Source $line "код символа $($m.Value) вне диапазона" }
                    # Строки gettext (и .mo) завершаются нулём: #0 в тексте недопустим.
                    if ($code -eq 0) { Stop-Source $line "символ $($m.Value) (NUL) в тексте недопустим" }
                    [void]$sb.Append([char]$code)
                    $i += $m.Length
                }
            }
            $tokens.Add([pscustomobject]@{ Kind = 'Str'; Value = $sb.ToString(); Line = $start })
            continue
        }
        $m = $Script:IdentRegex.Match($Text, $i)
        if ($m.Success) {
            $tokens.Add([pscustomobject]@{ Kind = 'Id'; Value = $m.Value; Line = $line })
            $i += $m.Length
            continue
        }
        if ($c -eq '=' -or $c -eq '+' -or $c -eq ';') {
            $tokens.Add([pscustomobject]@{ Kind = 'Sym'; Value = [string]$c; Line = $line })
            $i++
            continue
        }
        Stop-Source $line "неожиданный символ '$c'"
    }
    return ,$tokens
}

# Ресурсные строки: Name, Lang (Ru/En), Key (имя без SRu/SEn), Text, Line — в порядке файла.
function Read-ResourceStrings {
    $text = (Read-SourceText $Script:ConstsRel).Replace("`r`n", "`n")
    # Ключевые слова — отдельной строкой: в шапке-комментарии слово resourcestring тоже бывает в начале строки.
    $begin = [regex]::Match($text, '(?mi)^[ \t]*resourcestring[ \t]*$')
    if (-not $begin.Success) { throw "В $Script:ConstsRel нет раздела resourcestring." }
    $bodyStart = $begin.Index + $begin.Length
    $end = $Script:ImplementationRegex.Match($text, $bodyStart)
    if (-not $end.Success) { throw "В $Script:ConstsRel нет implementation после resourcestring." }
    $firstLine = (Get-NewLineCount $text 0 $bodyStart) + 1
    $tokens = Get-PasTokens $text.Substring($bodyStart, $end.Index - $bodyStart) $firstLine

    $result = New-Object System.Collections.Generic.List[object]
    $names = @{}
    $k = 0
    while ($k -lt $tokens.Count) {
        $t = $tokens[$k]
        if ($t.Kind -ne 'Id') { Stop-Source $t.Line "ожидается имя ресурсной строки, получено '$($t.Value)'" }
        if ($k + 1 -ge $tokens.Count -or $tokens[$k + 1].Value -ne '=') { Stop-Source $t.Line "после $($t.Value) ожидается '='" }
        $k += 2
        $sb = New-Object Text.StringBuilder
        # Начало каждой части выражения в тексте и её строка — для сообщения об ошибке в тексте.
        $partStarts = New-Object System.Collections.Generic.List[int]
        $partLines = New-Object System.Collections.Generic.List[int]
        $needString = $true
        while ($true) {
            if ($k -ge $tokens.Count) { Stop-Source $t.Line "$($t.Value): выражение не завершено ';'" }
            $p = $tokens[$k]
            if ($p.Kind -eq 'Str') {
                if (-not $needString) { Stop-Source $p.Line "$($t.Value): две строки подряд — нужен '+'" }
                $partStarts.Add($sb.Length)
                $partLines.Add($p.Line)
                [void]$sb.Append($p.Value)
                $needString = $false
            } elseif ($needString) {
                Stop-Source $p.Line "$($t.Value): ожидается строка, получено '$($p.Value)'"
            } elseif ($p.Kind -eq 'Sym' -and $p.Value -eq '+') {
                $needString = $true
            } elseif ($p.Kind -eq 'Sym' -and $p.Value -eq ';') {
                $k++
                break
            } else {
                Stop-Source $p.Line "$($t.Value): ожидается '+' или ';', получено '$($p.Value)'"
            }
            $k++
        }
        $value = $sb.ToString()
        # Суррогатная пара (#$D83D#$DE00) допустима, одиночный суррогат в UTF-8 не кодируется.
        $lone = Find-LoneSurrogate $value
        if ($lone -ge 0) {
            $at = $t.Line
            for ($q = 0; $q -lt $partStarts.Count; $q++) { if ($partStarts[$q] -le $lone) { $at = $partLines[$q] } }
            Stop-Source $at ('{0}: одиночный суррогат UTF-16 #${1:X4} без пары' -f $t.Value, [int]($value[$lone]))
        }
        $m = [regex]::Match($t.Value, '^S(Ru|En)([A-Za-z0-9_]+)$')
        if (-not $m.Success) { Stop-Source $t.Line "имя $($t.Value) не вида SRu<Имя>/SEn<Имя>" }
        $upper = $t.Value.ToUpperInvariant()
        if ($names.ContainsKey($upper)) { Stop-Source $t.Line "повтор имени $($t.Value) (строка $($names[$upper]))" }
        $names[$upper] = $t.Line
        $result.Add([pscustomobject]@{
                Name = $t.Value; Lang = $m.Groups[1].Value; Key = $m.Groups[2].Value
                Text = $value; Line = $t.Line
            })
    }
    return ,$result
}

# Подпись аргументов строки формата Delphi Format: «индекс=тип» через пробел ('' — нет
# спецификаторов), $null — строка формата некорректна (одиночный '%', неизвестный тип, разные типы
# одного индекса, индекс аргумента больше CTgFormatMaxArgIndex). Порядок и повторы не важны — как
# TgSameFormatSignature в TgBot.Base.
function Get-FormatSignature {
    param([string]$Text)
    $max = $Script:FormatMaxArgIndex
    $types = @{}
    $next = 0
    $i = 0
    $n = $Text.Length
    while ($i -lt $n) {
        if ($Text[$i] -ne '%') { $i++; continue }
        $i++
        if ($i -ge $n) { return $null }
        if ($Text[$i] -eq '%') { $i++; continue }
        $arg = $next
        $digits = [regex]::Match($Text.Substring($i), '^[0-9]*').Value
        if ($i + $digits.Length -lt $n -and $Text[$i + $digits.Length] -eq ':') {
            # Длинное число — заведомо больше предела (без переполнения [int]); ведущие нули допустимы.
            $significant = $digits.TrimStart('0')
            if ($significant.Length -gt 9) { return $null }
            $arg = if ($significant) { [int]$significant } else { 0 }
            $i += $digits.Length + 1
            $digits = ''
        }
        if ($arg -gt $max) { return $null }
        if (-not $digits) {
            if ($i -lt $n -and $Text[$i] -eq '-') { $i++ }
            if ($i -lt $n -and $Text[$i] -eq '*') {
                if ($types.ContainsKey($arg) -and $types[$arg] -ne '*') { return $null }
                $types[$arg] = '*'
                $arg++
                $i++
            } else {
                $digits = [regex]::Match($Text.Substring($i), '^[0-9]*').Value
            }
        }
        $i += $digits.Length
        if ($i -lt $n -and $Text[$i] -eq '.') {
            $i++
            if ($i -lt $n -and $Text[$i] -eq '*') {
                if ($arg -gt $max) { return $null }
                if ($types.ContainsKey($arg) -and $types[$arg] -ne '*') { return $null }
                $types[$arg] = '*'
                $arg++
                $i++
            } else {
                $i += [regex]::Match($Text.Substring($i), '^[0-9]*').Value.Length
            }
        }
        if ($i -ge $n -or 'dDuUeEfFgGnNmMpPsSxX'.IndexOf($Text[$i]) -lt 0) { return $null }
        $type = [string]([char]::ToUpperInvariant($Text[$i]))
        if ($arg -gt $max) { return $null }
        if ($types.ContainsKey($arg) -and $types[$arg] -ne $type) { return $null }
        $types[$arg] = $type
        $next = $arg + 1
        $i++
    }
    return (@($types.Keys | Sort-Object | ForEach-Object { '{0}={1}' -f $_, $types[$_] }) -join ' ')
}

# Флаг формата записи: '' — в msgid нет '%' (простой текст), иначе object-pascal-format (строки
# передаются в Format Delphi; GNU gettext знает этот синтаксис).
function Get-FormatFlag {
    param([string]$Text)
    if ($Text.IndexOf('%') -lt 0) { return '' }
    return 'object-pascal-format'
}

# Записи каталога: Names, Refs (строки SEn…), MsgId (SEn), MsgStr (SRu), Flag — в порядке SEn….
function Get-CatalogEntries {
    $strings = Read-ResourceStrings
    $ru = @{}
    $en = @{}
    foreach ($s in $strings) {
        if ($s.Lang -eq 'Ru') { $ru[$s.Key] = $s } else { $en[$s.Key] = $s }
    }
    $errors = @()
    foreach ($s in $strings) {
        $pair = if ($s.Lang -eq 'Ru') { 'SEn' + $s.Key } else { 'SRu' + $s.Key }
        $other = if ($s.Lang -eq 'Ru') { $en } else { $ru }
        if (-not $other.ContainsKey($s.Key)) { $errors += ('{0}:{1}: {2} без пары {3}' -f $Script:ConstsRel, $s.Line, $s.Name, $pair) }
        if ($s.Text.Trim() -eq '') { $errors += ('{0}:{1}: {2} — пустой текст' -f $Script:ConstsRel, $s.Line, $s.Name) }
    }
    if ($errors.Count -gt 0) { throw ($errors -join "`n") }

    $entries = New-Object System.Collections.Generic.List[object]
    $byMsgId = @{}
    foreach ($s in $strings) {
        if ($s.Lang -ne 'En') { continue }
        $r = $ru[$s.Key]
        $enSig = Get-FormatSignature $s.Text
        $ruSig = Get-FormatSignature $r.Text
        if ($s.Text.IndexOf('%') -ge 0) {
            if ($null -eq $enSig) {
                $errors += ('{0}:{1}: {2} — некорректная строка формата (литерал процента — %%, индекс аргумента — не больше {3})' -f
                    $Script:ConstsRel, $s.Line, $s.Name, $Script:FormatMaxArgIndex)
            } elseif ($null -eq $ruSig) {
                $errors += ('{0}:{1}: {2} — некорректная строка формата (литерал процента — %%, индекс аргумента — не больше {3})' -f
                    $Script:ConstsRel, $r.Line, $r.Name, $Script:FormatMaxArgIndex)
            } elseif ($ruSig -ne $enSig) {
                $errors += ('{0}:{1}: спецификаторы Format {2} и {3} не совпадают («{4}» / «{5}»)' -f $Script:ConstsRel, $r.Line, $r.Name, $s.Name, $ruSig, $enSig)
            }
        } elseif ($null -ne $ruSig -and $ruSig -ne '') {
            $errors += ('{0}:{1}: в {2} есть спецификаторы Format ({3}), а в {4} — нет' -f $Script:ConstsRel, $r.Line, $r.Name, $ruSig, $s.Name)
        }
        # Ключ словаря .po — точный текст (Hashtable PowerShell сравнивает строки без учёта регистра).
        $msgKey = 'k' + [Convert]::ToBase64String($Script:Utf8NoBom.GetBytes($s.Text))
        if ($byMsgId.ContainsKey($msgKey)) {
            $prev = $byMsgId[$msgKey]
            if ($prev.MsgStr -cne $r.Text) {
                $errors += ('{0}:{1}: конфликт msgid — {2} совпадает по тексту с {3} (строка {4}), а {5} и SRu{6} разные' -f
                    $Script:ConstsRel, $s.Line, $s.Name, $prev.Names[0], $prev.Refs[0], $r.Name, $prev.Names[0].Substring(3))
            } else {
                $prev.Names += $s.Name
                $prev.Refs += $s.Line
            }
            continue
        }
        $entry = [pscustomobject]@{
            Names = @($s.Name); Refs = @($s.Line); MsgId = $s.Text; MsgStr = $r.Text; Flag = (Get-FormatFlag $s.Text)
        }
        $byMsgId[$msgKey] = $entry
        $entries.Add($entry)
    }
    if ($errors.Count -gt 0) { throw ($errors -join "`n") }
    if ($entries.Count -eq 0) { throw "В $Script:ConstsRel нет пар SRu…/SEn…." }
    return ,$entries
}

# Строка .po в кавычках: \\ \" \n \t \r, прочие управляющие символы — \ooo.
function ConvertTo-PoQuoted {
    param([string]$Text)
    # Разбор исходника отсекает #0 и одиночные суррогаты; здесь — страховка от молча испорченного
    # вывода (NUL обрезал бы строку gettext, суррогат стал бы U+FFFD).
    if ($Text.IndexOf([char]0) -ge 0) { throw "Символ NUL в тексте записи: «$($Text.Replace([string][char]0, '\0'))»" }
    if ((Find-LoneSurrogate $Text) -ge 0) { throw "Одиночный суррогат UTF-16 в тексте записи: «$Text»" }
    $sb = New-Object Text.StringBuilder
    [void]$sb.Append('"')
    foreach ($ch in $Text.ToCharArray()) {
        switch -CaseSensitive ([string]$ch) {
            '\' { [void]$sb.Append('\\') }
            '"' { [void]$sb.Append('\"') }
            "`n" { [void]$sb.Append('\n') }
            "`t" { [void]$sb.Append('\t') }
            "`r" { [void]$sb.Append('\r') }
            default {
                if ([int]$ch -lt 32 -or [int]$ch -eq 127) { [void]$sb.Append('\' + [Convert]::ToString([int]$ch, 8).PadLeft(3, '0')) }
                else { [void]$sb.Append($ch) }
            }
        }
    }
    [void]$sb.Append('"')
    return $sb.ToString()
}

# Поле записи: «ключевое_слово "текст"»; текст с переводами строк внутри — по строке .po на каждую
# (msgid "" и далее "…\n"), как у xgettext.
function Format-PoField {
    param([string]$Keyword, [string]$Text)
    $nl = $Text.IndexOf("`n")
    if ($nl -lt 0 -or $nl -eq $Text.Length - 1) { return @("$Keyword " + (ConvertTo-PoQuoted $Text)) }
    $lines = @("$Keyword """"")
    foreach ($part in [regex]::Split($Text, '(?<=\n)')) {
        if ($part -ne '') { $lines += (ConvertTo-PoQuoted $part) }
    }
    return $lines
}

# Текст каталога (LF, без BOM): заголовок и записи; AWithTranslation — msgstr = SRu… (ru.po).
function Build-Catalog {
    param([string[]]$Comments, [string[]]$Header, [bool]$Fuzzy, $Entries, [bool]$WithTranslation)
    $out = New-Object System.Collections.Generic.List[string]
    foreach ($c in $Comments) { $out.Add(('# ' + $c).TrimEnd()) }
    if ($Fuzzy) { $out.Add('#, fuzzy') }
    $out.Add('msgid ""')
    $out.Add('msgstr ""')
    foreach ($h in $Header) { $out.Add((ConvertTo-PoQuoted ($h + "`n"))) }
    foreach ($e in $Entries) {
        $out.Add('')
        foreach ($name in $e.Names) { $out.Add("#. $name") }
        $out.Add('#: ' + (@($e.Refs | ForEach-Object { '{0}:{1}' -f $Script:ConstsRel, $_ }) -join ' '))
        if ($e.Flag) { $out.Add("#, $($e.Flag)") }
        foreach ($l in (Format-PoField 'msgid' $e.MsgId)) { $out.Add($l) }
        $str = if ($WithTranslation) { $e.MsgStr } else { '' }
        foreach ($l in (Format-PoField 'msgstr' $str)) { $out.Add($l) }
    }
    return (($out -join "`n") + "`n")
}

# Расхождение файла APath с текстом AExpected: '' — совпадает, иначе описание.
function Compare-CatalogFile {
    param([string]$Path, [string]$Expected)
    if (-not (Test-Path -LiteralPath $Path -PathType Leaf)) { return 'файла нет' }
    $bytes = [IO.File]::ReadAllBytes($Path)
    if ($bytes.Length -ge 3 -and $bytes[0] -eq 0xEF -and $bytes[1] -eq 0xBB -and $bytes[2] -eq 0xBF) {
        return 'файл начинается с BOM (нужен UTF-8 без BOM)'
    }
    try { $actual = $Script:Utf8Strict.GetString($bytes) } catch { return 'файл не в кодировке UTF-8' }
    if ($actual -ceq $Expected) { return '' }
    if ($actual.Contains("`r")) { return 'переводы строк CR/CRLF (нужен LF)' }
    $a = $actual.Split("`n")
    $b = $Expected.Split("`n")
    $count = [Math]::Max($a.Length, $b.Length)
    for ($k = 0; $k -lt $count; $k++) {
        $x = if ($k -lt $a.Length) { $a[$k] } else { '<конец файла>' }
        $y = if ($k -lt $b.Length) { $b[$k] } else { '<конец файла>' }
        if ($x -cne $y) { return ("строка {0}:`n    ожидается: {1}`n    в файле:   {2}" -f ($k + 1), $y, $x) }
    }
    return 'различие в конце файла'
}

$exitCode = 0
try {
    # Относительный OutDir — от текущей папки PowerShell (не .NET Environment.CurrentDirectory, куда
    # смотрел бы [IO.File]): дальше путь только полный.
    if (-not $OutDir) { $OutDir = Join-Path $Script:Root 'Locale' }
    $OutDir = $ExecutionContext.SessionState.Path.GetUnresolvedProviderPathFromPSPath($OutDir)
    # Без завершающего '\', кроме корня диска ('C:' — уже не корень, а текущая папка диска).
    $OutDir = $OutDir.TrimEnd('\')
    if ($OutDir -match '^[A-Za-z]:$') { $OutDir += '\' }
    $version = Read-PasConst $Script:BaseRel 'TgBotVersion'
    $Script:FormatMaxArgIndex = Read-PasIntConst $Script:BaseRel 'CTgFormatMaxArgIndex'
    $entries = Get-CatalogEntries

    $mime = @('MIME-Version: 1.0', 'Content-Type: text/plain; charset=UTF-8', 'Content-Transfer-Encoding: 8bit')
    $potComments = @(
        'Шаблон перевода сообщений TgBot (Telegram Bot API для Delphi).',
        'Message catalog template of the TgBot library (Telegram Bot API for Delphi).',
        "Создан $Script:ScriptRel из $Script:ConstsRel — не правьте вручную.",
        "Generated by $Script:ScriptRel from $Script:ConstsRel — do not edit.",
        '',
        'msgid — английский текст сообщения (ключ ITgTranslator). Спецификаторы %s, %d…',
        'сохраняйте в том же количестве и с теми же типами; литерал процента в строке',
        'с флагом формата — %%. Загрузка: TgSetTranslator(TgLoadPoTranslator(''xx.po''))',
        '(модуль TgBot.Po).',
        'msgid is the English message text (ITgTranslator key). Keep %s, %d… specifiers',
        '(same count and types); a literal percent sign in a format string is %%.')
    # Порядок полей — как у xgettext; в шаблоне поля переводчика — стандартные заготовки gettext
    # (их заполняет msginit или редактор .po).
    $bugs = 'Report-Msgid-Bugs-To: https://github.com/kazann116/TgBot/issues'
    $potHeader = @("Project-Id-Version: TgBot $version", $bugs, 'PO-Revision-Date: YEAR-MO-DA HO:MI+ZONE',
        'Last-Translator: FULL NAME <EMAIL@ADDRESS>', 'Language-Team: LANGUAGE <LL@li.org>', 'Language: ') +
        $mime + @("X-Generator: $Script:Generator")
    $ruComments = @(
        "Русский перевод сообщений TgBot — тексты SRu… из $Script:ConstsRel.",
        "Создан $Script:ScriptRel — не правьте вручную: измените $Script:ConstsRel",
        'и перезапустите скрипт.')
    $ruHeader = @("Project-Id-Version: TgBot $version", $bugs, "PO-Revision-Date: $Script:PoRevisionDate",
        "Last-Translator: $Script:PoTeam", "Language-Team: $Script:PoTeam", 'Language: ru') + $mime +
        @("Plural-Forms: $Script:PluralRu", "X-Generator: $Script:Generator")
    $potText = Build-Catalog -Comments $potComments -Header $potHeader -Fuzzy $true -Entries $entries -WithTranslation $false
    $ruText = Build-Catalog -Comments $ruComments -Header $ruHeader -Fuzzy $false -Entries $entries -WithTranslation $true

    $files = @(
        [pscustomobject]@{ Name = 'tgbot.pot'; Text = $potText },
        [pscustomobject]@{ Name = 'ru.po'; Text = $ruText })
    $flags = @($entries | Where-Object { $_.Flag }).Count
    Write-Host ('TgBot {0}: {1} — {2} записей (с форматом: {3}), папка {4}' -f $version, $Script:ConstsRel, $entries.Count, $flags, $OutDir)
    if ($Check) {
        $stale = 0
        foreach ($f in $files) {
            $diff = Compare-CatalogFile (Join-Path $OutDir $f.Name) $f.Text
            if ($diff) {
                $stale++
                Write-Host ("УСТАРЕЛ {0}: {1}" -f $f.Name, $diff) -ForegroundColor Red
            } else {
                Write-Host "  OK $($f.Name)" -ForegroundColor Green
            }
        }
        if ($stale -gt 0) {
            Write-Host 'Каталоги не соответствуют TgBot.Consts.pas. Обновите: powershell -NoProfile -ExecutionPolicy Bypass -File Tools\Locale\MakePot.ps1' -ForegroundColor Red
            $exitCode = 1
        }
    } else {
        [void][IO.Directory]::CreateDirectory($OutDir)
        foreach ($f in $files) {
            $path = Join-Path $OutDir $f.Name
            if ((Compare-CatalogFile $path $f.Text) -eq '') {
                Write-Host "  без изменений $($f.Name)"
            } else {
                [IO.File]::WriteAllText($path, $f.Text, $Script:Utf8NoBom)
                Write-Host "  записан $($f.Name)" -ForegroundColor Green
            }
        }
    }
} catch {
    $exitCode = 1
    Write-Host ''
    Write-Host ('ОШИБКА: ' + $_.Exception.Message) -ForegroundColor Red
}
exit $exitCode
