#include "entity.hpp"

#ifndef ENTITY_BULLET
#define ENTITY_BULLET

class Bullet : public Entity 
{
    private:
        bool _direction;
        int _type;

    public:
        Bullet(phy::Point p, bool direction, int type);

        bool get_direction();
        int get_type();
};

#endif
