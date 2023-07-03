#include <ncurses.h>
#include "../draw/draw.hpp"
#include <string>

#ifndef GAME_SETTINGS
#define GAME_SETTINGS


class Settings
{
    private:
        nostd::string controls[8] = {"Move left: ", "Move right: ", "Jump left: ", "Jump right: ", "Shoot: ",  "Bomb: ", "Jump: ",  "Other: "};
        nostd::string options[4] = {"Controls", "Calibration", "Audio", "Sensibility"};
        
    public:
        //Settings();
        //~Settings();
        void drawFirstSettings(Draw settings);
        void ControlKeys(Draw settings);
        void calibrateKeys(Draw settings);

        // controlla se esiste il file dei salvataggi per controllare se è stata fatta la calibrazione
        bool checkifcalibrated(Draw settings);

        // funzione getkeys
        void changeKeys(Draw settings);

        bool is_alpha(int ch);
};

#endif