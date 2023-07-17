/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Peronese Lorenzo #0001081726
*
* file.hpp: Class with static methods that interfaces with files
*/

#include <fstream>
#include <chrono>
#include <iomanip>

#include "settings.hpp"
#include "../maps/map.hpp"
#include "../physics/body.hpp"
#include "../game/statistics.hpp"

#include "../../etc/nostd/string.hpp"
#include "../../etc/logs/logs.hpp"

#ifndef GAME_FILE
#define GAME_FILE

class File
{
	private:
		static bool openFile(std::fstream &file,nostd::string path,nostd::string mode="rw"); // mode can be r,w,rw,app; default is rw
		static bool exist(std::fstream &file,nostd::string path);
		static void appendSave(Map m,int chunk,phy::Point pos, Statistics stats, nostd::string enitites, nostd::string market, nostd::string name);
		static void updateSave(Map m,int chunk,phy::Point pos, Statistics stats, nostd::string enitites, nostd::string market);
		static void getSettings(Settings& sett);
public:
		File();
		static void initSettings(Settings& sett);
		static void saveSettings(Settings& sett);
		static bool isCalibrated(Settings& sett);
		static bool isAlreadySaved(Map m);
		static void saveMap(Map m,int chunk,phy::Point pos, Statistics stats, nostd::string entities, nostd::string market, nostd::string name="");
		static void changeName(nostd::string oldName,nostd::string newName);
		static nostd::vector<nostd::string> getNames();
		static nostd::vector<nostd::string> getLastSaves();
		static bool nameAlreadyInUse(nostd::string name);
		static Map getMap(nostd::string name);
		static int getChunk(nostd::string name);
		static phy::Point getPoint(nostd::string name);
		static Statistics getStatistics(nostd::string name);
		static nostd::string getEntitiesStatus(nostd::string name);
		static nostd::string getMarketSave(nostd::string name);
		static void deleteSave(nostd::string name);
		static int countSaves();
};

#endif
