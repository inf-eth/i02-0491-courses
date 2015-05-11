#include <Client.h>
#include <cstdlib>			// exit(), atoi()
#include <cstring>			// strlen()
#include <iostream>
using namespace std;

struct Complex
{
	float real;
	float img;
};
void Input(Complex&);
void Display(Complex&);

int main()
{
	// Create Client object.
	Client ClientObj;

	// Create Client Socket.
	ClientObj.CreateSocket(TCPSOCKET);
	ClientObj.SetSocketOptions();

	// Initialise and bind Client address.
	ClientObj.InitialiseAddress(6001);
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
	Complex A, B, C;
	int choice = -1;
	char ReceiveBuffer[512];

	while (choice != 5)
	{
		ClientObj.Receive((void*)ReceiveBuffer, 512);
		cout << ReceiveBuffer << endl << ">> ";
		cin >> choice;
		ClientObj.Send((void*)&choice, sizeof(int));

		switch (choice)
		{
			case 1:
			{
				cout << "Enter two complex numbers:" << endl;
				Input(A);
				Input(B);
				ClientObj.Send((void*)&A, sizeof(Complex));
				ClientObj.Send((void*)&B, sizeof(Complex));
				ClientObj.Receive((void*)&C, sizeof(Complex));
				cout << "Result is: ";
				Display(C);
				break;
			}
			case 2:
			{
				cout << "Enter two complex numbers:" << endl;
				Input(A);
				Input(B);
				ClientObj.Send((void*)&A, sizeof(Complex));
				ClientObj.Send((void*)&B, sizeof(Complex));
				ClientObj.Receive((void*)&C, sizeof(Complex));
				cout << "Result is: ";
				Display(C);
				break;
			}
			case 3:
			{
				cout << "Enter two complex numbers:" << endl;
				Input(A);
				Input(B);
				ClientObj.Send((void*)&A, sizeof(Complex));
				ClientObj.Send((void*)&B, sizeof(Complex));
				ClientObj.Receive((void*)&C, sizeof(Complex));
				cout << "Result is: ";
				Display(C);
				break;
			}
			case 4:
			{
				cout << "Enter two complex numbers:" << endl;
				Input(A);
				Input(B);
				ClientObj.Send((void*)&A, sizeof(Complex));
				ClientObj.Send((void*)&B, sizeof(Complex));
				ClientObj.Receive((void*)&C, sizeof(Complex));
				cout << "Result is: ";
				Display(C);
				break;
			}
			case 5:
				break;
		}
	}

	ClientObj.CloseClientSocket();

	return 0;
}

void Input(Complex& C)
{
	cout << "Enter real: ";
	cin >> C.real;
	cout << "Enter img: ";
	cin >> C.img;
}

void Display(Complex& C)
{
	if (C.img < 0.f)
		cout << C.real << "-j" << -1*C.img << endl;
	else
		cout << C.real << "+j" << C.img << endl;
}
