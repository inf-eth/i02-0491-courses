#include "RadixTreeDictionary.h"
#include <iostream>
using namespace std;

RadixTreeDictionary::RadixTreeDictionary()
{
	Root = new RadixNode;
	Root->Label = 'R';
}

void RadixTreeDictionary::Insert(string Word)
{
	if (Word == "")
		return;
	RadixNode* temp = Root;
	for (int i=0; i<(int)Word.length(); i++)
	{
		if (temp->Child[(unsigned char)Word[i]] == NULL)
		{
			temp->Child[(unsigned char)Word[i]] = new RadixNode;
			temp->Child[(unsigned char)Word[i]]->Label = Word[i];
			temp->Child[(unsigned char)Word[i]]->Parent = temp;
			temp->Childs++;
		}
		if (i == (int)Word.length()-1)
		{
			temp->Child[(unsigned char)Word[i]]->Check = true;
			break;
		}
		temp = temp->Child[(unsigned char)Word[i]];
	}
}

bool RadixTreeDictionary::Search(string Word)
{
	if (Word == "")
		return false;
	RadixNode* temp = Root;
	for (int i=0; i<(int)Word.length(); i++)
	{
		if (temp->Child[(unsigned char)Word[i]])
		{
			if (temp->Child[(unsigned char)Word[i]]->Label != Word[i])
				return false;
			if (i == (int)Word.length()-1)
			{
				if (temp->Child[(unsigned char)Word[i]]->Check == true)
					return true; // Search successful.
				else
					return false;
			}
		}
		else
			return false;
		temp = temp->Child[(unsigned char)Word[i]];
	}
	return false;
}

bool RadixTreeDictionary::Delete(string Word)
{
	if (Word == "")
		return false;
	RadixNode* temp = Root;
	for (int i=0; i<(int)Word.length(); i++)
	{
		if (temp->Child[(unsigned char)Word[i]])
		{
			if (temp->Child[(unsigned char)Word[i]]->Label != Word[i])
				return false;
			if (i == (int)Word.length()-1)
			{
				if (temp->Child[(unsigned char)Word[i]]->Check == true)
				{
					// Search successful. Delete word.
					temp = temp->Child[(unsigned char)Word[i]];
					temp->Check = false;
					for (int j=i; j>=0; j--)
					{
						if (temp->Childs == 0 && temp->Check == false)
						{
							temp->Parent->Child[(unsigned char)Word[j]] = NULL;
							temp->Parent->Childs--;
							RadixNode* deletethis = temp;
							temp = temp->Parent;
							delete deletethis;
						}
						else
							return true;
					}
					return true;
				}
				else
					return false;
			}
		}
		else
			return false;
		temp = temp->Child[(unsigned char)Word[i]];
	}
	return false;
}

void RadixNode::Print(RadixNode* &n, RadixNode* &r, vector<char> &ps)
{
	if (n != r)
		ps.push_back(n->Label);
	if (n->Check == true)
	{
		for (int i=0; i<(int)ps.size(); i++)
			cout << ps[i];
		cout << endl;
	}

	if (n->Childs == 0 && n != r)
		ps.pop_back();
	else
	{
		for (int i=0; i<256; i++)
		{
			if (n->Child[i])
				Print(n->Child[i], r, ps);
		}
		if (n != r)
			ps.pop_back();
	}
}
