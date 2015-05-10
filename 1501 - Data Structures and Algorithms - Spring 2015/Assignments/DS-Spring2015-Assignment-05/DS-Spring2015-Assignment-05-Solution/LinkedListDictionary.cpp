#include "LinkedListDictionary.h"
#include <iostream>
#include <fstream>
using namespace std;

LinkedListDictionary::LinkedListDictionary()
{
}

LinkedListDictionary::~LinkedListDictionary()
{
}

void LinkedListDictionary::Insert(string Word)
{
	list<string>::iterator it = Data.begin();
	for (int i=0; i<(int)Data.size(); i++, it++)
	{
		if (Word == *it)
			return;
		if (Word < *it)
		{
			Data.insert(it, Word);
			return;
		}
	}
	Data.push_back(Word);
	return;
}

bool LinkedListDictionary::Search(string Word)
{
	list<string>::iterator it = Data.begin();
	for (int i=0; i<(int)Data.size(); i++, it++)
	{
		if (Word == *it)
			return true;
		if (Word < *it)
			return false;
	}
	return false; // Not found.
}

bool LinkedListDictionary::Delete(string Word)
{
	// Error Check
	if ((int)Data.size()==0)
		return false;

	list<string>::iterator it = Data.begin();
	for (int i=0; i<(int)Data.size(); i++, it++)
	{
		if (Word == *it)
		{
			Data.erase(it);
			return true;
		}
		if (Word < *it)
			return false;
	}
	return false; // Not found.
}

string LinkedListDictionary::Retrieve(int p)
{
	// Error Check
	if (p>=(int)Data.size() || p<0 || (int)Data.size()==0)
		return NULL;
	else
	{
		list<string>::iterator it = Data.begin();
		for (int i=0; i<(int)Data.size(); i++)
			it++;
		return *it;
	}
}

int LinkedListDictionary::PrintList()
{
	list<string>::iterator it = Data.begin();
	for (int i=0; i<(int)Data.size(); i++, it++)
		cout << *it << endl;

	return 0;
}

int LinkedListDictionary::PrintList(char* filename)
{
	fstream file;
	file.open(filename, ios::out|ios::trunc);
	list<string>::iterator it = Data.begin();
	for (int i=0; i<(int)Data.size(); i++, it++)
		file << *it << endl;
	file.close();
	return 0;
}
