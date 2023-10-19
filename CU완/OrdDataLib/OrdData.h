#pragma once
#include <Windows.h>
#include <Shlwapi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "..\\common\\\ordef.h"

#pragma comment(lib,"Shlwapi.lib")
#define ORD_DB			TEXT("ord.txt")
#define MAX_ORD		100


enum OrdStatus
{
	EMPTY_OD = 0, REGED_OD = 1, LOGINED_OD = 2
};

#ifdef OXCVUWRJLDJSAODJSDFJO
#define ORD_DATA_DLL	__declspec(dllexport)
#else 
#define ORD_DATA_DLL	__declspec(dllimport)
#endif

struct ORD_DATA_DLL OrdData
{
	char name[MAX_NAME_LEN];
	char id[MAX_ID_LEN];
	char pw[MAX_PW_LEN];
	char price[MAX_PRICE_LEN];
	char total[MAX_TOTAL_LEN];
	OrdStatus orstatus;
};

extern "C" ORD_DATA_DLL  void MakeDB_or();
extern "C" ORD_DATA_DLL OrdData * Loading_or();
extern "C" ORD_DATA_DLL OrdData * FindFirstEmpty_or();
extern "C" ORD_DATA_DLL OrdData * AddOrdData(const char* name, const char* price, const char* total);
extern "C" ORD_DATA_DLL OrdData * FindOrdData(const char* id);
extern "C" ORD_DATA_DLL void RemoveOrdData(const char* id);
extern "C" ORD_DATA_DLL void CleanOrdDB();
