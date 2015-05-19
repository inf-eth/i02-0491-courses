
// MFCServerDlg.h : header file
//

#pragma once

#include "Server.h"
#include "afxcmn.h"
#include "afxwin.h"
// CMFCServerDlg dialog
class CMFCServerDlg : public CDialogEx
{
// Construction
public:
	CMFCServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCSERVER_DIALOG };

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
	Server ServerObj;
	CString m_Status;
	CString m_Client_IP;
	int m_Client_Port;
	CString m_Input;
//	CString m_Output;
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CRichEditCtrl m_RichEdit_Output_Control;
	int AppendToOutput(CString Input);
	int GetNumVisibleLines(void);

	CEdit m_Status_Control;
	CEdit m_Client_IP_Control;
	CEdit m_Client_Port_Control;
};
