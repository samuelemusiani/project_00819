#include "../../ect/nostd/string.hpp"
#include "../physics/point.hpp"

//coin are just entity with $ as id

#ifndef ENTITY_ENTITY
#define ENTITY_ENTITY

class Entity : public Manager {
protected:
  nostd::string id;
  phy::Point p;
public:

  Entity(nostd::string id, phy::Point p);
  Entity(nostd::string id, phy::Point p, int hp, int ms, int damg);
  void init_entity(nostd::string id, phy::Point p);
  void set_point(phy::Point p);

}
#endif
