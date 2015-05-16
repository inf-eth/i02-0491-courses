// OwnersList.cpp: implementation of the COwnersList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Vehicle Owners Database.h"
#include "OwnersList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COwnersList::COwnersList()
{
	
	// Initialization at the time of creation of the object.
	FirstOwner = NULL;
	LastOwner = NULL;
	Index = NULL;
	NoOfOwners = 0;

}

COwnersList::~COwnersList()
{
	
}

//////////////////////////////////////////////////////
// ********** Defintion of class functions ***********
//////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
// ********************************* Index Functions *************************************

void COwnersList::IndexForward ( )
{

	if ( Index != NULL )
	{
		
		Index = (*Index).NextOwner;

	}

}

void COwnersList::IndexReverse ( )
{

	if ( Index != NULL )
	{
		
		Index = (*Index).PreviousOwner;

	}

}

void COwnersList::ResetVehiclesIndex ( )
{
	
	if ( Index != NULL )
	{
		((*Index).OwnedVehicles).ResetIndex ( );
	}

}

void COwnersList::VehiclesIndexForward ( )
{

	if ( Index != NULL )
	{
		((*Index).OwnedVehicles).IndexForward ( );
	}

}

void COwnersList::VehiclesIndexReverse ( )
{

	if ( Index != NULL )
	{
		((*Index).OwnedVehicles).IndexReverse ( );
	}

}

// ***************************************************************************************
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
// ********************************** Get Functions **************************************

CString COwnersList::GetFirstName ( ) 
{ 
	
	CString Temp = "No First Name";

	if ( Index != NULL )
	{
		
		return (*Index).FirstName;

	}

	return Temp;
}
	
CString COwnersList::GetLastName ( ) 
{
	
	CString Temp = "No Last Name";

	if ( Index != NULL )
	{
		
		return (*Index).LastName;

	}

	return Temp;
	
}

int	COwnersList::GetSIN ( ) 
{ 

	if ( Index != NULL )
	{
		
		return (*Index).SIN; 

	}

	return 0;

}

CString COwnersList::GetPermanentAddress ( ) 
{ 
	
	CString Temp = "No Address.";

	if ( Index != NULL )
	{

		return (*Index).PermanentAddress; 

	}

	return Temp;

}

CString COwnersList::GetTelephoneNo ( ) 
{ 
	
	CString Temp = "No Telephone";

	if ( Index != NULL )
	{

		return (*Index).TelephoneNo; 
	
	}

	return Temp;

}

// *** Get vehicle attributes ***

int COwnersList::GetNoOfVehicles ( )
{
	
	if ( Index != NULL )
	{

		return  ((*Index).OwnedVehicles).GetNoOfVehicles ( ) ;

	}
	return 0;

}

CString COwnersList::GetVehicleMake ( )
{

	CString Temp = "No Vehicle Make.";

	if ( Index != NULL )
	{

		return  ((*Index).OwnedVehicles).GetVehicleMake ( ) ;

	}

	return Temp;

}

CString COwnersList::GetEngineSize ( )
{

	CString Temp = "No Engine Size.";

	if ( Index != NULL )
	{

		return ((*Index).OwnedVehicles).GetEngineSize ( );

	}

	return Temp;

}

CString COwnersList::GetVehicleRegistrationNumber ( )
{

	CString Temp = "No Vehicle Registration Number.";

	if ( Index != NULL )
	{

		return  ((*Index).OwnedVehicles).GetVehicleRegistrationNumber ( );

	}

	return Temp;

}

int COwnersList::GetVIN ( )
{

	if ( Index != NULL )
	{
		return ((*Index).OwnedVehicles).GetVIN ( );
	}

	return 0;

}

// ***************************************************************************************
//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
// ********************************** Add New Owner **************************************

