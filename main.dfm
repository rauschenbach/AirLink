object frmMain: TfrmMain
  Left = -1404
  Top = 215
  HorzScrollBar.Visible = False
  AutoScroll = False
  ClientHeight = 616
  ClientWidth = 1009
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = menuMain
  OldCreateOrder = False
  Position = poDesktopCenter
  OnActivate = FormActivate
  OnCloseQuery = FormCloseQuery
  OnDestroy = FormDestroy
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 377
    Width = 1009
    Height = 5
    Cursor = crVSplit
    Align = alTop
    OnMoved = Splitter1Moved
  end
  object sbInfo: TStatusBar
    Left = 0
    Top = 597
    Width = 1009
    Height = 19
    Hint = #1044#1074#1086#1081#1085#1086#1081' '#1097#1077#1083#1095#1077#1082' '#1084#1099#1096#1082#1086#1081' '#1089#1090#1080#1088#1072#1077#1090' '#1089#1086#1086#1073#1097#1077#1085#1080#1103
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBtnText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    Panels = <
      item
        Width = 250
      end
      item
        Text = #1042#1088#1077#1084#1103' '#1088#1072#1073#1086#1090#1099' '#1074' '#1090#1077#1082#1091#1097#1077#1084' '#1089#1077#1072#1085#1089#1077
        Width = 320
      end
      item
        Text = #1048#1079#1084#1077#1088#1077#1085#1080#1103' ('#1095#1095':'#1084#1084')'
        Width = 250
      end
      item
        Text = #1056#1077#1078#1080#1084' PC('#1095#1095':'#1084#1084')'
        Width = 250
      end
      item
        Text = #1052#1086#1076#1077#1084' ('#1095#1095':'#1084#1084')'
        Width = 200
      end>
    ParentShowHint = False
    ShowHint = True
    SimplePanel = False
    UseSystemFont = False
    OnDblClick = sbInfoDblClick
  end
  object tbButtons: TToolBar
    Left = 0
    Top = 0
    Width = 1009
    Height = 35
    ButtonHeight = 38
    ButtonWidth = 39
    Caption = 'tbButtons'
    Flat = True
    Images = imgList
    TabOrder = 1
    object btnReset: TToolButton
      Left = 0
      Top = 0
      Hint = #1055#1077#1088#1077#1079#1072#1075#1088#1091#1079#1082#1072
      Caption = 'btnReset'
      Enabled = False
      ImageIndex = 1
      ParentShowHint = False
      ShowHint = True
      OnClick = btnResetClick
    end
    object btnPowerOff: TToolButton
      Left = 39
      Top = 0
      Hint = #1042#1099#1082#1083#1102#1095#1077#1085#1080#1077
      Caption = 'btnPowerOff'
      Enabled = False
      ImageIndex = 2
      ParentShowHint = False
      ShowHint = True
      OnClick = btnPowerOffClick
    end
    object ToolButton5: TToolButton
      Left = 78
      Top = 0
      Width = 8
      Caption = 'ToolButton5'
      ImageIndex = 5
      Style = tbsSeparator
    end
    object btnTest: TToolButton
      Left = 86
      Top = 0
      Hint = #1057#1072#1084#1086#1090#1077#1089#1090#1080#1088#1086#1074#1072#1085#1080#1077
      Caption = 'btnTest'
      Enabled = False
      ImageIndex = 4
      ParentShowHint = False
      ShowHint = True
      OnClick = btnTestClick
    end
    object ToolButton1: TToolButton
      Left = 125
      Top = 0
      Width = 8
      Caption = 'ToolButton1'
      ImageIndex = 11
      Style = tbsSeparator
    end
    object btnModemOnOff: TToolButton
      Left = 133
      Top = 0
      Hint = #1052#1086#1076#1077#1084' '#1074#1082#1083'/'#1074#1099#1082#1083
      Caption = 'btnModemOnOff'
      Enabled = False
      ImageIndex = 8
      ParentShowHint = False
      ShowHint = True
      OnClick = btnModemOnOffClick
    end
    object btnModemRequest: TToolButton
      Left = 172
      Top = 0
      Hint = #1054#1087#1088#1086#1089#1080#1090#1100' '#1084#1086#1076#1077#1084
      Caption = 'btnModemRequest'
      Enabled = False
      ImageIndex = 15
      ParentShowHint = False
      ShowHint = True
      OnClick = btnModemRequestClick
    end
    object btnModemCommand: TToolButton
      Left = 211
      Top = 0
      Hint = #1047#1072#1087#1080#1089#1072#1090#1100' '#1074' '#1084#1086#1076#1077#1084
      Caption = 'btnModemCommand'
      Enabled = False
      ImageIndex = 14
      ParentShowHint = False
      ShowHint = True
      OnClick = btnModemCommandClick
    end
    object btnBurn: TToolButton
      Left = 250
      Top = 0
      Hint = #1055#1077#1088#1077#1078#1080#1075' '#1074#1082#1083'/'#1074#1099#1082#1083
      Caption = 'btnBurn'
      Enabled = False
      ImageIndex = 10
      ParentShowHint = False
      ShowHint = True
      OnClick = btnBurnClick
    end
    object btnGpsOn: TToolButton
      Left = 289
      Top = 0
      Hint = 'GPS '#1074#1082#1083'/'#1074#1099#1082#1083
      AllowAllUp = True
      Caption = 'btnGpsOn'
      Enabled = False
      Grouped = True
      ImageIndex = 16
      ParentShowHint = False
      ShowHint = True
      OnClick = btnGpsOnClick
    end
    object ToolButton6: TToolButton
      Left = 328
      Top = 0
      Width = 8
      Caption = 'ToolButton6'
      ImageIndex = 18
      Style = tbsSeparator
    end
    object btnStartThread: TToolButton
      Left = 336
      Top = 0
      Hint = #1054#1089#1094#1080#1083#1083#1086#1075#1088#1072#1092' '#1057#1090#1072#1088#1090'/'#1057#1090#1086#1087
      Caption = 'btnStartThread'
      Enabled = False
      ImageIndex = 5
      ParentShowHint = False
      ShowHint = True
      OnClick = btnStartThreadClick
    end
    object ToolButton4: TToolButton
      Left = 375
      Top = 0
      Width = 8
      Caption = 'ToolButton4'
      Enabled = False
      ImageIndex = 11
      Style = tbsDivider
    end
    object btnSync: TToolButton
      Left = 383
      Top = 0
      Hint = #1057#1080#1085#1093#1088#1086#1085#1080#1079#1072#1094#1080#1103
      Caption = 'btnSync'
      Enabled = False
      ImageIndex = 3
      ParentShowHint = False
      ShowHint = True
      OnClick = btnSyncClick
    end
    object btnConst: TToolButton
      Left = 422
      Top = 0
      Hint = #1047#1072#1087#1080#1089#1072#1090#1100' '#1082#1086#1085#1089#1090#1072#1085#1090#1099
      Caption = 'btnConst'
      Enabled = False
      ImageIndex = 12
      ParentShowHint = False
      ShowHint = True
      OnClick = btnConstClick
    end
    object btnSetName: TToolButton
      Left = 461
      Top = 0
      Hint = #1042#1074#1077#1089#1090#1080' '#1085#1086#1084#1077#1088' '#1089#1090#1072#1085#1094#1080#1080
      Caption = 'btnSetName'
      Enabled = False
      ImageIndex = 11
      ParentShowHint = False
      ShowHint = True
      OnClick = btnSetNameClick
    end
    object btnSetToZero: TToolButton
      Left = 500
      Top = 0
      Hint = #1048#1089#1093#1086#1076#1085#1099#1077' '#1082#1086#1085#1089#1090#1072#1085#1090#1099' '#1074' EEPROM'
      Caption = 'btnSetToZero'
      Enabled = False
      ImageIndex = 13
      ParentShowHint = False
      ShowHint = True
      OnClick = btnSetToZeroClick
    end
    object btnResetWorkTime: TToolButton
      Left = 539
      Top = 0
      Hint = #1057#1073#1088#1086#1089#1080#1090#1100' '#1074#1088#1077#1084#1103' '#1088#1072#1073#1086#1090#1099' '#1091#1089#1090#1088#1086#1081#1089#1090#1074
      Caption = 'btnResetWorkTime'
      Enabled = False
      ImageIndex = 18
      ParentShowHint = False
      ShowHint = True
      OnClick = btnResetWorkTimeClick
    end
  end
  object pnUp: TPanel
    Left = 0
    Top = 35
    Width = 1009
    Height = 115
    Align = alTop
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 2
    object gbTimes: TGroupBox
      Left = 192
      Top = 17
      Width = 210
      Height = 96
      Align = alLeft
      Caption = #1042#1088#1077#1084#1103' / '#1050#1086#1086#1088#1076#1080#1085#1072#1090#1099' GPS'
      Constraints.MinWidth = 200
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      object pnUTCTime: TPanel
        Left = 0
        Top = 15
        Width = 75
        Height = 15
        Alignment = taLeftJustify
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1042#1088#1077#1084#1103' PC*'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
      end
      object pnTimeGNS110: TPanel
        Left = 0
        Top = 30
        Width = 75
        Height = 15
        Alignment = taLeftJustify
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1042#1088#1077#1084#1103' GNS'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
      end
      object pnGpsTime: TPanel
        Left = 0
        Top = 45
        Width = 75
        Height = 15
        Alignment = taLeftJustify
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1042#1088#1077#1084#1103' GPS'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
      end
      object pnGpsLat: TPanel
        Left = 0
        Top = 60
        Width = 75
        Height = 15
        Alignment = taLeftJustify
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1064#1080#1088#1086#1090#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
      end
      object pnGpsLon: TPanel
        Left = 0
        Top = 75
        Width = 75
        Height = 15
        Alignment = taLeftJustify
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1044#1086#1083#1075#1086#1090#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 4
      end
      object lbGpsLon: TPanel
        Left = 75
        Top = 75
        Width = 120
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 5
      end
      object lbGpsLat: TPanel
        Left = 75
        Top = 60
        Width = 120
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 6
      end
      object lbGpsTime: TPanel
        Left = 75
        Top = 45
        Width = 120
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 7
      end
      object lbTimeGNS110: TPanel
        Left = 75
        Top = 30
        Width = 120
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 8
      end
      object lbUTCTime: TPanel
        Left = 75
        Top = 15
        Width = 120
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 9
      end
    end
    object gbParams: TGroupBox
      Left = 2
      Top = 17
      Width = 190
      Height = 96
      Align = alLeft
      Caption = #1055#1086#1076#1082#1083#1102#1095#1077#1085#1085#1072#1103' '#1089#1090#1072#1085#1094#1080#1103
      Constraints.MinWidth = 190
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      object sbRunModule: TSpeedButton
        Left = 150
        Top = 15
        Width = 30
        Height = 30
        Hint = #1055#1086#1076#1082#1083#1102#1095#1077#1085#1080#1077' '#1082' '#1089#1090#1072#1085#1094#1080#1080'/'#1086#1090#1082#1083#1102#1095#1077#1085#1080#1077' '#1086#1090' '#1089#1090#1072#1085#1094#1080#1080
        AllowAllUp = True
        GroupIndex = 26
        Enabled = False
        Glyph.Data = {
          B6080000424DB608000000000000360400002800000030000000180000000100
          0800000000008004000000000000000000000001000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000C0DCC000F0CA
          A6000020400000206000002080000020A0000020C0000020E000004000000040
          20000040400000406000004080000040A0000040C0000040E000006000000060
          20000060400000606000006080000060A0000060C0000060E000008000000080
          20000080400000806000008080000080A0000080C0000080E00000A0000000A0
          200000A0400000A0600000A0800000A0A00000A0C00000A0E00000C0000000C0
          200000C0400000C0600000C0800000C0A00000C0C00000C0E00000E0000000E0
          200000E0400000E0600000E0800000E0A00000E0C00000E0E000400000004000
          20004000400040006000400080004000A0004000C0004000E000402000004020
          20004020400040206000402080004020A0004020C0004020E000404000004040
          20004040400040406000404080004040A0004040C0004040E000406000004060
          20004060400040606000406080004060A0004060C0004060E000408000004080
          20004080400040806000408080004080A0004080C0004080E00040A0000040A0
          200040A0400040A0600040A0800040A0A00040A0C00040A0E00040C0000040C0
          200040C0400040C0600040C0800040C0A00040C0C00040C0E00040E0000040E0
          200040E0400040E0600040E0800040E0A00040E0C00040E0E000800000008000
          20008000400080006000800080008000A0008000C0008000E000802000008020
          20008020400080206000802080008020A0008020C0008020E000804000008040
          20008040400080406000804080008040A0008040C0008040E000806000008060
          20008060400080606000806080008060A0008060C0008060E000808000008080
          20008080400080806000808080008080A0008080C0008080E00080A0000080A0
          200080A0400080A0600080A0800080A0A00080A0C00080A0E00080C0000080C0
          200080C0400080C0600080C0800080C0A00080C0C00080C0E00080E0000080E0
          200080E0400080E0600080E0800080E0A00080E0C00080E0E000C0000000C000
          2000C0004000C0006000C0008000C000A000C000C000C000E000C0200000C020
          2000C0204000C0206000C0208000C020A000C020C000C020E000C0400000C040
          2000C0404000C0406000C0408000C040A000C040C000C040E000C0600000C060
          2000C0604000C0606000C0608000C060A000C060C000C060E000C0800000C080
          2000C0804000C0806000C0808000C080A000C080C000C080E000C0A00000C0A0
          2000C0A04000C0A06000C0A08000C0A0A000C0A0C000C0A0E000C0C00000C0C0
          2000C0C04000C0C06000C0C08000C0C0A000F0FBFF00A4A0A000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
          FF08B472292A2A2972B408FFFFFFFFFFFFFFFF9E0E0E0E0E0E0E0E0E0E0E0E0E
          0E0E0E0E0E0E0E0E9EFFFFFFFFFFFF08293232327A7A7A7A3232322908FFFFFF
          FFFF9F4F4F4F4F4F4F4F4F4F4F4F4F4F4F4F4F4F4F4F4F4F0F9FFFFFFFFFB429
          327A32323232323232327A3229B4FFFFFFFF0E4F4F4F4F4F4F4F4F4F4F4F4F4F
          4F4F4F0E4F4F4F4F4F0EFFFFFF732A3B3332333A3A3A32323232337B3B2A73FF
          FFFF0E4F4F4F4F0D0D4F4F4F4F4F4F4F4F4F0E0D0D4F4F4F4F0EFFFFB42A7B32
          323B722829723A3232323232327B2AB4FFFF0E57574F0D9E560D4F4F4F4F4F4F
          4F0E0DEF9E0D4F4F4F0EFF08293B33323B3202FF0828723A3232323232333B29
          08FF0E57570E9EFFF6560E4F575757574F0EEFFFFF9E0E4F4F0EFF213233333B
          3202FFFFFF0828323A32323233333B3221FF4E574E0EEFFFFFF69F0E5757574F
          0EEFFFFFF6560E4F570E08293B333B2902FFF6F6FFFF0828323A32323232337B
          29084E57574E0EEFFFFFFF9F0E574F0EEFFFFFFF560E5757570EB4323B3B2A28
          FFF6F6F6FFFFFF0828323B33333B333B32B44F5757574F0EEFFFFFFF9F0E0EEF
          FFFFFF9F0E575757574E697B333228FFF6F6FFFFFFFFFFFF0828323B3B3B3B32
          7B694F57575757570EEFFFFFFF9F9FFFFFFF9F0E57575757574F02BD7B29FFF6
          F6FF023102FFFFFFFF0828323B3B3B7BBD024F5757575757570EEFFFFFFFFFFF
          FF9F0E5757575757574F21BDBD28F6F6FF023B3B3B02FFFFFFFF0828323B7CBD
          BD025F5F5F5F5F5757570EA7FFFFFFFF9F0E5757575757575F5F02BDBDBD02F6
          02323B3B3B3B02FFFFFFFF082872BDBDBD025FA7A75F5F5F5F574F9FFFFFFFFF
          A74F5757575F5FA7A75F18BDBDBDBE737D7D7D7D7D7D7D02FFFFFFFF0802BDBD
          BD185FA7A7A7A7675F4F9FFFFFFFFFFFFFEF4F5F5FA7A7A7A75F61BD7DBD7DBD
          BD7D7DBD7D7DBDBE02FFFFF6FF08287DBD615FA7A7A7A7A75FAFFFFFFFAFAFFF
          FFFFEF5F9FA7A7A7A75FAB73BE7DBD7D7D7D7D7D7D7D7D7DBD02FFF6F6FF29BE
          73AB5FA7A7A7A75FAFFFFFFFEF5F5FAFFFFFFFEF5F9FA7A7A75F082108BE7D7D
          BD7D7D7D7D7D7D7D7DBD02FFFFFF730821089FA7A7A75FA7F6FFFFEF5FA7A75F
          AFFFFFFFEF5F9FA7A75FFF187408BE7D7D7D7D7D7D7D7D7D7D7DBE02736A0874
          18FF9FA7A75FA7F6FFFFEF5FA7A7A7A75FAFFFFFFFEF5F9FA75FFF0818BD08BE
          BE7D7D7D7D7D7D7D7D7D7DBEBF08BD1808FF9FA7A75FAFFFFFEF5FA7A7A7A7A7
          A75FA7F6FFAF5FA7A79FFFFFAB21BEBFBEBEBEBEBEBEBEBEBEBEBEBEBFBE21AB
          FFFF9FA7A7A75FAFEF5F9FA7A7A7A7A7A7A75FA7AF5FA7A7A79FFFFFFF6B21BD
          BFBEBEBF08BFBEBFBEBEBFBFBD216BFFFFFF9FAFAFAFA75F5F9FAFAFA7A7A7A7
          A7A7A75F5FA7A7A7A79FFFFFFFFFAB1874BEBFBFBFBEBEBFBFBFBE7418ABFFFF
          FFFF9FAFAFAFAFA7A7AFAFAFAFAFAFAFAFAFAFA7A7A7A7A7A79FFFFFFFFFFF08
          18026B75BEBEBEBE756B021808FFFFFFFFFFAFA7AFAFAFAFAFAFAFAFAFAFAFAF
          AFAFAFAFAFAFAFAFA7AFFFFFFFFFFFFFFF08AB591818181859AB08FFFFFFFFFF
          FFFFFFAF9F9F9F9F9F9F9F9F9F9F9F9F9F9F9F9F9F9F9F9FAFFF}
        Margin = 0
        NumGlyphs = 2
        ParentShowHint = False
        ShowHint = True
        OnClick = sbRunModuleClick
      end
      object cbPortName: TListBox
        Left = 8
        Top = 15
        Width = 140
        Height = 65
        Hint = #1053#1072#1081#1076#1077#1085#1085#1099#1077' '#1089#1090#1072#1085#1094#1080#1080
        ItemHeight = 13
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
      object pbLinkQuality: TProgressBar
        Left = 8
        Top = 80
        Width = 140
        Height = 12
        Hint = #1050#1072#1095#1077#1089#1090#1074#1086' '#1089#1074#1103#1079#1080
        Min = 0
        Max = 10
        ParentShowHint = False
        Smooth = True
        ShowHint = True
        TabOrder = 1
      end
    end
    object pnConfig1: TPanel
      Left = 2
      Top = 2
      Width = 1005
      Height = 15
      Align = alTop
      Caption = #1050#1086#1085#1092#1080#1075#1091#1088#1072#1094#1080#1103' '#1086#1073#1086#1088#1091#1076#1086#1074#1072#1085#1080#1103
      Color = clSkyBlue
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
    end
    object gbCounts: TGroupBox
      Left = 582
      Top = 17
      Width = 180
      Height = 96
      Align = alLeft
      Caption = #1057#1095#1077#1090#1095#1080#1082#1080' '#1086#1073#1084#1077#1085#1072' GNS110'
      Constraints.MinWidth = 180
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      object pnGnsTotalRx: TPanel
        Left = 0
        Top = 15
        Width = 115
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1042#1089#1077#1075#1086' '#1087#1088#1080#1085#1103#1090#1086
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
      end
      object pnGnsTotalTx: TPanel
        Left = 0
        Top = 30
        Width = 115
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1042#1089#1077#1075#1086' '#1087#1077#1088#1077#1076#1072#1085#1086
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
      end
      object pnTxPack: TPanel
        Left = 115
        Top = 30
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
      end
      object pnGnsFrameError: TPanel
        Left = 0
        Top = 60
        Width = 115
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1054#1096#1080#1073#1082#1080' '#1082#1072#1076#1088#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
      end
      object pnRxStatErr: TPanel
        Left = 115
        Top = 60
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 4
      end
      object pnGnsCmdError: TPanel
        Left = 0
        Top = 45
        Width = 115
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1054#1096#1080#1073#1082#1080' '#1074' '#1082#1086#1084#1072#1085#1076#1077
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 5
      end
      object pnRxCmdErr: TPanel
        Left = 115
        Top = 45
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 6
      end
      object pnGnsCrcError: TPanel
        Left = 0
        Top = 75
        Width = 115
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1054#1096#1080#1073#1082#1072' CRC'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 7
      end
      object pnRxCrcErr: TPanel
        Left = 115
        Top = 75
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 8
      end
      object pnRxPack: TPanel
        Left = 115
        Top = 15
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 9
      end
    end
    object gbMyCounts: TGroupBox
      Left = 402
      Top = 17
      Width = 180
      Height = 96
      Align = alLeft
      Caption = #1057#1095#1077#1090#1095#1080#1082#1080' '#1086#1073#1084#1077#1085#1072' PC'
      Constraints.MinWidth = 180
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      object pnPcTotalRx: TPanel
        Left = 0
        Top = 15
        Width = 115
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1042#1089#1077#1075#1086' '#1087#1088#1080#1085#1103#1090#1086
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
      end
      object pnPcTotalTx: TPanel
        Left = 0
        Top = 30
        Width = 115
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1042#1089#1077#1075#1086' '#1087#1077#1088#1077#1076#1072#1085#1086
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
      end
      object pnTxPackMy: TPanel
        Left = 115
        Top = 30
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
      end
      object pnPcCntPack: TPanel
        Left = 0
        Top = 60
        Width = 115
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1057#1095#1077#1090#1085#1099#1093' '#1087#1072#1082#1077#1090#1086#1074
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
      end
      object pnXchgOkMy: TPanel
        Left = 115
        Top = 60
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 4
      end
      object pnPcCmdError: TPanel
        Left = 0
        Top = 45
        Width = 115
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1054#1096#1080#1073#1082#1080' '#1074' '#1082#1086#1084#1072#1085#1076#1077
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 5
      end
      object pnRxCmdErrMy: TPanel
        Left = 115
        Top = 45
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 6
      end
      object pnPcXchgErr: TPanel
        Left = 0
        Top = 75
        Width = 115
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1054#1096#1080#1073#1086#1082' '#1086#1073#1084#1077#1085#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 7
      end
      object pnXchgErrMy: TPanel
        Left = 115
        Top = 75
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 8
      end
      object pnRxPackMy: TPanel
        Left = 115
        Top = 15
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 9
      end
    end
    object gbEnviron: TGroupBox
      Left = 762
      Top = 17
      Width = 520
      Height = 96
      Align = alLeft
      Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1089#1090#1072#1085#1094#1080#1080
      Constraints.MinWidth = 50
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      object gbEnvironement: TGroupBox
        Left = 324
        Top = 45
        Width = 195
        Height = 45
        Caption = #1057#1088#1077#1076#1072
        TabOrder = 0
        object Panel29: TPanel
          Left = 65
          Top = 15
          Width = 65
          Height = 15
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = 'T reg,'#176'C'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
        end
        object pnTemp1: TPanel
          Left = 65
          Top = 30
          Width = 65
          Height = 15
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = '0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
        end
        object Panel31: TPanel
          Left = 130
          Top = 15
          Width = 65
          Height = 15
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = 'P reg, kPa'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
        end
        object pnPressure: TPanel
          Left = 130
          Top = 30
          Width = 65
          Height = 15
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = '0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
        end
        object Panel42: TPanel
          Left = 0
          Top = 15
          Width = 65
          Height = 15
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = 'T sp,'#176'C'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
        end
        object pnTemp0: TPanel
          Left = 0
          Top = 30
          Width = 65
          Height = 15
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = '0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 5
        end
      end
      object gbOrientation: TGroupBox
        Left = 129
        Top = 45
        Width = 195
        Height = 45
        Caption = #1055#1086#1083#1086#1078#1077#1085#1080#1077' '#1087#1088#1080#1073#1086#1088#1072
        TabOrder = 1
        object pnPitchName: TPanel
          Left = 0
          Top = 15
          Width = 65
          Height = 15
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = #1050#1088#1077#1085','#176
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
        end
        object pnPitch: TPanel
          Left = 0
          Top = 30
          Width = 65
          Height = 15
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = '0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
        end
        object pnRollName: TPanel
          Left = 65
          Top = 15
          Width = 65
          Height = 15
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = #1053#1072#1082#1083#1086#1085','#176
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
        end
        object pnRoll: TPanel
          Left = 65
          Top = 30
          Width = 65
          Height = 15
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = '0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
        end
        object pnHeadName: TPanel
          Left = 130
          Top = 15
          Width = 65
          Height = 15
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = #1040#1079#1080#1084#1091#1090','#176
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
        end
        object pnHead: TPanel
          Left = 130
          Top = 30
          Width = 65
          Height = 15
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = '0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 5
        end
      end
      object gbFreqs: TGroupBox
        Left = 1
        Top = 45
        Width = 128
        Height = 45
        Caption = #1063#1072#1089#1090#1086#1090#1099', '#1052#1043#1094
        TabOrder = 2
        object Panel18: TPanel
          Left = 0
          Top = 15
          Width = 64
          Height = 15
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = 'CCLK'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
        end
        object pnCclk: TPanel
          Left = 0
          Top = 30
          Width = 64
          Height = 15
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = '0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
        end
        object Panel26: TPanel
          Left = 64
          Top = 15
          Width = 64
          Height = 15
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = 'SCLK'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
        end
        object pnSclk: TPanel
          Left = 64
          Top = 30
          Width = 64
          Height = 15
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = '0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
        end
      end
      object pnQuartz: TPanel
        Left = 0
        Top = 15
        Width = 64
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1052#1043#1094
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
      end
      object pnQuartzFreq: TPanel
        Left = 0
        Top = 30
        Width = 64
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 4
      end
      object Panel22: TPanel
        Left = 64
        Top = 15
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = 'U pow, V'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 5
      end
      object pnSupplyV: TPanel
        Left = 64
        Top = 30
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 6
      end
      object Panel28: TPanel
        Left = 129
        Top = 15
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = 'I q, mA'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 7
      end
      object pnSupplyA: TPanel
        Left = 129
        Top = 30
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 8
      end
      object Panel24: TPanel
        Left = 194
        Top = 15
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = 'U burn, V'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 9
      end
      object pnBurnV: TPanel
        Left = 194
        Top = 30
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 10
      end
      object Panel25: TPanel
        Left = 259
        Top = 15
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = 'I burn, mA'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 11
      end
      object pnBurnA: TPanel
        Left = 259
        Top = 30
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 12
      end
      object Panel53: TPanel
        Left = 324
        Top = 15
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = 'U ext, V'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 13
      end
      object pnBurnExtV: TPanel
        Left = 324
        Top = 30
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 14
      end
      object Panel23: TPanel
        Left = 389
        Top = 15
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = 'U mod, V'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 15
      end
      object pnModemV: TPanel
        Left = 389
        Top = 30
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 16
      end
      object Panel30: TPanel
        Left = 454
        Top = 15
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = 'I mod, mA'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 17
      end
      object pnModemA: TPanel
        Left = 454
        Top = 30
        Width = 65
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 18
      end
    end
  end
  object pcChangeMode: TPageControl
    Left = 0
    Top = 150
    Width = 1009
    Height = 227
    ActivePage = TabSheet1
    Align = alTop
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabIndex = 0
    TabOrder = 3
    object TabSheet1: TTabSheet
      Caption = #1054#1089#1094#1080#1083#1083#1086#1075#1088#1072#1092
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      object gbContr: TGroupBox
        Left = 830
        Top = 0
        Width = 171
        Height = 199
        Align = alRight
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1040#1062#1055
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        object Label4: TLabel
          Left = 5
          Top = 44
          Width = 26
          Height = 13
          Caption = 'PGA'
        end
        object lbFiltName: TLabel
          Left = 5
          Top = 116
          Width = 52
          Height = 13
          Caption = #1060#1042#1063', '#1043#1094
        end
        object lbAdcFreqName: TLabel
          Left = 5
          Top = 20
          Width = 50
          Height = 13
          Caption = #1063#1072#1089#1090#1086#1090#1072
        end
        object lbNumPoint: TLabel
          Left = 5
          Top = 140
          Width = 79
          Height = 13
          Caption = #1058#1086#1095#1077#1082' '#1086#1089#1094#1080#1083'.'
        end
        object lbConsum: TLabel
          Left = 5
          Top = 68
          Width = 79
          Height = 13
          Caption = #1055#1086#1090#1088#1077#1073#1083#1077#1085#1080#1077
        end
        object Label7: TLabel
          Left = 5
          Top = 92
          Width = 30
          Height = 13
          Caption = 'Chop'
        end
        object cbPGA: TComboBox
          Left = 95
          Top = 39
          Width = 65
          Height = 21
          Hint = #1059#1089#1080#1083#1077#1085#1080#1077' '#1082#1072#1085#1072#1083#1086#1074
          Style = csDropDownList
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ItemHeight = 13
          ItemIndex = 0
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
          Text = '1'
          Items.Strings = (
            '1'
            '2'
            '4'
            '8'
            '16'
            '32'
            '64')
        end
        object seFltFreq: TBMSpinEdit
          Left = 95
          Top = 111
          Width = 65
          Height = 24
          Cursor = crArrow
          Hint = #1063#1072#1089#1090#1086#1090#1072' '#1074#1093#1086#1076#1085#1086#1075#1086' '#1092#1080#1083#1100#1090#1088#1072
          EditorEnabled = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
          Increment = 1
          MaxValue = 25
          Precision = 3
          GuageHeight = 1
          TrackBarEnabled = False
        end
        object cbAdcFreq: TComboBox
          Left = 95
          Top = 15
          Width = 65
          Height = 21
          Hint = #1063#1072#1089#1090#1086#1090#1072' '#1040#1062#1055
          Style = csDropDownList
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ItemHeight = 13
          ItemIndex = 0
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 2
          Text = '250'
          Items.Strings = (
            '250'
            '500'
            '1000'
            '2000'
            '4000')
        end
        object cbTimeLimit: TComboBox
          Left = 95
          Top = 135
          Width = 65
          Height = 21
          Hint = #1063#1080#1089#1083#1086' '#1090#1086#1095#1077#1082' '#1076#1072#1085#1085#1099#1093' '#1085#1072' '#1086#1089#1094#1080#1083#1083#1086#1075#1088#1072#1092#1077
          Style = csDropDownList
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ItemHeight = 13
          ItemIndex = 0
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 3
          Text = '1000'
          OnChange = cbTimeLimitChange
          Items.Strings = (
            '1000'
            '2000'
            '5000'
            '10000'
            '20000')
        end
        object cbConsum: TComboBox
          Left = 95
          Top = 63
          Width = 65
          Height = 21
          Hint = #1063#1072#1089#1090#1086#1090#1072' '#1040#1062#1055
          Style = csDropDownList
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ItemHeight = 13
          ItemIndex = 0
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 4
          Text = 'Lo'
          Items.Strings = (
            'Lo'
            'Hi')
        end
        object cbChop: TComboBox
          Left = 95
          Top = 87
          Width = 65
          Height = 21
          Hint = #1059#1089#1080#1083#1077#1085#1080#1077' '#1082#1072#1085#1072#1083#1086#1074
          Style = csDropDownList
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ItemHeight = 13
          ItemIndex = 0
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 5
          Text = '0'
          Items.Strings = (
            '0'
            '1')
        end
      end
      object gbScope: TGroupBox
        Left = 0
        Top = 0
        Width = 830
        Height = 199
        Align = alClient
        Caption = #1044#1072#1085#1085#1099#1077
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        object slsDisplay: TSLScope
          Left = 2
          Top = 15
          Width = 826
          Height = 182
          Cursor = crDefault
          Align = alClient
          ToolBar.BorderColor = clGray
          Zooming.Mode = zmBoth
          NavigateMode = nmZoom
          TabOrder = 0
          InputPins.Count = 4
          InputPins.Form = frmMain
          XInputPins.Count = 4
          XInputPins.Form = frmMain
          YAxis.Align = vaLeft
          YAxis.MinorTicks.Count = 0
          YAxis.MajorTicks.Step = 10
          YAxis.MajorTicks.StartFrom._Floats = (
            (
              StartFrom
              0))
          YAxis.Format.PrecisionMode = dpmGeneral
          YAxis.Format.Precision = 3
          YAxis.Font.Charset = DEFAULT_CHARSET
          YAxis.Font.Color = clWhite
          YAxis.Font.Height = -11
          YAxis.Font.Name = 'Arial'
          YAxis.Font.Style = []
          YAxis.AxisLabel.Font.Charset = DEFAULT_CHARSET
          YAxis.AxisLabel.Font.Color = clWhite
          YAxis.AxisLabel.Font.Height = -13
          YAxis.AxisLabel.Font.Name = 'Arial'
          YAxis.AxisLabel.Font.Style = [fsBold]
          YAxis.AxisLabel.Text = #1044#1072#1085#1085#1099#1077' '#1040#1062#1055
          YAxis.Min.AutoScale = False
          YAxis.Min.DataValue = -8388608
          YAxis.Min.Range.High.Enabled = False
          YAxis.Min.Range.Low.Enabled = False
          YAxis.Min.Value = -8388608
          YAxis.Max.AutoScale = False
          YAxis.Max.DataValue = 8388608
          YAxis.Max.Range.High.Enabled = False
          YAxis.Max.Range.Low.Enabled = False
          YAxis.Max.Value = 8388608
          YAxis.AutoScaling.Enabled = False
          YAxis.AutoScaling.SpaceAbove.Space = 10
          YAxis.AutoScaling.SpaceAbove.Threshold = 5
          YAxis.AutoScaling.SpaceBelow.Space = 10
          YAxis.AutoScaling.SpaceBelow.Threshold = 5
          YAxis.Zooming.Range.High.Enabled = True
          YAxis.Zooming.Range.Low.Enabled = True
          YAxis.DataView.Lines.Pen.Color = clGray
          YAxis.DataView.Lines.Pen.Style = psDot
          YAxis.DataView.ZeroLine.Pen.Color = clWhite
          YAxis.AdditionalAxes = <>
          YAxis.MinMax = (
            -8388608
            8388608
            -1000
            1000
            -50
            50
            0.1
            100000000)
          XAxis.Align = vaBottom
          XAxis.MinorTicks.Count = 0
          XAxis.MajorTicks.Step = 10
          XAxis.MajorTicks.StartFrom._Floats = (
            (
              StartFrom
              0))
          XAxis.Format.PrecisionMode = dpmGeneral
          XAxis.Format.Precision = 3
          XAxis.Font.Charset = DEFAULT_CHARSET
          XAxis.Font.Color = clWhite
          XAxis.Font.Height = -11
          XAxis.Font.Name = 'Arial'
          XAxis.Font.Style = []
          XAxis.AxisLabel.Font.Charset = DEFAULT_CHARSET
          XAxis.AxisLabel.Font.Color = clWhite
          XAxis.AxisLabel.Font.Height = -13
          XAxis.AxisLabel.Font.Name = 'Arial'
          XAxis.AxisLabel.Font.Style = [fsBold]
          XAxis.AxisLabel.Text = 'Time, s'
          XAxis.OnCustomLabel = SLScope1XAxisCustomLabel
          XAxis.TicksMode = atmAuto
          XAxis.UnitScale.Exponent = 0
          XAxis.Min.Range.High.Enabled = False
          XAxis.Min.Range.Low.Enabled = False
          XAxis.Min.Tick._Floats = (
            (
              Value
              0))
          XAxis.Min.Tick.Value = 0
          XAxis.Min._Floats = (
            (
              DataValue
              0)
            (
              Value
              0))
          XAxis.Min.Value = 0
          XAxis.Max.DataValue = 2048
          XAxis.Max.Range.High.Enabled = False
          XAxis.Max.Range.Low.Enabled = False
          XAxis.Max.Tick.Value = 1024
          XAxis.Max.Mode = mamOffset
          XAxis.Max.Value = 200
          XAxis.Zooming.Range.High.Enabled = False
          XAxis.Zooming.Range.Low.Enabled = True
          XAxis.Zooming.Range.Low._Floats = (
            (
              Value
              0))
          XAxis.DataView.Lines.Pen.Color = clGray
          XAxis.DataView.Lines.Pen.Style = psDot
          XAxis.DataView.ZeroLine.Pen.Color = clWhite
          XAxis.AdditionalAxes = <>
          XAxis.MinMaxRange = (
            -1000
            1000
            -1000
            1000
            0
            25)
          Legend.ViewSize.AutoSize = False
          Legend.Align = vaRight
          Legend.Font.Charset = DEFAULT_CHARSET
          Legend.Font.Color = clWhite
          Legend.Font.Height = -11
          Legend.Font.Name = 'Arial'
          Legend.Font.Style = []
          Legend.Channels.Caption.Font.Charset = DEFAULT_CHARSET
          Legend.Channels.Caption.Font.Color = clWhite
          Legend.Channels.Caption.Font.Height = -13
          Legend.Channels.Caption.Font.Name = 'Arial'
          Legend.Channels.Caption.Font.Style = [fsBold]
          Legend.Channels.Caption.Text = 'Channels'
          Legend.ChannelLinks.Caption.Font.Charset = DEFAULT_CHARSET
          Legend.ChannelLinks.Caption.Font.Color = clWhite
          Legend.ChannelLinks.Caption.Font.Height = -13
          Legend.ChannelLinks.Caption.Font.Name = 'Arial'
          Legend.ChannelLinks.Caption.Font.Style = []
          Legend.MarkerGroups.Caption.Font.Charset = DEFAULT_CHARSET
          Legend.MarkerGroups.Caption.Font.Color = clWhite
          Legend.MarkerGroups.Caption.Font.Height = -13
          Legend.MarkerGroups.Caption.Font.Name = 'Arial'
          Legend.MarkerGroups.Caption.Font.Style = [fsBold]
          Legend.Zones.Caption.Font.Charset = DEFAULT_CHARSET
          Legend.Zones.Caption.Font.Color = clWhite
          Legend.Zones.Caption.Font.Height = -13
          Legend.Zones.Caption.Font.Name = 'Arial'
          Legend.Zones.Caption.Font.Style = [fsBold]
          Legend.Ellipses.Caption.Font.Charset = DEFAULT_CHARSET
          Legend.Ellipses.Caption.Font.Color = clWhite
          Legend.Ellipses.Caption.Font.Height = -13
          Legend.Ellipses.Caption.Font.Name = 'Arial'
          Legend.Ellipses.Caption.Font.Style = []
          Legend.Cursors.Caption.Font.Charset = DEFAULT_CHARSET
          Legend.Cursors.Caption.Font.Color = clWhite
          Legend.Cursors.Caption.Font.Height = -13
          Legend.Cursors.Caption.Font.Name = 'Arial'
          Legend.Cursors.Caption.Font.Style = [fsBold]
          Legend.CursorLinks.Caption.Font.Charset = DEFAULT_CHARSET
          Legend.CursorLinks.Caption.Font.Color = clWhite
          Legend.CursorLinks.Caption.Font.Height = -13
          Legend.CursorLinks.Caption.Font.Name = 'Arial'
          Legend.CursorLinks.Caption.Font.Style = [fsBold]
          Legend.CustomGroups = <>
          Title.Align = vaTop
          Title.Text = #1040#1062#1055
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clWhite
          Title.Font.Height = -21
          Title.Font.Name = 'Arial'
          Title.Font.Style = [fsBold]
          DataView.Border.Pen.Color = clGray
          DataView.Border.Pen.Style = psDashDot
          Trails.Font.Charset = DEFAULT_CHARSET
          Trails.Font.Color = clWhite
          Trails.Font.Height = -11
          Trails.Font.Name = 'Arial'
          Trails.Font.Style = []
          Highlighting.Channels.Color = clGreen
          Highlighting.MouseHitPoint.PointLabel.Font.Charset = DEFAULT_CHARSET
          Highlighting.MouseHitPoint.PointLabel.Font.Color = clWhite
          Highlighting.MouseHitPoint.PointLabel.Font.Height = -11
          Highlighting.MouseHitPoint.PointLabel.Font.Name = 'Arial'
          Highlighting.MouseHitPoint.PointLabel.Font.Style = []
          RefreshInterval = 2
          MarkerGroups = <>
          Zones = <>
          Ellipses = <>
          Channels = <
            item
              Name = 'X'
              Tag = 0
              Color = clRed
              Points.Visible = False
              Points.Shape = psCircle
              Points.Brush.Color = clRed
              Points.Brush.Style = bsSolid
              Points.Pen.Color = clRed
              ChannelMode = cmLine
              ShadeMode = csmZero
              Markers = <>
              AxisIndex_ = (
                0
                0)
            end
            item
              Name = 'Y'
              Tag = 0
              Color = clYellow
              Points.Visible = False
              Points.Shape = psCircle
              Points.Brush.Color = clRed
              Points.Brush.Style = bsSolid
              Points.Pen.Color = clRed
              ChannelMode = cmLine
              ShadeMode = csmZero
              Markers = <>
              AxisIndex_ = (
                0
                0)
            end
            item
              Name = 'Z'
              Tag = 0
              Color = clLime
              Points.Visible = False
              Points.Shape = psCircle
              Points.Brush.Color = clRed
              Points.Brush.Style = bsSolid
              Points.Pen.Color = clRed
              ChannelMode = cmLine
              ShadeMode = csmZero
              Markers = <>
              AxisIndex_ = (
                0
                0)
            end
            item
              Name = 'H'
              Tag = 0
              Color = clAqua
              Points.Visible = False
              Points.Shape = psCircle
              Points.Brush.Color = clRed
              Points.Brush.Style = bsSolid
              Points.Pen.Color = clRed
              ChannelMode = cmLine
              ShadeMode = csmZero
              Markers = <>
              AxisIndex_ = (
                0
                0)
            end>
          Cursors = <>
          CursorLinks = <>
          ChannelLinks = <>
          SizeLimit = 201
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #1056#1077#1078#1080#1084' '#1086#1087#1077#1088#1072#1090#1086#1088#1072
      ImageIndex = 1
      object gbFileParams: TGroupBox
        Left = 0
        Top = 0
        Width = 1001
        Height = 199
        Align = alClient
        Caption = #1060#1072#1081#1083' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074
        Constraints.MinWidth = 900
        Ctl3D = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 0
        object pnStartDate: TPanel
          Left = 0
          Top = 65
          Width = 325
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = #1053#1072#1095#1072#1083#1086' '#1088#1077#1075#1080#1089#1090#1088#1072#1094#1080#1080' *'
          Constraints.MinWidth = 325
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          object dtStartDate: TDateTimePicker
            Left = 160
            Top = 0
            Width = 80
            Height = 21
            CalAlignment = dtaLeft
            Date = 41488.5354217708
            Format = 'dd.MM.yy'
            Time = 41488.5354217708
            DateFormat = dfShort
            DateMode = dmComboBox
            Kind = dtkDate
            ParseInput = False
            TabOrder = 0
          end
          object dtStartTime: TDateTimePicker
            Left = 240
            Top = 0
            Width = 80
            Height = 21
            CalAlignment = dtaLeft
            Date = 41485.5152777778
            Format = 'HH:mm:ss'
            Time = 41485.5152777778
            DateFormat = dfShort
            DateMode = dmUpDown
            Kind = dtkTime
            ParseInput = False
            TabOrder = 1
          end
        end
        object pnFinishDate: TPanel
          Left = 0
          Top = 90
          Width = 325
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = #1054#1082#1086#1085#1095#1072#1085#1080#1077' '#1088#1077#1075#1080#1089#1090#1088#1072#1094#1080#1080' *'
          Constraints.MinWidth = 325
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          object dtFinishDate: TDateTimePicker
            Left = 160
            Top = 0
            Width = 80
            Height = 21
            CalAlignment = dtaLeft
            Date = 41488.5354217708
            Format = 'dd.MM.yy'
            Time = 41488.5354217708
            DateFormat = dfShort
            DateMode = dmComboBox
            Kind = dtkDate
            ParseInput = False
            TabOrder = 0
          end
          object dtFinishTime: TDateTimePicker
            Left = 240
            Top = 0
            Width = 80
            Height = 21
            CalAlignment = dtaLeft
            Date = 41485.5152777778
            Format = 'HH:mm:ss'
            Time = 41485.5152777778
            DateFormat = dfShort
            DateMode = dmUpDown
            Kind = dtkTime
            ParseInput = False
            TabOrder = 1
          end
        end
        object pnBurnDate: TPanel
          Left = 0
          Top = 115
          Width = 325
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = #1053#1072#1095#1072#1083#1086' '#1087#1077#1088#1077#1078#1080#1075#1072' *'
          Constraints.MinWidth = 325
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          object dtBurnDate: TDateTimePicker
            Left = 160
            Top = 0
            Width = 80
            Height = 21
            CalAlignment = dtaLeft
            Date = 41488.5354217708
            Format = 'dd.MM.yy'
            Time = 41488.5354217708
            DateFormat = dfShort
            DateMode = dmComboBox
            Kind = dtkDate
            ParseInput = False
            TabOrder = 0
          end
          object dtBurnTime: TDateTimePicker
            Left = 240
            Top = 0
            Width = 80
            Height = 21
            CalAlignment = dtaLeft
            Date = 41485.5152777778
            Format = 'HH:mm:ss'
            Time = 41485.5152777778
            DateFormat = dfShort
            DateMode = dmUpDown
            Kind = dtkTime
            ParseInput = False
            TabOrder = 1
          end
        end
        object pnPopupLen: TPanel
          Left = 325
          Top = 90
          Width = 340
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = #1044#1083#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1074#1089#1087#1083#1099#1090#1080#1103', '#1084
          Constraints.MinWidth = 340
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
          object udPopupLen: TUpDown
            Left = 240
            Top = 0
            Width = 16
            Height = 21
            Associate = mePopupLen
            Min = 1
            Max = 999
            Position = 1
            TabOrder = 0
            Wrap = False
          end
          object mePopupLen: TEdit
            Left = 180
            Top = 0
            Width = 60
            Height = 21
            MaxLength = 4
            TabOrder = 1
            Text = '1'
            OnChange = mePopupLenChange
            OnExit = mePopupLenExit
          end
        end
        object pnModemNum: TPanel
          Left = 325
          Top = 40
          Width = 340
          Height = 25
          Hint = #1045#1089#1083#1080' '#1085#1086#1084#1077#1088' '#1084#1086#1076#1077#1084#1072' 0 - '#1085#1077' '#1084#1077#1085#1103#1077#1084' '#1085#1086#1084#1077#1088
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = #1058#1080#1087' '#1084#1086#1076#1077#1084#1072': '
          Constraints.MinWidth = 340
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 4
          object edModemNum: TEdit
            Left = 260
            Top = 0
            Width = 60
            Height = 25
            Hint = #1045#1089#1083#1080' '#1085#1086#1084#1077#1088' '#1084#1086#1076#1077#1084#1072' 0 - '#1085#1077' '#1084#1077#1085#1103#1077#1084' '#1085#1086#1084#1077#1088
            AutoSize = False
            MaxLength = 4
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            Text = '1'
            OnChange = edModemNumChange
            OnExit = edModemNumExit
          end
          object cbModemNum: TComboBox
            Left = 180
            Top = 0
            Width = 80
            Height = 21
            Hint = #1045#1089#1083#1080' '#1085#1086#1084#1077#1088' '#1084#1086#1076#1077#1084#1072' 0 - '#1085#1077' '#1084#1077#1085#1103#1077#1084' '#1085#1086#1084#1077#1088
            Style = csDropDownList
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ItemHeight = 13
            ItemIndex = 2
            ParentFont = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 1
            Text = 'AM3'
            OnClick = cbModemNumClick
            Items.Strings = (
              'None'
              'AM0'
              'AM3'
              'Bentos')
          end
          object udModemNum: TUpDown
            Left = 320
            Top = 0
            Width = 16
            Height = 25
            Hint = #1045#1089#1083#1080' '#1085#1086#1084#1077#1088' '#1084#1086#1076#1077#1084#1072' 0 - '#1085#1077' '#1084#1077#1085#1103#1077#1084' '#1085#1086#1084#1077#1088
            Associate = edModemNum
            Min = 0
            Max = 9999
            ParentShowHint = False
            Position = 1
            ShowHint = True
            TabOrder = 2
            Thousands = False
            Wrap = False
          end
          object cbChangeModemName: TCheckBox
            Left = 79
            Top = 5
            Width = 98
            Height = 17
            Caption = #1053#1077' '#1084#1077#1085#1103#1090#1100' '#8470
            TabOrder = 3
            OnClick = cbChangeModemNameClick
          end
        end
        object pnAm3PopupDate: TPanel
          Left = 325
          Top = 115
          Width = 340
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = #1042#1088#1077#1084#1103' '#1087#1077#1088#1077#1078#1080#1075#1072' '#1084#1086#1076#1077#1084#1086#1084' *'
          Constraints.MinWidth = 340
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 5
          object dtAm3PopupDate: TDateTimePicker
            Left = 180
            Top = 0
            Width = 80
            Height = 21
            CalAlignment = dtaLeft
            Date = 41488.5354217708
            Format = 'dd.MM.yy'
            Time = 41488.5354217708
            DateFormat = dfShort
            DateMode = dmComboBox
            Kind = dtkDate
            ParseInput = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
          end
          object dtAm3PopupTime: TDateTimePicker
            Left = 260
            Top = 0
            Width = 80
            Height = 21
            CalAlignment = dtaLeft
            Date = 41485.5152777778
            Format = 'HH:mm:ss'
            Time = 41485.5152777778
            DateFormat = dfShort
            DateMode = dmUpDown
            Kind = dtkTime
            ParseInput = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 1
          end
        end
        object pnAm3Cal: TPanel
          Left = 325
          Top = 140
          Width = 340
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = #1057#1074#1077#1090#1083#1086#1077' '#1074#1088#1077#1084#1103' '#1089#1091#1090#1086#1082
          Constraints.MinWidth = 340
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 6
          object Label11: TLabel
            Left = 240
            Top = 5
            Width = 9
            Height = 13
            Caption = ' -'
          end
          object meAm3Cal0: TMaskEdit
            Left = 180
            Top = 0
            Width = 60
            Height = 25
            AutoSize = False
            EditMask = '!90:00;1;_'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            MaxLength = 5
            ParentFont = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            Text = '00:00'
            OnChange = meAm3Cal0Change
          end
          object meAm3Cal1: TMaskEdit
            Left = 260
            Top = 0
            Width = 60
            Height = 25
            AutoSize = False
            EditMask = '!90:00;1;_'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            MaxLength = 5
            ParentFont = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 1
            Text = '00:00'
            OnChange = meAm3Cal1Change
          end
        end
        object edSampleString: TEdit
          Left = 160
          Top = 15
          Width = 505
          Height = 21
          Constraints.MinWidth = 505
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          MaxLength = 77
          ParentFont = False
          TabOrder = 7
        end
        object pnBurnTime: TPanel
          Left = 325
          Top = 65
          Width = 340
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = #1044#1083#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1087#1077#1088#1077#1078#1080#1075#1072', '#1089
          Constraints.MinWidth = 340
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 8
          object udBurnTime: TUpDown
            Left = 240
            Top = 0
            Width = 16
            Height = 21
            Associate = edBurnTime
            Min = 1
            Max = 999
            Position = 1
            TabOrder = 0
            Wrap = False
          end
          object edBurnTime: TEdit
            Left = 180
            Top = 0
            Width = 60
            Height = 21
            MaxLength = 4
            TabOrder = 1
            Text = '1'
            OnChange = edBurnTimeChange
            OnExit = edBurnTimeExit
          end
        end
        object pnAdcFreq: TPanel
          Left = 665
          Top = 15
          Width = 280
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = #1063#1072#1089#1090#1086#1090#1072' '#1086#1094#1080#1092#1088#1086#1074#1082#1080' '#1040#1062#1055', '#1043#1094
          Constraints.MinWidth = 280
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 9
          object cbAdcSample: TComboBox
            Left = 190
            Top = 0
            Width = 80
            Height = 21
            Style = csDropDownList
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ItemHeight = 13
            ItemIndex = 2
            ParentFont = False
            TabOrder = 0
            Text = '250'
            Items.Strings = (
              '62'
              '125'
              '250'
              '500'
              '1000'
              '2000'
              '4000')
          end
        end
        object pnAdcPga: TPanel
          Left = 665
          Top = 65
          Width = 280
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = 'PGA '#1040#1062#1055
          Constraints.MinWidth = 280
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 10
          object cbAdcPGA: TComboBox
            Left = 190
            Top = 0
            Width = 80
            Height = 21
            Style = csDropDownList
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ItemHeight = 13
            ItemIndex = 0
            ParentFont = False
            TabOrder = 0
            Text = '1'
            Items.Strings = (
              '1'
              '2'
              '4'
              '8'
              '16'
              '32'
              '64')
          end
        end
        object pnAdcEnergo: TPanel
          Left = 665
          Top = 40
          Width = 280
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = #1069#1085#1077#1088#1075#1086#1087#1086#1090#1088#1077#1073#1083#1077#1085#1080#1077'  '#1040#1062#1055
          Constraints.MinWidth = 280
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 11
          object cbAdcCons: TComboBox
            Left = 190
            Top = 0
            Width = 80
            Height = 21
            Style = csDropDownList
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ItemHeight = 13
            ItemIndex = 1
            ParentFont = False
            TabOrder = 0
            Text = #1064#1090#1072#1090#1085#1086#1077
            Items.Strings = (
              #1055#1086#1085#1080#1078#1077#1085#1085#1086#1077
              #1064#1090#1072#1090#1085#1086#1077)
          end
        end
        object pnNumBytes: TPanel
          Left = 665
          Top = 90
          Width = 280
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = #1063#1080#1089#1083#1086' '#1073#1072#1081#1090' '#1074' '#1089#1083#1086#1074#1077' '#1076#1072#1085#1085#1099#1093
          Constraints.MinWidth = 280
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 12
          object cbNumBytes: TComboBox
            Left = 190
            Top = 0
            Width = 80
            Height = 21
            Style = csDropDownList
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ItemHeight = 13
            ItemIndex = 0
            ParentFont = False
            TabOrder = 0
            Text = '3'
            Items.Strings = (
              '3'
              '4')
          end
        end
        object pnChannels: TPanel
          Left = 665
          Top = 115
          Width = 280
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = #1042#1082#1083#1102#1095#1077#1085#1085#1099#1077' '#1082#1072#1085#1072#1083#1099
          Constraints.MinWidth = 280
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 13
          object cbChan1: TCheckBox
            Left = 134
            Top = 5
            Width = 25
            Height = 17
            Alignment = taLeftJustify
            Caption = 'x'
            Checked = True
            State = cbChecked
            TabOrder = 0
          end
          object cbChan2: TCheckBox
            Left = 164
            Top = 5
            Width = 25
            Height = 17
            Alignment = taLeftJustify
            Caption = 'y'
            Checked = True
            State = cbChecked
            TabOrder = 1
          end
          object cbChan3: TCheckBox
            Left = 194
            Top = 5
            Width = 25
            Height = 17
            Alignment = taLeftJustify
            Caption = 'z'
            Checked = True
            State = cbChecked
            TabOrder = 2
          end
          object cbChan4: TCheckBox
            Left = 224
            Top = 5
            Width = 25
            Height = 17
            Alignment = taLeftJustify
            Caption = 'h'
            Checked = True
            State = cbChecked
            TabOrder = 3
          end
        end
        object pnFileLen: TPanel
          Left = 665
          Top = 140
          Width = 280
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = #1044#1083#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1092#1072#1081#1083#1072' '#1079#1072#1087#1080#1089#1080
          Constraints.MinWidth = 280
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 14
          object cbDataFileLen: TComboBox
            Left = 190
            Top = 0
            Width = 80
            Height = 21
            Style = csDropDownList
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ItemHeight = 13
            ItemIndex = 1
            ParentFont = False
            TabOrder = 0
            Text = '4 '#1095#1072#1089#1072
            Items.Strings = (
              '1 '#1095#1072#1089
              '4 '#1095#1072#1089#1072
              '1 '#1089#1091#1090#1082#1080)
          end
        end
        object pnFiltFreq: TPanel
          Left = 665
          Top = 165
          Width = 280
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = #1063#1072#1089#1090#1086#1090#1072' '#1089#1088#1077#1079#1072' '#1060#1042#1063', '#1043#1094
          Constraints.MinWidth = 280
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 15
          object seFreq: TBMSpinEdit
            Left = 190
            Top = 0
            Width = 80
            Height = 24
            Cursor = crArrow
            AutoSize = False
            EditorEnabled = False
            TabOrder = 0
            Increment = 0.001
            IncrementGauge = 0.001
            MaxValue = 25
            Precision = 3
            GuageHeight = 1
            TrackBarEnabled = False
          end
          object cbFreq: TCheckBox
            Left = 160
            Top = 4
            Width = 15
            Height = 17
            Hint = #1042#1082#1083#1102#1095#1080#1090#1100' '#1092#1080#1083#1100#1090#1088
            ParentShowHint = False
            ShowHint = True
            TabOrder = 1
            OnClick = cbFreqClick
          end
        end
        object pnConstReg: TPanel
          Left = 0
          Top = 140
          Width = 325
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = #1055#1086#1089#1090#1086#1103#1085#1085#1072#1103' '#1088#1077#1075#1080#1089#1090#1088#1072#1094#1080#1103
          Constraints.MinWidth = 325
          Enabled = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 16
          object cbConstReg: TCheckBox
            Left = 280
            Top = 5
            Width = 15
            Height = 17
            Enabled = False
            TabOrder = 0
            OnClick = cbConstRegClick
          end
        end
        object pnPosition: TPanel
          Left = 0
          Top = 40
          Width = 325
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = #1055#1086#1079#1080#1094#1080#1103' '#1091#1089#1090#1072#1085#1086#1074#1082#1080
          Constraints.MinWidth = 325
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 17
          object edPosition: TEdit
            Left = 160
            Top = 0
            Width = 80
            Height = 21
            MaxLength = 5
            TabOrder = 0
            Text = '1'
            OnChange = edPositionChange
          end
        end
        object pnComments: TPanel
          Left = 0
          Top = 15
          Width = 160
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Caption = #1050#1086#1084#1077#1085#1090#1072#1088#1080#1080' (80 '#1089#1080#1084#1074'.)'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 18
        end
        object pnDisk: TPanel
          Left = 0
          Top = 165
          Width = 665
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          Constraints.MinWidth = 665
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 19
          object SpeedButton1: TSpeedButton
            Left = 160
            Top = 2
            Width = 23
            Height = 22
            Glyph.Data = {
              76010000424D7601000000000000760000002800000020000000100000000100
              04000000000000010000130B0000130B00001000000000000000000000000000
              800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0033333333B333
              333B33FF33337F3333F73BB3777BB7777BB3377FFFF77FFFF77333B000000000
              0B3333777777777777333330FFFFFFFF07333337F33333337F333330FFFFFFFF
              07333337F3FF3FFF7F333330F00F000F07333337F77377737F333330FFFFFFFF
              07333FF7F3FFFF3F7FFFBBB0F0000F0F0BB37777F7777373777F3BB0FFFFFFFF
              0BBB3777F3FF3FFF77773330F00F000003333337F773777773333330FFFF0FF0
              33333337F3FF7F37F3333330F08F0F0B33333337F7737F77FF333330FFFF003B
              B3333337FFFF77377FF333B000000333BB33337777777F3377FF3BB3333BB333
              3BB33773333773333773B333333B3333333B7333333733333337}
            NumGlyphs = 2
            OnClick = SpeedButton1Click
          end
          object sbOpenLogPath: TSpeedButton
            Left = 140
            Top = 2
            Width = 23
            Height = 22
            Glyph.Data = {
              76010000424D7601000000000000760000002800000020000000100000000100
              04000000000000010000120B0000120B00001000000000000000000000000000
              800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00555555555555
              555555FFFFFFFFFF55555000000000055555577777777775FFFF00B8B8B8B8B0
              0000775F5555555777770B0B8B8B8B8B0FF07F75F555555575F70FB0B8B8B8B8
              B0F07F575FFFFFFFF7F70BFB0000000000F07F557777777777570FBFBF0FFFFF
              FFF07F55557F5FFFFFF70BFBFB0F000000F07F55557F777777570FBFBF0FFFFF
              FFF075F5557F5FFFFFF750FBFB0F000000F0575FFF7F777777575700000FFFFF
              FFF05577777F5FF55FF75555550F00FF00005555557F775577775555550FFFFF
              0F055555557F55557F755555550FFFFF00555555557FFFFF7755555555000000
              0555555555777777755555555555555555555555555555555555}
            NumGlyphs = 2
            Visible = False
          end
          object lbUtcTimeComment: TLabel
            Left = 320
            Top = 5
            Width = 97
            Height = 13
            Caption = '     * '#1042#1088#1077#1084#1103' UTC'
          end
          object dcbDisk: TDriveComboBox
            Left = 9
            Top = 6
            Width = 80
            Height = 19
            TabOrder = 0
          end
          object btnCheckParams: TBitBtn
            Left = 200
            Top = 2
            Width = 80
            Height = 20
            Hint = #1055#1088#1086#1074#1077#1088#1080#1090#1100' '#1079#1072#1087#1080#1089#1072#1085#1099#1081' '#1092#1072#1081#1083
            Caption = #1057#1088#1072#1074#1085#1080#1090#1100
            ParentShowHint = False
            ShowHint = True
            TabOrder = 1
            OnClick = btnCheckParamsClick
            Kind = bkYes
          end
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = #1056#1077#1078#1080#1084' '#1085#1072#1083#1072#1076#1082#1080
      ImageIndex = 2
      object gbModem: TGroupBox
        Left = 0
        Top = 0
        Width = 1001
        Height = 199
        Align = alClient
        Caption = #1052#1086#1076#1077#1084
        Constraints.MinWidth = 950
        TabOrder = 0
        object lbUtcTimeMet: TLabel
          Left = 320
          Top = 180
          Width = 97
          Height = 13
          Caption = '     * '#1042#1088#1077#1084#1103' UTC'
        end
        object gbModemNum: TGroupBox
          Left = 5
          Top = 15
          Width = 340
          Height = 40
          Caption = #1053#1086#1084#1077#1088' '#1084#1086#1076#1077#1084#1072
          TabOrder = 0
          object ltModemNum: TLight
            Left = 310
            Top = 15
            Width = 15
            Height = 15
            Brush.Color = clRed
            Shape = stEllipse
            OnColor = clLime
            OffColor = clRed
          end
          object meModemNum: TEdit
            Left = 5
            Top = 15
            Width = 75
            Height = 20
            Hint = 
              #1053#1086#1084#1077#1088' '#1084#1086#1076#1077#1084#1072' (1...9999). 0-'#1085#1077' '#1086#1087#1088#1072#1096#1080#1074#1072#1102'. -1 - '#1085#1077#1090' '#1084#1086#1076#1077#1084#1072'. -2 - '#1089 +
              #1090#1072#1088#1099#1081' '#1084#1086#1076#1077#1084'.'
            AutoSize = False
            MaxLength = 4
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            Text = '1'
            OnChange = edModemNumChange
            OnExit = edModemNumExit
          end
          object udmeModemNum: TUpDown
            Left = 80
            Top = 15
            Width = 16
            Height = 20
            Associate = meModemNum
            Min = 1
            Max = 9999
            Position = 1
            TabOrder = 1
            Thousands = False
            Wrap = False
          end
          object btnSetModemNum: TBitBtn
            Left = 245
            Top = 10
            Width = 60
            Height = 22
            Caption = 'Send'
            Enabled = False
            TabOrder = 2
            Visible = False
            OnClick = btnSetModemNumClick
            Kind = bkYes
          end
          object btnGetModemNum: TBitBtn
            Left = 180
            Top = 10
            Width = 60
            Height = 22
            Caption = 'Get'
            Enabled = False
            TabOrder = 3
            Visible = False
            OnClick = btnGetModemTimeClick
            Kind = bkRetry
          end
        end
        object gbModemRtc: TGroupBox
          Left = 5
          Top = 55
          Width = 340
          Height = 40
          Caption = #1042#1088#1077#1084#1103' RTC '#1084#1086#1076#1077#1084#1072' ('#1076#1076'.'#1084#1084'.'#1075#1075#1075#1075' '#1095#1095':'#1084#1084') *'
          TabOrder = 1
          object ltModemTime: TLight
            Left = 310
            Top = 15
            Width = 15
            Height = 15
            Brush.Color = clRed
            Shape = stEllipse
            OnColor = clLime
            OffColor = clRed
          end
          object dtModemTime: TDateTimePicker
            Left = 100
            Top = 15
            Width = 75
            Height = 21
            CalAlignment = dtaLeft
            Date = 41485.5152777778
            Format = 'HH:mm:ss'
            Time = 41485.5152777778
            DateFormat = dfShort
            DateMode = dmUpDown
            Kind = dtkTime
            ParseInput = False
            TabOrder = 1
          end
          object btnGetModemTime: TBitBtn
            Left = 180
            Top = 10
            Width = 60
            Height = 22
            Caption = 'Get'
            Enabled = False
            TabOrder = 2
            Visible = False
            OnClick = btnGetModemTimeClick
            Kind = bkRetry
          end
          object btnSetModemTime: TBitBtn
            Left = 245
            Top = 10
            Width = 60
            Height = 22
            Caption = 'Send'
            Enabled = False
            TabOrder = 3
            Visible = False
            OnClick = btnSetModemTimeClick
            Kind = bkYes
          end
          object dtModemDate: TDateTimePicker
            Left = 5
            Top = 15
            Width = 90
            Height = 21
            CalAlignment = dtaLeft
            Date = 41488.5354217708
            Format = 'dd.MM.yyyy'
            Time = 41488.5354217708
            DateFormat = dfShort
            DateMode = dmComboBox
            Kind = dtkDate
            ParseInput = False
            TabOrder = 0
          end
        end
        object gbModemAlarm: TGroupBox
          Left = 5
          Top = 95
          Width = 340
          Height = 40
          Caption = #1042#1088#1077#1084#1103' '#1072#1074#1072#1088#1080#1081#1085#1086#1075#1086' '#1087#1077#1088#1077#1078#1080#1075#1072' ('#1076#1076'.'#1084#1084'.'#1075#1075#1075#1075' '#1095#1095':'#1084#1084') *'
          TabOrder = 2
          object ltAlarmTime: TLight
            Left = 310
            Top = 15
            Width = 15
            Height = 15
            Brush.Color = clRed
            Shape = stEllipse
            OnColor = clLime
            OffColor = clRed
          end
          object dtAlarmTime: TDateTimePicker
            Left = 100
            Top = 15
            Width = 75
            Height = 21
            CalAlignment = dtaLeft
            Date = 41474.5158755903
            Format = 'HH:mm'
            Time = 41474.5158755903
            DateFormat = dfShort
            DateMode = dmUpDown
            Kind = dtkTime
            ParseInput = False
            TabOrder = 1
          end
          object btnGetAlarmTime: TBitBtn
            Left = 180
            Top = 10
            Width = 60
            Height = 22
            Caption = 'Get'
            Enabled = False
            TabOrder = 2
            Visible = False
            OnClick = btnGetAlarmTimeClick
            Kind = bkRetry
          end
          object btnSetAlarmTime: TBitBtn
            Left = 245
            Top = 10
            Width = 60
            Height = 22
            Caption = 'Send'
            Enabled = False
            TabOrder = 3
            Visible = False
            OnClick = btnSetAlarmTimeClick
            Kind = bkYes
          end
          object dtAlarmDate: TDateTimePicker
            Left = 5
            Top = 15
            Width = 90
            Height = 21
            CalAlignment = dtaLeft
            Date = 41488.5354217708
            Format = 'dd.MM.yyyy'
            Time = 41488.5354217708
            DateFormat = dfShort
            DateMode = dmComboBox
            Kind = dtkDate
            ParseInput = False
            TabOrder = 0
          end
        end
        object gbModemLightTime: TGroupBox
          Left = 345
          Top = 15
          Width = 340
          Height = 40
          Caption = #1057#1074#1077#1090#1083#1086#1077' '#1074#1088#1077#1084#1103' '#1089#1091#1090#1086#1082
          TabOrder = 3
          object Label13: TLabel
            Left = 82
            Top = 20
            Width = 5
            Height = 13
            Caption = '-'
          end
          object ltCalTime: TLight
            Left = 310
            Top = 15
            Width = 15
            Height = 15
            Brush.Color = clRed
            Shape = stEllipse
            OnColor = clLime
            OffColor = clRed
          end
          object btnGetCalTime: TBitBtn
            Left = 180
            Top = 15
            Width = 60
            Height = 22
            Caption = 'Get'
            Enabled = False
            TabOrder = 2
            Visible = False
            OnClick = btnGetCalTimeClick
            Kind = bkRetry
          end
          object btnSetCalTime: TBitBtn
            Left = 245
            Top = 15
            Width = 60
            Height = 22
            Caption = 'Send'
            Enabled = False
            TabOrder = 3
            Visible = False
            OnClick = btnSetCalTimeClick
            Kind = bkYes
          end
          object dtCalTime1: TDateTimePicker
            Left = 90
            Top = 15
            Width = 75
            Height = 21
            CalAlignment = dtaLeft
            Date = 41474.5158755903
            Format = 'HH:mm'
            Time = 41474.5158755903
            DateFormat = dfShort
            DateMode = dmUpDown
            Kind = dtkTime
            ParseInput = False
            TabOrder = 1
          end
          object dtCalTime0: TDateTimePicker
            Left = 5
            Top = 15
            Width = 75
            Height = 21
            CalAlignment = dtaLeft
            Date = 41474.5158755903
            Format = 'HH:mm'
            Time = 41474.5158755903
            DateFormat = dfShort
            DateMode = dmUpDown
            Kind = dtkTime
            ParseInput = False
            TabOrder = 0
          end
        end
        object gbModemPopup: TGroupBox
          Left = 345
          Top = 55
          Width = 340
          Height = 40
          Caption = #1042#1088#1077#1084#1103' '#1087#1086#1076#1098#1077#1084#1072' '#1089#1086' '#1076#1085#1072' ('#1084#1080#1085')'
          TabOrder = 4
          object ltTimeForRelease: TLight
            Left = 310
            Top = 15
            Width = 15
            Height = 15
            Brush.Color = clRed
            Shape = stEllipse
            OnColor = clLime
            OffColor = clRed
          end
          object udTimeForRelease: TUpDown
            Left = 60
            Top = 15
            Width = 15
            Height = 21
            Associate = meTimeForRelease
            Min = 1
            Max = 1000
            Position = 1
            TabOrder = 0
            Wrap = False
          end
          object btnGetTimeForRelease: TBitBtn
            Left = 180
            Top = 15
            Width = 60
            Height = 22
            Caption = 'Get'
            Enabled = False
            TabOrder = 1
            Visible = False
            OnClick = btnGetTimeForReleaseClick
            Kind = bkRetry
          end
          object btnSetTimeForRelease: TBitBtn
            Left = 245
            Top = 15
            Width = 60
            Height = 22
            Caption = 'Send'
            Enabled = False
            TabOrder = 2
            Visible = False
            OnClick = btnSetTimeForReleaseClick
            Kind = bkYes
          end
          object meTimeForRelease: TEdit
            Left = 5
            Top = 15
            Width = 55
            Height = 21
            MaxLength = 4
            TabOrder = 3
            Text = '1'
            OnChange = meTimeForReleaseChange
          end
        end
        object gbModemBurnLen: TGroupBox
          Left = 345
          Top = 95
          Width = 340
          Height = 40
          Caption = #1044#1083#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1087#1077#1088#1077#1078#1080#1075#1072' '#1087#1088#1086#1074#1086#1083#1086#1082#1080' ('#1089')'
          TabOrder = 5
          object ltBurnLen: TLight
            Left = 310
            Top = 15
            Width = 15
            Height = 15
            Brush.Color = clRed
            Shape = stEllipse
            OnColor = clLime
            OffColor = clRed
          end
          object udBurnLen: TUpDown
            Left = 60
            Top = 15
            Width = 15
            Height = 21
            Associate = meBurnLen
            Min = 1
            Max = 99
            Position = 5
            TabOrder = 0
            Wrap = False
          end
          object btnGetBurnLen: TBitBtn
            Left = 180
            Top = 15
            Width = 60
            Height = 22
            Caption = 'Get'
            Enabled = False
            TabOrder = 1
            Visible = False
            OnClick = btnGetBurnLenClick
            Kind = bkRetry
          end
          object btnSetBurnLen: TBitBtn
            Left = 245
            Top = 15
            Width = 60
            Height = 22
            Caption = 'Send'
            Enabled = False
            TabOrder = 2
            Visible = False
            OnClick = btnSetBurnLenClick
            Kind = bkYes
          end
          object meBurnLen: TEdit
            Left = 5
            Top = 15
            Width = 55
            Height = 21
            MaxLength = 2
            TabOrder = 3
            Text = '5'
            OnChange = meBurnLenChange
          end
        end
        object gbModemBurnOn: TGroupBox
          Left = 685
          Top = 15
          Width = 340
          Height = 40
          Caption = #1042#1082#1083#1102#1095#1080#1090#1100'/'#1042#1099#1082#1083#1102#1095#1080#1090#1100' '#1087#1077#1088#1077#1078#1080#1075
          Constraints.MinWidth = 340
          TabOrder = 6
          object ltBurnCmdOnOff: TLight
            Left = 310
            Top = 15
            Width = 15
            Height = 15
            Brush.Color = clRed
            Shape = stEllipse
            OnColor = clLime
            OffColor = clRed
          end
          object btnBurnCmdOn: TBitBtn
            Left = 10
            Top = 15
            Width = 120
            Height = 22
            Caption = #1042#1082#1083
            Enabled = False
            TabOrder = 0
            OnClick = btnBurnCmdOnClick
            Kind = bkRetry
          end
        end
        object gbModemLampOn: TGroupBox
          Left = 685
          Top = 55
          Width = 340
          Height = 40
          Caption = #1042#1082#1083#1102#1095#1080#1090#1100'/'#1042#1099#1082#1083#1102#1095#1080#1090#1100' '#1083#1072#1084#1087#1091
          Constraints.MinWidth = 340
          TabOrder = 7
          object ltLampOnOff: TLight
            Left = 310
            Top = 15
            Width = 15
            Height = 15
            Brush.Color = clRed
            Shape = stEllipse
            OnColor = clLime
            OffColor = clRed
          end
          object btnLampOn: TBitBtn
            Left = 10
            Top = 15
            Width = 120
            Height = 22
            Caption = #1042#1082#1083
            Enabled = False
            TabOrder = 0
            OnClick = btnLampOnClick
            Kind = bkRetry
          end
        end
        object gbModemRadioOn: TGroupBox
          Left = 685
          Top = 95
          Width = 340
          Height = 40
          Caption = #1042#1082#1083#1102#1095#1080#1090#1100'/'#1042#1099#1082#1083#1102#1095#1080#1090#1100' '#1088#1072#1076#1080#1086
          Constraints.MinWidth = 340
          TabOrder = 8
          object ltRadioOnOff: TLight
            Left = 310
            Top = 15
            Width = 15
            Height = 15
            Brush.Color = clRed
            Shape = stEllipse
            OnColor = clLime
            OffColor = clRed
          end
          object btnRadioOn: TBitBtn
            Left = 10
            Top = 15
            Width = 120
            Height = 22
            Caption = #1042#1082#1083
            Enabled = False
            TabOrder = 0
            OnClick = btnRadioOnClick
            Kind = bkRetry
          end
        end
        object gbModemPingSend: TGroupBox
          Left = 685
          Top = 135
          Width = 340
          Height = 40
          Caption = #1055#1086#1089#1083#1072#1090#1100' '#1080#1084#1087#1091#1083#1100#1089'('#1099') '#1087#1086' '#1072#1082#1091#1089#1090#1080#1095#1077#1089#1082#1086#1084#1091' '#1082#1072#1085#1072#1083#1091
          Constraints.MinWidth = 340
          TabOrder = 9
          object ltPing: TLight
            Left = 310
            Top = 15
            Width = 15
            Height = 15
            Brush.Color = clRed
            Shape = stEllipse
            OnColor = clLime
            OffColor = clRed
          end
          object Label1: TLabel
            Left = 110
            Top = 20
            Width = 30
            Height = 13
            Caption = 'Num:'
          end
          object Label5: TLabel
            Left = 5
            Top = 20
            Width = 26
            Height = 13
            Caption = 'Freq'
          end
          object btnPing11: TBitBtn
            Left = 200
            Top = 15
            Width = 60
            Height = 22
            Caption = 'Send'
            Enabled = False
            TabOrder = 0
            OnClick = btnPing11Click
            Kind = bkOK
          end
          object edPingCount: TEdit
            Left = 145
            Top = 15
            Width = 35
            Height = 21
            Hint = #1063#1080#1089#1083#1086' '#1087#1086#1089#1099#1083#1086#1082
            MaxLength = 4
            ParentShowHint = False
            ShowHint = True
            TabOrder = 1
            Text = '3'
            OnChange = meTimeForReleaseChange
          end
          object udPingCount: TUpDown
            Left = 180
            Top = 15
            Width = 16
            Height = 21
            Associate = edPingCount
            Min = 1
            Position = 3
            TabOrder = 2
            Wrap = False
          end
          object cbPingFreq: TComboBox
            Left = 35
            Top = 16
            Width = 70
            Height = 21
            Hint = #1063#1072#1089#1090#1086#1090#1072' '#1087#1086#1089#1099#1083#1082#1080
            Style = csDropDownList
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ItemHeight = 13
            ItemIndex = 1
            ParentFont = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 3
            Text = '11 '#1082#1043#1094
            Items.Strings = (
              '9  '#1082#1043#1094
              '11 '#1082#1043#1094
              '13 '#1082#1043#1094)
          end
        end
        object gbModemWriteParams: TGroupBox
          Left = 345
          Top = 135
          Width = 340
          Height = 40
          Caption = #1047#1072#1087#1080#1089#1072#1090#1100' '#1087#1072#1088#1072#1084#1077#1090#1088#1099' '#1074' '#1084#1086#1076#1077#1084
          TabOrder = 10
          object ltApplyCommand: TLight
            Left = 310
            Top = 15
            Width = 15
            Height = 15
            Brush.Color = clRed
            Shape = stEllipse
            OnColor = clLime
            OffColor = clRed
          end
          object btnApplyCommand: TBitBtn
            Left = 5
            Top = 15
            Width = 60
            Height = 22
            Caption = 'Send'
            Enabled = False
            TabOrder = 0
            OnClick = btnApplyCommandClick
            Kind = bkOK
          end
        end
        object gbRandomStr: TGroupBox
          Left = 5
          Top = 135
          Width = 340
          Height = 40
          Caption = #1055#1086#1089#1083#1072#1090#1100' '#1087#1088#1086#1080#1079#1074#1086#1083#1100#1085#1091#1102' '#1082#1086#1084#1072#1085#1076#1091
          TabOrder = 11
          object ltModemCmd: TLight
            Left = 310
            Top = 15
            Width = 15
            Height = 15
            Brush.Color = clRed
            Shape = stEllipse
            OnColor = clLime
            OffColor = clRed
          end
          object edAnyCommand: TEdit
            Left = 4
            Top = 16
            Width = 170
            Height = 21
            Hint = #1051#1102#1073#1072#1103' '#1082#1086#1084#1072#1085#1076#1072' ('#1057#1077#1081#1095#1072#1089': '#1074#1099#1082#1083#1102#1095#1080#1090#1100' '#1088#1072#1076#1080#1086') '
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            Text = '$RSAGR,0,*e8c0'
          end
          object btnModemAnyString: TBitBtn
            Left = 180
            Top = 12
            Width = 60
            Height = 25
            Hint = #1051#1102#1073#1072#1103' '#1082#1086#1084#1072#1085#1076#1072' '#1084#1086#1076#1077#1084#1091': '#1085#1072#1095#1080#1085#1072#1077#1090#1089#1103' '#1089' $, '#1079#1072#1082#1072#1085#1095#1080#1074#1072#1077#1090#1089#1103' *'
            Caption = 'Send'
            Enabled = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 1
            OnClick = btnModemAnyStringClick
            Kind = bkOK
          end
        end
        object cbUpdateTime: TCheckBox
          Left = 130
          Top = 180
          Width = 157
          Height = 17
          Caption = #1054#1073#1085#1086#1074#1083#1103#1090#1100' '#1074#1088#1077#1084#1103
          TabOrder = 12
        end
      end
    end
  end
  object memoLog: TMemo
    Left = 0
    Top = 542
    Width = 1009
    Height = 55
    Align = alClient
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    OEMConvert = True
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 4
  end
  object pnStatus: TPanel
    Left = 0
    Top = 382
    Width = 1009
    Height = 160
    Align = alTop
    TabOrder = 5
    object gbStatus1: TGroupBox
      Left = 191
      Top = 16
      Width = 190
      Height = 143
      Align = alLeft
      Caption = #1057#1072#1084#1086#1090#1077#1089#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1091#1089#1090#1088#1086#1081#1089#1090#1074
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      object lbStatus1_0: TLabel
        Left = 5
        Top = 15
        Width = 26
        Height = 13
        Caption = 'RTC'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus1_1: TLabel
        Left = 5
        Top = 30
        Width = 104
        Height = 13
        Caption = #1044#1072#1090#1095#1080#1082' '#1076#1072#1074#1083#1077#1085#1080#1103
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus1_2: TLabel
        Left = 5
        Top = 45
        Width = 87
        Height = 13
        Caption = #1040#1082#1089#1077#1083#1077#1088#1086#1084#1077#1090#1088
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus1_3: TLabel
        Left = 5
        Top = 60
        Width = 46
        Height = 13
        Caption = #1050#1086#1084#1087#1072#1089
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus1_4: TLabel
        Left = 5
        Top = 75
        Width = 77
        Height = 13
        Caption = 'GPS '#1084#1086#1076#1091#1083#1100' '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus1_5: TLabel
        Left = 5
        Top = 90
        Width = 53
        Height = 13
        Caption = 'EEPROM'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus1_6: TLabel
        Left = 5
        Top = 105
        Width = 56
        Height = 13
        Caption = 'SD '#1082#1072#1088#1090#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus1_7: TLabel
        Left = 5
        Top = 120
        Width = 31
        Height = 13
        Caption = 'Flash'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object gbStatus0: TGroupBox
      Left = 1
      Top = 16
      Width = 190
      Height = 143
      Align = alLeft
      Caption = #1043#1083#1072#1074#1085#1099#1081' '#1089#1090#1072#1090#1091#1089
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      object lbStatus0_3: TLabel
        Left = 5
        Top = 60
        Width = 176
        Height = 13
        Caption = #1053#1077' '#1085#1072#1081#1076#1077#1085' '#1092#1072#1081#1083' '#1088#1077#1075#1080#1089#1090#1088#1072#1094#1080#1080
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus0_4: TLabel
        Left = 5
        Top = 75
        Width = 208
        Height = 13
        Caption = #1053#1077#1080#1089#1087#1088#1072#1074#1085#1086#1089#1090#1100' '#1040#1062#1055' '#1088#1077#1075#1080#1089#1090#1088#1072#1090#1086#1088#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus0_5: TLabel
        Left = 5
        Top = 90
        Width = 219
        Height = 13
        Caption = #1055#1077#1088#1077#1087#1086#1083#1085#1077#1085#1080#1077' '#1087#1072#1084#1103#1090#1080' '#1088#1077#1075#1080#1089#1090#1088#1072#1090#1086#1088#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus0_6: TLabel
        Left = 5
        Top = 105
        Width = 135
        Height = 13
        Caption = #1054#1089#1094#1080#1083#1083#1086#1075#1088#1072#1092' '#1074#1082#1083#1102#1095#1077#1085
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus0_7: TLabel
        Left = 5
        Top = 120
        Width = 199
        Height = 13
        Caption = #1057#1072#1084#1086#1090#1077#1089#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1088#1077#1075#1080#1089#1090#1088#1072#1090#1086#1088#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus2_1: TLabel
        Left = 5
        Top = 15
        Width = 95
        Height = 13
        Caption = #1052#1086#1076#1077#1084' '#1074#1082#1083#1102#1095#1077#1085
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus2_2: TLabel
        Left = 5
        Top = 30
        Width = 158
        Height = 13
        Caption = #1057#1072#1084#1086#1077#1089#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1084#1086#1076#1077#1084#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus0_1: TLabel
        Left = 5
        Top = 45
        Width = 97
        Height = 13
        Caption = #1054#1096#1080#1073#1082#1072' '#1084#1086#1076#1077#1084#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object pnStatusAndErrors: TPanel
      Left = 1
      Top = 1
      Width = 1007
      Height = 15
      Align = alTop
      Caption = #1057#1090#1072#1090#1091#1089' '#1080' '#1086#1096#1080#1073#1082#1080
      Color = clSkyBlue
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
    end
    object gbResetCause: TGroupBox
      Left = 793
      Top = 16
      Width = 190
      Height = 143
      Align = alLeft
      Caption = #1055#1088#1080#1095#1080#1085#1072' '#1086#1073#1088#1099#1074#1072' '#1089#1086#1077#1076#1080#1085#1077#1085#1080#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      object lbStatusReset_0: TLabel
        Left = 5
        Top = 15
        Width = 127
        Height = 13
        Caption = #1042#1099#1082#1083#1102#1095#1077#1085#1080#1077' '#1087#1080#1090#1072#1085#1080#1103
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatusReset_1: TLabel
        Left = 5
        Top = 30
        Width = 92
        Height = 13
        Caption = #1042#1085#1077#1096#1085#1080#1081' '#1089#1073#1088#1086#1089
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatusReset_2: TLabel
        Left = 5
        Top = 45
        Width = 112
        Height = 13
        Caption = #1057#1085#1080#1078#1077#1085#1080#1077' '#1087#1080#1090#1072#1085#1080#1103
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatusReset_3: TLabel
        Left = 5
        Top = 60
        Width = 69
        Height = 13
        Caption = 'WDT '#1089#1073#1088#1086#1089
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatusReset_4: TLabel
        Left = 5
        Top = 75
        Width = 182
        Height = 13
        Caption = #1044#1083#1080#1090#1077#1083#1100#1085#1086#1077' '#1086#1090#1089#1091#1090#1089#1090#1074#1080#1077' '#1089#1074#1103#1079#1080
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatusReset_5: TLabel
        Left = 5
        Top = 90
        Width = 142
        Height = 13
        Caption = #1053#1077#1087#1088#1077#1076#1074#1080#1076#1077#1085#1085#1099#1081' '#1089#1073#1088#1086#1089
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label17: TLabel
        Left = 5
        Top = 105
        Width = 25
        Height = 13
        Caption = 'rsvd'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        Visible = False
      end
      object Label18: TLabel
        Left = 5
        Top = 120
        Width = 25
        Height = 13
        Caption = 'rsvd'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        Visible = False
      end
    end
    object gbStatus2: TGroupBox
      Left = 381
      Top = 16
      Width = 412
      Height = 143
      Align = alLeft
      Caption = #1055#1088#1086#1095#1080#1077' '#1091#1089#1090#1088#1086#1081#1089#1090#1074#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      object lbStatus2_0: TLabel
        Left = 5
        Top = 15
        Width = 80
        Height = 13
        Caption = 'GPS '#1074#1082#1083#1102#1095#1077#1085
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus2_3: TLabel
        Left = 5
        Top = 60
        Width = 203
        Height = 13
        Caption = #1053#1077#1082#1086#1088#1088#1077#1082#1090#1085#1099#1077' '#1076#1072#1085#1085#1099#1077' '#1074' EEPROM'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus2_4: TLabel
        Left = 5
        Top = 75
        Width = 176
        Height = 13
        Caption = #1054#1096#1080#1073#1082#1072' '#1075#1077#1085#1077#1088#1072#1090#1086#1088#1072' 19.2 '#1052#1043#1094
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus2_5: TLabel
        Left = 5
        Top = 90
        Width = 183
        Height = 13
        Caption = #1054#1096#1080#1073#1082#1072' '#1075#1077#1085#1077#1088#1072#1090#1086#1088#1072' 4.096 '#1052#1043#1094
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus2_6: TLabel
        Left = 5
        Top = 105
        Width = 102
        Height = 13
        Caption = #1054#1090#1089#1091#1090#1089#1090#1074#1091#1077#1090' PPS'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus2_7: TLabel
        Left = 5
        Top = 120
        Width = 134
        Height = 13
        Caption = #1054#1096#1080#1073#1082#1072' '#1090#1072#1081#1084#1077#1088#1072' TIM3'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbStatus0_2: TLabel
        Left = 5
        Top = 45
        Width = 113
        Height = 13
        Caption = #1054#1096#1080#1073#1082#1072' '#1074' '#1082#1086#1084#1072#1085#1076#1077
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Bevel1: TBevel
        Left = 215
        Top = 30
        Width = 5
        Height = 90
        Shape = bsLeftLine
      end
      object lbStatus0_0: TLabel
        Left = 220
        Top = 105
        Width = 78
        Height = 13
        Caption = #1053#1077#1090' '#1074#1088#1077#1084#1077#1085#1080
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        Visible = False
      end
      object lbRele1: TLabel
        Left = 220
        Top = 120
        Width = 95
        Height = 13
        Caption = #1052#1086#1076#1077#1084' '#1074#1082#1083#1102#1095#1077#1085
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        Visible = False
      end
      object lbRele4: TLabel
        Left = 220
        Top = 75
        Width = 137
        Height = 13
        Caption = #1057#1077#1083#1077#1082#1090#1086#1088' '#1085#1072' COM '#1087#1086#1088#1090
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        Visible = False
      end
      object lbRele5: TLabel
        Left = 220
        Top = 90
        Width = 118
        Height = 13
        Caption = #1057#1077#1083#1077#1082#1090#1086#1088' '#1085#1072' '#1084#1086#1076#1077#1084
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        Visible = False
      end
      object lbRele2: TLabel
        Left = 220
        Top = 15
        Width = 107
        Height = 13
        Caption = #1055#1077#1088#1077#1078#1080#1075' '#1074#1082#1083#1102#1095#1077#1085
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbRele3: TLabel
        Left = 220
        Top = 30
        Width = 123
        Height = 13
        Caption = #1040#1085#1072#1083#1086#1075#1086#1074#1086#1077' '#1087#1080#1090#1072#1085#1080#1077
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbRele6: TLabel
        Left = 220
        Top = 45
        Width = 95
        Height = 13
        Caption = #1055#1088#1086#1074#1086#1076#1085#1086#1081' USB'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbRele7: TLabel
        Left = 220
        Top = 60
        Width = 127
        Height = 13
        Caption = #1041#1077'c'#1087#1088#1086#1074#1086#1076#1085#1086#1081' WUSB'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbRele0: TLabel
        Left = 5
        Top = 30
        Width = 25
        Height = 13
        Caption = 'rsvd'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        Visible = False
      end
    end
    object gbAdc: TGroupBox
      Left = 983
      Top = 16
      Width = 190
      Height = 143
      Align = alLeft
      Caption = #1056#1072#1073#1086#1095#1080#1077' '#1040#1062#1055
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      object pnAdcNum: TPanel
        Left = 0
        Top = 15
        Width = 80
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1040#1062#1055
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
      end
      object Panel3: TPanel
        Left = 0
        Top = 55
        Width = 80
        Height = 25
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '2'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
      end
      object Panel6: TPanel
        Left = 0
        Top = 30
        Width = 80
        Height = 25
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '1'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
      end
      object Panel9: TPanel
        Left = 0
        Top = 80
        Width = 80
        Height = 25
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '3'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
      end
      object Panel11: TPanel
        Left = 0
        Top = 105
        Width = 80
        Height = 25
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = '4'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 4
      end
      object Panel13: TPanel
        Left = 80
        Top = 30
        Width = 80
        Height = 25
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 5
        object ltAdc1: TLight
          Left = 2
          Top = 2
          Width = 76
          Height = 21
          Align = alClient
          Brush.Color = clRed
          Shape = stRoundRect
          OnColor = clLime
          OffColor = clRed
        end
      end
      object Panel14: TPanel
        Left = 80
        Top = 55
        Width = 80
        Height = 25
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 6
        object ltAdc2: TLight
          Left = 2
          Top = 2
          Width = 76
          Height = 21
          Align = alClient
          Brush.Color = clRed
          Shape = stRoundRect
          OnColor = clLime
          OffColor = clRed
        end
      end
      object Panel15: TPanel
        Left = 80
        Top = 80
        Width = 80
        Height = 25
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 7
        object ltAdc3: TLight
          Left = 2
          Top = 2
          Width = 76
          Height = 21
          Align = alClient
          Brush.Color = clRed
          Shape = stRoundRect
          OnColor = clLime
          OffColor = clRed
        end
      end
      object Panel16: TPanel
        Left = 80
        Top = 105
        Width = 80
        Height = 25
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 8
        object ltAdc4: TLight
          Left = 2
          Top = 2
          Width = 76
          Height = 21
          Align = alClient
          Brush.Color = clRed
          Shape = stRoundRect
          OnColor = clLime
          OffColor = clRed
        end
      end
      object pnAdcStatus: TPanel
        Left = 80
        Top = 15
        Width = 80
        Height = 15
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #1057#1086#1089#1090#1086#1103#1085#1080#1077
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 9
      end
    end
  end
  object sdParamFile: TSaveDialog
    Filter = 'Param files|recparam.cfg'
    Options = [ofEnableSizing]
    Title = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1092#1072#1081#1083' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074
    Left = 840
  end
  object menuMain: TMainMenu
    Left = 880
    object MenuFile: TMenuItem
      Caption = #1060'&'#1072#1081#1083
      ShortCut = 16454
      object menuOpenLogs: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100' '#1092#1072#1081#1083#1099' '#1083#1086#1075#1086#1074
        OnClick = menuOpenLogsClick
      end
      object menuOpen: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100' '#1092#1072#1081#1083' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074
        OnClick = menuOpenClick
      end
      object menuSave: TMenuItem
        Caption = #1047#1072#1087#1080#1089#1072#1090#1100' '#1092#1072#1081#1083' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074
        Enabled = False
        OnClick = menuSaveClick
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object menu10Min: TMenuItem
        Caption = #1057#1086#1079#1076#1072#1090#1100' '#1092#1072#1081#1083' 10-'#1090#1080' '#1084#1080#1085#1091#1090#1085#1086#1081' '#1079#1072#1087#1080#1089#1080' '
        OnClick = menu10MinClick
      end
      object menu60Min: TMenuItem
        Caption = #1057#1086#1079#1076#1072#1090#1100' '#1092#1072#1081#1083' '#1095#1072#1089#1086#1074#1086#1081' '#1079#1072#1087#1080#1089#1080
        OnClick = menu60MinClick
      end
      object menu1Day: TMenuItem
        Caption = #1057#1086#1079#1076#1072#1090#1100' '#1092#1072#1081#1083' '#1089#1091#1090#1086#1095#1085#1086#1081' '#1079#1072#1087#1080#1089#1080
        OnClick = menu1DayClick
      end
      object menu1Week: TMenuItem
        Caption = #1057#1086#1079#1076#1072#1090#1100' '#1092#1072#1081#1083' '#1085#1077#1076#1077#1083#1100#1085#1086#1081' '#1079#1072#1087#1080#1089#1080
        OnClick = menu1WeekClick
      end
      object menu1Month: TMenuItem
        Caption = #1057#1086#1079#1076#1072#1090#1100' '#1092#1072#1081#1083' '#1084#1077#1089#1103#1095#1085#1086#1081' '#1079#1072#1087#1080#1089#1080
        OnClick = menu1MonthClick
      end
      object N7: TMenuItem
        Caption = '-'
      end
      object menuExit: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = menuExitClick
      end
    end
    object menuCtrl: TMenuItem
      Caption = #1059#1087#1088#1072#1074#1083'&'#1077#1085#1080#1077
      ShortCut = 16468
      object menuOperator: TMenuItem
        AutoCheck = True
        Caption = #1056#1077#1078#1080#1084' '#1086#1087#1077#1088#1072#1090#1086#1088#1072
        Checked = True
        GroupIndex = 10
        RadioItem = True
        OnClick = menuStandardClick
      end
      object menuAdjust: TMenuItem
        AutoCheck = True
        Caption = #1056#1077#1078#1080#1084' '#1085#1072#1083#1072#1076#1082#1080
        GroupIndex = 10
        RadioItem = True
        OnClick = menuAdvancedClick
      end
    end
    object menuLang: TMenuItem
      Caption = #1071#1079#1099#1082
      object menuRus: TMenuItem
        AutoCheck = True
        Caption = #1056#1091#1089#1089#1082#1080#1081
        Checked = True
        GroupIndex = 22
        RadioItem = True
        OnClick = menuRusClick
      end
      object N9: TMenuItem
        AutoCheck = True
        Caption = '-'
        GroupIndex = 22
        RadioItem = True
      end
      object menuEng: TMenuItem
        AutoCheck = True
        Caption = #1040#1085#1075#1083#1080#1081#1089#1082#1080#1081
        GroupIndex = 22
        RadioItem = True
        OnClick = menuEngClick
      end
    end
    object menuHelp: TMenuItem
      Caption = #1057#1087'&'#1088#1072#1074#1082#1072
      ShortCut = 16456
      object menuAbout: TMenuItem
        Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
        OnClick = menuAboutClick
      end
    end
  end
  object odParamFile: TOpenDialog
    DefaultExt = '*.cfg'
    Filter = 'Config files|*.cfg'
    InitialDir = 'D:'
    Left = 808
  end
  object timIdle: TTimer
    Interval = 100
    OnTimer = timIdleTimer
    Left = 776
  end
  object tmFind: TTimer
    Enabled = False
    OnTimer = tmFindTimer
    Left = 744
  end
  object imgList: TImageList
    Height = 24
    Width = 24
    Left = 984
    Bitmap = {
      494C010114001800040018001800FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      00000000000036000000280000006000000090000000010020000000000000D8
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000080C0
      800000A0000000A0000000000000000000000000000000000000000000000000
      00000000000000000000C0DCC00080C0800040A0200000800000C0DCC0000000
      00000000000000000000000000000000000000000000000000000000000080C0
      800000A0000000A0000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FF000000FF000000FF000000000000000000
      000000000000000000000000000000000000000000000000000080C0800000A0
      000040A0200040A02000C0DCC000000000000000000000000000000000000000
      0000000000000000000080C08000C0DCC00000000000000000000080000080C0
      600000000000000000000000000000000000000000000000000080C0800000A0
      000040A0200040A02000C0DCC000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000A0000040A0
      200040A0200040C0A00000A00000C0DCC0000000000000000000000000000000
      0000000000000000000040A02000008000000080000080C06000C0DCC0000080
      000080A06000000000000000000000000000000000000000000000A0000040A0
      200040A0200040C0A00000A00000C0DCC0000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000A0000040C0
      800040C0800040A0000040A0200040A0000040A04000C0DCC000000000000000
      0000000000000000000040A0200040A04000C0DCC0000000000000A000000000
      000080C0600000A000000000000000000000000000000000000000A0000040C0
      800040C0800040A0000040A0200040A0000040A04000C0DCC000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      8000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000080C0A00040C0
      800040A0200040A0200040A0000040A0600080C0A00000A00000000000000000
      0000000000000000000080C0A00080C060000080000040A0400040A0200040A0
      400000000000008000000000000000000000000000000000000080C0A00040C0
      800040A0200040A0200040A0000040A0600080C0A00000A00000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000800000000000000000000000
      0000000000000000000000008000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000080C0
      600000A0000040A0200040A0400080C0A00040A0200040A02000F0FBFF000000
      000000000000000000000000000000000000F0FBFF0000800000C0DCC0000080
      0000F0FBFF0080C06000000000000000000000000000000000000000000080C0
      600000A0000040A0200040A0400080C0A00040A0200040A02000F0FBFF000000
      000000000000000000000000000000000000F0FBFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000080C0800000A0000080C0C00040A0400040A0200040A02000F0FBFF000000
      000080C0A00000A00000F0FBFF000000000000000000C0DCC0000000000000A0
      000080C08000C0DCC000F0FBFF00000000000000000000000000000000000000
      000080C0800000A0000080C0C00040A0400040A0200040A02000F0FBFF000000
      000080C0A00000A00000F0FBFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000008000000000000000000000000000000000000000
      0000000000000000000000000000000000000000800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000A0000040A0200000A00000C0DCC000C0DCC00040C0
      800040A0200040A0200040A0200040A02000000000000000000000000000C0C0
      A000C0C0A00000000000F0FBFF00000000000000000000000000000000000000
      0000000000000000000000A0000040A0200000A00000C0DCC000C0DCC00040C0
      800040A0200040A0200040A0200040A020000000000000000000000000000000
      00000000000000000000F0FBFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      FF00000000000000000000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000080A0600000800000C0C0A0000000000000A0000040C0
      600080C0A00040A0200040A0200000A0000080C0800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000080A0600000800000C0C0A0000000000000A0000040C0
      600080C0A00040A0200040A0200000A0000080C0800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      FF00000000000000000000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000F0FBFF0000000000C0DCC00040A0200040A0
      000040C0600080C0A00040A0200000A00000C0DCC00000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000F0FBFF0000000000C0DCC00040A0200040A0
      000040C0600080C0A00040A0200000A00000C0DCC00000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000800000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000008000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      0000FF0000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000040A0200040A0200040A0200040A0
      200040A0200040A0000080C0A000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000040A0200040A0200040A0200040A0
      200040A0200040A0000080C0A000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000FF000000FF000000FF00000000000000000000000000FF000000FF00
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000A0000040A0200040A0200040A0
      200040A0200000A0000000000000C0DCC00040A02000C0DCC000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000A0000040A0200040A0200040A0
      200040A0200000A0000000000000C0DCC00040A02000C0DCC000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000FF000000FF000000FF00000000000000000000000000FF000000FF00
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000040A0400040A0000040A0200040A0
      200000A0000080A06000C0DCC00000A0000040A0200000A00000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000040A0400040A0000040A0200040A0
      200000A0000080A06000C0DCC00000A0000040A0200000A00000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000008000000000000000000000000000000000000000
      0000000000000000000000000000000000000000800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF000000FF000000FF0000000000000000000000
      0000FF0000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000A0000040A0
      6000000000000000000040A0200040A0200040A0200040C0A00000A00000C0DC
      C000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000A0000040A0
      6000000000000000000040A0200040A0200040A0200040C0A00000A00000C0DC
      C000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF000000FF000000
      000000000000000000000000FF000000FF000000FF0000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000C0DCC00040A0200040A0200040C0A00040C0800040A0200000A0
      0000C0DCC0000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000C0DCC00040A0200040A0200040C0A00040C0800040A0200000A0
      0000C0DCC0000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000800000000000000000000000
      0000000000000000000000008000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF000000FF000000
      000000000000000000000000FF000000FF000000FF0000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000A0000040C0A00040C0800040A0000040A0200040A0
      400040C08000C0DCC00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000A0000040C0A00040C0800040A0000040A0200040A0
      400040C08000C0DCC00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF000000FF000000
      000000000000000000000000FF000000FF000000FF0000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F0FB
      FF000000000000000000F0FBFF00000000000000000000000000000000000000
      0000F0FBFF000000000080C0A00040C0600040A0000040A0200040A0200080C0
      A00040A0400000A000000000000000000000000000000000000000000000F0FB
      FF000000000000000000F0FBFF00000000000000000000000000000000000000
      0000F0FBFF000000000080C0A00040C0600040A0000040A0200040A0200080C0
      A00040A0400000A0000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF00000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000F0FBFF000000
      0000C0A0E0004020C0004040C00080A0E000000000000000000080A0E0008080
      E00000000000C0A0E000000000000000000040A0400000A0000040C0600040A0
      000040A0200000A0000000000000000000000000000000000000F0FBFF000000
      0000C0A0E0004020C0004040C00080A0E000000000000000000080A0E0008080
      E00000000000C0A0E000000000000000000040A0400000A0000040C0600040A0
      000040A0200000A0000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF00000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000F0FBFF00000000008080
      E0004020C0008080E0004060C0000020C0004020C0004040C00000000000C0A0
      E0004020C0000020C00000000000000000000000000080C0800040A0000040A0
      200000A0000080C06000000000000000000000000000F0FBFF00000000008080
      E0004020C0008080E0004060C0000020C0004020C0004040C00000000000C0A0
      E0004020C0000020C00000000000000000000000000080C0800040A0000040A0
      200000A0000080C0600000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F0FBFF00C0A0E0004040C000C0A0E000000000000020C000C0C0C0000020
      C000F0FBFF00F0FBFF000000000000000000000000000000000000A0000000A0
      000040A040000000000000000000000000000000000000000000000000000000
      0000F0FBFF00C0A0E0004040C000C0A0E000000000000020C000C0C0C0000020
      C000F0FBFF00F0FBFF000000000000000000000000000000000000A0000000A0
      000040A040000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FF000000FF000000FF000000000000000000
      0000000000000000000000000000000000000000000000000000F0FBFF0080A0
      E000F0FBFF0000000000F0FBFF00C0A0E000C0A0E0000000000000000000F0FB
      FF00C0A0E000C0DCC00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000F0FBFF0080A0
      E000F0FBFF0000000000F0FBFF00C0A0E000C0A0E0000000000000000000F0FB
      FF00C0A0E000C0DCC00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FF000000FF000000FF000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FF000000FF000000FF000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF00000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FF00000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FF000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FF00000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FF000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FFFF
      FF00A4A0A000A4A0A000FFFFFF00A4A0A000A4A0A000A4A0A000FFFFFF00FFFF
      FF00A4A0A000A4A0A000A4A0A000FFFFFF00A4A0A000A4A0A000A4A0A000FFFF
      FF00FFFFFF00FF00000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FF000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00000000000000000000000000FFFFFF000000000000000000000000000000
      000000000000FFFFFF0000000000000000000000000000000000000000000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FF000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00000000000000000000000000FFFFFF000000000000000000000000000000
      000000000000FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FFFF
      FF00A4A0A000A4A0A000FFFFFF00A4A0A000A4A0A000A4A0A000FFFFFF00FFFF
      FF00A4A0A000A4A0A000A4A0A000FFFFFF00A4A0A000A4A0A000A4A0A000FFFF
      FF00FFFFFF00FF000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      FF00000000000000000000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FF000000000000000000000000000000FFFFFF00FFFFFF000000
      00000000000000000000FFFFFF0000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000000000000000000000000000000000000000000000000000
      00000000FF000000FF0000000000000000000000000000000000FFFFFF00FFFF
      FF0000000000C0C0C000C0C0C000000000000000000000000000FFFFFF000000
      000000000000FFFFFF0000000000000000000000000000000000000000000000
      FF00000000000000000000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FF000000000000000000000000000000FFFFFF00FFFFFF000000
      00000000000000000000FFFFFF0000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000000000000000000000000000000000000000000000000000
      00000000FF000000FF0000000000000000000000000000000000FFFFFF00FFFF
      FF0000000000C0C0C000C0C0C000000000000000000000000000FFFFFF000000
      000000000000FFFFFF0000000000000000000000000000000000000000000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      0000FF0000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FFFF
      FF00C0A06000C0A06000C0A06000C0A06000C0A06000C0A06000C0A06000C0A0
      6000C0A06000C0A06000C0A06000C0A06000C0A06000C0A06000C0A06000FFFF
      FF00FFFFFF00FF000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000FF000000FF000000FF00000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      00000000FF000000FF000000FF00000000000000000000000000FF000000FF00
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FF000000000000000000000000000000FFFFFF00FFFFFF000000
      00000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF0000000000000000000000FF000000FF000000FF00000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF0000000000FFFFFF00FFFF
      FF00000000000000000000000000FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000FF000000FF000000FF00000000000000000000000000FF000000FF00
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FF000000000000000000000000000000FFFFFF00FFFFFF000000
      00000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF0000000000000000000000FF000000FF000000FF00000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF0000000000FFFFFF00FFFF
      FF00000000000000000000000000FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF000000FF000000FF0000000000000000000000
      0000FF0000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00A4A0A000A4A0A000A4A0A000FFFFFF00FFFF
      FF00A4A0A000A4A0A000A4A0A000FFFFFF00A4A0A000A4A0A000A4A0A000FFFF
      FF00FFFFFF00FF000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF0000000000000000000000FF000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF00000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000FFFFFF00FFFF
      FF00FFFFFF000000000000000000000000000000FF000000FF000000FF000000
      000000000000000000000000FF000000FF000000FF0000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FF000000000000000000000000000000FFFFFF00FFFFFF000000
      00000000000000000000FFFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF0000000000C0C0C000C0C0C000FFFFFF000000000000000000FFFFFF000000
      0000000000000000000000000000000000000000FF000000FF000000FF000000
      000000000000000000000000FF000000FF000000FF0000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FF000000000000000000000000000000FFFFFF00FFFFFF000000
      00000000000000000000FFFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF0000000000C0C0C000C0C0C000FFFFFF000000000000000000FFFFFF000000
      0000000000000000000000000000000000000000FF000000FF000000FF000000
      000000000000000000000000FF000000FF000000FF0000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FF000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF000000000000000000FFFFFF00FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF00000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF00000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000000000000000000000000000FFFFFF00FFFFFF000000
      0000C0C0C000C0C0C000FFFFFF000000000000000000FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF00000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000000000000000000000000000FFFFFF00FFFFFF000000
      0000C0C0C000C0C0C000FFFFFF000000000000000000FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FF000000FF000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000FF000000FF000000FF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FF000000FF000000FF000000000000000000
      00000000000000000000000000000000000000000000F0CAA600F0CAA600FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000F0CAA60000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FF000000FF000000FF000000000000000000
      00000000000000000000000000000000000000000000F0CAA600F0CAA600FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000F0CAA60000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008080
      E0000020C0000020C0008060C000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000004060C0000020
      C0000000FF004020E0000020C0004060C0000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000008060C0004020E0000020
      E0000020C0004020E0000000FF000020C0008080E00000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000F0FBFF000020C0004040E0004020
      E0000020E0000020C0004020E0004020E0000020C000C0A0E000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C0C0C000C0C0
      C000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C0C0C000C0C0
      C000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000008060E0004060E0004020E0004020
      E0004020E0000020E0000020C0004020E0004020E0000020C000C0A0E0000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C0C0C000C0C0
      C000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C0C0C000C0C0
      C000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000020C0008080E0004020E0004020
      E0004020E0004040E0000020E0000020C0004020E0004020E0000020C000F0FB
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000FF
      FF0000000000000000000000000000FFFF0000FFFF0000000000000000000000
      00000000000000FFFF0000FFFF0000000000000000000000000000FFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      0000000000000000000000000000000000004020E0008080E0004040E0004040
      E0004040E0004040E0004040E0000020C0000020C0004040E0000020E000C0A0
      E000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF000000000000FFFF0000FF
      FF000000000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00C0C0C00000000000000000004020E0008080E0004040E0004040
      E0004040E0004040E0004040E0004040E0000020C0000020C0000020C0000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF000000000000FFFF0000FF
      FF000000000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00C0C0C00000000000000000004020E0008080E0004040E0004040
      E0004040E0004040E0004040E0004040E0004020E0004040E000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000000000FFFFFF00FFFF
      FF000000000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000020E000C0A0E0004040E0004040
      E0004040E0004040E0004040E0000020E0008080E00000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00808080008080
      8000FFFFFF000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000FF
      FF0000FFFF0000FFFF0000FFFF000000000000000000FFFFFF00808080008080
      8000FFFFFF00000000000000000000FFFF0000FFFF0000FFFF0000FFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFF
      FF00FFFFFF00FFFFFF0000000000000000008060E0008080E0004060E0004040
      E0004040E0004040E0004040E0004040E0000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00808080008080
      8000FFFFFF000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000FF
      FF0000FFFF0000FFFF0000FFFF000000000000000000FFFFFF00808080008080
      8000FFFFFF00000000000000000000FFFF0000FFFF0000FFFF0000FFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFF
      FF00FFFFFF00FFFFFF000000000000000000C0A0E0004040E00080A0E0004040
      E0004060E0004060E0004040E0000020E0000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00808080008080
      8000FFFFFF00FFFFFF00FFFFFF00000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000FF
      FF0000FFFF0000FFFF0000000000FFFFFF00FFFFFF0000FFFF00808080008080
      800000FFFF00FFFFFF00FFFFFF000000000000FFFF0000FFFF0000FFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF000000000000000000000000000020E000C0A0E0004060
      E0004060E0004060E0004060E0004020E0008060E00000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00808080008080
      8000FFFFFF00FFFFFF00FFFFFF00000000000000000000000000000000000000
      00000000000000000000000000000000000000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF000000000000FFFF0000FFFF00FFFFFF00808080008080
      8000FFFFFF0000FFFF0000FFFF000000000000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF00000000000000000000000000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF00000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00000000000000000000000000000000008080E0004040E00080C0
      E0004060E0004060E0004060E0004060E0000020E000C0A0E000000000000000
      00000000000000000000000000000000000080A0E0004020E0008080E0000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00808080008080
      8000FFFFFF00FFFFFF00FFFFFF00000000000000000000000000000000000000
      00000000000000000000000000000000000000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF000000000000FFFF0000FFFF00FFFFFF00808080008080
      8000FFFFFF0000FFFF0000FFFF000000000000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF00000000000000000000000000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF00000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF0000000000000000000000000000000000000000000000FF0080A0
      E0008080E0004060E0004060E0004060E0004060E0000020E000C0A0E0000000
      00000000000000000000000000008060E0000020E0004060E0000020E0008060
      E000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000FF
      FF0000FFFF0000FFFF0000000000FFFFFF00FFFFFF0000FFFF00FFFFFF00FFFF
      FF0000FFFF00FFFFFF00FFFFFF000000000000FFFF0000FFFF0000FFFF000000
      000000000000000000000000000000000000000000000000000000000000FF00
      0000FF000000FF000000FF000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000F0FBFF000020
      E000C0A0E0004060E0004060E0004060E0004060E0004060E0000020E000C0A0
      E00000000000000000008060E0004040E0000020C0004040E0004060E0000020
      E0008060E0000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000FF
      FF0000FFFF0000FFFF0000FFFF000000000000000000FFFFFF0000FFFF0000FF
      FF00FFFFFF00000000000000000000FFFF0000FFFF0000FFFF0000FFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FF000000FF00000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008080
      E0004040E000C0A0E0004060E0004060E0004060E0004060E0004060E0000020
      E00080A0E0008060E0000020E0004060E0004060E0000020C0000020C0004080
      E0004020E0008060E00000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000FF
      FF0000FFFF0000FFFF0000FFFF000000000000000000FFFFFF0000FFFF0000FF
      FF00FFFFFF00000000000000000000FFFF0000FFFF0000FFFF0000FFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FF000000FF00000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00004020E0004040E000C0A0E0004060E0004060E0004060E0004060E0004060
      E0004040E0004040E0004060E0004060E0004060E0004060E0000020C0000020
      C0004080E0004020E0008060E000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000000000000000000000
      00000000000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000008080800000FFFF0000FF
      FF00808080000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000004020E0004060E000C0A0E0004060E0004060E0004060E0004060
      E0004080E0004060E0004060E0004060E0004060E0004060E0004060E0000020
      C0000020C0004080E0004020E0008060E0000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF00000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF0000000000000000000000000000FFFF0000FFFF0000FF
      FF0000FFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000004020E0004040E000C0A0E0004080E0004060E0004080
      E0004080E0004060E0004060E0004060E0004060E0004060E0004060E0004060
      E0000020C0000020C0004080E0004020E0000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF00000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF0000000000000000000000000000FFFF0000FFFF0000FF
      FF0000FFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000004040E0004040E000C0A0E00080A0E0004080
      E0004080E0004080E0004080E0004080E0004080E0004080E0004060E0004060
      E0004080E0000020C0000020C0000000FF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000FF
      FF0000000000000000000000000000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000000000000000000000000000FFFF000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF000000000000000000000000008080800000FFFF0000FF
      FF00808080000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000080A0E0000000FF008080E000C0A0
      E00080A0E0004080E0004060E0004080E0004080E0004060E0004060E0004080
      E0004080E0008080E0000000FF00C0A0E0000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000FFFF0000FF
      FF00000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000008060E0004020
      E0008080E000C0A0E000C0A0E00080C0E00080A0E00080A0E00080A0E00080A0
      E0008060E0000000FF00F0FBFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000FFFF0000FF
      FF00000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000C0A0E0004040E0000000FF004040E0004040E0004040E0004020E0004040
      E0008080E0000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000FFFF0000FF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000020A0004060C00000A0E00000A0E00000A0E00000A0E0000060E000C080
      6000C0802000C0802000C0802000C0802000C0604000C0DCC00040C0600040C0
      600040C0600040C0600040804000FFFFFF000000000000000000000000000000
      0000000000000A07AA000A07AA00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000006262B8000502A0000301A5000301A5000301A5000301
      A5000301A5000301A5000301A5000301A5000300A1006362B800000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000C0DCC00080A060004080200040A0400040A0400040A040004080400040A0
      6000C0C0A0000000000000000000000000000020E0000020E0000020E0000000
      00000020C0000020C00000A0E00000A0E00000A0E00000A0E0000040C0008060
      6000C0A02000C0802000C0802000C0A02000C04020008080200040C0600040C0
      600040C0600040C0600040602000408040000000000000000000000000000000
      0000000000000E0BAB00100DB7000906A7000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000005958B8001513BB001915F8000D0BF3000E0CF2000E0BF2000E0B
      F2000E0BF2000E0AF2000E0AF2000E08F3000E09F6000702BA005958B8000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000080C0800080A0
      600080E0800040E0600040E0800040E0800040E0800040E0800040E0800040E0
      600040C0400040802000C0DCC000000000000020E0000020E0000020E0000020
      E0000020C0000020C00000A0E00000A0E00000A0E00000A0E0000060C0008060
      6000C0A02000C0A02000C0A02000C0A02000C06020008080400040C0600040C0
      600040C0600040C0600040602000406020000000000000000000000000000000
      000000000000AAA9E1001713C700130FD1000906A40000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00005958BB001614BD001918F5000E0DEE000F0DED000F0DED000F0DED000E0D
      ED000E0CED000E0CED000E0BED000E0BED000D0BEE000E0CF4000603BC005A58
      BC00000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C0C0A00040A0400080E0A00040E0
      800040E0600040E0600040E0600040E0600040E0600040E0600040E0600040E0
      600040E0800040E0600040802000F0FBFF000020E0000020E0000020E0000020
      E0000020E0000020E00000C0E00000A0E00000A0E00000C0E0000060C0008060
      6000C0A02000C0A02000C0A02000C0A02000C06020008080400040C0600040C0
      600040C0600040C0600040602000406020000000000000000000000000000000
      000000000000000000000F0CA6002C25F4000E0ACD000906A300000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000005958
      BF001714C2001A1CF6000F11EF001012EE001011EE001010EE001010EE000F0F
      EE000F0FEE000F0FED000F0EED000F0EED000F0DED000F0DEE00100EF3000805
      BE005A59BF000000000000000000000000000000000000000000000000000000
      000000000000000000000000000080A0600080C0800080E0A00040E0600040E0
      600040E0600040E0600040E0600040E0600040E0600040E0600040E0600040E0
      600040E0600040A0400040A0400040A040004080E0004080E0004080E0004060
      E0000020E0000020E00000C0E00000A0E00000A0E00000C0E0000060E0008060
      8000C0A04000C0A04000C0A04000C0A04000C06020008080400040C0600040C0
      600040C0600040C0600040602000406020000000000000000000000000000000
      00000000000000000000AAA9E1001915C100251FFF00150EE3000806A200E4E4
      F600000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000005B58C3001816
      C4001C21F5001114EF001215EE001215EE001214EE001113EE001113EE001113
      EE001112EE001112EE001012EE001012EE001011EE001010EE001010EF001010
      F4000906C2005B59C30000000000000000000000000000000000000000000000
      0000000000000000000040A0400080E0A00040E0800040E0600040E0600040E0
      600040E0600040E0600040E0600040E0600040E0600040E0600040E0600040E0
      600040A0400040A0400040E0800040C0600080A0E00080A0E00080A0E00080A0
      E0004020E0000020E00080E0E00040E0E00040C0E00040C0E0000060E0008080
      8000C0A04000C0A04000C0A04000C0A04000C060200080A0400040C0600040C0
      600040C0600040C0600040602000406020000000000000000000000000000000
      00000000000000000000000000000E0CA500322CED001A14FA00160FE3000806
      A200E6E6F6000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000005B58C8001917C7001B23
      F5001217EF001318EE001218EE001217EE001217EE001216EE001216EE001216
      EE001215EE001215EE001215EE001215EE001214EE001113EE001113EE001113
      EF001213F3000A07C5005B59C800000000000000000000000000000000000000
      00000000000040A04000C0DCC00040E0800040E0800040E0800040E0800040E0
      800040E0800040E0600040E0600040E0600040E0600040E0600040E0800040A0
      400040A0400040E0800040E0800080C0800080A0E00080A0E00080A0E00080A0
      E0004020E0000020E00040E0E00040E0E00040E0E00080E0E0004080E0008080
      A000C0C04000C0A04000C0A04000C0A04000C060200080A0400040C0600040C0
      600040C0600040C0600040602000406020000000000000000000000000000000
      0000000000000000000000000000AAA9E1001B19C1002C25FA001A14F800160F
      E2000806A100E6E6F60000000000000000000000000000000000000000000000
      0000000000000000000000000000000000006563CE001918CB001E29F400131C
      EF00141CEE00131CEE00131BEE00131BEE00131AEE00131AEE001319EE001319
      EE001318EE001318EE001218EE001217EE001217EE001216EE001216EE001216
      EE001215EF001317F3000B09C7006664CE000000000000000000000000000000
      000040A0400080E0A00040E0800040E0800040E0800040E0800040E0800040E0
      800040C0600080E0A00080E0C00040E0600040E0600040E0800040A0400040C0
      400040E0800040E0800080C080000000000080A0E00080A0E00080A0E00080A0
      E0004060E0004040E00040E0E00040E0E00040E0E00040E0E0004080E0008080
      A000F0CAA600F0CAA600C0A04000C0C04000C060200080A0400040C0600040C0
      600040C0600040C0600040602000408020000000000000000000000000000000
      0000000000000000000000000000000000000602A6004A44EF001913F5001C16
      F7001914F1000A08AE00CECEEF00000000000000000000000000000000000000
      000000000000000000000000000000000000100CC2003344F800111EF1000F1C
      F1000E1BF100131FF1001520F0001520F000141FF200121DF100141FF000141D
      EF00141CF0000E18F0000C15F0001118F000131AEF00121AF0001118F0001219
      F1001318EF001318EF00131AF4000906C10000000000000000000000000080C0
      800080E0A00040E0A00040E0800040E0800040E0800040E0800040E0600040A0
      4000C0C0A00080C0800080C08000C0DCC00040E0600040A0400040C0600040E0
      A00040E0A00080C080000000000000000000FFFFFF00C0A0E00080C0E00080C0
      E000C0A0E00080C0E00040E0E00040E0E00040E0E00040E0E0004080E0008080
      A000F0CAA600F0CAA600F0CAA600C0C08000C060200080A0400040C0600040C0
      600040C0600040C0600040602000408020000000000000000000000000000000
      00000000000000000000000000006E6AD2001712C100302FF6001D1AF4001E1C
      F4001F1CF8001816E8002D2ABB00000000000000000000000000000000000000
      0000000000000000000000000000000000001311C9003040F3000F11C800615F
      D100615FD1000A0CC700101CEE000E17E2001C1CC1002B2CC9000D15E1001421
      F3000000CA004B4AD1004B4AD1001515C7000910E3001015D7002B2BCA001110
      BA00121BF100131BEE00141CF1000A09C6000000000000000000C0DCC00080C0
      600080E0C00040E0800040E0800040E0800040E0800040E0800040804000C0DC
      C000000000000000000080C0800080E0A00080E0A00040C0600040E0A00040C0
      800080C08000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00F0FBFF0040E0E00040E0E00040E0E00040E0E0004080E0008080
      C000F0CAA600F0CAA600F0CAA600F0CAA600C080400080A0400040C0600040C0
      600040C0600040C0600040602000408020000000000000000000000000000000
      0000000000000000000000000000302DC3005C5BF5003134F9001C1FF4001F22
      F5001C1DEF000D0AB80000000000000000000000000000000000000000000000
      0000000000000000000000000000000000001412CA002939EC00AFAAE6000000
      00000000000000000000292AD100030CDF00D5D3EF00000000000008DE000006
      DA00EBE8F200000000000000000000000000000000002B34E100000000002B2B
      CA000E1BF3001520F0001621F2000A09C900000000000000000040A04000C0DC
      C00040E0800040E0800040E0800040E0800040E0800040A04000C0DCC0000000
      000000000000000000000000000080C0800080E0A00080E0E00040E0800080C0
      800000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00F0FBFF0040E0E00040E0E00040E0E00040E0E0004080E00080A0
      C000F0CAA600F0CAA600F0CAA600F0CAA600C080400080A0600040C0600040C0
      600040C0600040C0600040802000408020000000000000000000000000000000
      0000000000000000000000000000BCBBED000B06BF006F78FC001F24F4002125
      F5001D21EE000E08BD0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000001411CE00354DF6002E2BD000191C
      D9000C0BCC00000000007871DC00000CE300CCC8F000000000000007E2004E4B
      D900000000008987E6000000CB008987E600000000000F0BC900000000002B2B
      CA000000D6000B18EA001624F3000B09CE000000000080C0A00080E0A00040E0
      A00040E0800040E0800040E0800040E0800040A04000C0DCC000000000000000
      000000000000000000000000000000000000C0DCC00040A0600080C0A0000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00F0FBFF0040E0E00040E0E00040E0E00040E0E0004080E0008080
      C000F0CAA600F0CAA600F0CAA600F0CAA600C0804000C0C0600080E0A00040C0
      600040C0600040C0600040802000408020000000000000000000000000000000
      000000000000000000000000000000000000AEACEB001712CD006B78FB002833
      F5002D37F6002B33F3000F09C300000000000000000000000000000000000000
      000000000000000000000000000000000000120FD1003850F6000816E8003531
      DA0000000000000000006662E200020EE600CDC8F000000000000007E4007870
      E300000000000D11DC000D21F3006F67E100000000006660E200000000000000
      000000000000000000000A17EB000B08D0000000000040A0400080E0C00040E0
      800040E0800040E0800040E0800040C0600080C0800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0080E0E00040E0E00040E0E00040E0E00000FFFF0080C0
      C000F0CAA600F0CAA600F0CAA600F0CAA600C0A04000C0C0600080E0A00080E0
      A00040C0600040C0600040802000408040000000000000000000000000000000
      000000000000000000000000000000000000000000005F5BD9004C4AE1008A99
      FD006071F8006576F9005B60EF00130EC8000000000000000000000000000000
      0000000000000000000000000000000000003C38DE004B67F6003D38E1000000
      0000000000008F88EC000611E4000816E900CDC8F30000000000000AE8007973
      E800000000000106DD001029F2007471E900000000006761E60000000000766F
      ED00766FED00000000002A2DE400201FDB00C0DCC00080E0A00040E0A00040E0
      800040E0800040E0800040E0800040A040000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0CAA600F0CAA600F0CAA600F0CAA600C0A04000C0C0600080E0A00080E0
      A00080E0A00040C0600040802000408040000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000433FD7007477
      ED006D83F9006176F700657AF9005B66F0002A26D00000000000000000000000
      0000000000000000000000000000000000004641E3006B84F800A59DF0000000
      00000E0BE200070BE4000205E2000000E000C8C5F600000000000000DF00463D
      E70000000000625DEC000000E400CDCAF700000000002219E200000000003B3A
      E8003B3AE800000000006C6EF0003937E10080C08000C0DCC00040E0800040E0
      800040E0800040E0800040E0800080C080000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F0CAA600F0CAA600F0CAA600F0CAA600C0A04000C0C0600080E0C00080E0
      A00080E0A00080E0A00040802000408040000000000000000000000000000000
      00000000000000000000000000000000000000000000000000004540DA00514F
      E4007F94FB00647AF700657CF7006981F9004F56EB004A45DB00000000000000
      0000000000000000000000000000000000004541E5006F88F900837BF0000000
      0000F8F8FD0000000000938EF30000000000000000000000000000000000A09B
      F300FBFBFF00000000000000000000000000000000005B65F00000000000F5F7
      FD0000000000000000003E44F0003838E40040A0600080E0E00040E0800040E0
      800040E0800040E0800040E0800040A0400080C0A00000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F0CAA600F0CAA600F0CAA600F0CAA600C0A04000C0C0800080E0C00080E0
      A00080E0A00080E0C00040A04000408040000000000000000000000000000000
      000000000000000000000000000000000000E2E2FA00150CD4007F85F2007992
      FC00667FF800687FF800687FF8006B85F9006371F2004F4ADE00000000000000
      0000000000000000000000000000000000004643E700758FF9003D51F1008582
      F500D5D0FB00A39BF7005E55F100A69EF700A199F600A199F600A69EF7006259
      F1003942EF00A49BF600D6D1FB009590F7003641F1005963F300A79EF700A39B
      F700A79EF700494AF1004B62F4003A38E60080C0800080E0C00040E0800040E0
      800040E0800040E0800040E0800040E0800040C0600040A06000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F0CAA600F0CAA600F0CAA600F0CAA600C0A04000C0C0800080E0C00080E0
      A00080E0A00080E0C00040A04000408040000000000000000000000000000000
      0000000000000000000000000000000000003F39DE008286F2007691FC006A83
      F8006C84F8006B84F8006C86F9005F6DF3002921DA0000000000000000000000
      000000000000000000000000000000000000403DE8008EA7F900546FF400506E
      F4004D6BF3004E6CF4004F6FF4004C6DF4004C6AF4004C6AF4004B6AF400506D
      F400516EF4004B69F4004863F3004C66F400506BF4004F68F4004B65F4004A64
      F4004A64F4004F69F400536FF6003936E70080C0800080E0C00040E0800040E0
      800040E0800040E0800040E0800040E0A00040A0400040A0400040C060000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F0CAA600F0CAA600F0CAA600F0CAA600F0CAA600C0C0800080E0C00080E0
      A00080E0A00080E0C00040A0400040A040000000000000000000000000000000
      000000000000000000000000000000000000F7F7FE00170FDA0097AAF9006F8A
      FA00708AF9006F8AF900708BFA006D82F600221ADD00ECEBFC00000000000000
      000000000000000000000000000000000000817CF0005154EE0090A8F9005572
      F4005672F4005772F4005772F4005772F4005571F4005571F4005571F4005571
      F4005571F4005570F4005371F4005371F400536EF400536EF400526EF400526D
      F400526EF4005573F5003F42EC00837EF00080C0800080E0C00040E0800040E0
      A00040E0800040E0800040E0A00040A0400040A0400040E0800040C06000C0DC
      C000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00F0FBFF00FFFFFF00FFFFFF00FFFFFF00C0DCC00080E0C00080E0
      C00080E0C00080E0C00040A0400040A040000000000000000000000000000000
      00000000000000000000000000000000000000000000C1BFF600332AE4008BA5
      FB00728FF900738FF900738EF9007592FA007387F600160DDB00000000000000
      000000000000000000000000000000000000000000007974F0005355EF0094AA
      F9005975F4005875F4005976F4005975F4005975F4005875F4005873F4005873
      F4005773F4005772F4005772F4005772F4005571F4005571F4005571F4005572
      F4005877F5004042EE007A75F1000000000040C0600080E0E00040E0A00040E0
      A00040E0A00040E0A00040C0800040A0400040E0800040E0A00040C06000F0FB
      FF00000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C0DCC00080E0C00080E0
      C00080E0C00080E0C00040A0400040A040000000000000000000000000000000
      00000000000000000000000000000000000000000000000000008784EE005A59
      EC0080A0FB007694F9007692F9007692F9007998FA006776F3002721E0000000
      00000000000000000000000000000000000000000000000000007974F3005555
      F00095ACF8005B77F4005A78F4005B79F4005A79F4005A77F4005A77F4005A77
      F4005976F4005976F4005976F4005975F4005975F4005875F4005974F4005B79
      F5004143EF007B76F300000000000000000080E0A000C0DCC00040E0A00040E0
      A00040E0A00040C0800040A0400040E0800040E0A00040E08000C0DCC0000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C0DCC00080E0C00080E0
      C00080E0C00080E0C00040A0400040A040000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000003C35
      E5007078F2007D9CFA007A97F9007B98F900809FFA007186F700251CE3000000
      0000000000000000000000000000000000000000000000000000000000007974
      F3005555F10096B0F9005C7AF6005C7AF4005D7AF4005D7AF4005D7AF4005D7A
      F4005B79F4005B79F4005B79F4005B79F4005A79F4005A78F4005D7EF5004145
      F0007B75F300000000000000000000000000F0FBFF0080C0800080E0E00040E0
      A00040C0800040A0400040E0800040E0A00040E08000C0DCC000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C0DCC00080E0C00080E0
      C00080E0C00080E0C00040A0600040A040000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000150CE2008A9FF800809FFA0086A6FA00626BF2001F17E300000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007974F5005656F20099B1F9005F7CF6005E7CF6005D7AF6005D7AF6005D7A
      F6005D7AF6005C79F6005C79F6005B79F3005B79F4006181F5004245F0007B75
      F500000000000000000000000000000000000000000080E0A00080E0C00080E0
      C00040A0400040E0800040E0A00040E0800080E0A00000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C0DCC00080E0C00080E0
      C00080E0C00080E0C00040A0600040A040000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000D6D5FA00291EE8008FAEFB004F4EEE003D35E90000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000007974F5005758F3009AB3F900809CF900819DF900819DF900819D
      F900819DF900829CF900829CF900819CF90084A1F9004146F1007B76F5000000
      000000000000000000000000000000000000000000000000000080E0800080E0
      A00080E0C00040E0A00040E0800080E080000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0080E0E00080E0
      C00080E0C00080E0C00080E0C00040C080000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000A5A2F400281FE600827EF0000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000827EF600443FF1004946F2004946F2004946F2004946
      F2004946F2004946F2004946F2004A47F2004640F100837EF600000000000000
      00000000000000000000000000000000000000000000000000000000000080E0
      A00040E0800080E0A00080E0A000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000080604000C0A02000C0A06000F0CAA6000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000C0A08000C0804000C0400000C0400000C060
      0000C0400000C0600000C0804000F0CAA6000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000F0FBFF00C0DCC000C0DC
      C000C0DCC000C0DCC000F0FBFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000F0CAA600C0A08000C0604000C0602000C060
      2000C0602000C0602000C0604000C0A08000F0CAA60000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000C0604000C0A02000C0A02000C0A02000C0A02000C0A02000C0A06000F0CA
      A600000000000000000000000000000000000000000000000000000000000000
      000000000000C0806000C0400000C0600000C0800000C0A00000C0A00000C0A0
      0000C0A00000C0A00000C0802000C0802000C0602000C0A08000000000000000
      00000000000000000000F0CAA600C08020000000000000000000000000000000
      0000000000000000000000000000C0C0C000A4A0A0008080E000C0A0E000C0A0
      E000C0A0E000C0A0E0008080E000A4A0A000C0C0C00000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000C0DCC000C0602000C0802000C0A02000C0A02000C0800000C080
      0000C0800000C0800000C0800000C0802000C0802000C0602000C0DCC0000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000F0CAA600C0A080008080
      A00080402000C0A02000C0A02000C0A02000C0A02000C0A02000C0A02000C0A0
      2000C0A02000C0A02000C0C06000C0A08000000000000000000000000000F0FB
      FF00C0400000C0600000C0A00000C0A00000C0A00000C0A00000C0A00000C0A0
      0000C0A00000C0A02000C0A02000C0A02000C0A04000C0802000C08020000000
      000000000000C0A06000C0802000C0A020000000000000000000000000000000
      000000000000C0C0C0008060C0004060E00080A0E000C0A0E000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00C0A0E00080A0E0004060E0008060C000C0C0C0000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000C0A08000C0802000C0A02000C0A02000C0A02000C0C04000C0C06000F0CA
      A600F0CAA600C0C06000C0C04000C0800000C0802000C0A02000C0602000C0A0
      8000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0804000804020000000
      000080400000C0A02000C0A02000C0A02000C0A02000C0A02000C0A02000C0A0
      2000C0A02000C0A02000C0A02000C06020000000000000000000F0FBFF00C040
      0000C0800000C0A00000C0A00000C0A00000C0A00000C0A00000C0A00000C0A0
      2000C0A02000C0A02000C0A02000C0A04000C0C04000C0C04000C0A04000C080
      2000C0804000C0A04000F0CAA600C0A040000000000000000000000000000000
      0000C0A0C0004040E0004040E0004060E0008080E000C0A0E000F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00C0A0E0008080E0004060E0004040E0004040E000C0A0
      A00000000000000000000000000000000000000000000000000000000000C0A0
      6000C0802000C0A02000C0A02000C0C06000F0CAA600C0A06000C0C08000C0A0
      6000C0A06000C0C08000C0A06000F0CAA600C0C06000C0A02000C0A02000C080
      2000C0A060000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0804000804020000000
      000080400000C0A02000C0A02000C0A02000C0A02000C0A02000C0A02000C0A0
      2000C0A02000C0A02000C0A02000C06020000000000000000000C0400000C080
      0000C0A00000C0A00000C0A00000C0A00000C0A00000C0A00000C0A02000C0A0
      2000C0A02000C0A02000C0A04000C0C04000C0C04000C0C06000C0C06000C0C0
      6000C0C06000C0C06000F0CAA600C0A04000000000000000000000000000C0A0
      C0004040E0004040E0004040E0004060E0008080E000C0A0E000C0A0E000F0FB
      FF00F0FBFF00C0A0E000C0A0E0008080E0004060E0004040E0004020E0000020
      E000C0A0A0000000000000000000000000000000000000000000C0A08000C080
      2000C0A02000C0A02000F0CAA600C0C08000F0CAA600F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00C0DCC000C0C0A000C0C08000F0CAA600C0A02000C0A0
      2000C0802000C0A0800000000000000000000000000000000000000000000000
      00000000000000000000F0FBFF000000000000000000C0806000806020000000
      000080400000C0A02000C0A02000C0A02000C0A02000C0A02000C0A02000C0A0
      2000C0A02000C0A02000C0A02000C060200000000000C0806000C0600000C0A0
      0000C0A00000C0A00000C0A00000C0A00000C0A02000C0802000C0A02000C080
      4000C0A06000F0CAA600F0CAA600C0C06000C0C04000C0C06000C0C06000C0C0
      6000C0C06000F0CAA600F0CAA600C0A040000000000000000000C0C0C0004020
      C0000020E0004020E0004040E0004040E0004060E00080A0E000C0A0E000F0FB
      FF00F0FBFF00C0A0E00080A0E0004060E0004040E0004040E0000020C0000020
      C0000020C000C0C0C000000000000000000000000000F0FBFF00C0802000C0A0
      4000C0A02000F0CAA600F0CAA600C0DCC000C0DCC000F0FBFF00F0FBFF004020
      2000A4A0A000F0FBFF00C0DCC000C0C0C000C0C0C000C0A08000F0CAA600C0A0
      2000C0A02000C0802000F0FBFF00000000000000000000000000000000000000
      000000000000000000000020C0000000000000000000C0A04000806020000000
      000080400000C0A02000C0A02000C0A02000C0A02000C0A02000C0A02000C0A0
      2000C0A02000C0A02000C0A02000C060200000000000C0400000C0A00000C0A0
      0000C0A00000C0A00000C0A00000C0A02000C0602000C0602000C0C08000F0FB
      FF00F0CAA600C0A06000C0802000C0C08000F0CAA600C0C06000C0C06000C0C0
      6000F0CAA600F0CAA600F0CAA600C0A0400000000000000000004040A0000020
      E0000020C0004020C0004020E0004040E00080A0E000F0FBFF00000000000000
      00000000000000000000F0FBFF0080A0E0004040E0000020E0000020C0000020
      C0000020C0004040A000000000000000000000000000C0602000C0C04000C0A0
      4000F0CAA600F0CAA60000000000F0FBFF0040202000F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00C0DCC000C0C0C00040202000C0DCC000C0C0C000C0A08000F0CA
      A600C0A02000C0A02000C0602000000000000000000000000000000000000000
      000000000000000000000020C0000020E00000000000C0A06000806020000000
      000080400000C0A02000C0A02000C0A02000C0A02000C0A02000C0A02000C0A0
      2000C0A02000C0A02000C0A02000C0602000C0A08000C0600000C0A00000C0A0
      0000C0A00000C0A00000C0A02000C0602000F0CAA60000000000000000000000
      00000000000000000000F0CAA600C0802000F0CAA600C0C06000C0C06000F0CA
      A600F0CAA600F0CAA600F0CAA600C0A0400000000000C0C0C0000020C0000020
      C0000020C0000020C0004020E000C0A0E000000000000000000000000000F0FB
      FF00F0FBFF00000000000000000000000000C0A0E0004020C0000020C0000020
      C0000020C0000020C000C0A0C00000000000F0CAA600C0A04000C0C04000C0C0
      4000F0CAA6000000000000000000F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00C0DCC000C0DCC000C0DCC000C0DCC000C0C0C000C0C0C000F0CA
      A600C0A04000C0A04000C0802000F0CAA6000000000000000000000000000000
      000000000000000000000020C0004020E0000020E00080606000C06020000000
      000080400000C0A02000C0802000C0A02000C0A02000C0A02000C0A02000C0A0
      2000C0A02000C0A02000C0A02000C0602000C0804000C0800000C0A00000C0A0
      0000C0A02000C0A02000C0602000C0C080000000000000000000000000000000
      000000000000C0A06000C0A06000F0CAA600C0C06000C0C06000F0CAA600F0CA
      A600F0CAA600F0CAA600F0CAA600C0C04000000000008060A0000020C0000020
      C0000020C0000020C000C0A0E0000000000000000000C0A0E0004060E0004040
      E0004040E0004040E00080A0E0000000000000000000C0A0E0000020C0000020
      C0000020A0000020A0008060A00000000000C0A08000C0C04000C0C04000F0CA
      A600F0FBFF0040202000F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00C0DCC000C0DCC000C0DCC000C0DCC00040202000C0C0C000C0A0
      8000C0C08000C0A04000C0A04000C0A080000020E0000020E0004020E0004020
      E0004020E0004020E0004020E0004040E0004040E0000020E000402080000000
      000080400000F0CAA600C0C0C000C0802000C0A02000C0A02000C0A02000C0A0
      2000C0A02000C0A02000C0A02000C0802000C0600000C0600000C0800000C0A0
      2000C0A02000C0A02000C0602000000000000000000000000000000000000000
      0000C0802000C0A04000F0CAA60000000000F0FBFF00F0CAA600F0CAA600F0CA
      A600F0CAA600F0CAA600F0CAA600C0C04000F0FBFF004020A000000080000020
      A0000020C0004040C000000000000000000080A0E0000020E0004020E0004040
      E0004040E0004020E0000020C0008080E00000000000000000004040C0000020
      A00000008000000080000020A000F0FBFF00C0804000C0C06000C0C04000C0C0
      600000000000C0C0C000F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00C0DCC000C0DCC000C0DCC000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C08000C0A04000C0C04000C08040008080E0004040E0004040E0004040
      E0004040E0004040E0004040E0004040E0004040E0004040E0004020E0000000
      800080600000C0C08000F0CAA600C0A02000C0A02000C0A02000C0A02000C0A0
      2000C0A02000C0A02000C0A02000C08040000000000000000000F0CAA600C080
      4000C0602000C0802000C0A06000000000000000000000000000000000000000
      000000000000F0CAA600F0CAA600C0A04000C0A04000F0CAA600F0CAA6000000
      000000000000F0CAA600F0CAA600C0C04000C0DCC0000020A000000080000000
      80000020A0008080E00000000000F0FBFF000020C0000020C0004020C0004020
      E0004020E0004020C0000020C0000020C000F0FBFF00000000008080E0000000
      8000000080000000800000008000C0C0C000C0804000C0C06000C0C04000F0CA
      A600000000000000000000000000F0FBFF00F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00C0DCC000C0DCC000C0C0C000C0C0C000C0C0
      C000C0A08000C0C04000C0C04000C08020008080E0004040E0004040E0004040
      E0004040E0004040E0004040E0004040E0004040E0004040E0004040E0004060
      E00040208000C0C04000C0A04000C0C06000C0A04000C0A04000C0A02000C0A0
      4000C0A04000C0A04000C0A04000C0804000C0600000F0CAA600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000F0CAA600C0C08000C0A0
      4000C0C06000F0CAA600F0CAA600C0C06000C0C0C00000008000000080000000
      80000020A000C0A0E00000000000C0A0E0000020C0000020C0000020C0000020
      C0000020C0000020C0000020C0000020C000C0A0E00000000000C0A0E0000020
      A000000080000000800000008000C0C0C000C0A04000C0C06000C0C06000F0CA
      A600000000004020200000000000F0FBFF00F0FBFF00F0FBFF00000000000000
      0000000000004020200040202000402020004020200040202000A4A0A000C0DC
      C000C0C08000C0C04000C0C06000C0A040008080E0004040E0004040E0004040
      E0004040E0004040E0004040E0004040E0004040E0004060E00080A0E0000020
      C00080602000C0C06000C0C06000C0C06000C0C06000C0C06000C0A04000C0A0
      4000C0A04000C0A04000C0A04000C0804000C0802000C0C06000C0C06000C080
      4000C0804000C0A06000F0CAA600000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000F0CAA600C0C04000C0C0C0000020A000000080000000
      80000020A000C0A0E00000000000C0A0E0000020C0000020C0000020C0000020
      C0000020C0000020C0000020C0000020C000C0A0E00000000000C0A0E0000000
      800000008000000080000020A000C0C0C000C0A04000F0CAA600C0C06000C0C0
      600000000000C0C0C00000000000F0FBFF00F0FBFF00F0FBFF00000000004020
      2000A4A0A00000000000000000000000000000000000F0FBFF00C0DCC000C0DC
      C000C0A04000C0C06000F0CAA600C0A040008080E00080A0E00080A0E00080A0
      E00080A0E00080A0E00080A0E0004040E0004060E00080A0E0004020E0000000
      000080602000C0C06000C0C06000C0C06000C0C06000C0C06000C0C06000C0C0
      6000C0A04000C0A04000C0A04000C0804000C0600000C0C02000C0C06000F0CA
      A60000000000F0CAA600C0C06000C0804000C0802000C0A08000F0CAA6000000
      00000000000000000000000000000000000000000000C0C08000C0A04000C0A0
      4000C0C06000000000000000000000000000C0C0C0000020C0000020A0000020
      A0000020A0008080E00000000000F0FBFF000020C0000020C0004020E00080A0
      E00080A0E0004020E0000020C0000020C000F0FBFF00000000008080E0000000
      80000020A0000020A0000020A000C0C0C000C0A04000F0CAA600C0C06000C0C0
      6000000000000000000000000000F0FBFF00F0FBFF00F0FBFF00000000004020
      2000C0A0C00000000000F0FBFF00F0FBFF00F0FBFF00F0FBFF00C0DCC000C0DC
      C000C0A06000C0C06000F0CAA600C0A040004040E0004060E0004040E0004040
      E0004040E0004060E0004040E0004060E00080A0E0008040C000C06020000000
      000080602000C0C06000C0C06000C0C06000C0C06000C0C06000C0C06000C0C0
      6000C0C06000C0C06000C0A04000C0804000C0600000C0A00000C0A00000C0A0
      0000C0A02000C0C06000F0CAA600F0CAA600F0CAA600F0CAA600C0804000C080
      20000000000000000000000000000000000000000000C0A04000F0CAA600F0CA
      A600F0CAA600F0CAA600F0CAA600C0C04000F0FBFF004020A0000020C0000020
      C0000020A0004020C000000000000000000080A0E0000020E0004060E0000000
      0000000000004060E0000020E000C0A0E00000000000F0FBFF004020C0000020
      A0000020C0000020C0004020A000F0FBFF00C0A04000F0CAA600F0CAA600C0C0
      600000000000000000000000000000000000F0FBFF00F0FBFF00000000004020
      2000C0A0C000F0FBFF00F0FBFF00F0FBFF00C0DCC000C0DCC000C0A0C000C0DC
      C000C0C08000F0CAA600F0CAA600C0A040000000000000000000000000000000
      000000000000000000004020E00080A0E0004020E000C0C06000C08040000000
      0000C0602000C0C08000C0C06000C0C06000C0C06000C0C06000C0C06000C0C0
      6000C0C06000C0C06000C0C08000C0804000C0600000C0A00000C0A00000C0A0
      2000C0A02000C0A02000C0A04000C0C04000F0CAA600C0A04000C0A060000000
      000000000000000000000000000000000000F0CAA600C0A04000F0CAA600F0CA
      A600F0CAA600F0CAA600F0CAA600C0C06000000000008060A0000020C0000020
      C0000020C0000020C00080A0E000000000000000000080A0E0008080E0000000
      0000000000008080E000C0A0E00000000000000000008080E0000020C0000020
      C0000020C0000020C0008060A00000000000C0C08000F0CAA600F0CAA600F0CA
      A600F0FBFF00F0FBFF004020200000000000F0FBFF00F0FBFF00000000004020
      2000C0C0C000F0FBFF00F0FBFF00F0FBFF00C0DCC00040202000C0DCC000F0CA
      A600F0CAA600F0CAA600F0CAA600C0C080000000000000000000000000000000
      000000000000000000004020E0000000FF0000000000C0C06000C08040000000
      0000C0602000F0CAA600C0C08000C0C08000C0C08000C0C08000C0C08000C0C0
      8000C0C08000C0C08000F0CAA600C0804000C0600000C0A00000C0A02000C0A0
      2000C0A02000C0A04000C0A04000F0CAA600C0802000F0CAA600000000000000
      0000000000000000000000000000F0CAA600C0A04000F0CAA600F0CAA600F0CA
      A600F0CAA60000000000F0CAA600F0CAA60000000000C0A0C0000020C0000020
      C0000020C0000020C0004020C000C0A0E00000000000F0FBFF008080E0000000
      000000000000C0A0E0000000000000000000C0A0E0000020C0000020C0000020
      C0000020C0000020C000C0A0C00000000000F0CAA600C0C08000F0FBFF00F0CA
      A600F0CAA60000000000C0C0C00000000000F0FBFF00F0FBFF00F0FBFF004020
      2000C0DCC000F0FBFF00F0FBFF00F0FBFF00C0DCC000C0DCC000C0DCC000F0CA
      A600F0CAA600F0FBFF00C0C06000F0CAA6000000000000000000000000000000
      000000000000000000000000FF000000000000000000C0A06000C08040000000
      0000C0802000F0CAA600F0CAA600F0CAA600F0CAA600F0CAA600F0CAA600F0CA
      A600F0CAA600F0CAA600F0CAA600C0A04000C0600000C0A00000C0A02000C0A0
      2000C0A02000C0A04000C0C04000F0CAA600C0C08000C0802000C0C08000F0CA
      A600F0FBFF00F0CAA600C0A04000C0A04000F0CAA600F0CAA600F0CAA600F0CA
      A600F0CAA60000000000C0C040000000000000000000000000004040A0000020
      C0000020C0000020C0004040E0004040E00080A0E0008080E00080A0E0000000
      000000000000C0A0E00080A0E0008080E0004040E0004040E0000020C0000020
      C0000020C0004040A000000000000000000000000000C0A04000F0CAA600F0FB
      FF00F0CAA600F0CAA6000000000000000000F0FBFF00F0FBFF00F0FBFF00F0FB
      FF00F0FBFF00F0FBFF00F0FBFF00C0DCC000C0C0C000C0DCC000F0CAA600F0CA
      A600F0FBFF00F0CAA600C0A04000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C06000C08040000000
      0000C0804000F0CAA600F0CAA600F0CAA600F0CAA600F0CAA600F0CAA600F0CA
      A600F0CAA600F0CAA600F0CAA600C0A04000C0600000C0A00000C0A02000C0A0
      2000C0A02000C0A04000C0C04000C0C04000C0C06000F0CAA600F0CAA600C0C0
      8000C0A04000C0C06000C0C06000F0CAA600F0CAA600F0CAA600F0CAA600F0CA
      A60000000000C0C06000F0CAA600000000000000000000000000C0C0C0004020
      C0000020C0004020E0004040E0004060E0008060E0008080E000C0A0E0000000
      000000000000C0A0E0008080E0008080E0004060E0004040E0004020E0000020
      C0000020C000C0C0C000000000000000000000000000F0FBFF00C0C06000F0FB
      FF00F0FBFF00F0CAA600F0CAA6000000000040202000C0C0C000000000004020
      2000C0DCC000F0FBFF00F0FBFF0040202000C0C0C000F0CAA600F0CAA600F0FB
      FF00F0FBFF00C0C06000F0FBFF00000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C06000C08040000000
      0000C0804000F0CAA600F0CAA600F0CAA600F0CAA600F0CAA600F0CAA600F0CA
      A600F0CAA600F0CAA600F0CAA600C0A04000C0600000C0A00000C0A02000C0A0
      2000C0A04000C0C04000C0C04000C0C04000C0C04000C0C06000C0C06000C0C0
      6000F0CAA600F0CAA600F0CAA600F0CAA600F0CAA600F0CAA600F0CAA6000000
      0000F0CAA600C0C040000000000000000000000000000000000000000000C0A0
      C0004020E0004040E0004040E0008060E0008080E00080A0E000C0A0E000F0FB
      FF00F0FBFF00C0A0E000C0A0E0008080E0008060E0004060E0004040E0000020
      E000A4A0A0000000000000000000000000000000000000000000F0CAA600F0CA
      A60000000000F0FBFF00F0CAA600F0CAA600F0FBFF00F0FBFF00F0FBFF000000
      0000F0FBFF00F0FBFF00F0FBFF00F0CAA600F0CAA600F0CAA600F0FBFF00F0FB
      FF00F0CAA600F0CAA60000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C06000C08040000000
      0000C0A04000F0CAA600F0CAA600F0CAA600F0CAA600F0CAA600F0CAA600F0CA
      A600F0CAA600F0CAA600F0CAA600C0A04000C0602000C0A02000C0802000C080
      2000C0802000C0A04000C0C04000C0C04000C0C06000C0C06000C0C06000C0C0
      6000F0CAA600F0CAA600F0CAA600F0CAA600F0CAA600F0CAA60000000000F0CA
      A600C0C040000000000000000000000000000000000000000000000000000000
      0000C0A0C0004040E0004060E0008080E0008080E000C0A0E000C0A0E000F0FB
      FF00F0FBFF00C0A0E000C0A0E00080A0E0008080E0004060E0004040E000A4A0
      A00000000000000000000000000000000000000000000000000000000000F0CA
      A600F0CAA6000000000000000000F0CAA600F0CAA600F0CAA600F0CAA600F0CA
      A600F0CAA600F0CAA600F0CAA600F0CAA600F0CAA600F0FBFF0000000000F0CA
      A600F0CAA6000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C08000C08040000000
      0000402020008080600080806000C0C08000F0CAA600F0CAA600F0CAA600F0CA
      A600F0CAA600F0CAA600F0CAA600C0A04000C0802000C0802000C0A060000000
      000000000000C0802000C0A04000C0C06000C0C06000C0C06000C0C06000C0C0
      6000C0C06000F0CAA600F0CAA600F0CAA600F0CAA60000000000C0C06000C0C0
      4000000000000000000000000000000000000000000000000000000000000000
      000000000000C0C0C0008060C0008060E00080A0E000C0A0E000C0A0E000C0A0
      E000C0A0E000C0A0E000C0A0E00080A0E0008080E0008060C000C0C0C0000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F0CAA600C0C08000000000000000000000000000F0FBFF00F0CAA600F0CA
      A600F0CAA600F0CAA600F0FBFF000000000000000000F0CAA600C0C08000F0CA
      A600000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C08000C0A040008060
      2000806020008040200080402000804020008040200040402000C0804000C0A0
      6000F0CAA600F0CAA600F0CAA600C0A04000C0602000F0CAA600000000000000
      00000000000000000000C0C08000C0802000C0C06000F0CAA600F0CAA600F0CA
      A600F0CAA600F0CAA60000000000F0CAA600F0CAA600C0C04000F0CAA6000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000C0A0C0008080C0008080E0008080E00080A0
      E00080A0E00080A0E0008080E0008080C000C0A0C00000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000F0FBFF00C0C04000F0CAA600F0CAA600F0FBFF00000000000000
      00000000000000000000F0FBFF00F0CAA600F0CAA600C0C04000F0FBFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C08000C0C06000C0C0
      6000C0C06000C0C06000C0C06000C0C06000C0C06000C0C06000C0C06000C0C0
      6000C0A04000C0A04000C0A04000C0C060000000000000000000000000000000
      000000000000000000000000000000000000F0CAA600C0A06000C0A02000C0A0
      2000C0C06000C0A04000C0A04000C0C06000F0CAA60000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000F0FBFF00C0C0C000C0C0
      C000C0C0C000C0C0C000F0FBFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000F0CAA600F0CAA600C0C06000C0C06000F0CA
      A600F0CAA600C0C06000C0C06000F0CAA600F0CAA60000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000060000000900000000100010000000000C00600000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFE3FC1FE3FFFFFFFFFFFFFE20C1FCCFC1FFFFFF83FFFFF9E0
      C0FC07C0FFFFFE7CFFFFF9E0C03C53C03FFFFDEF7FE3F9FFC03C0BC03FFFFB7D
      BFE3F9F8E01F03E01F7FF7FFDFE3F9F8F011A1F011FFF5FF5FFFF9F8FC00E5FC
      00FDEFFFEFEFF9FFFC407FFC407FEFFFEFEFF9FFFE807FFE807FEBE1AFE3F7F8
      FF01FFFF01FFEFEFEFF1CFF8FF023FFF023FEFEFEFF1CFF8FF003FFF003FF5EF
      5FFC77FFFFCC0FFFCC0FF7EFDF1C79F8FFF807FFF807FB6DBF1C79F8FFFC03FF
      FC03FDEF7F1C79F8EDF403EDF403FE7CFF81F9FFD0CB03D0CB03FF83FF81F9FF
      A02383A02383FFFFFFFFF9E0F083C7F083C7FFFFFFFFFE20C463FFC463FFFFFF
      FFFFFE20FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFF
      FFFFFFFEFFFFFFFFFFFE20800003FFFE3FFF8000FFF9E0800003FFFE1FFF8000
      FFF9E0800003FFFE1FFF8000E3F9FF800003000007FF8000E3F9F88000030000
      03FF8000E3F9F8800003000003FF8000FFF9F8800003000000F38000EFF9FF80
      0003000003F18000EFF9FF800003000003F18000E3F7F8800003000007F00000
      F1CFF880000300001F000000F1CFF880000300001F000000FC77FF8000030000
      3F0000031C79F88000030000FF0000071C79F88000030000FF0000071C79F880
      00030007FF00001F81F9FF800003000FFF00003F81F9FF800003000FFF00003F
      FFF9E0800003003FFFF07FFFFFFE20800003007FFFF1FFFFFFFE20800003007F
      FFF1FFFFFFFFFFFFFFFFFFFFFFF3FFFFE1FFFFFFCFFFFFCFFFFFC7FFC0FFFFFF
      CFFFFFCFFFFFC7FF807FFFFF87FFFF87FFFFC0FF003FFFFF87FFFF87FFFF801F
      001FFFFF87FFFF87FFFF801F000FFFFF87FFEE01DFFF8003000FFFFF87FFF000
      3FFE0000001FFFFF87FFF0003FFE0000003FFFFF87FFF0003FFE0000007FFFFE
      01FFE0001F00000000FFFFFE01FFE0001F00000000FFFFFC00FFE0001F000000
      807FFFFC00FF000003000003803F1FFC00FF000003000003C01E0FFC00FFE000
      1F0001C4C00C07FE01FFE0001F0001FCE00003FE01FFE0001F0001FCF00001FF
      87FFF0003F0001FCF80000FFFFFFF0003F0001FCFC0000FFFFFFF0003F0001FC
      FE0000FFFFFFEE01DF0000FBFF0000FFFFFFFFCFFF000107FFC001FFFFFFFFCF
      FF000107FFF007FFFFFFFFCFFF0001FFF00000F9FFFFFC003FFFF007100000F8
      FFFFF8001FFFC001000000F87FFFF0000FFF0000000000FC3FFFE00007FE0000
      000000FC0FFFC00003FC0000000000FE07FF800001F80000000000FE03FF0000
      00F00001000000FF01FF000000E00003000000FE01FF000000C00C07000000FE
      03FF1C47A0C01E0F000000FE03FF0448A0803F1F000000FF01FF0C48BC807FFF
      000000FF80FF1848A400FFFF000000FFC07F1048A400FFFF000000FFC03F15E7
      AC007FFF000000FF003F000000003FFF000000FF007F000000001FFF000000FF
      003F000000000FFF000000FF803F800001000FFF000000FFC01FC00003001FFF
      000000FFE01FE00007003FFF000000FFF03FF0000F807FFF000000FFF07FF800
      1FC0FFFF000000FFF8FFFC003FE1FFFFFFF0FFFE00FFFF81FFFE007FFFF00FF8
      003CFE007FF8001FFF8000E00018F8001FF0000FFF8000C00000F0000FE00007
      FF8000C00000E00007C00003FD8000800000C00003800001FD8000800000C03C
      03820001FC8000007C0080E701060000FC000000F80081818100000000000001
      F1000300C0080000000000C1F8180200400E00000000003FFF800200400A2000
      00000001FFFC0200400A2780000000081F870200400E2400000000000F800318
      800F2000FC0000001F00819981012000FC8000003E04809B01050000FD800000
      0005C01803830001FF8000000009C01803812001FF8000000013E00007C81003
      FF8000000027F0000FE60027FF800018004FF8001FF3818FFF80003C021FFE00
      7FF83C1FFF8000FF007FFF81FFFE007F00000000000000000000000000000000
      000000000000}
  end
  object odOpenLogs: TOpenDialog
    Filter = 'Log files (*.log)|*.log'
    Options = [ofReadOnly, ofHideReadOnly, ofEnableSizing]
    Left = 920
  end
  object odOpenLogPath: TOpenDialog
    Left = 1120
  end
end
