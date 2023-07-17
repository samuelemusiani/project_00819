#include "gun.hpp"
#include <cstring>

Gun::Gun()
    : _name("Not set"), _price(10), _reloading_time(10), _bullet_type(0) {}

Gun::Gun(nostd::string name, int price, int bullet_type, int reloading_time) {
  this->_name = name;
  this->_price = price;
  this->_bullet_type = bullet_type;
  this->_reloading_time = reloading_time;
}

nostd::string Gun::get_name() { return this->_name; }

int Gun::get_price() { return this->_price; }

int Gun::get_bullet_type() { return this->_bullet_type; }

int Gun::get_reloading_time() { return this->_reloading_time; }
