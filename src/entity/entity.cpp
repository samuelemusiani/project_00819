#include "entity.hpp"


Entity::Entity (char id, phy::Point p)
{

  this->init_entity(id, p);

}

Entity::Entity(){}

void Entity::init_entity(char id, phy::Point p)
{

  this->id = id;
  this->set_point(p);

}

void Entity::set_point(phy::Point p)
{

  this->p = p;

}

int Entity::get_y() {

  return(this->p.get_yPosition());

}

int Entity::get_x() {

  return(this->p.get_xPosition());

}

char Entity::get_id() {

  return(this->id);

}

phy::Point Entity::get_pos() {

  return(this->p);

}
