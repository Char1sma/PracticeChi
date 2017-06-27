#include "Vect.h"



Vect::Vect(cv::Point point1, cv::Point point2)			//Конструктор №1. В качестве аргументов принимает начальную и конечную точки
{
	spoint = point1;
	epoint = point2;
}

Vect::Vect(int x1, int y1, int x2, int y2)			//Конструктор №2. В качестве аргументов принимает координаты начальной и конечной точек
{
	spoint = cv::Point(x1, y1);
	epoint = cv::Point(x2, y2);
}

Vect::Vect(double x1, double y1, double x2, double y2)//Конструктор №3. В качестве аргументов принимает координаты начальной и конечной точек,
{													  //после чего приводит их к типу int
	spoint = cv::Point((int)x1, (int)y1);
	epoint = cv::Point((int)x2, (int)y2);
}


Vect::~Vect()
{
}


Vect Vect::Base()								// Вектор той же длины и направления, выходящий из начала координат
{
	return Vect(0, 0, epoint.x - spoint.x, epoint.y - spoint.y);
}



NormVect Vect::Norm()							//Нормированный вектор
{
	NormVect temp;
	temp.x = (double)this->Base().epoint.x / this->Length();
	temp.y = (double)this->Base().epoint.y / this->Length();
	return temp;
}

void Vect::Move(cv::Point p)
{
	Vect temp = this->Base();
	spoint = p;
	epoint = cv::Point(p.x + temp.epoint.x, p.y + temp.epoint.y);
}

void Vect::ShowBase()							//Вывод базового вектора на экран
{
	std::cout << "(" << this->Base().epoint.x << "; " << this->Base().epoint.y << ")\n";
}


double Vect::Length()							//Длина вектора
{
	return sqrt(pow(this->Base().epoint.x, 2) + pow(this->Base().epoint.y, 2));
}

double Vect::th()
{
	return (double)(this->Base().epoint.y) / (double)(this->Base().epoint.x);
}

Vect operator*(double left, Vect right)
{
	return Vect(right.spoint.x*left, right.spoint.y*left, right.epoint.x*left, right.epoint.y*left);
}

Vect operator*(Vect left, double right)
{
	return Vect(left.spoint.x*right, left.spoint.y*right, left.epoint.x*right, left.epoint.y*right);
}

Vect operator+(Vect left, Vect right)
{
	return Vect(left.spoint,cv::Point(left.epoint.x+right.Base().epoint.x, left.epoint.y + right.Base().epoint.y));
}

Vect operator/(Vect left, double right)
{
	return Vect(left.spoint.x/ right, left.spoint.y/ right, left.epoint.x/ right, left.epoint.y/ right);
}
