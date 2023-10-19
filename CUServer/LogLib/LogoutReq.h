#pragma once
#include "..\EHPacketLib\EHPacket.h"
#include "..\\common\\\ehdef.h"
#ifdef DJHFLKDJFKLDJLKFLDJFLKDJFL
#define LOG_DLL	__declspec(dllexport)
#else
#define LOG_DLL	__declspec(dllimport)
#endif

class LOG_DLL LogoutReq
{
	char id[MAX_ID_LEN];
	char pw[MAX_PW_LEN];
public:
	LogoutReq(const char* id, const char* pw);
	LogoutReq(EHPacket* ep);
	void Send(HANDLE hFile);
	void Send(SOCKET sock);
	const char* GetID();
	const char* GetPW();
};
