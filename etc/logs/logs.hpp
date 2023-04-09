#include <fstream>
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
