#include "IntegerArray.h"
#include <iostream>
#include <fstream>
using namespace std;

IntegerArray::IntegerArray()
{
	Data = new int[MAXSIZE];
	CurrentSize = 0;
}

int IntegerArray::Insert(int x, int p)
{
	// Error Check
	if (p>CurrentSize || p<0 || CurrentSize==MAXSIZE)
		return -1;

	for (int i=CurrentSize; i>p; i--)
		Data[i] = Data[i-1];

	Data[p] = x;
	CurrentSize++;

	return 0;
}

int IntegerArray::Locate(int x)
{
	for (int i=0; i<CurrentSize; i++)
	{
		if (Data[i] == x)
			return i;
	}
	return -1; // Not found.
}

int IntegerArray::Delete(int p)
{
	// Error Check
	if (p>=CurrentSize || p<0 || CurrentSize==0)
		return -1;

	for (int i=p; i<CurrentSize-1; i++)
		Data[i] = Data[i+1];

	CurrentSize--;

	return 0;
}

int IntegerArray::Retrieve(int p)
{
	// Error Check
	if (p>=CurrentSize || p<0 || CurrentSize==0)
		return -1;

	return Data[p];
}

int IntegerArray::Next(int p)
{
	// Error Check
	if (p>=CurrentSize-1 || p<-1 || CurrentSize==0)
		return -1;

	return Data[p+1];
}

int IntegerArray::Previous(int p)
{
	// Error Check
	if (p>=CurrentSize+1 || p<1 || CurrentSize==0)
		return -1;

	return Data[p-1];
}

int IntegerArray::MakeNULL()
{
	CurrentSize=0;

	return 0;
}

int IntegerArray::PrintList()
{
	for (int i=0; i<CurrentSize; i++)
		cout << Data[i] << " ";

	return 0;
}

int IntegerArray::PrintList(char* filename)
{
	fstream file;
	file.open(filename, ios::out|ios::trunc);
	for (int i=0; i<CurrentSize; i++)
		file << Data[i] << " ";
	file.close();
	return 0;
}

int IntegerArray::Purge(int x)
{
	int found = -1;
	for (int i=0; i<CurrentSize-1; i++)
	{
		if (Data[i] == x)
		{
			found = i;
			break;
		}
	}

	if (found != -1)
	{
		for (int j=found+1; j<CurrentSize; j++)
		{
			if (Data[j] == x)
			{
				Delete(j);
				j--;
			}
		}
	}

	return 0;
}

