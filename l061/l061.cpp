// l051.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Randy Fu pd.5

#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <math.h>
#include <cstring>


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
                    arr[centerx + x][centery - y] = Pixel(red, green, blue);
                }
            }
            if (centerx - x >= 0) {
                if (centery + y < ysize) {
                    arr[centerx - x][centery + y] = Pixel(red, green, blue);
                }
                if (centery - y >= 0) {
                    arr[centerx - x][centery - y] = Pixel(red, green, blue);
                }
            }
            if (centerx + y < xsize) {
                if (centery + x < ysize) {
                    arr[centerx + y][centery + x] = Pixel(red, green, blue);
                }
                if (centery - x >= 0) {
                    arr[centerx + y][centery - x] = Pixel(red, green, blue);
                }
            }
            if (centerx - y >= 0) {
                if (centery + x < ysize) {
                    arr[centerx - y][centery + x] = Pixel(red, green, blue);
                }
                if (centery - x >= 0) {
                    arr[centerx - y][centery - x] = Pixel(red, green, blue);
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
        vector<vector<Pixel>> img(height, vector<Pixel>(width, Pixel()));
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
    vector<vector<Pixel>> sobelP3(vector<vector<Pixel>>& imageg, vector<vector<int>>& tanMatrix, vector<vector<double>>& slopeMatrix) {//, string s){
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
                    int gx = -1 * imageg[i - 1][j - 1].getGray() + -2 * imageg[i][j - 1].getGray() - imageg[i + 1][j - 1].getGray() + imageg[i - 1][j + 1].getGray() + 2 * imageg[i][j + 1].getGray() + imageg[i + 1][j + 1].getGray();
                    int gy = -1 * imageg[i - 1][j - 1].getGray() + -2 * imageg[i - 1][j].getGray() - imageg[i - 1][j + 1].getGray() + imageg[i + 1][j - 1].getGray() + 2 * imageg[i + 1][j].getGray() + imageg[i + 1][j + 1].getGray();
                    int g = gx * gx + gy * gy;
                    double radians = atan2(gy, gx);
                    double angle = radians * (180 / 3.1415926535897932384626433832795028841971693993751058209);
                    slopeMatrix[i][j] = (double)gx / gy;
                    int trans = angleTrans(angle);
                    tanMatrix[i][j] = trans;
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
        vector<double> angles{ -180,-135,-90,-45,0,45,90,135,180 };
        int result = 0;
        int min = 1000;
        for (int i = 0; i < (int)angles.size(); i++) {
            double num = abs(angle - angles[i]);
            if (num < min) {
                min = num;
                result = angles[i];
            }
        }
        return result;
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
                    row.push_back(0);
                    outfile << 0 << " " << 0 << " " << 0 << " ";
                }
                else if (abs(angle) == 180 || angle == 0) {
                    if (gray[i - 1][j].getGray() < gVal && gray[i + 1][j].getGray() < gVal) {
                        row.push_back(0);
                        outfile << 0 << " " << 0 << " " << 0 << " ";
                    }
                    else {
                        row.push_back(1);
                        outfile << 1 << " " << 1 << " " << 1 << " ";
                    }
                }
                else if (angle == -135 || angle == 45) {
                    if (gray[i + 1][j + 1].getGray() < gVal && gray[i - 1][j - 1].getGray() < gVal) {
                        row.push_back(0);
                        outfile << 0 << " " << 0 << " " << 0 << " ";
                    }
                    else {
                        row.push_back(1);
                        outfile << 1 << " " << 1 << " " << 1 << " ";
                    }
                }
                else if (abs(angle) == 90) {
                    if (gray[i][j - 1].getGray() < gVal && gray[i][j + 1].getGray() < gVal) {
                        row.push_back(0);
                        outfile << 0 << " " << 0 << " " << 0 << " ";
                    }
                    else {
                        row.push_back(1);
                        outfile << 1 << " " << 1 << " " << 1 << " ";
                    }
                }
                else if (angle == 135 || angle == -45) {
                    if (gray[i - 1][j + 1].getGray() < gVal && gray[i + 1][j - 1].getGray() < gVal) {
                        row.push_back(0);
                        outfile << 0 << " " << 0 << " " << 0 << " ";
                    }
                    else {
                        row.push_back(1);
                        outfile << 1 << " " << 1 << " " << 1 << " ";
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
                //drawPoint(nms,i,j); //May have error here
                drawPoint(vimage, i, j, votes[i][j]); //May have error here
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
    vector<vector<Pixel>> overlay(vector<vector<Pixel>>& img, string in, int threshold) {
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
                if (img[i][j].getRed() >= threshold) {
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
    void drawPoint(vector<vector<Pixel>>& arr, int xcoord, int ycoord, int count) {
        Circle r1(1, xcoord, ycoord, xcoord, ycoord, 1);
        r1.drawCircle(arr, height, width, count, count, count); //change to number of votes 
        Circle r2(2, xcoord, ycoord, xcoord, ycoord, 2);
        r2.drawCircle(arr, height, width, count, count, count);
        Circle r3(3, xcoord, ycoord, xcoord, ycoord, 3);
        r3.drawCircle(arr, height, width, count, count, count);
        Circle r4(4, xcoord, ycoord, xcoord, ycoord, 4);
        r4.drawCircle(arr, height, width, count, count, count);
    }
    void doPart(int argc, char* argv[]) {
        int low_threshold = 4900;
        int high_threshold = 10000;
        int c_threshold = 25;
        string img = "image.ppm";
        string ofile = "image1.ppm";
        string nmsfile = "image2.ppm";
        string finalfile = "imagef.ppm";
        string gout = "imageg.ppm";
        string vout = "imagev.ppm";
        string combout = "imageCC.ppm";
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
            if (strcmp(argv[i], "-f1") == 0) {
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
                c_threshold = atoi(argv[i + 1]);
            }
            if (strcmp(argv[i], "-fv") == 0) {
                vout = argv[i + 1];
            }
            if (strcmp(argv[i], "-fcc") == 0) {
                combout = argv[i + 1];
            }
        }
        vector<vector<Pixel>> imageg = grayscale(img, gout);
        vector<vector<int>> tanMatrix(height, vector<int>(width, 0));
        vector<vector<double>> slopeMatrix(height, vector<double>(width, 0));
        vector<vector<Pixel>>temp = sobelP3(imageg, tanMatrix, slopeMatrix);//adapted sobel. Adds tangent angles
        vector<vector<Pixel>> d = dthreshold(temp, low_threshold, high_threshold, ofile);
        vector<vector<int>> nms = NMS(imageg, tanMatrix, nmsfile);
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
    }
};
int main(int argc, char* argv[])
{
    doParts a;
    //a.doPart1();
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

