// DlgTab2.cpp: 구현 파일
//

#include "pch.h"
#include "CUServer.h"
#include "afxdialogex.h"
#include "DlgTab2.h"
#include <afxdb.h>


// CDlgTab2 대화 상자

IMPLEMENT_DYNAMIC(CDlgTab2, CDialogEx)

CDlgTab2::CDlgTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_2, pParent)
{

}

CDlgTab2::~CDlgTab2()
{
}

void CDlgTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
}


BEGIN_MESSAGE_MAP(CDlgTab2, CDialogEx)
END_MESSAGE_MAP()


// CDlgTab2 메시지 처리기


BOOL CDlgTab2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_list.InsertColumn(0, TEXT("물품 번호"), 0, 70);
	m_list.InsertColumn(1, TEXT("점주 이름"), 0, 70);
	m_list.InsertColumn(2, TEXT("물품 이름"), 0, 50);
	m_list.InsertColumn(3, TEXT("물품 수량"), 0, 70);

	CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=system;uid=scott;PWD=tiger"));
	if (re == FALSE)
	{
		return 0;
	}

	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, TEXT("select * from SERVER"));

	CString pid, pname, price, desc;
	int i = 0;


	while (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0, pid);
		rs.GetFieldValue((short)1, pname);
		rs.GetFieldValue((short)2, price);
		rs.GetFieldValue((short)3, desc);

		m_list.InsertItem(i, pid);
		m_list.SetItemText(i, 1, pname);
		m_list.SetItemText(i, 2, price);
		m_list.SetItemText(i, 3, desc);
		i++;
		rs.MoveNext();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
