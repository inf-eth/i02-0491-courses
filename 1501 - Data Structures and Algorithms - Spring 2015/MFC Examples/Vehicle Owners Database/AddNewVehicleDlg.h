#if !defined(AFX_ADDNEWVEHICLEDLG_H__C633818A_76F9_456D_8F5E_645EF5D7E439__INCLUDED_)
#define AFX_ADDNEWVEHICLEDLG_H__C633818A_76F9_456D_8F5E_645EF5D7E439__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddNewVehicleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddNewVehicleDlg dialog

class CAddNewVehicleDlg : public CDialog
{
// Construction
public:
	CAddNewVehicleDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddNewVehicleDlg)
	enum { IDD = IDD_DIALOG_ADDNEWVEHICLE_DIALOG };
	CString	m_FirstName;
	CString	m_LastName;
	CString	m_PermanentAddress;
	int		m_SIN;
	CString	m_TelephoneNo;
	CString	m_EngineSize;
	CString	m_RegistrationNo;
	CString	m_VehicleMake;
	int		m_VIN;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddNewVehicleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddNewVehicleDlg)
	afx_msg void OnButtonMainmenu();
	afx_msg void OnButtonAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDNEWVEHICLEDLG_H__C633818A_76F9_456D_8F5E_645EF5D7E439__INCLUDED_)
