/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Ayache Omar #0001068895
 *
 * bullet.hpp: Class that implements
 * a bullet extending Entity
 */

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
