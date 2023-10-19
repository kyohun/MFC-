#include "..\\EHPacketLib\\EHPacket.h"

#include "..\\RegLib\\RegReq.h"
#include "..\\RegLib\\UnRegReq.h"
#include "..\\RegLib\\RegRes.h"

#include "..\\LogLib\\LoginReq.h"
#include "..\\LogLib\\LogoutReq.h"
#include "..\\LogLib\\LoginRes.h"

#include "..\\OrdLib\OrdReq.h"
#include "..\\OrdLib\OrdRes.h"
#include "..\\OrdLib\UnOrdReq.h"

#include "..\\UserDataLib\\UserData.h"
#include "..\\OrdDataLib\\OrdData.h"

#include "..\\common\\ehdef.h"
#include "..\\common\\ordef.h"
//#include "DBControl.h"


void RegReqProc(EHPacket* ep, SOCKET sock)
{
	RegReq* rr = new RegReq(ep);
	UserData* ud = FindUserData(rr->GetID());
	int result = REG_RES_NO;
	if (ud)
	{
		printf("(%s) �̹� ���� ������ ID�Դϴ�.\n", rr->GetID());
	}
	else
	{
		//DBControl* dbc = DBControl::GetInstance();
		AddUserData(rr->GetID(), rr->GetPW(), rr->GetName());

		//wchar_t query_str[100] = TEXT("");
		//wsprintf(query_str, TEXT("INSERT INTO CLIENTLIST (CID, CPW, CNAME) VALUES ('%s', '%s', '%s')"), rr->GetID(), rr->GetPW(), rr->GetName());

		result = REG_RES_OK;
		printf("%s %s %s ���� ����\n", rr->GetID(), rr->GetPW(), rr->GetName());

	}
	RegRes* rres = new RegRes(result);
	rres->Send(sock);
	delete rres;
}

void UnRegReqProc(EHPacket* ep, SOCKET sock)
{
	UnRegReq* urr = new UnRegReq(ep);
	UserData* ud = FindUserData(urr->GetID());
	if (ud == 0)
	{
		printf("ũ��Ŀ(black ��Ŀ)�� ���Գ���\n");
		return;
	}
	if (strcmp(ud->pw, urr->GetPW()) == 0)
	{
		RemoveUserData(urr->GetID());
		printf("%s Ż���Ͽ����ϴ�.\n", urr->GetID());
	}
	else
	{
		printf("�Ƹ��� ũ��Ŀ(black ��Ŀ)�� ���Գ���... ��й�ȣ�� �𸧽÷�...\n");
		return;
	}
}
void LoginReqProc(EHPacket* ep, SOCKET sock)
{
	LoginReq* lr = new LoginReq(ep);
	UserData* ud = FindUserData(lr->GetID());
	int result = LOGIN_RES_FA;
	if (ud == 0)
	{
		result = LOGIN_RES_NOI;
		printf("(%s) ���̵� ���µ� �α��� ��û�߳׿�.\n", lr->GetID());
	}
	else
	{
		if (strcmp(lr->GetPW(), ud->pw) == 0)
		{
			if (ud->status == LOGINED)
			{
				result = LOGIN_RES_ALR;
			}
			else
			{
				ud->status = LOGINED;
				result = LOGIN_RES_OK;
				printf("%s %s �α��� ����\n", lr->GetID(), lr->GetPW());
			}
		}
		else
		{
			result = LOGIN_RES_NOC;
			printf("(%s) ��й�ȣ�� �ٸ��� �α��� ��û�߳׿�.\n", lr->GetID());
		}

	}
	LoginRes* lres = new LoginRes(result);
	lres->Send(sock);
	delete lres;
}
void LogoutReqProc(EHPacket* ep, SOCKET sock)
{
	LogoutReq* lor = new LogoutReq(ep);
	UserData* ud = FindUserData(lor->GetID());
	if (ud == 0)
	{
		printf("ũ��Ŀ(black ��Ŀ)�� ���Գ���(%s ����)\n", lor->GetID());
		return;
	}
	if (strcmp(ud->pw, lor->GetPW()) == 0)
	{
		if (ud->status != LOGINED)
		{
			printf("ũ��Ŀ(black ��Ŀ)�� ���Գ���(%s �α� ���°� �ƴѵ� �α� �ƿ� ��û)\n", lor->GetID());
		}
		else
		{
			ud->status = REGED;
			printf("%s �α� �ƿ� �Ͽ����ϴ�.\n", lor->GetID());
		}
	}
	else
	{
		printf("%s �Ƹ��� ũ��Ŀ(black ��Ŀ)�� ���Գ���... ��й�ȣ�� �𸧽÷�...\n", lor->GetID());
		return;
	}
}

void OrdReqProc(EHPacket* ep, SOCKET sock)
{
	OrdReq* rr = new OrdReq(ep);
	OrdData* od = FindOrdData(rr->GetName());
	int result = ORD_RES_NO;
	if (od)
	{
		printf("��� �����մϴ�.\n");
	}
	else
	{
		AddOrdData(rr->GetName(), rr->GetPrice(), rr->GetTotal());

		result = ORD_RES_OK;
		printf("%s %s %s �ֹ� ����\n", rr->GetName(), rr->GetPrice(), rr->GetTotal());
	}
	OrdRes* rres = new OrdRes(result);
	rres->Send(sock);
	delete rres;
}

DWORD DoIt(LPVOID param)
{
	SOCKET sock = (SOCKET)param;
	EHPacket* ep = new EHPacket(sock);
	switch (ep->GetMsgID())
	{
	case REG_REQ: RegReqProc(ep, sock); break;
		//case UNREG_REQ: UnRegReqProc(ep, sock); break;
	case LOGIN_REQ: LoginReqProc(ep, sock); break;
	case LOGOUT_REQ: LogoutReqProc(ep, sock); break;
	case ORD_REQ: OrdReqProc(ep, sock); break;

	}
	closesocket(sock);
	return 0;
}