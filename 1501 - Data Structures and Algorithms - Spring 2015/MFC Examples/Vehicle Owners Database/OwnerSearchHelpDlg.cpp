// OwnerSearchHelpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vehicle Owners Database.h"
#include "OwnerSearchHelpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COwnerSearchHelpDlg dialog


COwnerSearchHelpDlg::COwnerSearchHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COwnerSearchHelpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COwnerSearchHelpDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COwnerSearchHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COwnerSearchHelpDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COwnerSearchHelpDlg, CDialog)
	//{{AFX_MSG_MAP(COwnerSearchHelpDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COwnerSearchHelpDlg message handlers

void COwnerSearchHelpDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
