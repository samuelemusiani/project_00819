#include "global.hpp"
#include "../../etc/nostd/string.hpp"

int SETTINGS_VOLUME_LEVEL = 20;
int SETTINGS_SENSITIVITY_LEVEL = 10;
nostd::string SETTINGS_CONTROL_KEYS[8] = {"s", "d", "a", "f", "o", "p", "v", "esc"};
bool SETTINGS_IS_CALIBRATED = false;
int SETTINGS_PRESSURE_CALIBRATION = 0;