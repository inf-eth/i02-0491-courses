// OwnedVehiclesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vehicle Owners Database.h"
#include "OwnedVehiclesDlg.h"
#include "OwnersList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern COwnersList *VehicleOwnersListPTR;

/////////////////////////////////////////////////////////////////////////////
// COwnedVehiclesDlg dialog


COwnedVehiclesDlg::COwnedVehiclesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COwnedVehiclesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COwnedVehiclesDlg)
	m_EngineSize = _T("");
	m_RegistrationNo = _T("");
	m_VehicleMake = _T("");
	m_VIN = 0;
	m_TotalVehiclesOwned = 0;
	//}}AFX_DATA_INIT
}


void COwnedVehiclesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COwnedVehiclesDlg)
	DDX_Text(pDX, IDC_EDIT_OV_ENGINESIZE, m_EngineSize);
	DDX_Text(pDX, IDC_EDIT_OV_REGISTRATIONNO, m_RegistrationNo);
	DDX_Text(pDX, IDC_EDIT_OV_VEHICLEMAKE, m_VehicleMake);
	DDX_Text(pDX, IDC_EDIT_OV_VIN, m_VIN);
	DDX_Text(pDX, IDC_EDIT_OV_TOTALVEHOCLESOWNED, m_TotalVehiclesOwned);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COwnedVehiclesDlg, CDialog)
	//{{AFX_MSG_MAP(COwnedVehiclesDlg)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnButtonPrevious)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COwnedVehiclesDlg message handlers

void COwnedVehiclesDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL COwnedVehiclesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	(*VehicleOwnersListPTR).ResetVehiclesIndex ( );

	UpdateData ( true );

	m_EngineSize = (*VehicleOwnersListPTR).GetEngineSize ( );
	m_RegistrationNo = (*VehicleOwnersListPTR).GetVehicleRegistrationNumber ( );
	m_VehicleMake = (*VehicleOwnersListPTR).GetVehicleMake ( );
	m_VIN = (*VehicleOwnersListPTR).GetVIN ( );
	m_TotalVehiclesOwned = (*VehicleOwnersListPTR).GetNoOfVehicles ( );

	UpdateData ( false );

		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COwnedVehiclesDlg::OnButtonNext() 
{
	// TODO: Add your control notification handler code here
	(*VehicleOwnersListPTR).VehiclesIndexForward ( );

	UpdateData ( true );

	m_EngineSize = (*VehicleOwnersListPTR).GetEngineSize ( );
	m_RegistrationNo = (*VehicleOwnersListPTR).GetVehicleRegistrationNumber ( );
	m_VehicleMake = (*VehicleOwnersListPTR).GetVehicleMake ( );
	m_VIN = (*VehicleOwnersListPTR).GetVIN ( );
	
	UpdateData ( false );

	return;

}

void COwnedVehiclesDlg::OnButtonPrevious() 
{
	// TODO: Add your control notification handler code here
	(*VehicleOwnersListPTR).VehiclesIndexReverse ( );

	UpdateData ( true );

	m_EngineSize = (*VehicleOwnersListPTR).GetEngineSize ( );
	m_RegistrationNo = (*VehicleOwnersListPTR).GetVehicleRegistrationNumber ( );
	m_VehicleMake = (*VehicleOwnersListPTR).GetVehicleMake ( );
	m_VIN = (*VehicleOwnersListPTR).GetVIN ( );
	
	UpdateData ( false );

	return;
}
