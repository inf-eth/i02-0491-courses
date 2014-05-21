#include <Server.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#define SENDBUFFERSIZE 4096

int main()
{
	// Create Server object.
	Server ServerObj(TCPSOCKET, DEFAULTSERVERPORT);			// Without any arguments Server will set defaults, TCPSOCKET as type and 6000 as port.

	// Create Server socket and set socket options.
	ServerObj.CreateSocket(TCPSOCKET);		// No argument means TCPSOCKET
	ServerObj.SetSocketOptions();

	// Initialise Server address struct and bind it with Server's socket.
	ServerObj.InitialiseAddress(6000);		// No argument here will take default port.
	ServerObj.Bind();

	// Listen for incoming connections.
	ServerObj.Listen();
	ServerObj.DisplayServerInfo();

	// Accept any incoming connections.
	ServerObj.Accept();
	ServerObj.DisplayClientInfo();

	// ***************** Actual File Transfer *****************
	// 1. Receive the name of file. File should exist in the 'Server' folder.
	cout << "Server waiting for filename." << endl;
	ServerObj.Receive();
	cout << "Client requested file: " << ServerObj.GetBuffer() << endl;

	// 2. Open the file for reading.
	fstream File;
	File.open(ServerObj.GetBuffer(), ios::in|ios::binary);
	if (File.is_open()==false)
	{
		cout << "Error: File failed to open" << endl;
		ServerObj.Send((void*)"NACK", sizeof("NACK")); // Sending NACK if file failed to open.
		exit(0);
	}
	else
	{
		ServerObj.Send((void*)"ACK", sizeof("ACK")); // Sending ACK if file opened.
		ServerObj.Receive(); // Receive ACK from client.
	}

	// 3. Send file size to client.
	File.seekg(ios::beg, ios::end);
	int FileSize = (int)File.tellg();
	ServerObj.Send((void*)&FileSize, sizeof(FileSize));
	ServerObj.Receive(); // Receive ACK (acknowledgement) from client.

	// 4. Send file in a loop.
	char FileBuffer[SENDBUFFERSIZE]; // Buffer to hold data read from file.

	File.seekg(0);
	int TotalBytesSent = 0;
	while (TotalBytesSent != FileSize)
	{
		int BytesRead;
		int BytesSent = 0;
		
		if (FileSize-TotalBytesSent >= SENDBUFFERSIZE)
			BytesRead = SENDBUFFERSIZE;
		else
			BytesRead = FileSize-TotalBytesSent;

		File.read(FileBuffer, BytesRead);
		while (BytesSent != BytesRead)
		{
			BytesSent = ServerObj.Send((void*)(FileBuffer+BytesSent), BytesRead-BytesSent);
			TotalBytesSent = TotalBytesSent + BytesSent;
		}
	}
	File.close();
	cout << "File transfered." << endl;
	// ****************************************************************

	// Close sockets.
	ServerObj.CloseClientSocket();
	ServerObj.CloseServerSocket();

	return 0;
}
