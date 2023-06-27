#include "entity.hpp"
#include <cstring>

Entity::Entity(const char* id, phy::Point p)
{
    this->init_entity(id, p);
}

Entity::Entity()
{}

void Entity::init_entity(const char* id, phy::Point p)
{
    // char tmp[2] = "$";
    // strcpy(this->id, tmp);
    strcpy(this->id, id);
    this->set_point(p);
}

void Entity::set_point(phy::Point p)
{
    this->p = p;
}

int Entity::get_y()
{
    return(this->p.get_yPosition());
}

int Entity::get_x()
{
    return(this->p.get_xPosition());
}

const char* Entity::get_id()
{
    return(this->id);
}

phy::Point Entity::get_position()
{
    return(this->p);
}
