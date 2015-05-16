#if !defined(AFX_SEARCHOWNERDLG_H__781FA4FC_3932_482D_8EDA_D2A0B1A6ED06__INCLUDED_)
#define AFX_SEARCHOWNERDLG_H__781FA4FC_3932_482D_8EDA_D2A0B1A6ED06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchOwnerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchOwnerDlg dialog

class CSearchOwnerDlg : public CDialog
{
// Construction
public:
	CSearchOwnerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSearchOwnerDlg)
	enum { IDD = IDD_SEARCHOWNER_DIALOG };
	CString	m_FirstName;
	CString	m_LastName;
	CString	m_PermanentAddress;
	int		m_SIN;
	CString	m_TelephoneNo;
	int		m_SearchSIN;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchOwnerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchOwnerDlg)
	afx_msg void OnButtonOiMainmenu();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonFind();
	afx_msg void OnNext();
	afx_msg void OnPrevious();
	afx_msg void OnButtonOsOwnedvehicles();
	afx_msg void OnButtonOsHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHOWNERDLG_H__781FA4FC_3932_482D_8EDA_D2A0B1A6ED06__INCLUDED_)
