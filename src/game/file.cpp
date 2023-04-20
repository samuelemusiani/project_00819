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
		if(openFile(&file,"./settings.txt","w"))
		{
			file << "{ JUMP KING }\n\n[ KeyBindings ]\nml=s\nmr=d\njl=a\njr=f\njp=v\nsh=o\nbb=p\not=esc\n\n"
					"[ Calibration ]\ncalibr=0\n\n[ Audio ]\nvol=5\n\n[ Sensitivity ]\nsens=5\n\n";
			file.close();
		}
}

void File::saveSettings(Settings s)
{
	std::fstream file;
	if(openFile(&file,"./settings.txt","w"))
		file << /*"{ JUMP KING }\n\n[ KeyBindings ]\nml="<<s.getKeys[0]<<"\nmr="<<s.getKeys[1]<<"\njl="<<s.getKeys[2]<<"\n"
				"jr="<<s.getKeys[3]<<"\njp="<<s.getKeys[4]<<"\nsh="<<s.getKeys[5]<<"\nbb="<<s.getKeys[6]<<"\not="<<s.getKeys[7]<<"\n\n"
				"[ Calibration ]\ncalibr="<<s.getCalibration<<"\n\n[ Audio ]\nvol="<<s.getVolume<<"\n\n[ Sensitivity ]\n"<<"sens="<<s.getVolume<<*/"\n";
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
				 << "\nCoins&Enemies: " << m.getCoinsAndEnemies() << "\n" << dateAndTime() << "\n\n";
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
		while(getline(file,buff) && !found)
		{
			tmp << buff << "\n";
			if(buff==search)
				found=true;
		}
		getline(file,buff); // this is the 1st line that has to be replaced
		tmp << "Coins&Enemies: " << m.getCoinsAndEnemies() << "\n";
		getline(file,buff); // this is the 2nd line that has to be replaced
		tmp << dateAndTime() << "\n\n";
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
		if (name != "")
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
		while(getline(file,buff) && !found)
		{
			count++;
			if(buff==search)
				found=true;
		}
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

nostd::vector<std::string>* File::getNames()
{
	static nostd::vector<std::string> names;
	std::fstream file;
	std::string buff;
	if(openFile(&file,"./save.txt","r"))
	{
		while(getline(file,buff))
			if(buff[0] == '[')
				names.push_back(buff.substr(8,buff.length()-10));
	}
	file.close();
	return &names;
}

nostd::vector<std::string>* File::getLastModify()
{
	static nostd::vector<std::string> lastModify;
	std::fstream file;
	std::string buff;
	if(openFile(&file,"./save.txt","r"))
	{
		while(getline(file,buff))
			if(buff.substr(0,2)=="20")
				lastModify.push_back(buff.substr(0,buff.length()-1));
	}
	file.close();
	return &lastModify;
}

bool File::nameAlreadyInUse(std::string name)
{
	std::fstream file;
	std::string search = "[ " + name + " ]";
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
