#include "LinkedListDictionary.h"
#include <iostream>
#include <fstream>
using namespace std;

void LinkedListDictionary::Insert(string Word)
{
	return;
}

bool LinkedListDictionary::Search(string Word)
{
	return false; // Not found.
}

bool LinkedListDictionary::Delete(string Word)
{
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
