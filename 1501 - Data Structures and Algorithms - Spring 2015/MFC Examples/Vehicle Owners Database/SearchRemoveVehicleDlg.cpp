// SearchRemoveVehicleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vehicle Owners Database.h"
#include "SearchRemoveVehicleDlg.h"
#include "OwnersLIst.h"
#include "ViewRemoveVehicleHelpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern COwnersList *VehicleOwnersListPTR;

/////////////////////////////////////////////////////////////////////////////
// CSearchRemoveVehicleDlg dialog


CSearchRemoveVehicleDlg::CSearchRemoveVehicleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchRemoveVehicleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchRemoveVehicleDlg)
	m_EngineSize = _T("");
	m_RegistrationNo = _T("");
	m_VehicleMake = _T("");
	m_VIN = 0;
	m_SearchByVIN = 0;
	m_RemoveByVIN = 0;
	//}}AFX_DATA_INIT
}


void CSearchRemoveVehicleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchRemoveVehicleDlg)
	DDX_Text(pDX, IDC_EDIT_SRV_ENGINESIZE, m_EngineSize);
	DDX_Text(pDX, IDC_EDIT_SRV_REGISTRATIONNO, m_RegistrationNo);
	DDX_Text(pDX, IDC_EDIT_SRV_VEHICLEMAKE, m_VehicleMake);
	DDX_Text(pDX, IDC_EDIT_SRV_VIN, m_VIN);
	DDX_Text(pDX, IDC_EDIT_SEARCHBYVIN, m_SearchByVIN);
	DDX_Text(pDX, IDC_EDIT_REMOVEVEHICLEBYVIN, m_RemoveByVIN);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchRemoveVehicleDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchRemoveVehicleDlg)
	ON_BN_CLICKED(IDMAINMENU, OnMainmenu)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_DELETEVEHICLE, OnButtonDeletevehicle)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchRemoveVehicleDlg message handlers

void CSearchRemoveVehicleDlg::OnMainmenu() 
{
	// TODO: Add your control notification handler code here
	(*this).EndDialog ( 1 );

}

void CSearchRemoveVehicleDlg::OnButtonFind() 
{

	// TODO: Add your control notification handler code here
	UpdateData ( true );

	// Find and bookmark the vehicle.

	if ( (*VehicleOwnersListPTR).BookmarkAVehicle ( m_SearchByVIN ) == 1 )
	{
		
		AfxMessageBox ( "Vehicle Found !!!", MB_ICONINFORMATION );
		
		UpdateData ( true );

		// Copy vehicle attributes into the realtime edit boxes for easy view.

		m_VehicleMake = (*VehicleOwnersListPTR).GetVehicleMake ( );
		m_EngineSize = (*VehicleOwnersListPTR).GetEngineSize ( );
		m_RegistrationNo = (*VehicleOwnersListPTR).GetVehicleRegistrationNumber ( );
		m_VIN = (*VehicleOwnersListPTR).GetVIN ( );

		UpdateData ( false );
		
		return;
	
	}

	// If vehicle is not found.

	else
	{

		AfxMessageBox ( "Vehicle was not found.", MB_ICONSTOP );
		return;

	}

	UpdateData ( false );

	return;

}

void CSearchRemoveVehicleDlg::OnButtonDeletevehicle() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData ( true );
	int ReturnValue;
	
	ReturnValue = ((*VehicleOwnersListPTR).DeleteVehicle ( m_RemoveByVIN ));

	if ( ReturnValue == 1 )
	{

		// Reinitializing the variables.
		
		UpdateData ( true );

		m_EngineSize = _T("");
		m_RegistrationNo = _T("");
		m_VehicleMake = _T("");
		m_VIN = 0;
		m_SearchByVIN = 0;
		m_RemoveByVIN = 0;
		
		UpdateData ( false );

		AfxMessageBox ( "The vehicle was successfully deleted.", MB_ICONINFORMATION );

		return;

	}

	if ( ReturnValue == 3 )
	{

		// Reinitializing the variables.
		
		UpdateData ( true );

		m_EngineSize = _T("");
		m_RegistrationNo = _T("");
		m_VehicleMake = _T("");
		m_VIN = 0;
		m_SearchByVIN = 0;
		m_RemoveByVIN = 0;
		
		UpdateData ( false );

		AfxMessageBox ( "The vehicle was deleted succcessfully. Owner's vehicle list empty. Owner deleted.", MB_ICONINFORMATION );

		return;

	}

	else// ( (*VehicleOwnersListPTR).DeleteVehicle ( m_RemoveByVIN ) != 1 && (*VehicleOwnersListPTR).DeleteVehicle ( m_RemoveByVIN ) != 3)
	{

		AfxMessageBox ( "Vehicle was not found.", MB_ICONSTOP );
		m_RemoveByVIN = 0;
		return;

	}

	UpdateData ( false );

}

void CSearchRemoveVehicleDlg::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CViewRemoveVehicleHelpDlg ViewRemoveVehicleHelpDlgObject;
	ViewRemoveVehicleHelpDlgObject.DoModal ( );
}
