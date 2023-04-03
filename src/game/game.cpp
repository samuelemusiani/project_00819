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
	mvwin(stdscr, 10, 10);
	resize_term(44, 150);
	Menu menu = Menu(LINES, COLS);
	menu.drawMenu();

}

bool Game::init()
{
	initscr();
	// crea una window di ncurses

	start_color();
	
	// sposta lo schermo al centro del terminale
	mvwin(stdscr, 10, 10);
	// Sposta la finestra di ncurses al centro del terminale
	
	wrefresh(stdscr);	
	curs_set(0);
}
