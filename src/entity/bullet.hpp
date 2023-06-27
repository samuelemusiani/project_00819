#include "entity.hpp"

#ifndef ENTITY_BULLET
#define ENTITY_BULLET

class Bullet : public Entity 
{
    private:
        bool direction;

    public:
        Bullet();
        Bullet(const char* id, phy::Point p, int direction);

        bool get_direction();
};

#endif
