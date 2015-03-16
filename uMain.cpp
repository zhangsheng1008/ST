//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uMain.h"
#include "mainflow.h"
#include "util.h"
#include "boost/regex.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmMain *fmMain;
//---------------------------------------------------------------------------
__fastcall TfmMain::TfmMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::btnStartClick(TObject *Sender)
{

	String para[] = {Edit1->Text, Edit4->Text};
	Edit3->Text = paraProcess(Edit2->Text, para);

}
//---------------------------------------------------------------------------

void __fastcall TfmMain::Button1Click(TObject *Sender)
{

	regexMap(Edit5->Text, Edit6->Text);
	for (int i = 0; i < 10 - 1; i++) {
		Memo1->Lines = (regexMap(Edit5->Text, Edit6->Text));
	}
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::Button2Click(TObject *Sender)
{
	initContent(this, "Edit", "a,b,c,d,e,f");
}
//---------------------------------------------------------------------------


void __fastcall TfmMain::Button3Click(TObject *Sender)
{
	unsigned char buf[5] = {0xff, 0xfd, 0x30, 0x01, 0x00};
	Edit7->Text = convertHexResult(buf, 5);
}
//---------------------------------------------------------------------------

