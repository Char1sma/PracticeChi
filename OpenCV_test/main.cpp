#include <opencv2\core\core.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Vect.h"
#include "Straight.h"

using namespace std;
using namespace cv;

double hyperb(double x)
{
	return 1.0 / (100 * x + 1);
}

double func(double x)
{
	if (x >= 0.2)
		return (-pow(10 * x - 2, 1. / 3) + 2) / (2 + pow(2, 1. / 3));
	else
		return (pow(2 - 10 * x, 1. / 3) + 2) / (2 + pow(2, 1. / 3));
}


bool Change(Mat &base, Mat &img, Vect V)
{
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
		{
			img.at<Vec3b>(i, j)[0] = 0;
			img.at<Vec3b>(i, j)[1] = 0;
			img.at<Vec3b>(i, j)[2] = 0;
		}

	

	double coeff;
	Straight *S1[4];
	S1[0] = new Straight(Point(0, 0), Point(0, img.cols));
	S1[1] = new Straight(Point(0, 0), Point(img.rows, 0));
	S1[2] = new Straight(Point(img.rows, 0), Point(img.rows, img.cols));
	S1[3] = new Straight(Point(0, img.cols), Point(img.rows, img.cols));
	int R, G, B;
	vector<vector<bool>> Changed;
	Changed.resize(img.rows);
	for (int i = 0; i < Changed.size(); i++)
	{
		Changed[i].resize(img.cols);
		for (int j = 0; j < Changed[i].size(); j++)
			Changed[i][j] = false;
	}
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
		{
			
			if (i != V.spoint.x||j != V.spoint.y)
			{
				
				Straight S = Straight(V.spoint, Point(i, j));
				
				int k = 0;
				bool stop = false;			
				while ((k < 4) && !stop)
				{
					Point temp;
					bool b = cross(S, *S1[k], temp);
					if (b)
						if (temp.x >= 0 && temp.x <= img.rows&&temp.y >= 0 && temp.y <= img.cols&&Vect(Point(i, j), temp).Length() < Vect(V.spoint, temp).Length())
						{
							coeff = Vect(Point(i, j), temp).Length() / Vect(V.spoint, temp).Length();
							stop = true;
						}
					k++;
				}
				img.at<Vec3b>(i, j)[2] = 255;
				cout << coeff << endl;
				//cout << func(coeff) << endl;
				coeff = hyperb(coeff);
				Vect res = V * coeff;
				res.Move(cv::Point(i, j));
				B = base.at<Vec3b>(i, j)[0];
				G = base.at<Vec3b>(i, j)[1];
				R = base.at<Vec3b>(i, j)[2];
				/*if (res.epoint.x <= img.rows&&res.epoint.y <= img.cols)
				{
					img.at<Vec3b>(res.epoint.x, res.epoint.y)[0] = 255;
					img.at<Vec3b>(res.epoint.x, res.epoint.y)[1] = 0;
					img.at<Vec3b>(res.epoint.x, res.epoint.y)[2] = 0;
				}*/
				//res.ShowBase();
			}
		}

	

	
	return true;
}

IplImage* image = 0;
IplImage* dst = 0;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");

	char* filename = "test.jpg";

	image = cvLoadImage(filename, 1);
	dst = cvCloneImage(image);

	printf("[i] image: %s\n", filename);
	assert(image != 0);

	cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("new", CV_WINDOW_AUTOSIZE);


	cvShowImage("original", image);

	Mat img = imread(filename);
	Mat img1 = imread(filename);	
	
	Vect mainvec = Vect(Point(50, 50), Point(100, 100));
	Change(img1, img, mainvec);
	imwrite("test1.jpg", img);
	dst = cvLoadImage("test1.jpg", 1);
	cvShowImage("new", dst);
	/*printf("[i] channels:  %d\n", image->nChannels);
	printf("[i] pixel depth: %d bits\n", image->depth);
	printf("[i] width:       %d pixels\n", image->width);
	printf("[i] height:      %d pixels\n", image->height);
	printf("[i] image size:  %d bytes\n", image->imageSize);
	printf("[i] width step:  %d bytes\n", image->widthStep);*/
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvReleaseImage(&dst);
	cvDestroyWindow("original");
	cvDestroyWindow("new");
	return 0;
}