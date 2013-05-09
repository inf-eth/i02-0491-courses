// The Main Router Implementation File. Router.cpp

// ***************************************** Header Files ***********************************************

#include "Router.h"

// ******************************************************************************************************


// ********************************************* Globals ************************************************

// This node's Information.
CLinkedList NodeInformation;
CLinkedList LinkStateNodes;
CLinkedList LinkStateNodesSequence;

// This node's graph containing information about the whole subnet.
CGraph Graph;

// This Node's routing table.
CRoutingTable RoutingTable;

CLinkedList TestLinkedList;

// File Descriptor Sets.
fd_set MasterSocketFDS;
fd_set ReadSocketFDS;

// Addresses.
struct sockaddr_in RouterSockAddress;	// Server's Address.
struct sockaddr_in ClientSockAddress;	// Client's Address (temporary).

// File Descriptors.
int MaxSocketFD;
int RouterSocketFD;
int ClientSocketFD;

// Recieved Packet.
CPacket ReceivedPacket;

// Server's Buffer.
char IncomingBuffer[MAXBUFFERSIZE];

// Mutex of mutual exclusion.
pthread_mutex_t MutexLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t LinkStateSequenceMutex = PTHREAD_MUTEX_INITIALIZER;

// Router Receiver Thread.
pthread_t RouterReceiver;

// Thread for Floating LS Packets.
pthread_t FloatLSPackets;

// Timer Thread for keeping time.
pthread_t Timer;
unsigned int CurrentSequence;

// Flags.
bool FloatLSPacketsFlag = true;

// Miscellaneous Variables.
int Control;
int Yes = 1;
int RouterAddress;
socklen_t AddressLength;
int i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z; // :)
char *FileName = NULL;
char *SearchPattern = NULL;
char *ConfigFile;
struct hostent *he;

// ******************************************************************************************************

CPacket packet;
// *************************************** Function Prototypes ******************************************

int ReadConfigFile ( char *, CLinkedList * );
void Fetch ( );
int  Decode ( );
void Execute ( int );
void UpdateRoutingTable ( );

// Threads
void * RouterReceiverThread ( void * );
void * FloatLSPacketsThread ( void * );
void * SendPacket ( void * );
void * SendLSPacket ( void * );
void * TimerThread ( void * );

// ******************************************************************************************************

// ******************************************************************************************************
// *********************************************** Main *************************************************
// ******************************************************************************************************

