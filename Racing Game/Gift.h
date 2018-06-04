# include "Point2D.h"
# pragma once

class CGift
{
protected:
	char type;
	CPoint2D pGift;
public:
	friend class CCar;
	void initGift();
	void outputGift();
	void addY();
	char getterGift();
	CGift();
};