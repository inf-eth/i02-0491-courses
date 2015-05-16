// VehiclesList.h: interface for the CVehiclesList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VEHICLESLIST_H__49953335_E69C_4A51_BDA3_3689E9398851__INCLUDED_)
#define AFX_VEHICLESLIST_H__49953335_E69C_4A51_BDA3_3689E9398851__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// This structure is one node of the the vehicles list.
struct SingleVehicle
{

	// *** The Data of the Vehicle ***

	CString VehicleMake;
	CString EngineSize;
	CString VehicleRegistrationNumber;
	int		VIN;

	// *** Pointers of this node ***

	SingleVehicle *PreviousVehicle;
	SingleVehicle *NextVehicle;

};


//  *** Class declaration of the vehicles list ***

class CVehiclesList  
{

private:

	// The 'Global' variables used in the class.
	
	SingleVehicle *FirstVehicle;
	SingleVehicle *LastVehicle;
	SingleVehicle *Index;
	int NoOfVehicles;

public:

	// *** Constructor ***
	CVehiclesList();

	// *** Destructor ***
	virtual ~CVehiclesList();

	// *** Index Functions ***
	void ResetIndex ( ) { Index = FirstVehicle; }
	void IndexForward ( );
	void IndexReverse ( );

	// *** Functions For the manipulation of the linklist ***
	void AddVehicle ( CString&, CString&, CString&, int );
	
	int SearchVehicle ( int );
	int DeleteVehicle ( int );
	int DeleteAllVehicles ( );
	
	// *** Get Functions ***
	int GetNoOfVehicles ( ) { return NoOfVehicles; }
	
	CString GetVehicleMake ( );
	CString GetEngineSize ( );
	CString GetVehicleRegistrationNumber ( );
	int		GetVIN ( );



};

#endif // !defined(AFX_VEHICLESLIST_H__49953335_E69C_4A51_BDA3_3689E9398851__INCLUDED_)
