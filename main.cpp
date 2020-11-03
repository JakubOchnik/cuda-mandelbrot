#include <iostream>
#include <chrono>
#include "gpu/cudaMandelbrot.h"
#include "cpu/cpuMandelbrot.h"
#include "utilities/params.h"
#include "utilities/export.h"

using namespace std;

int main() {
	// if monochrome alloc width*height pixels, else multiply it by RGB channels (3)
#ifdef MONOCHROME
	unsigned char* image = (unsigned char*)malloc(WIDTH * HEIGHT * sizeof(unsigned char));
	if (image == NULL)
		return -1;
	memset(image, 0, WIDTH * HEIGHT * sizeof(unsigned char));
#else
	unsigned char* image = (unsigned char*)malloc(3*WIDTH * HEIGHT * sizeof(unsigned char));
	if (image == NULL)
		return -1;
	memset(image, 0, 3* WIDTH * HEIGHT * sizeof(unsigned char));
#endif

	//execute the timer
#ifdef COUNT_TIME
	auto start = std::chrono::high_resolution_clock::now();
#endif

	// execute the proper function
#ifdef GPU
	calculateMandelbrot(image);
#else
	calculateMandelbrotCPU(image);
#endif

	//print out the time
#ifdef COUNT_TIME
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";
#endif

#ifdef MONOCHROME
	viewMandelbrot(image, WIDTH, HEIGHT, false);
#else
	viewMandelbrot(image, WIDTH, HEIGHT, true);
#endif
	
	free(image);
	return 0;
}