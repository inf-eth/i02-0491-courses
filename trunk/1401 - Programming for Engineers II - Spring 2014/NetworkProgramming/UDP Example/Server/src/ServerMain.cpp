#include <Server.h>
#include <cstring>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
	// Create Server object.
	Server ServerObj(UDPSOCKET);

	ServerObj.CreateSocket(UDPSOCKET);
	ServerObj.InitialiseAddress(6000);
	ServerObj.Bind();

	cout << "Server recv'in from() packets..." << endl;
	ServerObj.RecvFrom();
	cout << "They say: " << ServerObj.GetBuffer() << endl;
	ServerObj.DisplayTheirInfo();

	char UDPmessage[] = "UDP echo message from server.";
	ServerObj.SendTo((void *)UDPmessage, (unsigned int)strlen (UDPmessage)); // If sending a reply packet most recent received address is used.
	//ServerObj.SendTo((void *)UDPmessage, strlen (UDPmessage), ClientAddress, ClientPort);	// Need to explicitly mention receiver address if not a reply.

	ServerObj.CloseServerSocket();

	return 0;
}
