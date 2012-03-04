#include "complex.h"
#include <iostream>
using std::cout;
using std::endl;

complex::complex(): real(0.f), img(0.f)
{
}

complex::complex(float preal, float pimg): real(preal), img(pimg)
{
}

void complex::setreal (float preal)
{
	real = preal;
}
void complex::setimg (float pimg)
{
	img = pimg;
}

float complex::getreal ()
{
	return real;
}

float complex::getimg ()
{
	return img;
}

void complex::display ()
{
	cout << "Real = " << real << ", Img = " << img << endl;
}

// Operators.
complex complex::operator + (complex &B)
{
	complex C;
	C.real = real + B.real;
	C.img = img + B.img;
	return C;
}

complex complex::operator - (complex &B)
{
	complex C;
	C.real = real - B.real;
	C.img = img - B.img;
	return C;
}

// WARNING: Multiplication and division are not properly implemented.
complex complex::operator * (complex &B)
{
	complex C;
	C.real = real * B.real;
	C.img = img * B.img;
	return C;
}

complex complex::operator / (complex &B)
{
	complex C;
	C.real = real / B.real;
	C.img = img / B.img;
	return C;
}
