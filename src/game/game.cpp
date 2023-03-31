#include "game.hpp"

Game::Game()
{
	this->init();
}

void Game::run()
{
	initscr();			/* Start curses mode 		  */
	printw("Hello World !!!");	/* Print Hello World		  */
	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */


}

bool Game::init()
{

}
