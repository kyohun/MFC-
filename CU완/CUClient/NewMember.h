#pragma once
#include "afxdialogex.h"


// NewMember 대화 상자

class NewMember : public CDialogEx
{
	DECLARE_DYNAMIC(NewMember)

public:
	NewMember(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~NewMember();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit name;
	CEdit userid;
	CEdit userpw;
	afx_msg void OnBnClickedButtonNew();
	SOCKET Connect();
};
