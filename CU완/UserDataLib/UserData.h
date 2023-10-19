#pragma once
#include <Windows.h>
#include <Shlwapi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "..\\common\\\ehdef.h"

#pragma comment(lib,"Shlwapi.lib")
#define USER_DB			TEXT("user.txt")
#define MAX_USER		10


enum UserStatus
{
	EMPTY = 0, REGED = 1, LOGINED = 2
};

#ifdef SDIFEVDCVMEUCCIEJCU847567JCUENCYEJDC
#define USER_DATA_DLL	__declspec(dllexport)
#else 
#define USER_DATA_DLL	__declspec(dllimport)
#endif

struct USER_DATA_DLL UserData
{
	char name[MAX_NAME_LEN];
	char id[MAX_ID_LEN];
	char pw[MAX_PW_LEN];
	UserStatus status;
};

extern "C" USER_DATA_DLL  void MakeDB();
extern "C" USER_DATA_DLL UserData * Loading();
extern "C" USER_DATA_DLL UserData* FindFirstEmpty();
extern "C" USER_DATA_DLL UserData* AddUserData(const char* id, const char* pw, const char* name);
extern "C" USER_DATA_DLL UserData* FindUserData(const char* id);
extern "C" USER_DATA_DLL void RemoveUserData(const char* id);
extern "C" USER_DATA_DLL void CleanUserDB();
