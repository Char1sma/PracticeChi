#pragma once
#include <opencv2/core.hpp>
#include "Vect.h"
#include <iostream>

class Straight       //Прямая. Задаётся в каноническом виде ax+by+c=0
{
public:
	Straight(double c1, double c2, double c3);  //Конструкторы
	Straight(cv::Point p, Vect v);
	Straight(cv::Point point1, cv::Point point2);
	Straight(double k1, double k2);
	friend bool operator==(const Straight& left, const Straight& right);  //Параллельность прямых
	friend bool cross(Straight s1, Straight s2, cv::Point &p);
	double th();
	~Straight();
private:
	double a;		
	double b;		
	double c;
};

