#include <iostream>
#include <math.h>
#include "hough.h"
#include <opencv2\opencv.hpp>





using namespace cv;
using namespace std;



double reviseCoor(Point * centers) {
	/*
	计算chart是否摆正
	*/


	//通过计算1、2 与1、14角度
	float xDiff = abs(centers[1].x - centers[0].x);
	float yDiff = abs(centers[1].y - centers[0].y);

	double radian = atan(xDiff / yDiff);

	if ((centers[1].y - centers[0].y) < 0) {
		radian *= -1;
	}

	
	
	double angle = radian * 180 / 3.1415926535898;
	//cout << "y= " << deltay <<"  "<< "x=" << deltax << endl;

	//cout << "angle = " << angle << endl;
	

	//验证
	/*float xxDiff = abs(centers[0].x - centers[14].x);
	float yyDiff = abs(centers[0].y - centers[14].y);
	double xyradian = atan(xxDiff / yyDiff);
	if ((centers[1].y - centers[0].y) < 0) {
		radian *= -1;
	}
	double aangle = radian * 180 / 3.1415926535898;*/
	//cout << "y= " << deltay <<"  "<< "x=" << deltax << endl;
	//cout << "aangle = " << aangle << endl;

	return angle;
}