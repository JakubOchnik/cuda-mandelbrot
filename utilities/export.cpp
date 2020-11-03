#include <opencv2/opencv.hpp>
#include"export.h"

using namespace cv;
using namespace std;

void viewMandelbrot(unsigned char* image, int w, int h, bool color) {
	if (!color) {
		Mat img(h, w, CV_8UC1, image);
		imwrite("mandelbrot.jpg", img);
	}
	else {
		Mat img(h, w, CV_8UC3, image);
		imwrite("mandelbrot_color.jpg", img);
	}
}