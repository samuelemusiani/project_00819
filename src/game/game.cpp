#include "game.hpp"
#include "menu.hpp"
#include <unistd.h>
#include "../draw/screen.hpp"


Game::Game()
{	
	this->screen = Draw();
	screen.init();

}

Game::~Game()
{
	wgetch(this->screen.win);
	endwin();
}

void Game::run()
{
	//Menu::start();
	Menu menu = Menu(screen.get_maxX(), screen.get_maxY(), this->screen);
	menu.drawMenu();

}

