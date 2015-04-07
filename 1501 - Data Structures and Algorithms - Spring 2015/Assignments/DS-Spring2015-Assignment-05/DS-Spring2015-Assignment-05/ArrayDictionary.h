#include <vector>
#include <string>
using namespace std;

class ArrayDictionary
{
private:
	vector<string> Data;
public:
	int GetSize() { return (int)Data.size(); }
	void Insert(string Word);
	bool Search(string Word);
	bool Delete(string Word);
	string Retrieve(int p);
	int PrintList();
	int PrintList(char* filename);
};
