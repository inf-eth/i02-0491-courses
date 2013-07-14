\begin{lstlisting}[caption={operator+ prototype as member function and as \texttt{friend}}]
Complex Complex::operator+ (Complex&); // member function
Complex operator+ (Complex&, Complex&); // global friend function
\end{lstlisting}
\begin{lstlisting}[caption={operator+ implemented as \texttt{friend}}]
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
	friend Complex operator+(Complex&, Complex&);
};

// operator+ function in this case is external to the class.
// It cannot access private members of the class unless declared a `friend' in the class.
Complex operator+(Complex& lhs, Complex& rhs)
{
	return Complex(lhs.real+rhs.real, lhs.img+rhs.img);
}

int main()
{
	Complex A(2.f,3.3f);
	Complex B(2.32f,-1.3f);
	Complex C;
	C = A + B;

	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={Complex.hpp}]
class Complex
{
	private:
	float real, img;
	public:

	void Input();
	void Display();
};
\end{lstlisting}
\end{minipage}
\hspace*{1cm}
\begin{minipage}{7.5cm}
\begin{lstlisting}[caption={Complex.cpp}]
#include <iostream>
#include <Complex.hpp>
using namespace std;

void Complex::Input()
{
	cin >> real >> img;
}
void Complex::Display()
{
	cout << real << img;
}
\end{lstlisting}
\end{minipage}
\begin{lstlisting}[caption={main.cpp}]
#include <Complex.hpp>

int main()
{
	Complex A;
	A.Input();
	A.Display();

	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={private and protected members}]
class A
{
	private:
	int x;
	protected:
	int y;
	public:
	int z;
};
class B: public A
{
	public:
	void Test()
	{
		x = 3; // ERROR! cannot access private members of class A.
		y = 3; // OK
		z = 3; // OK
	}
};
int main()
{
	B Bobj;
	Bobj.x = 0; // ERROR!
	Bobj.y = 0; // ERROR!
	Bobj.z = 0; // OK
	
	return 0;
}
\end{lstlisting}
