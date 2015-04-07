#include "IntegerLinkedList.h"
#include <iostream>
#include <fstream>
using namespace std;

IntegerLinkedList::IntegerLinkedList()
{
	First = NULL;
	CurrentSize = 0;
}

IntegerLinkedList::~IntegerLinkedList()
{
}

int IntegerLinkedList::Insert(int x, int p)
{
	return -1;
}

int IntegerLinkedList::Locate(int x)
{
	return -1;
}

int IntegerLinkedList::Delete(int p)
{
	return -1;
}

int IntegerLinkedList::Retrieve(int p)
{
	return -1;
}

int IntegerLinkedList::Next(int p)
{
	return -1;
}

int IntegerLinkedList::Previous(int p)
{
	return -1;
}

int IntegerLinkedList::MakeNULL()
{
	return -1;
}

int IntegerLinkedList::PrintList()
{
	return -1;
}

int IntegerLinkedList::PrintList(char* filename)
{
	fstream file;
	file.open(filename, ios::out|ios::trunc);
	Node* temp = First;
	while (temp != NULL)
	{
		file << temp->Data << " ";
		temp = temp->Next;
	}
	file.close();
	return 0;
}

int IntegerLinkedList::Purge(int x)
{
	return -1;
}
