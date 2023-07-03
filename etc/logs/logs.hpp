/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Peronese Lorenzo #0001081726
*
* logs.hpp: Class for debug, prints text in a log file
*/

#include <fstream>
#include <iomanip>
#include <chrono>
#include "../../src/physics/point.hpp"
#include "../nostd/string.hpp"

#ifndef LOGS_LOGS
#define LOGS_LOGS

namespace deb {
    void debug(int x,nostd::string id="no_id");
    void debug(double x,nostd::string id="no_id");
    void debug(float x,nostd::string id="no_id");
    void debug(char x,nostd::string id="no_id");
    void debug(nostd::string x,nostd::string id="no_id");
    void debug(void *x,nostd::string id="no_id");
    void debug(phy::Point x,nostd::string id="no_id");
}

#endif
