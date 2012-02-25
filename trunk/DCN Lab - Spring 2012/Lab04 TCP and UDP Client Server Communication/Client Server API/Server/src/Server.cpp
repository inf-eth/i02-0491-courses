#include <Server.h>
#include <cstring>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::fill;

CServer::CServer (int pType, int pServerPort): Type (pType), ServerPort (pServerPort)
{
	cout << "Server object created with type " << (Type == TCPSOCKET ? "TCP" : "UDP") << " and port " << ServerPort << endl;
}

int CServer::CreateSocket (int pType)			// 0 = TCP, 1 = UDP; default is to create TCP socket.
{
	if (pType == TCPSOCKET)
	{
		Type = TCPSOCKET;
		errorcheck = ServerSocketFD = socket (AF_INET, SOCK_STREAM, 0);
	}
	else
	{
		Type = UDPSOCKET;
		errorcheck = ServerSocketFD = socket (AF_INET, SOCK_DGRAM, 0);
	}
	if (errorcheck == -1)
	{
		cerr << "ERROR001: Creating socket of type " << pType << endl;
	}
	return errorcheck;
}

int CServer::SetSocketOptions ()					// Set socket options to reuse address.
{
	int Yes = 1;
	errorcheck = setsockopt (ServerSocketFD, SOL_SOCKET, SO_REUSEADDR, &Yes, sizeof (int));
	if (errorcheck == -1)
	{
		cerr << "ERROR002: Setting socket options. " << endl;
	}
	return errorcheck;
}

int CServer::InitializeAddress (int pPort)	// Default Server port is 5000.
{
	ServerPort = pPort;
	// Server address initialization for binding.
	ServerAddress.sin_family = AF_INET;				// Socekt family.
	ServerAddress.sin_addr.s_addr = INADDR_ANY;		// Setting server IP. INADDR_ANY blank IP.
	ServerAddress.sin_port = htons (ServerPort);	// Setting server port.
	fill ((char*)&(ServerAddress.sin_zero), (char*)&(ServerAddress.sin_zero)+8, '\0');
	return 0;
}

int CServer::Bind ()								// Bind Server socket with address.
{
	errorcheck = bind (ServerSocketFD, (sockaddr *)&ServerAddress, sizeof (ServerAddress));
	if (errorcheck == -1)
	{
		cerr << "ERROR003: Binding." << endl;
	}
	return errorcheck;
}

int CServer::Listen ()								// Listen for incoming connections; for TCP Server.
{
	errorcheck = listen (ServerSocketFD, 0);
	if (errorcheck == -1)
	{
		cerr << "ERROR004: Listening." << endl;
	}
	return errorcheck;
}

int CServer::Accept ()								// Accept incoming connections.
{
	socklen_t ClientAddressLength = sizeof (ClientAddress);
	errorcheck = ClientSocketFD = accept (ServerSocketFD, (sockaddr *)&ClientAddress, &ClientAddressLength);
	if (errorcheck == -1)
	{
		cerr << "ERROR005: Accepting." << endl;
		return errorcheck;
	}
	cout << "*** Server got connection from " << inet_ntoa (ClientAddress.sin_addr) << " on socket '" << ClientSocketFD << "' ***" << endl;
	return errorcheck;
}

int CServer::Receive ()
{
	errorcheck = NumOfBytesReceived = recv (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0);
	if (errorcheck == -1)
	{
		cerr << "ERROR006 Receiving" << endl;
		return errorcheck;
	}
	Buffer[NumOfBytesReceived] = '\0';
	return errorcheck;
}

int CServer::Send (void *Data, int DataSize)
{
	errorcheck = NumOfBytesSent = send (ClientSocketFD, Data, DataSize, 0);
	if (errorcheck == -1)
	{
		cerr << "ERROR007: Server Sending. " << endl;
		return errorcheck;
	}
	return errorcheck;
}

// UDP, sendto (data, datasize, IP/name, port);
int CServer::SendTo (void *Data, int DataSize)
{
	errorcheck = NumOfBytesSent = sendto (ServerSocketFD, Data, DataSize, 0, (sockaddr *)&TheirAddress, sizeof (TheirAddress));
	if (errorcheck == -1)
	{
		cerr << "ERROR008: Server Sending to. " << endl;
	}
	return errorcheck;
}
int CServer::SendTo (void *Data, int DataSize, char * pTheirIP, int pTheirPort)
{
	struct hostent* TheirIP;		// Server name/IP.
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

	errorcheck = NumOfBytesSent = sendto (ServerSocketFD, Data, DataSize, 0, (sockaddr *)&TheirAddress, sizeof (TheirAddress));
	if (errorcheck == -1)
	{
		cerr << "ERROR010: Server Sending to. " << endl;
	}
	return errorcheck;
}
// recvfrom ();
int CServer::RecvFrom ()
{
	socklen_t TheirAddressSize = sizeof (TheirAddress);
	errorcheck = NumOfBytesReceived = recvfrom (ServerSocketFD, Buffer, MAXBUFFERSIZE-1, 0, (sockaddr *)&TheirAddress, &TheirAddressSize);
	if (errorcheck == -1)
	{
		cerr << "ERROR011 Receiveing" << endl;
		return errorcheck;
	}
	Buffer[NumOfBytesReceived] = '\0';
	cout << "Server got packet from " << inet_ntoa (TheirAddress.sin_addr) << " on socket " << ServerSocketFD << endl;
	return errorcheck;
}

int CServer::CloseServerSocket ()
{
	errorcheck = close (ServerSocketFD);
	return errorcheck;
}

int CServer::CloseClientSocket ()
{
	errorcheck = close (ClientSocketFD);
	return errorcheck;
}

// Additional Functions.
int CServer::DisplayServerInfo ()
{
	cout << "Server Address: " << inet_ntoa (ServerAddress.sin_addr) << endl;
	cout << "Server Port   : " << ntohs (ServerAddress.sin_port) << endl;
	cout << "Server Socket : " << ServerSocketFD << endl;
	return 0;
}

int CServer::DisplayClientInfo ()
{
	cout << "Client Address: " << inet_ntoa (ClientAddress.sin_addr) << endl;
	cout << "Client Port   : " << ntohs (ClientAddress.sin_port) << endl;
	cout << "Client Socket : " << ClientSocketFD << endl;
	return 0;
}

int CServer::DisplayTheirInfo ()
{
	cout << "Their Address: " << inet_ntoa (TheirAddress.sin_addr) << endl;
	cout << "Their Port   : " << ntohs (TheirAddress.sin_port) << endl;
	return 0;
}

int CServer::GetNumOfBytesSent ()
{
	return NumOfBytesSent;
}

int CServer::GetNumOfBytesReceived ()
{
	return NumOfBytesReceived;
}

char* CServer::GetBuffer ()
{
	return Buffer;
}