# include "control.h"

void createMenuSelection_1(char m[][50])
{
	string s;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			m[i][j] = 32;
			if (i % 2 == 0)
				m[i][j] = -51;
			if (j == 0 || j == 19)
			{
				m[i][j] = -70;
				if (i > 1 && i < 9 && i % 2 == 0)
				{
					if (j == 0)
						m[i][j] = -52;                                                                                 
					else
						m[i][j] = -71;
				}
			}
		}
	}

	m[0][0] = -55;
	m[0][19] = -69;
	m[8][0] = -56;
	m[8][19] = -68;

	s = "NEW GAME";
	for (int i = 0; i < 8; i++)
		m[1][i + 6] = s[i];
	s = "HIGH SCORE";
	for (int i = 0; i < 10; i++)
		m[3][i + 5] = s[i];
	s = "OPTION";
	for (int i = 0; i < 6; i++)
		m[5][i + 7] = s[i];
	s = "EXIT";
	for (int i = 0; i < 4; i++)
		m[7][i + 8] = s[i];
}

void createMenuSelection_2(char m[][50])
{
	string s;

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			m[i][j] = 32;
			if (i % 2 == 0)
				m[i][j] = -51;
			if (j == 0 || j == 19)
			{
				m[i][j] = -70;
				if (i > 1 && i < 9 && i % 2 == 0)
				{
					if (j == 0)
						m[i][j] = -52;                                                                                 
					else
						m[i][j] = -71;
				}
			}
		}
	}

	m[0][0] = -55;
	m[0][19] = -69;
	m[10][0] = -56;
	m[10][19] = -68;

	s = "CONTINUE";
	for (int i = 0; i < 8; i++)
		m[1][i + 6] = s[i];
	s = "NEW GAME";
	for (int i = 0; i < 8; i++)
		m[3][i + 6] = s[i];
	s = "HIGH SCORE";
	for (int i = 0; i < 10; i++)
		m[5][i + 5] = s[i];
	s = "OPTION";
	for (int i = 0; i < 6; i++)
		m[7][i + 7] = s[i];
	s = "EXIT";
	for (int i = 0; i < 4; i++)
		m[9][i + 8] = s[i];
}

void createMenuExit(char m[][50])
{
	string s;

	for (int i = 0; i < 4; i = i + 3)
		for (int j = 0; j < 33; j++)
			m[i][j] = -51;

	m[1][0] = -70;
	m[2][0] = -70;
	m[1][32] = -70;
	m[2][32] = -70;
	m[0][0] = -55;
	m[0][32] = -69;
	m[3][0] = -56;
	m[3][32] = -68;

	s = "Do you want to save game? Y/N";
	for (unsigned int i = 0; i < s.length(); i++)
		m[1][i + 2] = s[i];
}

void createMenuHighScore(char m[][50])
{
	string s;

	for (int i = 0; i < 25; i = i + 24)
		for (int j = 0; j < 42; j++)
			m[i][j] = -51;

	for (int i = 0; i < 25; i++)
		for (int j = 0; j < 42; j = j + 41)
			m[i][j] = -70;

	m[0][0] = -55;
	m[0][41] = -69;
	m[24][0] = -56;
	m[24][41] = -68;

	s = "  HIGH SCORE  ";
	for (int i = 0; i < 14; i++)
		m[0][i + 14] = s[i];
	s = "NAME";
	for (int i = 0; i < 4; i++)
		m[2][i + 5] = s[i];

	s = "LEVEL";
	for (int i = 0; i < 5; i++)
		m[2][i + 22] = s[i];
	
	s = "POINT";
	for (int i = 0; i < 5; i++)
		m[2][i + 32] = s[i];
	
	for (int i = 0; i < 9; i++)
		m[2*i + 4][2] = i + 49;

	m[22][2] = 49;
	m[22][3] = 48;
}

