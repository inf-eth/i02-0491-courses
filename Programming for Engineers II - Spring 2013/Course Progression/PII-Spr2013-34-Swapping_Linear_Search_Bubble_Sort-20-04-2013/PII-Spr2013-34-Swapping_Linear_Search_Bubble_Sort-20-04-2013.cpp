\begin{lstlisting}[caption={Swapping Functions Using Pointer and Reference},escapechar=$]
#include <iostream>
using namespace std;

// Swapping function using pointers.
void Swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
// Swapping function using reference.
void Swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}

int main()
{
	int A = 3;
	int B = 6;
	cout << "Initial values: A = " << A << ", B = " << B << endl;

	Swap(A, B);
	cout << "After swapping (using reference): A = " << A << ", B = " << B << endl;

	Swap(&A, &B);
	cout << "After swapping again (using pointers): A = " << A << ", B = " << B << endl;
	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={Linear Search for sorted and unsorted data},escapechar=$]
#include <iostream>
#include <cstdlib>
using namespace std;

// Sorted (ascending)
bool SearchSorted(int* Data, int Size, int Key)
{
	for (int i=0; i<Size; i++)
	{
		// If match found return true.
		if (Data[i] == Key)
			return true;
		// If values are greater than key then no need to search further.
		if (Data[i] > Key)
			return false;
	}
	return false; // If we ever get here, search was unsuccessful.
}
// Unsorted.
bool SearchUnSorted(int* Data, int Size, int Key)
{
	for (int i=0; i<Size; i++)
	{
		// If match found return true.
		if (Data[i] == Key)
			return true;
	}
	return false; // If we ever get here, search was unsuccessful.
}
int main()
{
	const int Size = 10;
	int Data[Size];
	for (int i=0; i<10; i++)
	{
		Data[i] = rand()%10;
		cout << "Data[i] = " << Data[i] << endl;
	}

	int Key;
	cout << "Enter a value to search: ";
	cin >> Key;

	if (SearchUnsorted(Data, Size, Key) == true)
		cout << "Search successful!" << endl;

	return 0;
}
\end{lstlisting}
\begin{lstlisting}[caption={Bubble Sort}]
#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
	const int Size = 5;
	int data[Size];

	// Storing random numbers in range 0-99 in data[]
	for (int i=0; i<Size; i++)
		data[i] = rand() % 100;
		
	// Displaying data before sorting.
	cout << "Data before sorting: ";
	for (int i=0; i<Size; i++)
		cout << data[i] << " ";
	cout << endl;

	// Bubblesort
	for (int c=0; c<Size; c++)
	{
		int currentsize = Size-c;
		cout << "===== Iteration no: " << c+1 << " ====" << endl;
		for (int i=0; i<currentsize-1; i++)
		{
			// Sorting condition.
			if (data[i] > data[i+1])
			{
				// Swap.
				int temp = data[i];
				data[i] = data[i+1];
				data[i+1] = temp;
			}
			cout << "Array after swapping no: " << i << endl;
			for (int z=0; z<Size; z++)
				cout << data[z] << " ";
			cout << endl;
		}
		cout << "===================================" << endl;
	}

	// Displaying data after sorting.
	cout << "Data after sorting: ";
	for (int i=0; i<Size; i++)
		cout << data[i] << " ";
	cout << endl;
	
	return 0;
}
\end{lstlisting}
