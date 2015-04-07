#include <iostream>
#include <string>
using namespace std;

class TreeNode
{
public:
	string Word;
	TreeNode* Left;
	TreeNode* Right;

	TreeNode() {Left=Right=NULL;}
	void Inorder(TreeNode* n);
	void Insert(TreeNode* &n, string &Word);
	bool Search(TreeNode* &n, string &Word);
	bool Delete(TreeNode* &n, TreeNode* &p, string &Word); // Current node, parent of current node and word to be deleted.
	string FindMin(TreeNode* &n);
};

class BinarySearchTreeDictionary
{
private:
	TreeNode* Root;
public:
	BinarySearchTreeDictionary() {Root=NULL;}
	void Inorder()
	{
		Root->Inorder(Root);
	}
	void Insert(string Word)
	{
		Root->Insert(Root, Word);
	}
	bool Search(string Word)
	{
		return Root->Search(Root, Word);
	}
	bool Delete(string Word)
	{
		return Root->Delete(Root, Root, Word);
	}
	string FindMin()
	{
		return Root->FindMin(Root);
	}
};
