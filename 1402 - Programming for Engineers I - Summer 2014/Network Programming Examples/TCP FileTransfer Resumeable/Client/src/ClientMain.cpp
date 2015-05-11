#include <Client.h>
#include <cstdlib>			// exit(), atoi()
#include <cstring>			// strlen()
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	// Create Client object.
	Client ClientObj;

	// Create Client Socket.
	ClientObj.CreateSocket(TCPSOCKET);
	ClientObj.SetSocketOptions();

	// Initialise and bind Client address.
	ClientObj.InitialiseAddress(6001);
	ClientObj.Bind();

	char ServerName[24];
	int ServerPort;
	cout << "Enter Server name or IP: "; // Use localhost or 127.0.0.1 for local server.
	cin.getline(ServerName, 24);
	cout << "Enter Server port: ";
	cin >> ServerPort;

	// Connect to Server. Server name/IP and port are provided as arguments.
	ClientObj.Connect(ServerName, ServerPort);

	// Send and receive.
	int Offset;
	fstream File;
	File.open("received.pdf", ios::in|ios::out|ios::binary);
	if (File.is_open()==true)
	{
		File.seekp(0, ios::end);
		Offset = (int)File.tellp();
	}
	else
	{
		// If file does not exist then create a new file.
		File.open("received.pdf", ios::out|ios::binary);
		Offset = 0;
	}
	ClientObj.Send((void*)&Offset, sizeof(int));

	int filesize;
	ClientObj.Receive((void*)&filesize, sizeof(int));
	cout << "File size: " << filesize << "B (" << (float)filesize/1024 << "KB)." << endl;
	if (Offset != 0)
		cout << "Resuming download from " << Offset << "B" << endl;

	char c;
	for (int i=0; i<(filesize-Offset); i++)
	{
		ClientObj.Receive((void*)&c, sizeof(char));
		File.write((char*)&c, sizeof(char));
	}
	File.close();

	ClientObj.CloseClientSocket();

	return 0;
}
