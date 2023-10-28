//Brian Xu, P5
#include<vector>
#include<string>
#include<math.h>
#include<fstream>
#include<string.h>
#include<iostream>
using namespace std;

vector<vector<vector<int>>> PPMtoMatrix(string fname){
    vector<vector<vector<int>>> img;
    fstream file;
    file.open(fname.c_str());
    string item;
    vector<string> raw;
    while(file >> item){
        raw.push_back(item);
    }
    int width = stoi(raw[1]);
    int height = stoi(raw[2]);
    for(int i = 0; i < height; i++){
        vector<vector<int>> row;
        for(int j = 0; j < width; j++){
            vector<int> pxl;
            pxl.push_back(stoi(raw[4+3*width*i+3*j]));
            pxl.push_back(stoi(raw[5+3*width*i+3*j]));
            pxl.push_back(stoi(raw[6+3*width*i+3*j]));
            row.push_back(pxl);
        }
        img.push_back(row);
    }
    return img;
}

vector<vector<int>> grayscale(vector<vector<vector<int>>> &rgbimg){
    vector<vector<int>> gsimg;
    for(int i = 0; i < rgbimg.size(); i++){
        vector<int> row;
        for(int j = 0; j < rgbimg[i].size(); j++){
            row.push_back((rgbimg[i][j][0] + rgbimg[i][j][1] + rgbimg[i][j][2]) / 3);
        }
        gsimg.push_back(row);
    }
    return gsimg;
}

vector<vector<int>> sobel(vector<vector<int>> &gsimg){
    vector<vector<int>> sobelimg;
    vector<int> top;
    for(int j = 0; j < gsimg[0].size(); j++){ top.push_back(0); }
    sobelimg.push_back(top);
    for(int i = 1; i < gsimg.size()-1; i++){
        vector<int> row;
        row.push_back(0);
        for(int j = 1; j < gsimg[i].size()-1; j++){
            int dx = -gsimg[i-1][j-1]-2*gsimg[i][j-1]-gsimg[i+1][j-1]+gsimg[i-1][j+1]+2*gsimg[i][j+1]+gsimg[i+1][j+1];
            int dy = -gsimg[i-1][j-1]-2*gsimg[i-1][j]-gsimg[i-1][j+1]+gsimg[i+1][j-1]+2*gsimg[i+1][j]+gsimg[i+1][j+1];
            row.push_back(sqrt(dx*dx + dy*dy));
        }
        row.push_back(0);
        sobelimg.push_back(row);
    }
    vector<int> bottom;
    for(int j = 0; j < gsimg[0].size(); j++){ bottom.push_back(0); }
    sobelimg.push_back(bottom);
    return sobelimg;
}

vector<vector<int>> bin(vector<vector<int>> gsimg, int threshold){
    vector<vector<int>> binimg;
    for(int i = 0; i < gsimg.size(); i++){
        vector<int> row;
        for(int j = 0; j < gsimg[i].size(); j++){
            if(gsimg[i][j] >= threshold) { row.push_back(1); }
            else { row.push_back(0); }
        }
        binimg.push_back(row);
    }
    return binimg;
}

void hys(vector<vector<int>> &terimg, int i, int j){
    terimg[i][j] = 2;
    if(i > 1){
        if(terimg[i-1][j] == 1){ hys(terimg, i-1, j); }
    }
    if(i < terimg.size()-2){
        if(terimg[i+1][j] == 1){ hys(terimg, i+1, j); }
    }
    if(j > 1){
        if(terimg[i][j-1] == 1){ hys(terimg, i, j-1); }
    }
    if(j < terimg[0].size()-2){
        if(terimg[i][j+1] == 1){ hys(terimg, i, j+1); }
    }
    if(i > 1 && j > 1){
        if(terimg[i-1][j-1] == 1){ hys(terimg, i-1, j-1); }
    }
    if(i > 1 && j < terimg[0].size()-2){
        if(terimg[i-1][j+1] == 1){ hys(terimg, i-1, j+1); }
    }
    if(i < terimg.size()-2 && j > 1){
        if(terimg[i+1][j-1] == 1){ hys(terimg, i+1, j-1); }
    }
    if(i < terimg.size()-2 && j < terimg[0].size()-2){
        if(terimg[i+1][j+1] == 1){ hys(terimg, i+1, j+1); }
    }
}

