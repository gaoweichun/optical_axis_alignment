#include <iostream>
#include <math.h>
#include "hough.h"
#include <opencv2\opencv.hpp>
using namespace cv;
using namespace std;


// swap two point
void swapPoint(Point *xp, Point *yp)
{
	/* 交换两个点*/
	Point temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void swapRadius(int  *xp, int *yp)
{
	/* 交换两个点*/
	int  temp = *xp;
	*xp = *yp;
	*yp = temp;
}


Point *  houghCir(Mat src, int count, double minDist, double param1, double param2, int minRadius, int maxRadius)

{
	/*霍夫圆检测圆心
	input:
	src: 图像矩阵
	count: 检测到圆的个数
	output:
	ret:检测到的圆心
	:*/



	Mat  src_gray;
	/// Convert it to gray
	cvtColor(src, src_gray, CV_BGR2GRAY);



	//将图像减小
	//Mat dst;
	//resize(stc.dst,size(dst.size())


	/// Reduce the noise so we avoid false circle detection
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

	vector<Vec3f> circles;

	/// Apply the Hough Transform to find the circles
	HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / minDist, param1, param2, minRadius, maxRadius);

	/// Draw the circles detected
	//int *ret = malloc(16 * sizeof(int));
	Point *ret = (Point *)malloc(count * sizeof(Point));

	int * rad = (int *)malloc(count * sizeof(int));

	/*cout << sizeof(ret) << endl;
	cout << sizeof(ret[0]) << endl;*/
	//cout << count << endl;
	if (!ret)
		return NULL;

	for (size_t i = 0; i < circles.size(); i++)
	{

		//Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		//int radius = cvRound(circles[i][2]);
		Point center(circles[i][0], circles[i][1]);
		int radius = circles[i][2];





		ret[i] = center;
		rad[i] = radius;

		//circle center
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//circle outline
		circle(src, center, radius, Scalar(0, 0, 255), 3, 8, 0);

		//write radius
		//putText(src, to_string(i), center, FONT_HERSHEY_SIMPLEX, 1.2, Scalar(0, 0, 255), 2);
	}


	/*sort Point*/
	//cout << circles.size() << endl;
	int i, j;
	bool swapped;
	for (i = 0; i < circles.size() - 1; i++) {
		swapped = false;

		for (j = 0; j < circles.size() - i - 1; j++) {
			if ((ret[j].x > ret[j + 1].x) || ((ret[j].x == ret[j + 1].x) && (ret[j].y > ret[j + 1].y))) {
				swapPoint(&(ret[j]), &(ret[j + 1]));

				swapRadius(&rad[j], &(rad[j + 1]));

				swapped = true;

			}
		}
		if (swapped == false)
			break;
	}


	///*print point*/

	/*for (size_t i = 0; i < count; i++)
	{
	cout << ret[i].x << "  " << ret[i].y << endl;
	cout << "rad "<< i<< "  "  <<rad[i] << endl;
	}*/



	// Show your results
	/*namedWindow("Hough Circle Transform Demo", CV_WINDOW_NORMAL);
	imshow("Hough Circle Transform Demo", src);*/


	return ret;
}
