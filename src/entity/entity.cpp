#include "entity.hpp"
#include <cstring>

Entity::Entity(phy::Point p)
    : _position(p)
{

}

void Entity::set_position(phy::Point p)
{
    this->_position = p;
}

phy::Point Entity::get_position()
{
    return(this->_position);
}
