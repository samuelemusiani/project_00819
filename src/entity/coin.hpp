#include "entity.hpp"

#ifndef ENTITY_COIN
#define ENTITY_COIN

class Coin : public Entity {
    protected:
        bool collected;

    public:
        Coin(phy::Point p);

        void make_collected();
        bool is_collected();

};
#endif
