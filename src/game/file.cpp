#include "file.hpp"

File::File()
{

}

bool File::openFile(std::fstream &file,std::string path,std::string mode)
{
	if(mode=="r")
		file.open(path,std::ios::in);
	else if(mode=="w")
		file.open(path,std::ios::out);
	else if(mode=="app")
		file.open(path,std::ios::app);
	else
		file.open(path,std::ios::in | std::ios::out);
	return file.is_open();
}

void File::initSettings() {
	std::fstream file;
	if (!exist(file, "./settings.txt"))
	{
		if (openFile(file, "./settings.txt", "w"))
		{
			file << "[ KeyBindings ]\nml=s\nmr=d\njl=a\njr=f\njp=v\nsh=o\nbb=p\not=esc\n\n"
					"[ Preferences ]\nCalibration=-1\nVolume=10\nSensitivity=10\n\n";
			file.close();
		}
	}
	getSettings();
}

void File::saveSettings()
{
	std::fstream file;
	if(openFile(file,"./settings.txt","w"))
		file << "[ KeyBindings ]\nml="<<SETTINGS_CONTROL_KEYS[0]<<"\nmr="<<SETTINGS_CONTROL_KEYS[1]<<"\n"
				"jl="<<SETTINGS_CONTROL_KEYS[2]<<"\njr="<<SETTINGS_CONTROL_KEYS[3]<<"\njp="<<SETTINGS_CONTROL_KEYS[4]<<"\n"
				"sh="<<SETTINGS_CONTROL_KEYS[5]<<"\nbb="<<SETTINGS_CONTROL_KEYS[6]<<"\not="<<SETTINGS_CONTROL_KEYS[7]<<"\n\n"
				"[ Preferencies ]\nCalibration="<<SETTINGS_PRESSURE_CALIBRATION<<"\nVolume="<<SETTINGS_VOLUME_LEVEL<<"\nSensitivity="<<SETTINGS_SENSITIVITY_LEVEL<<"\n";
	file.close();
}

bool File::isCalibrated()
{
	return (SETTINGS_PRESSURE_CALIBRATION!=-1);
}

bool File::exist(std::fstream &file, std::string path)
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
		std::string buff;
		std::string tmp = "Seed: "+std::to_string(m.getSeed().getSeed());
		bool found = false;
		while(!found && getline(file,buff))
			if(buff == tmp)
				found = true;
		file.close();
		return found;
	}
	else
		return false; // file does not exist yet
}

void File::appendSave(Map m,int chunk,phy::Point pos,std::string name)
{
	std::fstream file;
	if(openFile(file,"./save.txt","app")) {
		file << "[ Name: " << name << " ]\nSeed: " << m.getSeed().getSeed() << "\nCoins&Enemies: " << m.getCoinsAndEnemies()
		<< "\nChunk: " << chunk << "\nPlayerPos: " << pos.get_xPosition() << "," << pos.get_yPosition()<< "\nLastSave: " << dateAndTime() << "\n\n";
		file.close();
	}
}

void File::updateSave(Map m,int chunk,phy::Point pos)
{
	// the only way to do this is to rewrite the entire file
	std::fstream file;
	std::fstream tmp;
	if(openFile(tmp,"./tmp.txt","w") && openFile(file,"./save.txt","r"))
	{
		std::string buff;
		bool found=false;
		std::string search = "Seed: "+std::to_string(m.getSeed().getSeed());
		while(!found && getline(file,buff))
		{
			tmp << buff << "\n";
			if(buff==search)
				found=true;
		}
		getline(file,buff);
		tmp << "Coins&Enemies: " << m.getCoinsAndEnemies() << "\n";
		getline(file,buff);
		tmp << "Chunk: " << chunk << "\n";
		getline(file,buff);
		tmp << "PlayerPos: " << pos.get_xPosition() << "," << pos.get_yPosition() << "\n";
		getline(file,buff);
		tmp << "LastSave: " << dateAndTime() << "\n\n";
		while(getline(file,buff))
			tmp << buff << "\n";
		file.close();
		tmp.close();
		rename("./tmp.txt","./save.txt");
	}
}

void File::saveMap(Map m,int chunk,phy::Point pos,std::string name)
{
	if(!isAlreadySaved(m)) {
		if (!name.empty())
			appendSave(m,chunk,pos,name);
		else
			appendSave(m,chunk,pos,"Player"); // this shouldn't happen
	}
	else
		updateSave(m,chunk,pos);
}

void File::changeName(std::string oldName,std::string newName)
{
	std::fstream file;
	std::fstream tmp;
	if(openFile(tmp,"./tmp.txt","w") && openFile(file,"./save.txt","r"))
	{
		bool found = false;
		std::string buff;
		int count=0;
		std::string search = "[ Name: " + oldName + " ]";
		while(!found && getline(file,buff))
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
				getline(file, buff);
				tmp << buff << "\n";
			}
			getline(file, buff); // old name
			tmp << "[ Name: " << newName << " ]\n";
			while (getline(file, buff))
				tmp << buff << "\n";
		}
		file.close();
		tmp.close();
		if(found)
			rename("./tmp.txt","./save.txt");
	}
}

