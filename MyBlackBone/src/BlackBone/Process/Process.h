#pragma once
#include"../Config.h"
#include"ProcessCore.h"
#include<windows.h>

namespace blackbone
{
#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif
#define STATUS_SUCCESS                   ((NTSTATUS)0x00000000L)    // ntsubauth


#define DEFAULT_ACCESS_P  PROCESS_QUERY_INFORMATION | \
                          PROCESS_VM_READ           | \
                          PROCESS_VM_WRITE          | \
                          PROCESS_VM_OPERATION      | \
                          PROCESS_CREATE_THREAD     | \
                          PROCESS_SET_QUOTA         | \
                          PROCESS_TERMINATE         | \
                          PROCESS_SUSPEND_RESUME    | \
                          PROCESS_DUP_HANDLE


class Process
{
public:
		// BLACKBONE_API  自定义的导出
		BLACKBONE_API Process();
		BLACKBONE_API ~Process(void);


		/// 链接上一个现有的线程
		BLACKBONE_API NTSTATUS Attach(DWORD Pid, DWORD Access = DEFAULT_ACCESS_P);
		//断开重新连接
		BLACKBONE_API NTSTATUS Detach();

		Process(const Process&) = delete;
		Process& operator =(const Process&) = delete;
private:
	ProcessCore     _core;          //核心程序和本机
	};



}