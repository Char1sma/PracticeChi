#include <opencv2\core\core.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Vect.h"
#include "Straight.h"
#include <list>
#include <iterator>
#include "Lib.h"
#include <io.h>
#include <conio.h>
#include <Windows.h>

using namespace std;
using namespace cv;
using namespace distortion;


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	char filename[50];
	int n;
	bool exist = false;
	cout << "Введите название обрабатываемого файла>";
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (!exist)
	{
		cin >> filename;
		if (!access(filename, 0))
			exist = true;
		else
			cout << "Имя файла введено некорректно. Повторите ввод>";
	}
	Mat orig = imread(filename);
	Mat dst = imread(filename);
	IplImage *original = cvLoadImage(filename);
	IplImage *distorted;
	namedWindow("Оригинал", CV_WINDOW_AUTOSIZE);
	cvShowImage("Оригинал", original);
	namedWindow("Искажение", CV_WINDOW_AUTOSIZE);
	waitKey(1);
	//Вывод меню на экран
	char *action[6];
	char *subaction[3];
	list<Vect> VecList;
	action[0] = "Информация";
	action[1] = "Добавить вектор в список";
	action[2] = "Очистить список";
	action[3] = "Дополнительные возможности";
	action[4] = "Отрисовка";
	action[5] = "Выход";
	subaction[0] = "Просмотреть список векторов";
	subaction[1] = "Задать новый коэффициент кривой смещения";
	subaction[2] = "Назад";
	int flag = 0, subflag;
	int hcoeff = 200;
	bool breaking = false;
	bool back;
	Vect newVect = Vect(0, 0, 0, 0);
	while (!breaking)
	{
		cout << breaking << endl;
		system("cls");
		for (int i = 0; i < 6; i++)
		{
			if (i == flag)
				SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 14));
			cout << action[i] << endl;
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		}
		char c = getch();
		switch (c)
		{
		case 72:
			if (flag > 0)
				flag--;
			break;
		case 80:
			if (flag < 5)
				flag++;
			break;
		case 13:
			switch (flag)
			{
			case 0:
				system("cls");
				cout << filename << endl;
				printf("[i] channels:  %d\n", original->nChannels);
				printf("[i] pixel depth: %d bits\n", original->depth);
				printf("[i] width:       %d pixels\n", original->width);
				printf("[i] height:      %d pixels\n", original->height);
				printf("[i] image size:  %d bytes\n", original->imageSize);
				printf("[i] width step:  %d bytes\n", original->widthStep);
				getch();
				break;
			case 1:
				system("cls");
				int x1, x2, y1, y2;
				cout << "Введите координаты начальной точки\n";
				cin >> x1 >> y1;
				cout << "Введите координаты конечной точки\n";
				cin >> x2 >> y2;
				newVect = Vect(x1, y1, x2, y2);
				if (newVect.Length() > 0 && x1 >= 0 && x1 < orig.rows && x2 >= 0 && x2 < orig.rows && y1 >= 0 && y1 < orig.cols && y2 >= 0 && y2 < orig.cols)
					VecList.push_back(newVect);
				else
					cout << "Вектор задан некорректно!\n";
				getch();
				break;
			case 2:
				VecList.clear();
				break;
			case 3:
				back = false;
				subflag = 0;
				while (!back)
				{
				system("cls");
				for (int i = 0; i < 3; i++)
				{
					if (i == subflag)
						SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 14));
					cout << subaction[i] << endl;
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
				}
					char sc = getch();
					switch (sc)
					{
					case 72:
						if (subflag > 0)
							subflag--;
						break;
					case 80:
						if (subflag < 2)
							subflag++;
						break;
					case 13:
						switch (subflag)
						{
						case 0:
							system("cls");
							if (VecList.empty())
								cout << "Список пуст!";
							else
								for (list<Vect>::iterator it = VecList.begin(); it != VecList.end(); it++)
								{
									Vect V = *it;
									cout << "(" << V.spoint.x << ";" << V.spoint.y << ") -> (" << V.epoint.x << ";" << V.epoint.y << ")\n";
								}
							
							getch();
							break;
						case 1:
							system("cls");
							cout << "Текущее значение: " << hcoeff << endl;
							cout << "Рекомендуемое значение: 200" << endl;
							cout << "Новое значение> ";
							cin >> n;
							if (n <= 0)
								cout << "Некорректный коэффициент!";
							else
								hcoeff = n;
							getch();
							break;
						case 2:
							back = true;
							break;
						default:
							break;
						}
						break;
					default:
						break;
					}
				}
				break;
			case 4:
				Change(orig, dst, VecList, hcoeff);
				imwrite("Changed.jpg", dst);
				distorted = cvLoadImage("Changed.jpg");
				cvShowImage("Искажение", distorted);
				VecList.clear();
				waitKey(0);
				break;
			case 5:
				breaking = true;
				break;
			}
			break;
		default:
			break;
		}
	}
	cvDestroyWindow("Оригинал");
	cvDestroyWindow("Искажение");
	return 0;
}
