#pragma once
#include "..\EHPacketLib\EHPacket.h"
#ifdef CCIECUENCUEHNCYE8347HCYEBNCEBGCGEBCGWE
#define LOG_DLL	__declspec(dllexport)
#else
#define LOG_DLL	__declspec(dllimport)
#endif

class LOG_DLL LoginRes
{
	int result;
public:
	LoginRes(int result);
	LoginRes(EHPacket* ep);
	void Send(HANDLE hFile);
	void Send(SOCKET sock);
	int GetResult();
};

