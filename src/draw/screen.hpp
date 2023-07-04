#include <ncurses.h>


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
		void nodel(bool value);
		void refreshScreen();
		int getinput();
		void clearwithoutbox();
		// Funzione che cancella la riga y a partire dalla colonnna x 
		void clearLine(int y, int x);

		// Funzione che disegna una linea verticale a x, da y1 a y2
		void drawVerticalLine(int x, int y1, int y2);

		void deleteWin();
		void size(int &posY, int &posX, int offsetY, int offsetX);
		void noOutRefresh();
		static void update(); // Why static??
		void redraw();
};

#endif
