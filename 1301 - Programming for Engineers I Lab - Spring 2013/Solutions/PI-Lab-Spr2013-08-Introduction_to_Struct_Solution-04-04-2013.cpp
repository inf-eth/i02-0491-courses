#include <iostream>
#include <cstdlib>
using namespace std;

// StudentInfo definition
struct StudentInfo
{
	char name[20];
	int Age;
	float CGPA;
	char Gender;
};
void Input(StudentInfo& S)
{
	cout << "Enter name: ";
	cin.getline(S.name, 20);
	cout << "Enter age: ";
	cin >> S.Age;
	cout << "Enter CGPA: ";
	cin >> S.CGPA;
	cout << "Enter gender (M/F): ";
	cin >> S.Gender;
}
void Display(const StudentInfo& S)
{
	switch (S.Gender)
	{
		case 'M':
			cout << "Name: Mr. " << S.name << endl;
			break;
		case 'F':
			cout << "Name: Ms. " << S.name << endl;
			break;
	}
	cout << "Age: " << S.Age << endl;
	cout << "CGPA: " << S.CGPA << endl;
}

void SquareArray(int* array, int size)
{
	for (int i=0; i<size; i++)
		array[i] = array[i] * array[i];
}

int main()
{
	// Question no. 1
	StudentInfo S;
	cout << "Enter student info: " << endl;
	Input(S);
	cout << "Student info is: " << endl;
	Display(S);

	// Question no. 2
	int size;
	cout << "Enter size: ";
	cin >> size;
	int* Data;
	Data = new int[size];
	for (int i=0; i<size; i++)
		Data[i] = rand()%6;

	SquareArray(Data, size);
	for (int i=0; i<size; i++)
		cout << Data[i] << " ";
	cout << endl;

	return 0;
}
