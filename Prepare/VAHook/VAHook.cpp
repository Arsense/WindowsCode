// VAHook.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


class   CTest
{
public:
	int     m_nData;

	virtual void    PrintData()
	{
		printf("Data = 0x%x\n", m_nData);
	}
};


class   CBase1
{
public:
	int     m_nData;

	virtual void PrintData1() = 0;
};


class   CBase2
{
public:
	int     m_nData;

	virtual void PrintData2() = 0;
};

class   CBaseTest : public CBase1, public CBase2
{
public:
	void    PrintData1()
	{
		printf("Data = 0x%x\n", CBase1::m_nData);
	}

	void    PrintData2()
	{
		printf("Data = 0x%x\n", CBase2::m_nData);
	}
};

void    Test()
{
	CTest   oCTest;
	CTest*  pCTest = new CTest();

	pCTest->m_nData = 0x8888;
	pCTest->PrintData();

	oCTest.m_nData = 888;
	oCTest.PrintData();

	delete  pCTest;
}

void    BaseTest()
{
	CBaseTest   oCBaseTest;

	oCBaseTest.PrintData1();
}


int main()
{
	Test();
    return 0;
}

