//---------------------------------------------------------------------------

#ifndef actionH
#define actionH
//---------------------------------------------------------------------------

#include <vcl.h>

const int CTYPE_COMPORT = 0;
const int CTYPE_VALVE = 1;
const int CTYPE_TEMPERATURE = 2;
const int CTYPE_PRESSURE = 3;
const int CTYPE_FCL = 4;
const int CTYPE_FLOWMETER = 5;
const int CTYPE_ANALYZER = 6;

const int OPER_OPEN = 1;
const int OPER_CLOSE = 2;
const int OPER_READ = 3;
const int OPER_WRITE = 4;

const int PROC_STATUS_START = 1;
const int PROC_STATUS_END = 2;
const int PROC_STATUS_ERR = 3;


const int RESULT_SUCC = 0;
const int ERR_OPEN_PORT = 1;
const int ERR_SET_PORT = 2;
const int ERR_READ_PORT = 3;
const int ERR_WRITE_PORT = 4;

typedef struct {
	int type;
	String name;
	DCB *dcb;
	COMMTIMEOUTS timeoutSetting;
	String port;
	String para[];
} Component;

typedef struct {
	int type;
	String desc;
	int	   interval;
	String commandTemplate;
	String commandPara[6];
	String returnTemplate;
	String returnPara[6];
	bool   checkSum;
} Operation;

class Action {
	private:
        int status;
	protected:

//		virtual int init();
//		void log();
//		virtual void log(String str);

	public:
		Component *component;
		Operation *operation;
		virtual int execute();

};

class SleepAction : public Action{
	protected:
		int execute();


};

class ComponentAction : public Action {
	private:
		void setDCB(DCB *dcb);
		static OVERLAPPED osReader;
		static OVERLAPPED osWrite;

		static DWORD drRead;
		static DWORD drRes;
		static BOOL fWaitingOnRead;

		static DWORD dwWritten;
		static DWORD dwRes;
		DWORD READ_BUF_SIZE;
		DWORD READ_TIMEOUT;
	protected:
		HANDLE hCom;
		int openComPort();
		int closeComPort();
		String sendCommand();
		//void recieve();
		//void char_recieve();
		void buildCommand();
		virtual void processReadResult();
	public:
		unsigned char* command;
		String command_str;
		DWORD command_size;
		String returnResult;
		String parseResult[6];
		int execute();
		ComponentAction();

};


#endif

