#include "ability.hpp"
#include <cstring>

Ability::Ability()
    : _name("Not set")
{

}

Ability::Ability(const char* n)
{
    strcpy(this->_name, n);
}

const char* Ability::get_name()
{
    return this->_name;
}
