// Router.h. Contains generic function implementations for the Router.cpp

// ***************************************** Header Files ***********************************************

#include "../NetworkLayer/RoutingTable.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <netdb.h>

#include <pthread.h>

using namespace std;
// ******************************************************************************************************

void StringToPacketLinkedList ( CLinkedList *, CLinkedList * );
char *strrev ( const char * );

// ****************************************** #Defintions ***********************************************

#define  MAXBUFFERSIZE		512		// Maximum default buffersize.
#define  PAYLOADSIZE		496		// Payload size.
#define  ENDOFWORLD		  false		// Is it end of world?

// ******************************************************************************************************

// ************************************** Custom Datatypes **********************************************

struct LSPacketArgument
{

	CPacket LSPacket;
	int     Destination;
	
};

// ******************************************************************************************************

// ********************************** Itoa ( had to write it myself :( ) ********************************
char *itoa ( int Integer )
{

	int  Iterations = 1;
	int  Quotient = 0;
	int  Divisor = 1;
	char *LocalString;

	if ( Integer < 0 )
	{
		return 0;
	}

//	Iterations = (int)log ( Integer ) + 1;

	if ( Integer < 10  )
	{
		Iterations = 1;
	}
	if ( Integer < 100 && Integer >= 10 )
	{
		Iterations = 2;
	}
	if ( Integer < 1000 && Integer >= 100 )
	{
		Iterations = 3;
	}
	if ( Integer < 10000 && Integer >= 1000 )
	{
		Iterations = 4;
	}
	if ( Integer < 100000 && Integer >= 10000)
	{
		Iterations = 5;
	}
	if ( Integer < 1000000 && Integer >= 100000 )
	{
		Iterations = 6;
	}
	if ( Integer < 10000000 && Integer >= 1000000 )
	{
		Iterations = 7;
	}

	LocalString = new char[Iterations+1];
	for ( int i=1; i<Iterations; i++ )
	{
		Divisor = Divisor * 10;
	}

	for ( int i=0; i<Iterations; i++ )
	{

		Quotient = Integer / Divisor;
		LocalString[i] = (char)(Quotient+48);
		Integer = Integer - ( Quotient * Divisor );
		Divisor = Divisor / 10;

	}

	LocalString[Iterations] = '\0';

	return strdup ( LocalString );

}

char *GetTime ( int PassedSeconds )
{

	int Hours = 0;
	int Minutes = 0;
	int Seconds = 0;
	struct timezone Temp;
	struct timeval  Temp1;

	gettimeofday ( &Temp1, &Temp );

	int Temp2 = PassedSeconds;

	Hours = (int)( Temp2 / 3600 );
	Minutes = (int)( ( Temp2 -  ( 3600 * Hours ) ) / 60 );
	Seconds = (int)( Temp2 -  ( 3600 * Hours ) - ( 60 * Minutes ) );

	char *CHours = itoa ( Hours );
	char *CMinutes = itoa ( Minutes );
	char *CSeconds = itoa ( Seconds );

	char Time[MAXBUFFERSIZE];
	Time[0] = '\0';

	strcat ( Time, CHours );
	strcat ( Time, ":" );
	strcat ( Time, CMinutes );
	strcat ( Time, ":" );
	strcat ( Time, CSeconds );
	strcat ( Time, "\n" );

	return strdup ( Time );

}

// Converts a Linked List of strings to a Linked List of Packets.
void StringToPacketLinkedList ( CLinkedList *StringLinkedList, CLinkedList *PacketLinkedList, int ProcessID, int Destination )
{

	// Packet.
	CPacket *Packet;
	
	// Flags.
	bool EndOfEntryFlag = false;
	bool PacketFullFlag = false;
	bool LastPacketFlag = false;
	bool BreakoutFlag   = false;
	
	// Misc. variables.
	int  i, j, k;
	int  StringLinkedListLength = (*StringLinkedList).GetNoOfEntries ( );
	int  PacketNo = 0;
	char FML = 'F';
	char PayLoad[489];
	char *CurrentString;
	
	// Resetting the Packet Linked List.
	(*PacketLinkedList).Empty ( );
	
	// * End-of-World while.
	while ( !ENDOFWORLD )
	{
	
		if ( PacketNo == 0 )
		{
			
			i = j = k = 0;
			PacketNo = 1;
			CurrentString = (char *)(*StringLinkedList)[i];
			FML = 'F';
			
		}
		
		if ( EndOfEntryFlag )
		{
		
			EndOfEntryFlag = false;
			i++;
			
			if ( i != StringLinkedListLength )
			{
			
				CurrentString = (char *)(*StringLinkedList)[i];
				j = 0;
				
			}
			else
			{
				LastPacketFlag = true;
			}
			
		}
			
		if ( PacketFullFlag )
		{
		
			PacketFullFlag = false;
			
			if ( PacketNo != 1 )
			{
				FML = 'M';
			}
			if ( LastPacketFlag )
			{
				
				FML = 'L';
				BreakoutFlag = true;
				
			}
			PayLoad[k] = '\0';
			// MakePacket.
			Packet = new CPacket;
			(*Packet).MakePacket ( FML, '0', 'M', '0', PacketNo, ProcessID, Destination, PayLoad ); 
			(*PacketLinkedList).Add ( (void *) Packet );
			
			if ( BreakoutFlag )
			{
				break;
			}
			
			PacketNo++;
			k = 0;
			
		}
		
		if ( LastPacketFlag )
		{
		
			PayLoad[k] = '\0';
			FML = 'L';
			// Make Packet.
			Packet = new CPacket;
			(*Packet).MakePacket ( FML, '0', 'M', '0', PacketNo, ProcessID, Destination, PayLoad ); 
			(*PacketLinkedList).Add ( (void *) Packet );
			
			break;
			
		}
		
		if ( CurrentString[j] == '\0' || k == 488 )
		{
		
			if ( CurrentString[j] == '\0' )
			{
				EndOfEntryFlag = true;
			}
			if ( k == 488 )
			{
				PacketFullFlag = true;
			}
			continue;
				
		}
		
		PayLoad[k] = CurrentString[j];
		j++;
		k++;
		
	}
	// * End-of-World while end.
}
	
// Reverses a string.
char *strrev ( const char *String )
{

	int Length = strlen ( String );
	char *Temp = new char [ Length + 1 ];
	for ( int i=0; i<Length; i++ )
	{
	
		Temp[i] = String[Length-i-1];
		
	}
	Temp[Length] = '\0';
	
	return strdup ( Temp );
	
}
// **************************************************************************************************************

// ******************************************************************************************************

