# include "ListPlayer.h"

void CListPlayer::readFileHighScore(const char* fName)
{
	fstream f;
	f.open(fName, ios_base::in);

	if (f != NULL)
	{
		int n;
		CPlayer temp;
		L.resize(0);

		f >> n;
		for (int i = 0; i < n; i++)
		{
			getline(f, temp.sName, ',');
			f >> temp.level;
			f >> temp.point;
			L.push_back(temp);
		}

		for (int i = 0; i < n; i++)
			L[i].sName.erase(0, 1);

		f.close();
	}
}

void CListPlayer::writeFileHighScore(const char* fName)
{
	fstream f;

	f.open(fName, ios_base::out);
	f << L.size() << endl;
	for (unsigned int i = 0; i < L.size(); i++)
		f << L[i].sName << ", " << L[i].level << " " << L[i].point << endl;

	f.close();
}


void CListPlayer::insertPlayer(CPlayer pl)
{
	L.push_back(pl);
	int pos = 0;
	for (unsigned int i = 0; i < 9; i++)
	{
		if (pl.point <= L[i].point && pl.point > L[i + 1].point)
		{
			pos = i + 1;
			break;
		}
	}
	for (int i = 10; i > pos; i--)
		L[i] = L[i - 1];
	L[pos] = pl;
}

void CListPlayer::outputPlayer(int pos, CPoint2D p)
{
	int x = p.getterX();
	int y = p.getterY();
	gotoXY(x, y);
	cout << L[pos].sName;
	gotoXY(x + 17, y);
	cout << L[pos].level;
	gotoXY(x + 27, y);
	cout << L[pos].point;
}

int CListPlayer::getterPlayer(int pos)
{
	return L[pos].getterPoint();
}

CListPlayer::CListPlayer(void)
{
}


CListPlayer::~CListPlayer(void)
{
}
