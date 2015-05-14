
// MFCClientDlg.h : header file
//

#pragma once

#include "Client.h"
struct Complex
{
	float real;
	float img;
};
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
	int m_Port;
	CString m_IP;
	CString m_Status;
	afx_msg void OnBnClickedButtonConnect();
	float m_A_img;
	float m_A_real;
	float m_B_img;
	float m_B_real;
	float m_Result_img;
	float m_Result_real;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSubtract();
	afx_msg void OnBnClickedButtonDivide();
	afx_msg void OnBnClickedButtonMultiply();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
