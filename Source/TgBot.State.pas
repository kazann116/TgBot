unit TgBot.State;

{
  TgBot — хранилище состояния диалогов (FSM, «шаги» мастеров и т.п.).

  - ITgStateStorage — абстракция: значения-строки по ключу диалога и имени
    (TTgBot использует ключ 'chat:user'); реализации должны быть
    потокобезопасны — обработчики разных чатов выполняются параллельно;
    контракт объявлен в TgBot.Intf, здесь — псевдоним;
  - TTgMemoryStateStorage — хранилище в памяти процесса (по умолчанию):
    теряется при перезапуске; для постоянного хранения реализуйте
    ITgStateStorage поверх файла или базы данных.
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.SyncObjs,
  System.Generics.Collections,
  TgBot.Intf;

type
  /// <summary>
  ///   Хранилище состояния (описание — TgBot.Intf.ITgStateStorage; здесь —
  ///   псевдоним для совместимости, тот же тип и GUID).
  /// </summary>
  ITgStateStorage = TgBot.Intf.ITgStateStorage;

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
