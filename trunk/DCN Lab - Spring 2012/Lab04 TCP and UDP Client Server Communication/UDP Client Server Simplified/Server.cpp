// The Server ( Server.cpp )

// ***************************************** Header Files ***********************************************
#include <iostream>
#include <cstring>			// strlen()
#include <cstdlib>			// exit()
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

// Server's Buffer.
char Buffer[MAXBUFFERSIZE];
int  NumOfBytesReceived;
int  NumOfBytesSent;

// Miscellaneous Variables.
int ServerPort;
int Yes = 1;
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
	
	// Server socket.
	ServerSocketFD = socket (AF_INET, SOCK_DGRAM, 0);
	
	// Set socket options. SO_REUSEADDR will prevent "socket in use" errors if server is shutdown.
	setsockopt (ServerSocketFD, SOL_SOCKET, SO_REUSEADDR, &Yes, sizeof (int));
	
	// Server address initialization for binding.
	ServerAddress.sin_family = AF_INET;				// Socekt family.
	ServerAddress.sin_addr.s_addr = INADDR_ANY;		// Setting server IP. INADDR_ANY is the localhost IP.
	ServerAddress.sin_port = htons (ServerPort);	// Setting server port.
	fill ((char*)&(ServerAddress.sin_zero), (char*)&(ServerAddress.sin_zero)+8, '\0');

	// bind()		
	bind (ServerSocketFD, (sockaddr *)&ServerAddress, sizeof (ServerAddress));

	// recvfrom() is blocking and will wait for any messages from client.
	socklen_t ClientAddressSize = sizeof (ClientAddress);
	NumOfBytesReceived = recvfrom (ServerSocketFD, Buffer, MAXBUFFERSIZE-1, 0, (sockaddr *)&ClientAddress, &ClientAddressSize);
	
	Buffer[NumOfBytesReceived] = '\0';
	cout << "Server got packet from " << inet_ntoa (ClientAddress.sin_addr) << " on socket " << ServerSocketFD << endl;
	cout << "Client says: " << Buffer << endl;

	// sendto()
	char ServerMessage[] = "Hello from Server. Now bye!";
	NumOfBytesSent = sendto (ServerSocketFD, ServerMessage, strlen (ServerMessage), 0, (sockaddr *)&ClientAddress, sizeof (ClientAddress));

	// Close connection.
	close (ServerSocketFD);
	return 0;
}
	
	

