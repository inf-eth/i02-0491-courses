\begin{lstlisting}[caption={Recursive Factorial},escapechar=$]
#include <iostream>
using namespace std;

// Factorial function.
int Factorial(int n)
{
	if (n==0||n==1)
		return 1; // Base cases.
	else
		return n*Factorial(n-1);
}

int main()
{
	int x;
	cout << "Enter n: ";
	cin >> x;
	cout << "n! = " << Factorial(x) << endl;

	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Fibonacci Series},escapechar=$]
#include <iostream>
using namespace std;

// Calculate Fibonacci Series nth term.
int fib(int n)
{
	// Base cases.
	if (n==0)
		return 0;
	if (n==1)
		return 1;
	// If not base case go recursive.
	else
		return fib(n-1)+fib(n-2);
}

int main()
{
	int x;
	cout << "Enter number of terms: ";
	cin >> x;
	cout << "Fibonacci Series upto " << x << " terms is: ";
	for (int i=0; i<x; i++)
	{
		cout << fib(i) << " ";
	}
	cout << endl;

	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Binary Search}]
#include <cstdlib>
#include <iostream>
using namespace std;

bool BinarySearch(int* Data, int Size, int Key)
{
	int left = 0;
	int right = Size-1;
	int mid = (left+right)/2;

	cout << "================================" << endl;
	cout << "Data = ";
	for (int i=0; i<Size; i++)
		cout << Data[i] << " ";
	cout << endl;
	cout << "Size = " << Size << ", Key = " << Key << endl;
	cout << "left = " << left << ", right = " << right << ", mid = " << mid << endl;

	if (Data[mid] == Key)
		return true;
	if (Size == 1)
		return false;

	// Left half.
	if (Key < Data[mid])
		right = mid-1;
	else
		left = mid+1;

	return BinarySearch(Data+left, right-left+1, Key);
}

void BubbleSort(int* Data, int Size)
{
	// Bubblesort
	for (int c=0; c<Size; c++)
	{
		int currentsize = Size-c;
		for (int i=0; i<currentsize-1; i++)
		{
			// Sorting condition.
			if (Data[i] > Data[i+1])
			{
				// Swap.
				int temp = Data[i];
				Data[i] = Data[i+1];
				Data[i+1] = temp;
			}
		}
	}
}
int main()
{
	int Size;
	cout << "Enter size of data: ";
	cin >> Size;
	int* data = new int[Size];

	// Storing random numbers in range 0-99 in data[]
	for (int i=0; i<Size; i++)
		data[i] = rand() % 100;
		
	// Displaying data before sorting.
	cout << "Data before sorting: ";
	for (int i=0; i<Size; i++)
		cout << data[i] << " ";
	cout << endl;

	BubbleSort(data, Size);

	// Displaying data after sorting.
	cout << "Data after sorting: ";
	for (int i=0; i<Size; i++)
		cout << data[i] << " ";
	cout << endl;

	int Key;
	cout << "Enter key to search: ";
	cin >> Key;
	if (BinarySearch(data, Size, Key) == true)
		cout << "Key: " << Key << " was found!" << endl;

	return 0;
}
\end{lstlisting}
