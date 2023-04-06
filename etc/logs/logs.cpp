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

void deb::debug(int x,std::string id)
{
    if(openDebugFile(&debugLogFile)) {
        debugLogFile << dateAndTime() << " [" << id << ": " << x << "]\n";
        debugLogFile.close();
    }
}

void deb::debug(double x,std::string id)
{
    if(openDebugFile(&debugLogFile)) {
        debugLogFile << dateAndTime() << " [" << id << ": " << x << "]\n";
        debugLogFile.close();
    }
}

void deb::debug(float x,std::string id)
{
    if(openDebugFile(&debugLogFile)) {
        debugLogFile << dateAndTime() << " [" << id << ": " << x << "]\n";
        debugLogFile.close();
    }
}

void deb::debug(char x,std::string id)
{
    if(openDebugFile(&debugLogFile)) {
        debugLogFile << dateAndTime() << " [" << id << ": " << x << "]\n";
        debugLogFile.close();
    }
}

void deb::debug(std::string x,std::string id)
{
    if(openDebugFile(&debugLogFile)) {
        debugLogFile << dateAndTime() << " [" << id << ": " << x << "]\n";
        debugLogFile.close();
    }
}

void deb::debug(phy::Point x,std::string id)
{
    if(openDebugFile(&debugLogFile)) {
        debugLogFile << dateAndTime() << " [" << id << ": " << x.get_xPosition() << "," << x.get_yPosition() << "]\n";
        debugLogFile.close();
    }
}

void deb::debug(void *x,std::string id)
{
    if(openDebugFile(&debugLogFile)) {
        debugLogFile << dateAndTime() << " [" << id << ": " << x << "]\n";
        debugLogFile.close();
    }
}
