#include "Complex.hpp"
class Matrix
{
	private:
	int Rows;
	int Cols;
	Complex Data[20][20]; // Maximum matrix size is 20x20
	public:
	Matrix();
	Matrix(int, int);
	Matrix(const Matrix&); // TODO: Overload copy constructor (and also assignment operator)
	Matrix operator=(const Matrix&);

	void RandomInput(); // Random input;

	// Input/output. TODO: Replace with overloaded stream operators (<< and >>)
	void Input();
	void Display();

	// Math operations. TODO: Replace with operators.
	// NOTE: Operators will NOT WORK if copy constructor and assignment operator are not properly defined.
	Matrix Add(const Matrix&);
	Matrix Subtract(const Matrix&);
	Matrix Multiply(const Matrix&);

	// TODO: Overload rest of the operators.

};
