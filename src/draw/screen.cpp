#include "screen.hpp"
#include <unistd.h>



Screen::Screen()
{
}

void Screen::init()
{
	initscr();
	cbreak();
	noecho();
	if (LINES < 44 || COLS < 150)
	{
		printw("Your terminal is too small. Please resize it at least to 44x150");
		while (LINES < 44 || COLS < 150)
		{
			refresh();
			sleep(1); // attendo 1 secondo per non mandare la cpu a 100%
		}
	}
	curs_set(0);
	start_color();
	int xMaxSize, yMaxSize;
	getmaxyx(stdscr, yMaxSize, xMaxSize);
	int posY = (yMaxSize - 44) / 2;
	int posX = (xMaxSize - 150) / 2;
	win = newwin(44, 150, posY, posX);
	keypad(win, true);
	set_escdelay(1);
	this-> max_x = getmaxx(win);
	this-> max_y = getmaxy(win);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	// Ridefinisco il colore nero a 0,0,0 per alcuni terminali che mostrano un colore diverso
	init_color(COLOR_BLACK, 0, 0, 0);
	// Setto il background nero
	wbkgd(win, COLOR_BLACK);
	wrefresh(win);
}

int Screen::get_maxX()
{
	return this->max_x;
}

int Screen::get_maxY()
{
	return this->max_y;
}

void Screen::clearScreen()
{
	wclear(win);
	box(win, 0, 0);
	wrefresh(win);
}

void Screen::eraseScreen()
{
	werase(win);
	box(win, 0, 0);
}
