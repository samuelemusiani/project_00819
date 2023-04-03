#include <string>
#include <ncurses.h>
#include "../draw/draw.hpp"

#define NUMBER_OF_OPTIONS 4


class Menu
{
	private:
		int posY;
		int posX;
		bool flag = false;
		int selectedOption = 0;
		std::string options[NUMBER_OF_OPTIONS] = {"New Game", "Resume Game from saved file", "Help", "Credits"};
	public:

		Menu(int LINES, int COLS);

		void drawMenu();


		
};
