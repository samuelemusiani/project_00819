/*
* Alma Mater Studiorum - University of Bologna
* First cycle degree in Computer Science
* Computer Programming - 00819
*
* Author: Peronese Lorenzo #0001081726
*
* file.cpp: Implementation of the File class
*/

#include "file.hpp"

File::File()
{

}

bool File::openFile(std::fstream &file,nostd::string path,nostd::string mode)
{
	if(mode=="r")
		file.open(path.c_str(),std::ios::in);
	else if(mode=="w")
		file.open(path.c_str(),std::ios::out);
	else if(mode=="app")
		file.open(path.c_str(),std::ios::app);
	else
		file.open(path.c_str(),std::ios::in | std::ios::out);
	return file.is_open();
}

void File::initSettings(Settings& sett) {
	std::fstream file;
	if (!exist(file, "./settings.txt"))
	{
		if (openFile(file, "./settings.txt", "w"))
		{
			file << "[ KeyBindings ]\n";
            //TEMPORANEO
            file << sett.getControlsKeys();
            file << "\n\n[ Preferences ]\nCalibration=-1\nVolume=10\nSensitivity=10\n\n";
			file.close();
		}
	}
	getSettings(sett);
}

void File::saveSettings(Settings& sett) {
    std::fstream file;
    if (openFile(file, "./settings.txt", "w")) {
			file << "[ KeyBindings ]\n";
            //TEMPORANEO
            file << sett.getControlsKeys();

            file << "\n\n[ Preferences ]\nCalibration="
                << sett.getCalibration()
                << "\nVolume=" << sett.getVolume()
                << "\nSensitivity=" << sett.getSensitivity() << "\n";
    }
    file.close();
}

bool File::isCalibrated(Settings& sett)
{
	return sett.getCalibration() != -1 ;
}

bool File::exist(std::fstream &file, nostd::string path)
{
	bool x = openFile(file,path,"r");
	file.close();
	return x;
}

static auto dateAndTime()
{
	time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	return (std::put_time(localtime(&now), "%F %T"));
}

bool File::isAlreadySaved(Map m)
{
	std::fstream file;
	if(openFile(file,"./save.txt","r"))
	{
		nostd::string buff;
		nostd::string tmp = "Seed: "+nostd::to_string(m.getSeed());
		bool found = false;
		while(!found && nostd::getline(file,buff))
			if(buff == tmp)
				found = true;
		file.close();
		return found;
	}
	else
		return false; // file does not exist yet
}

void File::appendSave(Map m,int chunk,phy::Point pos, Statistics stats, nostd::string entities, nostd::string market, nostd::string name)
{
	std::fstream file;
	if(openFile(file,"./save.txt","app")) {
		file << "[ Name: " << name 
             << " ]\nSeed: " << m.getSeed()
		     << "\nChunk: " << chunk 
             << "\nPlayerPos: " << pos.get_xPosition() << "," << pos.get_yPosition()
             << "\nLastSave: " << dateAndTime() 
             << "\nStatistics: " << stats.getLevel() << " " << stats.getCoins() 
                 << " " << stats.getJumps() << " " << stats.getHearts() 
             << "\nEntities: " << entities
             << "\nMarket: " << market << "\n\n";
		file.close();
	}
}

void File::updateSave(Map m,int chunk,phy::Point pos, Statistics stats, nostd::string entities, nostd::string market)
{
	// the only way to do this is to rewrite the entire file
	std::fstream file;
	std::fstream tmp;
	if(openFile(tmp,"./tmp.txt","w") && openFile(file,"./save.txt","r"))
	{
		nostd::string buff;
		bool found=false;
		nostd::string search = "Seed: "+nostd::to_string(m.getSeed());
		while(!found && nostd::getline(file,buff))
		{
			tmp << buff << "\n";
			if(buff==search)
				found=true;
		}
		nostd::getline(file,buff);
		tmp << "Chunk: " << chunk << "\n";
		nostd::getline(file,buff);
		tmp << "PlayerPos: " << pos.get_xPosition() << "," << pos.get_yPosition() << "\n";
		nostd::getline(file,buff);
		tmp << "LastSave: " << dateAndTime() << "\n";
		nostd::getline(file,buff);
        tmp << "Statistics: " << stats.getLevel() << " " << stats.getCoins() 
                << " " << stats.getJumps() << " " << stats.getHearts() << "\n";
		nostd::getline(file,buff);
		tmp << "Entities: " << entities << "\n";
		nostd::getline(file,buff);
		tmp << "Market: " << market << "\n";

		while(nostd::getline(file,buff))
			tmp << buff << "\n";
		file.close();
		tmp.close();
		rename("./tmp.txt","./save.txt");
	}
}

