#include <ncurses.h>

#include "file.hpp"
#include "statistics.hpp"
#include "../entity/manager.hpp"
#include "../draw/draw.hpp"

#ifndef SAVE_HPP
#define SAVE_HPP

class Save {
    private: 
        bool alreadySaved; // per controllare se esiste già il nome del file di salvataggio
        nostd::string nome;
    public: 
        void saveNewGame(Draw* screen, Map& map, int& chunk, phy::Body& player, 
                Statistics& stats, Manager& manager);
        void saveGame(Draw* saved);

        void quitGame(Draw* screen, Map& map, int& chunk, phy::Body& player, 
                Statistics& stats, Manager& manager);
};


#endif
