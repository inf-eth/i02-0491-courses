// The Server ( Server.cpp )

// ***************************************** Header Files ***********************************************
#include <iostream>
#include <sstream>		// string stream for converting float into string.
#include <cstring>		// strlen()
#include <cstdlib>		// exit()
#ifdef WIN32
#include <WinSock2.h>
#define close closesocket
#else
#include <arpa/inet.h>		// bind(), listen(), accept(), send(), recv()
#define close close
#endif
#include <complex.h>

using std::cerr;
using std::cout;
using std::endl;
using std::fill;
using std::stringstream;
using std::string;			// string.c_str()
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
#ifdef WIN32
int sin_size;
#else
socklen_t sin_size;
#endif
// ******************************************************************************************************

void SafeCall (int, const char *);
// ******************************************************************************************************
// *********************************************** Main *************************************************
// ******************************************************************************************************

int main (int argc, char **argv)
{
#ifdef WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
	{
		cerr << "WSAStartup failed." << endl;
		exit(1);
	}
#endif

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
	errorcheck = setsockopt (ServerSocketFD, SOL_SOCKET, SO_REUSEADDR, (char *)&Yes, sizeof (int));
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

	complex A, B, C;
	cout << "WARNING: Multiplication and division are not properly implemented." << endl;
	while (true)
	{
		// Server Menu
		char ServerMenu[] = "1. Input\n2. Display\n3. Add\n4. Subtract\n5. Multiply\n6. Divide\n7. Exit";
		SafeCall (NumOfBytesSent = send (ClientSocketFD, ServerMenu, strlen (ServerMenu), 0), "send()");

		SafeCall (NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0), "recv()");
		Buffer[NumOfBytesReceived] = '\0';

		// Check Option.
		switch (Buffer[0])
		{
			case '1':
			{
				float temp[4];
				char Input[] = "Input";
				SafeCall (NumOfBytesSent = send (ClientSocketFD, Input, strlen (Input), 0), "send()");

				SafeCall (NumOfBytesReceived = recv (ClientSocketFD, (char *)&temp, 4 * sizeof (float), 0), "recv()");
				A.setreal (temp[0]);
				A.setimg (temp[1]);
				B.setreal (temp[2]);
				B.setimg (temp[3]);
				break;
			}
			case '2':
			{
				stringstream ABstream;
				string ABstreamString;
				char Display[] = "Display";
				SafeCall (NumOfBytesSent = send (ClientSocketFD, Display, strlen (Display), 0), "send()");
				
				// Ready to send.
				SafeCall (NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0), "recv()");
				
				ABstream << "A = " << A.getreal() << (A.getimg() < 0 ? "" : "+") << A.getimg() << "j\n"
						 << "B = " << B.getreal() << (B.getimg() < 0 ? "" : "+") << B.getimg() << "j";
				strcpy (Buffer, ABstream.str().c_str());
				SafeCall (NumOfBytesSent = send (ClientSocketFD, Buffer, strlen (Buffer), 0), "send()");

				// Acknowledgement.
				SafeCall (NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0), "recv()");
				break;
			}
			case '3':
			{
				stringstream Cstream;
				string ABstreamString;
				char Add[] = "Add";
				SafeCall (NumOfBytesSent = send (ClientSocketFD, Add, strlen (Add), 0), "send()");
				
				// Ready to send.
				SafeCall (NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0), "recv()");
				C = A + B;
				Cstream << "A + B = " << C.getreal() << (C.getimg() < 0 ? "" : "+") << C.getimg() << "j";
				strcpy (Buffer, Cstream.str().c_str());
				SafeCall (NumOfBytesSent = send (ClientSocketFD, Buffer, strlen (Buffer), 0), "send()");

				// Acknowledgement.
				SafeCall (NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0), "recv()");
				break;
			}
			case '4':
			{
				stringstream Cstream;
				string ABstreamString;
				char Subtract[] = "Subtract";
				SafeCall (NumOfBytesSent = send (ClientSocketFD, Subtract, strlen (Subtract), 0), "send()");
				
				// Ready to send.
				SafeCall (NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0), "recv()");
				C = A - B;
				Cstream << "A - B = " << C.getreal() << (C.getimg() < 0 ? "" : "+") << C.getimg() << "j";
				strcpy (Buffer, Cstream.str().c_str());
				SafeCall (NumOfBytesSent = send (ClientSocketFD, Buffer, strlen (Buffer), 0), "send()");

				// Acknowledgement.
				SafeCall (NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0), "recv()");
				break;
			}
			case '5':
			{
				stringstream Cstream;
				string ABstreamString;
				char Multiply[] = "Multiply";
				SafeCall (NumOfBytesSent = send (ClientSocketFD, Multiply, strlen (Multiply), 0), "send()");
				
				// Ready to send.
				SafeCall (NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0), "recv()");
				C = A * B;
				Cstream << "A * B = " << C.getreal() << (C.getimg() < 0 ? "" : "+") << C.getimg() << "j";
				strcpy (Buffer, Cstream.str().c_str());
				SafeCall (NumOfBytesSent = send (ClientSocketFD, Buffer, strlen (Buffer), 0), "send()");

				// Acknowledgement.
				SafeCall (NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0), "recv()");
				break;
			}
			case '6':
			{
				stringstream Cstream;
				string ABstreamString;
				char Divide[] = "Divide";
				SafeCall (NumOfBytesSent = send (ClientSocketFD, Divide, strlen (Divide), 0), "send()");
				
				// Ready to send.
				SafeCall (NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0), "recv()");
				C = A / B;
				Cstream << "A / B = " << C.getreal() << (C.getimg() < 0 ? "" : "+") << C.getimg() << "j";
				strcpy (Buffer, Cstream.str().c_str());
				SafeCall (NumOfBytesSent = send (ClientSocketFD, Buffer, strlen (Buffer), 0), "send()");

				// Acknowledgement.
				SafeCall (NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0), "recv()");
				break;
			}
			case '7':
			{
				char Exit[] = "Exit";
				SafeCall (NumOfBytesSent = send (ClientSocketFD, Exit, strlen (Exit), 0), "send()");
				close (ClientSocketFD);
				close (ServerSocketFD);
				exit (0);
				break;
			}
			default:
			{
				break;
			}
		}
	}
	// Close connection.
	close (ClientSocketFD);
	close (ServerSocketFD);
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
