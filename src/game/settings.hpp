#include <ncurses.h>
#include "../draw/draw.hpp"
#include <string>

class Settings
{
    private:
        nostd::string controls[8] = {"Move up: ", "Move down: ", "Move left: ", "Move right: ", "Shoot: ",  "Bomb: ", "Jump: ",  "Other: "};
        nostd::string keys[8] = {"W", "S", "A", "D", "O", "P", "SPACE", "ESC"};
        
    public:
        //Settings();
        //~Settings();
        void drawFirstSettings(Draw settings);
        void drawSettings(Draw settings);
        int calibrateKeys(Draw settings);

        // controlla se esiste il file dei salvataggi per controllare se è stata fatta la calibrazione
        bool checkifcalibrated(Draw settings);
        
        // disegna una barra di # per la regolazione del volume e sensibilità
        int drawBarSettings(Draw settings, int y);
};