#if defined __linux__ || defined __CYGWIN__
#include <pthread.h>
#define TRET_TYPE void*
#include <sys/time.h>
#else
#include <process.h>
#include <Windows.h>
#include "Timer.h"
#define TRET_TYPE void
#endif

#include <iostream>
#include <cstdlib>
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

int main (int argc, char **argv)
{

#if defined __linux__ || defined __CYGWIN__
	std::cout << "Running on linux..." << std::endl;
	pthread_t thread1, thread2;
	struct timeval tv1, tv2;
#else
	std::cout << "Running on windows..." << std::endl;
	__int64 tStart, tEnd;
	HANDLE th[2];
#endif

	std::cout << "Single thread test: " << X << " * " << Y << " * " << T2 << " multplications." << std::endl;

#if defined __linux__ || defined __CYGWIN__
	gettimeofday(&tv1, NULL);
#else
	tStart = GetTimeus64();
#endif

	PerformanceTest();

#if defined __linux__ || defined __CYGWIN__
	gettimeofday(&tv2, NULL);
	std::cout << "Elapsed time = " << (double)(tv2.tv_sec-tv1.tv_sec) + (double)(tv2.tv_usec-tv1.tv_usec)/(1000000.) << std::endl;
#else
	tEnd = GetTimeus64();
	std::cout << "Elapsed time = " << ((double)(tEnd-tStart))/(1000000.) << " seconds." << std::endl;
#endif

	std::cout << "2x thread test: " << X << " * " << Y << " * " << T1 << " multiplications per thread." << std::endl;

#if defined __linux__ || defined __CYGWIN__
	gettimeofday(&tv1, NULL);
	pthread_create (&thread1, NULL, thread1f, NULL);
	pthread_create (&thread2, NULL, thread2f, NULL);
	pthread_join (thread1, NULL);
	pthread_join (thread2, NULL);
	gettimeofday(&tv2, NULL);
	std::cout << "Elapsed time = " << (double)(tv2.tv_sec-tv1.tv_sec) + (double)(tv2.tv_usec-tv1.tv_usec)/(1000000.) << std::endl;
#else
	tStart = GetTimeus64();
	th[0] = (HANDLE)_beginthread (thread1f, 0, NULL);
	th[1] = (HANDLE)_beginthread (thread2f, 0, NULL);
	WaitForMultipleObjects (2, th, NULL, INFINITE);
	tEnd = GetTimeus64();
	std::cout << "Elapsed time = " << ((double)(tEnd-tStart))/(1000000.) << " seconds." << std::endl;
#endif

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
