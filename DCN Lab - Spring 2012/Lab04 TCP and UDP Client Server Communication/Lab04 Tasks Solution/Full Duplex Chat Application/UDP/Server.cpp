// The Server ( Server.cpp )

// ***************************************** Header Files ***********************************************
#include <iostream>
#include <cstring>		// strlen()
#include <cstdlib>		// exit()
#include <arpa/inet.h>	// inet_ntoa()
#include <netdb.h>		// gethostbyname(), connect(), send(), recv()
#include <pthread.h>

using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::fill;
// ******************************************************************************************************

// ****************************************** #Defintions ***********************************************
#define  MAXBUFFERSIZE		512		// Maximum default buffersize.
#define  SERVERPORT		   6000		// Server will be listening on this port by default.
// ******************************************************************************************************

// ********************************************* Globals ************************************************
// Addresses.
struct hostent *he;
struct sockaddr_in ServerAddress;	// Server's Address.
struct sockaddr_in ClientAddress;	// Client's Address.

// File Descriptors.
int ServerSocketFD;
//int ClientSocketFD;

// Server's Buffer.
char Buffer[MAXBUFFERSIZE];
int  NumOfBytesReceived;
int  NumOfBytesSent;

// Miscellaneous Variables.
int ServerPort;
int Yes = 1;
int AddressLength;
int errorcheck;
socklen_t sin_size;

// Sender and receiver threads.
pthread_t SenderThread;
pthread_t ReceiverThread;
// ******************************************************************************************************

// Thread functions (declaration/prototype).
void* SenderThreadFunction (void *);
void* ReceiverThreadFunction (void *);

// ******************************************************************************************************
// *********************************************** Main *************************************************
// ******************************************************************************************************

int main (int argc, char **argv)
{
	// Standard error checking. Must provide server name/IP and port to connect.
	if ( argc < 3 )
	{
		cout << "ERROR000: Incorrect input arguments." << endl;
		cout << "Usage: './Server [client name/IP] [client port]'" << endl;
		cout << "OR" << endl;
		cout << "if using Makefile: 'make runS ARG=\"[client name/IP] [client port]\"'" << endl;
		exit (-1);
	}

	// Getting client's name/IP.
	if ((he = gethostbyname (argv[1])) == NULL)
	{
		cerr << "ERROR001: Getting client name/IP" << endl;
		exit (-1);
	}

	// Setting Server's Listen Port
	ServerPort = SERVERPORT;
	cout << "Server listening on default port " << SERVERPORT << endl;

	// ********************************** Making Server Socekt **************************************
	errorcheck = ServerSocketFD = socket (AF_INET, SOCK_DGRAM, 0);
	if (errorcheck == -1)
	{
		cerr << "ERROR001: Creating Server Socket." << endl;
		exit (-1);
	}
	// **********************************************************************************************

	// ****************************************** Bind **********************************************
	// Server address initialization for binding.
	ServerAddress.sin_family = AF_INET;				// Socekt family.
	ServerAddress.sin_addr.s_addr = INADDR_ANY;		// Setting server IP. INADDR_ANY is the localhost IP.
	ServerAddress.sin_port = htons (SERVERPORT);	// Setting server port.
	fill ((char*)&(ServerAddress.sin_zero), (char*)&(ServerAddress.sin_zero)+8, '\0');

	errorcheck = bind (ServerSocketFD, (sockaddr *)&ServerAddress, sizeof (ServerAddress));
	if (errorcheck == -1)
	{
		cerr << "ERROR003: Binding." << endl;
		exit (-1);
	}
	// **********************************************************************************************

	// Initializing Client address to connect to.
	ClientAddress.sin_family = AF_INET;							// Socket family.
	ClientAddress.sin_addr = *((in_addr *)(*he).h_addr);		// Client name/IP.
	ClientAddress.sin_port = htons (atoi (argv[2]));			// Client port provided as argument.
	fill ((char*)&(ClientAddress.sin_zero), (char*)&(ClientAddress.sin_zero)+8, '\0');

	cout << "* Press 'ctrl-c' to terminate connection." << endl;
	// Creating Sender and Receiver threads. Essentially threaded function calls.
	pthread_create (&SenderThread, NULL, SenderThreadFunction, NULL);
	pthread_create (&ReceiverThread, NULL, ReceiverThreadFunction, NULL);

	// main() should block and wait on threads. main() is also a separate thread.
	pthread_join (SenderThread, NULL);
	pthread_join (ReceiverThread, NULL);

	// Close connection.
	//close (ClientSocketFD);
	close (ServerSocketFD);
	return 0;
}

// Thread function definition/implementation.
void* SenderThreadFunction (void *tmp)
{
	char ServerMessage[50];

	while (true)
	{
		cout << ">>";
		cin.getline (ServerMessage, 50);
		errorcheck = NumOfBytesSent = sendto (ServerSocketFD, ServerMessage, strlen (ServerMessage), 0, (sockaddr *)&ClientAddress, sizeof (ClientAddress));
		if (errorcheck == -1)
		{
			cerr << "ERROR003: Server Sending. " << endl;
			exit (-1);
		}
	}

	return NULL;
}

void* ReceiverThreadFunction (void *tmp)
{
	while (true)
	{
		socklen_t ClientAddressSize = sizeof (ClientAddress);
		errorcheck = NumOfBytesReceived = recvfrom (ServerSocketFD, Buffer, MAXBUFFERSIZE-1, 0, (sockaddr *)&ClientAddress, &ClientAddressSize);
		if (errorcheck == -1)
		{
			cerr << "ERROR004 Receiveing" << endl;
			exit (-1);
		}
		Buffer[NumOfBytesReceived] = '\0';
		cout << "Server got packet from " << inet_ntoa (ClientAddress.sin_addr) << " on socket " << ServerSocketFD << endl;
		cout << "Client says: " << Buffer << endl;
	}

	return NULL;
}