#define SAODFUXCZVJKLEWRUQFSOFJSDFK

#include "OrdReq.h"
#include "../common/ordef.h"
#pragma comment(lib,"..\\x64\\Debug\\EHPacketLib.lib")

OrdReq::OrdReq(const char* price, const char* total, const char* name)
{
	strcpy_s(this->price, MAX_PRICE_LEN, price);
	strcpy_s(this->total, MAX_TOTAL_LEN, total);
	strcpy_s(this->name, MAX_NAME_LEN, name);

}
OrdReq::OrdReq(EHPacket* ep)
{
	int plen = 0;
	ep->Decapsulate(&plen, sizeof(int));
	ep->Decapsulate(price, plen);
	int tlen = 0;
	ep->Decapsulate(&tlen, sizeof(int));
	ep->Decapsulate(total, tlen);
	int nlen = 0;
	ep->Decapsulate(&nlen, sizeof(int));
	ep->Decapsulate(name, nlen);
}
void OrdReq::Send(HANDLE hFile)
{
	EHPacket* ep = new EHPacket(ORD_REQ);
	int plen = strlen(price) + 1;
	ep->Capsulate(&plen, sizeof(int));
	ep->Capsulate(price, plen);
	int tlen = strlen(total) + 1;
	ep->Capsulate(&tlen, sizeof(int));
	ep->Capsulate(total, tlen);
	int nlen = strlen(name) + 1;
	ep->Capsulate(&nlen, sizeof(int));
	ep->Capsulate(name, nlen);
	ep->Serialize(hFile);
	delete ep;
}
void OrdReq::Send(SOCKET sock)
{
	EHPacket* ep = new EHPacket(ORD_REQ);
	int plen = strlen(price) + 1;
	ep->Capsulate(&plen, sizeof(int));
	ep->Capsulate(price, plen);
	int tlen = strlen(total) + 1;
	ep->Capsulate(&tlen, sizeof(int));
	ep->Capsulate(total, tlen);
	int nlen = strlen(name) + 1;
	ep->Capsulate(&nlen, sizeof(int));
	ep->Capsulate(name, nlen);
	ep->Send(sock);
	delete ep;
}

const char* OrdReq::GetPrice()
{
	return price;
}
const char* OrdReq::GetTotal()
{
	return total;
}
const char* OrdReq::GetName()
{
	return name;
}