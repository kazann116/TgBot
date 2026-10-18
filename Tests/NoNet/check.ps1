<#
.SYNOPSIS
  TgBot: клиент со своим транспортом собирается без HTTP-стека RTL.

.DESCRIPTION
  Собирает TgBotNoNetCheck.dpr (рядом со скриптом) компилятором Delphi с
  подробной картой (-GD) и ищет в .map модули System.Net.HttpClient,
  System.Net.URLClient, System.Net.Mime и TgBot.Http (вместе с подмодулями,
  например System.Net.HttpClient.Win). Найден хотя бы один — FAIL (код 1).
  Иначе запускает программу: она проверяет, что фабрика транспорта по
  умолчанию не зарегистрирована и GetMe работает через свой транспорт;
  код выхода программы 0 — PASS.

  Перед сборкой проверяет исходники Source (рекурсивно, *.pas и *.inc,
  включая Design и Generated): нет вызовов TMonitor.Wait/Pulse/PulseAll и
  System.MonitorWait/MonitorPulse/MonitorPulseAll (вызов — имя и '(',
  пробелы и переносы между ними допускаются) и примитивов RTL, ждущих через
  TMonitor (TLightweightEvent, TLightweightSemaphore, TCountdownEvent,
  TConditionVariable*, по имени типа). TMonitor.Enter/Exit и
  TLightweightMREW разрешены. Найдено — FAIL (код 1); подробнее — у функции
  Find-MonitorWaitUsages.

  Компилятор (первое найденное):
  1) -Compiler — полный путь к dcc64.exe или dcc32.exe (платформа — по имени);
  2) -BdsRoot — папка RAD Studio (bin\dcc64.exe или bin\dcc32.exe);
  3) переменная окружения BDS (задаёт rsvars.bat), если не указан -BdsVersion;
  4) реестр (только чтение): HKCU/HKLM\Software\Embarcadero\BDS\<версия>\RootDir —
     версия -BdsVersion (23.0 — Delphi 12, 22.0 — Delphi 11, 21.0 — Delphi 10.4)
     или последняя установленная.

  Вывод (exe, map, dcu) — в <OutDir>\<версия BDS>-<платформа>; файлы
  перезаписываются при каждом запуске, скрипт ничего не удаляет.

  Коды выхода: 0 — PASS; 1 — FAIL (TMonitor.Wait/Pulse в исходниках,
  запрещённые модули, ошибка сборки или программы); 2 — компилятор не найден
  или неверные параметры.

.PARAMETER Platform
  Win64 (по умолчанию) или Win32. При -Compiler определяется по имени компилятора.

.PARAMETER Compiler
  Полный путь к dcc64.exe или dcc32.exe.

.PARAMETER BdsRoot
  Папка установки RAD Studio (например C:\Program Files (x86)\Embarcadero\Studio\23.0).

.PARAMETER BdsVersion
  Версия BDS в реестре (23.0, 22.0, 21.0…), если установлено несколько.

.PARAMETER OutDir
  Папка вывода; по умолчанию %TEMP%\TgBotNoNet.

.EXAMPLE
  powershell -NoProfile -ExecutionPolicy Bypass -File Tests\NoNet\check.ps1

.EXAMPLE
  powershell -NoProfile -ExecutionPolicy Bypass -File Tests\NoNet\check.ps1 -Platform Win32 -BdsVersion 21.0
