#include <Windows.h>

#define LOG_TYPE_CONSOLE	0x8000
#define LOG_TYPE_FILE		0x8001
#define LOG_TYPE_MSGBOX		0x8002
#define LOG_TYPE_NULL		0x8003

#define LOG_LEVEL_ERROR		0x7000
#define LOG_LEVEL_WARNING	0x7001
#define LOG_LEVEL_INFORM	0x7002

DWORD DbgInit(int LogType, LPSTR LogFileName, bool Append);
bool DbgLog(int LogLevel, LPCSTR Format,...);