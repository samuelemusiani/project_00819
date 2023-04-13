#include "menu.hpp"

Menu::Menu(int x, int y) {
	posX = x;
	posY = y;
	
	}
	

void Menu::drawFirstMenu(Draw screen) {
	
	screen.clearScreen();
	bool selected = false;
	screen.nodel(true);

	// animazione del titolo all'avvio del gioco dai lati al centro
	for (int i = 0; i < 42 && !selected ; i++) {
		for (int j = 0; j < 6 ; j++) {
			screen.drawText(19 + j, i, this->Jump[j]); 
			screen.drawText(19 + j, 120 - i, this->King[j]);
			}
		screen.refreshScreen();
		screen.eraseScreen();	
		napms(50);
		int x = screen.getinput();
		if (x == 27 || x == 10) selected = true;
	}

	// animazione del titolo all'avvio del gioco dal centro al centro in alto
	for (int i = 0; i < 16 && !selected ; i++) {
		for (int j = 0; j < 6 ; j++) {
			screen.drawText(19 + j - i, 42, this->Jump[j]); 
			screen.drawText(19 + j - i, 78, this->King[j]);
			}
		int x = screen.getinput();
		if (x == 27 || x == 10) selected = true;
		screen.refreshScreen();
		screen.eraseScreen();
		napms(250);
	}

	screen.nodel(false);

}

void Menu::drawMenu(Draw screen){
		screen.clearScreen();
		// Scrive il titolo del gioco fermo in alto
		for (int j = 0; j < 6 ; j++) {
			screen.drawText(4 + j, 42, this->Jump[j]); 
			screen.drawText(4 + j, 78, this->King[j]);
		}
}

int Menu::get_selected_option(Draw screen) {
	bool isSelected = false;
	int selectedOption = 0;
	screen.nodel(false); // make getch() wait for input so that the menu doesn't refresh too fast - CPU FIX 
	while (!isSelected) {
		// Scrive le opzioni del menu
		for (int i = 0 ; i < NUMBER_OF_OPTIONS; i++)
		{
			screen.drawText((posY/2-2) +2*i, posX/2 - (options[i].length()/2), options[i].c_str());
			
		}

		screen.attrOn(COLOR_PAIR(1));
		screen.drawText((posY/2-2) +2*selectedOption, posX/2 - (options[selectedOption].length()/2), options[selectedOption].c_str());
		screen.attrOff(COLOR_PAIR(1));
		
		// Prende l'input dell'utente e cambia la selezione
		switch (screen.getinput()) {
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
				selectedOption = 27;
				isSelected = true;
				break;
			case 10: 
				isSelected = true;
				break;
			default: 
				break;
		}
		
	}
	return selectedOption;
}