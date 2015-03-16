//---------------------------------------------------------------------------

#ifndef uComponentConfigH
#define uComponentConfigH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TfmComponentConfig : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *dbComponet;
	TDBNavigator *DBNavigator1;
	TDBGrid *DBGrid1;
	TDBNavigator *DBNavigator2;
	TButton *btnSend;
	TMemo *memoLog;
	TLabel *Label1;
	TDBEdit *DBEdit1;
	TLabel *Label2;
	TDBEdit *DBEdit2;
	TLabel *Label3;
	TDBEdit *DBEdit3;
	TLabel *Label4;
	TDBEdit *DBEdit4;
	TLabel *Label5;
	TDBEdit *DBEdit5;
	TLabel *Label6;
	TDBEdit *DBEdit6;
	TLabel *Label7;
	TDBEdit *DBEdit7;
	TLabel *Label8;
	TDBEdit *DBEdit8;
	TLabel *Label9;
	TDBEdit *DBEdit9;
	TLabel *Label10;
	TDBEdit *DBEdit10;
	TLabel *Label11;
	TDBEdit *DBEdit11;
	TLabel *Label12;
	TDBEdit *DBEdit12;
	TLabel *Label13;
	TDBEdit *DBEdit13;
	TLabel *Label14;
	TDBEdit *DBEdit14;
	TDBCheckBox *DBCheckBox1;
	void __fastcall btnSendClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfmComponentConfig(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmComponentConfig *fmComponentConfig;
//---------------------------------------------------------------------------
#endif
