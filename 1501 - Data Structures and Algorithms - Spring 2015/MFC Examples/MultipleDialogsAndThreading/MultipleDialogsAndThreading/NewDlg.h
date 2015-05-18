#pragma once
#include "afxwin.h"


// CNewDlg dialog

class CNewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewDlg)

public:
	CNewDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewDlg();

// Dialog Data
	enum { IDD = IDD_NEW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonUpdate();
	CListBox m_ListControl;
};
