#include "entity.hpp"
#include "../maps/chunk.hpp"

#ifndef ENTITY_ENEMY
#define ENTITY_ENEMY

//enum DIRECTION_POSSIBILITY {dx, sx};

class Enemy : public Entity {
    protected:
        int _damage;
        bool _direction;
        bool _alive;

    public:

        Enemy(const char* id, phy::Point p, int damage) ;
        Enemy();

        int get_damage();
        bool get_direction();

        void set_direction(bool dir);

        bool can_move(Chunk chunk);
        bool is_alive();

        void kill();
};
#endif
