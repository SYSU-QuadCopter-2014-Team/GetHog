#include "opencv2/opencv.hpp"
#include <cstdio>
#include <iostream>    
#include <fstream>    
#include <string>    
#include <vector>    
using namespace cv; 
using namespace std;    

vector<float> getHog(Mat test) {

	resize(test, test, Size(64, 64));

	//winsize, blocksize, blockstride, cellsize, nbins
	HOGDescriptor hog(cvSize(64,64),cvSize(16,16),cvSize(8,8),cvSize(8,8),9);
	vector<float>descriptors;//结果数组       
	hog.compute(test, descriptors,Size(1,1), Size(0,0)); //调用计算函数开始计算   
	
	// for (int i = 0 ; i< descriptors.size(); i++)
	// 	descriptors[i] = descriptors[i] * 1e5;
	
	cout << "Descriptor Dim " << descriptors.size() << endl;
	return descriptors;  
	
}


int main()
{
	
	// Write Results
	ofstream hogstxt;
	string resultsPath = "./hogs.txt";
	hogstxt.open(resultsPath.c_str());
	
	// Read Images
	ifstream positiveList;
	string plistFrames = "./positives.txt";
	positiveList.open(plistFrames.c_str());
	string pframeName;
	
	int pFrames = 0;
	while ( getline(positiveList, pframeName) ){
		
		Mat image = imread(pframeName, CV_LOAD_IMAGE_COLOR);
		
		resize(image, image, Size(64, 64));
		
		vector<float> descriptor = getHog(image);
		hogstxt << 1 << ' ';
		for (int i = 0; i < descriptor.size(); i++){
			hogstxt << descriptor[i] << ' ';
		}
		hogstxt << endl;
		
		pFrames++;
		cout << "Processed " << pFrames << " positive frames" << endl;
	}
	
	ifstream negativeList;
	string nlistFrames = "./negatives.txt";
	negativeList.open(nlistFrames.c_str());
	string nframeName;
	
	int nFrames = 0;
	while ( getline(negativeList, nframeName) ){

		Mat image = imread(nframeName, CV_LOAD_IMAGE_COLOR);

		resize(image, image, Size(64, 64));

		vector<float> descriptor = getHog(image);
		hogstxt << -1 << ' ';
		for (int i = 0; i < descriptor.size(); i++){
			hogstxt << descriptor[i] << ' ';
		}
		hogstxt << endl;

		nFrames++;
		cout << "Processed " << nFrames << " negative frames" << endl;

	}

	cout << "Total " << pFrames + nFrames << " images " << "processed" << endl;
	
	positiveList.close();
	// negativeList.close();
	hogstxt.close();
	
	return 0;

}
