#include "Timer.h"
#include "IntegerLinkedList.h"
#include "IntegerDoublyLinkedList.h"
#include <iostream>
#include <cstdlib>
using namespace std;

#define MAXSIZE 1000000
int RandInt(int min, int max);

int main()
{
	IntegerLinkedList LinkedList;
	IntegerDoublyLinkedList DoublyLinkedList;

	Timer Watch;
	int nStart = 100000;
	int nIncrement = 100000;
	int Searches = 5000;
	int Retrievals = 5000;
	int Insertions = 5000;
	int Deletions = 5000;


	// Linked List Analysis
	cout << endl << "======================= Linked List ====================" << endl;
	for (int n=nStart; n<MAXSIZE; n=n+nIncrement)
	{
		cout << "---------------------- n=" << n << "--------------------" << endl;
		LinkedList.MakeNULL();
		srand(n);
		for (int i=0; i<n; i++)
		{
			int Data = RandInt(0,n-1);
			LinkedList.Insert(Data, 0);
		}

		srand(n);

		Watch.StartTimer();
		int Retrieval = 0;
		for (int i=0; i<Retrievals; i++)
		{
			int Index = RandInt(0,n-1);
			LinkedList.Retrieve(Index);
				Retrieval++;
		}
		cout << "Time for retrieve: " << Watch.GetElapsedTime() << " seconds. Retrievals: " << Retrieval << "." << endl;

		Watch.StartTimer();
		for (int i=0; i<Insertions; i++)
		{
			int Data = RandInt(0,n);
			int Index = LinkedList.GetSize()==0 ? 0 : RandInt(0, LinkedList.GetSize());
			LinkedList.Insert(Data, Index);
		}
		cout << "Time for insert:   " << Watch.GetElapsedTime() << " seconds." << endl;

		Watch.StartTimer();
		int Deleted = 0;
		for (int i=0; i<Deletions; i++)
		{
			int Index = RandInt(0,n-1);
			if (LinkedList.Delete(Index) == 0)
				Deleted++;
		}
		cout << "Time for delete:   " << Watch.GetElapsedTime() << " seconds. Deletions: " << Deleted << "." << endl;
	}

	// Doubly-Linked List Analysis
	cout << endl << "======================= Doubly-Linked List ====================" << endl;
	for (int n=nStart; n<MAXSIZE; n=n+nIncrement)
	{
		cout << "---------------------- n=" << n << "--------------------" << endl;
		DoublyLinkedList.MakeNULL();
		srand(n);
		for (int i=0; i<n; i++)
		{
			int Data = RandInt(0,n-1);
			DoublyLinkedList.Insert(Data, 0);
		}

		srand(n);

		Watch.StartTimer();
		int Retrieval = 0;
		for (int i=0; i<Retrievals; i++)
		{
			int Index = RandInt(0,n-1);
			DoublyLinkedList.Retrieve(Index);
				Retrieval++;
		}
		cout << "Time for retrieve: " << Watch.GetElapsedTime() << " seconds. Retrievals: " << Retrieval << "." << endl;

		Watch.StartTimer();
		for (int i=0; i<Insertions; i++)
		{
			int Data = RandInt(0,n);
			int Index = DoublyLinkedList.GetSize()==0 ? 0 : RandInt(0, DoublyLinkedList.GetSize());
			DoublyLinkedList.Insert(Data, Index);
		}
		cout << "Time for insert:   " << Watch.GetElapsedTime() << " seconds." << endl;

		Watch.StartTimer();
		int Deleted = 0;
		for (int i=0; i<Deletions; i++)
		{
			int Index = RandInt(0,n-1);
			if (DoublyLinkedList.Delete(Index) == 0)
				Deleted++;
		}
		cout << "Time for delete:   " << Watch.GetElapsedTime() << " seconds. Deletions: " << Deleted << "." << endl;
	}
	return 0;
}

int RandInt(int min, int max)
{
	return (int)(((float)rand()/RAND_MAX)*(float)max)+min;
}
