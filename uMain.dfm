object fmMain: TfmMain
  Left = 0
  Top = 0
  Caption = 'main'
  ClientHeight = 631
  ClientWidth = 898
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object btnStart: TButton
    Left = 280
    Top = 472
    Width = 75
    Height = 25
    Caption = #24320#22987
    TabOrder = 0
    OnClick = btnStartClick
  end
  object Edit1: TEdit
    Left = 520
    Top = 160
    Width = 121
    Height = 21
    TabOrder = 1
    Text = '10'
  end
  object Edit2: TEdit
    Left = 520
    Top = 216
    Width = 289
    Height = 21
    TabOrder = 2
    Text = 'abcd{1.1}fgs {1.2}, 2..3{2.1}, .23 {2.2}'
  end
  object Edit3: TEdit
    Left = 520
    Top = 264
    Width = 289
    Height = 21
    TabOrder = 3
  end
  object Edit4: TEdit
    Left = 688
    Top = 160
    Width = 121
    Height = 21
    TabOrder = 4
    Text = '20'
  end
  object Edit5: TEdit
    Left = 144
    Top = 152
    Width = 121
    Height = 21
    TabOrder = 5
    Text = '2233444556'
  end
  object Edit6: TEdit
    Left = 144
    Top = 208
    Width = 121
    Height = 21
    TabOrder = 6
    Text = '22(\d{2})(\d{3})55(\d{1})'
  end
  object Memo1: TMemo
    Left = 144
    Top = 280
    Width = 185
    Height = 89
    TabOrder = 7
  end
  object Button1: TButton
    Left = 144
    Top = 472
    Width = 75
    Height = 25
    Caption = 'test2'
    TabOrder = 8
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 416
    Top = 472
    Width = 75
    Height = 25
    Caption = 'test3'
    TabOrder = 9
    OnClick = Button2Click
  end
  object Edit7: TEdit
    Left = 520
    Top = 336
    Width = 289
    Height = 21
    TabOrder = 10
    Text = 'FF FD 01 01 00 00'
  end
  object Button3: TButton
    Left = 584
    Top = 472
    Width = 75
    Height = 25
    Caption = 'test1'
    TabOrder = 11
    OnClick = Button3Click
  end
end
