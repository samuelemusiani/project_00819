#include "../../etc/nostd/string.hpp"
#include "../physics/point.hpp"

//coins are just entity with $ as id

#ifndef ENTITY_ENTITY
#define ENTITY_ENTITY

class Entity {
protected:
  nostd::string id;
  phy::Point p;
public:

  Entity(nostd::string id, phy::Point p);//constructor for coins
  Entity(nostd::string id, phy::Point p, int hp, int ms, int damg);//constructor for enemies
  void init_entity(nostd::string id, phy::Point p);
  void set_point(phy::Point p);
  int get_x();
  int get_y();
  char get_id();

};
#endif
