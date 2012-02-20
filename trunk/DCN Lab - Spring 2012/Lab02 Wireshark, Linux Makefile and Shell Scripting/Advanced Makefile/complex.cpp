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