int main ( int argc, char * argv[ ] )
{

	if ( argc != 3 )
	{

		cout << "ERROR000: Invalid argument(s). Usage: ./Router.o [PORT] [CONTROL]." << endl;
		return -1;

	}
	else
	{

		RouterAddress = atoi ( argv[1] );

		ConfigFile = new char[ strlen ( argv[1] ) ];
		strcpy ( ConfigFile, argv[1] );

		Control = atoi ( argv[2] );

		if ( RouterAddress > 1023 )
		{
			cout << "Server listening on port " << RouterAddress << endl;
		}
		else
		{

			cout << "ERROR000: Incorrect argument provided or port less than 1024. " << endl;
			exit ( -1 );

		}

		int ReadFileStatus = 0;
		ReadFileStatus = ReadConfigFile ( argv[1], &NodeInformation );

		if ( ReadFileStatus != 0 )
		{

			cout << "ERROR001: Reading config file. " << endl;
			exit ( -1 );

		}

		Graph.DisplayGraph ( );
		RoutingTable.DisplayRoutingTable ( );
		//ConfigFile = new char [ strlen ( argv[1] ) + 1 ];


/*
		// Displaying the read shared directories.
		cout << "============= Shared Directories =============" << endl;
		DisplayStringLinkedList ( &SharedDirectories, true );
		cout << "==============================================" << endl;

		// Displaying all the shared files.
		cout << "============= Shared Files =============" << endl;
		DisplayStringLinkedList ( &SharedFiles, true );
		cout << "==============================================" << endl;
		cout << "============= Shared Files with Paths =============" << endl;
		DisplayStringLinkedList ( &SharedFilesPaths, true );
		cout << "==============================================" << endl;
*/

	}

/*
	CGraph TestGraph;
	int Neighbours[3];
	int *intPTR;
	intPTR = Neighbours;

	Neighbours[0] = 5001;
	Neighbours[1] = 5002;
	Neighbours[2] = 5003;

	cout << "Adding Node. " << endl;
	TestGraph.AddNode ( 500, 3, &Neighbours[0] );

	cout << "Displaying graph." << endl;
	TestGraph.DisplayGraph ( );
*/
/*
	int int1 = 5000;
	int int2 = 5001;
	int int3 = 5003;

	TestLinkedList.AddNoDupe ( (void * )&int1, 0 );
	TestLinkedList.AddNoDupe ( (void * )&int2, 0 );
	TestLinkedList.AddNoDupe ( (void * )&int3, 0 );

	int Get1, Get2, Get3;

	Get1 = *(int *)TestLinkedList[0];
	Get2 = *(int *)TestLinkedList[1];
	Get3 = *(int *)TestLinkedList[2];

	cout << "first entry is " << Get1 << endl;
	cout << "second entry is " << Get2 << endl;
	cout << "third entry is " << Get3 << endl;
*/

	// Getting host's name.
	if ( ( he = gethostbyname ( "localhost" ) ) == NULL )
	{

		perror ( "ERROR001: Getting host name" );
		exit ( -1 );

	}

	// Generic Stuff.
	ClientSockAddress.sin_family = AF_INET;
	ClientSockAddress.sin_port = htons ( 5000/*ClientPort*/ );
	ClientSockAddress.sin_addr = *( ( struct in_addr * )(*he).h_addr );
	memset ( &(ClientSockAddress.sin_zero ), '\0', 8 );

	// ********************************** Making Server Socekt **************************************
	if ( ( RouterSocketFD = socket ( AF_INET, SOCK_DGRAM, 0 ) ) == -1 )
	{

		perror ( "ERROR001: Creating Server Socket." );
		exit ( -1 );

	}
	// **********************************************************************************************

	// ******************************************* ??? **********************************************
	if ( setsockopt ( RouterSocketFD, SOL_SOCKET, SO_REUSEADDR, &Yes, sizeof ( int ) ) == -1 )
	{

		perror ( "ERROR002: Setting sockopt. " );
		exit ( -1 );

	}
	// **********************************************************************************************

	// ****************************************** Binding *******************************************
	RouterSockAddress.sin_family = AF_INET;
	RouterSockAddress.sin_addr.s_addr = INADDR_ANY;
	RouterSockAddress.sin_port = htons ( RouterAddress );
	memset ( &( RouterSockAddress.sin_zero ), '\0', 8 );

	if ( bind ( RouterSocketFD, ( struct sockaddr * ) &RouterSockAddress, sizeof ( RouterSockAddress ) ) == -1 )
	{

		perror ( "ERROR003: Binding." );
		exit ( -1 );

	}
	// **********************************************************************************************

	void * ServerThreadArgumentPTR;
	CurrentSequence = 0;
	pthread_create ( &FloatLSPackets, NULL, FloatLSPacketsThread, ServerThreadArgumentPTR );
	pthread_create ( &Timer, NULL, TimerThread, ServerThreadArgumentPTR );
	pthread_create ( &RouterReceiver, NULL, RouterReceiverThread, ServerThreadArgumentPTR );
	// ==============================================================================================

/*
	while ( true )
	{

		int Instruction = -1;

		// Fetch ( recvfrom ) the set socket descriptor.
		Fetch ( );
		Instruction = Decode ( );
		Execute ( Instruction );

	}
*/
	// ==============================================================================================

	pthread_exit ( 0 );

}

// ******************************************************************************************************
// ******************************************* Main Ends Here *******************************************
// ******************************************************************************************************

// ***************************************** Router's Reader Thread *************************************
void * RouterReceiverThread ( void * Argument )
{

	FD_ZERO ( &MasterSocketFDS );
	FD_ZERO ( &ReadSocketFDS );

	FD_SET ( RouterSocketFD, &MasterSocketFDS );		// Adding the Server to the file discriptor set.

	struct timeval Time;
	Time.tv_sec = 0;
	Time.tv_usec = 500000;

	for ( ; ; )
	{

		ReadSocketFDS = MasterSocketFDS;

		Time.tv_sec = 0;
		Time.tv_usec = 500000;

		if ( select ( RouterSocketFD + 1, &ReadSocketFDS, NULL, NULL, &Time ) == -1 )
		{

			perror ( "ERROR005: Selecting." );
			exit ( -1 );

		}

		// * If the fd_set is set if.
		if ( FD_ISSET ( RouterSocketFD, &ReadSocketFDS ) )
		{

			Fetch ( );
			int Instruction = Decode ( );
			Execute ( Instruction );

		}

	}

}
// ******************************************************************************************************

