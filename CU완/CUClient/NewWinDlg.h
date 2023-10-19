#pragma once
#include "afxdialogex.h"
#include "..\\EHPacketLib\\EHPacket.h"
#include "..\\OrdLib\\OrdReq.h"
#include "..\\OrdLib\\OrdRes.h"
#include "..\\OrdLib\\UnOrdReq.h"

#pragma comment(lib,"..\\x64\\Debug\\EHPacketLib.lib")
#pragma comment(lib,"..\\x64\\Debug\\OrdLib.lib")

#include <vector>

// NewWinDlg 대화 상자

using namespace std;

class NewWinDlg : public CDialogEx
{
	DECLARE_DYNAMIC(NewWinDlg)

public:
	NewWinDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~NewWinDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWWIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox ord_combo;
	CListCtrl List_Client;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo();
	CString ORD_NAME;
	CString ORD_PRICE;
	SOCKET Connect();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	int spin_value = 0;
	CStatic m_img;
	vector <CString> img11;
};
