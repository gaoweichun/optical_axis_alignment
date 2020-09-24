#ifndef __CALMTF_H__
#define __CALMTF_H__


#include "opencv2/highgui/highgui.hpp"


using namespace cv;
double *  calRight(Mat src, Point *centers,int xdistance, int ydistance, int width,int high);
double * calLeft(Mat src, Point *centers, int xdistance, int ydistance,int width, int high);

#endif // !__CALMTF_H__