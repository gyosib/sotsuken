#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/features2d.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>
#include<sys/stat.h>
#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include<sstream>

using namespace std;
using namespace cv;

void getline(string,string);
string tostr(int);

int main(){
	string twopath = "out/two/";
	string linepath = "out/line/";
	string path = "";
	int i = 0;
	struct stat st;

	while(!stat((path = twopath+tostr(i)+".png").c_str(),&st)){
		//Get line & Save
		getline(path,linepath+tostr(i)+".png");
		i++;
	}
	return 0;
}

void getline(string path_input,string path_output){
	//Original image
	Mat src_img = imread(path_input,1);
	Mat dst_img, work_img;
	dst_img = src_img.clone();
	int width = dst_img.cols;
	int height = dst_img.rows;
	//All white image
	Mat white(Size(dst_img.cols,dst_img.rows),CV_8UC3,Scalar::all(255));
	Mat chain(Size(dst_img.cols*2,dst_img.rows),CV_8UC3);
	cvtColor(src_img, work_img, CV_BGR2GRAY);
	//Get edge	
	Canny(work_img, work_img ,80, 100, 3);

	vector<Vec4i> lines;
	//Get line
	HoughLinesP(work_img, lines, CV_HOUGH_PROBABILISTIC, CV_PI/180, 70, 6, 10);

	vector<Vec4i>::iterator it =lines.begin();
	for(;it != lines.end(); ++it){
		Vec4i l = *it;
		//Draw line in the black to all white image
		line(white, Point(l[0], l[1]), Point(l[2], l[3]),Scalar(0,0,0), 5, CV_AA);
	}
	
	//Save
	imwrite(path_output,white);
}

string tostr(int num){
	stringstream ss;
	ss << num;
	return ss.str();
}
