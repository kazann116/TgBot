; Установщик TgBot — Telegram Bot API для Delphi (Inno Setup 6).
;
; Собирается из Tools\Dist\MakeDist.ps1 -Setup: скрипт готовит чистую копию дистрибутива (исходники без
; бинарников) и вызывает ISCC с параметрами:
;   /DAppVersion=<версия>   /DSourceDir=<папка TgBot-<версия>>   /DIconFile=<.ico>   [/DLicenseFile=<файл>]
; Ручной запуск без MakeDist не предусмотрен: в корне проекта есть вывод сборки, который не должен попасть
; в установщик.
;
; Что делает установщик:
;  - копирует библиотеку (исходники, пакеты, демо, тесты, документацию) в {userdocs}\TgBot (папку можно
;    сменить), права администратора не нужны;
;  - по галочке «Установить компонент в Delphi» (включена по умолчанию) запускает
;    Install\Install.ps1 -All: сборка пакетов и регистрация в каждой Delphi 10.4+ (реестр HKCU);
;  - при удалении сначала вызывает Install\Uninstall.ps1 -All, затем удаляет файлы.

#ifndef AppVersion
  #error Не задан AppVersion. Собирайте установщик командой Tools\Dist\MakeDist.ps1 -Setup
#endif
#ifndef SourceDir
  #error Не задан SourceDir. Собирайте установщик командой Tools\Dist\MakeDist.ps1 -Setup
#endif
#ifndef IconFile
  #define IconFile AddBackslash(SourcePath) + "..\..\Source\Design\Icons\TgBot.ico"
#endif

#define AppTitle "TgBot — Telegram Bot API для Delphi"

