#include "stdafx.h"
#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>

#include <fstream>
//my include
#include <opencv2/opencv.hpp>
#include "MyArucoDLL.h"

//https://stackoverflow.com/questions/44486169/questions-about-using-the-detect-markers-cpp-with-opencv-aruco
// ./detect_markers -d=0

using namespace std;
using namespace cv;

namespace MYARUCO {
	//VideoCapture inputVideo;
	VideoCapture * inputVideo;
	//int waitTime = 10;
	//BYTE* result;
	//int dictionaryId = 0;
	//bool estimatePose = true;
	//float markerLength = 0.1;
	//int camId = 0;
	//Mat image, imageCopy;
	//Mat camMatrix = (cv::Mat_<float>(3, 3)
	//	<< 741.20552174, 0, 400.13630197, 0, 741.20552174, 257.56731571, 0, 0, 1 //left
	//	);
	//Mat distCoeffs = (cv::Mat_<float>(5, 1)
	//	<< 0.04827601, -0.02498645, -0.02017935, 0.00854179, 0.00281892
	//	);

	//Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));

	void Initialize()
	{
		inputVideo = new cv::VideoCapture(0);
		//inputVideo.open(camId);
	}


	BYTE * MyAruco() {
		BYTE* result;
		int dictionaryId = 0;
		bool estimatePose = true;
		float markerLength = 0.1;
		int waitTime = 10;
		Mat camMatrix = (cv::Mat_<float>(3, 3)
			<< 741.20552174, 0, 400.13630197, 0, 741.20552174, 257.56731571, 0, 0, 1 //left
			);
		Mat distCoeffs = (cv::Mat_<float>(5, 1)
			<< 0.04827601, -0.02498645, -0.02017935, 0.00854179, 0.00281892
			);

		Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));


		Mat image, imageCopy;
		//Mat camMatrix, distCoeffs;

		//while ((*inputVideo).grab()) {

		//(*inputVideo).retrieve(image);
		(*inputVideo) >> image;

		vector< int > ids;
		vector< vector< Point2f > > corners, rejected;
		vector< Vec3d > rvecs, tvecs;

		aruco::detectMarkers(image, dictionary, corners, ids);

		//ofstream myfile;
		//myfile.open("ArucoCorner.txt");
		//myfile << "Writing this to a file.\n";
		//myfile.close();

		if (ids.size() > 0) {
			aruco::estimatePoseSingleMarkers(corners, markerLength, camMatrix, distCoeffs, rvecs, tvecs);

			//https://stackoverflow.com/questions/6406356/how-to-write-vector-values-to-a-file/39746650
			//https://stackoverflow.com/questions/11610743/save-2-dimensional-vector-to-a-text-file
			ofstream output_file("C:\\opencv\\ArucoCorner.txt");
			ostream_iterator<Point2f> output_iterator(output_file, "\n");
			//std::copy(corners.begin(), corners.end(), output_iterator);
			for (const auto& vt : corners) {
				//std::copy(vt.cbegin(), vt.cend(), ostream_iterator<Point2f>(output_file, " "));
				std::copy(vt.cbegin(), vt.cend(), output_iterator);
				output_file << '\n';
			}
			output_file << '\n';
			output_file << "Size of the image:\n";
			output_file << "Col: " << image.cols << "   Row: " << image.rows << endl;
			output_file.close();

			ofstream output_fileForRot("C:\\opencv\\ArucoRotMat.txt");
			ostream_iterator<Vec3d> output_iteratorForRot(output_fileForRot, "\n");
			//output_fileForRot << '\n';
			//output_fileForRot << "Rotation Matrix:\n";
			std::copy(rvecs.begin(), rvecs.end(), output_iteratorForRot);
			output_fileForRot << '\n';
			output_fileForRot.close();
		}

		image.copyTo(imageCopy);
		if (ids.size() > 0) {
			aruco::drawDetectedMarkers(imageCopy, corners, ids);

			if (estimatePose) {
				for (unsigned int i = 0; i < ids.size(); i++) {
					aruco::drawAxis(imageCopy, camMatrix, distCoeffs, rvecs[i], tvecs[i], markerLength * 0.5f);
				}
			}
		}
		//}

		result = new BYTE[imageCopy.cols*imageCopy.rows * 3];
		memcpy(result, imageCopy.data, imageCopy.cols*imageCopy.rows * 3);
		return result;
	}

	//void FreeMem() {
	//	free(result);
	//	image.~Mat();
	//	imageCopy.~Mat();
	//}

	void TheEnd() {
		(*inputVideo).release();
		(*inputVideo).~VideoCapture();
		//	FreeMem();
	}
}//1.mp4