#include <unistd.h>
#include <cmath>

#include "game.hpp"
#include "menu.hpp"
#include "file.hpp"
#include "save.hpp"

#include "../physics/collisions.hpp"
#include "../entity/entity.hpp"

#include "../../etc/logs/logs.hpp"

#define JUMPF (1/(1+m_exp(-0.18 * (cumulative - 8)))*5)
//#define JUMPF cumulative / (1 + cumulative)

double m_exp(double d)
{
	if (d >= 0)
		return exp(d);
	else
		return 1/exp(-d);
}

Game::Game()
{
	this->screen = new Draw(SCREEN_HEIGHT, SCREEN_WIDTH);
	screen->init();
	File::initSettings(settings);
}


Game::~Game()
{
    delete this->screen;
}

void Game::run() {
    Menu menu = Menu();
    menu.drawIntroAnimation(this->screen);
    bool exit = false;
    while (!exit) {

        menu.drawMenu(this->screen);
        int sel = menu.get_selected_option(this->screen);

        Credits credits;

        switch (sel) {
            case 0: { // The brackets are mandatory in order to call the
                      // destructor of each elements when a game finish
                        setDifficulty();
                        Map map = Map();
                        int current_chunk = 0;
                        phy::Body player = phy::Body(phy::Point(40, 20), phy::Vector(1, -90), phy::Vector(0, 0));
                        Statistics stats = Statistics();
                        Manager manager = Manager(map);

                        this->play(map, current_chunk, player, stats, manager);
                        break;
                    }
            case 1: {
                        this->resume();
                        break;
                    }
            case 2: {
                        this->settings.drawFirstSettings();

                        break;
                    }
            case 3: {
                        // chiama la funziona credits che si trova in credits.cpp
                        credits = Credits();
                        int dev = credits.drawCredits(this->screen);
                        if (dev != -1)
                            credits.openGithub(dev);

                        break;
                    }
            case 27: {
                         if (exitGame() == true)
                             exit = true;
                         break;
                     }
        }
    }
}

bool Game::exitGame(){
    // Esci dal gioco
    this->screen->clearScreen();
    this->screen->drawCenterText(16, "Are you sure you want to quit?");	
    nostd::string options[2] = {"Yes", "No"};
	int selected = 0;
	bool choose = false;
	// Create two button (yes or no) to quit the game
	while (!choose){


		for (int i = 0; i < 2; i++)
		{
			this->screen->drawSquareAround(options[i], 20, 65 + 15*i);
		}
		// Set the selected button to blue
		this->screen->attrOn(COLOR_PAIR(1));
		this->screen->drawText(20, 65 + 15*selected, options[selected]);
		this->screen->attrOff(COLOR_PAIR(1));

		// Wait for the user to press a key
		switch (this->screen->getinput())
		{
			case KEY_LEFT:
				if (selected == 1) selected = selected - 1;
				else if (selected == 0) selected = 1;
				break;
			case KEY_RIGHT:
				if (selected == 0) selected = selected + 1;
				else if (selected == 1) selected = 0;
				break;
			case 10:
				choose = true;
				break;
		}



	}
	return selected == 0;
}

