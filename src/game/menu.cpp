#include "menu.hpp"

Menu::Menu(int LINES, int COLS) {
    posY =  LINES/2 - NUMBER_OF_OPTIONS/2;
    posX = COLS/2;
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

    // Scrive le opzioni del menu
    for (int i = 0 ; i < NUMBER_OF_OPTIONS; i++)
    {
        Draw::drawText(posY + 2*i , posX - options[i].length()/2, options[i].c_str());
        
    }
    
    
}

