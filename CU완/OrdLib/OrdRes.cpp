#define SAODFUXCZVJKLEWRUQFSOFJSDFK
#include "OrdRes.h"
#include "../common/ordef.h"

OrdRes::OrdRes(int result)
{
	this->result = result;
}
OrdRes::OrdRes(EHPacket* ep)
{
	ep->Decapsulate(&result, sizeof(result));
}
void OrdRes::Send(HANDLE hFile)
{
	EHPacket* ep = new EHPacket(ORD_RES);
	ep->Capsulate(&result, sizeof(int));
	ep->Serialize(hFile);
	delete ep;
}
void OrdRes::Send(SOCKET sock)
{
	EHPacket* ep = new EHPacket(ORD_RES);
	ep->Capsulate(&result, sizeof(int));
	ep->Send(sock);
	delete ep;
}

int OrdRes::GetResult()
{
	return result;
}