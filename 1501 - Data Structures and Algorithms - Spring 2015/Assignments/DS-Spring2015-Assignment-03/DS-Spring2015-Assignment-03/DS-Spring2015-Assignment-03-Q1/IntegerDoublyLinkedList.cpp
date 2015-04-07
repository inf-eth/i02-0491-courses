#include "IntegerDoublyLinkedList.h"
#include <iostream>
#include <fstream>
using namespace std;

IntegerDoublyLinkedList::IntegerDoublyLinkedList()
{
	First = NULL;
	Last = NULL;
	CurrentSize = 0;
}

IntegerDoublyLinkedList::~IntegerDoublyLinkedList()
{
	DNode* temp = First;
	while (temp != NULL)
	{
		DNode* deletethis = temp;
		temp = temp->Next;
		delete deletethis;
		CurrentSize--;
	}
	First = NULL;
	Last = NULL;
}

int IntegerDoublyLinkedList::Insert(int x, int p)
{
	return -1;
}

int IntegerDoublyLinkedList::Delete(int p)
{
	return -1;
}

int IntegerDoublyLinkedList::Retrieve(int p)
{
	return -1;
}

int IntegerDoublyLinkedList::MakeNULL()
{
	DNode* temp = First;
	while (temp != NULL)
	{
		DNode* deletethis = temp;
		temp = temp->Next;
		delete deletethis;
		CurrentSize--;
	}
	First = NULL;
	Last = NULL;
	return 0;
}

int IntegerDoublyLinkedList::PrintList()
{
	DNode* temp = First;
	while (temp != NULL)
	{
		cout << temp->Data << " ";
		temp = temp->Next;
	}
	return 0;
}

int IntegerDoublyLinkedList::PrintList(char* filename)
{
	fstream file;
	file.open(filename, ios::out|ios::trunc);
	DNode* temp = First;
	while (temp != NULL)
	{
		file << temp->Data << " ";
		temp = temp->Next;
	}
	file.close();
	return 0;
}
