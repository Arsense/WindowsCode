#pragma once

BOOL AddNewImportTableDetails(LPCTSTR PEFilePath, char * InjecttionDllName, char * ImportFuncName);

BOOL AddImportTable(LPCTSTR FullFilePath, char * InjectionDllName, char * FuncName);

DWORD PEAlign(DWORD dwTarNum, DWORD dwAlignTo);

BOOL AddNewSection(LPCTSTR pModulePath, DWORD dwNewSectionSize);

DWORD RVA2Offset(PIMAGE_NT_HEADERS pImgNTHeader, DWORD dwRVA);

PIMAGE_SECTION_HEADER ImageRVA2Section(PIMAGE_NT_HEADERS pImgNTHeader, DWORD dwRVA);
