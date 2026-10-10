object FormMain: TFormMain
  Left = 0
  Top = 0
  Caption = 'TgBot '#8212' VCL-'#1076#1077#1084#1086' (TTelegramBot '#1085#1072' '#1092#1086#1088#1084#1077')'
  ClientHeight = 480
  ClientWidth = 720
  Color = clBtnFace
  Constraints.MinHeight = 360
  Constraints.MinWidth = 560
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 15
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 720
    Height = 72
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object LabelToken: TLabel
      Left = 12
      Top = 15
      Width = 72
      Height = 15
      Caption = #1058#1086#1082#1077#1085' '#1073#1086#1090#1072':'
      FocusControl = EditToken
    end
    object LabelState: TLabel
      Left = 12
      Top = 46
      Width = 103
      Height = 15
      Caption = #1057#1086#1089#1090#1086#1103#1085#1080#1077': Idle'
    end
    object LabelCount: TLabel
      Left = 240
      Top = 46
      Width = 77
      Height = 15
      Caption = #1057#1086#1086#1073#1097#1077#1085#1080#1081': 0'
    end
    object EditToken: TEdit
      Left = 96
      Top = 12
      Width = 400
      Height = 23
      Anchors = [akLeft, akTop, akRight]
      PasswordChar = '*'
      TabOrder = 0
      TextHint = #1087#1091#1089#1090#1086' '#8212' '#1080#1079' '#1087#1077#1088#1077#1084#1077#1085#1085#1086#1081' '#1086#1082#1088#1091#1078#1077#1085#1080#1103' TGBOT_TOKEN'
    end
    object ButtonStart: TButton
      Left = 508
      Top = 11
      Width = 96
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1057#1090#1072#1088#1090
      TabOrder = 1
      OnClick = ButtonStartClick
    end
    object ButtonStop: TButton
      Left = 612
      Top = 11
      Width = 96
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1057#1090#1086#1087
      Enabled = False
      TabOrder = 2
      OnClick = ButtonStopClick
    end
  end
  object PanelBottom: TPanel
    Left = 0
    Top = 408
    Width = 720
    Height = 72
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 2
    object LabelChat: TLabel
      Left = 12
      Top = 8
      Width = 208
      Height = 15
      Caption = #1055#1086#1089#1083#1077#1076#1085#1080#1081' '#1095#1072#1090': '#1085#1077#1090' ('#1085#1072#1087#1080#1096#1080#1090#1077' '#1073#1086#1090#1091')'
    end
    object EditSend: TEdit
      Left = 12
      Top = 32
      Width = 592
      Height = 23
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
      TextHint = #1058#1077#1082#1089#1090' '#1089#1086#1086#1073#1097#1077#1085#1080#1103' '#1074' '#1087#1086#1089#1083#1077#1076#1085#1080#1081' '#1072#1082#1090#1080#1074#1085#1099#1081' '#1095#1072#1090
    end
    object ButtonSend: TButton
      Left = 612
      Top = 31
      Width = 96
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1054#1090#1087#1088#1072#1074#1080#1090#1100
      Enabled = False
      TabOrder = 1
      OnClick = ButtonSendClick
    end
  end
  object MemoLog: TMemo
    AlignWithMargins = True
    Left = 12
    Top = 75
    Width = 696
    Height = 330
    Margins.Left = 12
    Margins.Right = 12
    Align = alClient
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 1
  end
  object TelegramBot1: TTelegramBot
    Active = False
    Delivery = Main
    Commands = <
      item
        Command = 'start'
        Description = #1053#1072#1095#1072#1090#1100
        OnExecute = BotCommandStartExecute
      end
      item
        Command = 'help'
        Description = #1057#1087#1088#1072#1074#1082#1072
        OnExecute = BotCommandHelpExecute
      end>
    OnStart = TelegramBot1Start
    OnStop = TelegramBot1Stop
    OnMessage = TelegramBot1Message
    OnCallbackQuery = TelegramBot1CallbackQuery
    OnError = TelegramBot1Error
    OnFault = TelegramBot1Fault
    Left = 640
    Top = 112
  end
end
