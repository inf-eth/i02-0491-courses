// VehiclesList.cpp: implementation of the CVehiclesList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Vehicle Owners Database.h"
#include "VehiclesList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CVehiclesList::CVehiclesList()
{
	
	FirstVehicle = NULL;
	LastVehicle = NULL;
	Index = NULL;
	NoOfVehicles = 0;

}

CVehiclesList::~CVehiclesList()
{

}

//////////////////////////////////////////////////////
// ********** Defintion of class functions ***********
//////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
// ****************************** Index Functions **********************************

void CVehiclesList::IndexForward ( )
{

	if ( Index != NULL )
	{

		Index = (*Index).NextVehicle;
	}

}

void CVehiclesList::IndexReverse ( )
{

	if ( Index != NULL )
	{

		Index = (*Index).PreviousVehicle;
	}

}

// *********************************************************************************
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
// ***************************** Add a New Vehicle *********************************

void CVehiclesList::AddVehicle ( CString& VehicleMake, CString& EngineSize, CString& VehicleRegistrationNumber, int VIN )
{

	// If the linklist contains one or more that one entries.
	if ( NoOfVehicles != 0 )
	{

		// Allocation memory using new.
		
		SingleVehicle *NewVehicle = new SingleVehicle;
		

		// Adjusting the pointer addresses for creation of a circular linklist.
		
		(*FirstVehicle).PreviousVehicle = NewVehicle;

		(*LastVehicle).NextVehicle = NewVehicle;
		(*NewVehicle).PreviousVehicle = LastVehicle;
		(*NewVehicle).NextVehicle = FirstVehicle;

		Index = NewVehicle;

		LastVehicle = NewVehicle;

		
		// Copying the data into the newly created node.

		(*NewVehicle).VehicleMake = VehicleMake;
		(*NewVehicle).EngineSize = EngineSize;
		(*NewVehicle).VehicleRegistrationNumber = VehicleRegistrationNumber;
		(*NewVehicle).VIN = VIN;
		
		++NoOfVehicles;
		
		return;

	}

	// If the linklist is empty.
	else if ( NoOfVehicles == 0 )
	{

		// Allocation memory using new.
		
		SingleVehicle *NewVehicle = new SingleVehicle;
		

		// Adjusting the pointer addresses for creation of a circular linklist.
		
		FirstVehicle = NewVehicle;
		LastVehicle = NewVehicle;

		(*NewVehicle).PreviousVehicle = LastVehicle;
		(*NewVehicle).NextVehicle = FirstVehicle;

		Index = NewVehicle;

		
		// Copying the data into the newly created node.

		(*NewVehicle).VehicleMake = VehicleMake;
		(*NewVehicle).EngineSize = EngineSize;
		(*NewVehicle).VehicleRegistrationNumber = VehicleRegistrationNumber;
		(*NewVehicle).VIN = VIN;

		++NoOfVehicles;

		return;

	}

}

// *********************************************************************************
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// ******************************** Search Vehicle *********************************

int CVehiclesList::SearchVehicle ( int VIN )
{

	/*
	// If there are no vehicles in the list.
	if ( NoOfVehicles == 0 )
	{
	
		return 2;		// Cant search. No entries in the list.

	}

	else
		*/
	{

		SingleVehicle *TempPTR;
		
		TempPTR = FirstVehicle;

		for ( int i=0; i<NoOfVehicles; i++ )
		{
			
			// Vehicle found.
			if ( (*TempPTR).VIN == VIN )
			{

				Index = TempPTR;
				return 1;	// Vehicle found.

			}
			
			TempPTR = (*TempPTR).NextVehicle;

		}

		return 0;		// Vehicle not found

	}

}

// *********************************************************************************
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// ******************************** Delete Vehicle *********************************

int CVehiclesList::DeleteVehicle ( int VIN )
{

	SingleVehicle* TempPTR;
	TempPTR = FirstVehicle;

	// If no Vehicle exists.
	if ( NoOfVehicles == 0 )
	{

		return -1;	// No entries exist.

	}

	// If there is only one Vehicle.
	if ( NoOfVehicles == 1 )
	{

		// If match is true.
		if ( (*TempPTR).VIN == VIN )
		{
			
			
			FirstVehicle = NULL;	// Initializing first and last pointers.
			LastVehicle = NULL;	//
			Index = NULL;		//
			NoOfVehicles = 0;

			delete TempPTR;		// Deallocate memory.
			
			return 1;			// Vehicle found.

		}
		
		return 2;
		
	}


	// If there are more than one Vehicles.
	for ( int i=0; i<NoOfVehicles; i++ )
	{
		
		// If Vehicle found.
		if ( (*TempPTR).VIN == VIN )
		{
				
			// Checking if the Vehicle is the First Vehicle.
			if ( TempPTR == FirstVehicle )
			{

				
				FirstVehicle = (*TempPTR).NextVehicle;

				( *(*TempPTR).PreviousVehicle ).NextVehicle = (*TempPTR).NextVehicle;
				( *(*TempPTR).NextVehicle ).PreviousVehicle = (*TempPTR).PreviousVehicle;
				
				delete TempPTR;

				--NoOfVehicles;

				return 1;		// Vehicle found.

			}

			// Checking if the Vehicle is the Last Vehicle.
			if ( TempPTR == LastVehicle )
			{

				LastVehicle = (*TempPTR).PreviousVehicle;

				( *(*TempPTR).PreviousVehicle ).NextVehicle = (*TempPTR).NextVehicle;
				( *(*TempPTR).NextVehicle ).PreviousVehicle = (*TempPTR).PreviousVehicle;
				
				delete TempPTR;

				--NoOfVehicles;

				return 1;		// Vehicle found.

			}

			// Else if the Vehicle is a middle node.
			{

				( *(*TempPTR).PreviousVehicle ).NextVehicle = (*TempPTR).NextVehicle;
				( *(*TempPTR).NextVehicle ).PreviousVehicle = (*TempPTR).PreviousVehicle;

				delete TempPTR;

				--NoOfVehicles;

				return 1;		// Vehicle found.

			}

		}

		TempPTR = (*TempPTR).NextVehicle;

	}

	return -1;		// Vehicle not found.

}

// *********************************************************************************
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// ***************************** Delete All Vehicles *******************************

int CVehiclesList::DeleteAllVehicles ( )
{

	SingleVehicle *TempPTR1 = FirstVehicle;
	SingleVehicle *TempPTR2;

	for ( int i=0; i < NoOfVehicles; i++ )
	{
		
		TempPTR2 = TempPTR1;
		TempPTR1 = (*TempPTR2).NextVehicle;

		delete TempPTR2;

	}

	return 1;

}


////////////////////////////////////////////////////////////////////////////////////
// ******************************* Get Functions ***********************************

CString CVehiclesList::GetVehicleMake ( )
{

	CString Temp = "No Vehicle Make.";

	if ( Index != NULL )
	{

		return (*Index).VehicleMake;

	}

	return Temp;

}

CString CVehiclesList::GetEngineSize ( )
{

	CString Temp = "No Engine Size.";

	if ( Index != NULL )
	{

		return (*Index).EngineSize;

	}

	return Temp;

}

CString CVehiclesList::GetVehicleRegistrationNumber ( )
{

	CString Temp = "No Vehicle Registration Number.";

	if ( Index != NULL )
	{

		return (*Index).VehicleRegistrationNumber;

	}

	return Temp;

}

int CVehiclesList::GetVIN ( )
{

	if ( Index != NULL )
	{
		return (*Index).VIN;
	}

	return 0;

}









// *********************************************************************************
////////////////////////////////////////////////////////////////////////////////////