[Setup]
AppId={{F2F68258-D32E-415A-9B84-9959B1DDF866}
AppName={#AppTitle}
AppVersion={#AppVersion}
AppVerName={#AppTitle} {#AppVersion}
VersionInfoVersion={#AppVersion}
VersionInfoDescription={#AppTitle} — установщик
VersionInfoProductName=TgBot
DefaultDirName={userdocs}\TgBot
DefaultGroupName=TgBot
DisableProgramGroupPage=yes
PrivilegesRequired=lowest
UsePreviousAppDir=yes
SetupIconFile={#IconFile}
UninstallDisplayIcon={uninstallexe}
UninstallDisplayName={#AppTitle} {#AppVersion}
WizardStyle=modern
ShowLanguageDialog=no
Compression=lzma2/max
SolidCompression=yes
OutputBaseFilename=TgBot-{#AppVersion}-Setup
MinVersion=6.1sp1
#ifdef LicenseFile
LicenseFile={#LicenseFile}
#endif

[Languages]
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

[Tasks]
Name: "delphi"; Description: "Установить компонент в Delphi (собрать пакеты и добавить вкладку Telegram; Delphi должна быть закрыта)"

[Files]
Source: "{#SourceDir}\*"; DestDir: "{app}"; Flags: recursesubdirs createallsubdirs ignoreversion

[Icons]
Name: "{group}\README — документация"; Filename: "{app}\README.ru.md"
Name: "{group}\Как установить"; Filename: "{app}\Как установить.txt"
Name: "{group}\Примеры (Demos)"; Filename: "{app}\Demos"
Name: "{group}\Установить в Delphi (Install.cmd)"; Filename: "{app}\Install\Install.cmd"; WorkingDir: "{app}\Install"
Name: "{group}\Удалить TgBot"; Filename: "{uninstallexe}"

[UninstallDelete]
; Созданное Install.ps1 после установки: собранные пакеты и журналы.
Type: filesandordirs; Name: "{app}\Lib"
Type: files; Name: "{app}\Install\Install.log"
Type: files; Name: "{app}\Install\Uninstall.log"

[Code]
var
  SkipDelphi: Boolean;

function PowerShellExe: String;
begin
  Result := ExpandConstant('{sysnative}\WindowsPowerShell\v1.0\powershell.exe');
  if not FileExists(Result) then
    Result := 'powershell.exe';
end;

{ Запущена ли IDE (bds.exe) — через WMI; при ошибке WMI считаем, что не запущена
  (Install.ps1 сам проверит и вернёт код 2). }
function IsDelphiRunning: Boolean;
var
  Locator, Service, List: Variant;
begin
  Result := False;
  try
    Locator := CreateOleObject('WbemScripting.SWbemLocator');
    Service := Locator.ConnectServer('.', 'root\CIMV2');
    List := Service.ExecQuery('SELECT ProcessId FROM Win32_Process WHERE Name = ''bds.exe''');
    Result := List.Count > 0;
  except
    Result := False;
  end;
end;

function InitializeSetup: Boolean;
begin
  SkipDelphi := False;
  Result := True;
end;

function PrepareToInstall(var NeedsRestart: Boolean): String;
var
  Answer: Integer;
begin
  Result := '';
  if not WizardIsTaskSelected('delphi') then
    Exit;
  while IsDelphiRunning do
  begin
    Answer := SuppressibleMsgBox(
      'Запущена Delphi (bds.exe). Закройте все окна RAD Studio/Delphi.' + #13#10#13#10 +
      'Повторить — проверить ещё раз.' + #13#10 +
      'Пропустить — только скопировать файлы (компонент потом можно установить через Install\Install.cmd).' + #13#10 +
      'Прервать — отменить установку.',
      mbError, MB_ABORTRETRYIGNORE, IDIGNORE);
    if Answer = IDABORT then
    begin
      Result := 'Установка отменена: запущена Delphi (bds.exe).';
      Exit;
    end;
    if Answer = IDIGNORE then
    begin
      SkipDelphi := True;
      Exit;
    end;
  end;
end;

procedure InstallIntoDelphi;
var
  Params: String;
  ResultCode: Integer;
begin
  WizardForm.StatusLabel.Caption := 'Сборка пакетов и установка компонента в Delphi (несколько минут)...';
  WizardForm.FilenameLabel.Caption := ExpandConstant('{app}\Install\Install.ps1 -All');
  Params := '-NoProfile -ExecutionPolicy Bypass -File "' + ExpandConstant('{app}\Install\Install.ps1') + '" -All';
  if not Exec(PowerShellExe, Params, ExpandConstant('{app}\Install'), SW_SHOWMINNOACTIVE,
    ewWaitUntilTerminated, ResultCode) then
  begin
    SuppressibleMsgBox('Не удалось запустить PowerShell: ' + SysErrorMessage(ResultCode) + #13#10#13#10 +
      'Файлы библиотеки скопированы. Установите компонент вручную: Install\Install.cmd.',
      mbError, MB_OK, IDOK);
    Exit;
  end;
  if ResultCode <> 0 then
    SuppressibleMsgBox(Format('Компонент в Delphi не установлен (код %d).', [ResultCode]) + #13#10#13#10 +
      'Файлы библиотеки скопированы. Подробности — в журнале:' + #13#10 +
      ExpandConstant('{app}\Install\Install.log') + #13#10#13#10 +
      'Исправьте причину (например, закройте Delphi или запустите её хотя бы раз) ' +
      'и запустите Install\Install.cmd.', mbError, MB_OK, IDOK);
end;

procedure CurStepChanged(CurStep: TSetupStep);
begin
  if (CurStep = ssPostInstall) and WizardIsTaskSelected('delphi') and not SkipDelphi then
    InstallIntoDelphi;
end;

function InitializeUninstall: Boolean;
begin
  Result := True;
  while IsDelphiRunning do
    if SuppressibleMsgBox('Запущена Delphi (bds.exe). Закройте все окна RAD Studio/Delphi и нажмите «Повторить».',
      mbError, MB_RETRYCANCEL, IDCANCEL) = IDCANCEL then
    begin
      Result := False;
      Exit;
    end;
end;

procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
var
  Params, LogFile: String;
  ResultCode: Integer;
begin
  if CurUninstallStep <> usUninstall then
    Exit;
  { Журнал — во временной папке: папка Install будет удалена вместе с библиотекой. }
  LogFile := AddBackslash(GetTempDir) + 'TgBot-Uninstall.log';
  Params := '-NoProfile -ExecutionPolicy Bypass -File "' + ExpandConstant('{app}\Install\Uninstall.ps1') +
    '" -All -LogPath "' + LogFile + '"';
  if not Exec(PowerShellExe, Params, ExpandConstant('{app}\Install'), SW_HIDE, ewWaitUntilTerminated, ResultCode) then
    SuppressibleMsgBox('Не удалось запустить PowerShell для удаления компонента из Delphi.' + #13#10 +
      'Уберите пакет TgBotDT вручную: Component -> Install Packages.', mbError, MB_OK, IDOK)
  else if ResultCode <> 0 then
    SuppressibleMsgBox(Format('Компонент из Delphi удалён не полностью (код %d). Журнал:', [ResultCode]) + #13#10 +
      LogFile, mbError, MB_OK, IDOK);
end;
