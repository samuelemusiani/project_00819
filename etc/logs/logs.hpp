#include <fstream>
#include <string>

#ifndef LOGS_LOGS
#define LOGS_LOGS

namespace deb {
    void debug(int x);
    void debug(double x);
    void debug(float x);
    void debug(char x);
    void debug(std::string x);
    void debug(void *x);
}

#endif