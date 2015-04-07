#define NULL 0
class DNode
{
public:
	int Data;
	DNode* Next;
	DNode* Previous;
};

class IntegerDoublyLinkedList
{
private:
	DNode* First;
	DNode* Last;
	int CurrentSize;
public:
	IntegerDoublyLinkedList();
	~IntegerDoublyLinkedList();
	int GetSize() { return CurrentSize; }
	int Insert(int x, int p);
	int Delete(int p);
	int Retrieve(int p);
	int MakeNULL();
	int PrintList();
	int PrintList(char* filename);
};
