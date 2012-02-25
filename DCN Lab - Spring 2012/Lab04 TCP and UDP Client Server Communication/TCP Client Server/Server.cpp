// The Server ( Server.cpp )

// ***************************************** Header Files ***********************************************
#include <iostream>
#include <cstring>		// strlen()
#include <cstdlib>		// exit()
#include <arpa/inet.h>		// bind(), listen(), accept(), send(), recv()

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
struct sockaddr_in ServerAddress;	// Server's Address.
struct sockaddr_in ClientAddress;	// Client's Address.

// File Descriptors.
int ServerSocketFD;
int ClientSocketFD;

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
// ******************************************************************************************************

// ******************************************************************************************************
// *********************************************** Main *************************************************
// ******************************************************************************************************

int main (int argc, char **argv)
{
	// Setting Server's Listen Port
	ServerPort = SERVERPORT;
	cout << "Server listening on default port " << SERVERPORT << endl;

	// ********************************** Making Server Socekt **************************************
	errorcheck = ServerSocketFD = socket (AF_INET, SOCK_STREAM, 0);
	if (errorcheck == -1)
	{
		cerr << "ERROR001: Creating Server Socket." << endl;
		exit (-1);
	}
	// **********************************************************************************************

	// ************************************* Socket Options *****************************************
	errorcheck = setsockopt (ServerSocketFD, SOL_SOCKET, SO_REUSEADDR, &Yes, sizeof (int));
	if (errorcheck == -1)
	{
		cerr << "ERROR002: Setting socket options. " << endl;
		exit (-1);
	}
	// **********************************************************************************************

	// ****************************************** Bind **********************************************
	// Server address initialization for binding.
	ServerAddress.sin_family = AF_INET;				// Socekt family.
	ServerAddress.sin_addr.s_addr = INADDR_ANY;		// Setting server IP. INADDR_ANY is the localhost IP.
	ServerAddress.sin_port = htons (ServerPort);	// Setting server port.
	fill ((char*)&(ServerAddress.sin_zero), (char*)&(ServerAddress.sin_zero)+8, '\0');

	errorcheck = bind (ServerSocketFD, (sockaddr *)&ServerAddress, sizeof (ServerAddress));
	if (errorcheck == -1)
	{
		cerr << "ERROR003: Binding." << endl;
		exit (-1);
	}
	// **********************************************************************************************

	// No need for listening in UDP.
	// ***************************************** Listening ******************************************
	errorcheck = listen (ServerSocketFD, 0);
	if (errorcheck == -1)
	{
		cerr << "ERROR004: Listening." << endl;
		exit (-1);
	}
	// **********************************************************************************************

	// ************************************** Accept Connection *************************************
	// Accept will block and wait for connections to accept.
	sin_size = sizeof (ClientAddress);
	errorcheck = ClientSocketFD = accept (ServerSocketFD, (sockaddr *)&ClientAddress, &sin_size);
	if (errorcheck == -1)
	{
		cerr << "ERROR006: Accepting." << endl;
		exit(-1);
	}
	cout << "*** Server got connection from " << inet_ntoa (ClientAddress.sin_addr) << " on socket '" << ClientSocketFD << "' ***" << endl;
	// **********************************************************************************************

	// ******************************************** recv ********************************************
	// recv() is blocking and will wait for any messages from client.
	errorcheck = NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0);
	if (errorcheck == -1)
	{
		cerr << "ERROR004 Receiveing" << endl;
		exit (-1);
	}
	Buffer[NumOfBytesReceived] = '\0';
	cout << "Client says: " << Buffer << endl;
	// **********************************************************************************************

	// ******************************************** Send ********************************************
	char ServerMessage[] = "Hello from Server. Now bye!";
	errorcheck = NumOfBytesSent = send (ClientSocketFD, ServerMessage, strlen (ServerMessage), 0);
	if (errorcheck == -1)
	{
		cerr << "ERROR003: Server Sending. " << endl;
		exit (-1);
	}
	// **********************************************************************************************

	// Close connection.
	close (ClientSocketFD);
	close (ServerSocketFD);
	return 0;
}



