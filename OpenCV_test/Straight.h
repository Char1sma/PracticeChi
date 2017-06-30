#pragma once
#include <opencv2/core.hpp>
#include "Vect.h"
#include <iostream>

class Straight       //Прямая. Задаётся в каноническом виде ax+by+c=0
{
public:
	//Конструктор №1. Параметры - коэффициенты канонического уравнения	
	Straight(double c1, double c2, double c3); 
	//Конструктор №2. Параметры - одна из точек и направление прямой
	Straight(cv::Point p, Vect v);
	//Конструктор №3. Параметры - 2 точки, лежащие на прямой
	Straight(cv::Point point1, cv::Point point2);
	//Конструктор №4. Параметры - коэффициенты уравнения y=k1*x+k2
	Straight(double k1, double k2);
	//Параллельность прямых
	friend bool operator==(const Straight& left, const Straight& right); 
	//Пересечение прямых (возвращает false, если прямые параллельны)
	//Аргументы:
	// 1) Две прямые, точку пересечения которых мы ищем.
	// 2) Объект "точка", куда необходимо поместить результат вычислений.
	friend bool cross(Straight s1, Straight s2, cv::Point &p);
	//Тангенс угла наклона прямой к оси х.
	double th();
	~Straight();
private:
	//Параметры канонического уравнения
	double a;		
	double b;		
	double c;
};

