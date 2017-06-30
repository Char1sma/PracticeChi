#include "Lib.h"

using namespace std;
using namespace cv;

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

namespace distortion
{

	double hyperb(double x, int a)
	{
		if (x >= 0 & x <= 0.9)
			return 1.0 / (a * x + 1);
		else
			return -10 / (0.9*(double)a + 1)*x + 10 / (0.9*(double)a + 1);
	}



	bool Change(Mat &base, Mat &img, list<Vect> VecList, int a)
	{
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
				Vect res = Vect(i, j, i, j);
				for (list<Vect>::iterator it = VecList.begin(); it != VecList.end(); it++)
				{
					Vect V = *it;
					if (V.epoint.x < 0 || V.epoint.y < 0 || V.spoint.x < 0 || V.spoint.y < 0 || V.epoint.x >= img.rows || V.epoint.y >= img.cols || V.spoint.x >= img.rows || V.spoint.y >= img.cols)
					{
						cout << "¬ектор задан некорректно";
						return false;
					}
					if (i != V.spoint.x || j != V.spoint.y)
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
						coeff = hyperb(coeff, a);
						res = res + (V * coeff);
					}
					else
					{
						res = res + V;
					}
				}
				B = base.at<Vec3b>(i, j)[0];
				G = base.at<Vec3b>(i, j)[1];
				R = base.at<Vec3b>(i, j)[2];
				if (res.epoint.x < img.rows && res.epoint.y < img.cols && res.epoint.x >= 0 && res.epoint.y >= 0)
				{
					img.at<Vec3b>(res.epoint.x, res.epoint.y)[0] = B;
					img.at<Vec3b>(res.epoint.x, res.epoint.y)[1] = G;
					img.at<Vec3b>(res.epoint.x, res.epoint.y)[2] = R;
					Changed[res.epoint.x][res.epoint.y] = true;
				}

			}
		//вот тут начинаетс€ заполнение битых точек
		int counter;
		for (int i = 0; i < img.rows; i++)
			for (int j = 0; j < img.cols; j++)
			{
				if (!Changed[i][j])
				{
					counter = 0;
					int step = 1;
					int B = 0;
					int G = 0;
					int R = 0;
					while (counter < 1)
					{
						for (int k = i - step; k <= i + step; k++)
							for (int l = j - step; l <= j + step; l++)
							{
								if (k > -1 && l > -1 && k < img.rows && l < img.cols && Changed[k][l])
								{
									counter++;
									B += img.at<Vec3b>(k, l)[0];
									G += img.at<Vec3b>(k, l)[1];
									R += img.at<Vec3b>(k, l)[2];

								}
							}

						step++;
					}
					B /= counter;
					G /= counter;
					R /= counter;
					img.at<Vec3b>(i, j)[0] = B;
					img.at<Vec3b>(i, j)[1] = G;
					img.at<Vec3b>(i, j)[2] = R;
				}
			}
		//а тут заканчиваетс€
		return true;
	}
}