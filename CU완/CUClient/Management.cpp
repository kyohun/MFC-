// Management.cpp: 구현 파일
//

#include "pch.h"
#include "CUClient.h"
#include "afxdialogex.h"
#include "Management.h"
#include <afxdb.h>
#include "DBControl.h"
#include "SellRecordDlg.h"

#pragma comment(lib,"ws2_32")

#pragma warning(disable:4996)

// Management 대화 상자

IMPLEMENT_DYNAMIC(Management, CDialogEx)

Management::Management(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LIST, pParent)
{

}

Management::~Management()
{
}

void Management::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_OBJECT, clist);
	DDX_Control(pDX, IDC_EDIT_NAME, name);
	DDX_Control(pDX, IDC_EDIT_NUM, num);
}


BEGIN_MESSAGE_MAP(Management, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_INPUT, &Management::OnBnClickedButtonInput)
	ON_BN_CLICKED(IDC_BUTTON_SELL, &Management::OnBnClickedButtonSell)
	ON_BN_CLICKED(IDC_BUTTON_ORDER, &Management::OnBnClickedButtonOrder)
	ON_BN_CLICKED(IDC_BUTTON_NOW, &Management::OnBnClickedButtonNow)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, &Management::OnBnClickedButtonRecord)
END_MESSAGE_MAP()


// Management 메시지 처리기


BOOL Management::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	i = 0, b = 1, total_price = 0;
	SetDlgItemText(IDC_EDIT_TOTAL, TEXT("0"));
	num.SetWindowText(TEXT(""));
	name.SetWindowText(TEXT(""));
	clist.DeleteAllItems();
	clist.InsertColumn(0, TEXT("No"), 0, 50);
	clist.InsertColumn(1, TEXT("제품 이름"), 0, 70);
	clist.InsertColumn(2, TEXT("제품 가격"), 0, 100);
	clist.InsertColumn(3, TEXT("구매 수량"), 0, 60);
	clist.InsertColumn(4, TEXT("합계"), 0, 100);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.

}

SOCKET Management::Connect()
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

void Management::OnBnClickedButtonInput()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString productid, productname, productprice, productnum, total_pirce_c, totalprice;
	int pn, price, totalpriceint;
	name.GetWindowText(productname);
	num.GetWindowText(productnum);
	DBControl* dbc = DBControl::GetInstance();
	CRecordset* rs = dbc->Select();
	wchar_t selectbuf[256];
	wsprintf(selectbuf, TEXT("Select pprice from server where pname = '%s'"), productname);
	rs->Open(CRecordset::forwardOnly, selectbuf);
	while (!rs->IsEOF())
	{
		rs->GetFieldValue((short)0, productprice);
		rs->MoveNext();
	}
	pn = _wtoi(productnum);
	productid.Format(_T("%d"), b);
	price = _wtoi(productprice);
	totalpriceint = pn * price;
	totalprice.Format(_T("%d"), totalpriceint);

	clist.InsertItem(i, productid);            //No
	clist.SetItemText(i, 1, productname);      //제품 번호
	clist.SetItemText(i, 2, productprice);      //제품명
	clist.SetItemText(i, 3, productnum);      //재고량
	clist.SetItemText(i, 4, totalprice);

	num.SetWindowText(TEXT(""));
	name.SetWindowText(TEXT(""));

	total_price = total_price + (pn * price);
	total_pirce_c.Format(_T("%d"), total_price);
	SetDlgItemText(IDC_EDIT_TOTAL, total_pirce_c);

	i++;
	b++;
}


void Management::OnBnClickedButtonSell()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 리스트에 있는 값들을 받아와서 DB에 판매기록으로 저장
	CString cd;
	CTime cdate = CTime::GetCurrentTime();
	cd.Format(_T("%d-%d-%d-%d-%d-%d"), cdate.GetYear(), cdate.GetMonth(), cdate.GetDay(), cdate.GetHour(), cdate.GetMinute(), cdate.GetSecond());
	DBControl* dbc = DBControl::GetInstance();


	CRecordset* rs = dbc->Select();
	rs->Open(CRecordset::forwardOnly, TEXT("select * from CPLIST"));

	CString SALENAME;
	GetDlgItemText(IDC_EDIT_NAME, SALENAME);

	CString pname;
	int index = 0;
	vector<CString> p_pname;
	vector<CString> l_name;
	vector<CString> I_price;


	while (!rs->IsEOF())
	{
		rs->GetFieldValue((short)1, pname);
		p_pname.push_back(pname);

		rs->MoveNext();
	}

	rs->Close();
	//db.Close();

	for (int k = 0; k < i; k++)
	{
		l_name.push_back(clist.GetItemText(k, 1));
		I_price.push_back(clist.GetItemText(k, 3));
	}
	vector<CString> ::iterator it;

	int result = 0;

	for (int u = 0; u < l_name.size(); u++)
	{
		it = find(p_pname.begin(), p_pname.end(), l_name[u]);
		if (it == p_pname.end())
		{
			result += 1;
		}
		else
		{
			result;
		}
	}

	if (result != 0)
	{
		//printf("판매 못함\n");
		MessageBox(TEXT("판매 못함"));
	}
	else
	{
		for (int j = 0; j < i; j++) {
			wchar_t insertbuf[256];
			CString to;
			wsprintf(insertbuf, TEXT("insert into CLIENTSALE values ('%s', '%s', '%s')"), l_name[j], I_price[j], cd);
			dbc->ExecuteQuery(insertbuf);
			CRecordset* rs = dbc->Select();
			wsprintf(insertbuf, TEXT("select ptotal from cplist where pname = '%s'"), l_name[j]);
			rs->Open(CRecordset::forwardOnly, insertbuf);
			rs->GetFieldValue((short)0, to);
			int cnt = _ttoi(to);
			int count = _ttoi(I_price[j]);
			rs->Close();
			cnt -= count;
			to.Format(_T("%d"), cnt);
			wchar_t updatebuf[256];
			wsprintf(updatebuf, TEXT("update CPLIST set ptotal = '%s' where pname = '%s'"), to, l_name[j]);
			dbc->ExecuteQuery(updatebuf);
		}
		clist.DeleteAllItems();
		MessageBox(TEXT("판매 완료."));
		SetDlgItemText(IDC_EDIT_TOTAL, _T(""));
	}
	i = 0;
	b = 1;
}


void Management::OnBnClickedButtonOrder()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NewWinDlg* nw = new NewWinDlg();
	nw->Create(IDD_NEWWIN_DIALOG);
	nw->ShowWindow(SW_SHOW);
}


void Management::OnBnClickedButtonNow()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	InventoryDlg* itd = new InventoryDlg();
	itd->Create(IDD_INVENTORY_DIALOG);
	itd->ShowWindow(SW_SHOW);
}


void Management::OnBnClickedButtonRecord()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SellRecordDlg* srdlg = new SellRecordDlg();
	srdlg->Create(IDD_DIALOG_SELLRECORD);
	srdlg->ShowWindow(SW_SHOW);
}
