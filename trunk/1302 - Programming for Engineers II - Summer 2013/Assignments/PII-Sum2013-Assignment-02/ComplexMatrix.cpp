#include <iostream>
using namespace std;

class Complex
{
	private:
	float real;
	float img;
	public:
	Complex();
	Complex(float, float);
	// Arithmetica operators.
	Complex operator+ (const Complex&); // Addition operator.
	Complex operator- (const Complex&); // Subtraction operator.
	Complex operator* (const Complex&); // Multiplication operator.
	Complex operator/ (const Complex&); // Division operator.
	// Comparison operators.
	bool operator== (const Complex&); // Comparison (is equal to?)

	Complex operator++ (); // Pre-increment.
	Complex operator++ (int); // Post-increment.

	void Input();
	void Display();
};

// Default constructor.
Complex::Complex(): real(0.f), img(0.f)
{
}
// User-defined constructor.
Complex::Complex(float preal, float pimg): real(preal), img(pimg)
{
}
// Addition operator.
Complex Complex::operator+ (const Complex& rhs)
{
	Complex result;
	result.real = real + rhs.real;
	result.img = img + rhs.img;
	return result;
}
// Subtraction operator.
Complex Complex::operator- (const Complex& rhs)
{
	// TODO: Write your code here.
	Complex result;
	return result;
}
// Multiplication operator.
Complex Complex::operator* (const Complex& rhs)
{
	// TODO: Write your code here.
	Complex result;
	return result;
}
// Division operator.
Complex Complex::operator/ (const Complex& rhs)
{
	Complex result;
	float a, b, c, d;
	a = real;
	b = img;
	c = rhs.real;
	d = rhs.img;

	float den = c*c + d*d; // denominator.
	result.real = (a*c+b*d)/den;
	result.img = (b*c-a*d)/den;

	return result;
}
// Comparison operator, is equal to?
bool Complex::operator== (const Complex& rhs)
{
	// TODO: Write your code here.
	bool result;
	return result;
}
// Pre-increment.
Complex Complex::operator++ ()
{
	// TODO: Write your code here.
	Complex result;
	return result;
}
// Post-increment.
Complex Complex::operator++ (int dummy)
{
	// TODO: Write your code here.
	Complex result;
	return result;
}
// Input function.
void Complex::Input()
{
	cout << "Enter real: ";
	cin >> real;
	cout << "Enter imaginary: ";
	cin >> img;
}
// Display function.
void Complex::Display()
{
	if (img < 0.f)
		cout << real << "-j" << -1.f*img;
	else
		cout << real << "+j" << img;
}

class Matrix
{
	private:
	int Size;
	Complex* Data;
	public:
	// Default constructor.
	Matrix(): Size(-1), Data(NULL)
	{
	}
	// User-defined constructor.
	Matrix(int pSize)
	{
		Size = pSize;
		Data = new Complex[Size];
	}
	// Arithmetic operator.
	Matrix operator+ (const Matrix&);
	// Resize function.
	void Resize(int);

	// Input.
	void Input();
	// Display.
	void Display();

};
void Matrix::Resize(int pSize)
{
	// TODO: Write your code here.
}
void Matrix::Input()
{
	for (int i=0; i<Size; i++)
	{
		cout << "Enter matrix element " << i << endl;
		Data[i].Input();
	}
}
void Matrix::Display()
{
	cout << "[";
	for (int i=0; i<Size; i++)
	{
		Data[i].Display();
		cout << " ";
	}
	cout << "]" << endl;
}
Matrix Matrix::operator+ (const Matrix& rhs)
{
	Matrix Result(Size);
	if (Size != rhs.Size)
	{
		cout << "Matrices are not conformable for addition." << endl;
		return Result;
	}
	else
	{
		for (int i=0; i<Size; i++)
		{
			Result.Data[i] = Data[i] + rhs.Data[i];
		}
		return Result;
	}
}
int main()
{
	Complex x(1.1f, -2.7f);
	Complex y(2.1f, 3.3f);
	Complex z;

	z = x+y;
	cout << "x+y = ";
	z.Display();
	cout << endl;

	z = x/y;
	cout << "x/y = ";
	z.Display();
	cout << endl;

	z = y/x;
	cout << "y/x = ";
	z.Display();
	cout << endl;

	// Matrix operations.
	Matrix m1(3);
	Matrix m2(3);
	Matrix m3(3);

	cout << "Enter matrices: " << endl;
	m1.Input();
	m2.Input();

	m3 = m1 + m2;
	cout << "Result of addition is: ";
	m3.Display();

	return 0;
}
