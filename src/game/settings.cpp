#include "settings.hpp"
#include "../../etc/logs/logs.hpp"
#include "file.hpp"
#include <locale>
#include <ncurses.h>

Settings::Settings()
    : pressure_calibration(-1), volume_level(10), sensitivity_level(10) {
  // used as an initializer
  this->resetControls();
}

void Settings::resetControls() { strcpy(keybinds, "sdafvwemm"); }

const char *Settings::getControlsKeys() { return this->keybinds; }

int Settings::getCalibration() { return pressure_calibration; }

int Settings::getVolume() { return volume_level; }

int Settings::getSensitivity() { return sensitivity_level; }

void Settings::setCalibration(int n) { this->pressure_calibration = n; }

void Settings::setVolume(int n) { this->volume_level = n; }

void Settings::setSensitivity(int n) { this->sensitivity_level = n; }

void Settings::setControlsKeys(int pos, char val) { this->keybinds[pos] = val; }

void Settings::setControlsKeys(const char *s) { strcpy(this->keybinds, s); }

void Settings::drawFirstSettings() {
  Draw screen(SCREEN_HEIGHT, SCREEN_WIDTH);
  // Variabili interne alla funzione
  int selectedOption = 0;
  bool saved = false;

  while (!saved) {
    screen.eraseScreen();

    // Disegno le opzioni
    screen.drawCenterText(3, "Settings");
    for (int i = 0; i < 4; i++) {
      screen.drawText(10 + 3 * i, 45, options[i]);
    }

    // Coloro l'opzione selezionata
    screen.attrOn(COLOR_PAIR(1));
    screen.drawText(10 + 3 * selectedOption, 45, options[selectedOption]);
    screen.attrOff(COLOR_PAIR(1));

    // Disegno le barre
    for (int i = 0; i < 2; i++) {
      int tmp = i == 0 ? volume_level : sensitivity_level;

      for (int j = 0; j < tmp; j++)
        screen.drawText(16 + i * 3, 66 + j, "#");

      screen.drawText(16 + i * 3, 65, "[");
      screen.drawText(16 + i * 3, 65 + 21, "]");
    }

    screen.refreshScreen();

    int input = screen.getinput();

    if (input == KEY_UP)
      selectedOption = std::max(0, selectedOption - 1);
    else if (input == KEY_DOWN) {
      // 3 Rapprenta il numero di opzioni (4 - 1). Andrebbe in una variabile a
      // parte
      selectedOption = std::min(3, selectedOption + 1);
    } else if (input == KEY_LEFT || input == KEY_RIGHT) {
      int delta = input == KEY_LEFT ? -1 : 1;

      // DA RIFARE

      if (selectedOption == 2) {
        volume_level += delta;
        volume_level = std::min(20, volume_level);
        volume_level = std::max(0, volume_level);
      } else if (selectedOption == 3) {
        sensitivity_level += delta;
        sensitivity_level = std::min(20, sensitivity_level);
        sensitivity_level = std::max(0, sensitivity_level);
      }
    } else if (input == 10) {
      if (selectedOption == 0)
        this->ControlKeys(&screen);
      else if (selectedOption == 1)
        calibrateKeys(&screen);
    } else if (input == 27) {
      // SOLUZIONE MOMENTANEA

      // In realtà andrebbe fatto un check se le impostazioni
      // sono state salvate e quindi aggiungere un tastos

      File::saveSettings(*this);
      saved = true;
    }
  }
}

void Settings::ControlKeys(Draw *screen) {

  screen->clearScreen();
  int selectedOption = 0;
  bool selected = false;
  while (!selected) {
    int a = 0;
    screen->eraseScreen();
    screen->drawCenterText(3, "Controls");
    screen->drawCenterText(30, "Press 'tab' to reset controls");
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 4; j++) {
        screen->drawText(10 + 3 * j, 45 + 45 * i, controls[a]);
        // Una volta implementata la funziona drawSquare userò quella
        screen->drawSquareAround(keybinds[a], 10 + 3 * j, 60 + 45 * i);

        screen->drawUpperText(10 + 3 * j, 60 + 45 * i, keybinds[a]);
        a = a + 1;
      }
    }
    screen->attrOn(COLOR_PAIR(1));
    if (selectedOption < 4)
      screen->drawUpperText(10 + 3 * selectedOption, 60,
                            keybinds[selectedOption]);
    else
      screen->drawUpperText(10 + 3 * (selectedOption - 4), 105,
                            keybinds[selectedOption]);
    screen->attrOff(COLOR_PAIR(1));
    switch (screen->getinput()) {
    case KEY_UP:
      if (selectedOption > 0) {
        selectedOption = selectedOption - 1;
      }
      break;
    case KEY_DOWN:
      if (selectedOption < 7) {
        selectedOption = selectedOption + 1;
      }
      break;
    case KEY_LEFT:
      if (selectedOption > 3) {
        selectedOption = selectedOption - 4;
      }
      break;
    case KEY_RIGHT:
      if (selectedOption < 4) {
        selectedOption = selectedOption + 4;
      }
      break;
    case 27:
      selected = true;
      break;
    case 10: { // <ENTER> to change a key
      screen->drawCenterText(6, "Press the key you want to use: ");
      int x = screen->getinput();
      if (this->is_alpha(x)) {
        if (!this->is_used(x))
          keybinds[selectedOption] = char(x);
        else if (keybinds[selectedOption] != x) {
          // This could be done a lot better but only if
          // we start to use colors in the whole game
          screen->clearLine(6, 0);
          init_pair(20, COLOR_RED, COLOR_BLACK);
          screen->attrOn(COLOR_PAIR(20));
          screen->drawCenterText(6, "THE KEY IS ALREADY IN USE");
          screen->attrOff(COLOR_PAIR(20));
          screen->getinput();
        }
      }
      break;
    }
    case 9: // <TAB> to reset
    {
      resetControls();
      break;
    }
    default:
      break;
    }
  }
}

bool Settings::is_used(int ch) {
  bool found = false;

  int i = 0;
  while (!found && i < 8) {
    found = this->keybinds[i] == ch;
    i++;
  }
  return found;
}

bool Settings::is_alpha(int ch) { return (ch >= 'a' && ch <= 'z'); }

void Settings::calibrateKeys(Draw *screen) {
  screen->eraseScreen();
  screen->drawCenterText(6, "Keep pressing the key!");
  screen->drawCenterText(8, "Calibration in progress...");
  screen->refreshScreen();
  bool finished = false;
  double mediakey = 20;
  unsigned int errorkey = 0;
  int keypressed = 0;
  screen->getinput();
  screen->nodel(true);
  screen->drawText(12, 69, "[");
  screen->drawText(12, 80, "]");
  for (int i = 0; i < 1000; i++) {
    int key = screen->getinput();
    if (key == ERR) {
      errorkey++;
    } else {
      keypressed++;
      errorkey = 0;
    }
    for (int j = 0; j < i / 100; j++)
      screen->drawText(12, 70 + j, "#");

    screen->refreshScreen();
    napms(5);
  }
  if (keypressed < 30) {
    screen->drawCenterText(12, "Calibration failed!");
    keypressed = 0;
  } else
    screen->drawCenterText(12, "Calibration completed!");
  screen->refreshScreen();
  screen->nodel(false);
  napms(1800);
  pressure_calibration = keypressed;
}
