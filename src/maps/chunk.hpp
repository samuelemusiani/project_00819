#include "platform.hpp"

#define MAX_PLATFORMS 25

class Chunk
{
    private:
        Platform platforms[MAX_PLATFORMS];
        int usedPlatforms;
    public:
        Chunk();
        void add_platform(int x, int y, int len);
        bool is_there_a_platform(int x, int y);
};