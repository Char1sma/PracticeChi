#include "Straight.h"



Straight::Straight(double c1,double c2, double c3)	
{
	a = c1;
	b = c2;
	c = c3;
}

Straight::Straight(cv::Point p, Vect v)			
{
	cv::Point temp = cv::Point(v.Base().epoint.x+p.x, v.Base().epoint.y+p.y);
	a = -v.Base().epoint.y;
	b = v.Base().epoint.x;
	c = p.x*temp.y - temp.x*p.y;
}

Straight::Straight(cv::Point point1, cv::Point point2)	
{
	a = point1.y - point2.y;
	b = point2.x - point1.y;
	c = point1.x*point2.y - point2.x*point1.y;
}

Straight::Straight(double k1, double k2)				
{
	a = -k1;
	b = 1;
	c = -k2;
}



double Straight::th()
{
	return (double)(-2 * a) / (double)(b);
}

Straight::~Straight()
{
}

bool operator==(const Straight & left, const Straight & right)
{
	
	if ((left.a == 0 && left.b == 0) || (right.a == 0 && right.b == 0))
	{
		return false;
	}
	else
		return ((right.a*left.b - left.a*right.b) == 0);

}

bool cross(Straight s1, Straight s2, cv::Point & p)
{
	if (s1==s2)
		return false;
	else
	{
		int x = -(s1.c*s2.b - s2.c*s1.b) / (s1.a*s2.b - s2.a*s1.b);
		int y = -(s1.a*s2.c - s2.a*s1.c) / (s1.a*s2.b - s2.a*s1.b);
		p.x = x;
		p.y = y;
		return true;
	}
}

