//Satvik Matta
//December 2, 2022
#include <fstream>
#include <math.h>
#include <string>
#include <vector>
using namespace std;

ofstream intensitymatrix(ifstream &infile){
    ofstream outfile;
    outfile.open("imageg.ppm");
    string line;
    int width, height, maxval;
    infile >> line;
    infile >> width >> height >> maxval;
    outfile << line << endl;
    outfile << width << " " << height << endl;
    outfile << maxval << endl;
    //convert to grayscale
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            int r, g, b;
            infile >> r >> g >> b;
            int intensity = (r + g + b) / 3;
            outfile << intensity << " " << intensity << " " << intensity << " ";
        }
        outfile << endl;
    }
    outfile.close();
    return outfile;

}

//sobel filter on a grayscale image
void sobel(ifstream &infile){
    ofstream outfile;
    outfile.open("images.ppm");
    string line;
    int width, height, maxval;
    infile >> line;
    infile >> width >> height >> maxval;
    outfile << line << endl;
    outfile << width << " " << height << endl;
    outfile << maxval << endl;
    //put image into 2d vector
    vector<vector<int>> image;
    for (int i = 0; i < height; i++){
        vector<int> row;
        for (int j = 0; j < width; j++){
            int r, g, b;
            infile >> r >> g >> b;
            row.push_back(r);
        }
        image.push_back(row);
    }
    vector<vector<int>> sobel;
    for (int i = 0; i < height; i++){
        vector<int> row;
        for (int j = 0; j < width; j++){
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1){
                row.push_back(0);
            }
            else{
                int gx = -1*image[i-1][j-1] + -2*image[i][j-1] - image[i+1][j-1] + image[i-1][j+1] + 2*image[i][j+1] + image[i+1][j+1];
                int gy = -1*image[i-1][j-1] + -2*image[i-1][j] - image[i-1][j+1] + image[i+1][j-1] + 2*image[i+1][j] + image[i+1][j+1];
                int g = sqrt(gx*gx + gy*gy);
                row.push_back(g);
            }
        }
        sobel.push_back(row);
    }
    //make sobel into ppm
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            outfile << sobel[i][j] << " " << sobel[i][j] << " " << sobel[i][j] << " ";
        }
        outfile << endl;
    }
    outfile.close();
}

ofstream thres(ifstream &infile){
    ofstream outfile;
    outfile.open("imagem.ppm");
    string line;
    int width, height, maxval;
    infile >> line;
    infile >> width >> height >> maxval;
    maxval = 1;
    outfile << line << endl;
    outfile << width << " " << height << endl;
    outfile << maxval << endl;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            int r, g, b;
            infile >> r >> g >> b;
            if (r > 75){
                outfile << 1 << " " << 1 << " " << 1 << " ";
            }
            else{
                outfile << 0 << " " << 0 << " " << 0 << " ";
            }
        }
        outfile << endl;
    }
    outfile.close();
    return outfile;
}

void part1(){
    ifstream infile("image.ppm");
    intensitymatrix(infile);
    ifstream infile2("imagegsat.ppm");
    sobel(infile2);
    ifstream infile3("imagessat.ppm");
    thres(infile3);
}

int main(){
    part1();
    return 0;
}