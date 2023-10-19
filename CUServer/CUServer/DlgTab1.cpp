// DlgTab1.cpp: 구현 파일
//
#include <WinSock2.h>
#include "pch.h"
#include "CUServer.h"
#include "afxdialogex.h"
#include "DlgTab1.h"
#include <afxdb.h>

#pragma comment(lib,"ws2_32")
#pragma warning(disable:4996)
// CDlgTab1 대화 상자

IMPLEMENT_DYNAMIC(CDlgTab1, CDialogEx)

CDlgTab1::CDlgTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_1, pParent)
{

}

CDlgTab1::~CDlgTab1()
{
}

void CDlgTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CDlgTab1, CDialogEx)
	//ON_MESSAGE(MESSAGE_INCREASE_COUNT, &CDlgTab1::UpdateCount)
END_MESSAGE_MAP()

SOCKET CDlgTab1::Connect()
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


// CDlgTab1 메시지 처리기


BOOL CDlgTab1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SOCKET sock = Connect();

	//m_isWorkingThread = true;

	m_list.InsertColumn(0, TEXT("회원 번호"), 0, 70);
	m_list.InsertColumn(1, TEXT("회원 이름"), 0, 70);
	m_list.InsertColumn(2, TEXT("ID"), 0, 50);
	m_list.InsertColumn(3, TEXT("PW"), 0, 50);

	CDatabase db;
	db.OpenEx(TEXT("DSN=system;uid=scott;PWD=tiger"));
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, TEXT("select * from CLIENTLIST"));

	CString pid, pname, price, desc;
	int i = 0;
	int num = 1;

	while (!rs.IsEOF())
	{
		pid.Format(_T("%d"), num);
		rs.GetFieldValue((short)0, pname);
		rs.GetFieldValue((short)1, price);
		rs.GetFieldValue((short)2, desc);

		m_list.InsertItem(i, pid);
		m_list.SetItemText(i, 1, pname);
		m_list.SetItemText(i, 2, price);
		m_list.SetItemText(i, 3, desc);
		num++;
		i++;
		rs.MoveNext();
	}

	rs.Close();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