void createControlPanel(char m[][50])
{
	string s;

	for (int i = 0; i < 13; i = i + 12)
		for (int j = 0; j < 40; j++)
			m[i][j] = -51;

	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 40; j = j + 39)
			m[i][j] = -70;

	m[0][0] = -55;
	m[0][39] = -69;
	m[12][0] = -56;
	m[12][39] = -68;

	s = "Exit (thoat): ESC";
	for (unsigned int i = 0; i < s.length(); i++)
		m[1][i + 3] = s[i];
	s = "Pause (dung choi): A";
	for (unsigned int i = 0; i < s.length(); i++)
		m[3][i + 3] = s[i];
	s = "Recharge (nap nang luong): W";
	for (unsigned int i = 0; i < s.length(); i++)
		m[5][i + 3] = s[i];
	s = "Invisibility (xe tang hinh): E";
	for (unsigned int i = 0; i < s.length(); i++)
		m[7][i + 3] = s[i];
	s = "Micro (xe ti hon): R";
	for (unsigned int i = 0; i < s.length(); i++)
		m[9][i + 3] = s[i];
	s = "Shooting (ban sung): SPACE";
	for (unsigned int i = 0; i < s.length(); i++)
		m[11][i + 3] = s[i];
}

void createResultTable(char m[][50])
{
	string s;

	for (int i = 0; i < 7; i = i + 6)
		for (int j = 0; j < 40; j++)
			m[i][j] = -51;

	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 40; j = j + 39)
			m[i][j] = -70;

	m[0][0] = -55;
	m[0][39] = -69;
	m[6][0] = -56;
	m[6][39] = -68;

	s = "Level: ";
	for (int i = 0; i < 7; i++)
		m[1][i + 3] = s[i];
	s = "Point: ";
	for (int i = 0; i < 7; i++)
		m[3][i + 3] = s[i];
	s = "Power: ";
	for (int i = 0; i < 7; i++)
		m[5][i + 3] = s[i];
}

void createNameTable(char m[][50])
{
	string s;

	for (int i = 0; i < 4; i = i + 3)
		for (int j = 0; j < 30; j++)
			m[i][j] = -51;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 30; j = j + 29)
			m[i][j] = -70;

	m[0][0] = -55;
	m[0][29] = -69;
	m[3][0] = -56;
	m[3][29] = -68;

	s = "Please enter your name!";
	for (unsigned int i = 0; i < s.length(); i++)
		m[1][i + 2] = s[i];
}

void createMenuChoiceCar(char m[][50])
{
	string s;

	for (int i = 0; i < 15; i = i + 14)
		for (int j = 0; j < 42; j++)
			m[i][j] = -51;

	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 42; j = j + 41)
			m[i][j] = -70;

	m[0][0] = -55;
	m[0][41] = -69;
	m[14][0] = -56;
	m[14][41] = -68;

	s = "Please, choice your car!";
	for (unsigned int i = 0; i < s.length(); i++)
		m[2][i + 9] = s[i];
	
	s = "Ferrari";
	for (unsigned int i = 0; i < s.length(); i++)
		m[12][i + 5] = s[i];

	s = "Toyota";
	for (unsigned int i = 0; i < s.length(); i++)
		m[12][i + 18] = s[i];
	
	s = "Mercedes";
	for (unsigned int i = 0; i < s.length(); i++)
		m[12][i + 29] = s[i];
}

void createMicroMenu(char m[][50])
{
	for (int i = 0; i < 7; i = i + 6)
		for (int j = 0; j < 7; j++)
			m[i][j] = -51;

	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j = j + 6)
			m[i][j] = -70;

	m[0][0] = -55;
	m[0][6] = -69;
	m[6][0] = -56;
	m[6][6] = -68;
}

