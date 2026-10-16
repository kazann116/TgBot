<#
.SYNOPSIS
  Сборка распространяемого дистрибутива TgBot (Telegram Bot API для Delphi).

.DESCRIPTION
  Копирует файлы проекта по белому списку во временную папку <TempRoot>\stage\src\TgBot-<версия>\ (версия —
  TgBotVersion из Source\TgBot.Base.pas), добавляет «Как установить.txt» (шаблон Tools\Dist\Как установить.txt),
  проверяет, что нет мусора сборки и токенов ботов, и кладёт в папку результата только готовые к раздаче файлы:
    TgBot-<версия>-Исходники.zip       — исходники без бинарников (всегда);
    TgBot-<версия>-Setup.exe           — установщик Inno Setup (-Setup, Tools\Dist\TgBot.iss);
    TgBot-<версия>-Готовые-пакеты.zip  — исходники + собранные пакеты Lib\ и Bin\ (-Prebuilt);
    SHA256SUMS.txt                     — SHA-256 всех файлов комплекта.
  Внутри архивов одна корневая папка TgBot-<версия>\. Исходный проект не меняется.

  -Prebuilt: собирает пакеты TgBotRT, TgBotIndyRT (Win32, Win64) и TgBotDT (Win32) для каждой установленной
  Delphi 10.4+ (через Install\Install.ps1 -BuildOnly копии дистрибутива: MSBuild + rsvars.bat). Результат:
  Lib\<Delphi>\<Platform>\ (bpl, dcp, dcu) и Bin\<Delphi>\<Platform>\ (bpl). Ошибка сборки останавливает скрипт.

.PARAMETER Setup
  Собрать установщик TgBot-<версия>-Setup.exe (нужен Inno Setup 6, ISCC.exe).
.PARAMETER Prebuilt
  Собрать архив с готовыми пакетами для всех установленных Delphi 10.4+.
.PARAMETER Force
  Пересоздать комплект: удаляет из папки результата прежние TgBot-<версия>* и SHA256SUMS.txt.
.PARAMETER OutRoot
  Папка результата (по умолчанию <корень проекта>\Dist).
.PARAMETER TempRoot
  Папка для временных файлов (по умолчанию %TEMP%\TgBotDist): staging, журналы сборки.
.PARAMETER IsccPath
  Путь к ISCC.exe, если Inno Setup установлен в нестандартное место.
.PARAMETER KeepStage
  Не удалять staging-папку <TempRoot>\stage после успешной сборки.

.EXAMPLE
  powershell -ExecutionPolicy Bypass -File Tools\Dist\MakeDist.ps1 -Setup -Force
.EXAMPLE
  powershell -ExecutionPolicy Bypass -File Tools\Dist\MakeDist.ps1 -Prebuilt -Force -TempRoot C:\tmp\tgdist
