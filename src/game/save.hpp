#include <ncurses.h>
#include "../draw/draw.hpp"

#ifndef SAVE_HPP
#define SAVE_HPP

class Save {
    public: 
        void saveGame(Draw screen);

        void quitGame(Draw screen);
};



#endif