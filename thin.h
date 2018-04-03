#ifndef THIN
#define THIN

#include<opencv2/opencv.hpp>
#include<string>
#include <windows.h>
//define patterns
//patterns defined in "Image Processing, Analysis, and Machine Vision Fourth Edition, Milan Sonka et. al."
const int L1[3][3] = {
	{0,0,0},
	{2,1,2},
	{1,1,1} };
const int L2[3][3] = {
	{ 1,2,0 },
	{ 1,1,0 },
	{ 1,2,0 } };
const int L3[3][3] = {
	{ 1,1,1 },
	{ 2,1,2 },
	{ 0,0,0 } };
const int L4[3][3] = {
	{ 0,2,1 },
	{ 0,1,1 },
	{ 0,2,1 } };
/*
const int L5[3][3] = {
	{ 2,0,0 },
	{ 1,1,0 },
	{ 2,1,2 } };
const int L6[3][3] = {
	{ 2,1,2 },
	{ 1,1,0 },
	{ 2,0,0 } };
const int L7[3][3] = {
	{ 2,1,2 },
	{ 0,1,1 },
	{ 0,0,2 } };
const int L8[3][3] = {
	{ 0,0,2 },
	{ 0,1,1 },
	{ 2,1,2 } };*/
auto L_Set = { L1,L2,L3,L4 };// , L5, L6, L7, L8 };
//
//bool dirExists(const std::string& dirName_in)
//{
//	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
//	if (ftyp == INVALID_FILE_ATTRIBUTES)
//		return false;  //something is wrong with your path!
//
//	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
//		return true;   // this is a directory!
//
//	return false;    // this is not a directory!
//}

void createFolder(std::string dirName) {
	std::string commandMd = "mkdir " + dirName;
	std::string commandRd = "rmdir /s /q " + dirName;
	if (std::system(commandMd.c_str()))
	{
		std::cout << "remove dir:output, and re-makedir" << std::endl;
		std::system(commandRd.c_str());
	}
	std::system(commandMd.c_str());
}

bool compare(cv::Mat& src, const int pattern[][3]) {
	bool flag = false;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!src.at<uchar>(i, j) && pattern[i][j] == 1) {
				flag = false;
				return flag;
			}else if (src.at<uchar>(i, j) && pattern[i][j] == 0) {
				flag = false;
				return flag;
			}else
				flag = true;
		}
	}
	return flag;
}
void findContour(cv::Mat& src, std::vector<cv::Point>& outlines) {
	//std::string dirName = "./output_Contours";
	//createFolder(dirName);
	cv::Mat temp = src.clone();
	const int B[][3] = { {1,1,1},{1,1,1},{1,1,1} };
	for (int i = 1; i < src.rows-1; i++) {
		for (int j = 1; j < src.cols-1; j++) {
			cv::Mat roi = src(cv::Range(i - 1, i + 2), cv::Range(j - 1, j + 2));
			if (compare(roi, B))
				temp.at<uchar>(i, j) = 0;
		}
	}
	for (int i = 1; i < src.rows - 1; i++) {
		for (int j = 1; j < src.cols - 1; j++) {
			if (temp.at<uchar>(i,j))
			outlines.push_back(cv::Point2i(i, j));
		}
	}
	//cv::imwrite(dirName+"/outlines.jpg", temp);
}
bool thinning_it(cv::Mat& src,cv::Mat& ridge) {
	ridge = src.clone();
	int flag = false;
	for (auto pattern : L_Set) {
		if (flag)
			return flag;
		else	
			flag = true;

		std::vector<cv::Point2i> outlines;
		findContour(src, outlines);
		if (outlines.empty())
		{
			std::cout << "No skeleton" << std::endl;
			return true;
		}
		for (cv::Point2i point : outlines) {
			int i = point.x;
			int j = point.y;
			cv::Mat roi = src(cv::Range(i - 1, i + 2), cv::Range(j - 1, j + 2));
			if (src.at<uchar>(i, j) && compare(roi, pattern))
			{
				ridge.at<uchar>(i, j) = 0;
				flag = false;
			}

		}
	}
	return flag;
}

void thinning(cv::Mat& src, cv::Mat& ridge) {
	std::string dirName = "output";
	createFolder(dirName);
	int i = 0;
	bool flag = false;
	ridge = src.clone();
	do{
		flag = thinning_it(ridge.clone(), ridge);
		std::cout << i << std::endl;
		 std::string name = dirName+"/result"+ std::to_string(i++)+".jpg";
		cv::imwrite(name, ridge);
	} while (!flag);
	
}


#endif // !THIN

