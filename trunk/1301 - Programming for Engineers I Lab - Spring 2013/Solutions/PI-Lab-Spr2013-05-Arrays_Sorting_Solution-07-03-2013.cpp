#include <iostream>
using namespace std;

int main()
{
	// Question No. 1.
	cout << "===================== Q1 =====================" << endl;
	// Both conditions will result in data sorted in descending order.

	const int Size = 5;
	int data[Size];

	// Question No. 2.
	cout << "===================== Q2 =====================" << endl;

	// Storing random numbers in range 0-99 in data[]
	for (int i=0; i<Size; i++)
		data[i] = rand() % 100;
		
	// Displaying data before sorting.
	cout << "Data before sorting (bubble sort): ";
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
			if (data[i] < data[i+1])
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

	// Question No. 3.
	cout << "===================== Q3 =====================" << endl;
	// Storing random numbers in range 0-99 in data[]
	for (int i=0; i<Size; i++)
		data[i] = rand() % 100;
		
	// Displaying data before sorting.
	cout << "Data before sorting (insertion sort): ";
	for (int i=0; i<Size; i++)
		cout << data[i] << " ";
	cout << endl;

	// Insertion sort
	for (int c=0; c<Size; c++)
	{
		int currentsize = Size-c;
		int min;
		int minindex;

		cout << "===== Iteration no: " << c+1 << " ====" << endl;
		if (currentsize > 1)
		{
			min = data[0];
			minindex = 0;

			// Pick minimum.
			for (int i=0; i<currentsize; i++)
			{
				if (data[i] < min)
				{
					min = data[i];
					minindex = i;
				}
			}
			// Swap with last element. data[minindex] <-> data[currentsize-1]
			int temp = data[minindex];
			data[minindex] = data[currentsize-1];
			data[currentsize-1] = temp;
			
			cout << "Array after swapping no: " << c+1 << endl;
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
