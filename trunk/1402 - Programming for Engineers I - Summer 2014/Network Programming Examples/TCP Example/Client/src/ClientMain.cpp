#include <Client.h>
#include <cstdlib>			// exit(), atoi()
#include <cstring>			// strlen()
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

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
	char ClientMessage[] = "Hello from client.";
	ClientObj.Send((void*)ClientMessage, (unsigned int)strlen(ClientMessage));

	ClientObj.Receive();
	cout << "Server says: " << ClientObj.GetBuffer() << endl;

	ClientObj.CloseClientSocket();

	return 0;
}
