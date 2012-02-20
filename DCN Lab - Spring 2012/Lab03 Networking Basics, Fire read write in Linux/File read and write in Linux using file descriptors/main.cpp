//#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
//#include <unistd.h>
#include<iostream>
using namespace std;
#define BUFFERSIZE 128

int main()
{
	int ReadFD, WriteFD, BytesRead, BytesWritten;
	char Buffer[BUFFERSIZE];
	
	ReadFD = open ("lab.pdf", O_RDONLY);
	WriteFD = open ("copy of.pdf", O_WRONLY | O_CREAT, S_IRWXU);

	while (true)
	{
		BytesRead = read (ReadFD, Buffer, BUFFERSIZE);
		
		if (BytesRead <= 0)
			break;
		
		BytesWritten = write (WriteFD, Buffer, BytesRead);
		
		if (BytesWritten != BytesRead)
		{
			cerr << "Error writing to file... " << endl;
			exit (-1);
		}
	}
	close (ReadFD);
	close (WriteFD);
	return 0;
}
