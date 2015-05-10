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
	float mean = 0;
	float var = 0;

	for (int i=0; i<BucketSize; i++)
		mean = mean + (float)Data[i].size();
	mean = mean / BucketSize;

	for (int i=0; i<BucketSize; i++)
		var = var + pow((float)Data[i].size() - mean, 2);
	var = var / BucketSize;

	return var;
}

unsigned int HashTableDictionaryChaining::Hash(string Input)
{
	int h = 0x83fd0ae1;
	bitset<8> c;
	bitset<5> fi;
	bitset<32> t = h;
	for (int i=0; i<(int)Input.size(); i++)
	{
		fi[0] = c[7];
		fi[1] = c[2];
		fi[2] = t[19];
		fi[3] = c[0];
		fi[4] = c[5];
		t.flip(fi.to_ulong());

		fi[0] = c[1];
		fi[1] = c[4];
		fi[2] = t[7];
		fi[3] = c[6];
		fi[4] = c[3];
		t.flip(fi.to_ulong());

		fi[0] = c[2];
		fi[1] = c[7];
		fi[2] = t[21];
		fi[3] = c[1];
		fi[4] = c[3];
		t.flip(fi.to_ulong());

		fi[0] = c[6];
		fi[1] = c[4];
		fi[2] = t[0];
		fi[3] = c[5];
		fi[4] = c[0];
		t.flip(fi.to_ulong());

		c = Input[i];

		t[0] = t[23] ^ c[7];
		t[1] = t[1] ^ c[3];
		t[2] = t[29] ^ c[1];
		t[3] = t[15] ^ c[0];
		t[4] = t[10] ^ c[5];
		t[5] = t[5] ^ c[2];
		t[6] = t[21] ^ c[6];
		t[7] = t[8] ^ c[4];

		t[8] = t[3] ^ c[1];
		t[9] = t[17] ^ c[3];
		t[10] = t[9] ^ c[7];
		t[11] = t[28] ^ c[2];
		t[12] = t[12] ^ c[4];
		t[13] = t[4] ^ c[6];
		t[14] = t[22] ^ c[5];
		t[15] = t[2] ^ c[0];

		t[16] = t[7] ^ c[4];
		t[17] = t[31] ^ c[0];
		t[18] = t[19] ^ c[5];
		t[19] = t[11] ^ c[6];
		t[20] = t[26] ^ c[2];
		t[21] = t[16] ^ c[3];
		t[22] = t[27] ^ c[7];
		t[23] = t[12] ^ c[1];

		t[24] = t[20] ^ c[2];
		t[25] = t[6] ^ c[1];
		t[26] = t[18] ^ c[6];
		t[27] = t[24] ^ c[3];
		t[28] = t[14] ^ c[0];
		t[29] = t[20] ^ c[7];
		t[30] = t[25] ^ c[4];
		t[31] = t[13] ^ c[5];

		fi[0] = c[7];
		fi[1] = c[2];
		fi[2] = t[19];
		fi[3] = c[0];
		fi[4] = c[5];
		t.flip(fi.to_ulong());

		fi[0] = c[1];
		fi[1] = c[4];
		fi[2] = t[7];
		fi[3] = c[6];
		fi[4] = c[3];
		t.flip(fi.to_ulong());

		fi[0] = c[2];
		fi[1] = c[7];
		fi[2] = t[21];
		fi[3] = c[1];
		fi[4] = c[3];
		t.flip(fi.to_ulong());

		fi[0] = c[6];
		fi[1] = c[4];
		fi[2] = t[0];
		fi[3] = c[5];
		fi[4] = c[0];
		t.flip(fi.to_ulong());
	}
	return t.to_ulong();
}

void HashTableDictionaryChaining::Insert(string Word)
{
	unsigned int Index = Hash(Word) % BucketSize;
	for (int i=0; i<(int)Data[Index].size(); i++)
	{
		if (Word == Data[Index][i])
			return;
	}
	Data[Index].push_back(Word);
	CurrentSize++;
}

bool HashTableDictionaryChaining::Search(string Word)
{
	unsigned int Index = Hash(Word) % BucketSize;
	for (int i=0; i<(int)Data[Index].size(); i++)
	{
		if (Word == Data[Index][i])
			return true;
	}
	return false;
}

