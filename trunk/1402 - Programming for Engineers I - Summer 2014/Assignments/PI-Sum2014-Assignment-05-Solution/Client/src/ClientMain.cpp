#include <Client.h>
#include <cstdlib>			// exit(), atoi()
#include <cstring>			// strlen()
#include <iostream>
#include <fstream>
using namespace std;

struct StudentRecord
{
	char Name[40];
	int Roll;
	int Age;
	float CGPA;
	int CourseMarks[3];
};

void Input(StudentRecord&);
void Display(StudentRecord&);

int main()
{
	// Create Client object.
	Client ClientObj;

	// Create Client Socket.
	ClientObj.CreateSocket(TCPSOCKET);
	ClientObj.SetSocketOptions();

	// Initialise and bind Client address.
	ClientObj.InitialiseAddress(DEFAULTCLIENTPORT);	// Without any argument default port will be chosen.
	ClientObj.Bind();

	char ServerName[24];
	int ServerPort;
	cout << "Enter Server name or IP: "; // Use localhost or 127.0.0.1 for local server.
	cin.getline(ServerName, 24);
	cout << "Enter Server port: ";
	cin >> ServerPort;

	// Connect to Server. Server name/IP and port are provided as arguments.
	ClientObj.Connect(ServerName, ServerPort);

	// Authorisation
	int a = 0;
	char pass[20];
	while (true)
	{
		cout << "Enter password: ";
		if (cin.peek()=='\n') cin.ignore();
		cin.getline(pass, 20);
		ClientObj.Send((void*)pass, strlen(pass)+1);
		ClientObj.Receive((void*)&a, sizeof(int));
		if (a==1)
		{
			cout << "Successful login!" << endl;
			break;
		}
		else
			cout << "Incorrect password!" << endl;
	}

	// Send and receive.
	StudentRecord temp;
	int choice = -1;
	char ReceiveBuffer[512];

	while (choice != 6)
	{
		ClientObj.Receive((void*)ReceiveBuffer, 512);
		cout << ReceiveBuffer << endl << ">>";
		cin >> choice;
		ClientObj.Send((void*)&choice, sizeof(int));

		switch (choice)
		{
		case 1:
			{
				Input(temp);
				ClientObj.Send((void*)&temp, sizeof(StudentRecord));
				break;
			}
		case 2:
			{
				int NoOfRecords;
				ClientObj.Receive((void*)&NoOfRecords, sizeof(int));
				cout << "Total records: " << NoOfRecords << endl;
				for (int i=0; i<NoOfRecords; i++)
				{
					ClientObj.Receive((void*)&temp, sizeof(StudentRecord));
					cout << "===== Record No: " << i+1 << " =====" << endl;
					Display(temp);
				}
				break;
			}
		case 3:
			{
				int found;
				char SearchName[40];
				cout << "Enter name to search: ";
				if (cin.peek()=='\n') cin.ignore();
				cin.getline(SearchName, 40);
				ClientObj.Send((void*)SearchName, strlen(SearchName)+1);
				ClientObj.Receive((void*)&found, sizeof(int));
				if (found==1)
				{
					cout << "Record found!" << endl;
					ClientObj.Receive((void*)&temp, sizeof(StudentRecord));
					Display(temp);
				}
				else
					cout << "Record was not found!" << endl;

				break;
			}
		case 4:
			{
				int found;
				char SearchName[40];
				cout << "Enter name to search: ";
				if (cin.peek()=='\n') cin.ignore();
				cin.getline(SearchName, 40);
				ClientObj.Send((void*)SearchName, strlen(SearchName)+1);
				ClientObj.Receive((void*)&found, sizeof(int));
				if (found==1)
				{
					cout << "Record found!" << endl;
					cout << "Enter updated data: " << endl;
					Input(temp);
					ClientObj.Send((void*)&temp, sizeof(StudentRecord));
					cout << "Record was updated!" << endl;
				}
				else
					cout << "Record was not found!" << endl;

				break;
			}
		case 5:
			{
				fstream File;
				File.open("received_Course_Outline.pdf", ios::out|ios::binary);
				int filesize;
				ClientObj.Receive((void*)&filesize, sizeof(int));
				cout << "Filesize: " << filesize << "B (" << (float)filesize/1024 << "KB)" << endl;
				char c;
				for (int i=0; i<filesize; i++)
				{
					ClientObj.Receive((void*)&c, sizeof(char));
					File.write((char*)&c, sizeof(char));
				}
				File.close();
				break;
			}
		case 6:
			break;
		}
	}

	ClientObj.CloseClientSocket();

	return 0;
}

void Input(StudentRecord& S)
{
	cout << "Enter name: ";
	if (cin.peek()=='\n') cin.ignore();
	cin.getline(S.Name, 40);
	cout << "Roll: ";
	cin >> S.Roll;
	cout << "Age: ";
	cin >> S.Age;
	cout << "CGPA: ";
	cin >> S.CGPA;
	cout << "Course 1 marks: ";
	cin >> S.CourseMarks[0];
	cout << "Course 2 marks: ";
	cin >> S.CourseMarks[1];
	cout << "Course 3 marks: ";
	cin >> S.CourseMarks[2];
}

void Display(StudentRecord& S)
{
	cout << "Name: " << S.Name << endl;
	cout << "Roll: " << S.Roll << endl;
	cout << "Age:  " << S.Age << endl;
	cout << "CGPA: " << S.CGPA << endl;
	cout << "Course 1 Marks: " << S.CourseMarks[0] << endl;
	cout << "Course 2 Marks: " << S.CourseMarks[1] << endl;
	cout << "Course 3 Marks: " << S.CourseMarks[2] << endl;
}
