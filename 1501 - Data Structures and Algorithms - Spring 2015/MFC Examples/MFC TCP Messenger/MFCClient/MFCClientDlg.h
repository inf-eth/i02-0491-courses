
// MFCClientDlg.h : header file
//

#pragma once

#include "Client.h"
#include "afxcmn.h"
#include "afxwin.h"
// CMFCClientDlg dialog
class CMFCClientDlg : public CDialogEx
{
// Construction
public:
	CMFCClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCCLIENT_DIALOG };

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
	Client ClientObj;
	CString m_Status;
	CString m_Server_IP;
	int m_Server_Port;
//	CString m_Input;
//	CString m_Output;
	afx_msg void OnEnChangeRicheditOutput();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CRichEditCtrl m_RichEdit_Output_Control;
	int AppendToOutput(CString Input);
	int GetNumVisibleLines(void);
	CString m_Input;
	CEdit m_Status_Control;
	CEdit m_Server_IP_Control;
	CEdit m_Server_Port_Control;
};
