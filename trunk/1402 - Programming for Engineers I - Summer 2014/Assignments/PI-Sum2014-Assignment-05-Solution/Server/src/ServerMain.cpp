#include <Server.h>
#include <cstring>
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

int main()
{
	// Create Server object.
	Server ServerObj;

	// Create Server socket and set socket options.
	ServerObj.CreateSocket(TCPSOCKET);		// No argument means TCPSOCKET
	ServerObj.SetSocketOptions();

	// Initialise Server address struct and bind it with Server's socket.
	ServerObj.InitialiseAddress(6000);		// No argument here will take default port.
	ServerObj.Bind();

	// Listen for incoming connections.
	ServerObj.Listen();
	ServerObj.DisplayServerInfo();

	// Accept any incoming connections.
	ServerObj.Accept();
	ServerObj.DisplayClientInfo();

	// Authorisation.
	int a = 0;
	char pass[] = "123";
	char recvpass[20];
	while (true)
	{
		ServerObj.Receive((void*)recvpass, 20);
		if (strcmp(recvpass, pass)==0)
			a = 1;
		ServerObj.Send((void*)&a, sizeof(int));
		if (a==1)
			break;
	}

	// Send and receive.
	StudentRecord temp;
	fstream file;
	int choice = -1;
	char Menu[] = "1. Add record\n2. Display all records\n3. Search record\n4. Update record\n5. Download course outline\n6. Disconnect";
	while (choice != 6)
	{
		ServerObj.Send((void*)Menu, strlen(Menu)+1); // Send NULL as well.
		ServerObj.Receive((void*)&choice, sizeof(int));

		switch (choice)
		{
		case 1:
			{
				ServerObj.Receive((void*)&temp, sizeof(StudentRecord));
				file.open("records.rec", ios::out|ios::app|ios::binary);
				file.write((char*)&temp, sizeof(StudentRecord));
				file.close();
				break;
			}
		case 2:
			{
				int NoOfRecords;
				file.open("records.rec", ios::in|ios::binary);
				if (file.is_open()==true)
				{
					file.seekg(0, ios::end);
					NoOfRecords = (int)file.tellg()/sizeof(StudentRecord);
				}
				else
					NoOfRecords = 0;

				ServerObj.Send((void*)&NoOfRecords, sizeof(int));
				file.seekg(0);
				for (int i=0; i<NoOfRecords; i++)
				{
					file.read((char*)&temp, sizeof(StudentRecord));
					ServerObj.Send((void*)&temp, sizeof(StudentRecord));
				}
				file.close();
				break;
			}
		case 3:
			{
				int found = 0;
				int index;
				int NoOfRecords;
				char SearchName[40];
				ServerObj.Receive((void*)SearchName, 40);

				file.open("records.rec", ios::in|ios::binary);
				file.seekg(0, ios::end);
				NoOfRecords = (int)file.tellg()/sizeof(StudentRecord);
				file.seekg(0);
				for (int i=0; i<NoOfRecords; i++)
				{
					file.read((char*)&temp, sizeof(StudentRecord));
					if (strcmp(temp.Name, SearchName)==0)
					{
						found = 1;
						index = i;
						break;
					}
				}
				ServerObj.Send((void*)&found, sizeof(int));
				if (found==1)
				{
					file.seekg(index*sizeof(StudentRecord));
					ServerObj.Send((void*)&temp, sizeof(StudentRecord));
				}
				file.close();
				break;
			}
		case 4:
			{
				int found = 0;
				int index;
				int NoOfRecords;
				char SearchName[40];
				ServerObj.Receive((void*)SearchName, 40);

				file.open("records.rec", ios::in|ios::out|ios::binary);
				file.seekg(0, ios::end);
				NoOfRecords = (int)file.tellg()/sizeof(StudentRecord);
				file.seekg(0);
				for (int i=0; i<NoOfRecords; i++)
				{
					file.read((char*)&temp, sizeof(StudentRecord));
					if (strcmp(temp.Name, SearchName)==0)
					{
						found = 1;
						index = i;
						break;
					}
				}
				ServerObj.Send((void*)&found, sizeof(int));
				if (found==1)
				{
					ServerObj.Receive((void*)&temp, sizeof(StudentRecord));
					file.seekp(sizeof(StudentRecord)*index);
					cout << (int)file.tellp() << endl;
					file.write((char*)&temp, sizeof(StudentRecord));
				}
				file.close();
				break;
			}
		case 5:
			{
				file.open("Course_Outline.pdf", ios::in|ios::binary);
				file.seekg(0, ios::end);
				int filesize = (int)file.tellg();
				ServerObj.Send((void*)&filesize, sizeof(int));

				file.seekg(0, ios::beg);
				char c;
				for (int i=0; i<filesize; i++)
				{
					file.read((char*)&c, sizeof(char));
					ServerObj.Send((void*)&c, sizeof(char));
				}
				file.close();
				break;
			}
		case 6:
			break;
		}
	}

	// Close sockets.
	ServerObj.CloseClientSocket();
	ServerObj.CloseServerSocket();

	return 0;
}
