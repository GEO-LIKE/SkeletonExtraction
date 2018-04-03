#ifndef SKELETON
#define SKELETON
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
//#include<iostream>
cv::Mat GenerateMat() {
	cv::Mat src, mask;
	
	src.create(300, 300, CV_8UC3);
	src.setTo(cv::Scalar(0, 0, 0));
	// draw some simple shape
	cv::circle(src, cv::Point(60, 60), 50, cv::Scalar(255, 225, 0), cv::FILLED, cv::LINE_8, 0);
	cv::rectangle(src, cv::Rect(200, 200, 80, 80), cv::Scalar(255, 225, 0), cv::FILLED);
	cv::ellipse(src, cv::RotatedRect(cv::Point(150, 100), cv::Size(150, 50), 90.0), cv::Scalar(255, 225, 0), cv::FILLED, cv::LINE_8);
	// convert to single band gray image
	return src;
}
void Gradient(cv::Mat& src, cv::Mat& grad) {
	//cv::Mat src;
	//cv::Mat grad;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	cv::Mat grad_x, grad_y;
	//cv::GaussianBlur(src, src, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
	float kernelY[9] = { 0,-1.0,0,0,0,0,0,1.0,0 };
	float kernelX[9] = { 0,0,0,-1.0,0,1.0,0,0,0 };
	cv::Mat filterY(3, 3, CV_32F, kernelY);
	cv::Mat filterX(3, 3, CV_32F, kernelX);
	//cv::multiply(src, mask,src);
	cv::filter2D(src, grad_x, -1, filterY, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
	cv::filter2D(src, grad_y, -1, filterX, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
	
	cv::Mat abs_grad_x, abs_grad_y;

	cv::normalize(grad_x, grad_x, 0, 255, cv::NORM_MINMAX);
	cv::normalize(grad_y, grad_y, 0, 255, cv::NORM_MINMAX);
	cv::convertScaleAbs(grad_x, abs_grad_x);
	cv::convertScaleAbs(grad_y, abs_grad_y);
	cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	cv::imshow("grad_x", grad_x);
	cv::imshow("grad_y", grad_y);
	cv::waitKey(0);
	cv::destroyAllWindows();
	cv::imwrite("D:\\Project\\cpp-workspace\\SkeletonExtraction\\ee.tif", src);
}
void getNeighbor(cv::Mat& src, cv::Point2i& center, int radius=1,int neighbors=8) {
	cv::Rect rect(center.x - radius, center.y - radius, 2 * radius + 1, 2 * radius + 1);
	cv::Mat temp;
	src(rect).copyTo(temp);
	std::vector<float> neighborPoints;
	//std::cout << temp.rows << ", " << temp.cols << std::endl;
	for (int n = 0; n < neighbors; n++) {
		float x = static_cast<float>(-radius*sin(2 * CV_PI*n / static_cast<float>(neighbors)));
		float y = static_cast<float>(radius*cos(2 * CV_PI*n / static_cast<float>(neighbors)));
		int fx = static_cast<int>(floor(x));
		int fy = static_cast<int>(floor(y));
		int cx = static_cast<int>(ceil(x));
		int cy = static_cast<int>(ceil(y));

		float tx = x - fx;
		float ty = y - fy;

		float w1 = (1 - tx) * (1 - ty);
		float w2 = tx  * (1 - ty);
		float w4 = (1 - tx) *      ty;
		float w3 = tx  *      ty;

		//float t = static_cast<float>(w1*src.at<float>(i + cx, j + cy) + w2*src.at<float>(i + fx, j + cy) + w3*src.at<float>(i + fx, j + fy) + w4*src.at<float>(i + cx, j + fy));
	}
}
void findRidge(cv::Mat& src, cv::Mat ridge) {
	// @srcÊÇÒ»·ù»Ò¶ÈÍ¼
	//cv::Mat 
	for (int i = 2; i < src.rows-2; i++) {
		for (int j = 2; j < src.cols-2; j++) {
			int window[3][3];
			
			
			getNeighbor(src,cv::Point(i,j),2);
		}
	}
}
//void Counter(cv::Mat& src) {
//	cv::Mat counters;
//	
//}
#endif // !SKELETON
