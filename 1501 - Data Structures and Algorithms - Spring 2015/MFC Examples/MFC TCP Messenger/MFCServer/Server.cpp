#include "stdafx.h"
#include "Server.h"
#include <cstring>
#include <fstream>
using std::fill;

Server::Server()
{
	#ifdef WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
	{
		AfxMessageBox(_T("WSAStartup failed"), MB_ICONSTOP);
		exit(1);
	}
	#endif
}

int Server::CreateSocket(int pType)			// 0 = TCP, 1 = UDP; default is to create TCP socket.
{
	if (pType == TCPSOCKET)
	{
		Type = TCPSOCKET;
		errorcheck = ServerSocketFD = (int)socket(AF_INET, SOCK_STREAM, 0);
	}
	else
	{
		Type = UDPSOCKET;
		errorcheck = ServerSocketFD = (int)socket(AF_INET, SOCK_DGRAM, 0);
	}
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR001: Creating socket"), MB_ICONSTOP);
	}
	return errorcheck;
}

int Server::SetSocketOptions()					// Set socket options to reuse address.
{
	int Yes = 1;
	errorcheck = setsockopt(ServerSocketFD, SOL_SOCKET, SO_REUSEADDR, (char*)&Yes, sizeof(int));
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR002: Setting socket options."), MB_ICONSTOP);
	}
	return errorcheck;
}

int Server::InitialiseAddress(int pPort)	// Default Server port is 5000.
{
	ServerPort = pPort;
	// Server address initialisation for binding.
	ServerAddress.sin_family = AF_INET;				// Socekt family.
	ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);		// Setting server IP. INADDR_ANY blank IP.
	ServerAddress.sin_port = htons(ServerPort);	// Setting server port.
	fill((char*)&(ServerAddress.sin_zero), (char*)&(ServerAddress.sin_zero)+8, '\0');
	return 0;
}

int Server::Bind()								// Bind Server socket with address.
{
	errorcheck = bind(ServerSocketFD, (sockaddr *)&ServerAddress, sizeof(ServerAddress));
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR002: Binding."), MB_ICONSTOP);
	}
	return errorcheck;
}

int Server::Listen()								// Listen for incoming connections; for TCP Server.
{
	errorcheck = listen(ServerSocketFD, 0);
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR004: Listening."), MB_ICONSTOP);
	}
	return errorcheck;
}

int Server::Accept()								// Accept incoming connections.
{
	socklen_t ClientAddressLength = sizeof(ClientAddress);
	errorcheck = ClientSocketFD = (int)accept(ServerSocketFD, (sockaddr*)&ClientAddress, &ClientAddressLength);
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR005: Accepting."), MB_ICONSTOP);
		return errorcheck;
	}
	//cout << "*** Server got connection from " << inet_ntoa(ClientAddress.sin_addr) << " on socket '" << ClientSocketFD << "' ***" << endl;
	return errorcheck;
}

int Server::Receive()
{
	errorcheck = NumOfBytesReceived = recv(ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0);
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR006: Receiving."), MB_ICONSTOP);
		return errorcheck;
	}
	Buffer[NumOfBytesReceived] = '\0';
	return errorcheck;
}

int Server::Receive(void* Data, int DataSize)
{
	errorcheck = NumOfBytesReceived = recv(ClientSocketFD, (char*)Data, DataSize, 0);
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR006: Receiving."), MB_ICONSTOP);
		return errorcheck;
	}
	return errorcheck;
}

int Server::Send(void* Data, int DataSize)
{
	errorcheck = NumOfBytesSent = send(ClientSocketFD, (char*)Data, DataSize, 0);
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR007: Server Sending. "), MB_ICONSTOP);
		return errorcheck;
	}
	return errorcheck;
}

