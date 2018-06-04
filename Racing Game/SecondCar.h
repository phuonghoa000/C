# include "Car.h"
# pragma once

class CSecondCar : public CCar
{
public:
	void initCar();
	void outputCar();
	void outputFullCar();
	int getterTypeCar();
	CSecondCar(CPoint2D);
};
