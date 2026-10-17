program CustomTransport;

{
  TgBot — свой транспорт: наследник TTgTransportBase (0.4.0).

  Переменные окружения:
    TGBOT_TOKEN   — токен бота от @BotFather (без него программа печатает
                    подсказку и выходит с кодом 0);
    TGBOT_CHAT_ID — (необязательно) чат для сообщения и файла: число или @username.

  База TTgTransportBase берёт на себя протокол Bot API: URL, JSON-тело и части
  формы multipart, разбор ответа, ошибки (ETgApiError, ETgNetworkError без
  токена в тексте), повтор 429, лимиты, отмену. Наследнику остаются два
  метода — Post (один POST метода) и Download (GET файла) на любом
  HTTP-клиенте. Здесь — THTTPClient напрямую (без TgBot.Http) плюс журнал:
  метод, HTTP-статус и время каждого запроса. Так же пишется транспорт на
  Indy (TIdHTTP + TIdMultiPartFormDataStream), Synapse или mORMot.

  В uses нет фасада TgBot: он подключает TgBot.Http. Модули протокола
  (TgBot.Intf/Base/Transport/Types) HTTP-клиент RTL не тянут.

  Сценарий: свой транспорт регистрируется транспортом по умолчанию
  (TTgApi.Create(Token) берёт его) -> getMe -> если задан чат: sendMessage,
  sendDocument (multipart), getFile и скачивание этого файла.
}

{$APPTYPE CONSOLE}

uses
{$IFDEF MSWINDOWS}
  Winapi.Windows,
{$ENDIF}
  System.SysUtils,
  System.Classes,
  System.Diagnostics,
  System.Net.URLClient,
  System.Net.HttpClient,
  System.Net.Mime,
  TgBot.Intf,
  TgBot.Base,
  TgBot.Transport,
  TgBot.Types;

type
  /// <summary>Транспорт на THTTPClient с журналом запросов.</summary>
  TLoggingTransport = class(TTgTransportBase)
  private
    function NewClient(AResponseTimeoutMs: Integer): THTTPClient;
    procedure Log(const AOperation, AResult: string; AWatch: TStopwatch);
    /// <summary>Сам POST на THTTPClient (без журнала).</summary>
    function Send(const ARequest: TTgPostRequest): TTgHttpResponse;
  protected
    function Post(const ARequest: TTgPostRequest): TTgHttpResponse; override;
    function Download(const ARequest: TTgDownloadRequest; ADest: TStream): Integer; override;
  end;

function TLoggingTransport.NewClient(AResponseTimeoutMs: Integer): THTTPClient;
begin
  // Клиент на запрос: Post/Download вызываются из разных потоков одновременно.
  Result := THTTPClient.Create;
  try
    if Settings.ConnectionTimeoutMs > 0 then
      Result.ConnectionTimeout := Settings.ConnectionTimeoutMs;
    Result.ResponseTimeout := AResponseTimeoutMs; // для getUpdates база уже прибавила long polling
    Result.UserAgent := Settings.UserAgent;
    if Settings.Proxy.IsEnabled then // прокси уже проверен базой (Normalized)
      Result.ProxySettings := TProxySettings.Create(Settings.Proxy.Host, Settings.Proxy.Port,
        Settings.Proxy.UserName, Settings.Proxy.Password);
  except
    Result.Free;
    raise;
  end;
end;

procedure TLoggingTransport.Log(const AOperation, AResult: string; AWatch: TStopwatch);
begin
  // URL содержит токен — в журнал попадают только метод, итог и время.
  // Writeln из нескольких потоков может перемешать строки; демо — один поток.
  Writeln(Format('  [транспорт] %-14s %s, %d мс', [AOperation, AResult, AWatch.ElapsedMilliseconds]));
end;

function TLoggingTransport.Send(const ARequest: TTgPostRequest): TTgHttpResponse;
var
  LClient: THTTPClient;
  LForm: TMultipartFormData;
  LBody, LContent: TBytesStream;
  LPart: TTgFormPart;
