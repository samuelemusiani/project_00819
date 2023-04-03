#include "game.hpp"
#include "menu.hpp"


Game::Game()
{
	this->init();
}

Game::~Game()
{
	endwin();
}

void Game::run()
{
	//Menu::start();
	keypad(stdscr, true);
	resize_term(44, 150);
	Menu menu = Menu(44, 150);
	menu.drawMenu();

}

bool Game::init()
{
	initscr();
	// crea una window di ncurses

	start_color();
	
	curs_set(0);
}
