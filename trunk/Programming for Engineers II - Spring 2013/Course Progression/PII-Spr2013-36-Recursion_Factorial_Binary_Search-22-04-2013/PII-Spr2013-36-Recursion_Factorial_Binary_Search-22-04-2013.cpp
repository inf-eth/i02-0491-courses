\begin{lstlisting}[caption={Insertion Sort},escapechar=$]
#include <iostream>
#include <cstdlib>
using namespace std;

// Swapping function using reference.
void Swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}

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

	// Insertion sort.
	for (int i=1; i<Size; i++)
	{
		int Key = data[i];
		int j;
		for (j=i-1; j>=0 && data[j]<Key; j--)
		{
			Swap(data[j+1], data[j]);	
		}
		data[j+1] = Key;
	}
	// Displaying data after sorting.
	cout << "Data after sorting: ";
	for (int i=0; i<Size; i++)
		cout << data[i] << " ";
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
