// l031.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <list>
#include <iterator>
#include <iomanip>
#include <sstream>
#include <vector>
#include <math.h>
#include <ctime>
#include <algorithm>
#define XSIZE  800
#define YSIZE  800

using namespace std;

class doublePoint {
private:
    double xcoor;
    double ycoor;
public:
    doublePoint() {
        xcoor = 0.0;
        ycoor = 0.0;
    }
    doublePoint(double x, double y) { //constructor
        xcoor = x;
        ycoor = y;
    }
    ~doublePoint() {

    }
    double getX() { return xcoor; }
    double getY() { return ycoor; }
    void setX(double value) { xcoor = value; }
    void setY(double value) { ycoor = value; }
    std::string toString() {
        std::ostringstream streamObj;
        streamObj << std::fixed;
        streamObj << std::setprecision(23);
        streamObj << std::to_string(xcoor) + "," + std::to_string(ycoor);
        std::string s = streamObj.str();
        return s;
    }
    bool operator < (const doublePoint& str) const {
        return (xcoor < str.xcoor);
    }
};//randomPoint

class Point { //for rendering
private:
    int xcoor;
    int ycoor;
public:
    Point() {
        xcoor = 0;
        ycoor = 0;
    }
    Point(int x, int y) { //constructor
        //dxcoor = (double)random between 0-1
        //dycoor = (double)random between 0-1 
        xcoor = x;
        ycoor = y;
    }
    int getX() { return xcoor; }
    int getY() { return ycoor; }
};
class Circle {
private:
    int radius;
    int centerx;
    int centery;
    double dcx;
    double dcy;
    double dradius;
public:
    Circle() {
        centerx = 0;
        centery = 0;
        radius = 0;
        dcx = dcy = dradius = 0;
    }
    Circle(int radi, int x, int y, double xcoord, double ycoord, double dr) {
        radius = radi;
        centerx = x;
        centery = y;
        dcx = xcoord;
        dcy = ycoord;
        dradius = dr;
    }
    void drawCircle(int** arr, int xsize, int ysize, int color) {//, int color) {//radius, center xcoord, center ycoord
        int xmax = (int)(radius / sqrt(2));
        int y = radius;
        int y2 = y * y;
        int ty = (2 * y) - 1;
        int y2_new = y2;
        for (int x = 0; x <= xmax + 2; x++) {
            if ((y2 - y2_new) >= ty) {
                y2 -= ty;
                y -= 1;
                ty -= 2;
            }
            if (centerx + x < xsize) {
                if (centery + y < ysize) {
                    arr[centerx + x][centery + y] = color;
                }
                if (centery - y >= 0) {
                    arr[centerx + x][centery - y] = color;
                }
            }
            if (centerx - x >= 0) {
                if (centery + y < ysize) {
                    arr[centerx - x][centery + y] = color;
                }
                if (centery - y >= 0) {
                    arr[centerx - x][centery - y] = color;
                }
            }
            if (centerx + y < xsize) {
                if (centery + x < ysize) {
                    arr[centerx + y][centery + x] = color;
                }
                if (centery - x >= 0) {
                    arr[centerx + y][centery - x] = color;
                }
            }
            if (centerx - y >= 0) {
                if (centery + x < ysize) {
                    arr[centerx - y][centery + x] = color;
                }
                if (centery - x >= 0) {
                    arr[centerx - y][centery - x] = color;
                }
            }
            y2_new -= (2 * x) - 3;
        }
    }
    int getX() {
        return centerx;
    }
    int getY() {
        return centery;
    }
    int getRadius() {
        return radius;
    }
    double getDX() {
        return dcx;
    }
    double getDY() {
        return dcy;
    }
    double getdRadius() {
        return dradius;
    }
};

class pairPoints {
private:
    double distance;
    doublePoint a;
    doublePoint b;
public:
    pairPoints() {
        distance = 0;
    }
    pairPoints(double num, doublePoint first, doublePoint sec) {
        distance = num;
        a = first;
        b = sec;
    }
    double getDist() {
        return distance;
    }
    doublePoint getPointA() {
        return a;
    }
    doublePoint getPointB() {
        return b;
    }
    pairPoints findMin(pairPoints comp1, pairPoints comp2) {
        if (comp1.getDist() < comp2.getDist()) {
            return comp1;
        }
        else {
            return comp2;
        }
    }
};

