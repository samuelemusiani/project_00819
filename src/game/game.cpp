#include "game.hpp"
#include "menu.hpp"
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
	//Menu::start();
	Menu menu = Menu(screen.get_maxX(), screen.get_maxY());
	bool exit = false;
	while (!exit) {
		if (menu.isSelected(menu.drawMenu())) exit = true;
	}
}
