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
		printf("(%s) 이미 가입 상태의 ID입니다.\n", rr->GetID());
	}
	else
	{
		//DBControl* dbc = DBControl::GetInstance();
		AddUserData(rr->GetID(), rr->GetPW(), rr->GetName());

		//wchar_t query_str[100] = TEXT("");
		//wsprintf(query_str, TEXT("INSERT INTO CLIENTLIST (CID, CPW, CNAME) VALUES ('%s', '%s', '%s')"), rr->GetID(), rr->GetPW(), rr->GetName());

		result = REG_RES_OK;
		printf("%s %s %s 가입 성공\n", rr->GetID(), rr->GetPW(), rr->GetName());

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
		printf("크래커(black 해커)가 들어왔나벼\n");
		return;
	}
	if (strcmp(ud->pw, urr->GetPW()) == 0)
	{
		RemoveUserData(urr->GetID());
		printf("%s 탈퇴하였습니다.\n", urr->GetID());
	}
	else
	{
		printf("아마도 크래커(black 해커)가 들어왔나벼... 비밀번호도 모름시롱...\n");
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
		printf("(%s) 아이디가 없는데 로그인 요청했네요.\n", lr->GetID());
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
				printf("%s %s 로그인 성공\n", lr->GetID(), lr->GetPW());
			}
		}
		else
		{
			result = LOGIN_RES_NOC;
			printf("(%s) 비밀번호를 다르게 로그인 요청했네요.\n", lr->GetID());
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
		printf("크래커(black 해커)가 들어왔나벼(%s 없음)\n", lor->GetID());
		return;
	}
	if (strcmp(ud->pw, lor->GetPW()) == 0)
	{
		if (ud->status != LOGINED)
		{
			printf("크래커(black 해커)가 들어왔나벼(%s 로긴 상태가 아닌데 로그 아웃 요청)\n", lor->GetID());
		}
		else
		{
			ud->status = REGED;
			printf("%s 로그 아웃 하였습니다.\n", lor->GetID());
		}
	}
	else
	{
		printf("%s 아마도 크래커(black 해커)가 들어왔나벼... 비밀번호도 모름시롱...\n", lor->GetID());
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
		printf("재고가 부족합니다.\n");
	}
	else
	{
		AddOrdData(rr->GetName(), rr->GetPrice(), rr->GetTotal());

		result = ORD_RES_OK;
		printf("%s %s %s 주문 성공\n", rr->GetName(), rr->GetPrice(), rr->GetTotal());
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