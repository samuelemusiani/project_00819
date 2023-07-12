#include "gun.hpp"
#include <cstring>

Gun::Gun()
    : _name("Not set"), _damage(1)
{

}

Gun::Gun(nostd::string n)
    : _damage(1)
{
    this->_name = n;
}

Gun::Gun(nostd::string n, int d)
{
    this->_name = n;
    this->_damage = d;
}


nostd::string Gun::get_name()
{
    return this->_name;
}

int Gun::get_damage()
{
    return this->_damage;
}
