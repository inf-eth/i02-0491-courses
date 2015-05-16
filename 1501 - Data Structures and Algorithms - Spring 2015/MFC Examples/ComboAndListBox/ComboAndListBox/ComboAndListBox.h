
// ComboAndListBox.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CComboAndListBoxApp:
// See ComboAndListBox.cpp for the implementation of this class
//

class CComboAndListBoxApp : public CWinApp
{
public:
	CComboAndListBoxApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CComboAndListBoxApp theApp;