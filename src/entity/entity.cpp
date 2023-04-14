#include "entity.hpp"


Entity::Entity (nostd::string id, phy::Point p)
{

  this->init_entity(id, p);

}

void Entity::init_entity(nostd::string id, phy::Point p)
{

  this->id = id;
  this->set_point(p);

}

void Entity::set_point(phy::Point p)
{

  this->p = p;

}
