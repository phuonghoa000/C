# include "RoadMap.h"
# include "FirstCar.h"
# include "SecondCar.h"
# include "ThirdCar.h"
# include "Competitor.h"
# include "ListPlayer.h"
# include <string>
# include <fstream>

void createMenuSelection_1(char m[][50]);
void createMenuSelection_2(char m[][50]);
void createMenuExit(char m[][50]);
void createMenuHighScore(char m[][50]);
void createControlPanel(char m[][50]);
void createResultTable(char m[][50]);
void createNameTable(char m[][50]);
void createMenuChoiceCar(char m[][50]);
void createMicromenu(char m[][50]);
void createGuideTable(char m[][50]);
void outputMenuHighScore(char m[][50]);
void outputMenu(char m[][50], int row, int column, CPoint2D pMenu);
int selectFunction(char m[][50]);
void playGame(CCar* owner);
void performFunction(int num);