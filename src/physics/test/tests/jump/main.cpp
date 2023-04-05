#include <ncurses.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "../../../point.hpp"
#include "../../../vector.hpp"
#include "../../../body.hpp"

//const char PROTAGONIST = 'T';

void drawChar(phy::Point p) 
{
	int x_max;
	int y_max;
	getmaxyx(stdscr, y_max, x_max);

	mvprintw(y_max - p.get_yPosition(), p.get_xPosition(), "T");
}

void drawProtagonist() 
{
	int ch;

	bool EXIT = false;

	int x = 0;
	int y = 0;

	phy::Body b;
	b.set_position(phy::Point(0, 0));
	b.set_velocity(phy::Vector(10, 70));
	b.set_acceleration(phy::Vector(1, -90));

	while(!EXIT)
	{
		b.update(1);
		//b.set_position(phy::Point(x, y));

		drawChar(b.get_position());
		refresh();
		//sleep(0.8);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));

		/*
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

			case 'g':
				b.set_velocity(phy::Vector(1, 0));
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
				break;
		}
		*/
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

	drawProtagonist();
	basicJump();

	endwin();

	return 0;
}
