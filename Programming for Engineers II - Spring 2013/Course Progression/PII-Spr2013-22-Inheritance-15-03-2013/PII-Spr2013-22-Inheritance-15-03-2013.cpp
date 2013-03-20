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
\begin{lstlisting}[caption={Example of Inheritance}]
#include <iostream>
using namespace std;

// AC = A constructor.
// BC = B constructor.
// AD = A destructor.
// BD = B destructor.
class A
{
	private:
	int x;
	public:
	A(): x(0)
	{
		cout << "AC" << endl;
	}
	A(int px): x(px)
	{
		cout << "AC" << endl;
	}
	~A()
	{
		cout << "AD" << endl;
	}
};
// class B is derived from class A.
// B will contain both x and y
class B: public A
{
	private:
	int y;
	public:
	B(): y(0) // This constructor will implicitly call A()
	{
		cout << "BC" << endl;
	}
	B(int py): A(), y(py) // This will explicitly call A()
	{
		cout << "BC" << endl;
	}
	B(int px, int py): A(py), y(py) // This will explicitly call A(int)
	{
		cout << "BC" << endl;
	}
	~B()
	{
		cout << "BD" << endl;
	}
};
int main()
{
	// Constructor calls in creation of B object:
	// 1. Constructor of A is called implicitly and x is set to 0.
	// 2. Constructor of B is called and y is set to 0.
	B Bobj;
	
	return 0;	
}
// Destructors are called in reverse order.
// First destructor of B is called and then destructor of A.
// Output of the program is:
// AC
// BC
// BD
// AD
\end{lstlisting}
\begin{lstlisting}[caption={Over--Riding Base Class Function}]
#include <iostream>
#include <string> // For string class.
using namespace std;

class Person
{
	private:
	string Name;
	int Age;
	public:
	Person(): Name("No name"), Age(-1)
	{
	}
	Person(string pName, int pAge): Name(pName), Age(pAge)
	{
	}
	void Input()
	{
		cin >> Name >> Age;
	}
	void Display()
	{
		cout << "Name: " << Name << endl
			 << "Age:  " << Age << endl;
	}
};

class Student: public Person
{
	private:
	float CGPA;
	public:
	Student(): Person(), CGPA(-1.f)
	{
	}
	Student(string pName, int pAge, float pCGPA): Person(pName, pAge), CGPA(pCGPA)
	{
	}
	// Input/display functions over-ride the ones in base class but call them explicitly.
	void Input()
	{
		Person::Input();
		cin >> CGPA;
	}
	void Display()
	{
		Person::Display();
		cout << "CGPA: " << CGPA << endl;
	}
};

int main()
{
	// Student object using default constructors.
	Student S1;
	
	// Student object by passing values.
	Student S2("Ahsan", 19, 3.97f);
	
	S1.Input();
	S1.Display(); // Default display: Displays name, age and cgpa.
	S1.Person::Display(); // This will only display name and age.
	
	return 0;
}
\end{lstlisting}
