#include <fstream>
#include <chrono>
#include <iomanip>
#include "../maps/map.hpp"
#include "../../etc/nostd/string.hpp"
#include "../../etc/logs/logs.hpp"
#include "settings.hpp"
#include "global.hpp"

#ifndef GAME_FILE
#define GAME_FILE

class File
{
	private:
		static bool openFile(std::fstream* file,std::string path,std::string mode="rw"); // mode can be r,w,rw,app; default is rw
		static bool exist(std::fstream* file,std::string path);
		static void appendSave(Map m,std::string name);
		static void updateSave(Map m);
	public:
		File();
		static void initSettings();
		static void saveSettings();
		static bool isAlreadySaved(Map m);
		static void saveMap(Map m,std::string name="");
		static void changeName(std::string oldName,std::string newName);
		static nostd::vector<std::string> getNames();
		static nostd::vector<std::string> getLastSave();
		static bool nameAlreadyInUse(std::string name);
		static Map getMap(std::string name);
		static void getSettings();
};

#endif
