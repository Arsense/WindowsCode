#pragma once
#include<windows.h>



void ConvertVolumePaths(IN PWCHAR DeviceName, IN PWCHAR VolumeName);

BOOL InitialDevice2Path();

BOOL EnableDebugPrivilege();

void DeviceName2PathName(OUT WCHAR * szPathName, IN const WCHAR * szDeviceName);

void EnumProcessModules(IN DWORD ProcessId);
