// BlackBoneTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"../BlackBoneTest/Process/Process.h"

int main()
{
	Process Process;
	Process.Attach(GetCurrentProcessId());


    return 0;
}

