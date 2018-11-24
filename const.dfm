object frmConst: TfrmConst
  Left = 403
  Top = 279
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = #1050#1086#1085#1089#1090#1072#1085#1090#1099' EEPROM'
  ClientHeight = 231
  ClientWidth = 382
  Color = clBtnFace
  DefaultMonitor = dmMainForm
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefault
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 382
    Height = 170
    Align = alTop
    Caption = #1040#1062#1055' ADS1282, PGA = 2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object Label1: TLabel
      Left = 5
      Top = 40
      Width = 9
      Height = 13
      Caption = 'X'
    end
    object Label2: TLabel
      Left = 5
      Top = 64
      Width = 9
      Height = 13
      Caption = 'Y'
    end
    object Label3: TLabel
      Left = 5
      Top = 88
      Width = 9
      Height = 13
      Caption = 'Z'
    end
    object Label4: TLabel
      Left = 240
      Top = 24
      Width = 100
      Height = 13
      Caption = #1042#1077#1089' '#1084#1083'. '#1088#1072#1079#1088#1103#1076#1072
    end
    object Label5: TLabel
      Left = 26
      Top = 24
      Width = 70
      Height = 13
      Caption = #1057#1084#1077#1097'. '#1085#1091#1083#1103
    end
    object Label6: TLabel
      Left = 5
      Top = 112
      Width = 10
      Height = 13
      Caption = 'H'
    end
    object seOffsetX: TBMSpinEdit
      Left = 20
      Top = 87
      Width = 120
      Height = 24
      Cursor = crArrow
      EditorEnabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = 8
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Increment = 1
      MaxValue = 200000
      MinValue = -200000
      Precision = 0
      GuageHeight = 1
      TrackBarEnabled = False
    end
    object seOffsetY: TBMSpinEdit
      Left = 20
      Top = 62
      Width = 120
      Height = 24
      Cursor = crArrow
      EditorEnabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = 8
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      Increment = 1E-6
      MaxValue = 200000
      MinValue = -200000
      Precision = 0
      GuageHeight = 1
      TrackBarEnabled = False
    end
    object seOffsetZ: TBMSpinEdit
      Left = 20
      Top = 39
      Width = 120
      Height = 24
      Cursor = crArrow
      EditorEnabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = 8
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      Increment = 1E-6
      MaxValue = 200000
      MinValue = -200000
      Precision = 0
      GuageHeight = 1
      TrackBarEnabled = False
    end
    object seGainX: TBMSpinEdit
      Left = 240
      Top = 87
      Width = 120
      Height = 24
      Cursor = crArrow
      EditorEnabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = 8
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      Increment = 1
      MaxValue = 8388607
      MinValue = -8388607
      Precision = 6
      GuageHeight = 1
      TrackBarEnabled = False
    end
    object seGainY: TBMSpinEdit
      Left = 240
      Top = 62
      Width = 120
      Height = 24
      Cursor = crArrow
      EditorEnabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = 8
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      Increment = 1
      MaxValue = 8388607
      MinValue = -8388607
      Precision = 6
      GuageHeight = 1
      TrackBarEnabled = False
    end
    object seGainZ: TBMSpinEdit
      Left = 240
      Top = 39
      Width = 120
      Height = 24
      Cursor = crArrow
      EditorEnabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = 8
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 6
      Increment = 1
      MaxValue = 8388607
      MinValue = -8388607
      Precision = 6
      GuageHeight = 1
      TrackBarEnabled = False
    end
    object seOffsetH: TBMSpinEdit
      Left = 20
      Top = 111
      Width = 120
      Height = 24
      Cursor = crArrow
      EditorEnabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = 8
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      Increment = 1E-6
      MaxValue = 200000
      MinValue = -200000
      Precision = 0
      GuageHeight = 1
      TrackBarEnabled = False
    end
    object seGainH: TBMSpinEdit
      Left = 240
      Top = 111
      Width = 120
      Height = 24
      Cursor = crArrow
      EditorEnabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = 8
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 7
      Increment = 1
      MaxValue = 8388607
      MinValue = -8388607
      Precision = 6
      GuageHeight = 1
      TrackBarEnabled = False
    end
    object cbConstWrite: TCheckBox
      Left = 20
      Top = 143
      Width = 165
      Height = 17
      Caption = #1047#1072#1087#1080#1089#1072#1090#1100' '#1074#1086'  Flash'
      TabOrder = 8
    end
  end
  object btnOk: TBitBtn
    Left = 10
    Top = 180
    Width = 120
    Height = 25
    Hint = #1047#1072#1087#1080#1089#1072#1090#1100' '#1079#1085#1072#1095#1077#1085#1080#1103
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    OnClick = btnOkClick
    Kind = bkOK
  end
  object BitBtn1: TBitBtn
    Left = 236
    Top = 180
    Width = 120
    Height = 25
    Hint = #1054#1090#1084#1077#1085#1072
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    Kind = bkCancel
  end
  object btnDefaultClick: TBitBtn
    Left = 238
    Top = 140
    Width = 107
    Height = 25
    Hint = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1087#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102
    Caption = 'Default'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 3
    OnClick = btnDefaultClickClick
    Glyph.Data = {
      F2010000424DF201000000000000760000002800000024000000130000000100
      0400000000007C01000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333334433333
      3333333333388F3333333333000033334224333333333333338338F333333333
      0000333422224333333333333833338F33333333000033422222243333333333
      83333338F3333333000034222A22224333333338F33F33338F33333300003222
      A2A2224333333338F383F3338F33333300003A2A222A222433333338F8333F33
      38F33333000034A22222A22243333338833333F3338F333300004222A2222A22
      2433338F338F333F3338F3330000222A3A2224A22243338F3838F338F3338F33
      0000A2A333A2224A2224338F83338F338F3338F300003A33333A2224A2224338
      333338F338F3338F000033333333A2224A2243333333338F338F338F00003333
      33333A2224A2233333333338F338F83300003333333333A2224A333333333333
      8F338F33000033333333333A222433333333333338F338F30000333333333333
      A224333333333333338F38F300003333333333333A223333333333333338F8F3
      000033333333333333A3333333333333333383330000}
    NumGlyphs = 2
  end
end
