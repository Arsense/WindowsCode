// ImportInjection.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<windows.h>
#include<iostream>
#include"ImportInjection.h"
using namespace std;


BOOL AddNewImportTableDetails(LPCTSTR PEFilePath, char* InjectionDllName, char* ImportFuncName)
{
	BOOL bSuccess = FALSE;
	LPVOID pModuleHandle = NULL;
	LPBYTE pData = NULL;
	HANDLE FileHandle = INVALID_HANDLE_VALUE, MappingHandle = INVALID_HANDLE_VALUE;
	PIMAGE_NT_HEADERS pNtHeader = NULL;
	PIMAGE_IMPORT_DESCRIPTOR pImportTable = NULL;
	PIMAGE_SECTION_HEADER    pSectionHeader = NULL;

	__try
	{
		//pe文件映射到内存
		FileHandle = CreateFile(
			PEFilePath,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);
		if (INVALID_HANDLE_VALUE == FileHandle)
		{
			OutputDebugString(L"[-] AddNewImportTableDetails CreateFile fail!\n");
			goto _EXIT_;
		}

		DWORD dwFileSize = GetFileSize(FileHandle, NULL);
		MappingHandle = CreateFileMapping(FileHandle, NULL, PAGE_READWRITE/* | SEC_IMAGE*/, 0, dwFileSize, L"WINSUN_MAPPING_FILE");
		if (NULL == MappingHandle)
		{

			OutputDebugString(L"[-] AddNewImportTableDetails CreateFileMapping fail!\n");
			goto _EXIT_;

		}

		pModuleHandle = MapViewOfFile(MappingHandle, FILE_MAP_ALL_ACCESS, 0, 0, dwFileSize);
		if (NULL == pModuleHandle)
		{
			OutputDebugString(L"[-] AddNewImportTableDetails MapViewOfFile fail!\n");
			goto _EXIT_;
		}

		pData = (LPBYTE)pModuleHandle;
		//判断是否是PE
		if (((PIMAGE_DOS_HEADER)pData)->e_magic != IMAGE_DOS_SIGNATURE)
		{
			OutputDebugString(L"[-] AddNewImportTableDetails PE Header MZ error!\n");
			goto _EXIT_;
		}

		pNtHeader = (PIMAGE_NT_HEADERS)(pData + ((PIMAGE_DOS_HEADER)(pData))->e_lfanew);
		if (pNtHeader->Signature != IMAGE_NT_SIGNATURE)
		{
			OutputDebugString(L"[-] AddNewImportTableDetails PE Header PE error!\n");
			goto _EXIT_;
		}

		//根据偏移得到导入表
		pImportTable = (PIMAGE_IMPORT_DESCRIPTOR)(pData + RVA2Offset(pNtHeader, pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress));
		BOOL bBoundImport = FALSE;
		if (pImportTable->Characteristics == 0 && pImportTable->FirstThunk != 0)
		{
			bBoundImport = TRUE;
			pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size = 0;
			pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress = 0;
		}

		pSectionHeader = (PIMAGE_SECTION_HEADER)(pNtHeader + 1) + pNtHeader->FileHeader.NumberOfSections - 1;
		PBYTE pNewSection = pSectionHeader->PointerToRawData + pData;
		int i = 0;
		while (pImportTable->FirstThunk != 0)
		{
			//偏移量是20
			memcpy(pNewSection, pImportTable, sizeof(IMAGE_IMPORT_DESCRIPTOR));
			pImportTable++;
			pNewSection += sizeof(IMAGE_IMPORT_DESCRIPTOR);
			i++;
		}
		//把导入表里面的内容拷贝到申请的节中
		memcpy(pNewSection, (pNewSection - sizeof(IMAGE_IMPORT_DESCRIPTOR)), sizeof(IMAGE_IMPORT_DESCRIPTOR));


		//减的是什么长度
		DWORD dwDelt = pSectionHeader->VirtualAddress - pSectionHeader->PointerToRawData;

		//avoid import not need table
		PIMAGE_THUNK_DATA pImgThunkData = (PIMAGE_THUNK_DATA)(pNewSection + sizeof(IMAGE_IMPORT_DESCRIPTOR) * 2);



		//import dll name
		PBYTE pDllNamePosition = (PBYTE)(pImgThunkData + 2);
		memcpy(pDllNamePosition, InjectionDllName, strlen(InjectionDllName));
		pDllNamePosition[strlen(InjectionDllName)] = 0;

		//确定IMAGE_IMPORT_BY_NAM的位置
		PIMAGE_IMPORT_BY_NAME pImgImportByName = (PIMAGE_IMPORT_BY_NAME)(pDllNamePosition + strlen(InjectionDllName) + 1);


		//init IMAGE_THUNK_DATA
		pImgThunkData->u1.Ordinal = dwDelt + (DWORD)pImgImportByName - (DWORD)pData;


		//init IMAGE_IMPORT_BY_NAME
		pImgImportByName->Hint = 1;
		memcpy(pImgImportByName->Name, ImportFuncName, strlen(ImportFuncName)); 
		//== dwDelt + (DWORD)pszFuncNamePosition - (DWORD)lpData ;
		pImgImportByName->Name[strlen(ImportFuncName)] = 0;
		//init OriginalFirstThunk
		if (bBoundImport)
		{
			((PIMAGE_IMPORT_DESCRIPTOR)pNewSection)->OriginalFirstThunk = 0;
		}
		else
			((PIMAGE_IMPORT_DESCRIPTOR)pNewSection)->OriginalFirstThunk = dwDelt + (DWORD)pImgThunkData - (DWORD)pData;
		//init FirstThunk
		((PIMAGE_IMPORT_DESCRIPTOR)pNewSection)->FirstThunk = dwDelt + (DWORD)pImgThunkData - (DWORD)pData;
		//init Name
		((PIMAGE_IMPORT_DESCRIPTOR)pNewSection)->Name = dwDelt + (DWORD)pDllNamePosition - (DWORD)pData;

		//改变导入表  改成我们创建节位置存放的导入表
		pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress = pSectionHeader->VirtualAddress;
		pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size = (i + 1)*sizeof(IMAGE_IMPORT_DESCRIPTOR);





	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		OutputDebugString(L"[-] AddNewImportDescriptor  Exception!\n");
		return false;

	}
_EXIT_:

	if (FileHandle)
	{
		CloseHandle(FileHandle);
	}

	if (pModuleHandle)
	{
		UnmapViewOfFile(pModuleHandle);
	}

	if (MappingHandle)
	{
		CloseHandle(MappingHandle);
	}
	return TRUE;

}


