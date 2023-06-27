#include "entity.hpp"

#ifndef ENTITY_COIN
#define ENTITY_COIN

class Coin : public Entity {
    protected:
        int value;
        bool collected;

    public:
        //We need to use a wider character for storing the coins signs
        Coin(const char* id, phy::Point p, int value);
        Coin();

        int get_value();
        void make_collected();
        bool is_collected();

};
#endif
