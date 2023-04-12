#include "settings.hpp"
#include <ncurses.h>

/*Settings::Settings()
{

}
/*
Settings::~Settings()
{
    wgetch(win);
    endwin();
}
*/
void Settings::drawSettings(Draw settings){
    
    settings.clearScreen(); 
    settings.drawText(3, 75 - (Draw::centerX("Settings")), "Settings");
    int selectedOption = 0;
    bool selected = false;
    while (!selected){
        int a = 0;
        for (int i = 0; i < 2; i++){
            for (int j = 0; j < 4; j++){
                settings.drawText(10 + 3*j, 45 + 45*i, controls[a]);
                // Una volta implementata la funziona drawSquare userò quella
                settings.drawSquare(keys[a], 10 + 3*j, 60 + 45*i);
                
                settings.drawText(10 + 3*j, 60 + 45*i, keys[a]);
                a = a +1; 
            }
        }
        wattron(win,    COLOR_PAIR(1));
        if (selectedOption < 4) settings.drawText(10 + 3*selectedOption, 60, keys[selectedOption]);
        else settings.drawText(10 + 3*(selectedOption - 4), 105, keys[selectedOption]);
        wattroff(win, COLOR_PAIR(1));
        switch (wgetch(win)){
            case KEY_UP:
                if (selectedOption > 0){
                    selectedOption = selectedOption - 1;
                }
                break;
            case KEY_DOWN:
                if (selectedOption < 7){
                    selectedOption = selectedOption + 1;
                }
                break;
            case KEY_LEFT:
                if (selectedOption > 3){
                    selectedOption = selectedOption - 4;
                }
                break;
            case KEY_RIGHT:
                if (selectedOption < 4){
                    selectedOption = selectedOption + 4;
                }
                break;
            case 27:
                selected = true;
                break;
            case 10:
                settings.drawText(6, 75 - (Draw::centerX("Press the key you want to use")), "Press the key you want to use: ");
                // implementare funzione che cambia i tasti
                selected = true;
                wgetch(win);
                break;
        }

    }
    
    
}