\begin{lstlisting}[caption={\texttt{friend} function to display Complex number}]
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
	friend void Display(Complex&); // Friend function specified.
};

// Display function definition. This is an ordinary function.
void Display(Complex& c)
{
	cout << c.real << "+j" << c.img << endl;
}

int main()
{
	Complex A(2.f,3.3f);
	Display(A);

	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={Overloading Stream Operators for Complex class}]
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
	friend ostream& operator <<(ostream&, Complex&);
	friend istream& operator >>(istream&, Complex&);
};

ostream& operator <<(ostream& out, Complex& c)
{
	out << c.real << "+j" << c.img;
	return out;
}
istream& operator >>(istream& in, Complex& c)
{
	in >> c.real >> c.img;
	return in;
}

int main()
{
	Complex A;
	cout << "Enter a complex number: ";
	cin >> A;
	cout << "You entered: " << A << endl;

	return 0;
}
\end{lstlisting}
