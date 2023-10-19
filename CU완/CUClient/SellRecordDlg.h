#pragma once
#include "afxdialogex.h"


// SellRecordDlg 대화 상자

class SellRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SellRecordDlg)

public:
	SellRecordDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SellRecordDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SELLRECORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl clist;
};
