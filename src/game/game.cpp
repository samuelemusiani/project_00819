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
	menu.doSelected(menu.drawMenu());
	endwin();
}

void Game::init()
{
	initscr();
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
	bool flag = false;
	int posY = 4;
	int posX = 4;
	std::ifstream fileCredits;
	std::string line;
	fileCredits.open("Credits.txt"); //open file
	while (std::getline(fileCredits, line)) //read until end of file
		{
			Draw::drawText(posY, posX, line.c_str()); //draw with drawtext every line
			posY += 2;
		}
}
