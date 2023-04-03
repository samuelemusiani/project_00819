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

	// Ottiene le dimensioni del terminale
    resize_term(40, 140);


	curs_set(0);
}
