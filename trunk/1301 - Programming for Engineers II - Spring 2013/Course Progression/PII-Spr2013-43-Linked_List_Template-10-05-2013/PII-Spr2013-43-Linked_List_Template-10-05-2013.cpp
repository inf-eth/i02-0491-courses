#include <iostream>
using namespace std;

// Node
template <class T> class Node
{
public:
	T Data;
	Node<T>* Next;
};

// Linked list class.
template <class Y> class LinkedList
{
private:
	Node<Y>* First;
	int Count;
public:
	// Constructor.
	LinkedList(): First(NULL), Count(0)
	{
	}
	// Adds a node at the end of linked list.
	void AddNode(Y pData)
	{
		// If creating first node we need to change first pointer.
		if (First == NULL)
		{
			Node<Y>* NewNode;
			NewNode = new Node<Y>;
			NewNode->Data = pData;
			NewNode->Next = NULL;
			First = NewNode;
			Count++;
		}
		// We need to traverse the whole list to get to last node.
		else
		{
			// Find last node.
			Node<Y>* temp;
			temp = First;
			while (temp->Next != NULL)
				temp = temp->Next;
			// temp now points to last node.
			Node<Y>* NewNode;
			NewNode = new Node<Y>;
			temp->Next = NewNode;
			NewNode->Data = pData;
			NewNode->Next = NULL;
			Count++;
		}
	}
	// Displays all entries in linked list.
	void Display()
	{
		Node<Y>* temp;
		temp = First;
		while(temp != NULL)
		{
			cout << "Data = " << temp->Data << endl;
			temp = temp->Next;
		}
	}
	// Search a data value.
	int Search(Y Key)
	{
		Node<Y>* temp;
		temp = First;
		while(temp != NULL)
		{
			if (temp->Data == Key)
				return 0;

			temp = temp->Next;
		}
		return -1; // If we ever get here then search was unsuccessful.
	}
	// Delete a Node by data value.
	int Delete(Y Key)
	{
		// If List is empty then nothing to do.
		if (First == NULL)
			return -1;

		Node<Y>* previous;
		Node<Y>* current;
		previous = current = First;
		// Checking first node.
		if (current->Data == Key)
		{
			// Delete First node. First will now point to next node.
			First = First->Next;
			delete current;
			Count--;
			return 0;
		}
		else
		{
			current = current->Next; // Move current pointer to next node.
			while(current != NULL)
			{
				// If entry is matched then link previous node to next node and delete current node.
				if (current->Data == Key)
				{
					previous->Next = current->Next;
					delete current;
					Count--;
					return 0;
				}
				// Move pointers forward.
				previous = current;
				current = current->Next;
			}
		}
		return -1; // If we ever get here then search was unsuccessful.
	}
	// Get size of linked list.
	int GetCount()
	{
		return Count;
	}
	// Subscript operator.
	Y& operator[](int Index)
	{
		// Checking index bounds.
		if (Index < 0 || Index >= Count)
		{
			cout << "Index out of bounds. Exiting..." << endl;
			exit(-1);
		}
		else
		{
			// Move temp pointer to point to node at desired index.
			Node<Y>* temp = First;
			for (int i=0; i<Index; i++)
				temp = temp->Next;

			return temp->Data;
		}
	}
};

int main()
{
	LinkedList<int> TestList;

	TestList.AddNode(-1);
	TestList.AddNode(2);
	TestList.AddNode(0);
	TestList.AddNode(7);

	cout << "Displaying Linked List: " << endl;
	TestList.Display();

	int SearchKey = 2;
	if (TestList.Search(SearchKey) == 0)
		cout << SearchKey << " is in the list." << endl;

	if (TestList.Delete(SearchKey) == 0)
		cout << SearchKey << " was deleted." << endl;

	cout << "Displaying Linked List: " << endl;
	TestList.Display();
	
	TestList[0] = -122;
	cout << "Displaying Linked List: " << endl;
	for (int i=0; i<TestList.GetCount(); i++)
		cout << TestList[i] << endl;

	return 0;
}