#>
param(
    [switch]$Setup,
    [switch]$Prebuilt,
    [switch]$Force,
    [string]$OutRoot = '',
    [string]$TempRoot = '',
    [string]$IsccPath = '',
    [switch]$KeepStage
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$Script:Root = Split-Path -Parent (Split-Path -Parent $PSScriptRoot)
$Script:TokenPattern = '\d{8,10}:[A-Za-z0-9_-]{35}'
$Script:HowToName = 'Как установить.txt'
$Script:SumsName = 'SHA256SUMS.txt'

# Папки, в которые рекурсивный обход не заходит (вывод сборки, история IDE).
$Script:SkipDirs = @('Bin', 'Dcu', 'Lib', 'Dist', '__history', '__recovery', 'Win32', 'Win64', 'Linux64',
    'Android', 'Android64', 'Debug', 'Release', 'Out')

# Файлы, которые сознательно не входят в дистрибутив (формат: 'Source\Файл.pas' = 'причина').
$Script:Excluded = @{}

function Write-Step {
    param([string]$Message)
    Write-Host ''
    Write-Host $Message -ForegroundColor White
}

function Write-Info {
    param([string]$Message, [string]$Color = 'Gray')
    Write-Host ('  ' + $Message) -ForegroundColor $Color
}

function Get-Relative {
    param([string]$Base, [string]$Full)
    return $Full.Substring($Base.TrimEnd('\').Length + 1)
}

function Read-PasConst {
    param([string]$File, [string]$Name)
    $text = [IO.File]::ReadAllText((Join-Path $Script:Root $File), [Text.Encoding]::UTF8)
    $m = [regex]::Match($text, '\b' + $Name + "\s*=\s*'([^']+)'")
    if (-not $m.Success) { throw "Не найдена константа $Name в $File." }
    return $m.Groups[1].Value
}

# Файлы папки Dir (относительно корня) по маскам; с -Recurse — без папок из SkipDirs.
function Get-WhiteFiles {
    param([string]$Dir, [string[]]$Patterns, [switch]$Recurse)
    $full = Join-Path $Script:Root $Dir
    if (-not (Test-Path -LiteralPath $full)) { return @() }
    $items = Get-ChildItem -LiteralPath $full -File -Recurse:$Recurse
    $result = @()
    foreach ($f in $items) {
        $rel = Get-Relative $Script:Root $f.FullName
        $segments = @((Split-Path -Parent $rel) -split '\\' | Where-Object { $_ })
        $skip = $false
        foreach ($s in $segments) { if ($Script:SkipDirs -contains $s) { $skip = $true; break } }
        if ($skip) { continue }
        foreach ($p in $Patterns) {
            if ($f.Name -like $p) { $result += $rel; break }
        }
    }
    return $result
}

function Copy-ToDist {
    param([string]$Rel, [string]$DistDir)
    $src = Join-Path $Script:Root $Rel
    $dst = Join-Path $DistDir $Rel
    $dir = Split-Path -Parent $dst
    if (-not (Test-Path -LiteralPath $dir)) { New-Item -ItemType Directory -Path $dir -Force | Out-Null }
    Copy-Item -LiteralPath $src -Destination $dst
}

function Remove-Generated {
    param([string]$Path, [string]$OutDir)
    if (-not (Test-Path -LiteralPath $Path)) { return }
    if (-not $Force) { throw "Уже существует $Path. Запустите с -Force, чтобы пересоздать." }
    $leaf = Split-Path -Leaf $Path
    if ((Split-Path -Parent $Path) -ne $OutDir -or ($leaf -notlike 'TgBot-*' -and $leaf -ne $Script:SumsName)) {
        throw "Отказ удалять ${Path}: путь вне папки результата."
    }
    Remove-Item -LiteralPath $Path -Recurse -Force
}

# Занят ли файл другим процессом (например, запущен Setup.exe или архив открыт в программе).
function Test-Locked {
    param([string]$Path)
    try {
        $fs = [IO.File]::Open($Path, [IO.FileMode]::Open, [IO.FileAccess]::ReadWrite, [IO.FileShare]::None)
        $fs.Dispose()
        return $false
    } catch {
        return $true
    }
}

# Временная папка staging (своя, внутри TempRoot) — удаляется без -Force.
function Remove-Stage {
    param([string]$StageRoot, [string]$TempDir)
    if (-not (Test-Path -LiteralPath $StageRoot)) { return }
    if ((Split-Path -Parent $StageRoot) -ne $TempDir.TrimEnd('\') -or (Split-Path -Leaf $StageRoot) -ne 'stage') {
        throw "Отказ удалять ${StageRoot}: это не staging-папка MakeDist."
    }
    Remove-Item -LiteralPath $StageRoot -Recurse -Force
}

# «Как установить.txt» из шаблона: {VERSION}, {API}; блок [[PREBUILT]]...[[/PREBUILT]] (с меткой
# {PREBUILT_FOR} — список собранных Delphi) — только для -Prebuilt. UTF-8 с BOM (Блокнот показывает кириллицу), CRLF.
function New-HowTo {
    param([string]$DestDir, [bool]$WithPrebuilt, [string]$Version, [string]$Api, [string]$PrebuiltFor = '')
    $tpl = Join-Path $PSScriptRoot $Script:HowToName
    if (-not (Test-Path -LiteralPath $tpl)) { throw "Нет шаблона $tpl." }
    $text = [IO.File]::ReadAllText($tpl, [Text.Encoding]::UTF8).TrimStart([char]0xFEFF)
    $text = $text.Replace("`r`n", "`n")
    $block = '(?s)\[\[PREBUILT\]\]\n(.*?)\[\[/PREBUILT\]\]\n'
    if (-not [regex]::IsMatch($text, $block)) { throw "В шаблоне $tpl нет блока [[PREBUILT]]...[[/PREBUILT]]." }
    if ($WithPrebuilt) { $text = [regex]::Replace($text, $block, '$1') } else { $text = [regex]::Replace($text, $block, '') }
    $text = $text.Replace('{VERSION}', $Version).Replace('{API}', $Api).Replace('{PREBUILT_FOR}', $PrebuiltFor)
    if ($text -match '\{[A-Z_]+\}|\[\[') { throw "В шаблоне $tpl остались неизвестные метки." }
    $text = $text.Replace("`n", "`r`n")
    [IO.File]::WriteAllText((Join-Path $DestDir $Script:HowToName), $text, (New-Object Text.UTF8Encoding($true)))
}

function Find-Iscc {
    if ($IsccPath) {
        if (-not (Test-Path -LiteralPath $IsccPath)) { throw "Не найден ISCC.exe: $IsccPath" }
        return $IsccPath
    }
    $candidates = @()
    foreach ($pf in @(${env:ProgramFiles(x86)}, $env:ProgramFiles, (Join-Path $env:LOCALAPPDATA 'Programs'))) {
        if ($pf) { $candidates += (Join-Path $pf 'Inno Setup 6\ISCC.exe') }
    }
    foreach ($hive in @([Microsoft.Win32.Registry]::LocalMachine, [Microsoft.Win32.Registry]::CurrentUser)) {
        foreach ($base in @('SOFTWARE\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall',
                            'SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall')) {
            $key = $hive.OpenSubKey($base + '\Inno Setup 6_is1', $false)
            if ($null -eq $key) { continue }
            try { $loc = [string]$key.GetValue('InstallLocation', '') } finally { $key.Close() }
            if ($loc) { $candidates += (Join-Path $loc 'ISCC.exe') }
        }
    }
    $cmd = Get-Command 'iscc.exe' -ErrorAction SilentlyContinue
    if ($cmd) { $candidates += $cmd.Source }
    foreach ($c in $candidates) { if (Test-Path -LiteralPath $c) { return $c } }
    throw 'Inno Setup 6 не найден (ISCC.exe). Установите его бесплатно: https://jrsoftware.org/isdl.php — или запустите без -Setup.'
}

function Write-Sums {
    param([string]$OutDir, [string[]]$Names)
    $lines = @()
    foreach ($n in ($Names | Sort-Object)) {
        $hash = (Get-FileHash -LiteralPath (Join-Path $OutDir $n) -Algorithm SHA256).Hash.ToLowerInvariant()
        $lines += "$hash *$n"
    }
    # Формат sha256sum: без BOM и с LF — иначе `sha256sum -c` считает BOM и CR частью имени файла.
    [IO.File]::WriteAllText((Join-Path $OutDir $Script:SumsName), (($lines -join "`n") + "`n"),
        (New-Object Text.UTF8Encoding($false)))
}

function New-Zip {
    param([string]$SourceDir, [string]$ZipPath)
    Add-Type -AssemblyName System.IO.Compression
    Add-Type -AssemblyName System.IO.Compression.FileSystem
    $base = Split-Path -Parent $SourceDir
    $zip = [System.IO.Compression.ZipFile]::Open($ZipPath, [System.IO.Compression.ZipArchiveMode]::Create)
    try {
        foreach ($f in (Get-ChildItem -LiteralPath $SourceDir -Recurse -File | Sort-Object FullName)) {
            # Разделитель '/' — архив корректно открывается и вне Windows.
            $entry = (Get-Relative $base $f.FullName).Replace('\', '/')
            [void][System.IO.Compression.ZipFileExtensions]::CreateEntryFromFile(
                $zip, $f.FullName, $entry, [System.IO.Compression.CompressionLevel]::Optimal)
        }
    } finally {
        $zip.Dispose()
    }
}

function Test-Dist {
    param([string]$DistDir, [switch]$NoBinaries)
    $problems = @()
    $latin1 = [Text.Encoding]::GetEncoding(28591)
    $files = @(Get-ChildItem -LiteralPath $DistDir -Recurse -File -Force)
    foreach ($f in $files) {
        $rel = Get-Relative $DistDir $f.FullName
        $top = ($rel -split '\\')[0]
        $ext = $f.Extension.ToLowerInvariant()
        if ($ext -in @('.exe', '.res', '.identcache', '.local', '.bak', '.dsk', '.stat', '.log', '.tmp',
                       '.map', '.drc', '.o', '.tvsconfig') -or $ext -like '.~*') {
            $problems += "мусор сборки: $rel"
        }
        if ($ext -eq '.dcu' -and $top -ne 'Lib') { $problems += "dcu вне Lib: $rel" }
        if ($ext -in @('.bpl', '.dcp') -and $top -notin @('Lib', 'Bin')) { $problems += "bpl/dcp вне Lib/Bin: $rel" }
        if ($NoBinaries -and ($ext -in @('.dcu', '.bpl', '.dcp', '.dll') -or $top -in @('Lib', 'Bin'))) {
            $problems += "бинарник в архиве исходников: $rel"
        }
        if ($f.Name -like '.*-memory.md' -or $f.Name -like 'pfull_*') { $problems += "служебный файл: $rel" }
        if ($rel -match '(^|\\)(__history|__recovery)\\') { $problems += "история IDE: $rel" }
        if ($rel -match '\\Spec\\[^\\]*-\d{8}\.html$') { $problems += "копия спецификации: $rel" }
        foreach ($ex in $Script:Excluded.Keys) { if ($rel -ieq $ex) { $problems += "исключённый файл: $rel" } }
        $text = $latin1.GetString([IO.File]::ReadAllBytes($f.FullName))
        $tokens = [regex]::Matches($text, $Script:TokenPattern)
        if ($tokens.Count -gt 0) { $problems += ('похоже на токен бота ({0} шт.): {1}' -f $tokens.Count, $rel) }
    }
    return [pscustomobject]@{ Files = $files.Count; Problems = $problems }
}

function Assert-Dist {
    param([string]$DistDir, [switch]$NoBinaries)
    $check = Test-Dist -DistDir $DistDir -NoBinaries:$NoBinaries
    if ($check.Problems.Count -gt 0) {
        foreach ($p in $check.Problems) { Write-Info $p 'Red' }
        throw ('Проверка дистрибутива {0} не пройдена: {1} замечаний.' -f $DistDir, $check.Problems.Count)
    }
    Write-Info ('OK: {0} файлов, мусора нет, совпадений с шаблоном токена {1} — 0.' -f $check.Files, $Script:TokenPattern) 'Green'
}

function Show-Tree {
    param([string]$DistDir)
    $name = Split-Path -Leaf $DistDir
    Write-Info "$name\"
    foreach ($d in (Get-ChildItem -LiteralPath $DistDir -Directory | Sort-Object Name)) {
        $n = @(Get-ChildItem -LiteralPath $d.FullName -Recurse -File).Count
        Write-Info ('  {0}\  ({1} файлов)' -f $d.Name, $n)
        foreach ($s in (Get-ChildItem -LiteralPath $d.FullName -Directory | Sort-Object Name)) {
            $m = @(Get-ChildItem -LiteralPath $s.FullName -Recurse -File).Count
            Write-Info ('    {0}\  ({1})' -f $s.Name, $m)
        }
    }
    foreach ($f in (Get-ChildItem -LiteralPath $DistDir -File | Sort-Object Name)) {
        Write-Info ('  {0}' -f $f.Name)
    }
}

$exitCode = 0
try {
    $version = Read-PasConst 'Source\TgBot.Base.pas' 'TgBotVersion'
    $api = Read-PasConst 'Source\TgBot.pas' 'TgBotApiVersion'
    if (-not $OutRoot) { $OutRoot = Join-Path $Script:Root 'Dist' }
    $OutRoot = $OutRoot.TrimEnd('\')
    if (-not $TempRoot) { $TempRoot = Join-Path $env:TEMP 'TgBotDist' }
    $TempRoot = $TempRoot.TrimEnd('\')
    if ($TempRoot.StartsWith($OutRoot + '\', [StringComparison]::OrdinalIgnoreCase) -or $TempRoot -ieq $OutRoot) {
        throw "TempRoot не должен быть внутри папки результата ($OutRoot)."
    }
    $distName = "TgBot-$version"
    $stageRoot = Join-Path $TempRoot 'stage'
    $srcDir = Join-Path (Join-Path $stageRoot 'src') $distName
    $preDir = Join-Path (Join-Path $stageRoot 'prebuilt') $distName
    $srcZipName = "$distName-Исходники.zip"
    $preZipName = "$distName-Готовые-пакеты.zip"
    $setupName = "$distName-Setup"

    Write-Step "TgBot $version (Bot API $api): сборка дистрибутива"
    Write-Info "Проект:    $Script:Root"
    Write-Info "Результат: $OutRoot"
    Write-Info "Staging:   $stageRoot"

    # ---- 1. белый список
    $list = @()
    $list += Get-WhiteFiles 'Source' @('*.pas') -Recurse
    $list += Get-WhiteFiles 'Source\Generated' @('*.inc')
    $list += Get-WhiteFiles 'Source\Design' @('*.rc', '*.dcr')
    $list += Get-WhiteFiles 'Source\Design\Icons' @('*.bmp', '*.png', 'MakeIcons.ps1')
    $list += Get-WhiteFiles 'Packages' @('*.dpk', '*.dproj', '*.groupproj')
    $list += Get-WhiteFiles 'Demos' @('*.dpr', '*.pas', '*.dfm', '*.dproj', '*.groupproj') -Recurse
    $list += Get-WhiteFiles 'Tests' @('*.dpr', '*.dproj')
    $list += Get-WhiteFiles 'Tools\TgBotGen' @('*.dpr', '*.pas', '*.dproj')
    $list += Get-WhiteFiles 'Tools\TgBotGen\Spec' @("api-$api.html", "model-$api.json", "returns-$api.json", 'overrides.json')
    $list += Get-WhiteFiles 'Install' @('*.ps1', '*.cmd')
    $list += Get-WhiteFiles '.' @('README.md', 'README.ru.md', 'CHANGELOG.md', 'LICENSE', 'LICENSE.txt', 'LICENSE.md')
    $list = @($list | Where-Object { $_ } | ForEach-Object { $_ -replace '^\.\\', '' } |
        Where-Object { -not $Script:Excluded.ContainsKey($_) } | Sort-Object -Unique)

    $required = @('Source\TgBot.pas', 'Source\TgBot.Base.pas', 'Source\Design\TgBot.Reg.pas',
        'Packages\TgBotRT.dpk', 'Packages\TgBotIndyRT.dpk', 'Packages\TgBotDT.dpk', 'Packages\TgBot.groupproj',
        'Tests\TgBotTests.dpr', 'Tools\TgBotGen\TgBotGen.dpr',
        "Tools\TgBotGen\Spec\api-$api.html", "Tools\TgBotGen\Spec\model-$api.json",
        "Tools\TgBotGen\Spec\returns-$api.json", 'Tools\TgBotGen\Spec\overrides.json',
        'Install\Install.ps1', 'Install\Uninstall.ps1', 'Install\Install.cmd', 'Install\Uninstall.cmd',
        'README.md', 'README.ru.md', 'CHANGELOG.md')
    $missing = @($required | Where-Object { $list -notcontains $_ })
    if ($missing.Count -gt 0) { throw ('Нет обязательных файлов: ' + ($missing -join ', ')) }
    $hasLicense = @($list | Where-Object { $_ -like 'LICENSE*' }).Count -gt 0

    if (-not (Test-Path -LiteralPath $OutRoot)) { New-Item -ItemType Directory -Path $OutRoot -Force | Out-Null }
    if (-not (Test-Path -LiteralPath $TempRoot)) { New-Item -ItemType Directory -Path $TempRoot -Force | Out-Null }
    # Прежний комплект этой версии, в т.ч. старого формата (папка TgBot-<версия>, .zip, .sha256.txt).
    $previous = @(Get-ChildItem -LiteralPath $OutRoot -Force |
        Where-Object { $_.Name -like "$distName*" -or $_.Name -eq $Script:SumsName })
    # Сначала проверяем, что ничего не занято, — иначе комплект удалился бы частично.
    $locked = @($previous | ForEach-Object {
            if ($_.PSIsContainer) { Get-ChildItem -LiteralPath $_.FullName -Recurse -File -Force } else { $_ }
        } | Where-Object { Test-Locked $_.FullName } | ForEach-Object { $_.FullName })
    if ($locked.Count -gt 0) {
        throw ('Файлы прежнего комплекта заняты другим процессом (закройте установщик/архиватор): ' + ($locked -join ', '))
    }
    foreach ($p in $previous) { Remove-Generated -Path $p.FullName -OutDir $OutRoot }
    Remove-Stage -StageRoot $stageRoot -TempDir $TempRoot

    # ---- 1. исходники: белый список + «Как установить.txt»
    Write-Step "1. Копирование по белому списку ($($list.Count) файлов) + $Script:HowToName"
    foreach ($rel in $list) { Copy-ToDist -Rel $rel -DistDir $srcDir }
    New-HowTo -DestDir $srcDir -WithPrebuilt $false -Version $version -Api $api
    foreach ($ex in $Script:Excluded.Keys) {
        if (Test-Path -LiteralPath (Join-Path $Script:Root $ex)) { Write-Info ("исключён {0} — {1}" -f $ex, $Script:Excluded[$ex]) 'Yellow' }
    }
    if (-not $hasLicense) { Write-Info 'LICENSE в корне проекта нет — в дистрибутив не добавлен (нужен текст лицензии от автора).' 'Yellow' }

    Write-Step '2. Проверка исходников: нет бинарников, мусора сборки, служебных файлов и токенов'
    Assert-Dist -DistDir $srcDir -NoBinaries

    $outputs = @()
    Write-Step "3. Архив $srcZipName"
    New-Zip -SourceDir $srcDir -ZipPath (Join-Path $OutRoot $srcZipName)
    $outputs += $srcZipName

    # ---- 4. установщик Inno Setup
    if ($Setup) {
        Write-Step "4. Установщик $setupName.exe (Inno Setup)"
        $iscc = Find-Iscc
        $iss = Join-Path $PSScriptRoot 'TgBot.iss'
        $ico = Join-Path $Script:Root 'Source\Design\Icons\TgBot.ico'
        if (-not (Test-Path -LiteralPath $ico)) {
            & powershell.exe -NoProfile -ExecutionPolicy Bypass -File (Join-Path $PSScriptRoot 'MakeIco.ps1') -OutFile $ico
            if ($LASTEXITCODE -ne 0) { throw "Не удалось создать иконку $ico." }
        }
        $isccArgs = @("/DAppVersion=$version", "/DSourceDir=$srcDir", "/DIconFile=$ico", "/O$OutRoot", "/F$setupName")
        $license = @($list | Where-Object { $_ -like 'LICENSE*' } | Select-Object -First 1)
        if ($license.Count -gt 0) { $isccArgs += ('/DLicenseFile=' + (Join-Path $srcDir $license[0])) }
        $isccArgs += $iss
        $isccLog = Join-Path $TempRoot "$setupName-iscc.log"
        Write-Info "ISCC: $iscc"
        $eap = $ErrorActionPreference
        $ErrorActionPreference = 'Continue'
        try {
            $isccOut = @(& $iscc @isccArgs 2>&1 | ForEach-Object { [string]$_ })
            $isccExit = $LASTEXITCODE
        } finally {
            $ErrorActionPreference = $eap
        }
        [IO.File]::WriteAllLines($isccLog, [string[]]$isccOut, (New-Object Text.UTF8Encoding($true)))
        if ($isccExit -ne 0 -or -not (Test-Path -LiteralPath (Join-Path $OutRoot "$setupName.exe"))) {
            foreach ($l in ($isccOut | Select-Object -Last 15)) { Write-Info $l 'Red' }
            throw "ISCC завершился с ошибкой (код $isccExit). Журнал: $isccLog"
        }
        $isccWarn = @($isccOut | Where-Object { $_ -match '^\s*Warning' })
        foreach ($w in $isccWarn) { Write-Info $w 'Yellow' }
        $packed = @($isccOut | Where-Object { $_ -match '^\s*Compressing:' }).Count
        Write-Info ('OK: файлов в установщике {0}, предупреждений {1}. Журнал: {2}' -f $packed, $isccWarn.Count, $isccLog) 'Green'
        $outputs += "$setupName.exe"
    }

    # ---- 5. готовые пакеты
    if ($Prebuilt) {
        Write-Step "5. Готовые пакеты (-Prebuilt): $preZipName"
        New-Item -ItemType Directory -Path (Split-Path -Parent $preDir) -Force | Out-Null
        Copy-Item -LiteralPath $srcDir -Destination $preDir -Recurse
        $installer = Join-Path $preDir 'Install\Install.ps1'
        $buildLog = Join-Path $TempRoot "$distName-prebuilt.log"
        & powershell.exe -NoProfile -ExecutionPolicy Bypass -File $installer -All -BuildOnly -LogPath $buildLog -TempRoot $TempRoot
        if ($LASTEXITCODE -ne 0) {
            throw "Сборка пакетов завершилась с ошибкой (код $LASTEXITCODE). Журнал: $buildLog"
        }
        $libRoot = Join-Path $preDir 'Lib'
        if (-not (Test-Path -LiteralPath $libRoot)) { throw 'После сборки нет папки Lib — не найдено ни одной Delphi 10.4+.' }
        $builtFor = (@(Get-ChildItem -LiteralPath $libRoot -Directory | Sort-Object Name | ForEach-Object { $_.Name }) -join ', ')
        New-HowTo -DestDir $preDir -WithPrebuilt $true -Version $version -Api $api -PrebuiltFor $builtFor
        foreach ($bpl in (Get-ChildItem -LiteralPath $libRoot -Recurse -File -Filter '*.bpl')) {
            $rel = Get-Relative $libRoot $bpl.DirectoryName
            $binDir = Join-Path (Join-Path $preDir 'Bin') $rel
            if (-not (Test-Path -LiteralPath $binDir)) { New-Item -ItemType Directory -Path $binDir -Force | Out-Null }
            Copy-Item -LiteralPath $bpl.FullName -Destination $binDir
        }
        foreach ($d in (Get-ChildItem -LiteralPath $libRoot -Directory)) {
            foreach ($p in (Get-ChildItem -LiteralPath $d.FullName -Directory)) {
                $files = @(Get-ChildItem -LiteralPath $p.FullName -File)
                $bpls = ($files | Where-Object { $_.Extension -eq '.bpl' } | ForEach-Object { $_.Name }) -join ', '
                Write-Info ('Lib\{0}\{1}: {2} файлов; bpl: {3}' -f $d.Name, $p.Name, $files.Count, $bpls) 'Green'
            }
        }
        Assert-Dist -DistDir $preDir
        New-Zip -SourceDir $preDir -ZipPath (Join-Path $OutRoot $preZipName)
        $outputs += $preZipName
    }

    # ---- 6. контрольные суммы и итог
    Write-Step "6. Контрольные суммы: $Script:SumsName"
    Write-Sums -OutDir $OutRoot -Names $outputs

    Write-Step "Состав $srcZipName"
    Show-Tree $srcDir
    Write-Step "Готово: комплект в $OutRoot"
    foreach ($n in ($outputs + $Script:SumsName)) {
        $f = Get-Item -LiteralPath (Join-Path $OutRoot $n)
        Write-Info ('{0,-36} {1,14:N0} байт' -f $n, $f.Length) 'Green'
    }
    foreach ($e in @(Get-ChildItem -LiteralPath $OutRoot -Force | Where-Object { ($outputs + $Script:SumsName) -notcontains $_.Name })) {
        Write-Info "в папке результата есть посторонний файл (не из комплекта): $($e.Name)" 'Yellow'
    }
    if ($KeepStage) {
        Write-Info "Staging сохранён: $stageRoot"
    } else {
        Remove-Stage -StageRoot $stageRoot -TempDir $TempRoot
    }
} catch {
    $exitCode = 1
    Write-Host ''
    Write-Host ('ОШИБКА: ' + $_.Exception.Message) -ForegroundColor Red
}
exit $exitCode
