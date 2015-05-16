#if !defined(AFX_OWNEDVEHICLESDLG_H__BE85987C_9200_4CB7_9755_15F4A92A94CA__INCLUDED_)
#define AFX_OWNEDVEHICLESDLG_H__BE85987C_9200_4CB7_9755_15F4A92A94CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OwnedVehiclesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COwnedVehiclesDlg dialog

class COwnedVehiclesDlg : public CDialog
{
// Construction
public:
	COwnedVehiclesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COwnedVehiclesDlg)
	enum { IDD = IDD_OWNEDVEHICLES_DIALOG };
	CString	m_EngineSize;
	CString	m_RegistrationNo;
	CString	m_VehicleMake;
	int		m_VIN;
	int		m_TotalVehiclesOwned;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COwnedVehiclesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COwnedVehiclesDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonNext();
	afx_msg void OnButtonPrevious();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OWNEDVEHICLESDLG_H__BE85987C_9200_4CB7_9755_15F4A92A94CA__INCLUDED_)
