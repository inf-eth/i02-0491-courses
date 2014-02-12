\begin{lstlisting}[caption={Typical Memory Leak}]
int main()
{
	int *x;
	x = new int;
	*x = 4;

	x = new int;  // Lost address of previously allocated memory!
	*x = 6;
	
	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Two Typical Program Crashes}]
int main()
{
	int *x;
	*x = 4;	 // CRASH1! x contains garbage address.
	delete x;// CRASH2! can't delete a random garbage address.
	
	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Using NULL to Properly Handle Pointers}]
int main()
{
	int *x = NULL;	// Pointer initialisation with NULL.
	
	// Allocation.
	if (x==NULL)
		x = new int;
	else
	{
		delete x;
		x = new int;
	}
		
	// Use pointer.
	*x = 4;
	
	// Explicit deallocation. Notice pointer is set to NULL.
	if (x!=NULL)
	{
		delete x;		// Deallocating memory.
		x = NULL;		// Pointer assigned NULL.
	}

	// New memory allocation.
	if (x==NULL)
		x = new int;
	else
	{
		delete x;
		x = new int;
	}

	// Pointer usage.
	*x = 6;
	
	// Deallocation before exiting.
	if (x!=NULL)
	{
		delete x;		// Deallocating memory.
		x = NULL;		// Pointer assigned NULL.
	}
	
	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Constructor and Destructor}]
#include <iostream>
using std::cout;
using std::endl;

class Simple
{
	private:
	const int x;
	int y;
	public:
	Simple();  // Default constructor.
	~Simple(); // Destructor.
};
// Notice member initialiser list after ':'
Simple::Simple(): x(0), y(0)
{
	cout << "Constructor called." << endl;
}
Simple::~Simple()
{
	cout << "Destructor called." << endl;
}

int main()
{
	Simple test;
	cout << "Object created in main(). Now exiting..." << endl;
	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Constructor and Destructor With Dynamic Allocation}]
#include <iostream>
using std::cout;
using std::endl;

class Simple
{
	private:
	const int x;
	int y;
	public:
	Simple();  // Default constructor.
	~Simple(); // Destructor.
};
// Notice member initialiser list after ':'
Simple::Simple(): x(0), y(0)
{
	cout << "Constructor called." << endl;
}
Simple::~Simple()
{
	cout << "Destructor called." << endl;
}

int main()
{
	Simple *test;
	
	cout << "Creating object..." << endl;
	test = new Simple;
	
	cout << "Deallocating object memory..." << endl;
	delete test;
	
	cout << "Exiting main()..." << endl;
	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Dynamic Matrix Class}]
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class matrix
{
private:
	float *Element;	// 1D matrix of size 1xSize.
	int Size;
public:
	matrix();
	matrix(int);
	~matrix();
	void SetSize(int);
	void Input();
	void Display();
	void Add(matrix&);
};

// Default constructor.
matrix::matrix(): Element(NULL), Size(0)
{
}
// User-defined constructor that takes in size.
matrix::matrix(int pSize)
{
	Element = new float[pSize];
	Size=pSize;

	// Initialising matrix.
	for (int i=0; i<Size; i++)
		Element[i] = 0.f;
}
// Destructor.
matrix::~matrix()
{
	if (Element != NULL)
		delete []Element;
}
// Resize matrix.
void matrix::SetSize(int pSize)
{
	if (Element == NULL)
		delete []Element;

	Element = new float[pSize];
	Size=pSize;
}
// Input matrix.
void matrix::Input()
{
	cout << "Enter matrix elements: ";
	for (int i=0; i<Size; i++)
		cin >> Element[i];
}
// Display matrix.
void matrix::Display()
{
	for (int i=0; i<Size; i++)
		cout << Element[i] << " ";

	cout << endl;
}
// Adds passed matrix into calling matrix.
void matrix::Add(matrix& m)
{
	for (int i=0; i<Size; i++)
		Element[i] = Element[i] + m.Element[i];
}

// Main.
int main()
{
	matrix matrix1(4);

	matrix matrix2;
	matrix2.SetSize(4);

	matrix1.Input();
	matrix2.Input();

	matrix1.Add(matrix2);

	cout << "Result is: ";
	matrix1.Display();

	// Resizing matrices.
	matrix1.SetSize(2);
	matrix2.SetSize(2);

	matrix1.Input();
	matrix2.Input();

	matrix1.Add(matrix2);
	cout << "Result is: ";
	matrix1.Display();

	return 0;
}
\end{lstlisting}
