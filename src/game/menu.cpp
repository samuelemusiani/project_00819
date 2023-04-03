#include "menu.hpp"

Menu::Menu(int LINES, int COLS) {
	this->posY =  LINES/2 - NUMBER_OF_OPTIONS/2;
	this->posX = COLS/2;
}

void Menu::drawMenu() {
	// Disegna una box attorno allo schermo
	box(stdscr, 0, 0);

	// Scrive il titolo del gioco
	Draw::drawText(3, (COLS)/2 - 4 , "JumpKing");

	// Crea un rettangolo di trattini attorno a JumpKing
	Draw::drawText(2, (COLS - 18)/2, "------------------");
	Draw::drawText(4, (COLS - 18)/2, "------------------");
	Draw::drawText(3, (COLS - 18)/2, "|");
	Draw::drawText(3, (COLS + 15)/2, "|");

	for (int i = 0 ; i < NUMBER_OF_OPTIONS; i++)
	{
		Draw::drawText(posY + 2*i , posX - options[i].length()/2, options[i].c_str());
	}
}


int Menu::get_selected_option() //return the selected option
{
	int selectedOption = 0;
	bool isSelected = false;
	while (!isSelected) {

		//clear the WINDOW
		Draw::clearWindow(stdscr);

		// Display the Menu Options
		Menu::drawMenu();

		// Highlight the selected option with a different color
		Draw::attribute_on(stdscr, A_REVERSE);
		Draw::drawText(posY + 2*selectedOption, posX - options[selectedOption].length()/2, options[selectedOption].c_str());
		Draw::attribute_off(stdscr, A_REVERSE);

		// Takes Users input
		switch (getch()) {
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
			case 27:
				selectedOption = -1;
				isSelected = true;
				break;
			default:
				break;
		}
	}
	return(selectedOption);
}
