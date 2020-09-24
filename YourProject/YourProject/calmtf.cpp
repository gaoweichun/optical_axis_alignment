#include <stdio.h>
#include <conio.h>
#include "YourLib.h"

#include <opencv2\opencv.hpp>


#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include "calmtf.h"

using namespace cv;
using namespace std;


double * calRight(Mat src, Point *centers,int xdistance,int ydistance, int width,int high) {
	/*����������
	*/

	double *mtf50 = (double *)malloc(16 * sizeof(double));
	for (int i = 0; i < 16; i++) {
		if (i == 4 || i == 5 || i == 11)                //�����ʵ��Բ������
			continue;


		Mat disp_image;
		if (i < 10) {
			disp_image = src(Rect(centers[i].x - xdistance - 70, centers[i].y - ydistance, width, high));
		}
		else {
			disp_image = src(Rect(centers[i].x + xdistance, centers[i].y - ydistance, width, high));
		}

		
	


		//Mat disp_image = imread("cut1.png", 1);
		//����matlab�������ͼ����ǿ
		mwSize  mdim[3] = { disp_image.rows,disp_image.cols,3 };
		mwArray mdisp_image(3, mdim, mxDOUBLE_CLASS, mxREAL);
		//C++����תmatlab  �ӿھ���ת�������ع�һ��
		for (int j = 0; j < disp_image.rows; ++j) {
			for (int i = 0; i < disp_image.cols; ++i) {
				Vec3b& mp = disp_image.at<Vec3b>(j, i);        //C++�������洢����ֵ
				double B = mp.val[0] * 1.0 / 255;                //���ع�һ����0-1֮��
				double G = mp.val[1] * 1.0 / 255;
				double R = mp.val[2] * 1.0 / 255;
				mdisp_image(j + 1, i + 1, 1) = R;            //matlab����������R��G��B�洢����ֵ
				mdisp_image(j + 1, i + 1, 2) = G;            //C++ͼ���������ֵ����matlab����
				mdisp_image(j + 1, i + 1, 3) = B;
			}
		}

		//imshow("orange", disp_image);
		if (!disp_image.data)
		{
			cout << "fail to load image!" << endl;
		}
		//waitKey(0);


		//mwArray in_1((mxInt32)3);
		//mwArray in_2((mxInt32)2);
		mwArray out1;

		sfrmat5(1, out1, mdisp_image);

		//YourFunc(1, out, in_1, in_2);


		mxDouble result;
		out1.GetData(&result, 1);
		//printf("result:%lf\n", result);

		mtf50[i] = result;
		//double angle = result;


		if(i<10){

			//disp_image = src(Rect(centers[i].x - xdistance - 70, centers[i].y - ydistance, width, high));

			rectangle(src, Rect(centers[i].x - xdistance - 70, centers[i].y - ydistance, width, high), Scalar(0, 255, 0), 2); //������Ȥ��������

			putText(src, to_string(result), centers[i], FONT_HERSHEY_SIMPLEX, 1.2, Scalar(0, 0, 255), 2); // ��ͼ��д��mtf50
		}
		else {
			rectangle(src, Rect(centers[i].x + xdistance, centers[i].y - ydistance, width, high), Scalar(0, 255, 0), 2); //������Ȥ��������

			putText(src, to_string(result), centers[i], FONT_HERSHEY_SIMPLEX, 1.2, Scalar(0, 0, 255), 2); // ��ͼ��д��mtf50
		}
		


	}


	//namedWindow("Hough Circle Transform Demo", CV_WINDOW_NORMAL);

	//

	//imshow("Hough Circle Transform Demo", src);
	//waitKey(0);
	return mtf50;

}

double * calLeft(Mat src, Point *centers, int xdistance,int ydistance,int width, int high) {
	/*����������
	*/

	double *mtf50 = (double *)malloc(16 * sizeof(double));
	for (int i = 0; i < 16; i++) {
		if (i == 4 || i == 5 || i == 11)                //�����ʵ��Բ������
			continue;



		

		Mat disp_image = src(Rect(centers[i].x - xdistance -70, centers[i].y - ydistance, width, high));
		//Mat disp_image = imread("cut1.png", 1);
		//����matlab�������ͼ����ǿ
		mwSize  mdim[3] = { disp_image.rows,disp_image.cols,3 };
		mwArray mdisp_image(3, mdim, mxDOUBLE_CLASS, mxREAL);
		//C++����תmatlab  �ӿھ���ת�������ع�һ��
		for (int j = 0; j < disp_image.rows; ++j) {
			for (int i = 0; i < disp_image.cols; ++i) {
				Vec3b& mp = disp_image.at<Vec3b>(j, i);        //C++�������洢����ֵ
				double B = mp.val[0] * 1.0 / 255;                //���ع�һ����0-1֮��
				double G = mp.val[1] * 1.0 / 255;
				double R = mp.val[2] * 1.0 / 255;
				mdisp_image(j + 1, i + 1, 1) = R;            //matlab����������R��G��B�洢����ֵ
				mdisp_image(j + 1, i + 1, 2) = G;            //C++ͼ���������ֵ����matlab����
				mdisp_image(j + 1, i + 1, 3) = B;
			}
		}

		//imshow("orange", disp_image);
		if (!disp_image.data)
		{
			cout << "fail to load image!" << endl;
		}
		//waitKey(0);


		//mwArray in_1((mxInt32)3);
		//mwArray in_2((mxInt32)2);
		mwArray out1;

		sfrmat5(1, out1, mdisp_image);

		//YourFunc(1, out, in_1, in_2);


		mxDouble result;
		out1.GetData(&result, 1);
		//printf("result:%lf\n", result);

		mtf50[i] = result;
		//double angle = result;

		Point leftCenter(centers[i].x - 200, centers[i].y);

		rectangle(src, Rect(centers[i].x - 60-70, centers[i].y - ydistance, width, high), Scalar(0, 255, 0), 2); //������Ȥ��������

		putText(src, to_string(result), leftCenter, FONT_HERSHEY_SIMPLEX, 1.2, Scalar(0, 0, 255), 2); // ��ͼ��д��mtf50


	}


	/*namedWindow("Hough Circle Transform Demo", CV_WINDOW_NORMAL);

	imshow("Hough Circle Transform Demo", src);
	waitKey(0);*/
	return mtf50;

}
