#define MAXSIZE 1024
class Stack
{
private:
	int StackArray[MAXSIZE];
	int Size;
public:
	Stack();
	void Push(int x);
	int Pop();
};
