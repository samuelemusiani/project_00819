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
	bool exit = false;
	Menu menu = Menu(LINES, COLS);
	while(!exit) {
		if(Game::doSelected(menu.drawMenu())) exit = true;
	}
	Game::~Game();
}


bool Game::doSelected(int x) //switch with 4 options
{
	switch (x) {
		/*case x=0:
			Game::start();
			return(false);
			break;
		case x=1:
			Game::resume();
			return(false);
			break;
		case x=2:
			Game::help();
			return(false);
			break;*/
		case 3:
		{
			Game::credits(); //provvisorio
			getch();
			return(false);
			break;
		}
		case -1:
		{
			return(true);
			break;
		}
		default:
			return(false);
			break;
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
/*
bool Game::resume()
{
	//...
}

bool Game::help()
{
	//...
}
*/

void Game::credits()
{
	clear();
	wrefresh(stdscr);
	Draw::drawText(1,1, "Credits Video Game JumpKing (da rivedere il nome) \n \
	Alma Mater Studiorum Bologna University: project-00819 \n This game has been \
	developed in the year 2023 by \n Argonni Emanuele \n Musiani Samuele \n Peronese\
	Lorenzo \n Ayache Omar \n Hope you had fun playing this game");
}
