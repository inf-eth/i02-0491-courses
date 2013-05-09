// Packet.cpp

#include "Packet.h"
#include "../CRC/CRC.h"
#include <iostream>
#include <string.h>
#include <sys/time.h>

using namespace std;

// *** Constructors ***

// Default Constructor.
CPacket::CPacket ( )
{

}

// Special-purpose Constructor 1.
CPacket::CPacket ( char *PassedPacket )
{

	int PassedPacketSize = strlen ( PassedPacket );

	for ( int i=0; i < PassedPacketSize; i++ )
	{
		
		Packet[i] = ( unsigned char ) PassedPacket[i];
		
	}
	
	PacketSize = PassedPacketSize;

}

// Special-purpose Constructor 2.
CPacket::CPacket ( char PacketIdentifier, char SequenceNumber, char ACK, char ACKNumber, int PacketNumber, int ProcessID, int Destination, char * Payload )
{

	int PayloadSize = strlen ( Payload );
	
	unsigned char *UnsignedPayload = new unsigned char [ PayloadSize + 1 ];
	
	for ( int i=0; i<PayloadSize; i++ )
	{
		UnsignedPayload[i] = (unsigned char) Payload[i];
	}
	
	UnsignedPayload[PayloadSize] = '\0';
	
	unsigned char *CharPacketNumber = (unsigned char *) &PacketNumber;
	unsigned char *CharProcessID = (unsigned char*) &ProcessID;
	unsigned char *CharPayloadSize = (unsigned char *) &PayloadSize;
	unsigned long CRC = crc32 ( UnsignedPayload, PayloadSize );
	unsigned char *CharCRC = (unsigned char *) &CRC;	
	unsigned char *CharDestination = (unsigned char *) &Destination;	
	
	Packet[0] = (unsigned char) PacketIdentifier;
	Packet[1] = (unsigned char) SequenceNumber;
	Packet[2] = (unsigned char) ACK;
	Packet[3] = (unsigned char) ACKNumber;
		
	Packet[4] = CharPacketNumber[0];
	Packet[5] = CharPacketNumber[1];
	Packet[6] = CharPacketNumber[2];
	Packet[7] = CharPacketNumber[3];
	
	Packet[8] = CharPayloadSize[0];
	Packet[9] = CharPayloadSize[1];
	Packet[10] = CharPayloadSize[2];
	Packet[11] = CharPayloadSize[3];
	
	Packet[12] = CharCRC[0];
	Packet[13] = CharCRC[1];
	Packet[14] = CharCRC[2];
	Packet[15] = CharCRC[3];
	
	Packet[16] = CharProcessID[0];
	Packet[17] = CharProcessID[1];
	Packet[18] = CharProcessID[2];
	Packet[19] = CharProcessID[3];
	
	Packet[20] = CharDestination[0];
	Packet[21] = CharDestination[1];
	Packet[22] = CharDestination[2];
	Packet[23] = CharDestination[3];
	
	for ( int i=0; i < strlen ( Payload ); i++ )
	{
		Packet[i+24] = UnsignedPayload[i];
	}	
	
	PacketSize = PayloadSize + 24;

}
// *********************

// Default Destructor.
CPacket::~CPacket ( )
{

}

int CPacket::SetPacketIdendifier ( char FME )
{
	
	Packet[0] = (unsigned char) FME;
	return 0;
	
}

// * Functions for getting the Packet attributes.
char CPacket::GetPacketIdentifier ( )
{
	return (char)Packet[0];
}

char CPacket::GetSequenceNumber ( )
{
	return (char)Packet[1];
}

char CPacket::GetACK ( )
{
	return (char)Packet[2];
}

char CPacket::GetACKNumber ( )
{
	return (char)Packet[3];
}

int  CPacket::GetPacketNumber ( )
{
	
	int *PacketNumber;
	PacketNumber = (int *) &Packet[4];
	return *PacketNumber;
	
}

int  CPacket::GetProcessID ( )
{

	int *ProcessID;
	ProcessID = (int *) &Packet[16];
	return *ProcessID;

}

int  CPacket::GetPayloadSize ( )
{
	
	int *PayloadSize;
	PayloadSize = (int *) &Packet[8];
	return *PayloadSize;
		
}

