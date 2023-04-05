#include "platform.hpp"

#define MAX_PLATFORMS 25

class Chunk
{
    private:
        Platform* platforms = new Platform[MAX_PLATFORMS];
        int usedPlatforms;
    public:
        Chunk();
        void add_platform(phy::Point pos, int len);
        bool is_there_a_platform(phy::Point pos);
        Platform* get_platforms();
};
