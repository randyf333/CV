#include <iostream>
#include <random>
#include <cmath>
#include <fstream>
//#include <tuple>
using namespace std;
#define XSIZE  800
#define YSIZE  800


class Point {
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
public:
    Line() {

    }
    Line(Point a, Point b) {
        p1 = a;
        p2 = b;
    }
    void setPoints(Point a, Point b) {
        p1 = a;
        p2 = b;
    }

    void drawLine(Point a, Point b, int** arr) { //Bresenham
        int x1 = a.getX();
        int y1 = a.getY();
        int x2 = b.getX();
        int y2 = b.getY();
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
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
};

class Triangle {
private:
    Point p1;
    Point p2;
    Point p3;
    Line linea;
    Line lineb;
    Line linec;
    double len1;
    double len2;
    double len3;
    double x1, x2, x3, y1, y2, y3;

public:
    Triangle() {
        len1 = len2 = len3 = x1 = x2 = x3 = y1 = y2 = y3 = 0;
    }
    Triangle(Point& a, Point& b, Point& c, double l1, double l2, double l3, double a1, double a2, double a3, double b1, double b2, double b3) {
        p1 = a;
        p2 = b;
        p3 = c;
        len1 = l1;
        len2 = l2;
        len3 = l3;
        x1 = a1;
        x2 = a2;
        x3 = a3;
        y1 = b1;
        y2 = b2;
        y3 = b3;
        linea.setPoints(a, b);
        lineb.setPoints(a, c);
        linec.setPoints(b, c);
    }
    double getX1() {
        return x1;
    }
    double getX2() {
        return x2;
    }
    double getX3() {
        return x3;
    }
    double getY1() {
        return y1;
    }
    double getY2() {
        return y2;
    }
    double getY3() {
        return y3;
    }
    int getP1X() {
        return p1.getX();
    }
    int getP2X() {
        return p2.getX();
    }
    int getP3X() {
        return p3.getX();
    }
    int getP1Y() {
        return p1.getY();
    }
    int getP2Y() {
        return p2.getY();
    }
    int getP3Y() {
        return p3.getY();
    }
    double getLength1() {
        return len1;
    }
    double getLength2() {
        return len2;
    }
    double getLength3() {
        return len3;
    }
    Point getP1() {
        return p1;
    }
    Point getP2() {
        return p2;
    }
    Point getP3() {
        return p3;
    }
    Line getLineA() {
        return linea;
    }
    Line getLineB() {
        return lineb;
    }
    Line getLineC() {
        return linec;
    }
    void drawTriangle(int** arr) {
        linea.drawLine(p1, p2, arr);
        lineb.drawLine(p2, p3, arr);
        linec.drawLine(p3, p1, arr);
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
    void drawCircle(int** arr, int xsize, int ysize) {//radius, center xcoord, center ycoord
        int xmax = (int)(radius / sqrt(2));
        int y = radius;
        int y2 = y * y;
        int ty = (2 * y) - 1;
        int y2_new = y2;
        for (int x = 0; x <= xmax+2; x++) {
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

class makeShapes {
private:
    static double generateCoord() {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<double> distr(0, 1);
        return distr(eng);
    }
    static bool isSame(double a, double b) {
        return std::fabs(a - b) < std::numeric_limits<double>::epsilon();
    }
    static int roundNum(double a) {
        return (int)((a*800) + 0.5);
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
    static double findXMidPoint(double x1, double x2) {
        return (x2 + x1) / 2;
    }
    static double findYMidPoint(double y1, double y2) {
        return (y2 + y1) / 2;
    }
    //static double l1, l2, l3;//, inradii, circumradii, semi; //side lengths 1,2,3 incircle radius, circumcircle radius, semiperimeter 
public:
    static Triangle makeTriangle() {
        double l1, l2, l3;
        double x1 = generateCoord();
        double x2 = generateCoord();
        double x3 = generateCoord();
        double y1 = generateCoord();
        double y2 = generateCoord();
        double y3 = generateCoord();
        //double x1 = 56;
        //double y1 = 15;
        //double x2 = 36;
        //double y2 = 0;
        //double x3 = 0;
        //double y3 = 15;
        if (isSame(x1, x2) && isSame(x1, x3) && isSame(x2, x3)) {
            x1 = generateCoord();
        }
        if (isSame(y1, y2) && isSame(y1, y3) && isSame(y2, y3)) {
            y1 = generateCoord();
        }
        if (isSame((y1 - y3 / x1 - x3), (y1 - y2 / x1 - x2))) {
            x1 = generateCoord();
            y1 = generateCoord();
        }
        double tempx21 = pow((x2 - x1), 2);
        double tempy21 = pow((y2 - y1), 2);
        l1 = sqrt(tempx21 + tempy21);//c
        double tempx31 = pow((x3 - x1), 2);
        double tempy31 = pow((y3 - y1), 2);
        l2 = sqrt(tempx31 + tempy31);//b
        double tempx32 = pow((x3 - x2), 2);
        double tempy32 = pow((y3 - y2), 2);
        l3 = sqrt(tempx32 + tempy32);//a
        Point a(checkBound(roundNum(x1), XSIZE), checkBound(roundNum(y1), YSIZE));
        Point b(checkBound(roundNum(x2), XSIZE), checkBound(roundNum(y2), YSIZE));
        Point c(checkBound(roundNum(x3), XSIZE), checkBound(roundNum(y3), YSIZE));
        return Triangle(a, b, c, l1, l2, l3, x1, x2, x3, y1, y2, y3);
    }
    static Circle makeinCircle(Triangle t) {
        double len1 = t.getLength1(); //a
        double len2 = t.getLength2(); //b
        double len3 = t.getLength3(); //c
        double x1 = t.getX1();
        double x2 = t.getX2();
        double x3 = t.getX3();
        double y1 = t.getY1();
        double y2 = t.getY2();
        double y3 = t.getY3();
        //double len1 = 300;
        //double len2 = 500;
        //double len3 = 400;
        //double x1 = 260;
        //double x2 = 560;
        //double x3 = 660;
        double semi = .5 * (len1 + len2 + len3); //semiperimeter
        double product = (semi - len1) * (semi - len2) * (semi - len3);
        double inradii = sqrt(product / semi);
        //double Slope1 = (y2 - y1) / (x2 - x1);
        //double Slope2 = (y3 - y1) / (x3 - x1);
        double xcoord = ((len3 * x1) + (len2 * x2) + (len1 * x3)) / (len1 + len2 + len3);
        double ycoord = ((len3 * y1) + (len2 * y2) + (len1 * y3)) / (len1 + len2 + len3);
        return Circle(roundNum(inradii), checkBound(roundNum(xcoord), XSIZE), checkBound(roundNum(ycoord), YSIZE), xcoord, ycoord, inradii);
    }
    static Circle makecircumCircle(Triangle t) {
        double len1 = t.getLength1();
        double len2 = t.getLength2();
        double len3 = t.getLength3();
        double x1 = t.getX1();
        double x2 = t.getX2();
        double x3 = t.getX3();
        double y1 = t.getY1();
        double y2 = t.getY2();
        double y3 = t.getY3();
        double semi = .5 * (len1 + len2 + len3);
        double product = (semi - len1) * (semi - len2) * (semi - len3);
        double inradii = sqrt(product / semi);
        double circumradii = (len1 * len2 * len3) / (4 * semi * inradii);
        double d = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
        double xpart = ((pow(x1, 2) + pow(y1, 2)) * (y2 - y3)) + ((pow(x2, 2) + pow(y2, 2)) * (y3 - y1)) + ((pow(x3, 2) + pow(y3, 2)) * (y1 - y2));
        double ypart = ((pow(x1, 2) + pow(y1, 2)) * (x3 - x2)) + ((pow(x2, 2) + pow(y2, 2)) * (x1 - x3)) + ((pow(x3, 2) + pow(y3, 2)) * (x2 - x1));
        double circumx = (1 / d) * xpart;
        double circumy = (1 / d) * ypart;
        return Circle(roundNum(circumradii), checkBound(roundNum(circumx), XSIZE), checkBound(roundNum(circumy), YSIZE), circumx, circumy, circumradii);
    }
    static Circle make9PointCircle(Triangle t, Circle circum) {
        double len1 = t.getLength1();
        double len2 = t.getLength2();
        double len3 = t.getLength3();
        double x1 = t.getX1();
        double x2 = t.getX2();
        double x3 = t.getX3();
        double y1 = t.getY1();
        double y2 = t.getY2();
        double y3 = t.getY3();
        double circumx = circum.getDX();
        double circumy = circum.getDY();
        double centroidx = (x1 + x2 + x3) / 3;
        double centroidy = (y1 + y2 + y3) / 3;
        double circumradii = circum.getdRadius();
        double orthox = (3 * centroidx) - (2 * circumx);
        double orthoy = (3 * centroidy) - (2 * circumy);
        double ninex = findXMidPoint(circumx, orthox);
        double niney = findYMidPoint(circumy, orthoy);
        double nineradii = circumradii / 2;
        return Circle(roundNum(nineradii), checkBound(roundNum(ninex), XSIZE), checkBound(roundNum(niney), YSIZE), ninex, niney, nineradii);
    }
    static Line makeEuler(Circle circumcircle, Circle nine_point_circle) {
        double circumx = circumcircle.getDX();
        double circumy = circumcircle.getDY();
        double ninepointx = nine_point_circle.getDX();
        double ninepointy = nine_point_circle.getDY();
        double dy = (ninepointy - circumy);
        double dx = (ninepointx - circumx);
        double slope = dy / dx;
        double pointx1 = 0;
        double pointx2 = 0;
        double pointy1 = 0;
        double pointy2 = 0;
        double intercept = circumy - (slope * circumx);
        double point800x = (1 - intercept) / slope;//finds x when y is maxed
        double point0x = (0 - intercept) / slope;//finds x when y is 0 y= mx+b
        if (point800x < 1 && point800x >= 0 && point0x < 1 && point0x >= 0) {
            pointx1 = point0x;
            pointx2 = point800x;
            pointy1 = 0;
            pointy2 = 0.998125;
        }
        else if (point800x > 1 || point800x < 0) {
            pointy2 = slope + intercept;
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
};

class makePPM {
public:
    static void makeImage(int width, int height, int** arr) {
        ofstream image;
        image.open("triangle.ppm");
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
                //cout << "" << arr[i][j] << "";
            }
            image << "\n";
        }
        image.close();
    }
};


int main() {//render points by scaling double to 800x800 and rounding

    //Point* first = new Point(5, 3);
    //Point* second = new Point(0, 0);
    //Point first(34, 16);
    //Point second(46,39);
    //int (*arr)[10] = new int[10][10];//change to 800x800, create array
    int xsize = XSIZE;
    int ysize = YSIZE;
    int** arr = new int* [xsize];
    for (int i = 0; i < xsize; i++) {
        arr[i] = new int[ysize];
        for (int j = 0; j < ysize; j++) {
            arr[i][j] = 1;
        }
    }
    //Line firLine(first,second); //on stack
    //*firLine.drawLineC1(*first, *second, arr)*/;//dereference, dereferece, pointer
    //firLine.drawLine(first, second, arr);
    Triangle triangle = makeShapes::makeTriangle();
    triangle.drawTriangle(arr);
    Circle incircle = makeShapes::makeinCircle(triangle);
    incircle.drawCircle(arr, xsize, ysize);

    Circle circumcircle = makeShapes::makecircumCircle(triangle);
    circumcircle.drawCircle(arr, xsize, ysize);
    Circle nine_point_circle = makeShapes::make9PointCircle(triangle,circumcircle);
    nine_point_circle.drawCircle(arr, xsize, ysize);
    //Circle circumcircle(325, 216, 471, 0.27012770646593243, 0.58928201273949832, 0.40591504588542826);
    //Circle nine_point_circle(162, 487, 456, 0.60921168062548603, 0.57053978843085029, 0.20295752294271413);
    Line euler = makeShapes::makeEuler(circumcircle,nine_point_circle);
    euler.drawLine(euler.getP1(), euler.getP2(), arr);
    makePPM::makeImage(xsize, ysize, arr);
    delete[] arr;

}