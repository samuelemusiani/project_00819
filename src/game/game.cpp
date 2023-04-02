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
	Game::doSelected(menu.drawMenu()); //dobbiamo decidere come implementare le scelte
	endwin();
}


void Game::doSelected(int x) //switch with 4 options
{
	switch (x) {
		/*case x=0:
			Game.init();
			break;
		case x=1:
			Game.resume();
			break;
		case x=2:
			Game.help();
			break;*/
		case 3:
		{
			Game::credits(); //provvisorio
			break;
		}
		default:
			break;
	}
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
	fileCredits.open("Credits.txt");
	std::string line;
	if(fileCredits.is_open())
	{
		while ( fileCredits.good() ) //read until end of file
		{
			std::getline (fileCredits, line);
			Draw::drawText(posY, posX, line.c_str()); //draw with drawtext every line
			posY += 2;
		}
	} else mvprintw(1, 1, "Error during reading file");
	fileCredits.close();
	getch();
}
