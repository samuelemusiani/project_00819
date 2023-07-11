#include "gun.hpp"
#include "ability.hpp"

#ifndef MARKET_MARKET
#define MARKET_MARKET

const int MARKET_MAX_GUN = 8;
const int MARKET_MAX_ABILITY  = 5;
const int MARKET_MAX_SUBMENUS = 3;

class Market
{
    private:
        Gun current_gun;
        Ability current_ability;

        char summenues[MARKET_MAX_SUBMENUS][15] = {"Guns", "Abilities", "Health"};

        Gun all_guns[MARKET_MAX_GUN];
        Ability all_abilities[MARKET_MAX_ABILITY];

    public:
        Market();

        void draw();
};

#endif
