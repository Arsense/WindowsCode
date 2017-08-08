#pragma once
#include <memory>

#include<windows.h>

namespace blackbone
{
	class ProcessCore
	{

		friend class Process;
private:
		ProcessCore();
		~ProcessCore();
		NTSTATUS Open(DWORD Pid, DWORD Access);
		void Close();
private:
		HANDLE    _hProcess = NULL; // Process handle
		DWORD     _pid = 0;         // Process ID
		

	};
}
