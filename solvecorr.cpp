#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>

#define NUM 32751

using namespace std;

int main(int argc, char** argv){
	double nums[NUM] = {}; //datas
	double DFT_re[NUM] = {}; //datas
	double DFT_im[NUM] = {}; //datas
	//double corr[NUM-1][NUM-1] = {{}}; //corrlations
	double sum = 0;
	double ave;

	string read_filename_back = argv[1];
	string write_filename_back = argv[2];
	string fourier_filename_back = argv[3];
	string read_filename = "out/two/txt/and/" + read_filename_back;
	string write_filename = "out/two/txt/and/" + write_filename_back;
	string fourier_filename = "out/two/txt/and/" + fourier_filename_back;
	ifstream reading_file;
	ofstream writing_file;
	ofstream fourier_file;
	reading_file.open(read_filename,std::ios::in);
	writing_file.open(write_filename,std::ios::out);
	fourier_file.open(fourier_filename,std::ios::out);

	string reading_line_buffer;

	cout << "reading " << read_filename << "..." << endl;

	//Data input
	int i = 0;
	while(getline(reading_file, reading_line_buffer)){
		cout << reading_line_buffer << endl;
		nums[i] = stoi(reading_line_buffer);
		sum += nums[i]*nums[i];
		i++;
	}
	ave = sum/i;

	//Solve correlation
	writing_file << "# dt  corr[dt]" << endl;
	int j;
	for(int i2=0;i2<i;i2++){
		sum = 0;
		//writing_file << setfill('0') << setw(5) << i2 <<" ";
		for(j=0;j<=i-i2;j++){
			//corr[j-i-1][i] = nums[i]*nums[j]/ave/ave;
			sum += nums[j]*nums[j+i2]/ave;
		}
		writing_file << setprecision(5) << sum/j << endl;;
		/*writing_file << setprecision(5) << sum/j << " ";
		writing_file << "" <<endl;*/
	}

	//Fourier transform
	int k,n;
	fourier_file << "#k,f,x_re,x_im,X_re,X_im\n" << endl;
	
	for(k=0;k<i;k++){
		cout << k << endl;
		DFT_re[k] = 0.0;	
		DFT_im[k] = 0.0;	
		for(n=0;n<i;n++){
			DFT_re[k] += 
				nums[n] *
				cos(2 * M_PI * k * n / i) *
				(0.5-0.5*cos(2*M_PI*n/(i-1)));
			DFT_im[k] -= 
				nums[n] *
				sin(2 * M_PI * k * n / i) *
				(0.5-0.5*cos(2*M_PI*n/(i-1)));
		}
		fourier_file << (2*M_PI/i)*k << " " <<
			DFT_re[k] << " " <<
			DFT_im[k] << endl;
	}
}
