unit TgBot.Reg;

{
  Регистрация TTelegramBot и TTgWebhookServer (Indy, пакет TgBotIndyRT) в
  палитре компонентов IDE (пакет времени разработки TgBotDT). Иконки
  палитры — ресурс TgBot.dcr (TgBot.rc).

  TTgBotSelectionEditor добавляет модуль TgBot в uses формы при сохранении:
  в сигнатурах событий компонента используются ITgContext и другие типы
  TgBot, без него обработчики, созданные двойным щелчком в Object
  Inspector, не компилируются.
}

interface

uses
  System.Classes,
  DesignIntf,
  DesignEditors;

type
  /// <summary>Добавляет модуль TgBot в uses формы с TTelegramBot.</summary>
  TTgBotSelectionEditor = class(TSelectionEditor)
  public
    procedure RequiresUnits(Proc: TGetStrProc); override;
  end;

  /// <summary>Добавляет модуль TgBot.Webhook в uses формы с TTgWebhookServer.</summary>
  TTgWebhookServerSelectionEditor = class(TSelectionEditor)
  public
    procedure RequiresUnits(Proc: TGetStrProc); override;
  end;

procedure Register;

implementation

uses
  TgBot.Component,
  TgBot.Webhook;

{$R TgBot.dcr}

const
  TgPaletteName = 'Telegram';

{ TTgBotSelectionEditor }

procedure TTgBotSelectionEditor.RequiresUnits(Proc: TGetStrProc);
begin
  inherited RequiresUnits(Proc);
  Proc('TgBot');
end;

{ TTgWebhookServerSelectionEditor }

procedure TTgWebhookServerSelectionEditor.RequiresUnits(Proc: TGetStrProc);
begin
  inherited RequiresUnits(Proc);
  Proc('TgBot.Webhook');
end;

procedure Register;
begin
  RegisterComponents(TgPaletteName, [TTelegramBot, TTgWebhookServer]);
  RegisterSelectionEditor(TTelegramBot, TTgBotSelectionEditor);
  RegisterSelectionEditor(TTgWebhookServer, TTgWebhookServerSelectionEditor);
end;

end.
