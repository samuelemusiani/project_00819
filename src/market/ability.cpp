#include "ability.hpp"
#include <cstring>

Ability::Ability()
    : _name("Not set"), _price(20)
{

}

Ability::Ability(nostd::string n)
{
    this->_name = n;
}

nostd::string Ability::get_name()
{
    return this->_name;
}

int Ability::get_price()
{
    return this->_price;
}