BOOL AddImportTable(LPCTSTR FullFilePath, char* InjectionDllName, char* FuncName)
{
	BOOL bSuccess = FALSE;
	try
	{
		//增加一个节
		bSuccess = AddNewSection(FullFilePath, 256);
		if (!bSuccess)
		{
			MessageBoxA(NULL, "Add new section fail", "error!", MB_OK);
			return bSuccess;
		}
		//增加一个导入表
		AddNewImportTableDetails(FullFilePath,InjectionDllName,FuncName);
	}
	catch (...)
	{
		return bSuccess;
	}

}
//对齐原理 除法 多的因保留整数被去掉
DWORD PEAlign(DWORD dwTarNum, DWORD dwAlignTo)
{
	return(((dwTarNum + dwAlignTo - 1) / dwAlignTo)*dwAlignTo);
}


BOOL AddNewSection(LPCTSTR pModulePath, DWORD dwNewSectionSize)
{
	bool   bSuccess = FALSE;
	LPVOID pModuleAddress = NULL;
	LPBYTE pData = NULL;
	HANDLE FileHandle = INVALID_HANDLE_VALUE;
	HANDLE	MappingHandle = INVALID_HANDLE_VALUE;
	PIMAGE_NT_HEADERS pNtHeader = NULL;
	PIMAGE_SECTION_HEADER pNewSection = NULL, pLastSection = NULL;

	OutputDebugString(L"[!] AddNewSection Enter!\n");
	
	//TODO:可能还涉及关闭windows文件保护
	__try
	{
		//pe文件映射到内存  后面操作为了找到PE文件的基地址

			FileHandle= CreateFile(
			pModulePath,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);
			if (INVALID_HANDLE_VALUE == FileHandle)
			{
				OutputDebugString(L"[-] AddNewSection CreateFile fail!\n");
				goto _EXIT_;
			}
			//50688
			DWORD dwFileSize = GetFileSize(FileHandle, NULL);
			MappingHandle = CreateFileMapping(FileHandle, NULL, PAGE_READWRITE/* | SEC_IMAGE*/, 0, dwFileSize, L"WINSUN_MAPPING_FILE");
			if (NULL == MappingHandle)
			{

				OutputDebugString(L"[-] AddNewSection CreateFileMapping fail!\n");
				goto _EXIT_;
			}

			pModuleAddress = MapViewOfFile(MappingHandle, FILE_MAP_ALL_ACCESS, 0, 0, dwFileSize);
			if (NULL == pModuleAddress)
			{
				OutputDebugString(L"[-] AddNewSection MapViewOfFile fail!\n");
				goto _EXIT_;;
			}
			//得到PE文件入口基地址
			pData = (LPBYTE)pModuleAddress;

			if (((PIMAGE_DOS_HEADER)pData)->e_magic != IMAGE_DOS_SIGNATURE)
			{
				OutputDebugString(L"[-] AddNewSection PE Header MZ error!\n");
				goto _EXIT_;;
			}
			//根据DOS头定位到NT头
			pNtHeader = (PIMAGE_NT_HEADERS)(pData + ((PIMAGE_DOS_HEADER)(pData))->e_lfanew);
			if (pNtHeader->Signature != IMAGE_NT_SIGNATURE)
			{
				OutputDebugString(L"[-] AddNewSection PE Header PE error!\n");
				goto _EXIT_;
			}
			//判断是否可以超出节表的范围，能否增加一个新节
			if (((pNtHeader->FileHeader.NumberOfSections + 1) * sizeof(IMAGE_SECTION_HEADER)) > (pNtHeader->OptionalHeader.SizeOfHeaders))
			{
				OutputDebugString(L"[-] AddNewSection cannot add a new section!\n");
				goto _EXIT_;
			}
			pNewSection = (PIMAGE_SECTION_HEADER)(pNtHeader + 1) + pNtHeader->FileHeader.NumberOfSections;
			
			pLastSection = pNewSection - 1;

			DWORD rsize, vsize, roffset, voffset;
			//对齐偏移和RVA  rsize512
			rsize = PEAlign(dwNewSectionSize,
				pNtHeader->OptionalHeader.FileAlignment);
			//50688
			roffset = PEAlign(pLastSection->PointerToRawData + pLastSection->SizeOfRawData,
				pNtHeader->OptionalHeader.FileAlignment);
			//RVA页大小对齐4096
			vsize = PEAlign(dwNewSectionSize,
				pNtHeader->OptionalHeader.SectionAlignment);
			//135168
			voffset = PEAlign(pLastSection->VirtualAddress + pLastSection->Misc.VirtualSize,
				pNtHeader->OptionalHeader.SectionAlignment);


			//填充新节表的名字，地址 偏移 大小等基本信息
			memcpy(pNewSection->Name, "WINSUN", strlen("WINSUN"));
			pNewSection->VirtualAddress = voffset;
			pNewSection->PointerToRawData = roffset;
			pNewSection->Misc.VirtualSize = vsize;
			pNewSection->SizeOfRawData = rsize;
			pNewSection->Characteristics = IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE;


			//修改IMAGE_NT_HEADERS，增加新节表
			pNtHeader->FileHeader.NumberOfSections++;
			pNtHeader->OptionalHeader.SizeOfImage += vsize;
			pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size = 0;
			pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress = 0;

			//增加新节到文件尾部
			DWORD dwWriteBytes;
			SetFilePointer(FileHandle, 0, 0, FILE_END);
			PBYTE pbNewSectionContent = new BYTE[rsize];
			ZeroMemory(pbNewSectionContent, rsize);
			bSuccess = WriteFile(FileHandle, pbNewSectionContent, rsize, &dwWriteBytes, NULL);
			if (!bSuccess)
			{
				MessageBox(NULL,L"新增节失败", L"error", MB_OK);
				goto _EXIT_;
			}

	}




	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		OutputDebugString(L"[-] AddImportTableItem  Exception!\n");
		return false;
	}
	OutputDebugString(L"[!] AddNewSection Exit!\n");
	bSuccess = TRUE;
