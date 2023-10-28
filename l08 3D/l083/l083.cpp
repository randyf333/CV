// l081.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>

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
			/*vertices = (Mat_<double>(8,3) << 1,1,1,1,1,-1,1,-1,1)*/
			Mat c1 = (Mat_<double>(3, 1) << 1, 1, 1); //a-0
			Mat c2 = (Mat_<double>(3, 1) << 1, 1, -1); //b-1
			Mat c3 = (Mat_<double>(3, 1) << 1, -1, 1); //c-2
			Mat c4 = (Mat_<double>(3, 1) << 1, -1, -1); //d-3
			Mat c5 = (Mat_<double>(3, 1) << -1, 1, 1);//e-4
			Mat c6 = (Mat_<double>(3, 1) << -1, 1, -1);//f-5
			Mat c7 = (Mat_<double>(3, 1) << -1, -1, 1);//g-6
			Mat c8 = (Mat_<double>(3, 1) << -1, -1, -1);//h-7
			vertices = { c1,c2,c3,c4,c5,c6,c7,c8 };
			edges = { {0,1},{0,2},{0,4},{1,5},{1,3},{3,7},{2,3},{2,6},{5,7},{4,5},{4,6},{6,7} };
		}
		if (n == 6) {
			Mat c1 = (Mat_<double>(3, 1) << 0, 0, 1);//e-0
			Mat c2 = (Mat_<double>(3, 1) << -1, 0, 0); //b-1
			Mat c3 = (Mat_<double>(3, 1) << 0, 1, 0); //c-2
			Mat c4 = (Mat_<double>(3, 1) << 0, -1, 0); //d-3
			Mat c5 = (Mat_<double>(3, 1) << 1, 0, 0); //a-4
			Mat c6 = (Mat_<double>(3, 1) << 0, 0, -1);//f-5
			vertices = { c1, c2, c3, c4, c5, c6 };
			edges = { {0,1},{0,2},{0,4},{0,3},{1,2},{1,3},{1,5},{2,4},{2,5},{3,4},{3,5}, {4,5} };
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
	double planex = 400, planey = 0, planez = 0; //update this to be pickable and mat
	double camerax = 500, cameray = 0, cameraz = 0; //update this to be pickable and mat
	Mat plane;
	Mat camera;
	Mat normal;

public:
	double checkMat(Mat vertex, Mat point, Mat perpen) { //point is point on plane, perpen is normal vector
		return (vertex - point).dot(perpen);
	}
	void makeScaling(double factor) { //make scaling matrix
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
	void pickPlane(double x, double y, double z) {
		plane = (Mat_<double>(3, 1) << x, y, z);
	}
	void pickCamera(double x, double y, double z) {
		camera = (Mat_<double>(3, 1) << x, y, z);
	}
	void pickNormal(double x, double y, double z) {
		normal = (Mat_<double>(3, 1) << x, y, z);
	}
	void render(vector<Mat>& points, Shape3D shape, vector<Mat>& frames, int& count2, ofstream& out2, ofstream& logfile, Mat& finalMat, bool toLog) { //make frame Change for 8.2
		Mat image = Mat::zeros(600, 800, CV_8UC3);
		vector<vector<int>> edges = shape.getEdges();
		vector<vector<double>> coords;
		vector<Mat> projections;
		for (int i = 0; i < points.size(); i++) { //update this
			//double t;
			//t = (planex - points[i].at<double>(0, 0)) / (camerax - points[i].at<double>(0, 0));
			Mat prime = ((plane - camera).dot(normal) / ((points[i] - camera).dot(normal))) * (points[i] - camera) + camera;
			//Mat prime = (t * (points[i] - camera)) + camera; //3d projection coords
			projections.push_back(prime);
		}

		for (int j = 0; j < projections.size(); j++) {
			double coord1;
			double coord2;
			//Mat project = projections[j].t();
			Mat solution = finalMat.inv() * projections[j];
			coord1 = solution.at<double>(0, 1);
			coord2 = solution.at<double>(0, 2);
			circle(image, Point(coord1 + 400, coord2 + 300), 5, Scalar(255, 255, 255), FILLED);
			if (count2 < 4 && toLog) {
				out2 << "(" << coord1 << "," << coord2 << ")" << " ";
				logfile << "The frame" << count2 + 1 << " in 3d has the following edges:" << endl;
				for (int k = 0; k < edges.size(); k++) { logfile << points[edges[k][0]].t() << ", " << points[edges[k][1]].t() << endl; } logfile << endl;
				logfile << "The frame" << count2 + 1 << " in 2d has the following edges:" << endl;
				for (int k = 0; k < edges.size(); k++) { logfile << projections[edges[k][0]].t() << ", " << projections[edges[k][0]].t() << endl; } logfile << endl;
				count2++;
			}
			vector<double> coordbit = { coord1, coord2 };
			coords.push_back(coordbit);
		}

		out2 << endl;
		for (int j = 0; j < edges.size(); j++) {
			vector<int> edge = edges[j];
			double coord1x = coords[edge[0]][0];
			double coord1y = coords[edge[0]][1];
			double coord2x = coords[edge[1]][0];
			double coord2y = coords[edge[1]][1];
			line(image, Point(coord1x + 400, coord1y + 300), Point(coord2x + 400, coord2y + 300), Scalar(0, 255, 255), 2);
		}
		frames.push_back(image);
	}
	Mat parse(string input) {
		// Input format: [x, y, z]

		input = input.substr(1, input.length() - 2);

		vector<string> splitInput; string delimiter = ", "; size_t pos = 0; string token;
		while ((pos = input.find(delimiter)) != string::npos) {
			token = input.substr(0, pos);
			splitInput.push_back(token);
			input.erase(0, pos + delimiter.length());
		}
		splitInput.push_back(input);


		vector<double> doubleInput;
		for (int i = 0; i < splitInput.size(); i++) { doubleInput.push_back(stod(splitInput[i])); }
		Mat output = (Mat_<double>(3, 1) << doubleInput[0], doubleInput[1], doubleInput[2]);

		return output;
	}
	void doParts(Shape3D& shape, vector<Mat>& frames, ofstream& out, ofstream& logFile, ofstream& out2, bool toLog) {
		vector<Mat> points = shape.getVertices();
		//pickCamera(500, 0, 0);
		//pickNormal(1, 0, 0);
		//pickPlane(400, 0, 0);
		double controlPoint = (points[0] - plane).dot(normal) * 100;
		for (int i = 1; i < points.size(); i++) {
			if ((points[i] - plane).dot(normal) * 100 * controlPoint < 0) {
				cout << "Not all points are on one side of the plane. Using default values." << endl;
				//camera = (Mat_<double>(1, 3) << 3, 0, 0); onPlane = (Mat_<double>(1, 3) << 2, 0, 0); planeNormal = (Mat_<double>(1, 3) << 1, 0, 0);
				pickCamera(500, 0, 0);
				pickNormal(1, 1, 1);
				pickPlane(300, 400, 100);
				break;
			}
		}

		//Check that the camera position is on the opposite side of the plane from the points
		if ((camera - plane).dot(normal) * controlPoint > 0) {
			cout << "Camera is on the same side of the plane as the points. Using default values." << endl;
			//camera = (Mat_<double>(1, 3) << 3, 0, 0); onPlane = (Mat_<double>(1, 3) << 2, 0, 0); planeNormal = (Mat_<double>(1, 3) << 1, 0, 0);
			pickCamera(500, 0, 0);
			pickNormal(1, 1, 1);
			pickPlane(300, 400, 100);
		}
		//Mat temp = rotMatx * rotMaty;
		vector<Mat> newPoints(points.size());
		vector<Mat> renderPoints(points.size());
		int count = 0;
		int count2 = 0;
		vector<Mat> projections;
		//cout << count << endl;
		bool projectCheck = false;
		Mat finalMat;
		for (int times = 0; times < 1000; times++) { //change back to 1000
			for (int i = 0; i < newPoints.size(); i++) {
				newPoints[i] = rotMatx * rotMaty * rotMatz * points[i];
			}
			for (int i = 0; i < newPoints.size(); i++) {
				renderPoints[i] = scaleMat * newPoints[i];
				//if (vertCheck == false) {
				//	logFile << "v" << i + 1 << " = " << "(" << renderPoints[i].at<double>(0, 0) << "," << renderPoints[i].at<double>(0, 1) << "," << renderPoints[i].at<double>(0, 2) << ")" << endl;
				//}
				if (count < 4) {
					out << "(" << renderPoints[i].at<double>(0, 0) << "," << renderPoints[i].at<double>(0, 1) << "," << renderPoints[i].at<double>(0, 2) << ")" << " ";
				}
			}
			if (projectCheck == false) {
				for (int i = 0; i < 3; i++) { //update this
					//double t;
					//t = (planex - points[i].at<double>(0, 0)) / (camerax - points[i].at<double>(0, 0));
					Mat prime = ((plane - camera).dot(normal) / ((renderPoints[i] - camera).dot(normal))) * (renderPoints[i] - camera) + camera;
					//Mat prime = (t * (points[i] - camera)) + camera; //3d projection coords
					projections.push_back(prime);
				}

				Mat u2 = projections[1] - projections[0];
				Mat u = u2 / norm(u2);
				Mat v2 = projections[2] - projections[0];
				Mat v = v2 - (v2.dot(u) / u.dot(u)) * u;
				v = v / norm(v);
				Mat origin = ((plane - camera).dot(normal) / ((-1 * camera).dot(normal))) * (-1 * camera) + camera;
				if (toLog){
					for (int i = 0; i < 3; i++) {
						logFile << "v" << i + 1 << " = " << renderPoints[i].t() << endl;
					}
					logFile << endl;
					for (int i = 0; i < 3; i++) {
						logFile << "pv" << i + 1 << " = " << projections[i].t() << endl;
					}
					logFile << endl;
					logFile << "The 2 vectors a and b that are in plane are:" << endl;
					logFile << "a = pv1 - pv2" << u2.t() << endl;
					logFile << "b = pv3 - pv1" << v2.t() << endl << endl;
					logFile << "The w1 and w2 obtained from a and b (these now are perpendicular and of magnitude 1) are:" << endl;
					logFile << "w1 = " << u.t() << endl;
					logFile << "w2 = " << v.t() << endl << endl;
					logFile << "The center of the cube in first frame and its projection are:" << endl;
					logFile << "center = " << "[0, 0, 0]" << endl;
					logFile << "p0 = " << origin.t() << endl << endl;

					logFile << "The coordinates in the 2d plane x = p0 + u*w1 + v*w2 are:" << endl;
					logFile << "P0 = " << origin.t() << endl;
					logFile << "w1 = " << u.t() << endl;
					logFile << "w2 = " << v.t() << endl;
				}
				hconcat(origin, u, finalMat);
				hconcat(finalMat, v, finalMat);
				finalMat = finalMat.t();
			}
			projectCheck = true;
			//vertCheck = true;
			render(renderPoints, shape, frames, count2, out2, logFile, finalMat, toLog);
			//cout << count2;
			points = newPoints;
			//cout << points.size() << endl;
			if (count < 4) {
				out << endl;
			}
			count++;
		}
	}
	void partt1(int argc, char* argv[]) {
		pickPlane(700.5, 200.1, 100.12);
		pickNormal(1, 2, 3.12);
		pickCamera(1000, 900.23, 100.1156);
		for (int i = 0; i < argc - 1; i++) {
			if (strcmp(argv[i], "-a") == 0) { plane = parse(argv[i + 1]); }
			else if (strcmp(argv[i], "-n") == 0) { normal = parse(argv[i + 1]); }
			else if (strcmp(argv[i], "-e") == 0) { camera = parse(argv[i + 1]); }
		}
		vector<Mat> cubeframes;
		vector<Mat> octframes;
		ofstream out;
		out.open("coordinates.txt");
		ofstream out2;
		out2.open("coordinates2D.txt");
		ofstream logFile;
		logFile.open("log.txt");
		logFile << "The plane defined by (x-a)*n =0 is:" << endl;
		logFile << "a = " << plane.t() << endl;
		logFile << "n = " << normal.t() << endl;
		logFile << "The eye e is: " << endl;
		logFile << "e = " << camera.t() << endl << endl;
		logFile << "Vertices I used to create the 2d coordinate system and their projections are:" << endl;

		makeScaling(100);//change back to 100
		Shape3D cube(8);
		//int times = 1; //rate of rotation for the image
		makeRotx(.05);
		makeRoty(.05);
		makeRotz(.05);
		doParts(cube,cubeframes,out,logFile,out2, true);

		Shape3D oct(6);
		doParts(oct, octframes, out, logFile, out2, false);
		VideoWriter writer("rotation.avi", VideoWriter::fourcc('m', 'p', '4', 'v'), 60, Size(800, 600));
		for (int i = 0; i < cubeframes.size(); i++) {
			writer.write(cubeframes[i]);
		}
		for (int i = 0; i < octframes.size(); i++) {
			writer.write(octframes[i]);
		}
		writer.release();
	}
};
int main(int argc, char* argv[])
{
	Projection a;
	a.partt1(argc, argv);
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
