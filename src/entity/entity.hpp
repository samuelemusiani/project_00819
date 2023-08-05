/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Ayache Omar #0001068895
 *
 * entity.hpp: Class that describe
 * a generic entity in the game
 */

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
