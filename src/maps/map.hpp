#include "chunk.hpp"

#ifndef MAPS_MAP
#define MAPS_MAP

#define NUM_MAPS 20

class Map
{
    private:
        Chunk possible_chunks[NUM_MAPS];
        void initialize_chunks();

    public:
        Map();
        Chunk get_chunk(int n);
};

#endif
