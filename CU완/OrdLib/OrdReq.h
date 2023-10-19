#pragma once

#include "..\\EHPacketLib\\EHPacket.h"
#include "..\\common\\\ordef.h"
#ifdef SAODFUXCZVJKLEWRUQFSOFJSDFK
#define ORD_DLL	__declspec(dllexport)
#else
#define ORD_DLL	__declspec(dllimport)
#endif

class ORD_DLL OrdReq
{
	char name[MAX_NAME_LEN];
	char price[MAX_PRICE_LEN];
	char total[MAX_TOTAL_LEN];
public:
	OrdReq(const char* price, const char* total, const char* name);
	OrdReq(EHPacket* ep);
	void Send(HANDLE hFile);
	void Send(SOCKET sock);
	const char* GetPrice();
	const char* GetTotal();
	const char* GetName();
};