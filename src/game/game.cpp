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
	bool exit = false;
	Menu menu = Menu(LINES, COLS);
	while (!exit) {
		menu.drawMenu();
		int option = menu.get_selected_option();
		switch (option) {
			case 3:
			{
				credits();
				getch();
				break;
			}
			case -1: //condizione di exit
			{
				exit = true;
				break;
			}
		}
	}
}


void Game::init()
{
	initscr();
	noecho();
	set_escdelay(0);
	keypad(stdscr, true);
	start_color();
	curs_set(0);
}


void Game::credits()
{
	Draw::clearWindow(stdscr);
	wrefresh(stdscr);
	Draw::drawText(1,1, "Credits Video Game JumpKing (da rivedere il nome) \n \
	Alma Mater Studiorum Bologna University: project-00819 \n This game has been \
	developed in the year 2023 by \n Argonni Emanuele \n Musiani Samuele \n Peronese\
	Lorenzo \n Ayache Omar \n Hope you had fun playing this game");
}
