#include "platform.hpp"

#define MAX_PLATFORMS 25

class Chunk
{
    private:
        static Platform platforms[MAX_PLATFORMS];
        int usedPlatforms;
    public:
        Chunk();
        void add_platform(int x, int y, int len);
        bool is_there_a_platform(int x, int y);
        Platform* get_platforms(int n);
};