vector<vector<int>> bin2(vector<vector<int>> &gsimg, int weak, int strong){
    vector<vector<int>> binimg;
    for(int i = 0; i < gsimg.size(); i++){
        vector<int> row;
        for(int j = 0; j < gsimg[i].size(); j++){
            if(gsimg[i][j] >= strong) { row.push_back(2); }
            else if(gsimg[i][j] >= weak) { row.push_back(1); }
            else { row.push_back(0); }
        }
        binimg.push_back(row);
    }
    for(int i = 0; i < binimg.size(); i++){
        for(int j = 0; j < binimg[0].size(); j++){
            if(binimg[i][j] == 2){ hys(binimg, i, j); }
        }
    }
    for(int i = 0; i < binimg.size(); i++){
        for(int j = 0; j < binimg[0].size(); j++){
            if(binimg[i][j] == 1){ binimg[i][j] = 0; }
            if(binimg[i][j] == 2){ binimg[i][j] = 1; }
        }
    }
    return binimg;
}

vector<vector<int>> theta(vector<vector<int>> &gsimg){
    vector<vector<int>> thetaimg;
    vector<int> top;
    for(int j = 0; j < gsimg[0].size(); j++){ top.push_back(0); }
    thetaimg.push_back(top);
    for(int i = 1; i < gsimg.size()-1; i++){
        vector<int> row;
        row.push_back(0);
        for(int j = 1; j < gsimg[i].size()-1; j++){
            double dx = -gsimg[i-1][j-1]-2*gsimg[i][j-1]-gsimg[i+1][j-1]+gsimg[i-1][j+1]+2*gsimg[i][j+1]+gsimg[i+1][j+1];
            double dy = -gsimg[i-1][j-1]-2*gsimg[i-1][j]-gsimg[i-1][j+1]+gsimg[i+1][j-1]+2*gsimg[i+1][j]+gsimg[i+1][j+1];
            row.push_back((int)(round(atan2(dy, dx)*-4/3.14159265358979323846)*-45));
        }
        row.push_back(0);
        thetaimg.push_back(row);
    }
    vector<int> bottom;
    for(int j = 0; j < gsimg[0].size(); j++){ bottom.push_back(0); }
    thetaimg.push_back(bottom);
    return thetaimg;
}

vector<vector<int>> maxsup(vector<vector<int>> &thetaimg, vector<vector<int>> &sobelimg){
    vector<vector<int>> maximg;
    vector<int> top;
    for(int j = 0; j < sobelimg[0].size(); j++){ top.push_back(0); }
    maximg.push_back(top);
    for(int i = 1; i < sobelimg.size()-1; i++){
        vector<int> row;
        row.push_back(0);
        for(int j = 1; j < sobelimg[i].size()-1; j++){
            if(thetaimg[i][j] < 0){ thetaimg[i][j] += 180; }
            if(thetaimg[i][j] == 45){
                if(sobelimg[i][j] >= max(sobelimg[i-1][j+1], sobelimg[i+1][j-1])){ row.push_back(1); }
                else{ row.push_back(0); }
            }else if(thetaimg[i][j] == 90){
                if(sobelimg[i][j] >= max(sobelimg[i-1][j], sobelimg[i+1][j])){ row.push_back(1); }
                else{ row.push_back(0); }
            }else if(thetaimg[i][j] == 135){
                if(sobelimg[i][j] >= max(sobelimg[i-1][j-1], sobelimg[i+1][j+1])){ row.push_back(1); }
                else{ row.push_back(0); }
            }else{
                if(sobelimg[i][j] >= max(sobelimg[i][j-1], sobelimg[i][j+1])){ row.push_back(1); }
                else{ row.push_back(0); }
            }
        }
        row.push_back(0);
        maximg.push_back(row);
    }
    vector<int> bottom;
    for(int j = 0; j < sobelimg[0].size(); j++){ bottom.push_back(0); }
    maximg.push_back(bottom);
    return maximg;
}

vector<vector<int>> combine(vector<vector<int>> &maximg, vector<vector<int>> &binimg){
    vector<vector<int>> cimg;
    for(int i = 0; i < binimg.size(); i++){
        vector<int> row;
        for(int j = 0; j < binimg[i].size(); j++){
            if(maximg[i][j] > 0 and binimg[i][j] > 0) { row.push_back(1); }
            else { row.push_back(0); }
        }
        cimg.push_back(row);
    }
    return cimg;
}

