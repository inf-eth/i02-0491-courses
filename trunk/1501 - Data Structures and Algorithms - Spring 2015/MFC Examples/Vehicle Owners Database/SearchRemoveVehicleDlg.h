#if !defined(AFX_SEARCHREMOVEVEHICLEDLG_H__B5CCAD29_014D_4C92_A3C7_C99CF652A7A8__INCLUDED_)
#define AFX_SEARCHREMOVEVEHICLEDLG_H__B5CCAD29_014D_4C92_A3C7_C99CF652A7A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchRemoveVehicleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchRemoveVehicleDlg dialog

class CSearchRemoveVehicleDlg : public CDialog
{
// Construction
public:
	CSearchRemoveVehicleDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSearchRemoveVehicleDlg)
	enum { IDD = IDD_SEARCHREMOVEVEHICLE_DIALOG };
	CString	m_EngineSize;
	CString	m_RegistrationNo;
	CString	m_VehicleMake;
	int		m_VIN;
	int		m_SearchByVIN;
	int		m_RemoveByVIN;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchRemoveVehicleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchRemoveVehicleDlg)
	afx_msg void OnMainmenu();
	afx_msg void OnButtonFind();
	afx_msg void OnButtonDeletevehicle();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHREMOVEVEHICLEDLG_H__B5CCAD29_014D_4C92_A3C7_C99CF652A7A8__INCLUDED_)
