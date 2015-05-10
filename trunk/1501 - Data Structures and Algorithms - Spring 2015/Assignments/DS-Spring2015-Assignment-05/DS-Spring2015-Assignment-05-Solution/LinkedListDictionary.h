#include <list>
#include <string>
using namespace std;

class LinkedListDictionary
{
private:
	list<string> Data;
public:
	LinkedListDictionary();
	~LinkedListDictionary();
	int GetSize() { return (int)Data.size(); }
	void Insert(string Word);
	bool Search(string Word);
	bool Delete(string Word);
	string Retrieve(int p);
	int PrintList();
	int PrintList(char* filename);
};
