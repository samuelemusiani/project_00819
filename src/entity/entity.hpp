#include "../physics/point.hpp"

#ifndef ENTITY_ENTITY
#define ENTITY_ENTITY

class Entity
{
    protected:
        phy::Point _position;

    public:
        Entity(phy::Point p);

        void set_position(phy::Point p);
        phy::Point get_position();

};
#endif
