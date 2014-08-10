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
	int choice = -1;
	char Menu[] = "1. Add record\n2. Display all records\n3. Search record\n4. Update record\n5. Download course outline\n6. Disconnect";
	while (choice != 6)
	{
		ServerObj.Send((void*)Menu, strlen(Menu)+1); // Send NULL as well.
		ServerObj.Receive((void*)&choice, sizeof(int));

		switch (choice)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		}
	}

	// Close sockets.
	ServerObj.CloseClientSocket();
	ServerObj.CloseServerSocket();

	return 0;
}
