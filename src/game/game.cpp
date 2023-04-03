#include "game.hpp"
#include "menu.hpp"
#include <unistd.h>


Game::Game()
{
	this->init();
	// Se la grandezza del terminale è minore di 44x150, allora printa errore
	if (LINES < 44 || COLS < 150)
	{
		printw("Your terminal is too small. Please resize it at least to 44x150");
		while (LINES < 44 || COLS < 150)
		{
			refresh();
			sleep(1); // attendi 1 secondo per non mandare la cpu a 100%
		}
	}
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
