
// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"


#include<windows.h>
#include<stdio.h>
#include<stdlib.h>


#pragma comment(lib,"imm32.lib")
#pragma data_seg("mysechx")

#pragma data_seg()


BOOL WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize);
BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize);

BOOL HookFlag;
char IMEString[256] = "";
HWND MainWndHandle = NULL;
char StringBuffer1[256] = "";
char StringBuffer2[256] = "";
UINT WM_HXWDLLWX_QQBTX = NULL;
UINT WM_HXWDLLWX_HOOKKEY = NULL;

class ImeHook
{

private:
	BYTE OldCode[5];
	BYTE NewCode[5];
	BOOL bOk;
	int ImeHookAddress;
public:

	BOOL HookApi(LPCTSTR DllName, LPCTSTR FunctionName, int ImeAddress)
	{
		bOk = FALSE;
		HMODULE ModuleHandle = NULL;
		ModuleHandle = GetModuleHandle(DllName);
		int JmpOffset = 0;
		if (ModuleHandle == NULL)
		{
			return FALSE;
		}
		ImeHookAddress = (int)GetProcAddress(ModuleHandle, (LPCSTR)FunctionName);

		if (ImeHookAddress == NULL)
		{
			return FALSE;
		}
		CopyMemory(OldCode, (const void *)ImeHookAddress, 5);
		NewCode[0] = 0xE9;
		//得出我的DLL到当前DLL地址的偏移
		JmpOffset = ImeAddress - ImeHookAddress - 5;
		CopyMemory(&NewCode[1], &JmpOffset, 4);
		bOk = TRUE;
		HookStatus(true);
		return true;


	}
	BOOL HookStatus(BOOL IsHook)
	{
		DWORD OldAcc, NewAcc;
		if (!bOk) return FALSE;
		if (IsHook)
		{
			//钩过了就卸载
			VirtualProtect((LPVOID*)ImeHookAddress, 5, PAGE_WRITECOPY, &OldAcc);
			CopyMemory((void*)ImeHookAddress, NewCode, 5);
			VirtualProtect((LPVOID*)ImeHookAddress, 5, OldAcc, &NewAcc);

		}
		else
		{
			//钩
			VirtualProtect((LPVOID)ImeHookAddress, 5, PAGE_WRITECOPY, &OldAcc);
			CopyMemory((void *)ImeHookAddress, OldCode, 5);
			VirtualProtect((LPVOID)ImeHookAddress, 5, OldAcc, &NewAcc);
		}
		return TRUE;
	}


};


ImeHook HookA;
ImeHook HookW;


LONG WINAPI HookImmGetCompositionStringA(HIMC hIMC, DWORD Index, LPVOID pBuffer, DWORD BufferLength)
{
	LONG Return = 0;
	LONG TempLength = 0;
	int StringBufferLength = 0;
	if (Index == GCS_RESULTSTR && HookFlag)
	{
		memset(IMEString, 0, 256);
		TempLength = 0;
		HookA.HookStatus(false);
		ImmGetCompositionStringA(hIMC, GCS_RESULTSTR, IMEString, TempLength);
		HookA.HookStatus(TRUE);
		IMEString[TempLength] = 0;

		if (lstrcmp((LPCWSTR)IMEString, (LPCWSTR)StringBuffer1) != 0)
		{
			memset(StringBuffer1, 0, 256);
			lstrcpy((LPWSTR)StringBuffer1, (LPCWSTR)IMEString);
			SendMessage(MainWndHandle, WM_HXWDLLWX_QQBTX, 0, 0);
			memset(StringBuffer2, 0, 256);
			lstrcpy((LPWSTR)StringBuffer2, (LPCWSTR)IMEString);
		}
		if (pBuffer == NULL || BufferLength == 0)
		{
			Return = lstrlen((LPCWSTR)StringBuffer2);
		}
		else
		{
			BufferLength = lstrlen((LPCWSTR)StringBuffer2);
			memset(pBuffer, 0, BufferLength);
			if (BufferLength >= StringBufferLength)
			{
				BufferLength = StringBufferLength;
				BufferLength = StringBufferLength;
			}
			else
			{
				Return = 0;
			}
			memcpy(pBuffer, StringBuffer2, BufferLength);
		}



	}
	else
	{
		HookA.HookStatus(false);
		Return = ImmGetCompositionStringA(hIMC, Index, pBuffer, BufferLength);
		HookA.HookStatus(true);
	}
	return Return;
}

LONG WINAPI HooKImmGetCompositionStringW(HIMC hIMC, DWORD Index, LPVOID pBuffer, DWORD BufferLength)
{

	LONG Return = 0;
	LONG TempLength = 0;
	int StringBufferLength = 0;
	if (Index == GCS_RESULTSTR && HookFlag)
	{
		memset(IMEString, 0, 256);
		TempLength = 0;
		HookW.HookStatus(false);
		ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, IMEString, TempLength);
		HookW.HookStatus(TRUE);
		IMEString[254] = 0;
		IMEString[255] = 0;
		if (lstrcmpW((wchar_t *)IMEString, (wchar_t *)StringBuffer1) != 0)
		{
			memset(StringBuffer1, 0, 256);
			lstrcpyW((wchar_t *)StringBuffer1, (wchar_t *)IMEString);
			WCharToMByte((wchar_t *)StringBuffer1, IMEString, 256);
			SendMessage(MainWndHandle, WM_HXWDLLWX_QQBTX, 0, 0);
			memset(StringBuffer2, 0, 256);
			MByteToWChar(IMEString, (wchar_t *)StringBuffer2, 128);
		}

		if (pBuffer == NULL || BufferLength == 0)
		{
			Return = lstrlenW((wchar_t *)StringBuffer2) * 2;
		}
		else
		{
			BufferLength = lstrlenW((wchar_t *)StringBuffer2) * 2;
			memset(pBuffer, 0, BufferLength);
			if (BufferLength >= StringBufferLength)
			{
				BufferLength = StringBufferLength;
				Return = StringBufferLength;
			}
			else
			{
				Return = 0;
			}
			memcpy(pBuffer, StringBuffer2, BufferLength);
		}


	}

	else
	{
		HookW.HookStatus(false);
		Return = ImmGetCompositionStringW(hIMC, Index, pBuffer, BufferLength);
		HookW.HookStatus(true);
	}
	return Return;

}
BOOL WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize)
{
	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, NULL, 0, NULL, FALSE);
	if (dwSize < dwMinSize)
	{
		return FALSE;
	}
	WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, lpszStr, dwSize, NULL, FALSE);
	return TRUE;
}
BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize)
{
	DWORD dwMinSize;
	dwMinSize = MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, NULL, 0);
	if (dwSize < dwMinSize)
	{
		return FALSE;
	}
	MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);
	return TRUE;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// 注入DLL
			//ImmGetCompositionStringA返回的参数的缓冲区的字节数
			//检索有关组合字符串的信息。就是专门处理输入的函数
			HookA.HookApi(L"imm32.dll", L"ImmGetCompositionStringA", (int)HookImmGetCompositionStringA);
			HookW.HookApi(L"imm32.dll", L"ImmGetCompositionStringW", (int)HooKImmGetCompositionStringW);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		HookA.HookStatus(false);
		HookW.HookStatus(false);

		break;
	}
	return TRUE;
}

