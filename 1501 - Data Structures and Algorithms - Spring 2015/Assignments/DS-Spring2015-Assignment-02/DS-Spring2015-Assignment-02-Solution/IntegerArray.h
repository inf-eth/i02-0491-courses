#define MAXSIZE 1000*1000
class IntegerArray
{
private:
	int* Data;
	int CurrentSize;
public:
	IntegerArray();
	~IntegerArray() { delete Data; };
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
