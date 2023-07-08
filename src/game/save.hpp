#include <ncurses.h>
#include "../draw/draw.hpp"
#include "file.hpp"
#include "statistics.hpp"

#ifndef SAVE_HPP
#define SAVE_HPP

class Save {
    private: 
        bool alreadySaved; // per controllare se esiste già il nome del file di salvataggio
        nostd::string nome;
    public: 
        void saveNewGame(Draw* screen, Map map, int chunk, phy::Point, Statistics stats);
        void saveGame(Draw* saved);

        void quitGame(Draw* screen, Map map, int chunk, phy::Point, Statistics stats);
};


#endif
