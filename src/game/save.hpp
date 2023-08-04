/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Argonni Emanuele #0001078626
 *
 * save.hpp: Class for the saving menu
 */

#include <ncurses.h>

#include "../engine/manager.hpp"
#include "../market/market.hpp"
#include "file.hpp"
#include "statistics.hpp"

#ifndef SAVE_HPP
#define SAVE_HPP

class Save {
private:
  bool alreadySaved; // per controllare se esiste già il nome del file di
                     // salvataggio
  nostd::string nome;

public:
  void saveNewGame(Map &map, int &chunk, phy::Body &player, Statistics &stats,
                   Manager &manager, Market &market);
  void game_saved_banner();

  void quitGame(Map &map, int &chunk, phy::Body &player, Statistics &stats,
                Manager &manager, Market &market);
};

#endif
