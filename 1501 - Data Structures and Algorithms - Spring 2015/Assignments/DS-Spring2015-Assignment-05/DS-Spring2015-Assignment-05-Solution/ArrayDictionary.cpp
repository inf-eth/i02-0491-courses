#include "ArrayDictionary.h"
#include <iostream>
#include <fstream>
using namespace std;

ArrayDictionary::ArrayDictionary()
{
}

ArrayDictionary::~ArrayDictionary()
{
}

void ArrayDictionary::Insert(string Word)
{
	for (int i=0; i<(int)Data.size(); i++)
	{
		if (Word == Data[i])
			return;
		if (Word < Data[i])
		{
			Data.insert(Data.begin()+i, Word);
			return;
		}
	}
	Data.push_back(Word);
	return;
}

bool ArrayDictionary::Search(string Word)
{
	for (int i=0; i<(int)Data.size(); i++)
	{
		if (Word == Data[i])
			return true;
		if (Word < Data[i])
			return false;
	}
	return false; // Not found.
}

bool ArrayDictionary::Delete(string Word)
{
	// Error Check
	if ((int)Data.size()==0)
		return false;

	for (int i=0; i<(int)Data.size(); i++)
	{
		if (Word == Data[i])
		{
			Data.erase(Data.begin()+i);
			return true;
		}
		if (Word < Data[i])
			return false;
	}
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
