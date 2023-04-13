#include "game.hpp"
#include "menu.hpp"
#include <unistd.h>
#include "game.hpp"
#include "../physics/body.hpp"
#include "../physics/point.hpp"
#include "../physics/vector.hpp"



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
			screen.getinput();
			break;}
		case 1: 
			{// Resume game
			this->resume();
			screen.getinput();
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
	screen.clearScreen();
	screen.drawText(16, 75 - Draw::centerX("Are you sure you want to quit?"), "Are you sure you want to quit?");	nostd::string options[2] = {"Yes", "No"};
	int selected = 0;
	bool choose = false;
	// Create two button (yes or no) to quit the game 	
	while (!choose){


		for (int i = 0; i < 2; i++)
		{
			screen.drawSquareAround(options[i], 20, 65 + 15*i);
		}
		// Set the selected button to blue
		screen.attrOn(COLOR_PAIR(1));
		screen.drawText(20, 65 + 15*selected, options[selected]);
		screen.attrOff(COLOR_PAIR(1));

		// Wait for the user to press a key
		switch (screen.getinput())
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
	Map map = Map();
	screen.drawMap(map, 0);

	// Creare un oggetto body, il body ha una posizione, chiamo getposition su body. Passo il punto che mi ritorna alla drawPlayer e la drawPlayer disegna il player in quella posizione
	phy::Body player = phy::Body(phy::Point(10, 10), 1, 1);
	screen.drawPlayer(player.get_position());
	screen.refreshScreen();
	
	// Implementare che con KEY_LEFT, KEY_RIGHT si sposta il giocatore utilizzando il metodo setPosition di body e poi disegnare il giocatore in quella posizione con drawPlayer
	// Se il giocatore si muove devo cancellare il giocatore dal vecchio punto facendo un clearScreen e poi disegnando il giocatore in quella posizione
	bool exit = false;
	screen.nodel(true);
	while (!exit){
		
		switch(screen.getinput())
		{
			case KEY_LEFT:
				player.set_position(player.get_position() + phy::Point(-1, 0));
				break;
			case KEY_RIGHT:
				player.set_position(player.get_position() + phy::Point(1, 0));
				break;
			case KEY_UP:
				player.set_position(player.get_position() + phy::Point(0, -1));
				break;
			case KEY_DOWN:
				player.set_position(player.get_position() + phy::Point(0, 1));
				break;
			case 27:
				exit = true;
				break;
			default:
				break;
		}

		screen.eraseScreen();
		screen.drawMap(map, 0);
		screen.drawPlayer(player.get_position());
		napms(1);
	
	}
	screen.nodel(false);
	screen.clearScreen();	
	
}

void Game::resume()
{
	screen.clearScreen();
	screen.drawText(3, 75 - (Draw::centerX("Load your game from a saved file")), "Load your game from a saved file");
}
