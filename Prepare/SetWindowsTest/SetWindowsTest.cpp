// SetWindowsTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <windows.h>
int test()
{
	char str[80];
	/*
	Get's the current process id to display in the message box
	*/
	int id = GetCurrentProcessId();
	sprintf(str, "Hello, process: %d", id);
	MessageBox(NULL, (LPCWSTR)str, L"Hello DLL!", MB_OK);
	return 0;
}
int main()
{
	test();
    return 0;
}

