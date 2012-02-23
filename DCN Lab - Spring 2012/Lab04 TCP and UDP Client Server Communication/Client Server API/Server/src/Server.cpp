#include <Server.h>
#include <iostream>
#include <cstring>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::fill;
CServer::CServer (int pType, int pServerPort): Type (pType), ServerPort (pServerPort)
{

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
	ServerAddress.sin_addr.s_addr = INADDR_ANY;		// Setting server IP. INADDR_ANY is the localhost IP.
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
		cerr << "ERROR006 Receiveing" << endl;
		return errorcheck;
	}
	Buffer[NumOfBytesReceived] = '\0';
	cout << "Buffer = " << Buffer << endl;
	return errorcheck;
}

int CServer::Send (char *Data, int DataSize)
{
	errorcheck = NumOfBytesSent = send (ClientSocketFD, Data, DataSize, 0);
	if (errorcheck == -1)
	{
		cerr << "ERROR003: Server Sending. " << endl;
		return errorcheck;
	}
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