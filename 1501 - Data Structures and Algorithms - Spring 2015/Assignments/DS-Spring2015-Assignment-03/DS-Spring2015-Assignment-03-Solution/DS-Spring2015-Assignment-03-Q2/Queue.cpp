#include "Queue.h"
#define NULL 0
Queue::Queue()
{
	First = Last = NULL;
	Size = 0;
}

void Queue::Enqueue(int x)
{
	if (Size == 0)
	{
		First = new QNode;
		First->Data = x;
		First->Next = NULL;
		Last = First;
	}
	else
	{
		QNode* temp = new QNode;
		temp->Data = x;
		temp->Next = NULL;
		Last->Next = temp;
		Last = temp;
	}
	Size++;
}

int Queue::Dequeue()
{
	if (Size == 0)
		return -1;
	else
	{
		int x = First->Data;
		QNode* temp = First;
		First = First->Next;
		delete temp;
		Size--;
		return x;
	}
}
