#include "bullet.hpp"

Bullet::Bullet()
    : Entity(), direction(false)
{

}

Bullet::Bullet(const char* id, phy::Point p, int direction)
    : Entity(id, p), direction(direction)
{

}

bool Bullet::get_direction()
{
    return this->direction;
}
