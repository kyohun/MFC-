// SellRecordDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CUClient.h"
#include "afxdialogex.h"
#include "SellRecordDlg.h"
#include "DBControl.h"


// SellRecordDlg 대화 상자

IMPLEMENT_DYNAMIC(SellRecordDlg, CDialogEx)

SellRecordDlg::SellRecordDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SELLRECORD, pParent)
{

}

SellRecordDlg::~SellRecordDlg()
{
}

void SellRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, clist);
}


BEGIN_MESSAGE_MAP(SellRecordDlg, CDialogEx)
END_MESSAGE_MAP()


// SellRecordDlg 메시지 처리기


BOOL SellRecordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	DBControl* dbc = DBControl::GetInstance();
	CRecordset* rs = dbc->Select();
	rs->Open(CRecordset::forwardOnly, TEXT("select * from CLIENTSALE"));
	CString no, name, num, datetime;
	int i = 0;
	clist.InsertColumn(0, TEXT("No"), 0, 50);
	clist.InsertColumn(1, TEXT("물품 이름"), 0, 70);
	clist.InsertColumn(2, TEXT("판매 수량"), 0, 70);
	clist.InsertColumn(3, TEXT("판매 시간"), 0, 120);
	while (!rs->IsEOF())
	{
		rs->GetFieldValue((short)0, no);
		rs->GetFieldValue((short)1, name);
		rs->GetFieldValue((short)2, num);
		rs->GetFieldValue((short)3, datetime);
		clist.InsertItem(i, no);
		clist.SetItemText(i, 1, name);
		clist.SetItemText(i, 2, num);
		clist.SetItemText(i, 3, datetime);
		i++;
		rs->MoveNext();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
