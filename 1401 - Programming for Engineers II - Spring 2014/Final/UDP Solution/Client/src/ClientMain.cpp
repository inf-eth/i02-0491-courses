#include <Client.h>
#include <iostream>
using namespace std;
class Complex
{
public:
	int real;
	int img;
};
int main()
{
	// Create Client object.
	Client ClientObj(UDPSOCKET);

	ClientObj.CreateSocket(UDPSOCKET);
	ClientObj.InitialiseAddress(6001);
	ClientObj.Bind();

	//char ServerAddress[] = "127.0.0.1"; // local test.
	char ServerAddress[] = "192.168.1.99";
	int ServerPort = 5601;

	Complex C1, C2, Result;
	C1.real = 1;
	C1.img = 2;
	C2.real = 3;
	C2.img = 4;

	ClientObj.SendTo((void*)&C1, sizeof(C1), ServerAddress, ServerPort);
	ClientObj.SendTo((void*)&C2, sizeof(C2), ServerAddress, ServerPort);
	ClientObj.RecvFrom((void*)&Result, sizeof(Result));
	cout << "Result: " << Result.real << "+j" << Result.img << endl;
	ClientObj.CloseClientSocket();

	return 0;
}
