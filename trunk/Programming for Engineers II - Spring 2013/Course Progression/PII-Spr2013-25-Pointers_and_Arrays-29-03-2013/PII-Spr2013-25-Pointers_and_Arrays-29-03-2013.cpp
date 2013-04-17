\begin{lstlisting}[caption={Pointers to Objects}]
#include <iostream>
using namespace std;

class Complex
{
	public:
	float real, img;
};
int main()
{
	Complex* c;
	delete c; // What will this do? Crash! Don't try to de-allocate un-allocated pointers.

	c = new Complex; // Dynamic memory allocation.

	// Member access using arrow operator.
	c->real = 3; // Also, (*c).real
	c->img = 5;  // Also, (*c).img

	delete c; // De-allocation.

	// Array allocation.
	c = new Complex[10];

	for (int i=0; i<10; i++)
	{
		c[i].real = 3;
		c[i].img = 5;
	}
	delete[] c; // Release or de-allocate memory.

	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Pointer levels}]
#include <iostream>
using namespace std;

int main()
{
	int** ipp;

	int x1 = 5;
	int x2 = 6;
	int x3 = 7;

	int* ip1;
	int* ip2;

	ip1 = &x1;
	ip2 = &x2;
	ipp = &ip1;

	*ipp = ip2;
	*ipp = &x3;
	**ipp = -1;

	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Arrays and Pointers}]
#include <iostream>
using namespace std;

int main()
{
	int Array[5] = {3,7,2,1,5};

	cout << Array << endl; // Prints the address of array.

	// Using subscript.
	cout << Array[0] << endl; // Print the value of element located a distance of 0 from start.
	cout << Array[3] << endl; // Print the value of element located a distance of 3 from start.
	cout << Array[5] << endl; // Print the value of element located a distance of 5 from start. ERROR! Out of bound.

	// Using Pointers.
	cout << *(Array+0) << endl; // Prints the value of first element which is 3.
	cout << *(Array+1) << endl; // Prints the value of second element which is 7.
	cout << *(Array+5) << endl; // Prints the value of sixth element which is out of bound. ERROR!

	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Dynamic 2D array}]
int main()
{
	int Rows = 3;
	int Cols = 3;
	// Pointer.
	int** Array2D;

	// Array of int* 'ers equal to number of rows.
	Array2D = new int*[Rows];
	// Each int* is used to allocate int array equal to number of columns.
	for (int i=0; i<Rows; i++)
	{
		Array2D[i] = new int[Cols];
	}

	// Accessing array elements.
	for (int i=0; i<Rows; i++)
	{
		for (int j=0; j<Cols; j++)
		{
			Array2D[i][j] = i*j;
		}
	}
	// Array2D[i][j] = *((*(Array2D+i))+j) = (*(Array2D+i))[j] = *(Array2D[i]+j)

	// De-allocation
	for (int i=0; i<Rows; i++)
	{
		delete[] Array2D[i];
	}
	delete[] Array2D;

	return 0;
}
\end{lstlisting}
