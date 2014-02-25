#include "Matrix.hpp"
#include <iostream>
using namespace std;

Matrix::Matrix(): Rows(3), Cols(3) // Default matrix size is 3x3.
{

}

Matrix::Matrix(int pRows, int pCols): Rows(pRows), Cols(pCols)
{
	// Reverting to default size if invalid row/col size is given.
	if (Rows < 1 || Rows > 20)
		Rows = 3;
	if (Cols < 1 || Cols > 20)
		Rows = 3;
}

Matrix::Matrix(const Matrix& m)
{
	// TODO: Write copy constructor code.

}

Matrix Matrix::operator=(const Matrix& m)
{
	// TODO: Overload assignment operator.
	return (*this);
}

void Matrix::RandomInput()
{
	for (int i=0; i<Rows; i++)
		for (int j=0; j<Cols; j++)
			Data[i][j].RandomInput();
}
// TODO: Replace with operator>>
void Matrix::Input()
{
	for (int i=0; i<Rows; i++)
	{
		cout << "Row " << i+1 << ": ";
		for (int j=0; j<Cols; j++)
			Data[i][j].Input();
	}
}

// TODO: Replace with operator<<
void Matrix::Display()
{
	for (int i=0; i<Rows; i++)
	{
		cout << "Row " << i+1 << ": ";
		for (int j=0; j<Cols; j++)
		{
			Data[i][j].Display();
			cout << "\t";
		}
		cout << endl;
	}
}

// TODO: Replace with operator+
Matrix Matrix::Add(const Matrix& m)
{
	Matrix result(Rows, Cols);
	if (Rows != m.Rows || Cols != m.Cols)
	{
		cout << "Error: Matrices not comforbale for addition." << endl;
		return result;
	}
	else
	{
		for (int i=0; i<Rows; i++)
			for (int j=0; j<Cols; j++)
				result.Data[i][j] = Data[i][j].Add(m.Data[i][j]);
		return result;
	}
}

// TODO: Replace with operator-
Matrix Matrix::Subtract(const Matrix& m)
{
	Matrix result(Rows, Cols);
	if (Rows != m.Rows || Cols != m.Cols)
	{
		cout << "Error: Matrices not comforbale for subtraction." << endl;
		return result;
	}
	else
	{
		for (int i=0; i<Rows; i++)
			for (int j=0; j<Cols; j++)
				result.Data[i][j] = Data[i][j].Subtract(m.Data[i][j]);
		return result;
	}
}

// TODO: Replace with operator*
Matrix Matrix::Multiply(const Matrix& m)
{
	Matrix result(Rows, m.Cols);
	if (Cols != m.Rows)
	{
		cout << "Error: Matrices not comforbale for multiplication." << endl;
		return result;
	}
	else
	{
		for (int i=0; i<Rows; i++)
			for (int j=0; j<m.Cols; j++)
				for (int k=0; k<Cols; k++)
				{
					// result.Data[i][j] = result.Data[i][j] + Data[i][k] * m.Data[k][j];
					result.Data[i][j] = result.Data[i][j].Add(Data[i][k].Multiply(m.Data[k][j]));
				}
		return result;
	}
}
