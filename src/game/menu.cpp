#include "menu.hpp"
#include "game.hpp"


Menu::Menu(int LINES, int COLS) {
	posY =  LINES/2 - NUMBER_OF_OPTIONS/2;
	posX = COLS/2;
	}

int Menu::drawMenu() //return the selected option
{
	// Disegna una box attorno allo schermo
	box(stdscr, 0, 0);

	// Scrive il titolo del gioco
	Draw::drawText(3, (COLS)/2 - 4 , "JumpKing");

	// Crea un rettangolo di trattini attorno a JumpKing
	Draw::drawText(2, (COLS - 18)/2, "------------------");
	Draw::drawText(4, (COLS - 18)/2, "------------------");
	Draw::drawText(3, (COLS - 18)/2, "|");
	Draw::drawText(3, (COLS + 15)/2, "|");

	while (!flag) {
		// Display the Menu Options
		for (int i = 0 ; i < NUMBER_OF_OPTIONS; i++)
		{
			Draw::drawText(posY + 2*i , posX - options[i].length()/2, options[i].c_str());
		}
		// Highlight the selected option with a different color
		attron(A_REVERSE);
		mvprintw(posY + 2*selectedOption, posX - options[selectedOption].length()/2, options[selectedOption].c_str());
		attroff(A_REVERSE);
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
				this->flag = true;
				break;
			default:
				break;
		}
	}
	return(selectedOption);
}
