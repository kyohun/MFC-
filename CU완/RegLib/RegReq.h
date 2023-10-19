#pragma once
#include "..\EHPacketLib\EHPacket.h"
#include "..\\common\\\ehdef.h"
#ifdef CCIECUENCUEHNCYE8347HCYEBNCEBGCGEBCGWE
#define REG_DLL	__declspec(dllexport)
#else
#define REG_DLL	__declspec(dllimport)
#endif

class REG_DLL RegReq
{
	char id[MAX_ID_LEN];
	char pw[MAX_PW_LEN];
	char name[MAX_NAME_LEN];
public:
	RegReq(const char* id, const char* pw, const char* name);
	RegReq(EHPacket *ep);
	void Send(HANDLE hFile);
	void Send(SOCKET sock);
	const char* GetID();
	const char* GetPW();
	const char* GetName();
};



