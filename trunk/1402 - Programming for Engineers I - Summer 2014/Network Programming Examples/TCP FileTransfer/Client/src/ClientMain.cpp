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

	// Send and receive.
	fstream File;
	File.open("received.pdf", ios::out|ios::binary);
	int filesize;
	ClientObj.Receive((void*)&filesize, sizeof(int));
	cout << filesize << endl;
	char c;
	for (int i=0; i<filesize; i++)
	{
		ClientObj.Receive((void*)&c, sizeof(char));
		File.write((char*)&c, sizeof(char));
	}
	File.close();

	ClientObj.CloseClientSocket();

	return 0;
}
