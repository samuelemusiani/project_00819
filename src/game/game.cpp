/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Argonni Emanuele #0001078626
 *
 * game.cpp: Primary game class that interact with
 * all other classes
 */

#include <unistd.h>

#include "file.hpp"
#include "game.hpp"
#include "menu.hpp"
#include "save.hpp"

#include "../engine/events.hpp"
#include "../engine/jump_lib.hpp"
#include "../entity/entity.hpp"
#include "../physics/collisions.hpp"

#include "../../etc/logs/logs.hpp"

Game::Game() {
  this->screen = new Draw(SCREEN_HEIGHT, SCREEN_WIDTH);
  screen->init();
  File::initSettings(this->settings);

  this->audio.play_music("music.mp3");
  audio.set_volume(this->settings.getVolume());
}

Game::~Game() {
  delete this->screen;
  this->audio.stop_music();
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
              // destructor of each element when a game finish
      Map map = Map();
      int current_chunk = 0;
      phy::Body player =
          phy::Body(phy::Point(74, 3), phy::Vector(1, -90), phy::Vector(0, 0));
      Statistics stats = Statistics();
      Manager manager = Manager(map);
      Market market = Market();

      this->play(map, current_chunk, player, stats, manager, market);
      break;
    }
    case 1: {
      this->resume();
      break;
    }
    case 2: {
      this->settings.drawFirstSettings(this->audio);
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

bool Game::exitGame() {
  // Esci dal gioco
  this->screen->clearScreen();
  this->screen->drawCenterText(16, "Are you sure you want to quit?");
  nostd::string options[2] = {"Yes", "No"};
  int selected = 0;
  bool choose = false;
  // Create two button (yes or no) to quit the game
  while (!choose) {

    for (int i = 0; i < 2; i++) {
      this->screen->drawSquareAround(options[i], 20, 65 + 15 * i);
    }
    // Set the selected button to blue
    this->screen->attrOn(COLOR_PAIR(1));
    this->screen->drawText(20, 65 + 15 * selected, options[selected]);
    this->screen->attrOff(COLOR_PAIR(1));

    // Wait for the user to press a key
    switch (this->screen->getinput()) {
    case KEY_LEFT:
      if (selected == 1)
        selected = selected - 1;
      else if (selected == 0)
        selected = 1;
      break;
    case KEY_RIGHT:
      if (selected == 0)
        selected = selected + 1;
      else if (selected == 1)
        selected = 0;
      break;
    case 10:
      choose = true;
      break;
    }
  }
  return selected == 0;
}

void Game::play(Map &map, int &current_chunk, phy::Body &player,
                Statistics &stats, Manager &manager, Market &market) {

  Events events = Events();

  this->screen->nodel(true);

  int entity_time = 0;

  bool exit = false;
  this->screen->nodel(true);

  int jump_cumulative = 0;
  int jump_count_not_key = 0;
  int jump_which_key = 0;

  int gun_cumulative = 0;
  int gun_count_not_key = 0;
  int gun_which_key = 0;

  while (!exit) {
    const char *control_keys = this->settings.getControlsKeys();

    bool right;
    int input = this->screen->getinput();

    bool is_player_on_a_platform =
        map.get_chunk(current_chunk)
            .is_there_a_platform(player.get_position() - phy::Point(0, 1));

    if (input == control_keys[3] && is_player_on_a_platform) // jump right
    {
      jump_which_key = 1;
      jump_cumulative++;
      jump_count_not_key = 0;
    } else if (input == control_keys[2] && is_player_on_a_platform) // jump left
    {
      jump_which_key = 2;
      jump_cumulative++;
      jump_count_not_key = 0;
    } else if (input == control_keys[4] &&
               is_player_on_a_platform) { // jump vertical
      jump_which_key = 3;
      jump_cumulative++;
      jump_count_not_key = 0;

    } else {
      jump_count_not_key++;
      if (jump_count_not_key > 30) {
        if (jump_cumulative > 1 && jump_which_key == 1 &&
            is_player_on_a_platform) {
          player.set_velocity(phy::Vector(jump_function(jump_cumulative), 55));
          stats.incrementJumps();
        }

        else if (jump_cumulative > 1 && jump_which_key == 2 &&
                 is_player_on_a_platform) {
          player.set_velocity(phy::Vector(jump_function(jump_cumulative), 125));
          stats.incrementJumps();
        }

        else if (jump_cumulative > 1 && jump_which_key == 3 &&
                 is_player_on_a_platform) {
          player.set_velocity(phy::Vector(jump_function(jump_cumulative), 90));
          stats.incrementJumps();
        }
        jump_cumulative = 0;
      }

      if (input == control_keys[0] &&
          is_player_on_a_platform) // move player left
      {
        player.set_position(player.get_position() - phy::Point(1, 0));
      } else if (input == control_keys[1] &&
                 is_player_on_a_platform) // move player right
      {
        player.set_position(player.get_position() + phy::Point(1, 0));
      } else if (input == control_keys[5]) // Shoot left
      {
        Gun current_gun = market.get_current_gun();

        // Grenade launcher
        if (current_gun.get_bullet_type() == 2) {
          gun_cumulative++;
          gun_which_key = 0;
          gun_count_not_key = 0;
        } else
          manager.player_shoot(player.get_position(), phy::Vector(1, 180),
                               current_gun);
      } else if (input == control_keys[6]) // Shoot right
      {
        Gun current_gun = market.get_current_gun();

        // Grenade launcher
        if (current_gun.get_bullet_type() == 2) {
          gun_cumulative++;
          gun_which_key = 1;
          gun_count_not_key = 0;
        } else
          manager.player_shoot(player.get_position(), phy::Vector(1, 0),
                               current_gun);
      } else {
        gun_count_not_key++;
        if (gun_count_not_key > 30) {
          if (gun_cumulative > 1 && gun_which_key == 0) {
            Gun current_gun = market.get_current_gun();
            manager.player_shoot(
                player.get_position(),
                phy::Vector(jump_function(gun_cumulative), 130), current_gun);
          } else if (gun_cumulative > 1 && gun_which_key == 1) {
            Gun current_gun = market.get_current_gun();
            manager.player_shoot(player.get_position(),
                                 phy::Vector(jump_function(gun_cumulative), 50),
                                 current_gun);
          }
          gun_cumulative = 0;
        }
      }

      if (input == control_keys[7]) // Ability
      {
        events.make_ability_happen(market.get_current_ability(), manager,
                                   player.get_position(), current_chunk);
      } else if (input == 27) // Pause menu con tasto esc
      {
        // The return value indicate if we have to quit the game
        exit =
            this->pauseGame(map, current_chunk, player, stats, manager, market);
      }
#ifdef USE_HACK
      else if (input == KEY_UP) {
        if (fly)
          player.set_position(player.get_position() + phy::Point(0, 1));
      } else if (input == KEY_LEFT) {
        if (fly)
          player.set_position(player.get_position() + phy::Point(-1, 0));
      } else if (input == KEY_DOWN) {
        if (fly)
          player.set_position(player.get_position() + phy::Point(0, -1));
      } else if (input == KEY_RIGHT) {
        if (fly)
          player.set_position(player.get_position() + phy::Point(1, 0));
      } else if (input == (int)'h') {
        this->screen->nodel(false);
        hack(current_chunk, stats);
        this->screen->nodel(true);
      }
#endif
    }
    // player.update(0.05);

#ifdef USE_HACK
    if (!fly)
      phy::updateWithCollisions(player, 0.15, map.get_chunk(current_chunk));
#else
    phy::updateWithCollisions(player, 0.15, map.get_chunk(current_chunk));
#endif
    this->screen->eraseScreen();
    if (player.get_position().get_yPosition() < 0) {
      current_chunk--;
      stats.setLevel(current_chunk);
      player.set_position(player.get_position() + phy::Point(0, 42));
    } else if (player.get_position().get_yPosition() >= 42) {
      current_chunk++;
      stats.setLevel(current_chunk);
      player.set_position(player.get_position() - phy::Point(0, 42));
    }

    events.update(manager);

    /* ENTITIES */
    manager.set_chunk(current_chunk);
    manager.update_entities(entity_time, player, stats);
    stats.setCoins(stats.getCoins() +
                   manager.collect_coin(player.get_position()));
    entity_time = ++entity_time % 100;
    manager.draw_entities(screen);

    this->screen->drawMap(map, current_chunk);
    this->screen->drawStats(stats);

    /* Ability cooldown */
    this->screen->drawText(1, SCREEN_WIDTH - 30,
                           "Ability: " + events.get_indicator());
    this->screen->drawText(1, SCREEN_WIDTH - 11, '|');

    napms(5);

    if (stats.getHearts() <= 0) {
      this->over();
      stats.setHearts(10);
      stats.setCoins(0);
      current_chunk = std::max(current_chunk - 2, 0);
      stats.setLevel(current_chunk);
      player.set_position(phy::Point(player.get_position().get_xPosition(), 2));
    }
  }

  this->screen->nodel(false);
}

void Game::resume() {
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
    } else {
      int selected = 0;
      bool choose = false;
      bool exit = false;

      while (!choose && !exit) {
        this->screen->drawCenterText(3, "Load your game from a saved file");
        this->screen->drawCenterText(7, "Press enter to play");
        this->screen->drawCenterText(9, "Press 'r' to remove a saved game");
        for (int i = 0; i < savedMaps.size(); i++) {
          this->screen->drawCenterSquareAround(
              savedMaps[i] + " " + savedDate[i], 13 + 4 * i);
        }

        this->screen->attrOn(COLOR_PAIR(1));
        this->screen->drawCenterText(
            13 + 4 * selected, savedMaps[selected] + " " + savedDate[selected]);
        this->screen->attrOff(COLOR_PAIR(1));

        switch (this->screen->getinput()) {
        case KEY_UP:
          if (selected == 0)
            selected = savedMaps.size() - 1;
          else
            selected = selected - 1;
          break;
        case KEY_DOWN:
          if (selected == savedMaps.size() - 1)
            selected = 0;
          else
            selected = selected + 1;
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
        phy::Body player = phy::Body(File::getPoint(savedMaps[selected]),
                                     phy::Vector(0, 0), phy::Vector(0, 0));
        Statistics stats = File::getStatistics(savedMaps[selected]);
        Manager manager = Manager(map);
        manager.set_entities_status(
            current_chunk, File::getEntitiesStatus(savedMaps[selected]));
        // We need to implement the market save
        Market market = Market();
        market.set_save(File::getMarketSave(savedMaps[selected]));
        play(map, current_chunk, player, stats, manager, market);
      }
    }
  } while (deleted);
}

