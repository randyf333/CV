// l04 Convex Hull.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <algorithm>
#include <set> 
using namespace std;
#define XSIZE  400
#define YSIZE  400

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
    bool operator == (const doublePoint& str) const {
        return (xcoor == str.xcoor && ycoor == str.ycoor);
    }
};
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

class Line {

private:
    Point p1;
    Point p2;
    double slope;
    double intercept;
public:
    Line() {

    }
    Line(Point a, Point b) {
        p1 = a;
        p2 = b;
        double dy = b.getY() - a.getY();
        double dx = b.getX() - a.getX();
        slope = dy / dx;
        intercept = b.getY() - (slope * b.getX());
    }
    void setPoints(Point a, Point b) {
        p1 = a;
        p2 = b;
    }
    void drawLine(Point a, Point b, int** arr, int color) { //Bresenham
        int x1 = a.getX();
        int y1 = a.getY();
        int x2 = b.getX();
        int y2 = b.getY();
        if (x1 == 800) { x1 = x1 - 1; }
        if (x2 == 800) { x2 = x2 - 1; }
        if (y1 == 800) { y1 = y1 - 1; }
        if (y2 == 800) { y2 = y2 - 1; }
        int dx = std::abs(x2 - x1);
        int dy = std::abs(y2 - y1);
        int x = x1;
        int y = y1;
        if (dx > dy) {
            arr[x][y] = color;
            int pk = (2 * dy) - dx;
            for (int i = 0; i < dx; i++) {
                x1 < x2 ? x++ : x--;
                if (pk < 0)
                    pk = pk + (2 * dy);
                else
                {
                    y1 < y2 ? y++ : y--;
                    pk = pk + (2 * dy) - (2 * dx);
                }
                arr[x][y] = color;

            }
        }
        else
        {
            arr[x][y] = color;
            int pk = (2 * dx) - dy;
            for (int i = 0; i < dy; i++) {
                y1 < y2 ? y++ : y--;
                if (pk < 0)
                    pk = pk + (2 * dx);
                else
                {
                    x1 < x2 ? x++ : x--;
                    pk = pk + (2 * dx) - (2 * dy);
                }
                arr[x][y] = color;
            }
        }
    }
    Point getP1() {
        return p1;
    }
    Point getP2() {
        return p2;
    }
    double getSlope() {
        return slope;
    }
    double getIntercept() {
        return intercept;
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
        image.open("quickhull.ppm");
        image << "P3" << " " << width << " " << height << " " << "255" << std::endl;
        for (int i = 0; i < width; i++) {//print array
            for (int j = 0; j < height; j++) {
                if (arr[i][j] == 0) {
                    image << "0 0 0" << " "; //black
                }
                else if (arr[i][j] == 2) {
                    image << "255 0 0" << " "; //red
                }
                else {
                    image << "255 255 255" << " "; //white
                }

            }
            image << "\n";
        }
        image.close();
    }
    static void drawPoint(doublePoint center, int** arr, int xsize, int ysize, int color) {
        Circle first(1, roundNum(center.getX()), roundNum(center.getY()), center.getX(), center.getY(), 1);
        Circle second(2, roundNum(center.getX()), roundNum(center.getY()), center.getX(), center.getY(), 1);
        first.drawCircle(arr, xsize, ysize, color);
        second.drawCircle(arr, xsize, ysize, color);
    }
    static int roundNum(double a) {
        return (int)((a * 400) + 0.5);
        //return (int)((a * 50) + 0.5);
    }
    static Point toPoint(doublePoint a) {
        Point b(roundNum(a.getX()), roundNum(a.getY()));
        return b;
    }
    static void makeTxTFile() {//doublePoint p1, doublePoint p2, double time, double distance) {
        std::ofstream file;
        file.open("points.txt");
        //file << "(" << std::fixed << std::setprecision(23) << p1.getX() << "," << p1.getY() << ")" << std::endl;
        //file << "(" << std::fixed << std::setprecision(23) << p2.getX() << "," << p2.getY() << ")" << std::endl;
        //file << "Distance: " << distance << endl;
        //file << "Time: " << time << endl;
        file.close();
    }
    static void writeToTxt(doublePoint p1) {
        std::ofstream file;
        file.open("points.txt", ios_base::app);
        //file << "Recursive" << endl;
        file << std::fixed << std::setprecision(20);
        file << p1.getX() << "  " << p1.getY();
        file << endl;
        file.close();
    }
    static bool comparePts(doublePoint x, doublePoint y) {
        if (x.getX() == y.getX()) {
            return x.getY() < y.getY();
        }
        else {
            return (x.getX() < y.getX());
        }
    }
    static bool findSide(doublePoint a, doublePoint b, doublePoint point) { //false on left side, true on right side
        //double d = (point.getX() - a.getX()) * (b.getY() - a.getY()) - (point.getY() - a.getY()) * (b.getX() - a.getX());
        double d = (b.getX() - a.getX()) * (point.getY() - a.getY()) - (b.getY() - a.getY()) * (point.getX() - a.getX());
        //if (d < 0) {
        //    return false;
        //}
        //else if (d > 0) {
        //    return true;
        //}
        return d < 0;
    }
    static list<doublePoint> quickHull(vector<doublePoint>& points) {
        sort(points.begin(), points.end(), comparePts);
        doublePoint a = points[0]; //leftmost point
        doublePoint b = points[points.size() - 1]; //rightmost point
        list<doublePoint> hull;
        hull.push_back(a);
        //cout << "num1 inserted" << endl;
        hull.push_back(b);
        //cout << "num2 inserted" << endl;
        hull.push_back(a);
        //cout << "num3 inserted" << endl;
        //cout << hull.size() << endl;
        set<doublePoint> s1; //pts on the right side of AB
        set<doublePoint> s2; //pts of right side of BA
        for (int i = 1; i < points.size() - 1; i++) {
            if (findSide(a, b, points[i])) {
                s1.insert(points[i]);
            }
            else if (findSide(b, a, points[i])) {
                s2.insert(points[i]);
            }
        }
        findHull(s1, a, b, hull);
        findHull(s2, b, a, hull);
        return hull;
    }
    static void getLine(double x1, double y1, double x2, double y2, double& a, double& b, double& c) { //line from 
        a = y1 - y2;
        b = x2 - x1;
        c = x1 * y2 - x2 * y1;//maybe y2

    }
    static double distLine(double x1, double y1, double x2, double y2, double x3, double y3) { //needs fixing
        double a, b, c;
        getLine(x1, y1, x2, y2, a, b, c);
        return abs(a * x3 + b * y3 + c) / sqrt(a * a + b * b);
    }
    static void findHull(set<doublePoint>& points, doublePoint a, doublePoint b, list<doublePoint>& hull) { //maybe change to void
        if (points.empty()) {
            return;
        }
        doublePoint furthest;
        //find furthurst point in points from line AB
        set<doublePoint>::iterator itr;
        double distance = 0;
        double temp;
        for (itr = points.begin(); itr != points.end(); itr++) {
            doublePoint p = *itr;
            temp = distLine(a.getX(), a.getY(), b.getX(), b.getY(), p.getX(), p.getY()); //needs fixing
            if (temp > distance) {
                distance = temp;
                furthest = p;
            }
        }
        list<doublePoint>::iterator first = find(hull.begin(), hull.end(), a);
        hull.insert(next(first,1), furthest);
        set<doublePoint> s1; //pts on the right side of AB
        set<doublePoint> s2; //pts of left side of AB
        set<doublePoint>::iterator itr2;
        for (itr2 = points.begin(); itr2 != points.end(); itr2++) {
            if (findSide(a, furthest, *itr2)) {
                s1.insert(*itr2);
            }
            else if (findSide(furthest, b, *itr2)) {//maybe issue
                s2.insert(*itr2);
            }
        }
        findHull(s1, a, furthest, hull);
        findHull(s2, furthest, b, hull);
        return;
    }
    static void doPart1() {
        int** arr = new int* [XSIZE];
        for (int i = 0; i < XSIZE; i++) {
            arr[i] = new int[YSIZE];
            for (int j = 0; j < YSIZE; j++) {
                arr[i][j] = 1;
            }
        }
        makeTxTFile();
        doublePoint p;
        vector<doublePoint> points;
        for (int i = 0; i < 60; i++) {
            p = generatePoints();
            points.push_back(p);
            writeToTxt(p);
        }
        //points = vreadFromTxt();
        list<doublePoint>::iterator itr;
        list<doublePoint> hull = quickHull(points);
        for (auto i : points) {
            if (find(hull.begin(), hull.end(), i) != hull.end()) {
                drawPoint(i, arr, XSIZE, YSIZE, 2);
            }
            else {
                drawPoint(i, arr, XSIZE, YSIZE, 0);
            }
        }
        Point first = toPoint(*hull.begin());
        for (itr = next(hull.begin(), 1); itr != hull.end(); itr++) {
            Point sec = toPoint(*itr);
            Line line(first, sec);
            line.drawLine(line.getP1(), line.getP2(), arr, 2);
            first = sec;
        }
        doParts::rotateMatrix(XSIZE, YSIZE, arr);
        doParts::makePPM(XSIZE, YSIZE, arr);
        delete[] arr;
    }
};

int main()
{
    doParts::doPart1();
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
