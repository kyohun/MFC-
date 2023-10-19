#pragma once

#include "..\\EHPacketLib\\EHPacket.h"
#ifdef SAODFUXCZVJKLEWRUQFSOFJSDFK
#define ORD_DLL	__declspec(dllexport)
#else
#define ORD_DLL	__declspec(dllimport)
#endif

class ORD_DLL OrdRes
{
	int result;
public:
	OrdRes(int result);
	OrdRes(EHPacket* ep);
	void Send(HANDLE hFile);
	void Send(SOCKET sock);
	int GetResult();
};