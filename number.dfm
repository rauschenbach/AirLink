object frmNumber: TfrmNumber
  Left = 2452
  Top = 252
  BorderIcons = [biHelp]
  BorderStyle = bsDialog
  Caption = #1042#1074#1077#1089#1090#1080' '#1085#1086#1084#1077#1088' '#1089#1090#1072#1085#1094#1080#1080
  ClientHeight = 159
  ClientWidth = 241
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 56
    Top = 50
    Width = 29
    Height = 16
    Caption = 'GNS'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object meDevNum: TMaskEdit
    Left = 96
    Top = 50
    Width = 65
    Height = 21
    EditMask = '!9999;1;0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MaxLength = 4
    ParentFont = False
    TabOrder = 0
    Text = '    '
  end
  object btnSet: TBitBtn
    Left = 20
    Top = 100
    Width = 75
    Height = 25
    TabOrder = 1
    OnClick = btnSetClick
    Kind = bkOK
  end
  object BitBtn1: TBitBtn
    Left = 152
    Top = 100
    Width = 75
    Height = 25
    TabOrder = 2
    Kind = bkCancel
  end
end
