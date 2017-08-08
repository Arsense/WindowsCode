// CreateToolhelp32Snapshot.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<windows.h>
#include <TlHelp32.h>
#include<stdio.h>
#include<psapi.h>
#pragma comment(lib,"psapi.lib")

int main()
{
	//进程结构
	PROCESSENTRY32 Pe32;  
	//用之前要知道大小
	Pe32.dwSize = sizeof(Pe32);
	//创建进程快照
	HANDLE ProcessSnapHandle=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,
		0);
	HANDLE ModuleSnapHandle = NULL;
	if (ProcessSnapHandle == INVALID_HANDLE_VALUE)
	{
		printf("[-]ProcessSnapHandle Error!\r\n");
		int Error = GetLastError();
		printf("Error is : %d\r\n", Error);
		return -1;
	}
	BOOL NextProcess = Process32First(ProcessSnapHandle,&Pe32);

	HANDLE ProcessHandle = 0;
	WCHAR ProcessPath[MAX_PATH] = { 0 };
	MODULEENTRY32 pModule;  //模块的结构

	pModule.dwSize = sizeof(MODULEENTRY32);
	BOOL Return = FALSE;
	//准备好了  开始遍历
	while (NextProcess)
	{
		//先打开进程对象得到句柄
		ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pe32.th32ParentProcessID);
		//得到模块的路径
		GetModuleFileNameEx(ProcessHandle, NULL, ProcessPath, _MAX_PATH);
		wprintf(_T("ProcessPath:%s\n ProcessName : %s\t\t ProcessID : %d\n\n"), ProcessPath, Pe32.szExeFile, Pe32.th32ProcessID);

		//创建模块的快照
		ModuleSnapHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,
			Pe32.th32ProcessID);

		Return = Module32First(ModuleSnapHandle, &pModule);

		while (Return)
		{
			//枚举输出
			wprintf(_T("\t\tModual:%s\tBase:%2x\n"), pModule.szExePath, pModule.modBaseAddr);
			Return = ::Module32Next(ModuleSnapHandle, &pModule);

		}

		CloseHandle(ModuleSnapHandle);
		NextProcess = Process32Next(ProcessSnapHandle, &Pe32);
	}
	CloseHandle(ProcessSnapHandle);
    return 0;
}

