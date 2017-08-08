// SetWindowsEx.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<windows.h>
#include<iostream>

using namespace std;


int main()
{
	//加载DLL
	HMODULE Dll = LoadLibrary(L"Inject.dll");
	if (!Dll)
	{
		printf("Cannot fing Dll\r\n");
		getchar();
		return FALSE;
	}
	//得到HOOK函数名
	HOOKPROC Address = (HOOKPROC)GetProcAddress(Dll, "Inject");
	if (Address = NULL)
	{
		printf("Cannot find function");
		getchar();
		return FALSE;
	}
	//把HOOK加载到HOOK链中
	//参数设置为0表示监视全局线程
	HHOOK HookHandle = SetWindowsHookEx(WH_KEYBOARD, Address, Dll, 0);
	if (HookHandle == NULL)
	{
		printf("Couldn't hook the keyboard");
	}
	printf("Hooked the program, hit enter to exit");
	getchar();
	UnhookWindowsHookEx(HookHandle);

    return 0;
}

