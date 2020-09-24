#define _CRT_SECURE_NO_WARNINGS
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>

using namespace std;
using namespace cv;

int Cornerdetect(const Mat& imgsrc, double(*arr_con)[2])//角点检测
{
	Mat dst, norm_dst, normScaleDst;
	//int blockSize = 2;//
	//int ksize = 5;//sobel算子孔径大小
	//double k = 0.04;
	cornerHarris(imgsrc, dst, 2, 5, 0.04, BORDER_DEFAULT);// 角点检测
	normalize(dst, norm_dst, 0, 255, NORM_MINMAX, CV_32FC1, Mat()); // 检测出的元素值范围不确定，而且有正有负，归一化一下
	convertScaleAbs(norm_dst, normScaleDst); // 将元素值取绝对值，且将输出图像深度变为 CV_8U    公式：dst(I)=abs(src(I)*scale + shift)


	Mat resultImg = imgsrc.clone();// 深拷贝
	int a = 0;
	for (int row = 0; row < resultImg.rows; row++)
	{
		uchar* currentRow = normScaleDst.ptr(row);
		for (int col = 0; col < resultImg.cols; col++)
		{
			int value = (int)*currentRow;
			if (value > 110)
			{// 过滤，角点响应值 大于 阈值才显示
				circle(resultImg, Point(col, row), 2, Scalar(0, 0, 255), 2, 8, 0);
				*(*(arr_con + a) + 0) = col;
				*(*(arr_con + a) + 1) = row;
				a++;
			}
			currentRow++;// scaleDst的深度是CV_8U ， 所以用 ++ 指针步长没有问题
		}
	}

	imshow("output_title", resultImg);
	waitKey(0);
	return a;
}

int mould_left(const Mat& src, double(*arr_con)[2])
{
	int a = 0;
	double minvalue;//阈值下限
	double maxvalue;//阈值上限
	Mat src1;
	src(Rect(0, 0, 600, 1900)).copyTo(src1);
	Mat src2 = imread("b1-2.jpg");
	Mat src3;
	src3.create(src1.cols - src2.cols + 1, src1.rows - src2.rows + 1, CV_32FC1);
	matchTemplate(src1, src2, src3, 1);
	normalize(src3, src3, 0, 1, NORM_MINMAX);

	int flag = 0;
	for (int y = 0; y < src3.rows; y++)//int x = 0; x < src3.cols; x++
	{
		for (int x = 0; x < src3.cols; x++)//int y = 0; y < src3.rows; y++
		{
			minvalue = 0.08;
			if (src3.at<float>(y, x) < minvalue)
			{
				rectangle(src1, Point(x, y), Point(x + src2.cols, y + src2.rows), Scalar(0, 0, 255), 1, 1, 0);
				Mat roi_src;
				src1(Rect(Point(x, y), Point(x + src2.cols, y + src2.rows))).copyTo(roi_src);
				Mat src_gary;
				cvtColor(roi_src, src_gary, COLOR_BGR2GRAY);
				for (int m = 0; m < src_gary.rows; m++)
				{
					for (int n = 0; n < src_gary.cols; n++)
					{
						if (src_gary.at<uchar>(m, n)>30)
						{
							src_gary.at<uchar>(m, n) = 255;//白
						}
						else
						{
							src_gary.at<uchar>(m, n) = 0;//黑
						}
					}
				}
				Mat dst, norm_dst, normScaleDst;
				//int blockSize = 2;//
				//int ksize = 5;//sobel算子孔径大小
				//double k = 0.04;
				cornerHarris(src_gary, dst, 2, 5, 0.04, BORDER_DEFAULT);// 角点检测
				normalize(dst, norm_dst, 0, 255, NORM_MINMAX, CV_32FC1, Mat()); // 检测出的元素值范围不确定，而且有正有负，归一化一下
				convertScaleAbs(norm_dst, normScaleDst); // 将元素值取绝对值，且将输出图像深度变为 CV_8U    公式：dst(I)=abs(src(I)*scale + shift)


				Mat resultImg = src_gary.clone();// 深拷贝
				for (int row = 0; row < resultImg.rows; row++)
				{
					uchar* currentRow = normScaleDst.ptr(row);
					for (int col = 0; col < resultImg.cols; col++)
					{
						int value = (int)*currentRow;
						if (value > 130)
						{// 过滤，角点响应值 大于 阈值才显示
							circle(resultImg, Point(col, row), 2, Scalar(0, 0, 0), 2, 8, 0);
							*(*(arr_con + a) + 0) = col + x;
							*(*(arr_con + a) + 1) = row + y;
							a++;
						}
						currentRow++;// scaleDst的深度是CV_8U ， 所以用 ++ 指针步长没有问题
					}
				}

				y = y + 20;
				flag++;
			}
		}
	}
	//printf("left %d\n", flag);
	return a;
}

