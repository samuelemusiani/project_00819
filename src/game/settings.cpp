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
void Settings::drawSettings(){
    // DEBUG
    settings.drawBox(); // perchè si cancella da sola prima? 
    settings.drawText(3, 75 - (Draw::centerX("Settings")), "Settings");
    int selectedOption = 0;
    bool selected = false;
    while (!selected){
        int a = 0;
        for (int j = 0; j < 4; j++){
            for (int i = 0; i < 2; i++){
                settings.drawText(10 + 3*j, 45 + 45*i, controls[a]);
                // Una volta implementata la funziona drawSquare userò quella
                mvwaddch(win, 10 + 3*j - 1, 60 + 45*i - 1, ACS_ULCORNER);
                mvwaddch(win, 10 + 3*j - 1, 60 + 45*i + 1, ACS_URCORNER);
                mvwaddch(win, 10 + 3*j + 1, 60 + 45*i - 1, ACS_LLCORNER);
                mvwaddch(win, 10 + 3*j + 1, 60 + 45*i + 1, ACS_LRCORNER);
                mvwaddch(win, 10 + 3*j, 60 + 45*i - 1, ACS_VLINE);
                mvwaddch(win, 10 + 3*j, 60 + 45*i + 1, ACS_VLINE);
                mvwaddch(win, 10 + 3*j - 1, 60 + 45*i, ACS_HLINE);
                mvwaddch(win, 10 + 3*j + 1, 60 + 45*i, ACS_HLINE);
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
                if (selectedOption > 0){
                    selectedOption = selectedOption - 4;
                }
                break;
            case KEY_RIGHT:
                if (selectedOption < 7){
                    selectedOption = selectedOption + 4;
                }
                break;
            case 10:
                settings.drawText(6, 75 - (Draw::centerX("Press the key you want to use")), "Press the key you want to use: ");
                selected = true;
                break;
        }

    }
    wrefresh(win);

}