int CPacket::GetDestination ( )
{

	int *Destination;
	Destination = (int *) &Packet[20];
	return *Destination;

}

char * CPacket::GetPacket ( )
{

	char *ReturnPacket = new char [ PacketSize + 1 ];
	for ( int i=0; i<PacketSize; i++ )
	{
		ReturnPacket[i] = (char)Packet[i];
	}
	ReturnPacket[PacketSize] = '\0';
	return ReturnPacket;

}

unsigned long CPacket::GetCRC ( )
{
	
	unsigned long *CRC;
		
	CRC = (unsigned long *) &Packet[12];
		
	return *CRC;
	
}

unsigned long CPacket::GetCalculatedCRC ( )
{
	
	unsigned long CRC;
	
	unsigned char *CRCPayload = new unsigned char [ PacketSize - 23 ];
	
	for ( int i=0; i < ( PacketSize - 24 ); i++ )
	{
		CRCPayload[i] = Packet[i+24];
	}
	CRCPayload[	PacketSize - 24 ] = '\0';
	
	CRC = crc32 ( CRCPayload, PacketSize - 24 );
		
	delete CRCPayload;
	
	return CRC;
	
}

char * CPacket::GetPayload ( )
{
	
	int PayloadSize = GetPayloadSize ( );
	char *ReturnPayload = new char[ PayloadSize + 1 ];
	
	for ( int i=0; i < PayloadSize; i++ )
	{
		ReturnPayload[i] = (char)Packet[i+24];
	}
	ReturnPayload[PayloadSize] = '\0';
	
	return ReturnPayload;

}
	
unsigned char * CPacket::GetUnsignedPayload ( )
{
	
	int PayloadSize = GetPayloadSize ( );
	unsigned char *ReturnPayload = new unsigned char[ PayloadSize + 1 ];
	
	for ( int i=0; i < PayloadSize; i++ )
	{
		ReturnPayload[i] = Packet[i+24];
	}
	ReturnPayload[PayloadSize] = '\0';
	
	return ReturnPayload;

}

// * Packet Construction Functions.
int CPacket::MakePacket ( char *PassedPacket )
{

	int PassedPacketSize = strlen ( PassedPacket );

	for ( int i=0; i < PassedPacketSize; i++ )
	{

		Packet[i] = (unsigned char)PassedPacket[i];

	}

	PacketSize = PassedPacketSize;

	return 0;

}

int CPacket::MakePacket ( int Length, char *PassedPacket )
{

	int PassedPacketSize = Length;

	for ( int i=0; i < PassedPacketSize; i++ )
	{

		Packet[i] = (unsigned char)PassedPacket[i];

	}

	PacketSize = PassedPacketSize;

	return 0;

}

int CPacket::MakePacket ( char PacketIdentifier, char SequenceNumber, char ACK, char ACKNumber, int PacketNumber, int ProcessID,  int PayloadSize, int Destination, char * Payload )
{

	//int PayloadSize = strlen ( Payload );

	unsigned char *UnsignedPayload = new unsigned char [ PayloadSize  ];

	for ( int i=0; i<PayloadSize; i++ )
	{
		UnsignedPayload[i] = (unsigned char) Payload[i];
	}

	unsigned char *CharPacketNumber = (unsigned char *) &PacketNumber;
	unsigned char *CharProcessID = (unsigned char *) &ProcessID;
	unsigned char *CharPayloadSize = (unsigned char *) &PayloadSize;
	unsigned long CRC = crc32 ( UnsignedPayload, PayloadSize );
	unsigned char *CharCRC = (unsigned char *) &CRC;
	unsigned char *CharDestination = (unsigned char *) &Destination;	

	Packet[0] = (unsigned char) PacketIdentifier;
	Packet[1] = (unsigned char) SequenceNumber;
	Packet[2] = (unsigned char) ACK;
	Packet[3] = (unsigned char) ACKNumber;

	Packet[4] = CharPacketNumber[0];
	Packet[5] = CharPacketNumber[1];
	Packet[6] = CharPacketNumber[2];
	Packet[7] = CharPacketNumber[3];

	Packet[8] = CharPayloadSize[0];
	Packet[9] = CharPayloadSize[1];
	Packet[10] = CharPayloadSize[2];
	Packet[11] = CharPayloadSize[3];

	Packet[12] = CharCRC[0];
	Packet[13] = CharCRC[1];
	Packet[14] = CharCRC[2];
	Packet[15] = CharCRC[3];

	Packet[16] = CharProcessID[0];
	Packet[17] = CharProcessID[1];
	Packet[18] = CharProcessID[2];
	Packet[19] = CharProcessID[3];
	
	Packet[20] = CharDestination[0];
	Packet[21] = CharDestination[1];
	Packet[22] = CharDestination[2];
	Packet[23] = CharDestination[3];
	
	for ( int i=0; i < PayloadSize; i++ )
	{
		Packet[i+24] = UnsignedPayload[i];
	}

	PacketSize = PayloadSize + 24;

	return 0;

}


