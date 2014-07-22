#include <Server.h>
#include <cstring>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

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
	ServerObj.Receive();
	cout << "No. of bytes received: " << ServerObj.GetNumOfBytesReceived() << endl;
	cout << "Client says: " << ServerObj.GetBuffer() << endl;

	char message[] = "Hello from server.";
	ServerObj.Send((void*)message, (unsigned int)strlen(message));

	// Close sockets.
	ServerObj.CloseClientSocket();
	ServerObj.CloseServerSocket();

	return 0;
}
