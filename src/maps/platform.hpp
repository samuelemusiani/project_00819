#include "../physics/point.hpp"

#ifndef MAPS_PLATFORM
#define MAPS_PLATFORM

class Platform
{
    private:
        phy::Point position;
        int length;
    public:
        Platform();
        Platform(phy::Point pos,int len);

        void set_position(phy::Point x);
        void set_length(int len);

        phy::Point get_position();
        int get_length();
};

#endif
