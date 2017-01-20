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
		for(int h=0;h<height;h++){
			string oneline = "";
			Vec3b *pixs = img.ptr<Vec3b>(h);
			for(int w=0;w<width;w++){
				int pix = static_cast<int>(img.at<unsigned char>(h,w)); 
				if(pix == 255){
					pix = 1;
				}
				oneline += tostr(pix);
				if(w < width){
					oneline += ",";
				}
			}
			ofs<<oneline<<endl;
		}
		cout<<i<<endl;
		i++;
	}
	destroyAllWindows();
}

string tostr(int num){
	stringstream ss ;
	ss << num;
	return ss.str();
}

