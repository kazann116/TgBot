@echo off
setlocal
chcp 65001 >nul
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0Install.ps1" %*
set "TGBOT_RC=%ERRORLEVEL%"
if "%~1"=="" pause
exit /b %TGBOT_RC%
