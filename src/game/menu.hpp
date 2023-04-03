#include <string>
#include <ncurses.h>
#include "../draw/draw.hpp"

#define NUMBER_OF_OPTIONS 4


class Menu
{
	private:
		int posY;
		int posX;
		std::string options[NUMBER_OF_OPTIONS] = {"New Game", "Resume Game from saved file", "Help", "Credits"};
	public:

		Menu(int LINES, int COLS);

		int drawMenu();

};
