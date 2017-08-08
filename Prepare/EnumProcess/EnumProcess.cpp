// EnumProcess.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<windows.h>

#include<iostream>


#include <winternl.h>

#include <string>
#include <map>
#include "EnumProcess.h"

using namespace std;
#pragma warning(disable:4312)



typedef enum _MEMORY_INFORMATION_CLASS
{
	MemoryBasicInformation,
	MemoryWorkingSetList,
	MemorySectionName
}MEMORY_INFORMATION_CLASS;

typedef
NTSTATUS
(WINAPI *ZWQUERYVIRTUALMEMORY) (
	IN HANDLE ProcessHandle,
	IN PVOID BaseAddress,
	IN MEMORY_INFORMATION_CLASS MemoryInformationClass,
	OUT PVOID MemoryInformation,
	IN ULONG MemoryInformationLength,
	OUT PULONG ReturnLength OPTIONAL
	);


map<wstring, wstring> MapDevice2Path;

void ConvertVolumePaths(
	IN PWCHAR DeviceName,
	IN PWCHAR VolumeName)
{
	DWORD  CharCount = MAX_PATH + 1;
	PWCHAR Names = NULL;
	PWCHAR NameIndex = NULL;
	BOOL   Success = FALSE;


	for (;;)
	{
		// //  Allocate a buffer to hold the paths
		Names = (PWCHAR) new BYTE[CharCount * sizeof(WCHAR)];

		if (!Names)
		{
			//
			//  If memory can't be allocated, return.
			return;
		}

		//
		//  Obtain all of the paths
		//  for this volume.
		Success = GetVolumePathNamesForVolumeNameW(
			VolumeName, Names, CharCount, &CharCount
			);

		if (Success)
		{
			break;
		}

		if (GetLastError() != ERROR_MORE_DATA)
		{
			break;
		}

		//
		//  Try again with the
		//  new suggested size.
		delete[] Names;
		Names = NULL;
	}

	if (Success)
	{
		//
		//  Display the various paths.
		for (NameIndex = Names;
		NameIndex[0] != L'\0';
			NameIndex += wcslen(NameIndex) + 1)
		{
			MapDevice2Path[DeviceName] = NameIndex;
		}
	}

	if (Names != NULL)
	{
		delete[] Names;
		Names = NULL;
	}

	return;


}

BOOL InitialDevice2Path()
{
	BOOL   bOK = FALSE;
	DWORD  CharCount = 0;
	WCHAR  DeviceName[MAX_PATH] = L"";
	DWORD  Error = ERROR_SUCCESS;
	HANDLE FindHandle = INVALID_HANDLE_VALUE;
	BOOL   Found = FALSE;
	size_t Index = 0;
	BOOL   Success = FALSE;
	WCHAR  VolumeName[MAX_PATH] = L"";

	//  Enumerate all volumes in the system.


	FindHandle = FindFirstVolumeW(VolumeName, ARRAYSIZE(VolumeName));

	if (FindHandle == INVALID_HANDLE_VALUE)
	{
		Error = GetLastError();
		wprintf(L"FindFirstVolumeW failed with error code %d\n", Error);
		return bOK;
	}

	for (;;)
	{
		//  Skip the \\?\ prefix and remove the trailing backslash.
		Index = wcslen(VolumeName) - 1;
		if (VolumeName[0] != L'\\' ||
			VolumeName[1] != L'\\' ||
			VolumeName[2] != L'?' ||
			VolumeName[3] != L'\\' ||
			VolumeName[Index] != L'\\')
		{
			Error = ERROR_BAD_PATHNAME;
			wprintf(L"FindFirstVolumeW/FindNextVolumeW returned a bad path: %s\n", VolumeName);
			break;
		}

		//  QueryDosDeviceW doesn't allow a trailing backslash,
		//  so temporarily remove it.


		CharCount = QueryDosDeviceW(&VolumeName[4], DeviceName, ARRAYSIZE(DeviceName));

		VolumeName[Index] = L'\\';

		if (CharCount == 0)
		{
			Error = GetLastError();
			wprintf(L"QueryDosDeviceW failed with error code %d\n", Error);
			break;
		}

		ConvertVolumePaths(DeviceName, VolumeName);

		//
		//  Move on to the next volume.
		Success = FindNextVolumeW(FindHandle, VolumeName, ARRAYSIZE(VolumeName));

		if (!Success)
		{
			Error = GetLastError();

			if (Error != ERROR_NO_MORE_FILES)
			{
				wprintf(L"FindNextVolumeW failed with error code %d\n", Error);
				break;
			}

			//
			//  Finished iterating
			//  through all the volumes.
			Error = ERROR_SUCCESS;
			break;
		}
	}

	FindVolumeClose(FindHandle);
	FindHandle = INVALID_HANDLE_VALUE;

	return bOK;


	}