int mould_right(const Mat& src, double(*arr_con)[2])
{
	int a = 0;
	double minvalue;//阈值下限
	double maxvalue;//阈值上限
	Mat src1;
	src(Rect(3600, 0, 400, 1900)).copyTo(src1);
	Mat src2 = imread("b1-2.jpg");
	Mat src3;
	src3.create(src1.cols - src2.cols + 1, src1.rows - src2.rows + 1, CV_32FC1);
	matchTemplate(src1, src2, src3, 1);
	normalize(src3, src3, 0, 1, NORM_MINMAX);

	int flag = 0;
	for (int y = 0; y < src3.rows; y++)//int x = 0; x < src3.cols; x++
	{
		for (int x = 0; x < src3.cols; x++)//int y = 0; y < src3.rows; y++
		{
			minvalue = 0.08;
			if (src3.at<float>(y, x) < minvalue)
			{
				rectangle(src1, Point(x, y), Point(x + src2.cols, y + src2.rows), Scalar(0, 0, 255), 1, 1, 0);
				Mat roi_src;
				src1(Rect(Point(x, y), Point(x + src2.cols, y + src2.rows))).copyTo(roi_src);
				Mat src_gary;
				cvtColor(roi_src, src_gary, COLOR_BGR2GRAY);
				for (int m = 0; m < src_gary.rows; m++)
				{
					for (int n = 0; n < src_gary.cols; n++)
					{
						if (src_gary.at<uchar>(m, n)>30)
						{
							src_gary.at<uchar>(m, n) = 255;//白
						}
						else
						{
							src_gary.at<uchar>(m, n) = 0;//黑
						}
					}
				}
				Mat dst, norm_dst, normScaleDst;
				//int blockSize = 2;//
				//int ksize = 5;//sobel算子孔径大小
				//double k = 0.04;
				cornerHarris(src_gary, dst, 2, 5, 0.04, BORDER_DEFAULT);// 角点检测
				normalize(dst, norm_dst, 0, 255, NORM_MINMAX, CV_32FC1, Mat()); // 检测出的元素值范围不确定，而且有正有负，归一化一下
				convertScaleAbs(norm_dst, normScaleDst); // 将元素值取绝对值，且将输出图像深度变为 CV_8U    公式：dst(I)=abs(src(I)*scale + shift)


				Mat resultImg = src_gary.clone();// 深拷贝
				for (int row = 0; row < resultImg.rows; row++)
				{
					uchar* currentRow = normScaleDst.ptr(row);
					for (int col = 0; col < resultImg.cols; col++)
					{
						int value = (int)*currentRow;
						if (value > 130)
						{// 过滤，角点响应值 大于 阈值才显示
							circle(resultImg, Point(col, row), 2, Scalar(0, 0, 0), 2, 8, 0);
							*(*(arr_con + a) + 0) = col + x + 3600;
							*(*(arr_con + a) + 1) = row + y;
							a++;
						}
						currentRow++;// scaleDst的深度是CV_8U ， 所以用 ++ 指针步长没有问题
					}
				}

				y = y + 20;
				flag++;
			}
		}
	}
	//printf("right  %d\n", flag);
	return a;
}

