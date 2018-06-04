# include "system.h"
# include <iostream>
# pragma once
using namespace std;

class CRoadMap
{
private:
	char roadLeft[24][4];
	char roadRight[24][4];
	char road[24][25];
public:
	void initRoad();
	void outputRoad();
	CRoadMap();
	~CRoadMap();
};

