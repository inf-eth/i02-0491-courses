#if !defined(AFX_MAINHELPDLG_H__0B42A555_DE0E_4AFF_AD63_7E279DB58B50__INCLUDED_)
#define AFX_MAINHELPDLG_H__0B42A555_DE0E_4AFF_AD63_7E279DB58B50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainHelpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainHelpDlg dialog

class CMainHelpDlg : public CDialog
{
// Construction
public:
	CMainHelpDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainHelpDlg)
	enum { IDD = IDD_MAINHELP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainHelpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainHelpDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINHELPDLG_H__0B42A555_DE0E_4AFF_AD63_7E279DB58B50__INCLUDED_)
