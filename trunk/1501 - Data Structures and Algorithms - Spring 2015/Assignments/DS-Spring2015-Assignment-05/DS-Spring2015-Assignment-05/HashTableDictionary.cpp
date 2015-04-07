#include "HashTableDictionary.h"

HashTableDictionaryChaining::HashTableDictionaryChaining(int pBucketSize)
{
	Data = new vector<string>[pBucketSize];
	CurrentSize = 0;
	BucketSize = pBucketSize;
}

HashTableDictionaryChaining::~HashTableDictionaryChaining()
{
	delete[] Data;
}

void HashTableDictionaryChaining::SetBucketSize(int pBucketSize)
{
	delete[] Data;
	Data = new vector<string>[pBucketSize];
	CurrentSize = 0;
	BucketSize = pBucketSize;
}

float HashTableDictionaryChaining::GetVariance()
{
	float var = 0;
	return var;
}

unsigned int HashTableDictionaryChaining::Hash(string Input)
{
	return 0;
}

void HashTableDictionaryChaining::Insert(string Word)
{
}

bool HashTableDictionaryChaining::Search(string Word)
{
	return false;
}

bool HashTableDictionaryChaining::Delete(string Word)
{
	return false;
}

int HashTableDictionaryChaining::PrintList()
{
	for (int i=0; i<BucketSize; i++)
	{
		cout << i << ":";
		for (int j=0; j<(int)Data[i].size(); j++)
			cout  << " -> " << Data[i][j];
		cout << endl;
	}
	return 0;
}

int HashTableDictionaryChaining::PrintList(char* filename)
{
	fstream file;
	file.open(filename, ios::out|ios::trunc);
	for (int i=0; i<BucketSize; i++)
	{
		file << i << ":";
		for (int j=0; j<(int)Data[i].size(); j++)
			file  << " -> " << Data[i][j];
		file << endl;
	}
	return 0;
}

// =====================================================================

HashTableDictionaryOpenAddressing::HashTableDictionaryOpenAddressing(int pBucketSize)
{
	Data = new string[pBucketSize];
	CurrentSize = 0;
	BucketSize = pBucketSize;
	Collisions = 0;
}

HashTableDictionaryOpenAddressing::~HashTableDictionaryOpenAddressing()
{
	delete[] Data;
}

void HashTableDictionaryOpenAddressing::SetBucketSize(int pBucketSize)
{
	delete[] Data;
	Data = new string[pBucketSize];
	CurrentSize = 0;
	BucketSize = pBucketSize;
	Collisions = 0;
}

unsigned int HashTableDictionaryOpenAddressing::Hash(string Input)
{
	return 0;
}

void HashTableDictionaryOpenAddressing::Insert(string Word)
{
}

bool HashTableDictionaryOpenAddressing::Search(string Word)
{
	return false;
}

bool HashTableDictionaryOpenAddressing::Delete(string Word)
{
	return false;
}

int HashTableDictionaryOpenAddressing::PrintList()
{
	for (int i=0; i<BucketSize; i++)
		cout << i << ": " << Data[i] << endl;
	return 0;
}

int HashTableDictionaryOpenAddressing::PrintList(char* filename)
{
	fstream file;
	file.open(filename, ios::out|ios::trunc);
	for (int i=0; i<BucketSize; i++)
		if (Data[i] != "") file << Data[i] << endl;
	return 0;
}
