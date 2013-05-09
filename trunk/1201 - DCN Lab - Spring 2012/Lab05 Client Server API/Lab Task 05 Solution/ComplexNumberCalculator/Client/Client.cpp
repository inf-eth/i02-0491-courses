// The Client ( Client.cpp )

// ***************************************** Header Files ***********************************************
#include <iostream>
#include <cstring>		// strlen()
#include <cstdlib>		// exit()
#ifdef WIN32
#include <WinSock2.h>
#define close closesocket
#else
#include <netdb.h>		// gethostbyname(), connect(), send(), recv()
#define close close
#endif

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
// ********************************************************************************************************

void SafeCall (int, const char *);

int main (int argc, char *argv[])
{
#ifdef WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
	{
		cerr << "WSAStartup failed." << endl;
		exit(1);
	}
#endif

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
	errorcheck = setsockopt (ClientSocketFD, SOL_SOCKET, SO_REUSEADDR, (char *)&Yes, sizeof (int));
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

	while (true)
	{
		SafeCall (NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0), "recv()");
		Buffer[NumOfBytesReceived] = '\0';

		// Input Option Case.
		if (strcmp (Buffer, "1. Input\n2. Display\n3. Add\n4. Subtract\n5. Multiply\n6. Divide\n7. Exit") == 0)
		{
			cout << Buffer << endl;
			char option;
			cout << ">>";
			cin >> option;
			SafeCall (NumOfBytesSent = send (ClientSocketFD, (char *)&option, sizeof (char), 0), "send()");
		}
		// 1. Input Case.
		else if (strcmp (Buffer, "Input") == 0)
		{
			float temp[4];
			cout << "Input two complex numbers A and B..." << endl;
			cout << "A.real :";
			cin >> temp[0];
			cout << "A.img :";
			cin >> temp[1];
			
			cout << "B.real :";
			cin >> temp[2];
			cout << "B.img :";
			cin >> temp[3];
			SafeCall (NumOfBytesSent = send (ClientSocketFD, (char *)&temp, 4 * sizeof (float), 0), "send()");
		}
		// 2,3,4,5,6
		else if (
					strcmp (Buffer, "Display") == 0 |
					strcmp (Buffer, "Add") == 0 |
					strcmp (Buffer, "Subtract") == 0 |
					strcmp (Buffer, "Multiply") == 0 |
					strcmp (Buffer, "Divide") == 0)
		{
			char Ready[] = "Ready";
			SafeCall (NumOfBytesSent = send (ClientSocketFD, Ready, strlen (Ready), 0), "send()");
			SafeCall (NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0), "recv()");
			Buffer[NumOfBytesReceived] = '\0';
			cout << Buffer << endl;
			SafeCall (NumOfBytesSent = send (ClientSocketFD, Ready, strlen (Ready), 0), "send()");
		}
		// 7. Exit
		else if (strcmp (Buffer, "Exit") == 0)
		{
			break;
		}
	}
	// Close client socket and exit.
	close (ClientSocketFD);
	return 0;
}

void SafeCall (int returnvalue, const char *FunctionName)
{
	if (returnvalue == -1)
	{
		cerr << "ERROR: " << FunctionName << endl;
		exit (-1);
	}
}