// ************************************* Thread for Floating LS Packets *********************************
void * FloatLSPacketsThread ( void * Argument )
{

	while ( !ENDOFWORLD )
	{

		if ( FloatLSPacketsFlag )
		{

			cout << "MESSAGE: Sending LS Packets." << endl;
			/* Send LS Packets to all Neighbours */

			CPacket LSPacket;
			NeighbourInfo *Neighbours = new NeighbourInfo[ *(int *)NodeInformation[1] ];

			for ( int i=0; i< *(int *)NodeInformation[1]; i++ )
			{
				Neighbours[i] = *(NeighbourInfo *)NodeInformation[i+2];
			}

			LSPacket.MakePacket ( RouterAddress, *(int *)NodeInformation[1], Neighbours, 30, RouterAddress, CurrentSequence );

			pthread_mutex_lock ( &LinkStateSequenceMutex );
			CurrentSequence = CurrentSequence + 1;
            pthread_mutex_unlock ( &LinkStateSequenceMutex );

//			cout << "DEBUG: Packet's source is " << LSPacket.GetSourceID ( ) << endl;

			LSPacketArgument *FloatLSPacketArgument = new LSPacketArgument;
			(*FloatLSPacketArgument).LSPacket = LSPacket;

			for ( int i=0; i< *(int *)NodeInformation[1]; i++ )
			{

				(*FloatLSPacketArgument).Destination = Neighbours[i].Address;
				pthread_t LSPacketThread;

				pthread_create ( &LSPacketThread, NULL, SendLSPacket, (void *)FloatLSPacketArgument );

				pthread_join ( LSPacketThread, NULL );

			}

			pthread_mutex_lock ( &MutexLock );
			FloatLSPacketsFlag = false;
			pthread_mutex_unlock ( &MutexLock );
			Graph.DisplayGraph ( );
			RoutingTable.DisplayRoutingTable ( );

		}




	}

}
// ******************************************************************************************************

// ********************************************** Timer Thread ******************************************
void * TimerThread ( void * Argument )
{

	cout << "MESSAGE: Timer Thread started." << endl;
	struct timezone Temp;
	struct timeval  Temp1;
	struct timeval  InitialTime;

	gettimeofday ( &InitialTime, &Temp );
	srand ( InitialTime.tv_usec );

	int CurrentTime = 0;

	while ( !ENDOFWORLD )
	{

		gettimeofday ( &Temp1, &Temp );

		if ( (Temp1.tv_sec - (rand ( ) % 7) - InitialTime.tv_sec) > (CurrentTime + 8)  )
		{
			CurrentTime = ( Temp1.tv_sec - InitialTime.tv_sec );

			pthread_mutex_lock ( &MutexLock );

			/*if ( FloatLSPacketsFlag == true )
			{

				FloatLSPacketsFlag = false;
				cout << "MESSAGE: Stopping LS Packets Flow. Time = " << CurrentTime << endl;
				Graph.DisplayGraph ( );
				RoutingTable.DisplayRoutingTable ( );

			}
			else   */
			{

				ReadConfigFile ( ConfigFile, &NodeInformation );
				FloatLSPacketsFlag = true;
				cout << "MESSAGE: Starting LS Packets Flow. Time = " << CurrentTime << endl;

			}

			pthread_mutex_unlock ( &MutexLock );

		}

	}

}
// ******************************************************************************************************

// ***************************************** Router's Sender Thread *************************************
void *SendPacket ( void * Argument )
{

	// Getting host's name.
	if ( ( he = gethostbyname ( "localhost" ) ) == NULL )
	{

		perror ( "ERROR001: Getting host name" );
		exit ( -1 );

	}

	// Generic Stuff.
	ClientSockAddress.sin_family = AF_INET;
	ClientSockAddress.sin_port = htons ( (*(LSPacketArgument *)Argument).Destination );
	ClientSockAddress.sin_addr = *( ( struct in_addr * )(*he).h_addr );
	memset ( &(ClientSockAddress.sin_zero ), '\0', 8 );

	int bytessent = sendto ( RouterSocketFD, (*(LSPacketArgument *)Argument).LSPacket.GetPacket ( ), (*(LSPacketArgument *)Argument).LSPacket.GetPacketSize ( ), 0, ( struct sockaddr * ) &ClientSockAddress, sizeof ( struct sockaddr ) );

	cout << "MESSAGE: Data Packet sent to : " << (*(LSPacketArgument *)Argument).Destination << endl;

}
// ******************************************************************************************************