int mould_up(const Mat& src, double(*arr_con)[2])
{
	int a = 0;
	double minvalue;//阈值下限
	double maxvalue;//阈值上限
	Mat src1;
	src(Rect(0, 0, 4000, 400)).copyTo(src1);
	Mat src2 = imread("b1-3.jpg");
	Mat src3;
	src3.create(src1.cols - src2.cols + 1, src1.rows - src2.rows + 1, CV_32FC1);
	matchTemplate(src1, src2, src3, 1);
	normalize(src3, src3, 0, 1, NORM_MINMAX);
	int flag = 0;

	for (int x = 0; x < src3.cols; x++)//int x = 0; x < src3.cols; x++
	{
		for (int y = 0; y < src3.rows; y++)//int y = 0; y < src3.rows; y++
		{
			minvalue = 0.1;
			if (src3.at<float>(y, x) < minvalue)
			{
				rectangle(src1, Point(x, y), Point(x + src2.cols, y + src2.rows), Scalar(0, 0, 255), 1, 1, 0);
				Mat roi_src;
				src1(Rect(Point(x, y), Point(x + src2.cols, y + src2.rows))).copyTo(roi_src);
				Mat src_gary;
				cvtColor(roi_src, src_gary, COLOR_BGR2GRAY);
				for (int m = 0; m < src_gary.rows; m++)
				{
					for (int n = 0; n < src_gary.cols; n++)
					{
						if (src_gary.at<uchar>(m, n)>30)
						{
							src_gary.at<uchar>(m, n) = 255;//白
						}
						else
						{
							src_gary.at<uchar>(m, n) = 0;//黑
						}
					}
				}
				Mat dst, norm_dst, normScaleDst;
				//int blockSize = 2;//
				//int ksize = 5;//sobel算子孔径大小
				//double k = 0.04;
				cornerHarris(src_gary, dst, 2, 5, 0.04, BORDER_DEFAULT);// 角点检测
				normalize(dst, norm_dst, 0, 255, NORM_MINMAX, CV_32FC1, Mat()); // 检测出的元素值范围不确定，而且有正有负，归一化一下
				convertScaleAbs(norm_dst, normScaleDst); // 将元素值取绝对值，且将输出图像深度变为 CV_8U    公式：dst(I)=abs(src(I)*scale + shift)


				Mat resultImg = src_gary.clone();// 深拷贝
				for (int row = 0; row < resultImg.rows; row++)
				{
					uchar* currentRow = normScaleDst.ptr(row);
					for (int col = 0; col < resultImg.cols; col++)
					{
						int value = (int)*currentRow;
						if (value > 130)
						{// 过滤，角点响应值 大于 阈值才显示
							circle(resultImg, Point(col, row), 2, Scalar(0, 0, 0), 2, 8, 0);
							*(*(arr_con + a) + 0) = col + x;
							*(*(arr_con + a) + 1) = row + y;
							a++;
						}
						currentRow++;// scaleDst的深度是CV_8U ， 所以用 ++ 指针步长没有问题
					}
				}

				x = x + 20;
				flag++;
			}
		}
	}
	//printf("up   %d\n", flag);
	return a;
}

int mould_down(const Mat& src, double(*arr_con)[2])
{
	int a = 0;
	double minvalue;//阈值下限
	double maxvalue;//阈值上限
	Mat src1;
	src(Rect(0, 1600, 4000, 500)).copyTo(src1);
	Mat src2 = imread("b1-3.jpg");
	Mat src3;
	src3.create(src1.cols - src2.cols + 1, src1.rows - src2.rows + 1, CV_32FC1);
	matchTemplate(src1, src2, src3, 1);
	normalize(src3, src3, 0, 1, NORM_MINMAX);
	int flag = 0;

	for (int x = 0; x < src3.cols; x++)//int x = 0; x < src3.cols; x++
	{
		for (int y = 0; y < src3.rows; y++)//int y = 0; y < src3.rows; y++
		{
			minvalue = 0.08;
			if (src3.at<float>(y, x) < minvalue)
			{
				rectangle(src1, Point(x, y), Point(x + src2.cols, y + src2.rows), Scalar(0, 0, 255), 1, 1, 0);
				Mat roi_src;
				src1(Rect(Point(x, y), Point(x + src2.cols, y + src2.rows))).copyTo(roi_src);
				Mat src_gary;
				cvtColor(roi_src, src_gary, COLOR_BGR2GRAY);
				for (int m = 0; m < src_gary.rows; m++)
				{
					for (int n = 0; n < src_gary.cols; n++)
					{
						if (src_gary.at<uchar>(m, n)>30)
						{
							src_gary.at<uchar>(m, n) = 255;//白
						}
						else
						{
							src_gary.at<uchar>(m, n) = 0;//黑
						}
					}
				}
				Mat dst, norm_dst, normScaleDst;
				//int blockSize = 2;//
				//int ksize = 5;//sobel算子孔径大小
				//double k = 0.04;
				cornerHarris(src_gary, dst, 5, 5, 0.04, BORDER_DEFAULT);// 角点检测
				normalize(dst, norm_dst, 0, 255, NORM_MINMAX, CV_32FC1, Mat()); // 检测出的元素值范围不确定，而且有正有负，归一化一下
				convertScaleAbs(norm_dst, normScaleDst); // 将元素值取绝对值，且将输出图像深度变为 CV_8U    公式：dst(I)=abs(src(I)*scale + shift)


				Mat resultImg = src_gary.clone();// 深拷贝
				for (int row = 0; row < resultImg.rows; row++)
				{
					uchar* currentRow = normScaleDst.ptr(row);
					for (int col = 0; col < resultImg.cols; col++)
					{
						int value = (int)*currentRow;
						if (value > 130)
						{// 过滤，角点响应值 大于 阈值才显示
							circle(resultImg, Point(col, row), 2, Scalar(0, 0, 0), 2, 8, 0);
							*(*(arr_con + a) + 0) = col + x;
							*(*(arr_con + a) + 1) = row + y + 1600;
							a++;
						}
						currentRow++;// scaleDst的深度是CV_8U ， 所以用 ++ 指针步长没有问题
					}
				}

				x = x + 20;
				flag++;
			}
		}
	}
	//printf("down   %d\n", flag);
	return a;
}

