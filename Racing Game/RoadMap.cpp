# include "RoadMap.h"

void CRoadMap::initRoad()
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			road[i][j] = ' ';
			if (j == 0 || j == 24)
				road[i][j] = -70;
			if (j == 12)
				road[i][j] = -37;
		}
		for (int j = 0; j < 4; j ++)
		{
			if ((i + j) % 2 == 0)
			{
				roadLeft[i][j] = 5;
				roadRight[i][3 - j] = 5;
				continue;
			}
			roadLeft[i][j] = ' ';
			roadRight[i][3 - j] = ' ';
		}
		roadLeft[i][3] = 5;
		roadRight[i][0] = 5;
	}
}

void CRoadMap::outputRoad()
{
	for (int i = 0; i < 24; i++)
	{
		textColor(2);
		for (int j = 0; j < 4; j++)
			cout << roadLeft[i][j];
		textColor(7);
		for (int j = 0; j < 25; j ++)
			cout << road[i][j];
		textColor(2);
		for (int j = 0; j < 4; j++)
			cout << roadRight[i][j];
		cout << endl;
	}
	cout << endl;
}

CRoadMap::CRoadMap()
{
}

CRoadMap::~CRoadMap()
{
}