void drawPoint(int x, int y, vector<vector<int>> &voteimg){
    if(y >= 0 && y < voteimg.size() && x >= 0 && x < voteimg[0].size()){
        voteimg[y][x] += 1;
    }
}

void drawSegmentHorizontal(int x1, int y1, int x2, int y2, vector<vector<int>> &voteimg)
//Draws segment if horizontal
{
    if(y1 < y2)
    {
        for(int j = y1; j < y2; j++)
        {
            drawPoint(x1, j, voteimg);
        }
    }else{
        for(int j = y2; j < y1; j++)
        {
            drawPoint(x1, j, voteimg);
        }
    }
}
void drawSegmentVertical(int x1, int y1, int x2, int y2, vector<vector<int>> &voteimg)
//Draws segment if vertical
{
    if(x1 < x2)
    {
        for(int i = x1; i < x2; i++)
        {
            drawPoint(i, y1, voteimg);
        }
    }else{
        for(int i = x2; i < x1; i++)
        {
            drawPoint(i, y1, voteimg);
        }
    }
}
void drawSegmentEN(int x1, int y1, int x2, int y2, vector<vector<int>> &voteimg)
//Draws segment if x is leading axis and in quadrant 1
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int j = y1;
    int e = dy - dx;
    for(int i = x1; i < x2; i++)
    {
        drawPoint(i, j, voteimg);
        if(e >= 0)
        {
            j += 1;
            e -= dx;
        }
        e += dy;
    }
}
void drawSegmentNE(int x1, int y1, int x2, int y2, vector<vector<int>> &voteimg)
//Draws segment if y is leading axis and in quadrant 1
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int i = x1;
    int e = dx - dy;
    for(int j = y1; j < y2; j++)
    {
        drawPoint(i, j, voteimg);
        if(e >= 0)
        {
            i += 1;
            e -= dy;
        }
        e += dx;
    }
}
void drawSegmentNW(int x1, int y1, int x2, int y2, vector<vector<int>> &voteimg)
//Draws segment if y is leading axis and in quadrant 2
{
    int dx = x2 - x1;
    int dy = y1 - y2;
    int i = x2;
    int e = dx - dy;
    for(int j = y2; j > y1; j--)
    {
        drawPoint(i, j, voteimg);
        if(e <= 0)
        {
            i += 1;
            e -= dy;
        }
        e += dx;
    }
}
void drawSegmentWN(int x1, int y1, int x2, int y2, vector<vector<int>> &voteimg)
//Draws segment if x is leading axis and in quadrant 2
{
    int dx = x2 - x1;
    int dy = y1 - y2;
    int j = y2;
    int e = dy - dx;
    for(int i = x2; i < x1; i++)
    {
        drawPoint(i, j, voteimg);
        if(e <= 0)
        {
            j -= 1;
            e -= dx;
        }
        e += dy;
    }
}
void drawSegmentWS(int x1, int y1, int x2, int y2, vector<vector<int>> &voteimg)
//Draws segment if x is leading axis and in quadrant 3
{
    int dx = x1 - x2;
    int dy = y1 - y2;
    int j = y2;
    int e = dy - dx;
    for(int i = x2; i < x1; i++)
    {
        drawPoint(i, j, voteimg);
        if(e >= 0)
        {
            j += 1;
            e -= dx;
        }
        e += dy;
    }
}
void drawSegmentSW(int x1, int y1, int x2, int y2, vector<vector<int>> &voteimg)
//Draws segment if y is leading axis and in quadrant 3
{
    int dx = x1 - x2;
    int dy = y1 - y2;
    int i = x2;
    int e = dx - dy;
    for(int j = y2; j < y1; j++)
    {
        drawPoint(i, j, voteimg);
        if(e >= 0)
        {
            i += 1;
            e -= dy;
        }
        e += dx;
    }
}
void drawSegmentSE(int x1, int y1, int x2, int y2, vector<vector<int>> &voteimg)
//Draws segment if y is leading axis and in quadrant 4
{
    int dx = x1 - x2;
    int dy = y2 - y1;
    int i = x1;
    int e = dx - dy;
    for(int j = y1; j > y2; j--)
    {
        drawPoint(i, j, voteimg);
        if(e <= 0)
        {
            i += 1;
            e -= dy;
        }
        e += dx;
    }
}
void drawSegmentES(int x1, int y1, int x2, int y2, vector<vector<int>> &voteimg)
//Draws segment if x is leading axis and in quadrant 4
{
    int dx = x1 - x2;
    int dy = y2 - y1;
    int j = y1;
    int e = dy - dx;
    for(int i = x1; i < x2; i++)
    {
        drawPoint(i, j, voteimg);
        if(e <= 0)
        {
            j -= 1;
            e -= dx;
        }
        e += dy;
    }
}