void createGuideTable(char m[][50])
{
	string s;

	for (int i = 0; i < 25; i = i + 24)
		for (int j = 0; j < 50; j++)
			m[i][j] = -51;

	for (int i = 0; i < 25; i++)
		for (int j = 0; j < 50; j = j + 49)
			m[i][j] = -70;

	m[0][0] = -55;
	m[0][49] = -69;
	m[24][0] = -56;
	m[24][49] = -68;

	s = "  GUIDE TABLE  ";
	for (int i = 0; i < 15; i++)
		m[0][i + 18] = s[i];

	s = "BUTTON      FUNCTION";
	for (unsigned int i = 0; i < s.length(); i++)
		m[2][i + 3] = s[i];

	s = "ESC         exit (thoat khoi game)";
	for (unsigned int i = 0; i < s.length(); i++)
		m[4][i + 3] = s[i];

	s = "A           pause (tam dung game)";
	for (unsigned int i = 0; i < s.length(); i++)
		m[6][i + 3] = s[i];

	s = "W           recharge (nap nang luong cho xe)";
	for (unsigned int i = 0; i < s.length(); i++)
		m[8][i + 3] = s[i];

	s = "E           invisibility (giup xe tang hinh)";
	for (unsigned int i = 0; i < s.length(); i++)
		m[10][i + 3] = s[i];

	s = "R           micro (thu nho kich thuoc xe)";
	for (unsigned int i = 0; i < s.length(); i++)
		m[12][i + 3] = s[i];

	s = "SPACE       shooting (ban sung)";
	for (unsigned int i = 0; i < s.length(); i++)
		m[14][i + 3] = s[i];

	s = "UP          move up (di chuyen len tren)";
	for (unsigned int i = 0; i < s.length(); i++)
		m[16][i + 3] = s[i];

	s = "DOWN        move down (di chuyen xuong duoi)";
	for (unsigned int i = 0; i < s.length(); i++)
		m[18][i + 3] = s[i];

	s = "RIGHT       move right (di chuyen sang phai)";
	for (unsigned int i = 0; i < s.length(); i++)
		m[20][i + 3] = s[i];

	s = "LEFT        move left (di chuyen sang trai)";
	for (unsigned int i = 0; i < s.length(); i++)
		m[22][i + 3] = s[i];

}

void outputMenuHighScore(char c[][50])
{
	CListPlayer List;

	gotoXY(0, 0);
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 42; j++)
			cout << c[i][j];
		cout << endl;
	}

	textColor(7);
	List.readFileHighScore("highscore.txt");
	for (int i = 0; i < 10; i++)
	{
		CPoint2D p(5, 2*i + 4);
		List.outputPlayer(i, p);
	}
	gotoXY(0, 25);
}

void outputMenu(char c[][50], int row, int column, CPoint2D pMenu)
{
	int x = pMenu.getterX();
	int y = pMenu.getterY();

	for (int i = 0; i < row; i++)
	{
		gotoXY(x, y + i);
		for (int j = 0; j < column; j++)
			cout << c[i][j];
	}
}

int selectFunction(char m[][50])
{
	fstream f;
	char key = 0;
	char c = 16;
	int choice = 0;
	int x = 32;
	int y = 6;
	int type;
	string s;
	CPoint2D pMenu(30, 7);

	f.open("savegame.txt", ios_base::in);
	f >> type;
	f.close();

	if (type == 1)
	{
		textColor(7);
		createMenuSelection_1(m);
		outputMenu(m, 9, 20, pMenu);
		while (true)
		{
			do
			{
				key = getch();
			}
			while (key != 13 && key != -32);
			if (key == 13 && y != 6)
			{
				if (y == 8)
					choice = 2;
				if (y == 10)
					choice = 3;
				if (y == 12)
					choice = 4;
				if (y == 14)
					choice = 5;
				break;
			}
			do
			{
				key = getch();
			}
			while (key != 72 && key != 80);
			if (key == 72)
			{
				y = y - 2;
				while (y < 8)
					y = y + 2;
			}
			else
			{
				y = y + 2;
				if ( y > 14)
					y = y - 2;
			}
			
			textColor(7);
			outputMenu(m, 9, 20, pMenu);

			s = "";
			s = s + c;
			switch (y)
			{
			case 8: s = s + "   NEW GAME"; break;
			case 10: s = s + "  HIGH SCORE"; break;
			case 12: s = s + "    OPTION"; break;
			case 14: s = s + "     EXIT"; break;
			}
			gotoXY(x, y);
			textColor(2);
			cout << s;
		}
	}
	else
	{
		textColor(7);
		createMenuSelection_2(m);
		outputMenu(m, 11, 20, pMenu);
		while (true)
		{
			do
			{
				key = getch();
			}
			while (key != 13 && key != -32);
			if (key == 13 && y != 6)
			{
				if (y == 8)
					choice = 1;
				if (y == 10)
					choice = 2;
				if (y == 12)
					choice = 3;
				if (y == 14)
					choice = 4;
				if (y == 16)
					choice = 5;
				break;
			}
			do
			{
				key = getch();
			}
			while (key != 72 && key != 80);
			if (key == 72)
			{
				y = y - 2;
				while (y < 8)
					y = y + 2;
			}
			else
			{
				y = y + 2;
				if ( y > 16)
					y = y - 2;
			}
			textColor(7);
			outputMenu(m, 11, 20, pMenu);
			s = "";
			s = s + c;
			switch (y)
			{
			case 8: s = s + "   CONTINUE"; break;
			case 10: s = s + "   NEW GAME"; break; 
			case 12: s = s + "  HIGH SCORE"; break; 
			case 14: s = s + "    OPTION"; break;
			case 16: s = s + "     EXIT"; break;
			}
			gotoXY(x, y);
			textColor(2);
			cout << s;
		}
	}

	return choice;
}

