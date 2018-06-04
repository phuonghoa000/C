# pragma warning (disable: 4996)
# include "Competitor.h"
# include "Gift.h"
# pragma once

class CCar
{
protected:
	int type;
	char car[3][3];
	CPoint2D pCar;
	int level;
	int point;
	int power;
	char powerLine[25];
	char bullet;
	CPoint2D pBul;
public:
	virtual void initCar();
	virtual void outputCar();
	virtual void outputFullCar();
	int gotoPos();
	char getChar(int, int);
	bool collision(CCompetitor);
	void checkXY(CGift &);
	void addLevel();
	void addPoint(int);
	void addPower(int);
	int getterPoint();
	int getterLevel();
	int getterPower();
	void setterPoint(int);
	void setterLevel(int);
	void setterPower(int);
	void shooting();
	void invisibility();
	void micro();
	void outputInCar();
	void outputMicroCar();
	bool checkBullet(CCompetitor &);
	void recharge();
	virtual int getterTypeCar();
	CCar();
	CCar(CPoint2D);
};