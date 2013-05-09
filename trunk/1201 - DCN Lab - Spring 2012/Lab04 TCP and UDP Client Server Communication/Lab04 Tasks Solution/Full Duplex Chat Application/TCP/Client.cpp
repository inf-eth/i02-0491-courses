// The Client ( Client.cpp )

// ***************************************** Header Files ***********************************************
#include <iostream>
#include <cstring>		// strlen()
#include <cstdlib>		// exit()
#include <netdb.h>		// gethostbyname(), connect(), send(), recv()
#include <pthread.h>

using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::fill;
// ****************************************** #Defintions ***********************************************
#define  MAXBUFFERSIZE		512		// Maximum default buffersize.
#define  SERVERPORT		   6000		// Server will be listening on this port by default.
#define  CLIENTPORT        6001		// Client will running on this port.
// ******************************************************************************************************

// *********************************************** Globals ************************************************
int AddressLength;
int ClientSocketFD;
int errorcheck;
int Yes = 1;

struct hostent *he;
struct sockaddr_in ServerAddress;
struct sockaddr_in ClientAddress;

// Client's Buffer.
char Buffer[MAXBUFFERSIZE];
int NumOfBytesSent;
int NumOfBytesReceived;

// Sender and receiver threads.
pthread_t SenderThread;
pthread_t ReceiverThread;
// ********************************************************************************************************

// Thread functions (declaration/prototype).
void* SenderThreadFunction (void *);
void* ReceiverThreadFunction (void *);

int main (int argc, char *argv[])
{
	// Standard error checking. Must provide server name/IP and port to connect.
	if ( argc < 3 )
	{
		cout << "ERROR000: Usage: 'Client [server name or IP] [server port]'" << endl;
		exit (-1);
	}

	// Getting server's name/IP.
	if ((he = gethostbyname (argv[1])) == NULL)
	{
		cerr << "ERROR001: Getting server name/IP" << endl;
		exit (-1);
	}

	// ********************************** Making Client Socket **************************************
	// Creating a socket for the client.
	errorcheck = ClientSocketFD = socket ( AF_INET, SOCK_STREAM, 0 );
	if (errorcheck == -1)
	{
		cerr << "ERROR002: Creating socket for client" << endl;
		exit (-1);
	}
	// **********************************************************************************************

	// ************************************* Socket Options *****************************************
	errorcheck = setsockopt (ClientSocketFD, SOL_SOCKET, SO_REUSEADDR, &Yes, sizeof (int));
	if (errorcheck == -1)
	{
		cerr << "ERROR002: Setting socket options. " << endl;
		exit (-1);
	}
	// **********************************************************************************************

	// ******************************************* Bind *********************************************
	// Initializing Client address for binding.
	ClientAddress.sin_family = AF_INET;					// Socket family.
	ClientAddress.sin_addr.s_addr = INADDR_ANY;			// Assigninig client IP.
	ClientAddress.sin_port = htons (CLIENTPORT);		// Client port.
	fill ((char*)&(ClientAddress.sin_zero), (char*)&(ClientAddress.sin_zero)+8, '\0');

	errorcheck = bind (ClientSocketFD, (sockaddr *)&ClientAddress, sizeof (ClientAddress));
	if (errorcheck == -1)
	{
		cerr << "ERROR003: Binding." << endl;
		exit (-1);
	}
	// **********************************************************************************************

	// ****************************************** Connect *******************************************
	// Initializing Server address to connect to.
	ServerAddress.sin_family = AF_INET;							// Socket family.
	ServerAddress.sin_addr = *((in_addr *)(*he).h_addr);	// Server name/IP.
	ServerAddress.sin_port = htons (atoi (argv[2]));			// Server port provided as argument.
	fill ((char*)&(ServerAddress.sin_zero), (char*)&(ServerAddress.sin_zero)+8, '\0');

	// Connecting to the server.
	errorcheck = connect (ClientSocketFD, (sockaddr *)&ServerAddress, sizeof (ServerAddress));
	if (errorcheck == -1)
	{
		cerr << "ERROR003: Connecting " << endl;
		exit (-1);
	}
	// **********************************************************************************************

	cout << "* Connection established. Press 'ctrl-c' to terminate connection." << endl;
	// Creating Sender and Receiver threads. Essentially threaded function calls.
	pthread_create (&SenderThread, NULL, SenderThreadFunction, NULL);
	pthread_create (&ReceiverThread, NULL, ReceiverThreadFunction, NULL);

	// main() should block and wait on threads. main() is also a separate thread.
	pthread_join (SenderThread, NULL);
	pthread_join (ReceiverThread, NULL);

	// Close client socket and exit.
	close (ClientSocketFD);
	return 0;
}

// Thread function definition/implementation.
void* SenderThreadFunction (void *tmp)
{
	char ClientMessage[50];

	while (true)
	{
		cout << ">>";
		cin.getline (ClientMessage, 50);
		errorcheck = NumOfBytesSent = send (ClientSocketFD, ClientMessage, strlen (ClientMessage), 0);
		if (errorcheck == -1)
		{
			cerr << "ERROR003: Client Sending. " << endl;
			exit (-1);
		}
	}

	return NULL;
}

void* ReceiverThreadFunction (void *tmp)
{
	while (true)
	{
		errorcheck = NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0);
		if (errorcheck <= 0)
		{
			if (errorcheck == 0)
			{
				cout << "Connection with Server terminated. Client exiting..." << endl;
			}
			else
			{
				cerr << "ERROR004 Receiveing" << endl;
			}
			exit (errorcheck);
		}
		Buffer[NumOfBytesReceived] = '\0';
		cout << "Server says: " << Buffer << endl;
	}

	return NULL;
}
