// TestApp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"Test.h"



int main(int /*argc*/, char* /*argv*/[])
{
	Process GetProcess;
	GetProcess.Attach(GetCurrentProcessId());




    return 0;
}

