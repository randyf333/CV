// l051.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Randy Fu pd.5

#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <math.h>
#include <cstring>



//#define XSIZE 4
//#define YSIZE 3
//#define XSIZE 380
//#define YSIZE 455
using namespace std;
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
class doParts {
private: 
    int width, height;
public:
    vector<vector<Pixel>> grayscale(string s, string out) {
        //ofstream grayscale(string s) {
        ifstream infile;
        infile.open(s);
        ofstream outfile;
        outfile.open(out);
        string p3;
        int max;
        infile >> p3;
        infile >> width;
        infile >> height;
        infile >> max;
        outfile << p3 << endl;
        outfile << width << " " << height << endl;
        outfile << max << endl;
        vector<vector<Pixel>> img(height, vector<Pixel>(width, Pixel()));
        //convert to grayscale
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int r, g, b;
                infile >> r >> g >> b;
                int intensity = (r + g + b) / 3;
                Pixel p(intensity, intensity, intensity);
                img[i][j] = p;
                outfile << intensity << " " << intensity << " " << intensity << " ";
            }
            outfile << endl;
        }
        outfile.close();
        return img;
    }

    //sobel filter on a grayscale image
    vector<vector<Pixel>> sobel(vector<vector<Pixel>>& imageg) {//, string s){
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
                    //row.push_back(g);
                    row.push_back(Pixel(g, g, g));

                }
            }
            sobel.push_back(row);
        }
        //make sobel into ppm
        //for (int i = 0; i < height; i++) {
        //    for (int j = 0; j < width; j++) {
        //        outfile << sobel[i][j].getGray() << " " << sobel[i][j].getGray() << " " << sobel[i][j].getGray() << " ";
        //    }
        //    outfile << endl;
        //}
        //outfile.close();
        return sobel;
    }
    vector<vector<Pixel>> sobelP3(vector<vector<Pixel>>& imageg, vector<vector<int>>& tanMatrix) {//, string s){
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
                    int angle = radians * (180 / 3.1415926535897932384626433832795028841971693993751058209);
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
    int angleTrans(int angle) {
        vector<int> angles{ -180,-135,-90,-45,0,45,90,135,180 };
        int result = 0;
        int min = 1000;
        for (int i = 0; i < (int) angles.size(); i++) {
            int num = abs(angle - angles[i]);
            if (num < min) {
                min = num;
                result = angles[i];
            }
        }
        return result;
    }
    ofstream threshold(vector<vector<Pixel>> imageg, int threshold) {
        ofstream outfile;
        outfile.open("imagem.ppm");
        //string line;
        //int maxval;
        //infile >> line;
        //infile >> width >> height >> maxval;
        int maxval = 1;
        outfile << "P3" << endl;
        outfile << width << " " << height << endl;
        outfile << maxval << endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                //int r, g, b;
                int value = imageg[i][j].getRed();
                if (value > threshold) {
                    outfile << 1 << " " << 1 << " " << 1 << " ";
                }
                else {
                    outfile << 0 << " " << 0 << " " << 0 << " ";
                }
            }
            outfile << endl;
        }
        outfile.close();
        return outfile;
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
        //string line;
        //int maxval;
        //infile >> line;
        //infile >> width >> height >> maxval;
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
        //vector<vector<Pixel>> final = hysthereses(start, low, high, xstart, ystart);
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
    //void doPart1() {
    //    vector<vector<Pixel>> imageg = grayscale("image.ppm");
    //    vector<vector<Pixel>>temp = sobel(imageg);
    //    int t = 10000;
    //    threshold(temp, t);
    //}
    //void doPart2(int argc, char* argv[]) {//Double threshold and Hysteresis
    //    int low_threshold = 10000;
    //    int high_threshold = 15000;
    //    string img = "image.ppm";
    //    string ofile = "image1.ppm";
    //    for (int i = 0; i < argc; i++) {
    //        if (strcmp(argv[i], "-f") == 0) {
    //            img = argv[i + 1];
    //        }
    //        if (strcmp(argv[i], "-lt") == 0) {
    //            low_threshold = pow(atoi(argv[i + 1]), 2);
    //        }
    //        if (strcmp(argv[i], "-ht") == 0) {
    //            high_threshold = pow(atoi(argv[i + 1]), 2);
    //        }
    //        if (strcmp(argv[i], "-of") == 0) {
    //            ofile = argv[i + 1];
    //        }
    //    }
    //    vector<vector<Pixel>> imageg = grayscale(img);
    //    vector<vector<Pixel>>temp = sobel(imageg);
    //    dthreshold(temp, low_threshold, high_threshold, ofile);
    //}
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
    void combine(vector<vector<int>> nms, vector<vector<Pixel>> dthres, string s) {
        ofstream outfile;
        outfile.open(s);
        outfile << "P3" << endl;
        outfile << width << " " << height << endl;
        outfile << 1 << endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (nms[i][j] == 1 && (dthres[i][j].getGray() == 1 || dthres[i][j].getGray() == 3)) {
                    outfile << 1 << " " << 1 << " " << 1 << " ";
                }
                else {
                    outfile << 0 << " " << 0 << " " << 0 << " ";
                }
            }
            outfile << endl;
        }
        outfile.close();
    }
    void doPart3(int argc, char* argv[]) {
        int low_threshold = 10000;
        int high_threshold = 15000;
        string img = "image.ppm";
        string ofile = "image1.ppm";
        string nmsfile = "image2.ppm";
        string finalfile = "imagef.ppm";
        string gout = "imageg.ppm";
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
            if (strcmp(argv[i], "-of") == 0) {
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
        }
        //doPart2(argc, argv);
        vector<vector<Pixel>> imageg = grayscale(img,gout);
        vector<vector<int>> tanMatrix(height, vector<int>(width, 0));
        vector<vector<Pixel>>temp = sobelP3(imageg, tanMatrix);//adapted sobel. Adds tangent angles
        vector<vector<Pixel>> d = dthreshold(temp, low_threshold, high_threshold, ofile);
        vector<vector<int>> nms = NMS(imageg,tanMatrix,nmsfile);
        combine(nms, d, finalfile);
    }
};
int main(int argc, char* argv[])
{
    doParts a;
    //a.doPart1();
    a.doPart3(argc, argv);
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

