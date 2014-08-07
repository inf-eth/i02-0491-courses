#include <Server.h>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	// Create Server object.
	Server ServerObj;

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

	// Send and receive.
	fstream File;
	File.open("abc.pdf", ios::in|ios::binary);
	File.seekg(0, ios::end);
	int filesize = (int)File.tellg();
	cout << filesize << endl;
	ServerObj.Send((void*)&filesize, sizeof(int));

	File.seekg(0, ios::beg);
	char c;
	for (int i=0; i<filesize; i++)
	{
		File.read((char*)&c, sizeof(char));
		ServerObj.Send((void*)&c, sizeof(char));
	}
	File.close();

	// Close sockets.
	ServerObj.CloseClientSocket();
	ServerObj.CloseServerSocket();

	return 0;
}