// ******************************** Router's Thread for Sending a LS Packet *****************************
void *SendLSPacket ( void * Argument )
{

	// Getting host's name.
	if ( ( he = gethostbyname ( "localhost" ) ) == NULL )
	{

		perror ( "ERROR001: Getting host name" );
		exit ( -1 );

	}

	// Generic Stuff.
	ClientSockAddress.sin_family = AF_INET;
	ClientSockAddress.sin_port = htons ( (*(LSPacketArgument *)Argument).Destination );
	ClientSockAddress.sin_addr = *( ( struct in_addr * )(*he).h_addr );
	memset ( &(ClientSockAddress.sin_zero ), '\0', 8 );

	int bytessent = sendto ( RouterSocketFD, (*(LSPacketArgument *)Argument).LSPacket.GetPacket ( ), (*(LSPacketArgument *)Argument).LSPacket.GetPacketSize ( ), 0, ( struct sockaddr * ) &ClientSockAddress, sizeof ( struct sockaddr ) );

//	cout << "MESSAGE: LS packet sent to : " << (*(LSPacketArgument *)Argument).Destination << endl;

}
// ******************************************************************************************************

// ******************************************************************************************************
// ************************************** Function Implementations **************************************
// ******************************************************************************************************

// ************************************************ Fetch ************************************************
void Fetch ( )
{

	int NumOfBytesReceived;
	AddressLength = sizeof ( struct sockaddr );

	NumOfBytesReceived = recvfrom ( RouterSocketFD, IncomingBuffer, MAXBUFFERSIZE-1, 0, (sockaddr *)&ClientSockAddress, &AddressLength );

	if ( NumOfBytesReceived == -1 )
	{

		perror ( "ERROR005: Receiving." );
		exit ( -1 );

	}

	IncomingBuffer[NumOfBytesReceived] = '\0';
	ReceivedPacket.MakePacket ( NumOfBytesReceived, IncomingBuffer );

}
// *******************************************************************************************************

// *********************************************** Decode ************************************************
int  Decode ( )
{

	switch ( ReceivedPacket.GetPacketIdentifier ( ) )
	{

		case 'F': case 'M': case 'E':
		{

			cout << "MESSAGE: Received a Data Packet destined to " << ReceivedPacket.GetDestination ( ) << endl;
			return 0;
		}

		case 'L':
		{

//			cout << "MESSAGE: LS Packet Received from " << ReceivedPacket.GetSourceID ( ) << endl;
			return 1;

		}


	}
	return -1;

}
// *******************************************************************************************************

