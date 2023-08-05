/*
 * Alma Mater Studiorum - University of Bologna
 * First cycle degree in Computer Science
 * Computer Programming - 00819
 *
 * Author: Ayache Omar #0001068895
 *
 * ability.cpp: Class that describe
 * an ability
 */

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
