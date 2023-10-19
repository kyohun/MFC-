#pragma once
#include "..\EHPacketLib\EHPacket.h"
#include "..\\common\\\ehdef.h"
#ifdef DJHFLKDJFKLDJLKFLDJFLKDJFL
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