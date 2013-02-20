\begin{lstlisting}[caption={Copy Constructor}]
// Notice, complex class doesn't define any constructors.
// 1. Default constructor will be provided by compiler.
// Complex(){}
// 2. Also, copy constructor will be provided by compiler.
// Prototypes for copy constructor.
// Complex(Complex &);
// Complex(const Complex &);

class Complex
{
	private:
	float real;
	float img;
};

int main()
{
	Complex x;
	Complex y(x);
	
	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Calling Assignment Operator}]
class Complex
{
	private:
	float real;
	float img;
};

int main()
{
	Complex x, y;
	Complex z(x);  // Copy constructor called.
	Complex y = x; // Assignment operator called. y was already created using default constructor.
	
	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Defining Assignment Operator}]
class Complex
{
	private:
	float real;
	float img;
	public:
	Complex& operator=(const Complex& rhs)
	{
		real = rhs.real;
		img = rhs.img;
		return (*this);
	}	
};

int main()
{
	Complex x, y;
	Complex z(x);  // Copy constructor called.
	Complex y = x; // Assignment operator called.
	
	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={User and Compiler Code}]
// User code for class.
class Complex
{
	private:
	float real;
	float img;
};

// Compiler code.
class Complex
{
	private:
	float real;
	float img;
	public:
	// Default constructor.
	Complex()
	{
	}
	// Copy constructor. Notice, member initialiser list.
	Complex(Complex& other): real(other.real), img(other.img)
	{
	}
	// Assignment operator.
	Complex& operator=(const Complex& rhs)
	{
		real = rhs.real;
		img = rhs.img;
		return (*this);  // 'this' is the pointer to calling object.
	}
};
\end{lstlisting}

\begin{lstlisting}[caption={Overloading Arithmetic Operators}]
class Complex
{
	private:
	float real;
	float img;
	public:
	Complex();
	Complex(float, float);
	Complex operator+ (const Complex&); // Addition operator.
	Complex operator/ (const Complex&); // Division operator.
	void Display();
};

// Default constructor.
Complex::Complex(): real(0.f), img(0.f)
{
}
// User-defined constructor.
Complex::Complex(float preal, float pimg): real(preal), img(pimg)
{
}
// Addition operator.
Complex Complex::operator+ (const Complex& rhs)
{
	Complex result;
	result.real = real + rhs.real;
	result.img = img + rhs.img;
	return result;
}
// Division operator.
Complex Complex::operator/ (const Complex& rhs)
{
	Complex result;
	float a, b, c, d;
	a = real;
	b = img;
	c = rhs.real;
	d = rhs.img;

	float den = c*c + d*d; // denominator.
	result.real = (a*c+b*d)/den;
	result.img = (b*c-a*d)/den;

	return result;
}
// Display function.
Complex Complex::Display()
{
	if (img < 0.f)
		cout << real << " - j" << -1.f*img << endl;
	else
		cout << real << " + j" << img << endl;
}

int main()
{
	Complex x(1.1f, -2.7f);
	Complex y(2.1f, 3.3f);
	Complex z;

	z = x+y;
	cout << "x+y = " << z << endl;

	z = x/y;
	cout << "x/y = " << z << endl;

	z = y/x;
	cout << "y/x = " << z << endl;

	return 0;
}
\end{lstlisting}