// ********************************************** Execute ************************************************
void Execute ( int Instruction )
{

	switch ( Instruction )
	{

		case 0:
		{

			int Destination = ReceivedPacket.GetDestination ( );

			// If the packet is destined to this router.
			if ( Destination == RouterAddress )
			{

				cout << "MESSAGE: Received a packet destined for this router." << endl;

			}
			// Else if the packet is destined somewhere else lookup the routing table.
			else
			{

				int NextHop = RoutingTable.GetNextHop ( Destination );

				if ( NextHop == -1 )
				{

					cout << "ERROR004: Cannot determine routing path for received packet. Dropping packet :( " << endl;
					return;

				}
				else
				{

					CPacket LSPacket;

					LSPacketArgument *FloatLSPacketArgument = new LSPacketArgument;


					char FML = ReceivedPacket.GetPacketIdentifier ( );
					char SequenceNumber = ReceivedPacket.GetSequenceNumber ( );
					char ACK = ReceivedPacket.GetACK ( );
					char ACKNumber = ReceivedPacket.GetACKNumber ( );
					int  PacketNumber = ReceivedPacket.GetPacketNumber ( );
					int  ProcessID = ReceivedPacket.GetProcessID ( );
					int  Destination = ReceivedPacket.GetDestination ( );
					char * PayLoad = ReceivedPacket.GetPayload ( );

					LSPacket.MakePacket ( FML, SequenceNumber, ACK, ACKNumber, PacketNumber, ProcessID, Destination, PayLoad );

					(*FloatLSPacketArgument).LSPacket = LSPacket;
					(*FloatLSPacketArgument).Destination = NextHop;

					pthread_t LSPacketThread;

					pthread_create ( &LSPacketThread, NULL, SendPacket, (void *)FloatLSPacketArgument );

					pthread_join ( LSPacketThread, NULL );

					cout << "MESSAGE: DATA Packet routed to " << NextHop << endl;
					return;

				}

			}
			return;

		}

		case 1:
		{

			bool ForwardFlag = true;
			int Index = 0;
			int *SourceIDPTR = new int;

			int SourceID = ReceivedPacket.GetSourceID ( );
			int PreviousSourceID = ReceivedPacket.GetPreviousSource ( );
			int NoOfNeighbours = ReceivedPacket.GetNoOfNeighbours ( );
			int TTL = ReceivedPacket.GetTTL ( );
			unsigned int LinkStateSequence = ReceivedPacket.GetLinkStateSequence ( );

            *SourceIDPTR = SourceID;
			Index = LinkStateNodes.Search ( (void *)SourceIDPTR, 0 );
            delete SourceIDPTR;

			// If Node doesn't exist in LinkState List.
			if ( Index == -1 )
			{

//              cout << "MESSAGE: Index is -1" << endl;
                int *LinkStateNodePTR = new int;
                unsigned int *LinkStateSequencePTR = new unsigned int;
			    *LinkStateNodePTR = SourceID;
				LinkStateNodes.AddNoDupe ( (void *)LinkStateNodePTR, 0 );
				*LinkStateSequencePTR = LinkStateSequence;
				LinkStateNodesSequence.Add ( (void *)LinkStateSequencePTR );
                cout << "MESSAGE: New Link State Node added with ID " << SourceID << " and Link State Sequence " << LinkStateSequence << endl;

			}
			// If Node exists
			else
			{

                // If new sequence.
				if ( LinkStateSequence > *(unsigned int *)LinkStateNodesSequence[Index] )
                {
//                  cout << "MESSAGE: New Link State sequence received " << LinkStateSequence << ". Old sequence is " << *(unsigned int *)LinkStateNodesSequence[Index] << endl;
                    unsigned int *LinkStateSequencePTR = new unsigned int;
                    *LinkStateSequencePTR = LinkStateSequence;
                    LinkStateNodesSequence.Modify ( Index, (void *)LinkStateSequencePTR, 3 );

                }

				else
				{
                    // If router went down and restarted.
                    if ( LinkStateSequence == 0 )
                    {
                        unsigned int *LinkStateSequencePTR = new unsigned int;
                        *LinkStateSequencePTR = 0;
                        LinkStateNodesSequence.Modify ( Index, (void *)LinkStateSequencePTR, 3 );
                        cout << "MESSAGE: Router " << SourceID << " went down. Resetting its Link State Sequence to 0." << endl;
                    }
                    // If old sequence then break out.
                    else
                    {
                        //cout << "MESSAGE: Obsolete Link State Sequence " << LinkStateSequence << " received. Current sequence is " << *(unsigned int *)LinkStateNodesSequence[Index] << ". Packet dropped..." << endl;
                        return;
                    }

				}

			}

			if ( TTL == 0 )
			{
				return;
			}

			NeighbourInfo *NeighboursInfoPTR = new NeighbourInfo[NoOfNeighbours];

			for ( int i=0; i<NoOfNeighbours; i++ )
			{

				NeighboursInfoPTR[i].Address = ReceivedPacket.GetNeighbourID ( i );
				NeighboursInfoPTR[i].Cost = ReceivedPacket.GetNeighbourCost ( i );

			}

			int GraphChanged = Graph.AddNode ( SourceID, NoOfNeighbours, NeighboursInfoPTR );
			if (  GraphChanged == -1 )
			{
				//ForwardFlag = false;
			}
			else
			{
				Graph.DisplayGraph ( );
				Graph.CalculateTranslation ( );
				Graph.CalculateDist ( );
				Graph.DisplayDist ( );
				UpdateRoutingTable ( );
			}

			if ( ForwardFlag )
			{


				CPacket LSPacket;
				LSPacket.MakePacket ( SourceID, NoOfNeighbours, NeighboursInfoPTR, TTL-1, RouterAddress, CurrentSequence );

				LSPacketArgument *FloatLSPacketArgument = new LSPacketArgument;
				(*FloatLSPacketArgument).LSPacket = LSPacket;

				NeighbourInfo *Neighbours = new NeighbourInfo[ *(int *)NodeInformation[1] ];

				for ( int i=0; i< *(int *)NodeInformation[1]; i++ )
				{
					Neighbours[i] = *(NeighbourInfo *)NodeInformation[i+2];
				}

				for ( int i=0; i< *(int *)NodeInformation[1]; i++ )
				{

					(*FloatLSPacketArgument).Destination = Neighbours[i].Address;

					if ( (*FloatLSPacketArgument).Destination == SourceID )
					{
						continue;
					}

					pthread_t LSPacketThread;

					pthread_create ( &LSPacketThread, NULL, SendLSPacket, (void *)FloatLSPacketArgument );

					pthread_join ( LSPacketThread, NULL );

				}


			}

			return;

		}

		default:
		{

			cout << "ERROR003: Unidentified packet received. Dropping... " << endl;
			return;

		}

	}

/*
	char HostNamePRE[] = "Your Server is : ";
	char HostNameAPP[50];
	char HostNameAPP1[] = ".\n";

	gethostname ( HostNameAPP, 50 );

	strcat ( HostNamePRE, HostNameAPP );
	strcat ( HostNamePRE, HostNameAPP1 );

	sendto ( RouterSocketFD, HostNamePRE, strlen ( HostNamePRE ), 0, ( struct sockaddr * ) &ClientSockAddress, sizeof ( struct sockaddr ) );
*/

}
// *******************************************************************************************************