begin
  LClient := nil;
  LForm := nil;
  LBody := nil;
  LContent := TBytesStream.Create;
  try
    LClient := NewClient(ARequest.ResponseTimeoutMs);
    if ARequest.IsMultipart then
    begin
      // Поля и файлы — в заданном порядке; потоки файлов принадлежат базе.
      LForm := TMultipartFormData.Create;
      for LPart in ARequest.Parts do
        if LPart.IsFile then
{$IF CompilerVersion >= 36}
          LForm.AddStream(LPart.Name, LPart.Stream, False, LPart.FileName, LPart.ContentType)
{$ELSE}
          LForm.AddStream(LPart.Name, LPart.Stream, LPart.FileName, LPart.ContentType)
{$ENDIF}
        else
          LForm.AddField(LPart.Name, LPart.Value);
      Result.StatusCode := LClient.Post(ARequest.Url, LForm, LContent).StatusCode;
    end
    else
    begin
      LBody := TBytesStream.Create(ARequest.Body);
      Result.StatusCode := LClient.Post(ARequest.Url, LBody, LContent,
        [TNetHeader.Create('Content-Type', ARequest.ContentType)]).StatusCode;
    end;
    // Любой статус — не ошибка: тело ({"ok":false,...}) разбирает база.
    Result.Body := Copy(LContent.Bytes, 0, LContent.Size);
  finally
    LClient.Free;
    LForm.Free;
    LBody.Free;
    LContent.Free;
  end;
end;

function TLoggingTransport.Post(const ARequest: TTgPostRequest): TTgHttpResponse;
var
  LWatch: TStopwatch;
begin
  // Исключения клиента можно не ловить: база превратит их в ETgNetworkError
  // (токен замаскирован) или в ETgCancelledError при отмене. Здесь они
  // только попадают в журнал и выбрасываются дальше.
  LWatch := TStopwatch.StartNew;
  try
    Result := Send(ARequest);
  except
    on E: Exception do
    begin
      // MaskToken базы убирает токен из текста (в нём бывает URL).
      Log(ARequest.Method, E.ClassName + ': ' + MaskToken(E.Message), LWatch);
      raise;
    end;
  end;
  Log(ARequest.Method, 'HTTP ' + IntToStr(Result.StatusCode), LWatch);
end;

function TLoggingTransport.Download(const ARequest: TTgDownloadRequest; ADest: TStream): Integer;
var
  LWatch: TStopwatch;
  LClient: THTTPClient;
begin
  // Статус, отличный от 200, база превратит в ETgNetworkError.
  LWatch := TStopwatch.StartNew;
  LClient := NewClient(ARequest.ResponseTimeoutMs);
  try
    Result := LClient.Get(ARequest.Url, ADest).StatusCode;
  finally
    LClient.Free;
  end;
  Log('(файл)', 'HTTP ' + IntToStr(Result), LWatch);
end;

var
  LToken, LChat: string;
  LFactory: TTgTransportFactory;
  LApi: TTgApi;
  LUser: ITgUser;
  LMessage: ITgMessage;
  LFile: TBytesStream;
begin
{$IFDEF MSWINDOWS}
  SetConsoleOutputCP(CP_UTF8);
  SetTextCodePage(Output, CP_UTF8);
{$ENDIF}
  LToken := Trim(GetEnvironmentVariable('TGBOT_TOKEN'));
  if LToken = '' then
  begin
    Writeln('TgBot CustomTransport ', TgBotVersion);
    Writeln('Переменная окружения TGBOT_TOKEN не задана.');
    Writeln('Пример (Windows):  set TGBOT_TOKEN=123456:ABC...');
    Exit; // ExitCode = 0
  end;
  // Без TgBot.Http фабрики по умолчанию нет: регистрируем свою. Иначе —
  // явно: TTgApi.Create(TLoggingTransport.Create(TTgHttpSettings.Create(LToken)) as ITgTransport).
  LFactory :=
    function(const ASettings: TTgHttpSettings): ITgTransport
    begin
      Result := TLoggingTransport.Create(ASettings);
    end;
  TgRegisterDefaultTransport(LFactory);
  try
    try
      LApi := TTgApi.Create(LToken);
      try
        // Сначала запрос, потом вывод: журнал транспорта пишет в ту же консоль.
        LUser := LApi.GetMe;
        Writeln('Бот: @', LUser.Username);
        LChat := Trim(GetEnvironmentVariable('TGBOT_CHAT_ID'));
        if LChat = '' then
          Writeln('TGBOT_CHAT_ID не задан — сообщение и файл не отправляются.')
        else
        begin
          LApi.SendMessage(LChat, 'Привет из своего транспорта!');
          LMessage := LApi.SendDocument(LChat, TTgInputFile.FromBytes(
            TEncoding.UTF8.GetBytes('Файл отправлен через TLoggingTransport.'), 'hello.txt', 'text/plain'));
          LFile := TBytesStream.Create;
          try
            LApi.DownloadFile(LApi.GetFile(LMessage.Document.FileId).FilePath, LFile);
            Writeln('Скачано обратно: ', LFile.Size, ' байт');
          finally
            LFile.Free;
          end;
        end;
      finally
        LApi.Free;
      end;
    except
      on E: Exception do
      begin
        Writeln('Ошибка: ', E.ClassName, ': ', E.Message);
        ExitCode := 1;
      end;
    end;
  finally
    TgUnregisterDefaultTransport(LFactory);
  end;
end.
