#include "stdafx.h"
#include "Client.h"
#include <cstring>
#include <fstream>
using std::fill;

Client::Client()
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

//Client (int = TCPSOCKET, int = DEFAULTPORT);

// Socket function wrappers.
int Client::CreateSocket(int pType)			// 0 = TCP, 1 = UDP; default is to create TCP socket.
{
	if (pType == TCPSOCKET)
	{
		Type = TCPSOCKET;
		errorcheck = ClientSocketFD = (int)socket(AF_INET, SOCK_STREAM, 0);
	}
	else
	{
		Type = UDPSOCKET;
		errorcheck = ClientSocketFD = (int)socket(AF_INET, SOCK_DGRAM, 0);
	}
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR001: Creating socket"), MB_ICONSTOP);
	}
	return errorcheck;
}

int Client::InitialiseAddress(int pPort)	// Default Client port is 6001.
{
	ClientPort = pPort;
	// Client address initialisation for binding.
	ClientAddress.sin_family = AF_INET;				// Socekt family.
	ClientAddress.sin_addr.s_addr = INADDR_ANY;		// Setting client IP. INADDR_ANY is blank IP.
	ClientAddress.sin_port = htons(ClientPort);	// Setting client port.
	fill((char*)&(ClientAddress.sin_zero), (char*)&(ClientAddress.sin_zero)+8, '\0');
	return 0;
}

int Client::SetSocketOptions()					// Set socket options to reuse address.
{
	int Yes = 1;
	errorcheck = setsockopt(ClientSocketFD, SOL_SOCKET, SO_REUSEADDR, (char*)&Yes, sizeof (int));
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR002: Setting socket options."), MB_ICONSTOP);
	}
	return errorcheck;
}

int Client::Bind()								// Bind Client socket with address.
{
	errorcheck = bind(ClientSocketFD, (sockaddr*)&ClientAddress, sizeof(ClientAddress));
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR002: Binding."), MB_ICONSTOP);
	}
	return errorcheck;
}

int Client::Connect(char* pServername, int pServerPort)
{
	struct hostent* Servername;		// Server name/IP.
	if ((Servername = gethostbyname(pServername)) == NULL)
	{
		AfxMessageBox(_T("ERROR003: Getting server name/IP."), MB_ICONSTOP);
		return -1;
	}

	// Initializing Server address to connect to.
	ServerAddress.sin_family = AF_INET;							// Socket family.
	ServerAddress.sin_addr = *((in_addr*)(*Servername).h_addr);	// Server name/IP.
	ServerAddress.sin_port = htons(pServerPort);			// Server port provided as argument.
	fill((char*)&(ServerAddress.sin_zero), (char*)&(ServerAddress.sin_zero)+8, '\0');

	// Connecting to the server.
	errorcheck = connect(ClientSocketFD, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR004: Connecting."), MB_ICONSTOP);
	}
	return errorcheck;
}

int Client::Receive()
{
	errorcheck = NumOfBytesReceived = recv(ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0);
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR005 Receiveing"), MB_ICONSTOP);
	}
	Buffer[NumOfBytesReceived] = '\0';
	return errorcheck;
}

int Client::Receive(void* Data, int DataSize)
{
	errorcheck = NumOfBytesReceived = recv(ClientSocketFD, (char*)Data, DataSize, 0);
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR005 Receiveing"), MB_ICONSTOP);
	}
	return errorcheck;
}

int Client::Send(void* Data, int DataSize)
{
	errorcheck = NumOfBytesSent = send(ClientSocketFD, (char*)Data, DataSize, 0);
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR006: Client Sending. "), MB_ICONSTOP);
	}
	return errorcheck;
}

// UDP, sendto (data, datasize, IP/name, port);
int Client::SendTo (void* Data, int DataSize)
{
	errorcheck = NumOfBytesSent = sendto(ClientSocketFD, (char*)Data, DataSize, 0, (sockaddr*)&TheirAddress, sizeof(TheirAddress));
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR008: Client Sending to. "), MB_ICONSTOP);
	}
	return errorcheck;
}
int Client::SendTo(void* Data, int DataSize, char* pTheirIP, int pTheirPort)
{
	struct hostent* TheirIP;		// Client name/IP.
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

	errorcheck = NumOfBytesSent = sendto(ClientSocketFD, (char *)Data, DataSize, 0, (sockaddr*)&TheirAddress, sizeof(TheirAddress));
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR010: Client Sending to. "), MB_ICONSTOP);
	}
	return errorcheck;
}
// recvfrom ();
int Client::RecvFrom()
{
	socklen_t TheirAddressSize = sizeof(TheirAddress);
	errorcheck = NumOfBytesReceived = recvfrom (ClientSocketFD, Buffer, MAXBUFFERSIZE-1, 0, (sockaddr*)&TheirAddress, &TheirAddressSize);
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR011 Receiveing."), MB_ICONSTOP);
		return errorcheck;
	}
	Buffer[NumOfBytesReceived] = '\0';
	//cout << "Client got packet from " << inet_ntoa(TheirAddress.sin_addr) << " on socket " << ClientSocketFD << endl;
	return errorcheck;
}
int Client::RecvFrom(void* Data, int DataSize)
{
	socklen_t TheirAddressSize = sizeof(TheirAddress);
	errorcheck = NumOfBytesReceived = recvfrom (ClientSocketFD, (char*)Data, DataSize, 0, (sockaddr*)&TheirAddress, &TheirAddressSize);
	if (errorcheck == -1)
	{
		AfxMessageBox(_T("ERROR011 Receiveing."), MB_ICONSTOP);
		return errorcheck;
	}
	//cout << "Client got packet from " << inet_ntoa(TheirAddress.sin_addr) << " on socket " << ClientSocketFD << endl;
	return errorcheck;
}
int Client::CloseClientSocket()
{
	errorcheck = close(ClientSocketFD);
	return errorcheck;
}

// Additional Functions.
CString Client::GetServerIP()
{
	CString ServerIP(inet_ntoa(ServerAddress.sin_addr));
	return ServerIP;
}

int Client::GetServerPort()
{
	return ntohs(ServerAddress.sin_port);
}

int Client::GetClientPort()
{
	return ntohs(ClientAddress.sin_port);
}

CString Client::GetTheirIP()
{
	CString TheirIP(inet_ntoa(TheirAddress.sin_addr));
	return TheirIP;
}

int Client::GetTheirPort()
{
	return ntohs(TheirAddress.sin_port);
}

int Client::DisplayServerInfo()
{
	//cout << "Server Address: " << inet_ntoa(ServerAddress.sin_addr) << endl;
	//cout << "Server Port   : " << ntohs(ServerAddress.sin_port) << endl;
	return 0;
}

int Client::DisplayClientInfo()
{
	//cout << "Client Address: " << inet_ntoa(ClientAddress.sin_addr) << endl;
	//cout << "Client Port   : " << ntohs(ClientAddress.sin_port) << endl;
	//cout << "Client Socket : " << ClientSocketFD << endl;
	return 0;
}

int Client::DisplayTheirInfo()
{
	//cout << "Their Address: " << inet_ntoa(TheirAddress.sin_addr) << endl;
	//cout << "Their Port   : " << ntohs(TheirAddress.sin_port) << endl;
	return 0;
}

int Client::GetNumOfBytesSent()
{
	return NumOfBytesSent;
}

int Client::GetNumOfBytesReceived()
{
	return NumOfBytesReceived;
}

char* Client::GetBuffer()
{
	return Buffer;
}
