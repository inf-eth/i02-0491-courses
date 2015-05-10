#include <string>
#include <vector>
#include <bitset>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

class HashTableDictionaryChaining
{
private:
	vector<string>* Data;
	int CurrentSize;
	int BucketSize;
	float Variance;
public:
	HashTableDictionaryChaining(int pBucketSize);
	~HashTableDictionaryChaining();
	void SetBucketSize(int pBucketSize);
	int GetSize() { return CurrentSize; }
	float GetVariance();
	float GetLoadFactor() { return (float)CurrentSize/BucketSize; }
	unsigned int Hash(string Input);
	void Insert(string Word);
	bool Search(string Word);
	bool Delete(string Word);
	int PrintList();
	int PrintList(char* filename);
};

class HashTableDictionaryOpenAddressing
{
private:
	string* Data;
	int CurrentSize;
	int BucketSize;
	int Collisions;
public:
	HashTableDictionaryOpenAddressing(int pBucketSize);
	~HashTableDictionaryOpenAddressing();
	void SetBucketSize(int pBucketSize);
	int GetSize() { return CurrentSize; }
	int GetCollisions() { return Collisions; }
	float GetLoadFactor() { return (float)CurrentSize/BucketSize; }
	unsigned int Hash(string Input);
	void Insert(string Word);
	bool Search(string Word);
	bool Delete(string Word);
	int PrintList();
	int PrintList(char* filename);
};
