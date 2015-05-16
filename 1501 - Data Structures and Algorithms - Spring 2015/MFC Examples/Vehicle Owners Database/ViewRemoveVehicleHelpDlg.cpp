// ViewRemoveVehicleHelpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vehicle Owners Database.h"
#include "ViewRemoveVehicleHelpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewRemoveVehicleHelpDlg dialog


CViewRemoveVehicleHelpDlg::CViewRemoveVehicleHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CViewRemoveVehicleHelpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewRemoveVehicleHelpDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CViewRemoveVehicleHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewRemoveVehicleHelpDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewRemoveVehicleHelpDlg, CDialog)
	//{{AFX_MSG_MAP(CViewRemoveVehicleHelpDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewRemoveVehicleHelpDlg message handlers

void CViewRemoveVehicleHelpDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
