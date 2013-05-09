// The Client ( Client.cpp )

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
// ****************************************** #Defintions ***********************************************
#define  MAXBUFFERSIZE		512		// Maximum default buffersize.
// ******************************************************************************************************

// *********************************************** Globals ************************************************
int AddressLength;
int ClientSocketFD;
int errorcheck;

struct hostent *he;
struct sockaddr_in TheirAddress;
struct sockaddr_in ClientAddress;

// Client's Buffer.
char Buffer[MAXBUFFERSIZE];
int NumOfBytesSent;
int NumOfBytesReceived;

// Sender and receiver threads.
pthread_t SenderThread;
pthread_t ReceiverThread;
// ******************************************************************************************************

// Thread functions (declaration/prototype).
void* SenderThreadFunction (void *);
void* ReceiverThreadFunction (void *);

int main (int argc, char *argv[])
{
	// Standard error checking. Must provide server name/IP and port to connect.
	if ( argc < 4 )
	{
		cout << "ERROR000: Incorrect input arguments." << endl;
		cout << "Usage: './UDPClient [Their name/IP] [Their port] [My Port]'" << endl;
		cout << "OR" << endl;
		cout << "if using Makefile: 'make run ARG=\"[Their name/IP] [Their Port] [My Port]\"'" << endl;
		cout << "e.g.: make run ARG=\"localhost 6000 60001\"'" << endl;
		exit (-1);
	}

	// Getting Their name/IP.
	if ((he = gethostbyname (argv[1])) == NULL)
	{
		cerr << "ERROR001: Getting Their name/IP" << endl;
		exit (-1);
	}

	// ********************************** Making Client Socket **************************************
	// Creating a socket for the client.
	errorcheck = ClientSocketFD = socket ( AF_INET, SOCK_DGRAM, 0 );
	if (errorcheck == -1)
	{
		cerr << "ERROR002: Creating socket for client" << endl;
		exit (-1);
	}
	// **********************************************************************************************

	// ******************************************* Bind *********************************************
	// Initializing Client address for binding.
	ClientAddress.sin_family = AF_INET;					// Socket family.
	ClientAddress.sin_addr.s_addr = INADDR_ANY;			// Assigninig client IP.
	ClientAddress.sin_port = htons (atoi (argv[3]));		// Client port.
	fill ((char*)&(ClientAddress.sin_zero), (char*)&(ClientAddress.sin_zero)+8, '\0');

	errorcheck = bind (ClientSocketFD, (sockaddr *)&ClientAddress, sizeof (ClientAddress));
	if (errorcheck == -1)
	{
		cerr << "ERROR003: Binding." << endl;
		exit (-1);
	}
	// **********************************************************************************************

	// ************************************* Initialization *****************************************
	// Initializing Their address to connect to.
	TheirAddress.sin_family = AF_INET;							// Socket family.
	TheirAddress.sin_addr = *((in_addr *)(*he).h_addr);		// Their name/IP.
	TheirAddress.sin_port = htons (atoi (argv[2]));			// Their port provided as argument.
	fill ((char*)&(TheirAddress.sin_zero), (char*)&(TheirAddress.sin_zero)+8, '\0');
	// **********************************************************************************************

	cout << "* Press 'ctrl-c' to terminate connection." << endl;
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
		errorcheck = NumOfBytesSent = sendto (ClientSocketFD, ClientMessage, strlen (ClientMessage), 0, (sockaddr *)&TheirAddress, sizeof (TheirAddress));
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
		socklen_t TheirAddressSize = sizeof (TheirAddress);
		errorcheck = NumOfBytesReceived = recvfrom (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0, (sockaddr *)&TheirAddress, &TheirAddressSize);
		if (errorcheck == -1)
		{
			cerr << "ERROR004 Receiveing" << endl;
			exit (-1);
		}
		Buffer[NumOfBytesReceived] = '\0';
		cout << "Client got packet from " << inet_ntoa (TheirAddress.sin_addr) << " on socket " << ClientSocketFD << endl;
		cout << "They say: " << Buffer << endl;
	}

	return NULL;
}
