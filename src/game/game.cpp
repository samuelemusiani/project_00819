#include "game.hpp"
#include <unistd.h>

WINDOW *win;

Game::Game()
{
	this->screen = Draw();
	screen.init();

}

Game::~Game()
{
	wgetch(win);
	endwin();
}

void Game::run()
{
	Menu menu = Menu(screen.get_maxX(), screen.get_maxY());
	bool exit = false;
	while (!exit) {

		menu.drawMenu();
		int x = menu.get_selected_option();
		menu.isSelected(x);
	}
}

void Game::start()
{
	// clear the screen and draw the border
	screen.clearScreen();
	Draw maps;
	Map map = Map();
	maps.drawMap(map, 0);
}

void Game::resume()
{
	screen.clearScreen();
	std::string s = "w";
	screen.drawSquare(s, 3, 75 - (s.length()/2) );
}
