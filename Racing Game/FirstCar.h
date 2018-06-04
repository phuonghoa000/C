# include "Car.h"
# pragma once

class CFirstCar : public CCar
{
public:
	void initCar();
	void outputCar();
	void outputFullCar();
	int getterTypeCar();
	CFirstCar(CPoint2D);
};

