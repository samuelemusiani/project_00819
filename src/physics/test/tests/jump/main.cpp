#include <ncurses.h>
#include <iostream>
#include "../../../point.hpp"
#include "../../../vector.hpp"

#define PROTAGONIST "T"

void drawProtagonist() 
{
	int ch;

	bool EXIT = false;

	int x = 0;
	int y = 0;

	while(!EXIT)
	{
		INPUT_KEY:
		ch = getchar();
		switch (ch)
		{
			case 'w':
				if(y > 0) y--;
				break;

			case 's':
				if(y < LINES - 2) y++;
				break;

			case 'a':
				if(x > 0) x--;
				break;

			case 'd':
				if(x < COLS - 1) x++;
				break;

			case 'q':
				if(x > 0 && y > 0) 
				{
					x--;
					y--;
				}
				break;
				
			case 'e':
				if(x < COLS - 1 && y > 0) 
				{
					x++;
					y--;
				}
				break;

			case KEY_F(1):
				EXIT = true;
				break;

			default:
				goto INPUT_KEY;
				break;
		}
		mvprintw(y, x, PROTAGONIST);
		refresh();
	}
}

void basicJump()
{
}

int main()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	//drawProtagonist();
	basicJump();

	endwin();

	return 0;
}
