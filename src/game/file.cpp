#include "file.hpp"

File::File()
{

}

bool File::openFile(std::fstream* file,std::string path,std::string mode)
{
	if(mode=="r")
		file->open(path,std::ios::in);
	else if(mode=="w")
		file->open(path,std::ios::out);
	else if(mode=="app")
		file->open(path,std::ios::app);
	else
		file->open(path,std::ios::in | std::ios::out);
	return file->is_open();
}

void File::initSettings() {
	std::fstream file;
	if (!exist(&file, "./settings.txt"))
	{
		if (openFile(&file, "./settings.txt", "w"))
		{
			file << "{ JUMP KING }\n\n[ KeyBindings ]\nml=s\nmr=d\njl=a\njr=f\njp=v\nsh=o\nbb=p\not=esc\n\n"
					"[ Calibration ]\ncalibr=-1\n\n[ Audio ]\nvol=10\n\n[ Sensitivity ]\nsens=10\n\n";
			file.close();
			getSettings();
		}
	}
	else
		getSettings();
}

void File::saveSettings()
{
	std::fstream file;
	if(openFile(&file,"./settings.txt","w"))
		file << "{ JUMP KING }\n\n[ KeyBindings ]\nml="<<SETTINGS_CONTROL_KEYS[0]<<"\nmr="<<SETTINGS_CONTROL_KEYS[1]<<"\njl="<<SETTINGS_CONTROL_KEYS[2]<<"\n"
				"jr="<<SETTINGS_CONTROL_KEYS[3]<<"\njp="<<SETTINGS_CONTROL_KEYS[4]<<"\nsh="<<SETTINGS_CONTROL_KEYS[5]<<"\nbb="<<SETTINGS_CONTROL_KEYS[6]<<"\not="<<SETTINGS_CONTROL_KEYS[7]<<"\n\n"
				"[ Calibration ]\ncalibr="<<SETTINGS_PRESSURE_CALIBRATION<<"\n\n[ Audio ]\nvol="<<SETTINGS_VOLUME_LEVEL<<"\n\n[ Sensitivity ]\n"<<"sens="<<SETTINGS_SENSITIVITY_LEVEL<<"\n";
	file.close();
}


bool File::exist(std::fstream *file, std::string path)
{
	bool x = openFile(file,path,"r");
	file->close();
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
	std::string buff;
	if(openFile(&file,"./save.txt","r"))
	{
		while(getline(file,buff))
		{
			std::string tmp = "Seed: "+std::to_string(m.getSeed().getSeed());
			if(buff == tmp)
			{
				file.close();
				return true;
			}
		}
		file.close();
		return false; // file exists but the searched seed is not saved
	}
	else
		return false; // file does not exist yet
}

void File::appendSave(Map m,std::string name)
{
	std::fstream file;
	if(openFile(&file,"./save.txt","app")) {
		file << "[ Name: " << name << " ]\nSeed: " << m.getSeed().getSeed()
				 << "\nCoins&Enemies: " << m.getCoinsAndEnemies() << "\nLastSave: " << dateAndTime() << "\n\n";
		file.close();
	}
}

void File::updateSave(Map m)
{
	// the only way to do this is to rewrite the entire file
	std::fstream file;
	std::fstream tmp;
	std::string buff;
	bool found=false;
	std::string search = "Seed: "+std::to_string(m.getSeed().getSeed());
	if(openFile(&tmp,"./tmp.txt","w") && openFile(&file,"./save.txt","r"))
	{
		while(!found && getline(file,buff))
		{
			tmp << buff << "\n";
			if(buff==search)
				found=true;
		}
		getline(file,buff); // this is the 1st line that has to be replaced
		tmp << "Coins&Enemies: " << m.getCoinsAndEnemies() << "\n";
		getline(file,buff); // this is the 2nd line that has to be replaced
		tmp << "LastSave: " << dateAndTime() << "\n\n";
		while(getline(file,buff))
			tmp << buff << "\n";
		file.close();
		tmp.close();
		rename("./tmp.txt","./save.txt");
	}
}

void File::saveMap(Map m,std::string name)
{
	if(!isAlreadySaved(m)) {
		if (!name.empty())
			appendSave(m, name);
		else
			appendSave(m, "Player"); // this shouldn't happen
	}
	else
		updateSave(m);
}

