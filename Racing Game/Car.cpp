#include "Car.h"

void CCar::initCar()
{
}

void CCar::outputCar()
{
}

void CCar::outputFullCar()
{
}

int CCar::gotoPos()
{
	if (kbhit())
	{
		char key;
	
		key = getch();

		if (key == 27)
			return 27;

		if (key == 65 || key == 97)
		{
			char m[3][15] = { };
			string s;

			for (int i = 0; i < 3; i = i + 2)
				for (int j = 0; j < 15; j++)
					m[i][j] = -51;

			m[1][0] = -70;
			m[1][14] = -70;
			m[0][0] = -55;
			m[0][14] = -69;
			m[2][0] = -56;
			m[2][14] = -68;
			
			s = "PAUSE";
			for (int i = 0; i < 5; i++)
				m[1][i + 5] = s[i];
			
			for (int i = 0; i < 3; i++)
			{
				gotoXY(9, 10 + i);
				for (int j = 0; j < 15; j++)
					cout << m[i][j];
			}
			do
			{
				key = getch();
			}
			while (key != 65 && key != 97 && key != 27);

			if (key == 65 || key == 97)
				return 1;
			if (key == 27)
				return 27;
		}
		
		if (key == 87 || key == 119)
		{
			this->recharge();
			return 1;
		}
		
		if (power == 0)
			return 0;
		
		if (key == 32)
		{
			power--;
			this->shooting();
			return 1;
		}
		
		if ((key == 69 || key == 101) && car[0][1] != -51 && car[1][1] != 111)
		{
			if (power >= 100)
			{
				power = power - 100;
				this->invisibility();
			}
			return 2;
		}

		if ((key == 82 || key == 114) && car[1][1] != 111 && car[0][1] != -51)
		{
			if (power >= 100)
			{
				power = power - 100;
				this->micro();
			}
			return 3;
		}

		if (key == -32)
		{
			key = getch();
			power--;

			if (key == 72)
				pCar.y--;
			if (pCar.y < 0)
			{
				pCar.y++;
				return 1;
			}

			if (key == 80)
				pCar.y++;
			if (pCar.y > 21)
			{
				pCar.y--;
				return 1;
			}

			if (key == 77)
				pCar.x++;
			if (pCar.x > 25)
			{
				pCar.x--;
				return 1;
			}

			if (key == 75)
				pCar.x--;
			if (pCar.x < 5)
			{
				pCar.x++;
				return 1;
			}
			return 1;
		}
		return 1;
	}
	return 1;
}

char CCar::getChar(int row, int column)
{
	return car[row][column];
}

bool CCar::collision(CCompetitor com)
{
	if (car[1][1] == 111)
	{
		if (pCar.x + 1 == com.pCar.x || pCar.x - 1 == com.pCar.x)
			if (pCar.y + 1 >= com.pCar.y && pCar.y - 1 <= com.pCar.y)
				return true;
		if (pCar.x == com.pCar.x && pCar.y == com.pCar.y)
			return true;
		return false;
	}
	else
	{
		if (pCar.x + 2 >= com.pCar.x && pCar.x - 2 <= com.pCar.x)
		{
			if (pCar.y - 2 == com.pCar.y)
				return true;
			if (pCar.y + 2 == com.pCar.y)
				return true;
		}
		if (pCar.y + 2 >= com.pCar.y && pCar.y - 2 <= com.pCar.y)
		{
			if (pCar.x - 2 == com.pCar.x)
				return true;
			if (pCar.x + 2 == com.pCar.x)
				return true;
		}
	}

	return false;
}

void CCar::checkXY(CGift &g)
{
	if (pCar.x <= g.pGift.x && pCar.x + 2 >= g.pGift.x)
	{
		if (pCar.y <= g.pGift.y && pCar.y >= g.pGift.y)
		{
			if (g.type == 36)
				this->addPoint(1);
			else
				this->addPower(10);
			g.pGift.y = 24;
			g.type = 32;
		}
	}
}

void CCar::addLevel()
{
	level++;
}

void CCar::addPoint(int num)
{
	point = point + num;
}

void CCar::addPower(int num)
{
	power = power + num;
}

int CCar::getterPoint()
{
	return point;
}

int CCar::getterLevel()
{
	return level;
}

int CCar::getterPower()
{
	return power;
}

void CCar::setterPoint(int p)
{
	point = p;
}

void CCar::setterLevel(int lv)
{
	level = lv;
}

void CCar::setterPower(int p)
{
	power = p;
}

void CCar::shooting()
{
	if (pBul.y < 0)
	{
		pBul.x = pCar.x + 1;
		pBul.y = pCar.y - 1;
	}
}

void CCar::invisibility()
{
	car[0][0] = -55;
	car[0][1] = -51;
	car[0][2] = -69; 
	car[1][0] = -70;
	car[1][1] = 88;
	car[1][2] = -70;
	car[2][0] = -56;
	car[2][1] = -51;
	car[2][2] = -68;
}

void CCar::micro()
{
	car[0][1] = 32;
	car[1][1] = 111;
}

void CCar::outputInCar()
{
	gotoXY(pCar.x, pCar.y);

	if (pCar.x == 16)
		textColor(378);
	else
		textColor(2);
	cout << car[0][0];
	
	if (pCar.x == 15)
		textColor(378);
	else
		textColor(2);
	cout << car[0][1];
	
	if (pCar.x == 14)
		textColor(378);
	else
		textColor(2);
	cout << car[0][2];
	
	gotoXY(pCar.x, pCar.y + 1);
	
	if (pCar.x == 16)
		textColor(378);
	else
		textColor(2);
	cout << car[1][0];
	
	if (pCar.x == 15)
		textColor(380);
	else
		textColor(12);
	cout << car[1][1];
	
	if (pCar.x == 14)
		textColor(378);
	else
		textColor(2);
	cout << car[1][2];
	
	gotoXY(pCar.x, pCar.y + 2);
	
	if (pCar.x == 16)
		textColor(378);
	else
		textColor(2);
	cout << car[2][0];
	
	if (pCar.x == 15)
		textColor(378);
	else
		textColor(2);
	cout << car[2][1];
	
	if (pCar.x == 14)
		textColor(378);
	else
		textColor(2);
	cout << car[2][2];
}

void CCar::outputMicroCar()
{
	gotoXY(pCar.x + 1, pCar.y + 1);
	if (pCar.x == 15)
		textColor(380);
	else
		textColor(12);
	cout << car[1][1];
}

bool CCar::checkBullet(CCompetitor &com)
{
	if (pBul.y > 0 && com.pCar.y > 0)
	{
		if ((pBul.x == com.pCar.x || pBul.x - 2 == com.pCar.x) && (pBul.y - 2 == com.pCar.y || pBul.y - 1 == com.pCar.y))
		{
			pBul.y = -1;
			com.pCar.y = 24;
			return true;
		}
		if ((pBul.x - 1 == com.pCar.x) && (pBul.y - 1 == com.pCar.y || pBul.y == com.pCar.y))
		{
			pBul.y = -1;
			com.pCar.y = 24;
			return true;
		}
		return false;
	}
	return false;
}

void CCar::recharge()
{
	if (power < 500)
	{
		int temp = 1000 - power;
		if (point >= temp)
		{
			point = point - temp;
			power = 1000;
		}
		else
		{
			power = power + point;
			point = 0;
		}
	}
}

int CCar::getterTypeCar()
{
	return 0;
}

CCar::CCar()
{
}

CCar::CCar(CPoint2D)
{
}