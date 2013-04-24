\begin{lstlisting}[caption={Writing to text file}]
#include <iostream>
#include <fstream>		// File handling library.
using namespace std;

int main()
{
	fstream OutFile;	// File handling object.

	// Open "abc.txt" for writing (ios::out). This will overwrite existing file.
	OutFile.open("abc.txt", ios::out);
	OutFile << "Hello world?" << endl;
	OutFile << "Some numbers: 2 3 7 11 13.33 -2.448" << endl;
	OutFile << "Grades: A A- B+ D C- F A+" << endl;
	OutFile.close();	// Close file.

	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Reading from text file (Creating file)}]
#include <iostream>
#include <fstream>		// File handling library.
using namespace std;

int main()
{
	int x = 3;
	float f = -2.348193f;
	char c = '^';

	fstream OutFile;	// File handling object.

	// Open "abc.txt" for writing (ios::out). This will overwrite existing file.
	OutFile.open("abc.txt", ios::out);
	OutFile << x << " " << f << " " << c << " " << endl;
	OutFile.close();	// Close file.
	
	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Reading from text file}]
#include <iostream>
#include <fstream>		// File handling library.
using namespace std;
int main()
{
	int x;
	float f;
	char c;

	fstream InFile;	// File handling object.

	// Open "abc.txt" for reading (ios::in).
	InFile.open("abc.txt", ios::in);
	InFile >> x >> f >> c;
	InFile.close();	// Close file.
	
	cout << "Data read is..." << endl;
	cout << "x = " << x << ", f = " << f << ", c = " << c << endl;

	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Reading a line from text file}]
#include <iostream>
#include <fstream>		// File handling library.
using namespace std;
int main()
{
	char Line[50];

	fstream InFile;	// File handling object.

	// Open "abc.txt" for reading (ios::in).
	InFile.open("abc.txt", ios::in);
	InFile.getline(Line, 50);
	InFile.close();	// Close file.
	
	cout << "Data read is..." << endl;
	cout << Line << endl;

	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Reading a whole text file line--by--line}]
#include <iostream>
#include <fstream>		// File handling library.
using namespace std;
int main()
{
	char Line[50];

	fstream InFile;	// File handling object.

	// Open "abc.txt" for reading (ios::in).
	InFile.open("abc.txt", ios::in);
	while(InFile)
	{
		InFile.getline(Line, 50);
		cout << "Read: " << Line << endl;
	}
	InFile.close();	// Close file.

	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Writing to binary file}]
#include <fstream>		// File handling library.
using namespace std;

int main()
{
	fstream OutFile;	// File handling object.

	int x = 7;
	double d = -1.32489;
	char c = '$';

	// Open "abc.txt" for writing in binary mode (ios::out|ios::binary). This will overwrite existing file.
	OutFile.open("abc.txt", ios::out|ios::binary);
	OutFile.write((char*)&x, sizeof(int));
	OutFile.write((char*)&d, sizeof(double));
	OutFile.write((char*)&c, sizeof(char));
	OutFile.close();	// Close file.

	return 0;
}
\end{lstlisting}

\begin{lstlisting}[caption={Reading from Binary file}]
#include <iostream>
#include <fstream>		// File handling library.
using namespace std;

int main()
{
	int x;
	double d;
	char c;

	fstream InFile;	// File handling object.

	// Open "abc.txt" for reading in binary mode (ios::in|ios::binary).
	InFile.open("abc.txt", ios::in|ios::binary);
	InFile.read((char*)&x, sizeof(int));
	InFile.read((char*)&d, sizeof(double));
	InFile.read((char*)&c, sizeof(char));
	InFile.close();	// Close file.

	cout << "x = " << x << endl;
	cout << "d = " << d << endl;
	cout << "c = " << c << endl;

	return 0;
}
\end{lstlisting}

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
