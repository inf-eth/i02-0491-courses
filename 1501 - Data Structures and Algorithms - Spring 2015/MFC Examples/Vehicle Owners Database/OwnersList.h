// OwnersList.h: interface for the COwnersList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OWNERSLIST_H__B74B1D2D_CBA2_497F_93F2_30A23EF7826C__INCLUDED_)
#define AFX_OWNERSLIST_H__B74B1D2D_CBA2_497F_93F2_30A23EF7826C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VehiclesList.h"

// This is the single node in the Owner list.
struct SingleOwner
{
	
	// *** The Data of the the Owner ***

	CString FirstName;
	CString LastName;
	int		SIN;
	CString PermanentAddress;
	CString	TelephoneNo;


	// *** The Vehicles Owned by the Owner ***

	CVehiclesList OwnedVehicles;
	
	// *** Pointers of this node ***

	SingleOwner *PreviousOwner;
	SingleOwner *NextOwner;

};


// *** Class declaration of the Owners' list ***

class COwnersList  
{

private:

	// The 'Global' variables used in the class.
		
	SingleOwner *FirstOwner;
	SingleOwner *LastOwner;
	SingleOwner *Index;
	int NoOfOwners;
	
public:

	// *** The Constructor ***
	COwnersList();

	// *** The Destructor ***
	~COwnersList();

	// *** Index Functions ***
	void ResetIndex ( ) { Index = FirstOwner; }
	void IndexForward ( );
	void IndexReverse ( );

	void ResetVehiclesIndex ( );
	void VehiclesIndexForward ( );
	void VehiclesIndexReverse ( );

	// *** Functions For the manipulation of the linklist ***
	
	// Owner related functions.
	void AddOwner ( CString&, CString&, int, CString&, CString& );
	int SearchOwner ( int );
	int DeleteOwner ( int );
	
	// Vehicle related functions.
	void AddVehicle ( CString&, CString&, CString&, int );
	
	int SearchVehicle ( int );
	int BookmarkAVehicle ( int );
	int SearchAllVehicles ( int );
	
	int DeleteVehicle ( int );
	int DeleteAllVehicles ( );

	// *** Get Functions ***
	CString GetFirstName ( );
	CString GetLastName ( );
	int		GetSIN ( );
	CString GetPermanentAddress ( );
	CString	GetTelephoneNo ( );

	int		GetNoOfVehicles ( );
	CString GetVehicleMake ( );
	CString GetEngineSize ( );
	CString GetVehicleRegistrationNumber ( );
	int		GetVIN ( );
	
};

#endif // !defined(AFX_OWNERSLIST_H__B74B1D2D_CBA2_497F_93F2_30A23EF7826C__INCLUDED_)
