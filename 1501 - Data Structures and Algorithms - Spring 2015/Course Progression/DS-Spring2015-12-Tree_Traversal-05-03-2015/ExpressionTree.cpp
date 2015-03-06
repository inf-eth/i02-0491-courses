#include <iostream>
using namespace std;

class Node
{
public:
	Node();
	char Data;
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
	cout << "(";
	cout << n->Data;
	for (int i=0; i<n->Childs; i++)
		Preorder(n->Child[i]);
	cout << ")";
}

void Node::Inorder(Node* n)
{
	cout << "(";
	if (n->Childs!=0)
		Inorder(n->Child[0]);
	cout << n->Data;
	for (int i=1; i<n->Childs; i++)
		Inorder(n->Child[i]);
	cout << ")";
}

void Node::Postorder(Node* n)
{
	cout << "(";
	for (int i=0; i<n->Childs; i++)
		Postorder(n->Child[i]);
	cout << n->Data;
	cout << ")";
}

void MakeTree(Node* &Root)
{
	Root = new Node;
	Root->Data = '*';
	Root->Childs = 2;
	Root->Child[0] = new Node;
	Root->Child[0]->Data = '-';

	Root->Child[1] = new Node;
	Root->Child[1]->Data = '+';

	Root->Child[0]->Childs = 2;
	Root->Child[0]->Child[0] = new Node;
	Root->Child[0]->Child[0]->Data = 'a';
	Root->Child[0]->Child[1] = new Node;
	Root->Child[0]->Child[1]->Data = '*';

	Root->Child[0]->Child[1]->Childs = 2;
	Root->Child[0]->Child[1]->Child[0] = new Node;
	Root->Child[0]->Child[1]->Child[0]->Data = 'd';
	Root->Child[0]->Child[1]->Child[1] = new Node;
	Root->Child[0]->Child[1]->Child[1]->Data = 'e';

	Root->Child[1]->Childs = 2;
	Root->Child[1]->Child[0] = new Node;
	Root->Child[1]->Child[0]->Data = 'b';
	Root->Child[1]->Child[1] = new Node;
	Root->Child[1]->Child[1]->Data = 'c';
}

void DisplayTree()
{
	cout << "\
        *\n\
      /    \\\n\
     /      \\\n\
    -        +\n\
   / \\      / \\\n\
  a   *    b   c\n\
     / \\  \n\
    d   e \n";
	cout << endl;
}

int main()
{
	Node *Root;
	MakeTree(Root);
	DisplayTree();

	Root->Preorder(Root);
	cout << endl;

	Root->Inorder(Root);
	cout << endl;

	Root->Postorder(Root);
	cout << endl;

	return 0;
}
