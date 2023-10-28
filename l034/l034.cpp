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
#include <vector>
#include <math.h>
#include <ctime>
#include <algorithm>
#include <unordered_map>
//#include <valarray>

#define XSIZE  800
#define YSIZE  800

using namespace std;

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
    double getX() const { return xcoor; }
    double getY() const { return ycoor; }
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

class gridPoint {
private:
    unsigned long long xcoor, ycoor;
public:
    gridPoint() {
        xcoor = 0;
        ycoor = 0;
    }
    gridPoint(unsigned long long x, unsigned long long y) {
        xcoor = x;
        ycoor = y;
    }
    //unsigned long getX() const {
    //    return xcoor;
    //}
    //unsigned long getY() const {
    //    return ycoor;
    //}
    unsigned long long getX() const{
        return xcoor;
    }
    unsigned long long getY() const {
        return ycoor;
    }
    bool operator == (const gridPoint& str) const {
        return xcoor == str.xcoor && ycoor == str.ycoor;
    }
};

class HashFunction {
public:
    size_t operator()(const gridPoint& str) const {
        //return hash<long>()(str.getX()) + hash<long>()(str.getY());
        return hash<unsigned long long>()(str.getX()) + hash<unsigned long long>()(str.getY());
    }
};

class pairPoints {
private:
    double distance;
    doublePoint a;
    doublePoint b;
public:
    pairPoints() {
        distance = 0;
    }
    pairPoints(double num, doublePoint first, doublePoint sec) {
        distance = num;
        a = first;
        b = sec;
    }
    double getDist() {
        return distance;
    }
    doublePoint getPointA() {
        return a;
    }
    doublePoint getPointB() {
        return b;
    }
    pairPoints findMin(pairPoints comp1, pairPoints comp2) {
        if (comp1.getDist() < comp2.getDist()) {
            return comp1;
        }
        else {
            return comp2;
        }
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
            double x;
            cout << "What size? ";
            cin >> x;
            std::ofstream file;
        file.open("points.txt");
        for (int i = 0; i < x; i++) {//change value to make larger
            doublePoint point = generatePoints();
            file << std::fixed << std::setprecision(23) << point.getX() << " " << point.getY() << std::endl;
        }
        file.close();
        std::cout << "Points generated" << std::endl;
        }
        makeTxTFile();
    }
    static std::vector<doublePoint> vreadFromTxt() {
        std::ifstream points;
        points.open("points.txt");
        std::string delim = " ";
        std::string line;
        std::vector<doublePoint> data;
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
        double x = b.getX() - a.getX();
        double y = b.getY() - a.getY();
        return sqrt((x * x) + (y * y));
    }
    static void makeTxTFile() {//doublePoint p1, doublePoint p2, double time, double distance) {
        std::ofstream file;
        file.open("results.txt");
        //file << "(" << std::fixed << std::setprecision(23) << p1.getX() << "," << p1.getY() << ")" << std::endl;
        //file << "(" << std::fixed << std::setprecision(23) << p2.getX() << "," << p2.getY() << ")" << std::endl;
        //file << "Distance: " << distance << endl;
        //file << "Time: " << time << endl;
        file.close();
    }
    static void writeToTxt(doublePoint p1, doublePoint p2, double time, double distance, int num) {
        std::ofstream file;
        file.open("results.txt", ios_base::app);
        //file << "Recursive" << endl;
        if (num == 1) {
            file << "Part 1" << endl;
        }
        else if (num == 2) {
            file << "Part 2" << endl;
        }
        else if (num == 3) {
            file << "Part 3" << endl;
        }
        else if (num == 4) {
            file << "Part 4" << endl;
        }
        file << "(" << std::fixed << std::setprecision(23) << p1.getX() << "," << p1.getY() << ")" << std::endl;
        file << "(" << std::fixed << std::setprecision(23) << p2.getX() << "," << p2.getY() << ")" << std::endl;
        file << "Distance: " << distance << endl;
        file << "Time: " << time << endl;
        file << endl;
        file.close();
    }
    static pairPoints bruteForce(vector<doublePoint>& points, int left, int right) {
        doublePoint a;
        doublePoint b;
        double distance = 1;
        for (int i = left; i < right; i++) {
            doublePoint temp1 = points[i];
            for (int j = i + 1; j <= right; j++) {
                doublePoint temp2 = points[j];
                double trydistance = findDistance(temp1, temp2);
                if (trydistance < distance) {
                    distance = trydistance;
                    a = temp1;
                    b = temp2;
                }
            }
        }
        pairPoints p(distance, a, b);
        return p;
    }
    static bool compareX(doublePoint x, doublePoint y) {
        return (x.getX() < y.getX());
    }
    static bool compareY(doublePoint x, doublePoint y) {
        return (x.getY() < y.getY());
    }
    static pairPoints p3recur(vector<doublePoint>& points, int left, int right) {
        int mid = (left + right) / 2;
        int n = (right - left) + 1;
        if (n <= 3) {
            return bruteForce(points, left, right);
        }
        pairPoints p1 = p3recur(points, left, mid);
        pairPoints p2 = p3recur(points, mid, right);
        pairPoints min = p1.findMin(p1, p2);
        double distance = min.getDist();
        int leftindex = 0;
        int rightindex = points.size() - 1;
        //vector<doublePoint> pointst;
        //for(int l = mid-1; l >= left; l--){
        for (int l = mid; l >= left; l--) {
            if (points[mid].getX() - points[l].getX() < distance) {
                leftindex = l;
                //pointst.push_back(points[l]);
            }
            else {
                break;
            }
        }
        //for(int r = mid+1; r <= right; r++){
        for (int r = mid; r <= right; r++) {
            if (points[r].getX() - points[mid].getX() < distance) {
                rightindex = r;
                //pointst.push_back(points[r]);
            }
            else {
                break;
            }
        }
        auto start = points.begin() + leftindex;
        auto end = points.begin() + rightindex + 1;
        vector<doublePoint> pointst(start, end);
        //vector<doublePoint> pointst;
        //for (int i = leftindex; i < rightindex; i++) {
        //    pointst.push_back(points[i]);
        //}
        sort(pointst.begin(), pointst.end(), compareY);//sorts vector by y
        for (int i = 0; i < pointst.size(); i++) {
            for (int j = i + 1; j < i + 16 && j < pointst.size(); j++) {
                double d = findDistance(pointst[i], pointst[j]);
                if (d < distance && i != j) {
                    distance = d;
                    min = pairPoints(d, pointst[i], pointst[j]);
                }
            }
        }
        //for (int i = 0; i < pointst.size(); i++) {
        //    for (int j = 1; j <= 15; j++) {
        //        if (i + j < pointst.size()) {
        //            break;
        //        }
        //        else{
        //            double d = findDistance(pointst[i], pointst[i+j]);
        //            if (d < distance) {
        //                distance = d;
        //                min = pairPoints(d, pointst[i], pointst[i + j]);
        //            }
        //        }
        //    }
        //}
        return min;
    }

    static void part3() {
        std::vector<doublePoint> points = vreadFromTxt();
        clock_t start2, end2;
        start2 = clock();
        sort(points.begin(), points.end(), compareX);
        int left = 0;
        int right = points.size() - 1;
        int mid = (left + right) / 2;
        pairPoints point = p3recur(points, left, right);
        end2 = clock();
        double time = (double)(end2 - start2) / CLOCKS_PER_SEC;
        cout << endl;
        cout << "Part 3 Recursive" << endl;
        cout << std::fixed << std::setprecision(23);
        std::cout << "First Point: " << point.getPointA().getX() << "," << point.getPointA().getY() << std::endl;
        std::cout << "Second Point: " << point.getPointB().getX() << "," << point.getPointB().getY() << std::endl;
        std::cout << "Distance: " << point.getDist() << std::endl;
        std::cout << "Time: " << time << std::endl;
        writeToTxt(point.getPointA(), point.getPointB(), time, point.getDist(), 3);
    }
    //static void swap(vector<doublePoint> points, int a, int b) { //swaps points at indexes
    //    doublePoint temp = points[a];
    //    points[a] = points[b];
    //    points[b] = temp;
    //}
    static int generateShufflePoint(int left, vector<doublePoint> points) {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_int_distribution<int> uni(left, points.size()-1);
        return uni(eng);
    }

    static void shuffle(vector<doublePoint>& points) { //knuth shuffle algorithm
        for (int i = 0; i < points.size(); i++) {
            int coord = generateShufflePoint(i, points);
            swap(points[i], points[coord]);
        }

    }

    //static unordered_map<pair<unsigned long, unsigned long>, doublePoint, HashFunction> makeDictionary(vector<doublePoint> points, double distance) {
    //    unordered_map<pair<unsigned long,unsigned long>, doublePoint, HashFunction> d;
    //    long subsq = distance / 2;

    //    return d;
    //}
    static pairPoints doPart4(vector<doublePoint> p) {
        shuffle(p); //shuffle the vector
        doublePoint first = p[0]; //first point
        doublePoint sec = p[1]; //second point
        double delta = findDistance(first, sec); //initial distance of first 2 points
        unordered_map<gridPoint, doublePoint, HashFunction> temp; //= makeDictionary(p, delta);
        double sublength = delta / 2;
        for (int i = 0; i < p.size(); i++) {
            //determine subsquare of p[i]
            unsigned long long xcoord = (unsigned long long)floor(p[i].getX() / sublength); //determine xcoord of subsquare
            unsigned long long ycoord = (unsigned long long)floor(p[i].getY() / sublength); //determine ycoord of subsquare
            unsigned long long xmin = (xcoord <= 1) ? xmin = 0 : xmin = xcoord - 2; //determine xmin of box
            unsigned long long ymin = (ycoord <= 1) ? ymin = 0 : ymin = ycoord - 2;//determin ymin of box
            unsigned long long xmax = xcoord + 2; //determine xmax of box
            unsigned long long ymax = ycoord + 2; //determine ymax of box
            double d = delta;
            gridPoint test;
            for (unsigned long long j = xmin; j <= xmax; j++) { //iterate through subsquares in box
                double sqdist; //distance of p[i] to subsquare
                for (unsigned long long k = ymin; k <= ymax; k++) {
                    gridPoint stest(j,k);
                    if (temp.find(stest) != temp.end()) {//error potntially
                        sqdist = findDistance(p[i], temp[stest]); //distance between points
                        if (sqdist < d) {
                            d = sqdist;
                            test = stest;
                        }
                    }
                }
            }
            if (d < delta) {
                delta = d; //update delta
                first = p[i]; //store first point
                sec = temp[test]; //store second point
                sublength = delta / 2;
                temp.clear(); //delete dictionary
                for (int a = 0; a <= i; a++) {
                    unsigned long long newxcoord = (unsigned long long)floor(p[a].getX() / (delta / 2));//determine subsquare coordinate
                    unsigned long long newycoord = (unsigned long long)floor(p[a].getY() / (delta / 2));//determine subsquare coordinate
                    //unsigned long newycoord = p[a].getY() / sublength;
                    gridPoint gpoint(newxcoord, newycoord);
                    temp[gpoint] = p[a]; //insert subsquare into dictionary
                }
            }
            else {
                gridPoint gpoint(xcoord, ycoord);
                temp[gpoint] = p[i];
            }
        }
        pairPoints point(delta, first, sec);
        return point;
    }

    static void part4() {
        vector<doublePoint> p = vreadFromTxt();
        clock_t start2, end2;
        start2 = clock();
        pairPoints point = doPart4(p);
        end2 = clock();
        double time = (double)(end2 - start2) / CLOCKS_PER_SEC;
        cout << endl;
        cout << "Part 4 Random" << endl;
        cout << std::fixed << std::setprecision(23);
        std::cout << "First Point: " << point.getPointA().getX() << "," << point.getPointA().getY() << std::endl;
        std::cout << "Second Point: " << point.getPointB().getX() << "," << point.getPointB().getY() << std::endl;
        std::cout << "Distance: " << point.getDist() << std::endl;
        std::cout << "Time: " << time << std::endl;
        writeToTxt(point.getPointA(), point.getPointB(), time, point.getDist(), 4);
    }

};

int main()
{
    doParts::part0();
    doParts::part3();
    doParts::part4();
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
