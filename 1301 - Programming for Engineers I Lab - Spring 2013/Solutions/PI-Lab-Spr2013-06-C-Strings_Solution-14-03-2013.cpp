#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	// Question No. 1.
	cout << "===================== Q1 =====================" << endl;
	char str[20];
	int length = 0;
	cout << "Enter a string to find length: ";
	if (cin.peek() == '\n') cin.ignore();
	cin.getline(str, 20);
	for (int i=0; i<20 && str[i]!= '\0'; i++)
		length++;
	cout << "Length of string is " << length << endl;

	
	// Question No. 2.
	cout << "===================== Q2 =====================" << endl;
	char str1[20];
	char str2[20];
	length = 0;
	cout << "Enter a string to copy: ";
	if (cin.peek() == '\n') cin.ignore();
	cin.getline(str1, 20);
	for (int i=0; str1[i] != '\0'; i++)
		length++;
	for (int i=0; i<=length; i++) // Copy '\0' character as well as string.
		str2[i] = str1[i];
	cout << "Copied string is: " << str2 << endl;

	// Question No. 3.
	cout << "===================== Q3 =====================" << endl;
	cout << "Enter a string to reverse: ";
	if (cin.peek() == '\n') cin.ignore();
	cin.getline(str, 20);
	length = 0;
	for (int i=0; str[i] != '\0'; i++)
		length++;
	char temp;
	for (int i=0; i<length/2; i++)
	{
		temp = str[i];
		str[i] = str[length-i-1];
		str[length-i-1] = temp;
	}
	cout << "Reversed string is: " << str << endl;

	// Question No. 4.
	cout << "===================== Q4 =====================" << endl;
	cout << "Enter two strings to check for match: " << endl;
	cout << "String 1: ";
	if (cin.peek() == '\n') cin.ignore();
	cin.getline(str1, 20);
	cout << "String 2: ";
	if (cin.peek() == '\n') cin.ignore();
	cin.getline(str2, 20);
	bool matchflag = true;
	for (int i=0; i<20; i++)
	{
		// If any mismatch.
		if (str1[i] != str2[i])
		{
			matchflag = false;
			break;
		}
		// If end of array length.
		if (i==19)
		{
			if (str1[i]!='\0' || str2[i] != '\0')
				matchflag = false;
			break;
		}
		// Break if NULL encountered.
		if (str1[i]=='\0' || str2[i] == '\0')
			break;
	}
	if (matchflag == true)
		cout << "Strings match." << endl;
	else
		cout << "Strings do not match." << endl;

	// Question No. 5.
	cout << "===================== Q5 =====================" << endl;
	char str3[40];
	cout << "Enter two strings to concatenate them: " << endl;
	cout << "String 1:";
	if (cin.peek() == '\n') cin.ignore();
	cin.getline(str1, 20);
	cout << "String 2:";
	if (cin.peek() == '\n') cin.ignore();
	cin.getline(str2, 20);
	length = 0;
	for (int i=0; i<20 && str1[i]!= '\0'; i++)
	{
		str3[i] = str1[i];
		length++;
	}
	for (int i=0; i<20; i++)
	{
		str3[length+i] = str2[i];
		if (str2[i] == '\0')
			break;
	}
	cout << "Concatenated string is: " << str3 << endl;

	return 0;
}
