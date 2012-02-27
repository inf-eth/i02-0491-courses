// The Client ( Client.cpp )

// ***************************************** Header Files ***********************************************
#include <iostream>
#include <cstring>		// strlen()
#include <cstdlib>		// exit()
#include <netdb.h>		// gethostbyname(), connect(), send(), recv()
#include <fcntl.h>

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

	while (true)
	{
		// Getting Server's menu.
		cout << "Getting server menu..." << endl;
		NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0);
		Buffer[NumOfBytesReceived] = '\0';
		cout << "Bytes received = " << NumOfBytesReceived << " ..." << endl;
		cout << Buffer << endl;

		// If file transfer is starting.
		if (strcmp (Buffer, "File transfer starting...") == 0)
		{
			char ReadytoReceiveFilename[] = "Ready to receive filename...";
			NumOfBytesSent = send (ClientSocketFD, ReadytoReceiveFilename, strlen (ReadytoReceiveFilename), 0);

			// Receive filename.
			char Filename[50];
			NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0);

			Buffer[NumOfBytesReceived] = '\0';
			cout << "Transferring " << Buffer << endl;

			strcpy (Filename, "Copy of ");
			strcat (Filename, Buffer);

			// Open file.
			cout << "File being downloaded as " << Filename << endl;
			int WriteFD = open (Filename, O_WRONLY | O_CREAT, S_IRWXU);

			// Ready to receive byte stream.
			char ReadytoReceiveStream[] = "Ready to receive stream...";
			NumOfBytesSent = send (ClientSocketFD, ReadytoReceiveStream, strlen (ReadytoReceiveStream), 0);

			// Start receiving file.
			while (true)
			{
				NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0);
				Buffer[NumOfBytesReceived] = '\0';

				// Check if file transfer ended otherwise write on file.
				if (strcmp (Buffer, "File transfer ended...") == 0)
				{
					cout << "File transfer done." << endl;
					char FileTransferDone[] = "File Transfer Done...";
					NumOfBytesSent = send (ClientSocketFD, FileTransferDone, strlen (FileTransferDone), 0);
					close (WriteFD);
					break;
				}
				else
				{
					write (WriteFD, Buffer, NumOfBytesReceived);
					cout << "Recieved " << NumOfBytesReceived << " bytes." << endl;
					NumOfBytesSent = send (ClientSocketFD, (void *)&NumOfBytesReceived, sizeof (int), 0);
				}
			}
		}
		// Else if no file transfer then send in client choice.
		else
		{
			// Sending choice.
			char ClientChoice;
			cin >> ClientChoice;
			Buffer[0] = ClientChoice;
			NumOfBytesSent = send (ClientSocketFD, Buffer, 1, 0);
			if (ClientChoice == '3')
			{
				close (ClientSocketFD);
				exit (0);
			}
		}
	}

	// Close client socket and exit.
	close (ClientSocketFD);
	return 0;
}

