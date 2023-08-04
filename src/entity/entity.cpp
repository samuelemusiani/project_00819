#include "entity.hpp"
#include <cstring>

Entity::Entity(phy::PrecisePoint p) : _position(p) {}

Entity::Entity(phy::Point p) : _position(p) {}

void Entity::set_position(phy::PrecisePoint p) { this->_position = p; }

void Entity::set_position(phy::Point p) { this->_position = p; }

phy::Point Entity::get_position() {
  return (phy::Point(this->_position.get_xPosition(),
                     this->_position.get_yPosition()));
}

phy::PrecisePoint Entity::get_precise_position() { return (this->_position); }
