#include <iostream>
using std::cout;
using std::endl;

int main (int argc, char **argv)
{
	cout << "No of arguments = " << argc << endl;
	for (int i=0; i<argc; i++)
	{
		cout << "Argument " << argc << " = " << argv[0] << endl;
	}
	return 0;
}
