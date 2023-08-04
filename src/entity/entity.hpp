#include "../physics/precisePoint.hpp"

#ifndef ENTITY_ENTITY
#define ENTITY_ENTITY

class Entity {
protected:
  phy::PrecisePoint _position;

public:
  Entity(phy::PrecisePoint p);
  Entity(phy::Point p);

  void set_position(phy::PrecisePoint p);
  void set_position(phy::Point p);
  phy::PrecisePoint get_precise_position();
  phy::Point get_position();
};
#endif