void bubblesort_lr(double(*arr_con)[2], int num)
{
	int temp[2] = { 0 };
	for (int i = 0; i < num - 1; i++)
	{
		for (int j = 0; j < num - i - 1; j++)
		{
			if ((*(*(arr_con + j) + 1)) >= (*(*(arr_con + j + 1) + 1)))
			{
				temp[0] = *(*(arr_con + j) + 0);
				temp[1] = *(*(arr_con + j) + 1);
				*(*(arr_con + j) + 0) = *(*(arr_con + j + 1) + 0);
				*(*(arr_con + j) + 1) = *(*(arr_con + j + 1) + 1);
				*(*(arr_con + j + 1) + 0) = temp[0];
				*(*(arr_con + j + 1) + 1) = temp[1];
			}
		}
	}
}

void bubblesort_ud(double(*arr_con)[2], int num)
{
	int temp[2] = { 0 };
	for (int i = 0; i < num - 1; i++)
	{
		for (int j = 0; j < num - i - 1; j++)
		{
			if ((*(*(arr_con + j) + 0)) >= (*(*(arr_con + j + 1) + 0)))
			{
				temp[0] = *(*(arr_con + j) + 0);
				temp[1] = *(*(arr_con + j) + 1);
				*(*(arr_con + j) + 0) = *(*(arr_con + j + 1) + 0);
				*(*(arr_con + j) + 1) = *(*(arr_con + j + 1) + 1);
				*(*(arr_con + j + 1) + 0) = temp[0];
				*(*(arr_con + j + 1) + 1) = temp[1];
			}
		}
	}
}

void arr_sort_left_new(double(*arr_con)[2], double(*left1)[2], double(*left2)[2], int num, int &num1, int &num2)
{
	double delta = *(*(arr_con + num - 1) + 1) - *(*(arr_con + 0) + 1);
	double flag1 = 0;  double flag2 = 0;  double flag3 = 0;  double flag4 = 0;  double flag5 = 0;
	double a = 0;  double b = 0;  double c = 0;  double d = 0;  double e = 0;
	int num_left1 = 0;    int num_left2 = 0;
	for (int i = 0; i < num; i++)
	{
		if (*(*(arr_con + i) + 1) >= *(*(arr_con + 0) + 1) && *(*(arr_con + i) + 1) < *(*(arr_con + 0) + 1) + delta / 5)
		{
			flag1 = flag1 + *(*(arr_con + i) + 0);
			a++;
		}
		else if (*(*(arr_con + i) + 1) >= *(*(arr_con + 0) + 1) + delta / 5 && *(*(arr_con + i) + 1) < *(*(arr_con + 0) + 1) + delta * 2 / 5)
		{
			flag2 = flag2 + *(*(arr_con + i) + 0);
			b++;
		}
		else if (*(*(arr_con + i) + 1) >= *(*(arr_con + 0) + 1) + delta * 2 / 5 && *(*(arr_con + i) + 1) < *(*(arr_con + 0) + 1) + delta * 3 / 5)
		{
			flag3 = flag3 + *(*(arr_con + i) + 0);
			c++;
		}
		else if (*(*(arr_con + i) + 1) >= *(*(arr_con + 0) + 1) + delta * 3 / 5 && *(*(arr_con + i) + 1) < *(*(arr_con + 0) + 1) + +delta * 4 / 5)
		{
			flag4 = flag4 + *(*(arr_con + i) + 0);
			d++;
		}
		else
		{
			flag5 = flag5 + *(*(arr_con + i) + 0);
			e++;
		}
	}
	for (int i = 0; i < num; i++)
	{
		if (*(*(arr_con + i) + 1) >= *(*(arr_con + 0) + 1) && *(*(arr_con + i) + 1) < *(*(arr_con + 0) + 1) + delta / 5.0)
		{
			if (*(*(arr_con + i) + 0) >= flag1 / a)
			{
				*(*(left1 + num_left1) + 0) = *(*(arr_con + i) + 0);
				*(*(left1 + num_left1) + 1) = *(*(arr_con + i) + 1);
				num_left1++;
			}
			else
			{
				*(*(left2 + num_left2) + 0) = *(*(arr_con + i) + 0);
				*(*(left2 + num_left2) + 1) = *(*(arr_con + i) + 1);
				num_left2++;
			}
		}
		else if (*(*(arr_con + i) + 1) >= *(*(arr_con + 0) + 1) + delta / 5.0 && *(*(arr_con + i) + 1) < *(*(arr_con + 0) + 1) + delta * 2.0 / 5.0)
		{
			if (*(*(arr_con + i) + 0) >= flag2 / b)
			{
				*(*(left1 + num_left1) + 0) = *(*(arr_con + i) + 0);
				*(*(left1 + num_left1) + 1) = *(*(arr_con + i) + 1);
				num_left1++;
			}
			else
			{
				*(*(left2 + num_left2) + 0) = *(*(arr_con + i) + 0);
				*(*(left2 + num_left2) + 1) = *(*(arr_con + i) + 1);
				num_left2++;
			}
		}
		else if (*(*(arr_con + i) + 1) >= *(*(arr_con + 0) + 1) + delta * 2.0 / 5.0 && *(*(arr_con + i) + 1) < *(*(arr_con + 0) + 1) + delta * 3.0 / 5.0)
		{
			if (*(*(arr_con + i) + 0) >= flag3 / c)
			{
				*(*(left1 + num_left1) + 0) = *(*(arr_con + i) + 0);
				*(*(left1 + num_left1) + 1) = *(*(arr_con + i) + 1);
				num_left1++;
			}
			else
			{
				*(*(left2 + num_left2) + 0) = *(*(arr_con + i) + 0);
				*(*(left2 + num_left2) + 1) = *(*(arr_con + i) + 1);
				num_left2++;
			}
		}
		else if (*(*(arr_con + i) + 1) >= *(*(arr_con + 0) + 1) + delta * 3.0 / 5.0 && *(*(arr_con + i) + 1) < *(*(arr_con + 0) + 1) + delta * 4.0 / 5.0)
		{
			if (*(*(arr_con + i) + 0) >= flag4 / d)
			{
				*(*(left1 + num_left1) + 0) = *(*(arr_con + i) + 0);
				*(*(left1 + num_left1) + 1) = *(*(arr_con + i) + 1);
				num_left1++;
			}
			else
			{
				*(*(left2 + num_left2) + 0) = *(*(arr_con + i) + 0);
				*(*(left2 + num_left2) + 1) = *(*(arr_con + i) + 1);
				num_left2++;
			}
		}
		else
		{
			if (*(*(arr_con + i) + 0) >= flag5 / e)
			{
				*(*(left1 + num_left1) + 0) = *(*(arr_con + i) + 0);
				*(*(left1 + num_left1) + 1) = *(*(arr_con + i) + 1);
				num_left1++;
			}
			else
			{
				*(*(left2 + num_left2) + 0) = *(*(arr_con + i) + 0);
				*(*(left2 + num_left2) + 1) = *(*(arr_con + i) + 1);
				num_left2++;
			}
		}
	}
	num1 = num_left1;
	num2 = num_left2;
}

