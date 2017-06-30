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
	//Конструктор №1. В качестве аргументов принимает начальную и конечную точки
	Vect(cv::Point point1, cv::Point point2);
	//Конструктор №2. В качестве аргументов принимает координаты начальной и конечной точек
	Vect(int x1, int y1, int x2, int y2);
	//Конструктор №3. В качестве аргументов принимает координаты начальной и конечной точек, после чего приводит их к типу int
	Vect(double x1, double y1, double x2, double y2);
	~Vect();
	// Вектор той же длины и направления, выходящий из начала координат
	Vect Base();
	cv::Point spoint;		//Начальная точка
	cv::Point epoint;		//Конечная точка
	friend Vect operator *(double left, Vect right);   //Перегрузки
	friend Vect operator *(Vect left, double right);
	friend Vect operator +(Vect left, Vect right);
	friend Vect operator /(Vect left, double right);
	//Нормированный вектор
	NormVect Norm();
	//Переместить вектор в заданную точку
	void Move(cv::Point p);
	//Вывод базового вектора на экран
	void ShowBase();
	//Длина вектора
	double Length();
	//Тангенс угла наклона к оси х
	double th();
};


