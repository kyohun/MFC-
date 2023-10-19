#define CCIECUENCUEHNCYE8347HCYEBNCEBGCGEBCGWE
#include "UnRegReq.h"
#include "../common/ehdef.h"
UnRegReq::UnRegReq(const char* id, const char* pw)
{
	strcpy_s(this->id, MAX_ID_LEN, id);
	strcpy_s(this->pw, MAX_PW_LEN, pw);
}
UnRegReq::UnRegReq(EHPacket* ep)
{
	int idlen = 0;
	ep->Decapsulate(&idlen, sizeof(int));
	ep->Decapsulate(id, idlen);
	int pwlen = 0;
	ep->Decapsulate(&pwlen, sizeof(int));
	ep->Decapsulate(pw, pwlen);
}
void UnRegReq::Send(HANDLE hFile)
{
	EHPacket* ep = new EHPacket(UNREG_REQ);
	int idlen = strlen(id) + 1;
	ep->Capsulate(&idlen, sizeof(int));
	ep->Capsulate(id, idlen);
	int pwlen = strlen(pw) + 1;
	ep->Capsulate(&pwlen, sizeof(int));
	ep->Capsulate(pw, pwlen);
	ep->Serialize(hFile);
	delete ep;
}

void UnRegReq::Send(SOCKET sock)
{
	EHPacket* ep = new EHPacket(UNREG_REQ);
	int idlen = strlen(id) + 1;
	ep->Capsulate(&idlen, sizeof(int));
	ep->Capsulate(id, idlen);
	int pwlen = strlen(pw) + 1;
	ep->Capsulate(&pwlen, sizeof(int));
	ep->Capsulate(pw, pwlen);
	ep->Send(sock);
	delete ep;
}

const char* UnRegReq::GetID()
{
	return id;
}

const char* UnRegReq::GetPW()
{
	return pw;
}