unit TgBot.Types;

{
  TgBot — сгенерированный слой Telegram Bot API 10.3: интерфейсы объектов
  ITg*, виды полиморфных типов (Kind), записи констант и объединений,
  фабрики TTg<Name>, записи необязательных параметров методов и клиент
  TTgApi с методами Bot API.

  Код — Source\Generated\Gen.*.inc (TgBotGen по спецификации Bot API 10.3),
  включается относительно этого файла, дополнительный путь -I не нужен.
  Не редактируйте Gen.*.inc вручную — перегенерируйте TgBotGen --gen.

  Указывать этот модуль в uses не нужно: TgBot реэкспортирует все его типы
  псевдонимами (Generated\Gen.Aliases.inc).
}

{$SCOPEDENUMS ON}

interface

uses
  System.SysUtils,
  System.JSON,
  System.Threading,
  TgBot.Base,
  TgBot.Json,
  TgBot.Dto,
  TgBot.Core;

type
{$I Generated\Gen.Forward.inc}
{$I Generated\Gen.Enums.inc}
{$I Generated\Gen.Unions.inc}
{$I Generated\Gen.Intf.inc}
{$I Generated\Gen.Factories.inc}
{$I Generated\Gen.Options.inc}

  /// <summary>
  ///   Клиент Telegram Bot API. Для каждого метода: синхронный вызов
  ///   (исключение при ошибке), Try* (False и TTgErrorInfo), *Async (колбэки
  ///   в рабочем потоке). Потокобезопасен. Не уничтожайте объект из колбэка Async.
  /// </summary>
  TTgApi = class(TTgApiCore)
{$I Generated\Gen.Methods.inc}
  end;

{ Служебное (для модуля TgBot): DTO поверх JSON без копирования. AOwner
  удерживает владельца AJson (например, сырое обновление); nil — значение
  не подходит. Не часть публичного API библиотеки. }

function TgMakeUpdate(AJson: TJSONValue; const AOwner: IInterface): ITgUpdate;
function TgMakeUser(AJson: TJSONValue; const AOwner: IInterface): ITgUser;
function TgMakeMessage(AJson: TJSONValue; const AOwner: IInterface): ITgMessage;

implementation

{$I Generated\Gen.ImplClasses.inc}
{$I Generated\Gen.ImplMake.inc}
{$I Generated\Gen.ImplTypes.inc}
{$I Generated\Gen.ImplMethods.inc}

end.
