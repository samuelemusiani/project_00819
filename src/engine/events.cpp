/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Ayache Omar #0001068895
 *
 * events.cpp: Class that implements
 * the abilities in game
 */

#include "events.hpp"

Events::Events() : _time(0), _start(0), _cooldown(0) {}

void Events::make_ability_happen(Ability ability, Manager &manager,
                                 phy::Point player_pos, int chunk) {
  if (this->_start == 0 && this->_cooldown == 0) {
    switch (ability.get_type()) {
    case 0: { // Shild
      manager.make_player_invincible(true);
      this->_ability_type = 0;
      this->_start = this->_time;
      break;
    }
    case 1: {
      list_enemies l = manager.get_all_enemies_in_chunk(chunk);
      while (l != nullptr) {
        if (l->val.get_type() == 0)
          l->val.kill();
        else
          l->val.set_type(l->val.get_type() - 1);

        l = l->next;
      }
      this->_ability_type = 1;
      this->_cooldown = this->_time;
      break;
    }
    case 2: {
      manager.stop_time();
      this->_ability_type = 2;
      this->_start = this->_time;
      break;
    }
    default:
      break;
    }
  }
}

nostd::string Events::get_indicator() {
  nostd::string s;

  int indicator = 10;

  if (this->_cooldown != 0) {
    unsigned long long int diff = this->_time - this->_cooldown;
    switch (this->_ability_type) {
    case 0:
      if (diff >= 1000)
        this->_cooldown = 0;

      indicator = (int)diff * 10 / 1000;
      break;
    case 1:
      if (diff >= 2000)
        this->_cooldown = 0;

      indicator = (int)diff * 10 / 2000;
      break;
    case 2:
      if (diff >= 1000)
        this->_cooldown = 0;

      indicator = (int)diff * 10 / 1000;
      break;
    default:
      indicator = 10;
      break;
    }
  } else if (this->_start != 0) {
    unsigned long long int diff = this->_time - this->_start;
    switch (this->_ability_type) {
    case 0:
      indicator = 10 - ((int)diff * 10 / 500);
      break;
    case 2:
      indicator = 10 - ((int)diff * 10 / 1000);
      break;
    default:
      indicator = 10;
      break;
    }
  }

  for (int i = 0; i < indicator; i++)
    s.push_back('>');

  return s;
}

void Events::update(Manager &manager) {
  unsigned long long int diff = this->_time - this->_start;
  if (this->_start != 0) {
    switch (this->_ability_type) {
    case 0:
      if (diff >= 500) {
        manager.make_player_invincible(false);
        this->_start = 0;
        this->_cooldown = this->_time;
      }
      break;
    case 2:
      if (diff >= 1000) {
        manager.unstop_time();
        this->_start = 0;
        this->_cooldown = this->_time;
      }
      break;
    default:
      break;
    }
  }

  this->_time++;
}
