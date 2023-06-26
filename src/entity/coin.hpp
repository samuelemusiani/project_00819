#include "entity.hpp"

#ifndef ENTITY_COIN
#define ENTITY_COIN

class Coin : public Entity {
protected:

  int value;
  bool alredyCollected;

public:
  //We need to use a wider character for storing the coins signs
  Coin(const char* id, phy::Point p, int value);
  Coin();
  
  void init_coin(int value);
  int get_value();
  void set_state(bool s);

};
#endif
