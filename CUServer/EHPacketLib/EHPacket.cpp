#define CIEUECUEHCEHC47546CEGHCTYE48746chEUENC
#include "EHPacket.h"
#pragma comment (lib,"ws2_32")

EHPacket::EHPacket(int msgid)
{
	mh.msgid = msgid;
	mh.bdlen = 0;
}
EHPacket::EHPacket(HANDLE hFile)
{
	DWORD dw;
	ReadFile(hFile, &mh, sizeof(MsgHead), &dw, 0);
	ReadFile(hFile, body, mh.bdlen, &dw, 0);
	offset = body;
}

EHPacket::EHPacket(SOCKET sock)
{
	recv(sock,(char*)&mh, sizeof(MsgHead), 0);
	recv(sock, body, mh.bdlen, 0);
	offset = body;
}



void EHPacket::Capsulate(void* data, int dlen)
{
	memcpy_s(body + mh.bdlen, MAX_BODY_LEN - mh.bdlen, data, dlen);
	mh.bdlen += dlen;
}
void EHPacket::Decapsulate(void* base, int blen)
{
	if ((offset + blen - body) > mh.bdlen)
	{
		return;
	}
	memcpy_s(base, blen, offset, blen);
	offset += blen;
}
void EHPacket::Serialize(HANDLE hFile)
{
	DWORD dw;
	WriteFile(hFile, &mh, sizeof(MsgHead), &dw, 0);
	WriteFile(hFile, body, mh.bdlen, &dw, 0);
}

void EHPacket::Send(SOCKET sock)
{
	send(sock, (char*) & mh, sizeof(MsgHead), 0);
	send(sock, body, mh.bdlen, 0);
}

int EHPacket::GetMsgID()
{
	return mh.msgid;
}