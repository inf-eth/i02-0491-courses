#include "complex.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main (int argc, char **argv)
{
	complex complexobj1;
	complexobj1.setreal(4.4);
	complexobj1.setimg(-8.11);
	complex complexobj2(3.2, -0.4);

	cout << "obj1: ";
	complexobj1.display();

	cout << "obj2: ";
	complexobj2.display();

	return 0;
}
