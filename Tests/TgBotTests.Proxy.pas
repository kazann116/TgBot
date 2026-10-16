unit TgBotTests.Proxy;

{
  TgBot — стенд тестов прокси без внешней сети (Indy).

  - TTestHttpProxy    — минимальный HTTP-прокси на TIdTCPServer (127.0.0.1,
                        свободный порт). Запрос с абсолютным URI (GET/POST
                        http://host:port/...) пересылает на host:port с
                        заголовком Via: tgbot-test-proxy; имя TestApiHost
                        разрешает в 127.0.0.1. CONNECT только записывает в
                        журнал и отвечает 502 — наружу прокси не соединяется.
                        Журнал — строки "METHOD target".
  - TTestBotApiServer — фейковый Bot API на TIdHTTPServer: getMe, getUpdates
                        (одно обновление "ping" из чата 42, затем пусто),
                        sendMessage, getFile, /file/bot<токен>/docs/f.bin
                        (иначе 404), прочие методы — true. Журнал —
                        "METHOD document [via]" или "... [direct]" (пришёл
                        ли запрос через прокси).

  WinHTTP всегда обходит прокси для loopback (127.0.0.1, localhost), поэтому
  фейковый Bot API адресуется вымышленным именем TestApiHost: его разрешает
  только прокси, и запрос мимо прокси невозможен в принципе.
}

interface

uses
  System.SysUtils, System.Classes, System.SyncObjs,
  IdGlobal, IdContext, IdTCPServer, IdTCPClient, IdURI, IdSocketHandle,
  IdCustomHTTPServer, IdHTTPServer;

const
  /// <summary>Имя хоста фейкового Bot API (домен .invalid не разрешается DNS).</summary>
  TestApiHost = 'tgbot-api.invalid';
  /// <summary>Содержимое файла docs/f.bin фейкового Bot API.</summary>
  TestFileData = 'FILE-DATA-0123456789';

type
  /// <summary>Потокобезопасный журнал строк.</summary>
  TTestJournal = class
  private
    FLock: TCriticalSection;
    FItems: TStringList;
  public
    constructor Create;
    destructor Destroy; override;
    procedure Add(const S: string);
    /// <summary>Число записей, содержащих ASub (пусто — все).</summary>
    function Count(const ASub: string = ''): Integer;
    function Text: string;
  end;

  /// <summary>Минимальный HTTP-прокси (см. описание модуля).</summary>
  TTestHttpProxy = class
  private
    FServer: TIdTCPServer;
    FLog: TTestJournal;
    procedure Execute(AContext: TIdContext);
    function GetPort: Integer;
  public
    constructor Create;
    destructor Destroy; override;
    property Port: Integer read GetPort;
    property Log: TTestJournal read FLog;
  end;

  /// <summary>Фейковый Bot API (см. описание модуля).</summary>
  TTestBotApiServer = class
  private
    FServer: TIdHTTPServer;
    FLog: TTestJournal;
    FUpdateSent: Integer;
    procedure CommandGet(AContext: TIdContext; ARequestInfo: TIdHTTPRequestInfo;
      AResponseInfo: TIdHTTPResponseInfo);
    function GetPort: Integer;
    function GetUrl: string;
  public
    constructor Create;
    destructor Destroy; override;
    property Port: Integer read GetPort;
    /// <summary>ApiUrl: http://TestApiHost:порт (доступен только через прокси).</summary>
    property Url: string read GetUrl;
    property Log: TTestJournal read FLog;
  end;

implementation

const
  CViaHeader = 'tgbot-test-proxy';

{ TTestJournal }

constructor TTestJournal.Create;
begin
  inherited Create;
  FLock := TCriticalSection.Create;
  FItems := TStringList.Create;
end;

destructor TTestJournal.Destroy;
begin
  FreeAndNil(FItems);
  FreeAndNil(FLock);
  inherited Destroy;
end;

procedure TTestJournal.Add(const S: string);
begin
  FLock.Enter;
  try
    FItems.Add(S);
  finally
    FLock.Leave;
  end;
end;

function TTestJournal.Count(const ASub: string): Integer;
var
  S: string;
begin
  Result := 0;
  FLock.Enter;
  try
    for S in FItems do
      if (ASub = '') or (Pos(ASub, S) > 0) then
        Inc(Result);
  finally
    FLock.Leave;
  end;
end;

function TTestJournal.Text: string;
begin
  FLock.Enter;
  try
    Result := FItems.Text;
  finally
    FLock.Leave;
  end;
end;

{ TTestHttpProxy }

constructor TTestHttpProxy.Create;
var
  LBinding: TIdSocketHandle;
begin
  inherited Create;
  FLog := TTestJournal.Create;
  FServer := TIdTCPServer.Create(nil);
  LBinding := FServer.Bindings.Add;
  LBinding.IP := '127.0.0.1';
  LBinding.Port := 0;
  FServer.OnExecute := Execute;
  FServer.Active := True;
end;

destructor TTestHttpProxy.Destroy;
begin
  if Assigned(FServer) then
    FServer.Active := False;
  FreeAndNil(FServer);
  FreeAndNil(FLog);
  inherited Destroy;
end;

function TTestHttpProxy.GetPort: Integer;
begin
  Result := FServer.Bindings[0].Port;
end;

procedure TTestHttpProxy.Execute(AContext: TIdContext);
var
  LLine, LMethod, LTarget, LName, LRequest: string;
  LHeaders: TStringList;
  LUri: TIdURI;
  LOut: TIdTCPClient;
  LBody: TIdBytes;
  LResponse: TMemoryStream;
  LLen, I, P: Integer;
begin
  LLine := AContext.Connection.IOHandler.ReadLn;
  if LLine = '' then
  begin
    AContext.Connection.Disconnect;
    Exit;
  end;
  // Строка запроса: METHOD target HTTP/1.1.
  P := Pos(' ', LLine);
  LMethod := Copy(LLine, 1, P - 1);
  LTarget := Copy(LLine, P + 1, MaxInt);
  P := Pos(' ', LTarget);
  if P > 0 then
    SetLength(LTarget, P - 1);
  LHeaders := TStringList.Create;
  try
    AContext.Connection.IOHandler.Capture(LHeaders, '', False);
    FLog.Add(LMethod + ' ' + LTarget);
    if SameText(LMethod, 'CONNECT') then
    begin
      // Туннель наружу не открывается: фиксация CONNECT и отказ.
      AContext.Connection.IOHandler.Write('HTTP/1.1 502 Bad Gateway'#13#10 +
        'Content-Length: 0'#13#10'Connection: close'#13#10#13#10);
      AContext.Connection.Disconnect;
      Exit;
    end;
    LLen := 0;
    for I := 0 to LHeaders.Count - 1 do
    begin
      P := Pos(':', LHeaders[I]);
      if (P > 0) and SameText(Trim(Copy(LHeaders[I], 1, P - 1)), 'Content-Length') then
        LLen := StrToIntDef(Trim(Copy(LHeaders[I], P + 1, MaxInt)), 0);
    end;
    SetLength(LBody, 0);
    if LLen > 0 then
      AContext.Connection.IOHandler.ReadBytes(LBody, LLen, False);
    LOut := TIdTCPClient.Create(nil);
    LUri := TIdURI.Create(LTarget);
    LResponse := TMemoryStream.Create;
    try
      if SameText(LUri.Host, TestApiHost) then
        LOut.Host := '127.0.0.1'
      else
        LOut.Host := LUri.Host;
      LOut.Port := StrToIntDef(LUri.Port, 80);
      LOut.ConnectTimeout := 5000;
      LOut.ReadTimeout := 30000;
      LRequest := LMethod + ' ' + LUri.GetPathAndParams + ' HTTP/1.1'#13#10;
      for I := 0 to LHeaders.Count - 1 do
      begin
        P := Pos(':', LHeaders[I]);
        LName := Trim(Copy(LHeaders[I], 1, P - 1));
        if SameText(LName, 'Proxy-Connection') or SameText(LName, 'Connection') or
          SameText(LName, 'Proxy-Authorization') then
          Continue;
        LRequest := LRequest + LHeaders[I] + #13#10;
      end;
      // Одно соединение на запрос: ответ читается до закрытия сервером.
      LRequest := LRequest + 'Via: ' + CViaHeader + #13#10'Connection: close'#13#10#13#10;
      LOut.Connect;
      try
        LOut.IOHandler.Write(LRequest);
        if Length(LBody) > 0 then
          LOut.IOHandler.Write(LBody);
        LOut.IOHandler.ReadStream(LResponse, -1, True);
      finally
        LOut.Disconnect;
      end;
      AContext.Connection.IOHandler.Write(LResponse, 0);
    finally
      LResponse.Free;
      LUri.Free;
      LOut.Free;
    end;
    AContext.Connection.Disconnect;
  finally
    LHeaders.Free;
  end;
end;

{ TTestBotApiServer }

constructor TTestBotApiServer.Create;
var
  LBinding: TIdSocketHandle;
begin
  inherited Create;
  FLog := TTestJournal.Create;
  FServer := TIdHTTPServer.Create(nil);
  LBinding := FServer.Bindings.Add;
  LBinding.IP := '127.0.0.1';
  LBinding.Port := 0;
  FServer.OnCommandGet := CommandGet;
  FServer.Active := True;
end;

destructor TTestBotApiServer.Destroy;
begin
  if Assigned(FServer) then
    FServer.Active := False;
  FreeAndNil(FServer);
  FreeAndNil(FLog);
  inherited Destroy;
end;

function TTestBotApiServer.GetPort: Integer;
begin
  Result := FServer.Bindings[0].Port;
end;

function TTestBotApiServer.GetUrl: string;
begin
  Result := 'http://' + TestApiHost + ':' + IntToStr(Port);
end;

procedure TTestBotApiServer.CommandGet(AContext: TIdContext;
  ARequestInfo: TIdHTTPRequestInfo; AResponseInfo: TIdHTTPResponseInfo);
var
  LDoc, LMethod, LVia, LJson: string;
begin
  LDoc := ARequestInfo.Document;
  if SameText(ARequestInfo.RawHeaders.Values['Via'], CViaHeader) then
    LVia := ' [via]'
  else
    LVia := ' [direct]';
  FLog.Add(ARequestInfo.Command + ' ' + LDoc + LVia);
  if LDoc.StartsWith('/file/bot') then
  begin
    if LDoc.EndsWith('/docs/f.bin') then
    begin
      AResponseInfo.ContentType := 'application/octet-stream';
      AResponseInfo.ContentStream := TBytesStream.Create(TEncoding.ASCII.GetBytes(TestFileData));
    end
    else
      AResponseInfo.ResponseNo := 404;
    Exit;
  end;
  LMethod := Copy(LDoc, LDoc.LastIndexOf('/') + 2, MaxInt);
  if SameText(LMethod, 'getMe') then
    LJson := '{"id":777,"is_bot":true,"first_name":"Proxy","username":"proxy_test_bot"}'
  else if SameText(LMethod, 'getUpdates') then
  begin
    if TInterlocked.CompareExchange(FUpdateSent, 1, 0) = 0 then
      LJson := '[{"update_id":100,"message":{"message_id":1,"date":0,' +
        '"chat":{"id":42,"type":"private"},"from":{"id":42,"is_bot":false,"first_name":"U"},' +
        '"text":"ping"}}]'
    else
    begin
      // Пустой ответ long polling без долгого ожидания.
      Sleep(100);
      LJson := '[]';
    end;
  end
  else if SameText(LMethod, 'sendMessage') then
    LJson := '{"message_id":2,"date":0,"chat":{"id":42,"type":"private"},"text":"pong"}'
  else if SameText(LMethod, 'getFile') then
    LJson := '{"file_id":"F1","file_unique_id":"U1","file_size":20,"file_path":"docs/f.bin"}'
  else
    LJson := 'true';
  AResponseInfo.ContentType := 'application/json';
  AResponseInfo.CharSet := 'utf-8';
  AResponseInfo.ContentText := '{"ok":true,"result":' + LJson + '}';
end;

end.
