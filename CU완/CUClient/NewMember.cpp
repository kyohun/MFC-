// NewMember.cpp: 구현 파일
//

#include "pch.h"
#include "CUClient.h"
#include "afxdialogex.h"
#include "NewMember.h"
#include <afxdb.h>
#include "DBControl.h"

#include "..\\EHPacketLib\\EHPacket.h"
#include "..\\RegLib\\RegReq.h"
#include "..\\RegLib\\RegRes.h"
#include "..\\RegLib\\UnRegReq.h"
#include "..\\LogLib\\LoginReq.h"
#include "..\\LogLib\\LoginRes.h"
#include "..\\LogLib\\LogoutReq.h"
#include "..\\common\\ehdef.h"

#pragma comment(lib,"..\\x64\\Debug\\EHPacketLib.lib")
#pragma comment(lib,"..\\x64\\Debug\\RegLib.lib")
#pragma comment(lib,"..\\x64\\Debug\\LogLib.lib")
#pragma comment(lib,"ws2_32")

#pragma warning(disable:4996)

// NewMember 대화 상자

IMPLEMENT_DYNAMIC(NewMember, CDialogEx)

NewMember::NewMember(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MEM, pParent)
{

}

NewMember::~NewMember()
{
}

void NewMember::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NM_NAME, name);
	DDX_Control(pDX, IDC_EDIT_NM_ID, userid);
	DDX_Control(pDX, IDC_EDIT_NM_PW, userpw);
}


BEGIN_MESSAGE_MAP(NewMember, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_NEW, &NewMember::OnBnClickedButtonNew)
END_MESSAGE_MAP()


// NewMember 메시지 처리기
SOCKET NewMember::Connect()
{
	//1.소켓 생성
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//2.연결
	SOCKADDR_IN servaddr = {};
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("192.168.0.49");
	servaddr.sin_port = htons(10200);
	if (connect(sock, (SOCKADDR*)&servaddr, sizeof(servaddr)) == -1)
	{
		return -1;
	}
	return sock;
}

void NewMember::OnBnClickedButtonNew()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DBControl* dbc = DBControl::GetInstance();
	CString strNAME, strID, strPW;

	GetDlgItemText(IDC_EDIT_NM_NAME, strNAME);
	GetDlgItemText(IDC_EDIT_NM_ID, strID);
	GetDlgItemText(IDC_EDIT_NM_PW, strPW);

	printf("===가입 요청===\n");
	//char id[MAX_ID_LEN] = "";
	//char pw[MAX_PW_LEN] = "";
	//char name[MAX_NAME_LEN] = "";

	SOCKET sock = Connect();
	if (Connect() == -1)
	{
		return;
	}
	CStringA aa = (CStringA)strNAME;
	const char* name_c = aa.GetBuffer();
	CStringA aaa = (CStringA)strID;
	const char* id_c = aaa.GetBuffer();
	CStringA aaaa = (CStringA)strPW;
	const char* pw_c = aaaa.GetBuffer();

	RegReq* rr = new RegReq(id_c, pw_c, name_c);
	rr->Send(sock);
	delete rr;

	EHPacket* ep = new EHPacket(sock);
	RegRes* rres = new RegRes(ep);//가입 요청 결과 수신

	if (rres->GetResult() == REG_RES_OK)
	{
		MessageBox(TEXT("가입 성공"));
		// Create an SQL query
		CString query;
		query.Format(_T("INSERT INTO CLIENTLIST (CID, CPW, CNAME) VALUES ('%s', '%s', '%s')"), strID, strPW, strNAME);

		// Execute the query using the DBControl instance
		dbc->ExecuteQuery(query);

	}
	else
	{
		MessageBox(TEXT("가입 실패"));
	}
	delete rres;
	closesocket(sock);
}