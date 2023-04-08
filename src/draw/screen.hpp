#include <ncurses.h>
#include "../constant.hpp"

#ifndef DRAW_SCREEN
#define DRAW_SCREEN

class Screen
{
	private:
		int max_x;
		int max_y;
		
	protected:
		WINDOW *screen;

	public:

		Screen();
		void init(); // Inzializza lo schermo e la WINDOW al centro del terminale
		int get_maxX();
		int get_maxY();
		void clearScreen();
		void eraseScreen();
};

#endif