_EXIT_:

			if (FileHandle)
			{
				CloseHandle(FileHandle);
			}

			if (pModuleAddress)
			{
				UnmapViewOfFile(pModuleAddress);
			}

			if (MappingHandle)
			{
				CloseHandle(MappingHandle);
			}
			return true;




	


}



//
// calulates the Offset from a RVA
// Base    - base of the MMF
// dwRVA - the RVA to calculate
// returns 0 if an error occurred else the calculated Offset will be returned
DWORD RVA2Offset(PIMAGE_NT_HEADERS pImgNTHeader, DWORD dwRVA)
{
	DWORD _offset;
	PIMAGE_SECTION_HEADER section;
	section = ImageRVA2Section(pImgNTHeader, dwRVA);//ImageRvaToSection(pimage_nt_headers,Base,dwRVA);
	if (section == NULL)
	{
		return(0);
	}
	_offset = dwRVA + section->PointerToRawData - section->VirtualAddress;
	return(_offset);
}


//
PIMAGE_SECTION_HEADER ImageRVA2Section(PIMAGE_NT_HEADERS pImgNTHeader, DWORD dwRVA)
{
	int i;
	PIMAGE_SECTION_HEADER pSectionHeader = (PIMAGE_SECTION_HEADER)(pImgNTHeader + 1);
	for (i = 0; i<pImgNTHeader->FileHeader.NumberOfSections; i++)
	{
		if ((dwRVA >= (pSectionHeader + i)->VirtualAddress) && (dwRVA <= ((pSectionHeader + i)->VirtualAddress + (pSectionHeader + i)->SizeOfRawData)))
		{
			return ((PIMAGE_SECTION_HEADER)(pSectionHeader + i));
		}
	}
	return(NULL);
}

int main()
{
	AddImportTable(L"ImportInjection.exe", "Dll.dll", "InjectFunc");
    return 0;
}

