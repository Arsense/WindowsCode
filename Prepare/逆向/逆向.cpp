char __fastcall sub_14003B130(const WCHAR *a1, _BYTE *a2, _WORD *a3)
{
	char result; // al@2
	char *v4; // [sp+40h] [bp-58h]@8
	signed int v5; // [sp+48h] [bp-50h]@16
	signed int v6; // [sp+48h] [bp-50h]@31
	char *lpBaseAddress; // [sp+50h] [bp-48h]@5
	HANDLE hFileMappingObject; // [sp+58h] [bp-40h]@3
	HANDLE hFile; // [sp+60h] [bp-38h]@1
	char *lp; // [sp+68h] [bp-30h]@14
	signed __int64 v11; // [sp+70h] [bp-28h]@16
	signed __int64 v12; // [sp+70h] [bp-28h]@31
	char v13; // [sp+80h] [bp-18h]@1
	_BYTE *v14; // [sp+A8h] [bp+10h]@1
	_WORD *v15; // [sp+B0h] [bp+18h]@1

	v15 = a3;
	v14 = a2;
	v13 = 0;
	*a2 = 0;
	hFile = CreateFileW(a1, 0x80000000, 1u, 0i64, 3u, 0x80u, 0i64);
	if (hFile == (HANDLE)-1)
	{
		result = 0;
	}
	else
	{
		hFileMappingObject = CreateFileMappingW(hFile, 0i64, 2u, 0, 0, 0i64);
		if (hFileMappingObject)
		{
			lpBaseAddress = (char *)MapViewOfFile(hFileMappingObject, 4u, 0, 0, 0i64);
			if (lpBaseAddress)
			{
				if (*(_WORD *)lpBaseAddress == 23117)
				{
					v4 = &lpBaseAddress[*((_DWORD *)lpBaseAddress + 15)];
					if (*((_WORD *)v4 + 11) & 0x100 && *((_WORD *)v4 + 2) != 34404 && *((_WORD *)v4 + 2) != 512)
						*v14 = 1;
					else
						*v14 = 2;
					*v15 = *((_WORD *)v4 + 47);
					if (*v14 == 2)
					{
						lp = &lpBaseAddress[*((_DWORD *)lpBaseAddress + 15)];
						if (!IsBadReadPtr(lp, 0x108ui64) && *(_DWORD *)lp == 17744)
						{
							v11 = (signed __int64)(lp + 264);
							v5 = 1;
							while (v5 <= *((_WORD *)lp + 3))
							{
								if (!*(_DWORD *)(v11 + 16)
									&& sub_1400954D0(v11, ".textbss", 8i64)
									&& sub_1400954D0(v11, ".tls", 8i64)
									&& sub_1400954D0(v11, ".bss", 8i64)
									&& sub_1400954D0(v11, ".bss", 8i64)
									&& sub_1400954D0(v11, "rt_bss", 8i64)
									&& *(_DWORD *)(v11 + 36) & 0x20000000
									&& *(_DWORD *)(v11 + 36) & 0xC0)
								{
									v13 = 1;
									break;
								}
								++v5;
								v11 += 40i64;
							}
						}
					}
					else if (!IsBadReadPtr(v4, 0xF8ui64) && *(_DWORD *)v4 == 17744)
					{
						v12 = (signed __int64)(v4 + 248);
						v6 = 1;
						while (v6 <= *((_WORD *)v4 + 3))
						{
							if (*(_DWORD *)(v12 + 36) & 0x20
								&& *(_DWORD *)(v12 + 8) > 0x1000u
								&& *(_DWORD *)(v12 + 16) < (unsigned int)(*(_DWORD *)(v12 + 8) - 4096))
							{
								v13 = 1;
								break;
							}
							if (!sub_1400954D0(v12, ".text", 8i64)
								&& *(_DWORD *)(v12 + 8) > 0x1000u
								&& *(_DWORD *)(v12 + 16) < (unsigned int)(*(_DWORD *)(v12 + 8) - 4096))
							{
								v13 = 1;
								break;
							}
							if (!*(_BYTE *)v12 && *(_DWORD *)(v12 + 16) < *(_DWORD *)(v12 + 8))
							{
								v13 = 1;
								break;
							}
							if (!*(_DWORD *)(v12 + 16)
								&& *(_DWORD *)(v12 + 8) >= 0x1000u
								&& sub_1400954D0(v12, ".textbss", 8i64)
								&& sub_1400954D0(v12, ".tls", 8i64)
								&& sub_1400954D0(v12, ".bss", 8i64)
								&& sub_1400954D0(v12, ".data", 8i64)
								&& *(_DWORD *)(v12 + 36) & 0x20000000
								&& *(_DWORD *)(v12 + 36) & 0xC0)
							{
								v13 = 1;
								break;
							}
							++v6;
							v12 += 40i64;
						}
					}
				}
				UnmapViewOfFile(lpBaseAddress);
				CloseHandle(hFileMappingObject);
				CloseHandle(hFile);
				result = v13;
			}
			else
			{
				CloseHandle(hFileMappingObject);
				CloseHandle(hFile);
				result = 0;
			}
		}
		else
		{
			CloseHandle(hFile);
			result = 0;
		}
	}
	return result;
}