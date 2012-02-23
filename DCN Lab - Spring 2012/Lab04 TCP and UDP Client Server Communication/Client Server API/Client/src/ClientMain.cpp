#include <iostream>
#include <Client.h>
using std::cout;
using std::endl;

int main (int argc, char **argv)
{
	CClient TestClient (33, 44);
	CClient TestClientDef;
	cout << "This is client, argc = " << argc << endl;
	for (int i=0; i<argc; i++)
	{
		cout << "argv[i] = " << argv[i] << endl;
	}
	return 0;
}