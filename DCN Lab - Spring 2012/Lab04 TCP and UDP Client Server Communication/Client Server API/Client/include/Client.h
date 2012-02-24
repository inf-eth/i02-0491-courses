// Client Interface. Client can be TCP or UDP.
#include <netdb.h>			// gethostbyname (), bind(), listen(), connect(), accept(), send(), receive()
#include <arpa/inet.h>		// inet_ntoa(), bind(), listen(), connect(), accept(), send(), receive()

#define MAXBUFFERSIZE	512
#define TCPSOCKET		0
#define UDPSOCKET		1
#define DEFAULTCLIENTPORT		6001

class CClient
{
private:
	int Type;		// TCP or UDP.
	// Addresses.
	struct sockaddr_in ServerAddress;	// Server's Address structure.
	struct sockaddr_in ClientAddress;	// Client's Address structure.

	// File Descriptors.
	int ClientSocketFD;

	// Client's Buffer.
	char Buffer[MAXBUFFERSIZE];
	int  NumOfBytesReceived;
	int  NumOfBytesSent;

	// Miscellaneous Variables.
	int ClientPort;
	int errorcheck;

public:
	CClient (int = TCPSOCKET, int = DEFAULTCLIENTPORT);
	// Socket function wrappers.
	int CreateSocket (int = TCPSOCKET);			// 0 = TCP, 1 = UDP; default is to create TCP socket.
	int InitializeAddress (int = DEFAULTCLIENTPORT);	// Default Client port is 6001.
	int Bind ();								// Bind Client socket with address.
	int Connect (char *, int);
	int Receive ();
	int Send (void *, int);
	int CloseClientSocket ();

	// Additional functions.
	int GetType () { return Type; }
	int GetPort () { return ClientPort; }
	int GetErrorCheck () { return errorcheck; }

	int DisplayServerInfo ();
	int DisplayClientInfo ();

	char* GetBuffer ();
	int GetNumOfBytesSent ();
	int GetNumOfBytesReceived ();
};