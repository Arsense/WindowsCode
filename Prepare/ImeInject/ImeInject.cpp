#include "stdafx.h"


#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

int __cdecl main(int argc, char **argv)
{
	HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (h != INVALID_HANDLE_VALUE) {
		THREADENTRY32 te;
		te.dwSize = sizeof(te);
		if (Thread32First(h, &te)) {
			do {
				if (te.dwSize >= FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) +
					sizeof(te.th32OwnerProcessID)) {
					printf("Process 0x%04x Thread 0x%04x\n",
						te.th32OwnerProcessID, te.th32ThreadID);
				}
				te.dwSize = sizeof(te);
			} while (Thread32Next(h, &te));
		}
		CloseHandle(h);
	}
	return 0;
}