int CPacket::MakePacket ( char PacketIdentifier, char SequenceNumber, char ACK, char ACKNumber, int PacketNumber, int ProcessID, int Destination, char * Payload )
{

	int PayloadSize = strlen ( Payload );

	unsigned char *UnsignedPayload = new unsigned char [ PayloadSize + 1 ];

	for ( int i=0; i<=PayloadSize; i++ )
	{
		UnsignedPayload[i] = (unsigned char) Payload[i];
	}

	unsigned char *CharPacketNumber = (unsigned char *) &PacketNumber;
	unsigned char *CharProcessID = (unsigned char *) &ProcessID;
	unsigned char *CharPayloadSize = (unsigned char *) &PayloadSize;
	unsigned long CRC = crc32 ( UnsignedPayload, PayloadSize );
	unsigned char *CharCRC = (unsigned char *) &CRC;
	unsigned char *CharDestination = (unsigned char *) &Destination;	
	
	Packet[0] = (unsigned char) PacketIdentifier;
	Packet[1] = (unsigned char) SequenceNumber;
	Packet[2] = (unsigned char) ACK;
	Packet[3] = (unsigned char) ACKNumber;

	Packet[4] = CharPacketNumber[0];
	Packet[5] = CharPacketNumber[1];
	Packet[6] = CharPacketNumber[2];
	Packet[7] = CharPacketNumber[3];

	Packet[8] = CharPayloadSize[0];
	Packet[9] = CharPayloadSize[1];
	Packet[10] = CharPayloadSize[2];
	Packet[11] = CharPayloadSize[3];

	Packet[12] = CharCRC[0];
	Packet[13] = CharCRC[1];
	Packet[14] = CharCRC[2];
	Packet[15] = CharCRC[3];

	Packet[16] = CharProcessID[0];
	Packet[17] = CharProcessID[1];
	Packet[18] = CharProcessID[2];
	Packet[19] = CharProcessID[3];
	
	Packet[20] = CharDestination[0];
	Packet[21] = CharDestination[1];
	Packet[22] = CharDestination[2];
	Packet[23] = CharDestination[3];
	
	for ( int i=0; i < strlen ( Payload ); i++ )
	{
		Packet[i+24] = UnsignedPayload[i];
	}

	PacketSize = PayloadSize + 24;

	return 0;

}

