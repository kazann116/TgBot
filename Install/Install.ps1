<#
.SYNOPSIS
  Установка TgBot (Telegram Bot API для Delphi) в Delphi 10.4 и новее.

.DESCRIPTION
  Для каждой выбранной версии Delphi:
   1. Собирает пакеты TgBotRT, TgBotIndyRT (Win32, Win64) и TgBotDT (Win32) через MSBuild
      (окружение берётся из bin\rsvars.bat). DCU, DCP и BPL складываются в Lib\<Delphi>\<Platform>
      дистрибутива. С -UsePrebuilt используются уже собранные файлы из Lib (если они есть).
   2. Копирует BPL в папку "Package DPL Output" IDE (обычно $(BDSCOMMONDIR)\Bpl, для Win64 — Bpl\Win64),
      DCP — в "Package DCP Output" (обычно $(BDSCOMMONDIR)\Dcp).
   3. Регистрирует TgBotDT в HKCU\Software\Embarcadero\BDS\<ver>\Known Packages, добавляет в
      Library\<Platform> "Search Path" папки Lib\<Delphi>\<Platform> и Source, в "Browsing Path" — Source
      (Win32, Win64 и Linux64, если платформа есть в IDE). Существующие пути не дублируются.
  IDE должна быть закрыта. -WhatIf (-DryRun) только печатает план и ничего не меняет.
  Журнал — Install.log рядом со скриптом.

.PARAMETER Delphi
  Версии BDS (23.0, 21.0) или имена (D12, D10.4). Несколько — через запятую.
.PARAMETER All
  Все найденные Delphi 10.4+.
.PARAMETER UsePrebuilt
  Не собирать, если в Lib\<Delphi>\<Platform> уже есть собранные пакеты.
.PARAMETER WhatIf
  Показать план без изменений (синоним -DryRun).
.PARAMETER Uninstall
  Обратные действия (используется Uninstall.ps1).
.PARAMETER BuildOnly
  Только собрать пакеты в Lib (без реестра и копирования в IDE). Используется MakeDist.ps1.

.EXAMPLE
  powershell -ExecutionPolicy Bypass -File Install.ps1 -Delphi 23.0 -WhatIf
.EXAMPLE
  Install.cmd -All
