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

int CClient::SetSocketOptions ()					// Set socket options to reuse address.
{
	int Yes = 1;
	errorcheck = setsockopt (ClientSocketFD, SOL_SOCKET, SO_REUSEADDR, &Yes, sizeof (int));
	if (errorcheck == -1)
	{
		cerr << "ERROR002: Setting socket options. " << endl;
	}
	return errorcheck;
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

// UDP, sendto (data, datasize, IP/name, port);
int CClient::SendTo (void *Data, int DataSize)
{
	errorcheck = NumOfBytesSent = sendto (ClientSocketFD, Data, DataSize, 0, (sockaddr *)&TheirAddress, sizeof (TheirAddress));
	if (errorcheck == -1)
	{
		cerr << "ERROR008: Client Sending to. " << endl;
	}
	return errorcheck;
}
int CClient::SendTo (void *Data, int DataSize, char * pTheirIP, int pTheirPort)
{
	struct hostent* TheirIP;		// Client name/IP.
	if ((TheirIP = gethostbyname (pTheirIP)) == NULL)
	{
		cerr << "ERROR009: Getting Their name/IP" << endl;
		return -1;
	}
	// Initializing Their address to send to.
	TheirAddress.sin_family = AF_INET;							// Socket family.
	TheirAddress.sin_addr = *((in_addr *)(*TheirIP).h_addr);		// Their name/IP.
	TheirAddress.sin_port = htons (pTheirPort);			// Their port provided as argument.
	fill ((char*)&(TheirAddress.sin_zero), (char*)&(TheirAddress.sin_zero)+8, '\0');

	errorcheck = NumOfBytesSent = sendto (ClientSocketFD, Data, DataSize, 0, (sockaddr *)&TheirAddress, sizeof (TheirAddress));
	if (errorcheck == -1)
	{
		cerr << "ERROR010: Client Sending to. " << endl;
	}
	return errorcheck;
}
// recvfrom ();
int CClient::RecvFrom ()
{
	socklen_t TheirAddressSize = sizeof (TheirAddress);
	errorcheck = NumOfBytesReceived = recvfrom (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0, (sockaddr *)&TheirAddress, &TheirAddressSize);
	if (errorcheck == -1)
	{
		cerr << "ERROR011 Receiveing" << endl;
		return errorcheck;
	}
	Buffer[NumOfBytesReceived] = '\0';
	cout << "Client got packet from " << inet_ntoa (TheirAddress.sin_addr) << " on socket " << ClientSocketFD << endl;
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

int CClient::DisplayTheirInfo ()
{
	cout << "Their Address: " << inet_ntoa (TheirAddress.sin_addr) << endl;
	cout << "Their Port   : " << ntohs (TheirAddress.sin_port) << endl;
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