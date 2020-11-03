#pragma once
//#include "cuda_runtime.h"
//#include "device_launch_parameters.h"

//complex number handler declaration


class cpu_complex {
private:
    double im;
    double re;
public:
    cpu_complex(double x, double y);
    cpu_complex();
    double r_sq();
    double im_sq();
    double modulus();
    cpu_complex operator*(const cpu_complex& a);
    cpu_complex operator+(const cpu_complex& a);
};
