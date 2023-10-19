#pragma once
#include "..\EHPacketLib\EHPacket.h"
#include "..\\common\\\ehdef.h"
#ifdef CCIECUENCUEHNCYE8347HCYEBNCEBGCGEBCGWE
#define LOG_DLL	__declspec(dllexport)
#else
#define LOG_DLL	__declspec(dllimport)
#endif

class LOG_DLL LoginReq
{
	char id[MAX_ID_LEN];
	char pw[MAX_PW_LEN];
public:
	LoginReq(const char* id, const char* pw);
	LoginReq(EHPacket* ep);
	void Send(HANDLE hFile);
	void Send(SOCKET sock);
	const char* GetID();
	const char* GetPW();
};



