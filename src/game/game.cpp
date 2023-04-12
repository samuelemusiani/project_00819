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
	
	endwin();
}

void Game::run()
{
	Menu menu = Menu(screen.get_maxX(), screen.get_maxY());
	bool exit = false;
	while (!exit) {

		menu.drawMenu(this->screen);
		int sel = menu.get_selected_option(this->screen);

		Credits credits;
		Settings settings;
		
		switch (sel)
		{
		
		
		case 0: 
			{// New Game
			// Chiama la funzione start della classe game che si trova in game.cpp che non è statica
			this->start();
			wgetch(win);
			break;}
		case 1: 
			{// Resume game
			this->resume();
			wgetch(win);
			break;}
		case 2: 
			{// Settings
			settings.drawSettings(this->screen);
			
			break; 
			}
		case 3:
		{
			// chiama la funziona credits che si trova in credits.cpp
			credits = Credits();
			int dev = credits.drawCredits(this->screen);
			if (dev != -1) credits.openGithub(dev);
			
			break;
		}
		case 27:
			{
				if (exitGame() == true) exit = true;
			}
		}
		

	}
}


bool Game::exitGame(){
	// Esci dal gioco
	wclear(win);
	mvwprintw(win, 16, 75 - Draw::centerX("Are you sure you want to quit?"), "Are you sure you want to quit?");
	std::string options[2] = {"Yes", "No"};
	int selected = 0;
	bool choose = false;
	// Create two button (yes or no) to quit the game 	
	while (!choose){


		for (int i = 0; i < 2; i++)
		{
			//mvwprintw(win, 20, 65 + 15*i, options[i].c_str());
			screen.drawSquare(options[i], 20, 65 + 15*i);

		}
		// Set the selected button to blue
		wattron(win, COLOR_PAIR(1));
		screen.drawText(20, 65 + 15*selected, options[selected]);
		wattroff(win, COLOR_PAIR(1));

		// Wait for the user to press a key
		switch (wgetch(win))
		{
			case KEY_LEFT:
				if (selected == 1) selected = selected - 1;
				else if (selected == 0) selected = 1;
				break;
			case KEY_RIGHT:
				if (selected == 0) selected = selected + 1;
				else if (selected == 1) selected = 0;
				break;
			case 10:
				choose = true;
				break;
		}

		
		
	}
	if (selected == 0) return true;
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