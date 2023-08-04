#include "../physics/vector.hpp"
#include "entity.hpp"

#ifndef ENTITY_BULLET
#define ENTITY_BULLET

class Bullet : public Entity {
private:
  phy::Vector _velocity;
  int _type;

public:
  Bullet(phy::Point p, phy::Vector velocity, int type);

  phy::Vector get_velocity();
  int get_type();

  void set_velocity(phy::Vector velocity);

  // This is horrible, but I don't see another SIMPLE way of doin it
  static int get_bullet_damage(int bullet_type);
};

#endif