void arr_sort_right_new(double(*arr_con)[2], double(*right1)[2], double(*right2)[2], int num, int &num1, int &num2)
{
	double delta = *(*(arr_con + num - 1) + 1) - *(*(arr_con + 0) + 1);
	double flag1 = 0;  double flag2 = 0;  double flag3 = 0;  double flag4 = 0;  double flag5 = 0;
	double a = 0;  double b = 0;  double c = 0;  double d = 0;  double e = 0;
	int num_right1 = 0;   int num_right2 = 0;
	for (int i = 0; i < num; i++)
	{
		if (*(*(arr_con + i) + 1) >= *(*(arr_con + 0) + 1) && *(*(arr_con + i) + 1) < *(*(arr_con + 0) + 1) + delta / 5)
		{
			flag1 = flag1 + *(*(arr_con + i) + 0);
			a++;
		}
		else if (*(*(arr_con + i) + 1) >= *(*(arr_con + 0) + 1) + delta / 5 && *(*(arr_con + i) + 1) < *(*(arr_con + 0) + 1) + delta * 2 / 5)
		{
			flag2 = flag2 + *(*(arr_con + i) + 0);
			b++;
		}
		else if (*(*(arr_con + i) + 1) >= *(*(arr_con + 0) + 1) + delta * 2 / 5 && *(*(arr_con + i) + 1) < *(*(arr_con + 0) + 1) + delta * 3 / 5)
		{
			flag3 = flag3 + *(*(arr_con + i) + 0);
			c++;
		}
		else if (*(*(arr_con + i) + 1) >= *(*(arr_con + 0) + 1) + delta * 3 / 5 && *(*(arr_con + i) + 1) < *(*(arr_con + 0) + 1) + +delta * 4 / 5)
		{
			flag4 = flag4 + *(*(arr_con + i) + 0);
			d++;
		}
		else
		{
			flag5 = flag5 + *(*(arr_con + i) + 0);
			e++;
		}
	}
	for (int i = 0; i < num; i++)
	{
		if (*(*(arr_con + i) + 1) >= *(*(arr_con + 0) + 1) && *(*(arr_con + i) + 1) < *(*(arr_con + 0) + 1) + delta / 5.0)
		{
			if (*(*(arr_con + i) + 0) >= flag1 / a)
			{
				*(*(right1 + num_right1) + 0) = *(*(arr_con + i) + 0);
				*(*(right1 + num_right1) + 1) = *(*(arr_con + i) + 1);
				num_right1++;
			}
			else
			{
				*(*(right2 + num_right2) + 0) = *(*(arr_con + i) + 0);
				*(*(right2 + num_right2) + 1) = *(*(arr_con + i) + 1);
				num_right2++;
			}
		}
		else if (*(*(arr_con + i) + 1) >= *(*(arr_con + 0) + 1) + delta / 5.0 && *(*(arr_con + i) + 1) < *(*(arr_con + 0) + 1) + delta * 2.0 / 5.0)
		{
			if (*(*(arr_con + i) + 0) >= flag2 / b)
			{
				*(*(right1 + num_right1) + 0) = *(*(arr_con + i) + 0);
				*(*(right1 + num_right1) + 1) = *(*(arr_con + i) + 1);
				num_right1++;
			}
			else
			{
				*(*(right2 + num_right2) + 0) = *(*(arr_con + i) + 0);
				*(*(right2 + num_right2) + 1) = *(*(arr_con + i) + 1);
				num_right2++;
			}
		}
		else if (*(*(arr_con + i) + 1) >= *(*(arr_con + 0) + 1) + delta * 2.0 / 5.0 && *(*(arr_con + i) + 1) < *(*(arr_con + 0) + 1) + delta * 3.0 / 5.0)
		{
			if (*(*(arr_con + i) + 0) >= flag3 / c)
			{
				*(*(right1 + num_right1) + 0) = *(*(arr_con + i) + 0);
				*(*(right1 + num_right1) + 1) = *(*(arr_con + i) + 1);
				num_right1++;
			}
			else
			{
				*(*(right2 + num_right2) + 0) = *(*(arr_con + i) + 0);
				*(*(right2 + num_right2) + 1) = *(*(arr_con + i) + 1);
				num_right2++;
			}
		}
		else if (*(*(arr_con + i) + 1) >= *(*(arr_con + 0) + 1) + delta * 3.0 / 5.0 && *(*(arr_con + i) + 1) < *(*(arr_con + 0) + 1) + delta * 4.0 / 5.0)
		{
			if (*(*(arr_con + i) + 0) >= flag4 / d)
			{
				*(*(right1 + num_right1) + 0) = *(*(arr_con + i) + 0);
				*(*(right1 + num_right1) + 1) = *(*(arr_con + i) + 1);
				num_right1++;
			}
			else
			{
				*(*(right2 + num_right2) + 0) = *(*(arr_con + i) + 0);
				*(*(right2 + num_right2) + 1) = *(*(arr_con + i) + 1);
				num_right2++;
			}
		}
		else
		{
			if (*(*(arr_con + i) + 0) >= flag5 / e)
			{
				*(*(right1 + num_right1) + 0) = *(*(arr_con + i) + 0);
				*(*(right1 + num_right1) + 1) = *(*(arr_con + i) + 1);
				num_right1++;
			}
			else
			{
				*(*(right2 + num_right2) + 0) = *(*(arr_con + i) + 0);
				*(*(right2 + num_right2) + 1) = *(*(arr_con + i) + 1);
				num_right2++;
			}
		}
	}
	num1 = num_right1;
	num2 = num_right2;
}