void File::saveMap(Map m, int chunk, phy::Point pos, Statistics stats, nostd::string entities, nostd::string market, nostd::string name)
{
	if(!isAlreadySaved(m)) {
		if (!name.empty())
			appendSave(m,chunk,pos, stats, entities, market, name);
		else
			appendSave(m,chunk,pos, stats, entities, market, "Player"); // this shouldn't happen
	}
	else
		updateSave(m,chunk,pos, stats, entities, market);
}

void File::changeName(nostd::string oldName,nostd::string newName)
{
	std::fstream file;
	std::fstream tmp;
	if(openFile(tmp,"./tmp.txt","w") && openFile(file,"./save.txt","r"))
	{
		bool found = false;
		nostd::string buff;
		int count=0;
		nostd::string search = "[ Name: " + oldName + " ]";
		while(!found && nostd::getline(file,buff))
		{
			if(buff==search)
				found=true;
			else
				count++;
		}
		if(found) {
			file.clear();
			file.seekg(0);
			for (int i = 0; i < count; i++) {
				nostd::getline(file, buff);
				tmp << buff << "\n";
			}
			nostd::getline(file, buff); // old name
			tmp << "[ Name: " << newName << " ]\n";
			while (nostd::getline(file, buff))
				tmp << buff << "\n";
		}
		file.close();
		tmp.close();
		if(found)
			rename("./tmp.txt","./save.txt");
	}
}

nostd::vector<nostd::string> File::getNames()
{
	nostd::vector<nostd::string> names;
	std::fstream file;
	if(openFile(file,"./save.txt","r"))
	{
		nostd::string buff;
		while(nostd::getline(file,buff))
			if(buff.substr(0,7)=="[ Name:")
				names.push_back(buff.substr(8,buff.length()-10));
		file.close();
	}
	return names;
}

nostd::vector<nostd::string> File::getLastSaves()
{
	nostd::vector<nostd::string> lastSave;
	std::fstream file;
	nostd::string buff;
	if(openFile(file,"./save.txt","r"))
	{
		while(nostd::getline(file,buff))
			if(buff.substr(0,9)=="LastSave:")
				lastSave.push_back(buff.substr(10));
		file.close();
	}
	return lastSave;
}

bool File::nameAlreadyInUse(nostd::string name)
{
	std::fstream file;
	if(openFile(file,"./save.txt","r"))
	{
		nostd::string search = "[ Name: " + name + " ]";
		nostd::string buff;
		bool found = false;
		while(!found && nostd::getline(file,buff))
			if(buff==search)
				found = true;
		file.close();
		return found;
	}
	else
		return false; // file does not exist yet
}

Map File::getMap(nostd::string name)
{
	std::fstream file;
	if(openFile(file,"./save.txt","r")) {
		nostd::string search = "[ Name: " + name + " ]";
		nostd::string buff;
		bool found = false;
		while (!found && nostd::getline(file, buff))
			if (buff == search)
				found = true;
		if (found) {
			nostd::string anotherBuff;
			nostd::getline(file, buff);
			file.close();
			Map m(nostd::stoi(buff.substr(6)));
			return m;
		} else
			file.close();
	}
	Map casualMap2;
	return casualMap2; // this shouldn't happen
}

int File::getChunk(nostd::string name)
{
	std::fstream file;
	if(openFile(file,"./save.txt","r")) {
		nostd::string search = "[ Name: " + name + " ]";
		nostd::string buff;
		bool found = false;
		while (!found && nostd::getline(file, buff))
			if (buff == search)
				found = true;
		if(found) {
			for (int i = 0; i < 2; i++)
				nostd::getline(file, buff);
			file.close();
			return nostd::stoi(buff.substr(7));
		}
		else
			file.close();
	}
	return 0; // this shouldn't happen
}

phy::Point File::getPoint(nostd::string name)
{
	phy::Point newPos(0,0);
	std::fstream file;
	if(openFile(file,"./save.txt","r")) {
		nostd::string search = "[ Name: " + name + " ]";
		nostd::string buff;
		phy::Point pos;
		bool found = false;
		while (!found && nostd::getline(file, buff))
			if (buff == search)
				found = true;
		if (found) {
			for (int i = 0; i < 3; i++)
				nostd::getline(file, buff);
			pos.set_xPosition(nostd::stoi(buff.substr(11, buff.find(',') - 11)));
			pos.set_yPosition(nostd::stoi(buff.substr(buff.find(',') + 1)));
			file.close();
			return pos;
		}
		else
			file.close();
	}
	return newPos; // this shouldn't happen
}

