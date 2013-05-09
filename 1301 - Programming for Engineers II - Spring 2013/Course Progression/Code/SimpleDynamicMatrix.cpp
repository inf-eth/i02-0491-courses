#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class matrix
{
private:
	float *Element;	// 1D matrix of size 1xSize.
	int Size;
public:
	matrix();
	matrix(int);
	~matrix();
	void SetSize(int);
	void Input();
	void Display();
	void Add(matrix&);
};

// Default constructor.
matrix::matrix(): Element(NULL), Size(0)
{
}
// User-define constructor that takes in size.
matrix::matrix(int pSize)
{
	Element = new float[pSize];
	Size=pSize;

	// Initialising matrix.
	for (int i=0; i<Size; i++)
		Element[i] = 0.f;
}
// Destructor.
matrix::~matrix()
{
	if (Element != NULL)
		delete []Element;
}
// Resize matrix.
void matrix::SetSize(int pSize)
{
	if (Element != NULL)
		delete []Element;

	Element = new float[pSize];
	Size=pSize;
}
// Input matrix.
void matrix::Input()
{
	cout << "Enter matrix elements: ";
	for (int i=0; i<Size; i++)
		cin >> Element[i];
}
// Display matrix.
void matrix::Display()
{
	for (int i=0; i<Size; i++)
		cout << Element[i] << " ";

	cout << endl;
}
// Adds passed matrix into calling matrix.
void matrix::Add(matrix& m)
{
	for (int i=0; i<Size; i++)
		Element[i] = Element[i] + m.Element[i];
}

// Main.
int main()
{
	matrix matrix1(4);

	matrix matrix2;
	matrix2.SetSize(4);

	matrix1.Input();
	matrix2.Input();

	matrix1.Add(matrix2);

	cout << "Result is: ";
	matrix1.Display();

	// Resizing matrices.
	matrix1.SetSize(2);
	matrix2.SetSize(2);

	matrix1.Input();
	matrix2.Input();

	matrix1.Add(matrix2);
	cout << "Result is: ";
	matrix1.Display();

	return 0;
}
