#include "menu.hpp"

Menu::Menu(int x, int y, Draw screen) {
	posX = x;
	posY = y;
	this->screen = screen;
	}
	
void Menu::drawMenu() {

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

		wattron(this->screen.win, COLOR_PAIR(1));
		screen.drawText((posY/2-2) +2*selectedOption, posX/2 - (options[selectedOption].length()/2), options[selectedOption].c_str());
		wattroff(this->screen.win, COLOR_PAIR(1));

		// Prende l'input dell'utente e cambia la selezione
		switch (wgetch(this->screen.win)) {
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
			case 10: 
				isSelected = true;
				break;
		}
	}
		
}
	