#include <stdio.h>
#include <Windows.h>
#include "pe-parse.h"
#define NOT_ENOUGH_ARGUMENTS -1


int main(int argc, char** argv)
{
	DWORD dwStatus;

	if(argc == 1)
		return -1;

	HANDLE hPE = CreateFile((LPCSTR) argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hPE == INVALID_HANDLE_VALUE)
	{
		dwStatus = GetLastError();
		printf("[x] Failed to open file: %s; Code: %08X\n", argv[1],dwStatus);
		return dwStatus;
	}
	ProcessHeaders(hPE);
	PRELOCATION relocs = ProcessRelocations(hPE);
}