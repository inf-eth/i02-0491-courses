\begin{lstlisting}[caption={Variable Casting}]
int main()
{
	int x = 3;
	float y = 4.3f;

	// Implicit conversion.
	x = y;
	y = x;

	// Explicit conversion.
	x = static_cast<int>(y);
	x = (int)y;
	y = (float)x;
	
	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={Conversion Between Objects}]
int intvar;
float floatvar
Complex complexobj;

intvar = floatvar;
floatvar = intvar;

complexobj = intvar; // complexobj.operator=(intvar)
complexobj = floatvar; // complexobj.operator=(floatvar)

intvar = complexobj; // overload int?
floatvar = complexobj; // overload float?

objA = objB; // objA.operator=(objB)
objB = objA; // objB.operator=(objA)
\end{lstlisting}
\begin{lstlisting}[caption={Object from Float}]
class Complex
{
	private:
	float real;
	float img;
	public:
	Complex(): real(0), img(0) {}
	Complex(float x, float y): real(x), img(y) {}
	void operator=(float pfloatvar)
	{
		real = pfloatvar;
		img = 0;
	}
};
int main()
{
	float resistance = 3.3;
	Complex impedance;
	impedance = resistance; // Complex from int conversion: impedance.operator=(resistance)
	// impedance is now 3.3+j0
	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={Float from Object}]
class Complex
{
	private:
	float real;
	float img;
	public:
	Complex(): real(0), img(0) {}
	Complex(float x, float y): real(x), img(y) {}
	operator float()
	{
		return real;
	}
};
int main()
{
	float resistance;
	Complex impedance(3.3,4.7);
	resistance = impedance; // float from complex conversion: impedance.operator float()
	// resistance now contains 3.3.

	return 0;
}
\end{lstlisting}
\begin{minipage}{7.5cm}
\begin{lstlisting}[caption={class A}]
class A
{
	private:
	float x;
	public:
	void operator=(B);
	operator B();
};
\end{lstlisting}
\end{minipage}
\hspace*{1cm}
\begin{minipage}{7.5cm}
\begin{lstlisting}[caption={class B}]
class B
{
	private:
	int y;
	public:
	// Cannot change code.
};
\end{lstlisting}
\end{minipage}
\begin{lstlisting}[caption={Object Conversion}]
int main()
{
	A Aobj;
	B Bobj;
	
	Aobj = Bobj; // conversion from B to A. Aobj.operator=(B) called.
	Bobj = Aobj; // conversion from A to B. Aobj.operator B() called.

	return 0;
}
\end{lstlisting}