void arr_sort_up_new(double(*arr_con)[2], double(*up1)[2], double(*up2)[2], int num, int &num1, int &num2)
{
	double delta = *(*(arr_con + num - 1) + 0) - *(*(arr_con + 0) + 0);
	double flag1 = 0;  double flag2 = 0;  double flag3 = 0;  double flag4 = 0;  double flag5 = 0;   double flag6 = 0;
	double a = 0;  double b = 0;  double c = 0;  double d = 0;  double e = 0;  double f = 0;
	int num_up1 = 0;    int num_up2 = 0;
	for (int i = 0; i < num; i++)
	{
		if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + delta / 6)
		{
			flag1 = flag1 + *(*(arr_con + i) + 1);
			a++;
		}
		else if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) + delta / 6 && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + delta * 2 / 6)
		{
			flag2 = flag2 + *(*(arr_con + i) + 1);
			b++;
		}
		else if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) + delta * 2 / 6 && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + delta * 3 / 6)
		{
			flag3 = flag3 + *(*(arr_con + i) + 1);
			c++;
		}
		else if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) + delta * 3 / 6 && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + +delta * 4 / 6)
		{
			flag4 = flag4 + *(*(arr_con + i) + 1);
			d++;
		}
		else if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) + delta * 4 / 6 && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + +delta * 5 / 6)
		{
			flag5 = flag5 + *(*(arr_con + i) + 1);
			e++;
		}
		else
		{
			flag6 = flag6 + *(*(arr_con + i) + 1);
			f++;
		}
	}
	for (int i = 0; i < num; i++)
	{
		if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + delta / 6.0)
		{
			if (*(*(arr_con + i) + 1) >= flag1 / a)
			{
				*(*(up1 + num_up1) + 0) = *(*(arr_con + i) + 0);
				*(*(up1 + num_up1) + 1) = *(*(arr_con + i) + 1);
				num_up1++;
			}
			else
			{
				*(*(up2 + num_up2) + 0) = *(*(arr_con + i) + 0);
				*(*(up2 + num_up2) + 1) = *(*(arr_con + i) + 1);
				num_up2++;
			}
		}
		else if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) + delta / 6.0 && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + delta * 2.0 / 6.0)
		{
			if (*(*(arr_con + i) + 1) >= flag2 / b)
			{
				*(*(up1 + num_up1) + 0) = *(*(arr_con + i) + 0);
				*(*(up1 + num_up1) + 1) = *(*(arr_con + i) + 1);
				num_up1++;
			}
			else
			{
				*(*(up2 + num_up2) + 0) = *(*(arr_con + i) + 0);
				*(*(up2 + num_up2) + 1) = *(*(arr_con + i) + 1);
				num_up2++;
			}
		}
		else if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) + delta * 2.0 / 6.0 && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + delta * 3.0 / 6.0)
		{
			if (*(*(arr_con + i) + 1) >= flag3 / c)
			{
				*(*(up1 + num_up1) + 0) = *(*(arr_con + i) + 0);
				*(*(up1 + num_up1) + 1) = *(*(arr_con + i) + 1);
				num_up1++;
			}
			else
			{
				*(*(up2 + num_up2) + 0) = *(*(arr_con + i) + 0);
				*(*(up2 + num_up2) + 1) = *(*(arr_con + i) + 1);
				num_up2++;
			}
		}
		else if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) + delta * 3.0 / 6.0 && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + delta * 4.0 / 6.0)
		{
			if (*(*(arr_con + i) + 1) >= flag4 / d)
			{
				*(*(up1 + num_up1) + 0) = *(*(arr_con + i) + 0);
				*(*(up1 + num_up1) + 1) = *(*(arr_con + i) + 1);
				num_up1++;
			}
			else
			{
				*(*(up2 + num_up2) + 0) = *(*(arr_con + i) + 0);
				*(*(up2 + num_up2) + 1) = *(*(arr_con + i) + 1);
				num_up2++;
			}
		}
		else if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) + delta * 4.0 / 6.0 && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + delta * 5.0 / 6.0)
		{
			if (*(*(arr_con + i) + 1) >= flag5 / e)
			{
				*(*(up1 + num_up1) + 0) = *(*(arr_con + i) + 0);
				*(*(up1 + num_up1) + 1) = *(*(arr_con + i) + 1);
				num_up1++;
			}
			else
			{
				*(*(up2 + num_up2) + 0) = *(*(arr_con + i) + 0);
				*(*(up2 + num_up2) + 1) = *(*(arr_con + i) + 1);
				num_up2++;
			}
		}
		else
		{
			if (*(*(arr_con + i) + 1) >= flag6 / f)
			{
				*(*(up1 + num_up1) + 0) = *(*(arr_con + i) + 0);
				*(*(up1 + num_up1) + 1) = *(*(arr_con + i) + 1);
				num_up1++;
			}
			else
			{
				*(*(up2 + num_up2) + 0) = *(*(arr_con + i) + 0);
				*(*(up2 + num_up2) + 1) = *(*(arr_con + i) + 1);
				num_up2++;
			}
		}
	}
	num1 = num_up1;
	num2 = num_up2;
}

