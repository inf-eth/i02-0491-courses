#include <Client.h>
#include <cstring>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::fill;

CClient::CClient (int pType, int pPort): Type (pType), ClientPort (pPort)
{
	cout << "Client object created with type " << (Type == TCPSOCKET ? "TCP" : "UDP") << " and port " << ClientPort << endl;
}

//CCLient (int = TCPSOCKET, int = DEFAULTPORT);

// Socket function wrappers.
int CClient::CreateSocket (int pType)			// 0 = TCP, 1 = UDP; default is to create TCP socket.
{
	if (pType == TCPSOCKET)
	{
		Type = TCPSOCKET;
		errorcheck = ClientSocketFD = socket (AF_INET, SOCK_STREAM, 0);
	}
	else
	{
		Type = UDPSOCKET;
		errorcheck = ClientSocketFD = socket (AF_INET, SOCK_DGRAM, 0);
	}
	if (errorcheck == -1)
	{
		cerr << "ERROR001: Creating socket of type " << pType << endl;
	}
	return errorcheck;
}

int CClient::InitializeAddress (int pPort)	// Default Client port is 6001.
{
	ClientPort = pPort;
	// Client address initialization for binding.
	ClientAddress.sin_family = AF_INET;				// Socekt family.
	ClientAddress.sin_addr.s_addr = INADDR_ANY;		// Setting client IP. INADDR_ANY is blank IP.
	ClientAddress.sin_port = htons (ClientPort);	// Setting client port.
	fill ((char*)&(ClientAddress.sin_zero), (char*)&(ClientAddress.sin_zero)+8, '\0');
	return 0;
}

int CClient::Bind ()								// Bind Client socket with address.
{
	errorcheck = bind (ClientSocketFD, (sockaddr *)&ClientAddress, sizeof (ClientAddress));
	if (errorcheck == -1)
	{
		cerr << "ERROR002: Binding." << endl;
	}
	return errorcheck;
}

int CClient::Connect (char *pServername, int pServerPort)
{
	struct hostent* Servername;		// Server name/IP.
	if ((Servername = gethostbyname (pServername)) == NULL)
	{
		cerr << "ERROR003: Getting server name/IP" << endl;
		return -1;
	}

	// Initializing Server address to connect to.
	ServerAddress.sin_family = AF_INET;							// Socket family.
	ServerAddress.sin_addr = *((in_addr *)(*Servername).h_addr);	// Server name/IP.
	ServerAddress.sin_port = htons (pServerPort);			// Server port provided as argument.
	fill ((char*)&(ServerAddress.sin_zero), (char*)&(ServerAddress.sin_zero)+8, '\0');

	// Connecting to the server.
	errorcheck = connect (ClientSocketFD, (sockaddr *)&ServerAddress, sizeof (ServerAddress));
	if (errorcheck == -1)
	{
		cerr << "ERROR004: Connecting " << endl;
	}
	return errorcheck;
}

int CClient::Receive ()
{
	errorcheck = NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0);
	if (errorcheck == -1)
	{
		cerr << "ERROR005 Receiveing" << endl;
	}
	Buffer[NumOfBytesReceived] = '\0';
	return errorcheck;
}

int CClient::Send (void *Data, int DataSize)
{
	errorcheck = NumOfBytesSent = send (ClientSocketFD, Data, DataSize, 0);
	if (errorcheck == -1)
	{
		cerr << "ERROR006: Client Sending. " << endl;
	}
	return errorcheck;
}

int CClient::CloseClientSocket ()
{
	errorcheck = close (ClientSocketFD);
	return errorcheck;
}

// Additional Functions.
int CClient::DisplayServerInfo ()
{
	cout << "Server Address: " << inet_ntoa (ServerAddress.sin_addr) << endl;
	cout << "Server Port   : " << ntohs (ServerAddress.sin_port) << endl;
	return 0;
}

int CClient::DisplayClientInfo ()
{
	cout << "Client Address: " << inet_ntoa (ClientAddress.sin_addr) << endl;
	cout << "Client Port   : " << ntohs (ClientAddress.sin_port) << endl;
	cout << "Client Socket : " << ClientSocketFD << endl;
	return 0;
}

int CClient::GetNumOfBytesSent ()
{
	return NumOfBytesSent;
}

int CClient::GetNumOfBytesReceived ()
{
	return NumOfBytesReceived;
}

char* CClient::GetBuffer ()
{
	return Buffer;
}