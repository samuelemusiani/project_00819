#include "ability.hpp"
#include <cstring>

Ability::Ability() : _name("Not set"), _price(20) {}

Ability::Ability(nostd::string name, int price, int type) {
  this->_name = name;
  this->_price = price;
  this->_type = type;
}

nostd::string Ability::get_name() { return this->_name; }

int Ability::get_price() { return this->_price; }

int Ability::get_type() { return this->_type; }
