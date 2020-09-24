#define _CRT_SECURE_NO_WARNINGS
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>

using namespace std;
using namespace cv;

double M11(double(*arr_con)[2], int num)
{
	int i = 0;
	double score = 0.0;
	double flag1 = 0.0;
	double flag2 = 0.0;
	for (i = 0; i < num; i++)
	{
		score = score + (*(*(arr_con + i) + 0))*(*(*(arr_con + i) + 0));
	}
	score = score * num;
	for (i = 0; i < num; i++)
	{
		flag1 = flag1 + (*(*(arr_con + i) + 0));
	}
	double FIN = score - flag1*flag1;
	return FIN;
}

double M22(double(*arr_con)[2], int num)
{
	int i = 0;
	double score = 0.0;
	double flag1 = 0.0;
	double flag2 = 0.0;
	for (i = 0; i < num; i++)
	{
		score = score + (*(*(arr_con + i) + 1))*(*(*(arr_con + i) + 1));
	}
	score = score * num;
	for (i = 0; i < num; i++)
	{
		flag1 = flag1 + (*(*(arr_con + i) + 1));
	}
	double FIN = score - flag1*flag1;
	return FIN;
}

double M12(double(*arr_con)[2], int num)
{
	int i = 0;
	int j = 0;
	double flag1 = 0.0;
	double flag2 = 0.0;
	double flag3 = 0.0;
	for (i = 0; i < num; i++)
	{
		flag1 = flag1 + (*(*(arr_con + i) + 0))*(*(*(arr_con + i) + 1));
	}
	flag1 = num * flag1;
	for (i = 0; i < num; i++)
	{
		flag2 = flag2 + (*(*(arr_con + i) + 1));
	}
	for (i = 0; i < num; i++)
	{
		flag3 = flag3 + (*(*(arr_con + i) + 0))*flag2;
	}
	double FIN = flag1 - flag3;
	return FIN;
}

double H1(double(*arr_con)[2], int num)
{
	int i = 0;
	double flag1 = 0.0;
	double flag2 = 0.0;
	double flag3 = 0.0;
	double flag4 = 0.0;
	for (i = 0; i < num; i++)
	{
		flag1 = flag1 + (*(*(arr_con + i) + 0)) * (*(*(arr_con + i) + 0)) * (*(*(arr_con + i) + 0));
	}
	flag1 = flag1 * num;
	for (i = 0; i < num; i++)
	{
		flag2 = flag2 + (*(*(arr_con + i) + 0))*(*(*(arr_con + i) + 1))*(*(*(arr_con + i) + 1));
	}
	flag2 = flag2 * num;
	for (i = 0; i < num; i++)
	{
		flag3 = flag3 + (*(*(arr_con + i) + 0));
	}
	for (i = 0; i < num; i++)
	{
		flag4 = flag4 + ((*(*(arr_con + i) + 0)) * (*(*(arr_con + i) + 0)) + (*(*(arr_con + i) + 1)) * (*(*(arr_con + i) + 1)));
	}
	double FIN = flag1 + flag2 - flag4*flag3;
	return FIN;
}

double H2(double(*arr_con)[2], int num)
{
	int i = 0;
	double flag1 = 0.0;
	double flag2 = 0.0;
	double flag3 = 0.0;
	double flag4 = 0.0;
	for (i = 0; i < num; i++)
	{
		flag1 = flag1 + (*(*(arr_con + i) + 1)) * (*(*(arr_con + i) + 1)) * (*(*(arr_con + i) + 1));
	}
	flag1 = flag1 * num;
	for (i = 0; i < num; i++)
	{
		flag2 = flag2 + (*(*(arr_con + i) + 0)) * (*(*(arr_con + i) + 0)) * (*(*(arr_con + i) + 1));
	}
	flag2 = flag2 * num;
	for (i = 0; i < num; i++)
	{
		flag3 = flag3 + (*(*(arr_con + i) + 1));
	}
	for (i = 0; i < num; i++)
	{
		flag4 = flag4 + ((*(*(arr_con + i) + 0)) * (*(*(arr_con + i) + 0)) + (*(*(arr_con + i) + 1)) * (*(*(arr_con + i) + 1)));
	}
	double FIN = flag1 + flag2 - flag4*flag3;
	return FIN;
}

double CC(double(*arr_con)[2], int num, double A, double B)
{
	int i = 0;
	double flag1 = 0.0;
	double flag2 = 0.0;
	for (i = 0; i < num; i++)
	{
		flag1 = flag1 + (*(*(arr_con + i) + 0)) * (*(*(arr_con + i) + 0)) + (*(*(arr_con + i) + 1)) * (*(*(arr_con + i) + 1)) + A*(*(*(arr_con + i) + 0)) + B*(*(*(arr_con + i) + 1));
	}
	flag2 = flag1*(-1.0) / double(num);
	return flag2;
}