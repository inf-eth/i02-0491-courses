#define NULL 0
class Node
{
public:
	Node();
	char Data;
	int Childs;
	Node* Child[5];

	void MakeTree(Node* &n, char* &prefix, int& i);
	void Preorder(Node* n);
	void Inorder(Node* n);
	void Postorder(Node* n);
};

class Tree
{
private:
	Node* Root;
public:
	Tree() {Root = NULL;}
	void MakeTree(char* &prefix);
	void Preorder();
	void Inorder();
	void Postorder();
};
