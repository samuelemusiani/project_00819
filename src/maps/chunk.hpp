#include "platform.hpp"
#include "../../etc/nostd/vector.hpp"
#include "../engine/random.hpp"
#include <vector>
#ifndef MAPS_CHUNK
#define MAPS_CHUNK

class Chunk
{
    private:
        nostd::vector<Platform> platforms;
    public:
        void add_platform(phy::Point pos, int len);
        bool is_there_a_platform(phy::Point pos);
        nostd::vector<Platform>* get_platforms();
};

#endif
