#include "game.hpp"
#include "menu.hpp"
#include <unistd.h>
#include "game.hpp"

WINDOW *win;

Game::Game()
{	
	this->screen = Draw();
	screen.init();

}	

Game::~Game()
{
	wgetch(win);
	endwin();
}

void Game::run()
{
	Menu menu = Menu(screen.get_maxX(), screen.get_maxY());
	bool exit = false;
	while (!exit) {

		menu.drawMenu();
		int x = menu.get_selected_option();
		menu.isSelected(x);
		// DEBUG
		wclear(win);
		mvwprintw(stdscr, 1, 1, "i am here");
		refresh();
	}
}

void Game::start()
{
	// clear the screen and draw the border
	screen.clearScreen();	
}

void Game::resume()
{
	screen.clearScreen();
	screen.drawText(3, 75 - (Draw::centerX("Load your game from a saved file")), "Load your game from a saved file");
}