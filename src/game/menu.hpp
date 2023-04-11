#include <string>
#include <ncurses.h>
#include "../draw/draw.hpp"
#include "credits.hpp"
#include "game.hpp"
#include "settings.hpp"

#define NUMBER_OF_OPTIONS 4


class Menu
{
	private:
		int posY;
		int posX;
		std::string options[NUMBER_OF_OPTIONS] = {"New Game", "Resume Game from saved file", "Settings", "Credits"};
		Draw screen;
	public:

		Menu(int x, int y);

		void drawMenu(); // Disegna il menu
		
		int get_selected_option();
		
};