class doParts {
public:
    static double generateCoord() {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<double> distr(0, 1);
        return distr(eng);
    }
    static doublePoint generatePoints() { //generate random points;
        doublePoint point(generateCoord(), generateCoord());
        return point;
    }
    static void part0() {
        std::string s;
        std::cout << "Generate Random Points? ";
        std::cin >> s;
        if (s == "yes" || s == "Yes" || s == "YES" || s == "Y" || s == "y") {
            double x;
            cout << "What size? ";
            cin >> x;
            std::ofstream file;
            file.open("points.txt");
            for (int i = 0; i < x; i++) {//change value to make larger
                doublePoint point = generatePoints();
                file << std::fixed << std::setprecision(23) << point.getX() << " " << point.getY() << std::endl;
            }
            file.close();
            std::cout << "Points generated" << std::endl;
        }
    }
    static std::list<doublePoint> readFromTxt() {
        std::ifstream points;
        points.open("points.txt");
        std::string delim = " ";
        std::string line;
        std::list<doublePoint> data;
        if (points.is_open()) {
            while (getline(points, line)) {
                int delim2ind = line.find(delim);
                std::string firsttok = line.substr(1, delim2ind - 1);
                std::string sectok = line.substr(delim2ind + 1, delim2ind - 1);
                doublePoint p(stod(firsttok), stod(sectok));

                data.push_back(p);
            }
        }
        points.close();
        return data;
    }
    static std::vector<doublePoint> vreadFromTxt() {
        std::ifstream points;
        points.open("points.txt");
        std::string delim = " ";
        std::string line;
        std::vector<doublePoint> data;
        if (points.is_open()) {
            while (getline(points, line)) {
                int delim2ind = line.find(delim);
                std::string firsttok = line.substr(1, delim2ind - 1);
                std::string sectok = line.substr(delim2ind + 1, delim2ind - 1);
                doublePoint p(stod(firsttok), stod(sectok));

                data.push_back(p);
            }
        }
        points.close();
        return data;
    }
    static double findDistance(doublePoint a, doublePoint b) {
        double ax = a.getX();
        double ay = a.getY();
        double bx = b.getX();
        double by = b.getY();
        return sqrt((pow((by - ay), 2) + pow((bx - ax), 2)));
    }
    static void makePPM(int width, int height, int** arr) {
        std::ofstream image;
        image.open("output.ppm");
        image << "P3" << " " << width << " " << height << " " << "255" << std::endl;
        for (int i = 0; i < width; i++) {//print array
            for (int j = 0; j < height; j++) {
                if (arr[i][j] == 0) {
                    image << "0 0 0" << " ";
                }
                else if (arr[i][j] == 2) {
                    image << "255 0 0" << " ";
                }
                else {
                    image << "255 255 255" << " ";
                }

            }
            image << "\n";
        }
        image.close();
    }
    static int roundNum(double a) {
        return (int)((a * 800) + 0.5);
        //return (int)((a * 50) + 0.5);
    }
    static void makeTxTFile(doublePoint p1, doublePoint p2, double time) {
        std::ofstream file;
        file.open("results.txt");
        file << "(" << std::fixed << std::setprecision(17) << p1.getX() << "," << p1.getY() << ")" << std::endl;
        file << "(" << std::fixed << std::setprecision(17) << p2.getX() << "," << p2.getY() << ")" << std::endl;
        file << "Time: " << time << endl;
        file.close();
    }
    static void writeToTxt(doublePoint p1, doublePoint p2, double time) {
        std::ofstream file;
        file.open("results.txt",ios_base::app);
        file << "Recursive" << endl;
        file << "(" << std::fixed << std::setprecision(17) << p1.getX() << "," << p1.getY() << ")" << std::endl;
        file << "(" << std::fixed << std::setprecision(17) << p2.getX() << "," << p2.getY() << ")" << std::endl;
        file << "Time: " << time << endl;
        file.close();
    }
    static void rotateMatrix(int width, int height, int** arr) {//rotates 90 cclockwise then reflects over x-axis
        for (int x = 0; x < width / 2; x++) {
            for (int y = x; y < height - x - 1; y++) {
                int temp = arr[x][y];
                arr[x][y] = arr[y][width - 1 - x];
                arr[y][width - 1 - x] = arr[width - 1 - x][height - 1 - y];
                arr[width - 1 - x][height - 1 - y] = arr[height - 1 - y][x];
                arr[height - 1 - y][x] = temp;
            }
        }
        for (int row = 0; row < width; row++) {
            for (int col = 0; col < height / 2; col++) {
                int temp = arr[col][row];
                arr[col][row] = arr[height - 1 - col][row];
                arr[height - 1 - col][row] = temp;
            }
        }
    }
    static void part1() { //part1 brute force algorithm, 23 decimal places
        int** arr = new int* [XSIZE];
        for (int i = 0; i < XSIZE; i++) {
            arr[i] = new int[YSIZE];
            for (int j = 0; j < YSIZE; j++) {
                arr[i][j] = 1;
            }
        }
        std::list<doublePoint> points = readFromTxt();//read points from txt
        doublePoint first;
        doublePoint second;
        double distance = 1;
        //start timer
        clock_t start, end;
        start = clock(); 
        std::list<doublePoint>::iterator trav;
        for (trav = points.begin(); trav != points.end(); trav++) {
            doublePoint temp1 = *trav;
            Circle draw3Point(3, roundNum(temp1.getX()), roundNum(temp1.getY()), temp1.getX(), temp1.getY(), 3);
            Circle draw2Point(2, roundNum(temp1.getX()), roundNum(temp1.getY()), temp1.getX(), temp1.getY(), 2);
            draw3Point.drawCircle(arr, XSIZE, YSIZE, 0);
            draw2Point.drawCircle(arr, XSIZE, YSIZE, 0);
            std::list<doublePoint>::iterator trav2;
            for (trav2 = next(trav, 1); trav2 != points.end(); trav2++) {
                doublePoint temp2 = *trav2;
                double trydistance = findDistance(temp1, temp2);
                if (trydistance < distance) {
                    distance = trydistance;
                    first = temp1;
                    second = temp2;
                }
            }
        }
        end = clock();
        double time = (double)(end - start) / CLOCKS_PER_SEC;
        Circle close13(3, roundNum(first.getX()), roundNum(first.getY()), first.getX(), first.getY(), 3);
        Circle close12(2, roundNum(first.getX()), roundNum(first.getY()), first.getX(), first.getY(), 2);
        close12.drawCircle(arr, XSIZE, YSIZE, 2); //2 means red
        close13.drawCircle(arr, XSIZE, YSIZE, 2);

        Circle close23(3, roundNum(second.getX()), roundNum(second.getY()), second.getX(), second.getY(), 3);
        Circle close22(2, roundNum(second.getX()), roundNum(second.getY()), second.getX(), second.getY(), 2);
        close23.drawCircle(arr, XSIZE, YSIZE, 2);
        close22.drawCircle(arr, XSIZE, YSIZE, 2);
        std::cout << "First Point: " << std::fixed << std::setprecision(23) << first.getX() << "," << first.getY() << std::endl;
        std::cout << "Second Point: " << std::fixed << std::setprecision(23) << second.getX() << "," << second.getY() << std::endl;
        std::cout << "Distance: " << distance << std::endl;
        //end timer
        std::cout << "Time: " << time << std::endl;
        makeTxTFile(first, second, time);
        // 
        doParts::rotateMatrix(XSIZE, YSIZE, arr);
        doParts::makePPM(XSIZE, YSIZE, arr);

        delete[] arr;
    }
    static pairPoints bruteForce(vector<doublePoint> &points, int left, int right) {
        doublePoint a;
        doublePoint b;
        double distance = 1;
        for (int i = left; i < right; i++) {
            doublePoint temp1 = points[i];
            for (int j = i + 1; j <= right; j++) {
                doublePoint temp2 = points[j];
                double trydistance = findDistance(temp1, temp2);
                if (trydistance < distance) {
                    distance = trydistance;
                    a = temp1;
                    b = temp2;
                }
            }
        }
        pairPoints p(distance, a, b);
        return p;
    }
    static pairPoints recur(std::vector<doublePoint> &pointst, int left, int right) {
        //vector<doublePoint>& npoints = points;
        //vector<doublePoint> ppoint(&pointst[left], &pointst[right] + 1);//points(left,right);
        int mid = (left + right) / 2;
        int n = (right - left) + 1;
        if (n <= 3) {
            return bruteForce(pointst, left, right);
        }
        pairPoints p1 = recur(pointst, left, mid);
        pairPoints p2 = recur(pointst, mid, right);
        pairPoints min = p1.findMin(p1, p2);
        double distance = min.getDist();
        int leftindex = 0;
        int rightindex = pointst.size() - 1;
        for (int l = mid; l >= left; l--) {
            if (pointst[mid].getX() - pointst[l].getX() < distance) {
                leftindex = l;
            }
            else {
                break;
            }
        }
        for (int r = mid; r <= right; r++) {
            if (pointst[r].getX() - pointst[mid].getX() < distance) {
                rightindex = r;
            }
            else {
                break;
            }
        }
        for (int i = leftindex; i <= mid; i++) {
            for (int j = mid; j < rightindex + 1; j++) {
                double tempd = findDistance(pointst[i], pointst[j]);
                if (tempd < distance && i != j) {
                    distance = tempd;
                    min = pairPoints(distance, pointst[i], pointst[j]);
                }
            }
        }
        return min;
    }
    static void part2() { //recursive method
        std::vector<doublePoint> points = vreadFromTxt();
        //start timer
        //auto start = high_resolution_clock::now();
        clock_t start2, end2;
        start2 = clock();
        std::sort(points.begin(), points.end());
        int left = 0;
        int right = points.size() - 1;
        int mid = (left + right) / 2;
        pairPoints point = recur(points, left, right);
        //auto stop = high_resolution_clock::now();
        //auto duration = duration_cast<seconds>(stop - start);
        end2 = clock();
        double time = (double)(end2 - start2) / CLOCKS_PER_SEC;
        cout << endl;
        cout << "Recursive" << endl;
        std::cout << "First Point: " << std::fixed << std::setprecision(23) << point.getPointA().getX() << "," << point.getPointA().getY() << std::endl;
        std::cout << "Second Point: " << std::fixed << std::setprecision(23) << point.getPointB().getX() << "," << point.getPointB().getY() << std::endl;
        std::cout << "Distance: " << std::fixed << std::setprecision(23) << point.getDist() << std::endl;
        std::cout << "Time: " << time << std::endl;
        writeToTxt(point.getPointA(), point.getPointB(), time);
    }
};

int main()
{
    doParts::part0();
    doParts::part1();
    doParts::part2();
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
