#pragma once
#include "..\EHPacketLib\EHPacket.h"
#ifdef CCIECUENCUEHNCYE8347HCYEBNCEBGCGEBCGWE
#define REG_DLL	__declspec(dllexport)
#else
#define REG_DLL	__declspec(dllimport)
#endif

class REG_DLL RegRes
{
	int result;
public:
	RegRes(int result);
	RegRes(EHPacket* ep);
	void Send(HANDLE hFile);
	void Send(SOCKET sock);
	int GetResult();
};

