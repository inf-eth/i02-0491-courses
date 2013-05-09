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
\begin{lstlisting}[caption={\texttt{mutable} variables}]
#include <iostream>
using namespace std;

class A
{
	private:
	mutable int x; // Declaration
	public:
	void Setx(int t) const { x = t; }
	int Getx() const { return x; }
};

int main()
{
	A obj;	
	A.Setx(3);
	cout << "x = " << A.Getx() << endl;

	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={\texttt{const} object with \texttt{mutable} data members}]
#include <iostream>
using namespace std;

class A
{
	private:
	mutable int x; // Declaration
	int y;
	public:
	void Setx(int t) const { x = t; }
	void Sety(int t) { y = t; }
	int Getx() const { return x; }
	int Gety() const { return y; }
};

int main()
{
	const A obj;	
	A.Setx(3); // Changing mutable data. This is OK.
	cout << "x = " << A.Getx() << endl;

	A.Sety(5); // This will not work, object is const.
	
	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={\texttt{explicit} constructor with distance class}]
#include <iostream>
using namespace std;

class distance
{
	private:
	float m;
	public:
	distance(): m(0)
	{
	}
	explicit distance(float km)
	{
		m = 1000 * km;
	}
	void display()
	{
		cout << "Distance = " << m << " meters." << endl;
	}
};

void showdist(distance d)
{
	d.display();
}

int main()
{
	distance d1(2.4);
	showdist(d1);
	showdist(3.4); // This won't work with explicit constructor.

	return 0;
}
\end{lstlisting}
