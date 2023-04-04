#include "logs.hpp"
#include <iomanip>
#include <chrono>

static std::string debugLogPath = "./logs.txt";
static std::fstream debugLogFile;

static auto dateAndTime()
{
    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    return (std::put_time(localtime(&now), "%F %T"));
}

static bool openDebugFile(std::fstream* file)
{
    file->open(debugLogPath,std::ios::app);
    return (file->is_open());
}

void deb::debug(int x)
{
    if(openDebugFile(&debugLogFile)) {
        debugLogFile << dateAndTime() << " [" << x << "]\n";
        debugLogFile.close();
    }
}

void deb::debug(double x)
{
    if(openDebugFile(&debugLogFile)) {
        debugLogFile << dateAndTime() << " [" << x << "]\n";
        debugLogFile.close();
    }
}

void deb::debug(float x)
{
    if(openDebugFile(&debugLogFile)) {
        debugLogFile << dateAndTime() << " [" << x << "]\n";
        debugLogFile.close();
    }
}

void deb::debug(char x)
{
    if(openDebugFile(&debugLogFile)) {
        debugLogFile << dateAndTime() << " [" << x << "]\n";
        debugLogFile.close();
    }
}

void deb::debug(std::string x)
{
    if(openDebugFile(&debugLogFile)) {
        debugLogFile << dateAndTime() << " [" << x << "]\n";
        debugLogFile.close();
    }
}

void deb::debug(void *x)
{
    if(openDebugFile(&debugLogFile)) {
        debugLogFile << dateAndTime() << " [" << x << "]\n";
        debugLogFile.close();
    }
}
