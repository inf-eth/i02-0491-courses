#define NULL 0
class Node
{
public:
	int Data;
	Node* Next;
};

class IntegerLinkedList
{
	private:
	Node* First;
	int CurrentSize;
public:
	IntegerLinkedList();
	~IntegerLinkedList();
	int GetSize() { return CurrentSize; }
	int Insert(int x, int p);
	int Locate(int x);
	int Delete(int p);
	int Retrieve(int p);
	int Next(int p);
	int Previous(int p);
	int MakeNULL();
	int Last();
	int PrintList();
	int PrintList(char* filename);
	int Purge(int x);
};