// UDP, sendto(data, datasize, IP/name, port);
int Server::SendTo(void* Data, int DataSize)
{
	errorcheck = NumOfBytesSent = sendto(ServerSocketFD, (char*)Data, DataSize, 0, (sockaddr*)&TheirAddress, sizeof(TheirAddress));
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR008: Server Sending to. "), MB_ICONSTOP);
	}
	return errorcheck;
}
int Server::SendTo(void* Data, int DataSize, char* pTheirIP, int pTheirPort)
{
	struct hostent* TheirIP;		// Server name/IP.
	if ((TheirIP = gethostbyname(pTheirIP)) == NULL)
	{
		AfxMessageBox(_T("ERROR009: Getting Their name/IP."), MB_ICONSTOP);
		return -1;
	}
	// Initializing Their address to send to.
	TheirAddress.sin_family = AF_INET;							// Socket family.
	TheirAddress.sin_addr = *((in_addr*)(*TheirIP).h_addr);		// Their name/IP.
	TheirAddress.sin_port = htons(pTheirPort);			// Their port provided as argument.
	fill((char*)&(TheirAddress.sin_zero), (char*)&(TheirAddress.sin_zero)+8, '\0');

	errorcheck = NumOfBytesSent = sendto(ServerSocketFD, (char*)Data, DataSize, 0, (sockaddr*)&TheirAddress, sizeof(TheirAddress));
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR010: Server Sending to. "), MB_ICONSTOP);
	}
	return errorcheck;
}
// recvfrom ();
int Server::RecvFrom()
{
	socklen_t TheirAddressSize = sizeof(TheirAddress);
	errorcheck = NumOfBytesReceived = recvfrom(ServerSocketFD, Buffer, MAXBUFFERSIZE-1, 0, (sockaddr*)&TheirAddress, &TheirAddressSize);
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR011 Receiveing."), MB_ICONSTOP);
		return errorcheck;
	}
	Buffer[NumOfBytesReceived] = '\0';
	//cout << "Server got packet from " << inet_ntoa(TheirAddress.sin_addr) << " on socket " << ServerSocketFD << endl;
	return errorcheck;
}

int Server::RecvFrom(void* Data, int DataSize)
{
	socklen_t TheirAddressSize = sizeof(TheirAddress);
	errorcheck = NumOfBytesReceived = recvfrom(ServerSocketFD, (char*)Data, DataSize, 0, (sockaddr*)&TheirAddress, &TheirAddressSize);
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR011 Receiveing."), MB_ICONSTOP);
		return errorcheck;
	}
	//cout << "Server got packet from " << inet_ntoa(TheirAddress.sin_addr) << " on socket " << ServerSocketFD << endl;
	return errorcheck;
}

int Server::CloseServerSocket()
{
	errorcheck = close(ServerSocketFD);
	return errorcheck;
}

int Server::CloseClientSocket()
{
	errorcheck = close(ClientSocketFD);
	return errorcheck;
}

// Additional Functions.
int Server::GetServerPort()
{
	return ntohs(ServerAddress.sin_port);
}

CString Server::GetClientIP()
{
	CString ClientIP(inet_ntoa(ClientAddress.sin_addr));
	return ClientIP;
}

int Server::GetClientPort()
{
	return ntohs(ClientAddress.sin_port);
}

CString Server::GetTheirIP()
{
	CString TheirIP(inet_ntoa(TheirAddress.sin_addr));
	return TheirIP;
}

int Server::GetTheirPort()
{
	return ntohs(TheirAddress.sin_port);
}

int Server::DisplayServerInfo()
{
	//cout << "Server Port   : " << ntohs(ServerAddress.sin_port) << endl;
	//cout << "Server Socket : " << ServerSocketFD << endl;
	return 0;
}

int Server::DisplayClientInfo()
{
	//cout << "Client Address: " << inet_ntoa(ClientAddress.sin_addr) << endl;
	//cout << "Client Port   : " << ntohs(ClientAddress.sin_port) << endl;
	//cout << "Client Socket : " << ClientSocketFD << endl;
	return 0;
}

int Server::DisplayTheirInfo()
{
	//cout << "Their Address: " << inet_ntoa(TheirAddress.sin_addr) << endl;
	//cout << "Their Port   : " << ntohs(TheirAddress.sin_port) << endl;
	return 0;
}

int Server::GetNumOfBytesSent()
{
	return NumOfBytesSent;
}

int Server::GetNumOfBytesReceived()
{
	return NumOfBytesReceived;
}

char* Server::GetBuffer()
{
	return Buffer;
}
