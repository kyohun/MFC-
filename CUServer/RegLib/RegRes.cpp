#define CCIECUENCUEHNCYE8347HCYEBNCEBGCGEBCGWE
#include "RegRes.h"

RegRes::RegRes(int result)
{
	this->result = result;
}
RegRes::RegRes(EHPacket* ep)
{
	ep->Decapsulate(&result, sizeof(result));
}
void RegRes::Send(HANDLE hFile)
{
	EHPacket* ep = new EHPacket(REG_RES);
	ep->Capsulate(&result, sizeof(int));
	ep->Serialize(hFile);
	delete ep;
}

void RegRes::Send(SOCKET sock)
{
	EHPacket* ep = new EHPacket(REG_RES);
	ep->Capsulate(&result, sizeof(int));
	ep->Send(sock);
	delete ep;
}
int RegRes::GetResult()
{
	return result;
}