#ifndef __HOUGH_H__
#define __HOUGH_H__



#include "opencv2/highgui/highgui.hpp"





using namespace cv;



void swapPoint(Point *xp, Point *yp);

Point *  houghCir(Mat src, int count, double minDist, double param1,double param2,int minRadius, int maxRadius);


#endif // !__HOUGH_H__
