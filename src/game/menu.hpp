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
		nostd::string options[NUMBER_OF_OPTIONS] = {"New Game", "Resume Game from saved file", "Settings", "Credits"};
		
	public:

		Menu(int x, int y);

		void drawMenu(Draw screen); // Disegna il menu
		
		int get_selected_option(Draw screen);
		
};
