#include <iostream>
#include <cstring>
#include <fcntl.h>
using namespace std;

// *** International Variables ***

char Buffer[512];					// Buffer to store data in transit.
int  FileNameLength;				// Length of the filename.
int  ReadFD = -1;
int  WriteFD = -1;
char WriteFileName[] = "Copy of ";	// Filename that will be written
int  BytesRead = -1;				// Actual bytes read in one loop.

// *******************************

int main ( int argc, char *argv[] )
{
	if ( argc != 2 )
	{
		cout << "ERROR000: Invalid argument(s). Aborting and shutting down everything. :(" << endl;
		cout << "Program exited with error code 000." << endl;
		return -1;
	}

	// Calculating the string length.
	FileNameLength = strlen (argv[1]);

	// Checking if the filename entered is too long for processing.
	if (FileNameLength >= 128)
	{
		cout << "ERROR001: Filename length is too long. Aborting and shutting down everything. :(" << endl;
		cout << "Program exited with error code 001." << endl;
		return -1;
	}

	// Opening the file to be read in read-only mode.
	ReadFD = open (argv[1], O_RDONLY);

	// Checking if the file was opened successfully or not.
	if ( ReadFD > 0 )
	{
		cout << "File opened successfully for reading." << endl;
	}
	else
	{
		cout << "ERROR002: File does not exist or invalid filename/path. Aborting and shutting down everything. :(" << endl;
		cout << "Program exited with error code 002." << endl;
		return -1;
	}

	// File with the following name will be created.
	strcat (WriteFileName, argv[1]);

	// Now that the file has been opened successfully let's create the file into which data is to be written.
	WriteFD = open (WriteFileName, O_WRONLY | O_CREAT, S_IRWXU);

	if (WriteFD > 0)
	{
		cout << "File opened successfully for writing." << endl;
	}
	else
	{
		cout << "ERROR003: File could not be created for writing. Aborting and shutting down everything. :(" << endl;
		cout << "Program exited with error code 003." << endl;
		return -1;
	}

	// If we are here, this means everything is OK and we can now start copying data.
	while (true)
	{
		BytesRead = read (ReadFD, Buffer, 512);
		// If EOF.
		if (BytesRead == 0)
		{
			break;
		}
		write (WriteFD, Buffer, BytesRead);
	}

	// Acknowledgement.
	cout << "A copy of the file was saved as ";
	cout << WriteFileName << endl;

	// Cleaning up.
	close (ReadFD);
	close (WriteFD);
	return 0;

}
