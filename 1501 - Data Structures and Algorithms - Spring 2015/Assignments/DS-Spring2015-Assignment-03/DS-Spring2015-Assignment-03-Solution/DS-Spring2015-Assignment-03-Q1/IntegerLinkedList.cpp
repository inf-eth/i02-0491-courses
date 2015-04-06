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
	Node* temp = First;
	while (temp != NULL)
	{
		Node* deletethis = temp;
		temp = temp->Next;
		delete deletethis;
		CurrentSize--;
	}
	First = NULL;
}

int IntegerLinkedList::Insert(int x, int p)
{
	// Error Check
	if (p>CurrentSize || p<0)
		return -1;

	if (p==0)
	{
		Node* FreshNode = new Node;
		FreshNode->Data = x;
		FreshNode->Next = First;
		First = FreshNode;
		CurrentSize++;
	}
	else
	{
		Node* temp = First;
		for (int i=0; i<p-1; i++)
			temp = temp->Next;

		Node* FreshNode = new Node;
		FreshNode->Data = x;
		FreshNode->Next = temp->Next;
		temp->Next = FreshNode;
		CurrentSize++;
	}
	return 0;
}

int IntegerLinkedList::Locate(int x)
{
	Node* temp = First;
	int i=0;
	while (temp != NULL)
	{
		if (temp->Data == x)
			return i;
		i++;
		temp= temp->Next;
	}
	return -1; // Not found.
}

int IntegerLinkedList::Delete(int p)
{
	// Error Check
	if (p>=CurrentSize || p<0 || CurrentSize==0)
		return -1;

	Node* temp = First;
	if (p==0)
	{
		First = First->Next;
		delete temp;
		CurrentSize--;
	}
	else
	{
		for (int i=0; i<p-1; i++)
			temp = temp->Next;

		Node* deletethis = temp->Next;
		temp->Next = temp->Next->Next;
		delete deletethis;
		CurrentSize--;
	}
	return 0;
}

int IntegerLinkedList::Retrieve(int p)
{
	// Error Check
	if (p>=CurrentSize || p<0 || CurrentSize==0)
		return -1;

	Node* temp = First;
	for (int i=0; i<p; i++)
		temp = temp->Next;
	return temp->Data;
}

int IntegerLinkedList::Next(int p)
{
	// Error Check
	if (p>=CurrentSize-1 || p<-1 || CurrentSize==0)
		return -1;

	Node* temp = First;
	for (int i=0; i<p+1; i++)
		temp = temp->Next;
	return temp->Data;
}

int IntegerLinkedList::Previous(int p)
{
	// Error Check
	if (p>=CurrentSize+1 || p<1 || CurrentSize==0)
		return -1;

	Node* temp = First;
	for (int i=0; i<p-1; i++)
		temp = temp->Next;
	return temp->Data;
}

int IntegerLinkedList::MakeNULL()
{
	Node* temp = First;
	while (temp != NULL)
	{
		Node* deletethis = temp;
		temp = temp->Next;
		delete deletethis;
		CurrentSize--;
	}
	First = NULL;
	return 0;
}

int IntegerLinkedList::PrintList()
{
	Node* temp = First;
	while (temp != NULL)
	{
		cout << temp->Data << " ";
		temp = temp->Next;
	}

	return 0;
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
	int found = -1;
	Node* temp = First;
	for (int i=0; i<CurrentSize-1; i++)
	{
		if (temp->Data == x)
			break;
		temp = temp->Next;
	}

	while (temp->Next != NULL)
	{
		if (temp->Next->Data == x)
		{
			Node* deletethis = temp->Next;
			temp->Next = temp->Next->Next;
			delete deletethis;
			CurrentSize--;
		}
		else
			temp = temp->Next;
	}
	return 0;
}
