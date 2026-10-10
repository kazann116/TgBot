<#
.SYNOPSIS
  Удаление TgBot (Telegram Bot API для Delphi) из Delphi 10.4 и новее.

.DESCRIPTION
  Обратные действия Install.ps1 (логика — в Install.ps1 с ключом -Uninstall):
   - удаляет регистрацию TgBotDT<суффикс>.bpl из Known Packages и Disabled Packages;
   - убирает из Library\<Platform> "Search Path" и "Browsing Path" папки Source и Lib\<Delphi>\<Platform>
     этого дистрибутива;
   - удаляет TgBotRT/TgBotIndyRT/TgBotDT .bpl и .dcp из папок IDE (Package DPL/DCP Output).
  IDE должна быть закрыта. -WhatIf (-DryRun) только печатает план. Журнал — Uninstall.log рядом.

.EXAMPLE
  powershell -ExecutionPolicy Bypass -File Uninstall.ps1 -Delphi 23.0 -WhatIf
#>
param(
    [string[]]$Delphi = @(),
    [switch]$All,
    [Alias('DryRun')]
    [switch]$WhatIf,
    [string]$LogPath = ''
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

if ($args.Count -gt 0) {
    Write-Host ('Неизвестные параметры: ' + ($args -join ' ')) -ForegroundColor Red
    exit 1
}

$installer = Join-Path $PSScriptRoot 'Install.ps1'
if (-not (Test-Path -LiteralPath $installer)) {
    Write-Host "Не найден $installer" -ForegroundColor Red
    exit 1
}

$forward = @{}
foreach ($k in $PSBoundParameters.Keys) { $forward[$k] = $PSBoundParameters[$k] }
& $installer -Uninstall @forward
exit $LASTEXITCODE
