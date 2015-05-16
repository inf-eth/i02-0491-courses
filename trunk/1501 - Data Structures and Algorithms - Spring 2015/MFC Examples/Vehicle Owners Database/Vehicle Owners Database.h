// Vehicle Owners Database.h : main header file for the VEHICLE OWNERS DATABASE application
//

#if !defined(AFX_VEHICLEOWNERSDATABASE_H__B2553976_3397_423F_8D2F_0308A868DEAC__INCLUDED_)
#define AFX_VEHICLEOWNERSDATABASE_H__B2553976_3397_423F_8D2F_0308A868DEAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVehicleOwnersDatabaseApp:
// See Vehicle Owners Database.cpp for the implementation of this class
//

class CVehicleOwnersDatabaseApp : public CWinApp
{
public:
	CVehicleOwnersDatabaseApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVehicleOwnersDatabaseApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVehicleOwnersDatabaseApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VEHICLEOWNERSDATABASE_H__B2553976_3397_423F_8D2F_0308A868DEAC__INCLUDED_)
