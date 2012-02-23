// Server Interface. Server can be TCP or UDP.
#include <arpa/inet.h>

#define MAXBUFFERSIZE	512
#define TCPSOCKET		0
#define UDPSOCKET		1
#define DEFAULTPORT		6000

class CServer
{
private:
	int Type;		// TCP or UDP.
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
	int errorcheck;

public:
	CServer (int = TCPSOCKET, int = DEFAULTPORT);
	// Socket function wrappers.
	int CreateSocket (int = TCPSOCKET);			// 0 = TCP, 1 = UDP; default is to create TCP socket.
	int SetSocketOptions ();					// Set socket options to reuse address.
	int InitializeAddress (int = DEFAULTPORT);	// Default Server port is 5000.
	int Bind ();								// Bind Server socket with address.
	int Listen ();								// Listen for incoming connections; for TCP Server.
	int Accept ();								// Accept incoming connections.
	int Receive ();
	int Send (char *, int);
	int CloseServerSocket ();
	int CloseClientSocket ();

	// Additional functions.
	int DisplayServerInfo ();
	int DisplayClientInfo ();
	char* GetBuffer ();
	int GetNumOfBytesSent ();
	int GetNumOfBytesReceived ();
};