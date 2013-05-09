\begin{lstlisting}[caption={Variable Scope}]
#include <iostream>
using namespace std;

int x; // Global variable

class Simple
{
	int y; // y is local variable for Simple class.
	public:
	// Default constructor.
	Simple()
	{
		cout << "Value of x in constructor: " << x << endl;
		x = 100;
		y = 0;
		cout << "Value of x after constructor call: " << x << endl;
	}
	~Simple()
	{
		x = -1;
		cout << "Value of x after destructor call: " << x << endl;
	}
};
void SimpleFunction()
{
	Simple functionobj; // functionobj is a local object of SimpleFunction().
	x = 1;
}
int main()
{
	x = 33;
	Simple* obj = new Simple;

	SimpleFunction();

	delete obj;

	for (int i=0; i<3; i++)
	{
		int j;
	}
	cout << i << j << endl; // Compilation error: i and j are local to for loop.

	cout << "main() is exiting now..." << endl;
	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={Function Returning Reference}]
#include <iostream>
using namespace std;
int x = 0;
int& SimpleFunction()
{
	int y=0;
	return x; // return y won't make sense but return x would, but wait! return x also doesn't make any sense because x is accessible everywhere! Why return a global variable?
}
int main()
{
	SimpleFunction() = 100; // SimpleFunction() returns reference to x and that is assigned a value.

	cout << "Value of x = " << x << endl;
	
	int z;
	z = SimpleFunction(); // Assigning z the value of x.
	cout << "Value of z = " << z << endl;

	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={Safe Array With Set() and Get()}]
#include <iostream>
#include <cstdlib> // for exit()
using namespace std;
const int SIZE = 10;
class SafeArray
{
	private:
	int element[SIZE];
	public:
	void Set(int index, int value)
	{
		if (index < 0 || index >= SIZE)
		{
			cout << "Array out of bounds." << endl;
			exit(-1);
		}
		element[index] = value;
	}
	 // Notice, a get() function doesn't change any variable, hence, const.
	int Get(int index) const
	{
		if (index < 0 || index >= SIZE)
		{
			cout << "Array out of bounds." << endl;
			exit(-1);
		}
		return element[index];
	}
};
int main()
{
	SafeArray obj;
	obj.Set(0, 10);
	cout << "Array[0] = " << obj.Get(0);

	obj.Set(10, 33); // ERROR!
	cout << "Array[-1] = " << obj.Get(-1); // ERROR!

	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={Safe Array With Subscript Operator[]}]
#include <iostream>
#include <cstdlib> // for exit()
using namespace std;
const int SIZE = 10;
class SafeArray
{
	private:
	int element[SIZE];
	public:
	int& operator[](int index)
	{
		if (index < 0 || index >= SIZE)
		{
			cout << "Array out of bounds." << endl;
			exit(-1);
		}
		return element[index];
	}
};
int main()
{
	SafeArray obj;
	obj[0] = 10; // obj.Set(0, 10);
	cout << "Array[0] = " << obj[0];

	obj[10] = 33; //obj.Set(10, 33); // ERROR!
	cout << "Array[-1] = " << obj[-1]; // ERROR!

	return 0;
}
\end{lstlisting}
