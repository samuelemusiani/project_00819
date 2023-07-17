#include "bullet.hpp"

Bullet::Bullet(phy::Point p, bool direction, int type)
    : Entity(p), _direction(direction), _type(type)
{

}

bool Bullet::get_direction()
{
    return this->_direction;
}

int Bullet::get_type()
{
    return this->_type;
}
