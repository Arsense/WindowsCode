// UsnUpdataDemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <string>
#include <deque>
using namespace std;

#include <set>
#include "UsnUpdataDemo.h"


struct MY_USN_RECORD
{
	DWORDLONG FileReferenceNumber;
	DWORDLONG ParentFileReferenceNumber;
	LARGE_INTEGER TimeStamp;
	DWORD Reason;
	WCHAR FileName[MAX_PATH];
};
HANDLE hVol = INVALID_HANDLE_VALUE;

bool PrintFullPath(const MY_USN_RECORD& mur, const std::deque<MY_USN_RECORD>& con)
{
	if ((mur.FileReferenceNumber & 0x0000FFFFFFFFFFFF) == 5)
		return true;

	std::deque<MY_USN_RECORD>::const_iterator recent = con.end();
	for (std::deque<MY_USN_RECORD>::const_iterator itor = con.begin(); itor != con.end() && itor->TimeStamp.QuadPart <= mur.TimeStamp.QuadPart; ++itor)
	{
		if (itor->FileReferenceNumber == mur.ParentFileReferenceNumber)
			recent = itor;
	}
	if (recent != con.end()) // 它的父目录可能也已被删除，所以要先在记录集中找找
	{
		bool r = PrintFullPath(*recent, con);
		printf("\%S", mur.FileName);
		return r;
	}

	bool GetFullPathByFileReferenceNumber(HANDLE hVol, DWORDLONG FileReferenceNumber);
	bool r = GetFullPathByFileReferenceNumber(hVol, mur.ParentFileReferenceNumber); // 如果记录中没有，再去看看这个文件实际存在否
	if (r)
		printf("\%S", mur.FileName);
	else
		printf("???\%S", mur.FileName);
	return r;
}
bool EnumUsnRecord(const char* drvname, std::deque<MY_USN_RECORD>& con)
{
	bool ret = false;

	char FileSystemName[MAX_PATH + 1];
	DWORD MaximumComponentLength;
	if (GetVolumeInformationA((std::string(drvname) + ":\\").c_str(),0,0,0,&MaximumComponentLength,0,FileSystemName,MAX_PATH+1)
		&& 0 == strcmp(FileSystemName, "NTFS")) // 判断是否为 NTFS 格式
	{
		hVol = CreateFileA((std::string("\\.\\")+drvname+":").c_str() // 需要管理员权限，无奈
			, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

		if (hVol != INVALID_HANDLE_VALUE)
		{
			DWORD br;
			USN_JOURNAL_DATA qujd;
			if (DeviceIoControl(hVol, FSCTL_QUERY_USN_JOURNAL, NULL, 0, &qujd, sizeof(qujd), &br, NULL))
			{
				char buffer[0x1000];
				DWORD BytesReturned;
				{
					READ_USN_JOURNAL_DATA rujd = { 0, -1, 0, 0, 0, qujd.UsnJournalID };
					for (; DeviceIoControl(hVol, FSCTL_READ_USN_JOURNAL, &rujd, sizeof(rujd), buffer, _countof(buffer), &BytesReturned, NULL); rujd.StartUsn = *(USN*)&buffer)
					{
						DWORD dwRetBytes = BytesReturned - sizeof(USN);
						PUSN_RECORD UsnRecord = (PUSN_RECORD)((PCHAR)buffer + sizeof(USN));
						if (dwRetBytes == 0)
						{
							ret = true;
							break;
						}

						while (dwRetBytes > 0)
						{
							MY_USN_RECORD myur = { UsnRecord->FileReferenceNumber, UsnRecord->ParentFileReferenceNumber, UsnRecord->TimeStamp, UsnRecord->Reason };
							memcpy(myur.FileName, UsnRecord->FileName, UsnRecord->FileNameLength);
							myur.FileName[UsnRecord->FileNameLength / 2] = L' ';

							con.push_back(myur);

							dwRetBytes -= UsnRecord->RecordLength;
							UsnRecord = (PUSN_RECORD)((PCHAR)UsnRecord + UsnRecord->RecordLength);
						}
					}
				}
			}

			//CloseHandle( hVol );
		}
	}

	return ret;
}
int main()
{
	// 获得所有变化记录
	std::deque<MY_USN_RECORD> con;
	EnumUsnRecord("D", con);

	// 搜寻文件名为"test.txt"的文件号（可能有多个）
	std::set<DWORDLONG> con2;
	for (std::deque<MY_USN_RECORD>::const_iterator itor = con.begin(); itor != con.end(); ++itor)
	{
		const MY_USN_RECORD& mur = *itor;
		if (_wcsicmp(mur.FileName, L"123.txt") == 0)
		{
			con2.insert(mur.FileReferenceNumber);
		}
	}

	// 遍历其历史操作
	setlocale(LC_CTYPE, "chs");
	for (std::set<DWORDLONG>::const_iterator itor2 = con2.begin(); itor2 != con2.end(); ++itor2)
	{
		for (std::deque<MY_USN_RECORD>::const_iterator itor = con.begin(); itor != con.end(); ++itor)
		{
			const MY_USN_RECORD& mur = *itor;
			if (*itor2 == mur.FileReferenceNumber)
			{
				FILETIME timestamp;
				FileTimeToLocalFileTime(&(FILETIME&)mur.TimeStamp, &timestamp);
				SYSTEMTIME st;
				FileTimeToSystemTime(&timestamp, &st);
				printf("%04d-%02d-%02d %02d:%02d:%02d ", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

				if (mur.Reason&USN_REASON_DATA_OVERWRITE)
					printf("%s|", "DATA_OVERWRITE");
				if (mur.Reason&USN_REASON_DATA_EXTEND)
					printf("%s|", "DATA_EXTEND");
				if (mur.Reason&USN_REASON_DATA_TRUNCATION)
					printf("%s|", "DATA_TRUNCATION");
				if (mur.Reason&USN_REASON_NAMED_DATA_OVERWRITE)
					printf("%s|", "NAMED_DATA_OVERWRITE");
				if (mur.Reason&USN_REASON_NAMED_DATA_EXTEND)
					printf("%s|", "NAMED_DATA_EXTEND");
				if (mur.Reason&USN_REASON_NAMED_DATA_TRUNCATION)
					printf("%s|", "NAMED_DATA_TRUNCATION");
				if (mur.Reason&USN_REASON_FILE_CREATE)
					printf("%s|", "FILE_CREATE");
				if (mur.Reason&USN_REASON_FILE_DELETE)
					printf("%s|", "FILE_DELETE");
				if (mur.Reason&USN_REASON_EA_CHANGE)
					printf("%s|", "EA_CHANGE");
				if (mur.Reason&USN_REASON_SECURITY_CHANGE)
					printf("%s|", "SECURITY_CHANGE");
				if (mur.Reason&USN_REASON_RENAME_OLD_NAME)
					printf("%s|", "RENAME_OLD_NAME");
				if (mur.Reason&USN_REASON_RENAME_NEW_NAME)
					printf("%s|", "RENAME_NEW_NAME");
				if (mur.Reason&USN_REASON_INDEXABLE_CHANGE)
					printf("%s|", "INDEXABLE_CHANGE");
				if (mur.Reason&USN_REASON_BASIC_INFO_CHANGE)
					printf("%s|", "BASIC_INFO_CHANGE");
				if (mur.Reason&USN_REASON_HARD_LINK_CHANGE)
					printf("%s|", "HARD_LINK_CHANGE");
				if (mur.Reason&USN_REASON_COMPRESSION_CHANGE)
					printf("%s|", "COMPRESSION_CHANGE");
				if (mur.Reason&USN_REASON_ENCRYPTION_CHANGE)
					printf("%s|", "ENCRYPTION_CHANGE");
				if (mur.Reason&USN_REASON_OBJECT_ID_CHANGE)
					printf("%s|", "OBJECT_ID_CHANGE");
				if (mur.Reason&USN_REASON_REPARSE_POINT_CHANGE)
					printf("%s|REPARSE_POINT_CHANGE", "");
				if (mur.Reason&USN_REASON_STREAM_CHANGE)
					printf("%s|", "STREAM_CHANGE");
				if (mur.Reason&USN_REASON_TRANSACTED_CHANGE)
					printf("%s|", "TRANSACTED_CHANGE");
				if (mur.Reason&USN_REASON_CLOSE)
					printf("%s|", "CLOSE");

				printf("\r\n");
					bool PrintFullPath(const MY_USN_RECORD& mur, const std::deque<MY_USN_RECORD>& con);
				PrintFullPath(mur, con);

				printf("\r\n");
			}
		}

		printf("\r\n");
	}

	if (hVol != INVALID_HANDLE_VALUE)
		CloseHandle(hVol);

	return 0;
}


bool GetFullPathByFileReferenceNumber(HANDLE hVol, DWORDLONG FileReferenceNumber) // 根据文件号获得全路径，上篇文章已经说过，共有3中方法，这是其中之一，代码简单但效率不高
{
	typedef ULONG(__stdcall *PNtCreateFile)(
		PHANDLE FileHandle,
		ULONG DesiredAccess,
		PVOID ObjectAttributes,
		PVOID IoStatusBlock,
		PLARGE_INTEGER AllocationSize,
		ULONG FileAttributes,
		ULONG ShareAccess,
		ULONG CreateDisposition,
		ULONG CreateOptions,
		PVOID EaBuffer,
		ULONG EaLength);
	PNtCreateFile NtCreatefile = (PNtCreateFile)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtCreateFile");

	typedef struct _UNICODE_STRING {
		USHORT Length, MaximumLength;
		PWCH Buffer;
	} UNICODE_STRING, *PUNICODE_STRING;
	UNICODE_STRING fidstr = { 8, 8, (PWSTR)&FileReferenceNumber };

	typedef struct _OBJECT_ATTRIBUTES {
		ULONG Length;
		HANDLE RootDirectory;
		PUNICODE_STRING ObjectName;
		ULONG Attributes;
		PVOID SecurityDescriptor;
		PVOID SecurityQualityOfService;
	} OBJECT_ATTRIBUTES;
	const ULONG OBJ_CASE_INSENSITIVE = 0x00000040UL;
	OBJECT_ATTRIBUTES oa = { sizeof(OBJECT_ATTRIBUTES), hVol, &fidstr, OBJ_CASE_INSENSITIVE, 0, 0 };

	HANDLE hFile;
	ULONG iosb[2];
	const ULONG FILE_OPEN_BY_FILE_ID = 0x00002000UL;
	const ULONG FILE_OPEN = 0x00000001UL;
	ULONG status = NtCreatefile(&hFile, GENERIC_ALL, &oa, iosb, NULL, FILE_ATTRIBUTE_NORMAL, FILE_SHARE_READ | FILE_SHARE_WRITE, FILE_OPEN, FILE_OPEN_BY_FILE_ID, NULL, 0);
	if (status == 0)
	{
		typedef struct _IO_STATUS_BLOCK {
			union {
				NTSTATUS Status;
				PVOID Pointer;
			};
			ULONG_PTR Information;
		} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;
		typedef enum _FILE_INFORMATION_CLASS {
			// ……
			FileNameInformation = 9
			// ……
		} FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;
		typedef NTSTATUS(__stdcall *PNtQueryInformationFile)(
			HANDLE FileHandle,
			PIO_STATUS_BLOCK IoStatusBlock,
			PVOID FileInformation,
			DWORD Length,
			FILE_INFORMATION_CLASS FileInformationClass);
		PNtQueryInformationFile NtQueryInformationFile = (PNtQueryInformationFile)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtQueryInformationFile");

		typedef struct _OBJECT_NAME_INFORMATION {
			UNICODE_STRING Name;
		} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;
		IO_STATUS_BLOCK IoStatus;
		size_t allocSize = sizeof(OBJECT_NAME_INFORMATION) + MAX_PATH*sizeof(WCHAR);
		POBJECT_NAME_INFORMATION pfni = (POBJECT_NAME_INFORMATION)operator new(allocSize);
		status = NtQueryInformationFile(hFile, &IoStatus, pfni, allocSize, FileNameInformation);
		if (status == 0)
		{
			printf("%.*S", pfni->Name.Length / 2, &pfni->Name.Buffer);
		}
		operator delete(pfni);

		CloseHandle(hFile);
	}

	return status == 0;
}