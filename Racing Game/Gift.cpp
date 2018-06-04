# include "Gift.h"

void CGift::initGift()
{
	pGift.x = 5 + rand() % 23;
	pGift.y = 0;
	int temp = rand() % 10;
	if (temp < 8)
		type = 36;
	else
		type = 80;
}

void CGift::outputGift()
{
	if (pGift.y < 24)
	{
		gotoXY(pGift.x, pGift.y);
		if (pGift.x == 16)
			textColor(374);
		else
			textColor(6);
		cout << type;
	}
}

void CGift::addY()
{
	pGift.y++;
}

char CGift::getterGift()
{
	return type;
}

CGift::CGift()
{
	pGift.x = 5;
	pGift.y = 24;
}