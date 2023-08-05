/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Ayache Omar #0001068895
 *
 * coin.hpp: Class that implements
 * a coin extending Entity
 */

#include "entity.hpp"

#ifndef ENTITY_COIN
#define ENTITY_COIN

class Coin : public Entity {
protected:
  bool collected;

public:
  Coin(phy::Point p);

  void make_collected();
  bool is_collected();
};
#endif