nostd::vector<std::string> File::getNames()
{
	nostd::vector<std::string> names;
	std::fstream file;
	if(openFile(file,"./save.txt","r"))
	{
		std::string buff;
		while(getline(file,buff))
			if(buff.substr(0,7)=="[ Name:")
				names.push_back(buff.substr(8,buff.length()-10));
		file.close();
	}
	return names;
}

nostd::vector<std::string> File::getLastSaves()
{
	nostd::vector<std::string> lastSave;
	std::fstream file;
	std::string buff;
	if(openFile(file,"./save.txt","r"))
	{
		while(getline(file,buff))
			if(buff.substr(0,9)=="LastSave:")
				lastSave.push_back(buff.substr(10));
		file.close();
	}
	return lastSave;
}

bool File::nameAlreadyInUse(std::string name)
{
	std::fstream file;
	if(openFile(file,"./save.txt","r"))
	{
		std::string search = "[ Name: " + name + " ]";
		std::string buff;
		bool found = false;
		while(!found && getline(file,buff))
			if(buff==search)
				found = true;
		file.close();
		return found;
	}
	else
		return false; // file does not exist yet
}

Map File::getMap(std::string name)
{
	std::fstream file;
	if(openFile(file,"./save.txt","r")) {
		std::string search = "[ Name: " + name + " ]";
		std::string buff;
		bool found = false;
		while (!found && getline(file, buff))
			if (buff == search)
				found = true;
		if (found) {
			std::string anotherBuff;
			getline(file, buff);
			getline(file, anotherBuff);
			file.close();
			Map m(std::stoi(buff.substr(6)), anotherBuff.substr(15));
			return m;
		} else
			file.close();
	}
	Map casualMap2;
	return casualMap2; // this shouldn't happen
}

int File::getChunk(std::string name)
{
	std::fstream file;
	if(openFile(file,"./save.txt","r")) {
		std::string search = "[ Name: " + name + " ]";
		std::string buff;
		bool found = false;
		while (!found && getline(file, buff))
			if (buff == search)
				found = true;
		if(found) {
			for (int i = 0; i < 3; i++)
				getline(file, buff);
			file.close();
			return stoi(buff.substr(7));
		}
		else
			file.close();
	}
	return 0; // this shouldn't happen
}

phy::Point File::getPoint(std::string name)
{
	phy::Point newPos(0,0);
	std::fstream file;
	if(openFile(file,"./save.txt","r")) {
		std::string search = "[ Name: " + name + " ]";
		std::string buff;
		phy::Point pos;
		bool found = false;
		while (!found && getline(file, buff))
			if (buff == search)
				found = true;
		if (found) {
			for (int i = 0; i < 4; i++)
				getline(file, buff);
			pos.set_xPosition(stoi(buff.substr(11, buff.find(',') - 11)));
			pos.set_yPosition(stoi(buff.substr(buff.find(',') + 1)));
			file.close();
			return pos;
		}
		else
			file.close();
	}
	return newPos; // this shouldn't happen
}

void File::getSettings()
{
	std::fstream file;
	if(openFile(file,"./settings.txt","r"))
	{
		std::string buff;
		getline(file,buff); // [ KeyBindings ]
		for(int i=0;i<8;i++)
		{
			getline(file,buff);
			SETTINGS_CONTROL_KEYS[i] = buff.substr(3);
		}
		getline(file,buff); // empty line
		getline(file,buff); // [ Preferences ]
		getline(file,buff);
		SETTINGS_PRESSURE_CALIBRATION = stoi(buff.substr(12));
		getline(file,buff); // empty line
		getline(file,buff); // [ Audio ]
		getline(file,buff);
		SETTINGS_VOLUME_LEVEL = stoi(buff.substr(7));
		getline(file,buff); // empty line
		getline(file,buff); // [ Sensitivity ]
		getline(file,buff);
		SETTINGS_SENSITIVITY_LEVEL = stoi(buff.substr(12));
		file.close();
	}
}

void File::deleteSave(std::string name)
{
	std::fstream file;
	std::fstream tmp;
	if(openFile(tmp,"./tmp.txt","w") && openFile(file,"./save.txt","r"))
	{
		bool found = false;
		std::string buff;
		int count=0;
		std::string search = "[ Name: " + name + " ]";
		while(!found && getline(file,buff))
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
				getline(file, buff);
				tmp << buff << "\n";
			}
			for (int i = 0; i < 5; i++)
				getline(file, buff);
			while (getline(file, buff))
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
		std::string buff;
		while (getline(file, buff))
			if (buff.substr(0, 7) == "[ Name:")
				count++;
		file.close();
	}
	return count;
}
