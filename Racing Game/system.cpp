# include "system.h"

void gotoXY(int x, int y)
{
	COORD co = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), co);
}

void clearScreen()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0}; 
    BOOL bSuccess;
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; 
    DWORD dwConSize;  
 
    bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y; 
    bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR)' ',
    dwConSize, coordScreen, &cCharsWritten);
    bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi); 
    bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
    dwConSize, coordScreen, &cCharsWritten);
    bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
    return;
}

void textColor(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
