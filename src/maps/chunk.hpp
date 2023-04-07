#include "platform.hpp"
#include <vector>
#ifndef MAPS_CHUNK
#define MAPS_CHUNK

class Chunk
{
    private:
        std::vector<Platform> platforms;
    public:
        void add_platform(phy::Point pos, int len);
        bool is_there_a_platform(phy::Point pos);
        std::vector<Platform>* get_platforms();
};

#endif
