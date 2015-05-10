#include <string>
#include <vector>
using namespace std;

class RadixNode
{
public:
	unsigned char Label;
	bool Check;
	int Childs;
	RadixNode* Parent;
	RadixNode* Child[256];
	RadixNode()
	{
		Label = '\0';
		Childs = 0;
		Check = false;
		Parent = NULL;
		for (int i=0; i<256; i++) Child[i] = NULL;
	}
	void Print(RadixNode* &n, RadixNode* &p, vector<char> &ps);
};

class RadixTreeDictionary
{
private:
	RadixNode* Root;
	vector<char> PrintStack;
public:
	RadixTreeDictionary();
	void Insert(string Word);
	bool Search(string Word);
	bool Delete(string Word);
	void Print() { Root->Print(Root, Root, PrintStack); }
};