void Game::play(Map& map, int& current_chunk, phy::Body& player, Statistics& stats, Manager& manager){

	this->screen->drawMap(map, 0);
	this->screen->drawPlayer(player.get_position());
	this->screen->nodel(true);
    
    // Creating a screen for statistics
	int posY, posX;
	this->screen->size(posY, posX, SCREEN_HEIGHT, SCREEN_WIDTH);
	Draw stats_scr = Draw(3, SCREEN_WIDTH, posY - 3, posX);

	int entity_time= 0;

	bool exit = false;
	this->screen->nodel(true);
	int cumulative = 0;
	int count_not_key = 0;
	int which_key = 0;

	while (!exit){
        const char* control_keys = this->settings.getControlsKeys();

		stats_scr.updateStats(stats);
		bool right; 
		int input = this->screen->getinput();

		if (input == control_keys[3]) // jump right

		{
			which_key = 1;
			cumulative++;
			count_not_key = 0;
		}
		else if (input == control_keys[2]) // jump left
		{
			which_key = 2;
			cumulative++;
			count_not_key = 0;
		}
		else if (input == control_keys[4]){ // jump vertical
			which_key = 3;
			cumulative++;
			count_not_key = 0;

		}
		else
		{
			count_not_key++;
			if(count_not_key > 30)
			{
				if (cumulative > 1 && which_key == 1 && map.get_chunk(current_chunk).is_there_a_platform(player.get_position() - phy::Point(0, 1)))
					{
						player.set_velocity(phy::Vector(JUMPF, 55));
						stats.incrementJumps();
					}

				else if (cumulative > 1 && which_key == 2 && map.get_chunk(current_chunk).is_there_a_platform(player.get_position() - phy::Point(0, 1)))
					{
						player.set_velocity(phy::Vector(JUMPF, 125));
						stats.incrementJumps();
					}

				else if (cumulative > 1 && which_key == 3 && map.get_chunk(current_chunk).is_there_a_platform(player.get_position() - phy::Point(0, 1)))
					{
						player.set_velocity(phy::Vector(JUMPF, 90));
						stats.incrementJumps();
					}
				cumulative = 0;
			}
		
			if (input == control_keys[0]) // move player left
			{
				if(map.get_chunk(current_chunk).is_there_a_platform(player.get_position() - phy::Point(0, 1)))
					player.set_position(player.get_position() - phy::Point(1, 0));
			}
			else if (input == control_keys[1]) // move player right
			{
				if(map.get_chunk(current_chunk).is_there_a_platform(player.get_position() - phy::Point(0, 1)))
					player.set_position(player.get_position() + phy::Point(1, 0));
			}
            else if(input == control_keys[5]) // Shoot left
            {
                 manager.shoot(player.get_position(), false);
            }
            else if(input == control_keys[6]) // Shoot right
            {
                 manager.shoot(player.get_position(), true);
            }
			else if (input == 27) // Pause menu con tasto esc
			{
                // The return value indicate if we have to quit the game
				exit = pauseGame(&stats_scr, map, current_chunk, player, stats, manager);
			}
#ifdef USE_HACK
            else if (input == KEY_UP)
            {
                if(fly) 
                    player.set_position(player.get_position() + phy::Point(0, 1));
            }
            else if (input == KEY_LEFT)
            {
                if (fly) 
                    player.set_position(player.get_position() + phy::Point(-1, 0));
            }
            else if (input == KEY_DOWN)
            {
                if (fly) 
                    player.set_position(player.get_position() + phy::Point(0, -1));
            }
            else if (input == KEY_RIGHT)
            {
                if (fly) 
                    player.set_position(player.get_position() + phy::Point(0, -1));
                if (fly) 
                    player.set_position(player.get_position() + phy::Point(1, 0));
            }
            else if(input == (int) 'h')
            {
				this->screen->nodel(false);
				hack(current_chunk, stats);
				this->screen->nodel(true);
            }

			if (input == KEY_UP){
				if (fly) player.set_position(player.get_position() + phy::Point(0, 1));
			}
			else if (input == KEY_LEFT){
				if (fly) player.set_position(player.get_position() + phy::Point(-1, 0));
			}
			else if (input == KEY_DOWN){
				if (fly) player.set_position(player.get_position() + phy::Point(0, -1));
			}
			else if (input == KEY_RIGHT){
				if (fly) player.set_position(player.get_position() + phy::Point(1, 0));
			}
			else if (input == int ('h')){
				this->screen->nodel(false);
				hack(current_chunk, stats);
				this->screen->nodel(true);
			}
#endif
		}
		// player.update(0.05);

#ifdef USE_HACK
		if (!fly) phy::updateWithCollisions(player, 0.15, map.get_chunk(current_chunk));
#else
		phy::updateWithCollisions(player, 0.15, map.get_chunk(current_chunk));
#endif
		this->screen->eraseScreen();
		if (player.get_position().get_yPosition() < 0)
		{
			current_chunk--;
			stats.setLevel(current_chunk);
			player.set_position(player.get_position() + phy::Point(0, 42));
		}
		else if (player.get_position().get_yPosition() >= 42)
		{
			current_chunk++;
			stats.setLevel(current_chunk);
			player.set_position(player.get_position() - phy::Point(0, 42)); 
		}
		this->screen->drawPlayer(player.get_position());


        /* ENTITIES */
		manager.set_chunk(current_chunk);
		manager.update_entities(entity_time, player, stats);
        stats.setCoins(stats.getCoins() + manager.collect_coin(player.get_position()));
        entity_time = ++entity_time % 100;
		manager.draw_entities(screen);

		this->screen->drawMap(map, current_chunk);
		this->screen->drawText(2, 1, nostd::to_string(current_chunk));
		this->screen->drawText(1, 1, nostd::to_string(player.get_position().get_xPosition()));
		this->screen->drawText(1, 5, nostd::to_string(player.get_position().get_yPosition()));
		this->screen->drawText(1, 140, nostd::to_string(JUMPF));
		//this->screen->drawText(2, 140, nostd::to_string(1+pow(1.1, - cumulative/50)));
		this->screen->drawText(3, 140, nostd::to_string(cumulative));
		napms(5);

        if(stats.getHearts() <= 0)
        {
            this->over();
            exit = true;
        }
	}

	this->screen->nodel(false);	
	stats_scr.deleteStats();
}

