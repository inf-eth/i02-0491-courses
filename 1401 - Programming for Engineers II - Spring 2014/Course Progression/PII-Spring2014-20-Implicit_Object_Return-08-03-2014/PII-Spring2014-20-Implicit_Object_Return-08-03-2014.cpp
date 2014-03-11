\begin{lstlisting}[caption={Implicitly Returning Objects}]
#include <iostream>
using namespace std;
class Complex
{
	private:
	float real;
	float img;
	public:
	Complex(): real(0.f), img(0.f) {}
	Complex(float a, float b): real(a), img(b) {}
	Complex operator+ (Complex& rhs)
	{
		return Complex(real+rhs.real, img+rhs.img); // Implicit object return.
	}
	// Prefix.
	Complex operator++ ()
	{
		return Complex(++real, ++img); // Implicit object return.
	}
	// Postfix.
	Complex operator++ (int dummy)
	{
		return Complex(real++, img++); // Implicit object return.
	}
};
int main()
{
	Complex A(0.f,0.f);
	A++;
	++A;
	Complex C = A + Complex(2.4f, 22.4f); // Notice implicit rhs operand.
	
	return 0;
}
\end{lstlisting}