BOOL EnableDebugPrivilege()
{
	HANDLE TokenHandle;
	TOKEN_PRIVILEGES TokenPriv;
	LUID Luid;



	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &TokenHandle))
	{
		return FALSE;
	}
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &Luid))
	{
		CloseHandle(TokenHandle);
		return FALSE;
	}

	TokenPriv.PrivilegeCount = 1;
	TokenPriv.Privileges[0].Luid = Luid;
	TokenPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!AdjustTokenPrivileges(TokenHandle, FALSE, &TokenPriv, sizeof(TokenPriv), NULL, NULL))
	{
		CloseHandle(TokenHandle);
		return FALSE;
	}

	return TRUE;
}




void DeviceName2PathName(OUT WCHAR* szPathName, IN const WCHAR* szDeviceName)
{
	memset(szPathName, 0, MAX_PATH * 2);
	wstring strDeviceName = szDeviceName;
	size_t pos = strDeviceName.find(L'\\', 9);
	wstring strTemp1 = strDeviceName.substr(0, pos);
	wstring strTemp2 = strDeviceName.substr(pos + 1);
	wstring strDriverLetter = MapDevice2Path[strTemp1];
	wstring strPathName = strDriverLetter + strTemp2;

	wcscpy_s(szPathName, MAX_PATH, strPathName.c_str());
}
/**
* 枚举指定进程加载的模块
* @param dwProcessId 进程Id
* @return void
*/
void EnumProcessModules(IN DWORD ProcessId)
{
	DWORD BeginAddress = 0x00000000;
	BYTE szBuffer[MAX_PATH * 2 + 4] = { 0 };
	WCHAR wModuleName[MAX_PATH] = { 0 };
	WCHAR wPathName[MAX_PATH] = { 0 };
	MEMORY_BASIC_INFORMATION MemoryInformation;
	PUNICODE_STRING usSectionName;
	ZWQUERYVIRTUALMEMORY fnZwQueryVirtualMemory;
	HANDLE ProcessHandle = NULL;


	ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE,ProcessId);

	if (ProcessHandle == NULL)
	{
		wprintf(L"Open Process %d Error\n", ProcessId);
		return;
	}


	fnZwQueryVirtualMemory = (ZWQUERYVIRTUALMEMORY)
		::GetProcAddress(GetModuleHandleA("ntdll.dll"),
			"ZwQueryVirtualMemory");

	if (fnZwQueryVirtualMemory)
	{
		do
		{
			if (fnZwQueryVirtualMemory(
				ProcessHandle,
				(PVOID)BeginAddress,
				MemoryBasicInformation,
				&MemoryInformation,
				sizeof(MemoryInformation),
				0) >= 0)
			{
				if (MemoryInformation.Type == MEM_IMAGE)
				{
					if (fnZwQueryVirtualMemory(
						ProcessHandle,
						(PVOID)BeginAddress,
						MemorySectionName,
						szBuffer,
						sizeof(szBuffer),
						0) >= 0)
					{
						usSectionName = (PUNICODE_STRING)szBuffer;
						if (_wcsnicmp(wModuleName, usSectionName->Buffer, usSectionName->Length / sizeof(WCHAR)))
						{
							wcsncpy_s(wModuleName, usSectionName->Buffer, usSectionName->Length / sizeof(WCHAR));
							wModuleName[usSectionName->Length / sizeof(WCHAR)] = UNICODE_NULL;
							DeviceName2PathName(wPathName,wModuleName);
							wprintf(L"[0x%.8x]\t%s\n", BeginAddress, wPathName);
						}
					}
				}

			}
			// 递增基址,开始下一轮查询!
			BeginAddress += 0x1000;
		} while (BeginAddress < 0x80000000);
	}

	CloseHandle(ProcessHandle);
}






int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwProcessId = 4;

	if (argc != 2)
	{
		wprintf(L"usage:CheckDll ProcessId");
		return 1;
	}

	dwProcessId = _ttoi(argv[1]);
	//初始化什么设备  原理不懂
	InitialDevice2Path();
	
	// 首先提示权限
	if (EnableDebugPrivilege())
	{
		//枚举所有模块
		EnumProcessModules(dwProcessId);
	}

	MapDevice2Path.clear();
	
    return 0;
}

