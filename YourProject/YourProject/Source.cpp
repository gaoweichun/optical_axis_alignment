#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <time.h>

#include "YourLib.h"

#include <opencv2\opencv.hpp>


#include "hough.h"
#include "calmtf.h"
#include "coordinate.h"
#include "fillChart.h"
#include "ini.h"
#include "piancha.h"


using namespace cv;
using namespace std;



int main()
{


	// matlab ��ʼ��
	printf("Initia Application\n");
	if (!mclInitializeApplication(NULL, 0))
	{
		printf("Failed");
		_getch();
		return -1;
	}
	else
	{
		printf("Done\n");
	}

	printf("InitiaLi LIbra...");
	if (!YourLibInitialize())
	{
		printf("Failed");
		_getch();
		return -1;
	}
	else
	{
		printf("Done\n");
	}



	//clock_t start,houghStart,houghEnd,mtfStart,mtfEnd, end;
	//start = clock();

	

	//���������ļ�

	HOUGH h;
	MTF m;
	readConfig(&h, &m);

	// main code 
	/*����ͼƬ*/
	Mat src, src_gray;



	while (1)
	{
		char url[20];
		cout << "������ͼƬ��(exit�˳�)��  " << endl;
		cin >> url;

		if (!strcmp(url, "exit")) {     //����exit�����������
			return 0;
		}


	

		src = imread(url, 1);
		//src = imread("test.jpg", 1);


		//imshow("orange", src);
		if (!src.data)
		{
			cout << "fail to load image!" << endl;
		}

		if (!src.data)
		{
			continue;
			//return -1;
		}





		//houghStart = clock();

		Point *centers = houghCir(src, 16, h.minDist, h.param1, h.param2, h.minRadius, h.maxRadius);

		//houghEnd = clock();

		//������λ���ģ�����ƶ���������Ϊ�����������ƶ��������ƶ�
		int deltax = centers[8].x - 2048;
		int deltay = centers[8].y - 1080;
		//cout << "x = " << deltax << " " << "y= " << deltay << endl;
		//cout << "0.y   "<<centers[0].y << "   1.y   " << centers[1].y << endl;


		//�����ת��������Ϊ����������ת
		double angle = reviseCoor(centers);
		cout << "��ת�Ƕ� angle=" << angle << endl;
		//system("pause");
		Point distorCen = piancha( src);
		cout << "�������ģ� x= " << distorCen.x << "  y = " << distorCen.y << endl;
		//system("pause");
		//int zShift = fillChart(centers[6], centers[10]);
		//cout << "zShift " << zShift << endl;






		/*���ϴ��У���mtfʱ��Ϊ������mtfʱ�䣨0.65s��
		ȥ�����У���mtf����ʱ��Ϊ�����л�ʱ�������mtfʱ�䣨2.06s��
		*/


		/*for (int i = 0; i < 4; i++) {
			if (i < 2) {
				cout << i << "   " << centers[i].x << "  " << centers[i].y << endl;
			}
			else
			{
				cout << i+12 << "   " << centers[i+12].x << "  " << centers[i+12].y << endl;
			}

		}*/

		//system("pause");
		//Point distortCenter = piancha(src, centers[0], centers[1], centers[14], centers[15]);
		//system("pause");

		//mtfStart = clock();

		double * mtfRight = calRight(src, centers, m.xdistance, m.ydistance, m.width, m.high);

		//double * mtfLeft = calLeft(src, centers, m.xdistance,m.ydistance,m.width,m.high);



		namedWindow("Hough Circle Transform Demo", CV_WINDOW_NORMAL);
		imshow("Hough Circle Transform Demo", src);
		waitKey(0);


		//mtf50 ����
		//double mtf50[13];
		//int j = 0;
		//for (int i = 0; i < 16; i++) {
		//	if (i == 4 || i == 5 || i == 11)                //�����ʵ��Բ������
		//		continue;
		//	
		//	mtf50[j] = mtfRight[i];
		//	cout << mtf50[j] << endl;

		//	j += 1;
		//}


		free(mtfRight);
		//free(mtfLeft);

		//mtfEnd = clock();
		free(centers);




		//free(mtf50);




		//end = clock();
		/*printf("mtf time=%f\n", (double)(mtfEnd - mtfStart) / CLOCKS_PER_SEC);
		printf("hough time=%f\n", (double)(houghEnd - houghStart) / CLOCKS_PER_SEC);
		printf("total time=%f\n", (double)(end-start) / CLOCKS_PER_SEC);*/

		//matlab ���ý���
	}
	printf("terminating Library...");
	YourLibTerminate();
	printf("Done \n");


	printf("Termi  Application");
	if (!mclTerminateApplication())
	{
		printf("Failed !......");
		_getch();
		return -1;
	}
	else
	{
		printf("Done\n");
	}

	printf("\nPredd any key to continue ..");
	_getch;
	system("pause");

	return 0;

}