void choiceCar(CCar* &owner)
{
	char m[15][50] = { };
	char m2[7][50] = { };
	CPoint2D pMenu(18, 5);
	CPoint2D pCar1(25, 11);
	CPoint2D pCar2(37, 11);
	CPoint2D pCar3(49, 11);
	CPoint2D pChoice(11, 9);
	CCar* car1 = new CFirstCar(pCar1);
	CCar* car2 = new CSecondCar(pCar2);
	CCar* car3 = new CThirdCar(pCar3);
	int key = 0;
	int x = pChoice.getterX();

	textColor(7);
	createMenuChoiceCar(m);
	outputMenu(m, 15, 42, pMenu);
	car1->initCar();
	car2->initCar();
	car3->initCar();
	car1->outputCar();
	car2->outputCar();
	car3->outputCar();
	createMicroMenu(m2);

	while (true)
	{
		do
		{
			key = getch();
		}
		while (key != 13 && key != 224);

		if (key == 13 && x != 11)
		{
			delete[] car1;
			car1 = NULL;
			delete[] car2;
			car2 = NULL;
			delete[] car3;
			car3 = NULL;

			CPoint2D p(15, 21);
			switch (x)
			{
			case 23: owner = new CFirstCar(p); return;
			case 35: owner = new CSecondCar(p); return;
			case 47: owner = new CThirdCar(p); return;
			}
		}

		do
		{
			key = getch();
		}
		while (key != 77 && key != 75);

		if (key == 77)
		{
			x = x + 12;
			if (x > 47)
				x = x - 12;
		}
		else
		{
			x = x - 12;
			while (x < 23)
				x = x + 12;
		}
		
		textColor(7);
		outputMenu(m, 15, 42, pMenu);
		
		pChoice.setterX(x);
		outputMenu(m2, 7, 7, pChoice);
		car1->outputCar();
		car2->outputCar();
		car3->outputCar();
	}
}

