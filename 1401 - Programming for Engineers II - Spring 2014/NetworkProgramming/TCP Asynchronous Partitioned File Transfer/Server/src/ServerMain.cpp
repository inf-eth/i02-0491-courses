#if defined __linux__ || defined __CYGWIN__
#include <pthread.h>
#define TRET_TYPE void*
#include <sys/time.h>
#else
#include <process.h>
#define TRET_TYPE void
#endif
#include <Server.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#define TOTALTHREADS 4
#define SENDBUFFERSIZE 4096

TRET_TYPE SenderThread(void*);

class SenderArgument
{
	public:
	int TID;
	int TotalThreads;
	int ServerPort;
	int FileSize;
	string FileName;
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

	int ServerPort = DEFAULTSERVERPORT;

	// Create Server object.
	Server ServerObj(TCPSOCKET, ServerPort);			// Without any arguments Server will set defaults, TCPSOCKET as type and 6000 as port.

	// Create Server socket and set socket options.
	ServerObj.CreateSocket(TCPSOCKET);		// No argument means TCPSOCKET
	ServerObj.SetSocketOptions();

	// Initialise Server address struct and bind it with Server's socket.
	ServerObj.InitialiseAddress(ServerPort);		// No argument here will take default port.
	ServerObj.Bind();

	// Listen for incoming connections.
	ServerObj.Listen();
	ServerObj.DisplayServerInfo();

	// Accept any incoming connections.
	ServerObj.Accept();
	ServerObj.DisplayClientInfo();

	// ***************** Actual File Transfer *****************
	// 1. Receive the name of file. File should exist in the 'Server' folder.
	cout << "Server waiting for filename." << endl;
	ServerObj.Receive();
	cout << "Client requested file: " << ServerObj.GetBuffer() << endl;

	// 2. Open the file for reading.
	fstream File;
	string FileName = ServerObj.GetBuffer();
	File.open(FileName.c_str(), ios::in|ios::binary);
	if (File.is_open()==false)
	{
		cout << "Error: File failed to open" << endl;
		ServerObj.Send((void*)"NACK", sizeof("NACK")); // Sending NACK if file failed to open.
		exit(0);
	}
	else
	{
		ServerObj.Send((void*)"ACK", sizeof("ACK")); // Sending ACK if file opened.
		ServerObj.Receive(); // Receive ACK from client.
	}

	// 3. Send file size to client.
	File.seekg(ios::beg, ios::end);
	int FileSize = (int)File.tellg();
	File.close();

	SenderArgument* Arg = new SenderArgument[TOTALTHREADS];
	for (int i=0; i<TOTALTHREADS; i++)
	{
		Arg[i].TID = i;
		Arg[i].TotalThreads = TOTALTHREADS;
		Arg[i].FileSize = FileSize;
		Arg[i].FileName = FileName;
		Arg[i].ServerPort = ServerPort;
	}

	for (unsigned int i=0; i<TOTALTHREADS; i++)
	{
		#if defined __linux__ || defined __CYGWIN__
		pthread_create(&thread[i], NULL, SenderThread, (void*)&Arg[i]);
		#else
		thread[i] = (HANDLE)_beginthread(SenderThread, 0, (void*)&Arg[i]);
		#endif
	}

	ServerObj.Send((void*)&FileSize, sizeof(FileSize));
	ServerObj.Receive(); // Receive ACK (acknowledgement) from client.

	for (unsigned int i=0; i<TOTALTHREADS; i++)
	{
		#if defined __linux__ || defined __CYGWIN__
		pthread_join(thread[i], NULL);
		#else
		WaitForSingleObject(thread[i], INFINITE);
		#endif
	}

	cout << "File transfered." << endl;
	// ****************************************************************

	// Close sockets.
	ServerObj.CloseClientSocket();
	ServerObj.CloseServerSocket();

	return 0;
}

TRET_TYPE SenderThread(void* Args)
{
	SenderArgument* sendArgs = (SenderArgument*)Args;
	int Offset = (sendArgs->FileSize % sendArgs->TotalThreads == 0 ? sendArgs->FileSize/sendArgs->TotalThreads : (sendArgs->FileSize/sendArgs->TotalThreads)+1);
	int PartitionSize = (sendArgs->TID == (sendArgs->TotalThreads-1) ? sendArgs->FileSize-sendArgs->TID*Offset : Offset);
	int ServerPort = sendArgs->ServerPort+sendArgs->TID+1;
	char FileBuffer[SENDBUFFERSIZE]; // Buffer to hold data read from file.

	// Create Server object.
	Server ServerObj(TCPSOCKET, ServerPort);			// Without any arguments Server will set defaults, TCPSOCKET as type and 6000 as port.

	// Create Server socket and set socket options.
	ServerObj.CreateSocket(TCPSOCKET);		// No argument means TCPSOCKET
	ServerObj.SetSocketOptions();

	// Initialise Server address struct and bind it with Server's socket.
	ServerObj.InitialiseAddress(ServerPort);		// No argument here will take default port.
	ServerObj.Bind();

	// Listen for incoming connections.
	ServerObj.Listen();
	ServerObj.DisplayServerInfo();

	// Accept any incoming connections.
	ServerObj.Accept();
	ServerObj.DisplayClientInfo();

	// Send file in a loop.
	fstream File;
	File.open(sendArgs->FileName.c_str(), ios::in|ios::binary);
	//int Iterations = PartitionSize%SENDBUFFERSIZE == 0 ? PartitionSize/SENDBUFFERSIZE: PartitionSize/SENDBUFFERSIZE+1; // Number of times file needs to be read.

	File.seekg(sendArgs->TID*Offset);
	int TotalBytesSent = 0;
	//for (int i=0; i<Iterations; i++)
	while (TotalBytesSent != PartitionSize)
	{
		int BytesRead;
		int BytesSent = 0;
		if (PartitionSize-TotalBytesSent >= SENDBUFFERSIZE)
			BytesRead = SENDBUFFERSIZE;
		else
			BytesRead = PartitionSize-TotalBytesSent;
		/*
		if (i==(Iterations-1))
			PartitionSize%SENDBUFFERSIZE == 0 ? BytesRead=SENDBUFFERSIZE : BytesRead = PartitionSize%SENDBUFFERSIZE;
		else
			BytesRead = SENDBUFFERSIZE;
		*/
		File.read(FileBuffer, BytesRead);
		while (BytesSent != BytesRead)
		{
			BytesSent = ServerObj.Send((void*)(FileBuffer+BytesSent), BytesRead-BytesSent);
			TotalBytesSent = TotalBytesSent + BytesSent;
		}
	}
	File.close();

	// Close sockets.
	ServerObj.CloseClientSocket();
	ServerObj.CloseServerSocket();

	#ifndef WIN32
	return NULL;
	#endif
}
