# include "Point2D.h"

void CPoint2D::setterPoint(int x1, int y1)
{
	x = x1;
	y = y1;
}

int CPoint2D::getterX()
{
	return x;
}

int CPoint2D::getterY()
{
	return y;
}

void CPoint2D::setterX(int x1)
{
	x = x1;
}

void CPoint2D::setterY(int y1)
{
	y = y1;
}

CPoint2D::CPoint2D()
{
	x = 5;
	y = 24;
}

CPoint2D::CPoint2D(int x1, int y1)
{
	x = x1;
	y = y1;
}