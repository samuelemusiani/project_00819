#ifndef GAME_GLOBAL
#define GAME_GLOBAL

#include "../../etc/nostd/string.hpp"
#include <string>

#define MAX_VOLUME_LEVEL 20
#define MIN_VOLUME_LEVEL 0

#define MAX_SENSITIVITY_LEVEL 20
#define MIN_SENSITIVITY_LEVEL 0

extern int SETTINGS_VOLUME_LEVEL;
extern int SETTINGS_SENSITIVITY_LEVEL;
extern nostd::string SETTINGS_CONTROL_KEYS[8];
extern bool SETTINGS_CALIBRATED;
extern int SETTINGS_PRESSURE_CALIBRATION;

#endif
