#include <Server.h>
#include <cstring>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main (int argc, char *argv[])
{
	// Create Server object.
	CServer ServerObj (TCPSOCKET, DEFAULTSERVERPORT);			// Without any arguments Server will set defaults, TCPSOCKET as type and 6000 as port.

	// Create Server socket and set socket options.
	ServerObj.CreateSocket (TCPSOCKET);		// No argument means TCPSOCKET
	ServerObj.SetSocketOptions ();

	// Initial Server address struct and bind it with Server's socket.
	ServerObj.InitializeAddress (6000);		// No argument here will take default port.
	ServerObj.Bind ();

	// Listen for incoming connections.
	ServerObj.Listen ();
	ServerObj.DisplayServerInfo ();

	// Accept any incoming connections.
	ServerObj.Accept ();
	ServerObj.DisplayClientInfo ();

	// Send and receive.
	ServerObj.Receive ();
	cout << "No. of bytes received: " << ServerObj.GetNumOfBytesReceived () << endl;
	cout << "Client says: " << ServerObj.GetBuffer() << endl;

	char message[] = "Hello from server.";
	ServerObj.Send ((void *)message, strlen (message));

	// Close sockets.
	ServerObj.CloseClientSocket ();
	ServerObj.CloseServerSocket ();

	// ********************* UDP Communication ***************************
	cout << "TCP connection closed, now doing UDP communication." << endl;
	ServerObj.CreateSocket (UDPSOCKET);
	ServerObj.InitializeAddress (6000);
	ServerObj.Bind ();

	cout << "Server recv'in from() packets..." << endl;
	ServerObj.RecvFrom ();
	cout << "They say: " << ServerObj.GetBuffer () << endl;
	ServerObj.DisplayTheirInfo ();

	char UDPmessage[] = "UDP echo message from server.";
	ServerObj.SendTo ((void *)UDPmessage, strlen (UDPmessage)); // If sending a reply packet most recent received address is used.
	//ServerObj.SendTo ((void *)UDPmessage, strlen (UDPmessage), "localhost", 6001);	// Need to explicitly mention receiver address if not a reply.

	ServerObj.CloseServerSocket ();
	// *******************************************************************

	return 0;
}