bool Game::pauseGame(Map &map, int &current_chunk, phy::Body &player,
                     Statistics &stats, Manager &manager, Market &market) {
  this->screen->nodel(false);

  Draw local_screen(SCREEN_HEIGHT, 60, 0, (SCREEN_WIDTH - 60) / 2);

  bool resumed = false;
  bool exit = false;

  while (!resumed) {

    local_screen.clearwithoutbox();
    local_screen.drawBox();
    local_screen.drawCenterText(3, "Game Paused");
    const int max_options = 5;
    nostd::string options[max_options] = {"Resume", "Market", "Settings",
                                          "Save", "Exit"};
    int selected = 0;
    bool choose = false;

    this->screen->drawStats(stats);
    this->screen->redraw();
    this->screen->noOutRefresh();
    local_screen.noOutRefresh();
    Screen::update();

    while (!choose) {
      for (int i = 0; i < max_options; i++) {
        local_screen.drawSquareAround(options[i], 20 + 4 * i,
                                      30 - (options[i].length() / 2));
      }
      local_screen.attrOn(COLOR_PAIR(1));
      local_screen.drawText(20 + 4 * selected,
                            30 - (options[selected].length() / 2),
                            options[selected]);
      local_screen.attrOff(COLOR_PAIR(1));
      switch (local_screen.getinput()) {
      case KEY_UP:
        if (selected == 0)
          selected = max_options - 1;
        else
          selected = selected - 1;
        break;
      case KEY_DOWN:
        if (selected == max_options - 1)
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
    local_screen.refreshScreen();
    Save save = Save();
    switch (selected) {
    case 0: {
      this->screen->nodel(true);
      local_screen.deleteWin();
      resumed = true;
      break;
    }
    case 1: {
      market.open(stats);
      break;
    }
    case 2: {
      this->settings.drawFirstSettings(this->audio);
      break;
    }
    case 3: {
      save.saveNewGame(map, current_chunk, player, stats, manager, market);
      break;
    }
    case 4: {
      local_screen.clearScreen();
      local_screen.deleteWin();
      this->screen->redraw();
      this->screen->refreshScreen();

      save.quitGame(map, current_chunk, player, stats, manager, market);

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

void Game::over() {
  this->screen->nodel(false);
  Draw over_win(8, 50);
  over_win.drawBox();
  over_win.drawCenterText(2, "You died...");
  over_win.attrOn(COLOR_PAIR(1));
  over_win.drawCenterText(5, "Keep going but with penalities");
  over_win.attrOn(COLOR_PAIR(1));
  over_win.refreshScreen();

  int input;
  do {
    input = over_win.getinput();
  } while (input != 10);

  over_win.eraseScreen();
  over_win.deleteWin();
  this->screen->nodel(true);
}

#ifdef USE_HACK

void Game::hack(int &current_chunk, Statistics &stats) {
  Draw hack(20, 50);
  hack.attrOn(COLOR_PAIR(2));
  hack.drawBox();
  hack.drawCenterText(2, "Hack Menu");
  hack.drawCenterText(4, "Only use for development purposes!");
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
  switch (x) {
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
  case 's': // set all custom
  {

    hack.eraseScreen();
    hack.drawCenterText(2, "Super secret menu");
    hack.drawCenterText(4, "WARNING: this menu is for skilled developers!");
    nostd::string options[4] = {"1. Set life", "2. Set coins", "3. Set jump",
                                "4. Set level"};
    for (int i = 0; i < 4; i++) {
      hack.drawText(7 + 2 * i, 7, options[i]);
    }
    hack.refreshScreen();

    int secret = hack.getinput();
    switch (secret) {
    case '1': {
      hack.eraseScreen();
      hack.drawCenterText(2, "Set life");
      int custom = setCustom(&hack);
      if (custom != -1)
        stats.setHearts(custom);
      break;
    }
    case '2': {
      hack.eraseScreen();
      hack.drawCenterText(2, "Set coins");
      int custom = setCustom(&hack);
      if (custom != -1)
        stats.setCoins(custom);
      break;
    }
    case '3': {
      hack.eraseScreen();
      hack.drawCenterText(2, "Set jump");
      int custom = setCustom(&hack);
      if (custom != -1)
        stats.setJumps(custom);
      break;
    }
    case '4': {
      hack.eraseScreen();
      hack.drawCenterText(2, "Set level");
      int custom = setCustom(&hack);
      if (custom != -1)
        current_chunk = custom;
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

int Game::setCustom(Draw *hack) {
  int a = hack->getinput();
  nostd::string set_chunk;
  while (a != 10 && a != 27) {
    // controlla se l'input è un numero
    if (a >= 48 && a <= 57)
      set_chunk = set_chunk + nostd::to_string(char(a));
    // se è backspace cancella l'ultimo carattere
    else if (a == 127)
      set_chunk = set_chunk.substr(0, set_chunk.length() - 1);
    hack->clearLine(4, 0);
    hack->drawCenterText(4, set_chunk);
    a = hack->getinput();
  }
  if (a == 27)
    return -1;
  else
    return stoi(set_chunk);
}
#endif
