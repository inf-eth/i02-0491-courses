#include "ArrayDictionary.h"
#include <iostream>
#include <fstream>
using namespace std;

void ArrayDictionary::Insert(string Word)
{
}

bool ArrayDictionary::Search(string Word)
{
	return false; // Not found.
}

bool ArrayDictionary::Delete(string Word)
{
	return false; // Not found.
}

string ArrayDictionary::Retrieve(int p)
{
	// Error Check
	if (p>=(int)Data.size() || p<0 || (int)Data.size()==0)
		return NULL;
	else
		return Data[p];
}

int ArrayDictionary::PrintList()
{
	for (int i=0; i<(int)Data.size(); i++)
		cout << Data[i] << endl;

	return 0;
}

int ArrayDictionary::PrintList(char* filename)
{
	fstream file;
	file.open(filename, ios::out|ios::trunc);
	for (int i=0; i<(int)Data.size(); i++)
		file << Data[i] << endl;
	file.close();
	return 0;
}