void File::changeName(std::string oldName,std::string newName)
{
	std::fstream file;
	std::fstream tmp;
	bool found = false;
	std::string buff;
	int count=-1;
	std::string search = "[ Name: " + oldName + " ]";
	if(openFile(&tmp,"./tmp.txt","w") && openFile(&file,"./save.txt","r"))
	{
		while(!found && getline(file,buff))
		{
			count++;
			if(buff==search)
				found=true;
		}
		if(!found)	return;
		file.clear();
		file.seekg(0);
		for(int i=0;i<count;i++)
		{
			getline(file, buff);
			tmp << buff << "\n";
		}
		getline(file,buff); // old name
		tmp << "[ Name: " << newName << " ]\n";
		while(getline(file,buff))
			tmp << buff << "\n";
		file.close();
		tmp.close();
		rename("./tmp.txt","./save.txt");
	}
}

nostd::vector<std::string> File::getNames()
{
	nostd::vector<std::string> names;
	std::fstream file;
	std::string buff;
	if(openFile(&file,"./save.txt","r"))
	{
		while(getline(file,buff))
			if(buff.substr(0,7)=="[ Name:")
				names.push_back(buff.substr(8,buff.length()-10));
	}
	file.close();
	return names;
}

nostd::vector<std::string> File::getLastSave()
{
	static nostd::vector<std::string> lastSave;
	std::fstream file;
	std::string buff;
	if(openFile(&file,"./save.txt","r"))
	{
		while(getline(file,buff))
			if(buff.substr(0,9)=="LastSave:")
				lastSave.push_back(buff.substr(10,buff.length()-10));
	}
	file.close();
	return lastSave;
}

bool File::nameAlreadyInUse(std::string name)
{
	std::fstream file;
	std::string search = "[ Name: " + name + " ]";
	std::string buff;
	if(openFile(&file,"./save.txt","r"))
	{
		while(getline(file,buff))
			if(buff==search)
			{
				file.close();
				return true;
			}
		file.close();
		return false; // file exists but the name isn't in use
	}
	else
		return false; // file does not exist
}

Map File::getMap(std::string name)
{
	std::fstream file;
	std::string search = "[ Name: " + name + " ]";
	std::string buff;
	std::string anotherBuff;
	bool found = false;
	if(openFile(&file,"./save.txt","r"))
	{
		while (!found && getline(file, buff))
			if (buff == search)
				found = true;
		if(!found)
		{
			Map casualMap;
			return casualMap; // this shouldn't happen
		}
		getline(file, buff);
		getline(file, anotherBuff);
		Map m(std::stoi(buff.substr(6, buff.length() - 6)), anotherBuff.substr(15, anotherBuff.length() - 15));
		return m;

	}
	Map casualMap2;
	return casualMap2; // this shouldn't happen
}

void File::getSettings()
{
	std::fstream file;
	std::string buff;
	bool found = false;
	if(openFile(&file,"./settings.txt","r"))
	{
		while(!found && getline(file,buff))
			if(buff == "[ KeyBindings ]")
				found = true;
		deb::debug("ok");
		for(int i=0;i<8;i++)
		{
			getline(file,buff);
			SETTINGS_CONTROL_KEYS[i] = buff.substr(3,buff.length()-3);
		}
		getline(file,buff); // empty line
		getline(file,buff); // [ Calibration ]
		getline(file,buff);
		SETTINGS_PRESSURE_CALIBRATION = stoi(buff.substr(7,buff.length()-7));
		getline(file,buff); // empty line
		getline(file,buff); // [ Audio ]
		getline(file,buff);
		SETTINGS_VOLUME_LEVEL = stoi(buff.substr(4,buff.length()-4));
		getline(file,buff); // empty line
		getline(file,buff); // [ Sensitivity ]
		getline(file,buff);
		SETTINGS_SENSITIVITY_LEVEL = stoi(buff.substr(5,buff.length()-5));
	}
}

void File::deleteSave(std::string name)
{
	std::fstream file;
	std::fstream tmp;
	bool found = false;
	std::string buff;
	int count=-1;
	std::string search = "[ Name: " + name + " ]";
	if(openFile(&tmp,"./tmp.txt","w") && openFile(&file,"./save.txt","r"))
	{
		while(!found && getline(file,buff))
		{
			count++;
			if(buff==search)
				found=true;
		}
		if(!found)	return;
		file.clear();
		file.seekg(0);
		for(int i=0;i<count;i++)
		{
			getline(file, buff);
			tmp << buff << "\n";
		}
		for(int i=0;i<5;i++)
			getline(file,buff);
		while(getline(file,buff))
			tmp << buff << "\n";
		file.close();
		tmp.close();
		rename("./tmp.txt","./save.txt");
	}
}
