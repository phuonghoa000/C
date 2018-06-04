# include "Car.h"
# pragma once

class CThirdCar : public CCar
{
public:
	void initCar();
	void outputCar();
	void outputFullCar();
	int getterTypeCar();
	CThirdCar(CPoint2D);
};

