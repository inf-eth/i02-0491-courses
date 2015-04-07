#include "Timer.h"
#include "IntegerArray.h"
#include "IntegerLinkedList.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int RandInt(int min, int max);

int main()
{
	IntegerArray Array;
	IntegerLinkedList LinkedList;

	Timer Watch;
	int nStart = 100000;
	int nIncrement = 100000;
	int Searches = 5000;
	int Retrievals = 5000;
	int Insertions = 5000;
	int Deletions = 5000;

	// Array Analysis
	cout << "======================= Array ====================" << endl;
	for (int n=nStart; n<MAXSIZE; n=n+nIncrement)
	{
		cout << "---------------------- n=" << n << "--------------------" << endl;
		Array.MakeNULL();
		srand(n);
		for (int i=0; i<n; i++)
		{
			int Data = RandInt(0,n-1);
			Array.Insert(Data, Array.GetSize());
		}

		srand(n);
		Watch.StartTimer();
		int Found = 0;
		for (int i=0; i<Searches; i++)
		{
			int Data = RandInt(0,n);
			if (Array.Locate(Data) != -1)
				Found++;
		}
		cout << "Time for search:   " << Watch.GetElapsedTime() << " seconds. Successful: " << Found << "." << endl;

		Watch.StartTimer();
		int Retrieval = 0;
		for (int i=0; i<Retrievals; i++)
		{
			int Index = RandInt(0,n-1);
			Array.Retrieve(Index);
				Retrieval++;
		}
		cout << "Time for retrieve: " << Watch.GetElapsedTime() << " seconds. Retrievals: " << Retrieval << "." << endl;

		Watch.StartTimer();
		for (int i=0; i<Insertions; i++)
		{
			int Data = RandInt(0,n);
			int Index = Array.GetSize()==0 ? 0 : RandInt(0, Array.GetSize());
			Array.Insert(Data, Index);
		}
		cout << "Time for insert:   " << Watch.GetElapsedTime() << " seconds." << endl;

		Watch.StartTimer();
		int Deleted = 0;
		for (int i=0; i<Deletions; i++)
		{
			int Index = RandInt(0,n-1);
			if (Array.Delete(Index) == 0)
				Deleted++;
		}
		cout << "Time for delete:   " << Watch.GetElapsedTime() << " seconds. Deletions: " << Deleted << "." << endl;

		// Setting up for purge.
		Array.MakeNULL();
		for (int i=0; i<n; i++)
		{
			int Data = rand()%100;
			Array.Insert(Data, Array.GetSize());
		}
		Watch.StartTimer();
		for (int i=0; i<5; i++)
			Array.Purge(rand()%100);
		cout << "Time for purge:    " << Watch.GetElapsedTime() << " seconds. " << endl;
	}

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
		int Found = 0;
		for (int i=0; i<Searches; i++)
		{
			int Data = RandInt(0,n);
			if (LinkedList.Locate(Data) != -1)
				Found++;
		}
		cout << "Time for search:   " << Watch.GetElapsedTime() << " seconds. Successful: " << Found << "." << endl;

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

		// Setting up for purge.
		LinkedList.MakeNULL();
		for (int i=0; i<n; i++)
		{
			int Data = rand()%100;
			LinkedList.Insert(Data, 0);
		}
		Watch.StartTimer();
		for (int i=0; i<5; i++)
			LinkedList.Purge(rand()%100);
		cout << "Time for purge:    " << Watch.GetElapsedTime() << " seconds. " << endl;
	}
	return 0;
}

int RandInt(int min, int max)
{
	return (int)(((float)rand()/RAND_MAX)*(float)max)+min;
}