void drawLine(int x1, int y1, int x2, int y2, vector<vector<int>> &voteimg)
//Draws line segment between two points
{
    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);
    if(x1 == x2)
    {
        drawSegmentHorizontal(x1, y1, x2, y2, voteimg);
    }else if(y1 == y2){
        drawSegmentVertical(x1, y1, x2, y2, voteimg);
    }else if(x2 > x1 && y2 > y1 && dx >= dy){
        drawSegmentEN(x1, y1, x2, y2, voteimg);
    }else if(x2 > x1 && y2 > y1 && dy >= dx){
        drawSegmentNE(x1, y1, x2, y2, voteimg);
    }else if(x1 > x2 && y2 > y1 && dy >= dx){
        drawSegmentNW(x1, y1, x2, y2, voteimg);
    }else if(x1 > x2 && y2 > y1 && dx >= dy){
        drawSegmentWN(x1, y1, x2, y2, voteimg);
    }else if(x1 > x2 && y1 > y2 && dx >= dy){
        drawSegmentWS(x1, y1, x2, y2, voteimg);
    }else if(x1 > x2 && y1 > y2 && dy >= dx){
        drawSegmentSW(x1, y1, x2, y2, voteimg);
    }else if(x2 > x1 && y1 > y2 && dy >= dx){
        drawSegmentSE(x1, y1, x2, y2, voteimg);
    }else if(x2 > x1 && y1 > y2 && dx >= dy){
        drawSegmentES(x1, y1, x2, y2, voteimg);
    }
}

vector<vector<int>> vote(vector<vector<int>> &binimg, vector<vector<int>> &gsimg, int rmax){
    vector<vector<int>> voteimg;
    for(int i = 0; i < gsimg.size(); i++){
        vector<int> top;
        for(int j = 0; j < gsimg[0].size(); j++){ top.push_back(0); }
        voteimg.push_back(top);
    }
    for(int i = 1; i < gsimg.size()-1; i++){
        for(int j = 1; j < gsimg[0].size()-1; j++){
            if(binimg[i][j] > 0){
                double dx = -gsimg[i-1][j-1]-2*gsimg[i][j-1]-gsimg[i+1][j-1]+gsimg[i-1][j+1]+2*gsimg[i][j+1]+gsimg[i+1][j+1];
                double dy = -gsimg[i-1][j-1]-2*gsimg[i-1][j]-gsimg[i-1][j+1]+gsimg[i+1][j-1]+2*gsimg[i+1][j]+gsimg[i+1][j+1];
                if(dx == 0){
                    drawLine(j, i - rmax, j, i + rmax, voteimg);
                }else if(dy == 0){
                    drawLine(j - rmax, i, j + rmax, i, voteimg);
                }else{
                    if(abs(dy) >= abs(dx)){
                        drawLine(j - (int)((dx/dy)*rmax), i - rmax, j + (int)((dx/dy)*rmax), i + rmax, voteimg);
                    }else{
                        drawLine(j - rmax, i - (int)((dy/dx)*rmax), j + rmax, i + (int)((dy/dx)*rmax), voteimg);
                    }
                }
            }
        }
    }
    return voteimg;
}

void fillPoint(int x, int y, vector<vector<vector<int>>> &img, int r, int g, int b){
    if(y >= 0 && y < img.size() && x >= 0 && x < img[0].size()){
        img[y][x] = {r, g, b};
    }
}

