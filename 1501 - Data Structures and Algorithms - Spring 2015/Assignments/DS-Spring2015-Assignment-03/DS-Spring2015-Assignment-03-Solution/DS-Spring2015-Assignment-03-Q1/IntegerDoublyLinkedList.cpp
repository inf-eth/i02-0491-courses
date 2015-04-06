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
	// Error Check
	if (p>CurrentSize || p<0)
		return -1;

	if (p==0)
	{
		DNode* FreshNode = new DNode;
		FreshNode->Data = x;
		FreshNode->Next = First;
		FreshNode->Previous = NULL;
		if (CurrentSize != 0)
			First->Previous = FreshNode;
		else
			Last = FreshNode;
		First = FreshNode;
		CurrentSize++;
	}
	else
	{
		if (p > CurrentSize/2)
		{
			DNode* temp = Last;
			for (int i=0; i<CurrentSize-p; i++)
				temp = temp->Previous;

			DNode* FreshNode = new DNode;
			FreshNode->Data = x;
			FreshNode->Next = temp->Next;
			FreshNode->Previous = temp;
			if (temp != Last)
				temp->Next->Previous = FreshNode;
			else
				Last = FreshNode;
			temp->Next = FreshNode;
		}
		else
		{
			DNode* temp = First;
			for (int i=0; i<p-1; i++)
				temp = temp->Next;

			DNode* FreshNode = new DNode;
			FreshNode->Data = x;
			FreshNode->Next = temp->Next;
			FreshNode->Previous = temp;
			temp->Next->Previous = FreshNode;
			temp->Next = FreshNode;
		}
		CurrentSize++;
	}
	return 0;
}

int IntegerDoublyLinkedList::Delete(int p)
{
	// Error Check
	if (p>=CurrentSize || p<0 || CurrentSize==0)
		return -1;

	if (p < CurrentSize/2)
	{
		DNode* temp = First;
		for (int i=0; i<p; i++)
			temp = temp->Next;

		if (p != 0)
		{
			temp->Previous->Next = temp->Next;
			temp->Next->Previous = temp->Previous;
			delete temp;
		}
		else
		{
			First = temp->Next;
			if (First)
				First->Previous = NULL;
			else
				Last = First;
			delete temp;
		}
	}
	else
	{
		DNode* temp = Last;
		for (int i=0; i<CurrentSize-p-1; i++)
			temp = temp->Previous;

		if (p != CurrentSize-1)
		{
			temp->Previous->Next = temp->Next;
			temp->Next->Previous = temp->Previous;
			delete temp;
		}
		else
		{
			Last = temp->Previous;
			if (Last)
				Last->Next = NULL;
			else
				First = Last;
			delete temp;
		}
	}
	CurrentSize--;
	return 0;
}

int IntegerDoublyLinkedList::Retrieve(int p)
{
	// Error Check
	if (p>=CurrentSize || p<0 || CurrentSize==0)
		return -1;

	if (p < CurrentSize/2)
	{
		DNode* temp = First;
		for (int i=0; i<p; i++)
			temp = temp->Next;
		return temp->Data;
	}
	else
	{
		DNode* temp = Last;
		for (int i=0; i<CurrentSize-p-1; i++)
			temp = temp->Previous;
		return temp->Data;
	}
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
