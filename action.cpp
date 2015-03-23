//---------------------------------------------------------------------------


#pragma hdrstop

#include "action.h"
#include "util.h"
#include <time.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)
//void Action::log(String str){
//
//}

int Action::execute(){
	  //log();
      return 0;
}

//int Action::init(){
//}

int SleepAction::execute(){
	return 0;
}



void ComponentAction::buildCommand(){
	command_str = paraProcess(operation->commandTemplate, operation->commandPara);
	if (component->type != 5) {
	  unsigned int len;
	  command = convertHexCommand(command_str, &len);
	  command_size = len;
	  unsigned int sum = 0;
	  if (operation->checkSum) {
		 for (unsigned int i = 0; i < len - 1; i++) {
		   sum = sum + command[i];
		 }
		 while (sum > 255)
			sum = sum - 256;
		 command[len-1] = sum;
		 command_str = command_str.SubString(0, command_str.Length() - 3) + IntToHex((unsigned char)sum, 2);
	  }
	} else {
	  command = command_str.t_str();
	  command_size = command_str.Length();
    }
}

void ComponentAction::setDCB(DCB *d){
	d->BaudRate = component->dcb->BaudRate;
	//d->fBinary=1;
	d->ByteSize=8;
	d->Parity=NOPARITY;
	d->StopBits=ONESTOPBIT;
}

int ComponentAction::openComPort(){
	hCom = CreateFile(component->port.t_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
	if (hCom == INVALID_HANDLE_VALUE) {
		return ERR_OPEN_PORT;
	}
	DCB dcb;
	GetCommState(hCom, &dcb);
	setDCB(&dcb);
	component->timeoutSetting.ReadIntervalTimeout = 0;
	component->timeoutSetting.ReadTotalTimeoutMultiplier = 0;
	component->timeoutSetting.ReadTotalTimeoutConstant    = 100;
	component->timeoutSetting.WriteTotalTimeoutMultiplier = 0;
	component->timeoutSetting.WriteTotalTimeoutConstant   = 100;
	//SetCommTimeouts(hCom,  &(component->timeoutSetting)) == false
	if (SetCommState(hCom, &dcb) == false){
		 closeComPort();
		 return ERR_SET_PORT;

	}

	return RESULT_SUCC;
}

int ComponentAction::closeComPort(){
	CloseHandle(hCom);
	return RESULT_SUCC;
}

int ComponentAction::execute(){
	if (openComPort() == RESULT_SUCC) {
		if (operation->type == OPER_WRITE) {
			buildCommand();
			time_t t1, t2;
			time(&t1);
			sendCommand();
			time(&t2);
			while(difftime(t2, t1) < operation->interval){
			  time(&t2);
			}
		}
		readCom();
		closeComPort();
		processResult();
    }
	return RESULT_SUCC;

}


void ComponentAction::sendCommand(){
	DWORD lpNumberOfBytesWritten;
	PurgeComm(hCom,PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	WriteFile(hCom, command, command_size, &lpNumberOfBytesWritten, NULL);
}


int ComponentAction::readCom(){
    DWORD lpErr ,lpNumberOfBytesRead;
	COMSTAT comStat;
	ClearCommError(hCom,  &lpErr, &comStat);
	if (comStat.cbInQue > 4096 || comStat.cbInQue == 0) {
		PurgeComm(hCom,PURGE_RXCLEAR);
		return ERR_READ_PORT;
	}
	result_size = comStat.cbInQue;
	ReadFile(hCom, result, comStat.cbInQue, &lpNumberOfBytesRead, NULL);
	return RESULT_SUCC;
}



void ComponentAction::processResult(){
	if (component->type == 1) {
		TStringList *s = new TStringList();
		s->DelimitedText = operation->returnTemplate;
		s->Delimiter = ',';
		for (int i = 0; i < s->Count; i++) {
           parseResult[i] = IntToStr(result[StrToInt((*s)[i])]);
		}
		result_str = convertHexResult(result, result_size);
	} else if(component->type == 2){
		for (unsigned int i = 0;i < result_size; i++) {
           result_str = result_str + (char)(result[i]);
		}
		TStrings *s = regexMap(result_str, operation->returnTemplate);
		for (int i = 0; i < s->Count; i++) {
			parseResult[i] = (*s)[i];
		}
	} else {
		result_str =  String((char*)result);
		TStrings *s = regexMap(result_str, operation->returnTemplate);
		for (int i = 0; i < s->Count; i++) {
			parseResult[i] = (*s)[i];
		}
	}

}


int ComponentAction::analyze(){
	for (int i= 0; i < result_size; i++) {

	}

}
ComponentAction::ComponentAction(){
}
