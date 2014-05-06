// Client Interface. Client can be TCP or UDP.
#if defined __linux__ || defined __CYGWIN__
#include <netdb.h>			// gethostbyname (), bind(), listen(), connect(), accept(), send(), receive()
#include <arpa/inet.h>		// inet_ntoa(), bind(), listen(), connect(), accept(), send(), receive()
#include <unistd.h>			// close()
#define close close
#else
#include <WinSock2.h>
#define close closesocket
#define socklen_t int
#endif

#define MAXBUFFERSIZE	512
#define TCPSOCKET		0
#define UDPSOCKET		1
#define DEFAULTCLIENTPORT		6001

class Client
{
private:
	int Type;		// TCP or UDP.
	// Addresses.
	struct sockaddr_in ServerAddress;	// Server's Address structure.
	struct sockaddr_in ClientAddress;	// Client's Address structure.
	struct sockaddr_in TheirAddress;	// Their Address structure for UDP communication.

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
	Client(int = TCPSOCKET, int = DEFAULTCLIENTPORT);
	// Socket function wrappers.
	int CreateSocket(int = TCPSOCKET);			// 0 = TCP, 1 = UDP; default is to create TCP socket.
	int InitialiseAddress(int = DEFAULTCLIENTPORT);	// Default Client port is 6001.
	int SetSocketOptions();					// Set socket options to reuse address.
	int Bind();								// Bind Client socket with address.
	int Connect(char*, int);

	// TCP send() and receive().
	int Send(void*, unsigned int);
	int Receive();

	// UDP, sendto (data, datasize, IP/name, port);
	int SendTo(void*, unsigned int);
	int SendTo(void*, unsigned int, char*, int);
	// recvfrom();
	int RecvFrom();

	int CloseClientSocket();

	// Additional functions.
	int GetType() { return Type; }
	int GetPort() { return ClientPort; }
	int GetErrorCheck() { return errorcheck; }

	int DisplayServerInfo();
	int DisplayClientInfo();
	int DisplayTheirInfo();

	char* GetBuffer();
	int GetNumOfBytesSent();
	int GetNumOfBytesReceived();
};
