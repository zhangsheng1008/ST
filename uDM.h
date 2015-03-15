//---------------------------------------------------------------------------

#ifndef uDMH
#define uDMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tdm : public TDataModule
{
__published:	// IDE-managed Components
	TADOConnection *dbConn;
	TADOTable *tbActionList;
	TADOCommand *cmdLog;
	TADOTable *tbActionLog;
	TDataSource *dsComp;
	TADOTable *tbComponent;
	TADOTable *tbOperation;
	TDataSource *dsOper;
	TAutoIncField *tbComponentId;
	TIntegerField *tbComponenttype;
	TStringField *tbComponentname;
	TIntegerField *tbComponentport;
	TStringField *tbComponentpara1;
	TStringField *tbComponentpara2;
	TStringField *tbComponentpara3;
	TStringField *tbComponentpara4;
	TStringField *tbComponentpara5;
	TStringField *tbComponentpara6;
	TIntegerField *tbComponentbaud_rate;
	TIntegerField *tbComponentstop_bits;
	TIntegerField *tbComponentbyte_size;
	TIntegerField *tbComponentparity;
	TIntegerField *tbComponentfparity;
private:	// User declarations
public:		// User declarations
	__fastcall Tdm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tdm *dm;
//---------------------------------------------------------------------------
#endif
