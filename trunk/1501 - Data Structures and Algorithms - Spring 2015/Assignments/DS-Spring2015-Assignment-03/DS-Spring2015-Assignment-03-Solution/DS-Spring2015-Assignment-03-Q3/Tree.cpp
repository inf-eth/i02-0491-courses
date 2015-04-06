#include "Tree.h"
#include <iostream>
using namespace std;

Node::Node()
{
	Childs = 0;
	for (int i=0; i<5; i++)
		Child[i] = NULL;
};

void Node::MakeTree(Node* &n, char* &prefix, int& i)
{
	// ======== Algorithm ========
	/*
	If prefix[i] is (
		If n is NULL allocate memory
		Else call MakeTree on first child pointer that is NULL. Increment number of children.
	Else If prefix[i] is ) or NULL
		return
	Else 
		data of n = prefix[i]

	Increment i
	Call MakeTree on n
	*/
	if (prefix[i] == '(')
	{
		if (n == NULL)
			n = new Node;
		else
		{
			MakeTree(n->Child[n->Childs], prefix, i);
			n->Childs++;
		}
	}
	else if (prefix[i] == ')' || prefix[i] == NULL)
		return;
	else
		n->Data = prefix[i];

	i++;
	MakeTree(n, prefix, i);
}

void Node::Preorder(Node* n)
{
	if (n == NULL)
		return;
	cout << "(";
	cout << n->Data;
	Preorder(n->Child[0]);
	Preorder(n->Child[1]);
	cout << ")";
}

void Node::Inorder(Node* n)
{
	if (n == NULL)
		return;
	cout << "(";
	Inorder(n->Child[0]);
	cout << n->Data;
	Inorder(n->Child[1]);
	cout << ")";
}

void Node::Postorder(Node* n)
{
	if (n == NULL)
		return;
	cout << "(";
	Postorder(n->Child[0]);
	Postorder(n->Child[1]);
	cout << n->Data;
	cout << ")";
}

void Tree::MakeTree(char* &prefix)
{
	int i=0;
	Root->MakeTree(Root, prefix, i);
}


void Tree::Preorder()
{
	Root->Preorder(Root);
}

void Tree::Inorder()
{
	Root->Inorder(Root);
}

void Tree::Postorder()
{
	Root->Postorder(Root);
}
