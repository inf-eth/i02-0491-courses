\begin{lstlisting}[caption={Static and Dynamic Objects}]
#include <iostream>
using namespace std;

class Complex
{
	char ID;
public:
	// Default constructor.
	Complex(): ID('z') { cout << ID << " constructor called." << endl; }
	// User-defined constructor.
	Complex(char pID): ID(pID) { cout << ID << " constructor called." << endl; }
	// Destructor.
	~Complex() { cout << ID << " destructor called." << endl; }
};
int main()
{
	Complex x('x');  // Static object x. Constructor called.

	Complex *y; // Pointer declaration. No constructor called.
	y = new Complex('y'); // Constructor called. New object created.
	delete y;        // Memory deallocation. Dynamic object destroyed. Destructor called.

	Complex z[2]; // Default constructor called for both z[0] and z[1]. Two static objects created with ID 'z'.

	Complex *t[2]; // Two pointers declared. No object creation.
	t[0] = new Complex('a');	// Object creation. Constructor called.
	t[1] = new Complex('b');	// Object creation. Constructor called.

	delete t[0]; // Destructor called for t[0] 'a';
	delete t[1]; // Destructor called for t[1] 'b';

	cout << "main() is exiting now..." << endl;

	return 0;
}
// All static object destructors are called after main ends.
\end{lstlisting}
\begin{lstlisting}[caption={Copying Pointers}]
int main()
{
	int *x;
	x = new int;
	*x = 44;

	int *y;
	y = x;   // Cannot simply just copy pointers. Must allocate new memory for y.
	*y = 33; // Both *x and *y become 33.

	return 0;
}

\end{lstlisting}
\begin{lstlisting}[caption={Proper Way to Copy Pointers}]
int main()
{
	int *x;
	x = new int;
	*x = 44;

	int *y;
	y = new int; // pointer y is assigned its own memory.
	*y = *x;     // *x is now copied to *y. Both *x and *y contain 44.
	*y = 33;     // *x remains 44 and *y is now 33. Both pointers are independent.

	return 0;
}

\end{lstlisting}
\begin{lstlisting}[caption={Copying Pointers Using Copy Constructor}]
class Simple
{
public:
	int *value;
};

int main()
{
	Simple x;
	x.value = new int;
	*(x.value) = 3;

	Simple z(x);  // Copy constructor called.
	*(z.value) = 5;  // What happens? *(x.value) and *(z.value) both become 5 because both pointers are pointing to same memory location.

	return 0;
}
\end{lstlisting}
