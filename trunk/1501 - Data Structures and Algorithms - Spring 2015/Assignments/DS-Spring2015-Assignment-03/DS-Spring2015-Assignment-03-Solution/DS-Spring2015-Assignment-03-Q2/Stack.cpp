#include "Stack.h"
Stack::Stack()
{
	Size = 0;
}

void Stack::Push(int x)
{
	if (Size < MAXSIZE)
		StackArray[Size++] = x;
}

int Stack::Pop()
{
	if (Size > 0)
		return StackArray[--Size];
	else
		return -1;
}
