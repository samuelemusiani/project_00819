#include "game.hpp"
#include "menu.hpp"
#include <unistd.h>
#include "game.hpp"
#include "../physics/body.hpp"
#include "../physics/point.hpp"
#include "../physics/vector.hpp"
#include "save.hpp"



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
	menu.drawFirstMenu(this->screen);
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
	screen.drawText(16, Draw::centerX("Are you sure you want to quit?"), "Are you sure you want to quit?");	nostd::string options[2] = {"Yes", "No"};
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
	setDifficulty();
	Map map = Map();
	screen.drawMap(map, 0);

	// Creare un oggetto body, chiamo getposition su body. Passo il punto che mi ritorna alla drawPlayer e la drawPlayer disegna il player in quella posizione
	phy::Body player = phy::Body(phy::Point(10, 10), 1, 1);
	screen.drawPlayer(player.get_position());
	screen.refreshScreen();
	
	// Implementare che con KEY_LEFT, KEY_RIGHT si sposta il giocatore utilizzando il metodo setPosition di body e poi disegnare il giocatore in quella posizione con drawPlayer
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

			{	
				bool quitGamepley = pauseGame();
				if (quitGamepley == true) exit = true;
				break;
			}
			default:
				break;
		}

		screen.eraseScreen();
		screen.drawMap(map, 0);
		screen.drawPlayer(player.get_position());
		napms(5);
	
	}
	screen.nodel(false);
	
	
}

void Game::resume()
{
	screen.clearScreen();
	screen.drawText(3, (Draw::centerX("Load your game from a saved file")), "Load your game from a saved file");
}

int Game::setDifficulty()
{
	screen.clearScreen();
	screen.drawText(3, (Draw::centerX("Select the difficulty")), "Select the difficulty");
	nostd::string options[3] = {"Easy", "Medium", "Hard"};
	int selected = 0;
	bool choose = false;
	while (!choose){
		for (int i = 0; i < 3; i++)
		{
			screen.drawSquareAround(options[i], 20, 58 + 15*i);
		}
		screen.attrOn(COLOR_PAIR(1));
		screen.drawText(20, 58 + 15*selected, options[selected]);
		screen.attrOff(COLOR_PAIR(1));

		switch (screen.getinput())
		{
			case KEY_LEFT:
				if (selected == 0) selected = 2;
				else selected = selected - 1;
				break;
			case KEY_RIGHT:
				if (selected == 2) selected = 0;
				else selected = selected + 1;
				break;
			case 10:
				choose = true;
				break;
		}
	}
	return selected;
}

bool Game::pauseGame()
{
	screen.nodel(false);
	// for che utilizzando move sposta il cursore a (y = i, x = 120) e cancella la riga con clrtoeol
	/*for (int i = 0; i < screen.get_maxY(); i++)
	{
		screen.clearLine(i, 90);
	}*/
	//screen.drawBox();
	bool resumed = false;
	bool exit = false;
	while(!resumed)
	{

	int xMaxSize, yMaxSize;
	getmaxyx(stdscr, yMaxSize, xMaxSize);
	int posY = (yMaxSize - 44) / 2;
	int posX = (xMaxSize - 150) / 2;
	
	Draw pause = screen.newWindow(44, 60, posY, 90 + posX);
	
	pause.clearwithoutbox();
	pause.drawBox();
	screen.drawBox();
	pause.drawText(3, 30 - pause.center("Game Paused"),  "Game Paused");
	nostd::string options[3] = {"Resume", "Save", "Exit"};
	int selected = 0;
	bool choose = false;
	wnoutrefresh(screen.getScreen()); // copying of information from a window data structure to the virtual screen
	wnoutrefresh(pause.getScreen()); // utilizzando wnoutrefresh, il refresh del terminale avviene solo al doupdate()
	doupdate(); // aggiorna il terminale. Quindi si evita il flicker dato dal tempo che intercorre tra l'aggiornamento di due window usando il classico refresh
	

	while (!choose){	
		for (int i = 0; i < 3; i++)
		{
			pause.drawSquareAround(options[i], 20 + 4*i, 30 - (options[i].length() / 2));
		}
		pause.attrOn(COLOR_PAIR(1));
		pause.drawText(20 + 4*selected, 30 - (options[selected].length() / 2), options[selected]);
		pause.attrOff(COLOR_PAIR(1));
		switch (pause.getinput())
		{
			case KEY_UP:
				if (selected == 0) selected = 2;
				else selected = selected - 1;
				break;
			case KEY_DOWN:
				if (selected == 2) selected = 0;
				else selected = selected + 1;
				break;
			case 10:
				choose = true;
				break;
			default: 
				break;
		}
	}
	pause.refreshScreen();
	Save save = Save();
	switch (selected)
	{
		case 0:
			screen.nodel(true);
			pause.deleteWin();

			resumed = true;
			break;
		case 1:
		{
			pause.deleteWin();
			int xMaxSize, yMaxSize;
			getmaxyx(stdscr, yMaxSize, xMaxSize);
			int posY = (yMaxSize - 44) / 2;
			int posX = (xMaxSize - 150) / 2;
			
			Draw save_scr = screen.newWindow(44, 150, posY, posX);

			save.saveGame(save_scr);
			save_scr.eraseScreen();
			save_scr.deleteWin();
			break;
		}
			
		case 2: 
			{
			pause.clearScreen();
			pause.deleteWin();
			redrawwin(screen.getScreen());	
			screen.refreshScreen();
			int xMaxSize, yMaxSize;
			getmaxyx(stdscr, yMaxSize, xMaxSize);
			int posY = (yMaxSize - 15) / 2;
			int posX = (xMaxSize - 55) / 2;
			
			Draw quit_scr = screen.newWindow(15, 55, posY, posX);
			save.quitGame(quit_scr);
			quit_scr.eraseScreen();
			quit_scr.deleteWin();
			resumed = true; 
			exit = true; 
			break;
			}	
		default:
			break;
		
	}
	}
	return exit;
}