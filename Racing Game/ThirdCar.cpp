# include "ThirdCar.h"

void CThirdCar::initCar()
{
	car[0][0] = 15;
	car[0][1] = 30;
	car[0][2] = 15; 
	car[1][0] = 15;
	car[1][1] = 88;
	car[1][2] = 15;
	car[2][0] = 15;
	car[2][1] = -51;
	car[2][2] = 15;
}

void CThirdCar::outputCar()
{
	if (car[0][1] == -51)
		this->outputInCar();
	else if (car[1][1] == 111)
		this->outputMicroCar();
	else
	{
		gotoXY(pCar.x, pCar.y);

		if (pCar.x == 16)
			textColor(379);
		else
			textColor(11);
		cout << car[0][0];
	
		if (pCar.x == 15)
			textColor(378);
		else
			textColor(10);
		cout << car[0][1];
	
		if (pCar.x == 14)
			textColor(379);
		else
			textColor(11);
		cout << car[0][2];
	
		gotoXY(pCar.x, pCar.y + 1);
	
		if (pCar.x == 16)
			textColor(379);
		else
			textColor(11);
		cout << car[1][0];
	
		if (pCar.x == 15)
			textColor(380);
		else
			textColor(12);
		cout << car[1][1];
	
		if (pCar.x == 14)
			textColor(379);
		else
			textColor(11);
		cout << car[1][2];
	
		gotoXY(pCar.x, pCar.y + 2);
	
		if (pCar.x == 16)
			textColor(379);
		else
			textColor(11);
		cout << car[2][0];
	
		if (pCar.x == 15)
			textColor(378);
		else
			textColor(10);
		cout << car[2][1];
	
		if (pCar.x == 14)
			textColor(379);
		else
			textColor(11);
		cout << car[2][2];
	}

	if (pBul.y >= 0)
	{
		if (pBul.x == 16)
			textColor(380);
		else
			textColor(12);
		gotoXY(pBul.x, pBul.y);
		cout << bullet;
		pBul.y--;
	}
}

void CThirdCar::outputFullCar()
{
	this->outputCar();

	textColor(12);
	gotoXY(4, 24);
	int carry = (power + 39) / 40;
	
	for (int i = 0; i < carry; i++)
		cout << powerLine[i];
	
	textColor(7);
	for (int i = carry; i < 25; i++)
		cout << powerLine[i];
	cout << "    ";

	gotoXY(50, 14);
	cout << level << "    ";
	gotoXY(50, 16);
	cout << point << "    ";
	gotoXY(50, 18);
	cout << power << "    ";
}

int CThirdCar::getterTypeCar()
{
	return type;
}

CThirdCar::CThirdCar(CPoint2D p)
{
	type = 3;
	bullet = 33;
	pCar = p;
	level = 1;
	point = 0;
	power = 1000;
	pBul.y = -1;
	pBul.x = pCar.x + 1;
	for (int i = 0; i < 25; i++)
		powerLine[i] = -37;
}