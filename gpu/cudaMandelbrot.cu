
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <math.h>
#include "../utilities/params.h"
#include<chrono>
#include<iostream>

class gpu_complex {
private:
    double im;
    double re;
public:
    __device__ gpu_complex(double x, double y) {
        re = x;
        im = y;
    }
    __device__ gpu_complex() {
        re = 0.0;
        im = 0.0;
    }
    __device__ double r_sq() {
        return re * re;
    }
    __device__ double im_sq() {
        return im * im;
    }
    __device__ double modulus() {
        return (r_sq() + im_sq());
    }
    __device__ gpu_complex operator*(const gpu_complex& a) {
        return gpu_complex(re * a.re - im * a.im, re * im + im * a.re);
    }
    __device__ gpu_complex operator+(const gpu_complex& a) {
        return gpu_complex(re + a.re, im + a.im);
    }
};

__device__ int checkIter(int x, int y, const bool color) {
    double s_x = x_min + x / (WIDTH -1.0) * (x_max - x_min);
    double s_y = y_min + y / (HEIGHT -1.0) * (y_max - y_min);
    gpu_complex num;
    gpu_complex C(s_x, s_y);
    int i = 0;
    for (; i < ITERATIONS; i++) {
        if (num.modulus() > 4)
            break;
        num = num * num + C;
    }
    if (!color) {
        if (i > 255)
            return 255;
        else
            return (unsigned char)i;
    }
    else {
        if (i >= ITERATIONS)
            return ITERATIONS;
        else
            return (unsigned char)i;
    }
}

__global__ void calculate(unsigned char* img)
{
    int x = blockIdx.x;
    int y = blockIdx.y;
    int tid = (x + y * gridDim.x) * 3;
    int val = checkIter(x, y, 1);
    float ratio = (float)val * 1.0f / (float)ITERATIONS;
    unsigned char r, g, b;
    r = r_1 + ratio * (r_2 - r_1);
    g = g_1 + ratio * (g_2 - g_1);
    b = b_1 + ratio * (b_2 - b_1);
    img[tid] = b;//r_1 + val / 255.0 * (r_2 - r_1);
    img[tid + 1] = g;// g_1 + val / 255.0 * (g_2 - g_1);
    img[tid + 2] = r;//b_1 + val / 255.0 * (b_2 - b_1);
}

__global__ void calculate_mono(unsigned char* img)
{
    int x = blockIdx.x;
    int y = blockIdx.y;
    int tid = x + y * gridDim.x;

    img[tid] = checkIter(x, y, 0);
}

void calculateMandelbrot(unsigned char* image) {
    dim3 blocksPerGrid(WIDTH, HEIGHT);
    unsigned char* dev_out;
    std::chrono::steady_clock::time_point start;
    size_t memSize;
    if (!color) 
        memSize = WIDTH * HEIGHT * sizeof(unsigned char);
    else 
        memSize = 3 * WIDTH * HEIGHT * sizeof(unsigned char);

    cudaMalloc(&dev_out, memSize);
    cudaMemcpy(dev_out, image, memSize, cudaMemcpyHostToDevice);
    start = std::chrono::high_resolution_clock::now();
    if (!color) {
        calculate_mono << <blocksPerGrid, 1 >> > (dev_out);
    }
    else {
        calculate << <blocksPerGrid, 1 >> > (dev_out);
    }
    cudaMemcpy(image, dev_out, memSize, cudaMemcpyDeviceToHost);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    cudaFree(dev_out);
}
