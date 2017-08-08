#include "Process.h"




Process::Process() : _core()
{

}

Process::~Process(void)
{	

}

NTSTATUS Process::Attach(DWORD Pid, DWORD Access /*= DEFAULT_ACCESS_P*/)
{
	Detach();

	auto Status = _core.Open(Pid,  Access);
	if (NT_SUCCESS(Status))
	{
		//_nativeLdr.Init();
		//status = _remote.CreateRPCEnvironment(false, false);
	}

	return Status;
}


NTSTATUS Process::Detach()
{
	// Reset data

	return STATUS_SUCCESS;
}



