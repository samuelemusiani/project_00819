#include <ncurses.h>
#include "../draw/draw.hpp"
#include <string>

class Settings
{
    private:
        std::string controls[8] = {"Move up: ", "Move down: ", "Move left: ", "Move right: ", "Shoot: ",  "Bomb: ", "Jump: ",  "Other: "};
        std::string keys[8] = {"W", "S", "A", "D", "O", "P", "SPACE", "ESC"};
        
    public:
        //Settings();
        //~Settings();
        void drawSettings(Draw settings);
};