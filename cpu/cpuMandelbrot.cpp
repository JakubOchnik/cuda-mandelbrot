#include "../cpu/cpuMandelbrot.h"
#include "../cpu/complexHandler.h"

void calculateMandelbrotCPU(unsigned char* img) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			int id = j + i * WIDTH;
			double s_x = x_min + j / (WIDTH - 1.0) * (x_max - x_min);
			double s_y = y_min + i / (HEIGHT - 1.0) * (y_max - y_min);
			cpu_complex num(0, 0);
			cpu_complex C(s_x, s_y);
			int k = 0;
			for (; k < ITERATIONS; k++) {
				if (num.modulus() > 4)
					break;
				num = num * num + C;
			}
			if (!color) {
				if (k > 255)
					img[id] = 255;
				else
					img[id] = (unsigned char)k;
			}
			else {
				if (i >= ITERATIONS)
					img[id] =  ITERATIONS;
				else
					img[id] = (unsigned char)k;
			}
		}
	}
}