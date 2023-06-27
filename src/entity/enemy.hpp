#include "entity.hpp"
#include "../maps/chunk.hpp"

#ifndef ENTITY_ENEMY
#define ENTITY_ENEMY

//enum DIRECTION_POSSIBILITY {dx, sx};

class Enemy : public Entity {
    protected:

        int hp;
        double ms;
        int damg;
        //DIRECTION_POSSIBILITY dir;
        bool dir;
        bool isAlive;

    public:

        Enemy(const char* id, phy::Point p, int hp, int ms, int damg) ;
        Enemy();

        void init_enemy(int hp, int ms, int damg);
        void set_hp(int hp);
        void got_hit(int damGot);
        void set_state(bool s);
        //void set_direction(DIRECTION_POSSIBILITY dir);
        void set_direction(bool dir);
        bool canMove(Chunk chunk);
        bool isItAlive();
        //DIRECTION_POSSIBILITY get_direction();
        bool get_direction();


};
#endif
