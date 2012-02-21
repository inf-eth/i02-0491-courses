#include <pthread.h>
#include <iostream>
using std::cout;
using std::endl;

// Thread function prototype.
void* thread1f (void *);
void* thread2f (void *);

int main (int argc, char **argv)
{
	pthread_t thread1, thread2;

	cout << "main() creating threads." << endl;
	pthread_create (&thread1, NULL, thread1f, NULL);
	pthread_create (&thread2, NULL, thread2f, NULL);

	cout << "main() waiting for threads." << endl;
	pthread_join (thread1, NULL);
	pthread_join (thread2, NULL);

	cout << "Both threads finished, exiting main()." << endl;
	return 0;
}

// Thread functions.
void* thread1f (void *a)
{
	float x;
	cout << "This is thread 1 looping 1024*1024*1024 times." << endl;
	for (int i=0; i<1024*1024*1024; i++)
	{
		x = 2.1 * 3.3 / 9.9;
	}
	cout << "Thread 1 exiting..." << endl;

	return NULL;
}

void* thread2f (void *a)
{
	float x;
	cout << "This is thread 2 looping 1024*1024*1024 times." << endl;
	for (int i=0; i<1024*1024*1024; i++)
	{
		x = 2.1 * 3.3 / 9.9 * 4.11;
	}
	cout << "Thread 2 exiting..." << endl;

	return NULL;
}