int CPacket::MakePacket ( int SourceID, int NoOfNeighbours, NeighbourInfo *Neighbour, int TTL, int PreviousSource, int LinkStateSequence )
{

//	cout << "DEBUG: No of Neighbours = " << NoOfNeighbours << endl;
//	cout << "DEBUG: Neighbour max = " << Neighbour[NoOfNeighbours-1].Address << " " << Neighbour[NoOfNeighbours-1].Cost << endl;
	
	unsigned char * CharTTL = (unsigned char *) &TTL;
	unsigned char * CharSourceID = (unsigned char *) &SourceID;
	unsigned char * CharNoOfNeighbours = (unsigned char *) &NoOfNeighbours;
	unsigned char * CharPreviousSource = (unsigned char *) &PreviousSource;
	unsigned char * CharLinkStateSequence = (unsigned char *) &LinkStateSequence;

	Packet[0] = (unsigned char) 'L';

	Packet[4]  = CharTTL[0];
	Packet[5]  = CharTTL[1];
	Packet[6]  = CharTTL[2];
	Packet[7]  = CharTTL[3];

	Packet[8]   = CharPreviousSource[0];
	Packet[9]   = CharPreviousSource[1];
	Packet[10]  = CharPreviousSource[2];
	Packet[11]  = CharPreviousSource[3];

	Packet[12] = CharLinkStateSequence[0];
	Packet[13] = CharLinkStateSequence[1];
	Packet[14] = CharLinkStateSequence[2];
	Packet[15] = CharLinkStateSequence[3];
	
	Packet[16] = CharSourceID[0];
	Packet[17] = CharSourceID[1];
	Packet[18] = CharSourceID[2];
	Packet[19] = CharSourceID[3];

	Packet[20] = CharNoOfNeighbours[0];
	Packet[21] = CharNoOfNeighbours[1];
	Packet[22] = CharNoOfNeighbours[2];
	Packet[23] = CharNoOfNeighbours[3];


	for ( int i=0; i<NoOfNeighbours; i++ )
	{

		unsigned char * CharNeighbourID = (unsigned char *)&Neighbour[i].Address;
		unsigned char * CharNeighbourCost = (unsigned char *)&Neighbour[i].Cost;

		Packet[ 24 + ( 8 * i ) ] = CharNeighbourID[0];
		Packet[ 25 + ( 8 * i ) ] = CharNeighbourID[1];
		Packet[ 26 + ( 8 * i ) ] = CharNeighbourID[2];
		Packet[ 27 + ( 8 * i ) ] = CharNeighbourID[3];

		Packet[ 28 + ( 8 * i ) ] = CharNeighbourCost[0];
		Packet[ 29 + ( 8 * i ) ] = CharNeighbourCost[1];
		Packet[ 30 + ( 8 * i ) ] = CharNeighbourCost[2];
		Packet[ 31 + ( 8 * i ) ] = CharNeighbourCost[3];

	}

	PacketSize = 24 + ( 8 * NoOfNeighbours );
	
	return 0;

}

// * GetPacket.
int CPacket::CopyPacket ( char *PassedPacket )
{

	int ReturnPacketSize = PacketSize;

	for ( int i=0; i < PacketSize; i++ )
	{
		PassedPacket[i] = (char)Packet[i];
	}

	//PassedPacket[PacketSize] = '\0';

	return ReturnPacketSize;

}

// * Corrupt Packet.

// Corrupts a random byte from the packet.
void CPacket::CorruptPacket ( )
{

	struct timezone Temp;
	struct timeval  Temp1;

	gettimeofday ( &Temp1, &Temp );

	int Temp2 = (int) ( Temp1.tv_sec );

	//srand ( Temp2 );

	//int CorruptionIndex = ( rand ( ) % ( PacketSize - 24 ) ) + 24;
	//Packet[CorruptionIndex] = '^';

}

// Get functions for the LS packets.
int CPacket::GetSourceID ( )
{

	int *SourceID;
	SourceID = (int *) &Packet[16];
	return *SourceID;

}

int CPacket::GetNoOfNeighbours ( )
{

	int *NoOfNeighbours;
	NoOfNeighbours = (int *) &Packet[20];
	return *NoOfNeighbours;

}

int CPacket::GetNeighbourID ( int Index )
{

	int *NeighbourID;
	NeighbourID = (int *) &Packet[ 24 + (8 * Index ) ];
	return *NeighbourID;

}

int CPacket::GetNeighbourCost ( int Index )
{

	int *NeighbourCost;
	NeighbourCost = (int *) &Packet[ 28 + (8 * Index ) ];
	return *NeighbourCost;

}

int CPacket::GetTTL ( )
{
	
	int *TTL;
	TTL = (int *) &Packet[ 4 ];
	return *TTL;

}

unsigned int CPacket::GetLinkStateSequence ( )
{

	unsigned int *LinkStateSequence;
	LinkStateSequence = (unsigned int *) &Packet[12];
	return *LinkStateSequence;

}

int CPacket::GetPreviousSource ( )
{

	int *PreviousSource;
	PreviousSource = (int *) &Packet[ 8 ];
	return *PreviousSource;

}

void CPacket::DecrementTTL ( )
{

	int *TTL;
	TTL = (int *) &Packet[ 4 ];
	(*TTL)--;
	
	unsigned char *CharTTL = (unsigned char *) (*TTL);
	
	Packet[4] = CharTTL[0];
	Packet[5] = CharTTL[1];
	Packet[6] = CharTTL[2];
	Packet[7] = CharTTL[3];

}

