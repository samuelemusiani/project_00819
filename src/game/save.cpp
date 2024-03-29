/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Argonni Emanuele #0001078626
 *
 * save.cpp: Class for the saving menu
 */

#include "save.hpp"

void Save::saveNewGame(Map &map, int &chunk, phy::Body &player,
                       Statistics &stats, Manager &manager, Market &market) {
  bool nosaved = false;
  if (File::isAlreadySaved(map)) {
    this->game_saved_banner();
  } else {
    Draw screen(SCREEN_HEIGHT, SCREEN_WIDTH);
    bool exit = false;
    // Check if there are already 5 saves
    if (File::countSaves() > 4) {
      bool deleted = false;
      int selected = 0;
      while (!deleted && !exit) {
        screen.eraseScreen();
        screen.drawCenterText(3, "You can't create more than 5 saves");
        screen.drawCenterText(5, "Delete one your old saved map");
        nostd::vector<nostd::string> savedMaps = File::getNames();
        nostd::vector<nostd::string> savedDate = File::getLastSaves();
        for (int i = 0; i < savedMaps.size(); i++) {
          screen.drawCenterSquareAround(savedMaps[i] + " " + savedDate[i],
                                        13 + 4 * i);
        }

        screen.attrOn(COLOR_PAIR(1));
        screen.drawCenterText(13 + 4 * selected,
                              savedMaps[selected] + " " + savedDate[selected]);
        screen.attrOff(COLOR_PAIR(1));

        switch (screen.getinput()) {
        case KEY_UP:
          if (selected == 0)
            selected = savedMaps.size() - 1;
          else
            selected = selected - 1;
          break;
        case KEY_DOWN:
          if (selected == savedMaps.size() - 1)
            selected = 0;
          else
            selected = selected + 1;
          break;
        case 10:
          File::deleteSave(savedMaps[selected]);
          deleted = true;
          break;
        case 27:
          exit = true;
          nosaved = true;
          break;
        default:
          break;
        }
      }
    }
    // SAVING PROMPT
    if (!exit) {
      screen.eraseScreen();
      screen.drawText(16, 65, "Insert the name of the file: ");
      screen.drawRectagle(19, 64, 2, 30);
      screen.refreshScreen();
      int ch;
      bool saved = false;
      while (!saved) {
        ch = screen.getinput();
        if (ch == 127 ||
            ch == KEY_BACKSPACE) { // 127 on mac, KEY_BACKSPACE on linux
          if (!nome.empty()) {
            nome.pop_back();
            screen.eraseScreen();
            screen.drawText(16, 65, "Insert the name of the file: ");
            screen.drawRectagle(19, 64, 2, 30);
            screen.drawText(20, 66, nome);
            screen.refreshScreen();
          }
        } else if (nome.length() == 27) {
          screen.clearLine(23, 0);
          screen.drawCenterText(23, "Max length reached");
          screen.refreshScreen();
        } else if (nome.empty() == true && ch == 10) {
          screen.clearLine(23, 0);
          screen.drawCenterText(23, "Insert a name");
          screen.refreshScreen();
        } else {
          if (isalnum(ch) && ch != KEY_DOWN && ch != KEY_UP && ch != KEY_LEFT &&
                  ch != KEY_RIGHT ||
              ch == 32) { // 32 = space
            nome.push_back(ch);
            screen.drawText(20, 66, nome);
            screen.refreshScreen();
          } else {
            screen.clearLine(23, 0);
            screen.drawCenterText(23, "Only alphanumeric characters");
            screen.refreshScreen();
          }
        }

        if (nome.length() > 0 && nome.length() < 27) {

          if (isalnum(ch)) {
            screen.clearLine(23, 0);
            screen.attrOn(COLOR_PAIR(1));
            screen.drawCenterText(23, "Press enter to confirm");
            screen.attrOff(COLOR_PAIR(1));
            screen.refreshScreen();
          }
          if (ch == 10) {

            screen.clearLine(23, 0);
            screen.refreshScreen();
            // Qui chiamare la funziona per salvare e se salvato con successo
            // printare File saved se ci sono errori ritornati dalla funzione
            // per salvare printare Error saving file

            // controllare se non esiste già un file con lo stesso nome
            if (File::nameAlreadyInUse(nome))
              screen.drawCenterText(23, "Name already in use");
            else {
              saved = true;
              screen.drawCenterText(23, "File saved");

              screen.attrOn(COLOR_PAIR(1));
              screen.drawCenterText(25, "Press enter to exit");
              screen.attrOff(COLOR_PAIR(1));
              screen.refreshScreen();
              screen.getinput();
              screen.eraseScreen();
            }
          }
        }
      }
    }
  }
  if (!nosaved)
    File::saveMap(map, chunk, player.get_position(), stats,
                  manager.get_entities_status(), market.get_save(), nome);
}

void Save::game_saved_banner() {
  Draw local_screen(5, 20);
  local_screen.eraseScreen();
  local_screen.drawBox();
  local_screen.drawCenterText(2, "Game saved");
  local_screen.refreshScreen();
  local_screen.getinput();
  // napms(2000);
  local_screen.eraseScreen();
  local_screen.deleteWin();
}

void Save::quitGame(Map &map, int &chunk, phy::Body &player, Statistics &stats,
                    Manager &manager, Market &market) {
  Draw quit_scr(15, 55);
  quit_scr.eraseScreen();
  quit_scr.drawBox();
  quit_scr.drawCenterText(2, "Quit without saving?");
  // creare due buttoni yes e no
  bool choose = false;
  int selected = 0;
  nostd::string options[2] = {"Yes", "Save Now"};
  while (!choose) {
    for (int i = 0; i < 2; i++) {
      quit_scr.drawText(8, 18 + 10 * i, options[i].c_str());
    }
    quit_scr.attrOn(COLOR_PAIR(1));
    quit_scr.drawText(8, 18 + 10 * selected, options[selected].c_str());
    quit_scr.attrOff(COLOR_PAIR(1));
    quit_scr.refreshScreen();
    switch (quit_scr.getinput()) {
    case KEY_LEFT:
      if (selected == 0)
        selected = 1;
      else
        selected--;
      break;
    case KEY_RIGHT:
      if (selected == 1)
        selected = 0;
      else
        selected++;
      break;
    case 10:
      choose = true;
      break;
    }
  }
  if (selected == 1) { // Se l'utente vuole salvare prima di uscire
    saveNewGame(map, chunk, player, stats, manager, market);
  }
  quit_scr.eraseScreen();
  quit_scr.deleteWin();
}
