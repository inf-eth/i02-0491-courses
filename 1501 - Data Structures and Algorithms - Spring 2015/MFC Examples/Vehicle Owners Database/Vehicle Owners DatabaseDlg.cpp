// Vehicle Owners DatabaseDlg.cpp : implementation file
//

// Programming log started 2-09-2003 0832 hrs.

/*

  
*******						**************************									*******************
Version								Progression											   Time and Date
*******						**************************									*******************

0.001	Created the workspace. Now trying to make the interface and the linklists.		0833 hrs 02-09-2003

0.015	Defined the Owner class linklist and made the add new owner funciton.			0925 hrs 02-09-2003

0.020	Starting work on the main menu.													0940 hrs 02-09-2003

0.025	Resumed work after the BEE class. Working on the owner linklist.				1111 hrs 02-09-2003

0.031	Currently designing the Add New Vehicle Dialog.									1141 hrs 02-09-2003

0.035	Design of the Add New Vehicle Dialog complete.									1155 hrs 02-09-2003

0.040	Resumed work now working on the linklist.										1350 hrs 02-09-2003

0.043	As there was verilog lab in the Kohsar lab I have to come down to Rawal.		1435 hrs 02-09-2003

0.050	Still working on the linklists.													1440 hrs 02-09-2003	

0.060	Delete and get functions still remaining. Now going for the Islamiat class.		1449 hrs 02-09-2003		

0.061	Again starting work on the assignment.											0158 hrs 03-09-2003

0.065	Added the search method in the vehicle class.									0209 hrs 03-09-2003

0.066	Writing the delete functions now.												0217 hrs 03-09-2003

0.067	Just found out that I cannot implement the vehicle list without using struct.	0225 hrs 03-09-2003

0.070	Working on the delete functions.												0316 hrs 03-09-2003

0.099	A few functions still remain but now I am going to check the linklist first.	0408 hrs 03-09-2003

0.120	Implementing the linklist... Working on the add new vehicle/owner dialog.		0423 hrs 03-09-2003

0.122	I know... I now need to convert the owner linklist to structure format. Can't	0512 hrs 03-09-2003
		do much without it. And I don't know how to use this static/class linklist.				

0.130	Still working on converting the linklist...										0600 hrs 03-09-2003

0.150	All work from version 0.130 upto version 0.136 lost. Didn't properly copy in	1520 hrs 03-09-2003
		the memory.	Beginning today's work from scratch.

0.170	Started testing the linklists in the program. The variables are not properly	1620 hrs 03-09-2003
		refreshed. I have to look into this.										

0.200	The program is working fine but there is an issue of vehicle not being deleted	1645 hrs 03-09-2003
		on a certain condition.															

0.205	Fixed a bug about searching the vehicles. This has removed the issue of vehicle	1800 hrs 03-09-2003
		not being deleted.													
		
0.206	Now I need to put in the check to delete the owner if he has no vehicle(s)		1803 hrs 03-09-2003
		left. But first, I have to make a backup.

0.210	Debugging functions related to adding and deleting owners.						1827 hrs 03-09-2003

0.220	Now the owner is properly deleted if all his vehicles are deleted.				1835 hrs 03-09-2003

0.225	Put the tab stops in correct order.												1958 hrs 03-09-2003

0.230	Working on searching and displaying owners and vehicles.						2049 hrs 03-09-2003

0.250	Still working on it... made the dialog box and added buttons. Now trying to		2245 hrs 03-09-2003
		implement it.																	

0.260	It is raining outside and we had a power shutdown about 5 minutes ago. As a		2320 hrs 03-09-2003
		result the OwnerList.cpp file was corrupted and I had to restore a backup.
		
0.261	ANOTHER power shutdown. Lost the OwnerList.cpp again. Restored backup.			2328 hrs 03-09-2003
		Now making a backup.

0.265	Wrote the Index related functions. Making a backup.								2349 hrs 03-09-2003		

0.270	Still working on the Owner Search dialog.										2359 hrs 03-09-2003

0.275	Search by SIN completed. Now working on manual search.							0037 hrs 04-09-2003

0.279	Manual search completed.														0042 hrs 04-09-2003

0.292	Going to start work on the Search/Remove vehicle dialog. Making backup.			0057 hrs 04-09-2003

0.307	Dialog made, implementation remains.											0140 hrs 04-09-2003

0.322	Working on the index functions for the vehicles linked list.					0156 hrs 04-09-2003	

0.333	Wrote the get functions for the vehicle class. I write 1 key word and sleep		0230 hrs 04-09-2003
		for 30 seconds. Can't keep awake... eyes closing... ZZZzzzzzzzz			

0.334	Woke up, resumed work. Work on Search/Remove dialog in progress.				0531 hrs 04-09-2003	

0.341	The vehicle search is completed. Now need to work on removing vehicle.			0609 hrs 04-09-2003	

0.400	Vehicle can be deleted without any problems. Also if the owner does not own		0618 hrs 04-09-2003		
		any other vehicle he is also deleted. Now I need to go to school.
		
0.401	Now that I am here at the Kohsar lab I can do something about the remaining		1127 hrs 04-09-2003
		help dialogs. All the functionality of the program is now complete. Only need
		to find bugs... debug... find bugs... debug...

0.406	Just found a bug about deleting vehicle. Just an overcheck which says vehicle	1146 hrs 04-09-2003
		not found AFTER deleting the vehicle.	
		
0.415	Found and fixed the bug. Actually there was a "return 1" missing in the			1156 hrs 04-09-2003
		owners' list delete vehicle function. I just missed it because there were
		so many closing braces.	
		
0.433	Made the about dialog. Making backup.											1207 hrs 04-09-2003

0.502	Made the main help dialog. Need to refine a few things. Making backup and going	1246 hrs 04-09-2003
		to common room. I missed the demo and need to talk with Hammad Bhai.			

0.505	Wasted all this time. Must refine the program.									1435 hrs 04-09-2003

0.511	Working on displaying idividual vehicles owned by the owners.					1441 hrs 04-09-2003

0.570	Going for the Islmic Study class.												1457 hrs 04-09-2003

0.599	Resuming work now. Making the Owned Vehicles Dialog. May need to declare a few	0552 hrs 05-09-2003
		extra functions in the VehicleList class.											

0.607	I need to make those extra functions in the OwnersList class.					0603 hrs 05-09-2003

0.613	Now I need to attach variables in the edit boxes in the Owned Vehicles Dialog	0614 hrs 05-09-2003
		and make the next and previous buttons to work. Then I will be working on the
		remaining help dialogs. But first let's go to school.
		
0.614	Didn't do anything at school. Now doing something.								0227 hrs 06-09-2003

0.617	Going to test the vehicle information dialog.									0244 hrs 06-09-2003

0.633	All the functionality is complete now. Of course there may be a few bugs which	0258 hrs 06-09-2003
		can only be found by testing. However, two help dialogs remain. Will be working
		on them.	
		
0.637	I am here at school. Made minor adjustments.									0925 hrs 06-09-2003

0.638	Still making minor asjustments.													1419 hrs 06-09-2003		

0.643	Trying to make the vehicle owner message to appear after vehicle deletion.		1442 hrs 06-09-2003

0.647	At last I have found what was wrong with that return value. The if condition	1722 hrs 06-09-2003
		actually deleted the vehicle.			
		
0.677	This is going to be the last programming session. Let's do it.					1833 hrs 06-09-2003

0.701	Owner search help dialog completed. Let's work on the remove vehicle dialog		1845 hrs 06-09-2003
		help.		
		
1.000	Assignment completed. This is the submission version of this program.			1923 hrs 06-09-2003
*/

