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
        int current_gun;
        int current_ability;

        nostd::string summenues[MARKET_MAX_SUBMENUS] = {"Guns", "Abilities", "Health"};

        Gun all_guns[MARKET_MAX_GUN];
        Ability all_abilities[MARKET_MAX_ABILITY];

        void set_current_gun();
        void set_current_ability();
    public:
        Market();

        Gun get_current_gun();
        Ability get_current_ability();

        void draw();
};

#endif
