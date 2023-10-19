#define OXCVUWRJLDJSAODJSDFJO
#include "OrdData.h"
static HANDLE hFile;
static HANDLE hMapping;
static OrdData* base;
static OrdData ods[MAX_ORD];

extern "C" ORD_DATA_DLL  void MakeDB_or()
{
	if (PathFileExists(ORD_DB))
	{
		return;
	}
	HANDLE hFile = CreateFile(ORD_DB, GENERIC_WRITE, 0, 0, CREATE_NEW, 0, 0);
	DWORD dw;
	WriteFile(hFile, ods, sizeof(ods), &dw, 0);
	CloseHandle(hFile);
}

extern "C" ORD_DATA_DLL OrdData * Loading_or()
{
	hFile = CreateFile(ORD_DB, GENERIC_ALL, 0, 0, OPEN_EXISTING, 0, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	hMapping = CreateFileMapping(hFile, 0, PAGE_READWRITE, 0, 0, 0);
	base = (OrdData*)MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	return base;
}

extern "C" ORD_DATA_DLL OrdData * FindFirstEmpty_or()
{
	for (int i = 0; i < MAX_ORD; i++)
	{
		if (base[i].orstatus == EMPTY_OD)
		{
			return base + i;
		}
	}
	return 0;
}

extern "C" ORD_DATA_DLL OrdData * AddOrdData(const char* name, const char* price, const char* total)
{
	OrdData* od = FindFirstEmpty_or();
	if (od == 0)
	{
		return od;
	}
	//strcpy_s(od->id, MAX_ID_LEN, id);
	//strcpy_s(od->pw, MAX_PW_LEN, pw);
	strcpy_s(od->name, MAX_NAME_LEN, name);
	strcpy_s(od->price, MAX_PRICE_LEN, price);
	strcpy_s(od->total, MAX_TOTAL_LEN, total);
	od->orstatus = REGED_OD;
	return od;
}
extern "C" ORD_DATA_DLL OrdData * FindOrdData(const char* id)
{
	for (int i = 0; i < MAX_ORD; i++)
	{
		if (strcmp(base[i].id, id) == 0)
		{
			return base + i;
		}
	}
	return 0;
}
extern "C" ORD_DATA_DLL void RemoveOrdData(const char* id)
{
	OrdData eraser = {};
	OrdData* od = FindOrdData(id);
	if (od == 0)
	{
		return;
	}

	OrdData* empty = FindFirstEmpty_or();
	if (empty == base)
	{
		return;
	}

	memcpy(od, empty - 1, sizeof(OrdData));
	memcpy(empty - 1, &eraser, sizeof(OrdData));
}
extern "C" ORD_DATA_DLL void CleanOrdDB()
{
	UnmapViewOfFile(base);
	CloseHandle(hMapping);
	CloseHandle(hFile);
}
