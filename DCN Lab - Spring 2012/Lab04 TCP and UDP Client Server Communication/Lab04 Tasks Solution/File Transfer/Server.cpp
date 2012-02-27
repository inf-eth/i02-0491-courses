// The Server ( Server.cpp )

// ***************************************** Header Files ***********************************************
#include <iostream>
#include <cstring>		// strlen()
#include <cstdlib>		// exit()
#include <arpa/inet.h>		// bind(), listen(), accept(), send(), recv()
#include <fcntl.h>

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

	// Sending server menu.
	char FilesList[] = "\
	Welcome to Server ABC. Available services are:\n\
	1. Download Beej's Guide.pdf\n\
	2. Download Basic Networking.pdf\n\
	3. Quit.\n\
	Please enter a number:";

	while (true)
	{
		// Send Server's Menu.
		NumOfBytesSent = send (ClientSocketFD, FilesList, strlen (FilesList), 0);

		// Get option.
		cout << "Expecting input.." << endl;
		NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0);
		Buffer[NumOfBytesReceived] = '\0';
		cout << "Client says: " << Buffer << endl;

		switch (Buffer[0])
		{
			case '1': case '2':
			{
				cout << "Starting file transfer..." << endl;
				// Start file transfer
				char Filename[50];
				if (Buffer[0] == '1')
				{
					strcpy (Filename, "Beej's Guide.pdf");
				}
				else
				{
					strcpy (Filename, "Basic Networking.pdf");
				}

				// Send "File transfer starting..." message.
				char FileTransferStartedMessage[] = "File transfer starting...";
				NumOfBytesSent = send (ClientSocketFD, FileTransferStartedMessage, strlen (FileTransferStartedMessage), 0);

				// Get client acknowledgement.
				NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0);
				Buffer[NumOfBytesReceived] = '\0';
				if (strcmp (Buffer, "Ready to receive filename...") == 0)
				{
					cout << "Client ready to receive filename..." << endl;
				}
				else
				{
					cout << "Error with client receiving filename" << endl;
					exit (-1);
				}
				
				// Open file.
				int ReadFD = open (Filename, O_RDONLY);
				
				// Send filename.
				cout << "Sending filename..." << endl;
				NumOfBytesSent = send (ClientSocketFD, Filename, strlen (Filename), 0);

				// Get client acknowledgement.
				NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0);
				Buffer[NumOfBytesReceived] = '\0';
				if (strcmp (Buffer, "Ready to receive stream...") == 0)
				{
					cout << "Client ready to receive stream..." << endl;
				}
				else
				{
					cout << "Error with client receiving stream" << endl;
					exit (-1);
				}
				
				// Send file stream.
				while (true)
				{
					int BytesRead = read (ReadFD, Buffer, MAXBUFFERSIZE-1);

					// Check if file has ended.
					if (BytesRead <= 0)
					{
						close (ReadFD);
						char FileTransferEndedMessage[] = "File transfer ended...";
						cout << "File transfer ended..." << endl;
						NumOfBytesSent = send (ClientSocketFD, FileTransferEndedMessage, strlen (FileTransferEndedMessage), 0);

						// Getting acknowledgement.
						NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0);
						Buffer[NumOfBytesReceived] = '\0';
						if (strcmp (Buffer, "File Transfer Done...") == 0)
						{
							cout << "File successfully transferred..." << endl;
						}
						else
						{
							cout << "ERROR: Transferring file." << endl;
							exit (-1);
						}
						break;
					}

					// Otherwise send file stream.
					NumOfBytesSent = send (ClientSocketFD, Buffer, BytesRead, 0);
					cout << "Sending " << NumOfBytesSent << " bytes..." << endl;

					// Getting acknowledgement.
					int tempint;
					NumOfBytesReceived = recv (ClientSocketFD, (void *)&tempint, sizeof (int), 0);
					cout << "Client received " << tempint << " bytes." << endl;
					if (tempint != NumOfBytesSent)
					{
						cout << "ERROR: Client did not receive correct number of bytes... " << endl;
						exit (-1);
					}
				}
				break;
			}
			case '3':
			{
				cout << "Client closed connection..." << endl;
				// Close connection and exit.
				close (ClientSocketFD);
				close (ServerSocketFD);
				exit (0);
				break;
			}
			default:
			{
				cout << "Invalid input... " << endl;
				break;
			}
		}
	}

	// Close connection.
	close (ClientSocketFD);
	close (ServerSocketFD);
	return 0;
}



