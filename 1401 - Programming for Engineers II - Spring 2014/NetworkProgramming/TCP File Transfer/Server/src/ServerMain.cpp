#include <Server.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

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
	char FileBuffer[512]; // Buffer to hold data read from file.
	int Iterations = FileSize/511 + 1; // Number of times file needs to be read.

	File.seekg(0);
	for (int i=0; i<Iterations; i++)
	{
		// Can only read MAXBUFFERSIZE-1 bytes at a time. Last byte is for NULL character.
		// Although NULL isn't needed for binary data but receive() function always sets ReceivedBytes+1 byte as NULL.
		File.read(FileBuffer, 511);
		unsigned int BytesRead;
		i==(Iterations-1) ? BytesRead = FileSize%511 : BytesRead=511;
		ServerObj.Send((void*)FileBuffer, BytesRead);
		ServerObj.Receive(); // Receive ACK (acknowledgement) from client.
	}
	File.close();
	cout << "File transfered." << endl;
	// ****************************************************************

	// Close sockets.
	ServerObj.CloseClientSocket();
	ServerObj.CloseServerSocket();

	return 0;
}
