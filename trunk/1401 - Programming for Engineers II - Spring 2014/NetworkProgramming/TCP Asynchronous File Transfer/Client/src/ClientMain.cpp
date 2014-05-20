#if defined __linux__ || defined __CYGWIN__
#include <pthread.h>
#define TRET_TYPE void*
#include <sys/time.h>
#else
#include <process.h>
#define TRET_TYPE void
#endif
#include <Client.h>
#include <cstdlib>			// exit(), atoi()
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

#define TOTALTHREADS 4
#define RECVBUFFERSIZE 128

TRET_TYPE ReceiverThread(void*);
#if defined __linux__ || defined __CYGWIN__
pthread_mutex_t MutexLock = PTHREAD_MUTEX_INITIALIZER;
#else
HANDLE MutexLock = CreateMutex(NULL, FALSE, NULL);
#endif

class ReceiverArgument
{
	public:
	int TID;
	int TotalThreads;
	int FileSize;
	string FileName;
	string ServerName;
	int ServerPort;
	int ClientPort;
};

int main()
{
	#if defined __linux__ || defined __CYGWIN__
	std::cout << "Running on linux..." << std::endl;
	pthread_t* thread = new pthread_t[TOTALTHREADS];
	#else
	std::cout << "Running on windows..." << std::endl;
	HANDLE* thread = new HANDLE[TOTALTHREADS];
	#endif

	char ServerName[24];
	int ServerPort;
	int ClientPort = 7000;

	// Create Client object.
	Client ClientObj(TCPSOCKET, ClientPort);			// Can create an object without arguments. Defaults are TCPSOCKET and DEFAULTPORT (6001).

	// Create Client Socket.
	ClientObj.CreateSocket(TCPSOCKET);
	ClientObj.SetSocketOptions();

	// Initialise and bind Client address.
	ClientObj.InitialiseAddress(ClientPort);	// Without any argument default port will be chosen.
	ClientObj.Bind();

	cout << "Enter Server name or IP: "; // Use localhost or 127.0.0.1 for local server.
	cin.getline(ServerName, 24);
	cout << "Enter Server port: ";
	cin >> ServerPort;

	// Connect to Server. Server name/IP and port are provided as arguments.
	ClientObj.Connect(ServerName, ServerPort);

	// ********************** Actual File Transfer **********************
	char Filename[48];
	cout << "Enter filename to download from server (STL.pdf): ";
	if (cin.peek() == '\n') cin.ignore(); // If input skips.
	cin.getline(Filename, 48);

	// 1. Send filename to server.
	ClientObj.Send((void*)Filename, (unsigned int)strlen(Filename));
	ClientObj.Receive(); // Receive ACK or NACK

	// 2. Checking if file opened.
	if (!strcmp(ClientObj.GetBuffer(), "NACK"))
	{
		cout << "Error: opening file." << endl;
		exit(0);
	}
	else
		ClientObj.Send((void*)"ACK", (unsigned int)strlen("ACK")); // Send ACK.

	// 3. Getting filesize.
	ClientObj.Receive();
	int FileSize = *((int*)ClientObj.GetBuffer());
	cout << "Filesize is " << FileSize << "B (" << (double)FileSize/1024 << "KB, " << (double)FileSize/1024/1024 << "MB)." << endl;
	ClientObj.Send((void*)"ACK", sizeof("ACK")); // Sending ACK.

	// 4. Starting receiver threads.
	string Received = "Received_";
	Received = Received + Filename;
	fstream File;
	File.open(Received.c_str(), ios::out|ios::binary|ios::trunc);
	File.close();

	ReceiverArgument* Arg = new ReceiverArgument[TOTALTHREADS];
	for (int i=0; i<TOTALTHREADS; i++)
	{
		Arg[i].TID = i;
		Arg[i].TotalThreads = TOTALTHREADS;
		Arg[i].FileSize = FileSize;
		Arg[i].FileName = Received;
		Arg[i].ServerName = ServerName;
		Arg[i].ServerPort = ServerPort;
		Arg[i].ClientPort = ClientPort;
	}

	for (unsigned int i=0; i<TOTALTHREADS; i++)
	{
		#if defined __linux__ || defined __CYGWIN__
		pthread_create(&thread[i], NULL, ReceiverThread, (void*)&Arg[i]);
		#else
		thread[i] = (HANDLE)_beginthread(ReceiverThread, 0, (void*)&Arg[i]);
		#endif
	}

	for (unsigned int i=0; i<TOTALTHREADS; i++)
	{
		#if defined __linux__ || defined __CYGWIN__
		pthread_join(thread[i], NULL);
		#else
		WaitForSingleObject(thread[i], INFINITE);
		#endif
	}

	cout << "File received." << endl; // Received file is in 'Client' folder.
	ClientObj.CloseClientSocket();

	return 0;
}

TRET_TYPE ReceiverThread(void* Args)
{
	ReceiverArgument* recvArgs = (ReceiverArgument*)Args;
	int Offset = recvArgs->FileSize % recvArgs->TotalThreads == 0 ? recvArgs->FileSize/recvArgs->TotalThreads : (recvArgs->FileSize/recvArgs->TotalThreads)+1;
	int PartitionSize = recvArgs->TID == (recvArgs->TotalThreads-1) ? recvArgs->FileSize-recvArgs->TID*Offset : Offset;
	int ServerPort = recvArgs->ServerPort+recvArgs->TID+1;
	int ClientPort = recvArgs->ClientPort+recvArgs->TID+1;
	char FileBuffer[RECVBUFFERSIZE];

	// Create Client object.
	Client ClientObj(TCPSOCKET, ClientPort);

	// Create Client Socket.
	ClientObj.CreateSocket(TCPSOCKET);
	ClientObj.SetSocketOptions();

	// Initialise and bind Client address.
	ClientObj.InitialiseAddress(ClientPort);
	ClientObj.Bind();

	// Connect to Server. Server name/IP and port are provided as arguments.
	ClientObj.Connect((char*)recvArgs->ServerName.c_str(), ServerPort);

	fstream File;
	File.open(((ReceiverArgument*)Args)->FileName.c_str(), ios::out|ios::binary);
	int Iterations = PartitionSize%RECVBUFFERSIZE == 0 ? PartitionSize/RECVBUFFERSIZE: PartitionSize/RECVBUFFERSIZE+1; // Number of times file needs to be written.

	File.seekp(recvArgs->TID*Offset);
	int TotalBytesReceived = 0;
	while (TotalBytesReceived != PartitionSize)
	{
		int BytesReceived = ClientObj.Receive((void*)FileBuffer, RECVBUFFERSIZE);
		TotalBytesReceived = TotalBytesReceived + BytesReceived;

		#if defined __linux__ || defined __CYGWIN__
		pthread_mutex_lock(&MutexLock);
		#else
		WaitForSingleObject(MutexLock, INFINITE);
		#endif
		// File writing must be atomic.
		File.write(FileBuffer, BytesReceived);
		#if defined __linux__ || defined __CYGWIN__
		pthread_mutex_unlock(&MutexLock);
		#else
		ReleaseMutex(MutexLock);
		#endif

		//ClientObj.Send((void*)"ACK", sizeof("ACK")); // Sending ACK.
	}
	File.close();

	ClientObj.CloseClientSocket();

	#ifndef WIN32
	return NULL;
	#endif
}
