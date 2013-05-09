\begin{lstlisting}[caption={Creating a Linked List}]
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
			temp = first;
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
};

int main()
{
	LinkedList TestList;

	TestList.AddNode(-1);
	TestList.AddNode(2);
	TestList.AddNode(0);
	TestList.AddNode(7);
	
	TestList.Display();
	
	return 0;
}
\end{lstlisting}
