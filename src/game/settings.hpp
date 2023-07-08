#include <ncurses.h>
#include "../draw/draw.hpp"
#include <string>

#ifndef GAME_SETTINGS
#define GAME_SETTINGS


class Settings
{
    private:
        nostd::string controls[8] = {
            "Move left: ", "Move right: ", "Jump left: ", "Jump right: ", 
            "Jump vertical: ",  "Shoot left: ", "Shoot right: ",  "Special: "
        };
        nostd::string options[4] = {
            "Controls", "Calibration", "Audio", "Sensibility"
        };

        //It's a string for semplicity in I/O. The last char is \0
        char keybinds[9];

        int pressure_calibration;
        int volume_level;
        int sensitivity_level;

    public:
        Settings();

        void resetControls();
        const char* getControlsKeys();
        int getCalibration();
        int getVolume();
        int getSensitivity();

        void setControlsKeys(int pos, char val);
        void setControlsKeys(const char* s);
        void setCalibration(int n);
        void setVolume(int n);
        void setSensitivity(int n);


        /* --------------- DA RIFARE --------------- */
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
