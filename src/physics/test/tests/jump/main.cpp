/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Musiani Samuele #0001069143
*
* main.cpp: Early implementation of a naive jump.
*/

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

	mvprintw(y_max - p.get_yPosition(), p.get_xPosition(), "@");
}

void drawProtagonist() 
{
	bool EXIT = false;

	int x = 0;
	int y = 0;

	phy::Body b;
	b.set_position(phy::Point(0, 0));
	b.set_velocity(phy::Vector(4, 60));
	b.set_acceleration(phy::Vector(0.4, -90));

	int tmp;

	while(!EXIT)
	{
		b.update(0.15);

		drawChar(b.get_position());

		refresh();
		std::this_thread::sleep_for(std::chrono::milliseconds(20));

		clear();
	}
}

int main()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);

	drawProtagonist();

	endwin();

	return 0;
}
