// Vehicle Owners DatabaseDlg.h : header file
//

#if !defined(AFX_VEHICLEOWNERSDATABASEDLG_H__A2668F2D_142A_4E7E_8105_DDEB8330622D__INCLUDED_)
#define AFX_VEHICLEOWNERSDATABASEDLG_H__A2668F2D_142A_4E7E_8105_DDEB8330622D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVehicleOwnersDatabaseDlg dialog

class CVehicleOwnersDatabaseDlg : public CDialog
{
// Construction
public:
	CVehicleOwnersDatabaseDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CVehicleOwnersDatabaseDlg)
	enum { IDD = IDD_VEHICLEOWNERSDATABASE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVehicleOwnersDatabaseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVehicleOwnersDatabaseDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExit();
	afx_msg void OnBUTTONAddaNewVehicle();
	afx_msg void OnButtonSearchownerslist();
	afx_msg void OnButtonSearchremovevehicle();
	afx_msg void OnAbout();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VEHICLEOWNERSDATABASEDLG_H__A2668F2D_142A_4E7E_8105_DDEB8330622D__INCLUDED_)
