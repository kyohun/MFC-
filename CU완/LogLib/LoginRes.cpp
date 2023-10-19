#define CCIECUENCUEHNCYE8347HCYEBNCEBGCGEBCGWE
#include "LoginRes.h"

#include "../common/ehdef.h"
LoginRes::LoginRes(int result)
{
	this->result = result;
}
LoginRes::LoginRes(EHPacket* ep)
{
	ep->Decapsulate(&result, sizeof(result));
}
void LoginRes::Send(HANDLE hFile)
{
	EHPacket* ep = new EHPacket(LOGIN_RES);
	ep->Capsulate(&result, sizeof(int));
	ep->Serialize(hFile);
	delete ep;
}
void LoginRes::Send(SOCKET sock)
{
	EHPacket* ep = new EHPacket(LOGIN_RES);
	ep->Capsulate(&result, sizeof(int));
	ep->Send(sock);
	delete ep;
}
int LoginRes::GetResult()
{
	return result;
}