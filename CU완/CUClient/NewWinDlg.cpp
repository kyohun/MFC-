// NewWinDlg.cpp: 구현 파일
//

#include "pch.h"
#include "CUClient.h"
#include "afxdialogex.h"
#include "NewWinDlg.h"
#include <afxdb.h>
#include "DBControl.h"
#include "..\\RegLib\\RegReq.h"
#include "..\\RegLib\\RegRes.h"
#include "useridsingle.h"
#include "OrderRecordDlg.h"
#include <vector>
#pragma comment(lib,"..\\x64\\Debug\\EHPacketLib.lib")
#pragma comment(lib,"..\\x64\\Debug\\RegLib.lib")
#pragma comment(lib,"ws2_32")

#pragma warning(disable:4996)


using namespace std;
// NewWinDlg 대화 상자

IMPLEMENT_DYNAMIC(NewWinDlg, CDialogEx)

NewWinDlg::NewWinDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEWWIN_DIALOG, pParent)
	, ORD_NAME(_T(""))
	, ORD_PRICE(_T(""))
{

}

NewWinDlg::~NewWinDlg()
{
}

void NewWinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO, ord_combo);
	DDX_Control(pDX, IDC_LIST_CLIENT, List_Client);
	DDX_Text(pDX, IDC_EDIT_ORD_NAME, ORD_NAME);
	DDX_Text(pDX, IDC_EDIT_ORD_PRICE, ORD_PRICE);
	DDX_Control(pDX, IDC_IMG, m_img);
}


BEGIN_MESSAGE_MAP(NewWinDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &NewWinDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO, &NewWinDlg::OnCbnSelchangeCombo)
	ON_BN_CLICKED(IDC_BUTTON2, &NewWinDlg::OnBnClickedButton2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN, &NewWinDlg::OnDeltaposSpin)
END_MESSAGE_MAP()


// NewWinDlg 메시지 처리기


BOOL NewWinDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	List_Client.InsertColumn(0, TEXT("no"), 0, 50);
	List_Client.InsertColumn(1, TEXT("제품 이름"), 0, 70);
	List_Client.InsertColumn(2, TEXT("제품 가격"), 0, 100);
	List_Client.InsertColumn(3, TEXT("재고 수"), 0, 60);

	DBControl* dbc = DBControl::GetInstance();
	/*CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=demo; uid = scott; PWD=tiger"));

	if (re == FALSE)
	{
		return TRUE;
	}*/

	CString pid;
	CString pname;
	CString price;
	CString total;
	CString image;

	CRecordset* rs = dbc->Select();
	CString aa[4];

	rs->Open(CRecordset::forwardOnly, TEXT("select* from SERVER"));
	int index = 0;
	while (!rs->IsEOF())
	{
		rs->GetFieldValue((short)0, pid);
		rs->GetFieldValue((short)1, pname);
		rs->GetFieldValue((short)2, price);
		rs->GetFieldValue((short)3, total);
		rs->GetFieldValue((short)4, image);

		img11.push_back(image);

		List_Client.InsertItem(index, pid);				//No
		List_Client.SetItemText(index, 1, pname);		//제품 번호
		List_Client.SetItemText(index, 2, price);		//제품명
		List_Client.SetItemText(index, 3, total);			//재고량

		ord_combo.AddString(pid);

		rs->MoveNext();
		index++;
	}
	rs->Close();
	//db.Close();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

SOCKET NewWinDlg::Connect()
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


void NewWinDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	// 리스트에 있는 값들을 받아와서 DB에 판매기록으로 저장
	CString cd;
	CTime cdate = CTime::GetCurrentTime();
	cd.Format(_T("%d-%d-%d-%d-%d-%d"), cdate.GetYear(), cdate.GetMonth(), cdate.GetDay(), cdate.GetHour(), cdate.GetMinute(), cdate.GetSecond());
	DBControl* dbc = DBControl::GetInstance();
	/*CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=demo; uid=scott; PWD=tiger"));*/
	wchar_t nbuf[256] = TEXT("");


	//ord_combo.SetCurSel(0);


	int num = 0;
	int num1 = 0;
	num = ord_combo.GetCurSel();	//1
	num1 = ord_combo.GetCurSel();	//1
	ord_combo.GetLBText(num, nbuf);
	ord_combo.GetLBText(num1, nbuf);

	num = _wtoi(nbuf);
	num1 = _wtoi(nbuf) - 1;

	SOCKET sock = Connect();
	if (Connect() == -1)
	{
		return;
	}

	if (num1 != 0)
	{

	}

	CString name = List_Client.GetItemText(num1, 1);
	CString price = List_Client.GetItemText(num1, 2);
	CString total = List_Client.GetItemText(num1, 3);

	int currentTotal = _wtoi(total);

	CString countStr;
	GetDlgItemText(IDC_EDIT_ORD_TOTAL, countStr);
	int soldCount = _wtoi(countStr);

	int newtotal = currentTotal + soldCount;

	CString newtotal_str;
	newtotal_str.Format(_T("%d"), newtotal);


	SetDlgItemText(IDC_EDIT_ORD_TOTAL, _T(""));

	CStringA aa = (CStringA)name;
	const char* name_c = aa.GetBuffer();

	CStringA aaa = (CStringA)price;
	const char* price_c = aaa.GetBuffer();

	CStringA aaaa = (CStringA)newtotal_str;
	const char* total_c = aaaa.GetBuffer();

	OrdReq* rr = new OrdReq(price_c, total_c, name_c);
	rr->Send(sock);
	delete rr;
	EHPacket* ep = new EHPacket(sock);
	OrdRes* rres = new OrdRes(ep);//가입 요청 결과 수신

	if (rres->GetResult() == ORD_RES_OK)
	{
		//printf("주문 성공\n");

		List_Client.SetItemText(num1, 3, newtotal_str);

		wchar_t total_buf1[256] = TEXT("");
		wsprintf(total_buf1, TEXT("%s"), newtotal_str);
		wchar_t query_str[512] = { 0 }; // 더 큰 버퍼 사용
		wsprintf(query_str, TEXT("update SERVER set PTOTAL = %s where PID = %s"), total_buf1, nbuf);
		dbc->ExecuteQuery(query_str);
		useridsingle* uis = useridsingle::GetInstance();
		wchar_t insert_str[256];
		wsprintf(insert_str, TEXT("insert into SERORDER (CNAME, CPNAME, CTOTAL, CDate) values ('%s', '%s', '%s', '%s')"), uis->GetuserID(), name, countStr, cd);
		dbc->ExecuteQuery(insert_str);
		spin_value = 0;
		SetDlgItemText(IDC_EDIT_ORD_NAME, TEXT(""));
		SetDlgItemText(IDC_EDIT_ORD_PRICE, TEXT(""));
		MessageBox(TEXT("주문 성공"), TEXT("확인"), MB_OK);
	}
	else
	{
		//printf("주문 실패(제고 없음)\n");
		MessageBox(TEXT("재고가 부족합니다."), TEXT("경고"), MB_ICONWARNING);
	}
}


void NewWinDlg::OnCbnSelchangeCombo()
{
	DBControl* dbc = DBControl::GetInstance();
	CRecordset* rs = dbc->Select();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = ord_combo.GetCurSel();
	if (index == -1)
	{
		ORD_NAME = TEXT("");
		ORD_PRICE = TEXT("");
	}
	else
	{
		img11.size();
		CString nos;
		ord_combo.GetLBText(index, nos);
		//rs->GetFieldValue(_T("P_IMAGE"), img);
		CString img;
		img = img11[index];
		CImage cimg;
		cimg.Load(img);

		// 이미지 컨트롤에 그림 그리기
		CDC* cdc = m_img.GetDC();
		RECT rt;
		m_img.GetClientRect(&rt);
		cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);


		int nos_i = _wtoi(nos) - 1;

		CString name = List_Client.GetItemText(nos_i, 1);
		CString price = List_Client.GetItemText(nos_i, 2);
		SetDlgItemText(IDC_EDIT_ORD_NAME, name);
		SetDlgItemText(IDC_EDIT_ORD_PRICE, price);
		/*ORD_NAME = name;
		ORD_PRICE = price;*/
	}
}



void NewWinDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OrderRecordDlg* ordlg = new OrderRecordDlg();
	ordlg->Create(IDD_DIALOG_ORDERRECORD);
	ordlg->ShowWindow(SW_SHOW);
}


void NewWinDlg::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (pNMUpDown->iDelta < 0)
	{
		spin_value++;
	}
	else
	{
		spin_value--;
	}
	SetDlgItemInt(IDC_EDIT_ORD_TOTAL, spin_value);
	*pResult = 0;
}

