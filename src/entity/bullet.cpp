#include "bullet.hpp"

Bullet::Bullet(phy::Point p, phy::Vector velocity, int type)
    : Entity(p), _velocity(velocity), _type(type) {}

phy::Vector Bullet::get_velocity() { return this->_velocity; }

int Bullet::get_type() { return this->_type; }

void Bullet::set_velocity(phy::Vector velocity) { this->_velocity = velocity; }

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
