#include <fstream>
#include <string>
#include "../../src/physics/point.hpp"

#ifndef LOGS_LOGS
#define LOGS_LOGS

namespace deb {
    void debug(int x,std::string id="no_id");
    void debug(double x,std::string id="no_id");
    void debug(float x,std::string id="no_id");
    void debug(char x,std::string id="no_id");
    void debug(std::string x,std::string id="no_id");
    void debug(void *x,std::string id="no_id");
    void debug(phy::Point x,std::string id="no_id");
}

#endif
