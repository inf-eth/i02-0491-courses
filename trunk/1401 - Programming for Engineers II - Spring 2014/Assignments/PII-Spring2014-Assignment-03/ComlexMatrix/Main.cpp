#include "Matrix.hpp"
#include <iostream>
using namespace std;

int main()
{
	Matrix A(1, 4);
	Matrix B(4, 2);
	Matrix C(1, 2);

	A.RandomInput();
	B.RandomInput();

	cout << "Matrix A is: " << endl;
	A.Display();

	cout << "Matrix B is: " << endl;
	B.Display();

	// This will not work without copy constructor/assignment operator.
	C = A.Multiply(B);
	C.Display();

	return 0;
}