#include "stdafx.h"
#include "Vehicle Owners Database.h"
#include "Vehicle Owners DatabaseDlg.h"
#include "AddNewVehicleDlg.h"
#include "OwnersList.h"
#include "SearchOwnerDlg.h"
#include "SearchRemoveVehicleDlg.h"
#include "MainHelpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// ** The Vehicle Owners' linklist Object and Global Pointer **
COwnersList VehicleOwnersList;
COwnersList *VehicleOwnersListPTR = &VehicleOwnersList;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVehicleOwnersDatabaseDlg dialog

CVehicleOwnersDatabaseDlg::CVehicleOwnersDatabaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVehicleOwnersDatabaseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVehicleOwnersDatabaseDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVehicleOwnersDatabaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVehicleOwnersDatabaseDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVehicleOwnersDatabaseDlg, CDialog)
	//{{AFX_MSG_MAP(CVehicleOwnersDatabaseDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDEXIT, OnExit)
	ON_BN_CLICKED(IDC_BUTTON_ADDANEWVEHICLE, OnBUTTONAddaNewVehicle)
	ON_BN_CLICKED(IDC_BUTTON_SEARCHOWNERSLIST, OnButtonSearchownerslist)
	ON_BN_CLICKED(IDC_BUTTON_SEARCHREMOVEVEHICLE, OnButtonSearchremovevehicle)
	ON_BN_CLICKED(ID_ABOUT, OnAbout)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVehicleOwnersDatabaseDlg message handlers

BOOL CVehicleOwnersDatabaseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVehicleOwnersDatabaseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVehicleOwnersDatabaseDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVehicleOwnersDatabaseDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVehicleOwnersDatabaseDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	(*this).EndDialog ( 1 );
}

void CVehicleOwnersDatabaseDlg::OnBUTTONAddaNewVehicle() 
{
	// TODO: Add your control notification handler code here
	CAddNewVehicleDlg AddVehicleDialogObject;
	AddVehicleDialogObject.DoModal ( );
}

void CVehicleOwnersDatabaseDlg::OnButtonSearchownerslist() 
{
	// TODO: Add your control notification handler code here
	CSearchOwnerDlg SearchOwnerDlgObject;
	SearchOwnerDlgObject.DoModal ( );
	
}

void CVehicleOwnersDatabaseDlg::OnButtonSearchremovevehicle() 
{
	// TODO: Add your control notification handler code here
	CSearchRemoveVehicleDlg SearchRemoveDialogObject;
	SearchRemoveDialogObject.DoModal ( );

}

void CVehicleOwnersDatabaseDlg::OnAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg AboutDlgObject;
	AboutDlgObject.DoModal ( );

}

void CAboutDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CVehicleOwnersDatabaseDlg::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CMainHelpDlg MainHelpDlgObject;
	MainHelpDlgObject.DoModal ( );
}
