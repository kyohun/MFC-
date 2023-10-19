// InventoryDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CUClient.h"
#include "afxdialogex.h"
#include "InventoryDlg.h"
#include <afxdb.h>
#include "DBControl.h"


// InventoryDlg 대화 상자

IMPLEMENT_DYNAMIC(InventoryDlg, CDialogEx)

InventoryDlg::InventoryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INVENTORY_DIALOG, pParent)
{

}

InventoryDlg::~InventoryDlg()
{
}

void InventoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INVENTORY, listctrl);
}


BEGIN_MESSAGE_MAP(InventoryDlg, CDialogEx)
END_MESSAGE_MAP()


// InventoryDlg 메시지 처리기


BOOL InventoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	listctrl.InsertColumn(0, TEXT("상품 번호"), 0, 100);
	listctrl.InsertColumn(1, TEXT("상품 이름"), 0, 100);
	listctrl.InsertColumn(2, TEXT("상품 가격"), 0, 100);
	listctrl.InsertColumn(3, TEXT("상품 수량"), 0, 100);

	DBControl* dbc = DBControl::GetInstance();

	CRecordset* rs = dbc->Select();
	rs->Open(CRecordset::forwardOnly, TEXT("select * from CPLIST"));

	CString pid, pname, price, desc;
	int i = 0;

	while (!rs->IsEOF())
	{
		rs->GetFieldValue((short)0, pid);
		rs->GetFieldValue((short)1, pname);
		rs->GetFieldValue((short)2, price);
		rs->GetFieldValue((short)3, desc);
		listctrl.InsertItem(i, pid);
		listctrl.SetItemText(i, 1, pname);
		listctrl.SetItemText(i, 2, price);
		listctrl.SetItemText(i, 3, desc);
		i++;
		rs->MoveNext();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