#>
[CmdletBinding()]
param(
  [ValidateSet('Win64', 'Win32')]
  [string]$Platform = 'Win64',
  [string]$Compiler = '',
  [string]$BdsRoot = '',
  [string]$BdsVersion = '',
  [string]$OutDir = (Join-Path $env:TEMP 'TgBotNoNet')
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

# Модули HTTP-стека, которых не должно быть в программе (и их подмодули).
$Forbidden = @('System.Net.HttpClient', 'System.Net.URLClient', 'System.Net.Mime', 'TgBot.Http')
# Модули протокола, которые обязаны быть: иначе карта разобрана неверно.
$Required = @('TgBot.Transport', 'TgBot.Core', 'TgBot.Types')
$ProgramName = 'TgBotNoNetCheck'

function Write-Fail([string]$AText, [int]$ACode) {
  Write-Host "FAIL: $AText" -ForegroundColor Red
  exit $ACode
}

# Папка RAD Studio из реестра (только чтение): версия AVersion или последняя.
function Find-BdsRootInRegistry([string]$AVersion) {
  $LKeys = @('HKCU:\Software\Embarcadero\BDS', 'HKLM:\SOFTWARE\WOW6432Node\Embarcadero\BDS',
    'HKLM:\SOFTWARE\Embarcadero\BDS')
  $LFound = @()
  foreach ($LKey in $LKeys) {
    if (-not (Test-Path -LiteralPath $LKey)) { continue }
    foreach ($LSub in @(Get-ChildItem -LiteralPath $LKey -ErrorAction SilentlyContinue)) {
      $LProps = Get-ItemProperty -LiteralPath $LSub.PSPath -ErrorAction SilentlyContinue
      if (-not $LProps -or -not ($LProps.PSObject.Properties.Name -contains 'RootDir')) { continue }
      $LRoot = [string]$LProps.RootDir
      $LVersion = $null
      if ($LRoot -and (Test-Path -LiteralPath $LRoot) -and
          [version]::TryParse($LSub.PSChildName, [ref]$LVersion)) {
        $LFound += [pscustomobject]@{ Version = $LVersion; Name = $LSub.PSChildName; Root = $LRoot }
      }
    }
  }
  if ($AVersion) { $LFound = @($LFound | Where-Object { $_.Name -eq $AVersion }) }
  $LBest = @($LFound | Sort-Object Version -Descending)
  if ($LBest.Count -gt 0) { return $LBest[0].Root }
  return $null
}

# Исходники: ожидания только на TEvent, без TMonitor.Wait/Pulse. Ищет в
# ASourceDir рекурсивно (*.pas, *.inc — в т.ч. Design и Generated), без учёта
# регистра (как Delphi), по всему тексту файла (не построчно):
#  - вызовы TMonitor.Wait/Pulse/PulseAll и MonitorWait/MonitorPulse/
#    MonitorPulseAll (с префиксом System. и без). Считается только имя со
#    скобкой '(' после него; пробелы и переносы строк вокруг '.' и перед '('
#    допускаются. Упоминание без скобки («TMonitor.Wait/Pulse» в
#    комментарии) не считается, со скобкой — считается и в комментарии;
#  - примитивы RTL, ждущие через TMonitor: TLightweightEvent,
#    TLightweightSemaphore, TCountdownEvent, TConditionVariable* — по имени
#    типа где угодно, включая комментарии и строки.
# Разрешены TMonitor.Enter/TryEnter/Exit и TLightweightMREW (TgBot.Webhook) —
# они не ждут через TMonitor.Wait. Возвращает строки «файл:строка: найденное»;
# $null — нет исходников (проверять нечего, это ошибка вызова).
function Find-MonitorWaitUsages([string]$ASourceDir) {
  $LPattern = '\bTMonitor\s*\.\s*(Wait|Pulse|PulseAll)\s*\(|' +
    '\bMonitor(Wait|Pulse|PulseAll)\s*\(|' +
    '\b(TLightweightEvent|TLightweightSemaphore|TCountdownEvent|TConditionVariable\w*)\b'
  $LRegex = New-Object System.Text.RegularExpressions.Regex($LPattern,
    [System.Text.RegularExpressions.RegexOptions]::IgnoreCase)
  $LRoot = (Resolve-Path -LiteralPath $ASourceDir).Path.TrimEnd('\')
  $LFiles = @(Get-ChildItem -LiteralPath $LRoot -Recurse -File |
    Where-Object { @('.pas', '.inc') -contains $_.Extension.ToLowerInvariant() } |
    Sort-Object FullName)
  if ($LFiles.Count -eq 0) { return $null }
  $LHits = @()
  foreach ($LFile in $LFiles) {
    # ReadAllText: UTF-8 по умолчанию, BOM распознаётся.
    $LText = [IO.File]::ReadAllText($LFile.FullName)
    foreach ($LMatch in $LRegex.Matches($LText)) {
      $LLine = $LText.Substring(0, $LMatch.Index).Split("`n").Count
      $LName = $LFile.FullName.Substring($LRoot.Length).TrimStart('\')
      $LHits += ('{0}:{1}: {2}' -f $LName, $LLine, ($LMatch.Value -replace '\s+', ' '))
    }
  }
  return ,$LHits
}

# --- Исходники ---
$LSourceDir = Join-Path $PSScriptRoot '..\..\Source'
if (-not (Test-Path -LiteralPath $LSourceDir -PathType Container)) {
  Write-Fail "нет папки исходников $LSourceDir" 2
}
$LWaitHits = Find-MonitorWaitUsages $LSourceDir
if ($null -eq $LWaitHits) { Write-Fail "в $LSourceDir нет *.pas/*.inc — проверять нечего" 1 }
if ($LWaitHits.Count -gt 0) {
  $LWaitHits | ForEach-Object { Write-Host "  $_" }
  Write-Fail 'в Source есть TMonitor.Wait/Pulse/PulseAll, MonitorWait/Pulse/PulseAll или примитивы на них' 1
}
Write-Host 'Source: TMonitor.Wait/Pulse/PulseAll, MonitorWait/Pulse/PulseAll и примитивы на них не используются'

# --- Компилятор ---
if ($Compiler) {
  switch ([IO.Path]::GetFileNameWithoutExtension($Compiler).ToLowerInvariant()) {
    'dcc64' { $Platform = 'Win64' }
    'dcc32' { $Platform = 'Win32' }
    default { Write-Fail "-Compiler: ожидается dcc64.exe или dcc32.exe, получено '$Compiler'" 2 }
  }
}
else {
  $LDccName = if ($Platform -eq 'Win64') { 'dcc64.exe' } else { 'dcc32.exe' }
  $LRoot = $BdsRoot
  if (-not $LRoot -and -not $BdsVersion -and $env:BDS) { $LRoot = $env:BDS }
  if (-not $LRoot) { $LRoot = Find-BdsRootInRegistry $BdsVersion }
  if ($LRoot) { $Compiler = Join-Path $LRoot (Join-Path 'bin' $LDccName) }
}
if (-not $Compiler -or -not (Test-Path -LiteralPath $Compiler -PathType Leaf)) {
  Write-Fail ("компилятор Delphi не найден ('$Compiler'). Укажите -Compiler, -BdsRoot или " +
    "-BdsVersion либо выполните rsvars.bat (переменная BDS).") 2
}
$Compiler = (Resolve-Path -LiteralPath $Compiler).Path
# Версия BDS — имя папки над bin (…\Studio\23.0\bin\dcc64.exe → 23.0).
$LTag = Split-Path -Leaf (Split-Path -Parent (Split-Path -Parent $Compiler))
$WorkDir = Join-Path $OutDir "$LTag-$Platform"
$DcuDir = Join-Path $WorkDir 'dcu'
New-Item -ItemType Directory -Force -Path $DcuDir | Out-Null
$WorkDir = (Resolve-Path -LiteralPath $WorkDir).Path
$DcuDir = (Resolve-Path -LiteralPath $DcuDir).Path

Write-Host "TgBot NoNet: $Platform, $Compiler"
Write-Host "Вывод: $WorkDir"

# --- Сборка ---
# Из папки скрипта, пути к исходникам — относительные: путь проекта может
# содержать пробелы и кириллицу.
$LExitCode = 0
Push-Location -LiteralPath $PSScriptRoot
# Windows PowerShell 5.1: при 'Stop' строка stderr нативной программы (2>&1)
# прерывает скрипт — на время вызова компилятора 'Continue', итог — по коду выхода.
$ErrorActionPreference = 'Continue'
try {
  $LDccArgs = @('-B', '-Q', '-GD', '-W+', '-H+', '--codepage:65001', '-U..\..\Source',
    "-E$WorkDir", "-NU$DcuDir", "$ProgramName.dpr")
  $LOutput = & $Compiler @LDccArgs 2>&1
  $LExitCode = $LASTEXITCODE
}
finally {
  $ErrorActionPreference = 'Stop'
  Pop-Location
}
$LOutput | Where-Object { "$_".Trim() -ne '' } | ForEach-Object { Write-Host "  $_" }
if ($LExitCode -ne 0) { Write-Fail "сборка $ProgramName.dpr — код $LExitCode" 1 }

# --- Карта: какие модули попали в программу ---
$MapFile = Join-Path $WorkDir "$ProgramName.map"
$ExeFile = Join-Path $WorkDir "$ProgramName.exe"
if (-not (Test-Path -LiteralPath $MapFile)) { Write-Fail "нет карты $MapFile (ключ -GD)" 1 }
# Строки сегментов: ' 0001:00000000 0000A8F4 C=CODE S=.text G=(none) M=System ACBP=A9'.
$Units = @(Select-String -LiteralPath $MapFile -Pattern '\bM=([A-Za-z0-9_.]+)' -AllMatches |
  ForEach-Object { $_.Matches } | ForEach-Object { $_.Groups[1].Value } | Sort-Object -Unique)
$Missing = @($Required | Where-Object { $Units -notcontains $_ })
if ($Units.Count -eq 0 -or $Missing.Count -gt 0) {
  Write-Fail ("карта не разобрана: в $MapFile нет модулей " + ($Missing -join ', ')) 1
}
$Found = @($Units | Where-Object {
    $LUnit = $_
    @($Forbidden | Where-Object {
        $LUnit -eq $_ -or $LUnit.StartsWith($_ + '.', [StringComparison]::OrdinalIgnoreCase) }).Count -gt 0
  })
Write-Host ("Модули TgBot: " + (@($Units | Where-Object { $_ -like 'TgBot.*' }) -join ', '))
Write-Host ("Модули System.Net*: " + (@($Units | Where-Object { $_ -like 'System.Net*' }) -join ', '))
if ($Found.Count -gt 0) {
  Write-Fail ("в программе есть модули HTTP-стека: " + ($Found -join ', ') +
    ". Их подключает $ProgramName.dpr или один из модулей протокола " +
    "(TgBot.Intf/Json/Base/Transport/Core/Types и их uses).") 1
}

# --- Запуск ---
$ErrorActionPreference = 'Continue'
& $ExeFile
$LRunCode = $LASTEXITCODE
$ErrorActionPreference = 'Stop'
if ($LRunCode -ne 0) { Write-Fail "$ProgramName.exe завершилась с кодом $LRunCode" 1 }

Write-Host "PASS: $Platform ($LTag) — без System.Net.HttpClient/URLClient/Mime и TgBot.Http, GetMe через свой транспорт" -ForegroundColor Green
exit 0
