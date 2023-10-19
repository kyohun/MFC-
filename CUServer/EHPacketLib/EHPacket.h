#pragma once
#include <WinSock2.h>
#include <Windows.h>
#ifdef CIEUECUEHCEHC47546CEGHCTYE48746chEUENC
#define EHPACKET_DLL __declspec(dllexport)
#else
#define EHPACKET_DLL __declspec(dllimport)
#endif

struct EHPACKET_DLL MsgHead
{
	int msgid;
	int bdlen;
};

#define MAX_BODY_LEN	4088

class EHPACKET_DLL EHPacket
{	
	MsgHead mh;
	char body[MAX_BODY_LEN];
	char* offset;
public:
	EHPacket(int msgid);
	EHPacket(HANDLE hFile);
	EHPacket(SOCKET hFile);
	void Capsulate(void* data, int dlen);
	void Decapsulate(void* base, int blen);
	void Serialize(HANDLE hFile);
	void Send(SOCKET sock);
	int GetMsgID();
};