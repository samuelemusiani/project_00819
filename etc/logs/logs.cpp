/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Peronese Lorenzo #0001081726
 *
 * logs.cpp: Implementation of the Logs class
 */

#include "logs.hpp"

static std::string debugLogPath = "./logs.txt";
static std::fstream debugLogFile;

static auto dateAndTime() {
  time_t now =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  return (std::put_time(localtime(&now), "%F %T"));
}

static bool openDebugFile(std::fstream *file) {
  file->open(debugLogPath, std::ios::app);
  return (file->is_open());
}

void deb::debug(int x, nostd::string id) {
  if (openDebugFile(&debugLogFile)) {
    debugLogFile << dateAndTime() << " [" << id << ": " << x << "]\n";
    debugLogFile.close();
  }
}

void deb::debug(double x, nostd::string id) {
  if (openDebugFile(&debugLogFile)) {
    debugLogFile << dateAndTime() << " [" << id << ": " << x << "]\n";
    debugLogFile.close();
  }
}

void deb::debug(float x, nostd::string id) {
  if (openDebugFile(&debugLogFile)) {
    debugLogFile << dateAndTime() << " [" << id << ": " << x << "]\n";
    debugLogFile.close();
  }
}

void deb::debug(char x, nostd::string id) {
  if (openDebugFile(&debugLogFile)) {
    debugLogFile << dateAndTime() << " [" << id << ": " << x << "]\n";
    debugLogFile.close();
  }
}

void deb::debug(nostd::string x, nostd::string id) {
  if (openDebugFile(&debugLogFile)) {
    debugLogFile << dateAndTime() << " [" << id << ": " << x << "]\n";
    debugLogFile.close();
  }
}

void deb::debug(phy::Point x, nostd::string id) {
  if (openDebugFile(&debugLogFile)) {
    debugLogFile << dateAndTime() << " [" << id << ": " << x.get_xPosition()
                 << "," << x.get_yPosition() << "]\n";
    debugLogFile.close();
  }
}

void deb::debug(void *x, nostd::string id) {
  if (openDebugFile(&debugLogFile)) {
    debugLogFile << dateAndTime() << " [" << id << ": " << x << "]\n";
    debugLogFile.close();
  }
}
