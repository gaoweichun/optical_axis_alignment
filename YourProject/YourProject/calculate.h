#define _CRT_SECURE_NO_WARNINGS
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>

using namespace std;
using namespace cv;

double M11(double(*arr_con)[2], int num);

double M22(double(*arr_con)[2], int num);

double M12(double(*arr_con)[2], int num);

double H1(double(*arr_con)[2], int num);

double H2(double(*arr_con)[2], int num);

double CC(double(*arr_con)[2], int num, double A, double B);
