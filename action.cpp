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
	  unsigned int sum;
	  if (operation->checkSum) {
		 for (int i = 0; i < len - 1; i++) {
		   sum = sum + command[i];
		   if (sum > 255)
			  sum = sum - 255;
		 }
		 command[len-1] = sum;
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
	// || SetCommTimeouts(hCom,  &(component->timeoutSetting)) == false
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
		buildCommand();
		returnResult = sendCommand();
		closeComPort();
		processReadResult();
    }
	return RESULT_SUCC;

}


String ComponentAction::sendCommand(){
	char rcBuf[1024];
	DWORD lpNumberOfBytesWritten,lpNumberOfBytesRead, lpErr;
	PurgeComm(hCom,PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	time_t t1, t2;
	time(&t1);
	WriteFile(hCom, command, command_size, &lpNumberOfBytesWritten, NULL);
	time(&t2);
	while(difftime(t2, t1) < operation->interval){
	  time(&t2);
	}
	COMSTAT comStat;
	ClearCommError(hCom,  &lpErr, &comStat);
	if (comStat.cbInQue > 1024) {
		PurgeComm(hCom,PURGE_RXCLEAR);
		return "Err";
	}
	ReadFile(hCom, rcBuf, comStat.cbInQue, &lpNumberOfBytesRead, NULL);
	return String(rcBuf);
}


//void ComponentAction::recieve(){
//	char *lpBuf;
//	ONESTOPBIT;
//	if (!fWaitingOnRead){
//		if (!ReadFile(hCom, lpBuf, READ_BUF_SIZE, &drRead, &osReader)){
//			int check =GetLastError();
//			if (GetLastError() != ERROR_IO_PENDING)     // read not delayed?
//				log("Read error !=ERROR_IO_PENDING : %d \n");
//			else
//			{
//				log("IO_PENDING \n");
//				fWaitingOnRead = TRUE;
//			}
//		}
//		else
//		{
//			for(int i=0; i<(int)drRead;i++)
//				log("Received: %c \n ");
//		}
//		processReadResult(lpBuf);
//	}
//	else{
//		drRes = WaitForSingleObject(osReader.hEvent, READ_TIMEOUT);
//		switch(drRes)
//		{
//			// Read completed.
//		case WAIT_OBJECT_0:
//			if (!GetOverlappedResult(hCom, &osReader, &drRead, FALSE))
//				log("Overlap Error \n");				// Error in communications; report it.
//			else
//			{
//				// Read completed successfully.
//				for(int i=0; i<(int)drRead;i++)
//					log("Received: %c \n ");
//			}
//
//			//HandleASuccessfulRead(lpBuf, dwRead);
//
//			//  Reset flag so that another opertion can be issued.
//			fWaitingOnRead = FALSE;
//			break;
//
//		case WAIT_TIMEOUT:
//			// Operation isn't complete yet. fWaitingOnRead flag isn't
//			// changed since I'll loop back around, and I don't want
//			// to issue another read until the first one finishes.
//			//
//			// This is a good time to do some background work.
//			log("Read Timeout Occur !!!! \n");
//			break;
//
//		default:
//			// Error in the WaitForSingleObject; abort.
//			// This indicates a problem with the OVERLAPPED structure's
//			// event handle.
//			break;
//		}
//	}
//
//}
//
//void ComponentAction::char_recieve(){
//	char * lpBuf;
//	if (!fWaitingOnRead)
//	{
//		if (!ReadFile(hCom, lpBuf, 1, &drRead, &osReader))
//		{
//			int check =GetLastError();
//			if (GetLastError() != ERROR_IO_PENDING)     // read not delayed?
//				log("Read error !=ERROR_IO_PENDING : %d \n");
//			else
//			{
//				log("IO_PENDING \n");
//				fWaitingOnRead = TRUE;
//			}
//		}
//		else if(lpBuf[0]!=0)
//		{
//			log("Received: %c \n ");
//		}
//		processReadResult(lpBuf);
//	} else {
//		drRes = WaitForSingleObject(osReader.hEvent, READ_TIMEOUT);
//		switch(drRes){
//			// Read completed.
//		case WAIT_OBJECT_0:
//			if (!GetOverlappedResult(hCom, &osReader, &drRead, FALSE)){
//				log("Overlap Error \n");				// Error in communications; report it.
//			} else {
//					log("Received: %c \n ");
//			}
//
//			//HandleASuccessfulRead(lpBuf, dwRead);
//
//			//  Reset flag so that another opertion can be issued.
//			fWaitingOnRead = FALSE;
//			break;
//
//		case WAIT_TIMEOUT:
//			// Operation isn't complete yet. fWaitingOnRead flag isn't
//			// changed since I'll loop back around, and I don't want
//			// to issue another read until the first one finishes.
//			//
//			// This is a good time to do some background work.
//			log("Read Timeout Occur !!!! \n");
//			break;
//
//		default:
//			// Error in the WaitForSingleObject; abort.
//			// This indicates a problem with the OVERLAPPED structure's
//			// event handle.
//			break;
//		}
//	}
//
//}

void ComponentAction::processReadResult(){
	TStrings *s = regexMap(returnResult, operation->returnTemplate);
	for (int i = 0; i < s->Count; i++) {
		parseResult[i] = (*s)[i];
	}

}

ComponentAction::ComponentAction(){
}
