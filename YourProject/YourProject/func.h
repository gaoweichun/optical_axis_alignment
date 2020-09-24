#define _CRT_SECURE_NO_WARNINGS
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>

using namespace std;
using namespace cv;

int Cornerdetect(const Mat& imgsrc, double(*arr_con)[2]);

int mould_left(const Mat& src, double(*arr_con)[2]);

int mould_right(const Mat& src, double(*arr_con)[2]);

int mould_up(const Mat& src, double(*arr_con)[2]);

int mould_down(const Mat& src, double(*arr_con)[2]);

void bubblesort_lr(double(*arr_con)[2], int num);

void bubblesort_ud(double(*arr_con)[2], int num);

void arr_sort_left_new(double(*arr_con)[2], double(*left1)[2], double(*left2)[2], int num, int &num1, int &num2);

void arr_sort_right_new(double(*arr_con)[2], double(*right1)[2], double(*right2)[2], int num, int &num1, int &num2);

void arr_sort_up_new(double(*arr_con)[2], double(*up1)[2], double(*up2)[2], int num, int &num1, int &num2);

void arr_sort_down_new(double(*arr_con)[2], double(*down1)[2], double(*down2)[2], int num, int &num1, int &num2);