Statistics File::getStatistics(nostd::string name)
{
    Statistics stats = Statistics();

	std::fstream file;
	if(openFile(file,"./save.txt","r")) {
		nostd::string search = "[ Name: " + name + " ]";
		nostd::string buff;
		bool found = false;
		while (!found && nostd::getline(file, buff))
			if (buff == search)
				found = true;

        if(found)
        {
			for (int i = 0; i < 5; i++)
				nostd::getline(file, buff);

            // I can't think tonight...forgive me
            int pos_space[5];
            int i = 0;
            int k = 0;
            while(i < buff.length()) {
                if(buff[i] == ' ') {
                    pos_space[k] = i;
                    k++;
                }
                i++;
            }
            pos_space[4] = buff.length();

            stats.setLevel(nostd::stoi(buff.substr(pos_space[0] + 1, pos_space[1] - pos_space[0] - 1)));
            stats.setCoins(nostd::stoi(buff.substr(pos_space[1] + 1, pos_space[2] - pos_space[1] - 1)));
            stats.setJumps(nostd::stoi(buff.substr(pos_space[2] + 1, pos_space[3] - pos_space[2] - 1)));
            stats.setHearts(nostd::stoi(buff.substr(pos_space[3] + 1, pos_space[4] - pos_space[3] - 1)));
        }
	}

    return stats;
}

void File::getSettings(Settings& sett)
{
	std::fstream file;
	if(openFile(file,"./settings.txt","r"))
	{
		nostd::string buff;
		nostd::getline(file,buff); // [ KeyBindings ]
        nostd::getline(file,buff);
        sett.setControlsKeys(buff.c_str());

		nostd::getline(file,buff); // empty line
		nostd::getline(file,buff); // [ Preferences ]
		nostd::getline(file,buff);
		sett.setCalibration(nostd::stoi(buff.substr(12)));
		nostd::getline(file,buff);
		sett.setVolume(nostd::stoi(buff.substr(7)));
		nostd::getline(file,buff);
		sett.setSensitivity(nostd::stoi(buff.substr(12)));
		file.close();
	}
}

nostd::string File::getEntitiesStatus(nostd::string name)
{
	std::fstream file;
	if(openFile(file,"./save.txt","r")) {
		nostd::string search = "[ Name: " + name + " ]";
		nostd::string buff;
		bool found = false;
		while (!found && nostd::getline(file, buff))
			if (buff == search)
				found = true;

        if(found)
        {
			for (int i = 0; i < 6; i++)
				nostd::getline(file, buff);

            return buff.substr(10);
        }
	}

    // Error
    return nostd::string("");
}

nostd::string File::getMarketSave(nostd::string name)
{
	std::fstream file;
	if(openFile(file,"./save.txt","r")) {
		nostd::string search = "[ Name: " + name + " ]";
		nostd::string buff;
		bool found = false;
		while (!found && nostd::getline(file, buff))
			if (buff == search)
				found = true;

        if(found)
        {
			for (int i = 0; i < 7; i++)
				nostd::getline(file, buff);

            return buff.substr(8);
        }
	}

    // Error
    return nostd::string("");
}

void File::deleteSave(nostd::string name)
{
	std::fstream file;
	std::fstream tmp;
	if(openFile(tmp,"./tmp.txt","w") && openFile(file,"./save.txt","r"))
	{
		bool found = false;
		nostd::string buff;
		int count=0;
		nostd::string search = "[ Name: " + name + " ]";
		while(!found && nostd::getline(file,buff))
		{
			if(buff==search)
				found=true;
			else
				count++;
		}
		if(found) {
			file.clear();
			file.seekg(0);
			for (int i = 0; i < count; i++) {
				nostd::getline(file, buff);
				tmp << buff << "\n";
			}
			for (int i = 0; i < 8; i++)
				nostd::getline(file, buff);
			while (nostd::getline(file, buff))
				tmp << buff << "\n";
		}
		file.close();
		tmp.close();
		if(found)
			rename("./tmp.txt","./save.txt");
	}
}

int File::countSaves()
{
	int count=0;
	std::fstream file;
	if(openFile(file,"./save.txt","r")) {
		nostd::string buff;
		while (nostd::getline(file, buff))
			if (buff.substr(0, 7) == "[ Name:")
				count++;
		file.close();
	}
	return count;
}
