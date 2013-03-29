\begin{lstlisting}[caption={Pointer Basics}]
#include <iostream>
using namespace std;
int main()
{
	int x = 3; // x declaration and initialisation.
	int* px; // Pointer declaration.
	px = &x; // Pointer xp now `points' to x.
	
	cout << x << endl;   // Value of x.
	cout << &x << endl;  // Address of x.
	cout << xp << endl;  // Value of xp = Address of x.
	cout << *xp << endl; // Pointer dereference: Using xp to access value of x.
	
	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={Dynamic memory allocation with pointer}]
int main()
{
	int* p;
	
	// Single integer.
	p = new int; // Allocation.
	*p = 3;
	delete p;    // De-allocation.
	
	// Integer array.
	p = new int[5]; // Array allocation.
	for (int i=0; i<5; i++)
	{
		p[i] = i;
	}		
	delete[] p;     // Array de-allocation.
	
	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={Default object copy}]
#include <iostream>
using namespace std;
class Test
{
	public:
	int x;
};
int main()
{
	Test A, B;
	A.x = 3;
	
	B = A;		// Assignment operator.
	Test C = A; // Copy constructor.
	
	// B.x and C.x now contain 3. Same as A.x.
	// Changing B.x won't affect A.x or B.x.
	// All x's are independent.
	
	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={Default cbject copy with pointers}]
#include <iostream>
using namespace std;
class Test
{
	public:
	int* x;
};
int main()
{
	Test A, B;
	A.x = new int;
	*(A.x) = 3;
	
	B = A;		// Assignment operator.
	Test C = A; // Copy constructor.
	
	delete A.x; // De-allocates memory for all pointers!

	// B.x and C.x now contain the same address as A.x.
	// All point to same memory location!
	// Sharing same value!
	
	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={Overloading copy constructor and assignment operator}]
class Test
{
	public:
	int* x;
	// Copy constructor.
	Test(const Test& rhs)
	{
		x = new int;
		*x = *(rhs.x); // Copying value.
	}
	// Assignment operator.
	Test operator= (const Test& rhs)
	{
		x = new int;
		*x = *(rhs.x); // Copying value.
	}
};
\end{lstlisting}
