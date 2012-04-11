#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

int main (int argc, char **argv)
{
	char Password[4];
	char Input[4];

	strcpy(Password, "123");

	strcpy(Input, argv[1]);

	if (strncmp(Password, Input, 4) == 0)
		cout << "Correct password!" << endl;
	else
		cout << "Incorrect!" << endl;

	return 0;
}