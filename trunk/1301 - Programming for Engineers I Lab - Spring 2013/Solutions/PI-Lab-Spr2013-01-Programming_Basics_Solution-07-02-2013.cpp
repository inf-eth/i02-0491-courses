#include <iostream>
using namespace std;

int main()
{
	// Question No. 1.
	cout << "===================== Q1 =====================" << endl;
	bool A, B, C;

	// NOT.
	cout << "===== NOT =====" << endl;
	cout << "A | !A" << endl;
	A = 0;
	cout << A << " | " << !A << endl;
	A = 1;
	cout << A << " | " << !A << endl;
	cout << "===============" << endl;
	// AND
	cout << "===== AND =====" << endl;
	cout << "A & B = C" << endl;
	A = 0;
	B = 0;
	C = A & B;
	cout << A << " & " << B << " = " << C << endl;
	A = 0;
	B = 1;
	C = A & B;
	cout << A << " & " << B << " = " << C << endl;
	A = 1;
	B = 0;
	C = A & B;
	cout << A << " & " << B << " = " << C << endl;
	A = 1;
	B = 1;
	C = A & B;
	cout << A << " & " << B << " = " << C << endl;
	cout << "===============" << endl;
	// OR
	cout << "===== OR =====" << endl;
	cout << "A | B = C" << endl;
	A = 0;
	B = 0;
	C = A | B;
	cout << A << " | " << B << " = " << C << endl;
	A = 0;
	B = 1;
	C = A | B;
	cout << A << " | " << B << " = " << C << endl;
	A = 1;
	B = 0;
	C = A | B;
	cout << A << " | " << B << " = " << C << endl;
	A = 1;
	B = 1;
	C = A | B;
	cout << A << " | " << B << " = " << C << endl;
	cout << "===============" << endl;
	// XOR
	cout << "===== XOR =====" << endl;
	cout << "A ^ B = C" << endl;
	A = 0;
	B = 0;
	C = A ^ B;
	cout << A << " ^ " << B << " = " << C << endl;
	A = 0;
	B = 1;
	C = A ^ B;
	cout << A << " ^ " << B << " = " << C << endl;
	A = 1;
	B = 0;
	C = A ^ B;
	cout << A << " ^ " << B << " = " << C << endl;
	A = 1;
	B = 1;
	C = A ^ B;
	cout << A << " ^ " << B << " = " << C << endl;
	cout << "===============" << endl;

	// Question No. 2.
	cout << "===================== Q2 =====================" << endl;
	unsigned int Mask = 15; // Binary of 15 = 0000...00001111 which can preserve first 4 bits.
	unsigned int Result = (4&5) & Mask;
	cout << "4 & 5 = " << Result << endl;
	Result = (4|5) & Mask;
	cout << "4 | 5 = " << Result << endl;
	Result = (8<<1) & Mask;
	cout << "8<<1 = " << Result << endl;
	Result = (8>>1) & Mask;
	cout << "8>>1 = " << Result << endl;

	// Question No. 3.
	cout << "===================== Q3 =====================" << endl;
	int TotalDays;
	cout << "Enter days: ";
	cin >> TotalDays;
	int years = TotalDays / 365;
	int months = (TotalDays % 365)/30;
	int days = (TotalDays % 365)%30;
	cout << years << " years, " << months << " months and " << days << " days." << endl;

	// Question No. 3.
	cout << "===================== Q3 =====================" << endl;
	int n1, n2, n3;
	cout << "Enter three numbers: " << endl;
	cout << "n1: ";
	cin >> n1;
	cout << "n2: ";
	cin >> n2;
	cout << "n3: ";
	cin >> n3;
	int Max = n1;
	if (n2 >= n1 && n2 >= n3)
		Max = n2;
	if (n3 >= n1 && n3 >= n2)
		Max = n3;
	cout << "Max is " << Max << endl;

	return 0;
}
