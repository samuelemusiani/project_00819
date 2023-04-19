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
		file << "{ JUMP KING }\n\n[ KeyBindings ]\nml="<<s.getKeys[0]<<"\nmr="<<s.getKeys[1]<<"\njl="<<s.getKeys[2]<<"\n"
				"jr="<<s.getKeys[3]<<"\njp="<<s.getKeys[4]<<"\nsh="<<s.getKeys[5]<<"\nbb="<<s.getKeys[6]<<"\not="<<s.getKeys[7]<<"\n\n"
				"[ Calibration ]\ncalibr="<<s.getCalibration<<"\n\n[ Audio ]\nvol="<<s.getVolume<<"\n\n[ Sensitivity ]\n"<<"sens="<<s.getVolume<<"\n";
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
	if(openFile(&file,"./save.txt"))
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
		return false;
	}
}

void File::appendSave(Map m,std::string name)
{
	std::fstream file;
	if(openFile(&file,"./save.txt","app")) {
		file << "[ Nome: " << name << " ]\nSeed: " << m.getSeed().getSeed()
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
			appendSave(m, "Player"); // this shouldn't be happening
	}
	else
		updateSave(m);
}
