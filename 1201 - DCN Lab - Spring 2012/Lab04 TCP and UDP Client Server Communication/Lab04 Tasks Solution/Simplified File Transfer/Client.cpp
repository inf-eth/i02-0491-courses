// The Client ( Client.cpp )

// ***************************************** Header Files ***********************************************
#include <iostream>
#include <cstring>		// strlen()
#include <cstdlib>		// exit()
#include <netdb.h>		// gethostbyname(), connect(), send(), recv()
#include <fcntl.h>

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
// ********************************************************************************************************

int main (int argc, char *argv[])
{
	// Standard error checking. Must provide server name/IP and port to connect.
	if ( argc < 3 )
	{
		cout << "ERROR000: Usage: 'Client [server name or IP] [server port]'" << endl;
		exit (-1);
	}

	// Getting server's name/IP.
	he = gethostbyname (argv[1]);

	// Creating a socket for the client.
	ClientSocketFD = socket ( AF_INET, SOCK_STREAM, 0 );


	setsockopt (ClientSocketFD, SOL_SOCKET, SO_REUSEADDR, &Yes, sizeof (int));

	// Initializing Client address for binding.
	ClientAddress.sin_family = AF_INET;					// Socket family.
	ClientAddress.sin_addr.s_addr = INADDR_ANY;			// Assigninig client IP.
	ClientAddress.sin_port = htons (CLIENTPORT);		// Client port.
	fill ((char*)&(ClientAddress.sin_zero), (char*)&(ClientAddress.sin_zero)+8, '\0');

	// bind()
	bind (ClientSocketFD, (sockaddr *)&ClientAddress, sizeof (ClientAddress));

	// Initializing Server address to connect to.
	ServerAddress.sin_family = AF_INET;							// Socket family.
	ServerAddress.sin_addr = *((in_addr *)(*he).h_addr);	// Server name/IP.
	ServerAddress.sin_port = htons (atoi (argv[2]));			// Server port provided as argument.
	fill ((char*)&(ServerAddress.sin_zero), (char*)&(ServerAddress.sin_zero)+8, '\0');

	// Connecting to the server.
	connect (ClientSocketFD, (sockaddr *)&ServerAddress, sizeof (ServerAddress));

	// send() filename to download
	char ClientMessage[] = "abc.pdf";
	NumOfBytesSent = send (ClientSocketFD, ClientMessage, strlen (ClientMessage), 0);

	// Try to open file.
	int WriteFD = open ("Downloaded abc.pdf", O_WRONLY | O_CREAT, S_IRWXU);
	if (WriteFD < 0)
	{
		cout << "ERROR: Opening file..." << endl;
		exit (-1);
	}

	while (true)
	{
		// recv() is blocking and will wait for any messages.
		NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0);		// Blocking
		Buffer[NumOfBytesReceived] = '\0';

		// Check if end of file.
		if (strcmp (Buffer, "EOF") == 0)
		{
			cout << "File downloaded." << endl;
			close (WriteFD);
			break;
		}

		// Write to file.
		int BytesWritten = write (WriteFD, Buffer, NumOfBytesReceived);

		// Send acknowledgement to server about bytes received/written.
		NumOfBytesSent = send (ClientSocketFD, &BytesWritten, sizeof (int), 0);
	}

	// Close client socket and exit.
	close (ClientSocketFD);
	return 0;
}

