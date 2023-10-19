
// CUServerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CUServer.h"
#include "CUServerDlg.h"
#include "afxdialogex.h"
#include "DBControl.h"
#include "DlgTab1.h"

#include <afxdb.h>
//#include "DBControl.h"
//#include "NewMember.h"

#include "..\\EHPacketLib\\EHPacket.h"
#include "..\\LogLib\\LoginReq.h"
#include "..\\LogLib\\LoginRes.h"
#include "..\\LogLib\\LogoutReq.h"
#include "..\\common\\ehdef.h"

#pragma comment(lib,"..\\x64\\Debug\\EHPacketLib.lib")
#pragma comment(lib,"..\\x64\\Debug\\LogLib.lib")
#pragma comment(lib,"ws2_32")
#pragma warning (disable : 4996)

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


// CCUServerDlg 대화 상자



CCUServerDlg::CCUServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCUServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_tab);
}

BEGIN_MESSAGE_MAP(CCUServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CCUServerDlg::OnSelchangeTabMain)
END_MESSAGE_MAP()


// CCUServerDlg 메시지 처리기

SOCKET CCUServerDlg::Connect()
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


BOOL CCUServerDlg::OnInitDialog()
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

	SOCKET sock = Connect();
	DBControl* dbc = DBControl::GetInstance();
	//m_isworkingThread = true;
	//m_pThread = AfxBeginThread(ThreadForCounting, this);

	CRect rect;
	m_tab.GetWindowRect(rect);
	
	m_tab.InsertItem(0, (CString)"점주 목록");
	m_tab.InsertItem(1, (CString)"서버 재고");

	m_tab.SetCurSel(0);

	c_dlg1 = new CDlgTab1;
	c_dlg1->Create(IDD_DIALOG_1, &m_tab);
	c_dlg1->MoveWindow(0, 20, rect.Width(), rect.Height());
	c_dlg1->ShowWindow(SW_SHOW);

	c_dlg2 = new CDlgTab2;
	c_dlg2->Create(IDD_DIALOG_2, &m_tab);
	c_dlg2->MoveWindow(0, 20, rect.Width(), rect.Height());
	c_dlg2->ShowWindow(SW_HIDE);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCUServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCUServerDlg::OnPaint()
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
HCURSOR CCUServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCUServerDlg::OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	DBControl* dbc = DBControl::GetInstance();
	CRecordset* rs = dbc->Select();
	
	CString pid, name, id, pw;
	wchar_t idbuf[256];
	
	int i = 0;
	int num = 1;
	if (IDC_TAB_MAIN == pNMHDR->idFrom)
	{
		int select = m_tab.GetCurSel();
		switch (select)
		{
		case 0:
			
			c_dlg1->ShowWindow(SW_SHOW);

			rs->Open(CRecordset::forwardOnly, TEXT("select * from CLIENTLIST"));

			c_dlg1->m_list.DeleteAllItems();

			while (!rs->IsEOF())
			{
				pid.Format(_T("%d"), num);
				rs->GetFieldValue((short)0, name);
				rs->GetFieldValue((short)1, id);
				rs->GetFieldValue((short)2, pw);

				c_dlg1->m_list.InsertItem(i, pid);
				c_dlg1->m_list.SetItemText(i, 1, name);
				c_dlg1->m_list.SetItemText(i, 2, id);
				c_dlg1->m_list.SetItemText(i, 3, pw);
				
				num++;
				i++;
				rs->MoveNext();
			}

			c_dlg2->ShowWindow(SW_HIDE);
			break;
		case 1:
			c_dlg1->ShowWindow(SW_HIDE);
			rs->Open(CRecordset::forwardOnly, TEXT("select * from SERORDER"));

			c_dlg2->m_list.DeleteAllItems();

			while (!rs->IsEOF())
			{
				pid.Format(_T("%d"), num);
				rs->GetFieldValue((short)0, name);
				rs->GetFieldValue((short)1, id);
				rs->GetFieldValue((short)2, pw);

				c_dlg2->m_list.InsertItem(i, pid);
				c_dlg2->m_list.SetItemText(i, 1, name);
				c_dlg2->m_list.SetItemText(i, 2, id);
				c_dlg2->m_list.SetItemText(i, 3, pw);

				num++;
				i++;
				rs->MoveNext();
			}
			c_dlg2->ShowWindow(SW_SHOW);
			break;
		}
	}

	*pResult = 0;
}

