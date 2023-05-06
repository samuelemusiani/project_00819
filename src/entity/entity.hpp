#include "../physics/point.hpp"

//coins are just entity with $ as id

#ifndef ENTITY_ENTITY
#define ENTITY_ENTITY

class Entity {
protected:
  char id;
  phy::Point p;
public:

  Entity(char id, phy::Point p);
  Entity();
  void init_entity(char id, phy::Point p);
  void set_point(phy::Point p);
  int get_x();
  int get_y();
  phy::Point get_point();
  char get_id();

};
#endif
