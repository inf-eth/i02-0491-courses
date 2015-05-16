#if !defined(AFX_VIEWREMOVEVEHICLEHELPDLG_H__90770D2C_A7B9_4313_88DF_F87053BF1120__INCLUDED_)
#define AFX_VIEWREMOVEVEHICLEHELPDLG_H__90770D2C_A7B9_4313_88DF_F87053BF1120__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewRemoveVehicleHelpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewRemoveVehicleHelpDlg dialog

class CViewRemoveVehicleHelpDlg : public CDialog
{
// Construction
public:
	CViewRemoveVehicleHelpDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewRemoveVehicleHelpDlg)
	enum { IDD = IDD_REMOVEVEHICLEHELP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewRemoveVehicleHelpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewRemoveVehicleHelpDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWREMOVEVEHICLEHELPDLG_H__90770D2C_A7B9_4313_88DF_F87053BF1120__INCLUDED_)
