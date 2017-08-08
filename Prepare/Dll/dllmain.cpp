// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

#include<windows.h>

#ifdef __cplusplus
extern "C"
{
#endif	


__declspec (dllexport) void InjectFunc(void);

#ifdef  __cplusplus
}
#endif

void InjectFunc(void)
{
	MessageBoxA(NULL, "Dll export Inject Success", "Dll Inject", MB_OKCANCEL);
}






BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		MessageBoxA(NULL, "the simple inject success", "Dll Inject", MB_OKCANCEL);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

