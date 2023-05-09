#include "settings.hpp"
#include "global.hpp"
#include <ncurses.h>
#include "file.hpp"
#include "../../etc/logs/logs.hpp"
#include <locale>

void Settings::drawFirstSettings(Draw screen){
    // Variabili interne alla funzione
    int selectedOption = 0;
    bool saved = false;

    while (!saved){
        screen.eraseScreen();

        // Disegno le opzioni
        screen.drawText(3, (Draw::centerX("Settings")), "Settings");
        for (int i = 0; i < 4; i++){
            screen.drawText(10 + 3*i, 45, options[i]);
        }

        // Coloro l'opzione selezionata
        screen.attrOn(COLOR_PAIR(1));
        screen.drawText(10 + 3*selectedOption, 45, options[selectedOption]);
        screen.attrOff(COLOR_PAIR(1));

        // Disegno le barre
        for (int i = 0; i < 2; i++)
        {
            int tmp = i == 0 ? SETTINGS_VOLUME_LEVEL : SETTINGS_SENSITIVITY_LEVEL;

            for (int j = 0; j < tmp; j++)
                screen.drawText(16 + i*3, 66 + j, "#");

            screen.drawText(16 + i*3, 65, "[");
            screen.drawText(16 + i*3, 65 + 21, "]");
        }

        screen.refreshScreen();

        int input = screen.getinput();

        if (input == KEY_UP)
            selectedOption = std::max(0, selectedOption - 1);
        else if (input == KEY_DOWN)
        {
            // 3 Rapprenta il numero di opzioni (4 - 1). Andrebbe in una variabile a parte
            selectedOption = std::min(3, selectedOption + 1);
        }
        else if (input == KEY_LEFT || input == KEY_RIGHT)
        {
            int delta = input == KEY_LEFT ? -1 : 1;

            // DA RIFARE

            if (selectedOption == 2)
            {
                SETTINGS_VOLUME_LEVEL += delta;
                SETTINGS_VOLUME_LEVEL = std::min(MAX_VOLUME_LEVEL, SETTINGS_VOLUME_LEVEL);
                SETTINGS_VOLUME_LEVEL = std::max(MIN_VOLUME_LEVEL, SETTINGS_VOLUME_LEVEL);
            }
            else if (selectedOption == 3)
            {
                SETTINGS_SENSITIVITY_LEVEL += delta;
                SETTINGS_SENSITIVITY_LEVEL = std::min(MAX_SENSITIVITY_LEVEL, SETTINGS_SENSITIVITY_LEVEL);
                SETTINGS_SENSITIVITY_LEVEL = std::max(MIN_SENSITIVITY_LEVEL, SETTINGS_SENSITIVITY_LEVEL);
            }
        } 
        else if (input == 10)
        {
            if (selectedOption == 0)
                ControlKeys(screen);
            else if (selectedOption == 1)
                calibrateKeys(screen);
        }
        else if (input == 27)
        {
            // SOLUZIONE MOMENTANEA

            // In realtà andrebbe fatto un check se le impostazioni
            // sono state salvate e quindi aggiungere un tastos

            File::saveSettings();
            saved = true;
        }
    }
}

void Settings::ControlKeys(Draw settings){
    
    settings.clearScreen(); 
    int selectedOption = 0;
    bool selected = false;
    while (!selected){
        int a = 0;
        settings.eraseScreen();
        settings.drawText(3, (Draw::centerX("Controls")), "Controls");
        settings.drawText(30, Draw::centerX("Press 'tab' to reset controls"), "Press 'tab' to reset controls");
        for (int i = 0; i < 2; i++){
            for (int j = 0; j < 4; j++){
                settings.drawText(10 + 3*j, 45 + 45*i, controls[a]);
                // Una volta implementata la funziona drawSquare userò quella
                settings.drawSquareAround(SETTINGS_CONTROL_KEYS[a], 10 + 3*j, 60 + 45*i);
                
                settings.drawUpperText(10 + 3*j, 60 + 45*i, SETTINGS_CONTROL_KEYS[a] );
                a = a +1; 
            }
        }
        settings.attrOn(COLOR_PAIR(1));
        if (selectedOption < 4) settings.drawUpperText(10 + 3*selectedOption, 60, SETTINGS_CONTROL_KEYS[selectedOption]);
        else settings.drawUpperText(10 + 3*(selectedOption - 4), 105, SETTINGS_CONTROL_KEYS[selectedOption]);
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
            case 10:{
                settings.drawText(6, (Draw::centerX("Press the key you want to use")), "Press the key you want to use: ");
                int x = settings.getinput();
                deb::debug("xstr: " , nostd::to_string(x));
                deb::debug("char(x): ", nostd::to_string(char(x)));
                if (is_alpha(x)) SETTINGS_CONTROL_KEYS[selectedOption] = char(x);
                break;
            }
            case 9:
            {
                resetControls();
                break;
            }
            default:
                break;
        }

    }
    
}

void Settings::resetControls(){
    SETTINGS_CONTROL_KEYS[0] = 's';
    SETTINGS_CONTROL_KEYS[1] = 'd';
    SETTINGS_CONTROL_KEYS[2] = 'a';
    SETTINGS_CONTROL_KEYS[3] = 'f';
    SETTINGS_CONTROL_KEYS[4] = 'v';
    SETTINGS_CONTROL_KEYS[5] = 'o';
    SETTINGS_CONTROL_KEYS[6] = 'p';
    SETTINGS_CONTROL_KEYS[7] = 'm';
}

bool Settings::is_alpha(int ch){
    return (ch >= 'a' && ch <= 'z');
}


void Settings::calibrateKeys(Draw settings){
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
    settings.drawText(12, 69, "[");
    settings.drawText(12, 80, "]");
    for (int i = 0; i < 1000; i++) {
        int key = settings.getinput();
        if (key == ERR) {
            errorkey++;
        } else {
            keypressed ++; 
            errorkey = 0;
        }
        for (int j = 0; j < i /100; j++)
            settings.drawText(12, 70 + j, "#");

        settings.refreshScreen();        
        napms(5);

    
    }
    if (keypressed < 30) {
        settings.drawText(12, settings.centerX("Calibration failed!"), "Calibration failed!");
        keypressed = 0;
    }
    else settings.drawText(12, settings.centerX("Calibration completed!"), "Calibration completed!");
    settings.refreshScreen();
    settings.nodel(false);
    napms(1800);
    SETTINGS_PRESSURE_CALIBRATION = keypressed;
}
