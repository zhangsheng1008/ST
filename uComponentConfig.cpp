//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uComponentConfig.h"
#include "uDM.h"
#include "action.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmComponentConfig *fmComponentConfig;
//---------------------------------------------------------------------------
__fastcall TfmComponentConfig::TfmComponentConfig(TComponent* Owner)
	: TForm(Owner)
{


}
//---------------------------------------------------------------------------


Component* __fastcall loadCompConfig(){
	Component *component = new Component();
	DCB *lpdcb = new DCB();
	lpdcb->BaudRate = dm->tbComponent->FieldByName("baud_rate")->AsInteger;
	component->port = "COM" + dm->tbComponent->FieldByName("port")->AsString;
	component->dcb =  lpdcb;
	return component;
}

Operation* __fastcall loadOperation(){
	Operation *operation = new Operation();
	operation->commandPara[0] = dm->tbOperation->FieldByName("wpara1")->AsString;
	operation->commandPara[1] = dm->tbOperation->FieldByName("wpara2")->AsString;
	operation->commandPara[2] = dm->tbOperation->FieldByName("wpara3")->AsString;
	operation->commandPara[3] = dm->tbOperation->FieldByName("wpara4")->AsString;
	operation->commandPara[4] = dm->tbOperation->FieldByName("wpara5")->AsString;
	operation->commandPara[5] = dm->tbOperation->FieldByName("wpara6")->AsString;
	operation->commandTemplate = dm->tbOperation->FieldByName("write_tpl")->AsString;
	operation->returnPara[0] = dm->tbOperation->FieldByName("rpara1")->AsString;
	operation->returnPara[1] = dm->tbOperation->FieldByName("rpara2")->AsString;
	operation->returnPara[2] = dm->tbOperation->FieldByName("rpara3")->AsString;
	operation->returnPara[3] = dm->tbOperation->FieldByName("rpara4")->AsString;
	operation->returnPara[4] = dm->tbOperation->FieldByName("rpara5")->AsString;
	operation->returnPara[5] = dm->tbOperation->FieldByName("rpara6")->AsString;
	operation->returnTemplate = dm->tbOperation->FieldByName("read_tpl")->AsString;
	operation->interval = dm->tbOperation->FieldByName("interval")->AsInteger;
	operation->checkSum = dm->tbOperation->FieldByName("checksum")->AsBoolean;
	return operation;
}
void __fastcall TfmComponentConfig::btnSendClick(TObject *Sender)
{
	ComponentAction cAction ;
	cAction.operation = loadOperation();
	cAction.component = loadCompConfig();
	cAction.execute();
	memoLog->Lines->Add(cAction.command_str);
	memoLog->Lines->Add(cAction.result_str);
	for (int i= 0; i < 5; i++) {
	  memoLog->Lines->Add("result para " + IntToStr(i) + ": " + cAction.parseResult[i]);
	}
}
//---------------------------------------------------------------------------

