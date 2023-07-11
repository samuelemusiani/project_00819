#include "gun.hpp"
#include <cstring>

Gun::Gun()
    : _name("Not set"), _damage(1)
{

}

Gun::Gun(const char* n)
    : _damage(1)
{
    strcpy(this->_name, n);
}

Gun::Gun(const char* n, int d)
{
    strcpy(this->_name, n);
    this->_damage = d;
}


const char* Gun::get_name()
{
    return this->_name;
}

int Gun::get_damage()
{
    return this->_damage;
}
