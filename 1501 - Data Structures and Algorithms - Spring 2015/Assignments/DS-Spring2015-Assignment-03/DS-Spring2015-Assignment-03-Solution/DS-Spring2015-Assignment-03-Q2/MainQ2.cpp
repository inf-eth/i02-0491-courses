#include "Queue.h"
#include "Stack.h"
#include <iostream>
using namespace std;

int main()
{
	Queue QueueObj;
	Stack StackObj;

	QueueObj.Enqueue(3);
	QueueObj.Enqueue(4);
	QueueObj.Enqueue(6);
	QueueObj.Enqueue(2);
	QueueObj.Enqueue(1);
	QueueObj.Enqueue(9);

	cout << QueueObj.Dequeue() << endl;
	cout << QueueObj.Dequeue() << endl;
	cout << QueueObj.Dequeue() << endl;
	cout << QueueObj.Dequeue() << endl;
	cout << QueueObj.Dequeue() << endl;
	cout << QueueObj.Dequeue() << endl;
	cout << QueueObj.Dequeue() << endl;
	cout << QueueObj.Dequeue() << endl;

	StackObj.Push(3);
	StackObj.Push(7);
	cout << StackObj.Pop() << endl;
	cout << StackObj.Pop() << endl;
	cout << StackObj.Pop() << endl;
	StackObj.Push(1);
	StackObj.Push(5);
	StackObj.Push(4);
	cout << StackObj.Pop() << endl;
	StackObj.Push(9);
	StackObj.Push(8);
	cout << StackObj.Pop() << endl;
	cout << StackObj.Pop() << endl;
	cout << StackObj.Pop() << endl;
	cout << StackObj.Pop() << endl;
	cout << StackObj.Pop() << endl;
	cout << StackObj.Pop() << endl;

	return 0;
}
