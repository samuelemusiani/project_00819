#include "menu.hpp"

Menu::Menu(int x, int y) {
	posX = x;
	posY = y;
	this->screen = screen;
	}
	
int Menu::drawMenu() {

	// Disegna la box di colore verde
	screen.clearScreen();

	// Titolo del gioco all'interno di una box
	screen.drawText(2, (posX/2)-9, "------------------");
	screen.drawText(4, (posX/2)-9, "------------------");
	screen.drawText(3, (posX/2)-9, "|");
	screen.drawText(3, (posX/2)+8, "|");
	screen.drawText(3, (posX/2)-4, "JumpKing");
	
	bool isSelected = false;
	int selectedOption = 0;

	while (!isSelected) {
		// Scrive le opzioni del menu
		for (int i = 0 ; i < NUMBER_OF_OPTIONS; i++)
		{
			screen.drawText((posY/2-2) +2*i, posX/2 - (options[i].length()/2), options[i].c_str());
			
		}

		wattron(win, COLOR_PAIR(1));
		screen.drawText((posY/2-2) +2*selectedOption, posX/2 - (options[selectedOption].length()/2), options[selectedOption].c_str());
		wattroff(win, COLOR_PAIR(1));

		// Prende l'input dell'utente e cambia la selezione
		switch (wgetch(win)) {
			case KEY_UP:
				if (selectedOption > 0) {
					selectedOption--;
				}
				else if (selectedOption == 0) {
					selectedOption = NUMBER_OF_OPTIONS - 1;
				}
				break;
			case KEY_DOWN:
				if (selectedOption < NUMBER_OF_OPTIONS - 1) {
					selectedOption++; 
				}
				else if (selectedOption == NUMBER_OF_OPTIONS - 1) {
					selectedOption = 0;
				}
				break;
			case 27:
				selectedOption = -1;
				isSelected = true;
				break;
			case 10: 
				isSelected = true;
				break;
		}
	}
	return(selectedOption);
		
}
	
bool Menu::isSelected(int selection){
	Credits credits;
	Game game;
	switch (selection)
	{
	
	case 0: 
		// New Game
		// Chiama la funzione start della classe game che si trova in game.cpp che non è statica
		game.start();
		return(false);
		break;
	case 1: 
		// Resume game
		game.resume();
		return(false);
		break;
	case 2: 
		// Settings and help
		break; 
	
	case 3:
		// chiama la funziona credits che si trova in credits.cpp
		credits = Credits();
		int dev = credits.drawCredits();
		if (dev != -1) credits.openGithub(dev);
		
		wgetch(win);
		return(false);
		break;
	

	}
}