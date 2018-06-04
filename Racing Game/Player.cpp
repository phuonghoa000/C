# include "Player.h"

int CPlayer::getterPoint()
{
	return point;
}

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(string s, int lv, int p)
{
	sName = s;
	level = lv;
	point = p;
}

CPlayer::~CPlayer(void)
{
}
