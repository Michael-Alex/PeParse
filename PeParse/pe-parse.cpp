#include <Windows.h>
#include <WinNT.h>
#include "pe-parse.h"
#include "dbg-utils.h"

PIMAGE_DOS_HEADER DosHeader;
PIMAGE_NT_HEADERS NtHeaders;

DWORD ProcessHeaders(HANDLE hFile){
	DWORD status= ERROR_SUCCESS;

	HANDLE hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if(hFileMapping == INVALID_HANDLE_VALUE)
	{
		status = GetLastError();
		DbgLog(LOG_LEVEL_ERROR, "Error in CreateFileMapping. Code %08X\n", status);
		return status;
	}

	DWORD FileSize = 0;
	status = GetFileSize(hFileMapping, &FileSize);
	LPVOID ImageBase = MapViewOfFile(hFileMapping, GENERIC_READ, 0, 0, FileSize);

	if(ImageBase == NULL)
	{
		status = GetLastError();
		DbgLog(LOG_LEVEL_ERROR, "Error in MapViewOfFile. Code %08X\n", status);
		return status;
	}

	DosHeader = (PIMAGE_DOS_HEADER)ImageBase;
	if(DosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		DbgLog(LOG_LEVEL_WARNING,"File is not a valid PE");

	NtHeaders = (PIMAGE_NT_HEADERS)((LONG)ImageBase + DosHeader->e_lfanew);
	IMAGE_OPTIONAL_HEADER32 OptionalHeaders = (IMAGE_OPTIONAL_HEADER32)NtHeaders->OptionalHeader;

}