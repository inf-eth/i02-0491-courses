// SearchOwnerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vehicle Owners Database.h"
#include "SearchOwnerDlg.h"
#include "OwnersList.h"
#include "OwnedVehiclesDlg.h"
#include "OwnerSearchHelpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern COwnersList *VehicleOwnersListPTR;

/////////////////////////////////////////////////////////////////////////////
// CSearchOwnerDlg dialog


CSearchOwnerDlg::CSearchOwnerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchOwnerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchOwnerDlg)
	m_FirstName = _T("");
	m_LastName = _T("");
	m_PermanentAddress = _T("");
	m_SIN = 0;
	m_TelephoneNo = _T("");
	m_SearchSIN = 0;
	//}}AFX_DATA_INIT
}


void CSearchOwnerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchOwnerDlg)
	DDX_Text(pDX, IDC_EDIT_OI_FIRSTNAME, m_FirstName);
	DDX_Text(pDX, IDC_EDIT_OI_LASTNAME, m_LastName);
	DDX_Text(pDX, IDC_EDIT_OI_PERMANENTADDRESS, m_PermanentAddress);
	DDX_Text(pDX, IDC_EDIT_OI_SIN, m_SIN);
	DDX_Text(pDX, IDC_EDIT_OI_TELEPHONENO, m_TelephoneNo);
	DDX_Text(pDX, IDC_EDIT_SEARCHBYSIN, m_SearchSIN);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchOwnerDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchOwnerDlg)
	ON_BN_CLICKED(IDC_BUTTON_OI_MAINMENU, OnButtonOiMainmenu)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnButtonFind)
	ON_BN_CLICKED(IDNEXT, OnNext)
	ON_BN_CLICKED(IDPREVIOUS, OnPrevious)
	ON_BN_CLICKED(IDC_BUTTON_OS_OWNEDVEHICLES, OnButtonOsOwnedvehicles)
	ON_BN_CLICKED(IDC_BUTTON_OS_HELP1, OnButtonOsHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchOwnerDlg message handlers

void CSearchOwnerDlg::OnButtonOiMainmenu() 
{
	// TODO: Add your control notification handler code here
	(*this).EndDialog ( 1 );
}

BOOL CSearchOwnerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	(*VehicleOwnersListPTR).ResetIndex ( );

	UpdateData ( true );
	
	m_FirstName = (*VehicleOwnersListPTR).GetFirstName ( );
	m_LastName = (*VehicleOwnersListPTR).GetLastName ( );
	m_PermanentAddress = (*VehicleOwnersListPTR).GetPermanentAddress ( );
	m_SIN = (*VehicleOwnersListPTR).GetSIN ( );
	m_TelephoneNo = (*VehicleOwnersListPTR).GetTelephoneNo ( );

	UpdateData ( false );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSearchOwnerDlg::OnButtonFind() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData ( true );
	
	// *** Performing a search for the owner with the given SIN ***

	// If the owner is found.
	if ( (*VehicleOwnersListPTR).SearchOwner ( m_SearchSIN ) == 1 )
	{
		
		AfxMessageBox ( "Owner found !!!", MB_ICONINFORMATION );

		m_FirstName = (*VehicleOwnersListPTR).GetFirstName ( );
		m_LastName = (*VehicleOwnersListPTR).GetLastName ( );
		m_PermanentAddress = (*VehicleOwnersListPTR).GetPermanentAddress ( );
		m_SIN = (*VehicleOwnersListPTR).GetSIN ( );
		m_TelephoneNo = (*VehicleOwnersListPTR).GetTelephoneNo ( );
			
	}

	// If the owner is not found.
	else
	{
	
		AfxMessageBox ( "Owner with that SIN does not exist.", MB_ICONSTOP );

	}

	UpdateData ( false );

	
}

void CSearchOwnerDlg::OnNext() 
{
	// TODO: Add your control notification handler code here
	(*VehicleOwnersListPTR).IndexForward ( );

	UpdateData ( true );
	
	m_FirstName = (*VehicleOwnersListPTR).GetFirstName ( );
	m_LastName = (*VehicleOwnersListPTR).GetLastName ( );
	m_PermanentAddress = (*VehicleOwnersListPTR).GetPermanentAddress ( );
	m_SIN = (*VehicleOwnersListPTR).GetSIN ( );
	m_TelephoneNo = (*VehicleOwnersListPTR).GetTelephoneNo ( );

	UpdateData ( false );
	
	return;

}

void CSearchOwnerDlg::OnPrevious() 
{
	// TODO: Add your control notification handler code here
	(*VehicleOwnersListPTR).IndexReverse ( );

	UpdateData ( true );
	
	m_FirstName = (*VehicleOwnersListPTR).GetFirstName ( );
	m_LastName = (*VehicleOwnersListPTR).GetLastName ( );
	m_PermanentAddress = (*VehicleOwnersListPTR).GetPermanentAddress ( );
	m_SIN = (*VehicleOwnersListPTR).GetSIN ( );
	m_TelephoneNo = (*VehicleOwnersListPTR).GetTelephoneNo ( );

	UpdateData ( false );
	
	return;
}

void CSearchOwnerDlg::OnButtonOsOwnedvehicles() 
{
	// TODO: Add your control notification handler code here
	COwnedVehiclesDlg OwnedVehiclesDialogObject;
	OwnedVehiclesDialogObject.DoModal ( );
	
}

void CSearchOwnerDlg::OnButtonOsHelp() 
{
	// TODO: Add your control notification handler code here
	COwnerSearchHelpDlg OwnerSearchHelpDlgObject;
	OwnerSearchHelpDlgObject.DoModal ( );
}
