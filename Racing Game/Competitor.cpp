# include "Competitor.h"

void CCompetitor::initCar()
{
	char c = -37;
	int x = 5 + rand() % 21;
	int y = -4;

	pCar.x = x;
	pCar.y = y;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			car[i][j] = c;
	car[0][1] = 32;
	car[2][1] = 32;
}

void CCompetitor::outputCar()
{
	for (int i = 0; i < 3; i++)
	{
		if (pCar.y + i >= 0 && pCar.y + i < 24)
		{
			gotoXY(pCar.x, pCar.y + i);
			textColor(9);
			for (int j = 0; j < 3; j++)
			{
				if (pCar.x + j == 16 && car[i][j] == 32)
				{
					char c = -37;
					textColor(7);
					cout << c;
					textColor(9);
				}
				else
					cout << car[i][j];

			}
		}
	}
}

int CCompetitor::getterY()
{
	return pCar.y;
}

void CCompetitor::setterY(int num)
{
	pCar.y = num;
}

void CCompetitor::addY()
{
	pCar.y++;
}

CCompetitor::CCompetitor()
{
	pCar.x = 5;
	pCar.y = 25;
}
