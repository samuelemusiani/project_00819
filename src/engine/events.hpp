#include "../market/ability.hpp"
#include "../physics/point.hpp"
#include "manager.hpp"

#ifndef ENGINE_EVENTS
#define ENGINE_EVENTS

struct drawable {
  char val;
  phy::Point pos;
  drawable *next;
};

class Events {
private:
  unsigned long long int _time;
  unsigned long long int _start;

  drawable *_to_draw;

  drawable *head_insert(drawable *head, char val, phy::Point pos);

public:
  Events();

  void make_ability_happen(Ability ability, Manager &manager,
                           phy::Point player_pos);
  void refresh();
  void draw(Draw* screen);
};

#endif