void COwnersList::AddOwner ( CString& FirstName, CString& LastName, int SIN, CString& PermanentAddress, CString& TelephoneNo )
{

	// If the linklist contains one or more that one entries.
	if ( NoOfOwners != 0 )
	{

		// Allocation memory using new.
		
		SingleOwner *NewOwner = new SingleOwner;
		

		// Adjusting the pointer addresses for creation of a circular linklist.
		
		(*FirstOwner).PreviousOwner = NewOwner;

		(*LastOwner).NextOwner = NewOwner;
		(*NewOwner).PreviousOwner = LastOwner;
		(*NewOwner).NextOwner = FirstOwner;

		Index = NewOwner;

		LastOwner = NewOwner;

		
		// Copying the data into the newly created node.

		(*NewOwner).FirstName = FirstName;
		(*NewOwner).LastName = LastName;
		(*NewOwner).SIN = SIN;
		(*NewOwner).PermanentAddress = PermanentAddress;
		(*NewOwner).TelephoneNo = TelephoneNo;

		NoOfOwners++;
		return;

	}

	// If the linklist is empty.
	else if ( NoOfOwners == 0 )
	{

		// Allocation memory using new.
		
		SingleOwner *NewOwner = new SingleOwner;
		

		// Adjusting the pointer addresses for creation of a circular linklist.
		
		FirstOwner = NewOwner;
		LastOwner = NewOwner;

		(*NewOwner).PreviousOwner = LastOwner;
		(*NewOwner).NextOwner = FirstOwner;

		Index = NewOwner;
		
		// Copying the data into the newly created node.

		(*NewOwner).FirstName = FirstName;
		(*NewOwner).LastName = LastName;
		(*NewOwner).SIN = SIN;
		(*NewOwner).PermanentAddress = PermanentAddress;
		(*NewOwner).TelephoneNo = TelephoneNo;

		NoOfOwners++;

		return;

	}

}

// *********************************************************************************
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// ********************************* Search Owner **********************************

int COwnersList::SearchOwner ( int SIN )
{

	SingleOwner *TempPTR;
	
	TempPTR = FirstOwner;

	for ( int i=0; i<NoOfOwners; i++ )
	{

		if ( (*TempPTR).SIN == SIN )
		{

			Index = TempPTR;
			return 1;

		}
		
		TempPTR = (*TempPTR).NextOwner;

	}

	return 0;


}

// *********************************************************************************
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// ********************************* Delete Owner **********************************

int COwnersList::DeleteOwner ( int SIN )
{

	SingleOwner* TempPTR;
	TempPTR = FirstOwner;

	// If no Owner exists.
	if ( NoOfOwners == 0 )
	{

		return 2;	// No entries exist.

	}

	// If there is only one Owner.
	if ( NoOfOwners == 1 )
	{

		// If match is true.
		if ( (*TempPTR).SIN == SIN )
		{
			
			// Deleting all vehicles for this Owner.
			( (*TempPTR).OwnedVehicles ).DeleteAllVehicles ( );

			FirstOwner = NULL;	// Initializing first and last pointers.
			LastOwner = NULL;	//
			Index = NULL;		//
			NoOfOwners = 0;

			delete TempPTR;		// Deallocate memory.
			
			return 1;			// Owner found.

		}
		
		return 0;
		
	}


	// If there are more than one Owners.
	for ( int i=0; i<NoOfOwners; i++ )
	{
		
		// If Owner found.
		if ( (*TempPTR).SIN == SIN )
		{
				
			// Checking if the Owner is the First Owner.
			if ( TempPTR == FirstOwner )
			{

				// Deleting all vehicles for this Owner.
				( (*TempPTR).OwnedVehicles ).DeleteAllVehicles ( );

				FirstOwner = (*TempPTR).NextOwner;

				( *(*TempPTR).PreviousOwner ).NextOwner = (*TempPTR).NextOwner;
				( *(*TempPTR).NextOwner ).PreviousOwner = (*TempPTR).PreviousOwner;
				
				delete TempPTR;

				--NoOfOwners;

				return 1;		// Owner found.

			}

			// Checking if the Owner is the Last Owner.
			if ( TempPTR == LastOwner )
			{

				// Deleting all vehicles for this Owner.
				( (*TempPTR).OwnedVehicles ).DeleteAllVehicles ( );

				LastOwner = (*TempPTR).PreviousOwner;

				( *(*TempPTR).PreviousOwner ).NextOwner = (*TempPTR).NextOwner;
				( *(*TempPTR).NextOwner ).PreviousOwner = (*TempPTR).PreviousOwner;
				
				delete TempPTR;

				--NoOfOwners;

				return 1;		// Owner found.

			}

			// Else if the owner is a middle node.
			{

				// Deleting all vehicles for this Owner
				( (*TempPTR).OwnedVehicles ).DeleteAllVehicles ( );

				( *(*TempPTR).PreviousOwner ).NextOwner = (*TempPTR).NextOwner;
				( *(*TempPTR).NextOwner ).PreviousOwner = (*TempPTR).PreviousOwner;
				
				delete TempPTR;

				--NoOfOwners;

				return 1;		// Owner found.

			}

		}

		TempPTR = (*TempPTR).NextOwner;

	}

	return 0;		// Owner not found.

}

// *********************************************************************************
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// ********************************* Add Vehicle ***********************************

void COwnersList::AddVehicle ( CString& VehicleMake, CString& EngineSize, CString& VehicleRegistrationNumber, int VIN )
{

	(*Index).OwnedVehicles.AddVehicle ( VehicleMake, EngineSize, VehicleRegistrationNumber, VIN );
	

}