// ***************************************** Reads a Configuration File **********************************

// Assumes a single shared directory path cannot exceed 510 characters.
int  ReadConfigFile ( char *PassedFilename, CLinkedList *NodeInformation )
{

	int NoOfNeighbours;
	NeighbourInfo *NeighboursInfoPTR;

	NeighbourInfo *NeighbourInfoPTR;
	char DotCFG[] = ".cfg";
	char *ReadFileName = new char [ strlen ( PassedFilename ) + 5 ];
	ReadFileName[0] = '\0';

	strcpy ( ReadFileName, PassedFilename );
	strcat ( ReadFileName, DotCFG );

	int CheckFD = open ( ReadFileName, O_RDONLY );
	if ( CheckFD < 0 )
	{
		return -1;
	}
	close ( CheckFD );

	(*NodeInformation).Empty ( );

	cout << "Reading config file '" << ReadFileName << endl;
	fstream ReadFile;

 	ReadFile.open ( ReadFileName );

	int  *IntPTR;

	IntPTR = new int;
	*IntPTR = RouterAddress;
	(*NodeInformation).AddNoDupe ( (void *)IntPTR, 0 );

	IntPTR = new int;
	ReadFile >> *IntPTR;
	(*NodeInformation).AddNoDupe ( (void *)IntPTR, 0 );

	NoOfNeighbours = *IntPTR;

	NeighboursInfoPTR = new NeighbourInfo[NoOfNeighbours];

	for ( int i=0; i<NoOfNeighbours; i++ )
	{

		NeighbourInfoPTR = new NeighbourInfo;
		ReadFile >> (*NeighbourInfoPTR).Address;
		NeighboursInfoPTR[i].Address = (*NeighbourInfoPTR).Address;

		ReadFile >> (*NeighbourInfoPTR).Cost;
		NeighboursInfoPTR[i].Cost = (*NeighbourInfoPTR).Cost;

		(*NodeInformation).AddNoDupe ( (void *)NeighbourInfoPTR, 2 );

		RoutingTable.AddEntry ( (*NeighbourInfoPTR).Address, (*NeighbourInfoPTR).Address, (*NeighbourInfoPTR).Cost );

	}

	ReadFile.close ( );

	Graph.AddNode ( RouterAddress, NoOfNeighbours, NeighboursInfoPTR );
	Graph.CalculateTranslation ( );
	Graph.CalculateDist ( );
	Graph.DisplayDist ( );
	UpdateRoutingTable ( );

	return 0;

}

void UpdateRoutingTable ( )
{

	int NodeIDs[ Graph.GetNoOfEntries ( ) ];
	for ( int i=0; i<Graph.GetNoOfEntries ( ); i++ )
	{

		NodeIDs[i] = Graph.GetID ( i );

	}

	for ( int i=0; i<Graph.GetNoOfEntries ( ); i++ )
	{

		RoutingTable.AddEntry ( NodeIDs[i], Graph.GetNextHop ( RouterAddress, NodeIDs[i] ), 1 );

	}


}


// ******************************************************************************************************
// ********************************** Function Implementations End Here *********************************
// ******************************************************************************************************