void fillcenters(vector<vector<vector<int>>> &img, vector<vector<int>> &binimg){
    for(int i = 0; i < img.size(); i++){
        for(int j = 0; j < img[i].size(); j++){
            if(binimg[i][j] > 0){
                for(int r = 1; r < 5; r++){
                    int xmax = int((r * 0.70710678) + 0.5);
                    int y1 = int(r + 0.5);
                    int y2 = y1 * y1;
                    int ty = (2 * y1) - 1;
                    int ynew = y2;
                    for(int x1 = 0; x1 <= xmax; x1++)
                    {
                        if((y2 - ynew) >= ty)
                        {
                            y2 -= ty;
                            y1 -= 1;
                            ty -=2;
                        }
                        fillPoint(x1 + j, y1 + i, img, 255, 0 ,0);
                        fillPoint(x1 + j, -y1 + i, img, 255, 0 ,0);
                        fillPoint(-x1 + j, y1 + i, img, 255, 0 ,0);
                        fillPoint(-x1 + j, -y1 + i, img, 255, 0 ,0);
                        fillPoint(y1 + j, x1 + i, img, 255, 0 ,0);
                        fillPoint(y1 + j, -x1 + i, img, 255, 0 ,0);
                        fillPoint(-y1 + j, x1 + i, img, 255, 0 ,0);
                        fillPoint(-y1 + j, -x1 + i, img, 255, 0 ,0);
                        ynew -= (2 * x1) - 3;
                    }
                }
            }
        }
    }
}

void drawradii(vector<vector<vector<int>>> &img, vector<vector<int>> &radimg, int small, int medium, int large, double pennyred){
    int pennies = 0, nickels = 0, dimes = 0, quarters = 0, dollars = 0;
    for(int i = 0; i < img.size(); i++){
        for(int j = 0; j < img[i].size(); j++){
            if(radimg[i][j] > 0){
                int r = 0, g = 0, b = 0;
                if(radimg[i][j] < medium){
                    double redness = 0, nonredness = 0;
                    for(int i2 = max(i-50, 0); i2 < min(i+51, (int)radimg.size()); i2++){
                        for(int j2 = max(j-50, 0); j2 < min(j+51, (int)radimg[0].size()); j2++){
                            redness += img[i2][j2][0];
                            nonredness += img[i2][j2][1] + img[i2][j2][2];
                        }
                    }
                    if(redness/nonredness > pennyred){
                        r = 255;
                        pennies++;
                    }else{
                        if(radimg[i][j] < small){
                            b = 255;
                            dimes++;
                        }else{
                            r = 255, b = 255;
                            nickels++;
                        }
                        
                    }
                    
                }else if(radimg[i][j] < large){
                    g = 255;
                    quarters++;
                }else{
                    r = 255, g = 255;
                    dollars++;
                }
                for(int a = radimg[i][j]-1; a <= radimg[i][j]+1; a++){
                    int xmax = int((a * 0.70710678) + 0.5);
                    int y1 = int(a + 0.5);
                    int y2 = y1 * y1;
                    int ty = (2 * y1) - 1;
                    int ynew = y2;
                    for(int x1 = 0; x1 <= xmax; x1++)
                    {
                        if((y2 - ynew) >= ty)
                        {
                            y2 -= ty;
                            y1 -= 1;
                            ty -=2;
                        }
                        fillPoint(x1 + j, y1 + i, img, r, g, b);
                        fillPoint(x1 + j, -y1 + i, img, r, g, b);
                        fillPoint(-x1 + j, y1 + i, img, r, g, b);
                        fillPoint(-x1 + j, -y1 + i, img, r, g, b);
                        fillPoint(y1 + j, x1 + i, img, r, g, b);
                        fillPoint(y1 + j, -x1 + i, img, r, g, b);
                        fillPoint(-y1 + j, x1 + i, img, r, g, b);
                        fillPoint(-y1 + j, -x1 + i, img, r, g, b);
                        ynew -= (2 * x1) - 3;
                    }
                }
            }
        }
    }
    ofstream out("results.txt");
    out<<pennies<<" pennies, "<<nickels<<" nickels, "<<dimes<<" dimes, "<<quarters<<" quarters, "<<dollars<<" dollar coins"<<endl<<"Total Sum: $"<<(0.01 * pennies + 0.05 * nickels + 0.1 * dimes + 0.25 * quarters + dollars)<<endl;
    cout<<pennies<<" pennies, "<<nickels<<" nickels, "<<dimes<<" dimes, "<<quarters<<" quarters, "<<dollars<<" dollar coins"<<endl<<"Total Sum: $"<<(0.01 * pennies + 0.05 * nickels + 0.1 * dimes + 0.25 * quarters + dollars)<<endl;
    out.close();
}

