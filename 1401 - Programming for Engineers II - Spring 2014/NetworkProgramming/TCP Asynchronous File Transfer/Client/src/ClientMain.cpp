#include <Client.h>
#include <cstdlib>			// exit(), atoi()
#include <cstring>			// strlen()
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

#define RECVBUFFERSIZE 4096

int main()
{
	// Create Client object.
	Client ClientObj(TCPSOCKET, DEFAULTCLIENTPORT);			// Can create an object without arguments. Defaults are TCPSOCKET and DEFAULTPORT (6001).

	// Create Client Socket.
	ClientObj.CreateSocket(TCPSOCKET);
	ClientObj.SetSocketOptions();

	// Initialise and bind Client address.
	ClientObj.InitialiseAddress(DEFAULTCLIENTPORT);	// Without any argument default port will be chosen.
	ClientObj.Bind();

	char ServerName[24];
	int ServerPort;
	cout << "Enter Server name or IP: "; // Use localhost or 127.0.0.1 for local server.
	cin.getline(ServerName, 24);
	cout << "Enter Server port: ";
	cin >> ServerPort;

	// Connect to Server. Server name/IP and port are provided as arguments.
	ClientObj.Connect(ServerName, ServerPort);

	// ********************** Actual File Transfer **********************
	char Filename[40];
	cout << "Enter filename to download from server (STL.pdf): ";
	if (cin.peek() == '\n') cin.ignore(); // If input skips.
	cin.getline(Filename, 40);

	// 1. Send filename to server.
	ClientObj.Send((void*)Filename, (unsigned int)strlen(Filename));
	ClientObj.Receive(); // Receive ACK or NACK

	// 2. Checking if file opened.
	if (!strcmp(ClientObj.GetBuffer(), "NACK"))
	{
		cout << "Error: opening file." << endl;
		exit(0);
	}
	else
		ClientObj.Send((void*)"ACK", (unsigned int)strlen("ACK")); // Send ACK.

	// 3. Getting filesize.
	ClientObj.Receive();
	int FileSize = *((int*)ClientObj.GetBuffer());
	cout << "Filesize is " << FileSize << "B (" << (double)FileSize/1024 << "KB, " << (double)FileSize/1024/1024 << "MB)." << endl;
	ClientObj.Send((void*)"ACK", sizeof("ACK")); // Sending ACK.

	// 4. Receiving file in a loop.
	fstream File;
	string Received = "Received_";
	Received = Received + Filename;
	File.open(Received.c_str(), ios::out|ios::binary|ios::trunc);
	int TotalBytesReceived = 0;
	char FileBuffer[RECVBUFFERSIZE];
	while (TotalBytesReceived != FileSize)
	{
		int BytesReceived = ClientObj.Receive((void*)FileBuffer, RECVBUFFERSIZE);
		File.write(FileBuffer, BytesReceived);
		TotalBytesReceived = TotalBytesReceived + BytesReceived;
	}
	File.close();
	cout << "File received." << endl; // Received file is in 'Client' folder.

	ClientObj.CloseClientSocket();

	return 0;
}
