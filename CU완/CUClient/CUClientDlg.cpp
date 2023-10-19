
// CUClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CUClient.h"
#include "CUClientDlg.h"
#include "afxdialogex.h"
#include <afxdb.h>
#include "DBControl.h"
#include "NewMember.h"

#include "..\\EHPacketLib\\EHPacket.h"
#include "..\\LogLib\\LoginReq.h"
#include "..\\LogLib\\LoginRes.h"
#include "..\\LogLib\\LogoutReq.h"
#include "..\\common\\ehdef.h"
#include "useridsingle.h"

#pragma comment(lib,"..\\x64\\Debug\\EHPacketLib.lib")
#pragma comment(lib,"..\\x64\\Debug\\LogLib.lib")
#pragma comment(lib,"ws2_32")

#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCUClientDlg 대화 상자



CCUClientDlg::CCUClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCUClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ID, LogID);
	DDX_Control(pDX, IDC_EDIT_PW, LOGPW);
}

BEGIN_MESSAGE_MAP(CCUClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CCUClientDlg::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CCUClientDlg::OnBnClickedButtonLogin)
END_MESSAGE_MAP()


// CCUClientDlg 메시지 처리기

BOOL CCUClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCUClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCUClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCUClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


SOCKET CCUClientDlg::Connect()
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


void CCUClientDlg::OnBnClickedButtonNew()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NewMember* Nm = new NewMember();
	Nm->Create(IDD_DIALOG_MEM);
	Nm->ShowWindow(SW_SHOW);
}


void CCUClientDlg::OnBnClickedButtonLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DBControl* dbc = DBControl::GetInstance();

	CString strID, strPW;

	GetDlgItemText(IDC_EDIT_ID, strID);
	GetDlgItemText(IDC_EDIT_PW, strPW);

	//printf("===로그인 요청===\n");

	SOCKET sock = Connect();
	if (Connect() == -1)
	{
		return;
	}

	CStringA aaa = (CStringA)strID;
	const char* id_c = aaa.GetBuffer();
	CStringA aaaa = (CStringA)strPW;
	const char* pw_c = aaaa.GetBuffer();

	LoginReq* lr = new LoginReq(id_c, pw_c);
	lr->Send(sock);
	delete lr;

	EHPacket* ep = new EHPacket(sock);
	LoginRes* lres = new LoginRes(ep);//로긴 요청 결과 수신
	int result = lres->GetResult();

	if (lres->GetResult() == LOGIN_RES_OK)
	{
		useridsingle* uis = useridsingle::GetInstance();
		uis->SetuserID(strID);
		MessageBox(TEXT("로그인 성공"));
		Management* Mg = new Management();
		Mg->Create(IDD_DIALOG_LIST);
		Mg->ShowWindow(SW_SHOW);

	}
	else
	{
		switch (result)
		{
		case LOGIN_RES_ALR:  MessageBox(TEXT("이미 로그인중입니다")); break;
		case LOGIN_RES_NOC:  MessageBox(TEXT("비밀 번호가 다릅니다")); break;
		case LOGIN_RES_NOI:  MessageBox(TEXT("아이디가 다릅니다")); break;
		default:   MessageBox(TEXT("알수없는 오류입니다.")); break;
		}
	}
	delete lres;
	closesocket(sock);
}


void CCUClientDlg::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CString strID, strPW;

	GetDlgItemText(IDC_EDIT_ID, strID);
	GetDlgItemText(IDC_EDIT_PW, strPW);

	SOCKET sock = Connect();
	if (Connect() == -1)
	{
		return;
	}

	CStringA aaa = (CStringA)strID;
	const char* id_c = aaa.GetBuffer();
	CStringA aaaa = (CStringA)strPW;
	const char* pw_c = aaaa.GetBuffer();

	LogoutReq* lor = new LogoutReq(id_c, pw_c);
	lor->Send(sock);
	delete lor;
	closesocket(sock);


	DBControl* dbc = DBControl::GetInstance();
	dbc->Close();

	CDialogEx::OnCancel();
}