vector<vector<int>> radiusvote(vector<vector<int>> &voteimg, vector<vector<int>> &edgeimg, double rthreshold, int rmin, int rmax){
    vector<vector<int>> radimg;
    vector<vector<double>> tempimg;
    for(int i = 0; i < voteimg.size(); i++){
        vector<int> row;
        vector<double> temp;
        for(int j = 0; j < voteimg[0].size(); j++){
            if(voteimg[i][j] == 0){
                row.push_back(0);
                temp.push_back(0);
            }else{
                double maxt = 0;
                int maxr = 0;
                for(int r = rmin; r < 115; r++){
                    double cur = 0, all = 0;
                    int xmax = int((r * 0.70710678) + 0.5);
                    int y1 = int(r + 0.5);
                    int y2 = y1 * y1;
                    int ty = (2 * y1) - 1;
                    int ynew = y2;
                    for(int x1 = 0; x1 <= xmax; x1++)
                    {
                        if((y2 - ynew) >= ty)
                        {
                            y2 -= ty;
                            y1 -= 1;
                            ty -=2;
                        }
                        if(x1+i >= 0 && x1+i < edgeimg.size() && y1+j >= 0 && y1+j < edgeimg[0].size()){
                            all += 1;
                            if(edgeimg[x1+i][y1+j] > 0) cur += 1;
                        }if(x1+i >= 0 && x1+i < edgeimg.size() && -y1+j >= 0 && -y1+j < edgeimg[0].size()){
                            all += 1;
                            if(edgeimg[x1+i][-y1+j] > 0) cur += 1;
                        }if(-x1+i >= 0 && -x1+i < edgeimg.size() && y1+j >= 0 && y1+j < edgeimg[0].size()){
                            all += 1;
                            if(edgeimg[-x1+i][y1+j] > 0) cur += 1;
                        }if(-x1+i >= 0 && -x1+i < edgeimg.size() && -y1+j >= 0 && -y1+j < edgeimg[0].size()){
                            all += 1;
                            if(edgeimg[-x1+i][-y1+j] > 0) cur += 1;
                        }if(y1+i >= 0 && y1+i < edgeimg.size() && x1+j >= 0 && x1+j < edgeimg[0].size()){
                            all += 1;
                            if(edgeimg[y1+i][x1+j] > 0) cur += 1;
                        }if(y1+i >= 0 && y1+i < edgeimg.size() && -x1+j >= 0 && -x1+j < edgeimg[0].size()){
                            all += 1;
                            if(edgeimg[y1+i][-x1+j] > 0) cur += 1;
                        }if(-y1+i >= 0 && -y1+i < edgeimg.size() && x1+j >= 0 && x1+j < edgeimg[0].size()){
                            all += 1;
                            if(edgeimg[-y1+i][x1+j] > 0) cur += 1;
                        }if(-y1+i >= 0 && -y1+i < edgeimg.size() && -x1+j >= 0 && -x1+j < edgeimg[0].size()){
                            all += 1;
                            if(edgeimg[-y1+i][-x1+j] > 0) cur += 1;
                        }
                        ynew -= (2 * x1) - 3;
                    }
                    double ratio = cur/all;
                    if(ratio > maxt && ratio > rthreshold){
                        maxt = ratio;
                        maxr = r;
                    }
                }
                if(rmax > 165){
                    for(int r = 165; r < rmax; r++){
                        double cur = 0, all = 0;
                        int xmax = int((r * 0.70710678) + 0.5);
                        int y1 = int(r + 0.5);
                        int y2 = y1 * y1;
                        int ty = (2 * y1) - 1;
                        int ynew = y2;
                        for(int x1 = 0; x1 <= xmax; x1++)
                        {
                            if((y2 - ynew) >= ty)
                            {
                                y2 -= ty;
                                y1 -= 1;
                                ty -=2;
                            }
                            if(x1+i >= 0 && x1+i < edgeimg.size() && y1+j >= 0 && y1+j < edgeimg[0].size()){
                                all += 1;
                                if(edgeimg[x1+i][y1+j] > 0) cur += 1;
                            }if(x1+i >= 0 && x1+i < edgeimg.size() && -y1+j >= 0 && -y1+j < edgeimg[0].size()){
                                all += 1;
                                if(edgeimg[x1+i][-y1+j] > 0) cur += 1;
                            }if(-x1+i >= 0 && -x1+i < edgeimg.size() && y1+j >= 0 && y1+j < edgeimg[0].size()){
                                all += 1;
                                if(edgeimg[-x1+i][y1+j] > 0) cur += 1;
                            }if(-x1+i >= 0 && -x1+i < edgeimg.size() && -y1+j >= 0 && -y1+j < edgeimg[0].size()){
                                all += 1;
                                if(edgeimg[-x1+i][-y1+j] > 0) cur += 1;
                            }if(y1+i >= 0 && y1+i < edgeimg.size() && x1+j >= 0 && x1+j < edgeimg[0].size()){
                                all += 1;
                                if(edgeimg[y1+i][x1+j] > 0) cur += 1;
                            }if(y1+i >= 0 && y1+i < edgeimg.size() && -x1+j >= 0 && -x1+j < edgeimg[0].size()){
                                all += 1;
                                if(edgeimg[y1+i][-x1+j] > 0) cur += 1;
                            }if(-y1+i >= 0 && -y1+i < edgeimg.size() && x1+j >= 0 && x1+j < edgeimg[0].size()){
                                all += 1;
                                if(edgeimg[-y1+i][x1+j] > 0) cur += 1;
                            }if(-y1+i >= 0 && -y1+i < edgeimg.size() && -x1+j >= 0 && -x1+j < edgeimg[0].size()){
                                all += 1;
                                if(edgeimg[-y1+i][-x1+j] > 0) cur += 1;
                            }
                            ynew -= (2 * x1) - 3;
                        }
                        double ratio = cur/all;
                        if(ratio > maxt && ratio > rthreshold){
                            maxt = ratio;
                            maxr = r;
                        }
                    }
                }
                row.push_back(maxr);
                temp.push_back(maxt);
            }
        }
        radimg.push_back(row);
        tempimg.push_back(temp);
    }
    for(int i = 0; i < radimg.size(); i++){
        for(int j = 0; j < radimg[0].size(); j++){
            if(radimg[i][j] > 0){
                for(int i2 = max(i-rmin, 0); i2 < min(i+rmin, (int)radimg.size()); i2++){
                    for(int j2 = max(j-rmin, 0); j2 < min(j+rmin, (int)radimg[0].size()); j2++){
                        if(radimg[i2][j2] > 0 && (i2 != i || j2 != j) && abs(radimg[i][j]-radimg[i2][j2]) < 50){
                            if(tempimg[i][j] > tempimg[i2][j2]){
                                radimg[i2][j2] = 0;
                            }else{
                                radimg[i][j] = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    return radimg;
}

void toPPM(vector<vector<int>> gsimg, string filename, int maxval){
    ofstream out(filename);
    out<<"P3 "<<gsimg[0].size()<<" "<<gsimg.size()<<" "<<maxval<<" ";
    for(int i = 0; i < gsimg.size(); i++){
        for(int j = 0; j < gsimg[i].size(); j++){
            out<<gsimg[i][j]<<" "<<gsimg[i][j]<<" "<<gsimg[i][j]<<" ";
        }
    }
    out.close();
}

void tocolPPM(vector<vector<vector<int>>> img, string filename){
    ofstream out(filename);
    out<<"P3 "<<img[0].size()<<" "<<img.size()<<" "<<255<<" ";
    for(int i = 0; i < img.size(); i++){
        for(int j = 0; j < img[i].size(); j++){
            out<<img[i][j][0]<<" "<<img[i][j][1]<<" "<<img[i][j][2]<<" ";
        }
    }
    out.close();
}

void part1(int argc, char** argv){
    int low = 75;
    int high = 200;
    int tc = 75;
    string filename = "image.ppm";
    for(int i = 1; i < argc; i++){
        if(!strcmp(argv[i],"-L")) low = stoi(argv[i+1]);
        else if(!strcmp(argv[i],"-H")) high = stoi(argv[i+1]);
        else if(!strcmp(argv[i],"-F")) filename = argv[i+1];
        else if(!strcmp(argv[i],"-TC")) tc = stoi(argv[i+1]);
    }
    cout<<"Lower threshold: "<<low<<endl<<"Upper threshold: "<<high<<endl<<"Center threshold: "<<tc<<endl;
    auto img = PPMtoMatrix(filename);
    auto gsimg = grayscale(img);
    auto sobelimg = sobel(gsimg);
    auto thetaimg = theta(gsimg);
    auto maximg = maxsup(thetaimg, sobelimg);
    auto binimg = bin2(sobelimg, low, high);
    binimg = combine(maximg, binimg);
    toPPM(binimg, "imagef.ppm", 1);
    auto voteimg = vote(binimg, gsimg, 150);
    int max = 0;
    for(int i = 0; i < voteimg.size(); i++){
        for(int j = 0; j < voteimg[0].size(); j++){
            if(voteimg[i][j] > max) max = voteimg[i][j];
        }
    }
    toPPM(voteimg, "imagev.ppm", max);
    voteimg = bin(voteimg,  tc);
    fillcenters(img, voteimg);
    tocolPPM(img, "imageCC.ppm");
}

void part2(int argc, char** argv){
    int low = 75, high = 150;
    int tc = 16;
    double tr = 0.16;
    int rmin = 85, rmax = 115;
    int small = 93, medium = 105, large = 115;
    double pennyred = 0.55;
    string filename = "testCircle2.ppm";
    for(int i = 1; i < argc; i++){
        if(!strcmp(argv[i],"-L")) low = stoi(argv[i+1]);
        else if(!strcmp(argv[i],"-H")) high = stoi(argv[i+1]);
        else if(!strcmp(argv[i],"-F")) filename = argv[i+1];
        else if(!strcmp(argv[i],"-TC")) tc = stoi(argv[i+1]);
        else if(!strcmp(argv[i],"-TCircle")) tr = stod(argv[i+1]);
        else if(!strcmp(argv[i],"-RMin")) rmin = stoi(argv[i+1]);
        else if(!strcmp(argv[i],"-RMax")) rmax = stoi(argv[i+1]);
        else if(!strcmp(argv[i],"-SMALL")) small = stoi(argv[i+1]);
        else if(!strcmp(argv[i],"-MEDIUM")) medium = stoi(argv[i+1]);
        else if(!strcmp(argv[i],"-LARGE")) large = stoi(argv[i+1]);
        else if(!strcmp(argv[i],"-Red")) pennyred = stod(argv[i+1]);
    }
    cout<<"Lower threshold: "<<low<<endl<<"Upper threshold: "<<high<<endl<<"Center threshold: "<<tc<<endl<<"Radius threshold: "<<tr<<endl<<"Min radius: "<<rmin<<endl<<"Max radius: "<<rmax<<endl<<"Max Penny/Dime Radius: "<<small<<endl<<"Max Nickel Radius: "<<medium<<endl<<"Max Quarter Radius: "<<large<<endl<<"Penny redness: "<<pennyred<<endl;
    auto img = PPMtoMatrix(filename);
    auto gsimg = grayscale(img);
    auto sobelimg = sobel(gsimg);
    auto thetaimg = theta(gsimg);
    auto maximg = maxsup(thetaimg, sobelimg);
    auto binimg = bin2(sobelimg, low, high);
    binimg = combine(maximg, binimg);
    toPPM(binimg, "imagef.ppm", 1);
    auto voteimg = vote(binimg, gsimg, rmax);
    int vmax = 0;
    for(int i = 0; i < voteimg.size(); i++){
        for(int j = 0; j < voteimg[0].size(); j++){
            if(voteimg[i][j] > vmax) vmax = voteimg[i][j];
        }
    }
    toPPM(voteimg, "imagev.ppm", vmax);
    voteimg = bin(voteimg, tc);
    auto radimg = radiusvote(voteimg, binimg, tr, rmin, rmax);
    drawradii(img, radimg, small, medium, large, pennyred);
    tocolPPM(img, "coins.ppm");
}

int main(int argc, char** argv){
    //part1(argc, argv);
    part2(argc, argv);
}