# include "Point2D.h"
# pragma once

class CCompetitor
{
private:
	char car[3][3];
	CPoint2D pCar;
public:
	friend class CCar;
	friend class CTeamCompetitor;
	void initCar();
	void outputCar();
	int getterY();
	void setterY(int);
	void addY();
	CCompetitor();
	//CCompetitor(CPoint2D);
	//CCompetitor(int, int);
};
