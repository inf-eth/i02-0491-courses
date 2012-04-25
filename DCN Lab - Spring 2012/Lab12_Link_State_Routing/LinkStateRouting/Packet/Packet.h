// Packet.h

/*

****************
Packet Structure
****************

=====================
|    Total Packet   |
=====================
|       512B        |
=====================
          |
          v
==========================    ======================================================================================================================
|  Header  |   Payload   |    | F/M/E | Seq. No. |  ACK  | ACK No.| Packet No. | Payload Size | CRC  | Process ID  |    Destination |   Payload    |
========================== -> ======================================================================================================================
|    24B   |    488B     |    |  1B   |    1B    |  1B   |   1B   |     4B     |     4B       |  4B  |     4B	   |        4B      |     488B     |
==========================    ======================================================================================================================

F/M/E        : First, intermediate or the last packet in the sequence. Can also be L for LS Packet.
Seq. No.     : Window Seq. No. Only required when implementing windows.
ACK          : Is this ACK, NACK or DATA or ...
ACK No.      : ACK or NACK for what Seq. No.?
Packet No.   : The packet no. in the sequence of packets.
Payload Size : Size of payload carried by the packet. Special payload for a LS packet.
CRC          : CRC
Payload      : The real data.

*/

#include "../NetworkLayer/Graph.h"

#define PACKETSIZE 512

class CPacket
{

	// Public Functions.
	public:

	// * Constructors.
	CPacket ( );										// Standard Constructor.
	CPacket ( char * );								// Special-purpose Constructor 1.
	CPacket ( char, char, char, char, int, int, int, char * );	// Special-purpose Constructor 2.
	
	// * Destructor.	
	~CPacket ( );

	// * Functions for setting the Packet attributes.
	int SetPacketIdendifier ( char );
/*
	int SetSequenceNumber ( char );
	int SetACK ( char );
	int SetACKNumber ( char );
	int SetPacketNumber ( int );
	int SetPayloadSize ( int );
	int SetCRC ( long );
	int SetPayload ( char * );
*/	
	// * Functions for getting the Packet attributes.
	char GetPacketIdentifier ( );
	char GetSequenceNumber ( );
	char GetACK ( );
	char GetACKNumber ( );
	int  GetPacketNumber ( );
	int  GetProcessID ( );
	int  GetPayloadSize ( );
	unsigned long GetCRC ( );
	unsigned long GetCalculatedCRC ( );
	char * GetPayload ( );
	unsigned char * GetUnsignedPayload ( );
	int  GetPacketSize ( ) { return PacketSize; }
	int  GetDestination ( );
	char * GetPacket ( );
	
	int GetSourceID ( );
	int GetNoOfNeighbours ( );
	int GetNeighbourID ( int );
	int GetNeighbourCost ( int );
	int GetTTL ( );
	unsigned int GetLinkStateSequence ( );
	int GetPreviousSource ( );
	void DecrementTTL ( );


	// * Packet Construction Functions.
	int MakePacket ( char * );
	int MakePacket ( int, char * );
	int MakePacket ( char, char, char, char, int, int, int, int, char * );
	int MakePacket ( char, char, char, char, int, int, int, char * );
	int MakePacket ( int, int, NeighbourInfo *, int, int, int );
	
	// * GetPacket.
	int CopyPacket ( char * );

	// * Corrupt Packet.
	void CorruptPacket ( );
	
	// * Private Data Members.
	private:
	
	int  PacketSize;
	unsigned char Packet[PACKETSIZE];
			
};
