class QNode
{
public:
	int Data;
	QNode* Next;
};

class Queue
{
private:
	QNode* First;
	QNode* Last;
	int Size;
public:
	Queue();
	void Enqueue(int x);
	int Dequeue();
};
