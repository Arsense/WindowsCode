
#include "../Config.h"
#include "ProcessCore.h"


namespace blackbone
{
	ProcessCore::ProcessCore()
	{
		//LOAD_IMPORT("GetProcessDEPPolicy", L"kernel32.dll");

	}
	ProcessCore::~ProcessCore()
	{
		//Close();
	}
//连接到已有的进程
	NTSTATUS ProcessCore::Open(DWORD Pid, DWORD Access)
	{
		//防止句柄泄漏 所以先关闭一下
		Close();
		//不同地处理当前进程
		return 1;
	}


//关闭句柄 指针
	void ProcessCore::Close()
	{
		if (_hProcess)
		{
			CloseHandle(_hProcess);

			_hProcess = NULL;
			_pid = 0;
			//_native.reset(nullptr);
		}
	}



}