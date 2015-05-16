// AddNewVehicleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vehicle Owners Database.h"
#include "AddNewVehicleDlg.h"
#include "OwnersList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern COwnersList *VehicleOwnersListPTR;

/////////////////////////////////////////////////////////////////////////////
// CAddNewVehicleDlg dialog


CAddNewVehicleDlg::CAddNewVehicleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddNewVehicleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddNewVehicleDlg)
	m_FirstName = _T("");
	m_LastName = _T("");
	m_PermanentAddress = _T("");
	m_SIN = 0;
	m_TelephoneNo = _T("");
	m_EngineSize = _T("");
	m_RegistrationNo = _T("");
	m_VehicleMake = _T("");
	m_VIN = 0;
	//}}AFX_DATA_INIT
}


void CAddNewVehicleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddNewVehicleDlg)
	DDX_Text(pDX, IDC_EDIT_OI_FIRSTNAME, m_FirstName);
	DDX_Text(pDX, IDC_EDIT_OI_LASTNAME, m_LastName);
	DDX_Text(pDX, IDC_EDIT_OI_PERMANENTADDRESS, m_PermanentAddress);
	DDX_Text(pDX, IDC_EDIT_OI_SIN, m_SIN);
	DDX_Text(pDX, IDC_EDIT_OI_TELEPHONENO, m_TelephoneNo);
	DDX_Text(pDX, IDC_EDIT_VI_ENGINESIZE, m_EngineSize);
	DDX_Text(pDX, IDC_EDIT_VI_REGISTRATIONNO, m_RegistrationNo);
	DDX_Text(pDX, IDC_EDIT_VI_VEHICLEMAKE, m_VehicleMake);
	DDX_Text(pDX, IDC_EDIT_VI_VIN, m_VIN);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddNewVehicleDlg, CDialog)
	//{{AFX_MSG_MAP(CAddNewVehicleDlg)
	ON_BN_CLICKED(IDC_BUTTON_MAINMENU, OnButtonMainmenu)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddNewVehicleDlg message handlers

void CAddNewVehicleDlg::OnButtonMainmenu() 
{
	// TODO: Add your control notification handler code here
	(*this).EndDialog ( 0 );
}

void CAddNewVehicleDlg::OnButtonAdd() 
{
	
	// TODO: Add your control notification handler code here
	UpdateData ( true );

	////////////////////////////////////////////////////////////////////////////////////////////
	// ***************************** If Owner already exists *********************************//
	////////////////////////////////////////////////////////////////////////////////////////////

	if ( (*VehicleOwnersListPTR).SearchOwner ( m_SIN ) == 1 )
	{
		
		// ********************* A. If Owner owns vehicle ******************************
		
		if ( (*VehicleOwnersListPTR).SearchVehicle ( m_VIN ) == 1 )
		{

			AfxMessageBox ( "The owner already owns this vehicle.", MB_ICONINFORMATION );

			// Refreshing the variables.
			
			UpdateData ( true );

			m_FirstName = _T("");
			m_LastName = _T("");
			m_PermanentAddress = _T("");
			m_SIN = 0;
			m_TelephoneNo = _T("");
			m_EngineSize = _T("");
			m_RegistrationNo = _T("");
			m_VehicleMake = _T("");
			m_VIN = 0;

			UpdateData ( false );

			////////////////////////////

			return;

		}

		// *****************************************************************************

		// ********************* B. If Owner does not own vehicle **********************

		if ( (*VehicleOwnersListPTR).SearchVehicle ( m_VIN ) == 0 )
		{

			// Search all vehicles and delete the vehicle if found.
			if ( (*VehicleOwnersListPTR).SearchAllVehicles ( m_VIN ) == 1 )
			{

				(*VehicleOwnersListPTR).DeleteVehicle ( m_VIN );

			}

			// Add the vehicle to the owner's account.

			(*VehicleOwnersListPTR).AddVehicle ( m_EngineSize, m_RegistrationNo, m_VehicleMake, m_VIN );
			AfxMessageBox ( "Vehicle was successfully added to the owner's vehicle list.", MB_ICONINFORMATION );
			
			// Refreshing the variables.
			
			UpdateData ( true );

			m_FirstName = _T("");
			m_LastName = _T("");
			m_PermanentAddress = _T("");
			m_SIN = 0;
			m_TelephoneNo = _T("");
			m_EngineSize = _T("");
			m_RegistrationNo = _T("");
			m_VehicleMake = _T("");
			m_VIN = 0;

			UpdateData ( false );

			////////////////////////////
			return;

		}

		// ******************************************************************************
	
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////
	// ****************************** If Owner does not Exist ********************************//
	////////////////////////////////////////////////////////////////////////////////////////////

	if ( (*VehicleOwnersListPTR).SearchOwner ( m_SIN ) == 0 )
	{
		
		// Search all vehicles and delete the vehicle if found.
		if ( (*VehicleOwnersListPTR).SearchAllVehicles ( m_VIN ) == 1 )
		{

			(*VehicleOwnersListPTR).DeleteVehicle ( m_VIN );

		}
		
		// Create the owner.

		(*VehicleOwnersListPTR).AddOwner ( m_FirstName, m_LastName, m_SIN, m_PermanentAddress, m_TelephoneNo );

		// Add the vehicle to the owner's account.

		(*VehicleOwnersListPTR).AddVehicle ( m_EngineSize, m_RegistrationNo, m_VehicleMake, m_VIN );
		AfxMessageBox ( "Vehicle was successfully added to the owner's vehicle list.", MB_ICONINFORMATION );
		
		// Refreshing the variables.
			
		UpdateData ( true );

		m_FirstName = _T("");
		m_LastName = _T("");
		m_PermanentAddress = _T("");
		m_SIN = 0;
		m_TelephoneNo = _T("");
		m_EngineSize = _T("");
		m_RegistrationNo = _T("");
		m_VehicleMake = _T("");
		m_VIN = 0;

		UpdateData ( false );

		////////////////////////////
		return;
		
	}

	UpdateData ( false );

}
