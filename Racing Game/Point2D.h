# include "system.h"
# include <iostream>
# include <cstdlib>
# include <ctime>
# include <conio.h>
# pragma once
using namespace std;

class CPoint2D
{
private:
	int x;
	int y;
public:
	friend class CGift;
	friend class CCar;
	friend class CFirstCar;
	friend class CSecondCar;
	friend class CThirdCar;
	friend class CCompetitor;
	friend class CListPlayer;
	void setterPoint(int, int);
	int getterX();
	int getterY();
	void setterX(int);
	void setterY(int);
	CPoint2D();
	CPoint2D(int, int);
};
