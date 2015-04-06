#include <iostream>
#include <string>
using namespace std;

template<class T> class Node
{
public:
	T Data;
	Node<T>* Left;
	Node<T>* Right;

	Node() {Left=Right=NULL;}
	void Inorder(Node<T>* n)
	{
		if (n==NULL)
			return;
		Inorder(n->Left);
		cout << n->Data << " ";
		Inorder(n->Right);
	}
	void Insert(Node<T>* &n, T &x)
	{
		if (n==NULL)
		{
			n=new Node<T>;
			n->Data = x;
			return;
		}
		if (x < n->Data)
			Insert(n->Left, x);
		else
			Insert(n->Right, x);
	}
};

template<class V> class Tree
{
private:
	Node<V>* Root;
public:
	Tree() {Root=NULL;}
	void Inorder()
	{
		Root->Inorder(Root);
	}
	void Insert(V Data)
	{
		Root->Insert(Root, Data);
	}
};

int main()
{

	Tree<int> IntTree;
	IntTree.Insert(4);
	IntTree.Insert(6);
	IntTree.Insert(8);
	IntTree.Insert(3);
	IntTree.Insert(7);
	IntTree.Inorder();
	cout << endl;

	Tree<string> Dictionary;
	Dictionary.Insert("hello");
	Dictionary.Insert("rat");
	Dictionary.Insert("bat");
	Dictionary.Insert("sat");
	Dictionary.Insert("cat");
	Dictionary.Insert("caterpiller");
	Dictionary.Insert("rock");
	Dictionary.Insert("crane");
	Dictionary.Inorder();
	cout << endl;

	return 0;
}
