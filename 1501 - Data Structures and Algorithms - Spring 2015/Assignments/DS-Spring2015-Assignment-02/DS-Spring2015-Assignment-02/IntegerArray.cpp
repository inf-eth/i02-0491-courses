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
	return -1;
}

int IntegerArray::Locate(int x)
{
	return -1;
}

int IntegerArray::Delete(int p)
{
	return -1;
}

int IntegerArray::Retrieve(int p)
{
	return -1;
}

int IntegerArray::Next(int p)
{
	return -1;
}

int IntegerArray::Previous(int p)
{
	return -1;
}

int IntegerArray::MakeNULL()
{
	return -1;
}

int IntegerArray::PrintList()
{
	return -1;
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
	return -1;
}

