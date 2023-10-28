// l081.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <map>

using namespace cv;
using namespace std;

class Shape3D {
private:
	//map<Point3d, vector<Point3d>> connections;
	vector<Mat> vertices;
	vector<vector<int>>edges;
public:
	Shape3D(int n) {
		if (n == 8) {
			Mat c1 = (Mat_<double>(3, 1) << 1, 1, 1); //a-0
			Mat c2 = (Mat_<double>(3, 1) << 1, 1, -1); //b-1
			Mat c3 = (Mat_<double>(3, 1) << 1, -1, 1); //c-2
			Mat c4 = (Mat_<double>(3, 1) << 1, -1, -1); //d-3
			Mat c5 = (Mat_<double>(3, 1) << -1, 1, 1);//e-4
			Mat c6 = (Mat_<double>(3, 1) << -1, 1, -1);//f-5
			Mat c7 = (Mat_<double>(3, 1) << -1, -1, 1);//g-6
			Mat c8 = (Mat_<double>(3, 1) << -1, -1, -1);//h-7
			vertices.push_back(c1);
			vertices.push_back(c2);
			vertices.push_back(c3);
			vertices.push_back(c4);
			vertices.push_back(c5);
			vertices.push_back(c6);
			vertices.push_back(c7);
			vertices.push_back(c8);
			edges = { {0,1},{0,2},{0,4},{1,5},{1,3},{3,7},{2,3},{2,6},{5,7},{4,5},{4,6},{6,7} };
		}
		if (n == 6) {
			Mat c1 = (Mat_<double>(3, 1) << 1, 0, 0); //a-0
			Mat c2 = (Mat_<double>(3, 1) << -1, 0, 0); //b-1
			Mat c3 = (Mat_<double>(3, 1) << 0, 1, 0); //c-2
			Mat c4 = (Mat_<double>(3, 1) << 0, -1, 0); //d-3
			Mat c5 = (Mat_<double>(3, 1) << 0, 0, 1);//e-4
			Mat c6 = (Mat_<double>(3, 1) << 0, 0, -1);//f-5
			edges = { {0,2},{0,3},{0,4},{0,5},{1,2},{1,3},{1,4},{1,5},{2,4},{2,5},{3,4},{3,5} };
		}
	}
	vector<Mat> getVertices() {
		return vertices;
	}
	vector<vector<int>> getEdges() {
		return edges;
	}

};
class Projection {
private:
	Mat scaleMat = Mat(3, 3, CV_64F, Scalar::all(0));
	Mat transMat = Mat(3, 3, CV_64F, Scalar::all(0));
	Mat rotMatx;
	Mat rotMaty;
	Mat rotMatz;
	int width = 800;
	int height = 600;
public:
	void makeScaling(double factor) { //ake scaling matrix
		scaleMat.at<double>(0, 0) = factor;
		scaleMat.at<double>(1, 1) = factor;
		//scaleMat.at<double>(2, 2) = factor;
		scaleMat.at<double>(2, 2) = factor;
	}
	void makeTrans(double factor) { //make translation matrix
		transMat.at<double>(0, 0) = 1;
		transMat.at<double>(1, 1) = 1;
		transMat.at<double>(2, 2) = 1;
		//transMat.at<double>(3, 3) = 1;
		transMat.at<double>(0, 2) = factor;
		transMat.at<double>(1, 2) = factor;
		transMat.at<double>(2, 2) = factor;
	}
	void makeRotx(double theta) { //make rotation matrix
		rotMatx = (Mat_<double>(3, 3) << 1, 0, 0, 0, cos(theta), -sin(theta), 0, sin(theta), cos(theta));
	}
	void makeRoty(double theta) {
		rotMaty = (Mat_<double>(3, 3) << cos(theta), 0, sin(theta), 0, 1, 0, -sin(theta), 0, cos(theta));
	}
	void makeRotz(double theta) {
		rotMatz = (Mat_<double>(3, 3) << cos(theta), -sin(theta), 0, sin(theta), cos(theta), 0, 0, 0, 1);
	}

	void render(vector<Mat>& points, Shape3D shape, vector<Mat>& frames) { //make frame Change for 8.2
		Mat image = Mat::zeros(600, 800, CV_8UC3);
		vector<vector<int>> edges = shape.getEdges();
		for (int i = 0; i < points.size(); i++) {
			circle(image, Point(points[i].at<double>(0, 0) + 400, points[i].at<double>(0, 1) + 300), 5, Scalar(255, 255, 255), FILLED);
		}
		for (int j = 0; j < edges.size(); j++) {
			vector<int> edge = edges[j];
			Mat p1 = points[edge[0]];
			Mat p2 = points[edge[1]];
			line(image, Point(p1.at<double>(0, 0) + 400, p1.at<double>(0, 1) + 300), Point(p2.at<double>(0, 0) + 400, p2.at<double>(0, 1) + 300), Scalar(0, 255, 255), 2);
		}
		frames.push_back(image);
	}

	void partt1() {
		ofstream out;
		out.open("coordinates.txt");
		makeScaling(100);
		Shape3D cube(8);
		//int times = 1; //rate of rotation for the image
		makeRotx(.05);
		makeRoty(.05);
		makeRotz(.05);
		vector<Mat> points = cube.getVertices();
		//for (int j = 0; j < points.size(); j++) {
		//	//cout << points[j].at<double>(0, 0) << "and " << points[j].at<double>(0, 1) << endl;
		//	points[j] = rotMatx * rotMaty * points[j];
		//}
		vector<Mat> frames;
		//Mat temp = rotMatx * rotMaty;
		vector<Mat> newPoints(points.size());
		vector<Mat> renderPoints(points.size());
		int count = 0;
		for (int times = 0; times < 1000; times++) {
			for (int i = 0; i < newPoints.size(); i++) {
				newPoints[i] = rotMatx * rotMaty * rotMatz * points[i];

			}
			for (int i = 0; i < newPoints.size(); i++) {
				renderPoints[i] = scaleMat * newPoints[i];
				if (count < 4) {
					out << "(" << renderPoints[i].at<double>(0, 0) << "," << renderPoints[i].at<double>(0, 1) << "," << renderPoints[i].at<double>(0, 2) << ")" << " ";
				}
			}
			if (count < 4) {
				out << endl;
			}
			count++;
			render(renderPoints, cube, frames);
			points = newPoints;
			//cout << points.size() << endl;
		}
		VideoWriter writer("rotation.avi", VideoWriter::fourcc('m', 'p', '4', 'v'), 60, Size(800, 600));
		for (int i = 0; i < frames.size(); i++) {
			writer.write(frames[i]);
		}
		writer.release();
	}
};
int main()
{
	Projection a;
	a.partt1();
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
