#include "timer.h"
#include <iostream>

int main (int argc, char **argv)
{
	__int64 ms = GetTimeMs64();
	__int64 us = GetTimeus64();
	std::cout << "ms = " << ms << std::endl;
	std::cout << "us = " << us << std::endl;

	// Benchmarking.
	__int64 tStart, tEnd;
	tStart = GetTimeus64();

	for (int i=0; i<1024*1024*1000; i++)
		for (int j=0; j<10; j++)
			double x = 2.34 * 332.2212 / 32342.2 / 32.234 * 432.2131;

	tEnd = GetTimeus64();
	std::cout << "Time taken = " << ((double)(tEnd-tStart))/(1000000.) << " seconds." << std::endl;

	return 0;
}
