#include "chunk.hpp"
#define NUM_MAPS 20

class Map
{
    private:
        Chunk possible_chunks[NUM_MAPS];
        void initialize_chunks();

    public:
        Map();
        Chunk get_chunk();
};
