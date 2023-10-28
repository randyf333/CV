// l051.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <math.h>



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
public:
    int width, height;
    vector<vector<Pixel>> grayscale(string s){
    //ofstream grayscale(string s) {
        ifstream infile;
        infile.open(s);
        ofstream outfile;
        outfile.open("imageg.ppm");
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
    vector<vector<Pixel>> sobel(vector<vector<Pixel>> &imageg){//, string s){
        vector<vector<Pixel>> sobel;
        for (int i = 0; i < height; i++) {
            vector<Pixel> row;
            for (int j = 0; j < width; j++) {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                    row.push_back(Pixel(0,0,0));
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

    ofstream threshold(vector<vector<Pixel>> imageg, int threshold){
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
void doPart1() {
    vector<vector<Pixel>> imageg = grayscale("image.ppm");
    //ifstream infile2("imageg.ppm");
    vector<vector<Pixel>>temp = sobel(imageg);//,"imageg.ppm");
    //ifstream infile3("images.ppm");
    int t = 10000;
    threshold(temp, t);
}
};
int main()
{
    doParts a;
    a.doPart1();
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

