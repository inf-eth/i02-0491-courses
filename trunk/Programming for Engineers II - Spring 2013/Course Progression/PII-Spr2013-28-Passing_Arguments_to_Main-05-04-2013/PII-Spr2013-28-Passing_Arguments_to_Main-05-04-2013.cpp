\begin{lstlisting}[caption={Passing Arguments to main()}]
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
	cout << "Number of arguments = " << argc << endl;
	cout << "Argument list: " << endl;
	for (int i=0; i<argc; i++)
		cout << "Arg " << i+1 << " = " << argv[i] << endl;

	string pass = "password";
	if (pass == string(argv[1]))
		cout << "Correct Password!" << endl;
	else
		cout << "Incorrect Password." << endl;

	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={Passing Variable as Reference and as Pointer}]
#include <iostream>
using namespace std;

void SquareRef(int& x)
{
	x = x*x;
}
void SquarePtr(int* x)
{
	*x = *x * *x;
}
int main()
{
	int a = 3;
	int b = 5;

	SquareRef(a);
	SquarePtr(&b);

	cout << "a^2 = " << a << endl;
	cout << "b^2 = " << b << endl;

	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={Function that `returns' int and double}]
#include <iostream>
using namespace std;

void Square(int* x, double* y)
{
	*x = *x * *x;
	*y = *y * *y;
}
int main()
{
	int a = 3;
	double b = 5;

	Square(&a, &b);

	cout << "a^2 = " << a << endl;
	cout << "b^2 = " << b << endl;

	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={Function to Allocate Array}]
#include <iostream>
using namespace std;

void CreateArray(int** ArrayPtr, int* SizePtr)
{
	cin >> *SizePtr;
	*ArrayPtr = new int[*SizePtr];
}
int main()
{
	int* Array;
	int Size;

	CreateArray(&Array, &Size);

	return 0;
}
\end{lstlisting}
