#include "ArrayDictionary.h"
#include "BinarySearchTreeDictionary.h"
#include "HashTableDictionary.h"
#include "LinkedListDictionary.h"
#include "RadixTreeDictionary.h"
#include "Timer.h"
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void LoadWordList(vector<string> &List, const char* filename, int n);

int main()
{
	vector<string> WordList;
	Timer Watch;
	int MaxInsert = 50000;
	int MaxSearch = 100000;
	int MaxDelete= 100000;
	int Insertions = 10000;
	int Searches = 10000;
	int Deletions = 10000;

	// Insertion Test.
	LoadWordList(WordList, "en-GB.insert.dic", MaxInsert);
	for (int n=10000; n<=MaxInsert; n=n+10000)
	{
		ArrayDictionary ArrayObj;
		LinkedListDictionary LinkedListObj;
		BinarySearchTreeDictionary TreeObj;
		HashTableDictionaryChaining HashChainObj(2*n);
		HashTableDictionaryOpenAddressing HashOpenObj(2*n);

		for (int i=0; i<n; i++)
		{
			ArrayObj.Insert(WordList[i]);
			LinkedListObj.Insert(WordList[i]);
			TreeObj.Insert(WordList[i]);
			HashChainObj.Insert(WordList[i]);
			HashOpenObj.Insert(WordList[i]);
		}

		cout << "================ n: " << n << " =================" << endl;
		Watch.StartTimer();
		// Array Insertion Test
		for (int i=0; i<Insertions; i++)
			ArrayObj.Insert(WordList[i]);
		cout << "Array insertion time: " << Watch.GetElapsedTime() << " seconds." << endl;

		Watch.StartTimer();
		// LinkedList Insertion Test
		for (int i=0; i<Insertions; i++)
			LinkedListObj.Insert(WordList[i]);
		cout << "Linked list insertion time: " << Watch.GetElapsedTime() << " seconds." << endl;

		Watch.StartTimer();
		// Binary Search Tree Insertion Test
		for (int i=0; i<Insertions; i++)
			TreeObj.Insert(WordList[i]);
		cout << "Binary search tree insertion time: " << Watch.GetElapsedTime() << " seconds." << endl;

		Watch.StartTimer();
		// Hash Table (Chaining) Insertion Test
		for (int i=0; i<Insertions; i++)
			HashChainObj.Insert(WordList[i]);
		cout << "Hash table (chaining) insertion time: " << Watch.GetElapsedTime() << " seconds." << endl;
		cout << "Variance = " << HashChainObj.GetVariance() << endl;

		Watch.StartTimer();
		// Hash Table (Open addressing) Insertion Test
		for (int i=0; i<Insertions; i++)
			HashOpenObj.Insert(WordList[i]);
		cout << "Hash table (open addressing) insertion time: " << Watch.GetElapsedTime() << " seconds." << endl;
	}

	// Search Test.
	LoadWordList(WordList, "en-GB.search.dic", MaxSearch);
	for (int n=10000; n<=MaxSearch; n=n+10000)
	{
		ArrayDictionary ArrayObj;
		LinkedListDictionary LinkedListObj;
		BinarySearchTreeDictionary TreeObj;
		HashTableDictionaryChaining HashChainObj(2*n);
		HashTableDictionaryOpenAddressing HashOpenObj(2*n);

		for (int i=0; i<n; i++)
		{
			ArrayObj.Insert(WordList[i]);
			LinkedListObj.Insert(WordList[i]);
			TreeObj.Insert(WordList[i]);
			HashChainObj.Insert(WordList[i]);
			HashOpenObj.Insert(WordList[i]);
		}

		cout << "================ n: " << n << " =================" << endl;
		Watch.StartTimer();
		// Array Search Test
		for (int i=0; i<Searches; i++)
			ArrayObj.Search(WordList[i]);
		cout << "Array search time: " << Watch.GetElapsedTime() << " seconds." << endl;

		Watch.StartTimer();
		// LinkedList Search Test
		for (int i=0; i<Searches; i++)
			LinkedListObj.Search(WordList[i]);
		cout << "Linked list search time: " << Watch.GetElapsedTime() << " seconds." << endl;

		Watch.StartTimer();
		// Binary Search Tree search Test
		for (int i=0; i<Searches; i++)
			TreeObj.Search(WordList[i]);
		cout << "Binary search tree search time: " << Watch.GetElapsedTime() << " seconds." << endl;

		Watch.StartTimer();
		// Hash Table (Chaining) Search Test
		for (int i=0; i<Searches; i++)
			HashChainObj.Search(WordList[i]);
		cout << "Hash table (chaining) search time: " << Watch.GetElapsedTime() << " seconds." << endl;

		Watch.StartTimer();
		// Hash Table (Open addressing) Search Test
		for (int i=0; i<Searches; i++)
			HashOpenObj.Search(WordList[i]);
		cout << "Hash table (open addressing) search time: " << Watch.GetElapsedTime() << " seconds." << endl;
	}

	// Deletion Test.
	LoadWordList(WordList, "en-GB.delete.dic", MaxDelete);
	for (int n=10000; n<=MaxDelete; n=n+10000)
	{
		ArrayDictionary ArrayObj;
		LinkedListDictionary LinkedListObj;
		BinarySearchTreeDictionary TreeObj;
		HashTableDictionaryChaining HashChainObj(2*n);
		HashTableDictionaryOpenAddressing HashOpenObj(2*n);

		for (int i=0; i<n; i++)
		{
			ArrayObj.Insert(WordList[i]);
			LinkedListObj.Insert(WordList[i]);
			TreeObj.Insert(WordList[i]);
			HashChainObj.Insert(WordList[i]);
			HashOpenObj.Insert(WordList[i]);
		}

		cout << "================ n: " << n << " =================" << endl;
		Watch.StartTimer();
		// Array Delete Test
		for (int i=0; i<Deletions; i++)
			ArrayObj.Delete(WordList[i]);
		cout << "Array delete time: " << Watch.GetElapsedTime() << " seconds." << endl;

		Watch.StartTimer();
		// LinkedList Delete Test
		for (int i=0; i<Deletions; i++)
			LinkedListObj.Delete(WordList[i]);
		cout << "Linked list delete time: " << Watch.GetElapsedTime() << " seconds." << endl;

		Watch.StartTimer();
		// Tree Delete Test
		for (int i=0; i<Deletions; i++)
			TreeObj.Delete(WordList[i]);
		cout << "Tree delete time: " << Watch.GetElapsedTime() << " seconds." << endl;

		Watch.StartTimer();
		// Hash Table (Chaining) Delete Test
		for (int i=0; i<Deletions; i++)
			HashChainObj.Delete(WordList[i]);
		cout << "Hash table (chaining) delete time: " << Watch.GetElapsedTime() << " seconds." << endl;

		Watch.StartTimer();
		// Hash Table (Open addressing) Delete Test
		for (int i=0; i<Deletions; i++)
			HashOpenObj.Delete(WordList[i]);
		cout << "Hash table (open addressing) delete time: " << Watch.GetElapsedTime() << " seconds." << endl;
	}
}

void LoadWordList(vector<string> &List, const char* filename, int n)
{
	List.clear();
	fstream file;
	file.open(filename);
	for (int i=0; i<n; i++)
	{
		string temp;
		getline(file, temp);
		if (file.eof())
			break;
		List.push_back(temp);
	}
}