bool HashTableDictionaryChaining::Delete(string Word)
{
	unsigned int Index = Hash(Word) % BucketSize;
	for (int i=0; i<(int)Data[Index].size(); i++)
	{
		if (Word == Data[Index][i])
		{
			Data[Index].erase(Data[Index].begin()+i);
			CurrentSize--;
			return true;
		}
	}
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
	int h = 0x83fd0ae1;
	bitset<8> c;
	bitset<5> fi;
	bitset<32> t = h;
	for (int i=0; i<(int)Input.size(); i++)
	{
		fi[0] = c[7];
		fi[1] = c[2];
		fi[2] = t[19];
		fi[3] = c[0];
		fi[4] = c[5];
		t.flip(fi.to_ulong());

		fi[0] = c[1];
		fi[1] = c[4];
		fi[2] = t[7];
		fi[3] = c[6];
		fi[4] = c[3];
		t.flip(fi.to_ulong());

		fi[0] = c[2];
		fi[1] = c[7];
		fi[2] = t[21];
		fi[3] = c[1];
		fi[4] = c[3];
		t.flip(fi.to_ulong());

		fi[0] = c[6];
		fi[1] = c[4];
		fi[2] = t[0];
		fi[3] = c[5];
		fi[4] = c[0];
		t.flip(fi.to_ulong());

		c = Input[i];

		t[0] = t[23] ^ c[7];
		t[1] = t[1] ^ c[3];
		t[2] = t[29] ^ c[1];
		t[3] = t[15] ^ c[0];
		t[4] = t[10] ^ c[5];
		t[5] = t[5] ^ c[2];
		t[6] = t[21] ^ c[6];
		t[7] = t[8] ^ c[4];

		t[8] = t[3] ^ c[1];
		t[9] = t[17] ^ c[3];
		t[10] = t[9] ^ c[7];
		t[11] = t[28] ^ c[2];
		t[12] = t[12] ^ c[4];
		t[13] = t[4] ^ c[6];
		t[14] = t[22] ^ c[5];
		t[15] = t[2] ^ c[0];

		t[16] = t[7] ^ c[4];
		t[17] = t[31] ^ c[0];
		t[18] = t[19] ^ c[5];
		t[19] = t[11] ^ c[6];
		t[20] = t[26] ^ c[2];
		t[21] = t[16] ^ c[3];
		t[22] = t[27] ^ c[7];
		t[23] = t[12] ^ c[1];

		t[24] = t[20] ^ c[2];
		t[25] = t[6] ^ c[1];
		t[26] = t[18] ^ c[6];
		t[27] = t[24] ^ c[3];
		t[28] = t[14] ^ c[0];
		t[29] = t[20] ^ c[7];
		t[30] = t[25] ^ c[4];
		t[31] = t[13] ^ c[5];

		fi[0] = c[7];
		fi[1] = c[2];
		fi[2] = t[19];
		fi[3] = c[0];
		fi[4] = c[5];
		t.flip(fi.to_ulong());

		fi[0] = c[1];
		fi[1] = c[4];
		fi[2] = t[7];
		fi[3] = c[6];
		fi[4] = c[3];
		t.flip(fi.to_ulong());

		fi[0] = c[2];
		fi[1] = c[7];
		fi[2] = t[21];
		fi[3] = c[1];
		fi[4] = c[3];
		t.flip(fi.to_ulong());

		fi[0] = c[6];
		fi[1] = c[4];
		fi[2] = t[0];
		fi[3] = c[5];
		fi[4] = c[0];
		t.flip(fi.to_ulong());
	}
	return t.to_ulong();
}

void HashTableDictionaryOpenAddressing::Insert(string Word)
{
	unsigned int Index = Hash(Word) % BucketSize;
	for (int i=0; i<(int)BucketSize/2+1; i++)
	{
		if (Data[Index] == Word)
			return;
		else if (Data[Index] == "")
		{
			Data[Index] = Word;
			CurrentSize++;
			return;
		}
		else
		{
			Index = (Index + Hash(to_string((unsigned long long)i))) % BucketSize;
			Collisions++;
		}
	}
	//cout << "* Insert aborted *" << endl;
}

bool HashTableDictionaryOpenAddressing::Search(string Word)
{
	unsigned int Index = Hash(Word) % BucketSize;
	for (int i=0; i<(int)BucketSize/2+1; i++)
	{
		if (Data[Index] == Word)
			return true;
		else
			Index = (Index + Hash(to_string((unsigned long long)i))) % BucketSize;
	}
	return false;
}

bool HashTableDictionaryOpenAddressing::Delete(string Word)
{
	unsigned int Index = Hash(Word) % BucketSize;
	for (int i=0; i<(int)BucketSize/2+1; i++)
	{
		if (Data[Index] == Word)
		{
			Data[Index] = "";
			CurrentSize--;
			return true;
		}
		else
			Index = (Index + Hash(to_string((unsigned long long)i))) % BucketSize;
	}
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
