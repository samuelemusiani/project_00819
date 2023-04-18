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
    nostd::string options[4] = {"Controls", "Calibration", "Audio", "Sensibility"};
    settings.refreshScreen();
    int selectedOption = 0;
    bool selected = false;
    while (!selected){
        settings.eraseScreen();
        settings.drawText(3, (Draw::centerX("Settings")), "Settings");
        for (int i = 0; i < 4; i++){
            settings.drawText(10 + 3*i, 45, options[i]);
        }
        settings.attrOn(COLOR_PAIR(1));
        settings.drawText(10 + 3*selectedOption, 45, options[selectedOption]);
        settings.attrOff(COLOR_PAIR(1));
        settings.refreshScreen();
        switch (settings.getinput()){
            case KEY_UP:
                if (selectedOption > 0){
                    selectedOption = selectedOption - 1;
                }
                break;
            case KEY_DOWN:
                if (selectedOption < 3){
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
                        break;
                    case 2:
                        {// Disegno la barra per la regolazione del volume
                        int volume = drawBarSettings(settings, 16);
                        break;
                        }
                    case 3:
                        {
                        // Disegno la barra per la regolazione della sensibilità
                        int sensitivity = drawBarSettings(settings, 19);
                        break;
                        }

                }
                
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

bool Settings::checkifcalibrated(Draw settings){
    // fa un check se esiste il file e se è già stata calibrata
    return true;
}

int Settings::calibrateKeys(Draw settings){
    settings.eraseScreen();
    settings.drawText(6, settings.centerX("Keep pressing the key!"), "Keep pressing the key!");
    settings.drawText(8, settings.centerX("Calibration in progress..."), "Calibration in progress...");
    settings.refreshScreen();
    bool finished = false;
    double mediakey = 20; 
    unsigned int errorkey = 0;
    int keypressed = 0;
    settings.getinput();
    settings.nodel(true);
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
    if (keypressed < 40) settings.drawText(12, settings.centerX("Calibration failed!"), "Calibration failed!");
    else settings.drawText(12, settings.centerX("Calibration completed!"), "Calibration completed!");
    settings.refreshScreen();
    napms(1800);
    settings.nodel(false);
    return keypressed; 
}

int Settings::drawBarSettings(Draw settings, int y){
    std::string bar = "#########";
    int ch;
    bool saved = false; 
    settings.drawText(y, 66, bar.c_str());
    settings.drawText(y, 65, "[");
    settings.drawText(y, 85, "]");
    while (!saved) {
        ch = settings.getinput();
        if (ch == KEY_LEFT) { // backspace key
            if (!bar.empty()) {
                bar.pop_back();
                settings.clearLine(y, 66); 
                settings.drawText(y, 66, bar.c_str());
                settings.drawText(y, 85, "]");
                settings.refreshScreen();
            }
        } 
        else if (ch == KEY_RIGHT && bar.length() < 19){ // 32 = space
                bar += "#";
                settings.drawText(y, 66, bar.c_str());
                settings.refreshScreen();
            }
        if (ch == 10)  {
            // TODO: salvare la lunghezza della stringa in un file
            // bar.length()
            saved = true; 
            settings.refreshScreen();
            settings.eraseScreen();
        }
    }
    return bar.length();
}