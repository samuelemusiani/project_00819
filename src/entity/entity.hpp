#include "../../etc/nostd/string.hpp"
#include "../physics/point.hpp"
//#include "enemy.hpp"

//coins are just entity with $ as id

#ifndef ENTITY_ENTITY
#define ENTITY_ENTITY

class Entity {
protected:
  nostd::string id;
  phy::Point p;
public:

  Entity(nostd::string id, phy::Point p);
  Entity();
  void init_entity(nostd::string id, phy::Point p);
  void set_point(phy::Point p);
  int get_x();
  int get_y();
  phy::Point get_pos();
  nostd::string get_id();

};
#endif
