#include "../market/ability.hpp"
#include "../physics/point.hpp"
#include "manager.hpp"

#ifndef ENGINE_EVENTS
#define ENGINE_EVENTS

struct drawable {
  char val;
  phy::Point pos;
  int type;
  drawable *next;
};

class Events {
private:
  unsigned long long int _time;

  unsigned long long int _start;
  unsigned long long int _cooldown;
  int _ability_type;

public:
  Events();

  void make_ability_happen(Ability ability, Manager &manager,
                           phy::Point player_pos, int chunk);
  nostd::string get_indicator();
  void update(Manager &manager);
};

#endif
