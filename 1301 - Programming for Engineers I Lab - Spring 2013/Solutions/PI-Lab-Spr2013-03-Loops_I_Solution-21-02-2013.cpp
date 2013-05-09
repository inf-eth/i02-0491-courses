#include <iostream>
using namespace std;

int main()
{
	// Question No. 1.
	cout << "===================== Q1 =====================" << endl;
	cout << "Squares of first 10 numbers are: " << endl;
	for (int i=1; i<11; i++)
		cout << i*i << " ";
	cout << endl;

	// Question No. 2.
	cout << "===================== Q2 =====================" << endl;
	int n1, n2, diff;
	char c = 'n';
	while (c == 'n')
	{
		cout << "Enter two numbers: " << endl;
		cout << "n1: ";
		cin >> n1;
		cout << "n2: ";
		cin >> n2;
		diff = n1-n2;
		if (diff >= 0)
		{
			cout << "Difference is positive (" << diff << "). Do you want to quit (y/n)? ";
			cin >> c;
		}
		else
		{
			cout << "Difference is negative (" << diff << "). Quitting..." << endl;
			c = 'y';
		}
	}

	// Question No. 3.
	cout << "===================== Q3 =====================" << endl;
	int height;
	cout << "Enter height: ";
	cin >> height;
	for (int i=0; i<height; i++)
	{
		for (int j=0; j<=i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}

	// Question No. 4.
	cout << "===================== Q4 =====================" << endl;
	int unit, ten, hundred;
	for (int num=100; num<1000; num++)
	{
		hundred = num/100;
		ten = (num/10)%10;
		unit = num%10;
		int test = hundred*hundred*hundred + ten*ten*ten + unit*unit*unit;
		if (num == test)
			cout << num << " is Armstrong number." << endl;
	}

	// Question No. 5.
	cout << "===================== Q5 =====================" << endl;
	cout << "Enter height: ";
	cin >> height;
	// Variation 1.
	for (int i=0; i<height; i++)
	{
		for (int j=0; j<=i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	// Variation 2.
	for (int i=0; i<height; i++)
	{
		for (int j=height-i; j>0; j--)
		{
			cout << "*";
		}
		cout << endl;
	}
	// Variation 3.
	for (int i=0; i<height; i++)
	{
		for (int j=0; j<height; j++)
		{
			if ((height-j)<=i+1)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}
	// Variation 4.
	for (int i=0; i<height; i++)
	{
		for (int j=0; j<height; j++)
		{
			if (j>=i)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}
	return 0;
}
