#pragma once

#include <opencv2\core.hpp>
#include <iostream>
#include <math.h>

struct NormVect
{
	double x;
	double y;
};

class Vect
{
public:
	Vect(cv::Point point1, cv::Point point2);			//Конструкторы
	Vect(int x1, int y1, int x2, int y2);
	Vect(double x1, double y1, double x2, double y2);
	~Vect();
	Vect Base();
	cv::Point spoint;		//Начальная точка
	cv::Point epoint;		//Конечная точка
	friend Vect operator *(double left, Vect right);   //Перегрузки
	friend Vect operator *(Vect left, double right);
	friend Vect operator +(Vect left, Vect right);
	friend Vect operator /(Vect left, double right);
	NormVect Norm();
	void Move(cv::Point p);
	void ShowBase();
	double Length();
	double th();
};


