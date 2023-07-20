#include "bullet.hpp"

Bullet::Bullet(phy::Point p, phy::Vector direction, int type)
    : Entity(p), _direction(direction), _type(type) {}

phy::Vector Bullet::get_direction() { return this->_direction; }

int Bullet::get_type() { return this->_type; }

int Bullet::get_bullet_damage(int bullet_type) {
  switch (bullet_type) {
  case 0:
    return 1;
  case -1:
    return 2;
  case 1:
    return 2;
  case 2:
    return 4;
  default:
    return 1;
  }
}
