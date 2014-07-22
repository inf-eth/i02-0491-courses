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

	ClientObj.CreateSocket(UDPSOCKET);
	ClientObj.InitialiseAddress(6001);
	ClientObj.Bind();

	char ServerAddress[24];
	int ServerPort;
	cout << "Enter Server name or IP address: "; // Use localhost or 127.0.0.1 for local server.
	cin.getline(ServerAddress, 24);
	cout << "Server port: ";
	cin >> ServerPort;

	char UDPmessage[] = "UDP message from client.";
	ClientObj.SendTo((void *)UDPmessage, (unsigned int)strlen(UDPmessage), ServerAddress, ServerPort);

	cout << "Client recv'in from() packets..." << endl;
	ClientObj.RecvFrom();
	cout << "They say: " << ClientObj.GetBuffer() << endl;
	ClientObj.DisplayTheirInfo();

	ClientObj.CloseClientSocket();

	return 0;
}
