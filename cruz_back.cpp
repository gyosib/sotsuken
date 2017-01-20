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

void img_to_bw(string,string);
string tostr(int);

int main(){
	img_to_bw("out/two/","out/two/txt/");	
	return 0;
}

void img_to_bw(string path_input,string path_output){
	int i = 0;
	struct stat st;
	
	//image propaty
	Mat img = imread(path_input+"0.png",CV_LOAD_IMAGE_GRAYSCALE);
	int height = img.size().height;
	int width = img.size().width;

	while(1){
		string path = path_input+tostr(i)+".png";
		if(stat(path.c_str(),&st) != 0){
			//no File
			break;
		}
		ofstream ofs(path_output+tostr(i)+".txt");
		Mat img = imread(path,CV_LOAD_IMAGE_GRAYSCALE);
		int height = img.size().height;
		int width = img.size().width;
		Mat temp = imread("cruz.png",IMREAD_GRAYSCALE); //later
		
		Mat result;
		matchTemplate(img,temp,result,TM_CCORR_NORMED);
		vector<Point> detected_point;
		fload threshold = 0.96f;
		for(int y = 0;y<height;y++){
			for(int x = 0;x<width;x++){
				if(result.at<float>(x,y) > threshold)
					detected_point.push_back(Point(x,y));
			}
		}

		for(auto it = detected_point.begin(); it !=detected_point.end(); ++it){
			rectangle(img,*it,Point(it->x+temp.cols,it->y+temp.rows),Scalar(0,0,255),2,8,0);
		}
		namedWindow("Matching");
		imshow("Matching",img);
		waitKey(0);
	}
	cout<<i<<endl;
	i++;
	destroyAllWindows();
}

string tostr(int num){
	stringstream ss ;
	ss << num;
	return ss.str();
}

