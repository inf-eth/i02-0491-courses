#if !defined(AFX_OWNERSEARCHHELPDLG_H__A3D017F3_F035_47CD_AA51_9177B794623A__INCLUDED_)
#define AFX_OWNERSEARCHHELPDLG_H__A3D017F3_F035_47CD_AA51_9177B794623A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OwnerSearchHelpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COwnerSearchHelpDlg dialog

class COwnerSearchHelpDlg : public CDialog
{
// Construction
public:
	COwnerSearchHelpDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COwnerSearchHelpDlg)
	enum { IDD = IDD_OWNERSEARCHHELP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COwnerSearchHelpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COwnerSearchHelpDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OWNERSEARCHHELPDLG_H__A3D017F3_F035_47CD_AA51_9177B794623A__INCLUDED_)
