#include"dbg-utils.h"
#include "errors.h"
#include<stdio.h>
#include<stdarg.h>

FILE* LogFile;
int LogType = 0;

char	LogPrefixStr[3][4]= {"[X]", "[!]", "[*]"};
DWORD	LogMsgIcons[3] = {MB_ICONERROR, MB_ICONASTERISK, MB_ICONINFORMATION};
char	LogMsgTitle[3][12] = {"Error...", "Warning...", "Status..."};

DWORD DbgInit(int type, LPSTR lpFileName, bool Append)
{
	if (LogType == LOG_TYPE_FILE)
	{	
		if(lpFileName == NULL)
			return ERROR_INVALID_FILE;

		DWORD flags = CREATE_ALWAYS | ((!Append)? TRUNCATE_EXISTING : 0);
		LogFile = fopen(lpFileName, (Append)? "a": "w");
		if(LogFile == NULL)
			return ERROR_INVALID_FILE;
	}
	LogType = type;
	return ERROR_SUCCESS;
}

bool DbgLog(int LogLevel, LPSTR Format, ...)
{
	if(LogType == 0)
		return false;

	va_list argumnets;
	int index = LogLevel ^ 0x7000;
	char Message[120];
	FILE* dest = stdout;

	switch(LogType)
	{
	case LOG_TYPE_NULL:	break;

	case LOG_TYPE_MSGBOX:
		vsprintf(Message, Format, argumnets);
		MessageBox(NULL, (LPCSTR) Message, (LPCSTR) LogMsgTitle[index], LogMsgIcons[index]);
		break;

	case LOG_TYPE_FILE:
		if (LogFile == NULL)
			return false;
		dest = LogFile;
	case LOG_TYPE_CONSOLE:
		vsprintf(Message,Format,argumnets);
		fprintf(dest, "%s %s\n", LogPrefixStr[index], Message);
		break;
	}
	return true;
}