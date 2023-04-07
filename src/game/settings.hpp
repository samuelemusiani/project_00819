#include <ncurses.h>
#include "../draw/draw.hpp"
#include <string>

class Settings
{
    private:
        Draw settings;
        std::string controls[8] = {"Move up: ", "Shoot: ", "Move down: ", "Bomb: ", "Move left: ", "Jump: ", "Move right: ",  "Other: "};
        std::string keys[8] = {"W", "O", "S", "P", "A" , "SPACE", "D", "ESC"};
        
    public:
        //Settings();
        //~Settings();
        void drawSettings();
};