#include <iostream>
#include <chrono>

#include "gpu/cudaMandelbrot.h"
#include "cpu/cpuMandelbrot.h"
#include "utilities/params.h"
#include "utilities/export.h"

using namespace std;

int main() {

	if (color && !useGPU) {
		cout << "Colorized Mandelbrot is not implemented on CPU yet. Exiting...";
		return -1;
	}

	// if monochrome alloc width*height pixels, else multiply it by RGB channels (3)
	unsigned int factor = 1;

	if (color)
		factor = 3;
	else
		factor = 1;

	size_t memorySize = factor * WIDTH * HEIGHT * sizeof(unsigned char);
	unsigned char* image = (unsigned char*)malloc(memorySize);
	if (image == NULL)
		return -1;
	memset(image, 0, memorySize);


	if (useGPU) {
		calculateMandelbrot(image);
	}
	else {
		auto start = std::chrono::high_resolution_clock::now();
		calculateMandelbrotCPU(image);
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		std::cout << "Elapsed time (CPU): " << elapsed.count() << " s\n";
	}

	viewMandelbrot(image, WIDTH, HEIGHT);
	
	free(image);
	return 0;
}