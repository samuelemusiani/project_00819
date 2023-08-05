/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Ayache Omar #0001068895
 *
 * ability.hpp: Class that describe
 * an ability
 */

#include "../../etc/nostd/string.hpp"

#ifndef MARKET_ABILITY
#define MARKET_ABILITY

class Ability {
private:
  nostd::string _name;

  int _price;
  int _type;

public:
  Ability();
  Ability(nostd::string name, int price, int type);

  nostd::string get_name();

  int get_price();
  int get_type();
};

#endif
