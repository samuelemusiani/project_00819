#include "../../etc/nostd/string.hpp"

#ifndef MARKET_ABILITY
#define MARKET_ABILITY

class Ability
{
    private:
        nostd::string _name;

        int _price;

    public:
        Ability();
        Ability(nostd::string n);
        Ability(nostd::string n, int p);

        nostd::string get_name();

        int get_price();
};

#endif
