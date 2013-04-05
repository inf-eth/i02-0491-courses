\begin{lstlisting}[caption={Pointer Example},escapechar=!]
#include <iostream>
using namespace std;

int main()
{
	int** pp;
	int* p1;
	int* p2;

	int arr1[5] = {6,7,8,9,10};
	int arr2[5] = {1,2,3,4,5};

	p1 = arr1;
	p2 = arr2;
	pp = &p1;

	cout << "&p1: " << &p1 << endl
		 << "p1: " << p1 << endl
		 << "*p1: " << *p1 << endl
		 << "*(p1+0): " << *(p1+0) << endl
		 << "p1[0]: " << p1[0] << endl
		 << "p1[1]: " << p1[1] << endl
		 << "*(p1+2): " << *(p1+2) << endl;

	cout << "&pp: " << &pp << endl
		 << "pp: " << pp << endl
		 << "*pp: " << *pp << endl
		 << "**pp: " << **pp << endl
		 << "*(pp+0): " << *(pp+0) << endl
		 << "pp[0]: " << pp[0] << endl
		 << "*pp[0]: " << *pp[0] << endl
		 << "(*pp)[0]: " << (*pp)[0] << endl
		 << "*(pp[0]): " << *(pp[0]) << endl
		 << "p2: " << p2 << endl
		 << "pp[-3] = *(pp-3): " << pp[-3] << endl
		 << "*pp[-3]: " << *pp[-3] << endl
		 << "(*pp)[1]: " << (*pp)[1] << endl
		 << "*(pp[-3]): " << *(pp[-3]) << endl;

	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={\texttt{this} pointer}]
#include <iostream>
using namespace std;

class Complex
{
	private:
	float real;
	float img;
	public:
	Complex()
	{
		cout << "My object's address is: " << this << endl;
	}
	void Input()
	{
		cin >> this->real;
		cin >> this->img;
	}
	void Display()
	{
		cout << this->real << endl;
		cout << this->img << endl;
	}
};

int main()
{
	Complex c;
	c.Input();
	c.Display();

	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Returning by reference using \texttt{this} pointer},escapechar=!]
class Complex
{
	private:
	float real;
	float img;
	public:
	Test& operator= (Test & rhs)
	{
		real = rhs.real;
		img = rhs.img;
		return (*this);
	}
};
int main()
{
	Complex A, B, C;
	!\color{red}{A = B = C}!;

	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={\texttt{void*} usage}]
#include <iostream>
using namespace std;

int main()
{
	void* vp;
	vp = new int[5];
	delete[] vp;

	vp = new float;
	*((float*)vp) = 3.3f; // Notice, explicit casting from void* to float* before dereferencing.
	cout << "*vp: " << *((float*)vp) << endl;
	delete vp;

	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={constant string}]
#include <iostream>
using namespace std;

int main()
{
	char str1[] = "Defined as an array";
	char* str2 = "Defined as a pointer";
	cout << str1 << endl; // display both strings
	cout << str2 << endl;
	//str1++; //can’t do this; str1 is a const ptr
	str2++; // this is OK, str2 is a pointer
	cout << str2 << endl; //now str2 starts "efined..."

	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Array of constant strings, contiguous storage}]
#include <iostream>
using namespace std;

int main()
{
	const int DAYS = 7;
	char* arrptrs[DAYS] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

	for(int j=0; j<DAYS; j++) //cout every string
		cout << arrptrs[j] << endl;

	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Constant column length, non-contiguous storage},escapechar=!]
#include <iostream>
using namespace std;

int main()
{
	const int DAYS = 7;
	!\color{red}{char arrptrs[DAYS][10]}! = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

	for(int j=0; j<DAYS; j++) //cout every string
		cout << arrptrs[j] << endl;

	return 0;
}
\end{lstlisting}
