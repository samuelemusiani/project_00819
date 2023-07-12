#include "ability.hpp"
#include <cstring>

Ability::Ability()
    : _name("Not set")
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
