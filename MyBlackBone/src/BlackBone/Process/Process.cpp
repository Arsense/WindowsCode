#include "Process.h"





namespace blackbone
{


Process::Process() : _core()
{

}

Process::~Process(void)
{	

}

NTSTATUS Process::Attach(DWORD Pid, DWORD Access /*= DEFAULT_ACCESS_P*/)
{
	Detach();

	auto status = _core.Open(Pid,  Access);
	if (NT_SUCCESS(status))
	{
		//_nativeLdr.Init();
		//status = _remote.CreateRPCEnvironment(false, false);
	}

	return status;
}



NTSTATUS Process::Detach()
{
	// Reset data
	

	return STATUS_SUCCESS;
}


}
