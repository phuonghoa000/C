# include "control.h"

int main()
{
	char menu[25][50] = { };
	int choice;

	gotoXY(26, 4);
	textColor(14);
	cout << "WELCOME TO SPEED RACING GAME";
	do
	{
		
		choice = selectFunction(menu);
		performFunction(choice);
		clearScreen();
	}
	while (choice == 3 || choice == 4);

	textColor(7);
	return 0;
}