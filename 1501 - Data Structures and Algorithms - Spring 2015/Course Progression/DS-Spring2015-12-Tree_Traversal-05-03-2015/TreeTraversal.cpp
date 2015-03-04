#include <iostream>
using namespace std;

class Node
{
public:
	Node();
	int Data;
	int Childs;
	Node* Child[5];

	void Preorder(Node* n);
	void Inorder(Node* n);
	void Postorder(Node* n);
};

Node::Node()
{
	Childs = 0;
	for (int i=0; i<5; i++)
		Child[i] = NULL;
};

void Node::Preorder(Node* n)
{
	cout << n->Data << ", ";
	for (int i=0; i<n->Childs; i++)
		Preorder(n->Child[i]);
}

void Node::Inorder(Node* n)
{
	if (n->Childs!=0)
		Inorder(n->Child[0]);
	cout << n->Data << ", ";
	for (int i=1; i<n->Childs; i++)
		Inorder(n->Child[i]);
}

void Node::Postorder(Node* n)
{
	for (int i=0; i<n->Childs; i++)
		Postorder(n->Child[i]);
	cout << n->Data << ", ";
}

void MakeTree(Node* &Root)
{
	Root = new Node;
	Root->Data = 1;
	Root->Childs = 3;
	Root->Child[0] = new Node;
	Root->Child[0]->Data = 2;

	Root->Child[1] = new Node;
	Root->Child[1]->Data = 3;

	Root->Child[1]->Childs = 2;
	Root->Child[1]->Child[0] = new Node;
	Root->Child[1]->Child[0]->Data = 5;
	Root->Child[1]->Child[1] = new Node;
	Root->Child[1]->Child[1]->Data = 6;

	Root->Child[1]->Child[0]->Childs = 2;
	Root->Child[1]->Child[0]->Child[0] = new Node;
	Root->Child[1]->Child[0]->Child[0]->Data = 8;
	Root->Child[1]->Child[0]->Child[1] = new Node;
	Root->Child[1]->Child[0]->Child[1]->Data = 9;

	Root->Child[1]->Child[1]->Childs = 1;
	Root->Child[1]->Child[1]->Child[0] = new Node;
	Root->Child[1]->Child[1]->Child[0]->Data = 10;

	Root->Child[2] = new Node;
	Root->Child[2]->Data = 4;
	Root->Child[2]->Childs = 1;
	Root->Child[2]->Child[0] = new Node;
	Root->Child[2]->Child[0]->Data = 7;
}

int main()
{
	Node *Root;
	MakeTree(Root);

	Root->Preorder(Root);
	cout << endl;

	Root->Inorder(Root);
	cout << endl;

	Root->Postorder(Root);
	cout << endl;

	return 0;
}
