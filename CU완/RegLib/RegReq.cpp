#define CCIECUENCUEHNCYE8347HCYEBNCEBGCGEBCGWE

#include "RegReq.h"
#include "../common/ehdef.h"
#pragma comment(lib,"..\\x64\\Debug\\EHPacketLib.lib")
RegReq::RegReq(const char* id, const char* pw, const char* name)
{
	strcpy_s(this->id, MAX_ID_LEN, id);
	strcpy_s(this->pw, MAX_PW_LEN, pw);
	strcpy_s(this->name, MAX_NAME_LEN, name);

}
RegReq::RegReq(EHPacket* ep)
{	
	int idlen = 0;
	ep->Decapsulate(&idlen, sizeof(int));
	ep->Decapsulate(id, idlen);
	int pwlen = 0;
	ep->Decapsulate(&pwlen, sizeof(int));
	ep->Decapsulate(pw, pwlen);
	int nlen = 0;
	ep->Decapsulate(&nlen, sizeof(int));
	ep->Decapsulate(name, nlen);
}

void RegReq::Send(HANDLE hFile)
{
	EHPacket* ep = new EHPacket(REG_REQ);
	int idlen = strlen(id) + 1;
	ep->Capsulate(&idlen, sizeof(int));
	ep->Capsulate(id, idlen);
	int pwlen = strlen(pw) + 1;
	ep->Capsulate(&pwlen, sizeof(int));
	ep->Capsulate(pw, pwlen);
	int nlen = strlen(name) + 1;
	ep->Capsulate(&nlen, sizeof(int));
	ep->Capsulate(name, nlen);
	ep->Serialize(hFile);
	delete ep;
}
void RegReq::Send(SOCKET sock)
{
	EHPacket* ep = new EHPacket(REG_REQ);
	int idlen = strlen(id) + 1;
	ep->Capsulate(&idlen, sizeof(int));
	ep->Capsulate(id, idlen);
	int pwlen = strlen(pw) + 1;
	ep->Capsulate(&pwlen, sizeof(int));
	ep->Capsulate(pw, pwlen);
	int nlen = strlen(name) + 1;
	ep->Capsulate(&nlen, sizeof(int));
	ep->Capsulate(name, nlen);
	ep->Send(sock);
	delete ep;
}
const char* RegReq::GetID()
{
	return id;
}
const char* RegReq::GetPW()
{
	return pw;
}
const char* RegReq::GetName()
{
	return name;
}