void Game::resume()
{	
	bool deleted = false; 
	do {
	this->screen->clearScreen();
	deleted = false;
	nostd::vector<nostd::string> savedMaps = File::getNames();
	nostd::vector<nostd::string> savedDate = File::getLastSaves();
	if (savedMaps.size() == 0) {
		this->screen->drawCenterText(5, "No saved maps");
		this->screen->refreshScreen();
		this->screen->getinput();
	}
	else {
		int selected = 0;
		bool choose = false;
		bool exit = false;
		
		while (!choose && !exit){
			this->screen->drawCenterText(3, "Load your game from a saved file");
			this->screen->drawCenterText(7, "Press enter to play");
			this->screen->drawCenterText(9, "Press 'r' to remove a saved game");
			for (int i = 0; i < savedMaps.size(); i++)
			{
				this->screen->drawCenterSquareAround(savedMaps[i] + " " + savedDate[i], 13 + 4*i);
			}

			this->screen->attrOn(COLOR_PAIR(1));
			this->screen->drawCenterText(13 + 4*selected, savedMaps[selected] + " " + savedDate[selected]);
			this->screen->attrOff(COLOR_PAIR(1));

			switch (this->screen->getinput())
			{
				case KEY_UP:
					if (selected == 0) selected = savedMaps.size() - 1;
					else selected = selected - 1;
					break;
				case KEY_DOWN:
					if (selected == savedMaps.size() - 1) selected = 0;
					else selected = selected + 1;
					break;
				case 10:
					choose = true;
					break;
				case 'r':
					File::deleteSave(savedMaps[selected]);
					deleted = true;
					exit = true;
					break;
				case 27:
					exit = true;
					break;
				default:
					break;
			}
			this->screen->eraseScreen();
		}
		if (choose) {
			Map map = File::getMap(savedMaps[selected]);
			int current_chunk = File::getChunk(savedMaps[selected]);
            phy::Body player = phy::Body(File::getPoint(savedMaps[selected]), phy::Vector(0, 0), phy::Vector(0, 0));
            Statistics stats = File::getStatistics(savedMaps[selected]);
            Manager manager = Manager(map);
            manager.set_entities_status(current_chunk, File::getEntitiesStatus(savedMaps[selected]));
			play(map, current_chunk, player, stats, manager);
		}
	}
	} while (deleted);
}

