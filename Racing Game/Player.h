# include <string>
# pragma once
using namespace std;

class CPlayer
{
private:
	string sName;
	int level;
	int point;
public:
	friend class CListPlayer;
	int getterPoint();
	CPlayer();
	CPlayer(string, int, int);
	~CPlayer(void);
};

