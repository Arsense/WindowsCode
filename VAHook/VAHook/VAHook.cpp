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

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

