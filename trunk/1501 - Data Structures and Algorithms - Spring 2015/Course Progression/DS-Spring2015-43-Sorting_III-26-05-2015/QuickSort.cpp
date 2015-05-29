#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void Swap(int& x1, int& x2)
{
	int temp = x1;
	x1 = x2;
	x2 = temp;
}

int FindPivot(int* Data, int Left, int Right)
{
	int temp = Data[Left];
	for (int i=Left; i<=Right; i++)
	{
		if (Data[i] != temp)
		{
			int n = Right - Left + 1;
			return Data[rand()%n+Left];
		}
	}
	return -1;
}

void QuickSort(int* Data, int Left, int Right)
{

	if (Left >= Right)
		return;

	int n = Right - Left + 1;
	int l = Left;
	int r = Right;
	int p = FindPivot(Data, Left, Right);
	if (p == -1)
		return;

	while (l <= r)
	{
		while (Data[l] < p)
			l++;
		while (Data[r] >= p && r > l-1)
			r--;
		if (l <= r)
			Swap(Data[r], Data[l]);
	}
	QuickSort(Data, Left, r);
	QuickSort(Data, l, Right);
}

int main()
{
	srand(time(NULL));
	int size = 10;
	int* Data = new int[size];
	for (int i=0; i<size; i++)
		Data[i] = rand()%20;
	for (int i=0; i<size; i++)
		cout << Data[i] << " ";
	cout << endl;
	QuickSort(Data, 0, size-1);
	for (int i=0; i<size; i++)
		cout << Data[i] << " ";
	cout << endl;
	return 0;
}
