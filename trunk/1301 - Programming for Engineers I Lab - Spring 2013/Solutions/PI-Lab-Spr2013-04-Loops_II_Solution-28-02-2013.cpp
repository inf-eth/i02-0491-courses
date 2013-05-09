#include <iostream>
using namespace std;

int main()
{
	// Question No. 1.
	cout << "===================== Q1 =====================" << endl;
	int n;
	int factorial = 1;
	cout << "Enter a number to find factorial: ";
	cin >> n;
	for (int i=0; i<n; i++)
		factorial = factorial*(n-i);
	cout << "Factorial is " << factorial << endl;

	// Question No. 2.
	cout << "===================== Q2 =====================" << endl;
	float x;
	int exponent;
	float power = 1;
	cout << "Enter a number to find its power: ";
	cin >> x;
	cout << "Enter exponent: ";
	cin >> exponent;
	for (int i=0; i<exponent; i++)
		power = power * x;
	cout << x << "^" << exponent << " = " << power << endl;

	// Question No. 3.
	cout << "===================== Q3 =====================" << endl;
	float result = 0;
	cout << "Enter x: ";
	cin >> x;
	cout << "Enter number of terms: ";
	cin >> n;
	for (int t=0; t<n; t++)
	{
		factorial = 1;
		for (int i=0; i<t; i++)
			factorial = factorial*(t-i);

		power = 1;
		for (int i=0; i<t; i++)
			power = power * x;

		result = result + power/(float)factorial;
	}
	cout << "e^" << x << " = " << result << endl;

	return 0;
}
