//---------------------------------------------------------------------------


#pragma hdrstop

#include "mainflow.h"
#include <vcl.h>
#include "uDM.h"
#include "action.h"
#include "util.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)








void _fastcall clearLog(){
	dm->cmdLog->CommandText = "delete from action_log";
	dm->cmdLog->Execute();
	dm->tbActionLog->Refresh();
}

void _fastcall saveLog(int groupId){
	TStringList *sql = new TStringList();
	sql->Add("insert into log_history(group_id, component_type, operation, status, log_time, para_desc) select");
	sql->Add(IntToStr(groupId));
	sql->Add(", component_type, operation, status, insert_time, para_desc from action_log");
	dm->cmdLog->CommandText = sql->Text;
	dm->cmdLog->Execute();
}

void _fastcall writeLog(Action action, const int status){


}

bool _fastcall initDB(){
	if (!dm->tbActionLog->Active)
		dm->tbActionLog->Open();
	return true;
}

void _fastcall initActions(){
	initDB();
	clearLog();
//	const int actSize = dm->tbActionList->RecordCount;
//	Action *pAct = new Action[actSize];
//	dm->tbActionList->Sort = "order_id";
//	dm->tbActionList->First();
//	while(!dm->tbActionList->Eof){
//		pAct[dm->tbActionList->RecNo - 1].type = dm->tbActionList->FieldByName("compnent_type")->AsInteger;
//		pAct[dm->tbActionList->RecNo - 1].operation = dm->tbActionList->FieldByName("actionType")->AsInteger;
//		pAct[dm->tbActionList->RecNo - 1].para[0] = dm->tbActionList->FieldByName("para1")->AsInteger;
//		pAct[dm->tbActionList->RecNo - 1].para[1] = dm->tbActionList->FieldByName("para2")->AsInteger;
//		pAct[dm->tbActionList->RecNo - 1].para[2] = dm->tbActionList->FieldByName("para3")->AsInteger;
//		pAct[dm->tbActionList->RecNo - 1].para[3] = dm->tbActionList->FieldByName("para4")->AsInteger;
//		pAct[dm->tbActionList->RecNo - 1].para[4] = dm->tbActionList->FieldByName("para5")->AsInteger;
//		dm->tbActionList->Next();
//	}
//	delete[] pAct;
	saveLog(dm->tbActionList->FieldByName("group_id")->AsInteger);
}



void _fastcall trigger(Action *action){
	int len = sizeof(action);
	for (int i = 0; i < len - 1; i++) {


	}


}


