// Common header files.
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include "Timer.h"

using std::cout;
using std::endl;

#if defined __linux__ || defined __CYGWIN__
// Linux headers.
#include <pthread.h>
#include <sys/time.h>

// Thread function prototypes.
void* thread1f (void *);
void* thread2f (void *);

// Main.
int main (int argc, char **argv)
{
	cout << "Running on linux..." << endl;
	__int64 tStart, tEnd;
	pthread_t thread1, thread2;
	
	cout << "This is main() creating two threads now." << endl;
	tStart = GetTimeus64();		// Start time.

	pthread_create (&thread1, NULL, thread1f, NULL);
	pthread_create (&thread2, NULL, thread2f, NULL);

	cout << "This is main() waiting on threads..." << endl;
	pthread_join (thread1, NULL);
	pthread_join (thread2, NULL);

	tEnd = GetTimeus64();		// End time.
	cout << "Elapsed time = " << ((double)(tEnd-tStart))/(1000000.) << " seconds." << endl;

	return 0;
}

void* thread1f (void *a)
{
	cout << "This is thread 1 looping 1024x1024x1024 times..." << endl;
	unsigned int i, j, t;
	for (t=0; t<1024; t++)
		for (i=0; i<1024; i++)
			for (j=0; j<1024; j++)
				double x = 3.2*4.5/333.0*444.0;
	cout << "Thread 1 is fininhed and is now returning..." << endl;

	return NULL;
}

void* thread2f (void *a)
{
	cout << "This is thread 2 looping 1024x1024x1024 times..." << endl;
	unsigned int i, j, t;
	for (t=0; t<1024; t++)
		for (i=0; i<1024; i++)
			for (j=0; j<1024; j++)
				double x = 3.2*4.5/333.0*444.0;
	cout << "Thread 2 is fininhed and is now returning..." << endl;

	return NULL;
}

// Windows Code.
#else

// Windows headers.
#include <process.h>
#include <Windows.h>

// Thread function prototypes.
void thread1f (void *);
void thread2f (void *);

// Main.
int main (int argc, char **argv)
{
	cout << "Running on windows..." << endl;
	__int64 tStart, tEnd;
	HANDLE thread1, thread2;
	tStart = GetTimeus64();		// Start stop-watch.

	cout << "This is main() creating two threads..." << endl;
	thread1 = (HANDLE)_beginthread (thread1f, 0, NULL);
	thread2 = (HANDLE)_beginthread (thread2f, 0, NULL);

	cout << "This is main() waiting for both threads..." << endl;
	WaitForSingleObject(thread2, INFINITE);
	WaitForSingleObject(thread1, INFINITE);

	tEnd = GetTimeus64();		// Stop stop-watch.
	cout << "Elapsed time = " << ((double)(tEnd-tStart))/(1000000.) << " seconds." << endl;		// Print execution time.

	return 0;
}

// Thread function definitions.
void thread1f (void *a)
{
	cout << "This is thread 1 looping 1024x1024x1024 times..." << endl;
	unsigned int i, j, t;
	for (t=0; t<1024; t++)
		for (i=0; i<1024; i++)
			for (j=0; j<1024; j++)
				double x = 3.2*4.5/333.0*444.0;
	cout << "Thread 1 is fininhed and is now returning..." << endl;
}

void thread2f (void *a)
{
	cout << "This is thread 2 looping 1024x1024x1024 times..." << endl;
	unsigned int i, j, t;
	for (t=0; t<1024; t++)
		for (i=0; i<1024; i++)
			for (j=0; j<1024; j++)
				double x = 3.2*4.5/333.0*444.0;
	cout << "Thread 2 is fininhed and is now returning..." << endl;
}
#endif
