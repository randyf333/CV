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
#define XSIZE  800
#define YSIZE  800

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
            std::ofstream file;
            file.open("points.txt");
            for (int i = 0; i < 60; i++) {
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
    static double findDistance(doublePoint a, doublePoint b) {
        double ax = a.getX();
        double ay = a.getY();
        double bx = b.getX();
        double by = b.getY();
        return sqrt((pow((by - ay), 2) + pow((bx - ax), 2)));
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
    static void makePPM(int width, int height, int** arr) {
        std::ofstream image;
        image.open("points.ppm");
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
        std::list<doublePoint>::iterator trav;
        for (trav = points.begin(); trav != points.end(); trav++) {
            doublePoint temp1 = *trav;
            Circle draw3Point(3, roundNum(temp1.getX()), roundNum(temp1.getY()), temp1.getX(), temp1.getY(), 3);
            Circle draw2Point(2, roundNum(temp1.getX()), roundNum(temp1.getY()), temp1.getX(), temp1.getY(), 2);
            draw3Point.drawCircle(arr, XSIZE, YSIZE,0);
            draw2Point.drawCircle(arr, XSIZE, YSIZE,0);
            std::list<doublePoint>::iterator trav2;
            for (trav2 = next(trav, 1); trav2 != points.end(); trav2++) {
                doublePoint temp2 = *trav2;
                double trydistance = findDistance(temp1,temp2);
                if (trydistance < distance) {
                    distance = trydistance;
                    first = temp1;
                    second = temp2;
                }
            }
        }
        Circle close13(3, roundNum(first.getX()), roundNum(first.getY()), first.getX(), first.getY(), 3);
        Circle close12(2, roundNum(first.getX()), roundNum(first.getY()), first.getX(), first.getY(), 2);
        close12.drawCircle(arr, XSIZE, YSIZE,2); //2 means red
        close13.drawCircle(arr, XSIZE, YSIZE,2);

        Circle close23(3, roundNum(second.getX()), roundNum(second.getY()), second.getX(), second.getY(), 3);
        Circle close22(2, roundNum(second.getX()), roundNum(second.getY()), second.getX(), second.getY(), 2);
        close23.drawCircle(arr, XSIZE, YSIZE,2);
        close22.drawCircle(arr, XSIZE, YSIZE,2);
        std::cout << "First Point: " << std::fixed << std::setprecision(23) << first.getX() << "," << first.getY() << std::endl;
        std::cout << "Second Point: " << std::fixed << std::setprecision(23) << second.getX() << "," << second.getY() << std::endl;
        std::cout << "Distance: " << std::fixed << std::setprecision(23) << distance << std::endl;
        doParts::rotateMatrix(XSIZE, YSIZE, arr);
        doParts::makePPM(XSIZE, YSIZE, arr);
        delete[] arr;
    }
};

int main()
{
    doParts::part0();;
    doParts::part1();
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
