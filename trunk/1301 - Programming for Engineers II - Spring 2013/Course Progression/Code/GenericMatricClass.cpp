#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define Rows 1
#define Columns 4

class matrix
{
private:
	float Element[Rows][Columns];	// Matrix of size RowsxColumns.

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
	cout << "Enter matrix elements row-wise: " << endl;
	for (int i=0; i<Rows; i++)
	{
		cout << "Row " << i+1 << ": ";
		for (int j=0; j<Columns; j++)
		{
			cin >> Element[i][j];
		}
	}
}
void matrix::Display()
{
	for (int i=0; i<Rows; i++)
	{
		cout << "Row " << i+1 << ": ";
		for (int j=0; j<Columns; j++)
		{
			cout << Element[i][j] << " ";
		}
		cout << endl;
	}
}
matrix matrix::Add(matrix m)
{
	matrix result;

	for (int i=0; i<Rows; i++)
	{
		for (int j=0; j<Columns; j++)
			result.Element[i][j] = Element[i][j] + m.Element[i][j];
	}

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
