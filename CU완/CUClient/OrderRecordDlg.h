#pragma once
#include "afxdialogex.h"


// OrderRecordDlg 대화 상자

class OrderRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(OrderRecordDlg)

public:
	OrderRecordDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~OrderRecordDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ORDERRECORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl clist;
};
