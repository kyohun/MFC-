#define SDIFEVDCVMEUCCIEJCU847567JCUENCYEJDC
#include "UserData.h"
static HANDLE hFile;
static HANDLE hMapping;
static UserData* base;
static UserData uds[MAX_USER];

extern "C" USER_DATA_DLL  void MakeDB()
{
	if (PathFileExists(USER_DB))
	{
		return;
	}
	HANDLE hFile = CreateFile(USER_DB, GENERIC_WRITE, 0, 0, CREATE_NEW, 0, 0);
	DWORD dw;
	WriteFile(hFile, uds, sizeof(uds), &dw, 0);
	CloseHandle(hFile);
}
extern "C" USER_DATA_DLL UserData* Loading()
{
	hFile = CreateFile(USER_DB, GENERIC_ALL, 0, 0, OPEN_EXISTING, 0, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	hMapping = CreateFileMapping(hFile, 0, PAGE_READWRITE, 0, 0, 0);
	base = (UserData*)MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	return base;
}
extern "C" USER_DATA_DLL UserData* FindFirstEmpty()
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (base[i].status == EMPTY)
		{
			return base + i;
		}
	}
	return 0;
}
extern "C" USER_DATA_DLL UserData* AddUserData(const char* id, const char* pw, const char* name)
{
	UserData* ud = FindFirstEmpty();
	if (ud == 0)
	{
		return ud;
	}
	strcpy_s(ud->id, MAX_ID_LEN, id);
	strcpy_s(ud->pw, MAX_PW_LEN, pw);
	strcpy_s(ud->name, MAX_NAME_LEN, name);
	ud->status = REGED;
	return ud;
}
extern "C" USER_DATA_DLL UserData* FindUserData(const char* id)
{
	for (int i = 0; i < MAX_USER; i++)
	{
		if (strcmp(base[i].id, id) == 0)
		{
			return base + i;
		}
	}
	return 0;
}
extern "C" USER_DATA_DLL void RemoveUserData(const char* id)
{
	UserData eraser = {};
	UserData* ud = FindUserData(id);
	if (ud == 0)
	{
		return;
	}

	UserData* empty = FindFirstEmpty();
	if (empty == base)
	{
		return;
	}

	memcpy(ud, empty - 1, sizeof(UserData));
	memcpy(empty - 1, &eraser, sizeof(UserData));
}
extern "C" USER_DATA_DLL void CleanUserDB()
{
	UnmapViewOfFile(base);
	CloseHandle(hMapping);
	CloseHandle(hFile);
}
