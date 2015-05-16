
// ComboAndListBoxDlg.h : header file
//

#pragma once


// CComboAndListBoxDlg dialog
class CComboAndListBoxDlg : public CDialogEx
{
// Construction
public:
	CComboAndListBoxDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_COMBOANDLISTBOX_DIALOG };

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
	CString m_FirstName;
	CString m_LastName;
	CListBox m_ListControl;
	CComboBox m_ComboControl;
	afx_msg void OnBnClickedButtonAdd();
};
