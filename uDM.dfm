object dm: Tdm
  OldCreateOrder = False
  Height = 305
  Width = 424
  object dbConn: TADOConnection
    Connected = True
    ConnectionString = 
      'Provider=SQLNCLI11.1;Integrated Security=SSPI;Persist Security I' +
      'nfo=False;User ID="";Initial Catalog=proj;Data Source=(localdb)\' +
      'Projects;Initial File Name="";Server SPN=zslabtop-PC\zslabtop'
    ConnectionTimeout = 30
    LoginPrompt = False
    Provider = 'SQLNCLI11.1'
    Left = 56
    Top = 16
  end
  object tbActionList: TADOTable
    Active = True
    Connection = dbConn
    CursorType = ctStatic
    LockType = ltReadOnly
    TableName = 'action_list'
    Left = 280
    Top = 136
  end
  object cmdLog: TADOCommand
    Connection = dbConn
    ExecuteOptions = [eoExecuteNoRecords]
    Parameters = <>
    Left = 280
    Top = 96
  end
  object tbActionLog: TADOTable
    Connection = dbConn
    TableName = 'action_log'
    Left = 304
    Top = 224
  end
  object dsComp: TDataSource
    DataSet = tbComponent
    Left = 104
    Top = 88
  end
  object tbComponent: TADOTable
    Active = True
    Connection = dbConn
    CursorType = ctStatic
    TableName = 'component'
    Left = 48
    Top = 80
    object tbComponentId: TAutoIncField
      FieldName = 'Id'
      ReadOnly = True
    end
    object tbComponenttype: TIntegerField
      FieldName = 'type'
    end
    object tbComponentname: TStringField
      FieldName = 'name'
      Size = 50
    end
    object tbComponentport: TIntegerField
      FieldName = 'port'
    end
    object tbComponentpara1: TStringField
      FieldName = 'para1'
      Size = 50
    end
    object tbComponentpara2: TStringField
      FieldName = 'para2'
      Size = 50
    end
    object tbComponentpara3: TStringField
      FieldName = 'para3'
      Size = 50
    end
    object tbComponentpara4: TStringField
      FieldName = 'para4'
      Size = 50
    end
    object tbComponentpara5: TStringField
      FieldName = 'para5'
      Size = 50
    end
    object tbComponentpara6: TStringField
      FieldName = 'para6'
      Size = 50
    end
    object tbComponentbaud_rate: TIntegerField
      FieldName = 'baud_rate'
    end
    object tbComponentstop_bits: TIntegerField
      FieldName = 'stop_bits'
    end
    object tbComponentbyte_size: TIntegerField
      FieldName = 'byte_size'
    end
    object tbComponentparity: TIntegerField
      FieldName = 'parity'
    end
    object tbComponentfparity: TIntegerField
      FieldName = 'fparity'
    end
  end
  object tbOperation: TADOTable
    Active = True
    Connection = dbConn
    CursorType = ctStatic
    TableName = 'operation'
    Left = 48
    Top = 136
  end
  object dsOper: TDataSource
    DataSet = tbOperation
    Left = 96
    Top = 136
  end
end
