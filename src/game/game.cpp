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
	Menu menu = Menu(LINES, COLS);
	menu.drawMenu();

}

bool Game::init()
{
	initscr();
	start_color();
	curs_set(0);
}
