// l091.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>

using namespace cv;
using namespace std;

vector<Mat> readVideo(string filename) {
	VideoCapture cap("withChessBoard.MOV");
	vector<Mat> frames;
	while (1) {
		Mat frame; cap >> frame;
		if (frame.empty()) {
			break;
		}
		flip(frame, frame, -1); //flip the board across both axis.
		frames.push_back(frame);
	}
	cap.release();
	cout << "Video read" << endl;
	return frames;
}
int Checkerboard[2]{ 7,7 };

int main()
{
	
	//2,2,2
	//2,2,0
	vector<Point3f> vertices = {
		Point3f(2, 2, 0), Point3f(2, 4, 0), Point3f(4, 4, 0), Point3f(4, 2, 0),
		Point3f(2, 2, 1), Point3f(2, 4, 1), Point3f(4, 4, 1), Point3f(4, 2, 1) };
	vector<vector<int>> edges = { {0, 1}, {1, 2}, {2, 3}, {3, 0},
								  {4, 5}, {5, 6}, {6, 7}, {7, 4},
								  {0, 4}, {1, 5}, {2, 6}, {3, 7} };
	vector<Mat> videoInput = readVideo("withChessBoard.MOV");
	vector<Mat> project = videoInput;
	vector<Point2f> corners;
	vector<Mat> frames;
	Mat gray;
	bool success;
	vector<vector<Point3f>> objPoints; //3d points
	vector<vector<Point2f>> imgPoints; //2d points
	vector<Point3f> objp;
	for (int i = 0; i < Checkerboard[1]; i++) {
		for (int j = 0; j < Checkerboard[0]; j++) {
			objp.push_back(Point3f(j, i, 0));
		}
	}
	for (int i = 0; i < videoInput.size(); i+=20) {
		cvtColor(videoInput[i], gray, COLOR_BGR2GRAY);
		success = findChessboardCorners(gray, Size(Checkerboard[0], Checkerboard[1]), corners, CALIB_CB_ADAPTIVE_THRESH+CALIB_CB_NORMALIZE_IMAGE+CALIB_CB_FAST_CHECK);
		if (success) {
			cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1), TermCriteria(TermCriteria::COUNT+TermCriteria::EPS,30,.001));
			drawChessboardCorners(videoInput[i], Size(Checkerboard[0], Checkerboard[1]), corners, success); 
			objPoints.push_back(objp);
			imgPoints.push_back(corners);
		}
	}
	//cout << objPoints.size() << "," << imgPoints.size() << endl;
	//cout << obj20.size() << "," << img20.size() << endl;
	Mat camera, dist, rotation, translation;
	////cout << gray.rows << " " << gray.cols << endl;
	calibrateCamera(objPoints, imgPoints, Size(gray.rows, gray.cols), camera, dist, rotation, translation);
	cout << "Camera Calibrated" << endl;
	vector<Point2f> lastCorners;
	for (int i = 0; i < videoInput.size(); i++) { //changed to 20
		Mat R2, T2;
		vector<Point2f> image;
		success = findChessboardCorners(gray, Size(Checkerboard[0], Checkerboard[1]), corners, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);
		if (success) {
			solvePnP(objp, corners, camera, dist, R2, T2); //does not update R2 and T2. 
			//cout << R2 << endl;
			//cout << T2 << endl;
			projectPoints(vertices, R2, T2, camera, dist, image);
			//for (int t = 0; t < image.size(); t++) {
			//	cout << image[t] << " ";
			//}
			//cout << endl;
			lastCorners = corners;
		}
		Mat pic = videoInput[i];
		for (int j = 0; j < edges.size(); j++) {
			Point2f coord1 = image[edges[j][0]];
			Point2f coord2 = image[edges[j][1]];
			line(pic, coord1, coord2, Scalar(0, 255, 255), 2);
		}
		frames.push_back(pic);
		//cout << pic.rows << " " << pic.cols << endl;
		//line(image, Point(image[edges], coord1y + 300), Point(coord2x + 400, coord2y + 300), Scalar(0, 255, 255), 2);
		//obj points-pooints like in lab 8 and edges like in lab 8
	}
	cout << "Cube Rendered" << endl;
	VideoWriter writer("vr.avi", VideoWriter::fourcc('m', 'p', '4', 'v'), 30, Size(gray.cols,gray.rows));
	for (int i = 0; i < frames.size(); i++) {
		writer.write(frames[i]);
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
