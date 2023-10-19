// OrderRecordDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CUClient.h"
#include "afxdialogex.h"
#include "OrderRecordDlg.h"
#include "DBControl.h"
#include "useridsingle.h"


// OrderRecordDlg 대화 상자

IMPLEMENT_DYNAMIC(OrderRecordDlg, CDialogEx)

OrderRecordDlg::OrderRecordDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ORDERRECORD, pParent)
{

}

OrderRecordDlg::~OrderRecordDlg()
{
}

void OrderRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, clist);
}


BEGIN_MESSAGE_MAP(OrderRecordDlg, CDialogEx)
END_MESSAGE_MAP()


// OrderRecordDlg 메시지 처리기


BOOL OrderRecordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	DBControl* dbc = DBControl::GetInstance();
	CRecordset* rs = dbc->Select();
	//유저 아이디 가져오기
	useridsingle* uis = useridsingle::GetInstance();
	wchar_t idbuf[256];
	wsprintf(idbuf, TEXT("select * from SERORDER where cname = '%s'"), uis->GetuserID());
	rs->Open(CRecordset::forwardOnly, idbuf);
	CString no, name, num, datetime;
	int i = 0;
	clist.InsertColumn(0, TEXT("물품 이름"), 0, 50);
	clist.InsertColumn(1, TEXT("물품 수량"), 0, 70);
	clist.InsertColumn(2, TEXT("주문 시간"), 0, 150);
	while (!rs->IsEOF())
	{
		rs->GetFieldValue((short)1, no);
		rs->GetFieldValue((short)2, name);
		rs->GetFieldValue((short)3, datetime);
		clist.InsertItem(i, no);
		clist.SetItemText(i, 1, name);
		clist.SetItemText(i, 2, datetime);
		i++;
		rs->MoveNext();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
