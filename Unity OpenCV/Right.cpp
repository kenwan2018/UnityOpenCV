#include "stdafx.h"
#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>

#include <fstream>
#include <opencv2/opencv.hpp>
#include "Right.h"


using namespace std;
using namespace cv;

namespace RIGHT {
	VideoCapture * inputVideoR; 

	void InitializeR()
	{
		inputVideoR = new cv::VideoCapture(1);
	}

	BYTE * MyArucoR() {
		BYTE* resultR;
		int dictionaryId = 0;
		bool estimatePose = true;
		float markerLength = 0.1;
		int waitTime = 10;
		Mat camMatrixR = (cv::Mat_<float>(3, 3)
			<< 741.20552174, 0, 400.13630197, 0, 741.20552174, 257.56731571, 0, 0, 1 //left
			);
		Mat distCoeffsR = (cv::Mat_<float>(5, 1)
			<< 0.04827601, -0.02498645, -0.02017935, 0.00854179, 0.00281892
			);

		Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));

		Mat imageR, imageCopyR;

		(*inputVideoR) >> imageR;

		vector< int > ids;
		vector< vector< Point2f > > cornersR, rejectedR;
		vector< Vec3d > rvecsR, tvecsR;

		aruco::detectMarkers(imageR, dictionary, cornersR, ids);

		if (ids.size() > 0) {
			aruco::estimatePoseSingleMarkers(cornersR, markerLength, camMatrixR, distCoeffsR, rvecsR, tvecsR);

			ofstream output_file("C:\\opencv\\ArucoCornerR.txt");
			ostream_iterator<Point2f> output_iterator(output_file, "\n");
			for (const auto& vt : cornersR) {
				std::copy(vt.cbegin(), vt.cend(), output_iterator);
				output_file << '\n';
			}
			output_file << '\n';
			output_file << "Size of the image:\n";
			output_file << "Col: " << imageR.cols << "   Row: " << imageR.rows << endl;
			output_file.close();

			ofstream output_fileForRot("C:\\opencv\\ArucoRotMatR.txt");
			ostream_iterator<Vec3d> output_iteratorForRot(output_fileForRot, "\n");
			//output_fileForRot << "Rotation Matrix:\n";
			std::copy(rvecsR.begin(), rvecsR.end(), output_iteratorForRot);
			output_fileForRot.close();
		}

		imageR.copyTo(imageCopyR);
		if (ids.size() > 0) {
			aruco::drawDetectedMarkers(imageCopyR, cornersR, ids);

			if (estimatePose) {
				for (unsigned int i = 0; i < ids.size(); i++) {
					aruco::drawAxis(imageCopyR, camMatrixR, distCoeffsR, rvecsR[i], tvecsR[i], markerLength * 0.5f);
				}
			}
		}

		resultR = new BYTE[imageCopyR.cols*imageCopyR.rows * 3];
		memcpy(resultR, imageCopyR.data, imageCopyR.cols*imageCopyR.rows * 3);
		return resultR;
	}

	//void FreeMem() {
	//	free(result);
	//	image.~Mat();
	//	imageCopy.~Mat();
	//}

	void TheEndR() {
		(*inputVideoR).release();
		(*inputVideoR).~VideoCapture();
		//	FreeMem();
	}
}
