// l051.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Randy Fu pd.5

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <map>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class doParts {
private:
    int width, height;
public:
    void doPart(int argc, char* argv[]) { //85, 105, 120, 135, 0.6
        int low_threshold = 80;
        int high_threshold = 100;
        int c_threshold = 30;
        int penny = 0, nickels = 0, dimes = 0, quarters = 0, dollars = 0, half_dollars = 0;
        string img = "image.jpg";
        int minR = 50;
        int maxR = 200;
        //double pennyred = 0.6;
        int specialCoins = 0;
        int minDist = 100;
        /*string ofile = "image1.ppm";
        string nmsfile = "image2.ppm";
        string finalfile = "imagef.ppm";
        string gout = "imageg.ppm";
        string vout = "imagev.ppm";
        string combout = "imageCC.ppm";
        string circlesOut = "imageCircles.ppm";
        string colorCircles = "imageCoins.ppm";*/
        string total = "results.txt";
        for (int i = 0; i < argc; i++) {
            if (strcmp(argv[i], "-f") == 0) {
                img = argv[i + 1];
            }
            if (strcmp(argv[i], "-lt") == 0) {
                low_threshold = atoi(argv[i + 1]);
            }
            if (strcmp(argv[i], "-ht") == 0) {
                high_threshold = atoi(argv[i + 1]);
            }
            if (strcmp(argv[i], "-TC") == 0) {
                c_threshold = atoi(argv[i + 1]);
            }
            if (strcmp(argv[i], "-minR") == 0) {
                minR = atoi(argv[i + 1]);
            }
            if (strcmp(argv[i], "-maxR") == 0) {
                maxR = atoi(argv[i + 1]);
            }
            /*if (strcmp(argv[i], "-fl") == 0) {
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
            if (strcmp(argv[i], "-fv") == 0) {
                vout = argv[i + 1];
            }
            if (strcmp(argv[i], "-fcc") == 0) {
                combout = argv[i + 1];
            }
            if (strcmp(argv[i], "-TCircle") == 0) {
                percentage = stod(argv[i + 1]) / 10;
            }
            if (strcmp(argv[i], "-fCi") == 0) {
                circlesOut = argv[i + 1];
            }
            if (strcmp(argv[i], "-fCo") == 0) {
                colorCircles = argv[i + 1];
            }*/
            if (strcmp(argv[i], "-fR") == 0) {
                total = argv[i + 1];
            }
            if (strcmp(argv[i], "-sC") == 0) {
                specialCoins = stoi(argv[i + 1]);
            }
            if (strcmp(argv[i], "-minDist") == 0) {
                minDist = stoi(argv[i + 1]);
            }
        }
        //grayscale
        Mat gray;
        gray = imread(img, IMREAD_GRAYSCALE);
        imwrite("./imageg.jpg", gray);
        cout << "Gray done" << endl;
        //Canny edge
        Mat edges;
        Canny(gray, edges, low_threshold, high_threshold);
        imwrite("./imagef.jpg", edges);
        cout << "Canny done" << endl;
        //find circles
        GaussianBlur(gray, gray, Size(9, 9), 2, 2);
        Mat circleImage = imread(img);
        Mat coinImage = imread(img);
        vector<Vec3f> coins;
        HoughCircles(gray, coins, HOUGH_GRADIENT, 1, minDist, high_threshold, c_threshold, minR, maxR);
        int qr = 115;
        int dr = 75;
        int pr = 90;
        int hd = 150;
        int nr = 100;
        for (int i = 0; i < coins.size(); i++) {
            Point center(cvRound(coins[i][0]), cvRound(coins[i][1]));
            Vec3b color = coinImage.at<Vec3b>(center);
            int b = color[0];
            int g = color[1];
            int r = color[2];
            int radius = cvRound(coins[i][2]);
            circle(circleImage, center, 4, Scalar(0, 0, 255), -1, 8, 0);
            circle(circleImage, center, radius, Scalar(0, 0, 255), 3, 8, 0);
            if (radius > pr - 11 && radius < pr + 5 && (r > b && r > g)) {
                penny++;
                circle(coinImage, center, radius, Scalar(255, 0, 0), 3, 8, 0);
            }
            else if (radius > dr-5 && radius < dr+11) {
                dimes++;
                circle(coinImage, center, radius, Scalar(255, 0, 0), 3, 8, 0);
            }
            else if (radius > nr - 10 && radius < nr + 3) {
                nickels++;
                circle(coinImage, center, radius, Scalar(0, 255, 255), 3, 8, 0);
            }
            else if (radius > qr - 15 && radius < qr + 10) {
                quarters++;
                circle(coinImage, center, radius, Scalar(250, 32, 160), 3, 8, 0);
            }
            //if (specialCoins == 0) {
            //    if (radius >= large) {
            //        continue;
            //    }
            //}
            //circle(circleImage, center, 4, Scalar(0, 0, 255), -1, 8, 0);
            //circle(circleImage, center, radius, Scalar(0, 0, 255), 3, 8, 0);
            //if (radius < pennySize-5) {
            //    dimes++;
            //    circle(coinImage, center, radius, Scalar(255, 0, 0), 3, 8, 0);
            //}
            //else if (radius < nickelSize-5) {
            //    penny++;
            //    circle(coinImage, center, radius, Scalar(0, 0, 255), 3, 8, 0);
            //}
            //else if (radius < quarterSize-5) {
            //    nickels++;
            //    circle(coinImage, center, radius, Scalar(0, 255, 255), 3, 8, 0);
            //}
            //else if (radius < dollarSize + 5) {
            //    quarters++;
            //    circle(coinImage, center, radius, Scalar(250, 32, 160), 3, 8, 0);
            //}
            //else {
            //    dollars++;
            //    circle(coinImage, center, radius, Scalar(255, 0, 255), 3, 8, 0);
            //}

        }
        ofstream out;
        out.open(total);
        imwrite("./imageCircles.jpg", circleImage);
        imwrite("./imageCoins.jpg", coinImage);
        cout << "Circles done" << endl;
        waitKey(0);
        out << penny << " pennies" << endl;
        out << nickels << " nickels" << endl;
        out << dimes << " dimes" << endl;
        out << quarters << " quarters" << endl;
        out << half_dollars << " half-dollar coins" << endl;
        out << dollars << " dollar coins" << endl;
        out << "Total Sum: $" << (0.01 * penny + 0.05 * nickels + 0.1 * dimes + 0.25 * quarters + 0.5 * half_dollars + dollars) << endl;
        cout << penny << " pennies" << endl;
        cout << nickels << " nickels" << endl;
        cout << dimes << " dimes" << endl;
        cout << quarters << " quarters" << endl;
        cout << half_dollars << " half-dollar coins" << endl;
        cout << dollars << " dollar coins" << endl;
        cout << "Total Sum: $" << (0.01 * penny + 0.05 * nickels + 0.1 * dimes + 0.25 * quarters + 0.5 * half_dollars + dollars) << endl;
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

