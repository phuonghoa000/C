# include "system.h"
# include "Player.h"
# include "Point2D.h"
# include <iostream>
# include <fstream>
# include <vector>
# pragma once

class CListPlayer
{
private:
	vector<CPlayer> L;
public:
	void readFileHighScore(const char*);
	void writeFileHighScore(const char*);
	void insertPlayer(CPlayer);
	void outputPlayer(int, CPoint2D);
	int getterPlayer(int);
	CListPlayer(void);
	~CListPlayer(void);
};

