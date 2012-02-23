#include <Server.h>
#include <cstring>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int main (int argc, char *argv[])
{
	CServer obj;
	obj.CreateSocket ();
	obj.SetSocketOptions ();
	obj.InitializeAddress (5000);
	obj.Bind ();
	obj.Listen ();
	obj.DisplayServerInfo ();
	obj.Accept ();
	obj.DisplayClientInfo ();
	obj.Receive ();
	cout << "Client says: " << obj.GetBuffer() << endl;
	char message[] = "Hello from server.";
	obj.Send (message, strlen (message));
	obj.CloseClientSocket ();
	obj.CloseServerSocket ();
	return 0;
}