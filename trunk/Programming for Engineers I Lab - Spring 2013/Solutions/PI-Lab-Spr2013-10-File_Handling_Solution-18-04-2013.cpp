#include <iostream>
#include <fstream>
using namespace std;

struct Item
{
	char Type;
	float Weight;
	int Price;
};

void Input(Item& I)
{
	cout << "Enter Item data: " << endl;
	cout << "Type (A/B/C/D): ";
	cin >> I.Type;
	cout << "Weight: ";
	cin >> I.Weight;
	cout << "Price: ";
	cin >> I.Price;
}

void Display(Item& I)
{
	cout << "Type: " << I.Type << endl;
	cout << "Weight: " << I.Weight << endl;
	cout << "Price: " << I.Price << endl;
}

int main()
{
	char Question;
	cout << "Select question: " << endl
		 << "1. Write to text file." << endl
		 << "2. Read text file." << endl
		 << "3. Write to binary file." << endl
		 << "4. Read binary file." << endl;
	cout << ">>";
	cin >> Question;
	switch (Question)
	{
		case '1':
		{
			// Question No. 1.
			cout << "===================== Q1 =====================" << endl;
			Item temp;
			char choice = 'y';
			fstream file;
			file.open("ItemDataText.txt", ios::out|ios::app);
			cout << "Enter item data to write to file." << endl;
			while (choice == 'y')
			{
				Input(temp);
				file << temp.Type << " " << temp.Weight << " " << temp.Price << endl;
				cout << "Continue (y/n): ";
				cin >> choice;
			}
			file.close();
			break;
		}
		case '2':
		{
			// Question No. 2.
			cout << "===================== Q2 =====================" << endl;
			cout << "Displaying text file data." << endl;
			Item temp;
			fstream file;
			file.open("ItemDataText.txt", ios::in);
			if (file.is_open() == false)
				cout << "Error opening file 'ItemDataText.txt'..." << endl;
			else
			{
				while (true)
				{
					// Read file.
					file >> temp.Type >> temp.Weight >> temp.Price;

					// If input operation failed.
					if (file.fail() == true)
						break;

					// Display read data.
					Display(temp);

					// If end of file reached.
					if (file.eof() == true)
						break;
				}
			}
			break;
		}
		case '3':
		{
			// Question No. 3.
			cout << "===================== Q3 =====================" << endl;
			Item temp;
			char choice = 'y';
			fstream file;
			file.open("ItemDataBinary.txt", ios::out|ios::binary|ios::app);
			cout << "Enter item data to write to file." << endl;
			while (choice == 'y')
			{
				Input(temp);
				file.write((char*)&temp, sizeof(temp));
				cout << "Continue (y/n): ";
				cin >> choice;
			}
			file.close();
			break;
		}
		case '4':
		{
			// Question No. 4.
			cout << "===================== Q4 =====================" << endl;
			cout << "Displaying binary file data." << endl;
			Item temp;
			fstream file;
			file.open("ItemDataBinary.txt", ios::in);
			if (file.is_open() == false)
				cout << "Error opening file 'ItemDataBinary.txt'..." << endl;
			else
			{
				while (true)
				{
					// Read file.
					file.read((char*)&temp, sizeof(temp));

					// If input operation failed.
					if (file.fail() == true)
						break;

					// Display read data.
					Display(temp);

					// If end of file reached.
					if (file.eof() == true)
						break;
				}
			}
			break;
		}
		default:
		{
			cout << "Invalid choice..." << endl;
			break;
		}
	}

	return 0;
}