void playGame(CCar* owner)
{
	CRoadMap rm;
	CCompetitor* teamCom;
	CGift* g;
	time_t tStart, tEnd;
	time_t tStartCount, tEndCount;
	int check;
	int pos = 0;
	int x = 0;
	int y = 0;
	int speedTime = 200;
	char m[13][50] = { };
	char m2[7][50] = { };
	CPoint2D pMenu(40, 0);

	textColor(7);
	createControlPanel(m);
	outputMenu(m, 13, 40, pMenu);
	pMenu.setterY(13);
	createResultTable(m2);
	outputMenu(m2, 7, 40, pMenu);

	rm.initRoad();
	owner->initCar();
	tStart = -1;
	tStartCount = -1;
	srand((unsigned int)time(NULL));
	teamCom = new CCompetitor[8];
	g = new CGift[8];

	while (true)
	{
		if (tStartCount == -1)
			tStartCount = clock();
		check = owner->gotoPos();
		if (check == 27)
			break;
		if (check == 2)
			tStart = clock();
		if (check == 3)
			tStart = clock();
		if (owner->getChar(0, 1) != -51)
		{
			for (int i = 0; i < 8; i++)
			{
				if (owner->collision(teamCom[i]))
				{
					check = 0;
					break;
				}
			}
		}
		if (check == 0)
			break;
		gotoXY(0, 0);
		rm.outputRoad();
		if (y == 0)
		{
			g[pos].initGift();
			teamCom[pos].initCar();
		}
		for (int i = 0; i < 8; i++)
		{
			owner->checkXY(g[i]);
			g[i].outputGift();
			teamCom[i].outputCar();
		}
		for (int i = 0; i < 8; i++)
			if (owner->checkBullet(teamCom[i]))
				owner->addPoint(1);
		tEnd = clock();
		if (tStart > -1 && tEnd - tStart >= 10000)
		{
			owner->initCar();
			tStart = -1;
		}
		owner->outputFullCar();
		for (int i = 0; i < 8; i++)
		{
			y = teamCom[i].getterY();
			if (y == 24)
				owner->addPoint(1);
		}
		y = teamCom[pos].getterY();
		if (y == 0)
			pos = (pos + 1) % 8;
		for (int i = 0; i < 8; i++)
		{
			g[i].addY();
			teamCom[i].addY();
		}
		tEndCount = clock();
		if (tEndCount - tStartCount >= 20000)
		{
			tStartCount = -1;
			owner->addLevel();
			if (speedTime > 25)
				speedTime = speedTime - 25;
		}
		Sleep(speedTime);
	}
	
	if (check == 27)
	{
		char m3[4][50] = { };
		pMenu.setterX(0);
		pMenu.setterY(10);
		createMenuExit(m3);
		outputMenu(m3, 4, 33, pMenu);
		gotoXY(11, 12);
		char c;
		do
		{
			cin >> c;
			gotoXY(11, 12);
		}
		while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
		fstream f;
		int num = 1;
		f.open("savegame.txt", ios_base::out);
		
		if (c == 'y' || c == 'Y')
		{
			num = 2;
			f << num << " ";
			num = owner->getterTypeCar();
			f << num << " ";
			num = owner->getterLevel();
			f << num << " ";
			num = owner->getterPoint();
			f << num << " ";
			num = owner->getterPower();
			f << num;
			f.close();
		}
		else
		{
			f << num;
			f.close();
		}
		return;
	}

	CListPlayer List;
	int temp;
	int point;

	List.readFileHighScore("highscore.txt");
	temp = List.getterPlayer(9);
	point = owner->getterPoint();
	if (point > temp)
	{
		char m3[4][50] = { };
		string sName;
		int level = owner->getterLevel();
		pMenu.setterX(10);
		pMenu.setterY(11);
		createNameTable(m3);
		outputMenu(m3, 4, 30, pMenu);
		gotoXY(11, 13);
		cin >> sName;
		if (sName == "")
			sName = "Pikachu";
		CPlayer pl(sName, level, point);
		List.insertPlayer(pl);
		List.writeFileHighScore("highscore.txt");
	}
}

void performFunction(int num)
{
	clearScreen();
	switch (num)
	{
	case 1:
		{
			fstream f;
			f.open("savegame.txt", ios_base::in);
			if (f == NULL)
				return;
			CPoint2D p(15, 21);
			CCar* owner;
			int type;
			int temp;
			f >> type;
			f >> type;
			switch (type)
			{
			case 1: owner = new CFirstCar(p); break;
			case 2: owner = new CSecondCar(p); break;
			case 3: owner = new CThirdCar(p); break;
			}
			owner->initCar();
			f >> temp;
			owner->setterLevel(temp);
			f >> temp;
			owner->setterPoint(temp);
			f >> temp;
			owner->setterPower(temp);
			f.close();
			playGame(owner);
			break;
		}
	case 2: 
		{
			CCar* owner;
			choiceCar(owner);
			clearScreen();
			playGame(owner);
			break;
		}
	case 3:
		{
			char menu[25][50] = { };
			CPoint2D pMenu(0, 0);
			createMenuHighScore(menu);
			outputMenuHighScore(menu);
			getch();
			break;
		}
	case 4:
		{
			char menu[25][50] = { };
			CPoint2D pMenu(0, 0);
			createGuideTable(menu);
			textColor(7);
			outputMenu(menu, 25, 50, pMenu);
			getch();
			break;
		}
	case 5: return;
	}
}