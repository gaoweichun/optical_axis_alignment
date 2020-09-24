#define _CRT_SECURE_NO_WARNINGS
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#include "calculate.h"
#include "func.h"

using namespace std;
using namespace cv;

//typedef struct piancha
//{
//	double x;
//	double y;
//};

Point piancha(Mat& src)
{
	Point point;
	int num_left1 = 0;    int num_left2 = 0;
	int num_right1 = 0;   int num_right2 = 0;
	int num_up1 = 0;      int num_up2 = 0;
	int num_down1 = 0;    int num_down2 = 0;


	double arr_left[4096][2] = { 0 };   double arr_left1[4096][2] = { 0 };     double arr_left2[4096][2] = { 0 };
	double arr_right[4096][2] = { 0 };  double arr_right1[4096][2] = { 0 };    double arr_right2[4096][2] = { 0 };
	double arr_up[4096][2] = { 0 };     double arr_up1[4096][2] = { 0 };       double arr_up2[4096][2] = { 0 };
	double arr_down[4096][2] = { 0 };   double arr_down1[4096][2] = { 0 };     double arr_down2[4096][2] = { 0 };//坐标数组

	double A[8] = { 0 };   double B[8] = { 0 };    double C[8] = { 0 };

	int left = mould_left(src, arr_left);
	int right = mould_right(src, arr_right);
	int up = mould_up(src, arr_up);
	int down = mould_down(src, arr_down);//坐标点个数


	bubblesort_lr(arr_left, left);
	bubblesort_lr(arr_right, right);
	bubblesort_ud(arr_up, up);
	bubblesort_ud(arr_down, down);

	arr_sort_left_new(arr_left, arr_left1, arr_left2, left, num_left1, num_left2);
	arr_sort_right_new(arr_right, arr_right1, arr_right2, right, num_right1, num_right2);
	arr_sort_up_new(arr_up, arr_up1, arr_up2, up, num_up1, num_up2);
	arr_sort_down_new(arr_down, arr_down1, arr_down2, down, num_down1, num_down2);

	/*for (int i = 0; i < right;i++)
	{
	printf("%f\n", arr_right[i][0]);
	}
	printf("\n\n\n\n\n\n\n\n");
	for (int i = 0; i <right; i++)
	{
	printf("%f\n", arr_right[i][1]);
	}
	*/
	A[0] = (H2(arr_left1, num_left1)*M12(arr_left1, num_left1) - H1(arr_left1, num_left1)*M22(arr_left1, num_left1)) / (M11(arr_left1, num_left1)*M22(arr_left1, num_left1) - M12(arr_left1, num_left1)*M12(arr_left1, num_left1));
	B[0] = (H2(arr_left1, num_left1)*M11(arr_left1, num_left1) - H1(arr_left1, num_left1)*M12(arr_left1, num_left1)) / (M12(arr_left1, num_left1)*M12(arr_left1, num_left1) - M11(arr_left1, num_left1)*M22(arr_left1, num_left1));
	C[0] = CC(arr_left1, num_left1, A[0], B[0]);

	A[1] = (H2(arr_left2, num_left2)*M12(arr_left2, num_left2) - H1(arr_left2, num_left2)*M22(arr_left2, num_left2)) / (M11(arr_left2, num_left2)*M22(arr_left2, num_left2) - M12(arr_left2, num_left2)*M12(arr_left2, num_left2));
	B[1] = (H2(arr_left2, num_left2)*M11(arr_left2, num_left2) - H1(arr_left2, num_left2)*M12(arr_left2, num_left2)) / (M12(arr_left2, num_left2)*M12(arr_left2, num_left2) - M11(arr_left2, num_left2)*M22(arr_left2, num_left2));
	C[1] = CC(arr_left2, num_left2, A[1], B[1]);

	A[2] = (H2(arr_right1, num_right1)*M12(arr_right1, num_right1) - H1(arr_right1, num_right1)*M22(arr_right1, num_right1)) / (M11(arr_right1, num_right1)*M22(arr_right1, num_right1) - M12(arr_right1, num_right1)*M12(arr_right1, num_right1));
	B[2] = (H2(arr_right1, num_right1)*M11(arr_right1, num_right1) - H1(arr_right1, num_right1)*M12(arr_right1, num_right1)) / (M12(arr_right1, num_right1)*M12(arr_right1, num_right1) - M11(arr_right1, num_right1)*M22(arr_right1, num_right1));
	C[2] = CC(arr_right1, num_right1, A[2], B[2]);

	A[3] = (H2(arr_right2, num_right2)*M12(arr_right2, num_right2) - H1(arr_right2, num_right2)*M22(arr_right2, num_right2)) / (M11(arr_right2, num_right2)*M22(arr_right2, num_right2) - M12(arr_right2, num_right2)*M12(arr_right2, num_right2));
	B[3] = (H2(arr_right2, num_right2)*M11(arr_right2, num_right2) - H1(arr_right2, num_right2)*M12(arr_right2, num_right2)) / (M12(arr_right2, num_right2)*M12(arr_right2, num_right2) - M11(arr_right2, num_right2)*M22(arr_right2, num_right2));
	C[3] = CC(arr_right2, num_right2, A[3], B[3]);

	A[4] = (H2(arr_up1, num_up1)*M12(arr_up1, num_up1) - H1(arr_up1, num_up1)*M22(arr_up1, num_up1)) / (M11(arr_up1, num_up1)*M22(arr_up1, num_up1) - M12(arr_up1, num_up1)*M12(arr_up1, num_up1));
	B[4] = (H2(arr_up1, num_up1)*M11(arr_up1, num_up1) - H1(arr_up1, num_up1)*M12(arr_up1, num_up1)) / (M12(arr_up1, num_up1)*M12(arr_up1, num_up1) - M11(arr_up1, num_up1)*M22(arr_up1, num_up1));
	C[4] = CC(arr_up1, num_up1, A[4], B[4]);

	A[5] = (H2(arr_up2, num_up2)*M12(arr_up2, num_up2) - H1(arr_up2, num_up2)*M22(arr_up2, num_up2)) / (M11(arr_up2, num_up2)*M22(arr_up2, num_up2) - M12(arr_up2, num_up2)*M12(arr_up2, num_up2));
	B[5] = (H2(arr_up2, num_up2)*M11(arr_up2, num_up2) - H1(arr_up2, num_up2)*M12(arr_up2, num_up2)) / (M12(arr_up2, num_up2)*M12(arr_up2, num_up2) - M11(arr_up2, num_up2)*M22(arr_up2, num_up2));
	C[5] = CC(arr_up2, num_up2, A[5], B[5]);

	A[6] = (H2(arr_down1, num_down1)*M12(arr_down1, num_down1) - H1(arr_down1, num_down1)*M22(arr_down1, num_down1)) / (M11(arr_down1, num_down1)*M22(arr_down1, num_down1) - M12(arr_down1, num_down1)*M12(arr_down1, num_down1));
	B[6] = (H2(arr_down1, num_down1)*M11(arr_down1, num_down1) - H1(arr_down1, num_down1)*M12(arr_down1, num_down1)) / (M12(arr_down1, num_down1)*M12(arr_down1, num_down1) - M11(arr_down1, num_down1)*M22(arr_down1, num_down1));
	C[6] = CC(arr_down1, num_down1, A[6], B[6]);

	A[7] = (H2(arr_down2, num_down2)*M12(arr_down2, num_down2) - H1(arr_down2, num_down2)*M22(arr_down2, num_down2)) / (M11(arr_down2, num_down2)*M22(arr_down2, num_down2) - M12(arr_down2, num_down2)*M12(arr_down2, num_down2));
	B[7] = (H2(arr_down2, num_down2)*M11(arr_down2, num_down2) - H1(arr_down2, num_down2)*M12(arr_down2, num_down2)) / (M12(arr_down2, num_down2)*M12(arr_down2, num_down2) - M11(arr_down2, num_down2)*M22(arr_down2, num_down2));
	C[7] = CC(arr_down2, num_down2, A[7], B[7]);


	double del_A[28] = { 0 };
	double del_B[28] = { 0 };
	double del_C[28] = { 0 };
	int q = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = i + 1; j < 8; j++)
		{
			del_A[q] = A[i] - A[j];
			del_B[q] = B[i] - B[j];
			del_C[q] = -(C[i] - C[j]);
			q++;
		}
	}
	double a = 0.0;  double b = 0.0;   double c = 0.0;   double d = 0.0;   double e = 0.0;
	for (int i = 0; i < 28; i++)
	{
		a = a + del_A[i] * del_A[i];
		b = b + del_A[i] * del_B[i];
		c = c + del_B[i] * del_B[i];
		d = d + del_A[i] * del_C[i];
		e = e + del_B[i] * del_C[i];
	}

	double xxx = (d*c - b*e) / (a*c - b*b);
	double yyy = d / b - (a*d*c - a*b*e) / (a*b*c - b*b*b);

	point.x = xxx;
	point.y = yyy;

	return point;
}
