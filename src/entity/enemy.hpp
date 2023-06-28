#include "entity.hpp"
#include "../maps/chunk.hpp"

#ifndef ENTITY_ENEMY
#define ENTITY_ENEMY

class Enemy : public Entity {
    protected:
        int _damage;
        bool _direction;
        bool _alive;
        int _type;

    public:
        Enemy(int type, phy::Point p, bool direction) ;

        int get_damage();
        bool get_direction();
        int get_type();

        void set_direction(bool dir);

        bool can_move(Chunk chunk);
        bool is_alive();

        void kill();
        void move();
};
#endif
