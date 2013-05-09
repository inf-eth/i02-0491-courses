\begin{lstlisting}[caption={Reading a line from text file with error checking}]
#include <iostream>
#include <fstream>		// File handling library.
using namespace std;
int main()
{
	fstream InFile;	// File handling object.

	// Open "abc.txt" for reading (ios::in).
	InFile.open("abc.txt", ios::in);

	// Checking if file opened successfully.
	if (InFile.is_open() == true)
	{
		cout << "File opened successfully." << endl;

		InFile.getline(Line, 50); // Reading a line of text from file.

		// Checking if data was read successfully.
		if (InFile.fail() == true)
			cout << "Some error occured during read operation." << endl;
		else
		{
			cout << "Data read is..." << endl;
			cout << Line << endl;
		}

		// Checking end of file.
		if (InFile.eof() == true)
			cout << "End of file was encountered during last read operation. " << endl;

		InFile.close();	// Close file.
	}
	else
	{
		cout << "Error opening file." << endl;
		return -1;
	}

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
