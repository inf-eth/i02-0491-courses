#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class matrix
{
private:
	float Element[4];	// 1D matrix of size 1x4.

public:
	void Input();
	void Display();
	matrix Add(matrix);
};

// Class functions can be defined inside or outside the class.
// Here, functions are defined outside the class.
// Notice the `::' operator.
void matrix::Input()
{
	cout << "Enter matrix elements: ";
	cin >> Element[0] >> Element[1] >> Element[2] >> Element[3];
}
void matrix::Display()
{
	cout << Element[0] << " " << Element[1] << " " << Element[2] << " " << Element[3] << endl;
}
matrix matrix::Add(matrix m)
{
	matrix result;
	result.Element[0] = Element[0] + m.Element[0];
	result.Element[1] = Element[1] + m.Element[1];
	result.Element[2] = Element[2] + m.Element[2];
	result.Element[3] = Element[3] + m.Element[3];

	return result;
}

int main()
{
	// First matrix.
	matrix matrix1;
	// Second matrix.
	matrix matrix2;
	// Resultant matrix.
	matrix matrix3;

	// First matrix input.
	matrix1.Input();
	// Second matrix input.
	matrix2.Input();

	// Addition.
	matrix3 = matrix1.Add(matrix2);

	// Result.
	cout << "Result is: ";
	matrix3.Display();

	return 0;
}
