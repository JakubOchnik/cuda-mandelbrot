#include <opencv2/opencv.hpp>
#include "export.h"
#include "params.h"

using namespace cv;
using namespace std;

void viewMandelbrot(unsigned char* image, int w, int h) {
	Mat img;
	std::string filename;
	if (!color) {
		img = Mat(h, w, CV_8UC1, image);
		filename = "mandelbrot_mono.png";
	}
	else {
		img = Mat(h, w, CV_8UC3, image);
		filename = "mandelbrot_color.png";
	}
	if (exportFile)
		imwrite(filename, img);
	std::string wName = "Mandelbrot set (" + to_string(WIDTH) + "x" + to_string(HEIGHT) + ")";
	cv::imshow(wName, img);
	cv::waitKey(0);
	cv::destroyWindow(wName);

}