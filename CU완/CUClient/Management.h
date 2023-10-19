#pragma once
#include "afxdialogex.h"
#include "NewWinDlg.h"
#include "InventoryDlg.h"
#include <vector>
using namespace std;

// Management 대화 상자

class Management : public CDialogEx
{
	DECLARE_DYNAMIC(Management)

public:
	Management(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Management();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl clist;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonInput();
	int i = 0;
	int b = 1;
	int total_price = 0;
	CEdit name;
	CEdit num;
	afx_msg void OnBnClickedButtonSell();
	afx_msg void OnBnClickedButtonOrder();
	afx_msg void OnBnClickedButtonNow();
	SOCKET Connect();
	afx_msg void OnBnClickedButtonRecord();
};
