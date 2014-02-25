#include "Complex.hpp"
#include <iostream>
#include <cstdlib> // for rand().
using namespace std;

Complex::Complex(): real(0.f), img(0.f)
{

}

Complex::Complex(float preal, float pimg): real(preal), img(pimg)
{

}

void Complex::RandomInput()
{
	real = (float)(rand()%200-100);
	img = (float)(rand()%200-100);
}

// TODO: Replace with operator>>
void Complex::Input()
{
	cin >> real >> img;
}

// TODO: Replace with operator<<
void Complex::Display()
{
	if (img < 0.f)
		cout << real << "-j" << -1.*img;
	else
		cout << real << "+j" << img;
}

// TODO: Replace with operator+
Complex Complex::Add(const Complex& c)
{
	Complex result;
	result.real = real+c.real;
	result.img = img+c.img;

	return result;
}

// TODO: Replace with operator-
Complex Complex::Subtract(const Complex& c)
{
	Complex result;
	result.real = real-c.real;
	result.img = img-c.img;

	return result;
}

// TODO: Replace with operator*
Complex Complex::Multiply(const Complex& c)
{
	Complex result;
	result.real = real*c.real-img*c.img;
	result.img = real*c.img+img*c.real;

	return result;
}

// TODO: Replace with operator/
Complex Complex::Divide(const Complex& c1)
{
	Complex result;
	float a, b, c, d;
	a = real;
	b = img;
	c = c1.real;
	d = c1.img;

	if (c == 0.f && d == 0.f)
	{
		cout << "Division by zero detected! Complex number division operation not possible." << endl;
		return result;
	}

	result.real = (a*c+b*d)/(c*c+d*d);
	result.img = (b*c-a*d)/(c*c+d*d);

	return result;
}
