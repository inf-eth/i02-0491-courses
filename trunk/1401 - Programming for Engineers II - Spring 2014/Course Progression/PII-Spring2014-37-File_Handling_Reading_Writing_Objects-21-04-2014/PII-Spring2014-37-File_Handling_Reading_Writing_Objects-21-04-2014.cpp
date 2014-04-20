\begin{lstlisting}[caption={Writing an object to binary file}]
#include <iostream>
#include <fstream>		// File handling library.
using namespace std;

class StudentInfo
{
	public:
	char Name[20];
	int Age;
	float CGPA;
	char Gender;
};

int main()
{
	StudentInfo S;
	cout << "Enter student information: " << endl;
	cout << "Name: ";
	cin.getline(S.Name, 20);
	cout << "Age: ";
	cin >> S.Age;
	cout << "CGPA: ";
	cin >> S.CGPA;
	cout << "Gender (M/F): ";
	cin >> S.Gender;

	fstream OutFile;	// File handling object.

	// Open "abc.txt" for writing in binary mode (ios::out|ios::binary). This will overwrite existing file.
	OutFile.open("abc.txt", ios::out|ios::binary);
	OutFile.write((char*)&S, sizeof(StudentInfo));
	OutFile.close();	// Close file.

	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Reading an object from binary file}]
#include <iostream>
#include <fstream>		// File handling library.
using namespace std;
class StudentInfo
{
	public:
	char Name[20];
	int Age;
	float CGPA;
	char Gender;
};

int main()
{
	StudentInfo S;

	fstream InFile;	// File handling object.

	// Open "abc.txt" for reading in binary mode (ios::in|ios::binary).
	InFile.open("abc.txt", ios::in|ios::binary);
	InFile.read((char*)&S, sizeof(StudentInfo));
	InFile.close();	// Close file.

	switch (S.Gender)
	{
		case 'M':
			cout << "Name: Mr. " << S.Name << endl;
			break;
		case 'F':
			cout << "Name: Ms. " << S.Name << endl;
			break;
	}
	cout << "Age: " << S.Age << endl;
	cout << "CGPA: " << S.CGPA << endl;

	return 0;
}
\end{lstlisting}
