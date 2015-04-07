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
}

void Node::Preorder(Node* n)
{
	cout << "(";
	// Print data of n
	// Call Preorder on all children of n
	cout << ")";
}

void Node::Inorder(Node* n)
{
	cout << "(";
	// Call Inorder on leftmost child
	// Print data of n
	// Call Inorder on rest of children of n
	cout << ")";
}

void Node::Postorder(Node* n)
{
	cout << "(";
	// Call Postorder on all children of n
	// Print data of n
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
