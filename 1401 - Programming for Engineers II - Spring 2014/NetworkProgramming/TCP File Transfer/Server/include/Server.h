// Server Interface. Server can be TCP or UDP.
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
#define DEFAULTSERVERPORT		6000

class Server
{
private:
	int Type;		// TCP or UDP.
	// Addresses.
	struct sockaddr_in ServerAddress;	// Server's Address structure.
	struct sockaddr_in ClientAddress;	// Client's Address structure.
	struct sockaddr_in TheirAddress;	// Default address to sendto() and recvfrom() UDP packets.

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
	Server(int = TCPSOCKET, int = DEFAULTSERVERPORT);
	// Socket function wrappers.
	int CreateSocket(int = TCPSOCKET);			// 0 = TCP, 1 = UDP; default is to create TCP socket.
	int SetSocketOptions();					// Set socket options to reuse address.
	int InitialiseAddress(int = DEFAULTSERVERPORT);	// Default Server port is 5000.

	int Bind();								// Bind Server socket with address.
	int Listen();								// Listen for incoming connections; for TCP Server.
	int Accept();								// Accept incoming connections.

	// TCP send() and recv()
	int Send (void*, unsigned int);
	int Receive();

	// UDP, sendto (data, datasize, IP/name, port);
	int SendTo(void*, unsigned int);
	int SendTo(void*, unsigned int, char*, int);
	// recvfrom();
	int RecvFrom();
	
	int CloseServerSocket();
	int CloseClientSocket();

	// Additional functions.
	int GetType() { return Type; }
	int GetPort() { return ServerPort; }
	int GetErrorCheck() { return errorcheck; }

	int DisplayServerInfo();
	int DisplayClientInfo();
	int DisplayTheirInfo();

	char* GetBuffer();
	int GetNumOfBytesSent();
	int GetNumOfBytesReceived();
};
