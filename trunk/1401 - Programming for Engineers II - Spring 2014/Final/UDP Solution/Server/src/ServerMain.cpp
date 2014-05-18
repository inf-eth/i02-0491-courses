#include <Server.h>
#include <cstring>
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
	// Create Server object.
	Server ServerObj(UDPSOCKET, 5601);

	ServerObj.CreateSocket(UDPSOCKET);
	ServerObj.InitialiseAddress(5601);
	ServerObj.Bind();

	Complex C1, C2, Result;
	ServerObj.RecvFrom((void*)&C1, sizeof(C1));
	ServerObj.RecvFrom((void*)&C2, sizeof(C2));
	Result.real = C1.real + C2.real;
	Result.img = C1.img + C2.img;
	ServerObj.SendTo((void*)&Result, sizeof(Result));
	ServerObj.CloseServerSocket();

	return 0;
}
