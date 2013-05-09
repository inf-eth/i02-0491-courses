#include <iostream>
#include <cstring>
using namespace std;

typedef char String[20];
enum Fruit{apple, orange, strawberry};
union MixTypes
{
	int x;
	double d;
	char c;
};

int main()
{
	// Question No. 1.
	cout << "===================== Q1 =====================" << endl;
	String str;
	cout << "Enter a string: ";
	if (cin.peek() == '\n') cin.ignore();
	cin.getline(str, 20);
	cout << "String is: " << str << endl;

	// Question No. 2.
	cout << "===================== Q2 =====================" << endl;
	int choice = 0;
	cout << "Select a fruit: " << endl
		 << "0. Apple, 1. Orange, 3. Strawberry" << endl;
	cout << ">>";
	cin >> choice;
	Fruit test = (Fruit)choice;

	if (test == apple)
		cout << "Apple selected." << endl;
	if (test == orange)
		cout << "Orange selected." << endl;
	if (test == strawberry)
		cout << "Strawberry selected." << endl;

	// Question No. 3.
	cout << "===================== Q3 =====================" << endl;
	MixTypes t;
	t.x = 65;
	cout << "Char value after settign t.x = 65 is " << t.c << endl;

	return 0;
}
