unit TgBot.State;

{
  TgBot — хранилище состояния диалогов (FSM, «шаги» мастеров и т.п.).

  - ITgStateStorage — абстракция: значения-строки по ключу диалога и имени
    (TTgBot использует ключ 'chat:user'); реализации должны быть
    потокобезопасны — обработчики разных чатов выполняются параллельно;
  - TTgMemoryStateStorage — хранилище в памяти процесса (по умолчанию):
    теряется при перезапуске; для постоянного хранения реализуйте
    ITgStateStorage поверх файла или базы данных.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.SyncObjs,
  System.Generics.Collections;

type
  /// <summary>
  ///   Хранилище состояния: строковые значения AName в пределах ключа AKey.
  ///   Реализации обязаны быть потокобезопасными.
  /// </summary>
  ITgStateStorage = interface
    ['{0C6A2F51-5A3B-4D7E-9B83-61A7C4E2D915}']
    /// <summary>Значение AName ключа AKey; False — значения нет.</summary>
    function TryGet(const AKey, AName: string; out AValue: string): Boolean;
    /// <summary>Записывает (заменяет) значение AName ключа AKey.</summary>
    procedure Put(const AKey, AName, AValue: string);
    /// <summary>Удаляет значение AName ключа AKey; AName = '' — все значения ключа.</summary>
    procedure Delete(const AKey: string; const AName: string = '');
  end;

  /// <summary>
  ///   Потокобезопасное хранилище состояния в памяти процесса. Ключ без
  ///   значений удаляется сразу — память не растёт от завершённых диалогов.
  /// </summary>
  TTgMemoryStateStorage = class(TInterfacedObject, ITgStateStorage)
  private
    FLock: TCriticalSection;
    FData: TObjectDictionary<string, TDictionary<string, string>>;
  public
    constructor Create;
    destructor Destroy; override;
    function TryGet(const AKey, AName: string; out AValue: string): Boolean;
    procedure Put(const AKey, AName, AValue: string);
    procedure Delete(const AKey: string; const AName: string = '');
    /// <summary>Число ключей, у которых есть значения (для диагностики и тестов).</summary>
    function KeyCount: Integer;
  end;

implementation

{ TTgMemoryStateStorage }

constructor TTgMemoryStateStorage.Create;
begin
  inherited Create;
  FLock := TCriticalSection.Create;
  FData := TObjectDictionary<string, TDictionary<string, string>>.Create([doOwnsValues]);
end;

destructor TTgMemoryStateStorage.Destroy;
begin
  FreeAndNil(FData);
  FreeAndNil(FLock);
  inherited Destroy;
end;

function TTgMemoryStateStorage.TryGet(const AKey, AName: string; out AValue: string): Boolean;
var
  LValues: TDictionary<string, string>;
begin
  AValue := '';
  FLock.Enter;
  try
    Result := FData.TryGetValue(AKey, LValues) and LValues.TryGetValue(AName, AValue);
  finally
    FLock.Leave;
  end;
end;

procedure TTgMemoryStateStorage.Put(const AKey, AName, AValue: string);
var
  LValues: TDictionary<string, string>;
begin
  FLock.Enter;
  try
    if not FData.TryGetValue(AKey, LValues) then
    begin
      LValues := TDictionary<string, string>.Create;
      // При ошибке добавления словарь освобождается здесь (владельца ещё нет).
      try
        FData.Add(AKey, LValues);
      except
        LValues.Free;
        raise;
      end;
    end;
    LValues.AddOrSetValue(AName, AValue);
  finally
    FLock.Leave;
  end;
end;

procedure TTgMemoryStateStorage.Delete(const AKey, AName: string);
var
  LValues: TDictionary<string, string>;
begin
  FLock.Enter;
  try
    if not FData.TryGetValue(AKey, LValues) then
      Exit;
    if AName <> '' then
      LValues.Remove(AName);
    if (AName = '') or (LValues.Count = 0) then
      FData.Remove(AKey);
  finally
    FLock.Leave;
  end;
end;

function TTgMemoryStateStorage.KeyCount: Integer;
begin
  FLock.Enter;
  try
    Result := FData.Count;
  finally
    FLock.Leave;
  end;
end;

end.
