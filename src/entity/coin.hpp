#include "entity.hpp"

#ifndef ENTITY_COIN
#define ENTITY_COIN

class Coin : public Entity {
protected:

  int value;
  bool alredyCollected;

public:

  Coin(nostd::string id, phy::Point p, int value);
  Coin();
  void init_coin(int value);
  int get_value();
  void set_state(bool s);

};
#endif