void arr_sort_down_new(double(*arr_con)[2], double(*down1)[2], double(*down2)[2], int num, int &num1, int &num2)
{
	double delta = *(*(arr_con + num - 1) + 0) - *(*(arr_con + 0) + 0);
	double flag1 = 0;  double flag2 = 0;  double flag3 = 0;  double flag4 = 0;  double flag5 = 0;   double flag6 = 0;
	double a = 0;  double b = 0;  double c = 0;  double d = 0;  double e = 0;  double f = 0;
	int num_down1 = 0;   int num_down2 = 0;
	for (int i = 0; i < num; i++)
	{
		if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + delta / 6)
		{
			flag1 = flag1 + *(*(arr_con + i) + 1);
			a++;
		}
		else if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) + delta / 6 && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + delta * 2 / 6)
		{
			flag2 = flag2 + *(*(arr_con + i) + 1);
			b++;
		}
		else if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) + delta * 2 / 6 && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + delta * 3 / 6)
		{
			flag3 = flag3 + *(*(arr_con + i) + 1);
			c++;
		}
		else if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) + delta * 3 / 6 && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + +delta * 4 / 6)
		{
			flag4 = flag4 + *(*(arr_con + i) + 1);
			d++;
		}
		else if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) + delta * 4 / 6 && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + +delta * 5 / 6)
		{
			flag5 = flag5 + *(*(arr_con + i) + 1);
			e++;
		}
		else
		{
			flag6 = flag6 + *(*(arr_con + i) + 1);
			f++;
		}
	}
	for (int i = 0; i < num; i++)
	{
		if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + delta / 6.0)
		{
			if (*(*(arr_con + i) + 1) >= flag1 / a)
			{
				*(*(down1 + num_down1) + 0) = *(*(arr_con + i) + 0);
				*(*(down1 + num_down1) + 1) = *(*(arr_con + i) + 1);
				num_down1++;
			}
			else
			{
				*(*(down2 + num_down2) + 0) = *(*(arr_con + i) + 0);
				*(*(down2 + num_down2) + 1) = *(*(arr_con + i) + 1);
				num_down2++;
			}
		}
		else if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) + delta / 6.0 && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + delta * 2.0 / 6.0)
		{
			if (*(*(arr_con + i) + 1) >= flag2 / b)
			{
				*(*(down1 + num_down1) + 0) = *(*(arr_con + i) + 0);
				*(*(down1 + num_down1) + 1) = *(*(arr_con + i) + 1);
				num_down1++;
			}
			else
			{
				*(*(down2 + num_down2) + 0) = *(*(arr_con + i) + 0);
				*(*(down2 + num_down2) + 1) = *(*(arr_con + i) + 1);
				num_down2++;
			}
		}
		else if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) + delta * 2.0 / 6.0 && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + delta * 3.0 / 6.0)
		{
			if (*(*(arr_con + i) + 1) >= flag3 / c)
			{
				*(*(down1 + num_down1) + 0) = *(*(arr_con + i) + 0);
				*(*(down1 + num_down1) + 1) = *(*(arr_con + i) + 1);
				num_down1++;
			}
			else
			{
				*(*(down2 + num_down2) + 0) = *(*(arr_con + i) + 0);
				*(*(down2 + num_down2) + 1) = *(*(arr_con + i) + 1);
				num_down2++;
			}
		}
		else if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) + delta * 3.0 / 6.0 && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + delta * 4.0 / 6.0)
		{
			if (*(*(arr_con + i) + 1) >= flag4 / d)
			{
				*(*(down1 + num_down1) + 0) = *(*(arr_con + i) + 0);
				*(*(down1 + num_down1) + 1) = *(*(arr_con + i) + 1);
				num_down1++;
			}
			else
			{
				*(*(down2 + num_down2) + 0) = *(*(arr_con + i) + 0);
				*(*(down2 + num_down2) + 1) = *(*(arr_con + i) + 1);
				num_down2++;
			}
		}
		else if (*(*(arr_con + i) + 0) >= *(*(arr_con + 0) + 0) + delta * 4.0 / 6.0 && *(*(arr_con + i) + 0) < *(*(arr_con + 0) + 0) + delta * 5.0 / 6.0)
		{
			if (*(*(arr_con + i) + 1) >= flag5 / e)
			{
				*(*(down1 + num_down1) + 0) = *(*(arr_con + i) + 0);
				*(*(down1 + num_down1) + 1) = *(*(arr_con + i) + 1);
				num_down1++;
			}
			else
			{
				*(*(down2 + num_down2) + 0) = *(*(arr_con + i) + 0);
				*(*(down2 + num_down2) + 1) = *(*(arr_con + i) + 1);
				num_down2++;
			}
		}
		else
		{
			if (*(*(arr_con + i) + 1) >= flag6 / f)
			{
				*(*(down1 + num_down1) + 0) = *(*(arr_con + i) + 0);
				*(*(down1 + num_down1) + 1) = *(*(arr_con + i) + 1);
				num_down1++;
			}
			else
			{
				*(*(down2 + num_down2) + 0) = *(*(arr_con + i) + 0);
				*(*(down2 + num_down2) + 1) = *(*(arr_con + i) + 1);
				num_down2++;
			}
		}
	}
	num1 = num_down1;
	num2 = num_down2;
}