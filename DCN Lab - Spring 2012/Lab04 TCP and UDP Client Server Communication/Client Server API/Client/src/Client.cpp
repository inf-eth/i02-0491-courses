#include <Client.h>
#include <iostream>
using std::cout;
using std::endl;
CClient::CClient (int pType, int pPort): Type (pType), ClientPort (pPort)
{
	cout << "Client object created with type " << Type << " and port " << ClientPort << endl;
}