int Game::setDifficulty()
{
	this->screen->clearScreen();
	this->screen->drawCenterText(3, "Select the difficulty");
	nostd::string options[3] = {"Easy", "Medium", "Hard"};
	int selected = 0;
	bool choose = false;
	while (!choose){
		for (int i = 0; i < 3; i++)
		{
			this->screen->drawSquareAround(options[i], 20, 58 + 15*i);
		}
		this->screen->attrOn(COLOR_PAIR(1));
		this->screen->drawText(20, 58 + 15*selected, options[selected]);
		this->screen->attrOff(COLOR_PAIR(1));

		switch (this->screen->getinput())
		{
			case KEY_LEFT:
				if (selected == 0) selected = 2;
				else selected = selected - 1;
				break;
			case KEY_RIGHT:
				if (selected == 2) selected = 0;
				else selected = selected + 1;
				break;
			case 10:
				choose = true;
				break;
		}
	}
	return selected;
}

bool Game::pauseGame(Draw* stats_scr, Map& map, int& current_chunk, 
        phy::Body& player, Statistics& stats, Manager& manager) {
    this->screen->nodel(false);

    int posY, posX;
    this->screen->size(posY, posX, SCREEN_HEIGHT, 60);
    Draw pause =
        Draw(SCREEN_HEIGHT, 60, posY, posX + (SCREEN_WIDTH - 60) / 2);

    bool resumed = false;
    bool exit = false;

    while (!resumed) {

        pause.clearwithoutbox();
        pause.drawBox();
        pause.drawText(3, 30 - pause.center("Game Paused"),
                "Game Paused");
        nostd::string options[4] = {"Resume", "Settings", "Save",
            "Exit"};
        int selected = 0;
        bool choose = false;

        stats_scr->redraw();
        this->screen->redraw();
        this->screen->noOutRefresh();
        stats_scr->noOutRefresh();
        pause.noOutRefresh();
        Screen::update();

        while (!choose) {
            for (int i = 0; i < 4; i++) {
                pause.drawSquareAround(options[i], 20 + 4 * i,
                        30 - (options[i].length() / 2));
            }
            pause.attrOn(COLOR_PAIR(1));
            pause.drawText(
                    20 + 4 * selected,
                    30 - (options[selected].length() / 2),
                    options[selected]);
            pause.attrOff(COLOR_PAIR(1));
            switch (pause.getinput()) {
                case KEY_UP:
                    if (selected == 0)
                        selected = 3;
                    else
                        selected = selected - 1;
                    break;
                case KEY_DOWN:
                    if (selected == 3)
                        selected = 0;
                    else
                        selected = selected + 1;
                    break;
                case 10:
                    choose = true;
                    break;
                case 27:
                    selected = -1;
                    choose = true;
                    break;
                default:
                    break;
            }
        }
        pause.refreshScreen();
        Save save = Save();
        switch (selected) {
            case 0: {
                        this->screen->nodel(true);
                        pause.deleteWin();

                        resumed = true;
                        break;
                    }
            case 1: {
                        this->settings.drawFirstSettings();
                        break;
                    }
            case 2: {
                        int posY, posX;
                        this->screen->size(posY, posX, 46, 150);

                        Draw save_scr = Draw(46, 150, posY, posX);

                        save.saveNewGame(&save_scr, map, current_chunk,
                                player, stats, manager);
                        save_scr.eraseScreen();
                        save_scr.deleteWin();
                        break;
                    }
            case 3: {
                        pause.clearScreen();
                        pause.deleteWin();
                        this->screen->redraw();
                        this->screen->refreshScreen();

                        save.quitGame(screen, map, current_chunk,
                                player, stats, manager);

                        resumed = true;
                        exit = true;
                        break;
                    }
            default: {
                         resumed = true;
                         exit = false;
                         break;
                     }
        }
    }
        // pause.deleteWin();
        this->screen->nodel(true);
        return exit;
}

void Game::over()
{
	this->screen->nodel(false);	
	int posX, posY;
	this->screen->size(posY, posX, 8, 50);
	Draw over_win = Draw(8, 50, posY, posX);
	over_win.drawBox();
	over_win.drawText(2, 25 - over_win.center("GAME OVER"), "GAME OVER");
	over_win.attrOn(COLOR_PAIR(1));
	over_win.drawText(5, 25 - over_win.center("Back to menu") , "Back to menu");
	over_win.attrOn(COLOR_PAIR(1));
	over_win.refreshScreen();
	over_win.getinput();
    over_win.eraseScreen();
    over_win.deleteWin();
}

