#include "settings.hpp"
#include <ncurses.h>
#include "../../etc/logs/logs.hpp"
/*Settings::Settings()
{

}
/*
Settings::~Settings()
{
    endwin();
}
*/
void Settings::drawFirstSettings(Draw settings){
    // create button with (controls, calibration, audio) using swtich and wattron
    settings.clearScreen();
    nostd::string options[3] = {"Controls", "Calibration", "Audio"};
    settings.refreshScreen();
        int selectedOption = 0;
    bool selected = false;
    while (!selected){
        settings.clearScreen();
        settings.drawText(3, (Draw::centerX("Settings")), "Settings");
        for (int i = 0; i < 3; i++){
            settings.drawText(10 + 3*i, 45, options[i]);
        }
        settings.attrOn(COLOR_PAIR(1));
        settings.drawText(10 + 3*selectedOption, 45, options[selectedOption]);
        settings.attrOff(COLOR_PAIR(1));
        switch (settings.getinput()){
            case KEY_LEFT:
                if (selectedOption > 0){
                    selectedOption = selectedOption - 1;
                }
                break;
            case KEY_RIGHT:
                if (selectedOption < 2){
                    selectedOption = selectedOption + 1;
                }
                break;
            case 27:
                selected = true;
                break;
            case 10:
                switch (selectedOption){
                    case 0:
                        drawSettings(settings);
                        break;
                    case 1:
                        calibrateKeys(settings);
                        settings.drawText(10, 10, "omar");
                        settings.refreshScreen();
    
                        break;
                    case 2:
                        //drawAudioSettings(settings);
                        break;
                }
                selected = true;
                break;
        }
    }

}

void Settings::drawSettings(Draw settings){
    
    settings.clearScreen(); 
    settings.drawText(3, (Draw::centerX("Settings")), "Settings");
    int selectedOption = 0;
    bool selected = false;
    while (!selected){
        int a = 0;
        for (int i = 0; i < 2; i++){
            for (int j = 0; j < 4; j++){
                settings.drawText(10 + 3*j, 45 + 45*i, controls[a]);
                // Una volta implementata la funziona drawSquare userò quella
                settings.drawSquareAround(keys[a], 10 + 3*j, 60 + 45*i);
                
                settings.drawText(10 + 3*j, 60 + 45*i, keys[a]);
                a = a +1; 
            }
        }
        settings.drawText(30, 60, "Calibration pressure: ");

        settings.attrOn(COLOR_PAIR(1));
        if (selectedOption < 4) settings.drawText(10 + 3*selectedOption, 60, keys[selectedOption]);
        else settings.drawText(10 + 3*(selectedOption - 4), 105, keys[selectedOption]);
        settings.attrOff(COLOR_PAIR(1));
        switch (settings.getinput()){
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
                settings.drawText(6, (Draw::centerX("Press the key you want to use")), "Press the key you want to use: ");
                // implementare funzione che cambia i tasti
                selected = true;
                settings.getinput();
                break;
        }

    }
    
    
}

int Settings::calibrateKeys(Draw settings){
    settings.eraseScreen();
    settings.drawText(6, 70, "Keep pressing a key until this bar is full");
    settings.nodel(true);
    settings.refreshScreen();
    bool finished = false;
    double mediakey = 20; 
    unsigned int errorkey = 0;
    int keypressed = 0;
    for (int i = 0; i < 1000; i++) {
        deb::debug((int)keypressed);
        int key = settings.getinput();
        if (key == ERR) {
            errorkey++;
        } else {
            keypressed ++; 
            errorkey = 0;
        }
        for (int j = 0; j < i /100; j++)
            settings.drawText(10, 70 + j, "#");


        settings.refreshScreen();        
        napms(5);

    
    }
}