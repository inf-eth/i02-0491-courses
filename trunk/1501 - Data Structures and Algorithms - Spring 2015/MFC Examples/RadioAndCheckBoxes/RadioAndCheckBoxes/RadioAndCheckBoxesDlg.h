
// RadioAndCheckBoxesDlg.h : header file
//

#pragma once


// CRadioAndCheckBoxesDlg dialog
class CRadioAndCheckBoxesDlg : public CDialogEx
{
// Construction
public:
	CRadioAndCheckBoxesDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RADIOANDCHECKBOXES_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	BOOL m_RadioChoice;
	BOOL m_Check1;
	BOOL m_Check2;
	BOOL m_Check3;
	int m_Radio;
	afx_msg void OnBnClickedButtonRadio();
	afx_msg void OnBnClickedButtonCheck();
};
