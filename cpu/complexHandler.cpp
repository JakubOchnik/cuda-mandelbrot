#include "complexHandler.h"

//complex number handler definition

cpu_complex::cpu_complex(double x, double y) {
	re = x;
	im = y;
}
cpu_complex::cpu_complex() {
	re = 0.0;
	im = 0.0;
}

double cpu_complex::r_sq() {
	return re * re;
}
double cpu_complex::im_sq() {
	return im * im;
}
double cpu_complex::modulus() {
	return (r_sq() + im_sq());
}

cpu_complex cpu_complex::operator*(const cpu_complex& a) {
	return cpu_complex(re * a.re - im * a.im, re * im + im * a.re);
}
cpu_complex cpu_complex::operator+(const cpu_complex& a) {
	return cpu_complex(re + a.re, im + a.im);
}