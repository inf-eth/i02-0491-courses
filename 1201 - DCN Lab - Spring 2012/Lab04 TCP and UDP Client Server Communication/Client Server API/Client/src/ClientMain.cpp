#include <Client.h>
#include <cstdlib>			// exit(), atoi()
#include <cstring>			// strlen()
#include <iostream>
using std::cout;
using std::endl;

int main (int argc, char **argv)
{
	// Standard error checking. Must provide server name/IP and port to connect.
	if ( argc < 3 )
	{
		cout << "ERROR000: Incorrect input arguments." << endl;
		cout << "Usage: './Client [server name or IP] [server port]'" << endl;
		cout << "OR" << endl;
		cout << "if using Makefile: 'make runC ARG=\"[server name or IP] [server port]\"'" << endl;
		exit (-1);
	}

	// Create Client object.
	CClient ClientObj (TCPSOCKET, DEFAULTCLIENTPORT);			// Can create an object without arguments. Defaults are TCPSOCKET and DEFAULTPORT (6001).

	// Create Client Socket.
	ClientObj.CreateSocket (TCPSOCKET);
	ClientObj.SetSocketOptions ();

	// Initialize and bind Client address.
	ClientObj.InitializeAddress (DEFAULTCLIENTPORT);	// Without any argument default port will be chosen.
	ClientObj.Bind ();

	// Connect to Server. Server name/IP and port are provided as arguments.
	ClientObj.Connect (argv[1], atoi (argv[2]));

	// Send and receive.
	char ClientMessage[] = "Hello from client.";
	ClientObj.Send ((void *)ClientMessage, strlen (ClientMessage));

	ClientObj.Receive ();
	cout << "Server says: " << ClientObj.GetBuffer () << endl;

	ClientObj.CloseClientSocket ();

	// ********************* UDP Communication ***************************
	cout << "TCP connection closed, now doing UDP communication." << endl;
	ClientObj.CreateSocket (UDPSOCKET);
	ClientObj.InitializeAddress (6001);
	ClientObj.Bind ();

	char UDPmessage[] = "UDP message from client.";
	ClientObj.SendTo ((void *)UDPmessage, strlen (UDPmessage), "localhost", 6000);

	cout << "Client recv'in from() packets..." << endl;
	ClientObj.RecvFrom ();
	cout << "They say: " << ClientObj.GetBuffer () << endl;
	ClientObj.DisplayTheirInfo ();

	ClientObj.CloseClientSocket ();
	// *******************************************************************

	return 0;
}