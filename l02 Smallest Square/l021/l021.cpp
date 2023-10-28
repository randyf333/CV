// l02 Smallest Square.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
using namespace std;

class randomPoint {
private:
    double xcoor;
    double ycoor;
public:
    randomPoint() {
        xcoor = 0.0;
        ycoor = 0.0;
    }
    randomPoint(double x, double y) { //constructor
        xcoor = x;
        ycoor = y;
    }
    ~randomPoint() {

    }
    double getX() { return xcoor; }
    double getY() { return ycoor; }
    void setX(double value) { xcoor = value; }
    void setY(double value) { ycoor = value; }
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
    static double findArea(double x1, double y1, double x2, double y2, double x3, double y3) {
        return std::abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
    }
    static bool checkPoint(randomPoint p1, randomPoint p2, randomPoint p3, randomPoint p4) {
        double area = findArea(p1.getX(), p1.getY(), p2.getX(), p2.getY(), p3.getX(), p3.getY());
        double areap1 = findArea(p4.getX(), p4.getY(), p2.getX(), p2.getY(), p3.getX(), p3.getY());
        double areap2 = findArea(p1.getX(), p1.getY(), p4.getX(), p4.getY(), p3.getX(), p3.getY());
        double areap3 = findArea(p1.getX(), p1.getY(), p2.getX(), p2.getY(), p4.getX(), p4.getY());
        return std::abs(area - (areap1 + areap2 + areap3)) <= .0000001;
    }
    //cross product(a,b,c,d)
    //a*d-b*c
};

class part1 {
public:
    static void makeTxTFile(randomPoint p1, randomPoint p2, randomPoint p3, randomPoint p4) {
        std::ofstream file;
        file.open("points.txt");
        file << "(" << std::fixed << std::setprecision(17) << p1.getX() << "," << p1.getY() << ")" << " ," << std::endl;
        file << "(" << std::fixed << std::setprecision(17) << p2.getX() << "," << p2.getY() << ")" << " ," << std::endl;
        file << "(" << std::fixed << std::setprecision(17) << p3.getX() << "," << p3.getY() << ")" << " ," << std::endl;
        file << "(" << std::fixed << std::setprecision(17) << p4.getX() << "," << p4.getY() << ")" << std::endl;
        file.close();
    }
    static randomPoint makeLog(randomPoint p1, randomPoint p2, randomPoint p3){//,randomPoint p) { //delete last randomPoint p after tests
        std::ofstream file;
        file.open("log.txt");
        file << "(" << std::fixed << std::setprecision(17) << p1.getX() << "," << p1.getY() << ")" << ", ";
        file << "(" << std::fixed << std::setprecision(17) << p2.getX() << "," << p2.getY() << ")" << ", ";
        file << "(" << std::fixed << std::setprecision(17) << p3.getX() << "," << p3.getY() << ")" << endl;
        cout << "(" << std::fixed << std::setprecision(17) << p1.getX() << "," << p1.getY() << ")" << ", ";
        cout << "(" << std::fixed << std::setprecision(17) << p2.getX() << "," << p2.getY() << ")" << ", ";
        cout << "(" << std::fixed << std::setprecision(17) << p3.getX() << "," << p3.getY() << ")" << endl;
        randomPoint p4;
        bool check = true;
        while(check){
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
        randomPoint p1(makePoints::generateCoord(), makePoints::generateCoord());
        randomPoint p2(makePoints::generateCoord(), makePoints::generateCoord());
        randomPoint p3(makePoints::generateCoord(), makePoints::generateCoord());
        //randomPoint p1(0.86941074168708876, 0.15993302053892403);
        //randomPoint p2(0.47638208467888199, 0.52377581382253224);
        //randomPoint p3(0.45226436226113620, 0.90460559530182882);
        //randomPoint p4(0.30872328944542649, 0.30329380287552415);
        //p4 = makeLog(p1, p2, p3, p4);
        randomPoint p4 = part1::makeLog(p1, p2, p3);
        part1::makeTxTFile(p1, p2, p3, p4);
    }
};

int main()
{
    //create random variables
    part1::doPart1();
    //randomPoint p1(0.89186075345279259, 0.06936545462987417);
    //randomPoint p2(0.34943825580667676, 0.83988630306304768);
    //randomPoint p3(0.72268848141198438, 0.91922820670067773);
    //randomPoint p4(0.21686348733612901, 0.84329504347390427);
    //cout << "(" << std::fixed << std::setprecision(17) << p1.getX() << "," << p1.getY() << ")" << ", ";
    //cout << "(" << std::fixed << std::setprecision(17) << p2.getX() << "," << p2.getY() << ")" << ", ";
    //cout << "(" << std::fixed << std::setprecision(17) << p3.getX() << "," << p3.getY() << ")" << endl;
    //randomPoint p4;
    //bool check = true;
    //while (check) {
    //    //p4.setX(makePoints::generateCoord());
    //    //p4.setY(makePoints::generateCoord());
    //    cout << "Testing the point: " << "(" << std::fixed << std::setprecision(17) << p4.getX() << "," << p4.getY() << ")" << endl;
    //    bool check1 = makePoints::checkPoint(p1, p2, p3, p4);
    //    bool check2 = makePoints::checkPoint(p1, p2, p4, p3);
    //    bool check3 = makePoints::checkPoint(p1, p4, p3, p2);
    //    bool check4 = makePoints::checkPoint(p4, p2, p3, p1);
    //    if (check1 == check2 == check3 == check4) {
    //        check = false;
    //    }
    //}
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
