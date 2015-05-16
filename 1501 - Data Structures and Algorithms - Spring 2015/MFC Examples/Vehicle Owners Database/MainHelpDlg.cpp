// MainHelpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vehicle Owners Database.h"
#include "MainHelpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainHelpDlg dialog


CMainHelpDlg::CMainHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainHelpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainHelpDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMainHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainHelpDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainHelpDlg, CDialog)
	//{{AFX_MSG_MAP(CMainHelpDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainHelpDlg message handlers

void CMainHelpDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
