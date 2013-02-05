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
complex complex::Add(complex c)
{
	complex result;
	result.real = real + c.real;
	result.img = img + c.img;

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

	// Result.
	cout << "Result is: ";
	complex3.Display();

	return 0;
}
