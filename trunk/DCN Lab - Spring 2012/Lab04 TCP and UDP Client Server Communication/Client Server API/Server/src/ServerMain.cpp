#include <Server.h>
#include <cstring>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main (int argc, char *argv[])
{
	// Create Server object.
	CServer obj (TCPSOCKET, DEFAULTSERVERPORT);			// Without any arguments Server will set defaults, TCPSOCKET as type and 6000 as port.

	// Create Server socket and set socket options.
	obj.CreateSocket (TCPSOCKET);		// No argument means TCPSOCKET
	obj.SetSocketOptions ();

	// Initial Server address struct and bind it with Server's socket.
	obj.InitializeAddress (6000);		// No argument here will take default port.
	obj.Bind ();

	// Listen for incoming connections.
	obj.Listen ();
	obj.DisplayServerInfo ();

	// Accept any incoming connections.
	obj.Accept ();
	obj.DisplayClientInfo ();

	// Send and receive.
	obj.Receive ();
	cout << "No. of bytes received: " << obj.GetNumOfBytesReceived () << endl;
	cout << "Client says: " << obj.GetBuffer() << endl;
	
	char message[] = "Hello from server.";
	obj.Send ((void *)message, strlen (message));

	// Close sockets.
	obj.CloseClientSocket ();
	obj.CloseServerSocket ();
	return 0;
}