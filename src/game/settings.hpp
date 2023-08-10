/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Argonni Emanuele #0001078626
 *
 * settings.hpp: Class for the settings menu
 */

#include "../../etc/audio/audio.hpp"
#include "../draw/draw.hpp"

#include <ncurses.h>
#include <string>

#ifndef GAME_SETTINGS
#define GAME_SETTINGS

class Settings {
private:
  nostd::string controls[8] = {
      "Move left: ",     "Move right: ", "Jump left: ",   "Jump right: ",
      "Jump vertical: ", "Shoot left: ", "Shoot right: ", "Special: "};
  nostd::string options[4] = {"Controls", "Calibration", "Audio",
                              "Sensibility"};

  // It's a string for semplicity in I/O. The last char is \0
  char keybinds[9];

  int pressure_calibration;
  int volume_level;
  int sensitivity_level;

  bool is_used(int ch);

  void ControlKeys(Draw *settings);
  void calibrateKeys(Draw *settings);

  // controlla se esiste il file dei salvataggi per controllare se è stata fatta
  // la calibrazione
  bool checkifcalibrated(Draw *settings);

  // funzione getkeys
  void changeKeys(Draw *settings);

  bool is_alpha(int ch);

public:
  Settings();

  void resetControls();
  const char *getControlsKeys();
  int getCalibration();
  int getVolume();
  int getSensitivity();

  void setControlsKeys(int pos, char val);
  void setControlsKeys(const char *s);
  void setCalibration(int n);
  void setVolume(int n);
  void setSensitivity(int n);

  void drawFirstSettings(Audio &audio);
};

#endif
