#include <Client.h>
#include <cstdlib>			// exit(), atoi()
#include <cstring>			// strlen()
#include <iostream>
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
	int choice = -1;
	char ReceiveBuffer[512];

	while (choice != 6)
	{
		ClientObj.Receive((void*)ReceiveBuffer, 512);
		cout << ReceiveBuffer << endl << ">>";
		cin >> choice;
		ClientObj.Send((void*)&choice, sizeof(int));

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

	ClientObj.CloseClientSocket();

	return 0;
}
