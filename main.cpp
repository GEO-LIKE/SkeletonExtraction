#include <opencv2\opencv.hpp>
#include "skeleton.h"
#include "thin.h"

int main() {
	// Create a matrix and initialization
	cv::Mat src = GenerateMat();
	cv::Mat grayImage, binaryImage, distImage, gradientImage,ridge;
	cv::cvtColor(src, grayImage,CV_BGR2GRAY);
	// Binarization
	cv::threshold(grayImage, binaryImage,150, 255, cv::THRESH_BINARY);
	// Thinning
	thinning(binaryImage, ridge);

	cv::imshow("Skeleton", ridge);
	cv::imwrite("Skeleton.jpg", ridge);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return(0);
}
