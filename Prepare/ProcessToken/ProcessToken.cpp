// ProcessToken.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<windows.h>
#include<iostream>
using namespace std;
VOID TestProcessToken();
int main()
{
	TestProcessToken();
    return 0;
}



VOID TestProcessToken()
{
	BOOL fResult;
	TOKEN_PRIVILEGES tkp;
	HANDLE hToken;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		printf("OpenProcessToken failed!"); //获得进程句柄失败
	}
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); //获得本地机唯一的标识
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0); //调整获得的权限
	if (GetLastError() != ERROR_SUCCESS)
	{
		printf("AdjustTokenPrivileges enable failed!"); //修改权限失败
	}
	fResult = InitiateSystemShutdown(
		NULL, // 要关的计算机用户名
		L"由于系统不稳定，WINDOWS将在上面的时间内关机，请做好保存工作!", // 显示消息
		0, // 关机所需的时间
		FALSE, // 是否提示用户
		FALSE //设为TRUE为重起，设为FALSE为关机

		);
}