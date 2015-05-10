#include "BinarySearchTreeDictionary.h"

void TreeNode::Inorder(TreeNode* n)
{
	if (n==NULL)
		return;
	Inorder(n->Left);
	cout << n->Word << endl;
	Inorder(n->Right);
}
void TreeNode::Insert(TreeNode* &n, string &Word)
{
	if (n==NULL)
	{
		n=new TreeNode;
		n->Word = Word;
		return;
	}
	if (Word < n->Word)
		Insert(n->Left, Word);
	else if (Word > n->Word)
		Insert(n->Right, Word);
	else 
		return;
}

bool TreeNode::Search(TreeNode* &n, string &Word)
{
	if (n==NULL)
		return false;
	if (Word == n->Word)
		return true;
	else if (Word < n->Word)
		return Search(n->Left, Word);
	else if (Word > n->Word)
		return Search(n->Right, Word);
	else 
		return false;
}

bool TreeNode::Delete(TreeNode* &n, TreeNode* &p, string &Word)
{
	TreeNode* temp = n;
	TreeNode* Parent = n==p ? NULL : p;
	while (true)
	{
		if (temp == NULL)
			return false;
		if (Word == temp->Word)
			break;
		else if (Word < temp->Word)
		{
			Parent = temp;
			temp = temp->Left;
		}
		else if (Word > temp->Word)
		{
			Parent = temp;
			temp = temp->Right;
		}
		else 
			return false;
	}
	// 1. Delete if Leaf.
	if (temp->Left == NULL && temp->Right == NULL)
	{
		if (Parent)
		{
			if (Parent->Left == temp)
				Parent->Left = NULL;
			else
				Parent->Right = NULL;
		}
		delete temp;
		return true;
	}
	// 2. Shift if only one subtree
	else if (temp->Left == NULL || temp->Right == NULL)
	{
		if (Parent)
		{
			if (Parent->Left == temp)
				Parent->Left = temp->Left == NULL ? temp->Right : temp->Left;
			else
				Parent->Right = temp->Left == NULL ? temp->Right : temp->Left;
		}
		delete temp;
		return true;
	}
	// 3. If Two children
	else if (temp->Left != NULL && temp->Right != NULL)
	{
		string min = FindMin(temp->Right);
		temp->Word = min;
		return Delete(temp->Right, temp, min);
	}
	else
		return false;
}

string TreeNode::FindMin(TreeNode* &n)
{
	if (n->Left == NULL)
		return n->Word;
	else
		return FindMin(n->Left);
}
