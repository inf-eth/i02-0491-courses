#ifdef WIN32
#include <process.h>
#include <Windows.h>
#define TRET_TYPE void
#else
#include <pthread.h>
#define TRET_TYPE void*
#endif

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sys/types.h>

void PerformanceTest ();
TRET_TYPE thread1f (void *);
TRET_TYPE thread2f (void *);

const unsigned int X  = 1024;
const unsigned int Y  = 1024;
const unsigned int T1  = 500;
const unsigned int T2  = 1000;

double A[X][Y];
double B[X][Y];
double C[X][Y];

clock_t tStart, tEnd;

int main (int argc, char **argv)
{

#ifdef WIN32
	HANDLE th[2];
#else
	pthread_t thread1, thread2;
#endif

	std::cout << "Single thread test: " << X << " * " << Y << " * " << T2 << " multplications." << std::endl;
	tStart = clock();
	PerformanceTest();
	tEnd = clock();
	std::cout << "Time elapsed = " << (double)(tEnd - tStart)/CLOCKS_PER_SEC << " seconds." << std::endl;

	std::cout << "2x thread test: " << X << " * " << Y << " * " << T1 << " multiplications per thread." << std::endl;
	tStart = clock();

#ifdef WIN32
	th[0] = (HANDLE)_beginthread (thread1f, 0, NULL);
	th[1] = (HANDLE)_beginthread (thread2f, 0, NULL);
	WaitForMultipleObjects (2, th, NULL, INFINITE);
#else
	pthread_create (&thread1, NULL, thread1f, NULL);
	pthread_create (&thread2, NULL, thread2f, NULL);
	pthread_join (thread1, NULL);
	pthread_join (thread2, NULL);
#endif

	clock_t tEnd = clock();
	std::cout << "Time elapsed = " << (double)(tEnd - tStart)/CLOCKS_PER_SEC << " seconds." << std::endl;
	return 0;
}

void PerformanceTest ()
{
	unsigned int i, j, t;
	for (t=0; t<(T1+T2); t++)
		for (i=0; i<X; i++)
			for (j=0; j<Y; j++)
				C[i][j] = A[i][j] * B[i][j];
}

TRET_TYPE thread1f (void *a)
{
	unsigned int i, j, t;
	for (t=0; t<T1; t++)
		for (i=0; i<X; i++)
			for (j=0; j<Y; j++)
				C[i][j] = A[i][j] * B[i][j];
#ifndef WIN32
	return NULL;
#endif
}

TRET_TYPE thread2f (void *a)
{
	unsigned int i, j, t;
	for (t=T1; t<T2; t++)
		for (i=0; i<X; i++)
			for (j=0; j<Y; j++)
				C[i][j] = A[i][j] * B[i][j];
#ifndef WIN32
	return NULL;
#endif
}
