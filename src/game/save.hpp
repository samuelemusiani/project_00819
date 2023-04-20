#include <ncurses.h>
#include "../draw/draw.hpp"

#ifndef SAVE_HPP
#define SAVE_HPP

class Save {
    private: 
        bool alreadySaved; // per controllare se esiste già il nome del file di salvataggio
    public: 
        void saveNewGame(Draw screen);
        void saveGame(Draw saved);

        void quitGame(Draw screen);
};



#endif