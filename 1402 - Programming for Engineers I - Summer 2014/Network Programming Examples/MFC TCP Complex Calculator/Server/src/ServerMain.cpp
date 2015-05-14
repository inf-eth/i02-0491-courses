#include <Server.h>
#include <cstring>
#include <iostream>
using namespace std;

struct Complex
{
	float real;
	float img;
};

int main()
{
	// Create Server object.
	Server ServerObj;

	// Create Server socket and set socket options.
	ServerObj.CreateSocket(TCPSOCKET);		// No argument means TCPSOCKET
	ServerObj.SetSocketOptions();

	// Initialise Server address struct and bind it with Server's socket.
	ServerObj.InitialiseAddress(6000);
	ServerObj.Bind();

	// Listen for incoming connections.
	ServerObj.Listen();
	ServerObj.DisplayServerInfo();

	// Accept any incoming connections.
	ServerObj.Accept();
	ServerObj.DisplayClientInfo();

	// Send and receive.
	int choice = -1;
	Complex A, B, C;
	char Menu[] = "1. Add\n2. Subtract\n3. Multiply\n4. Divide\n5. Disconnect";

	while (choice != 5)
	{
		ServerObj.Receive((void*)&choice, sizeof(int));

		switch (choice)
		{
			case 1:
			{
				ServerObj.Receive((void*)&A, sizeof(Complex));
				ServerObj.Receive((void*)&B, sizeof(Complex));
				C.real = A.real + B.real;
				C.img = A.img + B.img;
				ServerObj.Send((void*)&C, sizeof(Complex));
				break;
			}
			case 2:
			{
				ServerObj.Receive((void*)&A, sizeof(Complex));
				ServerObj.Receive((void*)&B, sizeof(Complex));
				C.real = A.real - B.real;
				C.img = A.img - B.img;
				ServerObj.Send((void*)&C, sizeof(Complex));
				break;
			}
			case 3:
			{
				ServerObj.Receive((void*)&A, sizeof(Complex));
				ServerObj.Receive((void*)&B, sizeof(Complex));
				float a = A.real;
				float b = A.img;
				float c = B.real;
				float d = B.img;
				C.real = a*c-b*d;
				C.img = a*d+b*c;
				ServerObj.Send((void*)&C, sizeof(Complex));
				break;
			}
			case 4:
			{
				ServerObj.Receive((void*)&A, sizeof(Complex));
				ServerObj.Receive((void*)&B, sizeof(Complex));
				float a = A.real;
				float b = A.img;
				float c = B.real;
				float d = B.img;
				float den =c*c+d*d;
				C.real = (a*c+b*d)/den;
				C.img = (b*c-a*d)/den;
				ServerObj.Send((void*)&C, sizeof(Complex));
				break;
			}
			case 5:
				break;
		}
	}

	// Close sockets.
	ServerObj.CloseClientSocket();
	ServerObj.CloseServerSocket();

	return 0;
}
