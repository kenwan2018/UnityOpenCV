/**
* @file Morphology_1.cpp
* @brief Erosion and Dilation sample code
* @author OpenCV team
*/
#include "stdafx.h"
#include "BackgroundSubtraction.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;



namespace BackgroundSubtraction
{
	cv::VideoCapture *cap;
	BYTE* result;

	void Functions::Initialize()
	{
		cap = new cv::VideoCapture(0);
	}

	BYTE* Functions::ProcessFrame() {
		cv::Mat image;
		cv::Mat betterImage;

		//BYTE* result;

		(*cap) >> image;

		cv::flip(image, image, 0);

		cv::cvtColor(image, betterImage, COLOR_BGR2BGRA, 4);

		result = new BYTE[image.cols*image.rows * 4];

		memcpy(result, betterImage.data, betterImage.cols*image.rows * 4);
		return result;
	}

	void Functions::freeMemory() {
		free(result);
	}
}