// *********************************************************************************
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// ****************************** Search Vehicle ***********************************

int COwnersList::SearchVehicle ( int VIN )
{

	if ( (*Index).OwnedVehicles.SearchVehicle ( VIN ) == 0 )
	{
	
		return 0;

	}

	if ( (*Index).OwnedVehicles.SearchVehicle ( VIN ) == 1 )
	{
	
		return 1;

	}

	else if ( (*Index).OwnedVehicles.SearchVehicle ( VIN ) == 2 )
	{
		return 2;
	}

	return 0;

}

// *********************************************************************************
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
// ***************************** Bookmark a Vehicle ********************************

// This functions basically sets the index to that owner who owns a particular vehicle.

int COwnersList::BookmarkAVehicle ( int VIN )
{

	SingleOwner *TempPTR = FirstOwner;

	for ( int i=0; i<NoOfOwners; i++ )
	{
		
		if ( (*TempPTR).OwnedVehicles.SearchVehicle ( VIN ) == 1 )
		{

			// Setting Index.
			Index = TempPTR;

			// Returning true.
			return 1;

		}
		
		TempPTR = (*TempPTR).NextOwner;

	}

	return 0;

}

// *********************************************************************************
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
// **************************** Search All Vehicles ********************************

int COwnersList::SearchAllVehicles ( int VIN )
{

	SingleOwner *TempPTR = FirstOwner;

	for ( int i=0; i<NoOfOwners; i++ )
	{
		
		if ( (*TempPTR).OwnedVehicles.SearchVehicle ( VIN ) == 1 )
		{
			return 1;
		}
		
		TempPTR = (*TempPTR).NextOwner;

	}

	return 0;

}


////////////////////////////////////////////////////////////////////////////////////
// ******************************** Delete Vehicle *********************************

int COwnersList::DeleteVehicle ( int VIN )
{
	

	SingleOwner *TempPTR = FirstOwner;
     

	for ( int i=0; i<NoOfOwners; i++ )
	{
		
		if ( (*TempPTR).OwnedVehicles.DeleteVehicle ( VIN ) == 1 )
		{
			
			// If the owner has no vehicle he needs to be deleted.
			if ( ((*TempPTR).OwnedVehicles).GetNoOfVehicles ( ) == 0 )
			{
			
				// If there is only one Owner.
				if ( NoOfOwners == 1 )
				{

					FirstOwner = NULL;	// Initializing first and last pointers.
					LastOwner = NULL;	//
					Index = NULL;		//
					NoOfOwners = 0;

					delete TempPTR;		// Deallocate memory.
					
					return 3;			// Owner deleted.
			
				}
				
								// Checking if the Owner is the First Owner.
				if ( TempPTR == FirstOwner )
				{

					FirstOwner = (*TempPTR).NextOwner;

					( *(*TempPTR).PreviousOwner ).NextOwner = (*TempPTR).NextOwner;
					( *(*TempPTR).NextOwner ).PreviousOwner = (*TempPTR).PreviousOwner;
					
					delete TempPTR;

					--NoOfOwners;

					return 3;		// Owner deleted.

				}

				// Checking if the Owner is the Last Owner.
				if ( TempPTR == LastOwner )
				{

					LastOwner = (*TempPTR).PreviousOwner;

					( *(*TempPTR).PreviousOwner ).NextOwner = (*TempPTR).NextOwner;
					( *(*TempPTR).NextOwner ).PreviousOwner = (*TempPTR).PreviousOwner;
					
					delete TempPTR;

					--NoOfOwners;

					return 3;		// Owner deleted.

				}

				// Else if the owner is a middle node.
				{

					( *(*TempPTR).PreviousOwner ).NextOwner = (*TempPTR).NextOwner;
					( *(*TempPTR).NextOwner ).PreviousOwner = (*TempPTR).PreviousOwner;
					
					delete TempPTR;

					--NoOfOwners;

					return 3;		// Owner deleted.

				}


			}

			return 1;
			
		}
		
		TempPTR = (*TempPTR).NextOwner;	
		
	}
	return 2;
	
}

// *********************************************************************************
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
// **************************** Delete All Vehicles ********************************

int COwnersList::DeleteAllVehicles ( )
{

	SingleOwner *TempPTR = FirstOwner;

	for ( int i=0; i<NoOfOwners; i++ )
	{
		
		(*TempPTR).OwnedVehicles.DeleteAllVehicles ( );

		TempPTR = (*TempPTR).NextOwner;

	}

	return 1;

}

// *********************************************************************************
////////////////////////////////////////////////////////////////////////////////////