#ifdef USE_HACK

void Game::hack(int& current_chunk, Statistics& stats){
	Draw hack = Draw(20, 50);
	hack.attrOn(COLOR_PAIR(2));
	hack.drawBox();
	hack.drawText(2, 25 - hack.center("Hack Menu"), "Hack Menu");
	hack.drawText(4, 25 - hack.center("Only use for development purposes!") , "Only use for development purposes!");
	hack.drawText(7, 7, "1. Add life");
	hack.drawText(7, 25, "6. Remove life");
	hack.drawText(9, 7, "2. Add coin");
	hack.drawText(9, 25, "7. Remove coin");
	hack.drawText(11, 7, "3. Add jump");
	hack.drawText(11, 25, "8. Remove jump");
	hack.drawText(13, 7, "4. Add level");
	hack.drawText(13, 25, "9. Remove level");
	hack.drawText(15, 7, "5. Enable fly");
	hack.drawText(15, 25, "0. Disable fly");
	hack.refreshScreen();
	int x = hack.getinput();
	switch (x){
		case '1':
			stats.incrementHearts();
			break;
		case '2':
			stats.incrementCoins();
			break;
		case '3':
			stats.incrementJumps();
			break;
		case '4':
			current_chunk++;
			break;
		case '5':
			fly = true;
			break;
		case '6':
			stats.incrementHearts(-1);
			break;
		case '7':
			stats.incrementCoins(-1);
			break;
		case '8':
			stats.incrementJumps(-1);
			break;
		case '9':
			current_chunk++;
			break;
		case '0':
			fly = false;
			break;
		case 's':  // set all custom 
		{

			hack.eraseScreen();
			hack.drawText(2, 25 - hack.center("Super secret menu"), "Super secret menu");
			hack.drawText(4, 25 - hack.center("WARNING: this menu is for skilled developers!"), "WARNING: this menu is for skilled developers!");
			nostd::string options[4] = {"1. Set life", "2. Set coins", "3. Set jump", "4. Set level"};
			for (int i = 0; i < 4; i++)
			{
				hack.drawText(7 + 2*i, 7, options[i]);
			}
			hack.refreshScreen();
			
			int secret = hack.getinput();
			switch (secret){
				case '1':
				{
					hack.eraseScreen();
					hack.drawText(2, 25 - hack.center("Set life"), "Set life");
					int custom = setCustom(&hack);
					if (custom != -1) stats.setHearts(custom);
					break;
				}
				case '2':
				{
					hack.eraseScreen();
					hack.drawText(2, 25 - hack.center("Set coins"), "Set coins");
					int custom = setCustom(&hack);
					if (custom != -1) stats.setCoins(custom); 
					break;
				}
				case '3':
				{
					hack.eraseScreen();
					hack.drawText(2, 25 - hack.center("Set jump"), "Set jump");
					int custom = setCustom(&hack);
					if (custom != -1) stats.setJumps(custom);  
					break;
				}
				case '4':
				{
					hack.eraseScreen();
					hack.drawText(2, 25 - hack.center("Set level"), "Set level");
					int custom = setCustom(&hack);
					if (custom != -1) current_chunk = custom;
					break;
				}
				default:
					break;
			}
			break;
		}
		default:
			break;
	}
	hack.attrOff(COLOR_PAIR(2));
	hack.eraseScreen();
	hack.deleteWin();
}

int Game::setCustom(Draw* hack){
	int a = hack->getinput();
	nostd::string set_chunk;
	while (a != 10  && a != 27){ 
		// controlla se l'input è un numero
		if (a >= 48 && a <= 57) set_chunk = set_chunk + nostd::to_string(char(a));
		// se è backspace cancella l'ultimo carattere
		else if (a == 127) set_chunk = set_chunk.substr(0, set_chunk.length() - 1);
		hack->clearLine(4, 0);
		hack->drawText(4, 25 - hack->center(set_chunk), set_chunk);
		a = hack->getinput();
	}
	if (a == 27) return -1;
	else return stoi(set_chunk);
}
#endif
