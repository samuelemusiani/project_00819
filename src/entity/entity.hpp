#include "../physics/point.hpp"

#ifndef ENTITY_ENTITY
#define ENTITY_ENTITY

class Entity
{
    protected:
        char id[10];
        phy::Point p;

    public:
        Entity(const char* id, phy::Point p);
        Entity();
        void init_entity(const char* id, phy::Point p);
        void set_point(phy::Point p);
        int get_x();
        int get_y();
        phy::Point get_point();
        const char* get_id();

};
#endif
