// l02 Smallest Square.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <vector>
#include <tuple>
#include <string>
#include <sstream>
using namespace std;
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
    string toString() {
        string s = to_string(xcoor) + "," + to_string(ycoor);
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
    void drawLine(Point a, Point b, int** arr) {//, int color) { //Bresenham
        int x1 = a.getX();
        int y1 = a.getY();
        int x2 = b.getX();
        int y2 = b.getY();
        int dx = std::abs(x2 - x1);
        int dy = std::abs(y2 - y1);
        int x = x1;
        int y = y1;
        if (dx > dy) {
            arr[x][y] = 0;
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
                arr[x][y] = 0;

            }
        }
        else
        {
            arr[x][y] = 0;
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
                arr[x][y] = 0;
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

class makePoints {
public:
    static double generateCoord() {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<double> distr(0, 1);
        return distr(eng);
    }
    //static bool isSame(double a, double b) {
    //    return std::fabs(a - b) < std::numeric_limits<double>::epsilon();
    //}
    static int roundNum(double a) {
        return (int)((a * 800) + 0.5);
        //return (int)((a * 50) + 0.5);
    }
    static int checkBound(int num, int bound) {
        if (num >= bound) {
            return bound - 1;
        }
        else {
            return num;
        }
    }
    static double findArea(double x1, double y1, double x2, double y2, double x3, double y3) { //triangles
        return std::abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
    }
    static bool checkPoint(doublePoint p1, doublePoint p2, doublePoint p3, doublePoint p4) { //check if points are in triangle, part 1
        double area = findArea(p1.getX(), p1.getY(), p2.getX(), p2.getY(), p3.getX(), p3.getY());
        double areap1 = findArea(p4.getX(), p4.getY(), p2.getX(), p2.getY(), p3.getX(), p3.getY());
        double areap2 = findArea(p1.getX(), p1.getY(), p4.getX(), p4.getY(), p3.getX(), p3.getY());
        double areap3 = findArea(p1.getX(), p1.getY(), p2.getX(), p2.getY(), p4.getX(), p4.getY());
        return std::abs(area - (areap1 + areap2 + areap3)) <= .0000001;
    }
    //cross product(a,b,c,d)
    //a*d-b*c
    static Point toPoint(doublePoint a) {
        Point b(roundNum(a.getX()), roundNum(a.getY()));
        return b;
    }
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
    void drawCircle(int** arr, int xsize, int ysize) {//, int color) {//radius, center xcoord, center ycoord
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
                    arr[centerx + x][centery + y] = 0;
                }
                if (centery - y >= 0) {
                    arr[centerx + x][centery - y] = 0;
                }
            }
            if (centerx - x >= 0) {
                if (centery + y < ysize) {
                    arr[centerx - x][centery + y] = 0;
                }
                if (centery - y >= 0) {
                    arr[centerx - x][centery - y] = 0;
                }
            }
            if (centerx + y < xsize) {
                if (centery + x < ysize) {
                    arr[centerx + y][centery + x] = 0;
                }
                if (centery - x >= 0) {
                    arr[centerx + y][centery - x] = 0;
                }
            }
            if (centerx - y >= 0) {
                if (centery + x < ysize) {
                    arr[centerx - y][centery + x] = 0;
                }
                if (centery - x >= 0) {
                    arr[centerx - y][centery - x] = 0;
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
class part1 {
public:
    static void makeTxTFile(doublePoint p1, doublePoint p2, doublePoint p3, doublePoint p4) {
        std::ofstream file;
        file.open("points.txt");
        file << "(" << std::fixed << std::setprecision(17) << p1.getX() << "," << p1.getY() << ")" << " ," << std::endl;
        file << "(" << std::fixed << std::setprecision(17) << p2.getX() << "," << p2.getY() << ")" << " ," << std::endl;
        file << "(" << std::fixed << std::setprecision(17) << p3.getX() << "," << p3.getY() << ")" << " ," << std::endl;
        file << "(" << std::fixed << std::setprecision(17) << p4.getX() << "," << p4.getY() << ")" << std::endl;
        file.close();
    }
    static doublePoint makeLog(doublePoint p1, doublePoint p2, doublePoint p3) {//,doublePoint p) { //delete last doublePoint p after tests
        std::ofstream file;
        file.open("log.txt");
        file << "(" << std::fixed << std::setprecision(17) << p1.getX() << "," << p1.getY() << ")" << ", ";
        file << "(" << std::fixed << std::setprecision(17) << p2.getX() << "," << p2.getY() << ")" << ", ";
        file << "(" << std::fixed << std::setprecision(17) << p3.getX() << "," << p3.getY() << ")" << endl;
        cout << "(" << std::fixed << std::setprecision(17) << p1.getX() << "," << p1.getY() << ")" << ", ";
        cout << "(" << std::fixed << std::setprecision(17) << p2.getX() << "," << p2.getY() << ")" << ", ";
        cout << "(" << std::fixed << std::setprecision(17) << p3.getX() << "," << p3.getY() << ")" << endl;
        doublePoint p4;
        bool check = true;
        while (check) {
            p4.setX(makePoints::generateCoord());
            p4.setY(makePoints::generateCoord());
            cout << "Testing the point: " << "(" << std::fixed << std::setprecision(17) << p4.getX() << "," << p4.getY() << ")" << endl;
            file << "Testing the point: " << "(" << std::fixed << std::setprecision(17) << p4.getX() << "," << p4.getY() << ")" << endl;
            bool check1 = makePoints::checkPoint(p1, p2, p3, p4);
            bool check2 = makePoints::checkPoint(p1, p2, p4, p3);
            bool check3 = makePoints::checkPoint(p1, p4, p3, p2);
            bool check4 = makePoints::checkPoint(p4, p2, p3, p1);
            if (check1 == check2 == check3 == check4) {
                check = false;
            }
        }
        file.close();
        return p4;
    }
    static void doPart1() {
        doublePoint p1(makePoints::generateCoord(), makePoints::generateCoord());
        doublePoint p2(makePoints::generateCoord(), makePoints::generateCoord());
        doublePoint p3(makePoints::generateCoord(), makePoints::generateCoord());
        //doublePoint p1(0.86941074168708876, 0.15993302053892403);
        //doublePoint p2(0.47638208467888199, 0.52377581382253224);
        //doublePoint p3(0.45226436226113620, 0.90460559530182882);
        //doublePoint p4(0.30872328944542649, 0.30329380287552415);
        //p4 = makeLog(p1, p2, p3, p4);
        doublePoint p4 = part1::makeLog(p1, p2, p3);
        part1::makeTxTFile(p1, p2, p3, p4);
    }
};

class part2 {
public:
    //static void swapValues(int x1, int y1, int x2, int y2, int** arr) {
    //    int temp = arr[x1][y1];
    //    arr[x1][y1] = arr[x2][y2];
    //    arr[x2][y2] = temp;
    //}
    static doublePoint findIntersection(Line a, Line b, int xsize, int ysize) {
        double xcoord = (b.getIntercept() - a.getIntercept()) / (a.getSlope() - b.getSlope());
        double ycoord = (a.getSlope() * xcoord) + a.getIntercept();
        doublePoint intersection(xcoord / xsize, ycoord / ysize);
        return intersection;
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

    static Line makeperpend(doublePoint c, double slope) {
        double perslope = (1 / slope) * -1;
        double pointx1 = 0;
        double pointx2 = 0;
        double pointy1 = 0;
        double pointy2 = 0;
        double intercept = c.getY() - (perslope * c.getX());
        double point800x = (1 - intercept) / perslope;//finds x when y is maxed
        double point0x = (0 - intercept) / perslope;//finds x when y is 0 y= mx+b

        if (point800x < 1 && point800x >= 0 && point0x < 1 && point0x >= 0) {
            pointx1 = point0x;
            pointx2 = point800x;
            pointy1 = 0;
            pointy2 = 0.998125;
        }
        else if (point800x > 1 || point800x < 0) {
            pointy2 = perslope + intercept;
            if (point0x > 1 || point0x < 0) {
                pointy1 = intercept;
                pointx1 = 0;
                pointx2 = 0.998125;
            }
            else {
                pointx1 = point0x;
                pointx2 = 0.998125;
                pointy1 = 0;
            }
        }
        else {
            pointy1 = intercept;
            pointx1 = 0;
            pointx2 = point800x;
            pointy2 = 0.998125;
        }
        Point final1(roundNum(pointx1), roundNum(pointy1));
        Point final2(roundNum(pointx2), roundNum(pointy2));
        return Line(final1, final2);
    }


    static vector<doublePoint> makeTxT() {
        vector<doublePoint>data;
        ofstream file;
        file.open("output.txt");
        ifstream points;
        points.open("points.txt");
        string line;
        //string delim1 = "(";
        string delim2 = ",";
        //string delim3 = ")";
        //cout << "Hello" << endl;
        if (points.is_open()) {
            while (getline(points, line)) {
                int delim2ind = line.find(delim2);
                //int delim3ind = line.find(delim3);
                //cout << line << endl;
                file << line << endl;
                string firsttok = line.substr(1, delim2ind - 1);
                //cout << firsttok << endl;
                string sectok = line.substr(delim2ind + 2, delim2ind - 1);
                doublePoint p(stod(firsttok), stod(sectok));
                //cout << std::fixed << std::setprecision(17) << stod(firsttok) << ", " << stod(sectok) << endl;

                data.push_back(p);
            }
        }
        file.close();
        return data;
    }

    static void writetoTxT(doublePoint a, bool comma) {
        ofstream file;
        file.open("output.txt", std::ios_base::app);
        if (comma) {
            file << "(" << std::fixed << std::setprecision(17) << a.getX() << "," << a.getY() << ")" << " ," << std::endl;
        }
        else {
            file << "(" << std::fixed << std::setprecision(17) << a.getX() << "," << a.getY() << ")";
        }
        file.close();
    }
    static double getArea(doublePoint a, doublePoint b) {
        double distance = findDistance(a, b);
        return (distance * distance);
    }
    static double writeArea(doublePoint a, doublePoint b) {
        ofstream file;
        file.open("output.txt", std::ios_base::app);
        double area = getArea(a, b);
        file << " " << "Area = " << std::fixed << std::setprecision(17) << area << endl;
        return area;
    }

    static double findXMidPoint(double x1, double x2) {
        return (x2 + x1) / 2;
    }
    static double findYMidPoint(double y1, double y2) {
        return (y2 + y1) / 2;
    }

    static void makePPM(int width, int height, int** arr) {
        ofstream image;
        image.open("output.ppm");
        image << "P3" << " " << width << " " << height << " " << "1" << endl;
        //image << width << " " << height << endl;
        //image << "1" << endl; //can change to 255 for color
        for (int i = 0; i < width; i++) {//print array
            for (int j = 0; j < height; j++) {
                if (arr[i][j] == 0) {
                    image << "0 0 0" << " ";
                }
                else {
                    image << "1 1 1" << " ";
                }
                //image << arr[i][j] << " " << arr[i][j] << " " << arr[i][j] << " ";
                //cout << "" << arr[i][j] << "";
            }
            image << "\n";
        }
        image.close();
    }


    static int checkBound(int num, int bound) {
        if (num >= bound) {
            return bound - 1;
        }
        else {
            return num;
        }
    }
    static double findDistance(doublePoint a, doublePoint b) {
        double ax = a.getX();
        double ay = a.getY();
        double bx = b.getX();
        double by = b.getY();
        return sqrt((pow((by - ay), 2) + pow((bx - ax), 2)));
    }
    static vector<doublePoint> pickE(doublePoint source, double slope, double length) { //tuple<doublePoint,doublePoint>
        vector<doublePoint> options;
        if (slope == 0) {
            doublePoint point((source.getX() + length), source.getY());
            doublePoint point2((source.getX() - length), source.getY());
            options.push_back(point);
            options.push_back(point2);
        }
        else if (slope == std::numeric_limits<double>::max()) {
            doublePoint point(source.getX(), (source.getY() + length));
            doublePoint point2(source.getX(), (source.getY() - length));
            options.push_back(point);
            options.push_back(point2);
        }
        else {
            double dx = (length / sqrt(1 + (slope * slope)));//length*sqrt(1 / (1 + (slope * slope)));
            double dy = slope * dx;
            doublePoint point((source.getX() + dx), (source.getY() + dy));
            doublePoint point2((source.getX() - dx), (source.getY() - dy));
            options.push_back(point);
            options.push_back(point2);
        }
        return options;
    }
    static int roundNum(double a) {
        return (int)((a * 800) + 0.5);
        //return (int)((a * 50) + 0.5);
    }
    //maybe change tuple to tuple<doublePoint,doublePoint,doublePoint,doublePoint>
    static vector<tuple<doublePoint, doublePoint, doublePoint, doublePoint>> getCombinations(doublePoint a, doublePoint b, doublePoint c, doublePoint d) {
        vector<tuple<doublePoint, doublePoint, doublePoint, doublePoint>> combos;
        tuple<doublePoint, doublePoint, doublePoint, doublePoint> first;
        tuple<doublePoint, doublePoint, doublePoint, doublePoint> second;
        tuple<doublePoint, doublePoint, doublePoint, doublePoint> third;
        //tuple<doublePoint, doublePoint> fourth; tuple<doublePoint, doublePoint> fifth; tuple<doublePoint, doublePoint> sixth;
        //(first point, opp point, third point, third point opp)
        first = make_tuple(a, b, c, d); //a
        second = make_tuple(a, c, b, d); // b
        third = make_tuple(a, d, b, c); // c
        //fourth = make_tuple(b, c); //c
        //fifth = make_tuple(b, d);//b
        //sixth = make_tuple(c, d);//a
        combos.push_back(first);
        combos.push_back(second);
        combos.push_back(third);
        //combos.push_back(fourth);
        //combos.push_back(fifth);
        //combos.push_back(sixth);
        return combos;
    }
    static Line makeLine(doublePoint a, doublePoint b) {

        double dy = (b.getY() - a.getY());
        double dx = (b.getX() - a.getX());
        double slope = dy / dx;

        double pointx1 = 0;
        double pointx2 = 0;
        double pointy1 = 0;
        double pointy2 = 0;

        double intercept = b.getY() - (slope * b.getX());
        double point0x = intercept;//y when x is 0
        double point800x = slope + intercept; //y when x is maxed

        //double point800x = (1 - intercept) / slope;//finds x when y is maxed
        //double point0x = (0 - intercept) / slope;//finds x when y is 0 y= mx+b
        if (point800x < 1 && point800x >= 0 && point0x < 1 && point0x >= 0) {
            pointx1 = 0;
            pointx2 = .998125;
            pointy1 = point0x;
            pointy2 = point800x;
        }
        else {
            if (point0x < 0) {
                pointy1 = 0;
            }
            if (point0x > 1) {
                pointy1 = 0.998125;
            }
            else {
                pointy1 = point0x;
            }
            if (point800x < 0) {
                pointy2 = 0;
            }
            else if (point800x > 1) {
                pointy2 = .998125;
            }
            else {
                pointy2 = point800x;
            }
            pointx2 = (pointy2 - intercept) / slope;
            pointx1 = (pointy1 - intercept) / slope;
            //if (point800x < 0 || point800x > 1) {
            //    pointx2 = .998125;
            //    pointy2 = (slope * pointx2) + intercept;
            //}
            //else {
            //    pointy2 = point800x;
            //    pointx2 = .998125;
        }
        //else if (point800x > 1) {
        //    pointy2 = slope + intercept;
        //    pointx2 = 0.998125;
        //    if (point0x > 1 || point0x < 0) {
        //        pointy1 = intercept;
        //        pointx1 = 0;
        //    }
        //    else {
        //        pointx1 = point0x;
        //        pointy1 = 0.998125;
        //    }
        //}
        //else if (point800x < 0) {
        //    pointy2 = intercept;
        //    pointx2 = 0;
        //    if (point0x > 1 || point0x < 0) {
        //        pointy1 = slope+intercept;
        //        pointx1 = 0.998125;
        //    }
        //    else {
        //        pointx1 = point0x;
        //        pointy1 = 0.998125;
        //    }
        //}
        // 
        //else if (point800x > 1 || point800x < 0) {
        //    pointy2 = slope + intercept;
        //    if (point0x > 1 || point0x < 0) {
        //        pointy1 = intercept;
        //        pointx1 = 0;
        //        pointx2 = 0.998125;
        //    }
        //    else {
        //        pointx1 = point0x;
        //        pointx2 = 0.998125;
        //        pointy1 = 0;
        //    }
        //}
        //else {
        //    pointy1 = intercept;
        //    pointx1 = 0;
        //    pointx2 = point800x;
        //    pointy2 = 0.998125;
        //}
        Point final1(roundNum(pointx1), roundNum(pointy1));
        Point final2(roundNum(pointx2), roundNum(pointy2));
        return Line(final1, final2);
    }



    static void doPart2() {//read points from file
        int xsize = XSIZE;
        int ysize = YSIZE;
        int** arr = new int* [xsize];
        for (int i = 0; i < xsize; i++) {
            arr[i] = new int[ysize];
            for (int j = 0; j < ysize; j++) {
                arr[i][j] = 1;
            }
        }
        vector<doublePoint> points = makeTxT();
        doublePoint a(0.27674557802620864, 0.34522475881631287);
        doublePoint b(0.35760905208947141, 0.69230657856073929);
        doublePoint c(0.61802737442787070, 0.85858168233222754);
        doublePoint d(0.34072825868924328, 0.20677572026710833);

        //doublePoint a(0.74139249080494474, 0.42210299880582108);
        //doublePoint b(0.15106317677259185, 0.54780212810607409);
        //doublePoint c(0.34067626500602843, 0.34494233348184139);
        //doublePoint d(0.92916063053233255, 0.88580826123861878);

        //doublePoint a(0.18161564989165929, 0.49650563066499831);
        //doublePoint b(0.20331431012909329, 0.66115298928800315);
        //doublePoint c(0.45457319864497819, 0.36802270577105012);
        //doublePoint d(0.86330759605700857, 0.82033753471480453);

        //doublePoint a = points[0];
        //doublePoint b = points[1];
        //doublePoint c = points[2];
        //doublePoint d = points[3];

        Circle acircle(2, roundNum(a.getX()), roundNum(a.getY()), a.getX(), a.getY(), 10);
        Circle bcircle(2, roundNum(b.getX()), roundNum(b.getY()), b.getX(), b.getY(), 10);
        //Circle ccircle(2, roundNum(c.getX()), roundNum(c.getY()), c.getX(), c.getY(), 10);
        //Circle dcircle(2, roundNum(d.getX()), roundNum(d.getY()), d.getX(), d.getY(), 10);
        acircle.drawCircle(arr, xsize, ysize);
        bcircle.drawCircle(arr, xsize, ysize);
        //ccircle.drawCircle(arr, xsize, ysize);
        //dcircle.drawCircle(arr, xsize, ysize);
        //vector<tuple<doublePoint, doublePoint, doublePoint, doublePoint>> options = getCombinations(a, b, c, d); //finds d
        Line test = part2::makeLine(a, b);
        test.drawLine(test.getP1(), test.getP2(),arr);
        //cout << "First point " << get<0>(test).toString() << endl;
        //cout << "Second point" << get<1>(test).toString() << endl;

        //cout << "Third point"

        //Line test = part2::makeLine(a, b);
        //Line perp = part2::makeperpend(c, test.getSlope());
        //test.drawLine(test.getP1(), test.getP2(), arr);
        //perp.drawLine(perp.getP1(), perp.getP2(), arr);
        ////Line way
        //vector<tuple<double, Line, Line, Line, Line>>render;
        //vector<tuple<double, doublePoint, doublePoint, doublePoint, doublePoint>>render;
        //for (int num = 0; num < options.size(); num++) {
        //    tuple<doublePoint, doublePoint, doublePoint, doublePoint> test = options[num];
        //    Line temp = part2::makeLine(get<0>(test), get<1>(test)); //connects two points that end up on opposite sides of the square
        //    //temp.drawLine(temp.getP1(), temp.getP2(), arr);//delete this
        //    Line tempper = part2::makeperpend(get<2>(test), temp.getSlope());//perpendicular line to temp
        //    double distance = part2::findDistance(get<0>(test), get<1>(test));
        //    //cout << distance << endl;
        //    //tempper.drawLine(tempper.getP1(), tempper.getP2(), arr);//delete this
        //    vector<doublePoint> e = part2::pickE(get<2>(test), tempper.getSlope(), distance);

        //    //for (int option = 0; option < len(e vector); option++)
        //    for (int option = 0; option < e.size(); option++) {//goes through both option of point e
        //        Line tempfirst = part2::makeLine(e[option], get<3>(test)); //first choice
        //        //Line tempsec = part2::makeLine(get<1>(e), get<3>(test));
        //        //Circle firstpoint(2, roundNum(e[option].getX()), roundNum(e[option].getY()), e[option].getX(), e[option].getY(), 10);//remove 
        //        //firstpoint.drawCircle(arr, xsize, ysize);//remove
        //        //cout << findDistance(get<0>(e), get<2>(test)) << endl;
        //        //tempfirst.drawLine(tempfirst.getP1(), tempfirst.getP2(),arr);//remove
        //        Line perpenfirst = part2::makeperpend(get<0>(test), tempfirst.getSlope());
        //        Line perpensecond = part2::makeperpend(get<1>(test), tempfirst.getSlope());
        //        Line perpenthird = part2::makeperpend(get<2>(test), perpenfirst.getSlope());

        //        doublePoint firstinter = part2::findIntersection(perpenfirst, tempfirst, xsize, ysize);
        //        part2::writetoTxT(firstinter, true);
        //        doublePoint secinter = part2::findIntersection(perpensecond, tempfirst, xsize, ysize);
        //        part2::writetoTxT(secinter, true);
        //        doublePoint thirdinter = part2::findIntersection(perpenthird, perpenfirst, xsize, ysize);
        //        part2::writetoTxT(thirdinter, true);
        //        doublePoint fourthinter = part2::findIntersection(perpenthird, perpensecond, xsize, ysize);
        //        part2::writetoTxT(fourthinter, false);
        //        double area = part2::writeArea(firstinter, secinter);

        //        //Line firstline = part2::makeLine(firstinter,thirdinter);
        //        //Line secline = part2::makeLine(firstinter,secinter);
        //        //Line thirdline = part2::makeLine(fourthinter,thirdinter);
        //        //Line fourthline = part2::makeLine(fourthinter,secinter);

        //        //tuple<double, Line, Line, Line, Line> potential;
        //        //potential = make_tuple(area, tempfirst, perpenfirst, perpensecond, perpenthird);
        //        //potential = make_tuple(area, firstline, secline, thirdline, fourthline);
        //        tuple<double, doublePoint, doublePoint, doublePoint, doublePoint> potential;
        //        potential = make_tuple(area, firstinter, secinter, thirdinter, fourthinter);
        //        render.push_back(potential);
        //    }
        //}
        //int index = 0;
        //double minarea = 1;
        //for (int i = 0; i < render.size(); i++) {
        //    double test_area = get<0>(render[i]);
        //    if (test_area < minarea) {
        //        minarea = test_area;
        //        index = i;
        //    }
        //}
        ////tuple<double, Line, Line, Line, Line>square = render[index];
        ////get<1>(square).drawLine(get<1>(square).getP1(), get<1>(square).getP2(), arr);
        ////get<2>(square).drawLine(get<2>(square).getP1(), get<2>(square).getP2(), arr);
        ////get<3>(square).drawLine(get<3>(square).getP1(), get<3>(square).getP2(), arr);
        ////get<4>(square).drawLine(get<4>(square).getP1(), get<4>(square).getP2(), arr);
        //tuple<double, doublePoint, doublePoint, doublePoint, doublePoint>square = render[index];
        ////Line = part2::makeLine(doublePoint,doublePoint);
        ////Line firline = part2::makeLine(get<1>(square), get<2>(square));
        ////firline.drawLine(firline.getP1(), firline.getP2(), arr);

        //Line secline = part2::makeLine(get<1>(square), get<3>(square));
        //secline.drawLine(secline.getP1(), secline.getP2(), arr);

        //Line thirline = part2::makeLine(get<4>(square), get<2>(square));
        //thirline.drawLine(thirline.getP1(), thirline.getP2(), arr);

        //Line fourline = part2::makeLine(get<4>(square), get<3>(square));
        //fourline.drawLine(fourline.getP1(), fourline.getP2(), arr);

        //Circle fintercept(2, roundNum(0.13956839992642042), roundNum(0.58280239821853452), 0.13956839992642042, 0.58280239821853452, 2);
        //Circle secintercpt(2, roundNum(.12868228902697765), roundNum(.57653894020827545), .12868228902697765, .57653894020827545, 2);
        //Circle thirdintercept(2, roundNum(.14666624131339454), roundNum(.57047011055811181), .14666624131339454, .57047011055811181, 2);
        //Circle fourthintercept(2, roundNum(.13576661728984424), roundNum(.56421122281349601), .13576661728984424, .56421122281349601, 2);
        //fintercept.drawCircle(arr, xsize, ysize);
        //secintercpt.drawCircle(arr, xsize, ysize);
        //thirdintercept.drawCircle(arr, xsize, ysize);
        //fourthintercept.drawCircle(arr, xsize, ysize);

        part2::rotateMatrix(xsize, ysize, arr);
        part2::makePPM(xsize, ysize, arr);
        delete[] arr;
    }
};

int main()
{
    //create random variables
    //part1::doPart1();
    part2::doPart2();
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
