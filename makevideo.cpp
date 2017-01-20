#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <sys/stat.h>
#include <string>
#include <time.h>
#include "unistd.h"

//#define NUM 32752
#define NUM 3275
#define RAN_FPS 10 //Default Random fps
#define NOR_FPS 1000 //Default Normal fps

using namespace std;
using namespace cv;

int getrnd(int,int);
void on_trackbar1(int);
void on_trackbar2(int);
void on_record(int,void*);

int savetriger = 0;

int nor_fps = NOR_FPS; //Normal fps
int ran_fps = RAN_FPS; //Normal fps
int fps_rate = nor_fps/RAN_FPS; //How times ? (Nor/Ran)

int main(int args, char **argv){
	//Parameter
	double fps = 10;
	int height = 132;
	int width = 528;
	double recordtime = 0.0; //[frame]/[fps]
	
	//Video setting
	int codec = CV_FOURCC('M','J','P','G');
	VideoWriter vw("polarbear.avi",codec,nor_fps,Size(width,height*2),true);

	srand((unsigned int)time(NULL));
	Mat images[NUM] = {};
	Mat img,frame;
	char load_name[NUM];

	//Create the window
	namedWindow("KurumadaLAB",CV_WINDOW_AUTOSIZE);
	int n_infps = nor_fps;
	int r_infps = ran_fps;
	int rate_infps = fps_rate;
	cvCreateTrackbar("Normal Speed[fps]","KurumadaLAB",&n_infps,1000,on_trackbar1);
	cvCreateTrackbar("Random Speed[fps]","KurumadaLAB",&r_infps,1000,on_trackbar2);
	//cvCreateButton("Record",on_record,(void*)"test",CV_PUSH_BUTTON,0);

	Mat img1;
	Mat img2;
	int num = 0; //How many images?
	//VideoWriter wrt("polarbear.avi",CV_FOURCC('X','V','I','D'),fps,Size(300,400),true);
	
	//Get many images
	cout<<"GET IMAGES ..."<<endl;

	for(int i=0;i<NUM;i++){
		sprintf(load_name,"out/two/%d.png",i);
		images[i] = imread(load_name);
		if(!images[i].empty())
			num++;
		else
			break;
	}

	//Show two images (Normal & Random)
	cout<<"SHOW IMAGES !"<<endl;
	cout<<num<<endl;
	int ran_spf; //ex. Def_1000[fps] <--> Ran_10[fps]
	int r;
	int time = 0;
	for(int i=0;i<num;i++){
		ran_spf = 1000/nor_fps; //ex. Def_1000[fps] <--> Ran_10[fps]
		//img1 = images[i];
		if(time % fps_rate == 0){
			img1 = images[i];
			r = getrnd(0,num-1);
			time = 1;
		}else{
			time++;
		}
		img2 = images[r];

		if(!img1.empty() && !img2.empty()){

			Mat twoimg = Mat(img1.rows,img1.cols*2,img1.type());
			vconcat(img1,img2,twoimg);
			 
			imshow("KurumadaLAB",twoimg);
			
			//cout<<img.size()<<" "<<img.channels()<<endl;
			int key = waitKey(ran_spf);
			if(key == 113) break; //q
			if(key == 115){ //s
				vw.open("polarbear_"+to_string(nor_fps)+","+to_string(ran_fps)+"_.avi",codec,nor_fps,Size(width,height*2),true);
				if(!vw.isOpened())
					return -1;
				recordtime = 0;
				cout << "Start to Record" << endl;
				savetriger = 1;
			}
			if(savetriger == 1){
				recordtime += 1;
				vw << twoimg;
				cout << recordtime / nor_fps << endl;
				if(key == 27){ //esc
					cout << "Save video!" << endl; 
					savetriger = 0;
				}
			}
		}else{
			break;
		}
		
		if(i >= num-1){
			i = 0;
		}
	}

		vw.release();

	return 0;
}

int getrnd(int min, int max){
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void on_trackbar1(int val){
	if(val>0 && val>ran_fps){
		nor_fps = val;
		fps_rate = nor_fps/ran_fps;
	}
}
void on_trackbar2(int val){
	if(val>0 && val<nor_fps){
		ran_fps = val;
		fps_rate = nor_fps/ran_fps;
	}
}

void on_record(int state, void* userdata){
	savetriger = 1;
}
