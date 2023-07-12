#include "gun.hpp"
#include <cstring>

Gun::Gun()
    : _name("Not set"), _damage(1), _price(10)
{

}

Gun::Gun(nostd::string n)
    : Gun(n, 1)
{
}

Gun::Gun(nostd::string n, int d)
   : Gun(n, d, 0) 
{
}

Gun::Gun(nostd::string n, int d, int p)
{
    this->_name = n;
    this->_damage = d;
    this->_price = p;
}

nostd::string Gun::get_name()
{
    return this->_name;
}

int Gun::get_damage()
{
    return this->_damage;
}

int Gun::get_price()
{
    return this->_price;
}
