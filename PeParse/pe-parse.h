#include <Windows.h>

#define VAtoRVA(VAddr, ImageBase) (VAddr - ImageBase)

typedef struct _relocation
{
	DWORD dwVA;
} RELOCATION, *PRELOCATION;

DWORD       ProcessHeaders(HANDLE hFile);
PRELOCATION	ProcessRelocations(HANDLE hFile);