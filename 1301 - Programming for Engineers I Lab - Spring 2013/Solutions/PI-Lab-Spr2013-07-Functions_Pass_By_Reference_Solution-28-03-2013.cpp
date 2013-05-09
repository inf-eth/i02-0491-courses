#include <iostream>
using namespace std;

void Square(int&); // Prototype.
void Square(int*); // Prototype.
void SquareArray(int*, int); // Prototype. Array pointer and array size are arguments
int main()
{
	int x1 = 5;
	int x2 = 7;

	Square(x1);
	cout << "Square by reference: " << x1 << endl;
	Square(&x2);
	cout << "Square by pointer: " << x2 << endl;

	int Data[5] = {2, 3, 7, -1, 1};
	SquareArray(Data, 5);
	for (int i=0; i<5; i++)
		cout << Data[i] << " ";
	cout << endl;

	return 0;
}
void Square(int& x)
{
	x = x*x;
}
void Square(int* xp)
{
	*xp = (*xp) * (*xp);
}
void SquareArray(int* array, int size)
{
	for (int i=0; i<size; i++)
		array[i] = array[i] * array[i];
}
