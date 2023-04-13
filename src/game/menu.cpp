#include "menu.hpp"

Menu::Menu(int x, int y) {
	posX = x;
	posY = y;
	
	}
	

void Menu::drawFirstMenu(Draw screen) {
	
	// Disegna la box di colore verde
	screen.clearScreen();

	    bool selected = false;
	screen.nodel(true);
	// crea un foor loop che mette in movimento il testo qui sopra da sinistra a destra 
	for (int i = 0; i < 42 && !selected; i++) {
		screen.drawText(19, i, "     ██╗██╗   ██╗███╗   ███╗██████╗ ");
		screen.drawText(20, i, "     ██║██║   ██║████╗ ████║██╔══██╗");
		screen.drawText(21, i, "     ██║██║   ██║██╔████╔██║██████╔ ");
		screen.drawText(22, i, "██   ██║██║   ██║██║╚██╔╝██║██╔═══╝ ");
		screen.drawText(23, i, "╚█████╔╝╚██████╔╝██║ ╚═╝ ██║██║     ");
		screen.drawText(24, i," ╚════╝  ╚═════╝ ╚═╝     ╚═╝╚═╝      "); 
		screen.drawText(19, 120-i, " ██╗  ██╗██╗███╗   ██╗ ██████╗ ");
		screen.drawText(20, 120-i, " ██║ ██╔╝██║████╗  ██║██╔════╝ ");
		screen.drawText(21, 120-i, " █████╔╝ ██║██╔██╗ ██║██║  ███╗");
		screen.drawText(22, 120-i, " ██╔═██╗ ██║██║╚██╗██║██║   ██║");
		screen.drawText(23, 120-i, " ██║  ██╗██║██║ ╚████║╚██████╔╝");
		screen.drawText(24, 120-i," ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝ "); 
		screen.refreshScreen();
		int x = screen.getinput();
		if (x == 27 || x == 10)
			selected = true;
		napms(50);
		screen.eraseScreen();	
	}
	// un for loop che muove il testo dal centro al centro in alto
	for (int i = 0; i < 16 && !selected; i++) {
		screen.drawText(19-i, 42, "     ██╗██╗   ██╗███╗   ███╗██████╗ ");
		screen.drawText(20-i, 42, "     ██║██║   ██║████╗ ████║██╔══██╗");
		screen.drawText(21-i, 42, "     ██║██║   ██║██╔████╔██║██████╔ ");
		screen.drawText(22-i, 42, "██   ██║██║   ██║██║╚██╔╝██║██╔═══╝ ");
		screen.drawText(23-i, 42, "╚█████╔╝╚██████╔╝██║ ╚═╝ ██║██║     ");
		screen.drawText(24-i, 42," ╚════╝  ╚═════╝ ╚═╝     ╚═╝╚═╝      "); 
		screen.drawText(19-i, 78, " ██╗  ██╗██╗███╗   ██╗ ██████╗ ");
		screen.drawText(20-i, 78, " ██║ ██╔╝██║████╗  ██║██╔════╝ ");
		screen.drawText(21-i, 78, " █████╔╝ ██║██╔██╗ ██║██║  ███╗");
		screen.drawText(22-i, 78, " ██╔═██╗ ██║██║╚██╗██║██║   ██║");
		screen.drawText(23-i, 78, " ██║  ██╗██║██║ ╚████║╚██████╔╝");
		screen.drawText(24-i, 78," ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝ "); 
		screen.refreshScreen();
		int x = screen.getinput();
		if (x == 27 || x == 10)
			selected = true;
		napms(300);
		screen.eraseScreen();	
	}


}

void Menu::drawMenu(Draw screen){
		screen.clearScreen();
		screen.drawText(4, 42, "     ██╗██╗   ██╗███╗   ███╗██████╗ ");
		screen.drawText(5, 42, "     ██║██║   ██║████╗ ████║██╔══██╗");
		screen.drawText(6, 42, "     ██║██║   ██║██╔████╔██║██████╔ ");
		screen.drawText(7, 42, "██   ██║██║   ██║██║╚██╔╝██║██╔═══╝ ");
		screen.drawText(8, 42, "╚█████╔╝╚██████╔╝██║ ╚═╝ ██║██║     ");
		screen.drawText(9, 42," ╚════╝  ╚═════╝ ╚═╝     ╚═╝╚═╝      "); 
		screen.drawText(4, 78, " ██╗  ██╗██╗███╗   ██╗ ██████╗ ");
		screen.drawText(5, 78, " ██║ ██╔╝██║████╗  ██║██╔════╝ ");
		screen.drawText(6, 78, " █████╔╝ ██║██╔██╗ ██║██║  ███╗");
		screen.drawText(7, 78, " ██╔═██╗ ██║██║╚██╗██║██║   ██║");
		screen.drawText(8, 78, " ██║  ██╗██║██║ ╚████║╚██████╔╝");
		screen.drawText(9, 78," ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝ "); 
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