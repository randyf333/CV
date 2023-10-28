// l051.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Randy Fu pd.5

#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <math.h>
#include <cstring>
#include <map>

using namespace std;
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
class Pixel {
private:
    int red;
    int green;
    int blue;
    int gscale;
public:
    Pixel() {
        red = 0;
        green = 0;
        blue = 0;
        gscale = 0;
    }
    Pixel(int r, int g, int b) {
        red = r;
        green = g;
        blue = b;
        gscale = (red + green + blue) / 3;
    }
    void setRed(int r) {
        red = r;
    }
    void setGreen(int g) {
        green = g;
    }
    void setBlue(int b) {
        blue = b;
    }
    void setGray() {
        gscale = (red + green + blue) / 3;
    }
    int getRed() {
        return red;
    }
    int getGreen() {
        return green;
    }
    int getBlue() {
        return blue;
    }
    int getGray() {
        return gscale;
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
    void drawCircle(vector<vector<Pixel>>& arr, int xsize, int ysize, int red, int green, int blue) {//radius, center xcoord, center ycoord
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
                    arr[centerx + x][centery + y] = Pixel(red, green, blue);
                }
                if (centery - y >= 0) {
                    arr[centerx + x][centery - y] = Pixel(red, green, blue);;
                }
            }
            if (centerx - x >= 0) {
                if (centery + y < ysize) {
                    arr[centerx - x][centery + y] = Pixel(red, green, blue);;
                }
                if (centery - y >= 0) {
                    arr[centerx - x][centery - y] = Pixel(red, green, blue);;
                }
            }
            if (centerx + y < xsize) {
                if (centery + x < ysize) {
                    arr[centerx + y][centery + x] = Pixel(red, green, blue);;
                }
                if (centery - x >= 0) {
                    arr[centerx + y][centery - x] = Pixel(red, green, blue);;
                }
            }
            if (centerx - y >= 0) {
                if (centery + x < ysize) {
                    arr[centerx - y][centery + x] = Pixel(red, green, blue);;
                }
                if (centery - x >= 0) {
                    arr[centerx - y][centery - x] = Pixel(red, green, blue);;
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
    Line(Point a, double nslope) {
        p1 = a;
        slope = nslope;
        intercept = a.getY() - (slope * a.getX());
    }
    void setPoints(Point a, Point b) {
        p1 = a;
        p2 = b;
    }
    int getXfromY(int y) {
        return (y - intercept) / slope;
    }
    int getYfromX(int x) {
        return (slope * x) + intercept;
    }
    void drawLine(Point a, Point b, vector<vector<int>>& arr, int width, int height) {//, int color) { //Bresenham - Switch height and width maybe
        int x1 = a.getX();
        int y1 = a.getY();
        int x2 = b.getX();
        int y2 = b.getY();
        if (x1 == height) { x1 = x1 - 1; }
        if (x2 == height) { x2 = x2 - 1; }
        if (y1 >= width) { y1 = y1 - 1; }
        if (y2 >= width) { y2 = y2 - 1; }
        int dx = std::abs(x2 - x1);
        int dy = std::abs(y2 - y1);
        int x = x1;
        int y = y1;
        if (dx > dy) {
            arr[x][y] = arr[x][y] + 1;
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
                arr[x][y] = arr[x][y] + 1;

            }
        }
        else
        {
            arr[x][y] = arr[x][y] + 1;
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
                arr[x][y] = arr[x][y] + 1;
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
private:
    int width, height;
public:
    vector<vector<Pixel>> grayscale(string s, string out) {
        //ofstream grayscale(string s) {
        ifstream infile;
        infile.open(s);
        //ofstream outfile;
        //outfile.open(out);
        string p3;
        //int max; 
        infile >> p3;
        infile >> width;
        infile >> height;
        //infile >> max;
        //outfile << p3 << endl;
        //outfile << width << " " << height << endl;
        //outfile << max << endl;
        vector<vector<Pixel>> img(height, vector<Pixel>(width, Pixel(0, 0, 0)));
        //convert to grayscale
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int r, g, b;
                infile >> r >> g >> b;
                int intensity = (r + g + b) / 3;
                Pixel p(intensity, intensity, intensity);
                img[i][j] = p;
                //outfile << intensity << " " << intensity << " " << intensity << " ";
            }
            //outfile << endl;
        }
        //outfile.close();
        return img;
    }
    //sobel filter on image and finding angle for NMS
    vector<vector<Pixel>> sobelP3(vector<vector<Pixel>>& grey, vector<vector<int>>& tanMatrix, vector<vector<double>>& slopeMatrix) {//, string s){
        //ofstream o;
        //o.open("angles.txt");
        vector<vector<Pixel>> sobel;
        for (int i = 0; i < height; i++) {
            vector<Pixel> row;
            for (int j = 0; j < width; j++) {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                    row.push_back(Pixel(0, 0, 0));
                }
                else {
                    //int gx = -1 * (grey[i - 1][j - 1].getGray()) + (grey[i + 1][j - 1].getGray()) + -2 * (grey[i - 1][j].getGray()) + 2 * (grey[i + 1][j].getGray()) + -1 * (grey[i - 1][j + 1].getGray()) + (grey[i + 1][j + 1].getGray());
                    //int gy = grey[i - 1][j - 1].getGray() + 2 * (grey[i][j - 1].getGray()) + (grey[i + 1][j - 1].getGray()) + -1 * (grey[i - 1][j + 1].getGray()) + -2 * (grey[i][j + 1].getGray()) + -1 * (grey[i + 1][j + 1].getGray());
                    int gx = -grey[i - 1][j - 1].getGray() - 2 * grey[i][j - 1].getGray() - grey[i + 1][j - 1].getGray() + grey[i - 1][j + 1].getGray() + 2 * grey[i][j + 1].getGray() + grey[i + 1][j + 1].getGray();
                    int gy = -grey[i - 1][j - 1].getGray() - 2 * grey[i - 1][j].getGray() - grey[i - 1][j + 1].getGray() + grey[i + 1][j - 1].getGray() + 2 * grey[i + 1][j].getGray() + grey[i + 1][j + 1].getGray();
                    int g = gx * gx + gy * gy;
                    double radians = atan2(gy, gx);
                    double angle = radians * (180 / 3.1415926535897932384626433832795028841971693993751058209);
                    slopeMatrix[i][j] = (double)gx / gy;
                    tanMatrix[i][j] = angleTrans(angle);
                    //row.push_back(g);
                    row.push_back(Pixel(g, g, g));

                }
            }
            sobel.push_back(row);
        }
        //outfile.close();
        //o.close()
        return sobel;
    }
    int angleTrans(double angle) {
        if (angle <= -157.5) { return -180; }
        else if (angle <= -112.5) { return -135; }
        else if (angle <= -67.5) { return -90; }
        else if (angle <= -22.5) { return -45; }
        else if (angle <= 22.5) { return 0; }
        else if (angle <= 67.5) { return 45; }
        else if (angle <= 112.5) { return 90; }
        else if (angle <= 157.5) { return 135; }
        else { return 180; }
    }
    void hysthereses(vector<vector<Pixel>>& img, int low, int high, int xstart, int ystart) {
        //vector<vector<Pixel>> final(height, vector<Pixel>(width, Pixel()));
        if (img[xstart][ystart].getGray() == 3 || xstart < 0 || xstart >= width || ystart < 0 || ystart >= height || img[xstart][ystart].getGray() == 0) {
            return;
        }
        img[xstart][ystart] = Pixel(3, 3, 3);
        hysthereses(img, low, high, xstart - 1, ystart - 1);
        hysthereses(img, low, high, xstart - 1, ystart);
        hysthereses(img, low, high, xstart - 1, ystart + 1);
        hysthereses(img, low, high, xstart, ystart - 1);
        hysthereses(img, low, high, xstart, ystart + 1);
        hysthereses(img, low, high, xstart + 1, ystart - 1);
        hysthereses(img, low, high, xstart + 1, ystart);
        hysthereses(img, low, high, xstart + 1, ystart + 1);
    }
    vector<vector<Pixel>> dthreshold(vector<vector<Pixel>>& image, int low, int high, string s) {
        ofstream outfile;
        outfile.open(s);
        int maxval = 1;
        outfile << "P3" << endl;
        outfile << width << " " << height << endl;
        outfile << maxval << endl;
        vector<vector<Pixel>> start(height, vector<Pixel>(width, Pixel()));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int value = image[i][j].getGray();
                if (value > high) {
                    start[i][j] = Pixel(1, 1, 1);
                }
                else if (value < high && value > low) {
                    start[i][j] = Pixel(2, 2, 2);
                }
                else {
                    start[i][j] = Pixel(0, 0, 0);
                }
            }
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (start[i][j].getGray() == 1) {
                    hysthereses(start, low, high, i, j);
                }
            }
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                //int r, g, b;
                int value = start[i][j].getRed();
                if (value == 1 || value == 3) {
                    outfile << 1 << " " << 1 << " " << 1 << " ";
                }
                else {
                    outfile << 0 << " " << 0 << " " << 0 << " ";
                }
            }
            outfile << endl;
        }
        outfile.close();
        return start;
    }
    vector<vector<int>> NMS(vector<vector<Pixel>>& gray, vector<vector<int>>& angles, string s) {
        ofstream outfile;
        outfile.open(s);
        outfile << "P3" << endl;
        outfile << width << " " << height << endl;
        outfile << 1 << endl;
        vector<vector<int>> nms;
        for (int i = 0; i < height; i++) {
            vector<int> row;
            for (int j = 0; j < width; j++) {
                int angle = angles[i][j];
                int gVal = gray[i][j].getGray();
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                    row.push_back(1);
                    outfile << 1 << " " << 1 << " " << 1 << " ";
                }
                else if (abs(angle) == 180 || angle == 0) {
                    //gray[i][j - 1].getGray() <= gVal && gray[i][j + 1].getGray() <= gVal
                    //
                    if (gray[i - 1][j].getGray() <= gVal && gray[i + 1][j].getGray() <= gVal) {
                        row.push_back(1);
                        outfile << 1 << " " << 1 << " " << 1 << " ";
                        //row.push_back(0);
                        //outfile << 0 << " " << 0 << " " << 0 << " ";
                    }
                    else {
                        row.push_back(0);
                        outfile << 0 << " " << 0 << " " << 0 << " ";
                        //row.push_back(1);
                        //outfile << 1 << " " << 1 << " " << 1 << " ";
                    }
                }
                else if (angle == -135 || angle == 45) { //switch signs
                    if (gray[i + 1][j + 1].getGray() <= gVal && gray[i - 1][j - 1].getGray() <= gVal) {
                        //row.push_back(0);
                        //outfile << 0 << " " << 0 << " " << 0 << " ";
                        row.push_back(1);
                        outfile << 1 << " " << 1 << " " << 1 << " ";
                    }
                    else {
                        //row.push_back(1);
                        //outfile << 1 << " " << 1 << " " << 1 << " ";
                        row.push_back(0);
                        outfile << 0 << " " << 0 << " " << 0 << " ";
                    }
                }
                else if (abs(angle) == 90) {
                    //gray[i - 1][j].getGray() <= gVal && gray[i + 1][j].getGray() <= gVal
                    //gray[i][j - 1].getGray() <= gVal && gray[i][j + 1].getGray() <= gVal
                    if (gray[i][j - 1].getGray() <= gVal && gray[i][j + 1].getGray() <= gVal) {
                        //row.push_back(0);
                        //outfile << 0 << " " << 0 << " " << 0 << " ";
                        row.push_back(1);
                        outfile << 1 << " " << 1 << " " << 1 << " ";
                    }
                    else {
                        //row.push_back(1);
                        //outfile << 1 << " " << 1 << " " << 1 << " ";
                        row.push_back(0);
                        outfile << 0 << " " << 0 << " " << 0 << " ";
                    }
                }
                else if (angle == 135 || angle == -45) { //switch signs
                    if (gray[i - 1][j + 1].getGray() <= gVal && gray[i + 1][j - 1].getGray() <= gVal) {
                        //row.push_back(0);
                        //outfile << 0 << " " << 0 << " " << 0 << " ";
                        row.push_back(1);
                        outfile << 1 << " " << 1 << " " << 1 << " ";
                    }
                    else {
                        //row.push_back(1);
                        //outfile << 1 << " " << 1 << " " << 1 << " ";
                        row.push_back(0);
                        outfile << 0 << " " << 0 << " " << 0 << " ";
                    }
                }
            }
            outfile << endl;
            nms.push_back(row);
        }
        return nms;
    }
    vector<vector<Pixel>> combine(vector<vector<int>> nms, vector<vector<Pixel>> dthres, string s) {
        vector<vector<Pixel>> last(height, vector<Pixel>(width, Pixel()));
        ofstream outfile;
        outfile.open(s);
        outfile << "P3" << endl;
        outfile << width << " " << height << endl;
        outfile << 255 << endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (nms[i][j] == 1 && (dthres[i][j].getGray() == 1 || dthres[i][j].getGray() == 3)) {
                    outfile << 255 << " " << 255 << " " << 255 << " ";
                    last[i][j] = Pixel(255, 255, 255);
                }
                else {
                    outfile << 0 << " " << 0 << " " << 0 << " ";
                    last[i][j] = Pixel(0, 0, 0);
                }
            }
            outfile << endl;
        }
        outfile.close();
        return last;
    }
    void edgeDetection(int argc, char* argv[]) {
        int low_threshold = 10000;
        int high_threshold = 15000;
        string img = "image.ppm";
        string ofile = "image1.ppm";
        string nmsfile = "image2.ppm";
        string finalfile = "imagef.ppm";
        string gout = "imageg.ppm";
        int threshold = 12500;
        for (int i = 0; i < argc; i++) {
            if (strcmp(argv[i], "-F") == 0) {
                img = argv[i + 1];
            }
            if (strcmp(argv[i], "-L") == 0) {
                low_threshold = pow(atoi(argv[i + 1]), 2);
            }
            if (strcmp(argv[i], "-H") == 0) {
                high_threshold = pow(atoi(argv[i + 1]), 2);
            }
            if (strcmp(argv[i], "-TC") == 0) {
                threshold = atoi(argv[i + 1]);
            }
            //if (strcmp(argv[i], "-of") == 0) {
            //    ofile = argv[i + 1];
            //}
            //if (strcmp(argv[i], "fg") == 0) {
            //    gout = argv[i + 1];
            //}
            //if (strcmp(argv[i], "f2") == 0) {
            //    nmsfile = argv[i + 1];
            //}
            //if (strcmp(argv[i], "ff") == 0) {
            //    finalfile = argv[i + 1];
            //}
        }
        //doPart2(argc, argv);
        vector<vector<Pixel>> imageg = grayscale(img, gout);
        vector<vector<int>> tanMatrix(height, vector<int>(width, 0));
        vector<vector<double>> angleMatrix(height, vector<double>(width, 0));
        vector<vector<Pixel>>temp = sobelP3(imageg, tanMatrix, angleMatrix);//adapted sobel. Adds tangent angles
        vector<vector<Pixel>> d = dthreshold(temp, low_threshold, high_threshold, ofile);
        vector<vector<int>> nms = NMS(imageg, tanMatrix, nmsfile);
        combine(nms, d, finalfile);
    }
    void lineVote(Line l, vector<vector<int>>& votes, Point start) {
        Point p1 = Point(start.getX() - 100, l.getYfromX(start.getX() - 100));
        Point p2 = Point(start.getX() + 100, l.getYfromX(start.getX() + 100));
        int x0 = p1.getX();
        int x1 = p2.getX();
        int y0 = p1.getY();
        int y1 = p2.getY();
        int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1, dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int error = dx + dy;
        while (true) {
            if (x0 >= 0 && x0 < (int)votes.size() && y0 >= 0 && y0 < (int)votes[0].size()) {
                votes[x0][y0] += 1;
            }
            if (x0 == x1 && y0 == y1) {
                break;
            }
            int error2 = 2 * error;

            if (error2 >= dy) {
                if (x0 == x1) { break; }
                error = error + dy;
                x0 = x0 + sx;
            }

            if (error2 <= dx) {
                if (y0 == y1) { break; }
                error = error + dx;
                y0 = y0 + sy;
            }

        }
    }
    int voteOnCircle(int xc, int yc, int x, int y, vector<vector<Pixel>>& edges) {
        int count = 0;
        Point temp[8] = { Point(xc + x,yc + y),Point(xc - x,yc + y),Point(xc + x,yc - y),Point(xc - x,yc - y),
            Point(xc + y,yc + x),Point(xc - y,yc + x),Point(xc + y,yc - x),Point(xc - y,yc - x) };
        for (int i = 0; i < 8; i++) {
            if (temp[i].getX() >= 0 && temp[i].getX() < height && temp[i].getY() >= 0 && temp[i].getY() < width) {
                if (edges[temp[i].getX()][temp[i].getY()].getGray() == 255) {
                    count++;
                }
            }
        }
        return count;
    }
    int circleVote(vector<vector<Pixel>>& arr, int xsize, int ysize, int radius, int centerx, int centery) {//radius, center xcoord, center ycoord
        int total = 0;
        int xc = centerx;
        int yc = centery;
        int r = radius;
        int x = 0, y = r, dec = 3 - 2 * r;
        total += voteOnCircle(xc, yc, x, y, arr);
        while (y >= x) {
            x++;
            if (dec > 0) {
                y--;
                dec = dec + 4 * (x - y) + 10;
            }
            else {
                dec = dec + 4 * x + 6;
            }
            total += voteOnCircle(xc, yc, x, y, arr);
        }
        return total;
    }
    vector<vector<int>> vote(vector<vector<Pixel>>& nms, vector<vector<double>>& slopes) { //final canny edge, threshold, matrix of slopes //May have error here
        vector<vector<int>> votes(height, vector<int>(width, 0));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (nms[i][j].getGray() == 255) { //find if edge
                    //vote on direction of gradient 
                    Point start(i, j);
                    Line l(start, slopes[i][j]); //slopes are x/y
                    lineVote(l, votes, start);
                    //150
                }
            }
        }
        return votes;
    }
    vector<vector<Pixel>> findCenter(vector<vector<int>>& votes, int threshold) {
        vector<vector<Pixel>> vimage(height, vector<Pixel>(width, Pixel(0, 0, 0)));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                drawPoint(vimage, i, j, votes[i][j], votes[i][j], votes[i][j]);
            }
        }
        return vimage;
    }
    void toPPM(vector<vector<Pixel>>& img, string s, int max) {//edit to overlay
        ofstream outfile;
        outfile.open(s);
        outfile << "P3" << endl;
        outfile << width << " " << height << endl;
        outfile << max << endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                outfile << img[i][j].getRed() << " " << img[i][j].getGreen() << " " << img[i][j].getBlue() << " ";
            }
        }
        outfile.close();
    }
    vector<vector<Pixel>> overlay(vector<vector<Pixel>>& img, string in, int threshold) { //img is votes
        vector<vector<Pixel>> comb(height, vector<Pixel>(width, Pixel(0, 0, 0)));
        ifstream infile;
        infile.open(in);
        infile.ignore(100, '\n');
        infile.ignore(100, '\n');
        infile.ignore(100, '\n');
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int r, g, b;
                infile >> r >> g >> b;
                if (img[i][j].getRed() >= threshold || img[i][j].getRed() == 255) {
                    comb[i][j] = Pixel(255, 0, 0);
                }
                else {
                    comb[i][j] = Pixel(r, g, b);
                }
            }
        }
        infile.close();
        return comb;
    }
    void drawPoint(vector<vector<Pixel>>& arr, int xcoord, int ycoord, int r, int g, int b) {
        Circle r1(1, xcoord, ycoord, xcoord, ycoord, 1);
        r1.drawCircle(arr, height, width, r, g, b); //change to number of votes 
        Circle r2(2, xcoord, ycoord, xcoord, ycoord, 2);
        r2.drawCircle(arr, height, width, r, g, b);
        Circle r3(3, xcoord, ycoord, xcoord, ycoord, 3);
        r3.drawCircle(arr, height, width, r, g, b);
        Circle r4(4, xcoord, ycoord, xcoord, ycoord, 4);
        r4.drawCircle(arr, height, width, r, g, b);
    }
    vector<vector<Pixel>> catchCoins(vector<vector<Pixel>>& ccImage, int threshold, vector<vector<Pixel>>& edges, double percentage, vector<vector<int>>& radi) {
        //int minR = width / 20;
        //int maxR = width / 15;
        int minR = 80;
        int maxR = 130;
        int count = 0;
        vector<vector<Pixel>> cEdges(height, vector<Pixel>(width, Pixel(0, 0, 0)));
        vector<vector<double>> percent(height, vector<double>(width));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (ccImage[i][j].getRed() >= threshold) { //only do on centers
                    map<int, int> radtoVotes;
                    for (int t = minR; t <= maxR; t++) {
                        radtoVotes[t] = 0;
                    }
                    double maxPercent = -1;
                    double maxRadius = 0;
                    for (int r = minR; r <= maxR; r++) {
                        radtoVotes[r] = circleVote(edges, height, width, r, i, j); //votes at that radius
                        if (radtoVotes[r] > (2 * 3.14159 * r) * percentage) { //fix percentage
                            if ((double)radtoVotes[r] / (2 * 3.14159 * r) > maxPercent) {
                                maxPercent = (double)radtoVotes[r] / (2 * 3.14159 * r);
                                ////cout << "Dividing " << radtoVotes[r] << " " << (2 * 3.1415926535 * r) << " " << maxPercent << endl;
                                maxRadius = r;
                            }
                        }
                    }
                    radi[i][j] = maxRadius;
                    percent[i][j] = maxPercent;
                }
            }
        }
        //for (int a = 0; a < height; a++) {
        //    for (int b = 0; b < width; b++) {
        //        cout << radi[a][b];
        //    }
        //}
        //cout << endl;
        //cout << endl;
        
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (radi[i][j] > 0) {
                    for (int i2 = max(i - minR, 0); i2 < min(i + minR, (int)height); i2++) {
                        for (int j2 = max(j - minR, 0); j2 < min(j + minR, (int)width); j2++) {
                            if (radi[i2][j2] > 0 && (i2 != i || j2 != j) && abs(radi[i][j] - radi[i2][j2]) < 50) {
                                if (percent[i][j] > percent[i2][j2]) {
                                    radi[i2][j2] = 0;
                                }
                                else {
                                    radi[i][j] = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        //for (int r = 0; r < height; r++) {
        //    for (int c = 0; c < width; c++) {
        //        if (radi[r][c] == 0) {
        //            continue;
        //        }
        //        for (int x = -50; x <= 50; x++) {
        //            for (int y = -50; y <= 50; y++) {
        //                if (r + x >= 0 && r + x < height && c + y >= 0 && c + y < width) {
        //                    if (radi[r + x][c + y] == 0) {
        //                        continue;
        //                    }
        //                    if (radi[r + x][c + y] == radi[r][c]) {
        //                        int c1 = 0;
        //                        int c2 = 0;
        //                        for (int k = -50; k <= 50; k++) {
        //                            for (int l = -50; l <= 50; l++) {
        //                                if (r + k >= 0 && r + k < height && c + l >= 0 && c + l < width) {
        //                                    if (radi[r + k][c + l] != 0) {
        //                                        c1++;
        //                                    }
        //                                    if (radi[r + x + k][c + y + l] != 0) {
        //                                        c2++;
        //                                    }
        //                                }
        //                            }
        //                        }
        //                        if (c1 > c2) {
        //                            radi[r + x][c + y] = 0;
        //                        }
        //                        else if (c2 > c1) {
        //                            radi[r][c] = 0;
        //                        }
        //                        else {
        //                            if (rand() % 2 == 0) {
        //                                radi[r + x][c + y] = 0;
        //                            }
        //                            else {
        //                                radi[r][c] = 0; 
        //                            }
        //                        }
        //                    }
        //                    //cout << "Comparing: " << percent[r + x][c + y] << " to " << percent[r][c] << " ";
        //                    if (percent[r + x][c + y] >= percent[r][c]) {
        //                        radi[r][c] = 0;
        //                        //percent[r][c] = -1;
        //                    }
        //                    else {
        //                        radi[r + x][c + y] = 0;
        //                        //percent[r + x][c + y] = -1;
        //                    }

        //                }
        //            }
        //        }
        //    }
        //}
        for (int a = 0; a < height; a++) {
            for (int b = 0; b < width; b++) {
                //cout << radi[a][b];
                if (radi[a][b] != 0) {
                    drawEdges(cEdges, a, b, radi[a][b]);
                }
            }
        }
        return cEdges;
    }

    void drawEdges(vector<vector<Pixel>>& arr, int xcoord, int ycoord, int radius) {
        Circle r1(radius - 1, xcoord, ycoord, xcoord, ycoord, radius - 1);
        r1.drawCircle(arr, height, width, 255, 0, 0);
        Circle r2(radius, xcoord, ycoord, xcoord, ycoord, radius);
        r2.drawCircle(arr, height, width, 255, 0, 0);
        Circle r3(radius + 1, xcoord, ycoord, xcoord, ycoord, radius + 1);
        r3.drawCircle(arr, height, width, 255, 0, 0);
    }
    void drawCoins(vector<vector<Pixel>>& img, vector<vector<int>>& radi, string in, string money, int small, int medium, int large, int half_dollar, double pennyred) { //radius of penny, radius of nickels+, radius of dollar coins
        //vector<vector<Pixel>> final(height, vector<Pixel>(width, Pixel(0,0,0)));
        ofstream out;
        out.open(money);
        int pennies = 0, nickels = 0, dimes = 0, quarters = 0, dollars = 0, half_dollars = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (radi[i][j] > 0) {
                    int r = 0, g = 0, b = 0;
                    if (radi[i][j] < medium) {
                        double redness = 0;
                        //double greeness = 0;
                        //double blueness = 0;
                        double nonredness = 0;
                        for (int i2 = max(i - 50, 0); i2 < min(i + 51, (int)radi.size()); i2++) {
                            for (int j2 = max(j - 50, 0); j2 < min(j + 51, (int)radi[0].size()); j2++) {
                                redness += img[i2][j2].getRed();
                                nonredness += img[i2][j2].getGreen() + img[i2][j2].getBlue();
                                //greeness += img[i2][j2].getGreen();
                                //blueness += img[i2][j2].getBlue();
                            }
                        }
                        if (redness/nonredness > pennyred){//greeness && redness > blueness) {
                            r = 255;
                            pennies++;
                        }
                        else {
                            //g = 255;
                            //b = 255;
                            //nickels++;
                            if (radi[i][j] < small) {
                                b = 255;
                                dimes++;
                            }
                            else {
                                r = 255, g = 255;
                                nickels++;
                            }
                        }
                    }
                    //else {
                    //    g = 32;
                    //    r = 160;
                    //    b = 250;
                    //    quarters++;
                    //}
                    else if(radi[i][j] < large){
                        g = 32;
                        r = 160;
                        b = 250;
                        quarters++;
                    }
                    else if(radi[i][j] < half_dollar){
                        r = 255, b = 255;
                        dollars++;
                    }
                    else {
                        g = 255;
                        half_dollars++;
                    }
                    if (radi[i][j] > 0) {
                        Circle drawC(radi[i][j], i, j, i, j, radi[i][j]);
                        drawC.drawCircle(img, height, width, r, g, b);
                        drawPoint(img, i, j, 255, 0, 0);
                    }
                }
            }
        }
        out << pennies << " pennies" << endl;
        out << nickels << " nickels" << endl;
        out << dimes << " dimes" << endl;
        out << quarters << " quarters" << endl;
        out << half_dollars << " half-dollar coins" << endl;
        out << dollars << " dollar coins" << endl;
        out << "Total Sum: $" << (0.01 * pennies + 0.05 * nickels + 0.1 * dimes + 0.25 * quarters + 0.5 * half_dollars + dollars) << endl;
        cout << pennies << " pennies" << endl;
        cout << nickels << " nickels" << endl;
        cout << dimes << " dimes" << endl;
        cout << quarters << " quarters" << endl;
        cout << half_dollars << " half-dollar coins" << endl;
        cout << dollars << " dollar coins" << endl;
        cout << "Total Sum: $" << (0.01 * pennies + 0.05 * nickels + 0.1 * dimes + 0.25 * quarters + 0.5 * half_dollars + dollars) << endl;
        //return final;
    }
    vector<vector<Pixel>> getPic(string in) {
        vector<vector<Pixel>> pic(height, vector<Pixel>(width));
        ifstream infile;
        infile.open(in);
        infile.ignore(100, '\n');
        infile.ignore(100, '\n');
        infile.ignore(100, '\n');
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int r, g, b;
                infile >> r >> g >> b;
                pic[i][j] = Pixel(r, g, b);
            }
        }
        return pic;
    }
    void doPart(int argc, char* argv[]) {
        int low_threshold = 4900;
        int high_threshold = 10000;
        int c_threshold = 15;
        string img = "image.ppm";
        string ofile = "image1.ppm";
        string nmsfile = "image2.ppm";
        string finalfile = "imagef.ppm";
        string gout = "imageg.ppm";
        string vout = "imagev.ppm";
        string combout = "imageCC.ppm";
        string circlesOut = "imageCircles.ppm";
        string colorCircles = "imageCoins.ppm";
        string total = "results.txt";
        double percentage = 0.15;
        for (int i = 0; i < argc; i++) {
            if (strcmp(argv[i], "-f") == 0) {
                img = argv[i + 1];
            }
            if (strcmp(argv[i], "-lt") == 0) {
                low_threshold = pow(atoi(argv[i + 1]), 2);
            }
            if (strcmp(argv[i], "-ht") == 0) {
                high_threshold = pow(atoi(argv[i + 1]), 2);
            }
            if (strcmp(argv[i], "-fl") == 0) {
                ofile = argv[i + 1];
            }
            if (strcmp(argv[i], "fg") == 0) {
                gout = argv[i + 1];
            }
            if (strcmp(argv[i], "f2") == 0) {
                nmsfile = argv[i + 1];
            }
            if (strcmp(argv[i], "ff") == 0) {
                finalfile = argv[i + 1];
            }
            if (strcmp(argv[i], "-TC") == 0) {
                c_threshold = atoi(argv[i + 1]) / 10;
            }
            if (strcmp(argv[i], "-fv") == 0) {
                vout = argv[i + 1];
            }
            if (strcmp(argv[i], "-fcc") == 0) {
                combout = argv[i + 1];
            }
            if (strcmp(argv[i], "-TCircle") == 0) {
                percentage = stod(argv[i + 1]);
            }
            if (strcmp(argv[i], "-fCi") == 0) {
                circlesOut = argv[i + 1];
            }
            if (strcmp(argv[i], "-fCo") == 0) {
                colorCircles = argv[i + 1];
            }
            if (strcmp(argv[i], "-fR") == 0) {
                total = argv[i + 1];
            }
        }
        vector<vector<Pixel>> imageg = grayscale(img, gout);
        vector<vector<Pixel>> picture = getPic(img);
        vector<vector<int>> tanMatrix(height, vector<int>(width, 0));
        vector<vector<double>> slopeMatrix(height, vector<double>(width, 0));
        vector<vector<Pixel>>temp = sobelP3(imageg, tanMatrix, slopeMatrix);//adapted sobel. Adds tangent angles
        vector<vector<Pixel>> d = dthreshold(temp, low_threshold, high_threshold, ofile);
        vector<vector<int>> nms = NMS(temp, tanMatrix, nmsfile);
        vector<vector<Pixel>> last = combine(nms, d, finalfile);

        vector<vector<int>> votes = vote(last, slopeMatrix);
        vector<vector<Pixel>>vimage = findCenter(votes, c_threshold);
        int votesmax = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (votes[i][j] > votesmax) {
                    votesmax = votes[i][j];
                }
            }
        }
        toPPM(vimage, vout, votesmax);

        vector<vector<Pixel>> combined = overlay(vimage, img, c_threshold);
        toPPM(combined, combout, 255);
        cout << "Part A Start" << endl;

        //Part A 
        vector<vector<int>> radi(height, vector<int>(width));
        vector<vector<Pixel>> cEdges = /*radiusvote(vimage, last, percentage);*/catchCoins(vimage, c_threshold, last, percentage, radi);
        vector<vector<Pixel>> circles = overlay(cEdges, img, c_threshold);
        toPPM(circles, circlesOut, 255);
        drawCoins(picture, radi, img, total, 85, 105, 120, 135, 0.6); ////change values
        toPPM(picture, colorCircles, 255);
    }
};
int main(int argc, char* argv[])
{
    doParts a;
    a.doPart(argc, argv);
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

