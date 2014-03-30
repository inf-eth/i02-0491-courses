#include <iostream>
using namespace std;

class Node
{
public:
	int Data;
	Node* Next;
};

class LinkedList
{
private:
	Node* First;
public:
	LinkedList(): First(NULL)
	{
	}
	// Adds a node at the end of linked list.
	void AddNode(int pData)
	{
		// If creating first node we need to change first pointer.
		if (First == NULL)
		{
			Node* NewNode;
			NewNode = new Node;
			NewNode->Data = pData;
			NewNode->Next = NULL;
			First = NewNode;
		}
		// We need to traverse the whole list to get to last node.
		else
		{
			// Find last node.
			Node* temp;
			temp = First;
			while (temp->Next != NULL)
				temp = temp->Next;
			// temp now points to last node.
			Node* NewNode;
			NewNode = new Node;
			temp->Next = NewNode;
			NewNode->Data = pData;
			NewNode->Next = NULL;
		}
	}
	// Displays all entries in linked list.
	void Display()
	{
		Node* temp;
		temp = First;
		while(temp != NULL)
		{
			cout << "Data = " << temp->Data << endl;
			temp = temp->Next;
		}
	}
	// Search a data value.
	int Search(int Key)
	{
		Node* temp;
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
	int Delete(int Key)
	{
		// If List is empty then nothing to do.
		if (First == NULL)
			return -1;

		Node* previous;
		Node* current;
		previous = current = First;
		// Checking first node.
		if (current->Data == Key)
		{
			// Delete First node. First will now point to next node.
			First = First->Next;
			delete current;
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
					return 0;
				}
				// Move pointers forward.
				previous = current;
				current = current->Next;
			}
		}
		return -1; // If we ever get here then search was unsuccessful.
	}
};

int main()
{
	LinkedList TestList;

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

	return 0;
}
