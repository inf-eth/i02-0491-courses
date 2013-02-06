#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class complex
{
private:
	float real;
	float img;

public:
	void Input();
	void Display();
	complex Add(complex);
	complex DivideBy(complex);
};

// Class functions can be defined inside or outside the class.
// Here, functions are defined outside the class.
// Notice the `::' operator.
void complex::Input()
{
	cout << "Enter complex number: ";
	cin >> real >> img;
}
void complex::Display()
{
	if (img < 0.f)
		cout << real << " - j" << -1.f*img << endl;
	else
		cout << real << " + j" << img << endl;
}
// First complex number (or operand) is the calling object.
// Second operand is passed as argument.
// Resultant complex number is calculated and returned.
// Result = Complex1 + Complex2.
complex complex::Add(complex c)
{
	complex result;
	result.real = real + c.real;
	result.img = img + c.img;

	return result;
}
// (a+jb)/(c+jd) = (ac+bd+j(bc-ad))/(c^2+d^2)
// a = real;
// b = img;
// c = c1.real;
// d = c1.img;
// result.real = (ac+bd)/(c^2+d^2)
// result.img = (bd-ad)/(c^2+d^2)
complex complex::DivideBy(complex c1)
{
	complex result;
	float a = real;
	float b = img;
	float c = c1.real;
	float d = c1.img;
	float den = c*c + d*d; // denominator.

	result.real = (a*c+b*d)/den;
	result.img = (b*c-a*d)/den;

	return result;
}

int main()
{
	// First complex number.
	complex complex1;	// complex1 is an object of complex class.
	// Second complex number.
	complex complex2;
	// Resultant complex number.
	complex complex3;

	// First complex input.
	complex1.Input();
	// Second complex input.
	complex2.Input();

	// Addition.
	complex3 = complex1.Add(complex2);

	// Addition result.
	cout << "Result of addition is: ";
	complex3.Display();

	// Division.
	complex3 = complex1.DivideBy(complex2);
	cout << "C1 / C2 = ";
	complex3.Display();

	complex3 = complex2.DivideBy(complex1);
	cout << "C2 / C1 = ";
	complex3.Display();

	return 0;
}