#>
param(
    [string[]]$Delphi = @(),
    [switch]$All,
    [switch]$UsePrebuilt,
    [Alias('DryRun')]
    [switch]$WhatIf,
    [switch]$Uninstall,
    [switch]$BuildOnly,
    [string]$LogPath = '',
    [string]$TempRoot = ''
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$Script:DistRoot = Split-Path -Parent $PSScriptRoot
$Script:SourceDir = Join-Path $Script:DistRoot 'Source'
$Script:PackagesDir = Join-Path $Script:DistRoot 'Packages'
$Script:LibRoot = Join-Path $Script:DistRoot 'Lib'
$Script:LogFile = $null
$Script:ExitCode = 0
$Script:StageDir = $null
$Script:Changes = 0

# Пакеты в порядке сборки. DT — только Win32: IDE 32-битная.
$Script:PackageList = @(
    [pscustomobject]@{ Name = 'TgBotRT';     Platforms = @('Win32', 'Win64'); Design = $false },
    [pscustomobject]@{ Name = 'TgBotIndyRT'; Platforms = @('Win32', 'Win64'); Design = $false },
    [pscustomobject]@{ Name = 'TgBotDT';     Platforms = @('Win32');          Design = $true }
)
$Script:BuildPlatforms = @('Win32', 'Win64')
$Script:PathPlatforms = @('Win32', 'Win64', 'Linux64')

$Script:DelphiNames = @{
    '21.0' = @('D10.4', 'Delphi 10.4 Sydney')
    '22.0' = @('D11', 'Delphi 11 Alexandria')
    '23.0' = @('D12', 'Delphi 12 Athens')
    '37.0' = @('D13', 'Delphi 13 Florence')
}

# ---------------------------------------------------------------- журнал

function Initialize-Log {
    $name = 'Install.log'
    if ($Uninstall) { $name = 'Uninstall.log' }
    $candidates = @()
    if ($LogPath) { $candidates += $LogPath }
    $candidates += (Join-Path $PSScriptRoot $name)
    $candidates += (Join-Path $env:TEMP ('TgBot-' + $name))
    foreach ($c in $candidates) {
        try {
            $dir = Split-Path -Parent $c
            if ($dir -and -not (Test-Path -LiteralPath $dir)) { New-Item -ItemType Directory -Path $dir -Force | Out-Null }
            Add-Content -LiteralPath $c -Value '' -Encoding UTF8
            $Script:LogFile = $c
            return
        } catch {
            continue
        }
    }
}

function Write-Log {
    param([string]$Message, [string]$Level = 'INFO')
    switch ($Level) {
        'ERROR' { Write-Host $Message -ForegroundColor Red }
        'WARN'  { Write-Host $Message -ForegroundColor Yellow }
        'PLAN'  { Write-Host ('  [план] ' + $Message) -ForegroundColor Cyan }
        'DO'    { Write-Host ('  ' + $Message) -ForegroundColor Green }
        'HEAD'  { Write-Host ''; Write-Host $Message -ForegroundColor White }
        default { Write-Host $Message }
    }
    if ($Script:LogFile) {
        $line = '{0:yyyy-MM-dd HH:mm:ss} [{1}] {2}' -f (Get-Date), $Level, $Message
        try { Add-Content -LiteralPath $Script:LogFile -Value $line -Encoding UTF8 } catch { }
    }
}

# Действие: в режиме -WhatIf только печатается, иначе выполняется.
function Invoke-Action {
    param([string]$Description, [scriptblock]$Action)
    if ($WhatIf) {
        Write-Log $Description 'PLAN'
    } else {
        Write-Log $Description 'DO'
        & $Action
        $Script:Changes++
    }
}

# ---------------------------------------------------------------- версия библиотеки

function Get-TgBotVersion {
    $base = Join-Path $Script:SourceDir 'TgBot.Base.pas'
    if (-not (Test-Path -LiteralPath $base)) {
        throw "Не найден $base. Запускайте установщик из папки Install дистрибутива TgBot."
    }
    $text = [IO.File]::ReadAllText($base, [Text.Encoding]::UTF8)
    $m = [regex]::Match($text, "\bTgBotVersion\s*=\s*'([^']+)'")
    if ($m.Success) { return $m.Groups[1].Value }
    return '?'
}

function Get-DesignDescription {
    $dpk = Join-Path $Script:PackagesDir 'TgBotDT.dpk'
    $text = [IO.File]::ReadAllText($dpk, [Text.Encoding]::UTF8)
    $m = [regex]::Match($text, "\{\`$DESCRIPTION\s+'([^']*)'\}")
    if ($m.Success) { return $m.Groups[1].Value }
    return 'Telegram Bot API для Delphi (design-time)'
}

# ---------------------------------------------------------------- поиск Delphi

function Get-DelphiName {
    param([string]$Version, [int]$Major)
    if ($Script:DelphiNames.ContainsKey($Version)) { return $Script:DelphiNames[$Version] }
    return @("BDS$Version", "RAD Studio $Version")
}

function Get-DelphiInstalls {
    $found = @{}
    foreach ($base in @('SOFTWARE\WOW6432Node\Embarcadero\BDS', 'SOFTWARE\Embarcadero\BDS')) {
        $key = [Microsoft.Win32.Registry]::LocalMachine.OpenSubKey($base, $false)
        if ($null -eq $key) { continue }
        try {
            foreach ($ver in $key.GetSubKeyNames()) {
                if ($ver -notmatch '^(\d+)\.(\d+)$') { continue }
                $major = [int]$Matches[1]
                if ($major -lt 21) { continue }
                if ($found.ContainsKey($ver)) { continue }
                $sub = $key.OpenSubKey($ver, $false)
                if ($null -eq $sub) { continue }
                try {
                    $root = [string]$sub.GetValue('RootDir', '')
                    $productVersion = [string]$sub.GetValue('ProductVersion', '')
                } finally {
                    $sub.Close()
                }
                if (-not $root) { continue }
                $root = $root.TrimEnd('\')
                if (-not (Test-Path -LiteralPath (Join-Path $root 'bin\rsvars.bat'))) { continue }
                if ($productVersion -match '^\d+$') {
                    $suffix = [string]([int]$productVersion * 10)
                } elseif ($major -le 23) {
                    $suffix = [string](($major + 6) * 10)
                } else {
                    $suffix = [string]($major * 10)
                }
                $names = Get-DelphiName -Version $ver -Major $major
                $found[$ver] = [pscustomobject]@{
                    Version  = $ver
                    Major    = $major
                    RootDir  = $root
                    Short    = $names[0]
                    Title    = $names[1]
                    Suffix   = $suffix
                    HasWin64 = (Test-Path -LiteralPath (Join-Path $root 'bin\dcc64.exe'))
                }
            }
        } finally {
            $key.Close()
        }
    }
    return @($found.Values | Sort-Object Major)
}

function Select-Delphi {
    param([object[]]$Installs)
    if ($All) { return $Installs }
    $wanted = @()
    foreach ($d in $Delphi) { $wanted += @($d -split '[,;\s]+' | Where-Object { $_ }) }
    if ($wanted.Count -eq 0) {
        Write-Log 'Найдены версии Delphi:' 'HEAD'
        for ($i = 0; $i -lt $Installs.Count; $i++) {
            Write-Log ('  {0}. {1} (BDS {2}) — {3}' -f ($i + 1), $Installs[$i].Title, $Installs[$i].Version, $Installs[$i].RootDir)
        }
        $answer = Read-Host 'Номер версии (несколько — через запятую), A — все, пусто — отмена'
        if (-not $answer) { throw 'Отменено пользователем.' }
        if ($answer.Trim() -match '^[AaАа]$') { return $Installs }
        $result = @()
        foreach ($n in ($answer -split '[,;\s]+' | Where-Object { $_ })) {
            $idx = 0
            if (-not [int]::TryParse($n, [ref]$idx) -or $idx -lt 1 -or $idx -gt $Installs.Count) {
                throw "Неверный номер: $n"
            }
            $result += $Installs[$idx - 1]
        }
        return $result
    }
    $result = @()
    foreach ($w in $wanted) {
        $norm = $w.Trim()
        if ($norm -match '^\d+$') { $norm = $norm + '.0' }
        $hit = @($Installs | Where-Object {
            $_.Version -eq $norm -or $_.Short -ieq $w -or ('D' + $w) -ieq $_.Short
        })
        if ($hit.Count -eq 0) {
            $list = ($Installs | ForEach-Object { '{0} ({1})' -f $_.Version, $_.Short }) -join ', '
            throw "Delphi '$w' не найдена. Установлены: $list."
        }
        $result += $hit[0]
    }
    return $result
}

# ---------------------------------------------------------------- окружение rsvars.bat

function Get-RsVars {
    param([object]$Inst)
    $bat = Join-Path $Inst.RootDir 'bin\rsvars.bat'
    $vars = [ordered]@{}
    foreach ($line in [IO.File]::ReadAllLines($bat, [Text.Encoding]::Default)) {
        $m = [regex]::Match($line, '^\s*@?SET\s+([^=\s]+)=(.*)$', 'IgnoreCase')
        if (-not $m.Success) { continue }
        $name = $m.Groups[1].Value
        $value = $m.Groups[2].Value
        foreach ($ref in [regex]::Matches($value, '%([^%]+)%')) {
            $refName = $ref.Groups[1].Value
            if ($vars.Contains($refName)) {
                $refValue = [string]$vars[$refName]
            } else {
                $refValue = [string][Environment]::GetEnvironmentVariable($refName)
            }
            $value = $value.Replace($ref.Value, $refValue)
        }
        $vars[$name] = $value
    }
    if (-not $vars.Contains('BDSCOMMONDIR') -or -not $vars.Contains('FrameworkDir')) {
        throw "Не удалось прочитать окружение из $bat."
    }
    return $vars
}

function Invoke-WithRsVars {
    param([System.Collections.IDictionary]$Vars, [scriptblock]$Body)
    $saved = @{}
    foreach ($n in $Vars.Keys) {
        $saved[$n] = [Environment]::GetEnvironmentVariable($n, 'Process')
        $v = [string]$Vars[$n]
        if ($v -eq '') { $v = $null }
        [Environment]::SetEnvironmentVariable($n, $v, 'Process')
    }
    try {
        & $Body
    } finally {
        foreach ($n in $saved.Keys) { [Environment]::SetEnvironmentVariable($n, $saved[$n], 'Process') }
    }
}

# ---------------------------------------------------------------- реестр HKCU (BDS)

function Get-BdsKeyPath {
    param([object]$Inst, [string]$Sub)
    $p = 'Software\Embarcadero\BDS\' + $Inst.Version
    if ($Sub) { $p = $p + '\' + $Sub }
    return $p
}

function Open-UserKey {
    param([string]$Path, [bool]$Writable = $false)
    return [Microsoft.Win32.Registry]::CurrentUser.OpenSubKey($Path, $Writable)
}

# Есть ли настройки IDE в HKCU (IDE запускалась хотя бы раз).
function Test-BdsUserKey {
    param([object]$Inst)
    $key = Open-UserKey -Path (Get-BdsKeyPath $Inst '')
    if ($null -eq $key) { return $false }
    $key.Close()
    return $true
}

function Get-RegString {
    param([Microsoft.Win32.RegistryKey]$Key, [string]$Name)
    if ($null -eq $Key) { return $null }
    if (-not ($Key.GetValueNames() -contains $Name)) { return $null }
    return [string]$Key.GetValue($Name, '', [Microsoft.Win32.RegistryValueOptions]::DoNotExpandEnvironmentNames)
}

function Set-RegString {
    param([string]$Path, [string]$Name, [string]$Value)
    $key = Open-UserKey -Path $Path -Writable $true
    if ($null -eq $key) { throw "Нет ключа реестра HKCU\$Path." }
    try {
        $kind = [Microsoft.Win32.RegistryValueKind]::String
        if ($key.GetValueNames() -contains $Name) { $kind = $key.GetValueKind($Name) }
        $key.SetValue($Name, $Value, $kind)
    } finally {
        $key.Close()
    }
}

function Remove-RegValue {
    param([string]$Path, [string]$Name)
    $key = Open-UserKey -Path $Path -Writable $true
    if ($null -eq $key) { return }
    try { $key.DeleteValue($Name, $false) } finally { $key.Close() }
}

# Подстановка $(BDSCOMMONDIR), $(Platform) и т.п. в значения из реестра IDE.
function Expand-BdsValue {
    param([string]$Value, [System.Collections.IDictionary]$Vars, [string]$Platform)
    $result = $Value
    foreach ($m in [regex]::Matches($Value, '\$\(([^)]+)\)')) {
        $n = $m.Groups[1].Value
        $r = $null
        if ($n -ieq 'Platform') { $r = $Platform }
        elseif ($Vars.Contains($n)) { $r = [string]$Vars[$n] }
        else { $r = [Environment]::GetEnvironmentVariable($n) }
        if ($null -ne $r) { $result = $result.Replace($m.Value, $r) }
    }
    return $result
}

function Get-OutputDir {
    param([object]$Inst, [System.Collections.IDictionary]$Vars, [string]$Platform, [string]$ValueName, [string]$Default)
    $key = Open-UserKey -Path (Get-BdsKeyPath $Inst ('Library\' + $Platform))
    try { $raw = Get-RegString -Key $key -Name $ValueName } finally { if ($key) { $key.Close() } }
    $fallback = Join-Path $Vars['BDSCOMMONDIR'] $Default
    if ($Platform -ne 'Win32') { $fallback = Join-Path $fallback $Platform }
    if (-not $raw) { return $fallback }
    $expanded = Expand-BdsValue -Value $raw -Vars $Vars -Platform $Platform
    if ($expanded -match '\$\(' -or -not [IO.Path]::IsPathRooted($expanded)) { return $fallback }
    return $expanded.TrimEnd('\')
}

function Test-SamePath {
    param([string]$A, [string]$B)
    return ($A.Trim().TrimEnd('\').ToLowerInvariant() -eq $B.Trim().TrimEnd('\').ToLowerInvariant())
}

# ---------------------------------------------------------------- сборка

function Get-LibDir {
    param([object]$Inst, [string]$Platform)
    return (Join-Path (Join-Path $Script:LibRoot $Inst.Short) $Platform)
}

function Get-PackageFiles {
    param([object]$Inst, [object]$Package)
    $files = @("$($Package.Name)$($Inst.Suffix).bpl")
    if (-not $Package.Design) { $files += "$($Package.Name).dcp" }
    return $files
}

function Test-Prebuilt {
    param([object]$Inst, [string]$Platform)
    $lib = Get-LibDir $Inst $Platform
    foreach ($p in $Script:PackageList) {
        if ($p.Platforms -notcontains $Platform) { continue }
        foreach ($f in (Get-PackageFiles $Inst $p)) {
            if (-not (Test-Path -LiteralPath (Join-Path $lib $f))) { return $false }
        }
    }
    return $true
}

function Initialize-Stage {
    if ($Script:StageDir) { return }
    $root = $TempRoot
    if (-not $root) { $root = $env:TEMP }
    $Script:StageDir = Join-Path $root ('TgBotBuild-' + [guid]::NewGuid().ToString('N').Substring(0, 8))
    New-Item -ItemType Directory -Path $Script:StageDir -Force | Out-Null
    Copy-Item -LiteralPath $Script:SourceDir -Destination (Join-Path $Script:StageDir 'Source') -Recurse
    $pk = Join-Path $Script:StageDir 'Packages'
    New-Item -ItemType Directory -Path $pk -Force | Out-Null
    Get-ChildItem -LiteralPath $Script:PackagesDir -File |
        Where-Object { $_.Extension -in @('.dpk', '.dproj') } |
        ForEach-Object { Copy-Item -LiteralPath $_.FullName -Destination $pk }
    New-Item -ItemType Directory -Path (Join-Path $Script:StageDir 'logs') -Force | Out-Null
    Write-Log "Временная папка сборки: $Script:StageDir"
}

function Invoke-PackageBuild {
    param([object]$Inst, [System.Collections.IDictionary]$Vars, [object]$Package, [string]$Platform, [string]$OutDir)
    $msbuild = Join-Path $Vars['FrameworkDir'] 'MSBuild.exe'
    if (-not (Test-Path -LiteralPath $msbuild)) { throw "Не найден MSBuild: $msbuild" }
    $dproj = Join-Path $Script:StageDir ('Packages\' + $Package.Name + '.dproj')
    $log = Join-Path $Script:StageDir ('logs\{0}-{1}-{2}.log' -f $Inst.Short, $Platform, $Package.Name)
    if (-not (Test-Path -LiteralPath $OutDir)) { New-Item -ItemType Directory -Path $OutDir -Force | Out-Null }
    $msArgs = @(
        $dproj, '/t:Build', '/p:Config=Release', "/p:Platform=$Platform",
        "/p:DCC_DcuOutput=$OutDir", "/p:DCC_BplOutput=$OutDir", "/p:DCC_DcpOutput=$OutDir",
        "/p:DCC_UnitSearchPath=$OutDir", '/nologo', '/v:quiet', '/m:1',
        "/flp:LogFile=$log;Verbosity=normal;Encoding=UTF-8"
    )
    $exit = 0
    Invoke-WithRsVars -Vars $Vars -Body {
        $old = $ErrorActionPreference
        $ErrorActionPreference = 'Continue'
        try {
            & $msbuild @msArgs 2>&1 | Out-Null
            $Script:LastMsBuildExit = $LASTEXITCODE
        } finally {
            $ErrorActionPreference = $old
        }
    }
    $exit = $Script:LastMsBuildExit
    $lines = @()
    if (Test-Path -LiteralPath $log) { $lines = @([IO.File]::ReadAllLines($log, [Text.Encoding]::UTF8)) }
    $diag = @($lines | Where-Object { $_ -match '(?i)\b(error|fatal|warning|hint)\s+([EFWH]\d{4}|MSB\d{4})' } | Sort-Object -Unique)
    $errors = @($diag | Where-Object { $_ -match '(?i)\b(error|fatal)\s+' })
    $warnings = @($diag | Where-Object { $_ -match '(?i)\bwarning\s+W\d{4}' -or $_ -match '(?i)\bwarning\s+MSB\d{4}' })
    $hints = @($diag | Where-Object { $_ -match '(?i)\b(hint|warning)\s+H\d{4}' })
    if ($exit -ne 0 -or $errors.Count -gt 0) {
        foreach ($e in ($errors | Select-Object -First 20)) { Write-Log $e 'ERROR' }
        $Script:KeepStage = $true
        throw ('Сборка {0} ({1}, {2}) завершилась с ошибкой (код MSBuild {3}). Полный лог: {4}' -f $Package.Name, $Platform, $Inst.Title, $exit, $log)
    }
    foreach ($w in ($warnings + $hints)) { Write-Log $w 'WARN' }
    Write-Log ('  {0} {1}: OK (ошибок 0, предупреждений {2}, подсказок {3})' -f $Package.Name, $Platform, $warnings.Count, $hints.Count)
    $Script:BuildSummary += [pscustomobject]@{
        Delphi = $Inst.Short; Platform = $Platform; Package = $Package.Name
        Errors = 0; Warnings = $warnings.Count; Hints = $hints.Count
    }
}

function Invoke-Build {
    param([object]$Inst, [System.Collections.IDictionary]$Vars, [string[]]$Platforms)
    foreach ($pl in $Platforms) {
        $lib = Get-LibDir $Inst $pl
        if ($UsePrebuilt -and (Test-Prebuilt $Inst $pl)) {
            Write-Log "  $pl — используются готовые пакеты из $lib (-UsePrebuilt)"
            continue
        }
        if ($UsePrebuilt) { Write-Log "  $pl — готовых пакетов нет в $lib, собираю из исходников" 'WARN' }
        foreach ($p in $Script:PackageList) {
            if ($p.Platforms -notcontains $pl) { continue }
            if ($WhatIf) {
                Write-Log ('собрать {0} ({1}, Release) MSBuild -> {2}' -f $p.Name, $pl, $lib) 'PLAN'
                continue
            }
            Initialize-Stage
            Invoke-PackageBuild -Inst $Inst -Vars $Vars -Package $p -Platform $pl -OutDir $lib
        }
    }
}

# ---------------------------------------------------------------- пути Library

function Add-PathEntry {
    param([object]$Inst, [string]$Platform, [string]$ValueName, [string]$Entry)
    $path = Get-BdsKeyPath $Inst ('Library\' + $Platform)
    $key = Open-UserKey -Path $path
    try { $current = Get-RegString -Key $key -Name $ValueName } finally { if ($key) { $key.Close() } }
    if ($null -eq $current) { $current = '' }
    $items = @($current.Split(';') | Where-Object { $_.Trim() -ne '' })
    if (($ValueName -eq 'Search Path') -and (Test-SamePath $Entry $Script:SourceDir)) {
        # Другая копия исходников TgBot в пути даст конфликт модулей — только предупреждаем.
        foreach ($i in $items) {
            if ($i -match '\$\(' -or (Test-SamePath $i $Entry)) { continue }
            $hasTgBot = $false
            try { $hasTgBot = Test-Path -LiteralPath (Join-Path $i 'TgBot.pas') } catch { $hasTgBot = $false }
            if ($hasTgBot) {
                Write-Log "  ${Platform} '$ValueName': указана другая копия TgBot — $i. Уберите её вручную, чтобы не было конфликта модулей." 'WARN'
            }
        }
    }
    foreach ($i in $items) {
        if (Test-SamePath $i $Entry) {
            Write-Log "  ${Platform} '$ValueName': уже есть $Entry"
            return
        }
    }
    if ($current.Trim() -eq '') { $new = $Entry } else { $new = $current.TrimEnd(';') + ';' + $Entry }
    Invoke-Action -Description "реестр HKCU\$path '$ValueName': добавить $Entry" -Action {
        Set-RegString -Path $path -Name $ValueName -Value $new
    }
}

function Remove-PathEntry {
    param([object]$Inst, [string]$Platform, [string]$ValueName, [string]$Entry)
    $path = Get-BdsKeyPath $Inst ('Library\' + $Platform)
    $key = Open-UserKey -Path $path
    try { $current = Get-RegString -Key $key -Name $ValueName } finally { if ($key) { $key.Close() } }
    if (-not $current) { return }
    $parts = $current.Split(';')
    $kept = @($parts | Where-Object { -not ($_.Trim() -ne '' -and (Test-SamePath $_ $Entry)) })
    if ($kept.Count -eq $parts.Count) { return }
    $new = $kept -join ';'
    Invoke-Action -Description "реестр HKCU\$path '$ValueName': убрать $Entry" -Action {
        Set-RegString -Path $path -Name $ValueName -Value $new
    }
}

function Get-PathPlatforms {
    param([object]$Inst)
    $result = @()
    foreach ($pl in $Script:PathPlatforms) {
        $key = Open-UserKey -Path (Get-BdsKeyPath $Inst ('Library\' + $pl))
        if ($null -ne $key) { $key.Close(); $result += $pl }
    }
    return $result
}

# ---------------------------------------------------------------- Known Packages

function Get-KnownDesignPackages {
    param([object]$Inst, [string]$SubKey)
    $key = Open-UserKey -Path (Get-BdsKeyPath $Inst $SubKey)
    if ($null -eq $key) { return @() }
    try {
        return @($key.GetValueNames() | Where-Object { $_ -match '(?i)(^|\\)TgBotDT\d*\.bpl$' })
    } finally {
        $key.Close()
    }
}

# ---------------------------------------------------------------- установка

function Invoke-Install {
    param([object]$Inst)
    Write-Log ('{0} (BDS {1}, суффикс пакетов {2}) — {3}' -f $Inst.Title, $Inst.Version, $Inst.Suffix, $Inst.RootDir) 'HEAD'
    $vars = Get-RsVars $Inst
    $platforms = @('Win32')
    if ($Inst.HasWin64) { $platforms += 'Win64' } else { Write-Log '  Win64-компилятор не найден — только Win32.' 'WARN' }

    if (-not $BuildOnly -and -not (Test-BdsUserKey $Inst)) {
        throw "Нет настроек HKCU\Software\Embarcadero\BDS\$($Inst.Version). Запустите эту версию IDE хотя бы раз и закройте её."
    }

    Write-Log 'Сборка пакетов:'
    Invoke-Build -Inst $Inst -Vars $vars -Platforms $platforms
    if ($BuildOnly) { return }

    Write-Log 'Копирование BPL/DCP в папки IDE:'
    $dtBpl = $null
    foreach ($pl in $platforms) {
        $lib = Get-LibDir $Inst $pl
        $bplDir = Get-OutputDir -Inst $Inst -Vars $vars -Platform $pl -ValueName 'Package DPL Output' -Default 'Bpl'
        $dcpDir = Get-OutputDir -Inst $Inst -Vars $vars -Platform $pl -ValueName 'Package DCP Output' -Default 'Dcp'
        foreach ($p in $Script:PackageList) {
            if ($p.Platforms -notcontains $pl) { continue }
            foreach ($f in (Get-PackageFiles $Inst $p)) {
                $src = Join-Path $lib $f
                if ($f -like '*.bpl') { $dstDir = $bplDir } else { $dstDir = $dcpDir }
                $dst = Join-Path $dstDir $f
                if ($p.Design -and $f -like '*.bpl') { $dtBpl = $dst }
                Invoke-Action -Description "копировать $src -> $dstDir" -Action {
                    if (-not (Test-Path -LiteralPath $src)) { throw "Нет файла $src (сборка не выполнена?)." }
                    if (-not (Test-Path -LiteralPath $dstDir)) { New-Item -ItemType Directory -Path $dstDir -Force | Out-Null }
                    Copy-Item -LiteralPath $src -Destination $dst -Force
                }
            }
        }
    }

    Write-Log 'Регистрация в IDE (Known Packages):'
    $kpPath = Get-BdsKeyPath $Inst 'Known Packages'
    $kpDescription = Get-DesignDescription
    foreach ($other in (Get-KnownDesignPackages $Inst 'Known Packages')) {
        if (Test-SamePath $other $dtBpl) { continue }
        Invoke-Action -Description "реестр HKCU\${kpPath}: удалить старую регистрацию '$other'" -Action {
            Remove-RegValue -Path $kpPath -Name $other
        }
    }
    $kpKey = Open-UserKey -Path $kpPath
    try { $existing = Get-RegString -Key $kpKey -Name $dtBpl } finally { if ($kpKey) { $kpKey.Close() } }
    if ($existing -eq $kpDescription) {
        Write-Log "  уже зарегистрирован: $dtBpl"
    } else {
        Invoke-Action -Description "реестр HKCU\${kpPath}: '$dtBpl' = '$kpDescription'" -Action {
            $k = [Microsoft.Win32.Registry]::CurrentUser.CreateSubKey($kpPath)
            try { $k.SetValue($dtBpl, $kpDescription, [Microsoft.Win32.RegistryValueKind]::String) } finally { $k.Close() }
        }
    }
    $dpPath = Get-BdsKeyPath $Inst 'Disabled Packages'
    foreach ($disabled in (Get-KnownDesignPackages $Inst 'Disabled Packages')) {
        Invoke-Action -Description "реестр HKCU\${dpPath}: убрать '$disabled' из отключённых" -Action {
            Remove-RegValue -Path $dpPath -Name $disabled
        }
    }

    Write-Log 'Пути Library (Search Path / Browsing Path):'
    foreach ($pl in (Get-PathPlatforms $Inst)) {
        if ($platforms -contains $pl) {
            Add-PathEntry -Inst $Inst -Platform $pl -ValueName 'Search Path' -Entry (Get-LibDir $Inst $pl)
        }
        Add-PathEntry -Inst $Inst -Platform $pl -ValueName 'Search Path' -Entry $Script:SourceDir
        Add-PathEntry -Inst $Inst -Platform $pl -ValueName 'Browsing Path' -Entry $Script:SourceDir
    }
}

# ---------------------------------------------------------------- удаление

function Invoke-Uninstall {
    param([object]$Inst)
    Write-Log ('{0} (BDS {1}, суффикс пакетов {2})' -f $Inst.Title, $Inst.Version, $Inst.Suffix) 'HEAD'
    if (-not (Test-BdsUserKey $Inst)) {
        Write-Log "  нет настроек HKCU для BDS $($Inst.Version) — пропускаю." 'WARN'
        return
    }
    $vars = Get-RsVars $Inst

    Write-Log 'Known Packages / Disabled Packages:'
    foreach ($sub in @('Known Packages', 'Disabled Packages')) {
        $p = Get-BdsKeyPath $Inst $sub
        foreach ($name in (Get-KnownDesignPackages $Inst $sub)) {
            Invoke-Action -Description "реестр HKCU\${p}: удалить '$name'" -Action {
                Remove-RegValue -Path $p -Name $name
            }
        }
    }

    Write-Log 'Пути Library:'
    foreach ($pl in (Get-PathPlatforms $Inst)) {
        Remove-PathEntry -Inst $Inst -Platform $pl -ValueName 'Search Path' -Entry (Get-LibDir $Inst $pl)
        Remove-PathEntry -Inst $Inst -Platform $pl -ValueName 'Search Path' -Entry $Script:SourceDir
        Remove-PathEntry -Inst $Inst -Platform $pl -ValueName 'Browsing Path' -Entry $Script:SourceDir
    }

    Write-Log 'Файлы BPL/DCP в папках IDE:'
    foreach ($pl in $Script:BuildPlatforms) {
        $bplDir = Get-OutputDir -Inst $Inst -Vars $vars -Platform $pl -ValueName 'Package DPL Output' -Default 'Bpl'
        $dcpDir = Get-OutputDir -Inst $Inst -Vars $vars -Platform $pl -ValueName 'Package DCP Output' -Default 'Dcp'
        foreach ($p in $Script:PackageList) {
            $files = @(
                (Join-Path $bplDir "$($p.Name)$($Inst.Suffix).bpl"),
                (Join-Path $dcpDir "$($p.Name).dcp")
            )
            foreach ($f in $files) {
                if (-not (Test-Path -LiteralPath $f)) { continue }
                Invoke-Action -Description "удалить $f" -Action {
                    Remove-Item -LiteralPath $f -Force
                }
            }
        }
    }
    Write-Log "  Папка Lib дистрибутива не удаляется: $Script:LibRoot"
}

# ---------------------------------------------------------------- main

function Assert-IdeClosed {
    $ide = @(Get-Process -Name 'bds' -ErrorAction SilentlyContinue)
    if ($ide.Count -eq 0) { return }
    if ($WhatIf) {
        Write-Log 'Запущена IDE (bds.exe). Перед настоящей установкой её нужно закрыть.' 'WARN'
        return
    }
    $Script:ExitCode = 2
    throw 'Запущена IDE (bds.exe). Закройте все окна RAD Studio/Delphi и повторите запуск.'
}

$Script:BuildSummary = @()
$Script:KeepStage = $false
$Script:LastMsBuildExit = 0
try {
    Initialize-Log
    $action = 'Установка'
    if ($Uninstall) { $action = 'Удаление' } elseif ($BuildOnly) { $action = 'Сборка пакетов' }
    $mode = ''
    if ($WhatIf) { $mode = ' — режим -WhatIf: только план, без изменений' }
    Write-Log ('TgBot {0}: {1}{2}' -f (Get-TgBotVersion), $action, $mode) 'HEAD'
    Write-Log "Дистрибутив: $Script:DistRoot"
    if ($Script:LogFile) { Write-Log "Журнал: $Script:LogFile" }
    if ($args.Count -gt 0) { throw ('Неизвестные параметры: ' + ($args -join ' ')) }
    if ($Uninstall -and $BuildOnly) { throw 'Параметры -Uninstall и -BuildOnly несовместимы.' }

    $installs = @(Get-DelphiInstalls)
    if ($installs.Count -eq 0) {
        throw 'Не найдено ни одной Delphi 10.4 или новее (HKLM\SOFTWARE\WOW6432Node\Embarcadero\BDS\<версия>\RootDir).'
    }
    $selected = @(Select-Delphi $installs)
    if (-not $BuildOnly) { Assert-IdeClosed }

    foreach ($inst in $selected) {
        if ($Uninstall) { Invoke-Uninstall $inst } else { Invoke-Install $inst }
    }

    if ($WhatIf) {
        Write-Log 'Готово: план показан, изменений не сделано.' 'HEAD'
    } elseif ($BuildOnly) {
        Write-Log ('Готово: собрано пакетов — {0}, результат в {1}.' -f $Script:BuildSummary.Count, $Script:LibRoot) 'HEAD'
    } else {
        Write-Log ('Готово: выполнено действий — {0}.' -f $Script:Changes) 'HEAD'
        if (-not $Uninstall -and -not $BuildOnly) {
            Write-Log 'Запустите IDE: на палитре появится вкладка Telegram (TTelegramBot, TTgWebhookServer).'
        }
    }
} catch {
    if ($Script:ExitCode -eq 0) { $Script:ExitCode = 1 }
    Write-Log ('ОШИБКА: ' + $_.Exception.Message) 'ERROR'
} finally {
    if ($Script:StageDir -and (Test-Path -LiteralPath $Script:StageDir)) {
        if ($Script:KeepStage) {
            Write-Log "Временная папка сборки сохранена для разбора ошибки: $Script:StageDir" 'WARN'
        } else {
            Remove-Item -LiteralPath $Script:StageDir -Recurse -Force -ErrorAction SilentlyContinue
        }
    }
}
exit $Script:ExitCode
