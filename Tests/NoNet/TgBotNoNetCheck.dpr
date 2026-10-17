program TgBotNoNetCheck;

{
  TgBot — проверка «протокол без HTTP-стека RTL» (0.4.0).

  Клиент Bot API со своим транспортом (наследник TTgTransportBase) должен
  собираться и работать без System.Net.HttpClient/URLClient/Mime и без
  TgBot.Http. Здесь uses — только модули протокола TgBot.Intf, TgBot.Json,
  TgBot.Base, TgBot.Transport, TgBot.Core, TgBot.Types и System.*: все шесть
  подключены явно, чтобы проверка покрывала каждый из них, даже если связи
  между ними изменятся. Свой транспорт отвечает на getMe заготовкой — сети нет.

  Отсутствие запрещённых модулей в программе проверяет check.ps1 по карте
  (.map, ключ -GD); эта программа проверяет, что всё работает:
  - фабрика транспорта по умолчанию не зарегистрирована (её регистрирует
    только TgBot.Http);
  - TTgApi.Create(ATransport).GetMe возвращает пользователя из заготовки.

  Вывод — ASCII (кодовая страница консоли не настраивается: Winapi.* не
  подключается). Код выхода: 0 — успех, 1 — ошибка.
}

{$APPTYPE CONSOLE}

uses
  System.SysUtils,
  System.Classes,
  TgBot.Intf,
  TgBot.Json,
  TgBot.Base,
  TgBot.Transport,
  TgBot.Core,
  TgBot.Types;

type
  /// <summary>
  ///   Минимальный свой транспорт без сети: getMe — заготовка, остальные
  ///   методы — ошибка API 404, файлов нет (статус 404).
  /// </summary>
  TOfflineTransport = class(TTgTransportBase)
  protected
    function Post(const ARequest: TTgPostRequest): TTgHttpResponse; override;
    function Download(const ARequest: TTgDownloadRequest; ADest: TStream): Integer; override;
  end;

const
  CBotId = 4242;
  CBotUsername = 'nonet_check_bot';

function TOfflineTransport.Post(const ARequest: TTgPostRequest): TTgHttpResponse;
const
  CGetMe = '{"ok":true,"result":{"id":4242,"is_bot":true,"first_name":"NoNet",' +
    '"username":"nonet_check_bot"}}';
  CNotFound = '{"ok":false,"error_code":404,"description":"Not Found: offline transport"}';
begin
  if SameText(ARequest.Method, 'getMe') then
  begin
    Result.StatusCode := 200;
    Result.Body := TEncoding.UTF8.GetBytes(CGetMe);
  end
  else
  begin
    Result.StatusCode := 404;
    Result.Body := TEncoding.UTF8.GetBytes(CNotFound);
  end;
end;

function TOfflineTransport.Download(const ARequest: TTgDownloadRequest;
  ADest: TStream): Integer;
begin
  Result := 404;
end;

/// <summary>Проверки; результат — код выхода.</summary>
function Run: Integer;
var
  LApi: TTgApi;
  LUser: ITgUser;
begin
  Result := 1;
  // Фабрику по умолчанию регистрирует только TgBot.Http (initialization).
  if Assigned(TgDefaultTransportFactory()) then
  begin
    Writeln('FAIL: a default transport factory is registered (an HTTP implementation is linked)');
    Exit;
  end;
  LApi := TTgApi.Create(TOfflineTransport.Create(TTgHttpSettings.Create('123456:NONET')) as ITgTransport);
  try
    LUser := LApi.GetMe;
    if (LUser.Id = CBotId) and (LUser.Username = CBotUsername) then
    begin
      Writeln('OK: GetMe via own transport -> @', LUser.Username);
      Result := 0;
    end
    else
      Writeln('FAIL: unexpected GetMe result: id=', LUser.Id, ' username=', LUser.Username);
  finally
    LUser := nil;
    LApi.Free;
  end;
end;

begin
  ReportMemoryLeaksOnShutdown := True;
  try
    ExitCode := Run;
  except
    on E: Exception do
    begin
      Writeln('FAIL: ', E.ClassName, ': ', E.Message);
      ExitCode := 1;
    end;
  end;
end.
